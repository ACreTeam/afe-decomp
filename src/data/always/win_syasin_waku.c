#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 win_syasin_waku_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_syasin_waku/win_syasin_waku_pal.inc"
};

u8 win_syasin_waku_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_syasin_waku/win_syasin_waku_tex.inc"
};

Vtx win_syasin_01_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/win_syasin_waku/win_syasin_01_v.inc"
};

Gfx win_syasin_shadow_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 40, 40, 60, 120),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
gsSPVertex(win_syasin_01_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx win_syasin_waku_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, win_syasin_waku_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, win_syasin_waku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&win_syasin_01_v[4], 24, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 5, 8, 7, 8, 9, 7, 3, 10, 1),
gsSPNTriangles_5b(3, 11, 10, 12, 13, 14, 12, 15, 13, 16, 17, 18),
gsSPNTriangles_5b(17, 19, 18, 20, 5, 21, 20, 8, 5, 17, 22, 19),
gsSPNTriangles_5b(22, 23, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx win_syasin_base_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_16b, 640, 480, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&win_syasin_01_v[28], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx win_syasin_mode[] ATTRIBUTE_ALIGN(8) = {
gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_OPA_SURF2),
gsSPEndDisplayList(),
};

Gfx win_syasin_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(win_syasin_shadow_model),
gsSPDisplayList(win_syasin_waku_model),
gsSPEndDisplayList(),
};
