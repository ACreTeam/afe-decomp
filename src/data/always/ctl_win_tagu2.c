#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

static u8 ctl_win_tagu2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/ctl_win_tagu2_tex.inc"
};

u8 clg_win_ha2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/clg_win_ha2_tex.inc"
};

u8 clg_win_jyuutan2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/clg_win_jyuutan2_tex.inc"
};

u8 clg_win_kabe2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/clg_win_kabe2_tex.inc"
};

u8 clg_win_fuku2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/clg_win_fuku2_tex.inc"
};

u8 clg_win_hone2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/clg_win_hone2_tex.inc"
};

u8 clg_win_tegami2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/clg_win_tegami2_tex.inc"
};

u8 clg_win_onpu2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/clg_win_onpu2_tex.inc"
};

u8 clg_win_hani2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/clg_win_hani2_tex.inc"
};

u8 clg_win_kasa2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_win_tagu2/clg_win_kasa2_tex.inc"
};

Vtx clg_tagu_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ctl_win_tagu2/clg_tagu_v.inc"
};

Gfx clg_tag_win_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_tag_picture_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsSPEndDisplayList(),
};

Gfx clg_win_haT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(clg_tagu_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_kabeT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&clg_tagu_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_jyuutanT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&clg_tagu_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_fukuT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&clg_tagu_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_kasaT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&clg_tagu_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_tegamiT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&clg_tagu_v[20], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_haniwaT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&clg_tagu_v[24], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_honeT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&clg_tagu_v[28], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_onpuT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&clg_tagu_v[32], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_ha2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_ha2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[36], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_kabe2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_kabe2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[40], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_jyuutan2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_jyuutan2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[44], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_fuku2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_fuku2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[48], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_kasa2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_kasa2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[52], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_tegami2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_tegami2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[56], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_haniwa2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_hani2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[60], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_hone2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_hone2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[64], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx clg_win_onpu2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, clg_win_onpu2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_tagu_v[68], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
