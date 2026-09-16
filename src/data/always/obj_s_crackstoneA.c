#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 obj_s_crackstone_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_s_crackstoneA/obj_s_crackstone_pal.inc"
};

u8 obj_s_crackstone_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_s_crackstoneA/obj_s_crackstone_tex.inc"
};

Vtx obj_s_crackstoneA_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_s_crackstoneA/obj_s_crackstoneA_v.inc"
};

Gfx obj_s_crackstoneA_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_crackstone_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_crackstone_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_s_crackstoneA_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_s_crackstoneA_v, 10, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 4, 1, 0),
gsSPNTriangles_5b(4, 5, 1, 1, 6, 3, 6, 7, 3, 1, 5, 6),
gsSPNTriangles_5b(2, 8, 9, 2, 3, 8, 3, 7, 8, 0, 0, 0),
gsSPEndDisplayList(),
};
