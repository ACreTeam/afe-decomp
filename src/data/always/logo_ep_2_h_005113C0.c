#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

static u8 logo_ep_1_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_ep_2_h_005113C0/logo_ep_1_h_tex.inc"
};

static u8 logo_ep_2_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_ep_2_h_005113C0/logo_ep_2_h_tex.inc"
};

static u8 logo_ep_3_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_ep_2_h_005113C0/logo_ep_3_h_tex.inc"
};

static u8 logo_ep_4_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_ep_2_h_005113C0/logo_ep_4_h_tex.inc"
};

static u8 logo_back_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_ep_2_h_005113C0/logo_back_tex.inc"
};

static u8 logo_mori_1_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_ep_2_h_005113C0/logo_mori_1_h_tex.inc"
};

static u8 logo_mori_2_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_ep_2_h_005113C0/logo_mori_2_h_tex.inc"
};

Vtx logo_mori_ep_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/logo_ep_2_h_005113C0/logo_mori_ep_v.inc"
};

Gfx logo_point_mori_ep_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, logo_ep_4_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(logo_mori_ep_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx logo_back_mori_epT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, logo_back_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&logo_mori_ep_v[4], 32, 0),
gsSPNTrianglesInit_5b(30, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(3, 5, 4, 5, 6, 4, 5, 7, 6, 7, 8, 6),
gsSPNTriangles_5b(8, 9, 6, 9, 10, 6, 11, 12, 13, 11, 14, 12),
gsSPNTriangles_5b(12, 15, 13, 15, 16, 13, 9, 17, 10, 9, 18, 17),
gsSPNTriangles_5b(18, 19, 17, 18, 20, 19, 20, 21, 19, 20, 22, 21),
gsSPNTriangles_5b(22, 23, 21, 0, 24, 1, 0, 25, 24, 25, 26, 24),
gsSPNTriangles_5b(25, 27, 26, 27, 28, 26, 27, 29, 28, 29, 12, 28),
gsSPNTriangles_5b(29, 15, 12, 8, 30, 9, 8, 31, 30, 0, 0, 0),
gsSPVertex(&logo_mori_ep_v[36], 19, 0),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(3, 5, 4, 5, 6, 4, 5, 7, 6, 7, 8, 6),
gsSPNTriangles_5b(7, 9, 8, 9, 10, 8, 9, 11, 10, 11, 12, 10),
gsSPNTriangles_5b(11, 13, 12, 13, 14, 12, 13, 15, 14, 15, 16, 14),
gsSPNTriangles_5b(15, 17, 16, 17, 18, 16, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx logo_type_mori_epT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 80, 48, logo_mori_2_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&logo_mori_ep_v[55], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 80, 48, logo_mori_1_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx logo_type2_mori_epT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, logo_ep_3_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&logo_mori_ep_v[63], 14, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, logo_ep_2_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 120, 32, logo_ep_1_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 10, 12, 13),
gsSPNTriangles_5b(10, 13, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
