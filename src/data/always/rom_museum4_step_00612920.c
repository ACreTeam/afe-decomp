#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 rom_museum4_wall_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_wall_pal.inc"
};

u16 rom_museum4_floor_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_floor_pal.inc"
};

static u16 rom_museum4_step_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_step_pal.inc"
};

static u16 grd_bush_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_bush_pal.inc"
};

u16 grd_cliff_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_cliff_pal.inc"
};

u16 grd_earth_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_earth_pal.inc"
};

u16 rom_m4_pp_bB_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_m4_pp_bB_pal.inc"
};

u16 rom_m4_pp_bA_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_m4_pp_bA_pal.inc"
};

u16 grd_beach_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_beach_pal.inc"
};

static u8 rom_museum4_wallA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_wallA_tex.inc"
};

u8 rom_museum4_wallB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_wallB_tex.inc"
};

u8 rom_museum4_floorA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_floorA_tex.inc"
};

u8 rom_museum4_step_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_step_tex.inc"
};

u8 grd_s_bushB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_s_bushB_tex.inc"
};

static u8 grd_s_cliff_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_s_cliff_tex.inc"
};

static u8 grd_s_earth_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_s_earth_tex.inc"
};

static u8 grd_s_grass_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_s_grass_tex.inc"
};

static u8 grd_s_river_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_s_river_tex.inc"
};

u8 rom_museum4_pp_bB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_pp_bB_tex.inc"
};

u8 rom_museum4_pp_bA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_pp_bA_tex.inc"
};

u8 grd_s_sand_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_00612920/grd_s_sand_tex.inc"
};

Vtx rom_museum4_pp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_museum4_step_00612920/rom_museum4_pp_v.inc"
};

