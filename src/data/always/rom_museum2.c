#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_museum2_wall_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum2/rom_museum2_wall_pal.inc"
};

u16 rom_museum2_floor_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum2/rom_museum2_floor_pal.inc"
};

u16 rom_museum2_step1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum2/rom_museum2_step1_pal.inc"
};

u8 rom_museum2_wallA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum2/rom_museum2_wallA_tex.inc"
};

u8 rom_museum2_wallB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum2/rom_museum2_wallB_tex.inc"
};

u8 rom_museum2_floorA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum2/rom_museum2_floorA_tex.inc"
};

u8 rom_museum2_step1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum2/rom_museum2_step1_tex.inc"
};

u8 rom_museum2_plate_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum2/rom_museum2_plate_tex.inc"
};

Vtx rom_museum2_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_museum2/rom_museum2_v.inc"
};

Gfx rom_museum2_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPEndDisplayList(),
};

Gfx rom_museum2_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum2_step1_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum2_step1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(rom_museum2_v, 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum2_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum2_wallB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum2_v[5], 25, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 2, 1, 2, 3, 4),
gsSPNTriangles_5b(0, 5, 1, 5, 6, 1, 7, 8, 9, 8, 10, 9),
gsSPNTriangles_5b(4, 3, 11, 3, 12, 11, 6, 5, 13, 5, 14, 13),
gsSPNTriangles_5b(13, 15, 9, 7, 9, 15, 13, 14, 15, 16, 17, 18),
gsSPNTriangles_5b(19, 16, 18, 20, 21, 22, 23, 16, 19, 16, 23, 22),
gsSPNTriangles_5b(24, 22, 23, 24, 20, 22, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum2_wallA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum2_v[30], 25, 0),
gsSPNTrianglesInit_5b(27, 0, 1, 2, 3, 4, 5, 3, 6, 4),
gsSPNTriangles_5b(6, 7, 4, 7, 5, 4, 8, 9, 10, 8, 0, 9),
gsSPNTriangles_5b(0, 2, 9, 2, 10, 9, 11, 12, 6, 11, 13, 12),
gsSPNTriangles_5b(13, 14, 12, 14, 6, 12, 0, 15, 1, 15, 5, 1),
gsSPNTriangles_5b(0, 3, 15, 3, 5, 15, 7, 6, 14, 16, 17, 18),
gsSPNTriangles_5b(19, 18, 20, 18, 17, 20, 21, 20, 17, 21, 19, 20),
gsSPNTriangles_5b(17, 16, 22, 16, 23, 22, 24, 22, 23, 24, 17, 22),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum2_floor_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum2_floorA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum2_v[55], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 0, 4, 3, 1, 0),
gsSPNTriangles_5b(3, 5, 1, 6, 7, 8, 9, 10, 11, 12, 9, 11),
gsSPNTriangles_5b(13, 12, 11, 14, 15, 16, 17, 18, 19, 14, 20, 19),
gsSPNTriangles_5b(18, 14, 19, 21, 22, 23, 24, 25, 23, 24, 26, 27),
gsSPNTriangles_5b(24, 23, 26, 28, 0, 2, 28, 29, 0, 29, 28, 7),
gsSPNTriangles_5b(28, 8, 7, 29, 4, 0, 12, 13, 29, 15, 30, 16),
gsSPNTriangles_5b(15, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum2_v[87], 27, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 2, 3, 4, 2, 5, 3),
gsSPNTriangles_5b(2, 1, 5, 5, 6, 7, 8, 9, 0, 10, 11, 12),
gsSPNTriangles_5b(10, 13, 11, 13, 14, 11, 14, 15, 11, 16, 13, 10),
gsSPNTriangles_5b(14, 13, 17, 18, 19, 20, 18, 21, 19, 18, 22, 21),
gsSPNTriangles_5b(18, 4, 22, 23, 21, 24, 25, 21, 22, 26, 11, 18),
gsSPNTriangles_5b(11, 2, 18, 26, 12, 11, 2, 11, 15, 26, 18, 20),
gsSPNTriangles_5b(18, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum2_step1_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_museum2_plate_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum2_v[114], 32, 0),
gsSPNTrianglesInit_5b(30, 0, 1, 2, 0, 2, 3, 2, 4, 5),
gsSPNTriangles_5b(2, 5, 3, 1, 6, 4, 1, 4, 2, 0, 7, 6),
gsSPNTriangles_5b(0, 6, 1, 8, 9, 10, 8, 10, 11, 11, 10, 12),
gsSPNTriangles_5b(11, 12, 13, 13, 12, 14, 13, 14, 15, 8, 11, 13),
gsSPNTriangles_5b(8, 13, 15, 16, 17, 18, 16, 18, 19, 18, 20, 21),
gsSPNTriangles_5b(18, 21, 19, 17, 22, 20, 17, 20, 18, 16, 23, 22),
gsSPNTriangles_5b(16, 22, 17, 24, 25, 26, 24, 26, 27, 27, 26, 28),
gsSPNTriangles_5b(27, 28, 29, 24, 27, 29, 24, 29, 30, 0, 0, 0),
gsSPVertex(&rom_museum2_v[145], 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 0, 6, 4, 0, 4, 1, 7, 8, 9),
gsSPNTriangles_5b(7, 9, 10, 10, 9, 11, 10, 11, 12, 7, 10, 12),
gsSPNTriangles_5b(7, 12, 13, 14, 15, 16, 14, 16, 17, 17, 16, 18),
gsSPNTriangles_5b(17, 18, 19, 20, 14, 17, 20, 17, 19, 21, 22, 23),
gsSPNTriangles_5b(21, 23, 24, 23, 25, 26, 23, 26, 24, 22, 27, 25),
gsSPNTriangles_5b(22, 25, 23, 28, 29, 30, 28, 30, 31, 0, 0, 0),
gsSPVertex(&rom_museum2_v[177], 32, 0),
gsSPNTrianglesInit_5b(30, 0, 1, 2, 0, 2, 3, 3, 2, 4),
gsSPNTriangles_5b(3, 4, 5, 6, 0, 3, 6, 3, 5, 7, 8, 9),
gsSPNTriangles_5b(7, 9, 10, 9, 11, 12, 9, 12, 10, 8, 13, 11),
gsSPNTriangles_5b(8, 11, 9, 7, 14, 13, 7, 13, 8, 15, 16, 17),
gsSPNTriangles_5b(15, 17, 18, 18, 17, 19, 18, 19, 20, 20, 19, 21),
gsSPNTriangles_5b(20, 21, 22, 15, 18, 20, 15, 20, 22, 23, 24, 25),
gsSPNTriangles_5b(23, 25, 26, 25, 27, 28, 25, 28, 26, 24, 29, 27),
gsSPNTriangles_5b(24, 27, 25, 23, 30, 29, 23, 29, 24, 0, 0, 0),
gsSPVertex(&rom_museum2_v[208], 32, 0),
gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 2, 3, 3, 2, 4),
gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 0, 3, 5),
gsSPNTriangles_5b(0, 5, 7, 8, 9, 10, 8, 10, 11, 10, 12, 13),
gsSPNTriangles_5b(10, 13, 11, 9, 14, 12, 9, 12, 10, 8, 15, 14),
gsSPNTriangles_5b(8, 14, 9, 16, 17, 18, 16, 18, 19, 19, 18, 20),
gsSPNTriangles_5b(19, 20, 21, 21, 20, 22, 21, 22, 23, 16, 19, 21),
gsSPNTriangles_5b(16, 21, 23, 24, 25, 26, 24, 26, 27, 26, 28, 29),
gsSPNTriangles_5b(26, 29, 27, 25, 30, 28, 25, 28, 26, 24, 31, 30),
gsSPNTriangles_5b(24, 30, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum2_v[240], 32, 0),
gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 2, 3, 3, 2, 4),
gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 0, 3, 5),
gsSPNTriangles_5b(0, 5, 7, 8, 9, 10, 8, 10, 11, 10, 12, 13),
gsSPNTriangles_5b(10, 13, 11, 9, 14, 12, 9, 12, 10, 8, 15, 14),
gsSPNTriangles_5b(8, 14, 9, 16, 17, 18, 16, 18, 19, 18, 20, 21),
gsSPNTriangles_5b(18, 21, 19, 17, 22, 20, 17, 20, 18, 16, 23, 22),
gsSPNTriangles_5b(16, 22, 17, 24, 25, 26, 24, 26, 27, 27, 26, 28),
gsSPNTriangles_5b(27, 28, 29, 29, 28, 30, 29, 30, 31, 24, 27, 29),
gsSPNTriangles_5b(24, 29, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
