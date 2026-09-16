#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_museum1_mado_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_mado_pal.inc"
};

u16 rom_museum1_step_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_step_pal.inc"
};

u16 rom_museum1_floor_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_floor_pal.inc"
};

u16 rom_museum1_wall_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_wall_pal.inc"
};

u8 rom_museum1_mado1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_mado1_tex.inc"
};

u8 rom_museum1_step1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_step1_tex.inc"
};

u8 rom_museum1_step2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_step2_tex.inc"
};

u8 rom_museum1_floorA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_floorA_tex.inc"
};

u8 rom_museum1_floorB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_floorB_tex.inc"
};

u8 rom_museum1_mado2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_mado2_tex.inc"
};

u8 rom_museum1_sign1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_sign1_tex.inc"
};

u8 rom_museum1_wallA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_wallA_tex.inc"
};

u8 rom_museum1_wallB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_wallB_tex.inc"
};

u8 rom_museum1_sign2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_sign2_tex.inc"
};

u8 rom_museum1_sign3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_sign3_tex.inc"
};

u8 rom_museum1_sign4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum1/rom_museum1_sign4_tex.inc"
};

Vtx rom_museum1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_museum1/rom_museum1_v.inc"
};

Gfx rom_museum1_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 1, 0, PRIM_LOD_FRAC, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_mado_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum1_mado2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_museum1_v[268], 16, 0),
gsSPNTriangles(8, 0, 1, 2, 3, 4, 5, 3, 5, 6),
gsSPNTriangles_5b(0, 2, 7, 8, 9, 10, 11, 12, 13, 8, 10, 14),
gsSPNTriangles_5b(11, 13, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum1_mado1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum1_v[284], 16, 0),
gsSPNTriangles(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(7, 8, 9, 10, 11, 12, 13, 4, 6, 14, 7, 9),
gsSPNTriangles_5b(11, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx rom_museum1_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(rom_museum1_v, 16, 0),
gsSPNTriangles(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_step_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_museum1_sign4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum1_v[16], 20, 0),
gsSPNTriangles(3, 0, 1, 2, 0, 3, 4, 0, 2, 3),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_museum1_sign3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTriangles(3, 5, 6, 7, 7, 8, 9, 5, 7, 9),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_museum1_sign2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTriangles(3, 10, 11, 12, 12, 13, 10, 10, 14, 11),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_museum1_sign1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTriangles(3, 15, 16, 17, 17, 18, 15, 15, 19, 16),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_museum1_step2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum1_v[36], 27, 0),
gsSPNTriangles(14, 0, 1, 2, 2, 3, 4, 4, 5, 2),
gsSPNTriangles_5b(5, 0, 2, 6, 7, 8, 6, 9, 7, 8, 10, 6),
gsSPNTriangles_5b(6, 11, 9, 12, 13, 14, 15, 16, 12, 12, 14, 15),
gsSPNTriangles_5b(17, 18, 19, 19, 20, 17, 17, 21, 18, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum1_step1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTriangles(3, 22, 23, 24, 24, 25, 22, 22, 26, 23),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum1_wallA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum1_v[63], 32, 0),
gsSPNTriangles(24, 0, 1, 2, 3, 4, 5, 6, 0, 7),
gsSPNTriangles_5b(4, 8, 9, 10, 6, 7, 8, 11, 9, 12, 2, 1),
gsSPNTriangles_5b(5, 13, 3, 2, 14, 0, 4, 15, 5, 0, 16, 7),
gsSPNTriangles_5b(17, 4, 9, 18, 19, 14, 20, 15, 21, 15, 4, 21),
gsSPNTriangles_5b(22, 23, 17, 23, 4, 17, 24, 25, 16, 0, 24, 16),
gsSPNTriangles_5b(19, 0, 14, 26, 10, 7, 0, 19, 24, 12, 27, 2),
gsSPNTriangles_5b(28, 29, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum1_v[94], 18, 0),
gsSPNTriangles(11, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(4, 2, 1, 3, 5, 6, 5, 7, 6, 3, 8, 5),
gsSPNTriangles_5b(8, 7, 5, 9, 10, 11, 12, 13, 14, 15, 16, 17),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum1_wallB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum1_v[112], 32, 0),
gsSPNTriangles(21, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
gsSPNTriangles_5b(13, 15, 14, 8, 16, 9, 8, 17, 16, 17, 18, 16),
gsSPNTriangles_5b(17, 19, 18, 20, 11, 9, 21, 22, 23, 22, 24, 23),
gsSPNTriangles_5b(14, 15, 25, 22, 12, 24, 12, 14, 24, 26, 27, 28),
gsSPNTriangles_5b(29, 26, 28, 29, 28, 30, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum1_v[143], 32, 0),
gsSPNTriangles(20, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 5, 8, 7, 9, 0, 2, 10, 11, 12),
gsSPNTriangles_5b(10, 13, 11, 13, 14, 11, 15, 16, 17, 18, 15, 17),
gsSPNTriangles_5b(15, 19, 16, 20, 21, 22, 23, 20, 22, 23, 22, 24),
gsSPNTriangles_5b(25, 23, 24, 25, 26, 27, 28, 26, 25, 28, 25, 24),
gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum1_v[175], 8, 0),
gsSPNTriangles(6, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(4, 3, 5, 6, 4, 5, 6, 5, 7, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_floor_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum1_floorB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum1_v[183], 32, 0),
gsSPNTriangles(20, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 8, 9, 7, 10, 11, 12),
gsSPNTriangles_5b(10, 13, 11, 11, 14, 12, 15, 16, 17, 16, 18, 17),
gsSPNTriangles_5b(16, 19, 18, 20, 21, 22, 20, 23, 21, 24, 25, 26),
gsSPNTriangles_5b(24, 27, 25, 20, 22, 28, 26, 29, 24, 3, 30, 4),
gsSPNTriangles_5b(14, 31, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum1_v[215], 10, 0),
gsSPNTriangles(4, 0, 1, 2, 3, 4, 5, 6, 7, 8),
gsSPNTriangles_5b(7, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_museum1_floorA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum1_v[225], 27, 0),
gsSPNTriangles(16, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 9, 11, 12, 13, 14, 15),
gsSPNTriangles_5b(16, 13, 17, 6, 18, 7, 19, 20, 21, 22, 19, 21),
gsSPNTriangles_5b(22, 21, 14, 23, 24, 25, 23, 26, 24, 10, 9, 12),
gsSPNTriangles_5b(17, 13, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum1_v[252], 16, 0),
gsSPNTriangles(12, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(5, 6, 1, 7, 6, 5, 5, 1, 0, 8, 9, 10),
gsSPNTriangles_5b(8, 11, 9, 8, 10, 12, 12, 10, 13, 10, 14, 13),
gsSPNTriangles_5b(13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
