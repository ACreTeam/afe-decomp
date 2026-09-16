#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 kei_win_hyouji1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_hyouji1_tex.inc"
};

u8 kei_win_hyouji2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_hyouji2_tex.inc"
};

u8 kei_win_hyouji3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_hyouji3_tex.inc"
};

u8 kei_win_hyouji4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_hyouji4_tex.inc"
};

u8 kei_win_yaji2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_yaji2_tex.inc"
};

static u8 std_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/std_tex.inc"
};

static u8 yaji[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/yaji.inc"
};

static u8 ct_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/ct_tex.inc"
};

u8 kei_win_st1_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_st1_tex_rgb_ia8.inc"
};

u8 kei_win_st2_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_st2_tex_rgb_ia8.inc"
};

u8 kei_win_st3_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_st3_tex_rgb_ia8.inc"
};

u8 kei_win_st4_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_st4_tex_rgb_ia8.inc"
};

u8 kei_win_st5_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_st5_tex_rgb_ia8.inc"
};

u8 kei_win_st6_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_st6_tex_rgb_ia8.inc"
};

u8 lat_tegami_b2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/lat_tegami_b2_tex.inc"
};

static u8 lat_tegami_b3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/lat_tegami_b3_tex.inc"
};

u8 kei_win_2b1_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kei_win_hyouji1/kei_win_2b1_tex_rgb_i4.inc"
};

Vtx kei_hyouji_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/kei_win_hyouji1/kei_hyouji_v.inc"
};

Gfx kei_win_bt_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, lat_tegami_b2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, kei_win_2b1_tex_rgb_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(kei_hyouji_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_b2_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, lat_tegami_b3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, kei_win_2b1_tex_rgb_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&kei_hyouji_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_cbt_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 215, 0, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, yaji),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kei_hyouji_v[8], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_3D_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(0, 0, 0, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, std_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kei_hyouji_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_cmoji_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(185, 100, 50, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, kei_win_hyouji2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kei_hyouji_v[20], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, kei_win_hyouji1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_bmoji_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(155, 0, 0, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, kei_win_hyouji3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kei_hyouji_v[28], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_amoji_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(30, 130, 55, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, kei_win_hyouji4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kei_hyouji_v[32], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_st_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 215, 215, 215, 255),
gsDPSetEnvColor(50, 50, 50, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kei_hyouji_v[36], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_cb_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 195, 50, 255),
gsDPSetEnvColor(70, 70, 50, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, ct_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kei_hyouji_v[40], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_yaji1T_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 165, 255, 255),
gsDPSetEnvColor(70, 0, 0, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kei_win_yaji2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kei_hyouji_v[44], 8, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_yaji1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};

Gfx kei_win_yaji2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx kei_hyouji_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPEndDisplayList(),
};

Gfx kei_hyouji_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(kei_hyouji_mode),
gsDPPipeSync(),
gsDPSetCycleType(G_CYC_2CYCLE),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_CLD_SURF2),
gsSPDisplayList(kei_win_bt_model),
gsSPDisplayList(kei_win_b2_model),
gsDPPipeSync(),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPDisplayList(kei_win_cbt_model),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsSPDisplayList(kei_win_3D_model),
gsSPDisplayList(kei_win_cb_model),
gsSPDisplayList(kei_win_cmoji_model),
gsSPDisplayList(kei_win_bmoji_model),
gsSPDisplayList(kei_win_amoji_model),
gsSPEndDisplayList(),
};
