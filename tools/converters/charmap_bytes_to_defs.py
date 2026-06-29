import argparse
import pathlib
import re
import sys
from dataclasses import dataclass


DEFAULT_TEST_SOURCE = "src/game/m_mark_room_ovl.c"
DEFAULT_TEST_ARRAY = "mMkRm_series_name"
DEFAULT_CHARMAP = "include/charmap.h"


@dataclass(frozen=True)
class CharPPEntry:
    name: str
    text: str


def load_char_pp_map(charmap_path: pathlib.Path) -> dict[int, CharPPEntry]:
    value_to_entry: dict[int, CharPPEntry] = {}
    pattern = re.compile(r"^\s*#define\s+(CHAR_PP_\d{3})\s+(\d+)\b(?:\s*//\s*(.*))?")

    for line in charmap_path.read_text(encoding="utf-8").splitlines():
        match = pattern.match(line)
        if not match:
            continue
        name, value, text = match.groups()
        value_to_entry[int(value)] = CharPPEntry(name, text or name)

    if not value_to_entry:
        raise ValueError(f"No CHAR_PP_* defines found in {charmap_path}")

    return value_to_entry


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
    symbol_pattern = re.compile(r"CHAR_PP_(\d{3})$")

    for token in row_text.split(","):
        token = token.strip()
        if not token:
            continue
        match = symbol_pattern.match(token)
        if match:
            values.append(int(match.group(1), 10))
        else:
            values.append(int(token, 0))
    return values


def symbols_for_values(values: list[int], char_pp_map: dict[int, CharPPEntry]) -> list[str]:
    return [char_pp_map[value].name if value in char_pp_map else f"0x{value:02X}" for value in values]


def convert_row(values: list[int], char_pp_map: dict[int, CharPPEntry]) -> str:
    symbols = symbols_for_values(values, char_pp_map)
    return "{ " + ", ".join(symbols) + " }"


def text_for_value(value: int, char_pp_map: dict[int, CharPPEntry]) -> str:
    text = char_pp_map[value].text if value in char_pp_map else f"0x{value:02X}"
    if text == "(space)":
        return " "
    if text == "\\n":
        return "\\n"
    if len(text) == 1:
        return text
    return f"<{text}>"


def decode_text(values: list[int], char_pp_map: dict[int, CharPPEntry]) -> str:
    return "".join(text_for_value(value, char_pp_map) for value in values)


def convert_1d_initializer(initializer_text: str, char_pp_map: dict[int, CharPPEntry]) -> str:
    inner = initializer_text.strip()
    if not (inner.startswith("{") and inner.endswith("}")):
        raise ValueError("Expected brace-wrapped initializer")

    values = parse_byte_tokens(inner[1:-1])
    symbols = symbols_for_values(values, char_pp_map)
    single_line = "{ " + ", ".join(symbols) + " }"
    if len(single_line) <= 120:
        return single_line

    rows = [", ".join(symbols[i : i + 8]) for i in range(0, len(symbols), 8)]
    return "{\n    " + ",\n    ".join(rows) + "\n}"


def convert_array(source_text: str, array_name: str, char_pp_map: dict[int, CharPPEntry]) -> str:
    initializer = extract_initializer_block(source_text, array_name)

    try:
        rows = extract_rows(initializer)
    except ValueError:
        return convert_1d_initializer(initializer, char_pp_map) + ";"

    converted_rows = [convert_row(parse_byte_tokens(row), char_pp_map) for row in rows]
    return "{\n    " + ",\n    ".join(converted_rows) + "\n};"


def convert_array_with_text_comment(source_text: str, array_name: str, char_pp_map: dict[int, CharPPEntry]) -> str:
    initializer = extract_initializer_block(source_text, array_name)
    values = parse_byte_tokens(initializer.strip()[1:-1])
    return f"// JP: {decode_text(values, char_pp_map)}\n{convert_array(source_text, array_name, char_pp_map)}"


def find_u8_arrays(source_text: str) -> list[tuple[str, int, int, str]]:
    arrays: list[tuple[str, int, int, str]] = []
    pattern = re.compile(
        r"(?m)^(?P<decl>[ \t]*(?:static[ \t]+)?(?:const[ \t]+)?u8[ \t]+(?P<name>\w+)[ \t]*\[[^\]]*\][ \t]*=[ \t]*)"
    )

    for match in pattern.finditer(source_text):
        initializer = extract_initializer_block(source_text[match.start() :], match.group("name"))
        initializer_start = source_text.find("{", match.end() - 1)
        initializer_end = initializer_start + len(initializer)
        arrays.append((match.group("name"), match.start(), initializer_end, source_text[match.start() : initializer_end]))

    return arrays


def convert_u8_array_declaration(
    declaration_text: str, array_name: str, char_pp_map: dict[int, CharPPEntry]
) -> str:
    initializer = extract_initializer_block(declaration_text, array_name)
    values = parse_byte_tokens(initializer.strip()[1:-1])
    converted = convert_array(declaration_text, array_name, char_pp_map)
    converted_initializer = converted[:-1] if converted.endswith(";") else converted
    declaration_prefix = declaration_text[: declaration_text.find("{")]
    return f"// JP: {decode_text(values, char_pp_map)}\n{declaration_prefix}{converted_initializer}"


def convert_all_u8_arrays(source_text: str, char_pp_map: dict[int, CharPPEntry]) -> str:
    converted_text = source_text

    for array_name, start, end, declaration_text in reversed(find_u8_arrays(source_text)):
        preceding_end = start
        while preceding_end > 0:
            preceding_line_start = source_text.rfind("\n", 0, preceding_end - 1) + 1
            preceding_line = source_text[preceding_line_start:preceding_end].strip()
            if preceding_line:
                if preceding_line.startswith("// JP: "):
                    start = preceding_line_start
                break
            preceding_end = preceding_line_start
        converted_text = (
            converted_text[:start]
            + convert_u8_array_declaration(declaration_text, array_name, char_pp_map)
            + converted_text[end:]
        )

    return converted_text


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
    parser.add_argument(
        "--text-comment",
        action="store_true",
        help="Print the decoded JP text as a comment before the converted array.",
    )
    parser.add_argument(
        "--all-u8-arrays",
        action="store_true",
        help="Convert every u8 array initializer in the source.",
    )
    parser.add_argument(
        "--rewrite",
        action="store_true",
        help="Rewrite the source file in place. Implies --all-u8-arrays.",
    )
    args = parser.parse_args()

    source_path = pathlib.Path(args.source)
    charmap_path = pathlib.Path(args.charmap)

    try:
        source_text = source_path.read_text(encoding="utf-8")
        char_pp_map = load_char_pp_map(charmap_path)
        if args.rewrite:
            converted_text = convert_all_u8_arrays(source_text, char_pp_map)
            source_path.write_text(converted_text, encoding="utf-8")
        elif args.all_u8_arrays:
            print(convert_all_u8_arrays(source_text, char_pp_map), end="")
        elif args.text_comment:
            print(convert_array_with_text_comment(source_text, args.array, char_pp_map))
        else:
            print(convert_array(source_text, args.array, char_pp_map))
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
