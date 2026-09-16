#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 obj_tree_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_tree/obj_tree_pal.inc"
};

static u8 obj_s_tree_trunk_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_tree/obj_s_tree_trunk_tex.inc"
};

static u8 obj_s_tree_leaf_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_tree/obj_s_tree_leaf_tex.inc"
};

Vtx rom_museum4_pp_jama_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_tree/rom_museum4_pp_jama_v.inc"
};

Gfx rom_museum4_pp_jama_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_tree_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_trunk_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(rom_museum4_pp_jama_v, 7, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 2, 5),
gsSPNTriangles_5b(4, 0, 2, 5, 2, 6, 2, 3, 6, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_leaf_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_jama_v[7], 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 3, 2),
gsSPNTriangles_5b(1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_leaf_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_jama_v[12], 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 3, 2, 4),
gsSPNTriangles_5b(1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_leaf_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_jama_v[17], 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 2, 1, 4, 0, 2),
gsSPNTriangles_5b(3, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
