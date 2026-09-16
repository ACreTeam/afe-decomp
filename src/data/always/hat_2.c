#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 hat_2_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_2/hat_2_pal.inc"
};

u8 hat_2_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/hat_2/hat_2_tex_txt.inc"
};

Vtx hat_party2_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/hat_2/hat_party2_v.inc"
};

Gfx hat_party2_body_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, hat_2_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, hat_2_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(hat_party2_v, 15, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 1, 3, 2, 4, 0, 2),
gsSPNTriangles_5b(3, 5, 2, 6, 7, 2, 5, 6, 2, 8, 9, 6),
gsSPNTriangles_5b(8, 6, 5, 9, 10, 7, 9, 7, 6, 11, 8, 5),
gsSPNTriangles_5b(11, 5, 3, 12, 13, 0, 12, 0, 4, 14, 11, 3),
gsSPNTriangles_5b(14, 3, 1, 13, 14, 1, 13, 1, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
