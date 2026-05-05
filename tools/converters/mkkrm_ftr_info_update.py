import argparse
import pathlib
import re
import sys


SERIES_NAMES = [
    "mMkRm_SERIES_EXOTIC",
    "mMkRm_SERIES_LOVELY",
    "mMkRm_SERIES_CLASSIC",
    "mMkRm_SERIES_RANCH",
    "mMkRm_SERIES_CABANA",
    "mMkRm_SERIES_BLUE",
    "mMkRm_SERIES_MODERN",
    "mMkRm_SERIES_REGAL",
    "mMkRm_SERIES_GREEN",
    "mMkRm_SERIES_CABIN",
    "mMkRm_SERIES_SPOOKY",
    "mMkRm_SERIES_JINGLE",
    "mMkRm_SERIES_KIDDIE",
    "mMkRm_SERIES_GARDEN",
    "mMkRm_SERIES_ROCKGARDEN",
    "mMkRm_SERIES_JAPANESE",
    "mMkRm_SERIES_CONSTRUCTION",
    "mMkRm_SERIES_SPACE",
    "mMkRm_SERIES_PUBLICBATH",
    "mMkRm_SERIES_SCHOOL",
    "mMkRm_SERIES_CHESS",
    "mMkRm_SERIES_BONSAI",
    "mMkRm_SERIES_WRITING",
    "mMkRm_SERIES_VASE",
    "mMkRm_SERIES_VENDING",
    "mMkRm_SERIES_NINTENDO",
    "mMkRm_SERIES_DARUMA",
    "mMkRm_SERIES_CACTUS",
    "mMkRm_SERIES_BEAR",
    "mMkRm_SERIES_FIGURE",
    "mMkRm_SERIES_TOTEMPOLE",
    "mMkRm_SERIES_GUITAR",
    "mMkRm_SERIES_DRUM",
    "mMkRm_SERIES_STRINGS",
    "mMkRm_SERIES_OFFICE",
    "mMkRm_SERIES_TRICERA",
    "mMkRm_SERIES_TREX",
    "mMkRm_SERIES_BRONT",
    "mMkRm_SERIES_STEGO",
    "mMkRm_SERIES_PTERA",
    "mMkRm_SERIES_PLESIO",
    "mMkRm_SERIES_MAMMOTH",
    "mMkRm_SERIES_ROBOT",
    "mMkRm_SERIES_APPLE",
    "mMkRm_SERIES_CITRUS",
    "mMkRm_SERIES_MELON",
    "mMkRm_SERIES_PEAR",
    "mMkRm_SERIES_LUCKY",
    "mMkRm_SERIES_PINE",
    "mMkRm_SERIES_FROGGY",
    "mMkRm_SERIES_IRIS",
    "mMkRm_SERIES_TULIP",
    "mMkRm_SERIES_DAFFODIL",
    "mMkRm_SERIES_OTHER",
    "mMkRm_SERIES_SNOWMAN",
    "mMkRm_SERIES_WESTERN",
    "mMkRm_SERIES_BACKYARD",
    "mMkRm_SERIES_HARVEST",
    "mMkRm_SERIES_BOXING",
    "mMkRm_SERIES_MARIO",
]

NECESSITY_NAMES = [
    "mMkRm_NECESSITY_CHAIR",
    "mMkRm_NECESSITY_DRESSER",
    "mMkRm_NECESSITY_WARDROBE",
    "mMkRm_NECESSITY_TABLE",
    "mMkRm_NECESSITY_BED",
    "mMkRm_NOT_NECESSITY",
]

FACE_NAMES = ["mMkRm_FACE_TYPE_NO_FACE", "mMkRm_FACE_TYPE_HAS_FACE"]
LUCK_NAMES = ["mMkRm_LUCK_TYPE_NOT_LUCKY", "mMkRm_LUCK_TYPE_LUCKY"]
SURFACE_NAMES = ["mMkRm_SURFACE_TYPE_NONE", "mMkRm_SURFACE_TYPE_SURFACE", "mMkRm_SURFACE_TYPE_PLACEABLE"]

