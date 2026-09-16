#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 obj_f_tree_dead_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_f_tree1_dead/obj_f_tree_dead_tex.inc"
};

Vtx obj_f_tree1_dead_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_f_tree1_dead/obj_f_tree1_dead_v.inc"
};

Gfx obj_f_tree1_deadT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_f_tree_dead_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 6, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_f_gold_tree1_deadT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_f_tree_dead_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 8, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_f_tree1_deadT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_f_tree1_dead_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
