#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 hat_hg1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_hg1/hat_hg1_pal.inc"
};

u8 hat_hg2_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_hg1/hat_hg2_tex_txt.inc"
};

u8 hat_hg1_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_hg1/hat_hg1_tex_txt.inc"
};

u8 hat_hg3_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_hg1/hat_hg3_tex_txt.inc"
};

u8 hat_hg4_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_hg1/hat_hg4_tex_txt.inc"
};

u8 hat_hg5_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_hg1/hat_hg5_tex_txt.inc"
};

Vtx hat_harvest2_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/hat_hg1/hat_harvest2_v.inc"
};

Gfx hat_harvest2_body_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, hat_hg1_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hat_hg2_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(hat_harvest2_v, 30, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 2, 5, 6, 7),
gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 0, 2, 16),
gsSPNTriangles_5b(13, 12, 14, 14, 16, 13, 10, 9, 11, 8, 10, 7),
gsSPNTriangles_5b(4, 3, 5, 7, 4, 5, 2, 1, 17, 2, 17, 3),
gsSPNTriangles_5b(16, 15, 0, 7, 6, 8, 13, 10, 11, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hat_hg1_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(12, 18, 19, 20, 21, 18, 22, 23, 24, 25),
gsSPNTriangles_5b(20, 22, 18, 26, 20, 19, 25, 26, 23, 27, 25, 24),
gsSPNTriangles_5b(28, 27, 29, 19, 23, 26, 24, 29, 27, 22, 28, 21),
gsSPNTriangles_5b(29, 21, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hat_hg3_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&hat_harvest2_v[30], 29, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 2, 5, 3, 2),
gsSPNTriangles_5b(6, 0, 2, 1, 5, 2, 4, 6, 2, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hat_hg4_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 7, 8, 9, 10, 8, 7, 9, 11, 7),
gsSPNTriangles_5b(9, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 13, 14, 15, 16, 14, 13, 15, 17, 13),
gsSPNTriangles_5b(15, 14, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hat_hg5_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 19, 20, 21, 22, 19, 21, 20, 23, 21),
gsSPNTriangles_5b(23, 22, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 24, 25, 26, 27, 24, 26, 25, 28, 26),
gsSPNTriangles_5b(28, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hat_hg4_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&hat_harvest2_v[59], 18, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 1, 3, 3, 1, 4),
gsSPNTriangles_5b(3, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 6, 7, 8, 8, 7, 9, 9, 7, 10),
gsSPNTriangles_5b(9, 11, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 12, 13, 14, 14, 13, 15, 15, 13, 16),
gsSPNTriangles_5b(15, 17, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
