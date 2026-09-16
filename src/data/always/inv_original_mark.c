#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 inv_original_mark_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_original_mark/inv_original_mark_tex.inc"
};

Vtx sav_mark_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/inv_original_mark/sav_mark_v.inc"
};

Gfx sav_mark_winT_before_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, inv_original_mark_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPEndDisplayList(),
};

Gfx sav_mark_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(sav_mark_v, 4, 0),
gsSPNTriangles(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
