#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 inv_win_mark_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mark/inv_win_mark_tex.inc"
};

Vtx inv_mark_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/inv_mark/inv_mark_v.inc"
};

Gfx inv_mark_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, inv_win_mark_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(inv_mark_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
