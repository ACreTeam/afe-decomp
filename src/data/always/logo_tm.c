#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 logo_tm_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_tm/logo_tm_h_tex.inc"
};

Vtx logo_tm_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/logo_tm/logo_tm_v.inc"
};

Gfx logo_tmT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, logo_tm_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(logo_tm_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
