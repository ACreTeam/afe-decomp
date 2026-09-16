#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 obj_item_shell_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_shellC/obj_item_shell_pal.inc"
};

u8 obj_item_shellC_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_item_shellC/obj_item_shellC_tex.inc"
};

Vtx obj_item_shellC_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_item_shellC/obj_item_shellC_v.inc"
};

Gfx obj_item_shellCT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_item_shell_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_item_shellC_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_item_shellCT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_item_shellC_v, 32, 0),
gsSPNTrianglesInit_5b(50, 0, 1, 2, 1, 3, 4, 1, 4, 2),
gsSPNTriangles_5b(5, 6, 7, 5, 8, 6, 5, 9, 8, 9, 10, 11),
gsSPNTriangles_5b(9, 12, 10, 10, 13, 11, 10, 12, 13, 9, 14, 12),
gsSPNTriangles_5b(15, 16, 17, 15, 18, 16, 15, 14, 18, 18, 9, 16),
gsSPNTriangles_5b(18, 14, 9, 15, 19, 14, 11, 20, 9, 11, 13, 20),
gsSPNTriangles_5b(12, 19, 13, 12, 14, 19, 13, 0, 20, 16, 21, 17),
gsSPNTriangles_5b(21, 5, 17, 5, 7, 17, 5, 21, 9, 21, 16, 9),
gsSPNTriangles_5b(6, 4, 3, 6, 8, 4, 8, 9, 4, 9, 20, 4),
gsSPNTriangles_5b(2, 20, 0, 2, 4, 20, 22, 1, 0, 22, 23, 3),
gsSPNTriangles_5b(22, 3, 1, 7, 6, 24, 6, 25, 24, 25, 26, 24),
gsSPNTriangles_5b(27, 28, 26, 28, 29, 26, 27, 13, 28, 13, 29, 28),
gsSPNTriangles_5b(29, 30, 26, 17, 31, 15, 31, 18, 15, 18, 30, 15),
gsSPNTriangles_5b(31, 26, 18, 26, 30, 18, 30, 19, 15, 0, 0, 0),
gsSPVertex(&obj_item_shellC_v[32], 18, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 3, 4, 5),
gsSPNTriangles_5b(4, 6, 5, 1, 7, 3, 8, 9, 10, 8, 11, 9),
gsSPNTriangles_5b(8, 12, 11, 0, 9, 11, 0, 10, 9, 13, 14, 15),
gsSPNTriangles_5b(14, 16, 15, 14, 0, 16, 14, 1, 0, 7, 1, 17),
gsSPNTriangles_5b(1, 14, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
