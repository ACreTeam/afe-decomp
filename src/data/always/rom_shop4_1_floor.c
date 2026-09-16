#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 rom_shop4_1_floor_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_floor_tex_pal.inc"
};

static u16 rom_shop4_1_base_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_base_tex_pal.inc"
};

static u16 rom_shop4_1_stair_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_stair_tex_pal.inc"
};

static u16 rom_shop4_1_table_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_table_tex_pal.inc"
};

static u16 rom_shop4_1_wall_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_wall_tex_pal.inc"
};

static u16 rom_shop4_1_sign01_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_sign01_tex_pal.inc"
};

static u16 rom_shop4_1_kaunta_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_kaunta_tex_pal.inc"
};

static u16 rom_shop4_2_sign01_us_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_2_sign01_us_tex_pal.inc"
};

static u16 rom_shop4_1_us_sign02_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_us_sign02_tex_pal.inc"
};

u16 rom_shop4_1_us_sign0_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_us_sign0_tex_pal.inc"
};

static u16 rom_shop4_1_sign03_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_sign03_tex_pal.inc"
};

static u16 rom_shop4_1_reji_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_reji_tex_pal.inc"
};

static u16 rom_shop_kouhaku_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop_kouhaku_pal.inc"
};

static u8 rom_shop4_1_floor01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_floor01_tex.inc"
};

static u8 rom_shop4_1_base_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_base_tex.inc"
};

static u8 rom_shop4_1_stair01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_stair01_tex.inc"
};

static u8 rom_shop4_1_table01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_table01_tex.inc"
};

static u8 rom_shop4_1_table02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_table02_tex.inc"
};

static u8 rom_shop4_1_wall01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_wall01_tex.inc"
};

static u8 rom_shop4_1_wall02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_wall02_tex.inc"
};

static u8 rom_shop4_1_sign05_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_sign05_tex.inc"
};

static u8 rom_shop4_1_kaunta01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_kaunta01_tex.inc"
};

static u8 rom_shop4_1_kaunta02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_kaunta02_tex.inc"
};

static u8 rom_shop4_2_us_sign01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_2_us_sign01_tex.inc"
};

static u8 rom_shop4_1_us_sign02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_us_sign02_tex.inc"
};

u8 rom_shop4_1_us_sign0_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_us_sign0_tex.inc"
};

static u8 rom_shop4_1_sign04_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_sign04_tex.inc"
};

static u8 rom_shop4_1_reji01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_reji01_tex.inc"
};

static u8 rom_shop4_1_reji02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_reji02_tex.inc"
};

static u8 rom_shop4_1_reji03_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_reji03_tex.inc"
};

static u8 rom_shop4_1_floor02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_floor02_tex.inc"
};

static u8 rom_shop4_1_floor03_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_floor03_tex.inc"
};

static u8 rom_shop4_1_floor04_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_floor04_tex.inc"
};

static u8 rom_shop4_1_shadow02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_1_shadow02_tex.inc"
};

static u8 rom_shop_kouhaku_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop_kouhaku_tex.inc"
};

Vtx rom_shop4_fuku_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_shop4_1_floor/rom_shop4_fuku_v.inc"
};

