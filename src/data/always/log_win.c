#include "types.h"
#include "PR/mbi.h"

u8 log_win_w_tex[] = {
#include "assets/forestd/log_win/log_win_w_tex.inc"
};

Vtx log_win_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/log_win/log_win_v.inc"
};

#pragma force_active on
Gfx log_win_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 255, 245, 0, 255),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, log_win_w_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 2047, 256),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 8, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 252),
gsSPVertex(log_win_v, 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};
#pragma force_active reset
