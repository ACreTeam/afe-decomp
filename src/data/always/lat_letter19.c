#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

extern u8 lat_letter19_1[];
extern u8 lat_letter19_2[];
extern u16 lat_letter19_pal[];

Vtx lat_letter19_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter19/lat_letter19_v.inc"
};

Gfx lat_letter19_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, lat_letter19_2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(lat_letter19_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_RGBA16),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter19_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, lat_letter19_1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&lat_letter19_v[4], 16, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_OFF),
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 1, 0, 0, 0, PRIMITIVE, 0, 0, 0, 1),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&lat_letter19_v[20], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};
