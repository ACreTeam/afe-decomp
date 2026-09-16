#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 mus_win_nuno_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_nuno_tex_rgb_ci4_pal.inc"
};

u16 mus_win_sw4_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_sw4_tex_rgb_ci4_pal.inc"
};

u16 mus_win_sw1_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_sw1_tex_rgb_ci4_pal.inc"
};

u16 mus_win_sw2_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_sw2_tex_rgb_ci4_pal.inc"
};

u16 mus_win_sw3_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_sw3_tex_rgb_ci4_pal.inc"
};

static u8 inv_mwin_nwaku_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/inv_mwin_nwaku_tex.inc"
};

u8 mus_win_tagu_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_tagu_tex.inc"
};

u8 mus_win_moji_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_moji_tex.inc"
};

u8 mus_win_w1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_w1_tex.inc"
};

u8 mus_win_w2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_w2_tex.inc"
};

u8 mus_win_w3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_w3_tex.inc"
};

u8 mus_win_w4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_w4_tex.inc"
};

u8 mus_win_w5_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_w5_tex.inc"
};

static u8 dlt_win_yajirushi_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/dlt_win_yajirushi_tex.inc"
};

u8 mus_win_nuno_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_nuno_tex_rgb_ci4.inc"
};

u8 mus_win_sw4_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_sw4_tex_rgb_ci4.inc"
};

u8 mus_win_sw1_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_sw1_tex_rgb_ci4.inc"
};

u8 mus_win_sw2_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_sw2_tex_rgb_ci4.inc"
};

u8 mus_win_sw3_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_sw3_tex_rgb_ci4.inc"
};

Vtx mus_win_pp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_win_pp_v.inc"
};

Gfx mus_win_sw1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[12], 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 2, 0, 4, 1),
gsSPEndDisplayList(),
};

Gfx mus_win_sw2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[17], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_sw3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[21], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_sw4T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[25], 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 2, 0, 4, 1),
gsSPEndDisplayList(),
};

Gfx mus_win_sw5T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mus_win_sw3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[30], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_sw6T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mus_win_sw3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[34], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_sw7T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[38], 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 1, 3, 0, 4, 1),
gsSPEndDisplayList(),
};

Gfx mus_win_sw8T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[43], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_sw9T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[47], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_sw10T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, mus_win_sw1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[51], 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 1, 3, 0, 4, 1),
gsSPEndDisplayList(),
};

Gfx mus_win_sw11T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mus_win_sw3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[56], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_sw12T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mus_win_sw3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[60], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_sw13_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_win_sw4_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, mus_win_sw4_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(mus_win_pp_v, 12, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 2, 1),
gsSPNTriangles_5b(0, 7, 1, 2, 8, 0, 2, 9, 8, 9, 4, 8),
gsSPNTriangles_5b(9, 5, 4, 5, 10, 3, 3, 11, 4, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_ueT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 0, 0, 0, 255),
gsDPSetEnvColor(110, 105, 110, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, mus_win_w5_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[64], 28, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 11, 12, 9),
gsSPNTriangles_5b(11, 13, 12, 13, 14, 12, 13, 15, 14, 15, 16, 14),
gsSPNTriangles_5b(15, 17, 16, 7, 18, 5, 7, 19, 18, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, mus_win_w4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 20, 21, 22, 21, 23, 22, 24, 25, 26),
gsSPNTriangles_5b(27, 24, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, mus_win_w3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[92], 30, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 4, 6, 7),
gsSPNTriangles_5b(4, 7, 5, 6, 8, 7, 9, 10, 11, 10, 12, 11),
gsSPNTriangles_5b(0, 13, 1, 13, 14, 1, 15, 16, 17, 16, 18, 17),
gsSPNTriangles_5b(5, 19, 3, 7, 8, 20, 9, 21, 10, 9, 0, 2),
gsSPNTriangles_5b(9, 2, 21, 22, 23, 24, 25, 22, 24, 26, 27, 28),
gsSPNTriangles_5b(26, 29, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, mus_win_w2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[122], 28, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, mus_win_w1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(12, 8, 9, 10, 11, 12, 13, 12, 14, 13),
gsSPNTriangles_5b(15, 12, 11, 16, 8, 10, 8, 17, 9, 18, 19, 20),
gsSPNTriangles_5b(21, 22, 23, 24, 18, 20, 18, 25, 19, 22, 26, 23),
gsSPNTriangles_5b(27, 22, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_ue2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 110, 105, 110, 255),
gsDPSetEnvColor(40, 60, 70, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[150], 12, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 8, 6, 5, 8, 9, 6, 10, 2, 1),
gsSPNTriangles_5b(10, 11, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_kyokumeiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 20, 20, 30, 255),
gsDPSetEnvColor(145, 145, 145, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, mus_win_tagu_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_REPEAT, 0, 0),
gsSPVertex(&mus_win_pp_v[162], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_shirushi1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, dlt_win_yajirushi_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&mus_win_pp_v[166], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_mojiT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 20, 225, 225, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 64, mus_win_moji_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mus_win_pp_v[174], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_model_before[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(14, 16, 1, mus_win_nuno_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, mus_win_nuno_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPEndDisplayList(),
};

Gfx mus_win_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(mus_win_sw1T_model),
gsSPDisplayList(mus_win_sw2T_model),
gsSPDisplayList(mus_win_sw3T_model),
gsSPDisplayList(mus_win_sw4T_model),
gsSPDisplayList(mus_win_sw5T_model),
gsSPDisplayList(mus_win_sw6T_model),
gsSPDisplayList(mus_win_sw7T_model),
gsSPDisplayList(mus_win_sw8T_model),
gsSPDisplayList(mus_win_sw9T_model),
gsSPDisplayList(mus_win_sw10T_model),
gsSPDisplayList(mus_win_sw11T_model),
gsSPDisplayList(mus_win_sw12T_model),
gsSPDisplayList(mus_win_sw13_model),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPDisplayList(mus_win_ueT_model),
gsSPDisplayList(mus_win_ue2T_model),
gsSPDisplayList(mus_win_kyokumeiT_model),
gsSPDisplayList(mus_win_mojiT_model),
gsSPEndDisplayList(),
};

u8 mus_clg_win_hajime_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_clg_win_hajime_tex.inc"
};

u8 mus_clg_win_saigo_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_clg_win_saigo_tex.inc"
};

u8 mus_cat_c_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_cat_c_tex.inc"
};

u8 mus_yaji[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_yaji.inc"
};

Vtx mus_clg_hyouji_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_win_nuno_tex_rgb_ci4/mus_clg_hyouji_v.inc"
};

Gfx mus_clg_win_cbT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 0, 255, 255, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, mus_yaji),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(mus_clg_hyouji_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 245, 245, 30, 255),
gsDPSetEnvColor(85, 75, 105, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, mus_cat_c_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_clg_hyouji_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(20, 30, 150, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, mus_clg_win_saigo_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mus_clg_hyouji_v[12], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, mus_clg_win_hajime_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
gsSPEndDisplayList(),
};
