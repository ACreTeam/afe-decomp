#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

static u8 clk_etc_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_sec/clk_etc_tex.inc"
};

Vtx clk_sec_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/clk_sec/clk_sec_v.inc"
};

Gfx clk_sec_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, clk_etc_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(clk_sec_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
