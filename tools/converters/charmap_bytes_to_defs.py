import argparse
import pathlib
import re
import sys


DEFAULT_TEST_SOURCE = "src/game/m_mark_room_ovl.c"
DEFAULT_TEST_ARRAY = "mMkRm_series_name"
DEFAULT_CHARMAP = "include/charmap.h"


def load_char_pp_map(charmap_path: pathlib.Path) -> dict[int, str]:
    value_to_name: dict[int, str] = {}
    pattern = re.compile(r"^\s*#define\s+(CHAR_PP_\d{3})\s+(\d+)\b")

    for line in charmap_path.read_text(encoding="utf-8").splitlines():
        match = pattern.match(line)
        if not match:
            continue
        name, value = match.groups()
        value_to_name[int(value)] = name

    if not value_to_name:
        raise ValueError(f"No CHAR_PP_* defines found in {charmap_path}")

    return value_to_name


def extract_initializer_block(source_text: str, array_name: str) -> str:
    declaration_start = source_text.find(array_name)
    if declaration_start == -1:
        raise ValueError(f"Array '{array_name}' not found in source text")

    equal_index = source_text.find("=", declaration_start)
    if equal_index == -1:
        raise ValueError(f"Could not find '=' for array '{array_name}'")

    brace_start = source_text.find("{", equal_index)
    if brace_start == -1:
        raise ValueError(f"Could not find initializer for array '{array_name}'")

    depth = 0
    for i in range(brace_start, len(source_text)):
        ch = source_text[i]
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                return source_text[brace_start : i + 1]

    raise ValueError(f"Unterminated initializer for array '{array_name}'")


def extract_rows(initializer_text: str) -> list[str]:
    rows: list[str] = []
    depth = 0
    row_start = -1

    for i, ch in enumerate(initializer_text):
        if ch == "{":
            depth += 1
            if depth == 2:
                row_start = i + 1
        elif ch == "}":
            if depth == 2 and row_start != -1:
                rows.append(initializer_text[row_start:i])
                row_start = -1
            depth -= 1

    if not rows:
        raise ValueError("No inner rows found; is this a 2D initializer?")

    return rows


def parse_byte_tokens(row_text: str) -> list[int]:
    values: list[int] = []
    for token in row_text.split(","):
        token = token.strip()
        if not token:
            continue
        values.append(int(token, 0))
    return values


def convert_row(values: list[int], char_pp_map: dict[int, str]) -> str:
    symbols = [char_pp_map.get(value, f"0x{value:02X}") for value in values]
    return "{ " + ", ".join(symbols) + " }"


def convert_array(source_text: str, array_name: str, char_pp_map: dict[int, str]) -> str:
    initializer = extract_initializer_block(source_text, array_name)
    rows = extract_rows(initializer)
    converted_rows = [convert_row(parse_byte_tokens(row), char_pp_map) for row in rows]
    return "{\n    " + ",\n    ".join(converted_rows) + "\n};"


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Convert byte-array initializers to CHAR_PP_* symbols.",
    )
    parser.add_argument(
        "source",
        nargs="?",
        default=DEFAULT_TEST_SOURCE,
        help=f"C source path containing the 2D byte array (default: {DEFAULT_TEST_SOURCE})",
    )
    parser.add_argument(
        "--array",
        default=DEFAULT_TEST_ARRAY,
        help=f"Array symbol name to convert (default: {DEFAULT_TEST_ARRAY})",
    )
    parser.add_argument(
        "--charmap",
        default=DEFAULT_CHARMAP,
        help=f"Path to charmap header (default: {DEFAULT_CHARMAP})",
    )
    args = parser.parse_args()

    source_path = pathlib.Path(args.source)
    charmap_path = pathlib.Path(args.charmap)

    try:
        source_text = source_path.read_text(encoding="utf-8")
        char_pp_map = load_char_pp_map(charmap_path)
        print(convert_array(source_text, args.array, char_pp_map))
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