Gfx rom_shop4_fuku_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 140, 50, 0, 40, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, rom_shop4_1_shadow02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_shop4_fuku_v[346], 24, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx rom_shop4_fuku_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_2_sign01_us_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rom_shop4_2_us_sign01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_shop4_fuku_v[278], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_us_sign0_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 64, rom_shop4_1_us_sign0_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[282], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_sign03_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_shop4_1_sign04_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[286], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_kaunta_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop4_1_kaunta01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[290], 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop_kouhaku_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop_kouhaku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[296], 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 2, 4, 3, 0, 2),
gsSPNTriangles_5b(5, 3, 4, 6, 7, 8, 6, 8, 9, 7, 10, 11),
gsSPNTriangles_5b(7, 11, 8, 10, 12, 13, 10, 13, 11, 12, 14, 13),
gsSPNTriangles_5b(12, 15, 14, 15, 16, 14, 16, 17, 14, 9, 18, 6),
gsSPNTriangles_5b(9, 19, 18, 19, 20, 18, 19, 21, 20, 21, 22, 20),
gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 24, 27, 25, 27, 28, 29),
gsSPNTriangles_5b(27, 29, 25, 28, 30, 31, 28, 31, 29, 0, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[328], 14, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 1, 4, 2),
gsSPNTriangles_5b(4, 5, 2, 6, 7, 8, 6, 8, 9, 9, 8, 10),
gsSPNTriangles_5b(9, 10, 11, 11, 10, 12, 11, 12, 13, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_reji_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_shop4_1_reji03_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[342], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_base_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop4_1_base_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(rom_shop4_fuku_v, 7, 0),
gsSPNTrianglesInit_5b(5, 0, 1, 2, 1, 3, 2, 4, 2, 5),
gsSPNTriangles_5b(4, 6, 2, 6, 0, 2, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_stair_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_shop4_1_stair01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[7], 8, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(1, 5, 3, 1, 6, 5, 5, 7, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_floor_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_1_floor01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[15], 23, 0),
gsSPNTrianglesInit_5b(13, 0, 1, 2, 3, 0, 4, 3, 1, 0),
gsSPNTriangles_5b(3, 5, 1, 6, 7, 8, 7, 9, 8, 10, 11, 12),
gsSPNTriangles_5b(10, 13, 11, 14, 15, 16, 15, 17, 16, 15, 14, 18),
gsSPNTriangles_5b(19, 20, 21, 20, 19, 22, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_1_floor02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[38], 25, 0),
gsSPNTrianglesInit_5b(13, 0, 1, 2, 0, 3, 1, 4, 5, 1),
gsSPNTriangles_5b(6, 7, 8, 9, 10, 11, 12, 9, 13, 9, 11, 13),
gsSPNTriangles_5b(10, 14, 11, 15, 16, 17, 18, 15, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 23, 21, 24, 22, 21, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_1_floor03_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[63], 24, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 4, 3, 0),
gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 5, 11, 10, 9, 5, 10),
gsSPNTriangles_5b(12, 13, 14, 13, 15, 14, 13, 16, 15, 15, 17, 14),
gsSPNTriangles_5b(12, 18, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_1_floor04_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[87], 26, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 8, 7, 9, 10, 11, 12, 13, 14, 15),
gsSPNTriangles_5b(13, 11, 14, 16, 17, 11, 18, 19, 20, 18, 20, 21),
gsSPNTriangles_5b(20, 22, 21, 23, 24, 21, 22, 25, 21, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_wall_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_shop4_1_wall01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[113], 32, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 5, 8, 6, 5, 9, 8, 10, 11, 12),
gsSPNTriangles_5b(11, 13, 12, 14, 15, 12, 16, 17, 14, 16, 14, 12),
gsSPNTriangles_5b(18, 19, 20, 19, 21, 20, 18, 22, 19, 18, 23, 24),
gsSPNTriangles_5b(18, 25, 23, 26, 27, 28, 27, 29, 28, 29, 30, 28),
gsSPNTriangles_5b(30, 31, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[145], 32, 0),
gsSPNTrianglesInit_5b(25, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 7, 8, 6, 5, 9, 7, 9, 0, 7),
gsSPNTriangles_5b(5, 10, 9, 10, 0, 9, 10, 3, 0, 11, 12, 8),
gsSPNTriangles_5b(12, 13, 8, 13, 4, 8, 4, 6, 8, 14, 15, 16),
gsSPNTriangles_5b(15, 17, 16, 17, 18, 16, 18, 19, 16, 15, 20, 17),
gsSPNTriangles_5b(21, 18, 17, 21, 22, 18, 23, 24, 25, 26, 27, 28),
gsSPNTriangles_5b(29, 26, 28, 30, 31, 25, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[177], 13, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(3, 2, 5, 4, 3, 5, 5, 6, 7, 4, 5, 7),
gsSPNTriangles_5b(8, 4, 7, 2, 1, 9, 2, 9, 10, 11, 6, 5),
gsSPNTriangles_5b(12, 11, 5, 10, 12, 5, 2, 10, 5, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_shop4_1_wall02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[190], 16, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 1, 0),
gsSPNTriangles_5b(4, 0, 5, 6, 7, 4, 6, 4, 5, 8, 9, 10),
gsSPNTriangles_5b(8, 10, 11, 10, 12, 13, 10, 13, 11, 13, 12, 14),
gsSPNTriangles_5b(13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_table_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_shop4_1_table01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[206], 12, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_shop4_1_table02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[218], 20, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_sign01_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop4_1_sign05_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[238], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_reji_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, rom_shop4_1_reji01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[242], 10, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(4, 3, 5, 6, 4, 5, 6, 5, 7, 8, 6, 7),
gsSPNTriangles_5b(8, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_shop4_1_reji02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[252], 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(5, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_kaunta_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_shop4_1_kaunta02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[258], 16, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 5, 12, 15, 5, 15, 6, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_shop4_1_us_sign02_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_shop4_1_us_sign02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_shop4_fuku_v[274], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