BIRTH_NAMES = [
    "mRmTp_BIRTH_TYPE_GRP_A",
    "mRmTp_BIRTH_TYPE_GRP_B",
    "mRmTp_BIRTH_TYPE_GRP_C",
    "mRmTp_BIRTH_TYPE_EVENT",
    "mRmTp_BIRTH_TYPE_BIRTHDAY",
    "mRmTp_BIRTH_TYPE_HALLOWEEN",
    "mRmTp_BIRTH_TYPE_HANIWA",
    "mRmTp_BIRTH_TYPE_LOTTERY",
    "mRmTp_BIRTH_TYPE_FTR_CLOTH",
    "mRmTp_BIRTH_TYPE_FTR_UMBRELLA",
    "mRmTp_BIRTH_TYPE_FTR_INSECT",
    "mRmTp_BIRTH_TYPE_FTR_FISH",
    "mRmTp_BIRTH_TYPE_SINGLE_FOSSIL",
    "mRmTp_BIRTH_TYPE_MULTI_FOSSIL",
    "mRmTp_BIRTH_TYPE_XMAS",
    "mRmTp_BIRTH_TYPE_SANTA",
    "mRmTp_BIRTH_TYPE_UNOBTAINABLE",
    "mRmTp_BIRTH_TYPE_SNOWMAN",
    "mRmTp_BIRTH_TYPE_HALLOWEEN_TRICK",
    "mRmTp_BIRTH_TYPE_POST_OFFICE",
    "mRmTp_BIRTH_TYPE_MARK_ROOM",
    "mRmTp_BIRTH_TYPE_SONCHO",
    "mRmTp_BIRTH_TYPE_JONASON",
    "mRmTp_BIRTH_TYPE_UNUSED_23",
    "mRmTp_BIRTH_TYPE_FAMICOM_EREADER",
    "mRmTp_BIRTH_TYPE_ISLAND",
    "mRmTp_BIRTH_TYPE_FAMICOM_ISLAND",
    "mRmTp_BIRTH_TYPE_MY_ORIGINAL",
    "mRmTp_BIRTH_TYPE_FAMICOM_CODE",
    "mRmTp_BIRTH_TYPE_MUSEUM",
    "mRmTp_BIRTH_TYPE_SONCHO_LIGHTHOUSE_QUEST",
    "mRmTp_BIRTH_TYPE_FTR_DIARY",
    "mRmTp_BIRTH_TYPE_GROUNDHOG",
    "mRmTp_BIRTH_TYPE_KAMAKURA",
    "mRmTp_BIRTH_TYPE_NINTENDO_CODE",
    "mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL",
    "mRmTp_BIRTH_TYPE_UNUSED_36",
    "mRmTp_BIRTH_TYPE_SUMMER_CAMPER",
    "mRmTp_BIRTH_TYPE_GBA_MINIGAME",
    "mRmTp_BIRTH_TYPE_OLD_NPC_CODE",
]


ENTRY_RE = re.compile(
    r"\{\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*"
    r"(0x[0-9A-Fa-f]+|\d+)\s*,\s*(0x[0-9A-Fa-f]+|\d+)\s*,\s*(0x[0-9A-Fa-f]+|\d+)\s*\}"
)


def parse_int(token: str) -> int:
    return int(token, 0)


def enum_or_num(value: int, names: list[str]) -> str:
    if 0 <= value < len(names):
        return names[value]
    return str(value)


def convert_entry(values: tuple[int, int, int, int, int, int]) -> str:
    series, group_idx, has_face, is_lucky, birth_type, surface_type = values
    return (
        "{ "
        + ", ".join(
            [
                enum_or_num(series, SERIES_NAMES),
                enum_or_num(group_idx, NECESSITY_NAMES),
                enum_or_num(has_face, FACE_NAMES),
                enum_or_num(is_lucky, LUCK_NAMES),
                enum_or_num(birth_type, BIRTH_NAMES),
                enum_or_num(surface_type, SURFACE_NAMES),
            ]
        )
        + " }"
    )


