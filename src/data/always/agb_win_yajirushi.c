#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 agb_win_yajirushi_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/agb_win_yajirushi/agb_win_yajirushi_tex.inc"
};

Vtx agb_yajirushi_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/agb_win_yajirushi/agb_yajirushi_v.inc"
};

Gfx agb_win_yajirushiT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 50, 50, 255),
gsDPSetEnvColor(255, 30, 30, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, agb_win_yajirushi_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(agb_yajirushi_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
