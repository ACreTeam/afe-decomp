#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_letter31_ed_tex[];
extern u16 lat_letter31_pal[];
extern u8 lat_letter31_xk_tex[];

Vtx lat_letter31_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter31/lat_letter31_v.inc"
};

Gfx lat_letter31_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter31_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter31_ed_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(lat_letter31_v, 20, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 4, 0),
gsSP2Triangles(0, 4, 1, 0, 3, 5, 4, 0),
gsSP2Triangles(6, 7, 8, 0, 7, 0, 9, 0),
gsSP2Triangles(7, 9, 8, 0, 0, 2, 9, 0),
gsSP2Triangles(10, 11, 12, 0, 13, 14, 15, 0),
gsSP2Triangles(11, 13, 15, 0, 11, 15, 12, 0),
gsSP2Triangles(16, 17, 18, 0, 13, 16, 18, 0),
gsSP2Triangles(13, 18, 19, 0, 13, 19, 14, 0),
gsSPVertex(&lat_letter31_v[20], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter31_sen_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 215, 215, 0, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter31_xk_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter31_v[24], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};
