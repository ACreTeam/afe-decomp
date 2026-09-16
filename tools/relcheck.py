#!/usr/bin/env python3
"""REL-aware checker for GameCube/Wii decompilation projects.

Compares an original REL against a rebuilt REL, including:
  * REL header and section layout
  * section payload bytes
  * import table ordering
  * decoded relocation records
  * raw relocation stream encoding

Differences in section payloads and relocation *source locations* are mapped back
onto translation units using a DTK splits.txt. Self-REL relocation targets are
also mapped to a TU/symbol when possible.

Designed to be dependency-free (Python stdlib only).
"""
from __future__ import annotations

import argparse
import bisect
import hashlib
import json
import os
import re
import struct
import sys
from collections import defaultdict
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Iterable, Optional


RELOC_NAMES = {
    0: "R_PPC_NONE",
    1: "R_PPC_ADDR32",
    2: "R_PPC_ADDR24",
    3: "R_PPC_ADDR16",
    4: "R_PPC_ADDR16_LO",
    5: "R_PPC_ADDR16_HI",
    6: "R_PPC_ADDR16_HA",
    7: "R_PPC_ADDR14",
    8: "R_PPC_ADDR14_BRTAKEN",
    9: "R_PPC_ADDR14_BRNTAKEN",
    10: "R_PPC_REL24",
    11: "R_PPC_REL14",
    201: "R_DOLPHIN_NOP",
    202: "R_DOLPHIN_SECTION",
    203: "R_DOLPHIN_END",
}


def u32(data: bytes, off: int) -> int:
    if off < 0 or off + 4 > len(data):
        raise ValueError(f"u32 out of range at 0x{off:X}")
    return struct.unpack_from(">I", data, off)[0]


def u16(data: bytes, off: int) -> int:
    if off < 0 or off + 2 > len(data):
        raise ValueError(f"u16 out of range at 0x{off:X}")
    return struct.unpack_from(">H", data, off)[0]


def sha1(data: bytes) -> str:
    return hashlib.sha1(data).hexdigest()


@dataclass(frozen=True)
class RelHeader:
    module_id: int
    next_ptr: int
    prev_ptr: int
    section_count: int
    section_info_offset: int
    name_offset: int
    name_size: int
    version: int
    bss_size: int
    relocation_offset: int
    import_offset: int
    import_size: int
    prolog_section: int
    epilog_section: int
    unresolved_section: int
    bss_section: int
    prolog: int
    epilog: int
    unresolved: int
    align: Optional[int]
    bss_align: Optional[int]
    fix_size: Optional[int]


@dataclass(frozen=True)
class RelSection:
    index: int
    raw_offset: int
    offset: int
    flags: int
    executable: bool
    size: int


@dataclass(frozen=True)
class RelImport:
    index: int
    module_id: int
    relocation_offset: int


@dataclass(frozen=True)
class RelocEntry:
    file_offset: int
    delta: int
    type: int
    field_section: int
    addend: int
    source_section: Optional[int]
    source_offset: Optional[int]


@dataclass(frozen=True)
class Relocation:
    import_index: int
    module_id: int
    file_offset: int
    source_section: int
    source_offset: int
    type: int
    target_section: int
    addend: int

    def value_tuple(self) -> tuple[int, int, int]:
        return (self.type, self.target_section, self.addend)


@dataclass
class ParsedREL:
    path: Path
    data: bytes
    header: RelHeader
    sections: list[RelSection]
    imports: list[RelImport]
    relocation_entries: dict[int, list[RelocEntry]]
    relocations: list[Relocation]
    relocation_streams: dict[int, bytes]
    name: bytes


@dataclass(frozen=True)
class SplitRange:
    owner: str
    section: str
    start: int
    end: int


@dataclass
class SplitInfo:
    section_order: list[str]
    ranges_by_section: dict[str, list[SplitRange]]
    starts_by_section: dict[str, list[int]]
    extents: dict[str, int]

    def owner_at(self, section: str, offset: int) -> Optional[str]:
        ranges = self.ranges_by_section.get(section, [])
        starts = self.starts_by_section.get(section, [])
        if not ranges:
            return None
        i = bisect.bisect_right(starts, offset) - 1
        if i >= 0:
            r = ranges[i]
            if r.start <= offset < r.end:
                return r.owner
        # Overlap / same-start fallback, uncommon but cheap.
        for j in range(max(0, i - 2), min(len(ranges), i + 3)):
            r = ranges[j]
            if r.start <= offset < r.end:
                return r.owner
        return None

    def overlapping_owners(self, section: str, start: int, end: int) -> list[tuple[str, int]]:
        if end <= start:
            return []
        out: list[tuple[str, int]] = []
        for r in self.ranges_by_section.get(section, []):
            if r.end <= start:
                continue
            if r.start >= end:
                break
            n = max(0, min(end, r.end) - max(start, r.start))
            if n:
                out.append((r.owner, n))
        return out



@dataclass(frozen=True)
class MapContribution:
    section: str
    start: int
    size: int
    raw_owner: str
    owner: Optional[str]

    @property
    def end(self) -> int:
        return self.start + self.size


@dataclass
class LinkMapInfo:
    path: Path
    contributions_by_section: dict[str, list[MapContribution]]
    starts_by_section: dict[str, list[int]]
    by_owner_section: dict[tuple[str, str], list[MapContribution]]

    def owner_at(self, section: str, offset: int) -> Optional[str]:
        rows = self.contributions_by_section.get(section, [])
        starts = self.starts_by_section.get(section, [])
        if not rows:
            return None
        i = bisect.bisect_right(starts, offset) - 1
        for j in range(max(0, i - 2), min(len(rows), i + 3)):
            r = rows[j]
            if r.start <= offset < r.end:
                return r.owner
        return None

    def contribution_for(self, section: str, owner: str) -> Optional[MapContribution]:
        rows = self.by_owner_section.get((section, owner), [])
        if len(rows) == 1:
            return rows[0]
        return None


_MAP_SECTION_RE = re.compile(r"^(\.[A-Za-z0-9_.$]+) section layout\s*$")
_MAP_ROW_RE = re.compile(
    r"^\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+"
    r"\d+\s+(\.[A-Za-z0-9_.$]+)\s+(.+?)\s*$"
)


def _split_owner_object_names(owner: str) -> set[str]:
    """Possible linker-map object spellings for a split owner."""
    norm = owner.replace("\\", "/")
    p = Path(norm)
    suffix = p.suffix.lower()
    if suffix in (".c", ".cpp", ".cc", ".cxx", ".s", ".asm"):
        obj_rel = str(p.with_suffix(".o")).replace("\\", "/")
    else:
        obj_rel = norm
    names = {obj_rel, Path(obj_rel).name}
    # Some MW map outputs retain .obj for extracted objects, while generated
    # source objects are normally .o. Keep stem matching as a last resort only.
    names.add(Path(obj_rel).stem)
    return names


