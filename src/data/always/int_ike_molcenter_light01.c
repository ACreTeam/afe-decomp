#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

u16 int_ike_molcenter_lightin1_pic_ci4_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/int_ike_molcenter_light01/int_ike_molcenter_lightin1_pic_ci4_pal.inc"
};

u8 int_ike_molcenter_lightin1_pic_ci4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/int_ike_molcenter_light01/int_ike_molcenter_lightin1_pic_ci4.inc"
};

u8 int_ike_molcenter_light1_pic_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/int_ike_molcenter_light01/int_ike_molcenter_light1_pic_ia8.inc"
};

Vtx int_ike_molcenter_light01_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/int_ike_molcenter_light01/int_ike_molcenter_light01_v.inc"
};

Gfx int_ike_molcenter_lightin2_off_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_molcenter_lightin1_pic_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_molcenter_lightin1_pic_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&int_ike_molcenter_light01_v[12], 9, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 4, 2, 3, 0),
gsSPNTriangles_5b(5, 1, 0, 6, 5, 0, 7, 6, 0, 8, 7, 0),
gsSPNTriangles_5b(4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx int_ike_molcenter_lightin1_off_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(4800, 4000, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_molcenter_lightin1_pic_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_molcenter_lightin1_pic_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&int_ike_molcenter_light01_v[21], 9, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 4, 2, 3, 0),
gsSPNTriangles_5b(5, 1, 0, 6, 5, 0, 7, 6, 0, 8, 7, 0),
gsSPNTriangles_5b(4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx int_ike_molcenter_ball2_off_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(4800, 4000, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_molcenter_lightin1_pic_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_molcenter_lightin1_pic_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&int_ike_molcenter_light01_v[30], 12, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 1, 0, 3, 1, 3, 4),
gsSPNTriangles_5b(4, 3, 5, 6, 0, 2, 0, 6, 7, 0, 7, 3),
gsSPNTriangles_5b(3, 7, 5, 8, 6, 2, 6, 8, 9, 6, 9, 7),
gsSPNTriangles_5b(7, 9, 5, 10, 8, 2, 8, 10, 11, 8, 11, 9),
gsSPNTriangles_5b(9, 11, 5, 1, 10, 2, 10, 1, 4, 10, 4, 11),
gsSPNTriangles_5b(11, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx int_ike_molcenter_ball1_off_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_molcenter_lightin1_pic_ci4_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, int_ike_molcenter_lightin1_pic_ci4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 3, 3),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(int_ike_molcenter_light01_v, 12, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 2, 3, 2, 1),
gsSPNTriangles_5b(5, 4, 3, 0, 2, 6, 4, 7, 6, 4, 6, 2),
gsSPNTriangles_5b(5, 7, 4, 0, 6, 8, 7, 9, 8, 7, 8, 6),
gsSPNTriangles_5b(5, 9, 7, 0, 8, 10, 9, 11, 10, 9, 10, 8),
gsSPNTriangles_5b(5, 11, 9, 0, 10, 1, 11, 3, 1, 11, 1, 10),
gsSPNTriangles_5b(5, 3, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx int_ike_molcenter_light1_off_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(4100, 4400, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 170, 170, 255),
gsDPSetEnvColor(200, 0, 0, 210),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, int_ike_molcenter_light1_pic_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 1, 1),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&int_ike_molcenter_light01_v[42], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 4, 4, 3, 5),
gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 2),
gsSPNTriangles_5b(14, 15, 3, 3, 15, 16, 16, 17, 6, 10, 18, 19),
gsSPNTriangles_5b(20, 21, 9, 22, 14, 2, 22, 13, 15, 15, 13, 12),
gsSPNTriangles_5b(12, 23, 17, 24, 19, 1, 23, 12, 11, 25, 22, 2),
gsSPNTriangles_5b(25, 26, 13, 13, 26, 11, 11, 27, 23, 28, 8, 29),
gsSPNTriangles_5b(30, 31, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&int_ike_molcenter_light01_v[74], 32, 0),
gsSPNTrianglesInit_5b(29, 0, 1, 2, 0, 3, 4, 4, 3, 5),
gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 6, 5, 11, 12, 0, 2),
gsSPNTriangles_5b(12, 13, 3, 3, 13, 11, 11, 14, 6, 15, 16, 17),
gsSPNTriangles_5b(18, 19, 9, 20, 12, 2, 20, 21, 13, 13, 21, 22),
gsSPNTriangles_5b(22, 23, 14, 24, 8, 15, 11, 5, 3, 25, 20, 2),
gsSPNTriangles_5b(25, 26, 21, 21, 26, 19, 19, 18, 23, 27, 17, 28),
gsSPNTriangles_5b(19, 22, 21, 29, 25, 2, 29, 10, 26, 26, 10, 9),
gsSPNTriangles_5b(9, 30, 18, 31, 24, 27, 0, 0, 0, 0, 0, 0),
gsSPVertex(&int_ike_molcenter_light01_v[106], 31, 0),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 5, 3, 6, 7),
gsSPNTriangles_5b(7, 6, 8, 8, 9, 10, 11, 12, 13, 14, 1, 0),
gsSPNTriangles_5b(15, 13, 16, 2, 16, 17, 18, 17, 19, 9, 8, 20),
gsSPNTriangles_5b(21, 20, 22, 23, 22, 24, 24, 22, 11, 25, 19, 26),
gsSPNTriangles_5b(27, 26, 28, 29, 30, 25, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_int_ike_molcenter_light01_tbl[] = {
0,
7,
0,
0,
0
};

s16 cKF_kn_int_ike_molcenter_light01_tbl[] = {
2,
2,
2
};

s16 cKF_c_int_ike_molcenter_light01_tbl[] = {
0,
0,
0,
0,
0,
-900,
0,
0,
0,
0,
0,
0,
0,
0,
0
};

s16 cKF_ds_int_ike_molcenter_light01_tbl[] = {
1,
40,
1197,
90,
3600,
0,
1,
0,
0,
90,
0,
0,
1,
-1800,
0,
90,
-1800,
0
};

cKF_Animation_R_c cKF_ba_r_int_ike_molcenter_light01 = 
	{ cKF_ckcb_r_int_ike_molcenter_light01_tbl, cKF_ds_int_ike_molcenter_light01_tbl, cKF_kn_int_ike_molcenter_light01_tbl, cKF_c_int_ike_molcenter_light01_tbl, -1, 90 }
;

cKF_Joint_R_c cKF_je_r_int_ike_molcenter_light01_tbl[] = {
	{ int_ike_molcenter_light1_off_model, 1, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
	{ int_ike_molcenter_ball1_off_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ int_ike_molcenter_ball2_off_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ int_ike_molcenter_lightin1_off_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ int_ike_molcenter_lightin2_off_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_int_ike_molcenter_light01 = 
	{ ARRAY_COUNT(cKF_je_r_int_ike_molcenter_light01_tbl), 5, cKF_je_r_int_ike_molcenter_light01_tbl }
;
