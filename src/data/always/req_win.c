#include "types.h"
#include "PR/mbi.h"

u16 req_win_kao_pal[] = {
#include "assets/forestd/req_win/req_win_kao_pal.inc"
};

u8 req_win_fuki_tex[] = {
#include "assets/forestd/req_win/req_win_fuki_tex.inc"
};

static u8 req_win_w1_tex[] = {
#include "assets/forestd/req_win/req_win_w1_tex.inc"
};

static u8 req_win_w2_tex[] = {
#include "assets/forestd/req_win/req_win_w2_tex.inc"
};

static u8 req_win_w3_tex[] = {
#include "assets/forestd/req_win/req_win_w3_tex.inc"
};

u8 req_win_kao_tex[] = {
#include "assets/forestd/req_win/req_win_kao_tex.inc"
};

u8 req_win_sen2_tex[] = {
#include "assets/forestd/req_win/req_win_sen2_tex.inc"
};

static u8 req_win_w4_tex[] = {
#include "assets/forestd/req_win/req_win_w4_tex.inc"
};

u16 req_win_onpu_tex_rgb_ci4_pal[] = {
#include "assets/forestd/req_win/req_win_onpu_tex_rgb_ci4_pal.inc"
};

u16 req_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/forestd/req_win/req_win_sw4_tex_rgb_ci4_pal.inc"
};

u16 req_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/forestd/req_win/req_win_sw1_tex_rgb_ci4_pal.inc"
};

u16 req_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/forestd/req_win/req_win_sw2_tex_rgb_ci4_pal.inc"
};

u16 req_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/forestd/req_win/req_win_sw3_tex_rgb_ci4_pal.inc"
};

u8 req_win_onpu_tex_rgb_ci4[] = {
#include "assets/forestd/req_win/req_win_onpu_tex_rgb_ci4.inc"
};

u8 req_win_sw4_tex_rgb_ci4[] = {
#include "assets/forestd/req_win/req_win_sw4_tex_rgb_ci4.inc"
};

u8 req_win_sw1_tex_rgb_ci4[] = {
#include "assets/forestd/req_win/req_win_sw1_tex_rgb_ci4.inc"
};

u8 req_win_sw2_tex_rgb_ci4[] = {
#include "assets/forestd/req_win/req_win_sw2_tex_rgb_ci4.inc"
};

u8 req_win_sw3_tex_rgb_ci4[] = {
#include "assets/forestd/req_win/req_win_sw3_tex_rgb_ci4.inc"
};

Vtx req_win_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/req_win/req_win_v.inc"
};

Gfx req_win_w11_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw4_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw4_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 124),
gsSPVertex(req_win_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_ueT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 205, 205, 255, 255),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, req_win_w4_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
gsSPVertex(&req_win_v[4], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, req_win_w3_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPVertex(&req_win_v[8], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, req_win_w2_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPVertex(&req_win_v[16], 16, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSP2Triangles(8, 9, 10, 0, 11, 8, 10, 0),
gsSP2Triangles(12, 13, 14, 0, 15, 12, 14, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, req_win_w1_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
gsSPVertex(&req_win_v[32], 12, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSP2Triangles(0, 4, 1, 0, 4, 5, 1, 0),
gsSP2Triangles(6, 7, 8, 0, 9, 6, 8, 0),
gsSP2Triangles(10, 9, 11, 0, 9, 8, 11, 0),
gsSPEndDisplayList(),
};

Gfx req_win_fukiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 30, 30, 180, 180),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, req_win_fuki_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 8, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 124),
gsSPVertex(&req_win_v[44], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_iconT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
gsDPSetTextureLUT(G_TT_RGBA16),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_kao_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_kao_tex),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
gsSPVertex(&req_win_v[48], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_reqT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 20, 255, 255),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, req_win_sen2_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 8, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1535, 171),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 12, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 8, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 764, 124),
gsSPVertex(&req_win_v[52], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&req_win_v[56], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&req_win_v[60], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 124),
gsSPVertex(&req_win_v[64], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w4T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&req_win_v[68], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w5T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&req_win_v[72], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w6T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&req_win_v[76], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w7T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&req_win_v[80], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w8T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 124),
gsSPVertex(&req_win_v[84], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w9T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&req_win_v[88], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_w10T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&req_win_v[92], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx req_win_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, req_win_onpu_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 480, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, req_win_onpu_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 14, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPEndDisplayList(),
};

Gfx req_win_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(req_win_w1T_model),
gsSPDisplayList(req_win_w2T_model),
gsSPDisplayList(req_win_w3T_model),
gsSPDisplayList(req_win_w4T_model),
gsSPDisplayList(req_win_w5T_model),
gsSPDisplayList(req_win_w6T_model),
gsSPDisplayList(req_win_w7T_model),
gsSPDisplayList(req_win_w8T_model),
gsSPDisplayList(req_win_w9T_model),
gsSPDisplayList(req_win_w10T_model),
gsSPDisplayList(req_win_w11_model),
gsDPPipeSync(),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPDisplayList(req_win_ueT_model),
gsSPDisplayList(req_win_reqT_model),
gsSPDisplayList(req_win_iconT_model),
gsSPDisplayList(req_win_fukiT_model),
gsSPEndDisplayList(),
};
