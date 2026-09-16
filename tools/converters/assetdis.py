import pathlib
import re
from argparse import ArgumentParser
from gfxdis import convert_binary_to_gfx
from dataclasses import dataclass
import struct

ASSET_ALIGN = "ATTRIBUTE_ALIGN(32)"
NO_ALIGN = ""

SUPPORTED_VERSIONS = ("GAEJ01_00", "GAEJ01_01")
DEFAULT_VERSION = "GAEJ01_00"


def dict_enum_from_list(l: list): return {i: x for i, x, in enumerate(l)}


EFFECT_TYPES = dict_enum_from_list([
    "eEC_EFFECT_SHOCK",
    "eEC_EFFECT_DUST",
    "eEC_EFFECT_MUKA",
    "eEC_EFFECT_WARAU",
    "eEC_EFFECT_HA",
    "eEC_EFFECT_SIBUKI",
    "eEC_EFFECT_GIMONHU",
    "eEC_EFFECT_KANTANHU",
    "eEC_EFFECT_ASE",
    "eEC_EFFECT_ASE_CH",
    "eEC_EFFECT_KANGAERU",
    "eEC_EFFECT_OTIKOMI",
    "eEC_EFFECT_BURUBURU",
    "eEC_EFFECT_SIAWASE_HIKARI",
    "eEC_EFFECT_SIAWASE_HANA",
    "eEC_EFFECT_SIAWASE_HANA_CH",
    "eEC_EFFECT_TAKURAMI",
    "eEC_EFFECT_TAKURAMI_KIRA",
    "eEC_EFFECT_KAZE",
    "eEC_EFFECT_KAZE_HAPPA",
    "eEC_EFFECT_LOVELOVE",
    "eEC_EFFECT_LOVELOVE_HEART",
    "eEC_EFFECT_PUN",
    "eEC_EFFECT_PUN_YUGE",
    "eEC_EFFECT_PUN_SEKIMEN",
    "eEC_EFFECT_NAKU",
    "eEC_EFFECT_NAMIDA",
    "eEC_EFFECT_HIRAMEKI_DEN",
    "eEC_EFFECT_HIRAMEKI_HIKARI",
    "eEC_EFFECT_SITUREN",
    "eEC_EFFECT_ASE2",
    "eEC_EFFECT_DASH_ASIMOTO",
    "eEC_EFFECT_KONPU",
    "eEC_EFFECT_LOVELOVE2",
    "eEC_EFFECT_KPUN",
    "eEC_EFFECT_KISHA_KEMURI",
    "eEC_EFFECT_NEBOKE",
    "eEC_EFFECT_NEBOKE_AWA",
    "eEC_EFFECT_HANABI_YANAGI",
    "eEC_EFFECT_HANABI_BOTAN1",
    "eEC_EFFECT_HANABI_BOTAN2",
    "eEC_EFFECT_HANABI_HOSHI",
    "eEC_EFFECT_HANABI_SET",
    "eEC_EFFECT_HANABI_SWITCH",
    "eEC_EFFECT_FOOTPRINT",
    "eEC_EFFECT_TURN_FOOTPRINT",
    "eEC_EFFECT_BUBU",
    "eEC_EFFECT_TURN_ASIMOTO",
    "eEC_EFFECT_STRING",
    "eEC_EFFECT_YUKIHANE",
    "eEC_EFFECT_ANAHIKARI",
    "eEC_EFFECT_BUSH_HAPPA",
    "eEC_EFFECT_BUSH_YUKI",
    "eEC_EFFECT_TUMBLE",
    "eEC_EFFECT_TUMBLE_BODYPRINT",
    "eEC_EFFECT_SLIP",
    "eEC_EFFECT_TUMBLE_DUST",
    "eEC_EFFECT_SWING_NET",
    "eEC_EFFECT_AMI_MIZU",
    "eEC_EFFECT_MIZUTAMA",
    "eEC_EFFECT_YUKIDAMA",
    "eEC_EFFECT_KIKUZU",
    "eEC_EFFECT_SWING_AXE",
    "eEC_EFFECT_STEAM",
    "eEC_EFFECT_NIGHT15_MOON",
    "eEC_EFFECT_NIGHT13_MOON",
    "eEC_EFFECT_NEBOKE_AKUBI",
    "eEC_EFFECT_SLIP_FOOTPRINT",
    "eEC_EFFECT_WALK_ASIMOTO",
    "eEC_EFFECT_TURI_HAMON",
    "eEC_EFFECT_TURI_MIZU",
    "eEC_EFFECT_TURI_HANE0",
    "eEC_EFFECT_TURI_HANE1",
    "eEC_EFFECT_TURI_SUITEKI",
    "eEC_EFFECT_ONGEN",
    "eEC_EFFECT_IMPACT_STAR",
    "eEC_EFFECT_SANDSPLASH",
    "eEC_EFFECT_YOUNG_TREE",
    "eEC_EFFECT_SWING_ROD",
    "eEC_EFFECT_DOYON",
    "eEC_EFFECT_KAGU_HAPPA",
    "eEC_EFFECT_HANABI_DUMMY",
    "eEC_EFFECT_DIG_HOLE",
    "eEC_EFFECT_DIG_SCOOP",
    "eEC_EFFECT_DIG_MUD",
    "eEC_EFFECT_KIGAE",
    "eEC_EFFECT_KIGAE_LIGHT",
    "eEC_EFFECT_TAPE",
    "eEC_EFFECT_CLACKER",
    "eEC_EFFECT_KAMIFUBUKI",
    "eEC_EFFECT_CAR_BLIGHT",
    "eEC_EFFECT_TAMAIRE",
    "eEC_EFFECT_CAR_LIGHT",
    "eEC_EFFECT_RESET_HOLE",
    "eEC_EFFECT_GOKI",
    "eEC_EFFECT_HANABIRA",
    "eEC_EFFECT_WAIT_ASIMOTO",
    "eEC_EFFECT_OTOSIANA",
    "eEC_EFFECT_IKIGIRE",
    "eEC_EFFECT_YUKIDARUMA",
    "eEC_EFFECT_KYOUSOU_ONPU",
    "eEC_EFFECT_DOUZOU_LIGHT",
    "eEC_EFFECT_HALLOWEEN_SMOKE",
    "eEC_EFFECT_HALLOWEEN",
    "eEC_EFFECT_MOTIYUGE",
    "eEC_EFFECT_TABERU",
    "eEC_EFFECT_KASAMIZU",
    "eEC_EFFECT_KASAMIZUTAMA",
    "eEC_EFFECT_HANATIRI",
    "eEC_EFFECT_URANAI",
    "eEC_EFFECT_SUISOU_AWA",
    "eEC_EFFECT_BREAK_AXE",
    "eEC_EFFECT_YAJIRUSHI",
    "eEC_EFFECT_SOBA_YUGE",
    "eEC_EFFECT_FURO_YUGE",
    "eEC_EFFECT_SHOOTING",
    "eEC_EFFECT_SHOOTING_SET",
    "eEC_EFFECT_SHOOTING_KIRA",
    "eEC_EFFECT_COIN",
    "eEC_EFFECT_TENT_LAMP",
    "eEC_EFFECT_FLASH",
    "eEC_EFFECT_FLASHC",
    "eEC_EFFECT_KILLER",
    "eEC_EFFECT_MAKE_HEM",
    "eEC_EFFECT_MAKE_HEM_KIRA",
    "eEC_EFFECT_MAKE_HEM_LIGHT",
    "eEC_EFFECT_NOMI",
    "eEC_EFFECT_RESETBREAK",
    "eEC_EFFECT_RESETBREAK_PARTS",
    "eEC_EFFECT_RESETBREAK_DUST",
    "eEC_EFFECT_RESETBREAK_PIECE",
    "eEC_EFFECT_PRESENTOPEN",
    "eEC_EFFECT_PRESENTOPEN_PARTS",
    "eEC_EFFECT_NUM"
])

