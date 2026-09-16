#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 int_ike_kajiki_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/int_ike_kajiki/int_ike_kajiki_pal.inc"
};

u8 act_f44_kajiki_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/int_ike_kajiki/act_f44_kajiki_tex.inc"
};

Vtx act_f44_kajiki_a_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/int_ike_kajiki/act_f44_kajiki_a_v.inc"
};

Gfx act_f44_kajiki_aT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_kajiki_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_f44_kajiki_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_f44_kajiki_a_v, 9, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 0, 3, 0, 5),
gsSPNTriangles_5b(1, 6, 2, 1, 7, 6, 1, 8, 7, 1, 4, 8),
gsSPNTriangles_5b(0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Vtx act_f44_kajiki_b_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/int_ike_kajiki/act_f44_kajiki_b_v.inc"
};

Gfx act_f44_kajiki_bT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_kajiki_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_f44_kajiki_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_f44_kajiki_b_v, 9, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 0, 3, 0, 5),
gsSPNTriangles_5b(1, 6, 2, 1, 7, 6, 1, 8, 7, 1, 4, 8),
gsSPNTriangles_5b(0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Vtx act_f44_kajiki_c_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/int_ike_kajiki/act_f44_kajiki_c_v.inc"
};

Gfx act_f44_kajiki_cT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_kajiki_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_f44_kajiki_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_f44_kajiki_c_v, 9, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 0, 3, 0, 5),
gsSPNTriangles_5b(1, 6, 2, 1, 7, 6, 1, 8, 7, 1, 4, 8),
gsSPNTriangles_5b(0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
