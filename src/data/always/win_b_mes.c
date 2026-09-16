#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 win_b_mes_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_b_mes/win_b_mes_pal.inc"
};

u8 win_b_mes_01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_b_mes/win_b_mes_01_tex.inc"
};

u8 win_b_mes_02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_b_mes/win_b_mes_02_tex.inc"
};

u8 win_b_mes_03_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_b_mes/win_b_mes_03_tex.inc"
};

static u8 lat_tegami_fusen_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_b_mes/lat_tegami_fusen_tex.inc"
};

Vtx win_b_mes_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/win_b_mes/win_b_mes_v.inc"
};

Gfx win_b_mes_win_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, win_b_mes_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, win_b_mes_03_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(win_b_mes_v, 20, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, win_b_mes_02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(12, 4, 5, 6, 4, 7, 5, 8, 9, 10),
gsSPNTriangles_5b(8, 11, 9, 11, 12, 9, 11, 13, 12, 14, 6, 15),
gsSPNTriangles_5b(14, 4, 6, 16, 17, 18, 17, 13, 18, 13, 19, 18),
gsSPNTriangles_5b(13, 11, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx win_b_mes_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, win_b_mes_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, win_b_mes_01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
gsSPVertex(&win_b_mes_v[20], 8, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 4, 1, 5),
gsSPNTriangles_5b(3, 6, 4, 1, 0, 5, 6, 7, 4, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx win_b_mes_senT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, lat_tegami_fusen_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&win_b_mes_v[28], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&win_b_mes_v[60], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&win_b_mes_v[92], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx win_b_mes_mode[] ATTRIBUTE_ALIGN(8) = {
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
gsSPEndDisplayList(),
};

Gfx win_b_mes_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(win_b_mes_mode),
gsSPDisplayList(win_b_mes_win_model),
gsSPDisplayList(win_b_mes_winT_model),
gsSPDisplayList(win_b_mes_senT_model),
gsSPEndDisplayList(),
};