Gfx rom_museum4_pp_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rom_museum4_wallB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_museum4_pp_v[405], 18, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 0, 6, 0, 7, 6, 1, 0, 5, 0, 2, 8),
gsSPNTriangles_5b(0, 8, 7, 9, 10, 11, 10, 12, 11, 13, 14, 9),
gsSPNTriangles_5b(11, 13, 9, 15, 16, 9, 15, 9, 14, 16, 15, 17),
gsSPNTriangles_5b(16, 10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_step_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum4_step_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(rom_museum4_pp_v, 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 1, 4, 2),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsSPVertex(&rom_museum4_pp_v[5], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_museum4_wallA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum4_pp_v[13], 32, 0),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(7, 0, 5, 0, 6, 5, 0, 2, 6, 0, 7, 8),
gsSPNTriangles_5b(0, 8, 1, 9, 10, 11, 10, 12, 11, 13, 12, 14),
gsSPNTriangles_5b(12, 15, 14, 16, 14, 15, 16, 13, 14, 13, 17, 12),
gsSPNTriangles_5b(15, 12, 10, 17, 11, 12, 18, 19, 20, 19, 21, 20),
gsSPNTriangles_5b(4, 22, 5, 22, 23, 5, 24, 25, 26, 27, 26, 28),
gsSPNTriangles_5b(26, 25, 28, 29, 28, 25, 29, 27, 28, 25, 24, 30),
gsSPNTriangles_5b(24, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_v[45], 22, 0),
gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(7, 4, 6, 8, 2, 9, 10, 4, 7, 4, 10, 9),
gsSPNTriangles_5b(11, 9, 10, 11, 8, 9, 12, 13, 14, 13, 15, 14),
gsSPNTriangles_5b(12, 16, 13, 17, 18, 19, 17, 19, 20, 19, 21, 20),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_floor_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum4_floorA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum4_pp_v[67], 25, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 6, 8, 4, 9, 10, 11, 10, 12, 11),
gsSPNTriangles_5b(10, 13, 12, 10, 14, 13, 15, 13, 16, 17, 4, 8),
gsSPNTriangles_5b(17, 18, 4, 7, 19, 6, 19, 1, 6, 15, 16, 20),
gsSPNTriangles_5b(0, 2, 15, 13, 14, 16, 1, 19, 3, 15, 20, 0),
gsSPNTriangles_5b(21, 22, 23, 21, 23, 24, 0, 0, 0, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, grd_cliff_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, grd_s_river_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_v[92], 32, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 3, 5, 6),
gsSPNTriangles_5b(7, 3, 6, 8, 7, 9, 10, 8, 11, 12, 10, 13),
gsSPNTriangles_5b(12, 13, 14, 15, 12, 14, 16, 15, 17, 18, 16, 19),
gsSPNTriangles_5b(20, 18, 21, 20, 21, 22, 23, 20, 22, 24, 23, 22),
gsSPNTriangles_5b(24, 22, 25, 26, 24, 25, 27, 26, 28, 29, 27, 30),
gsSPNTriangles_5b(31, 29, 2, 31, 2, 1, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_v[124], 32, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 0, 4, 5, 3, 6),
gsSPNTriangles_5b(7, 5, 8, 7, 8, 9, 7, 9, 10, 11, 12, 13),
gsSPNTriangles_5b(14, 15, 16, 17, 14, 16, 17, 16, 18, 19, 17, 18),
gsSPNTriangles_5b(19, 18, 20, 21, 19, 20, 21, 20, 22, 23, 22, 24),
gsSPNTriangles_5b(25, 24, 26, 27, 25, 26, 27, 26, 28, 29, 27, 28),
gsSPNTriangles_5b(29, 28, 30, 31, 29, 30, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_v[156], 3, 0),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, grd_beach_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, grd_s_sand_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_v[159], 10, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 0, 2, 3, 2, 4),
gsSPNTriangles_5b(5, 3, 4, 6, 5, 4, 6, 4, 7, 8, 6, 7),
gsSPNTriangles_5b(9, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, grd_cliff_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, grd_s_cliff_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum4_pp_v[169], 32, 0),
gsSPNTrianglesInit_5b(23, 0, 1, 2, 0, 3, 1, 0, 2, 4),
gsSPNTriangles_5b(2, 5, 4, 6, 7, 8, 7, 5, 8, 1, 9, 8),
gsSPNTriangles_5b(9, 6, 8, 10, 11, 12, 10, 13, 11, 14, 15, 16),
gsSPNTriangles_5b(17, 16, 15, 16, 18, 19, 16, 17, 18, 20, 19, 18),
gsSPNTriangles_5b(21, 22, 23, 23, 22, 24, 21, 25, 22, 14, 26, 15),
gsSPNTriangles_5b(20, 27, 19, 28, 23, 29, 4, 5, 21, 30, 19, 31),
gsSPVertex(&rom_museum4_pp_v[201], 32, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 2, 1, 3, 4, 5, 6),
gsSPNTriangles_5b(6, 3, 1, 4, 6, 1, 4, 7, 5, 8, 9, 10),
gsSPNTriangles_5b(2, 3, 11, 12, 10, 9, 13, 14, 15, 16, 12, 17),
gsSPNTriangles_5b(12, 14, 17, 4, 1, 18, 1, 0, 18, 19, 20, 21),
gsSPNTriangles_5b(20, 22, 21, 23, 24, 25, 24, 26, 25, 27, 28, 29),
gsSPNTriangles_5b(27, 30, 28, 28, 31, 29, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_v[233], 32, 0),
gsSPNTrianglesInit_5b(30, 0, 1, 2, 0, 3, 1, 1, 4, 2),
gsSPNTriangles_5b(5, 6, 0, 5, 7, 6, 6, 3, 0, 5, 8, 7),
gsSPNTriangles_5b(7, 8, 9, 8, 10, 9, 8, 11, 10, 11, 12, 10),
gsSPNTriangles_5b(11, 8, 5, 11, 5, 13, 5, 0, 13, 13, 2, 14),
gsSPNTriangles_5b(13, 0, 2, 14, 2, 15, 16, 14, 15, 16, 17, 14),
gsSPNTriangles_5b(18, 19, 20, 21, 22, 19, 21, 23, 22, 22, 20, 19),
gsSPNTriangles_5b(21, 24, 23, 25, 26, 27, 25, 28, 26, 26, 29, 27),
gsSPNTriangles_5b(29, 30, 27, 30, 24, 27, 30, 23, 24, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_v[264], 22, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 4, 3, 5, 4),
gsSPNTriangles_5b(6, 7, 8, 7, 9, 8, 0, 2, 3, 9, 4, 5),
gsSPNTriangles_5b(7, 4, 9, 10, 1, 0, 11, 12, 13, 14, 15, 16),
gsSPNTriangles_5b(17, 18, 19, 17, 19, 20, 17, 20, 21, 17, 21, 2),
gsSPNTriangles_5b(17, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, grd_earth_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, grd_s_earth_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_v[286], 11, 0),
gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 6, 3, 7),
gsSPNTriangles_5b(1, 8, 9, 8, 6, 10, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, grd_s_grass_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum4_pp_v[297], 32, 0),
gsSPNTrianglesInit_5b(23, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 6, 9, 7, 9, 10, 7),
gsSPNTriangles_5b(11, 12, 13, 11, 14, 12, 14, 15, 12, 14, 16, 15),
gsSPNTriangles_5b(17, 18, 19, 18, 20, 19, 18, 21, 20, 21, 22, 20),
gsSPNTriangles_5b(22, 23, 20, 22, 24, 23, 25, 26, 27, 3, 4, 27),
gsSPNTriangles_5b(0, 28, 1, 2, 29, 0, 2, 30, 29, 30, 31, 29),
gsSPVertex(&rom_museum4_pp_v[329], 32, 0),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(3, 5, 2, 3, 6, 5, 3, 7, 6, 3, 8, 7),
gsSPNTriangles_5b(8, 9, 7, 5, 10, 2, 10, 11, 2, 11, 12, 2),
gsSPNTriangles_5b(11, 13, 12, 14, 15, 12, 15, 16, 12, 15, 17, 16),
gsSPNTriangles_5b(17, 18, 16, 18, 19, 16, 18, 20, 19, 20, 21, 19),
gsSPNTriangles_5b(21, 8, 19, 21, 22, 8, 19, 23, 16, 19, 24, 23),
gsSPNTriangles_5b(23, 25, 16, 26, 27, 28, 26, 29, 27, 26, 30, 29),
gsSPNTriangles_5b(26, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_v[361], 15, 0),
gsSPNTrianglesInit_5b(11, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(4, 5, 3, 6, 7, 5, 6, 8, 7, 8, 9, 7),
gsSPNTriangles_5b(10, 11, 9, 10, 12, 11, 12, 13, 11, 13, 14, 11),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, grd_bush_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, grd_s_bushB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_v[376], 11, 0),
gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 0, 4, 5, 6, 7),
gsSPNTriangles_5b(1, 5, 8, 9, 3, 10, 0, 0, 0, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_m4_pp_bA_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_museum4_pp_bA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_v[387], 10, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(3, 5, 4, 5, 6, 4, 6, 7, 4, 6, 8, 7),
gsSPNTriangles_5b(8, 9, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_m4_pp_bB_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_museum4_pp_bB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_v[397], 8, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(5, 4, 3, 6, 7, 5, 6, 5, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
