#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

static u8 ctl_win_tagu3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ctl_sentaku/ctl_win_tagu3_tex.inc"
};

Vtx ctl_sentaku_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ctl_sentaku/ctl_sentaku_v.inc"
};

Gfx ctl_sentaku_taguT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsSPDisplayList(anime_1_txt + 0x30),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(ctl_sentaku_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};
