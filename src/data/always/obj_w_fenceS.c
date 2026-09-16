#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

extern u16 obj_fence_pal[];
extern u8 obj_w_fence_tex[];

Vtx obj_w_fenceS_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_w_fenceS/obj_w_fenceS_v.inc"
};

Gfx obj_w_fenceST_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_fence_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_w_fence_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_w_fenceST_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_w_fenceS_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
