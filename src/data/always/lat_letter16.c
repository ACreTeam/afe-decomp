#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_letter16_1[];
extern u8 lat_letter16_3[];
extern u16 lat_letter16_pal[];
extern u8 lat_letter16_sen[];

Vtx lat_letter16_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter16/lat_letter16_v.inc"
};

Gfx lat_letter16_win_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter16_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter16_1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(lat_letter16_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter16_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter16_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter16_3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter16_v[4], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter16_sen_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
gsDPSetEnvColor(89, 89, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, lat_letter16_sen),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter16_v[8], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter16_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(lat_letter16_win_model),
gsSPDisplayList(lat_letter16_winT_model),
gsSPEndDisplayList(),
};
