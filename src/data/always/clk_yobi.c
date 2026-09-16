#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 clk_yobi_1_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi/clk_yobi_1_tex_rgb_ia8.inc"
};

u8 clk_yobi_2_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi/clk_yobi_2_tex_rgb_ia8.inc"
};

u8 clk_yobi_3_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi/clk_yobi_3_tex_rgb_ia8.inc"
};

u8 clk_yobi_4_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi/clk_yobi_4_tex_rgb_ia8.inc"
};

u8 clk_yobi_5_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi/clk_yobi_5_tex_rgb_ia8.inc"
};

u8 clk_yobi_6_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi/clk_yobi_6_tex_rgb_ia8.inc"
};

u8 clk_yobi_7_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_yobi/clk_yobi_7_tex_rgb_ia8.inc"
};

Vtx clk_yobi_a_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/clk_yobi/clk_yobi_a_v.inc"
};

Gfx clk_yobi_aT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_MIRROR, 0, 0),
gsSPDisplayList(anime_2_txt),
gsSPVertex(clk_yobi_a_v, 7, 0),
gsSPNTrianglesInit_5b(5, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
