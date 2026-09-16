#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 grd_wave1_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/grd_wave1_tex_rgb_ia8/grd_wave1_tex_rgb_ia8.inc"
};

u8 grd_wave2_tex_rgb_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/grd_wave1_tex_rgb_ia8/grd_wave2_tex_rgb_ia8.inc"
};

static u8 grd_water1_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/grd_wave1_tex_rgb_ia8/grd_water1_tex_rgb_i4.inc"
};

static u8 grd_water2_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/grd_wave1_tex_rgb_ia8/grd_water2_tex_rgb_i4.inc"
};

Vtx obj_museum4_pp_water_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/grd_wave1_tex_rgb_ia8/obj_museum4_pp_water_v.inc"
};

Gfx obj_museum4_pp_water_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, grd_wave1_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, grd_wave2_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPDisplayList(anime_1_txt),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(obj_museum4_pp_water_v, 14, 0),
gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 4, 2, 5),
gsSPNTriangles_5b(2, 1, 5, 0, 6, 1, 0, 7, 6, 7, 8, 6),
gsSPNTriangles_5b(8, 9, 10, 6, 8, 10, 6, 10, 11, 1, 6, 11),
gsSPNTriangles_5b(5, 1, 11, 5, 11, 12, 3, 5, 12, 13, 3, 12),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0, SHADE, TEXEL0, COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE),
gsDPSetPrimColor(0, 50, 255, 255, 255, 50),
gsDPSetEnvColor(0, 60, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, grd_water1_tex_rgb_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, grd_water2_tex_rgb_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPDisplayList(anime_2_txt),
gsSPVertex(&obj_museum4_pp_water_v[14], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