def parse_link_map(path: Path, splits: SplitInfo) -> LinkMapInfo:
    # Build conservative indexes. Basename/stem matches are accepted only when
    # unique, which avoids silently mapping two same-named TUs to one map row.
    exact: dict[str, set[str]] = defaultdict(set)
    basename: dict[str, set[str]] = defaultdict(set)
    stem: dict[str, set[str]] = defaultdict(set)
    all_owners = sorted({r.owner for rs in splits.ranges_by_section.values() for r in rs})
    for owner in all_owners:
        norm = owner.replace("\\", "/")
        p = Path(norm)
        suffix = p.suffix.lower()
        obj_rel = str(p.with_suffix(".o")).replace("\\", "/") if suffix in (".c", ".cpp", ".cc", ".cxx", ".s", ".asm") else norm
        exact[obj_rel.lower()].add(owner)
        basename[Path(obj_rel).name.lower()].add(owner)
        stem[Path(obj_rel).stem.lower()].add(owner)

    def resolve(raw: str) -> Optional[str]:
        r = raw.strip().strip('"').replace("\\", "/")
        # Map files can include archive(member.o) spellings.
        if "(" in r and r.endswith(")"):
            r = r.rsplit("(", 1)[1][:-1]
        keys = [
            (exact, r.lower()),
            (basename, Path(r).name.lower()),
            (stem, Path(r).stem.lower()),
        ]
        for table, key in keys:
            vals = table.get(key, set())
            if len(vals) == 1:
                return next(iter(vals))
        return None

    by_sec: dict[str, list[MapContribution]] = defaultdict(list)
    current: Optional[str] = None
    text = path.read_text(encoding="utf-8", errors="replace")
    for line in text.splitlines():
        sm = _MAP_SECTION_RE.match(line.strip())
        if sm:
            current = sm.group(1)
            continue
        m = _MAP_ROW_RE.match(line)
        if not m or current is None:
            continue
        start_s, size_s, _virt_s, input_section, raw_owner = m.groups()
        # The map contains one contribution row whose symbol is the input section,
        # followed by individual symbols from that contribution. Only retain the
        # former; symbol rows would otherwise look like overlapping objects.
        if input_section != current:
            continue
        by_sec[current].append(
            MapContribution(
                section=current,
                start=int(start_s, 16),
                size=int(size_s, 16),
                raw_owner=raw_owner.strip(),
                owner=resolve(raw_owner),
            )
        )

    starts: dict[str, list[int]] = {}
    by_owner: dict[tuple[str, str], list[MapContribution]] = defaultdict(list)
    for sec, rows in by_sec.items():
        rows.sort(key=lambda r: (r.start, r.size, r.raw_owner))
        starts[sec] = [r.start for r in rows]
        for r in rows:
            if r.owner:
                by_owner[(sec, r.owner)].append(r)
    return LinkMapInfo(path, dict(by_sec), starts, dict(by_owner))


def _split_range_lookup(splits: SplitInfo) -> dict[tuple[str, str], SplitRange]:
    out: dict[tuple[str, str], SplitRange] = {}
    dup: set[tuple[str, str]] = set()
    for sec, rows in splits.ranges_by_section.items():
        for r in rows:
            k = (sec, r.owner)
            if k in out:
                dup.add(k)
            else:
                out[k] = r
    for k in dup:
        out.pop(k, None)
    return out


