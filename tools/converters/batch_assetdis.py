#!/usr/bin/env python3
"""Batch assetdis using a module's splits.txt and symbols.txt (no map/manifest).

Run from the project root, with the previously updated assetdis.py installed:
    python batch_assetdis.py --module forestd                 # preview
    python batch_assetdis.py --module forestd --run           # stage C + recipes
    python batch_assetdis.py --module foresti -v GAEJ01_01 --run

The existing generated .s files supply the bytes/relocations. A single large
assembly file and a directory of smaller files are both supported. By default the
script stages output only. Pass --src-dir (for example, data/always) to install
successful TUs under src/, move their data ranges to those TU names in splits.txt,
add NonMatching Object entries to configure.py, and add/update the emitted asset
includes in the selected module's config.yml extract list.
"""
from __future__ import annotations

import argparse
import ast
import bisect
import collections
import contextlib
import dataclasses
import fnmatch
import importlib.util
import inspect
import json
import os
from pathlib import Path
import re
import struct
import sys
import traceback
from typing import Any

VERSIONS = ("GAEJ01_00", "GAEJ01_01")
MODULES = ("foresta", "forestd", "foresto", "foresti")
IDENT = r"[A-Za-z_]\w*"
ATTR = re.compile(r"([\w]+):([^\s]+)")
SYM = re.compile(r"^\s*(\S+)\s*=\s*(\.[^:\s]+):((?:0[xX])?[0-9A-Fa-f]+)\s*;\s*(?://\s*(.*))?$")
OBJ = re.compile(r"^\s*\.obj\s+(\S+?)\s*,\s*(\w+)\s*$")
SECTION = re.compile(r'^\s*\.section\s+["\']?([^\s,"\']+)')
ADDRESS = re.compile(r"^\s*#\s*(0[xX][0-9A-Fa-f]+)\s*\|\s*(0[xX][0-9A-Fa-f]+)")
DECL = re.compile(r"^(static\s+)?([A-Za-z_]\w*\s*\*?)\s+(" + IDENT + r")\s*(\[\])?\s*(?:ATTRIBUTE_ALIGN\(\d+\)\s*)?=", re.M)
ASSET_INCLUDE = re.compile(r'^\s*#include\s+"assets/[^"\n]+"\s*$', re.M)
EXPR = re.compile(r"^(" + IDENT + r")(?:\s*([+-])\s*(0[xX][0-9A-Fa-f]+|\d+))?$")
LEX = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)


@dataclasses.dataclass(frozen=True)
class Symbol:
    name: str
    section: str
    address: int
    size: int
    scope: str = "global"
    align: int = 1

    @property
    def key(self) -> tuple[str, int]:
        return self.section, self.address


@dataclasses.dataclass
class Unit:
    owner: str
    section: str
    start: int
    end: int
    line: int
    symbols: list[Symbol] = dataclasses.field(default_factory=list)
    guessed_stem: str | None = None

    @property
    def stem(self) -> str:
        """Stable address-based ID used to trace this unit back to splits.txt."""
        return f"{self.section.lstrip('.')}_{self.start:08X}"

    @property
    def file_stem(self) -> str:
        """Best-effort source filename, or the stable address ID before naming."""
        return self.guessed_stem or self.stem


@dataclasses.dataclass
class AsmObject:
    symbol: Symbol
    name: str
    body: list[str]
    path: str
    line: int
    data: bytes = b""
    references: dict[int, str] = dataclasses.field(default_factory=dict)
    labels: dict[str, int] = dataclasses.field(default_factory=dict)
    error: str | None = None


def reference_name(ref: str) -> str | None:
    """Return the base symbol referenced by one decoded relocation/expression."""
    value = ref[5:] if ref.startswith(".rel ") else ref
    match = re.match(IDENT, value)
    return match[0] if match else None


def _symbol_gap(a: Symbol, b: Symbol) -> int:
    """Distance between two symbol byte ranges (zero when they overlap)."""
    a_end = a.address + max(a.size, 1)
    b_end = b.address + max(b.size, 1)
    if a_end <= b.address:
        return b.address - a_end
    if b_end <= a.address:
        return a.address - b_end
    return 0


def resolve_external_local_references(unit: Unit, objects: list[AsmObject],
                                      symbols: list[Symbol]) -> dict[str, Symbol]:
    """Resolve local symbols referenced from outside *unit*.

    Decompiled data sometimes contains several local/static objects with the same
    spelling. DTK's symbols metadata keeps each occurrence address-qualified, while
    the generated assembly relocation still spells only the C identifier. The
    completed ac-decomp sources handle the shared occurrence by exposing exactly one
    definition to C and keeping its extraction selector address-qualified.

    Prefer the same section, then the occurrence closest to the referencing object.
    Refuse an exact tie rather than silently picking the wrong duplicate.
    """
    current = {s.name for s in unit.symbols}
    globals_ = {s.name for s in symbols if s.scope == "global"}
    locals_by_name: dict[str, list[Symbol]] = collections.defaultdict(list)
    for symbol in symbols:
        if symbol.scope == "local":
            locals_by_name[symbol.name].append(symbol)

    sources_by_name: dict[str, list[Symbol]] = collections.defaultdict(list)
    for obj in objects:
        for ref in obj.references.values():
            name = reference_name(ref)
            if name and name not in current and name not in globals_:
                sources_by_name[name].append(obj.symbol)

    resolved: dict[str, Symbol] = {}
    for name, sources in sources_by_name.items():
        options = locals_by_name.get(name, [])
        if not options:
            continue
        same_section = [s for s in options if any(src.section == s.section for src in sources)]
        if same_section:
            options = same_section
        scored = sorted(
            (min(_symbol_gap(src, candidate) for src in sources), candidate.address, candidate)
            for candidate in options
        )
        if len(scored) > 1 and scored[0][0] == scored[1][0]:
            best_gap = scored[0][0]
            choices = ", ".join(
                f"{candidate.section}:0x{candidate.address:08X}"
                for gap, _addr, candidate in scored if gap == best_gap
            )
            raise ValueError(
                f"Cannot disambiguate duplicated local {name!r}; equally near occurrences: {choices}"
            )
        resolved[name] = scored[0][2]
    return resolved


def number(text: str) -> int:
    text = text.strip()
    return int(text, 16 if text.lower().lstrip("+-").startswith("0x") else 10)


def uncomment(line: str) -> str:
    """Remove assembly/config comments, but leave quoted strings intact."""
    return re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|#[^\n]*|//[^\n]*',
                  lambda m: "" if m[0].startswith(("#", "//")) else m[0], line).strip()


def read_symbols(path: Path, sections: set[str]) -> list[Symbol]:
    result: list[Symbol] = []
    seen: set[tuple[str, int]] = set()
    for lineno, line in enumerate(path.read_text(encoding="utf-8-sig").splitlines(), 1):
        if not line.strip() or line.lstrip().startswith(("#", "//")):
            continue
        match = SYM.fullmatch(line)
        if not match:
            raise ValueError(f"{path}:{lineno}: unrecognized symbols.txt line")
        name, section, address, metadata = match.groups()
        if section not in sections:
            continue
        attrs = dict(ATTR.findall(metadata or ""))
        if attrs.get("type") != "object":
            continue
        if "size" not in attrs:
            raise ValueError(f"{path}:{lineno}: object {name} has no size")
        symbol = Symbol(name, section, int(address, 16), number(attrs["size"]),
                        attrs.get("scope", "global"), number(attrs.get("align", "1")))
        if symbol.size < 0 or symbol.align < 1 or symbol.align & (symbol.align - 1):
            raise ValueError(f"{path}:{lineno}: invalid size/alignment")
        if symbol.key in seen:
            raise ValueError(f"{path}:{lineno}: aliased objects at {section}:{address}; resolve the alias first")
        seen.add(symbol.key)
        result.append(symbol)
    return sorted(result, key=lambda s: (s.section, s.address))


def read_splits(path: Path, sections: set[str], owner_patterns: list[str]) -> tuple[list[Unit], dict[str, int]]:
    owner = ""
    units: list[Unit] = []
    stats: collections.Counter[str] = collections.Counter()
    seen: set[tuple[str, int, int]] = set()
    for lineno, raw in enumerate(path.read_text(encoding="utf-8-sig").splitlines(), 1):
        line = uncomment(raw)
        if not line:
            continue
        if not raw[0].isspace() and line.endswith(":"):
            owner = line[:-1]
            continue
        if owner == "Sections":
            continue
        section = line.split()[0]
        # Ignore .text before reading start/end: even malformed bogus text is irrelevant.
        if section not in sections:
            if section.startswith("."):
                stats["ignored_section_lines"] += 1
                if section == ".text":
                    stats["ignored_text_lines"] += 1
            continue
        if not owner:
            raise ValueError(f"{path}:{lineno}: section range has no owner")
        if owner_patterns:
            selected = any(fnmatch.fnmatchcase(owner, p) for p in owner_patterns)
        else:
            # Process only the still-raw object contribution by default. Once a
            # range is promoted to a real .c TU, later batch runs skip it.
            selected = Path(owner).suffix.lower() == ".obj" and Path(owner).stem not in {"executor", "fakemain"}
        if not selected:
            stats["excluded_owner_ranges"] += 1
            continue
        attrs = dict(ATTR.findall(line))
        if not {"start", "end"} <= attrs.keys():
            raise ValueError(f"{path}:{lineno}: expected explicit start and end")
        start, end = number(attrs["start"]), number(attrs["end"])
        stats["selected_range_lines"] += 1
        if start < 0 or end < start:
            raise ValueError(f"{path}:{lineno}: invalid range {start:#x}..{end:#x}")
        if start == end:
            stats["empty_ranges"] += 1
            continue
        key = (section, start, end)
        if key in seen:
            stats["duplicate_ranges"] += 1
            continue
        seen.add(key)
        units.append(Unit(owner, section, start, end, lineno))
    units.sort(key=lambda u: (u.section, u.start))
    for a, b in zip(units, units[1:]):
        if a.section == b.section and a.end > b.start:
            raise ValueError(f"{path}:{b.line}: overlapping {b.section} ranges at {b.start:#x}; not silently merged")
    if not units:
        raise ValueError("No nonempty selected data ranges in splits.txt")
    return units, dict(stats)


def assign_symbols(units: list[Unit], symbols: list[Symbol]) -> None:
    by_section: dict[str, list[Unit]] = collections.defaultdict(list)
    for unit in units:
        by_section[unit.section].append(unit)
    for section, group in by_section.items():
        starts = [u.start for u in group]
        for symbol in (s for s in symbols if s.section == section and s.size > 0):
            i = bisect.bisect_right(starts, symbol.address) - 1
            if i < 0 or symbol.address >= group[i].end:
                following = i + 1
                if following < len(group) and symbol.address + symbol.size > group[following].start:
                    raise ValueError(f"{symbol.name} overlaps the start of split {group[following].stem}")
                continue
            unit = group[i]
            if symbol.address + symbol.size > unit.end:
                raise ValueError(f"{symbol.name} at {section}:{symbol.address:#x} crosses the split ending at {unit.end:#x}")
            if unit.symbols and unit.symbols[-1].address + unit.symbols[-1].size > symbol.address:
                raise ValueError(f"Overlapping symbol sizes in {unit.stem}: {symbol.name}")
            unit.symbols.append(symbol)


def unit_key(unit: Unit) -> tuple[str, int, int]:
    return unit.section, unit.start, unit.end


def unit_real_end(unit: Unit) -> int:
    """End of meaningful bytes in a split, excluding linker-created tail padding."""
    if unit.symbols:
        return max(symbol.address + symbol.size for symbol in unit.symbols)
    # Unnamed/raw split ranges are real bytes and must occupy their complete range.
    return unit.end


def alignment_to_reach(previous_end: int, target_start: int, maximum: int = 0x1000) -> int | None:
    """Smallest power-of-two alignment that rounds previous_end up to target_start."""
    if target_start <= previous_end:
        return 1 if target_start == previous_end else None
    alignment = 2
    while alignment <= maximum:
        if (previous_end + alignment - 1) & ~(alignment - 1) == target_start:
            return alignment
        alignment <<= 1
    return None


def infer_tu_entry_alignments(units: list[Unit], minimum: int = 32) -> dict[tuple[str, int, int], int]:
    """Infer alignment that belongs to the *next TU* rather than to the previous TU's data.

    The original aggregate data object contains linker/compiler alignment gaps between
    logical translation units.  After splitting those ranges into independent C files,
    the next object's first definition must recreate that boundary.  Infer only strong
    entry alignments (32+ by default); ordinary 4/8/16-byte placement is left to MWCC.
    """
    result: dict[tuple[str, int, int], int] = {}
    previous_by_section: dict[str, Unit] = {}
    for unit in sorted(units, key=lambda item: (item.section, item.start, item.end, item.owner)):
        previous = previous_by_section.get(unit.section)
        if previous is not None:
            previous_end = unit_real_end(previous)
            if unit.start > previous_end:
                required = alignment_to_reach(previous_end, unit.start)
                if required is not None and required >= minimum:
                    result[unit_key(unit)] = required
        previous_by_section[unit.section] = unit
    return result