FRAMECONTROL_MODE = dict_enum_from_list([
    "cKF_FRAMECONTROL_STOP",
    "cKF_FRAMECONTROL_REPEAT",
])

MOUTH_TYPES = dict_enum_from_list([
    "aNPC_MOUTH_TEX0",
    "aNPC_MOUTH_TEX1",
    "aNPC_MOUTH_TEX2",
    "aNPC_MOUTH_TEX3",
    "aNPC_MOUTH_TEX4",
    "aNPC_MOUTH_TEX5",
    "aNPC_MOUTH_TEX_NUM"
])

EYE_TYPES = dict_enum_from_list([
    "aNPC_EYE_TEX0",
    "aNPC_EYE_TEX1",
    "aNPC_EYE_TEX2",
    "aNPC_EYE_TEX3",
    "aNPC_EYE_TEX4",
    "aNPC_EYE_TEX5",
    "aNPC_EYE_TEX6",
    "aNPC_EYE_TEX7",
    "aNPC_EYE_TEX_NUM",
])

FEEL_TYPES = dict_enum_from_list([
    "mNpc_FEEL_NORMAL",
    "mNpc_FEEL_HAPPY",
    "mNpc_FEEL_ANGRY",
    "mNpc_FEEL_SAD",
    "mNpc_FEEL_SLEEPY",
    "mNpc_FEEL_PITFALL",
    "mNpc_FEEL_6",
    "mNpc_FEEL_UZAI_0",
    "mNpc_FEEL_UZAI_1",
    "mNpc_FEEL_ALL_NUM"
])


# Check the finished C source, not the assembly object names or the initial
# type guesses: parsers can discover additional types and emit enum constants.
# Include each directly used type/macro's header rather than depending on
# unrelated headers to bring it in transitively.
HEADER_SYMBOLS = {
    "types.h": set("""
        u8 u16 u32 u64 s8 s16 s32 s64 f32 f64
        NULL TRUE FALSE ARRAY_COUNT ATTRIBUTE_ALIGN
    """.split()),
    "PR/gbi.h": {"Gfx", "Vtx", "Mtx"},
    "PR/mbi.h": {"_SHIFTL", "_SHIFTR", "_SHIFT", "G_ON", "G_OFF",
                 "SEGMENT_ADDR", "SEGMENT_OFFSET", "SEGMENT_NUMBER"},
    "evw_anime.h": set("""
        EVW_ANIME_DATA EVW_ANIME_SCROLL EVW_ANIME_COL_PRIM EVW_ANIME_COL_ENV
        EVW_ANIME_COLREG EVW_ANIME_TEXANIME EVW_ANIME_TYPE_SCROLL1
        EVW_ANIME_TYPE_SCROLL2 EVW_ANIME_TYPE_COLREG_MANUAL
        EVW_ANIME_TYPE_COLREG_LINEAR EVW_ANIME_TYPE_COLREG_NONLINEAR
        EVW_ANIME_TYPE_TEXANIME EVW_ANIME_TYPE_NUM
    """.split()),
    "c_keyframe.h": {
        "cKF_Skeleton_R_c", "cKF_Joint_R_c", "cKF_Animation_R_c",
        "cKF_JOINT_FLAG_DISP_OPA", "cKF_JOINT_FLAG_DISP_XLU",
    } | set(FRAMECONTROL_MODE.values()),
    "ac_npc.h": {
        "aNPC_Animation_c", "aNPC_se_data_table_c", "aNPC_se_data_c",
        "aNPC_other_se_data_c", "aNPC_feel_effect_c",
        "aNPC_OTHER_SE_TYPE_NONE", "aNPC_OTHER_SE_TYPE1",
    } | set(MOUTH_TYPES.values()) | set(EYE_TYPES.values()),
    "m_npc.h": set(FEEL_TYPES.values()),
    "ef_effect_control.h": set(EFFECT_TYPES.values()),
}

