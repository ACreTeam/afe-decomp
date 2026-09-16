#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 obj_shop_cracker_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_shop_cracker/obj_shop_cracker_pal.inc"
};

u8 obj_shop_cracker[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_shop_cracker/obj_shop_cracker.inc"
};

Vtx obj_shop_cracker_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_shop_cracker/obj_shop_cracker_v.inc"
};

Gfx obj_shop_cracker_1T_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_cracker_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, obj_shop_cracker),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_shop_cracker_1T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_shop_cracker_v, 26, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 4, 0, 5, 6),
gsSPNTriangles_5b(7, 8, 0, 9, 10, 0, 2, 11, 0, 0, 12, 13),
gsSPNTriangles_5b(0, 14, 15, 0, 8, 16, 17, 5, 0, 18, 19, 0),
gsSPNTriangles_5b(13, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(4, 21, 22, 23, 21, 24, 22, 24, 25, 22),
gsSPNTriangles_5b(25, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
