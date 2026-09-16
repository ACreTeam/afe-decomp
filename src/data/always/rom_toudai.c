#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_toudai_yuka_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_yuka_pal.inc"
};

u16 rom_toudai_kabe_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_kabe_pal.inc"
};

u16 rom_toudai_step_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_step_pal.inc"
};

u16 rom_toudai_meka_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_meka_pal.inc"
};

u16 rom_toudai_ukiwa_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_ukiwa_pal.inc"
};

u8 rom_toudai_yuka_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_yuka_tex.inc"
};

u8 rom_toudai_kabeA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_kabeA_tex.inc"
};

u8 rom_toudai_kabeB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_kabeB_tex.inc"
};

u8 rom_toudai_step_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_step_tex.inc"
};

u8 rom_toudai_mekaA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_mekaA_tex.inc"
};

u8 rom_toudai_ukiwa_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_ukiwa_tex.inc"
};

u8 rom_toudai_kage1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_kage1_tex.inc"
};

u8 rom_toudai_mekaC_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_mekaC_tex.inc"
};

u8 rom_toudai_kage2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_toudai/rom_toudai_kage2_tex.inc"
};

Vtx rom_toudai_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_toudai/rom_toudai_v.inc"
};

Gfx rom_toudai_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPEndDisplayList(),
};

Gfx rom_toudai_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_meka_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_toudai_mekaC_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_toudai_v[66], 11, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 0, 4, 5),
gsSPNTriangles_5b(0, 6, 4, 7, 8, 9, 8, 10, 9, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_toudai_mekaA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_toudai_v[77], 22, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 8, 11),
gsSPNTriangles_5b(20, 11, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_ukiwa_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_toudai_ukiwa_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_toudai_v[99], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_yuka_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_toudai_yuka_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(rom_toudai_v, 19, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 4, 1, 0, 5),
gsSPNTriangles_5b(2, 6, 0, 0, 4, 7, 0, 8, 3, 9, 10, 0),
gsSPNTriangles_5b(10, 11, 0, 11, 12, 0, 12, 13, 0, 14, 15, 0),
gsSPNTriangles_5b(15, 16, 0, 16, 17, 0, 17, 18, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_step_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_toudai_step_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_toudai_v[19], 8, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 0, 2, 4, 3, 2),
gsSPNTriangles_5b(5, 4, 2, 6, 4, 5, 0, 7, 1, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_toudai_kabe_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_toudai_kabeB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&rom_toudai_v[27], 31, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(5, 4, 3, 6, 7, 8, 9, 6, 8, 10, 11, 8),
gsSPNTriangles_5b(10, 8, 12, 9, 13, 14, 9, 14, 15, 16, 12, 15),
gsSPNTriangles_5b(14, 16, 15, 11, 13, 9, 8, 11, 9, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_toudai_kabeA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(12, 17, 18, 19, 20, 17, 19, 21, 22, 23),
gsSPNTriangles_5b(24, 21, 23, 25, 26, 27, 25, 27, 28, 24, 26, 25),
gsSPNTriangles_5b(21, 24, 25, 29, 23, 22, 29, 22, 30, 18, 17, 28),
gsSPNTriangles_5b(18, 28, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 110, 0, 0, 30, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_toudai_kage2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_toudai_v[58], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_toudai_kage1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
gsSPEndDisplayList(),
};
