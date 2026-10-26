#include "bootdata.h"
#include "libforest/gbi_extensions.h"

u8 gam_win_moji9_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/win3/gam_win_moji9_tex.inc"
};

Vtx gam_win3_v[] = {
#include "assets/bootdata/win3/gam_win3_v.inc"
};

Gfx gam_win3_moji_model[] = {
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji9_tex, G_IM_FMT_I, 128, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
  gsSPVertex(&gam_win3_v[0], 4, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};
