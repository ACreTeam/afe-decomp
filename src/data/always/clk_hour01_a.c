#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 clk_num_00_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_hour01_a/clk_num_00_tex_rgb_ia8.inc"
};

Vtx clk_hour01_a_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/clk_hour01_a/clk_hour01_a_v.inc"
};

Gfx clk_hour01_aT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_MIRROR, 0, 0),
gsSPDisplayList(anime_2_txt),
gsSPVertex(clk_hour01_a_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
