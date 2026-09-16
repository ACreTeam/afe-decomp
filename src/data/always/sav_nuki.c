#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 sav_nuki_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/sav_nuki/sav_nuki_tex.inc"
};

Vtx sav_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/sav_nuki/sav_v.inc"
};

Gfx sav_mb_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, anime_2_txt),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(sav_v, 4, 0),
gsSPNTriangles(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
