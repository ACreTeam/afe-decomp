#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 hat_ab1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_ab1/hat_ab1_pal.inc"
};

u8 hat_ab1_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_ab1/hat_ab1_tex_txt.inc"
};

u8 hat_ab2_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_ab1/hat_ab2_tex_txt.inc"
};

u8 hat_ab3_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_ab1/hat_ab3_tex_txt.inc"
};

Vtx hat_athletic1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/hat_ab1/hat_athletic1_v.inc"
};

Gfx hat_athletic1_body_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, hat_ab1_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hat_ab1_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(hat_athletic1_v, 28, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 1, 6, 7),
gsSPNTriangles_5b(4, 8, 9, 10, 0, 11, 6, 9, 8, 8, 7, 6),
gsSPNTriangles_5b(7, 2, 1, 2, 11, 0, 9, 5, 4, 11, 3, 10),
gsSPNTriangles_5b(5, 10, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, hat_ab2_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(7, 12, 13, 14, 15, 16, 17, 17, 16, 18),
gsSPNTriangles_5b(12, 19, 15, 15, 17, 12, 18, 20, 17, 14, 19, 12),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, hat_ab3_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 21, 22, 23, 24, 21, 23, 25, 26, 23),
gsSPNTriangles_5b(27, 24, 23, 22, 25, 23, 26, 27, 23, 0, 0, 0),
gsSPEndDisplayList(),
};