GBI_EXTENSION_HEADER = "libforest/gbi_extensions.h"
# Fallback for use outside a full checkout. In a checkout the actual header's
# #define names are used, so newly added extension macros are recognized too.
GBI_EXTENSION_SYMBOLS = set("""
    SOFTSPRITE_MTX_SEG ANIME_1_TXT_SEG ANIME_2_TXT_SEG ANIME_3_TXT_SEG
    ANIME_4_TXT_SEG ANIME_5_TXT_SEG ANIME_6_TXT_SEG ANIME_4_TXT_SIZE
    ANIME_6_MODEL_SIZE SEG_EQUALS softsprite_mtx anime_1_txt anime_1_model
    anime_2_txt anime_2_model anime_3_txt anime_3_model anime_4_txt anime_4_model
    anime_5_txt anime_5_model anime_6_txt anime_6_model anime_6_mdl
    G_TRIN G_TRIN_INDEPEND G_SETTEXEDGEALPHA G_SETCOMBINE_NOTEV G_SETCOMBINE_TEV
    G_SETTILE_DOLPHIN G_FIRST_CMD G_CC_BLENDPRIMDECALA POLY_5b POLY_7b POLY_BITMASK
    SHARED_MTX NONSHARED_MTX MTX_SHARED MTX_NONSHARED
    G_TAG_NONE G_TAG_HERE G_TAG_STRING G_TAG_WORD G_TAG_FLOAT G_TAG_INFO
    G_TAG_CALLBACK G_TAG_OPENDISP G_TAG_CLOSEDISP G_TAG_FILL
    G_CULL_X_LESSTHAN G_CULL_X_GREATERTHAN G_CULL_Y_LESSTHAN G_CULL_Y_GREATERTHAN
    G_CULL_Z_LESSTHAN G_CULL_Z_GREATERTHAN G_LIGHTING_POSITIONAL
    G_DECAL_LEQUAL G_DECAL_GEQUAL G_DECAL_EQUAL G_DECAL_ALWAYS G_DECAL_SPECIAL
    G_DECAL_ALL G_SPECIAL_NONE G_SPECIAL_UNKNOWN G_SPECIAL_TA_MODE
    G_TA_N64 G_TA_DOLPHIN COMBINER_PARAM_A COMBINER_PARAM_B COMBINER_PARAM_C
    COMBINER_PARAM_D TEV_COMBINED TEV_COMBINED_ALPHA TEV_FILL TEV_PRIM_LOD_FRAC
    TEV_PRIMITIVE TEV_PRIMITIVE_ALPHA TEV_ENVIRONMENT TEV_ENV_ALPHA
    TEV_TEXEL0 TEV_TEXEL0_ALPHA TEV_SHADE TEV_SHADE_ALPHA TEV_ONE TEV_HALF
    TEV_KONST TEV_ZERO TEV_ALPHA_COMBINED TEV_ALPHA_PRIM_LOD_FRAC
    TEV_ALPHA_PRIMITIVE TEV_ALPHA_ENVIRONMENT TEV_ALPHA_TEXEL0 TEV_ALPHA_SHADE
    TEV_ALPHA_ONE TEV_ALPHA_ZERO EXPAND_WIDTH EXPAND_HEIGHT
    gsDPParam2 gsDPNoOpTag2 gsDPNoOpHere gsDPNoOpString gsDPNoOpWord
    gsDPNoOpFloat gsDPNoOpQuiet gsDPNoOpVerbose gsDPNoOpCallBack
    gsDPNoOpOpenDisp gsDPNoOpCloseDisp gsDPNoOpFill gsDPNoOpTag3
    G_TLUT_DOLPHIN gsDPLoadTLUT_Dolphin gsDPSetTextureImage_Dolphin
    gsDPSetTile_Dolphin gsDPSetTileSize_Dolphin G_DOLPHIN_TLUT_DEFAULT_MODE
    gsDPLoadTextureBlock_4b_Dolphin gsDPLoadMultiBlock_4b_Dolphin
    gsSPNTriangles_Independ gsSPNTriangleData1 gsSPNTriangleData2
    G_VTX_MODE_5bit G_VTX_MODE_7bit gsSPNTriangles_5b gsSPNTrianglesInit_5b
    gsSPNTriangles_7b gsSPNTrianglesInit_7b gsSPNTriangles
    gsDPSetTexEdgeAlpha gsDPSetTextureAdjustMode qs1616 IPART FPART gdSPDefMtx
    G_DL_GXDL gsGXCallDisplayList
""".split())

# Preserve the original extension-before-GBI ordering when both are needed.
HEADER_ORDER = (
    "types.h", GBI_EXTENSION_HEADER, "PR/mbi.h", "PR/gbi.h", "evw_anime.h",
    "c_keyframe.h", "ac_npc.h", "m_npc.h", "ef_effect_control.h",
)
_C_NON_CODE = re.compile(
    r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
    re.DOTALL,
)


def strip_c_non_code(source: str) -> str:
    """Ignore comments/literals (including asset include filenames)."""
    source = re.sub(r"\\\r?\n", "", source)
    return _C_NON_CODE.sub(lambda match: " " + "\n" * match[0].count("\n"), source)


