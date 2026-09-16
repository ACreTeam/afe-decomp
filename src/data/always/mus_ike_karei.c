#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

u16 mus_ike_karei_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_karei/mus_ike_karei_pal.inc"
};

u8 act_mus_karei_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_karei/act_mus_karei_body_tex_txt.inc"
};

Vtx act_mus_karei_a1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_ike_karei/act_mus_karei_a1_v.inc"
};

Gfx act_mus_karei_sakana_body_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_mus_karei_a1_v, 10, 0),
gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_karei_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_karei_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_karei_a1_v[10], 20, 10),
gsSPNTrianglesInit_5b(12, 4, 11, 10, 5, 13, 12, 5, 15, 14),
gsSPNTriangles_5b(6, 9, 16, 9, 17, 18, 8, 7, 19, 8, 20, 21),
gsSPNTriangles_5b(8, 22, 4, 5, 23, 9, 0, 24, 25, 1, 26, 27),
gsSPNTriangles_5b(4, 29, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_karei_a1_v[30], 4, 10),
gsSPNTrianglesInit_5b(4, 3, 4, 10, 5, 2, 11, 0, 3, 12),
gsSPNTriangles_5b(2, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_karei_a1_v[34], 32, 0),
gsSPNTrianglesInit_5b(32, 0, 1, 2, 3, 4, 2, 5, 6, 7),
gsSPNTriangles_5b(8, 9, 10, 8, 10, 11, 12, 13, 14, 1, 3, 2),
gsSPNTriangles_5b(15, 16, 17, 18, 9, 8, 12, 14, 19, 8, 20, 12),
gsSPNTriangles_5b(21, 13, 12, 22, 23, 24, 25, 26, 16, 27, 21, 22),
gsSPNTriangles_5b(16, 15, 28, 24, 27, 22, 16, 28, 25, 2, 4, 15),
gsSPNTriangles_5b(21, 12, 20, 20, 22, 21, 17, 2, 15, 12, 19, 29),
gsSPNTriangles_5b(29, 18, 12, 2, 7, 0, 30, 5, 17, 20, 8, 11),
gsSPNTriangles_5b(2, 17, 5, 30, 31, 6, 30, 6, 5, 7, 2, 5),
gsSPNTriangles_5b(8, 12, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_karei_sakana_head_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_karei_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_karei_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_karei_a1_v[66], 10, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 2, 6, 0),
gsSPNTriangles_5b(3, 7, 4, 1, 8, 2, 5, 9, 3, 0, 0, 0),
gsSPVertex(&act_mus_karei_a1_v[76], 31, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 7, 0),
gsSPNTriangles_5b(5, 8, 9, 7, 10, 0, 5, 11, 8, 0, 10, 1),
gsSPNTriangles_5b(12, 13, 14, 4, 11, 5, 15, 16, 17, 9, 16, 5),
gsSPNTriangles_5b(0, 18, 6, 0, 12, 19, 17, 20, 15, 19, 18, 0),
gsSPNTriangles_5b(21, 22, 20, 5, 20, 3, 2, 12, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 23, 24, 25, 26, 27, 28, 29, 24, 23),
gsSPNTriangles_5b(28, 27, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_karei_a1_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 2, 65533, 1203 } },
	{ act_mus_karei_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ act_mus_karei_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_karei_a1 = 
	{ ARRAY_COUNT(cKF_je_r_act_mus_karei_a1_tbl), 2, cKF_je_r_act_mus_karei_a1_tbl }
;
