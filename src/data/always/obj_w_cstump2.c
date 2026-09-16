#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

extern u8 obj_w_cedar_young_tex[];

Vtx obj_w_cstump2_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_w_cstump2/obj_w_cstump2_v.inc"
};

Gfx obj_w_cstump2T_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_cedar_young_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_w_cstump2T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_w_cstump2_v, 7, 0),
gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 4, 6, 5),
gsSPNTriangles_5b(0, 3, 1, 3, 5, 1, 1, 6, 2, 1, 5, 6),
gsSPEndDisplayList(),
};
