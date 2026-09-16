#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_letter27_4[];
extern u8 lat_letter27_6[];
extern u8 lat_letter27_8[];
extern u8 lat_letter27_9[];
extern u16 lat_letter27_pal[];

Vtx lat_letter27_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter27_win/lat_letter27_v.inc"
};

Gfx lat_letter27_win_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter27_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 128, lat_letter27_8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(lat_letter27_v, 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter27_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter27_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter27_6),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter27_v[8], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter27_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter27_4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter27_v[12], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter27_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter27_9),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter27_v[16], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter27_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(lat_letter27_win_model),
gsSPDisplayList(lat_letter27_winT_model),
gsSPEndDisplayList(),
};
