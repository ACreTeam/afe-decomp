#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_museum5_on_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_on_pal.inc"
};

static u16 rom_museum5_wall_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_wall_pal.inc"
};

u16 rom_museum5_floor_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_floor_pal.inc"
};

u16 rom_museum5_step_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_step_pal.inc"
};

u8 rom_museum5_ki_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_ki_tex.inc"
};

static u8 rom_museum5_wallA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_wallA_tex.inc"
};

u8 rom_museum5_floor_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_floor_tex.inc"
};

u8 rom_museum5_step_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_step_tex.inc"
};

u8 rom_museum5_isi_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_isi_tex.inc"
};

u8 rom_museum5_plate_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum5/rom_museum5_plate_tex.inc"
};

Vtx rom_museum5_pp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_museum5/rom_museum5_pp_v.inc"
};

Gfx rom_museum5_pp_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPEndDisplayList(),
};

Gfx rom_museum5_pp_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum5_step_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_museum5_plate_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_museum5_pp_v[196], 24, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsSPVertex(rom_museum5_pp_v, 12, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 5, 8, 6, 9, 10, 11, 11, 2, 1),
gsSPNTriangles_5b(9, 11, 1, 7, 4, 0, 4, 3, 0, 0, 0, 0),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum5_step_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum5_pp_v[12], 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum5_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum5_wallA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum5_pp_v[17], 32, 0),
gsSPNTrianglesInit_5b(32, 0, 1, 2, 3, 4, 5, 6, 3, 5),
gsSPNTriangles_5b(6, 5, 7, 1, 7, 5, 1, 8, 7, 0, 8, 1),
gsSPNTriangles_5b(9, 10, 11, 9, 11, 12, 13, 9, 12, 13, 14, 15),
gsSPNTriangles_5b(9, 13, 15, 15, 14, 16, 15, 16, 17, 9, 18, 10),
gsSPNTriangles_5b(9, 19, 18, 19, 20, 18, 21, 2, 22, 23, 21, 22),
gsSPNTriangles_5b(22, 2, 1, 23, 22, 1, 5, 4, 24, 23, 5, 24),
gsSPNTriangles_5b(25, 23, 24, 25, 24, 4, 23, 1, 5, 9, 15, 19),
gsSPNTriangles_5b(15, 26, 19, 26, 27, 19, 15, 17, 26, 26, 17, 27),
gsSPNTriangles_5b(28, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum5_pp_v[48], 9, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 4, 3, 2),
gsSPNTriangles_5b(4, 2, 1, 3, 5, 0, 3, 6, 7, 7, 8, 5),
gsSPNTriangles_5b(3, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum5_floor_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum5_floor_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum5_pp_v[57], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(7, 4, 8, 5, 7, 9, 5, 4, 7, 10, 11, 12),
gsSPNTriangles_5b(13, 14, 15, 16, 13, 15, 17, 16, 15, 3, 18, 19),
gsSPNTriangles_5b(20, 1, 0, 3, 21, 2, 22, 23, 24, 25, 26, 24),
gsSPNTriangles_5b(25, 27, 28, 25, 24, 27, 29, 7, 8, 29, 30, 7),
gsSPNTriangles_5b(30, 29, 11, 29, 12, 11, 30, 9, 7, 16, 17, 30),
gsSPNTriangles_5b(18, 31, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum5_pp_v[89], 26, 0),
gsSPNTrianglesInit_5b(23, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(1, 5, 6, 7, 8, 1, 9, 10, 11, 9, 12, 10),
gsSPNTriangles_5b(12, 13, 10, 13, 14, 10, 15, 12, 9, 13, 12, 16),
gsSPNTriangles_5b(17, 18, 19, 17, 20, 18, 17, 21, 20, 17, 4, 21),
gsSPNTriangles_5b(22, 20, 23, 24, 20, 21, 25, 10, 17, 10, 2, 17),
gsSPNTriangles_5b(25, 11, 10, 2, 10, 14, 25, 17, 19, 17, 2, 4),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum5_on_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_museum5_isi_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum5_pp_v[115], 32, 0),
gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 2, 3, 4, 2, 1),
gsSPNTriangles_5b(4, 1, 5, 6, 7, 8, 6, 8, 9, 10, 11, 12),
gsSPNTriangles_5b(13, 10, 12, 12, 11, 1, 12, 1, 0, 5, 1, 14),
gsSPNTriangles_5b(14, 7, 6, 5, 14, 6, 12, 0, 3, 13, 12, 3),
gsSPNTriangles_5b(4, 5, 6, 4, 6, 9, 15, 16, 17, 18, 19, 15),
gsSPNTriangles_5b(18, 15, 17, 20, 21, 22, 23, 24, 20, 23, 20, 22),
gsSPNTriangles_5b(25, 19, 18, 22, 21, 25, 22, 25, 18, 26, 23, 22),
gsSPNTriangles_5b(26, 22, 18, 26, 18, 17, 27, 28, 29, 28, 30, 29),
gsSPNTriangles_5b(31, 28, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum5_pp_v[147], 9, 0),
gsSPNTrianglesInit_5b(7, 0, 1, 2, 2, 3, 4, 3, 5, 4),
gsSPNTriangles_5b(2, 1, 3, 6, 7, 8, 6, 4, 7, 4, 5, 7),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, rom_museum5_ki_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum5_pp_v[156], 32, 0),
gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 5, 8, 9, 10, 11, 12, 10, 13, 11),
gsSPNTriangles_5b(8, 12, 9, 8, 10, 12, 9, 12, 14, 15, 10, 8),
gsSPNTriangles_5b(15, 16, 10, 17, 18, 19, 20, 21, 22, 20, 22, 23),
gsSPNTriangles_5b(23, 22, 18, 23, 18, 17, 22, 24, 25, 22, 25, 18),
gsSPNTriangles_5b(26, 23, 17, 26, 27, 28, 29, 26, 28, 0, 0, 0),
gsSPVertex(&rom_museum5_pp_v[186], 10, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(3, 2, 5, 3, 5, 4, 2, 7, 8, 2, 8, 5),
gsSPNTriangles_5b(9, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
