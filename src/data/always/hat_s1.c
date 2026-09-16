#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 hat_s1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_s1/hat_s1_pal.inc"
};

u8 hat_s1_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_s1/hat_s1_tex_txt.inc"
};

Vtx hat_christmas1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/hat_s1/hat_christmas1_v.inc"
};

Gfx hat_christmas1_body_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, hat_s1_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hat_s1_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(hat_christmas1_v, 22, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 0, 2),
gsSPNTriangles_5b(3, 5, 2, 6, 7, 2, 5, 6, 2, 0, 0, 0),
gsSPNTrianglesInit_5b(24, 8, 9, 10, 9, 8, 11, 9, 11, 12),
gsSPNTriangles_5b(12, 11, 13, 14, 8, 10, 8, 14, 15, 8, 15, 11),
gsSPNTriangles_5b(11, 15, 13, 16, 14, 10, 14, 16, 17, 14, 17, 15),
gsSPNTriangles_5b(15, 17, 13, 18, 16, 10, 16, 18, 19, 16, 19, 17),
gsSPNTriangles_5b(17, 19, 13, 20, 18, 10, 18, 20, 21, 18, 21, 19),
gsSPNTriangles_5b(19, 21, 13, 9, 20, 10, 20, 9, 12, 20, 12, 21),
gsSPNTriangles_5b(21, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
