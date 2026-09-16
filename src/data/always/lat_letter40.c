#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_letter40_hw_tex[];
extern u8 lat_letter40_nk_tex[];
extern u16 lat_letter40_pal[];
extern u8 lat_letter40_xk_tex[];

Vtx lat_letter40_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter40/lat_letter40_v.inc"
};

Gfx lat_letter40_win_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter40_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter40_hw_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(lat_letter40_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter40_sen_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 255, 55, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter40_xk_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter40_v[4], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter40_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter40_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter40_nk_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter40_v[8], 26, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsSP2Triangles(8, 9, 10, 0, 8, 10, 6, 0),
gsSP2Triangles(11, 0, 3, 0, 11, 3, 12, 0),
gsSP2Triangles(6, 10, 13, 0, 6, 13, 14, 0),
gsSP2Triangles(15, 16, 17, 0, 15, 17, 18, 0),
gsSP2Triangles(19, 20, 21, 0, 19, 21, 22, 0),
gsSP2Triangles(23, 24, 22, 0, 23, 22, 25, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter40_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(lat_letter40_win_model),
gsSPDisplayList(lat_letter40_winT_model),
gsSPEndDisplayList(),
};
