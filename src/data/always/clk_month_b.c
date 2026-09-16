#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

Vtx clk_month_b_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/clk_month_b/clk_month_b_v.inc"
};

Gfx clk_month_b_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
gsSPVertex(clk_month_b_v, 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPEndDisplayList(),
};
