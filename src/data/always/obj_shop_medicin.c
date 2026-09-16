#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 obj_shop_medicin_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_shop_medicin/obj_shop_medicin_pal.inc"
};

u8 obj_shop_medicin[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_shop_medicin/obj_shop_medicin.inc"
};

Vtx obj_shop_medicin_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_shop_medicin/obj_shop_medicin_v.inc"
};

Gfx obj_shop_medicin_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_medicin_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_medicin),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_shop_medicin_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_shop_medicin_v, 22, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 8, 12, 11),
gsSPNTriangles_5b(8, 13, 12, 12, 14, 11, 14, 15, 11, 15, 9, 11),
gsSPNTriangles_5b(7, 16, 6, 7, 17, 16, 18, 19, 0, 18, 0, 2),
gsSPNTriangles_5b(5, 1, 0, 5, 0, 7, 15, 14, 20, 15, 20, 21),
gsSPNTriangles_5b(19, 17, 7, 19, 7, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
