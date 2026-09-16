#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 obj_w_cedar_dead_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_w_cedar1_dead/obj_w_cedar_dead_tex.inc"
};

Vtx obj_w_cedar1_dead_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_w_cedar1_dead/obj_w_cedar1_dead_v.inc"
};

Gfx obj_w_cedar1_deadT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, obj_w_cedar_dead_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_w_cedar1_deadT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_w_cedar1_dead_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
