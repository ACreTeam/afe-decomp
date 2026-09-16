#include "types.h"
#include "PR/mbi.h"

u16 kti_win_hate_pal[] = {
#include "assets/forestd/kti_win_hate/kti_win_hate_pal.inc"
};

u8 kti_win_sen_tex[] = {
#include "assets/forestd/kti_win_hate/kti_win_sen_tex.inc"
};

u8 kti_win_w1_tex[] = {
#include "assets/forestd/kti_win_hate/kti_win_w1_tex.inc"
};

u8 kti_win_w2_tex[] = {
#include "assets/forestd/kti_win_hate/kti_win_w2_tex.inc"
};

u8 kti_win_w3_tex[] = {
#include "assets/forestd/kti_win_hate/kti_win_w3_tex.inc"
};

u8 kti_win_w4_tex[] = {
#include "assets/forestd/kti_win_hate/kti_win_w4_tex.inc"
};

u8 kti_win_w5_tex[] = {
#include "assets/forestd/kti_win_hate/kti_win_w5_tex.inc"
};

u8 kti_win_fuki_tex[] = {
#include "assets/forestd/kti_win_hate/kti_win_fuki_tex.inc"
};

u8 kti_win_hate_tex[] = {
#include "assets/forestd/kti_win_hate/kti_win_hate_tex.inc"
};

u16 kti_win_nuno_tex_rgb_ci4_pal[] = {
#include "assets/forestd/kti_win_hate/kti_win_nuno_tex_rgb_ci4_pal.inc"
};

u16 kti_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw1_tex_rgb_ci4_pal.inc"
};

u16 kti_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw2_tex_rgb_ci4_pal.inc"
};

u16 kti_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw3_tex_rgb_ci4_pal.inc"
};

u16 kti_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw4_tex_rgb_ci4_pal.inc"
};

u16 kti_win_sw5_tex_rgb_ci4_pal[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw5_tex_rgb_ci4_pal.inc"
};

u16 kti_win_sw6_tex_rgb_ci4_pal[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw6_tex_rgb_ci4_pal.inc"
};

u16 kti_win_sw7_tex_rgb_ci4_pal[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw7_tex_rgb_ci4_pal.inc"
};

u8 kti_win_nuno_tex_rgb_ci4[] = {
#include "assets/forestd/kti_win_hate/kti_win_nuno_tex_rgb_ci4.inc"
};

u8 kti_win_sw1_tex_rgb_ci4[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw1_tex_rgb_ci4.inc"
};

u8 kti_win_sw2_tex_rgb_ci4[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw2_tex_rgb_ci4.inc"
};

u8 kti_win_sw3_tex_rgb_ci4[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw3_tex_rgb_ci4.inc"
};

u8 kti_win_sw4_tex_rgb_ci4[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw4_tex_rgb_ci4.inc"
};

u8 kti_win_sw5_tex_rgb_ci4[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw5_tex_rgb_ci4.inc"
};

u8 kti_win_sw6_tex_rgb_ci4[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw6_tex_rgb_ci4.inc"
};

u8 kti_win_sw7_tex_rgb_ci4[] = {
#include "assets/forestd/kti_win_hate/kti_win_sw7_tex_rgb_ci4.inc"
};

Vtx kti_win_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/kti_win_hate/kti_win_v.inc"
};

Gfx ephrase_win_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_nuno_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 480, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_nuno_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 14, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPEndDisplayList(),
};

Gfx kti_win_ueT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 235, 255, 215, 255),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, kti_win_w5_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
gsSPVertex(kti_win_v, 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, kti_win_w4_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPVertex(&kti_win_v[8], 11, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
gsSP2Triangles(8, 9, 3, 0, 9, 10, 3, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, kti_win_w3_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPVertex(&kti_win_v[19], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, kti_win_w2_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPVertex(&kti_win_v[27], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
gsSP2Triangles(6, 3, 5, 0, 7, 0, 2, 0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, kti_win_w1_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[35], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_fukiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 60, 145, 0, 180),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, kti_win_fuki_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 8, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 124),
gsSPVertex(&kti_win_v[43], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_kafuT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_hate_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_hate_tex),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&kti_win_v[47], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[51], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[55], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[59], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw4T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw4_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw4_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[63], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw5T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw5_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw5_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[67], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw6T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw6_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw6_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[71], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw7T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw7_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw7_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[75], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw8T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[79], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw9T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[83], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw10T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[87], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw11T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw4_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw4_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[91], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw12T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw5_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw5_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[95], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw13T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw6_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw6_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[99], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_sw14T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, kti_win_sw7_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, kti_win_sw7_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&kti_win_v[103], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx kti_win_senT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 80, 80, 235, 255),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, kti_win_sen_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 256),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 8, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 508, 60),
gsSPVertex(&kti_win_v[107], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx ephrase_win_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(kti_win_sw1T_model),
gsSPDisplayList(kti_win_sw2T_model),
gsSPDisplayList(kti_win_sw3T_model),
gsSPDisplayList(kti_win_sw4T_model),
gsSPDisplayList(kti_win_sw5T_model),
gsSPDisplayList(kti_win_sw6T_model),
gsSPDisplayList(kti_win_sw7T_model),
gsSPDisplayList(kti_win_sw8T_model),
gsSPDisplayList(kti_win_sw9T_model),
gsSPDisplayList(kti_win_sw10T_model),
gsSPDisplayList(kti_win_sw11T_model),
gsSPDisplayList(kti_win_sw12T_model),
gsSPDisplayList(kti_win_sw13T_model),
gsSPDisplayList(kti_win_sw14T_model),
gsDPPipeSync(),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsSPDisplayList(kti_win_ueT_model),
gsSPDisplayList(kti_win_senT_model),
gsSPDisplayList(kti_win_fukiT_model),
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
gsDPSetTextureLUT(G_TT_RGBA16),
gsSPDisplayList(kti_win_kafuT_model),
gsSPEndDisplayList(),
};
