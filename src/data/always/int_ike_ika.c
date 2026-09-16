#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 int_ike_ika_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/int_ike_ika/int_ike_ika_pal.inc"
};

u8 act_f43_ika_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/int_ike_ika/act_f43_ika_tex.inc"
};

Vtx act_f43_ika_a_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/int_ike_ika/act_f43_ika_a_v.inc"
};

Gfx act_f43_ika_aT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_ika_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_f43_ika_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_f43_ika_a_v, 11, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(1, 5, 4, 0, 6, 1, 6, 5, 1, 7, 8, 9),
gsSPNTriangles_5b(7, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Vtx act_f43_ika_b_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/int_ike_ika/act_f43_ika_b_v.inc"
};

Gfx act_f43_ika_bT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_ika_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_f43_ika_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_f43_ika_b_v, 11, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(1, 5, 4, 0, 6, 1, 6, 5, 1, 7, 8, 9),
gsSPNTriangles_5b(7, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Vtx act_f43_ika_c_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/int_ike_ika/act_f43_ika_c_v.inc"
};

Gfx act_f43_ika_cT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_ika_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_f43_ika_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_f43_ika_c_v, 11, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(1, 5, 4, 0, 6, 1, 6, 5, 1, 7, 8, 9),
gsSPNTriangles_5b(7, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
