#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_letter46_ce_tex[];
extern u8 lat_letter46_ed_tex[];
extern u16 lat_letter46_pal[];
extern u8 lat_letter46_xk_tex[];

Vtx lat_letter46_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter46/lat_letter46_v.inc"
};

Gfx lat_letter46_win_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter46_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, lat_letter46_ed_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(lat_letter46_v, 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(0, 4, 5, 0, 0, 5, 1, 0),
gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
gsSP2Triangles(3, 2, 7, 0, 3, 7, 6, 0),
gsSP2Triangles(5, 7, 2, 0, 5, 2, 1, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter46_sen_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 255, 215, 0, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter46_xk_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter46_v[8], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter46_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter46_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter46_ce_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter46_v[12], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter46_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(lat_letter46_win_model),
gsSPDisplayList(lat_letter46_winT_model),
gsSPEndDisplayList(),
};
