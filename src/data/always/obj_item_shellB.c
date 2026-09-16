#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 obj_item_shell_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_shellB/obj_item_shell_pal.inc"
};

u8 obj_item_shellB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_shellB/obj_item_shellB_tex.inc"
};

Vtx obj_item_shellB_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_item_shellB/obj_item_shellB_v.inc"
};

Gfx obj_item_shellBT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_item_shell_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_item_shellB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_item_shellBT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_item_shellB_v, 20, 0),
gsSPNTrianglesInit_5b(36, 0, 1, 2, 0, 3, 1, 0, 4, 3),
gsSPNTriangles_5b(5, 6, 7, 6, 1, 3, 6, 3, 7, 5, 7, 8),
gsSPNTriangles_5b(7, 9, 8, 7, 10, 9, 7, 3, 10, 5, 11, 6),
gsSPNTriangles_5b(11, 12, 6, 12, 13, 6, 13, 1, 6, 13, 14, 1),
gsSPNTriangles_5b(14, 2, 1, 4, 15, 3, 15, 10, 3, 16, 10, 15),
gsSPNTriangles_5b(16, 15, 4, 17, 2, 14, 17, 14, 13, 18, 17, 13),
gsSPNTriangles_5b(18, 13, 12, 18, 12, 11, 18, 11, 5, 10, 16, 19),
gsSPNTriangles_5b(9, 10, 19, 8, 9, 19, 8, 19, 5, 19, 16, 17),
gsSPNTriangles_5b(19, 17, 18, 19, 18, 5, 16, 4, 0, 17, 16, 0),
gsSPNTriangles_5b(2, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
