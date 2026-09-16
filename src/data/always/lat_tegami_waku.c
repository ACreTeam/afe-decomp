#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 lat_tegami_waku_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/lat_tegami_waku/lat_tegami_waku_tex.inc"
};

Vtx lat_kakunin_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_tegami_waku/lat_kakunin_v.inc"
};

Gfx lat_kakunin_DL_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_AA_TEX_EDGE | G_RM_AA_TEX_EDGE2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPEndDisplayList(),
};

Gfx lat_kakunin_c_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPVertex(lat_kakunin_v, 3, 0),
gsSP1Triangle(0, 1, 2, 0),
gsSPEndDisplayList(),
};

Gfx lat_kakunin_wakuT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 255, 200, 255),
gsDPSetEnvColor(255, 60, 0, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, lat_tegami_waku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_kakunin_v[3], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};
