#include "bootdata.h"
#include "libforest/gbi_extensions.h"

u8 logo_nin2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/logo_nin2_tex.inc"
};

u8 logo_nin1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/logo_nin1_tex.inc"
};

Vtx logo_nin_v[] = {
#include "assets/bootdata/logo_nin_v.inc"
};

Gfx logo_ninT_model[] = {
  gsDPLoadTextureBlock_4b_Dolphin(logo_nin1_tex, G_IM_FMT_I, 256, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPVertex(&logo_nin_v[0], 8, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    0, 2, 3, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(logo_nin2_tex, G_IM_FMT_I, 256, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    4, 5, 6, // tri0
    4, 6, 7, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};
