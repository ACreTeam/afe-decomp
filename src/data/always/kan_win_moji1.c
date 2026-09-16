#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 kan_win_moji1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kan_win_moji1/kan_win_moji1_tex.inc"
};

Vtx kan_mura_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/kan_win_moji1/kan_mura_v.inc"
};

Gfx kan_win_muraT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsSPDisplayList(anime_4_txt + 0x80),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, kan_win_moji1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(kan_mura_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
