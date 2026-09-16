#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_train_1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_1_pal.inc"
};

u16 rom_train_2_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_2_pal.inc"
};

static u16 rom_train_3_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_3_pal.inc"
};

u8 rom_train_seat1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_seat1_tex.inc"
};

u8 rom_train_seat2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_seat2_tex.inc"
};

u8 rom_train_floor_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_floor_tex.inc"
};

u8 rom_train_wall1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_wall1_tex.inc"
};

u8 rom_train_roof_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_roof_tex.inc"
};

u8 rom_train_wall2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_wall2_tex.inc"
};

u8 rom_train_net_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_net_tex.inc"
};

u8 rom_train_glass_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_glass_tex.inc"
};

u8 rom_train_light_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_train_in/rom_train_light_tex.inc"
};

Vtx rom_train_in_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_train_in/rom_train_in_v.inc"
};

Gfx rom_train_in_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetEnvColor(100, 230, 255, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_train_glass_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_train_in_v[479], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetEnvColor(255, 255, 120, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, rom_train_light_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_train_in_v[511], 16, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx rom_train_in_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_1_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_train_seat1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_train_in_v[213], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 1, 0, 0, 2, 4),
gsSPNTriangles_5b(3, 0, 4, 5, 6, 7, 5, 7, 8, 9, 10, 6),
gsSPNTriangles_5b(9, 6, 5, 11, 12, 13, 11, 13, 14, 15, 16, 17),
gsSPNTriangles_5b(16, 18, 17, 15, 19, 16, 19, 18, 16, 19, 20, 21),
gsSPNTriangles_5b(19, 21, 18, 22, 23, 24, 22, 24, 25, 25, 24, 26),
gsSPNTriangles_5b(25, 26, 27, 28, 29, 23, 28, 23, 22, 30, 22, 25),
gsSPNTriangles_5b(30, 25, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[245], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 2, 4, 5),
gsSPNTriangles_5b(2, 5, 6, 7, 8, 9, 7, 9, 1, 1, 9, 4),
gsSPNTriangles_5b(1, 4, 2, 10, 11, 12, 10, 12, 13, 14, 10, 13),
gsSPNTriangles_5b(14, 13, 15, 16, 10, 14, 16, 14, 15, 17, 18, 19),
gsSPNTriangles_5b(17, 19, 20, 21, 22, 23, 21, 23, 24, 25, 26, 22),
gsSPNTriangles_5b(25, 22, 21, 27, 28, 29, 27, 30, 28, 28, 31, 29),
gsSPNTriangles_5b(30, 31, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[277], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 5, 8, 6, 5, 7, 8, 7, 9, 10),
gsSPNTriangles_5b(7, 10, 8, 11, 12, 13, 11, 13, 14, 15, 16, 12),
gsSPNTriangles_5b(15, 12, 11, 14, 13, 17, 14, 17, 18, 19, 11, 14),
gsSPNTriangles_5b(19, 14, 20, 21, 22, 23, 21, 23, 24, 25, 26, 27),
gsSPNTriangles_5b(25, 27, 22, 23, 28, 29, 23, 29, 30, 22, 27, 28),
gsSPNTriangles_5b(22, 28, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[308], 11, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(5, 0, 4, 4, 3, 6, 5, 4, 6, 7, 8, 9),
gsSPNTriangles_5b(7, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_3_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, rom_train_net_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&rom_train_in_v[319], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[351], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[383], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[415], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[447], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_1_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_train_seat2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(rom_train_in_v, 32, 0),
gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 8, 10, 8, 12, 9),
gsSPNTriangles_5b(11, 12, 8, 13, 14, 15, 14, 16, 15, 17, 13, 18),
gsSPNTriangles_5b(13, 19, 18, 13, 15, 19, 15, 20, 19, 15, 21, 20),
gsSPNTriangles_5b(22, 23, 24, 25, 22, 24, 25, 24, 26, 27, 25, 26),
gsSPNTriangles_5b(27, 26, 28, 24, 29, 30, 24, 30, 26, 0, 0, 0),
gsSPVertex(&rom_train_in_v[31], 26, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 1, 0, 4, 0, 2),
gsSPNTriangles_5b(4, 3, 0, 5, 6, 7, 5, 7, 8, 6, 9, 7),
gsSPNTriangles_5b(7, 9, 8, 10, 11, 12, 10, 13, 14, 13, 15, 11),
gsSPNTriangles_5b(16, 17, 18, 16, 18, 19, 20, 16, 19, 21, 22, 23),
gsSPNTriangles_5b(23, 22, 24, 21, 23, 25, 23, 24, 25, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_train_2_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_train_wall1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_train_in_v[57], 32, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(4, 5, 3, 4, 6, 5, 6, 7, 5, 5, 8, 9),
gsSPNTriangles_5b(5, 7, 8, 10, 11, 5, 10, 5, 12, 13, 14, 15),
gsSPNTriangles_5b(13, 15, 16, 17, 18, 19, 17, 19, 20, 6, 21, 7),
gsSPNTriangles_5b(21, 22, 7, 23, 24, 25, 23, 25, 26, 27, 28, 22),
gsSPNTriangles_5b(27, 22, 29, 22, 30, 31, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[89], 32, 0),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 0, 4, 5, 6, 7),
gsSPNTriangles_5b(5, 7, 8, 9, 10, 11, 9, 11, 12, 13, 14, 15),
gsSPNTriangles_5b(16, 17, 14, 16, 14, 13, 18, 13, 19, 18, 19, 20),
gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 25, 13, 15, 25, 15, 26),
gsSPNTriangles_5b(27, 28, 29, 27, 29, 30, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[120], 17, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 5, 10, 8, 5, 5, 9, 11),
gsSPNTriangles_5b(5, 11, 12, 13, 5, 12, 13, 12, 14, 15, 13, 14),
gsSPNTriangles_5b(15, 14, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_train_roof_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
gsSPVertex(&rom_train_in_v[137], 15, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(4, 5, 1, 2, 1, 6, 1, 7, 6, 1, 8, 7),
gsSPNTriangles_5b(1, 5, 8, 8, 9, 7, 8, 10, 9, 9, 6, 7),
gsSPNTriangles_5b(9, 11, 6, 11, 9, 12, 9, 13, 12, 9, 14, 13),
gsSPNTriangles_5b(9, 10, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_train_wall2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_train_in_v[152], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 0, 2, 3, 2, 4),
gsSPNTriangles_5b(3, 4, 5, 3, 5, 6, 7, 3, 6, 7, 6, 8),
gsSPNTriangles_5b(9, 10, 11, 10, 12, 11, 10, 13, 12, 13, 14, 12),
gsSPNTriangles_5b(14, 15, 12, 15, 16, 12, 15, 17, 16, 18, 19, 20),
gsSPNTriangles_5b(19, 21, 20, 22, 23, 24, 23, 25, 24, 26, 22, 24),
gsSPNTriangles_5b(20, 27, 24, 20, 28, 27, 27, 26, 24, 21, 28, 20),
gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_train_in_v[184], 10, 0),
gsSPNTrianglesInit_5b(9, 0, 1, 2, 3, 4, 5, 3, 5, 6),
gsSPNTriangles_5b(2, 1, 4, 2, 4, 3, 7, 8, 5, 7, 5, 9),
gsSPNTriangles_5b(9, 5, 4, 9, 4, 1, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_train_floor_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_train_in_v[194], 19, 0),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 0, 5, 4, 3),
gsSPNTriangles_5b(1, 6, 2, 7, 8, 3, 2, 7, 3, 7, 9, 8),
gsSPNTriangles_5b(7, 10, 9, 11, 12, 9, 11, 9, 13, 9, 14, 13),
gsSPNTriangles_5b(9, 10, 14, 10, 15, 14, 10, 16, 15, 13, 14, 17),
gsSPNTriangles_5b(14, 18, 17, 0, 2, 3, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
