#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u8 obj_flower_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_flower/obj_flower_tex.inc"
};

Vtx obj_flower_a_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_flower/obj_flower_a_v.inc"
};

Gfx obj_flower_aT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_flower_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_flower_aT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_flower_a_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Vtx obj_flower_b_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_flower/obj_flower_b_v.inc"
};

Gfx obj_flower_bT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_flower_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 1, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_flower_bT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_flower_b_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Vtx obj_flower_c_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_flower/obj_flower_c_v.inc"
};

Gfx obj_flower_cT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_flower_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 2, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_flower_cT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_flower_c_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