def get_required_includes(source: str, include_dir="include") -> list[str]:
    """Return a stable, duplicate-free list of headers used by emitted C."""
    code = strip_c_non_code(source)
    identifiers = set(re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", code))
    required = {header for header, symbols in HEADER_SYMBOLS.items()
                if identifiers & symbols}

    extension_path = pathlib.Path(include_dir) / GBI_EXTENSION_HEADER
    try:
        extension_source = extension_path.read_text(encoding="utf-8")
    except FileNotFoundError:
        extension_symbols = GBI_EXTENSION_SYMBOLS
    else:
        extension_symbols = set(re.findall(
            r"^\s*#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)",
            strip_c_non_code(extension_source), re.MULTILINE,
        ))
    if identifiers & extension_symbols:
        required.add(GBI_EXTENSION_HEADER)

    # Static display-list commands use _SHIFTL/_SHIFTR from mbi.h; gbi.h
    # alone is sufficient for Vtx/Gfx declarations, but not those commands.
    # The extension header already includes mbi.h. Otherwise use mbi.h as
    # the graphics entry point (it also includes gbi.h).
    if re.search(r"\bgs[A-Za-z0-9_]+\s*\(", code) and GBI_EXTENSION_HEADER not in required:
        required.add("PR/mbi.h")
    if "PR/mbi.h" in required:
        required.discard("PR/gbi.h")

    return [header for header in HEADER_ORDER if header in required]


def validate_version(version: str) -> None:
    if version not in SUPPORTED_VERSIONS:
        raise ValueError(
            f"Unsupported version {version!r}; expected one of "
            f"{', '.join(SUPPORTED_VERSIONS)}"
        )


def get_asset_config_path(version: str = DEFAULT_VERSION) -> pathlib.Path:
    validate_version(version)
    path = pathlib.Path("config") / version / "config.yml"
    if not path.is_file():
        raise FileNotFoundError(f"Asset configuration for {version} not found: {path}")
    return path


@dataclass
class struct_ref:
    symbol_name: str
    symbol_type: str


@dataclass
class struct_parse_result:
    formatted_str: str
    referenced_objects: list[struct_ref]
    c_type: str = None


def anim_type_conv(anim_type: int):
    return {
        0: "EVW_ANIME_TYPE_SCROLL1",
        1: "EVW_ANIME_TYPE_SCROLL2",
        2: "EVW_ANIME_TYPE_COLREG_MANUAL",
        3: "EVW_ANIME_TYPE_COLREG_LINEAR",
        4: "EVW_ANIME_TYPE_COLREG_NONLINEAR",
        5: "EVW_ANIME_TYPE_TEXANIME",
    }.get(anim_type, str(anim_type))


def parse_bin_formatted(buff: bytes, in_format: list[tuple[str, str]], _symbols: dict[int, str], val_conv: callable = None, type_conv: callable = None, fmt_conv: callable = None):
    struct_format = ">"
    symbols_offsets = {}
    symbol_order = []
    reloc_symbols = []

    for format_pair in in_format:
        if format_pair == None:
            struct_format += "x"
            continue

        this_offset = struct.calcsize(struct_format)
        struct_type, name = format_pair

        if struct_type == "p":
            reloc_symbols.append(name)
            struct_type = "xxxx"

        struct_format += struct_type
        symbols_offsets[name] = this_offset
        symbol_order.append(name)

    BUFF_SIZE = struct.calcsize(struct_format)
    assert ((len(buff) % BUFF_SIZE) == 0)
    found_syms = []
    out_c_data = []
    i = 0
    for i in range(0, len(buff), BUFF_SIZE):
        b = buff[i:i+BUFF_SIZE]
        if len(b) < BUFF_SIZE:
            break
        extracted_data: list[int] = list(struct.unpack(struct_format, b))

        collapsed_data = {}

        for this_symbol_name in symbol_order:
            if this_symbol_name in reloc_symbols:
                ref_name = _symbols.get(
                    i + symbols_offsets[this_symbol_name], "NULL")

                collapsed_data[this_symbol_name] = ref_name
            else:
                collapsed_data[this_symbol_name] = extracted_data.pop(0)

        new_converted_vals = {}

        if val_conv:
            for name, val in collapsed_data.items():
                new_val = val_conv(name, val, dict(collapsed_data))
                if new_val != None:
                    new_converted_vals[name] = new_val

        collapsed_data.update(new_converted_vals)

        if type_conv:
            for name, value in collapsed_data.items():
                new_type = type_conv(name, dict(collapsed_data))
                if new_type != None:
                    found_syms.append(struct_ref(value, new_type))

        new_converted_vals = {}

        if fmt_conv:
            for name, val in collapsed_data.items():
                new_val = fmt_conv(name, val, dict(collapsed_data))
                if new_val != None:
                    new_converted_vals[name] = new_val

        collapsed_data.update(new_converted_vals)

        new_converted_vals = {}

        vals = collapsed_data.values()
        out_c_data.append(f"\t{{ {', '.join([str(x) for x in vals])} }}")

    return struct_parse_result(",\n".join(out_c_data), found_syms)


def parse_evw_anime_data(buff: bytes, symbols) -> struct_parse_result:
    this_format = [("b", "segment"), None, ("h", "anim_type"),
                   ("p", "this_symbol_name")]

    def vcf(name, value, all_values):
        if name == "anim_type":
            return anim_type_conv(value)

    def tcf(name, all_values):
        if name == "this_symbol_name":
            return all_values["anim_type"]

    return parse_bin_formatted(buff, this_format, symbols, vcf, tcf)


def parse_evw_anime_col_prim(buff: bytes, symbols):
    this_format = [("B", "r"), ("B", "g"), ("B", "b"), ("B", "a"), ("B", "l")]
    return parse_bin_formatted(buff, this_format, symbols)


def parse_evw_anime_col_env(buff: bytes, symbols: list[str]):
    this_format = [("B", "r"), ("B", "g"), ("B", "b"), ("B", "a")]
    return parse_bin_formatted(buff, this_format, symbols)


def parse_evw_anime_colreg(buff: bytes, symbols: list[str]):
    this_format = [("H", "prim_colors"), ("H", "key_count"),
                   ("p", "prim_colors"), ("p", "env_colors"), ("p", "keyframes")]

    def tcf(name, symbols):
        return {
            "prim_colors": "EVW_ANIME_COL_PRIM",
            "env_colors": "EVW_ANIME_COL_ENV",
            "keyframes": "u16",
        }.get(name, None)
    return parse_bin_formatted(buff, this_format, symbols, type_conv=tcf)


def parse_evw_anime_scroll(buff: bytes, symbols: list[str]):
    this_format = [("b", "x"), ("b", "y"), ("B", "width"), ("B", "height")]
    res = parse_bin_formatted(buff, this_format, symbols)
    res.c_type = "EVW_ANIME_SCROLL"
    return res


def parse_evw_texanime(buff: bytes, symbols: list[str]):
    this_format = [("H", "frame_count"), ("H", "key_count"), ("p",
                                                              "texture_tbl"), ("p", "animation_pattern"), ("p", "keyframes")]

    def tcf(name, symbols):
        return {
            "texture_tbl": "VOID*_LIST",
            "animation_pattern": "u8",
            "keyframes": "u16",
        }.get(name, None)

    def fcf(name, value, symbols):
        if name == "frame_count":
            return F"ARRAY_COUNT({symbols['animation_pattern']})"
    res = parse_bin_formatted(
        buff, this_format, symbols, type_conv=tcf, fmt_conv=fcf)
    res.c_type = "EVW_ANIME_TEXANIME"
    return res


def parse_voidstarlist(buff: bytes, symbols: dict[int:str]):
    return struct_parse_result(", ".join(symbols.values()), [], "void*")


def parse_aNPC_se_data_table_c(buff: bytes, symbols: dict[int:str]):
    this_format = [("p", "lfoot_data"), ("p", "rfoot_data"),
                   ("l", "other_se_type"), ("p", "other_se_data")]

    def tcf(name, symbols):
        return {
            "lfoot_data": "aNPC_se_data_c",
            "rfoot_data": "aNPC_se_data_c",
            "other_se_data": "aNPC_other_se_data_c",
        }.get(name, None)

    def vcf(name, value, symbols):
        if name == "other_se_type":
            return {
                0: "aNPC_OTHER_SE_TYPE_NONE",
                1: "aNPC_OTHER_SE_TYPE1",
            }.get(value, str(value))

    return parse_bin_formatted(buff, this_format, symbols, vcf, tcf)


def parse_aNPC_se_data_c(buff: bytes, symbols: dict[int:str]):
    this_format = [("l", "num_check_frames"), ("p", "check_frame_tbl")]

    def tcf(name, symbols):
        return {
            "check_frame_tbl": "int"
        }.get(name, None)

    def fcf(name, value, symbols):
        if name == "num_check_frames":
            return f"ARRAY_COUNT({symbols['check_frame_tbl']})"
    # def vcf(name, value, symbols):
    #     if name == "other_se_type":
    #         return {
    #             0: "aNPC_OTHER_SE_TYPE_NONE",
    #             1: "aNPC_OTHER_SE_TYPE1",
    #         }.get(value, str(value))

    return parse_bin_formatted(buff, this_format, symbols, type_conv=tcf, fmt_conv=fcf)


def parse_aNPC_feel_effect_c(buff: bytes, symbols: dict[int:str]):
    this_format = [("h", "feel_type"),
                   ("B", "max"), ("B", "set_num"), ("p", "set_p")]

    def tcf(name, symbols):
        return {
            "set_p": "u32"
        }.get(name, None)

    def fcf(name, value, symbols):
        if name == "feel_type":
            return FEEL_TYPES.get(value, str(value))
        if name == "set_num":
            return f"ARRAY_COUNT({symbols['set_p']})"

    return parse_bin_formatted(buff, this_format, symbols, type_conv=tcf, fmt_conv=fcf)


def parse_aNPC_other_se_data_c(buff: bytes, symbols: dict[int:str]):
    this_format = [("l", "num_check_frames"),
                   ("p", "check_frame_tbl"), ("H", "se_no"), None, None]

    def tcf(name, symbols):
        return {
            "check_frame_tbl": "int"
        }.get(name, None)

    def fcf(name, value, symbols):
        if name == "num_check_frames":
            return f"{{ ARRAY_COUNT({symbols['check_frame_tbl']})"
        if name == "check_frame_tbl":
            return f"{value}}}"

    return parse_bin_formatted(buff, this_format, symbols, type_conv=tcf, fmt_conv=fcf)


def parse_cKF_Skeleton_R_c(buff: bytes, symbols: list[str]):
    this_format = [("B", "num_joints"), ("B", "num_shown_joints"),
                   None, None, ("p", "joint_table")]

    def tcf(name, symbols):
        return {
            "joint_table": "cKF_Joint_R_c",
        }.get(name, None)

    def vcf(name, value, symbols):
        if name == "num_joints":
            return f"ARRAY_COUNT({symbols['joint_table']})"

    return parse_bin_formatted(buff, this_format, symbols, vcf, tcf)


def parse_cKF_Animation_R_c(buff: bytes, symbols: list[str]):
    this_format = [("p", "flag_table"), ("p", "data_table"),
                   ("p", "key_table"), ("p", "fixed_table"), ("h", "pad"), ("h", "frames")]

    def tcf(name, symbols):
        return {
            "flag_table": "u8",
            "data_table": "s16",
            "key_table": "s16",
            "fixed_table": "s16",
        }.get(name, None)

    return parse_bin_formatted(buff, this_format, symbols, type_conv=tcf)


def parse_aNPC_Animation_c(buff: bytes, symbols: list[str]):
    this_format = [
        ("p", "flag_table"),
        ("p", "data_table"),
        ("p", "key_table"),
        ("p", "fixed_table"),
        ("h", "pad"),
        ("h", "frames"),
        ("f", "start_time"),
        ("f", "end_time"),
        ("l", "mode"),
        ("f", "morph_counter"),
        ("p", "eye_seq_p"),
        ("h", "eye_seq_type"),
        ("h", "eye_seq_stop_frame"),
        ("p", "mouth_seq_p"),
        ("h", "mouth_seq_type"),
        ("h", "mouth_seq_stop_frame"),
        ("h", "feel_effect_set_frame"),
        ("h", "feel_effect_type"),
        ("p", "feel_effect"),
        ("p", "se_data_table")]

    def tcf(name, symbols):
        return {
            "flag_table": "u8",
            "data_table": "s16",
            "key_table": "s16",
            "fixed_table": "s16",
            "eye_seq_p": "u8",
            "mouth_seq_p": "u8",
            "feel_effect": "aNPC_feel_effect_c",
            "se_data_table": "aNPC_se_data_table_c",
        }.get(name, None)

    def fcf(name, value, symbols):
        if name == "flag_table":
            return f"{{ {value}"
        if name == "frames":
            return f"{value} }}"
        if name == "se_data_table":
            return f"{value},"
        if name in ["start_time", "end_time", "morph_counter"]:
            return f"{value}f"

    def vcf(name, value, symbols):
        if name == "feel_effect_type":
            return EFFECT_TYPES.get(value, str(value))
        if name == "mode":
            return FRAMECONTROL_MODE.get(value, str(value))
        if name == "mouth_seq_type":
            return MOUTH_TYPES.get(value, str(value))
        if name == "eye_seq_type":
            return EYE_TYPES.get(value, str(value))

    return parse_bin_formatted(buff, this_format, symbols, vcf, tcf, fcf)


def parse_cKF_Joint_R_c(buff: bytes, symbols: list[str]):
    this_format = [("p", "model"), ("B", "child"),
                   ("B", "flags"), ("H", "x"), ("H", "y"), ("H", "z")]

    def tcf(name, symbols):
        return {
            "joint_table": "Gfx",
        }.get(name, None)

    def fcf(name, value, symbols):
        if name == "x":
            return f"{{ {value}"
        if name == "z":
            return f"{value} }}"

    def vcf(name, value, symbols):
        if name == "flags":
            return {
                0: "cKF_JOINT_FLAG_DISP_OPA",
                1: "cKF_JOINT_FLAG_DISP_XLU"
            }.get(value, None)
    return parse_bin_formatted(buff, this_format, symbols, vcf, tcf, fcf)


def parse_u16(buff: bytes, symbols: list[str]):
    vals = struct.unpack(">" + "H" * (len(buff) // 2), buff)
    out_str = ",\n".join(str(x) for x in vals)
    return struct_parse_result(out_str, [], "u16")


def parse_int(buff: bytes, symbols: list[str]):
    vals = struct.unpack(">" + "l" * (len(buff) // 4), buff)
    out_str = ",\n".join(str(x) for x in vals)
    return struct_parse_result(out_str, [])


def parse_u32(buff: bytes, symbols: list[str]):
    vals = struct.unpack(">" + "L" * (len(buff) // 4), buff)
    out_str = ",\n".join(str(x) for x in vals)
    return struct_parse_result(out_str, [])


def parse_s16(buff: bytes, symbols: list[str]):
    vals = struct.unpack(">" + "h" * (len(buff) // 2), buff)
    out_str = ",\n".join(str(x) for x in vals)
    return struct_parse_result(out_str, [], "s16")


def parse_u8(buff: bytes, symbols: list[str]):
    vals = struct.unpack(">" + "B" * len(buff), buff)
    out_str = ",\n".join(str(x) for x in vals)
    return struct_parse_result(out_str, [], "u8")


def lookup_rel_vtx_offset(lines: list[str], name: str):
    symbol_name, offset_label = name.split(", ")
    offset = 0
    inside = False
    for line in lines:
        if line.startswith(f".obj {symbol_name},"):
            inside = True
        if not inside:
            continue

        if line.startswith(offset_label):
            return offset

        if ".4byte" in line:
            offset += 4
        elif ".2byte" in line:
            offset += 2
        elif ".byte" in line:
            offset += line.count(",") + 1
        else:
            assert (not line.endswith(f".endobj {symbol_name}"))
    assert (False)


def lookup_bins_and_symbols(lines: list[str], name: str):
    out_bin = bytearray()
    out_symbols = []
    begin_ind = 0
    end_ind = 0
    for i, line in enumerate(lines):
        if line.startswith(f".obj {name},"):
            begin_ind = i
        if line == f".endobj {name}":
            end_ind = i
    data_lines = lines[begin_ind+1:end_ind]

    for line in data_lines:
        if ".4byte" in line:
            data = line.split(".4byte ")[1]
            try:
                out_bin.extend(int(data, 16).to_bytes(4, 'big'))
            except Exception as e:
                out_bin.extend(b'\0\0\0\0')
                out_symbols.append(data)
        elif ".rel" in line:
            out_bin.extend(b'\0\0\0\0')
            rel_plus_offset = line.split(".rel ")[1]
            vtx_offset = lookup_rel_vtx_offset(lines, rel_plus_offset)
            out_symbols.append(
                f"&{rel_plus_offset.split(', ')[0]}[{vtx_offset//0x10}]")
        elif ".byte" in line:
            data = line.split(".byte ")[1]
            out_bin.extend(int(data, 16).to_bytes(1, 'big'))

    return out_bin, out_symbols


def is_static(lines: list[str], name: str):
    lookfor = f".obj {name},"
    for line in lines:
        if line.startswith(lookfor):
            if line.startswith(lookfor + " local"):
                return True
            break
    return False


def lookup_static(lines: list[str], name: str):
    if is_static(lines, name):
        return "static "
    return ""


def lookup_align(lines: list[str], name: str):
    out = ""
    align_32 = False
    inside_obj = False
    for i, line in enumerate(lines):
        if line == ".balign 32":
            align_32 = True
        if line.startswith(f".obj {name},"):
            if align_32:
                return ASSET_ALIGN
            else:
                return NO_ALIGN
        elif line.startswith(".obj"):
            inside_obj = True
        elif line.startswith(f".endobj"):
            inside_obj = False
            align_32 = False
        elif not inside_obj and line.startswith("\t.4byte"):
            align_32 = True
    return out


def lookup_bins_and_symbols2(lines: list[str], name: str):
    out_bin = bytearray()
    out_symbols = {}
    begin_ind = 0
    end_ind = 0
    for i, line in enumerate(lines):
        if line.startswith(f".obj {name},"):
            begin_ind = i
        if line == f".endobj {name}":
            end_ind = i
            break
    data_lines = lines[begin_ind+1:end_ind]
    offset_count = 0
    for line in data_lines:
        if ".4byte" in line:
            data = line.split(".4byte ")[1]
            try:
                out_bin.extend(int(data, 16).to_bytes(4, 'big'))
            except Exception as e:
                out_bin.extend(b'\0\0\0\0')
                out_symbols[offset_count] = data
            offset_count += 4
        elif ".2byte" in line:
            data = line.split(".2byte ")[1]
            out_bin.extend(int(data, 16).to_bytes(2, 'big'))
            offset_count += 2
        elif ".byte" in line:
            data = line.split(".byte ")[1]
            if ", " in data:
                for d in data.split(", "):
                    out_bin.extend(int(d, 16).to_bytes(1, 'big'))
                    offset_count += 1
            else:
                out_bin.extend(int(data, 16).to_bytes(1, 'big'))
                offset_count += 1

        elif ".rel" in line:
            out_bin.extend(b'\0\0\0\0')
            data = f"&{line.split('.rel ')[1].split(',')[0]}[xxx]"
            out_symbols[offset_count] = data
            offset_count += 4
        else:
            assert (False), line
    return out_bin, out_symbols


def lookup_address(lines: list[str], name: str):
    for i, line in enumerate(lines):
        if line.startswith(f".obj {name},"):
            addr = lines[i-1].split(" | ")[1]
            return addr
    assert (False)


def mark_matching(config_change_path):
    config_py = "configure.py"
    with open(config_py, "r") as f:
        config_txt = f.read()

    config_txt = config_txt.replace(f"Object(NonMatching, \"{config_change_path}\"),",
                                    f"Object(Matching, \"{config_change_path}\"),")
    with open(config_py, "w") as f:
        f.write(config_txt)


def update_extracted_assets(lines: list[str], out: str, src_file_name: str, version: str = DEFAULT_VERSION):
    # Static symbol addresses come from this revision's assembly. Never append
    # them to a different revision's extraction configuration.
    config_yaml = get_asset_config_path(version)
    with open(config_yaml, "a") as f:
        for i, line in enumerate(out.split("\n")):
            if line.startswith("#include \"assets"):
                prev_line = out.split("\n")[i-1]
                parts = prev_line.split("=")[0].split(" ")
                type = parts[0]
                name = parts[1]
                im_static = False
                if type == "static":
                    im_static = True
                    type = parts[1]
                    name = parts[2]
                name = name[:-2]  # cut off the array []
                if im_static:
                    out_config = f"""
  - symbol: {name}!.data:{lookup_address(lines, name)}
    binary: assets/{src_file_name}/{name}.bin
    header: assets/{src_file_name}/{name}.inc
"""
                else:
                    out_config = f"""
  - symbol: {name}
    binary: assets/{name}.bin
    header: assets/{name}.inc
"""
                if type == "u8":
                    out_config += "    header_type: raw\n"
                elif type == "Vtx":
                    out_config += "    header_type: none\n    custom_type: vtx\n"
                elif type == "u16":
                    out_config += "    header_type: none\n    custom_type: pal16\n"
                else:
                    assert (False)
                f.write(out_config)


def get_externs(lines: list[str]):
    found_objs: set[str] = set()
    found_refs: set[str] = set()
    for line in lines:
        if line.startswith(".obj "):
            found_objs.add(line.split(" ")[1][:-1])
        elif line.startswith("\t.4byte") and not line.startswith("\t.4byte 0x"):
            name = line.split(" ")[1]
            if name not in found_objs:
                found_refs.add(name)
        elif line.startswith("\t.rel"):
            name = line.split(" ")[1][:-1]
            found_refs.add(name)
            if name not in found_objs:
                found_refs.add(name)
    externs = []
    for ex in found_refs:
        type = "u8"
        if ex.endswith("_pal"):
            type = "u16"
        elif ex.endswith("_model"):
            type = "Gfx"
        elif ex.endswith("_v"):
            type = "Vtx"
        externs.append(f"extern {type} {ex}[];")
    return "\n".join(externs) + "\n"


def convert_source_to_gfx_c_source(src_file, dest_path, known_types: dict[str, str], should_extract_symbols=False, should_link=False, version: str = DEFAULT_VERSION):
    validate_version(version)
    # Fail before changing generated source or configure.py if -u cannot run.
    if should_extract_symbols:
        get_asset_config_path(version)
    with open(src_file) as f:
        lines = f.read().split("\n")
    src_file_name = pathlib.Path(src_file).stem
    config_change_path = str(
        pathlib.PurePosixPath(dest_path).relative_to("src"))

    # found_objs = []
    found_types = []
    all_objs = []
    for line in lines:
        if line.startswith(".obj"):
            this_obj = line.split(" ")[1].strip(",")
            all_objs.append(this_obj)
            if this_obj in known_types:
                found_types.append((this_obj, known_types[this_obj]))
            elif this_obj.endswith("_v") or \
                    this_obj.endswith("_v2"):
                found_types.append((this_obj, "Vtx"))
            elif "_model" in this_obj or \
                    this_obj.endswith("_setmode") or \
                    this_obj.endswith("_modeset") or \
                    this_obj.endswith("_mode") or \
                    this_obj.endswith("_gfx") or \
                    this_obj.endswith("_vtx") or \
                    this_obj.endswith("_gfx2"):
                found_types.append((this_obj, "Gfx"))
            elif "_tex_index" in this_obj:
                found_types.append((this_obj, "u8"))
            elif this_obj.endswith("evw_anime"):
                found_types.append((this_obj, "EVW_ANIME_DATA"))
            elif this_obj.endswith("_pal"):
                found_types.append((this_obj, "PAL"))
            elif this_obj.endswith("_tex"):
                found_types.append((this_obj, "TEX"))
            elif this_obj.startswith("cKF_bs_r"):
                found_types.append((this_obj, "cKF_Skeleton_R_c"))
            elif this_obj.startswith("cKF_ba_r_npc"):
                found_types.append((this_obj, "aNPC_Animation_c"))
            elif this_obj.startswith("cKF_ba_r"):
                found_types.append((this_obj, "cKF_Animation_R_c"))

    # we now have a list of all objects, and we have a partial mapping of what type they could have
    # what we want to do is go through all the objects we know, and get the out-data
    # there are some objs that will add to this list, we can queue them onto the list

    converted_types = {}
    lookup_table = {
        "EVW_ANIME_DATA": parse_evw_anime_data,
        "EVW_ANIME_TYPE_SCROLL1": parse_evw_anime_scroll,
        "EVW_ANIME_TYPE_SCROLL2": parse_evw_anime_scroll,
        "EVW_ANIME_TYPE_COLREG_MANUAL": parse_evw_anime_colreg,
        "EVW_ANIME_TYPE_COLREG_LINEAR": parse_evw_anime_colreg,
        "EVW_ANIME_TYPE_COLREG_NONLINEAR": parse_evw_anime_colreg,
        "EVW_ANIME_TYPE_TEXANIME": parse_evw_texanime,
        "EVW_ANIME_COL_PRIM": parse_evw_anime_col_prim,
        "EVW_ANIME_COL_ENV": parse_evw_anime_col_env,
        "cKF_Skeleton_R_c": parse_cKF_Skeleton_R_c,
        "cKF_Joint_R_c": parse_cKF_Joint_R_c,
        "cKF_Animation_R_c": parse_cKF_Animation_R_c,
        "u8": parse_u8,
        "u16": parse_u16,
        "s16": parse_s16,
        "int": parse_int,
        "u32": parse_u32,
        "aNPC_Animation_c": parse_aNPC_Animation_c,
        "VOID*_LIST": parse_voidstarlist,
        "aNPC_se_data_table_c": parse_aNPC_se_data_table_c,
        "aNPC_se_data_c": parse_aNPC_se_data_c,
        "aNPC_other_se_data_c": parse_aNPC_other_se_data_c,
        "aNPC_feel_effect_c": parse_aNPC_feel_effect_c,
    }
    # we now have a list of objects+type
    while len(found_types) > 0:
        obj_name, type = found_types.pop()
        default_data = f'#include "assets/{obj_name}.inc"'
        if is_static(lines, obj_name):
            default_data = f'#include "assets/{src_file_name}/{obj_name}.inc"'

        if obj_name in converted_types:
            continue
        if type == "Vtx":
            converted_types[obj_name] = (type, default_data)
        elif type == "Gfx":
            bins, symbols = lookup_bins_and_symbols(lines, obj_name)
            data = convert_binary_to_gfx(bins, symbols)
            converted_types[obj_name] = (type, data + ",")
        elif type == "PAL":
            converted_types[obj_name] = ("u16", default_data)
        elif type == "TEX":
            converted_types[obj_name] = ("u8", default_data)

        elif type in lookup_table:
            res: struct_parse_result = lookup_table[type](
                *lookup_bins_and_symbols2(lines, obj_name))
            if res.c_type != None:
                type = res.c_type
            data = res.formatted_str
            converted_types[obj_name] = (type, data)
            if len(res.referenced_objects) > 0:
                found_types = [(ref.symbol_name, ref.symbol_type)
                               for ref in res.referenced_objects] + found_types

    # Build the complete body first, including extern declarations and types
    # discovered recursively, so header selection sees everything actually used.
    out = get_externs(lines)

    for obj in all_objs:
        default_include = f'#include "assets/{obj}.inc"'
        if is_static(lines, obj):
            default_include = f'#include "assets/{src_file_name}/{obj}.inc"'

        this_type, out_data = converted_types.get(
            obj, ("u8", default_include))
        static_typing = lookup_static(lines, obj)
        align = lookup_align(lines, obj)
        if this_type in ["aNPC_Animation_c", "cKF_Animation_R_c", "cKF_Skeleton_R_c"]:
            out += f"{static_typing}{this_type} {obj} {align}= \n{out_data}\n;\n\n"
        else:
            out += f"{static_typing}{this_type} {obj}[] {align}= {{\n{out_data}\n}};\n\n"

    includes = get_required_includes(out)
    if includes:
        header = "\n".join(f'#include "{name}"' for name in includes)
        out = header + "\n\n" + out.lstrip("\n")

    pathlib.Path(dest_path).parent.mkdir(parents=True, exist_ok=True)
    with open(dest_path, "w") as f:
        f.write(out)
    if should_link:
        mark_matching(config_change_path)
    if should_extract_symbols:
        update_extracted_assets(lines, out, src_file_name, version=version)


def main():
    parser = ArgumentParser(
        description="Converts an asset assembly file into C source"
    )
    parser.add_argument("src_path", type=str, help="Output C path relative to src/ (for example, data/example.c)")
    parser.add_argument('-v', '--version', choices=SUPPORTED_VERSIONS,
                        default=DEFAULT_VERSION,
                        help="Build/config revision to use (default: %(default)s)")
    parser.add_argument('-t', '--types', action='append', required=False)
    parser.add_argument('-u', '--update_splits',
                        action='store_true', default=False)
    parser.add_argument('-l', '--link', action='store_true', default=False)
    args = parser.parse_args()

    presented_path = args.src_path

    src_path = str(pathlib.PurePosixPath(
        "build") / args.version / "foresta" / "asm" /
        pathlib.PurePosixPath(presented_path).with_suffix(".s"))
    dest_path = str(pathlib.PurePosixPath("src") / presented_path)
    print(dest_path)
    print(f"version: {args.version}")
    print(f"update splits: {args.update_splits}")
    print(f"update link: {args.link}")
    known_types = {}
    if args.types != None:
        known_types = {x.split(",")[1]: x.split(",")[0] for x in args.types}
    # print(known_types)
    try:
        convert_source_to_gfx_c_source(
            src_path, dest_path, known_types, args.update_splits, args.link,
            version=args.version)
    except (OSError, ValueError) as exc:
        parser.error(str(exc))


if __name__ == "__main__":
    main()
