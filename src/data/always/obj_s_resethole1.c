#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 obj_e_resethole_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_s_resethole1/obj_e_resethole_pal.inc"
};

u8 obj_e_resethole_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_s_resethole1/obj_e_resethole_tex.inc"
};

Vtx obj_s_resethole1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_s_resethole1/obj_s_resethole1_v.inc"
};

Gfx obj_s_resethole1T_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_e_resethole_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_e_resethole_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_s_resethole1T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_s_resethole1_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
