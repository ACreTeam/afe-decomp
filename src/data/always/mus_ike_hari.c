#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

u16 mus_ike_hari_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_hari/mus_ike_hari_pal.inc"
};

u8 act_mus_hari2_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_hari/act_mus_hari2_body_tex_txt.inc"
};

u8 act_mus_hari3_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_hari/act_mus_hari3_body_tex_txt.inc"
};

u8 act_mus_hari1_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_hari/act_mus_hari1_body_tex_txt.inc"
};

Vtx act_mus_hari_a1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_ike_hari/act_mus_hari_a1_v.inc"
};

Gfx act_mus_hari_sakana_bodyhari_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_mus_hari_a1_v, 14, 0),
gsSPMatrix(&anime_6_mdl[3], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_hari_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_hari_a1_v[14], 15, 14),
gsSPNTrianglesInit_5b(2, 0, 1, 14, 1, 16, 15, 0, 0, 0),
gsSPNTrianglesInit_5b(2, 3, 2, 17, 2, 19, 18, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 20, 5, 22, 21, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 7, 6, 23, 6, 25, 24, 0, 0, 0),
gsSPNTrianglesInit_5b(2, 8, 9, 26, 9, 28, 27, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&act_mus_hari_a1_v[29], 14, 14),
gsSPNTrianglesInit_5b(2, 11, 10, 14, 10, 16, 15, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 13, 12, 17, 12, 19, 18, 0, 0, 0),
gsSPNTrianglesInit_5b(6, 20, 21, 22, 20, 22, 23, 24, 20, 23),
gsSPNTriangles_5b(24, 23, 25, 25, 26, 27, 25, 27, 24, 0, 0, 0),
gsSPVertex(&act_mus_hari_a1_v[43], 24, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(4, 3, 5, 5, 6, 7, 5, 7, 4, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 10, 11, 12, 8, 11),
gsSPNTriangles_5b(12, 11, 13, 13, 14, 15, 13, 15, 12, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 16, 17, 18, 16, 18, 19, 20, 16, 19),
gsSPNTriangles_5b(20, 19, 21, 21, 22, 23, 21, 23, 20, 0, 0, 0),
gsSPVertex(&act_mus_hari_a1_v[67], 24, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 7, 0, 3, 7, 3, 4, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 10, 11, 9, 12, 13),
gsSPNTriangles_5b(9, 13, 10, 11, 14, 15, 11, 15, 8, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 16, 17, 18, 16, 18, 19, 17, 20, 21),
gsSPNTriangles_5b(17, 21, 18, 19, 22, 23, 19, 23, 16, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_hari_sakana_body_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_hari_a1_v[91], 8, 0),
gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_hari_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari1_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_hari_a1_v[99], 18, 8),
gsSPNTrianglesInit_5b(9, 6, 0, 8, 7, 5, 9, 7, 10, 11),
gsSPNTriangles_5b(3, 2, 12, 5, 4, 13, 2, 14, 15, 2, 6, 16),
gsSPNTriangles_5b(5, 17, 18, 2, 19, 20, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(3, 6, 22, 21, 1, 7, 23, 7, 24, 25),
gsSPVertex(&act_mus_hari_a1_v[117], 32, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(29, 0, 1, 2, 0, 3, 4, 5, 6, 0),
gsSPNTriangles_5b(7, 8, 9, 0, 4, 1, 3, 0, 6, 9, 10, 11),
gsSPNTriangles_5b(11, 7, 9, 9, 12, 13, 13, 10, 9, 0, 2, 5),
gsSPNTriangles_5b(6, 14, 3, 12, 9, 8, 15, 16, 17, 18, 12, 19),
gsSPNTriangles_5b(20, 21, 22, 8, 23, 12, 5, 24, 25, 24, 5, 26),
gsSPNTriangles_5b(27, 28, 19, 14, 6, 17, 17, 16, 29, 19, 12, 23),
gsSPNTriangles_5b(17, 6, 30, 19, 28, 31, 23, 27, 19, 17, 29, 14),
gsSPNTriangles_5b(31, 18, 19, 17, 30, 15, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_hari_a1_v[149], 31, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 6, 7, 8),
gsSPNTriangles_5b(9, 10, 11, 6, 8, 12, 13, 14, 15, 12, 16, 17),
gsSPNTriangles_5b(15, 9, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(7, 18, 19, 20, 21, 22, 23, 24, 23, 22),
gsSPNTriangles_5b(21, 23, 25, 20, 26, 18, 18, 27, 28, 29, 30, 21),
gsSPEndDisplayList(),
};

Gfx act_mus_hari_sakana_headhari_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_hari_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_hari_a1_v[180], 24, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
gsSPNTrianglesInit_5b(6, 12, 13, 14, 12, 14, 15, 16, 17, 18),
gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&act_mus_hari_a1_v[204], 24, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 12, 13, 14, 12, 14, 15, 16, 17, 18),
gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
gsSPVertex(&act_mus_hari_a1_v[228], 28, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 12, 13, 14, 12, 14, 15, 16, 17, 18),
gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 24, 25, 26, 24, 26, 27, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_hari_sakana_head_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_hari_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hari1_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_hari_a1_v[256], 20, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 6, 7, 8),
gsSPNTriangles_5b(9, 10, 11, 5, 12, 3, 0, 6, 13, 0, 13, 1),
gsSPNTriangles_5b(5, 9, 14, 0, 15, 16, 2, 15, 0, 4, 10, 9),
gsSPNTriangles_5b(4, 9, 5, 9, 17, 14, 16, 6, 0, 14, 12, 5),
gsSPNTriangles_5b(8, 13, 6, 11, 18, 9, 6, 19, 7, 18, 17, 9),
gsSPNTriangles_5b(16, 19, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_hari_a1_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 8, 85, 1095 } },
	{ act_mus_hari_sakana_head_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ act_mus_hari_sakana_headhari_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ act_mus_hari_sakana_body_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 942, 0, 0 } },
	{ act_mus_hari_sakana_bodyhari_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_hari_a1 = 
	{ ARRAY_COUNT(cKF_je_r_act_mus_hari_a1_tbl), 4, cKF_je_r_act_mus_hari_a1_tbl }
;
