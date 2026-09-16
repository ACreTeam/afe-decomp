#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

static u16 inv_mushi_w5_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w5_tex_rgb_ci4_pal.inc"
};

u16 inv_sakana_nuno_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_sakana_nuno_tex_rgb_ci4_pal.inc"
};

static u16 inv_mushi_w1_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w1_tex_rgb_ci4_pal.inc"
};

static u16 inv_mushi_w2_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w2_tex_rgb_ci4_pal.inc"
};

static u16 inv_mushi_w3_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w3_tex_rgb_ci4_pal.inc"
};

static u16 inv_mushi_w4_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w4_tex_rgb_ci4_pal.inc"
};

static u16 inv_mushi_w6_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w6_tex_rgb_ci4_pal.inc"
};

static u16 inv_mushi_w7_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w7_tex_rgb_ci4_pal.inc"
};

static u8 inv_mwin_nwaku_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mwin_nwaku_tex.inc"
};

u8 inv_mwin_shirushi2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mwin_shirushi2_tex.inc"
};

static u8 inv_mwin_shirushi_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mwin_shirushi_tex.inc"
};

static u8 inv_mushi_aw1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_aw1_tex.inc"
};

static u8 inv_mushi_aw2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_aw2_tex.inc"
};

static u8 inv_mushi_aw3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_aw3_tex.inc"
};

static u8 inv_mushi_aw4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_aw4_tex.inc"
};

u8 inv_sakana_waku1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_sakana_waku1_tex.inc"
};

static u8 inv_mushi_aw7_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_aw7_tex.inc"
};

u8 inv_sakana_moji_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_sakana_moji_tex.inc"
};

u8 inv_sakana_waku2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_sakana_waku2_tex.inc"
};

static u8 inv_mwin_aw5_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mwin_aw5_tex.inc"
};

static u8 inv_mushi_w5_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w5_tex_rgb_ci4.inc"
};

u8 inv_sakana_nuno_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_sakana_nuno_tex_rgb_ci4.inc"
};

static u8 inv_mushi_w1_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w1_tex_rgb_ci4.inc"
};

static u8 inv_mushi_w2_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w2_tex_rgb_ci4.inc"
};

static u8 inv_mushi_w3_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w3_tex_rgb_ci4.inc"
};

static u8 inv_mushi_w4_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w4_tex_rgb_ci4.inc"
};

static u8 inv_mushi_w6_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w6_tex_rgb_ci4.inc"
};

static u8 inv_mushi_w7_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_mushi_w7_tex_rgb_ci4.inc"
};

Vtx inv_sakana_pp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/inv_mushi_w5_tex_rgb_ci4/inv_sakana_pp_v.inc"
};

Gfx inv_sakana_w1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mushi_w3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w4_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w4_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w4T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mushi_w3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[20], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w5T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[24], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w6T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w6_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_mushi_w6_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[28], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w7T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w7_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_mushi_w7_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[32], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w8T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[36], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w9T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mushi_w3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[40], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w10T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w4_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w4_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[44], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w11T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, inv_mushi_w3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[48], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w12T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mushi_w1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[52], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w13T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, inv_mushi_w2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[56], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_w14_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mushi_w5_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, inv_mushi_w5_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(inv_sakana_pp_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_waku2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 50, 50, 235, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, inv_mwin_shirushi_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[60], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_ueT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 185, 205, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, inv_mwin_aw5_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[64], 19, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 1, 0, 3, 4, 1),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, inv_mushi_aw7_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 5, 6, 7, 8, 7, 9, 8, 9, 10),
gsSPNTriangles_5b(5, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_mushi_aw4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 11, 12, 13, 14, 15, 16, 15, 17, 16),
gsSPNTriangles_5b(11, 13, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, inv_mushi_aw3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[83], 28, 0),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 5, 6, 7, 8),
gsSPNTriangles_5b(9, 6, 8, 10, 0, 11, 0, 2, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 17, 19, 18, 3, 20, 4),
gsSPNTriangles_5b(21, 5, 4, 19, 22, 18, 23, 10, 11, 24, 25, 26),
gsSPNTriangles_5b(27, 24, 26, 23, 7, 10, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, inv_mushi_aw2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[111], 23, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_mushi_aw1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(9, 6, 7, 8, 9, 6, 8, 10, 11, 12),
gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 17, 15, 18, 19, 20),
gsSPNTriangles_5b(20, 21, 18, 9, 22, 6, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_ue2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 185, 205, 255, 255),
gsDPSetEnvColor(80, 165, 130, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, inv_mwin_nwaku_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[134], 13, 0),
gsSPNTrianglesInit_5b(11, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 3, 2, 8, 9, 8, 2, 10, 6, 11),
gsSPNTriangles_5b(10, 7, 6, 11, 12, 10, 8, 11, 6, 8, 6, 3),
gsSPEndDisplayList(),
};

Gfx inv_sakana_daimeiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 40, 40, 185, 255),
gsDPSetEnvColor(100, 100, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, inv_sakana_waku2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[147], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, inv_sakana_waku1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_shirushiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 215, 215, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, inv_mwin_shirushi2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[155], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_moji_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 215, 215, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 80, 16, inv_sakana_moji_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&inv_sakana_pp_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_scroll_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(14, 16, 1, inv_sakana_nuno_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_sakana_nuno_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPEndDisplayList(),
};

Gfx inv_sakana_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(inv_sakana_w1T_model),
gsSPDisplayList(inv_sakana_w2T_model),
gsSPDisplayList(inv_sakana_w3T_model),
gsSPDisplayList(inv_sakana_w4T_model),
gsSPDisplayList(inv_sakana_w5T_model),
gsSPDisplayList(inv_sakana_w6T_model),
gsSPDisplayList(inv_sakana_w7T_model),
gsSPDisplayList(inv_sakana_w8T_model),
gsSPDisplayList(inv_sakana_w9T_model),
gsSPDisplayList(inv_sakana_w10T_model),
gsSPDisplayList(inv_sakana_w11T_model),
gsSPDisplayList(inv_sakana_w12T_model),
gsSPDisplayList(inv_sakana_w13T_model),
gsSPDisplayList(inv_sakana_w14_model),
gsSPDisplayList(inv_sakana_waku2T_model),
gsSPDisplayList(inv_sakana_ueT_model),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
gsSPDisplayList(inv_sakana_ue2T_model),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPDisplayList(inv_sakana_daimeiT_model),
gsSPDisplayList(inv_sakana_shirushiT_model),
gsSPDisplayList(inv_sakana_moji_model),
gsSPEndDisplayList(),
};

Gfx inv_sakana_part_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(inv_sakana_waku2T_model),
gsSPDisplayList(inv_sakana_shirushiT_model),
gsSPEndDisplayList(),
};
