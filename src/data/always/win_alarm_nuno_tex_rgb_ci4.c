#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 win_alarm_nuno_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_nuno_tex_rgb_ci4_pal.inc"
};

u16 win_alarm_sw1_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw1_tex_rgb_ci4_pal.inc"
};

u16 win_alarm_sw2_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw2_tex_rgb_ci4_pal.inc"
};

u16 win_alarm_sw3_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw3_tex_rgb_ci4_pal.inc"
};

u16 win_alarm_sw4_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw4_tex_rgb_ci4_pal.inc"
};

u16 win_alarm_sw5_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw5_tex_rgb_ci4_pal.inc"
};

u16 win_alarm_sw6_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw6_tex_rgb_ci4_pal.inc"
};

u16 win_alarm_sw7_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw7_tex_rgb_ci4_pal.inc"
};

u8 win_alarm_w1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_w1_tex.inc"
};

u8 win_alarm_w2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_w2_tex.inc"
};

u8 win_alarm_w3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_w3_tex.inc"
};

u8 win_alarm_w4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_w4_tex.inc"
};

u8 win_alarm_w5_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_w5_tex.inc"
};

static u8 inv_mwin_3Dma_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/inv_mwin_3Dma_tex.inc"
};

static u8 hni_nwin2_w_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/hni_nwin2_w_tex.inc"
};

u8 win_alarm_nuno_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_nuno_tex_rgb_ci4.inc"
};

u8 win_alarm_sw1_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw1_tex_rgb_ci4.inc"
};

u8 win_alarm_sw2_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw2_tex_rgb_ci4.inc"
};

u8 win_alarm_sw3_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw3_tex_rgb_ci4.inc"
};

u8 win_alarm_sw4_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw4_tex_rgb_ci4.inc"
};

u8 win_alarm_sw5_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw5_tex_rgb_ci4.inc"
};

u8 win_alarm_sw6_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw6_tex_rgb_ci4.inc"
};

u8 win_alarm_sw7_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_sw7_tex_rgb_ci4.inc"
};

Vtx win_alarm_jikoku_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/win_alarm_nuno_tex_rgb_ci4/win_alarm_jikoku_v.inc"
};

Gfx alarm_sw1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[43], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[47], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[51], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw4T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw4_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw4_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[55], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw5T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw5_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw5_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[59], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw6T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw6_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw6_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[63], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw7T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw7_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw7_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[67], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw8T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw1_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw1_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[71], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw9T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw2_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw2_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[75], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw10T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw3_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw3_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[79], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw11T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw4_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw4_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[83], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw12T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw5_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw5_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[87], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw13T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw6_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw6_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[91], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_sw14T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, win_alarm_sw7_tex_rgb_ci4_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, win_alarm_sw7_tex_rgb_ci4),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 64, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 64, 1, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(1, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[95], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx alarm_ue_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 235, 245, 255),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, win_alarm_w5_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
gsSPVertex(win_alarm_jikoku_v, 8, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, win_alarm_w4_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPVertex(&win_alarm_jikoku_v[8], 11, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSP2Triangles(8, 3, 9, 0, 3, 10, 9, 0),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, win_alarm_w3_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPVertex(&win_alarm_jikoku_v[19], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, win_alarm_w2_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPVertex(&win_alarm_jikoku_v[27], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, win_alarm_w1_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 1024),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
gsSPVertex(&win_alarm_jikoku_v[35], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};

Gfx alarm_maruT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 60, 130, 255, 255),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, inv_mwin_3Dma_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
gsSPVertex(&win_alarm_jikoku_v[115], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx alarm_fukiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 115, 0, 115, 190),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, hni_nwin2_w_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 8, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1279, 205),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 10, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 8, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 636, 124),
gsSPVertex(&win_alarm_jikoku_v[119], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx ain_win_jikoku_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(14, 16, 1, win_alarm_nuno_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, win_alarm_nuno_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx ain_win_jikoku_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(alarm_sw1T_model),
gsSPDisplayList(alarm_sw2T_model),
gsSPDisplayList(alarm_sw3T_model),
gsSPDisplayList(alarm_sw4T_model),
gsSPDisplayList(alarm_sw5T_model),
gsSPDisplayList(alarm_sw6T_model),
gsSPDisplayList(alarm_sw7T_model),
gsSPDisplayList(alarm_sw8T_model),
gsSPDisplayList(alarm_sw9T_model),
gsSPDisplayList(alarm_sw10T_model),
gsSPDisplayList(alarm_sw11T_model),
gsSPDisplayList(alarm_sw12T_model),
gsSPDisplayList(alarm_sw13T_model),
gsSPDisplayList(alarm_sw14T_model),
gsDPSetCycleType(G_CYC_1CYCLE),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPDisplayList(alarm_ue_model),
gsSPDisplayList(alarm_maruT_model),
gsSPDisplayList(alarm_fukiT_model),
gsSPEndDisplayList(),
};
