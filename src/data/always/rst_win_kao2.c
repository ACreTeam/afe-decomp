#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rst_win_kao2_pal[] = {
#include "assets/forestd/rst_win_kao2/rst_win_kao2_pal.inc"
};

u8 rst_win_kagi2_tex[] = {
#include "assets/forestd/rst_win_kao2/rst_win_kagi2_tex.inc"
};

u8 rst_win_seri_tex[] = {
#include "assets/forestd/rst_win_kao2/rst_win_seri_tex.inc"
};

static u8 req_win_w1_tex[] = {
#include "assets/forestd/rst_win_kao2/req_win_w1_tex.inc"
};

static u8 req_win_w2_tex[] = {
#include "assets/forestd/rst_win_kao2/req_win_w2_tex.inc"
};

static u8 req_win_w3_tex[] = {
#include "assets/forestd/rst_win_kao2/req_win_w3_tex.inc"
};

u8 rst_win_kao_tex[] = {
#include "assets/forestd/rst_win_kao2/rst_win_kao_tex.inc"
};

u8 rst_win_kagi1_tex[] = {
#include "assets/forestd/rst_win_kao2/rst_win_kagi1_tex.inc"
};

static u8 req_win_w4_tex[] = {
#include "assets/forestd/rst_win_kao2/req_win_w4_tex.inc"
};

u16 rst_win_bittkuri_tex_rgb_ci4_pal[] = {
#include "assets/forestd/rst_win_kao2/rst_win_bittkuri_tex_rgb_ci4_pal.inc"
};

u16 rst_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/forestd/rst_win_kao2/rst_win_sw4_tex_rgb_ci4_pal.inc"
};

u16 rst_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/forestd/rst_win_kao2/rst_win_sw1_tex_rgb_ci4_pal.inc"
};

u16 rst_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/forestd/rst_win_kao2/rst_win_sw2_tex_rgb_ci4_pal.inc"
};

u16 rst_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/forestd/rst_win_kao2/rst_win_sw3_tex_rgb_ci4_pal.inc"
};

u8 rst_win_bittkuri_tex_rgb_ci4[] = {
#include "assets/forestd/rst_win_kao2/rst_win_bittkuri_tex_rgb_ci4.inc"
};

u8 rst_win_sw4_tex_rgb_ci4[] = {
#include "assets/forestd/rst_win_kao2/rst_win_sw4_tex_rgb_ci4.inc"
};

u8 rst_win_sw1_tex_rgb_ci4[] = {
#include "assets/forestd/rst_win_kao2/rst_win_sw1_tex_rgb_ci4.inc"
};

u8 rst_win_sw2_tex_rgb_ci4[] = {
#include "assets/forestd/rst_win_kao2/rst_win_sw2_tex_rgb_ci4.inc"
};

u8 rst_win_sw3_tex_rgb_ci4[] = {
#include "assets/forestd/rst_win_kao2/rst_win_sw3_tex_rgb_ci4.inc"
};

Vtx rst_win_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rst_win_kao2/rst_win_v.inc"
};

Gfx rst_win_waku11_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw4_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw4_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 124),
gsSPVertex(rst_win_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_ueT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 255, 200, 255),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, req_win_w4_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
gsSPVertex(&rst_win_v[4], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, req_win_w3_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPVertex(&rst_win_v[8], 8, 0),
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
gsSPVertex(&rst_win_v[16], 16, 0),
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
gsSPVertex(&rst_win_v[32], 12, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSP2Triangles(0, 4, 1, 0, 4, 5, 1, 0),
gsSP2Triangles(6, 7, 8, 0, 9, 6, 8, 0),
gsSP2Triangles(10, 9, 11, 0, 9, 8, 11, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_fukiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 30, 30, 20, 180),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, rst_win_seri_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPVertex(&rst_win_v[44], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_kaoT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
gsDPSetTextureLUT(G_TT_RGBA16),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_kao2_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_kao_tex),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
gsSPVertex(&rst_win_v[52], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_kagiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 40, 150, 40, 255),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, rst_win_kagi1_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
gsSPVertex(&rst_win_v[56], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, rst_win_kagi2_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
gsSPVertex(&rst_win_v[60], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&rst_win_v[64], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&rst_win_v[68], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 124),
gsSPVertex(&rst_win_v[72], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku4T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&rst_win_v[76], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku5T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&rst_win_v[80], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku6T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&rst_win_v[84], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku7T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&rst_win_v[88], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku8T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 124),
gsSPVertex(&rst_win_v[92], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku9T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 252, 124),
gsSPVertex(&rst_win_v[96], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx rst_win_waku10T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&rst_win_v[100], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx ledit_common_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsSPEndDisplayList(),
};

Gfx rst_win_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rst_win_bittkuri_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 480, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, rst_win_bittkuri_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 14, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPEndDisplayList(),
};

Gfx rst_win_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(rst_win_waku1T_model),
gsSPDisplayList(rst_win_waku2T_model),
gsSPDisplayList(rst_win_waku3T_model),
gsSPDisplayList(rst_win_waku4T_model),
gsSPDisplayList(rst_win_waku5T_model),
gsSPDisplayList(rst_win_waku6T_model),
gsSPDisplayList(rst_win_waku7T_model),
gsSPDisplayList(rst_win_waku8T_model),
gsSPDisplayList(rst_win_waku9T_model),
gsSPDisplayList(rst_win_waku10T_model),
gsSPDisplayList(rst_win_waku11_model),
gsDPPipeSync(),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPDisplayList(rst_win_ueT_model),
gsSPDisplayList(rst_win_kagiT_model),
gsSPDisplayList(rst_win_kaoT_model),
gsSPDisplayList(rst_win_fukiT_model),
gsSPEndDisplayList(),
};
