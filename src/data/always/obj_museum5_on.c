#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 obj_museum5_on_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_on_pal.inc"
};

u16 obj_museum5_wallB_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_wallB_pal.inc"
};

u16 obj_museum5_soko_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_soko_pal.inc"
};

u16 obj_museum5_hitode_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_hitode_pal.inc"
};

u16 obj_museum5_evw_tex_rgb_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_evw_tex_rgb_ci4_pal.inc"
};

u8 obj_museum5_isi_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_isi_tex.inc"
};

u8 obj_museum5_pink_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_pink_tex.inc"
};

u8 obj_museum5_inside_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_inside_tex.inc"
};

u8 obj_museum5_soko_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_soko_tex.inc"
};

u8 obj_museum5_wallB_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_wallB_tex.inc"
};

u8 obj_museum5_fuji_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_fuji_tex.inc"
};

u8 obj_museum5_evw_tex_rgb_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_evw_tex_rgb_ci4.inc"
};

static u8 grd_water1_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/grd_water1_tex_rgb_i4.inc"
};

static u8 grd_water2_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_museum5_on/grd_water2_tex_rgb_i4.inc"
};

Vtx obj_museum5_pp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_museum5_on/obj_museum5_pp_v.inc"
};

Gfx obj_museum5_pp_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(1500, 5000, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIM_LOD_FRAC, 0, 1, 0, ENVIRONMENT, COMBINED, 1, 0, PRIMITIVE, COMBINED),
gsDPSetPrimColor(0, 20, 255, 255, 255, 60),
gsDPSetEnvColor(0, 30, 120, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_evw_tex_rgb_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_museum5_evw_tex_rgb_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 1, 1),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&obj_museum5_pp_v[89], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, COMBINED, TEXEL0, 0, SHADE, COMBINED),
gsDPSetEnvColor(150, 255, 255, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, grd_water1_tex_rgb_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, grd_water2_tex_rgb_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPDisplayList(anime_1_txt),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&obj_museum5_pp_v[310], 32, 0),
gsSPNTrianglesInit_5b(22, 0, 1, 2, 1, 3, 2, 4, 5, 1),
gsSPNTriangles_5b(5, 6, 1, 7, 8, 5, 8, 9, 5, 10, 11, 8),
gsSPNTriangles_5b(11, 12, 8, 13, 14, 15, 14, 16, 15, 17, 18, 19),
gsSPNTriangles_5b(18, 20, 19, 2, 3, 21, 22, 2, 21, 0, 2, 22),
gsSPNTriangles_5b(23, 24, 25, 23, 26, 24, 24, 27, 25, 27, 28, 25),
gsSPNTriangles_5b(27, 29, 28, 29, 30, 28, 29, 31, 30, 0, 0, 0),
gsSPVertex(&obj_museum5_pp_v[342], 32, 0),
gsSPNTrianglesInit_5b(19, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(5, 6, 7, 6, 8, 7, 9, 10, 11, 10, 12, 11),
gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 16, 17, 15, 16, 18, 17),
gsSPNTriangles_5b(18, 19, 17, 19, 20, 17, 19, 21, 20, 19, 22, 21),
gsSPNTriangles_5b(23, 24, 25, 24, 26, 27, 28, 29, 26, 30, 28, 23),
gsSPVertex(&obj_museum5_pp_v[373], 16, 0),
gsSPNTrianglesInit_5b(11, 0, 1, 2, 1, 3, 4, 5, 6, 7),
gsSPNTriangles_5b(6, 5, 3, 7, 6, 0, 8, 9, 10, 11, 8, 10),
gsSPNTriangles_5b(12, 11, 10, 12, 10, 13, 14, 15, 12, 13, 14, 12),
gsSPEndDisplayList(),
};

