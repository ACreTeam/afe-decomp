#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u8 dlt_win_yajirushi_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/dlt_win_yajirushi/dlt_win_yajirushi_tex.inc"
};

Vtx clg_shirushi_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/dlt_win_yajirushi/clg_shirushi_v.inc"
};

Gfx clg_win_shirushi1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, dlt_win_yajirushi_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(clg_shirushi_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
