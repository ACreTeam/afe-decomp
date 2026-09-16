#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

Vtx mCL_rom_myhome1_wall_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mCL_rom_myhome1_wall/mCL_rom_myhome1_wall_v.inc"
};

Gfx mCL_rom_myhome1_wall_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(G_RM_NOOP, G_RM_AA_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, anime_3_txt),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(mCL_rom_myhome1_wall_v, 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsDPPipeSync(),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_2_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&mCL_rom_myhome1_wall_v[8], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};
