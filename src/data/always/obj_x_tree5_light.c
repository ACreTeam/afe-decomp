#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

extern u16 obj_tree_light_pal[];

u8 obj_x_tree_light_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_x_tree5_light/obj_x_tree_light_tex.inc"
};

Vtx obj_x_tree5_light_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_x_tree5_light/obj_x_tree5_light_v.inc"
};

Gfx obj_x_tree5_lightT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_tree_light_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_x_tree_light_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_x_tree5_lightT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_x_tree5_light_v, 12, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 0, 0, 0),
gsSPEndDisplayList(),
};
