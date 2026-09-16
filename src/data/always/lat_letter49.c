#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_letter49_ki_tex[];
extern u16 lat_letter49_pal[];
extern u8 lat_letter49_xk_tex[];

Vtx lat_letter49_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter49/lat_letter49_v.inc"
};

Gfx lat_letter49_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter49_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, lat_letter49_ki_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(lat_letter49_v, 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(3, 4, 5, 0, 3, 5, 6, 0),
gsSP2Triangles(3, 6, 7, 0, 3, 7, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter49_sen_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 200, 200, 200, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter49_xk_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter49_v[8], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};
