#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

static u8 ctl_win_tagu3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/sav_sentaku/ctl_win_tagu3_tex.inc"
};

Vtx sav_sentaku_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/sav_sentaku/sav_sentaku_v.inc"
};

Gfx sav_sentaku_taguT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ctl_win_tagu3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(sav_sentaku_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
