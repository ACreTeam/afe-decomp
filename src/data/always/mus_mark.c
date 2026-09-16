#include "types.h"
#include "PR/mbi.h"
#include "libforest/gbi_extensions.h"

u8 mus_win_mark_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_mark/mus_win_mark_tex.inc"
};

Vtx mus_mark_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_mark/mus_mark_v.inc"
};

Gfx mus_mark_before[] ATTRIBUTE_ALIGN(8) = {
    gsDPPipeSync(),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPSetCombineMode(G_CC_BLENDPEDECALA, G_CC_BLENDPEDECALA),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, mus_win_mark_tex),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 127, 1024),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0x0000, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, 60, 60),
    gsSPEndDisplayList(),
};

Gfx mus_mark_model[] ATTRIBUTE_ALIGN(8) = {
    gsSPVertex(mus_mark_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};
