#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

extern u8 obj_s_tree_young_tex[];

Vtx obj_s_stump3_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_stump3/obj_s_stump3_v.inc"
};

Gfx obj_stump3T_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_young_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 6, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_gold_stump3T_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_young_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 8, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_stump3T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_s_stump3_v, 7, 0),
gsSPNTrianglesInit_5b(7, 0, 1, 2, 2, 3, 0, 3, 4, 0),
gsSPNTriangles_5b(0, 5, 1, 0, 4, 5, 3, 6, 4, 4, 6, 5),
gsSPEndDisplayList(),
};