def extract_numeric_entries(text: str) -> list[tuple[int, int, int, int, int, int]]:
    out: list[tuple[int, int, int, int, int, int]] = []
    for m in ENTRY_RE.finditer(text):
        out.append(tuple(parse_int(m.group(i)) for i in range(1, 7)))
    return out


def update_array_in_source(source_text: str, new_rows: list[str]) -> str:
    start_marker = "static mMkRm_ftr_info_c mMkRm_ftr_info[FTR_NUM] = {"
    start = source_text.find(start_marker)
    if start == -1:
        raise ValueError("Could not find mMkRm_ftr_info array declaration")

    body_start = source_text.find("{", start) + 1
    i = body_start
    depth = 1
    while i < len(source_text):
        if source_text[i] == "{":
            depth += 1
        elif source_text[i] == "}":
            depth -= 1
            if depth == 0:
                body_end = i
                break
        i += 1
    else:
        raise ValueError("Could not find end of mMkRm_ftr_info initializer")

    old_body = source_text[body_start:body_end]
    old_lines = [line for line in old_body.splitlines() if line.strip()]
    old_comments: list[str] = []
    for line in old_lines:
        comment = ""
        if "//" in line:
            comment = "//" + line.split("//", 1)[1]
        old_comments.append(comment)

    if old_comments and len(old_comments) != len(new_rows):
        raise ValueError(
            f"Entry count mismatch: source has {len(old_comments)} rows, new data has {len(new_rows)} rows"
        )

    formatted_rows: list[str] = []
    for idx, row in enumerate(new_rows):
        comment = old_comments[idx] if idx < len(old_comments) else ""
        if comment:
            formatted_rows.append(f"    {row}, {comment}")
        else:
            formatted_rows.append(f"    {row},")

    new_body = "\n" + "\n".join(formatted_rows) + "\n"
    return source_text[:body_start] + new_body + source_text[body_end:]


def unpack_be_u32_entry(word: int) -> tuple[int, int, int, int, int, int]:
    # Big-endian bitfield layout for:
    # u8 series:6; u16 group_idx:10; u8 has_face:1; u8 is_lucky:1; u8 birth_type:6; u8 surface_type:2;
    series = (word >> 26) & 0x3F
    group_idx = (word >> 16) & 0x3FF
    has_face = (word >> 15) & 0x1
    is_lucky = (word >> 14) & 0x1
    birth_type = (word >> 8) & 0x3F
    surface_type = (word >> 6) & 0x3
    return series, group_idx, has_face, is_lucky, birth_type, surface_type


def main() -> int:
    parser = argparse.ArgumentParser(description="Convert numeric mMkRm_ftr_info rows to enum names and update source.")
    parser.add_argument("input", help="Path to file containing numeric rows like {0x0A, 0x0002, ...}")
    parser.add_argument(
        "--source",
        default="src/game/m_mark_room_ovl_data.c_inc",
        help="Target source file containing mMkRm_ftr_info",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Print converted rows only; do not update source file",
    )
    args = parser.parse_args()

    input_path = pathlib.Path(args.input)
    source_path = pathlib.Path(args.source)

    numeric_text = input_path.read_text(encoding="utf-8")
    entries = extract_numeric_entries(numeric_text)
    if not entries:
        raise ValueError("No 6-value entries found in input text")

    converted_rows = [convert_entry(entry) for entry in entries]

    if args.dry_run:
        print("\n".join(converted_rows))
        return 0

    source_text = source_path.read_text(encoding="utf-8")
    updated = update_array_in_source(source_text, converted_rows)
    source_path.write_text(updated, encoding="utf-8")
    print(f"Updated {source_path} with {len(converted_rows)} entries.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
