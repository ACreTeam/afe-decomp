#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 cal_win_nen0_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen0_tex_rgb_i4.inc"
};

u8 cal_win_nen1_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen1_tex_rgb_i4.inc"
};

u8 cal_win_nen2_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen2_tex_rgb_i4.inc"
};

u8 cal_win_nen3_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen3_tex_rgb_i4.inc"
};

u8 cal_win_nen4_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen4_tex_rgb_i4.inc"
};

u8 cal_win_nen5_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen5_tex_rgb_i4.inc"
};

u8 cal_win_nen6_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen6_tex_rgb_i4.inc"
};

u8 cal_win_nen7_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen7_tex_rgb_i4.inc"
};

u8 cal_win_nen8_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen8_tex_rgb_i4.inc"
};

u8 cal_win_nen9_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen9_tex_rgb_i4.inc"
};

Vtx cal_nen_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_nen_v.inc"
};

u8 cal_win_nen_before[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/cal_win_nen0_tex_rgb_i4/cal_win_nen_before.inc"
};

Gfx cal_win_nen1_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(cal_nen_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_nen2_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&cal_nen_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_nen3_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&cal_nen_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_win_nen4_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&cal_nen_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
