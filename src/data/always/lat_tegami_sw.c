#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 lat_tegami_sw_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/lat_tegami_sw/lat_tegami_sw_tex.inc"
};

Vtx onp_sentaku_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_tegami_sw/onp_sentaku_v.inc"
};

Gfx lat_sentaku_c_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
gsDPSetPrimColor(0, 255, 255, 0, 0, 255),
gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
gsSPVertex(onp_sentaku_v, 3, 0),
gsSP1Triangle(0, 1, 2, 0),
gsSPEndDisplayList(),
};

Gfx lat_sentaku_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 255, 165, 255),
gsDPSetEnvColor(255, 70, 0, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, lat_tegami_sw_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&onp_sentaku_v[3], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
gsSPEndDisplayList(),
};
