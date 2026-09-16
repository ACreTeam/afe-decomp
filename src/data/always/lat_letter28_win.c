#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_letter28_1[];
extern u8 lat_letter28_2[];
extern u8 lat_letter28_5[];
extern u8 lat_letter28_6[];
extern u8 lat_letter28_7[];
extern u8 lat_letter28_9[];
extern u16 lat_letter28_pal[];

Vtx lat_letter28_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_letter28_win/lat_letter28_v.inc"
};

Gfx lat_letter28_win_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter28_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter28_7),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(lat_letter28_v, 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter28_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter28_6),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter28_v[8], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter28_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter28_5),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter28_v[12], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter28_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter28_2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
gsSPVertex(&lat_letter28_v[20], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter28_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter28_1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter28_v[24], 11, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 3, 5, 0, 4, 5, 6, 0),
gsSP2Triangles(7, 8, 9, 0, 7, 9, 10, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter28_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter28_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter28_9),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&lat_letter28_v[35], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsSPEndDisplayList(),
};

Gfx lat_letter28_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(lat_letter28_win_model),
gsSPDisplayList(lat_letter28_winT_model),
gsSPEndDisplayList(),
};
