#include "types.h"
#include "PR/mbi.h"

u8 mny_win_test2_tex[] = {
#include "assets/forestd/mny_win/mny_win_test2_tex.inc"
};

u8 mny_win_test3_tex[] = {
#include "assets/forestd/mny_win/mny_win_test3_tex.inc"
};

u8 mny_win_u_tex[] = {
#include "assets/forestd/mny_win/mny_win_u_tex.inc"
};

Vtx mny_win_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mny_win/mny_win_v.inc"
};

Gfx mny_win_ueT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, mny_win_u_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
gsSPVertex(mny_win_v, 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};

Gfx mny_win_beruT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, mny_win_test3_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 127, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 60),
gsSPVertex(&mny_win_v[8], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx mny_win_mojiT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, mny_win_test2_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 7, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 383, 342),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 6, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 7, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 380, 60),
gsSPVertex(&mny_win_v[12], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};
