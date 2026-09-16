#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_letter12_1[];
extern u16 lat_letter12_pal[];
extern u8 lat_letter12_sen[];

Vtx lat_letter12_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter12/lat_letter12_v.inc"
};

Gfx lat_letter12_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter12_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, lat_letter12_1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(lat_letter12_v, 9, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(1, 4, 2, 0, 4, 5, 2, 0),
gsSP2Triangles(5, 6, 3, 0, 5, 3, 2, 0),
gsSP2Triangles(0, 7, 8, 0, 0, 8, 1, 0),
gsSP2Triangles(8, 4, 1, 0, 7, 6, 5, 0),
gsSP2Triangles(7, 5, 8, 0, 5, 4, 8, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter12_sen_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
gsDPSetEnvColor(240, 127, 171, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, lat_letter12_sen),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter12_v[9], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};
