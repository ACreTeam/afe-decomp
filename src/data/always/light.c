#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 obj_cedar_light_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/light/obj_cedar_light_pal.inc"
};

u8 obj_x_cedar_light_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/light/obj_x_cedar_light_tex.inc"
};

Vtx obj_x_cedar5_light_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/light/obj_x_cedar5_light_v.inc"
};

Gfx obj_x_ceder5_lightT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_cedar_light_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_x_cedar_light_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_x_ceder5_lightT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_x_cedar5_light_v, 28, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 0, 2, 4, 5, 6),
gsSPNTriangles_5b(7, 4, 6, 8, 9, 10, 11, 8, 10, 12, 11, 13),
gsSPNTriangles_5b(14, 12, 13, 12, 15, 16, 9, 12, 16, 8, 14, 17),
gsSPNTriangles_5b(15, 8, 17, 18, 19, 20, 19, 21, 20, 22, 23, 24),
gsSPNTriangles_5b(23, 18, 24, 21, 23, 25, 23, 26, 25, 26, 19, 27),
gsSPNTriangles_5b(19, 22, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
