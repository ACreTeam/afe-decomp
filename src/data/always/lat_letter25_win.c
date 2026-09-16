#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_letter25_1[];
extern u8 lat_letter25_2[];
extern u8 lat_letter25_3[];
extern u8 lat_letter25_4[];
extern u8 lat_letter25_5[];
extern u16 lat_letter25_pal[];

Vtx lat_letter25_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter25_win/lat_letter25_v.inc"
};

Gfx lat_letter25_win_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, TEXEL0_ALPHA, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, TEXEL0_ALPHA, 0, TEXEL0, 0, ENVIRONMENT, 0),
gsDPSetEnvColor(255, 255, 255, 250),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter25_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, lat_letter25_5),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
gsSPVertex(lat_letter25_v, 12, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
gsSP2Triangles(8, 10, 11, 0, 8, 11, 9, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter25_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter25_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter25_4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter25_v[12], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter25_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter25_3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter25_v[20], 12, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter25_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter25_2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter25_v[32], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter25_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter25_1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter25_v[40], 12, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter25_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(lat_letter25_winT_model),
gsSPDisplayList(lat_letter25_win_model),
gsSPEndDisplayList(),
};
