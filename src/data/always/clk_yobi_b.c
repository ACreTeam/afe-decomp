#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 clk_yobi_b_1_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi_b/clk_yobi_b_1_tex_rgb_i4.inc"
};

u8 clk_yobi_b_2_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi_b/clk_yobi_b_2_tex_rgb_i4.inc"
};

u8 clk_yobi_b_3_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi_b/clk_yobi_b_3_tex_rgb_i4.inc"
};

u8 clk_yobi_b_4_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi_b/clk_yobi_b_4_tex_rgb_i4.inc"
};

u8 clk_yobi_b_5_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi_b/clk_yobi_b_5_tex_rgb_i4.inc"
};

u8 clk_yobi_b_6_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi_b/clk_yobi_b_6_tex_rgb_i4.inc"
};

u8 clk_yobi_b_7_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi_b/clk_yobi_b_7_tex_rgb_i4.inc"
};

Vtx clk_yobi_b_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/clk_yobi_b/clk_yobi_b_v.inc"
};

Gfx clk_yobi_b_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, anime_2_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
gsSPVertex(clk_yobi_b_v, 7, 0),
gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
