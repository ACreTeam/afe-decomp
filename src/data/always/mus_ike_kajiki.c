#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

u16 mus_ike_kajiki_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_kajiki/mus_ike_kajiki_pal.inc"
};

u8 act_mus_kajiki_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_kajiki/act_mus_kajiki_body_tex_txt.inc"
};

Vtx act_mus_kajiki_a1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_ike_kajiki/act_mus_kajiki_a1_v.inc"
};

Gfx act_mus_kajiki_sakana_body_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_mus_kajiki_a1_v, 6, 0),
gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_kajiki_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_kajiki_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_kajiki_a1_v[6], 12, 6),
gsSPNTrianglesInit_5b(8, 0, 6, 2, 4, 7, 0, 1, 8, 5),
gsSPNTriangles_5b(3, 9, 1, 2, 10, 11, 3, 12, 13, 1, 15, 14),
gsSPNTriangles_5b(0, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_kajiki_a1_v[18], 24, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 3, 4, 5, 0, 2),
gsSPNTriangles_5b(6, 7, 8, 0, 4, 1, 5, 9, 10, 8, 11, 12),
gsSPNTriangles_5b(12, 6, 8, 11, 8, 13, 14, 15, 16, 9, 17, 10),
gsSPNTriangles_5b(18, 19, 20, 18, 20, 13, 21, 22, 23, 13, 8, 7),
gsSPNTriangles_5b(5, 10, 3, 7, 18, 13, 3, 0, 5, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_kajiki_sakana_head_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_kajiki_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_mus_kajiki_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_kajiki_a1_v[42], 14, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 0, 2),
gsSPNTriangles_5b(3, 5, 7, 0, 8, 9, 5, 10, 11, 12, 8, 0),
gsSPNTriangles_5b(13, 10, 5, 11, 7, 5, 0, 6, 12, 5, 4, 13),
gsSPNTriangles_5b(9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_kajiki_a1_v[56], 18, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 1, 6, 7),
gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 9, 13, 12, 14),
gsSPNTriangles_5b(7, 4, 3, 14, 9, 13, 3, 1, 7, 3, 5, 16),
gsSPNTriangles_5b(17, 11, 13, 13, 8, 17, 16, 2, 3, 13, 9, 8),
gsSPNTriangles_5b(2, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_kajiki_a1_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8, 65519, 2311 } },
	{ act_mus_kajiki_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ act_mus_kajiki_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 3100, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_kajiki_a1 = 
	{ ARRAY_COUNT(cKF_je_r_act_mus_kajiki_a1_tbl), 2, cKF_je_r_act_mus_kajiki_a1_tbl }
;
