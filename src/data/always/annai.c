#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 annai[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/annai.inc"
};

u8 kan_win_waku2a_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_waku2a_tex.inc"
};

u8 kan_win_w1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_w1_tex.inc"
};

u8 kan_win_w2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_w2_tex.inc"
};

u8 kan_win_w3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_w3_tex.inc"
};

u8 kan_win_suuji1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji1_tex.inc"
};

u8 kan_win_saki_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_saki_tex.inc"
};

u8 kan_win_ga_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_ga_tex.inc"
};

u8 kan_win_ga2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_ga2_tex.inc"
};

u8 kan_win_suuji2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji2_tex.inc"
};

u8 kan_win_suuji3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji3_tex.inc"
};

u8 kan_win_moji2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_moji2_tex.inc"
};

u8 kan_win_moji3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_moji3_tex.inc"
};

u8 kan_win_suuji4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji4_tex.inc"
};

u8 kan_win_suuji5_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji5_tex.inc"
};

u8 kan_win_suuji6_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji6_tex.inc"
};

u8 kan_win_ga3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_ga3_tex.inc"
};

u8 kan_win_ga4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_ga4_tex.inc"
};

u8 kan_win_suuji1_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji1_tex_rgb_ia8.inc"
};

u8 kan_win_suuji2_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji2_tex_rgb_ia8.inc"
};

u8 kan_win_suuji3_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji3_tex_rgb_ia8.inc"
};

u8 kan_win_suuji4_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji4_tex_rgb_ia8.inc"
};

u8 kan_win_suuji5_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji5_tex_rgb_ia8.inc"
};

u8 kan_win_suuji6_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/annai/kan_win_suuji6_tex_rgb_ia8.inc"
};

Vtx kan_win_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/annai/kan_win_v.inc"
};

Gfx kan_win_kiwakuT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(anime_4_txt),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kan_win_w3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(kan_win_v, 27, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 1, 0, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 1, 8, 9, 9, 8, 10, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, kan_win_w2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 11, 12, 13, 11, 13, 14, 15, 16, 17),
gsSPNTriangles_5b(15, 18, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 128, 32, kan_win_w1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 19, 20, 21, 20, 22, 21, 23, 24, 25),
gsSPNTriangles_5b(26, 23, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_futiT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(anime_4_txt + 0x18),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_ga4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&kan_win_v[27], 16, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 0, 3, 0, 4, 3),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_ga3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(1, 5, 6, 7, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_ga2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_ga_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(3, 11, 12, 13, 12, 14, 13, 11, 15, 12),
gsSPEndDisplayList(),
};

Gfx kan_win_futi2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(anime_4_txt + 0x30),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_ga4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&kan_win_v[43], 16, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 4, 2, 1),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_ga3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(3, 5, 6, 7, 5, 7, 8, 8, 7, 9),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_ga2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(1, 10, 11, 12, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_ga_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(1, 13, 14, 15, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_moji1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(anime_4_txt + 0x48),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, annai),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kan_win_v[59], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_wakuT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(anime_4_txt + 0x58),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, kan_win_waku2a_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kan_win_v[67], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_ban2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 60, 100, 60, 255),
gsDPSetEnvColor(100, 255, 80, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&kan_win_v[71], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_banT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 60, 100, 60, 255),
gsDPSetEnvColor(100, 255, 80, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji5_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kan_win_v[75], 20, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 8, 9, 10, 11, 8, 10, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 12, 13, 14, 15, 12, 14, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 16, 17, 18, 17, 19, 18, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_tyouT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 60, 80, 130, 255),
gsDPSetEnvColor(70, 240, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji6_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kan_win_v[95], 24, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji5_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 8, 9, 10, 11, 8, 10, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 12, 13, 14, 13, 15, 14, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 16, 17, 18, 17, 19, 18, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kan_win_suuji1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 20, 21, 22, 21, 23, 22, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_tyou2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 60, 80, 130, 255),
gsDPSetEnvColor(70, 240, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, anime_2_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&kan_win_v[119], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_sakiT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(anime_4_txt + 0x58),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, kan_win_saki_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kan_win_v[123], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_moji2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(anime_4_txt + 0x70),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, kan_win_moji3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&kan_win_v[127], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, kan_win_moji2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx kan_win_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsSPEndDisplayList(),
};

Gfx kan_win_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(kan_win_mode),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsSPDisplayList(kan_win_kiwakuT_model),
gsSPEndDisplayList(),
};

Gfx kan_win_model2[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(kan_win_mode),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsSPDisplayList(kan_win_futiT_model),
gsSPDisplayList(kan_win_futi2T_model),
gsSPDisplayList(anime_3_txt),
gsSPDisplayList(kan_win_sakiT_model),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsSPDisplayList(kan_win_moji1T_model),
gsSPDisplayList(kan_win_moji2T_model),
gsDPPipeSync(),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsSPDisplayList(kan_win_ban2T_model),
gsSPDisplayList(kan_win_banT_model),
gsSPDisplayList(kan_win_tyouT_model),
gsSPDisplayList(kan_win_tyou2T_model),
gsSPEndDisplayList(),
};

Gfx kan_win_color0_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 85, 255),
gsDPSetEnvColor(185, 0, 0, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 150, 60, 255),
gsDPSetEnvColor(100, 70, 60, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 85, 0, 255),
gsDPSetEnvColor(30, 20, 20, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 105, 50, 40, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 255, 175, 255),
gsDPSetEnvColor(255, 135, 0, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 125, 80, 70, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 125, 80, 70, 255),
gsSPEndDisplayList(),
};

Gfx kan_win_color1_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 215, 255, 255, 255),
gsDPSetEnvColor(60, 130, 255, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 60, 150, 255, 255),
gsDPSetEnvColor(60, 70, 100, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 0, 115, 255, 255),
gsDPSetEnvColor(20, 20, 30, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 40, 50, 105, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 255, 255, 235, 255),
gsDPSetEnvColor(55, 90, 255, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 60, 70, 105, 255),
gsSPEndDisplayList(),
gsDPSetPrimColor(0, 255, 40, 50, 105, 255),
gsSPEndDisplayList(),
};