def analyze_cascade_layout(
    expected: ParsedREL,
    rebuilt: ParsedREL,
    splits: SplitInfo,
    symbols: Optional[SymbolInfo],
    sec_names: dict[int, str],
    link_map: LinkMapInfo,
    max_details: int,
) -> dict:
    """Compare final RELs in TU-relative coordinates using a rebuilt linker map.

    Absolute REL offsets are intentionally *not* used as the primary key. A size
    error in one TU shifts every later TU, so absolute comparison massively
    over-counts downstream failures. This analysis maps expected locations via
    splits.txt and rebuilt locations via the linker map, then compares TU-relative
    payloads and relocations.
    """
    inv_sec = {name: idx for idx, name in sec_names.items()}
    split_lookup = _split_range_lookup(splits)
    out: dict = {
        "map": str(link_map.path),
        "mapped_contributions": 0,
        "unmapped_map_contributions": [],
        "layout_differences": [],
        "ignored_trailing_padding": [],
        "payload_tu_differences": [],
        "normalized_relocation_differences": [],
        "normalized_relocation_difference_count": 0,
        "normalized_relocation_by_module": {},
        "root_tu_summary": {},
        "root_tu_order": [],
    }
    root_stats: dict[str, dict[str, int]] = defaultdict(lambda: defaultdict(int))

    for sec, rows in link_map.contributions_by_section.items():
        for r in rows:
            if r.owner:
                out["mapped_contributions"] += 1
            elif len(out["unmapped_map_contributions"]) < max_details:
                out["unmapped_map_contributions"].append({
                    "section": sec, "start": r.start, "size": r.size, "raw_owner": r.raw_owner
                })

    def reloc_width(rel_type: int) -> int:
        if rel_type in (3, 4, 5, 6):
            return 2
        if rel_type in (1, 2, 7, 8, 9, 10, 11):
            return 4
        return 0

    expected_relocs_by_section: dict[int, list[Relocation]] = defaultdict(list)
    rebuilt_relocs_by_section: dict[int, list[Relocation]] = defaultdict(list)
    for rr in expected.relocations:
        expected_relocs_by_section[rr.source_section].append(rr)
    for rr in rebuilt.relocations:
        rebuilt_relocs_by_section[rr.source_section].append(rr)

    def mask_relocation_fields(buf: bytes, sites: list[tuple[int, int]]) -> bytes:
        if not sites:
            return buf
        b = bytearray(buf)
        for off, width in sites:
            if width <= 0:
                continue
            for i in range(max(0, off), min(len(b), off + width)):
                b[i] = 0
        return bytes(b)

    # TU-by-TU layout and payload. This is the key anti-cascade comparison.
    for sec, ranges in splits.ranges_by_section.items():
        sec_idx = inv_sec.get(sec)
        if sec_idx is None or sec_idx >= len(expected.sections) or sec_idx >= len(rebuilt.sections):
            continue
        esec, rsec = expected.sections[sec_idx], rebuilt.sections[sec_idx]
        if not esec.offset or not rsec.offset:
            continue
        ebytes = expected.data[esec.offset: esec.offset + esec.size]
        rbytes = rebuilt.data[rsec.offset: rsec.offset + rsec.size]
        for sr in ranges:
            mc = link_map.contribution_for(sec, sr.owner)
            if mc is None:
                continue
            exp_size = sr.end - sr.start
            size_delta = mc.size - exp_size
            start_delta = mc.start - sr.start
            ea_full = ebytes[sr.start:sr.end]
            rb_full = rbytes[mc.start:mc.end]

            # A DTK split range often includes linker-inserted zero padding up
            # to the next object boundary. The linker map reports only the
            # actual contribution. Ignore such zero-only tails as layout roots.
            padding_only = False
            if start_delta == 0 and 0 <= mc.size < exp_size:
                tail = ea_full[mc.size:]
                tail_has_reloc = any(
                    sr.start + mc.size <= rr.source_offset < sr.end
                    for rr in expected_relocs_by_section.get(sec_idx, [])
                )
                if tail and not any(tail) and not tail_has_reloc:
                    padding_only = True
                    out["ignored_trailing_padding"].append({
                        "owner": sr.owner,
                        "section": sec,
                        "expected_size": exp_size,
                        "object_size": mc.size,
                        "padding_bytes": exp_size - mc.size,
                    })

            if (size_delta and not padding_only) or start_delta:
                out["layout_differences"].append({
                    "owner": sr.owner,
                    "section": sec,
                    "expected_start": sr.start,
                    "rebuilt_start": mc.start,
                    "start_delta": start_delta,
                    "expected_size": exp_size,
                    "rebuilt_size": mc.size,
                    "size_delta": size_delta,
                })
                if size_delta and not padding_only:
                    root_stats[sr.owner]["size_delta"] = size_delta
                    root_stats[sr.owner]["size_error_bytes"] += abs(size_delta)

            # For padding-only differences compare the actual object bytes, not
            # the zero tail that belongs to link alignment.
            ea = ea_full[:mc.size] if padding_only else ea_full
            rb = rb_full

            # Relocation fields are reported independently below. Mask the union
            # of expected and rebuilt relocation sites here so a lost relocation
            # is not counted again as a payload-byte mismatch.
            sites: list[tuple[int, int]] = []
            for rr in expected_relocs_by_section.get(sec_idx, []):
                if sr.start <= rr.source_offset < sr.start + len(ea):
                    sites.append((rr.source_offset - sr.start, reloc_width(rr.type)))
            for rr in rebuilt_relocs_by_section.get(sec_idx, []):
                if mc.start <= rr.source_offset < mc.start + len(rb):
                    sites.append((rr.source_offset - mc.start, reloc_width(rr.type)))
            ea_cmp = mask_relocation_fields(ea, sites)
            rb_cmp = mask_relocation_fields(rb, sites)

            if ea_cmp != rb_cmp:
                runs = find_diff_runs(ea_cmp, rb_cmp)
                diff_bytes = sum(e - s for s, e in runs)
                root_stats[sr.owner]["payload_bytes"] += diff_bytes
                root_stats[sr.owner]["payload_runs"] += len(runs)
                item = {
                    "owner": sr.owner,
                    "section": sec,
                    "expected_start": sr.start,
                    "rebuilt_start": mc.start,
                    "expected_size": len(ea),
                    "rebuilt_size": len(rb),
                    "different_runs": len(runs),
                    "different_bytes_approx": diff_bytes,
                    "relocation_fields_masked": len(sites),
                    "expected_sha1": sha1(ea_cmp),
                    "rebuilt_sha1": sha1(rb_cmp),
                    "details": [],
                }
                for a, b in runs[:5]:
                    item["details"].append({
                        "start": a, "end": b,
                        "expected": hex_context(ea_cmp, a),
                        "rebuilt": hex_context(rb_cmp, a),
                    })
                out["payload_tu_differences"].append(item)

    # Normalize relocation source locations and self-REL targets by TU + relative
    # offset. This removes false missing/extra pairs caused solely by layout drift.
    def source_key(rel: Relocation, side: str):
        sec = sec_names.get(rel.source_section, f"section[{rel.source_section}]")
        if not sec.startswith("."):
            return (rel.module_id, sec, None, rel.source_offset), None, rel.source_offset
        if side == "expected":
            owner = splits.owner_at(sec, rel.source_offset)
            sr = split_lookup.get((sec, owner)) if owner else None
            base = sr.start if sr else None
        else:
            owner = link_map.owner_at(sec, rel.source_offset)
            mc = link_map.contribution_for(sec, owner) if owner else None
            base = mc.start if mc else None
        if owner is not None and base is not None:
            return (rel.module_id, sec, owner, rel.source_offset - base), owner, rel.source_offset - base
        return (rel.module_id, sec, None, rel.source_offset), owner, rel.source_offset

    def normalized_value(rel: Relocation, side: str):
        tgt_sec = sec_names.get(rel.target_section, f"section[{rel.target_section}]")
        if rel.module_id == expected.header.module_id and tgt_sec.startswith("."):
            if side == "expected":
                owner = splits.owner_at(tgt_sec, rel.addend)
                sr = split_lookup.get((tgt_sec, owner)) if owner else None
                if owner and sr:
                    return (rel.type, tgt_sec, "tu", owner, rel.addend - sr.start)
            else:
                owner = link_map.owner_at(tgt_sec, rel.addend)
                mc = link_map.contribution_for(tgt_sec, owner) if owner else None
                if owner and mc:
                    return (rel.type, tgt_sec, "tu", owner, rel.addend - mc.start)
        return (rel.type, tgt_sec, "raw", rel.addend)

    def nmap(rel: ParsedREL, side: str):
        d: dict[tuple, list[Relocation]] = defaultdict(list)
        meta: dict[tuple, tuple[Optional[str], int, str]] = {}
        for rr in rel.relocations:
            key, owner, rel_off = source_key(rr, side)
            d[key].append(rr)
            meta[key] = (owner, rel_off, sec_names.get(rr.source_section, f"section[{rr.source_section}]"))
        return d, meta

    em, emeta = nmap(expected, "expected")
    rm, rmeta = nmap(rebuilt, "rebuilt")
    module_counts: dict[int, int] = defaultdict(int)
    for key in sorted(set(em) | set(rm), key=str):
        ev, rv = em.get(key, []), rm.get(key, [])
        en = sorted(normalized_value(r, "expected") for r in ev)
        rn = sorted(normalized_value(r, "rebuilt") for r in rv)
        if en == rn:
            continue
        module_id = key[0]
        module_counts[module_id] += 1
        meta = emeta.get(key) or rmeta.get(key)
        owner, rel_off, sec = meta if meta else (None, 0, str(key[1]))
        kind = "changed" if ev and rv else ("missing" if ev else "extra")
        if owner:
            root_stats[owner][f"reloc_{kind}"] += max(len(ev), len(rv))
        if len(out["normalized_relocation_differences"]) < max_details:
            def fmt_vals(vals, side):
                result = []
                for rr in vals:
                    nv = normalized_value(rr, side)
                    item = {
                        "type": rr.type,
                        "type_name": RELOC_NAMES.get(rr.type, f"TYPE_{rr.type}"),
                        "target_section": nv[1],
                    }
                    if nv[2] == "tu":
                        item.update({"target_owner": nv[3], "target_relative_offset": nv[4]})
                    else:
                        item.update({"target_addend": nv[3]})
                    result.append(item)
                return result
            out["normalized_relocation_differences"].append({
                "kind": kind,
                "module_id": module_id,
                "source_section": sec,
                "source_owner": owner,
                "source_relative_offset": rel_off,
                "expected": fmt_vals(ev, "expected"),
                "rebuilt": fmt_vals(rv, "rebuilt"),
            })
    out["normalized_relocation_difference_count"] = sum(module_counts.values())
    out["normalized_relocation_by_module"] = {str(k): v for k, v in sorted(module_counts.items())}

    # Root ranking: size errors first, then normalized relocation differences,
    # then TU-local payload differences. Downstream absolute drift is excluded.
    ranked = []
    for owner, stats0 in root_stats.items():
        stats = dict(stats0)
        size_err = stats.get("size_error_bytes", 0)
        reloc_n = sum(v for k, v in stats.items() if k.startswith("reloc_"))
        payload = stats.get("payload_bytes", 0)
        score = size_err * 10**12 + reloc_n * 10**7 + min(payload, 9_999_999)
        ranked.append((score, owner, stats))
    ranked.sort(key=lambda x: (-x[0], x[1]))
    out["root_tu_order"] = [x[1] for x in ranked]
    out["root_tu_summary"] = {owner: {**stats, "score": score} for score, owner, stats in ranked}
    return out

@dataclass(frozen=True)
class Symbol:
    name: str
    section: str
    address: int
    size: Optional[int]
    scope: Optional[str]


@dataclass
class SymbolInfo:
    by_section: dict[str, list[Symbol]]
    starts_by_section: dict[str, list[int]]

    def symbol_at(self, section: str, offset: int) -> Optional[str]:
        symbols = self.by_section.get(section, [])
        starts = self.starts_by_section.get(section, [])
        if not symbols:
            return None
        i = bisect.bisect_right(starts, offset) - 1
        if i < 0:
            return None
        s = symbols[i]
        if s.size is not None and offset >= s.address + s.size:
            return None
        delta = offset - s.address
        return s.name if delta == 0 else f"{s.name}+0x{delta:X}"


