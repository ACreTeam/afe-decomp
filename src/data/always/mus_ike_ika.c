#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

u16 mus_ike_ika_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_ika/mus_ike_ika_pal.inc"
};

u8 act_mus_ika2_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_ika/act_mus_ika2_body_tex_txt.inc"
};

u8 act_mus_ika3_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_ika/act_mus_ika3_body_tex_txt.inc"
};

u8 act_mus_ika1_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_ika/act_mus_ika1_body_tex_txt.inc"
};

Vtx act_mus_ika_a1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_ike_ika/act_mus_ika_a1_v.inc"
};

Gfx act_mus_ika_foot_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_mus_ika_a1_v, 20, 0),
gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_ika_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_ika2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_ika_a1_v[20], 6, 20),
gsSPNTrianglesInit_5b(4, 7, 9, 20, 7, 21, 22, 8, 7, 23),
gsSPNTriangles_5b(8, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_ika_a1_v[26], 6, 20),
gsSPNTrianglesInit_5b(4, 6, 20, 21, 6, 4, 22, 4, 23, 24),
gsSPNTriangles_5b(4, 5, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_ika_a1_v[32], 10, 20),
gsSPNTrianglesInit_5b(6, 2, 20, 21, 3, 22, 23, 3, 24, 25),
gsSPNTriangles_5b(2, 26, 27, 1, 3, 28, 3, 0, 29, 0, 0, 0),
gsSPVertex(&act_mus_ika_a1_v[42], 8, 20),
gsSPNTrianglesInit_5b(2, 2, 1, 20, 0, 2, 21, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 19, 22, 23, 19, 17, 24, 17, 25, 26),
gsSPNTriangles_5b(17, 18, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_ika_a1_v[50], 6, 20),
gsSPNTrianglesInit_5b(4, 14, 16, 20, 14, 21, 22, 15, 14, 23),
gsSPNTriangles_5b(15, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_ika_a1_v[56], 10, 20),
gsSPNTrianglesInit_5b(6, 12, 20, 21, 13, 22, 23, 13, 24, 25),
gsSPNTriangles_5b(12, 26, 27, 13, 11, 28, 10, 13, 29, 0, 0, 0),
gsSPVertex(&act_mus_ika_a1_v[66], 8, 20),
gsSPNTrianglesInit_5b(2, 11, 12, 20, 12, 10, 21, 0, 0, 0),
gsSPNTrianglesInit_5b(6, 22, 23, 24, 24, 23, 25, 23, 26, 25),
gsSPNTriangles_5b(24, 27, 22, 22, 26, 23, 25, 27, 24, 0, 0, 0),
gsSPVertex(&act_mus_ika_a1_v[74], 18, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 5, 2, 3),
gsSPNTriangles_5b(0, 2, 5, 5, 4, 0, 2, 1, 3, 0, 0, 0),
gsSPNTrianglesInit_5b(6, 6, 7, 8, 9, 7, 6, 9, 10, 7),
gsSPNTriangles_5b(8, 11, 6, 7, 10, 8, 6, 11, 9, 0, 0, 0),
gsSPNTrianglesInit_5b(6, 12, 13, 14, 15, 16, 17, 17, 12, 15),
gsSPNTriangles_5b(15, 12, 14, 14, 16, 15, 17, 13, 12, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_ika_head_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_ika_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_ika3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_ika_a1_v[92], 31, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 2, 4, 5),
gsSPNTriangles_5b(1, 4, 2, 6, 3, 5, 6, 7, 8, 3, 9, 0),
gsSPNTriangles_5b(5, 3, 2, 5, 7, 6, 3, 6, 8, 3, 8, 10),
gsSPNTriangles_5b(10, 11, 9, 9, 11, 0, 10, 9, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_ika1_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(14, 12, 13, 14, 12, 14, 15, 12, 16, 17),
gsSPNTriangles_5b(17, 18, 19, 17, 19, 12, 20, 12, 19, 15, 21, 16),
gsSPNTriangles_5b(16, 21, 17, 13, 22, 14, 15, 16, 12, 20, 22, 13),
gsSPNTriangles_5b(19, 23, 20, 18, 23, 19, 13, 12, 20, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_ika2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(8, 24, 25, 26, 26, 27, 24, 26, 25, 28),
gsSPNTriangles_5b(25, 24, 29, 29, 24, 27, 30, 28, 25, 28, 27, 26),
gsSPNTriangles_5b(27, 28, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_ika_a1_v[123], 31, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 1, 3, 0, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 6, 5, 7, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 9),
gsSPNTriangles_5b(12, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 14, 15, 16, 16, 15, 17, 16, 17, 18),
gsSPNTriangles_5b(14, 19, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(8, 20, 21, 22, 22, 23, 20, 24, 21, 20),
gsSPNTriangles_5b(25, 22, 21, 23, 22, 25, 21, 24, 26, 20, 23, 24),
gsSPNTriangles_5b(26, 24, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(2, 27, 28, 29, 30, 28, 27, 0, 0, 0),
gsSPVertex(&act_mus_ika_a1_v[154], 16, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 1, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 4, 5, 6, 4, 6, 7, 7, 6, 8),
gsSPNTriangles_5b(7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 10, 11, 12, 13, 14, 15, 13, 15, 10),
gsSPNTriangles_5b(10, 15, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_ika_a1_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 3, 65532, 49 } },
	{ act_mus_ika_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ act_mus_ika_foot_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 49, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_ika_a1 = 
	{ ARRAY_COUNT(cKF_je_r_act_mus_ika_a1_tbl), 2, cKF_je_r_act_mus_ika_a1_tbl }
;
