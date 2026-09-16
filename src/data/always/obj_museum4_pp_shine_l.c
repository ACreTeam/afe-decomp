#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u8 obj_museum4_shine_1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum4_pp_shine_l/obj_museum4_shine_1.inc"
};

static u8 obj_museum4_shine_2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum4_pp_shine_l/obj_museum4_shine_2.inc"
};

Vtx obj_museum4_pp_shine_l_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_museum4_pp_shine_l/obj_museum4_pp_shine_l_v.inc"
};

Gfx obj_museum4_pp_shine_l_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, obj_museum4_shine_2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(obj_museum4_pp_shine_l_v, 24, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 1, 4, 2),
gsSPNTriangles_5b(1, 5, 4, 3, 6, 1, 6, 7, 1, 7, 8, 1),
gsSPNTriangles_5b(8, 5, 1, 6, 9, 7, 6, 10, 9, 9, 8, 7),
gsSPNTriangles_5b(9, 11, 8, 10, 12, 9, 12, 13, 9, 13, 14, 9),
gsSPNTriangles_5b(14, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_GEQUAL),
gsSPNTrianglesInit_5b(8, 15, 16, 17, 15, 18, 16, 16, 19, 17),
gsSPNTriangles_5b(16, 20, 19, 18, 21, 16, 21, 22, 16, 22, 23, 16),
gsSPNTriangles_5b(23, 20, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPClearGeometryMode(G_DECAL_GEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_museum4_pp_shine_l_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, obj_museum4_shine_1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&obj_museum4_pp_shine_l_v[24], 8, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 4, 0, 2, 3),
gsSPNTriangles_5b(4, 3, 5, 4, 5, 6, 6, 5, 7, 5, 1, 7),
gsSPNTriangles_5b(7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
