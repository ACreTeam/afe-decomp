#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u8 inv_mwin_nwaku_tex[] = {
#include "assets/forestd/pos_win/inv_mwin_nwaku_tex.inc"
};

u8 pos_win_w6_tex[] = {
#include "assets/forestd/pos_win/pos_win_w6_tex.inc"
};

u8 pos_win_w1_tex[] = {
#include "assets/forestd/pos_win/pos_win_w1_tex.inc"
};

u8 pos_win_w2_tex[] = {
#include "assets/forestd/pos_win/pos_win_w2_tex.inc"
};

u8 pos_win_w3_tex[] = {
#include "assets/forestd/pos_win/pos_win_w3_tex.inc"
};

u8 pos_win_w4_tex[] = {
#include "assets/forestd/pos_win/pos_win_w4_tex.inc"
};

u8 pos_win_w5_tex[] = {
#include "assets/forestd/pos_win/pos_win_w5_tex.inc"
};

u8 pos_win_post_tex[] = {
#include "assets/forestd/pos_win/pos_win_post_tex.inc"
};

u16 pos_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/forestd/pos_win/pos_win_nuno_tex_rgb_ci4_pal.inc"
};

u16 pos_win_sw5_tex_rgb_ci4_pal[] = {
#include "assets/forestd/pos_win/pos_win_sw5_tex_rgb_ci4_pal.inc"
};

u16 pos_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/forestd/pos_win/pos_win_sw1_tex_rgb_ci4_pal.inc"
};

u16 pos_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/forestd/pos_win/pos_win_sw2_tex_rgb_ci4_pal.inc"
};

u16 pos_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/forestd/pos_win/pos_win_sw3_tex_rgb_ci4_pal.inc"
};

u16 pos_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/forestd/pos_win/pos_win_sw4_tex_rgb_ci4_pal.inc"
};

u8 pos_win_nuno_tex_rgb_ci4[] = {
#include "assets/forestd/pos_win/pos_win_nuno_tex_rgb_ci4.inc"
};

u8 pos_win_sw5_tex_rgb_ci4[] = {
#include "assets/forestd/pos_win/pos_win_sw5_tex_rgb_ci4.inc"
};

u8 pos_win_sw1_tex_rgb_ci4[] = {
#include "assets/forestd/pos_win/pos_win_sw1_tex_rgb_ci4.inc"
};

u8 pos_win_sw2_tex_rgb_ci4[] = {
#include "assets/forestd/pos_win/pos_win_sw2_tex_rgb_ci4.inc"
};

u8 pos_win_sw3_tex_rgb_ci4[] = {
#include "assets/forestd/pos_win/pos_win_sw3_tex_rgb_ci4.inc"
};

u8 pos_win_sw4_tex_rgb_ci4[] = {
#include "assets/forestd/pos_win/pos_win_sw4_tex_rgb_ci4.inc"
};

Vtx pos_win_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/pos_win/pos_win_v.inc"
};

Gfx pos_win_w9_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_sw5_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_sw5_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 124),
gsSPVertex(pos_win_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_ue1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 165, 165, 255, 255),
gsDPSetEnvColor(255, 60, 60, 255),
gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, inv_mwin_nwaku_tex),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPVertex(&pos_win_v[4], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_ue2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 90, 90, 255, 255),
gsDPSetEnvColor(165, 165, 255, 255),
gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, pos_win_w5_tex),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
gsSPVertex(&pos_win_v[8], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSP2Triangles(4, 5, 6, 0, 6, 7, 4, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, pos_win_w4_tex),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
gsSPVertex(&pos_win_v[16], 6, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSP2Triangles(0, 4, 3, 0, 4, 5, 3, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, pos_win_w3_tex),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPVertex(&pos_win_v[22], 11, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
gsSP2Triangles(8, 5, 9, 0, 9, 10, 8, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, pos_win_w2_tex),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
gsSPVertex(&pos_win_v[33], 6, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 0, 5, 0, 0, 2, 5, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, pos_win_w1_tex),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPVertex(&pos_win_v[39], 11, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSP2Triangles(8, 0, 9, 0, 0, 10, 9, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_ue3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 165, 165, 255, 255),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, pos_win_w6_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
gsSPVertex(&pos_win_v[50], 11, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(2, 4, 5, 0, 4, 6, 5, 0),
gsSP2Triangles(7, 8, 9, 0, 7, 10, 8, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_postT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 60, 60, 205, 255),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, pos_win_post_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
gsSPVertex(&pos_win_v[61], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_w1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&pos_win_v[65], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_w2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&pos_win_v[69], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_w3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_sw4_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_sw4_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&pos_win_v[73], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_w4T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_sw4_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_sw4_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&pos_win_v[77], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_w5T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&pos_win_v[81], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_w6T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&pos_win_v[85], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_w7T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&pos_win_v[89], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_w8T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&pos_win_v[93], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx pos_win_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pos_win_nuno_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 480, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, pos_win_nuno_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 14, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPEndDisplayList(),
};

Gfx pos_win_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(pos_win_w1T_model),
gsSPDisplayList(pos_win_w2T_model),
gsSPDisplayList(pos_win_w3T_model),
gsSPDisplayList(pos_win_w4T_model),
gsSPDisplayList(pos_win_w5T_model),
gsSPDisplayList(pos_win_w6T_model),
gsSPDisplayList(pos_win_w7T_model),
gsSPDisplayList(pos_win_w8T_model),
gsSPDisplayList(pos_win_w9_model),
gsDPPipeSync(),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPDisplayList(pos_win_ue1T_model),
gsSPDisplayList(pos_win_ue2T_model),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsSPDisplayList(pos_win_ue3T_model),
gsSPDisplayList(pos_win_postT_model),
gsSPEndDisplayList(),
};
