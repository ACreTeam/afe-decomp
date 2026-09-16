#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

u16 mus_ike_tatu_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_tatu/mus_ike_tatu_pal.inc"
};

u8 act_mus_tatu_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_tatu/act_mus_tatu_body_tex_txt.inc"
};

Vtx act_mus_tatu_a1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_ike_tatu/act_mus_tatu_a1_v.inc"
};

Gfx act_mus_tatu_sakana_head_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_tatu_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_mus_tatu_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_mus_tatu_a1_v, 17, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 6, 4, 3),
gsSPNTriangles_5b(7, 1, 0, 8, 0, 9, 10, 11, 12, 0, 3, 5),
gsSPNTriangles_5b(6, 3, 0, 10, 13, 2, 6, 0, 13, 6, 13, 14),
gsSPNTriangles_5b(15, 13, 12, 0, 8, 7, 2, 13, 0, 2, 1, 10),
gsSPNTriangles_5b(12, 13, 10, 12, 11, 15, 15, 16, 14, 14, 13, 15),
gsSPNTriangles_5b(14, 16, 6, 9, 0, 5, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_tatu_a1_v[17], 17, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 5, 6, 7),
gsSPNTriangles_5b(8, 9, 10, 11, 12, 4, 2, 1, 4, 4, 3, 2),
gsSPNTriangles_5b(2, 3, 0, 13, 14, 15, 10, 9, 0, 15, 14, 5),
gsSPNTriangles_5b(4, 1, 11, 10, 3, 8, 8, 3, 7, 16, 4, 12),
gsSPNTriangles_5b(7, 6, 8, 7, 3, 5, 0, 3, 10, 13, 15, 4),
gsSPNTriangles_5b(13, 4, 16, 4, 15, 5, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_tatu_sakana_foot_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_tatu_a1_v[34], 6, 0),
gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_tatu_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_mus_tatu_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_tatu_a1_v[40], 23, 6),
gsSPNTrianglesInit_5b(4, 0, 6, 3, 3, 7, 1, 1, 9, 8),
gsSPNTriangles_5b(0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(3, 2, 12, 5, 5, 13, 4, 4, 14, 15),
gsSPNTrianglesInit_5b(5, 16, 17, 18, 19, 20, 18, 18, 17, 21),
gsSPNTriangles_5b(18, 22, 16, 18, 20, 22, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 23, 24, 25, 25, 26, 23, 25, 27, 28),
gsSPNTriangles_5b(24, 27, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_tatu_a1_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 6422 } },
	{ NULL, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
	{ act_mus_tatu_sakana_foot_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ act_mus_tatu_sakana_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_tatu_a1 = 
	{ ARRAY_COUNT(cKF_je_r_act_mus_tatu_a1_tbl), 2, cKF_je_r_act_mus_tatu_a1_tbl }
;
