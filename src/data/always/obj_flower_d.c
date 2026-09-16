#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 obj_flower_d[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_flower_d/obj_flower_d.inc"
};

Vtx obj_flower_d_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_flower_d/obj_flower_d_v.inc"
};

Gfx obj_flower_dT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_flower_d),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 9, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_flower_dT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_flower_d_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
