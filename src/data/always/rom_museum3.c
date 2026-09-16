#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_museum3_wall_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_wall_pal.inc"
};

u16 rom_museum3_back_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_back_pal.inc"
};

u16 rom_museum3_floor_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_floor_pal.inc"
};

u8 rom_museum3_wallA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_wallA_tex.inc"
};

u8 rom_museum3_wallB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_wallB_tex.inc"
};

u8 rom_museum3_back_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_back_tex.inc"
};

u8 rom_museum3_floorA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_floorA_tex.inc"
};

u8 rom_museum3_step_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_step_tex.inc"
};

u8 rom_museum3_hasira_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_hasira_tex.inc"
};

u8 rom_museum3_backside_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum3/rom_museum3_backside_tex.inc"
};

Vtx rom_museum3_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_museum3/rom_museum3_v.inc"
};

Gfx rom_museum3_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPEndDisplayList(),
};

Gfx rom_museum3_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_back_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum3_step_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(rom_museum3_v, 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum3_wallA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum3_v[5], 27, 0),
gsSPNTrianglesInit_5b(27, 0, 1, 2, 3, 4, 5, 3, 6, 4),
gsSPNTriangles_5b(6, 7, 4, 7, 5, 4, 8, 9, 10, 8, 0, 9),
gsSPNTriangles_5b(0, 2, 9, 2, 10, 9, 11, 12, 6, 11, 13, 12),
gsSPNTriangles_5b(13, 14, 12, 14, 6, 12, 0, 15, 1, 15, 16, 1),
gsSPNTriangles_5b(0, 17, 15, 17, 16, 15, 7, 6, 14, 18, 19, 20),
gsSPNTriangles_5b(21, 20, 22, 20, 19, 22, 23, 22, 19, 23, 21, 22),
gsSPNTriangles_5b(19, 18, 24, 18, 25, 24, 26, 24, 25, 26, 19, 24),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum3_wallB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum3_v[32], 27, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 2, 1, 2, 3, 4),
gsSPNTriangles_5b(0, 5, 1, 5, 6, 1, 7, 8, 9, 8, 10, 9),
gsSPNTriangles_5b(4, 3, 11, 3, 12, 11, 13, 14, 15, 14, 16, 15),
gsSPNTriangles_5b(15, 17, 9, 7, 9, 17, 15, 16, 17, 18, 19, 20),
gsSPNTriangles_5b(21, 18, 20, 22, 23, 24, 25, 18, 21, 18, 25, 24),
gsSPNTriangles_5b(26, 24, 25, 26, 22, 24, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_floor_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum3_floorA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_museum3_v[59], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 0, 4, 3, 1, 0),
gsSPNTriangles_5b(3, 5, 1, 6, 7, 8, 9, 10, 11, 12, 9, 11),
gsSPNTriangles_5b(13, 12, 11, 14, 15, 16, 17, 18, 19, 14, 20, 19),
gsSPNTriangles_5b(18, 14, 19, 21, 22, 23, 24, 25, 23, 24, 26, 27),
gsSPNTriangles_5b(24, 23, 26, 28, 0, 2, 28, 29, 0, 29, 28, 7),
gsSPNTriangles_5b(28, 8, 7, 29, 4, 0, 12, 13, 29, 15, 30, 16),
gsSPNTriangles_5b(15, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum3_v[91], 27, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 2, 3, 4, 2, 5, 3),
gsSPNTriangles_5b(2, 1, 5, 5, 6, 7, 8, 9, 0, 10, 11, 12),
gsSPNTriangles_5b(10, 13, 11, 13, 14, 11, 14, 15, 11, 16, 13, 10),
gsSPNTriangles_5b(14, 13, 17, 18, 19, 20, 18, 21, 19, 18, 22, 21),
gsSPNTriangles_5b(18, 4, 22, 23, 21, 24, 25, 21, 22, 26, 11, 18),
gsSPNTriangles_5b(11, 2, 18, 26, 12, 11, 2, 11, 15, 26, 18, 20),
gsSPNTriangles_5b(18, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_museum3_hasira_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum3_v[118], 32, 0),
gsSPNTrianglesInit_5b(40, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(1, 5, 6, 5, 7, 6, 7, 8, 6, 9, 0, 10),
gsSPNTriangles_5b(0, 11, 10, 11, 12, 10, 13, 9, 14, 9, 15, 14),
gsSPNTriangles_5b(15, 16, 14, 17, 18, 19, 17, 13, 18, 18, 20, 19),
gsSPNTriangles_5b(21, 22, 23, 21, 17, 22, 22, 24, 23, 16, 18, 14),
gsSPNTriangles_5b(16, 20, 18, 18, 13, 14, 12, 16, 10, 16, 15, 10),
gsSPNTriangles_5b(15, 9, 10, 20, 22, 19, 20, 24, 22, 22, 17, 19),
gsSPNTriangles_5b(24, 25, 23, 24, 26, 25, 25, 21, 23, 4, 12, 2),
gsSPNTriangles_5b(12, 11, 2, 11, 0, 2, 8, 4, 6, 4, 3, 6),
gsSPNTriangles_5b(3, 1, 6, 27, 7, 28, 27, 8, 7, 7, 5, 28),
gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum3_v[150], 32, 0),
gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 7, 8, 9, 7, 10, 8),
gsSPNTriangles_5b(7, 11, 10, 12, 13, 8, 12, 14, 13, 12, 15, 14),
gsSPNTriangles_5b(16, 9, 17, 16, 18, 9, 16, 19, 18, 20, 17, 21),
gsSPNTriangles_5b(20, 22, 17, 20, 23, 22, 24, 25, 26, 25, 21, 26),
gsSPNTriangles_5b(24, 27, 25, 28, 29, 30, 29, 26, 30, 28, 31, 29),
gsSPNTriangles_5b(20, 25, 23, 25, 27, 23, 20, 21, 25, 16, 23, 19),
gsSPNTriangles_5b(16, 22, 23, 16, 17, 22, 24, 29, 27, 29, 31, 27),
gsSPNTriangles_5b(24, 26, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum3_v[182], 26, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 0, 4, 1),
gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 5, 9, 8, 10, 7, 11),
gsSPNTriangles_5b(10, 12, 7, 10, 13, 12, 14, 15, 16, 15, 11, 16),
gsSPNTriangles_5b(14, 17, 15, 18, 19, 20, 18, 20, 21, 18, 21, 22),
gsSPNTriangles_5b(18, 22, 23, 18, 23, 24, 18, 24, 25, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum3_back_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, rom_museum3_backside_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum3_v[208], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 12, 13, 14),
gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 17, 19, 18, 20, 21, 22),
gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 24, 27, 25, 28, 29, 30),
gsSPNTriangles_5b(28, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum3_v[240], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum3_back_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum3_v[248], 32, 0),
gsSPNTrianglesInit_5b(23, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(4, 5, 2, 6, 7, 8, 6, 8, 9, 10, 7, 11),
gsSPNTriangles_5b(7, 6, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18),
gsSPNTriangles_5b(18, 19, 20, 18, 20, 21, 17, 19, 18, 22, 23, 24),
gsSPNTriangles_5b(23, 25, 24, 25, 23, 26, 25, 26, 27, 13, 12, 28),
gsSPNTriangles_5b(12, 29, 28, 4, 30, 31, 4, 3, 30, 3, 1, 30),
gsSPVertex(&rom_museum3_v[280], 3, 0),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