# Filename inference is intentionally conservative about *types* but permissive about
# names. The split already defines which symbols belong in one source file, so the
# useful signal is the shared semantic portion of those symbol names.
_FILENAME_SUFFIXES = (
    # Display-list/material conventions. Order matters: strip longest forms first.
    re.compile(r"(?:T_(?:mat|gfx)_model|T_model)$"),
    re.compile(r"_(?:mat|gfx)_model$"),
    re.compile(r"_model$"),
    re.compile(r"_(?:DL_mode|v2?|vtx|gfx2?|setmode|modeset|mode)$"),
    # Animation/image leaves that commonly sit under a larger asset family.
    re.compile(r"_(?:eye|mouth)\d+.*$", re.IGNORECASE),
    re.compile(r"_\d+_(?:TA_)?tex(?:_txt)?$", re.IGNORECASE),
    re.compile(r"_(?:TA_)?tex(?:_txt)?$", re.IGNORECASE),
    re.compile(r"_tmem_txt$", re.IGNORECASE),
    re.compile(r"_pal(?:_[A-Za-z0-9]+)?$", re.IGNORECASE),
    re.compile(r"_tex_index$", re.IGNORECASE),
    re.compile(r"_TXT$", re.IGNORECASE),
)
_CKF_WRAPPER = re.compile(r"^cKF_(?:je_r|bs_r|ckcb_r|kn|c|ds|ba_r)_(.+?)(?:_tbl)?$")
_BODY_PREFIX = re.compile(r"^(?:head|mouth|chest|base|tail\d+|[RL](?:arm|foot)\d+)_", re.IGNORECASE)


def normalize_asset_name(name: str) -> str:
    """Reduce a symbol name to the part most likely to name its source file.

    Examples:
      glider_v                         -> glider
      int_din_bront_bodyT_model       -> int_din_bront_body
      cKF_ckcb_r_npc_1_wait_r1_tbl    -> npc_1_wait_r1
    """
    match = _CKF_WRAPPER.fullmatch(name)
    if match:
        name = match.group(1)
    previous = None
    while name and name != previous:
        previous = name
        for pattern in _FILENAME_SUFFIXES:
            reduced = pattern.sub("", name)
            if reduced != name:
                name = reduced
                break
    name = re.sub(r"_+", "_", name).strip("_")
    # Symbols are usually valid identifiers already, but keep generated paths safe if
    # a tool emits a local-name spelling that is not.
    return re.sub(r"[^A-Za-z0-9_.-]+", "_", name).strip("._-")




def _token_prefix(values: list[str]) -> str:
    tokenized = [[part for part in value.split("_") if part] for value in values if value]
    if not tokenized:
        return ""
    result: list[str] = []
    for column in zip(*tokenized):
        if len(set(column)) != 1:
            break
        result.append(column[0])
    return "_".join(result)


def _token_suffix(values: list[str]) -> str:
    tokenized = [[part for part in value.split("_") if part] for value in values if value]
    if not tokenized:
        return ""
    result: list[str] = []
    for column in zip(*(reversed(parts) for parts in tokenized)):
        if len(set(column)) != 1:
            break
        result.append(column[0])
    return "_".join(reversed(result))


