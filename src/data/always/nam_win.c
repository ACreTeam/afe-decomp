#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u16 nam_win_enpitu_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_enpitu_pal.inc"
};

u16 nam_win_pen_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_pen_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw1_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw1_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw2_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw2_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw3_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw3_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw4_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw4_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw5_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw5_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw6_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw6_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw7_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw7_tex_rgb_ci4_pal.inc"
};

u8 nam_win_w1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_w1_tex.inc"
};

u8 nam_win_w2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_w2_tex.inc"
};

u8 nam_win_w3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_w3_tex.inc"
};

u8 nam_win_w4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_w4_tex.inc"
};

u8 nam_win_w5_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_w5_tex.inc"
};

static u8 nam_win_fuki_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_fuki_tex.inc"
};

u8 nam_win_enpitu_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_enpitu_tex.inc"
};

u8 nam_win_nw1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_nw1_tex.inc"
};

u8 nam_win_nw2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_nw2_tex.inc"
};

u8 nam_win_pen_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_pen_tex_rgb_ci4.inc"
};

u8 nam_win_sw1_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw1_tex_rgb_ci4.inc"
};

u8 nam_win_sw2_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw2_tex_rgb_ci4.inc"
};

u8 nam_win_sw3_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw3_tex_rgb_ci4.inc"
};

u8 nam_win_sw4_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw4_tex_rgb_ci4.inc"
};

u8 nam_win_sw5_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw5_tex_rgb_ci4.inc"
};

u8 nam_win_sw6_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw6_tex_rgb_ci4.inc"
};

u8 nam_win_sw7_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/nam_win/nam_win_sw7_tex_rgb_ci4.inc"
};

Vtx nam_win_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/nam_win/nam_win_v.inc"
};

Gfx nam_win_ueT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 215, 255, 235, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, nam_win_w5_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(nam_win_v, 27, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, nam_win_w4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
gsSPNTriangles_5b(15, 12, 14, 16, 17, 11, 17, 18, 11, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, nam_win_w3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 19, 20, 21, 20, 22, 21, 23, 24, 25),
gsSPNTriangles_5b(24, 26, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, nam_win_w2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&nam_win_v[27], 16, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 3, 5),
gsSPNTriangles_5b(7, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, nam_win_w1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_fukiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 0, 25, 20, 170),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, nam_win_fuki_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[43], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_enpituT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(AA_EN | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL | FORCE_BL | G_RM_PASS, AA_EN | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_enpitu_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, nam_win_enpitu_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[47], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_nmT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 80, 185, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, nam_win_nw2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[51], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, nam_win_nw1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&nam_win_v[59], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&nam_win_v[63], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&nam_win_v[67], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw4T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&nam_win_v[71], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw5T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw5_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw5_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&nam_win_v[75], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw6T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw6_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw6_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&nam_win_v[79], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw7T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw7_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw7_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&nam_win_v[83], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw8T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw1_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw1_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[87], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw9T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw2_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw2_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[91], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw10T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw3_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw3_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[95], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw11T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw4_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw4_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[99], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw12T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw5_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw5_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[103], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw13T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw6_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw6_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[107], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_sw14T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw7_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw7_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&nam_win_v[111], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

u8 nam_win_modeT[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/nam_win/nam_win_modeT.inc"
};

Gfx nam_win_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(nam_win_modeT),
gsSPDisplayList(nam_win_ueT_model),
gsSPDisplayList(nam_win_fukiT_model),
gsSPDisplayList(nam_win_enpituT_model),
gsSPDisplayList(nam_win_nmT_model),
gsSPEndDisplayList(),
};

Gfx nam_win_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPLoadTLUT_Dolphin(14, 16, 1, nam_win_pen_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, nam_win_pen_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPEndDisplayList(),
};

Gfx nam_win_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPDisplayList(nam_win_sw1T_model),
gsSPDisplayList(nam_win_sw2T_model),
gsSPDisplayList(nam_win_sw3T_model),
gsSPDisplayList(nam_win_sw4T_model),
gsSPDisplayList(nam_win_sw5T_model),
gsSPDisplayList(nam_win_sw6T_model),
gsSPDisplayList(nam_win_sw7T_model),
gsSPDisplayList(nam_win_sw8T_model),
gsSPDisplayList(nam_win_sw9T_model),
gsSPDisplayList(nam_win_sw10T_model),
gsSPDisplayList(nam_win_sw11T_model),
gsSPDisplayList(nam_win_sw12T_model),
gsSPDisplayList(nam_win_sw13T_model),
gsSPDisplayList(nam_win_sw14T_model),
gsSPDisplayList(nam_win_modelT),
gsSPEndDisplayList(),
};
