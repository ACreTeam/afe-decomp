#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 clk_ita_1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_ita/clk_ita_1_tex.inc"
};

u8 clk_ita_2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_ita/clk_ita_2_tex.inc"
};

static u8 clk_etc_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_ita/clk_etc_tex.inc"
};

Vtx clk_body_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/clk_ita/clk_body_v.inc"
};

Gfx clk_etc_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, clk_etc_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(clk_body_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clk_itaT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetEnvColor(120, 60, 30, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, clk_ita_2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&clk_body_v[4], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, clk_ita_1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clk_win_mode[] ATTRIBUTE_ALIGN(8) = {
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_ZB_XLU_SURF | G_RM_ZB_XLU_SURF2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPEndDisplayList(),
};
