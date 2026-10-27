#include "bootdata.h"
#include "libforest/gbi_extensions.h"

u8 gam_win_moji6_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/gam_win_moji6_tex.inc"
};

u8 gam_win_moji7_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/gam_win_moji7_tex.inc"
};

u8 gam_win_moji8_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/gam_win_moji8_tex.inc"
};

static u8 gam_win_moji1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/gam_win_moji1_tex.inc"
};

static u8 att_win_waku1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/att_win_waku1_tex.inc"
};

static u8 att_win_waku2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/att_win_waku2_tex.inc"
};

static u8 att_win_waku3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/att_win_waku3_tex.inc"
};

static u8 att_win_waku4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/att_win_waku4_tex.inc"
};

static u8 att_win_waku5_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/att_win_waku5_tex.inc"
};

static u8 att_win_waku6_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win2/att_win_waku6_tex.inc"
};

Vtx gam_win2_v[] = {
#include "assets/bootdata/win2/gam_win2_v.inc"
};

Gfx gam_win2_moji_model[] = {
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji8_tex, G_IM_FMT_I, 96, 16, 15, GX_CLAMP, GX_MIRROR, 0, 0),
  gsSPVertex(&gam_win2_v[0], 12, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji7_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji6_tex, G_IM_FMT_I, 96, 16, 15, GX_CLAMP, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    8, 9, 10, // tri0
    9, 11, 10, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

Gfx gam_win2_moji2_model[] = {
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji1_tex, G_IM_FMT_I, 128, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&gam_win2_v[12], 4, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};

Gfx gam_win2_winT_model[] = {
  gsDPSetPrimColor(0, 255, 225, 255, 255, 255),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku6_tex, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&gam_win2_v[16], 28, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku5_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    8, 9, 10 // tri2
  ),
  gsSPNTriangles_5b(
    11, 8, 10, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku4_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    12, 13, 14, // tri0
    15, 12, 14, // tri1
    16, 17, 18 // tri2
  ),
  gsSPNTriangles_5b(
    17, 19, 18, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku3_tex, G_IM_FMT_I, 32, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    20, 21, 22, // tri0
    21, 23, 22, // tri1
    24, 25, 26 // tri2
  ),
  gsSPNTriangles_5b(
    25, 27, 26, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku2_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&gam_win2_v[44], 16, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    4, 5, 6 // tri2
  ),
  gsSPNTriangles_5b(
    7, 4, 6, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsDPLoadTextureBlock_4b_Dolphin(att_win_waku1_tex, G_IM_FMT_I, 64, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPNTrianglesInit_5b(
    4, // tri count
    8, 9, 10, // tri0
    11, 8, 10, // tri1
    12, 13, 14 // tri2
  ),
  gsSPNTriangles_5b(
    13, 15, 14, // tri0
    0, 0, 0, // tri1
    0, 0, 0, // tri2
    0, 0, 0 // tri3
  ),
  gsSPEndDisplayList(),
};
