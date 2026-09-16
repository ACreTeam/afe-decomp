#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u8 int_ike_molcenter_wall[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_movechair/int_ike_molcenter_wall.inc"
};

static u8 int_ike_molcenter_locker[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_movechair/int_ike_molcenter_locker.inc"
};

static u8 int_ike_molcenter_chair3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_movechair/int_ike_molcenter_chair3.inc"
};

static u8 int_ike_molcenter_chair1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_movechair/int_ike_molcenter_chair1.inc"
};

static u8 int_ike_molcenter_chair2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_movechair/int_ike_molcenter_chair2.inc"
};

Vtx obj_item_movechair_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_item_movechair/obj_item_movechair_v.inc"
};

Gfx obj_item_movechair_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_molcenter_locker),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_molcenter_chair2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(obj_item_movechair_v, 14, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 0, 4, 1),
gsSPNTriangles_5b(5, 6, 7, 5, 7, 8, 9, 10, 11, 9, 11, 12),
gsSPNTriangles_5b(11, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_molcenter_chair1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&obj_item_movechair_v[14], 20, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_molcenter_wall),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_ike_molcenter_chair3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&obj_item_movechair_v[34], 12, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
gsSPEndDisplayList(),
};