def guess_unit_name(unit: Unit) -> str:
    """Best guess at a source stem from symbols contained by one split.

    Whole-range family matches remain the primary signal.  When those are ambiguous,
    prefer a coherent trailing family because asset TUs often start with generic/shared
    palettes and textures and end with the owning vertex/model objects.
    """
    if not unit.symbols:
        return unit.stem
    normalized = [normalize_asset_name(symbol.name) for symbol in unit.symbols]
    normalized = [name for name in normalized if name]
    if not normalized:
        return unit.stem

    # Strongest signal: most/all leaves reduce to exactly the same family name.
    counts = collections.Counter(normalized)
    candidate, support = max(counts.items(), key=lambda item: (item[1], len(item[0]), item[0]))
    if support >= max(2, (len(normalized) + 1) // 2):
        return candidate

    # Character/limb display lists often look like `head_bev_model`, `Rarm2_bev_model`,
    # etc. Treat the body-part prefix as decoration when looking for a shared family.
    variants: list[set[str]] = []
    for name in normalized:
        options = {name}
        without_body = _BODY_PREFIX.sub("", name)
        options.add(without_body)
        if re.search(r"_\d+$", name):
            options.add(re.sub(r"_\d+$", "", name))
        if re.search(r"_\d+$", without_body):
            options.add(re.sub(r"_\d+$", "", without_body))
        variants.append({value for value in options if len(value) >= 2})
    variant_support = collections.Counter(value for options in variants for value in options)
    if variant_support:
        candidate, support = max(variant_support.items(), key=lambda item: (item[1], len(item[0]), item[0]))
        if support >= max(2, (len(normalized) + 1) // 2):
            return candidate

    # Otherwise use a token-boundary common prefix/suffix. This avoids odd partial
    # strings such as `int_din_bro` while still finding families like `act_balloon`.
    shared = [value for value in (_token_prefix(normalized), _token_suffix(normalized)) if len(value) >= 2]
    if shared:
        candidate = max(shared, key=lambda value: (len(value.split("_")), len(value), value))
        first = normalized[0]
        # A one-token infrastructure prefix (`obj`, `rom`, `logo`, ...) is usually too
        # vague. Keep it only when the first symbol adds merely a numeric variant, as
        # in `ant_1_v` + `head_ant_model` -> `ant`.
        first_parts = first.split("_")
        if len(candidate.split("_")) == 1 and len(first_parts) > 1 and first_parts[0] == candidate:
            if not all(part.isdigit() for part in first_parts[1:]):
                return first
        return candidate

    # If the whole split is ambiguous, use the family named by its tail.  This pass is
    # intentionally tail-specific so normal filename inference remains stable.  A few
    # trailing wrappers use spellings such as tmpr2_modelT or mSP_binsen_list; reduce
    # those only here, then require a second adjacent tail symbol to confirm the family.
    def tail_name(symbol: Symbol) -> str:
        value = re.sub(r"^mSP_", "", symbol.name)
        value = re.sub(r"_modelT$", "", value)
        return normalize_asset_name(value)

    tail = [tail_name(symbol) for symbol in unit.symbols]
    tail = [name for name in tail if name]
    if tail:
        tail_anchor = tail[-1]
        tail_support = 0
        for name in reversed(tail):
            if name == tail_anchor or name.startswith(tail_anchor):
                tail_support += 1
            else:
                break
        if tail_support >= 2:
            return tail_anchor

    # Preserve the historical first-symbol fallback when even the tail is ambiguous.
    return normalized[0] or unit.stem

def assign_unit_names(units: list[Unit], use_guesses: bool = True) -> None:
    """Assign unique, path-safe source stems to named units.

    Duplicate guesses are first refined with the first symbol's normalized name. Any
    remaining case-insensitive collision gets a section/address suffix so no source or
    asset directory can overwrite another on Windows.
    """
    named = [unit for unit in units if unit.symbols]
    for unit in named:
        unit.guessed_stem = guess_unit_name(unit) if use_guesses else unit.stem

    groups: dict[str, list[Unit]] = collections.defaultdict(list)
    for unit in named:
        groups[unit.file_stem.casefold()].append(unit)
    for group in groups.values():
        if len(group) < 2:
            continue
        for unit in group:
            current = unit.file_stem.casefold()
            normalized = [normalize_asset_name(symbol.name) for symbol in unit.symbols]
            normalized = [name for name in normalized if name and name.casefold() != current]
            if not normalized:
                continue
            counts = collections.Counter(normalized)
            # Prefer a repeated, more-specific family inside this split (for example
            # rom_myhome1_wall over a shared rom_myhome palette). If nothing repeats,
            # the first non-generic contained symbol is still a better discriminator.
            repeated = [(name, count) for name, count in counts.items() if count >= 2]
            if repeated:
                specific = max(repeated, key=lambda item: (item[1], len(item[0]), item[0]))[0]
            else:
                specific = normalized[0]
            unit.guessed_stem = specific

    # Refinement can itself collide with another group, so resolve globally once more.
    groups = collections.defaultdict(list)
    for unit in named:
        groups[unit.file_stem.casefold()].append(unit)
    for group in groups.values():
        if len(group) < 2:
            continue
        for unit in group:
            section = unit.section.lstrip(".")
            suffix = f"{unit.start:08X}" if section == "data" else f"{section}_{unit.start:08X}"
            unit.guessed_stem = f"{unit.file_stem}_{suffix}"



def normalize_src_dir(value: Path, root: Path) -> Path:
    """Return a safe path relative to project src/. Accepts data/x or src/data/x."""
    src_root = (root / "src").resolve()
    if value.is_absolute():
        try:
            rel = value.resolve().relative_to(src_root)
        except ValueError as exc:
            raise ValueError(f"--src-dir absolute path must be inside {src_root}") from exc
    else:
        rel = value
        if rel.parts and rel.parts[0].lower() == "src":
            rel = Path(*rel.parts[1:])
    if not rel.parts or str(rel) in {"", "."}:
        return Path(".")
    if rel.is_absolute() or any(part in {"", ".", ".."} for part in rel.parts):
        raise ValueError("--src-dir must be a normal path inside src/ (for example data/always)")
    return Path(*rel.parts)


def owner_is_under_src_dir(owner: str, src_dir: Path) -> bool:
    """Return True when an existing C split owner lives under src/src_dir.

    Split owners are src-relative project paths (for example data/always/foo.c).
    Rerun mode treats those existing paths as authoritative and never reaches
    outside the explicitly requested --src-dir tree.
    """
    path = Path(owner)
    if path.suffix.lower() != ".c" or path.is_absolute() or ".." in path.parts:
        return False
    if str(src_dir) == ".":
        return True
    try:
        path.relative_to(src_dir)
    except ValueError:
        return False
    return True


def read_promoted_splits(path: Path, sections: set[str], src_dir: Path,
                         owner_patterns: list[str] | None = None) -> tuple[list[Unit], dict[str, int]]:
    """Read existing promoted C owners scoped strictly to *src_dir*.

    Optional --unit patterns further narrow the already-scoped set; they never
    allow a split outside --src-dir back into the rerun.
    """
    all_units, all_stats = read_splits(path, sections, ["*"])
    patterns = owner_patterns or []
    units = [unit for unit in all_units
             if owner_is_under_src_dir(unit.owner, src_dir)
             and (not patterns or any(fnmatch.fnmatchcase(unit.owner, pattern) for pattern in patterns))]
    if not units:
        raise ValueError(f"No promoted .c split owners found under src/{src_dir.as_posix()}")
    stats = dict(all_stats)
    stats["selected_range_lines"] = len(units)
    stats["excluded_owner_ranges"] = max(0, len(all_units) - len(units))
    stats["empty_ranges"] = 0
    stats["duplicate_ranges"] = 0
    return units, stats


def _split_range_key(raw: str) -> tuple[str, int, int] | None:
    line = uncomment(raw)
    if not line or not line.startswith("."):
        return None
    parts = line.split()
    if not parts:
        return None
    attrs = dict(ATTR.findall(line))
    if not {"start", "end"} <= attrs.keys():
        return None
    try:
        return parts[0], number(attrs["start"]), number(attrs["end"])
    except ValueError:
        return None


def update_splits_text(text: str, assignments: list[tuple[Unit, str]]) -> tuple[str, list[str]]:
    """Move exact section ranges to src-relative TU owners without touching .text."""
    if not assignments:
        return text, []
    wanted: dict[tuple[str, int, int], str] = {}
    for unit, tu in assignments:
        key = (unit.section, unit.start, unit.end)
        previous = wanted.get(key)
        if previous is not None and previous != tu:
            raise ValueError(f"Split {unit.stem} was assigned to two TUs: {previous} and {tu}")
        wanted[key] = tu

    preamble: list[str] = []
    blocks: list[dict[str, Any]] = []
    current: dict[str, Any] | None = None
    for raw in text.splitlines():
        clean = uncomment(raw)
        if raw and not raw[0].isspace() and clean.endswith(":"):
            current = {"owner": clean[:-1], "header": raw, "body": []}
            blocks.append(current)
        elif current is None:
            preamble.append(raw)
        else:
            current["body"].append(raw)

    found = collections.Counter()
    for block in blocks:
        kept = []
        for raw in block["body"]:
            key = _split_range_key(raw)
            if key in wanted:
                found[key] += 1
                continue
            kept.append(raw)
        block["body"] = kept

    missing = [key for key in wanted if not found[key]]
    if missing:
        section, start, end = missing[0]
        raise ValueError(f"Could not find split range {section}:{start:#x}..{end:#x} while updating splits.txt")
    duplicated = [key for key, count in found.items() if count > 1]
    if duplicated:
        section, start, end = duplicated[0]
        raise ValueError(f"Split range {section}:{start:#x}..{end:#x} occurs more than once; refusing ambiguous update")

    by_owner: dict[str, dict[str, Any]] = {}
    for block in blocks:
        by_owner.setdefault(block["owner"], block)
    created: list[str] = []
    for unit, tu in assignments:
        block = by_owner.get(tu)
        if block is None:
            block = {"owner": tu, "header": f"{tu}:", "body": []}
            blocks.append(block)
            by_owner[tu] = block
        body: list[str] = block["body"]
        insert_at = len(body)
        while insert_at and not body[insert_at - 1].strip():
            insert_at -= 1
        body.insert(insert_at, f"\t{unit.section:<11} start:0x{unit.start:08X} end:0x{unit.end:08X}")
        created.append(tu)

    out: list[str] = list(preamble)
    for block in blocks:
        if out and out[-1].strip():
            out.append("")
        out.append(block["header"])
        out.extend(block["body"])
    return "\n".join(out).rstrip() + "\n", created



def normalize_dataobject_splits_text(text: str, sections: set[str]) -> tuple[str, dict[str, Any]]:
    """Explode the synthetic dataobject.obj aggregate into one raw owner per range.

    DTK uses an object/TU name as a link-order graph node. If the same synthetic
    owner has ranges at multiple positions with promoted C TUs between them, that
    single node is constrained to appear both before and after those TUs and DTK
    reports a cycle. Zero-length ranges can participate in those constraints too.

    Remove zero-length dataobject.obj ranges entirely and move every remaining
    nonempty selected-section range to a deterministic synthetic .obj owner. The
    raw unit remains unconfigured in configure.py so the project generator keeps
    using DTK's extracted original object until that range is later promoted to C.
    """
    newline = "\r\n" if "\r\n" in text else "\n"
    trailing_newline = text.endswith(("\n", "\r"))
    lines = text.splitlines()

    preamble: list[str] = []
    blocks: list[dict[str, Any]] = []
    current: dict[str, Any] | None = None
    for raw in lines:
        clean = uncomment(raw)
        if raw and not raw[0].isspace() and clean.endswith(":"):
            current = {"owner": clean[:-1], "header": raw, "body": []}
            blocks.append(current)
        elif current is None:
            preamble.append(raw)
        else:
            current["body"].append(raw)

    targets = [i for i, block in enumerate(blocks) if Path(block["owner"]).name.lower() == "dataobject.obj"]
    if not targets:
        return text, {"removed_empty": 0, "removed_empty_by_section": {}, "split_nonempty": [], "already_split": []}
    if len(targets) != 1:
        raise ValueError(f"splits.txt has {len(targets)} dataobject.obj blocks; refusing ambiguous repair")
    target_index = targets[0]
    target = blocks[target_index]

    existing_by_owner: dict[str, dict[str, Any]] = {block["owner"]: block for block in blocks}
    removed_empty: collections.Counter[str] = collections.Counter()
    split_nonempty: list[dict[str, Any]] = []
    already_split: list[str] = []
    new_blocks: list[dict[str, Any]] = []
    kept: list[str] = []
    seen_nonempty: set[tuple[str, int, int]] = set()

    for raw in target["body"]:
        key = _split_range_key(raw)
        if key is None:
            kept.append(raw)
            continue
        section, start, end = key
        if start == end:
            removed_empty[section] += 1
            continue
        if section not in sections:
            kept.append(raw)
            continue
        if key in seen_nonempty:
            raise ValueError(
                f"dataobject.obj contains duplicate nonempty range {section}:{start:#x}..{end:#x}; "
                "refusing to guess which copy is real"
            )
        seen_nonempty.add(key)
        section_tag = re.sub(r"[^A-Za-z0-9]+", "_", section.lstrip(".")) or "section"
        owner = f"dataobject_split_{section_tag}_{start:08X}.obj"
        existing = existing_by_owner.get(owner)
        if existing is not None:
            existing_keys = [_split_range_key(line) for line in existing["body"]]
            if key not in existing_keys:
                raise ValueError(f"Synthetic split owner collision: {owner}")
            already_split.append(owner)
            continue
        block = {"owner": owner, "header": f"{owner}:", "body": [raw]}
        existing_by_owner[owner] = block
        new_blocks.append(block)
        split_nonempty.append({
            "owner": owner,
            "section": section,
            "start": f"0x{start:08X}",
            "end": f"0x{end:08X}",
        })

    # Keep comments or unsupported nonempty sections if any. If nothing meaningful
    # remains, remove dataobject.obj entirely so it cannot become a graph node.
    target["body"] = kept
    meaningful = any(line.strip() and not line.lstrip().startswith(("#", "//")) for line in kept)
    if not meaningful:
        blocks.pop(target_index)
        insert_at = target_index
    else:
        insert_at = target_index + 1
    blocks[insert_at:insert_at] = new_blocks

    out: list[str] = list(preamble)
    for block in blocks:
        if out and out[-1].strip():
            out.append("")
        out.append(block["header"])
        out.extend(block["body"])
    result = newline.join(out).rstrip() + (newline if trailing_newline or out else "")
    return result, {
        "removed_empty": sum(removed_empty.values()),
        "removed_empty_by_section": dict(removed_empty),
        "split_nonempty": split_nonempty,
        "already_split": already_split,
    }


def _call_name(node: ast.AST) -> str | None:
    return node.id if isinstance(node, ast.Name) else None


def update_configure_text(text: str, module: str, tu_paths: list[str]) -> tuple[str, list[str]]:
    """Add missing Object(NonMatching, path) entries to Rel(module, [...])."""
    unique = list(dict.fromkeys(path.replace("\\", "/") for path in tu_paths))
    if not unique:
        return text, []
    tree = ast.parse(text)
    existing: set[str] = set()
    for node in ast.walk(tree):
        if isinstance(node, ast.Call) and _call_name(node.func) == "Object" and len(node.args) >= 2:
            value = node.args[1]
            if isinstance(value, ast.Constant) and isinstance(value.value, str):
                existing.add(value.value.replace("\\", "/"))
    missing = [path for path in unique if path not in existing]
    if not missing:
        return text, []

    libs: ast.List | None = None
    for node in ast.walk(tree):
        if not isinstance(node, (ast.Assign, ast.AnnAssign)):
            continue
        targets = node.targets if isinstance(node, ast.Assign) else [node.target]
        if any(isinstance(t, ast.Attribute) and isinstance(t.value, ast.Name) and
               t.value.id == "config" and t.attr == "libs" for t in targets):
            value = node.value
            if not isinstance(value, ast.List):
                raise ValueError("configure.py config.libs is not a list")
            libs = value
            break
    if libs is None or libs.end_lineno is None:
        raise ValueError("Could not locate config.libs in configure.py")

    rel_list: ast.List | None = None
    for element in libs.elts:
        if not isinstance(element, ast.Call) or _call_name(element.func) != "Rel" or len(element.args) < 2:
            continue
        name = element.args[0]
        if isinstance(name, ast.Constant) and name.value == module:
            if not isinstance(element.args[1], ast.List):
                raise ValueError(f'configure.py Rel("{module}") object argument is not a list')
            rel_list = element.args[1]
            break

    lines = text.splitlines()
    if rel_list is not None and rel_list.end_lineno is not None:
        insert_at = rel_list.end_lineno - 1
        indent = " " * (rel_list.col_offset + 4)
        entries = [f'{indent}Object(NonMatching, "{path}"),' for path in missing]
        lines[insert_at:insert_at] = entries
    else:
        insert_at = libs.end_lineno - 1
        block = [
            "    Rel(",
            f'        "{module}",',
            "        [",
            *[f'            Object(NonMatching, "{path}"),' for path in missing],
            "        ],",
            "    ),",
        ]
        lines[insert_at:insert_at] = block
    updated = "\n".join(lines) + ("\n" if text.endswith(("\n", "\r")) else "")
    ast.parse(updated)
    return updated, missing


def atomic_write_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_name(path.name + ".assetdis.tmp")
    tmp.write_text(text, encoding="utf-8")
    os.replace(tmp, path)


def promote_definition_storage(source: str, symbol: Symbol) -> tuple[str, bool]:
    """Make one generated local definition externally visible to other generated TUs."""
    changed = False
    forward = re.compile(
        r"^static\s+([A-Za-z_]\w*\s*\*?)\s+" + re.escape(symbol.name) + r"(\[\])?\s*;\s*$",
        re.M,
    )
    source, forward_count = forward.subn(
        lambda m: f"extern {m[1]} {symbol.name}{m[2] or ''};", source
    )
    changed |= bool(forward_count)
    matches = [m for m in DECL.finditer(source) if m[3] == symbol.name]
    if len(matches) != 1:
        raise ValueError(
            f"Expected one definition of {symbol.name!r} while exporting "
            f"{symbol.section}:0x{symbol.address:08X}; found {len(matches)}"
        )
    match = matches[0]
    if match[1] is None:
        return source, changed
    replacement = match[0][len(match[1]):]
    return source[:match.start()] + replacement + source[match.end():], True


def recipe_symbol(entry: str) -> str:
    """Return the symbol selector from one generated extraction entry."""
    match = re.search(r"^  - symbol:\s*(.+?)\s*$", entry, re.M)
    if match is None:
        raise ValueError("Generated extraction entry has no symbol selector")
    return match.group(1)


def module_object_matches(value: str, module: str) -> bool:
    """Match files/forestd.rel, files/forestd.rel.szs, quoted variants, etc."""
    value = value.strip().strip('"\'')
    base = Path(value).name
    return base == module or base.startswith(module + ".")


def update_config_yml_text(text: str, module: str, entries: list[str]) -> tuple[str, list[str]]:
    """Add/update generated extract entries inside one module block without reformatting YAML."""
    if not entries:
        return text, []
    newline = "\r\n" if "\r\n" in text else "\n"
    trailing_newline = text.endswith(("\n", "\r"))
    lines = text.splitlines()

    modules_index = next((i for i, line in enumerate(lines) if line.strip() == "modules:" and not line[:1].isspace()), None)
    if modules_index is None:
        raise ValueError("config.yml has no top-level modules: list")

    target_start = target_end = None
    object_re = re.compile(r"^- object:\s*(.+?)\s*$")
    starts: list[tuple[int, str]] = []
    for i in range(modules_index + 1, len(lines)):
        match = object_re.match(lines[i])
        if match:
            starts.append((i, match.group(1)))
    for n, (start, value) in enumerate(starts):
        if module_object_matches(value, module):
            if target_start is not None:
                raise ValueError(f"config.yml has multiple module entries matching {module!r}")
            target_start = start
            target_end = starts[n + 1][0] if n + 1 < len(starts) else len(lines)
    if target_start is None or target_end is None:
        raise ValueError(f"Could not find the {module} module in config.yml")

    extract_line = next((i for i in range(target_start + 1, target_end) if re.match(r"^  extract:\s*(?:#.*)?$", lines[i])), None)
    if extract_line is None:
        # Put extract after splits/symbols metadata when possible, otherwise before the next module.
        insert_at = target_start + 1
        for i in range(target_start + 1, target_end):
            if re.match(r"^  (?:hash|symbols|splits|symbols_known|fill_gaps|mw_comment_version):", lines[i]):
                insert_at = i + 1
        rendered = ["  extract:"]
        for entry in entries:
            rendered.extend(entry.rstrip("\n").splitlines())
        lines[insert_at:insert_at] = rendered + [""]
        result = newline.join(lines) + (newline if trailing_newline else "")
        return result, [recipe_symbol(entry) for entry in entries]

    # extract: must be a block list, not [] / inline YAML. Find where that list ends.
    extract_end = target_end
    for i in range(extract_line + 1, target_end):
        line = lines[i]
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        indent = len(line) - len(line.lstrip(" "))
        if indent < 2 or (indent == 2 and not line.startswith("  - ")):
            extract_end = i
            break

    symbol_re = re.compile(r"^  - symbol:\s*(.+?)\s*$")
    existing: dict[str, list[tuple[int, int]]] = collections.defaultdict(list)
    starts2: list[tuple[int, str]] = []
    for i in range(extract_line + 1, extract_end):
        match = symbol_re.match(lines[i])
        if match:
            starts2.append((i, match.group(1)))
    for n, (start, symbol) in enumerate(starts2):
        end = starts2[n + 1][0] if n + 1 < len(starts2) else extract_end
        # Keep blank separators outside the entry so replacement is stable.
        while end > start + 1 and not lines[end - 1].strip():
            end -= 1
        existing[symbol].append((start, end))

    desired: dict[str, list[str]] = {}
    order: list[str] = []
    for entry in entries:
        symbol = recipe_symbol(entry)
        block = entry.rstrip("\n").splitlines()
        if symbol in desired:
            if desired[symbol] != block:
                raise ValueError(f"Conflicting generated extraction entries for {symbol!r}")
            continue
        desired[symbol] = block
        order.append(symbol)

    changed: list[str] = []
    replacements: list[tuple[int, int, list[str]]] = []
    additions: list[list[str]] = []
    for symbol in order:
        block = desired[symbol]
        if symbol in existing:
            matches = existing[symbol]
            if len(matches) != 1:
                raise ValueError(f"config.yml extract list has {len(matches)} entries for generated selector {symbol!r}")
            start, end = matches[0]
            if lines[start:end] != block:
                replacements.append((start, end, block))
                changed.append(symbol)
        else:
            additions.append(block)
            changed.append(symbol)

    for start, end, block in sorted(replacements, reverse=True):
        lines[start:end] = block
        delta = len(block) - (end - start)
        extract_end += delta

    if additions:
        # Insert before trailing blank lines / next module key.
        insert_at = extract_end
        while insert_at > extract_line + 1 and not lines[insert_at - 1].strip():
            insert_at -= 1
        rendered: list[str] = []
        if insert_at > extract_line + 1:
            rendered.append("")
        for n, block in enumerate(additions):
            if n:
                rendered.append("")
            rendered.extend(block)
        lines[insert_at:insert_at] = rendered

    result = newline.join(lines) + (newline if trailing_newline else "")
    return result, changed



def extract_entries_from_source(source: str, unit: Unit) -> list[str]:
    """Reconstruct config.yml extraction entries from one generated C TU.

    This is used to backfill projects where the TU/split/configure entry was promoted
    by an older batch_assetdis version before config.yml synchronization existed.
    """
    declarations = list(DECL.finditer(source))
    symbols = {s.name: s for s in unit.symbols}
    entries: list[str] = []
    include_re = re.compile(r'^\s*#include\s+"(assets/[^"\n]+\.inc)"\s*$', re.M)
    for include in include_re.finditer(source):
        previous = None
        for declaration in declarations:
            if declaration.start() >= include.start():
                break
            previous = declaration
        if previous is None or not previous[4]:
            raise ValueError(f"Could not associate {include[1]} with an array declaration in {unit.owner}")
        kind, name = previous[2].strip(), previous[3]
        if name not in symbols:
            raise ValueError(f"Asset include {include[1]} belongs to {name}, which is not in split {unit.owner}")
        if kind not in {"u8", "u16", "Vtx"}:
            raise ValueError(f"Unsupported asset include while syncing {unit.owner}: {kind} {name}")
        symbol = symbols[name]
        selector = (f"{symbol.name}!{symbol.section}:0x{symbol.address:08X}"
                    if symbol.scope == "local" else symbol.name)
        header = include[1]
        binary = header[:-4] + ".bin"
        entry = (f"  - symbol: {selector}\n"
                 f"    binary: {binary}\n"
                 f"    header: {header}\n")
        entry += {
            "u8": "    header_type: raw\n",
            "u16": "    header_type: none\n    custom_type: pal16\n",
            "Vtx": "    header_type: none\n    custom_type: vtx\n",
        }[kind]
        entries.append(entry)
    return entries


def collect_existing_project_extract_entries(root: Path, splits_text: str, src_dir: Path,
                                             symbols: list[Symbol], sections: set[str]) -> list[str]:
    """Collect extraction entries from already-promoted C TUs under src/src_dir."""
    import tempfile
    prefix = src_dir.as_posix().rstrip("/")
    pattern = f"{prefix}/*.c" if prefix and prefix != "." else "*.c"
    with tempfile.TemporaryDirectory() as td:
        path = Path(td) / "splits.txt"
        path.write_text(splits_text, encoding="utf-8")
        try:
            units, _ = read_splits(path, sections, [pattern])
        except ValueError as exc:
            if str(exc) == "No nonempty selected data ranges in splits.txt":
                return []
            raise
    assign_symbols(units, symbols)
    entries: list[str] = []
    for unit in units:
        source_path = root / "src" / unit.owner
        if not source_path.is_file():
            raise ValueError(f"Promoted split owner has no source file: {source_path}")
        source = source_path.read_text(encoding="utf-8-sig")
        entries.extend(extract_entries_from_source(source, unit))
    return entries


def normalize_generated_definition_alignments(source: str, unit: Unit, entry_align: int = 1) -> tuple[str, dict[str, int]]:
    """Apply the generated-source alignment policy to one promoted TU.

    DTK symbol metadata contains 4/8/32-byte symbol alignments.  Four-byte alignment
    is the compiler default and may be omitted, but explicit 8- and 32-byte symbol
    requirements must be preserved.  A separate inferred entry_align can promote
    the first definition of a TU to 32+ when that *next TU* is what created an
    inter-TU alignment gap in the original aggregate data layout.
    """
    current = {symbol.name: symbol for symbol in unit.symbols}
    first_symbol = min(unit.symbols, key=lambda symbol: symbol.address) if unit.symbols else None
    matches = [match for match in DECL.finditer(source) if match[3] in current]
    by_name: dict[str, list[re.Match[str]]] = collections.defaultdict(list)
    for match in matches:
        by_name[match[3]].append(match)
    missing = sorted(name for name in current if name not in by_name)
    duplicate = sorted(name for name, found in by_name.items() if len(found) != 1)
    if missing or duplicate:
        details = []
        if missing:
            details.append("missing definitions: " + ", ".join(missing[:8]))
        if duplicate:
            details.append("duplicate definitions: " + ", ".join(duplicate[:8]))
        raise ValueError(f"Cannot repair alignments in {unit.owner}: " + "; ".join(details))

    removed_low = 0
    restored_high = 0
    entry_promoted = 0
    changed_defs = 0
    for match in reversed(matches):
        symbol = current[match[3]]
        original = match[0]
        attr = re.search(r"ATTRIBUTE_ALIGN\((\d+)\)", original)
        line = re.sub(r"\s*ATTRIBUTE_ALIGN\(\d+\)", "", original)
        desired_align = symbol.align if symbol.align >= 8 else 1
        if first_symbol is not None and symbol.key == first_symbol.key and entry_align >= 8:
            desired_align = max(desired_align, entry_align)
        if desired_align >= 8:
            line = line[:-1].rstrip() + f" ATTRIBUTE_ALIGN({desired_align}) ="
            if attr is None or int(attr.group(1)) != desired_align:
                restored_high += 1
                if first_symbol is not None and symbol.key == first_symbol.key and desired_align > symbol.align:
                    entry_promoted += 1
        elif attr is not None:
            removed_low += 1
        if line != original:
            changed_defs += 1
            source = source[:match.start()] + line + source[match.end():]
    return source, {"definitions": changed_defs, "removed_low": removed_low,
                    "restored_high": restored_high, "entry_promoted": entry_promoted}


def repair_existing_project_alignments(root: Path, splits_path: Path, src_dir: Path,
                                       symbols: list[Symbol], sections: set[str],
                                       write: bool) -> dict[str, Any]:
    """Normalize alignment attributes in already-promoted generated TUs."""
    prefix = src_dir.as_posix().rstrip("/")
    pattern = f"{prefix}/*.c" if prefix and prefix != "." else "*.c"
    try:
        all_units, _ = read_splits(splits_path, sections, ["*"])
    except ValueError as exc:
        if str(exc) == "No nonempty selected data ranges in splits.txt":
            return {"files": [], "definitions": 0, "removed_low": 0, "restored_high": 0,
                    "entry_promoted": 0, "entry_alignments": {}}
        raise
    assign_symbols(all_units, symbols)
    entry_alignments = infer_tu_entry_alignments(all_units)
    units = [unit for unit in all_units if fnmatch.fnmatchcase(unit.owner, pattern)]
    changed_files: list[str] = []
    definitions = removed_low = restored_high = entry_promoted = 0
    for unit in units:
        if not unit.symbols:
            continue
        source_path = root / "src" / unit.owner
        if not source_path.is_file():
            raise ValueError(f"Promoted split owner has no source file: {source_path}")
        source = source_path.read_text(encoding="utf-8-sig")
        updated, stats = normalize_generated_definition_alignments(
            source, unit, entry_alignments.get(unit_key(unit), 1))
        definitions += stats["definitions"]
        removed_low += stats["removed_low"]
        restored_high += stats["restored_high"]
        entry_promoted += stats["entry_promoted"]
        if updated != source:
            changed_files.append(unit.owner)
            if write:
                atomic_write_text(source_path, updated)
    relevant_entry_alignments = {unit.owner: entry_alignments[unit_key(unit)] for unit in units
                                 if unit_key(unit) in entry_alignments}
    return {"files": changed_files, "definitions": definitions, "removed_low": removed_low,
            "restored_high": restored_high, "entry_promoted": entry_promoted,
            "entry_alignments": relevant_entry_alignments}


def sync_existing_project_config(root: Path, splits_path: Path, config_yml_path: Path, module: str,
                                 src_dir: Path, symbols: list[Symbol], sections: set[str],
                                 write: bool) -> tuple[list[str], int]:
    """Backfill config.yml entries from already-promoted sources."""
    splits_text = splits_path.read_text(encoding="utf-8-sig")
    entries = collect_existing_project_extract_entries(root, splits_text, src_dir, symbols, sections)
    config_text = config_yml_path.read_text(encoding="utf-8-sig")
    updated, changed = update_config_yml_text(config_text, module, entries)
    if write and updated != config_text:
        atomic_write_text(config_yml_path, updated)
    return changed, len(entries)

def read_splits_from_text_for_validation(text: str, sections: set[str]) -> tuple[list[Unit], dict[str, int]]:
    """Parse updated split text without depending on a project path."""
    import tempfile
    with tempfile.TemporaryDirectory() as td:
        path = Path(td) / "splits.txt"
        path.write_text(text, encoding="utf-8")
        return read_splits(path, sections, ["*"])


def install_project_tus(root: Path, splits_path: Path, configure_path: Path, config_yml_path: Path, module: str,
                        src_dir: Path, converted: list[tuple[Unit, Path, str, list[str]]],
                        symbols: list[Symbol], sections: set[str],
                        overwrite_source: bool = False,
                        local_exports: list[Symbol] | None = None) -> dict[str, Any]:
    """Install converted sources and atomically update splits/configure/config.yml metadata."""
    if not converted:
        return {"sources": [], "splits": [], "configure": [], "extract": [], "local_exports": []}
    local_exports = list({s.key: s for s in (local_exports or [])}.values())
    assignments: list[tuple[Unit, str]] = []
    source_writes: list[tuple[Path, str, str]] = []
    extract_entries: list[str] = []
    for unit, _staged, source, entries in converted:
        extract_entries.extend(entries)
        rel = (src_dir / f"{unit.file_stem}.c") if str(src_dir) != "." else Path(f"{unit.file_stem}.c")
        tu = rel.as_posix()
        target = root / "src" / rel
        if target.exists():
            existing = target.read_text(encoding="utf-8")
            if existing != source and not overwrite_source:
                raise ValueError(f"Refusing to overwrite existing source {target}; pass --overwrite-source to replace it")
        assignments.append((unit, tu))
        source_writes.append((target, source, tu))

    splits_text = splits_path.read_text(encoding="utf-8-sig")
    # A generated TU may reference a symbol that DTK metadata calls local because
    # several objects use the same spelling. The completed ac-decomp sources solve
    # this by exposing exactly the referenced occurrence to C while keeping its
    # extraction selector address-qualified. Patch the defining generated source,
    # whether it is part of this batch or was promoted by an earlier run.
    support_writes: dict[Path, str] = {}
    exported_selectors: list[str] = []
    if local_exports:
        all_units, _ = read_splits_from_text_for_validation(splits_text, sections)
        assign_symbols(all_units, symbols)
        current_owner: dict[tuple[str, int], str] = {}
        for owner_unit in all_units:
            for symbol in owner_unit.symbols:
                current_owner[symbol.key] = owner_unit.owner

        staged_owner: dict[tuple[str, int], int] = {}
        for index, (unit, _tu) in enumerate(assignments):
            for symbol in unit.symbols:
                staged_owner[symbol.key] = index

        exported_by_name: dict[str, set[tuple[str, int]]] = collections.defaultdict(set)
        for symbol in local_exports:
            exported_by_name[symbol.name].add(symbol.key)
        conflicts = {name: keys for name, keys in exported_by_name.items() if len(keys) > 1}
        if conflicts:
            name, keys = next(iter(conflicts.items()))
            choices = ", ".join(f"{section}:0x{address:08X}" for section, address in sorted(keys))
            raise ValueError(f"Multiple local occurrences of {name!r} need external linkage: {choices}; rename/alias one manually")

        for symbol in local_exports:
            if symbol.key in staged_owner:
                index = staged_owner[symbol.key]
                target, source, tu = source_writes[index]
                source, _changed = promote_definition_storage(source, symbol)
                source_writes[index] = (target, source, tu)
            else:
                owner = current_owner.get(symbol.key)
                if owner is None:
                    raise ValueError(
                        f"Could not find owner for local export {symbol.name} at "
                        f"{symbol.section}:0x{symbol.address:08X}"
                    )
                if Path(owner).suffix.lower() != ".c":
                    raise ValueError(
                        f"Local export {symbol.name} at {symbol.section}:0x{symbol.address:08X} "
                        f"is still owned by {owner}; convert/promote that range before linking this TU"
                    )
                target = root / "src" / owner
                if not target.is_file():
                    raise ValueError(f"Local export owner has no source file: {target}")
                source = support_writes.get(target, target.read_text(encoding="utf-8-sig"))
                source, changed = promote_definition_storage(source, symbol)
                if changed:
                    support_writes[target] = source
            exported_selectors.append(f"{symbol.name}!{symbol.section}:0x{symbol.address:08X}")

    # Backfill extraction metadata for TUs that may have been promoted by an older
    # batch_assetdis version before config.yml synchronization existed.
    extract_entries = collect_existing_project_extract_entries(root, splits_text, src_dir, symbols, sections) + extract_entries
    new_splits, moved = update_splits_text(splits_text, assignments)
    new_splits, raw_split_repair = normalize_dataobject_splits_text(new_splits, sections)
    configure_text = configure_path.read_text(encoding="utf-8-sig")
    new_configure, added = update_configure_text(configure_text, module, [tu for _, _, tu in source_writes])
    config_yml_text = config_yml_path.read_text(encoding="utf-8-sig")
    new_config_yml, extract_changed = update_config_yml_text(config_yml_text, module, extract_entries)

    test_units, _ = read_splits_from_text_for_validation(new_splits, {u.section for u, _ in assignments})
    expected = {(u.section, u.start, u.end): tu for u, tu in assignments}
    seen = {(u.section, u.start, u.end): u.owner for u in test_units}
    for key, tu in expected.items():
        if seen.get(key) != tu:
            raise ValueError(f"Internal error validating splits.txt update for {tu}")
    ast.parse(new_configure)

    for target, source, _tu in source_writes:
        atomic_write_text(target, source)
    for target, source in support_writes.items():
        atomic_write_text(target, source)
    atomic_write_text(splits_path, new_splits)
    atomic_write_text(configure_path, new_configure)
    atomic_write_text(config_yml_path, new_config_yml)
    return {"sources": [tu for _, _, tu in source_writes], "splits": moved, "configure": added,
            "extract": extract_changed, "local_exports": exported_selectors,
            "raw_split_repair": raw_split_repair}

def install_rerun_project_tus(root: Path, config_yml_path: Path, module: str, src_dir: Path,
                                converted: list[tuple[Unit, Path, str, list[str]]]) -> dict[str, Any]:
    """Overwrite selected promoted sources in place without changing ownership metadata.

    This is deliberately narrower than install_project_tus: split owners are
    authoritative, so rerunning generated sources cannot rename/move TUs or add
    duplicate configure.py entries.  The src-dir scope is revalidated here as a
    final guard before any write.
    """
    if not converted:
        return {"sources": [], "splits": [], "configure": [], "extract": [],
                "local_exports": [], "raw_split_repair": {}}

    source_writes: list[tuple[Path, str, str]] = []
    extract_entries: list[str] = []
    for unit, _staged, source, entries in converted:
        if not owner_is_under_src_dir(unit.owner, src_dir):
            raise ValueError(
                f"Refusing rerun outside src/{src_dir.as_posix()}: split owner {unit.owner}"
            )
        target = root / "src" / unit.owner
        if not target.is_file():
            raise ValueError(f"Promoted split owner has no source file: {target}")
        source_writes.append((target, source, unit.owner))
        extract_entries.extend(entries)

    config_yml_text = config_yml_path.read_text(encoding="utf-8-sig")
    new_config_yml, extract_changed = update_config_yml_text(config_yml_text, module, extract_entries)

    for target, source, _owner in source_writes:
        atomic_write_text(target, source)
    if new_config_yml != config_yml_text:
        atomic_write_text(config_yml_path, new_config_yml)

    return {"sources": [owner for _target, _source, owner in source_writes],
            "splits": [], "configure": [], "extract": extract_changed,
            "local_exports": [], "raw_split_repair": {}}


def operands(text: str) -> list[str]:
    """Split comma lists without splitting quoted strings or escaped quotes."""
    result: list[str] = []
    quote = ""
    escaped = False
    start = 0
    for i, char in enumerate(text):
        if escaped:
            escaped = False
        elif char == "\\" and quote:
            escaped = True
        elif quote:
            if char == quote:
                quote = ""
        elif char in {"\"", "'"}:
            quote = char
        elif char == ",":
            result.append(text[start:i].strip())
            start = i + 1
    if quote:
        raise ValueError("Unterminated quoted operand")
    result.append(text[start:].strip())
    if not all(result):
        raise ValueError("Missing operand")
    return result


def decode_object(obj: AsmObject) -> None:
    """Decode the supported data directives; fail rather than silently lose bytes."""
    data = bytearray()
    refs: dict[int, str] = {}
    labels: dict[str, int] = {}
    for raw in obj.body:
        line = uncomment(raw)
        if not line:
            continue
        label = re.match(r"^(\S+):\s*(.*)$", line)
        if label:
            labels[label[1]] = len(data)
            line = label[2]
            if not line:
                continue
        pieces = line.split(None, 1)
        directive = pieces[0]
        args = operands(pieces[1]) if len(pieces) == 2 else []
        if directive in {".4byte", ".long", ".2byte", ".short", ".byte"}:
            width = {".4byte": 4, ".long": 4, ".2byte": 2, ".short": 2, ".byte": 1}[directive]
            if not args:
                raise ValueError(f"Missing operand: {line}")
            for arg in args:
                try:
                    value = number(arg)
                except ValueError:
                    if width != 4 or not EXPR.fullmatch(arg):
                        raise ValueError(f"Unsupported data expression: {line}") from None
                    refs[len(data)] = arg
                    value = 0
                if not -(1 << (width * 8 - 1)) <= value < (1 << (width * 8)):
                    raise ValueError(f"Integer does not fit {width} bytes: {arg}")
                data.extend((value & ((1 << (width * 8)) - 1)).to_bytes(width, "big"))
        elif directive == ".rel":
            if len(args) != 2:
                raise ValueError(f"Expected .rel symbol, label: {line}")
            refs[len(data)] = f".rel {args[0]}, {args[1]}"
            data.extend(bytes(4))
        elif directive in {".ascii", ".asciz", ".string"}:
            for arg in args:
                value = ast.literal_eval(arg)
                if not isinstance(value, str):
                    raise ValueError(f"Expected an assembly string: {line}")
                data.extend(value.encode("latin-1"))
                if directive != ".ascii":
                    data.append(0)
        elif directive in {".float", ".double"}:
            for arg in args:
                data.extend(struct.pack(">f" if directive == ".float" else ">d", float(arg)))
        elif directive in {".skip", ".space", ".zero"}:
            if not 1 <= len(args) <= 2:
                raise ValueError(f"Unsupported padding: {line}")
            count = number(args[0])
            fill = number(args[1]) if len(args) == 2 else 0
            if not 0 <= count <= obj.symbol.size or not 0 <= fill <= 255:
                raise ValueError(f"Invalid padding: {line}")
            data.extend(bytes([fill]) * count)
        elif directive in {".balign", ".align"}:
            if len(args) != 1:
                raise ValueError(f"Unsupported alignment operands: {line}")
            align = number(args[0])
            if directive == ".align":
                if not 0 <= align <= 20:
                    raise ValueError(f"Invalid alignment: {line}")
                align = 1 << align
            if not 1 <= align <= 1 << 20:
                raise ValueError(f"Invalid alignment: {line}")
            data.extend(bytes(-(obj.symbol.address + len(data)) % align))
        else:
            raise ValueError(f"Unsupported assembly directive: {line}")
        if len(data) > obj.symbol.size:
            raise ValueError(f"Decoded size exceeds symbols.txt size ({obj.symbol.size:#x})")
    if len(data) != obj.symbol.size:
        raise ValueError(f"Assembly size {len(data):#x} != symbols.txt size {obj.symbol.size:#x}")
    obj.data, obj.references, obj.labels = bytes(data), refs, labels


def index_assembly(asm_path: Path, symbols: list[Symbol]) -> tuple[dict[tuple[str, int], AsmObject], list[str]]:
    paths = [asm_path] if asm_path.is_file() else sorted(set(asm_path.rglob("*.s")) | set(asm_path.rglob("*.S")))
    if not paths:
        raise ValueError(f"No generated .s files at {asm_path}; splits/symbols do not contain asset bytes")
    by_key = {s.key: s for s in symbols}
    by_name_addr: dict[tuple[str, int], list[Symbol]] = collections.defaultdict(list)
    by_name: dict[str, list[Symbol]] = collections.defaultdict(list)
    for s in symbols:
        by_name_addr[s.name, s.address].append(s)
        by_name[s.name].append(s)
    for candidates in by_name.values():
        candidates.sort(key=lambda s: (s.section, s.address))
    found: dict[tuple[str, int], AsmObject] = {}
    warnings: list[str] = []
    inferred_without_comments = 0
    ambiguous_inferred = 0
    for path in paths:
        section: str | None = None
        address: int | None = None
        active: tuple[str, str, int, int | None, str | None] | None = None
        body: list[str] = []
        with path.open(encoding="utf-8-sig") as stream:
            for lineno, raw in enumerate(stream, 1):
                clean = uncomment(raw)
                if active:
                    if clean.startswith(".endobj "):
                        name, scope, start_line, obj_addr, obj_section = active
                        if clean.split(None, 1)[1].strip() != name:
                            raise ValueError(f"{path}:{lineno}: .endobj name does not match {name}")
                        if obj_addr is None:
                            # Many generated dataobject.s files omit address comments entirely.
                            # symbols.txt already gives us section/address/size, so match by name,
                            # scope, and decodable size before falling back to metadata order.
                            #
                            # A generated assembly tree may also contain duplicate copies of the
                            # same object (for example a large dataobject.s plus a split-specific
                            # .s).  With repeated local names, blindly consuming the next unused
                            # metadata occurrence can then pair an 0x800-byte duplicate body with
                            # an unrelated 0x100-byte occurrence of the same local name.  Always
                            # probe unused occurrences first; if none fit and this body is an exact
                            # copy of an already indexed occurrence, ignore it as a duplicate.
                            candidates = [s for s in by_name.get(name, []) if s.key not in found]
                            if obj_section is not None:
                                candidates = [s for s in candidates if s.section == obj_section]
                            scope_candidates = [s for s in candidates if s.scope == scope]
                            if scope_candidates:
                                candidates = scope_candidates

                            decodable: list[Symbol] = []
                            for candidate in candidates:
                                probe = AsmObject(candidate, name, body[:], str(path), start_line)
                                try:
                                    decode_object(probe)
                                except (ValueError, SyntaxError, UnicodeError, OverflowError, struct.error):
                                    continue
                                decodable.append(candidate)

                            if decodable:
                                candidates = decodable
                            elif candidates:
                                duplicate = next((
                                    previous for previous in found.values()
                                    if previous.name == name
                                    and previous.symbol.scope == scope
                                    and (obj_section is None or previous.symbol.section == obj_section)
                                    and previous.body == body
                                ), None)
                                if duplicate is not None:
                                    warnings.append(
                                        f"Identical assembly copy ignored: {name} in {path} "
                                        f"(already indexed from {duplicate.path})"
                                    )
                                    candidates = []
                                # Otherwise leave candidates intact.  Selecting the next metadata
                                # occurrence below preserves the old diagnostic behavior: decode
                                # will attach the actual size/content error to that occurrence.

                            if candidates:
                                # symbols.txt is address-sorted, and dataobject.s is normally emitted
                                # in object order.  For genuinely indistinguishable repeated locals,
                                # consume the next unused metadata occurrence.
                                candidates.sort(key=lambda s: (s.section, s.address))
                                if len(candidates) > 1:
                                    ambiguous_inferred += 1
                                candidates = [candidates[0]]
                                inferred_without_comments += 1
                        elif obj_section is not None:
                            s = by_key.get((obj_section, obj_addr))
                            candidates = [s] if s else []
                        else:
                            candidates = by_name_addr.get((name, obj_addr), [])
                        if len(candidates) > 1:
                            raise ValueError(f"{path}:{start_line}: ambiguous object section for {name}")
                        if candidates:
                            s = candidates[0]
                            obj = AsmObject(s, name, body[:], str(path), start_line)
                            if name != s.name:
                                obj.error = f"Assembly name {name!r} != metadata name {s.name!r} at {s.section}:{s.address:#x}"
                            elif scope != s.scope:
                                obj.error = f"Assembly scope {scope!r} != metadata scope {s.scope!r}"
                            elif not re.fullmatch(IDENT, name):
                                obj.error = f"{name!r} is not a C identifier; give it a valid name in symbols.txt first"
                            else:
                                try:
                                    decode_object(obj)
                                except (ValueError, SyntaxError, UnicodeError, OverflowError, struct.error) as exc:
                                    obj.error = str(exc)
                            previous = found.get(s.key)
                            if previous is not None:
                                if previous.name != obj.name or previous.body != obj.body or previous.error != obj.error:
                                    previous.error = f"Conflicting assembly copies for {s.name}: {previous.path} and {path}"
                                else:
                                    warnings.append(f"Identical assembly copy ignored: {s.name} in {path}")
                            else:
                                found[s.key] = obj
                        active, body, address = None, [], None
                    elif OBJ.fullmatch(clean):
                        raise ValueError(f"{path}:{lineno}: nested .obj")
                    else:
                        body.append(raw.rstrip("\n"))
                    continue
                sm = SECTION.match(clean)
                if sm:
                    section, address = sm[1], None
                    continue
                if clean in {".text", ".data", ".rodata", ".bss", ".sdata", ".sdata2"}:
                    section, address = clean, None
                    continue
                am = ADDRESS.match(raw)
                if am:
                    address = int(am[2], 16)
                    continue
                om = OBJ.fullmatch(clean)
                if om:
                    active = (om[1], om[2], lineno, address, section)
                    body = []
                    continue
                # Do not reuse an older function/object's address across unrelated content.
                if clean and not clean.startswith((".balign", ".align")):
                    address = None
        if active:
            raise ValueError(f"{path}:{active[2]}: unterminated .obj {active[0]}")
    if inferred_without_comments:
        message = (f"Assembly address comments absent for {inferred_without_comments} matched objects; "
                   "used symbols.txt name/section/scope/size metadata instead")
        if ambiguous_inferred:
            message += f" ({ambiguous_inferred} repeated-name occurrences resolved by metadata order)"
        warnings.append(message)
    return found, warnings


def guess_type(name: str) -> str:
    """Only the name-based conventions already present in assetdis.py."""
    if name.endswith(("_v", "_v2")):
        return "Vtx"
    if "_model" in name or name.endswith(("_setmode", "_modeset", "_mode", "_gfx", "_vtx", "_gfx2")):
        return "Gfx"
    if name.endswith("_pal"):
        return "u16"
    if name.startswith("cKF_bs_r"):
        return "cKF_Skeleton_R_c"
    if name.startswith("cKF_ba_r_npc"):
        return "aNPC_Animation_c"
    if name.startswith("cKF_ba_r"):
        return "cKF_Animation_R_c"
    if name.endswith("evw_anime"):
        return "EVW_ANIME_DATA"
    return "u8"


def c_type(kind: str) -> str:
    return {"PAL": "u16", "TEX": "u8", "VOID*_LIST": "void*",
            "EVW_ANIME_TYPE_SCROLL1": "EVW_ANIME_SCROLL", "EVW_ANIME_TYPE_SCROLL2": "EVW_ANIME_SCROLL",
            "EVW_ANIME_TYPE_COLREG_MANUAL": "EVW_ANIME_COLREG", "EVW_ANIME_TYPE_COLREG_LINEAR": "EVW_ANIME_COLREG",
            "EVW_ANIME_TYPE_COLREG_NONLINEAR": "EVW_ANIME_COLREG", "EVW_ANIME_TYPE_TEXANIME": "EVW_ANIME_TEXANIME"}.get(kind, kind)


def load_assetdis(path: Path) -> Any:
    if not path.is_file():
        raise ValueError(f"assetdis.py not found: {path}; use --assetdis PATH")
    sys.path.insert(0, str(path.parent))
    spec = importlib.util.spec_from_file_location("_batch_assetdis_converter", path)
    if spec is None or spec.loader is None:
        raise ValueError(f"Cannot import {path}")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    for name in ("convert_source_to_gfx_c_source", "get_required_includes", "parse_bin_formatted"):
        if not callable(getattr(module, name, None)):
            raise ValueError("Use the previously updated assetdis.py (selective includes + revision support)")
    return module


class Adapter:
    """Use assetdis's converters with indexed bytes and checked relocation lookups.

    This avoids repeatedly scanning the huge original assembly and prevents its
    recursive parser from trying to decode NULL or an external symbol as a local
    object. No on-disk changes to assetdis.py are made.
    """
    def __init__(self, module: Any, objects: dict[tuple[str, int], AsmObject], root: Path, types: dict[str, str]):
        self.module = module
        self.objects = objects
        self.local: dict[str, AsmObject] = {}
        self.external_local: dict[str, AsmObject] = {}
        self.types = types
        self.discovered: dict[str, str] = {}
        self.by_name: dict[str, list[AsmObject]] = collections.defaultdict(list)
        for obj in objects.values():
            self.by_name[obj.name].append(obj)
        original = module.parse_bin_formatted
        includes = module.get_required_includes

        def parse(*args: Any, **kwargs: Any) -> Any:
            # A nonzero pointer word without relocation metadata must not become
            # NULL merely because assetdis's struct parser cannot resolve it.
            buff, layout, references = args[:3]
            fmt, pointer_offsets = ">", []
            for field in layout:
                if field is None:
                    fmt += "x"
                elif field[0] == "p":
                    pointer_offsets.append(struct.calcsize(fmt))
                    fmt += "xxxx"
                else:
                    fmt += field[0]
            stride = struct.calcsize(fmt)
            if stride:
                for base in range(0, len(buff), stride):
                    for offset in pointer_offsets:
                        position = base + offset
                        if position not in references and any(buff[position:position + 4]):
                            raise ValueError(f"Unresolved numeric pointer at object offset {position:#x}; use relocation-aware assembly")
            res = original(*args, **kwargs)
            kept = []
            for ref in res.referenced_objects:
                if ref.symbol_name == "NULL":
                    continue
                if re.fullmatch(IDENT, ref.symbol_name):
                    self.discovered[ref.symbol_name] = c_type(ref.symbol_type)
                    if ref.symbol_name in self.local:
                        kept.append(ref)
            res.referenced_objects = kept
            return res

        module.parse_bin_formatted = parse
        module.lookup_bins_and_symbols2 = lambda lines, name: self.lookup(name, False)
        module.lookup_bins_and_symbols = lambda lines, name: self.lookup(name, True)
        # Correct forward declarations are reconstructed using the generated types.
        module.get_externs = lambda lines: ""
        module.get_required_includes = lambda source: includes(source, root / "include")

    def target(self, name: str) -> AsmObject:
        if name in self.local:
            return self.local[name]
        if name in self.external_local:
            return self.external_local[name]
        options = self.by_name.get(name, [])
        if len(options) != 1:
            raise ValueError(f"Cannot resolve unique relocation target {name!r}")
        if options[0].symbol.scope == "local":
            raise ValueError(f"Relocation to local {name!r} outside this split requires review")
        return options[0]

    def expression(self, ref: str) -> str:
        if ref.startswith(".rel "):
            name, label = [v.strip() for v in ref[5:].split(",", 1)]
            target = self.target(name)
            if target.error:
                raise ValueError(f"Relocation target {name}: {target.error}")
            if label in target.labels:
                offset = target.labels[label]
            else:
                # DTK commonly emits local labels as .L_XXXXXXXX where XXXXXXXX is
                # the absolute section address.  When a large aggregate data object
                # is sliced into per-symbol AsmObjects, an interior relocation label
                # is not always retained in the target object's body even though the
                # address still unambiguously identifies the intended element.
                absolute_label = re.fullmatch(r"\.L_([0-9A-Fa-f]{8})", label)
                if absolute_label is None:
                    raise ValueError(f"Relocation label {label!r} not found in {name}")
                absolute = int(absolute_label.group(1), 16)
                start = target.symbol.address
                end = start + target.symbol.size
                if not start <= absolute < end:
                    raise ValueError(
                        f"Relocation label {label!r} not found in {name}; "
                        f"encoded address {absolute:#x} is outside {start:#x}..{end:#x}"
                    )
                offset = absolute - start
        else:
            match = EXPR.fullmatch(ref)
            if not match:
                raise ValueError(f"Unsupported relocation expression: {ref}")
            name, sign, amount = match.groups()
            offset = number(amount) * (-1 if sign == "-" else 1) if amount else 0
        if offset == 0:
            return name
        kind = c_type(self.types.get(name, self.discovered.get(name, guess_type(name))))
        element = {"Vtx": 16, "Gfx": 8, "u8": 1, "u16": 2, "s16": 2, "u32": 4, "int": 4}.get(kind)
        if element is not None and offset % element == 0:
            return f"&{name}[{offset // element}]"
        return f"((u8*){name} {'+' if offset >= 0 else '-'} {abs(offset)})"

    def lookup(self, name: str, graphics: bool) -> tuple[bytes, Any]:
        if name not in self.local:
            raise ValueError(f"assetdis requested undefined local object {name!r}")
        obj = self.local[name]
        refs = {offset: self.expression(ref) for offset, ref in obj.references.items()}
        return obj.data, list(refs.values()) if graphics else refs


def write_input(path: Path, objects: list[AsmObject]) -> None:
    text = []
    for obj in objects:
        s = obj.symbol
        text.extend([f".balign {s.align}", f"# 0x{s.address:08X} | 0x{s.address:08X}",
                     f".obj {obj.name}, {s.scope}", *obj.body, f".endobj {obj.name}", ""])
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(text), encoding="utf-8")


def make_recipe(source: str, unit: Unit, module: str, local: dict[str, AsmObject]) -> tuple[str, list[str], list[str]]:
    entries, warnings = [], []
    def replace(match: re.Match[str]) -> str:
        previous = source[:match.start()].rstrip().splitlines()[-1]
        declaration = DECL.match(previous)
        if declaration is None or not declaration[4]:
            raise ValueError(f"Unrecognized declaration before {match[0]}")
        kind, name = declaration[2].strip(), declaration[3]
        if name not in local or kind not in {"u8", "u16", "Vtx"}:
            raise ValueError(f"Unsupported asset include: {kind} {name}")
        obj = local[name]
        s = obj.symbol
        base = f"assets/{module}/{unit.file_stem}/{name}"
        selector = f"{s.name}!{s.section}:0x{s.address:08X}" if s.scope == "local" else s.name
        entry = (f"  - symbol: {selector}\n"
                 f"    binary: {base}.bin\n    header: {base}.inc\n")
        entry += {"u8": "    header_type: raw\n", "u16": "    header_type: none\n    custom_type: pal16\n",
                  "Vtx": "    header_type: none\n    custom_type: vtx\n"}[kind]
        entries.append(entry)
        if obj.references:
            warnings.append(f"{unit.file_stem}/{name}: raw included asset contains relocations; C is not ready to mark matching")
        return f'#include "{base}.inc"'
    return ASSET_INCLUDE.sub(replace, source), entries, warnings


def rebuild_declarations(source: str, unit: Unit, definitions: dict[str, tuple[str, bool]],
                         symbols: list[Symbol], hints: dict[str, str], module: Any,
                         reference_names: set[str] | None = None,
                         external_locals: dict[str, Symbol] | None = None,
                         exported_local_keys: set[tuple[str, int]] | None = None,
                         entry_align: int = 1) -> str:
    # Remove only generated header includes; preserve asset initializers.
    body = re.sub(r'^#include "(?!assets/)[^"\n]+"\s*\n', "", source, flags=re.M).lstrip()
    current = {s.name: s for s in unit.symbols}
    first_symbol = min(unit.symbols, key=lambda symbol: symbol.address) if unit.symbols else None
    declarations = {m[3]: m for m in DECL.finditer(body)}
    if declarations.keys() != current.keys():
        raise ValueError("Generated C definitions differ from the split's symbols")
    external_locals = external_locals or {}
    exported_local_keys = exported_local_keys or set()
    # Replace assetdis's alignment guess with the supplied symbol alignment.
    for m in reversed(list(DECL.finditer(body))):
        s = current[m[3]]
        line = re.sub(r"\s*ATTRIBUTE_ALIGN\(\d+\)", "", m[0])
        if s.key in exported_local_keys:
            line = re.sub(r"^static\s+", "", line)
        # Preserve explicit symbol-level 8/32-byte requirements.  Separately, the
        # first definition may need a stronger inferred entry alignment: the gap
        # belongs to the next TU's placement, not to literal zero bytes appended
        # to the previous TU.
        desired_align = s.align if s.align >= 8 else 1
        if first_symbol is not None and s.key == first_symbol.key and entry_align >= 8:
            desired_align = max(desired_align, entry_align)
        if desired_align >= 8:
            line = line[:-1].rstrip() + f" ATTRIBUTE_ALIGN({desired_align}) ="
        body = body[:m.start()] + line + body[m.end():]
    declarations = {m[3]: m for m in DECL.finditer(body)}
    code = LEX.sub(lambda m: " " * len(m[0]), body)
    # Local duplicate names are scoped by unit; external references use globals only.
    global_symbols = {s.name: s for s in symbols if s.scope == "global"}
    tokens: dict[str, int] = {}
    for match in re.finditer(r"\b" + IDENT + r"\b", code):
        tokens.setdefault(match[0], match.start())
    reference_names = reference_names or set()
    all_names = {s.name for s in symbols}
    prelude = []
    for name, pos in sorted(tokens.items()):
        if name in current:
            m = declarations[name]
            if pos >= m.start():
                continue
            kind, array = m[2].strip(), bool(m[4])
            storage = ("static" if current[name].scope == "local" and
                       current[name].key not in exported_local_keys else "extern")
        else:
            s = global_symbols.get(name)
            if s is None:
                if name not in reference_names:
                    continue
                if name in external_locals:
                    s = external_locals[name]
                elif name in all_names:
                    raise ValueError(f"Generated reference to local {name!r} outside this split")
            kind, array = definitions.get(name, (c_type(hints.get(name, guess_type(name))),
                                                 not guess_type(name).startswith(("cKF_Skeleton", "cKF_Animation", "aNPC_Animation"))))
            storage = "extern"
        prelude.append(f"{storage} {kind} {name}{'[]' if array else ''};")
    if prelude:
        body = "\n".join(prelude) + "\n\n" + body
    includes = module.get_required_includes(body)
    return "\n".join(f'#include "{h}"' for h in includes) + "\n\n" + body.rstrip() + "\n"


def unit_info(unit: Unit) -> dict[str, Any]:
    return {"unit": unit.stem, "guessed_stem": unit.file_stem, "owner": unit.owner, "section": unit.section,
            "start": f"0x{unit.start:08X}", "end": f"0x{unit.end:08X}",
            "symbols": len(unit.symbols), "first_symbol": unit.symbols[0].name if unit.symbols else None}


def parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--module", required=True, choices=MODULES)
    p.add_argument("-v", "--version", choices=VERSIONS, default=VERSIONS[0])
    p.add_argument("--splits", type=Path, help="Default: config/VERSION/MODULE/splits.txt")
    p.add_argument("--symbols", type=Path, help="Default: config/VERSION/MODULE/symbols.txt")
    p.add_argument("--asm", type=Path, help="One assembly file or directory; default build/VERSION/MODULE/asm")
    p.add_argument("--assetdis", type=Path, help="Updated assetdis.py; default tools/converters/assetdis.py or sibling")
    p.add_argument("--out", type=Path, help="New staging/work directory; default out/assetdis/VERSION/MODULE")
    p.add_argument("--src-dir", type=Path, help="Install successful TUs under src/DIR and update splits.txt/configure.py (example: data/always)")
    p.add_argument("--rerun-promoted", action="store_true", help="Regenerate existing .c split owners strictly under --src-dir, overwriting those sources in place without changing splits.txt/configure.py")
    p.add_argument("--configure", type=Path, help="configure.py to update when --src-dir is used; default project-root/configure.py")
    p.add_argument("--config-yml", type=Path, help="Revision config.yml to update when --src-dir is used; default config/VERSION/config.yml")
    p.add_argument("--sync-project", action="store_true", help="Backfill config.yml from already-promoted TUs under --src-dir; use --run to write")
    p.add_argument("--repair-splits", action="store_true", help="Repair dataobject.obj link-order cycles by removing empty ranges and giving each remaining raw range a unique .obj owner; use --run to write")
    p.add_argument("--repair-alignments", action="store_true", help="Normalize generated symbol alignments (preserve 8/32-byte requirements) and restore inferred 32-byte TU-entry alignment in already-promoted TUs under --src-dir; use --run to write")
    p.add_argument("--overwrite-source", action="store_true", help="Allow --src-dir to replace an existing, different source file")
    p.add_argument("--section", action="append", choices=(".data", ".rodata", ".sdata", ".sdata2"), help="Repeat to select; default .data. Code/BSS are never assets.")
    p.add_argument("--unit", action="append", default=[], metavar="GLOB", help="Select original split owners; default all except executor/fakemain")
    p.add_argument("--only", default="*", metavar="GLOB", help="Match guessed filename, address-based unit ID, or any contained symbol")
    p.add_argument("--address-names", action="store_true", help="Use legacy data_<address>.c names instead of guessing from contained symbols")
    p.add_argument("--limit", type=int, help="Process only the first N selected nonempty units")
    p.add_argument("-t", "--types", action="append", default=[], metavar="TYPE,NAME", help="Pass assetdis type overrides")
    p.add_argument("--run", action="store_true", help="Stage conversion; without this flag only preview metadata")
    return p


def main(argv: list[str] | None = None) -> int:
    p = parser()
    args = p.parse_args(argv)
    root = Path.cwd().resolve()
    try:
        project_src_dir = normalize_src_dir(args.src_dir, root) if args.src_dir is not None else None
        configure_path = (args.configure or root / "configure.py").resolve()
        config_yml_path = (args.config_yml or root / "config" / args.version / "config.yml").resolve()
        if project_src_dir is not None and not configure_path.is_file():
            raise ValueError(f"configure.py not found: {configure_path}")
        if project_src_dir is not None and not config_yml_path.is_file():
            raise ValueError(f"config.yml not found: {config_yml_path}")
        if args.rerun_promoted and project_src_dir is None:
            raise ValueError("--rerun-promoted requires --src-dir")
        if args.rerun_promoted and args.address_names:
            raise ValueError("--rerun-promoted cannot use --address-names; existing split owner names are authoritative")
        config = root / "config" / args.version / args.module
        splits_path = (args.splits or config / "splits.txt").resolve()
        symbols_path = (args.symbols or config / "symbols.txt").resolve()
        asm_path = (args.asm or root / "build" / args.version / args.module / "asm").resolve()
        sections = set(args.section or [".data"])
        symbols = read_symbols(symbols_path, sections)
        if args.repair_alignments:
            if project_src_dir is None:
                raise ValueError("--repair-alignments requires --src-dir")
            repair = repair_existing_project_alignments(
                root, splits_path, project_src_dir, symbols, sections, args.run)
            action = "Updated" if args.run else "Would update"
            print(f"{args.module} / {args.version}")
            print(f"{action} {len(repair['files'])} promoted source TUs under src/{project_src_dir.as_posix()}")
            print(f"  removed redundant ATTRIBUTE_ALIGN(4): {repair['removed_low']}")
            print(f"  restored/changed ATTRIBUTE_ALIGN(8+): {repair['restored_high']}")
            print(f"  inferred TU-entry ATTRIBUTE_ALIGN(32+): {repair['entry_promoted']}")
            if repair["files"]:
                for owner in repair["files"][:20]:
                    print(f"  {owner}")
                if len(repair["files"]) > 20:
                    print(f"  ... and {len(repair['files']) - 20} more")
            else:
                print("Generated source alignments are already normalized")
            if not args.run and repair["files"]:
                print("Preview only; add --run to write the repair")
            return 0
        if args.repair_splits:
            original = splits_path.read_text(encoding="utf-8-sig")
            repaired, repair = normalize_dataobject_splits_text(original, sections)
            action = "Updated" if args.run else "Would update"
            print(f"{args.module} / {args.version}")
            print(f"{action} {splits_path}")
            print(f"Removed {repair['removed_empty']} zero-length dataobject.obj ranges "
                  f"({repair['removed_empty_by_section']})")
            print(f"Moved {len(repair['split_nonempty'])} nonempty raw ranges to unique synthetic .obj owners")
            for item in repair["split_nonempty"][:20]:
                print(f"  {item['section']}:{item['start']}..{item['end']} -> {item['owner']}")
            if len(repair["split_nonempty"]) > 20:
                print(f"  ... and {len(repair['split_nonempty']) - 20} more")
            if args.run and repaired != original:
                atomic_write_text(splits_path, repaired)
            elif repaired == original:
                print("splits.txt is already normalized")
            else:
                print("Preview only; add --run to write the repair")
            return 0
        if args.sync_project:
            if project_src_dir is None:
                raise ValueError("--sync-project requires --src-dir")
            changed, discovered = sync_existing_project_config(
                root, splits_path, config_yml_path, args.module, project_src_dir, symbols, sections, args.run)
            action = "Updated" if args.run else "Would update"
            print(f"{args.module} / {args.version}")
            print(f"Found {discovered} asset include entries in already-promoted TUs under src/{project_src_dir.as_posix()}")
            print(f"{action} {len(changed)} config.yml extract entries")
            if changed:
                for symbol in changed[:20]:
                    print(f"  {symbol}")
                if len(changed) > 20:
                    print(f"  ... and {len(changed) - 20} more")
            elif discovered:
                print("config.yml is already synchronized for those TUs")
            return 0
        alignment_units, _ = read_splits(splits_path, sections, ["*"])
        assign_symbols(alignment_units, symbols)
        entry_alignments = infer_tu_entry_alignments(alignment_units)
        if args.rerun_promoted:
            units, stats = read_promoted_splits(splits_path, sections, project_src_dir, args.unit)
            assign_symbols(units, symbols)
            # Existing split paths are authoritative in rerun mode.  Do not feed
            # these TUs back through filename inference or they could be renamed.
            for unit in units:
                unit.guessed_stem = Path(unit.owner).stem
        else:
            units, stats = read_splits(splits_path, sections, args.unit)
            assign_symbols(units, symbols)
            assign_unit_names(units, use_guesses=not args.address_names)
        unnamed = [u for u in units if not u.symbols]
        selected = [u for u in units if u.symbols and (fnmatch.fnmatchcase(u.file_stem, args.only) or
                    fnmatch.fnmatchcase(u.stem, args.only) or
                    any(fnmatch.fnmatchcase(s.name, args.only) for s in u.symbols))]
        if args.limit is not None:
            if args.limit < 1:
                raise ValueError("--limit must be positive")
            selected = selected[:args.limit]
        if not selected:
            raise ValueError("No named asset units selected")
        overrides = {}
        for item in args.types:
            pieces = item.split(",")
            if len(pieces) != 2 or not all(pieces) or not re.fullmatch(IDENT, pieces[1]):
                raise ValueError("-t expects TYPE,NAME")
            overrides[pieces[1]] = pieces[0]
        print(f"{args.module} / {args.version}")
        print(f"{stats.get('selected_range_lines', 0)} selected range lines; "
              f"{stats.get('empty_ranges', 0)} empty; {stats.get('duplicate_ranges', 0)} duplicates; "
              f"{len(unnamed)} unnamed nonempty ranges")
        print(f"Ignoring .text ({stats.get('ignored_text_lines', 0)} lines). "
              f"Selected {len(selected)} conversion units / {sum(len(u.symbols) for u in selected)} symbols.")
        for unit in selected[:5]:
            print(f"  {unit.section}:0x{unit.start:08X}..0x{unit.end:08X} -> {unit.file_stem}.c ({unit.symbols[0].name}, {len(unit.symbols)} symbols)")
        if project_src_dir is not None:
            display_src = project_src_dir.as_posix() if str(project_src_dir) != "." else ""
            if args.rerun_promoted:
                print(f"Rerun scope: existing .c split owners under src/{display_src}")
                print("Existing split/configure ownership will be preserved")
            else:
                print(f"Project TU directory: src/{display_src}")
                print(f"Project metadata: {splits_path} + {configure_path} + {config_yml_path}")
        if not args.run:
            print(f"Assembly input: {asm_path}")
            print("Preview only; no files written and assembly not validated. Add --run to convert.")
            return 0
        if args.out is not None:
            out = args.out.resolve()
        elif project_src_dir is not None:
            # Project-integrating runs are commonly done one TU at a time. Give each
            # run its own work directory so the same command can advance to the next
            # raw split without manually deleting the previous report/logs.
            tag = selected[0].stem if len(selected) == 1 else f"{selected[0].stem}_{len(selected)}"
            out = (root / "out" / "assetdis" / args.version / args.module / tag).resolve()
        else:
            out = (root / "out" / "assetdis" / args.version / args.module).resolve()
        if out.exists() and (not out.is_dir() or any(out.iterdir())):
            raise ValueError(f"Refusing nonempty output directory: {out}; use a new --out")
        objects, warnings = index_assembly(asm_path, symbols)
        assetdis_path = args.assetdis
        if assetdis_path is None:
            choices = [root / "tools/converters/assetdis.py", Path(__file__).resolve().with_name("assetdis.py")]
            assetdis_path = next((path for path in choices if path.is_file()), choices[0])
        mod = load_assetdis(assetdis_path.resolve())
        adapter = Adapter(mod, objects, root, overrides)
        report: dict[str, Any] = {"module": args.module, "version": args.version,
            "splits": str(splits_path), "symbols": str(symbols_path), "assembly": str(asm_path), "config_yml": str(config_yml_path),
            "summary": stats, "selected_units": len(selected), "selected_symbols": sum(len(u.symbols) for u in selected),
            "unnamed_ranges": [unit_info(u) for u in unnamed], "converted": [], "failed": [], "warnings": warnings,
            "project_updates": None,
            "note": "Conversion is not proof of matching. Unnamed ranges are not converted; .bin/.inc extraction still uses the generated recipe."}
        out.mkdir(parents=True, exist_ok=True)
        (out / "logs").mkdir(exist_ok=True)
        generated: list[tuple[Unit, Path, str, list[str], dict[str, str], set[str], dict[str, Symbol]]] = []
        definitions: dict[str, tuple[str, bool]] = {}
        all_hints: dict[str, str] = {}
        with contextlib.ExitStack() as stack:
            stack.callback(os.chdir, root)
            os.chdir(out)  # assetdis expects a relative src/ destination
            for index, unit in enumerate(selected, 1):
                log = out / "logs" / f"{unit.file_stem}.log"
                dest = Path("src/data") / args.module / f"{unit.file_stem}.c"
                with log.open("w", encoding="utf-8") as stream:
                    try:
                        with contextlib.redirect_stdout(stream), contextlib.redirect_stderr(stream):
                            local = []
                            for s in unit.symbols:
                                obj = objects.get(s.key)
                                if obj is None:
                                    raise ValueError(f"Missing assembly object {s.name} at {s.section}:{s.address:#x}")
                                if obj.error:
                                    raise ValueError(f"{obj.path}:{obj.line}: {obj.name}: {obj.error}")
                                local.append(obj)
                            if len({o.name for o in local}) != len(local):
                                raise ValueError("Duplicate local names within one range; refine the splits")
                            adapter.local = {o.name: o for o in local}
                            external_locals = resolve_external_local_references(unit, local, symbols)
                            adapter.external_local = {}
                            for name, target_symbol in external_locals.items():
                                target_obj = objects.get(target_symbol.key)
                                if target_obj is None:
                                    raise ValueError(
                                        f"Missing assembly object for external local {name} at "
                                        f"{target_symbol.section}:{target_symbol.address:#x}"
                                    )
                                if target_obj.error:
                                    raise ValueError(
                                        f"{target_obj.path}:{target_obj.line}: {target_obj.name}: {target_obj.error}"
                                    )
                                adapter.external_local[name] = target_obj
                            adapter.discovered = {}
                            sliced = out / "asm" / f"{unit.stem}.s"
                            write_input(sliced, local)
                            kwargs = {"should_extract_symbols": False, "should_link": False}
                            if "version" in inspect.signature(mod.convert_source_to_gfx_c_source).parameters:
                                kwargs["version"] = args.version
                            mod.convert_source_to_gfx_c_source(str(sliced), dest.as_posix(), overrides, **kwargs)
                            source = dest.read_text(encoding="utf-8")
                            if "[xxx]" in source:
                                raise ValueError("Unresolved assetdis [xxx] placeholder")
                            if re.search(r"\bARRAY_COUNT\s*\(\s*NULL\s*\)", source):
                                raise ValueError("assetdis emitted ARRAY_COUNT(NULL); this structure needs manual review")
                            source, entries, extra = make_recipe(source, unit, args.module, adapter.local)
                            report["warnings"].extend(extra)
                            reference_names: set[str] = set()
                            for obj in local:
                                for ref in obj.references.values():
                                    name = reference_name(ref)
                                    if name:
                                        reference_names.add(name)
                            known_names = {s.name for s in symbols}
                            for name in sorted(reference_names - known_names):
                                report["warnings"].append(f"{unit.file_stem}/{name}: external to this module; declaration type inferred, not verified against its defining module")
                            for name, target_symbol in sorted(external_locals.items()):
                                report["warnings"].append(
                                    f"{unit.file_stem}/{name}: duplicate/local reference resolved to "
                                    f"{target_symbol.section}:0x{target_symbol.address:08X}; exporting that occurrence to C"
                                )
                            generated.append((unit, dest, source, entries, dict(adapter.discovered),
                                              reference_names, external_locals))
                            for d in DECL.finditer(source):
                                if adapter.local[d[3]].symbol.scope == "global":
                                    definitions[d[3]] = (d[2].strip(), bool(d[4]))
                            all_hints.update({k: v for k, v in adapter.discovered.items() if k not in adapter.local or adapter.local[k].symbol.scope == "global"})
                    except Exception as exc:
                        traceback.print_exc(file=stream)
                        dest.unlink(missing_ok=True)
                        report["failed"].append({**unit_info(unit), "phase": "conversion", "error": str(exc) or type(exc).__name__, "log": f"logs/{unit.file_stem}.log"})
                if index == 1 or index % 100 == 0 or index == len(selected):
                    print(f"{index}/{len(selected)}: {len(generated)} converted so far, {len(report['failed'])} failed", flush=True)
            exported_by_name: dict[str, set[tuple[str, int]]] = collections.defaultdict(set)
            external_target_by_key: dict[tuple[str, int], Symbol] = {}
            for _unit, _dest, source, _entries, _hints, _refs, external_locals in generated:
                for name, symbol in external_locals.items():
                    exported_by_name[name].add(symbol.key)
                    external_target_by_key[symbol.key] = symbol
            conflicts = {name: keys for name, keys in exported_by_name.items() if len(keys) > 1}
            if conflicts and args.rerun_promoted:
                # Reruns regenerate already-promoted sources in place.  A cross-TU
                # local-name collision is a reason to leave the affected existing
                # source alone, not to abort every otherwise-independent rerun.
                conflict_names = set(conflicts)
                kept = []
                for item in generated:
                    unit, dest, source, entries, hints, reference_names, external_locals = item
                    used = sorted(conflict_names.intersection(external_locals))
                    if not used:
                        kept.append(item)
                        continue
                    details = []
                    for name in used:
                        keys = conflicts[name]
                        choices = ", ".join(
                            f"{section}:0x{address:08X}" for section, address in sorted(keys)
                        )
                        details.append(f"{name!r} -> {choices}")
                    message = (
                        "rerun skipped to preserve the existing source: multiple local occurrences "
                        "would require conflicting external C symbols (" + "; ".join(details) + ")"
                    )
                    log = out / "logs" / f"{unit.file_stem}.log"
                    with log.open("a", encoding="utf-8") as stream:
                        print("\n=== rerun external-local conflict ===", file=stream)
                        print(message, file=stream)
                    dest.unlink(missing_ok=True)
                    report["failed"].append({
                        **unit_info(unit),
                        "phase": "external_local_conflict",
                        "error": message,
                        "log": f"logs/{unit.file_stem}.log",
                    })
                generated = kept

                # Rebuild the export set from the TUs that will actually be
                # regenerated.  Donors needed only by skipped TUs must remain
                # static, matching the existing project source behavior.
                exported_by_name = collections.defaultdict(set)
                external_target_by_key = {}
                for _unit, _dest, _source, _entries, _hints, _refs, external_locals in generated:
                    for name, symbol in external_locals.items():
                        exported_by_name[name].add(symbol.key)
                        external_target_by_key[symbol.key] = symbol
                conflicts = {name: keys for name, keys in exported_by_name.items() if len(keys) > 1}

            if conflicts:
                name, keys = next(iter(conflicts.items()))
                choices = ", ".join(f"{section}:0x{address:08X}" for section, address in sorted(keys))
                raise ValueError(
                    f"Multiple local occurrences of {name!r} are referenced across splits: {choices}; "
                    "automatic external-linkage promotion would create duplicate C symbols"
                )
            exported_local_keys = set(external_target_by_key)
            # Definitions initially recorded only globals because we did not yet know
            # which local occurrence would need external linkage. Add the chosen
            # occurrence's exact generated C type now.
            for unit, _dest, source, _entries, _hints, _refs, _external in generated:
                current = {s.name: s for s in unit.symbols}
                for declaration in DECL.finditer(source):
                    symbol = current[declaration[3]]
                    if symbol.key in exported_local_keys:
                        definitions[declaration[3]] = (declaration[2].strip(), bool(declaration[4]))
            recipe = []
            successful_local_exports: dict[tuple[str, int], Symbol] = {}
            for unit, dest, source, entries, hints, reference_names, external_locals in generated:
                try:
                    source = rebuild_declarations(
                        source, unit, definitions, symbols, {**all_hints, **hints, **overrides}, mod,
                        reference_names, external_locals, exported_local_keys,
                        entry_alignments.get(unit_key(unit), 1))
                    dest.write_text(source, encoding="utf-8")
                    recipe.extend(entries)
                    report["converted"].append({**unit_info(unit), "source": dest.as_posix(), "asset_includes": len(entries)})
                    for symbol in external_locals.values():
                        successful_local_exports[symbol.key] = symbol
                except Exception as exc:
                    log = out / "logs" / f"{unit.file_stem}.log"
                    with log.open("a", encoding="utf-8") as stream:
                        print("\n=== declaration rebuild failure ===", file=stream)
                        traceback.print_exc(file=stream)
                    dest.unlink(missing_ok=True)
                    report["failed"].append({**unit_info(unit), "phase": "declaration_rebuild", "error": str(exc) or type(exc).__name__, "log": f"logs/{unit.file_stem}.log"})
            if project_src_dir is not None and report["converted"]:
                converted_lookup = {item["unit"] for item in report["converted"]}
                installable = [(unit, dest, dest.read_text(encoding="utf-8"), entries)
                               for unit, dest, _source, entries, _hints, _refs, _external in generated
                               if unit.stem in converted_lookup and dest.exists()]
                if args.rerun_promoted:
                    report["project_updates"] = install_rerun_project_tus(
                        root, config_yml_path, args.module, project_src_dir, installable)
                    by_unit = {unit.stem: unit.owner for unit, _dest, _source, _entries in installable}
                else:
                    report["project_updates"] = install_project_tus(
                        root, splits_path, configure_path, config_yml_path, args.module, project_src_dir, installable,
                        symbols, sections, overwrite_source=args.overwrite_source,
                        local_exports=list(successful_local_exports.values()))
                    by_unit = {unit.stem: (project_src_dir / f"{unit.file_stem}.c").as_posix()
                               for unit, _dest, _source, _entries in installable}
                for item in report["converted"]:
                    if item["unit"] in by_unit:
                        item["project_source"] = f"src/{by_unit[item['unit']]}"
            header = f"# Merge this extract list into the {args.module} module for {args.version}.\n# Do not append it to the end of the project's YAML file.\n"
            (out / "extract.fragment.yml").write_text(header + ("extract:\n" + "\n".join(recipe) if recipe else "extract: []\n"), encoding="utf-8")
            (out / "report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        print(f"Done: {len(report['converted'])} converted, {len(report['failed'])} failed. Work output: {out}")
        if report["failed"]:
            print("Failed TUs:")
            for item in report["failed"]:
                phase = item.get("phase", "unknown")
                name = f"{item['guessed_stem']}.c"
                print(f"  {name}  {item['start']}..{item['end']}  [{phase}] {item['error']}")
                if item.get("log"):
                    print(f"    log: {out / item['log']}")
            print(f"Failure report: {out / 'report.json'}")
        if project_src_dir is not None and report.get("project_updates"):
            updates = report["project_updates"]
            repair = updates.get("raw_split_repair", {})
            print(f"Project updated: {len(updates['sources'])} source TUs, {len(updates['splits'])} split ranges, "
                  f"{len(updates['configure'])} configure.py entries, {len(updates['extract'])} config.yml extract entries, "
                  f"{len(updates.get('local_exports', []))} address-qualified local exports, "
                  f"{repair.get('removed_empty', 0)} empty raw ranges removed, "
                  f"{len(repair.get('split_nonempty', []))} raw ranges given unique owners")
        else:
            print("Project files unchanged. See report.json and extract.fragment.yml.")
        return 1 if report["failed"] else 0
    except (OSError, ValueError, ImportError, SyntaxError) as exc:
        p.error(str(exc))
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