Gfx obj_museum5_pp_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_soko_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_museum5_soko_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(obj_museum5_pp_v, 20, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(4, 5, 3, 4, 6, 5, 0, 7, 1, 7, 8, 1),
gsSPNTriangles_5b(8, 4, 1, 8, 9, 4, 9, 6, 4, 10, 0, 11),
gsSPNTriangles_5b(12, 13, 6, 0, 14, 11, 15, 12, 6, 7, 0, 10),
gsSPNTriangles_5b(2, 14, 0, 16, 12, 15, 16, 17, 12, 17, 13, 12),
gsSPNTriangles_5b(18, 11, 19, 18, 10, 11, 9, 15, 6, 6, 13, 5),
gsSPNTriangles_5b(14, 19, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_wallB_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_museum5_inside_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&obj_museum5_pp_v[20], 21, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(4, 5, 3, 4, 6, 5, 7, 8, 9, 8, 10, 9),
gsSPNTriangles_5b(6, 11, 5, 12, 13, 14, 13, 15, 14, 16, 17, 14),
gsSPNTriangles_5b(16, 18, 17, 12, 19, 13, 12, 20, 19, 20, 2, 19),
gsSPNTriangles_5b(20, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_on_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_museum5_isi_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPVertex(&obj_museum5_pp_v[41], 30, 0),
gsSPNTrianglesInit_5b(33, 0, 1, 2, 3, 4, 5, 4, 6, 5),
gsSPNTriangles_5b(4, 7, 6, 7, 8, 6, 7, 1, 8, 2, 9, 0),
gsSPNTriangles_5b(9, 10, 0, 10, 8, 0, 8, 1, 0, 2, 11, 9),
gsSPNTriangles_5b(10, 12, 8, 12, 6, 8, 12, 13, 6, 13, 5, 6),
gsSPNTriangles_5b(14, 15, 16, 14, 16, 17, 14, 17, 18, 19, 14, 18),
gsSPNTriangles_5b(19, 18, 20, 21, 19, 20, 21, 20, 22, 23, 21, 22),
gsSPNTriangles_5b(17, 16, 24, 17, 24, 25, 18, 17, 25, 18, 25, 26),
gsSPNTriangles_5b(20, 18, 26, 20, 26, 27, 22, 20, 27, 22, 27, 28),
gsSPNTriangles_5b(23, 22, 28, 29, 23, 28, 0, 0, 0, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_museum5_pink_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&obj_museum5_pp_v[71], 18, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 6, 7, 8),
gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_hitode_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_museum5_fuji_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&obj_museum5_pp_v[93], 29, 0),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 6, 7, 8, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(4, 9, 10, 11, 12, 13, 14, 15, 16, 12),
gsSPNTriangles_5b(16, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 17, 18, 19, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 23, 24, 25, 26, 27, 28, 0, 0, 0),
gsSPVertex(&obj_museum5_pp_v[122], 29, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 3, 4, 5, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(4, 6, 7, 8, 9, 6, 8, 8, 7, 10),
gsSPNTriangles_5b(11, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 14, 15, 16, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 17, 18, 19, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 20, 21, 22, 23, 24, 25, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 26, 27, 28, 0, 0, 0, 0, 0, 0),
gsSPVertex(&obj_museum5_pp_v[151], 29, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(4, 3, 4, 5, 6, 7, 8, 9, 10, 6),
gsSPNTriangles_5b(10, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 14, 15, 16, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 17, 18, 19, 20, 21, 22, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 26, 27, 28, 0, 0, 0, 0, 0, 0),
gsSPVertex(&obj_museum5_pp_v[180], 26, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 2, 1, 4),
gsSPNTriangles_5b(5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 14, 15, 16, 17, 18, 19, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
gsSPVertex(&obj_museum5_pp_v[206], 26, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 3),
gsSPNTriangles_5b(7, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 14, 15, 16, 17, 18, 19, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
gsSPVertex(&obj_museum5_pp_v[232], 26, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 2, 1, 4),
gsSPNTriangles_5b(5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 14, 15, 16, 17, 18, 19, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
gsSPVertex(&obj_museum5_pp_v[258], 26, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 2, 1, 4),
gsSPNTriangles_5b(5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 14, 15, 16, 17, 18, 19, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 20, 21, 22, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 23, 24, 25, 0, 0, 0, 0, 0, 0),
gsSPVertex(&obj_museum5_pp_v[284], 17, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 7, 3),
gsSPNTriangles_5b(7, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 8, 9, 10, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 11, 12, 13, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(1, 14, 15, 16, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_museum5_wallB_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_museum5_wallB_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&obj_museum5_pp_v[301], 9, 0),
gsSPNTrianglesInit_5b(7, 0, 1, 2, 1, 3, 2, 2, 3, 4),
gsSPNTriangles_5b(2, 4, 5, 6, 5, 4, 6, 7, 5, 7, 8, 5),
gsSPEndDisplayList(),
};
