#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 obj_tent_lamp1_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_tent/obj_tent_lamp1_rgb_ci4_pal.inc"
};

u16 obj_tent_lamp2_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_tent/obj_tent_lamp2_rgb_ci4_pal.inc"
};

u8 obj_tent_lamp1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_tent/obj_tent_lamp1.inc"
};

u8 obj_tent_lamp2_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_tent/obj_tent_lamp2_rgb_ci4.inc"
};

Vtx obj_tent_lamp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_tent/obj_tent_lamp_v.inc"
};

Gfx obj_tent_lamp_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_tent_lamp1_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_tent_lamp1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsDPLoadTLUT_Dolphin(14, 16, 1, obj_tent_lamp2_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_tent_lamp2_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 14, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(obj_tent_lamp_v, 32, 0),
gsSPNTrianglesInit_5b(19, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 11, 10, 16, 11, 16, 17, 15, 14, 9),
gsSPNTriangles_5b(15, 9, 8, 18, 19, 13, 18, 13, 12, 20, 21, 22),
gsSPNTriangles_5b(22, 23, 24, 25, 26, 20, 27, 28, 25, 24, 29, 30),
gsSPVertex(&obj_tent_lamp_v[31], 14, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 3),
gsSPNTriangles_5b(8, 9, 10, 11, 12, 6, 10, 13, 11, 0, 0, 0),
gsSPEndDisplayList(),
};
