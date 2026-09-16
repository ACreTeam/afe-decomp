#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u16 mra_win_pp_bl_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_bl_pal.inc"
};

u16 mra_win_pp_sita_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sita_tex_rgb_ci4_pal.inc"
};

u16 mra_win_pp_sw1_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw1_tex_rgb_ci4_pal.inc"
};

u16 mra_win_pp_sw2_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw2_tex_rgb_ci4_pal.inc"
};

u16 mra_win_pp_sw3_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw3_tex_rgb_ci4_pal.inc"
};

u16 mra_win_pp_sw4_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw4_tex_rgb_ci4_pal.inc"
};

u16 mra_win_pp_sw5_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw5_tex_rgb_ci4_pal.inc"
};

u16 mra_win_pp_sw6_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw6_tex_rgb_ci4_pal.inc"
};

u16 mra_win_pp_sw7_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw7_tex_rgb_ci4_pal.inc"
};

static u8 mra_win_w1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_w1_tex.inc"
};

static u8 mra_win_w2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_w2_tex.inc"
};

static u8 mra_win_w3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_w3_tex.inc"
};

static u8 mra_win_w4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_w4_tex.inc"
};

static u8 mra_win_w5_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_w5_tex.inc"
};

static u8 mra_win_fuki_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_fuki_tex.inc"
};

static u8 mra_win_yaji1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_yaji1_tex.inc"
};

static u8 mra_win_yaji2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_yaji2_tex.inc"
};

u8 mra_win_pp_bl_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_bl_tex.inc"
};

u8 mra_win_pp_sita_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sita_tex_rgb_ci4.inc"
};

u8 mra_win_pp_sw1_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw1_tex_rgb_ci4.inc"
};

u8 mra_win_pp_sw2_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw2_tex_rgb_ci4.inc"
};

u8 mra_win_pp_sw3_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw3_tex_rgb_ci4.inc"
};

u8 mra_win_pp_sw4_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw4_tex_rgb_ci4.inc"
};

u8 mra_win_pp_sw5_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw5_tex_rgb_ci4.inc"
};

u8 mra_win_pp_sw6_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw6_tex_rgb_ci4.inc"
};

u8 mra_win_pp_sw7_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_sw7_tex_rgb_ci4.inc"
};

Vtx mra_win_pp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mra_win_pp/mra_win_pp_v.inc"
};

static Gfx mra_win_ueT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 215, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, mra_win_w5_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(mra_win_pp_v, 24, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, mra_win_w4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
gsSPNTriangles_5b(15, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, mra_win_w3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 16, 17, 18, 17, 19, 18, 20, 21, 22),
gsSPNTriangles_5b(23, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, mra_win_w2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mra_win_pp_v[24], 19, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 1, 8, 9, 8, 10, 9, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, mra_win_w1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 11, 12, 13, 12, 14, 13, 15, 16, 17),
gsSPNTriangles_5b(16, 18, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_fukiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 70, 110, 0, 170),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, mra_win_fuki_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mra_win_pp_v[43], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mra_win_blT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_bl_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, mra_win_pp_bl_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&mra_win_pp_v[47], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_yajiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 0, 185, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, mra_win_yaji2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mra_win_pp_v[51], 12, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 16, mra_win_yaji1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 6, 7, 8, 9, 10),
gsSPNTriangles_5b(8, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mra_win_pp_v[63], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mra_win_pp_v[67], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mra_win_pp_v[71], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw4T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw4_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw4_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mra_win_pp_v[75], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw5T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw5_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw5_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mra_win_pp_v[79], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw6T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw6_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw6_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mra_win_pp_v[83], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw7T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw7_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw7_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mra_win_pp_v[87], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw8T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mra_win_pp_v[91], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw9T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mra_win_pp_v[95], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw10T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mra_win_pp_v[99], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw11T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw4_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw4_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mra_win_pp_v[103], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw12T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw5_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw5_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mra_win_pp_v[107], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw13T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw6_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw6_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mra_win_pp_v[111], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

static Gfx mra_win_sw14T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, mra_win_pp_sw7_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, mra_win_pp_sw7_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&mra_win_pp_v[115], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx mra_win_pp_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(14, 16, 1, mra_win_pp_sita_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, mra_win_pp_sita_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPEndDisplayList(),
};

Gfx mra_win_pp_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(mra_win_sw1T_model),
gsSPDisplayList(mra_win_sw2T_model),
gsSPDisplayList(mra_win_sw3T_model),
gsSPDisplayList(mra_win_sw4T_model),
gsSPDisplayList(mra_win_sw5T_model),
gsSPDisplayList(mra_win_sw6T_model),
gsSPDisplayList(mra_win_sw7T_model),
gsSPDisplayList(mra_win_sw8T_model),
gsSPDisplayList(mra_win_sw9T_model),
gsSPDisplayList(mra_win_sw10T_model),
gsSPDisplayList(mra_win_sw11T_model),
gsSPDisplayList(mra_win_sw12T_model),
gsSPDisplayList(mra_win_sw13T_model),
gsSPDisplayList(mra_win_sw14T_model),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureLUT(G_TT_NONE),
gsSPDisplayList(mra_win_ueT_model),
gsSPDisplayList(mra_win_fukiT_model),
gsSPDisplayList(mra_win_yajiT_model),
gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
gsDPSetTextureLUT(G_TT_RGBA16),
gsSPDisplayList(mra_win_blT_model),
gsSPEndDisplayList(),
};
