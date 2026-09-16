#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_tent_box_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_box_pal.inc"
};

u16 rom_tent_can_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_can_pal.inc"
};

u16 rom_tent_mono1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_mono1_pal.inc"
};

u16 rom_tent_gas_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_gas_pal.inc"
};

u8 rom_tent_enter[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_enter.inc"
};

u8 rom_tent_floor[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_floor.inc"
};

u8 rom_tent_wall1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_wall1.inc"
};

u8 rom_tent_wall2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_wall2.inc"
};

u8 rom_tent_bou[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_bou.inc"
};

u8 rom_tent_mono1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_mono1.inc"
};

u8 rom_tent_can[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_can.inc"
};

u8 rom_tent_conpas[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_conpas.inc"
};

u8 rom_tent_box[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_box.inc"
};

u8 rom_tent_kage_m[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_kage_m.inc"
};

u8 rom_tent_gas[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_gas.inc"
};

u8 rom_tent_kage_s[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_kage_s.inc"
};

u8 rom_tent_kage_b[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_tent/rom_tent_kage_b.inc"
};

Vtx rom_tent_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_tent/rom_tent_v.inc"
};

Gfx rom_tent_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPEndDisplayList(),
};

Gfx rom_tent_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_gas_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, rom_tent_gas),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_tent_v[187], 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 4, 0, 5, 6, 3),
gsSPNTriangles_5b(7, 8, 5, 9, 7, 10, 11, 10, 12, 13, 14, 11),
gsSPNTriangles_5b(6, 15, 4, 6, 16, 15, 8, 17, 16, 8, 16, 6),
gsSPNTriangles_5b(11, 18, 9, 11, 14, 18, 9, 18, 17, 9, 17, 8),
gsSPNTriangles_5b(3, 6, 4, 10, 11, 9, 12, 13, 11, 5, 8, 6),
gsSPNTriangles_5b(7, 9, 8, 19, 20, 21, 19, 21, 22, 23, 24, 25),
gsSPNTriangles_5b(23, 25, 26, 27, 28, 29, 27, 29, 30, 0, 0, 0),
gsSPVertex(&rom_tent_v[218], 32, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 2, 4, 5, 6, 7),
gsSPNTriangles_5b(8, 7, 1, 9, 10, 11, 12, 4, 10, 13, 14, 15),
gsSPNTriangles_5b(13, 16, 14, 17, 18, 16, 17, 16, 13, 15, 19, 20),
gsSPNTriangles_5b(15, 14, 19, 20, 19, 21, 20, 21, 22, 23, 18, 17),
gsSPNTriangles_5b(24, 25, 26, 25, 24, 27, 27, 26, 25, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_tent_v[250], 30, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 2, 4, 3),
gsSPNTriangles_5b(4, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_box_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rom_tent_box),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(16, 6, 7, 8, 7, 9, 8, 10, 11, 7),
gsSPNTriangles_5b(10, 7, 12, 11, 13, 9, 11, 9, 7, 6, 14, 7),
gsSPNTriangles_5b(6, 15, 14, 16, 9, 17, 16, 8, 9, 18, 19, 20),
gsSPNTriangles_5b(18, 20, 21, 22, 23, 24, 25, 26, 27, 26, 28, 27),
gsSPNTriangles_5b(22, 29, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_can_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_tent_conpas),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_tent_v[280], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_mono1_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_tent_mono1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_tent_v[284], 32, 0),
gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 4, 7),
gsSPNTriangles_5b(12, 7, 13, 14, 15, 16, 14, 16, 17, 16, 12, 13),
gsSPNTriangles_5b(16, 13, 17, 18, 19, 20, 21, 22, 23, 21, 23, 24),
gsSPNTriangles_5b(25, 21, 24, 25, 24, 26, 27, 25, 26, 27, 26, 28),
gsSPNTriangles_5b(29, 27, 28, 29, 28, 30, 31, 29, 30, 0, 0, 0),
gsSPVertex(&rom_tent_v[316], 13, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 4, 5, 4, 6, 5),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_can_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 8, rom_tent_bou),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 7, 8, 9, 7, 9, 10, 11, 7, 10),
gsSPNTriangles_5b(11, 10, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_tent_can),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(rom_tent_v, 32, 0),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(4, 5, 1, 5, 6, 1, 6, 7, 1, 7, 8, 1),
gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
gsSPNTriangles_5b(12, 2, 1, 13, 14, 15, 13, 16, 14, 17, 18, 19),
gsSPNTriangles_5b(18, 20, 19, 18, 21, 20, 21, 22, 20, 21, 23, 22),
gsSPNTriangles_5b(23, 24, 22, 15, 25, 13, 15, 26, 25, 26, 27, 25),
gsSPNTriangles_5b(26, 28, 27, 28, 29, 27, 28, 30, 29, 30, 19, 29),
gsSPNTriangles_5b(30, 17, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_tent_v[31], 32, 0),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 0, 4, 1),
gsSPNTriangles_5b(4, 5, 1, 5, 6, 1, 6, 7, 1, 7, 8, 1),
gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
gsSPNTriangles_5b(12, 3, 1, 13, 14, 15, 14, 16, 15, 17, 13, 18),
gsSPNTriangles_5b(13, 15, 18, 19, 18, 20, 19, 17, 18, 14, 21, 16),
gsSPNTriangles_5b(21, 22, 16, 23, 24, 25, 23, 26, 24, 27, 25, 28),
gsSPNTriangles_5b(27, 23, 25, 29, 20, 30, 29, 19, 20, 30, 28, 29),
gsSPNTriangles_5b(30, 27, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_tent_v[62], 32, 0),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(1, 5, 4, 1, 6, 5, 1, 7, 6, 0, 8, 1),
gsSPNTriangles_5b(8, 9, 1, 9, 10, 1, 10, 11, 1, 11, 12, 1),
gsSPNTriangles_5b(12, 7, 1, 13, 14, 15, 13, 16, 14, 16, 17, 14),
gsSPNTriangles_5b(16, 18, 17, 18, 19, 17, 18, 20, 19, 20, 21, 19),
gsSPNTriangles_5b(20, 22, 21, 15, 23, 13, 15, 24, 23, 24, 25, 23),
gsSPNTriangles_5b(25, 26, 23, 25, 27, 26, 27, 28, 26, 27, 29, 28),
gsSPNTriangles_5b(29, 30, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_tent_v[93], 31, 0),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 4, 2, 5),
gsSPNTriangles_5b(4, 0, 2, 6, 5, 7, 6, 4, 5, 8, 7, 9),
gsSPNTriangles_5b(8, 6, 7, 10, 11, 12, 11, 13, 12, 1, 10, 3),
gsSPNTriangles_5b(10, 12, 3, 14, 15, 16, 14, 17, 15, 9, 16, 8),
gsSPNTriangles_5b(9, 14, 16, 18, 19, 20, 18, 21, 19, 21, 22, 19),
gsSPNTriangles_5b(22, 23, 19, 23, 24, 19, 24, 25, 19, 25, 26, 19),
gsSPNTriangles_5b(26, 27, 19, 27, 28, 19, 28, 29, 19, 29, 30, 19),
gsSPNTriangles_5b(30, 20, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_tent_wall2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_tent_v[124], 24, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 2, 3, 4, 5, 6, 7),
gsSPNTriangles_5b(6, 8, 7, 5, 9, 6, 10, 11, 12, 10, 13, 11),
gsSPNTriangles_5b(13, 14, 11, 15, 16, 17, 15, 4, 16, 4, 3, 16),
gsSPNTriangles_5b(18, 19, 20, 18, 7, 19, 7, 8, 19, 21, 22, 13),
gsSPNTriangles_5b(22, 14, 13, 21, 23, 22, 0, 2, 4, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_tent_wall1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_tent_v[148], 24, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 7, 10, 11, 12, 13),
gsSPNTriangles_5b(12, 14, 13, 9, 15, 7, 15, 6, 7, 1, 16, 3),
gsSPNTriangles_5b(16, 17, 3, 13, 18, 11, 18, 19, 11, 20, 21, 19),
gsSPNTriangles_5b(21, 11, 19, 22, 23, 17, 23, 3, 17, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_tent_floor),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_tent_v[172], 15, 0),
gsSPNTrianglesInit_5b(9, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(1, 5, 2, 6, 7, 0, 0, 7, 3, 7, 8, 3),
gsSPNTriangles_5b(9, 6, 2, 6, 0, 2, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_box_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_tent_enter),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(3, 10, 11, 12, 13, 14, 10, 13, 10, 12),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 120, 40, 0, 40, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, rom_tent_kage_b),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_tent_v[329], 20, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_tent_kage_s),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_tent_kage_m),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
gsSPEndDisplayList(),
};