def parse_rel(path: Path) -> ParsedREL:
    data = path.read_bytes()
    if len(data) < 0x40:
        raise ValueError(f"{path}: too small to be a REL ({len(data)} bytes)")

    version = u32(data, 0x1C)
    if version not in (1, 2, 3):
        raise ValueError(f"{path}: unsupported/suspicious REL version {version}")
    header_size = 0x40 if version == 1 else (0x48 if version == 2 else 0x4C)
    if len(data) < header_size:
        raise ValueError(f"{path}: truncated REL v{version} header")

    h = RelHeader(
        module_id=u32(data, 0x00),
        next_ptr=u32(data, 0x04),
        prev_ptr=u32(data, 0x08),
        section_count=u32(data, 0x0C),
        section_info_offset=u32(data, 0x10),
        name_offset=u32(data, 0x14),
        name_size=u32(data, 0x18),
        version=version,
        bss_size=u32(data, 0x20),
        relocation_offset=u32(data, 0x24),
        import_offset=u32(data, 0x28),
        import_size=u32(data, 0x2C),
        prolog_section=data[0x30],
        epilog_section=data[0x31],
        unresolved_section=data[0x32],
        bss_section=data[0x33],
        prolog=u32(data, 0x34),
        epilog=u32(data, 0x38),
        unresolved=u32(data, 0x3C),
        align=u32(data, 0x40) if version >= 2 else None,
        bss_align=u32(data, 0x44) if version >= 2 else None,
        fix_size=u32(data, 0x48) if version >= 3 else None,
    )

    if h.section_count > 0x1000:
        raise ValueError(f"{path}: unreasonable section count {h.section_count}")
    if h.section_info_offset + h.section_count * 8 > len(data):
        raise ValueError(f"{path}: section table out of range")
    if h.import_size % 8:
        raise ValueError(f"{path}: import table size 0x{h.import_size:X} is not 8-byte aligned")
    if h.import_offset + h.import_size > len(data):
        raise ValueError(f"{path}: import table out of range")

    sections: list[RelSection] = []
    for i in range(h.section_count):
        off = h.section_info_offset + i * 8
        raw = u32(data, off)
        size = u32(data, off + 4)
        # Two low bits are flags in known REL variants; bit 0 is executable.
        sec_off = raw & ~0x3
        flags = raw & 0x3
        if sec_off and sec_off + size > len(data):
            raise ValueError(
                f"{path}: section {i} out of range: offset 0x{sec_off:X}, size 0x{size:X}"
            )
        sections.append(RelSection(i, raw, sec_off, flags, bool(raw & 1), size))

    imports: list[RelImport] = []
    for i in range(h.import_size // 8):
        off = h.import_offset + i * 8
        imports.append(RelImport(i, u32(data, off), u32(data, off + 4)))

    relocation_entries: dict[int, list[RelocEntry]] = {}
    relocation_streams: dict[int, bytes] = {}
    relocations: list[Relocation] = []

    for imp in imports:
        pos = imp.relocation_offset
        if pos >= len(data):
            raise ValueError(f"{path}: import {imp.index} relocation offset 0x{pos:X} out of range")
        start = pos
        current_section: Optional[int] = None
        current_offset = 0
        entries: list[RelocEntry] = []
        # Guard against malformed files that never terminate.
        max_entries = (len(data) - pos) // 8 + 1
        for _ in range(max_entries):
            if pos + 8 > len(data):
                raise ValueError(f"{path}: truncated relocation list for import {imp.index}")
            delta = u16(data, pos)
            rtype = data[pos + 2]
            field_sec = data[pos + 3]
            addend = u32(data, pos + 4)

            src_sec_for_entry = current_section
            src_off_for_entry: Optional[int] = current_offset
            if rtype == 202:  # R_DOLPHIN_SECTION
                current_section = field_sec
                current_offset = 0
                src_sec_for_entry = current_section
                src_off_for_entry = 0
            elif rtype == 203:  # END
                src_sec_for_entry = current_section
                src_off_for_entry = current_offset
            else:
                current_offset += delta
                src_sec_for_entry = current_section
                src_off_for_entry = current_offset

            entry = RelocEntry(
                file_offset=pos,
                delta=delta,
                type=rtype,
                field_section=field_sec,
                addend=addend,
                source_section=src_sec_for_entry,
                source_offset=src_off_for_entry,
            )
            entries.append(entry)

            if rtype not in (201, 202, 203):
                if current_section is None:
                    raise ValueError(
                        f"{path}: relocation at 0x{pos:X} appears before R_DOLPHIN_SECTION"
                    )
                relocations.append(
                    Relocation(
                        import_index=imp.index,
                        module_id=imp.module_id,
                        file_offset=pos,
                        source_section=current_section,
                        source_offset=current_offset,
                        type=rtype,
                        target_section=field_sec,
                        addend=addend,
                    )
                )

            pos += 8
            if rtype == 203:
                relocation_entries[imp.index] = entries
                relocation_streams[imp.index] = data[start:pos]
                break
        else:
            raise ValueError(f"{path}: unterminated relocation list for import {imp.index}")

    name = b""
    if h.name_offset and h.name_size:
        end = h.name_offset + h.name_size
        if end <= len(data):
            name = data[h.name_offset:end]

    return ParsedREL(path, data, h, sections, imports, relocation_entries, relocations, relocation_streams, name)


_OWNER_RE = re.compile(r"^([^\s].*):\s*$")
_RANGE_RE = re.compile(
    r"^\s+(\.[A-Za-z0-9_.$]+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)"
)
_SECTION_DEF_RE = re.compile(r"^\s+(\.[A-Za-z0-9_.$]+)\s+type:")


def parse_splits(path: Path) -> SplitInfo:
    section_order: list[str] = []
    ranges_by_section: dict[str, list[SplitRange]] = defaultdict(list)
    owner: Optional[str] = None
    in_sections = False
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if line.strip() == "Sections:":
            in_sections = True
            owner = None
            continue
        if in_sections:
            m = _SECTION_DEF_RE.match(line)
            if m:
                section_order.append(m.group(1))
                continue
            if line.strip() == "":
                in_sections = False
                continue
        m = _OWNER_RE.match(line)
        if m and not line.startswith((" ", "\t")):
            label = m.group(1)
            if label != "Sections":
                owner = label
            continue
        m = _RANGE_RE.match(line)
        if m and owner:
            section = m.group(1)
            start = int(m.group(2), 16)
            end = int(m.group(3), 16)
            if end > start:  # empty markers do not own bytes
                ranges_by_section[section].append(SplitRange(owner, section, start, end))

    starts: dict[str, list[int]] = {}
    extents: dict[str, int] = {}
    for section, ranges in ranges_by_section.items():
        ranges.sort(key=lambda r: (r.start, r.end, r.owner))
        starts[section] = [r.start for r in ranges]
        extents[section] = max((r.end for r in ranges), default=0)
    return SplitInfo(section_order, dict(ranges_by_section), starts, extents)


_SYMBOL_RE = re.compile(
    r"^([^\s=]+)\s*=\s*(\.[A-Za-z0-9_.$]+):0x([0-9A-Fa-f]+);(?:\s*//\s*(.*))?$"
)
_SIZE_RE = re.compile(r"\bsize:0x([0-9A-Fa-f]+)\b")
_SCOPE_RE = re.compile(r"\bscope:([A-Za-z0-9_]+)\b")


def parse_symbols(path: Optional[Path]) -> Optional[SymbolInfo]:
    if not path or not path.exists():
        return None
    by_section: dict[str, list[Symbol]] = defaultdict(list)
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        m = _SYMBOL_RE.match(line.strip())
        if not m:
            continue
        name, section, addr_s, comment = m.groups()
        comment = comment or ""
        sm = _SIZE_RE.search(comment)
        scm = _SCOPE_RE.search(comment)
        by_section[section].append(
            Symbol(
                name=name,
                section=section,
                address=int(addr_s, 16),
                size=int(sm.group(1), 16) if sm else None,
                scope=scm.group(1) if scm else None,
            )
        )
    starts: dict[str, list[int]] = {}
    for section, symbols in by_section.items():
        symbols.sort(key=lambda s: (s.address, s.name))
        starts[section] = [s.address for s in symbols]
    return SymbolInfo(dict(by_section), starts)


def parse_section_overrides(items: list[str]) -> dict[int, str]:
    out: dict[int, str] = {}
    for item in items:
        if "=" not in item:
            raise ValueError(f"bad --section-index {item!r}; use .data=4 or 4=.data")
        a, b = item.split("=", 1)
        a, b = a.strip(), b.strip()
        if a.startswith("."):
            name, idx_s = a, b
        else:
            idx_s, name = a, b
        if not name.startswith("."):
            raise ValueError(f"bad section name in --section-index {item!r}")
        out[int(idx_s, 0)] = name
    return out


def infer_section_names(rel: ParsedREL, splits: SplitInfo, overrides: dict[int, str]) -> dict[int, str]:
    mapping = dict(overrides)
    used_names = set(mapping.values())

    # Strongest signal: exact target section size vs splits section extent.
    for name in splits.section_order:
        if name in used_names:
            continue
        extent = splits.extents.get(name)
        if not extent:
            continue
        candidates = []
        for s in rel.sections:
            if s.index in mapping or s.size != extent:
                continue
            if name == ".bss" and s.offset != 0:
                continue
            if name == ".text" and not s.executable:
                continue
            if name != ".text" and s.executable and name not in (".init",):
                continue
            candidates.append(s.index)
        if len(candidates) == 1:
            mapping[candidates[0]] = name
            used_names.add(name)

    # Typical REL order fallback: declared split section order corresponds to the
    # non-null section order. Only fill names whose extents are known/nonzero.
    remaining_names = [
        n for n in splits.section_order if n not in used_names and splits.extents.get(n, 0) > 0
    ]
    remaining_sections = [
        s.index
        for s in rel.sections
        if s.index not in mapping and s.size > 0 and s.index != 0
    ]
    # Do not blindly force if counts diverge; only pair compatible sizes/flags in order.
    ni = 0
    for idx in remaining_sections:
        if ni >= len(remaining_names):
            break
        name = remaining_names[ni]
        sec = rel.sections[idx]
        if sec.size == splits.extents.get(name):
            mapping[idx] = name
            used_names.add(name)
            ni += 1

    return mapping


def find_diff_runs(a: bytes, b: bytes) -> list[tuple[int, int]]:
    n = min(len(a), len(b))
    runs: list[tuple[int, int]] = []
    i = 0
    while i < n:
        if a[i] == b[i]:
            i += 1
            continue
        start = i
        i += 1
        while i < n and a[i] != b[i]:
            i += 1
        runs.append((start, i))
    if len(a) != len(b):
        runs.append((n, max(len(a), len(b))))
    return runs


def hex_context(data: bytes, off: int, width: int = 8) -> str:
    if off < 0 or off >= len(data):
        return "<out-of-range>"
    end = min(len(data), off + width)
    return data[off:end].hex(" ").upper()


def describe_reloc(r: Relocation, sec_names: dict[int, str], splits: SplitInfo, symbols: Optional[SymbolInfo], self_id: int) -> dict:
    src_name = sec_names.get(r.source_section, f"section[{r.source_section}]")
    src_owner = splits.owner_at(src_name, r.source_offset) if src_name.startswith(".") else None
    src_symbol = symbols.symbol_at(src_name, r.source_offset) if symbols and src_name.startswith(".") else None
    out = {
        "module_id": r.module_id,
        "source_section_index": r.source_section,
        "source_section": src_name,
        "source_offset": r.source_offset,
        "source_owner": src_owner,
        "source_symbol": src_symbol,
        "type": r.type,
        "type_name": RELOC_NAMES.get(r.type, f"TYPE_{r.type}"),
        "target_section_index": r.target_section,
        "addend": r.addend,
    }
    if r.module_id == self_id:
        tgt_name = sec_names.get(r.target_section, f"section[{r.target_section}]")
        out["target_section"] = tgt_name
        if tgt_name.startswith("."):
            out["target_owner"] = splits.owner_at(tgt_name, r.addend)
            out["target_symbol"] = symbols.symbol_at(tgt_name, r.addend) if symbols else None
    elif r.module_id == 0:
        out["target"] = f"main.dol:0x{r.addend:08X}"
    else:
        out["target"] = f"module {r.module_id}:section[{r.target_section}]+0x{r.addend:X}"
    return out


def compare_rels(
    expected: ParsedREL,
    rebuilt: ParsedREL,
    splits: SplitInfo,
    symbols: Optional[SymbolInfo],
    sec_names: dict[int, str],
    max_details: int,
) -> dict:
    report: dict = {
        "expected": str(expected.path),
        "rebuilt": str(rebuilt.path),
        "expected_sha1": sha1(expected.data),
        "rebuilt_sha1": sha1(rebuilt.data),
        "expected_size": len(expected.data),
        "rebuilt_size": len(rebuilt.data),
        "identical": expected.data == rebuilt.data,
        "section_names": {str(k): v for k, v in sorted(sec_names.items())},
        "header_differences": [],
        "section_differences": [],
        "import_differences": [],
        "relocation_differences": [],
        "relocation_stream_differences": [],
        "raw_file_differences": [],
        "tu_summary": {},
    }

    tu_stats: dict[str, dict[str, int]] = defaultdict(lambda: defaultdict(int))

    # Header semantic + layout fields. Runtime-filled next/prev/bss_section are still
    # included because byte-perfect matching cares about them.
    for field in RelHeader.__dataclass_fields__:
        a = getattr(expected.header, field)
        b = getattr(rebuilt.header, field)
        if a != b:
            report["header_differences"].append({"field": field, "expected": a, "rebuilt": b})

    # Section table + payloads.
    max_sections = max(len(expected.sections), len(rebuilt.sections))
    detail_budget = max_details
    for i in range(max_sections):
        es = expected.sections[i] if i < len(expected.sections) else None
        rs = rebuilt.sections[i] if i < len(rebuilt.sections) else None
        sec_name = sec_names.get(i, f"section[{i}]")
        if es is None or rs is None:
            report["section_differences"].append({
                "section_index": i,
                "section": sec_name,
                "kind": "missing_section",
                "expected": asdict(es) if es else None,
                "rebuilt": asdict(rs) if rs else None,
            })
            continue
        meta_diff = {}
        for field in ("raw_offset", "offset", "flags", "executable", "size"):
            a, b = getattr(es, field), getattr(rs, field)
            if a != b:
                meta_diff[field] = {"expected": a, "rebuilt": b}

        payload_info = None
        if es.offset and rs.offset:
            ea = expected.data[es.offset: es.offset + es.size]
            rb = rebuilt.data[rs.offset: rs.offset + rs.size]
            if ea != rb:
                runs = find_diff_runs(ea, rb)
                owner_counts: dict[str, int] = defaultdict(int)
                run_details = []
                for start, end in runs:
                    if sec_name.startswith("."):
                        overlaps = splits.overlapping_owners(sec_name, start, min(end, es.size))
                    else:
                        overlaps = []
                    covered = 0
                    for owner, count in overlaps:
                        owner_counts[owner] += count
                        tu_stats[owner]["payload_bytes"] += count
                        tu_stats[owner]["payload_runs"] += 1
                        covered += count
                    if end > es.size:
                        extra = end - max(start, es.size)
                        if extra > 0:
                            owner_counts["<rebuilt-extra>"] += extra
                    if covered < max(0, min(end, es.size) - start):
                        owner_counts["<unmapped>"] += max(0, min(end, es.size) - start) - covered
                    if detail_budget > 0:
                        run_details.append({
                            "start": start,
                            "end": end,
                            "length": end - start,
                            "owner": splits.owner_at(sec_name, start) if sec_name.startswith(".") else None,
                            "expected": hex_context(ea, start),
                            "rebuilt": hex_context(rb, start),
                        })
                        detail_budget -= 1
                payload_info = {
                    "expected_sha1": sha1(ea),
                    "rebuilt_sha1": sha1(rb),
                    "different_runs": len(runs),
                    "different_bytes_approx": sum(e - s for s, e in runs),
                    "owners": dict(sorted(owner_counts.items(), key=lambda kv: (-kv[1], kv[0]))),
                    "details": run_details,
                }
        elif es.size != rs.size or es.offset != rs.offset:
            payload_info = {"note": "section has no file payload on one side (likely BSS/layout difference)"}

        if meta_diff or payload_info:
            report["section_differences"].append({
                "section_index": i,
                "section": sec_name,
                "metadata": meta_diff,
                "payload": payload_info,
            })

    # Import table ordering and offsets.
    exp_import_simple = [(x.module_id, x.relocation_offset) for x in expected.imports]
    reb_import_simple = [(x.module_id, x.relocation_offset) for x in rebuilt.imports]
    if exp_import_simple != reb_import_simple:
        report["import_differences"].append({
            "expected": exp_import_simple,
            "rebuilt": reb_import_simple,
            "expected_module_order": [x.module_id for x in expected.imports],
            "rebuilt_module_order": [x.module_id for x in rebuilt.imports],
        })

    # Canonical relocation compare keyed by import module + source location.
    def relmap(rel: ParsedREL) -> dict[tuple[int, int, int], list[Relocation]]:
        d: dict[tuple[int, int, int], list[Relocation]] = defaultdict(list)
        for r in rel.relocations:
            d[(r.module_id, r.source_section, r.source_offset)].append(r)
        return d

    em = relmap(expected)
    rm = relmap(rebuilt)
    all_keys = sorted(set(em) | set(rm))
    reloc_budget = max_details
    for key in all_keys:
        ev = em.get(key, [])
        rv = rm.get(key, [])
        et = [r.value_tuple() for r in ev]
        rt = [r.value_tuple() for r in rv]
        if et == rt:
            continue
        sample = ev[0] if ev else rv[0]
        src_name = sec_names.get(sample.source_section, f"section[{sample.source_section}]")
        owner = splits.owner_at(src_name, sample.source_offset) if src_name.startswith(".") else None
        kind = "changed" if ev and rv else ("missing" if ev else "extra")
        if owner:
            tu_stats[owner][f"reloc_{kind}"] += max(len(ev), len(rv))
        # A relocation mismatch is often caused by the *target* TU moving or changing,
        # not the source TU containing the pointer/instruction. Rank self-REL target
        # owners too, which is especially useful when one bad TU shifts many addends.
        for rr in ev + rv:
            if rr.module_id == expected.header.module_id:
                tgt_name = sec_names.get(rr.target_section)
                if tgt_name and tgt_name.startswith("."):
                    tgt_owner = splits.owner_at(tgt_name, rr.addend)
                    if tgt_owner:
                        tu_stats[tgt_owner]["reloc_target"] += 1
        item = {
            "kind": kind,
            "module_id": sample.module_id,
            "source_section_index": sample.source_section,
            "source_section": src_name,
            "source_offset": sample.source_offset,
            "source_owner": owner,
            "source_symbol": symbols.symbol_at(src_name, sample.source_offset) if symbols and src_name.startswith(".") else None,
            "expected": [describe_reloc(r, sec_names, splits, symbols, expected.header.module_id) for r in ev],
            "rebuilt": [describe_reloc(r, sec_names, splits, symbols, rebuilt.header.module_id) for r in rv],
        }
        if reloc_budget > 0:
            report["relocation_differences"].append(item)
            reloc_budget -= 1
        else:
            # Keep a compact marker so counts remain evident without exploding JSON.
            if not report.get("relocation_differences_truncated"):
                report["relocation_differences_truncated"] = True

    report["relocation_difference_count"] = sum(
        1 for key in all_keys
        if [r.value_tuple() for r in em.get(key, [])] != [r.value_tuple() for r in rm.get(key, [])]
    )

    # Raw relocation stream encoding compare by module ID occurrence. This catches
    # ordering/NOP/delta encoding differences even when canonical relocs are equal.
    def stream_groups(rel: ParsedREL) -> dict[int, list[tuple[RelImport, bytes, list[RelocEntry]]]]:
        out: dict[int, list[tuple[RelImport, bytes, list[RelocEntry]]]] = defaultdict(list)
        for imp in rel.imports:
            out[imp.module_id].append(
                (imp, rel.relocation_streams.get(imp.index, b""), rel.relocation_entries.get(imp.index, []))
            )
        return out

    eg = stream_groups(expected)
    rg = stream_groups(rebuilt)
    for module_id in sorted(set(eg) | set(rg)):
        el = eg.get(module_id, [])
        rl = rg.get(module_id, [])
        count = max(len(el), len(rl))
        for occurrence in range(count):
            e = el[occurrence] if occurrence < len(el) else None
            r = rl[occurrence] if occurrence < len(rl) else None
            if e and r and e[1] == r[1]:
                continue
            first_owner = None
            first_loc = None
            entries = (e[2] if e else []) + (r[2] if r else [])
            for ent in entries:
                if ent.source_section is None or ent.source_offset is None or ent.type in (201, 202, 203):
                    continue
                sec_name = sec_names.get(ent.source_section, f"section[{ent.source_section}]")
                if sec_name.startswith("."):
                    first_owner = splits.owner_at(sec_name, ent.source_offset)
                    first_loc = (sec_name, ent.source_offset)
                    if first_owner:
                        break
            if first_owner:
                tu_stats[first_owner]["reloc_stream"] += 1
            report["relocation_stream_differences"].append({
                "module_id": module_id,
                "occurrence": occurrence,
                "expected_size": len(e[1]) if e else None,
                "rebuilt_size": len(r[1]) if r else None,
                "expected_sha1": sha1(e[1]) if e else None,
                "rebuilt_sha1": sha1(r[1]) if r else None,
                "first_mapped_owner": first_owner,
                "first_mapped_location": first_loc,
            })

    # Raw file runs are a final safety net for checksum-only differences in padding,
    # module-name bytes, or other layout regions not covered above. Classification
    # uses the expected REL layout and is intentionally capped.
    if expected.data != rebuilt.data:
        raw_runs = find_diff_runs(expected.data, rebuilt.data)

        def classify_file_offset(off: int) -> str:
            header_size = 0x40 if expected.header.version == 1 else (0x48 if expected.header.version == 2 else 0x4C)
            if off < header_size:
                return "header"
            if expected.header.section_info_offset <= off < expected.header.section_info_offset + expected.header.section_count * 8:
                return "section_table"
            if expected.header.name_offset and expected.header.name_offset <= off < expected.header.name_offset + expected.header.name_size:
                return "module_name"
            if expected.header.import_offset <= off < expected.header.import_offset + expected.header.import_size:
                return "import_table"
            for sec in expected.sections:
                if sec.offset and sec.offset <= off < sec.offset + sec.size:
                    return f"section[{sec.index}]/{sec_names.get(sec.index, '?')}"
            for imp in expected.imports:
                stream = expected.relocation_streams.get(imp.index, b"")
                if imp.relocation_offset <= off < imp.relocation_offset + len(stream):
                    return f"relocations(module={imp.module_id},import={imp.index})"
            return "padding/other"

        for start, end in raw_runs[:max_details]:
            report["raw_file_differences"].append({
                "start": start,
                "end": end,
                "length": end - start,
                "region": classify_file_offset(start),
                "expected": hex_context(expected.data, start),
                "rebuilt": hex_context(rebuilt.data, start),
            })
        report["raw_file_difference_run_count"] = len(raw_runs)

    # Rank TUs. Relocation problems are weighted heavily because they can leave
    # section bytes looking correct while still changing the final REL.
    ranked = []
    for owner, stats in tu_stats.items():
        stats = dict(stats)
        reloc_n = sum(v for k, v in stats.items() if k.startswith("reloc_"))
        payload = stats.get("payload_bytes", 0)
        score = reloc_n * 100000 + min(payload, 99999)
        ranked.append((score, owner, stats))
    ranked.sort(key=lambda x: (-x[0], x[1]))
    report["tu_summary"] = {
        owner: {**stats, "score": score} for score, owner, stats in ranked
    }
    report["tu_order"] = [owner for _, owner, _ in ranked]
    return report


def format_num(v: Optional[int]) -> str:
    return "-" if v is None else f"0x{v:X}"


def print_report(report: dict, top: int, max_details: int) -> None:
    print(f"Expected: {report['expected']}")
    print(f"Rebuilt:  {report['rebuilt']}")
    print(f"SHA-1:    {report['expected_sha1']}  expected")
    print(f"          {report['rebuilt_sha1']}  rebuilt")
    print(f"Size:     0x{report['expected_size']:X} expected, 0x{report['rebuilt_size']:X} rebuilt")
    if report["identical"]:
        print("\nMATCH: files are byte-for-byte identical.")
        return

    print("\nMISMATCH")
    if report["header_differences"]:
        print(f"\nHeader differences ({len(report['header_differences'])}):")
        for d in report["header_differences"][:max_details]:
            print(f"  {d['field']}: {d['expected']!r} -> {d['rebuilt']!r}")

    print("\nSection mapping:")
    if report["section_names"]:
        for idx, name in report["section_names"].items():
            print(f"  [{idx}] {name}")
    else:
        print("  <none inferred; use --section-index .data=N if needed>")

    if report["section_differences"]:
        print(f"\nSection differences ({len(report['section_differences'])}):")
        for d in report["section_differences"]:
            sec = d.get("section", f"section[{d.get('section_index')}]")
            payload = d.get("payload")
            meta = d.get("metadata", {})
            parts = []
            if meta:
                parts.append("metadata: " + ", ".join(meta.keys()))
            if payload and payload.get("different_runs") is not None:
                parts.append(
                    f"payload: {payload['different_runs']} runs / ~{payload['different_bytes_approx']} bytes"
                )
            elif payload:
                parts.append("payload/layout differs")
            print(f"  {sec}: {'; '.join(parts) if parts else d.get('kind', 'differs')}")
            if payload and payload.get("owners"):
                owners = list(payload["owners"].items())[:10]
                print("    TUs: " + ", ".join(f"{o} ({n} bytes)" for o, n in owners))
            if payload:
                for detail in payload.get("details", [])[:5]:
                    print(
                        f"    +0x{detail['start']:X}..0x{detail['end']:X} "
                        f"{detail.get('owner') or '<unmapped>'}: "
                        f"{detail['expected']} -> {detail['rebuilt']}"
                    )

    if report["import_differences"]:
        print("\nImport table differs:")
        d = report["import_differences"][0]
        print(f"  expected module order: {d['expected_module_order']}")
        print(f"  rebuilt  module order: {d['rebuilt_module_order']}")

    reloc_count = report.get("relocation_difference_count", len(report["relocation_differences"]))
    if reloc_count:
        print(f"\nRelocation differences ({reloc_count} source locations):")
        for d in report["relocation_differences"][:max_details]:
            owner = d.get("source_owner") or "<unmapped>"
            sym = f" ({d['source_symbol']})" if d.get("source_symbol") else ""
            print(
                f"  {owner}: {d['source_section']}+0x{d['source_offset']:X}{sym} [{d['kind']}]"
            )
            for side in ("expected", "rebuilt"):
                vals = d.get(side, [])
                if not vals:
                    print(f"    {side}: <none>")
                    continue
                for r in vals:
                    target = r.get("target")
                    if not target:
                        ts = r.get("target_section", f"section[{r['target_section_index']}]")
                        target = f"{ts}+0x{r['addend']:X}"
                        if r.get("target_symbol"):
                            target += f" ({r['target_symbol']})"
                        if r.get("target_owner"):
                            target += f" in {r['target_owner']}"
                    print(f"    {side}: {r['type_name']} -> {target}")
        if report.get("relocation_differences_truncated"):
            print("  ... relocation detail truncated; increase --max-details or inspect --json output")

    if report["relocation_stream_differences"]:
        print(f"\nRaw relocation stream differences ({len(report['relocation_stream_differences'])}):")
        for d in report["relocation_stream_differences"][:10]:
            owner = d.get("first_mapped_owner") or "<unmapped>"
            print(
                f"  import module {d['module_id']} #{d['occurrence']}: "
                f"{d['expected_size']} -> {d['rebuilt_size']} bytes, near {owner}"
            )

    if report.get("raw_file_differences"):
        print(f"\nRaw file difference runs ({report.get('raw_file_difference_run_count', len(report['raw_file_differences']))}):")
        for d in report["raw_file_differences"][:10]:
            print(
                f"  file+0x{d['start']:X}..0x{d['end']:X} [{d['region']}]: "
                f"{d['expected']} -> {d['rebuilt']}"
            )
        if report.get("raw_file_difference_run_count", 0) > 10:
            print("  ...")

    order = report.get("tu_order", [])
    if order:
        print(f"\nSuspect TUs ({len(order)} total, top {min(top, len(order))}):")
        for owner in order[:top]:
            s = report["tu_summary"][owner]
            bits = []
            if s.get("payload_bytes"):
                bits.append(f"payload={s['payload_bytes']}B/{s.get('payload_runs', 0)} runs")
            for k in ("reloc_changed", "reloc_missing", "reloc_extra", "reloc_target", "reloc_stream"):
                if s.get(k):
                    bits.append(f"{k}={s[k]}")
            print(f"  {owner}: " + ", ".join(bits))
    else:
        print("\nNo section/relocation differences could be mapped to a TU.")



def print_cascade_report(c: dict, top: int, max_details: int) -> None:
    print("\nCascade-aware analysis:")
    print(f"  rebuilt map: {c['map']}")
    print(f"  mapped section contributions: {c['mapped_contributions']}")
    if c.get("unmapped_map_contributions"):
        print(f"  warning: {len(c['unmapped_map_contributions'])} shown map contributions could not be mapped to split owners")

    padding = c.get("ignored_trailing_padding", [])
    if padding:
        total_pad = sum(x.get("padding_bytes", 0) for x in padding)
        print(f"\nIgnored trailing alignment/padding ({len(padding)} TUs, {total_pad} bytes):")
        print("  zero-filled split tails excluded from root analysis")

    layout = c.get("layout_differences", [])
    size_roots = [d for d in layout if d.get("size_delta")]
    if size_roots:
        print(f"\nLayout root candidates ({len(size_roots)} TUs with actual size/start deltas):")
        for d in size_roots[:min(max_details, 30)]:
            print(
                f"  {d['owner']}: expected start=0x{d['expected_start']:X} size=0x{d['expected_size']:X}; "
                f"rebuilt start=0x{d['rebuilt_start']:X} size=0x{d['rebuilt_size']:X}; "
                f"size delta={d['size_delta']:+#x}, start drift={d['start_delta']:+#x}"
            )
    else:
        print("\nLayout: no mapped TU size/start deltas detected after excluding alignment padding.")

    payload = c.get("payload_tu_differences", [])
    if payload:
        print(f"\nTU-local payload mismatches after resynchronizing boundaries ({len(payload)} TUs):")
        for d in sorted(payload, key=lambda x: (-x['different_bytes_approx'], x['owner']))[:20]:
            print(
                f"  {d['owner']}: ~{d['different_bytes_approx']} bytes / {d['different_runs']} runs "
                f"(expected 0x{d['expected_size']:X}, rebuilt 0x{d['rebuilt_size']:X})"
            )

    n = c.get("normalized_relocation_difference_count", 0)
    print(f"\nNormalized relocation differences: {n} source locations")
    if c.get("normalized_relocation_by_module"):
        print("  by import/target module: " + ", ".join(
            f"{m}={n}" for m, n in c['normalized_relocation_by_module'].items()
        ))
    for d in c.get("normalized_relocation_differences", [])[:min(max_details, 20)]:
        owner = d.get("source_owner") or "<unmapped>"
        print(
            f"  {owner}: {d['source_section']}+TU0x{d['source_relative_offset']:X} "
            f"[{d['kind']}] target module {d['module_id']}"
        )

    order = c.get("root_tu_order", [])
    if order:
        print(f"\nRoot suspect TUs ({len(order)} total, top {min(top, len(order))}):")
        for owner in order[:top]:
            s = c['root_tu_summary'][owner]
            bits = []
            if s.get('size_delta'):
                bits.append(f"size_delta={s['size_delta']:+#x}")
            if s.get('payload_bytes'):
                bits.append(f"payload={s['payload_bytes']}B/{s.get('payload_runs',0)} runs")
            for k in ('reloc_changed','reloc_missing','reloc_extra'):
                if s.get(k):
                    bits.append(f"{k}={s[k]}")
            print(f"  {owner}: " + ", ".join(bits))

def find_first_existing(candidates: Iterable[Path]) -> Optional[Path]:
    for p in candidates:
        if p.exists() and p.is_file():
            return p
    return None


def detect_rel_paths(root: Path, version: str, module: str) -> tuple[Optional[Path], Optional[Path], list[Path], list[Path]]:
    target_candidates = [
        root / "orig" / version / "files" / f"{module}.rel",
        root / "orig" / version / f"{module}.rel",
        root / "original" / version / "files" / f"{module}.rel",
        root / "original" / version / f"{module}.rel",
        root / "extract" / version / "files" / f"{module}.rel",
        root / "extracted" / version / "files" / f"{module}.rel",
    ]
    rebuilt_candidates = [
        root / "build" / version / module / f"{module}.rel",
        root / "build" / version / f"{module}.rel",
        root / "build" / version / "files" / f"{module}.rel",
    ]
    target = find_first_existing(target_candidates)
    rebuilt = find_first_existing(rebuilt_candidates)
    if rebuilt is None:
        matches = list((root / "build" / version).glob(f"**/{module}.rel")) if (root / "build" / version).exists() else []
        if len(matches) == 1:
            rebuilt = matches[0]
    return target, rebuilt, target_candidates, rebuilt_candidates



def detect_rebuilt_map(root: Path, version: str, module: str) -> Optional[Path]:
    candidates = [
        root / "build" / version / module / f"{module}.map",
        root / "build" / version / module / f"{module}.rel.map",
        root / "build" / version / f"{module}.map",
    ]
    p = find_first_existing(candidates)
    if p:
        return p
    base = root / "build" / version
    if base.exists():
        matches = [x for x in base.glob(f"**/{module}*.map") if x.is_file()]
        if len(matches) == 1:
            return matches[0]
    return None

def main(argv: Optional[list[str]] = None) -> int:
    ap = argparse.ArgumentParser(
        description="Diff a rebuilt GameCube/Wii REL against the original and map differences to DTK split TUs."
    )
    ap.add_argument("--module", default="forestd", help="REL module name, e.g. forestd")
    ap.add_argument("-v", "--version", default="GAEJ01_00", help="project version")
    ap.add_argument("--project-root", type=Path, default=Path.cwd(), help="project root (default: cwd)")
    ap.add_argument("--expected", "--target", dest="expected", type=Path, help="original/expected .rel")
    ap.add_argument("--rebuilt", "--base", dest="rebuilt", type=Path, help="rebuilt .rel")
    ap.add_argument("--splits", type=Path, help="splits.txt (auto-detected by module/version)")
    ap.add_argument("--symbols", type=Path, help="symbols.txt for nicer relocation names")
    ap.add_argument("--rebuilt-map", "--map", dest="rebuilt_map", type=Path, help="rebuilt linker .map; enables cascade-aware TU-relative analysis")
    ap.add_argument(
        "--section-index", action="append", default=[], metavar=".data=N",
        help="override REL section index mapping; repeatable, e.g. --section-index .data=4",
    )
    ap.add_argument("--top", type=int, default=50, help="number of suspect TUs to print")
    ap.add_argument("--max-details", type=int, default=100, help="maximum detailed payload/relocation items")
    ap.add_argument("--json", type=Path, help="write full JSON report")
    args = ap.parse_args(argv)

    root = args.project_root.resolve()
    splits_path = (args.splits or (root / "config" / args.version / args.module / "splits.txt")).resolve()
    symbols_path = (args.symbols or (root / "config" / args.version / args.module / "symbols.txt")).resolve()

    rebuilt_map_path = args.rebuilt_map.resolve() if args.rebuilt_map else detect_rebuilt_map(root, args.version, args.module)

    detected_expected, detected_rebuilt, target_candidates, rebuilt_candidates = detect_rel_paths(root, args.version, args.module)
    expected_path = (args.expected.resolve() if args.expected else detected_expected)
    rebuilt_path = (args.rebuilt.resolve() if args.rebuilt else detected_rebuilt)

    if not splits_path.exists():
        ap.error(f"splits file not found: {splits_path}")
    if expected_path is None:
        msg = "Could not auto-detect original REL. Tried:\n" + "\n".join(f"  {p}" for p in target_candidates)
        ap.error(msg + "\nPass --expected path\\to\\original.rel")
    if rebuilt_path is None:
        msg = "Could not auto-detect rebuilt REL. Tried:\n" + "\n".join(f"  {p}" for p in rebuilt_candidates)
        ap.error(msg + "\nPass --rebuilt path\\to\\rebuilt.rel")

    try:
        overrides = parse_section_overrides(args.section_index)
        splits = parse_splits(splits_path)
        symbols = parse_symbols(symbols_path)
        expected = parse_rel(expected_path)
        rebuilt = parse_rel(rebuilt_path)
        sec_names = infer_section_names(expected, splits, overrides)
        report = compare_rels(expected, rebuilt, splits, symbols, sec_names, args.max_details)
        if rebuilt_map_path and rebuilt_map_path.exists():
            link_map = parse_link_map(rebuilt_map_path, splits)
            report["cascade"] = analyze_cascade_layout(expected, rebuilt, splits, symbols, sec_names, link_map, args.max_details)
        else:
            report["cascade"] = None
    except (OSError, ValueError) as e:
        print(f"relcheck: error: {e}", file=sys.stderr)
        return 2

    print_report(report, max(1, args.top), max(1, args.max_details))
    if report.get("cascade"):
        print_cascade_report(report["cascade"], max(1, args.top), max(1, args.max_details))
    elif not report["identical"]:
        print("\nCascade-aware analysis unavailable: no rebuilt linker map found.")
        print("  Generate one with: python configure.py --map  (then rebuild the REL)")
        print("  Or pass: --rebuilt-map path\\to\\forestd.map")
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        print(f"\nJSON report: {args.json}")

    return 0 if report["identical"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
