#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 clk_ampm_b_am_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_ampm_b/clk_ampm_b_am_tex_rgb_i4.inc"
};

u8 clk_ampm_b_pm_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clk_ampm_b/clk_ampm_b_pm_tex_rgb_i4.inc"
};

Vtx clk_ampm_b_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/clk_ampm_b/clk_ampm_b_v.inc"
};

Gfx clk_ampm_b_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, anime_2_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
gsSPVertex(clk_ampm_b_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
