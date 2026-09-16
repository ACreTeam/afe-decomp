#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 int_ike_yado_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_shellA/int_ike_yado_pal.inc"
};

static u8 act_mus_yado_body2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_shellA/act_mus_yado_body2.inc"
};

static u8 act_mus_yado_body3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_shellA/act_mus_yado_body3.inc"
};

Vtx obj_item_shellA_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_item_shellA/obj_item_shellA_v.inc"
};

Gfx obj_item_shellAT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_yado_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_yado_body3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_yado_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_item_shellAT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_item_shellA_v, 22, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 0, 2, 4, 1, 0),
gsSPNTriangles_5b(3, 5, 0, 5, 6, 4, 5, 4, 0, 7, 1, 4),
gsSPNTriangles_5b(6, 7, 4, 7, 8, 1, 8, 9, 1, 9, 10, 1),
gsSPNTriangles_5b(10, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(12, 11, 12, 13, 11, 13, 14, 11, 15, 16),
gsSPNTriangles_5b(11, 14, 15, 17, 16, 18, 17, 11, 16, 19, 20, 21),
gsSPNTriangles_5b(19, 17, 18, 19, 18, 20, 19, 11, 17, 12, 19, 21),
gsSPNTriangles_5b(12, 11, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
