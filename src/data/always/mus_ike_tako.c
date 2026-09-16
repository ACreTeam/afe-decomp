#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

u16 mus_ike_tako_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_tako/mus_ike_tako_pal.inc"
};

u8 act_mus_tako1_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_tako/act_mus_tako1_body_tex_txt.inc"
};

u8 act_mus_tako2_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_tako/act_mus_tako2_body_tex_txt.inc"
};

Vtx act_mus_tako_a1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_ike_tako/act_mus_tako_a1_v.inc"
};

Gfx act_mus_tako_head_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_mus_tako_a1_v, 16, 0),
gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_tako_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_tako2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_tako_a1_v[16], 12, 16),
gsSPNTrianglesInit_5b(4, 11, 10, 16, 11, 17, 18, 9, 19, 20),
gsSPNTriangles_5b(9, 8, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 14, 22, 15, 12, 23, 24, 12, 25, 13),
gsSPNTriangles_5b(14, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_tako1_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&act_mus_tako_a1_v[28], 15, 16),
gsSPNTrianglesInit_5b(9, 4, 16, 17, 4, 18, 2, 2, 19, 20),
gsSPNTriangles_5b(2, 21, 5, 1, 22, 23, 1, 24, 7, 5, 25, 26),
gsSPNTriangles_5b(5, 27, 0, 6, 28, 29, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(1, 6, 30, 3, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_tako_a1_v[43], 32, 0),
gsSPNTrianglesInit_5b(23, 0, 1, 2, 2, 3, 4, 5, 6, 7),
gsSPNTriangles_5b(8, 9, 10, 9, 11, 12, 13, 14, 15, 16, 17, 18),
gsSPNTriangles_5b(11, 15, 0, 19, 4, 3, 0, 12, 11, 20, 21, 22),
gsSPNTriangles_5b(4, 8, 2, 12, 10, 9, 23, 24, 25, 23, 25, 26),
gsSPNTriangles_5b(9, 8, 23, 10, 2, 8, 6, 24, 27, 26, 11, 9),
gsSPNTriangles_5b(28, 15, 11, 29, 16, 30, 8, 4, 31, 21, 11, 26),
gsSPVertex(&act_mus_tako_a1_v[75], 31, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 0, 2, 6),
gsSPNTriangles_5b(6, 7, 0, 8, 2, 9, 5, 10, 3, 11, 12, 13),
gsSPNTriangles_5b(14, 9, 2, 10, 15, 16, 3, 17, 0, 18, 19, 20),
gsSPNTriangles_5b(21, 19, 22, 23, 24, 25, 23, 25, 26, 27, 10, 16),
gsSPNTriangles_5b(14, 2, 1, 28, 29, 18, 30, 28, 18, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_tako2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&act_mus_tako_a1_v[106], 20, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 3, 4, 5, 6, 7),
gsSPNTriangles_5b(7, 8, 5, 4, 0, 2, 7, 9, 8, 0, 0, 0),
gsSPNTrianglesInit_5b(6, 10, 11, 12, 13, 14, 15, 15, 16, 13),
gsSPNTriangles_5b(12, 17, 10, 15, 18, 16, 17, 19, 10, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_tako_sakana_foot_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_tako_a1_v[126], 4, 0),
gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_tako_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_tako2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_tako_a1_v[130], 20, 4),
gsSPNTrianglesInit_5b(4, 0, 2, 4, 2, 6, 5, 3, 1, 7),
gsSPNTriangles_5b(1, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(10, 10, 11, 12, 12, 13, 10, 14, 15, 16),
gsSPNTriangles_5b(12, 17, 13, 15, 18, 16, 19, 12, 11, 19, 11, 20),
gsSPNTriangles_5b(21, 22, 16, 21, 16, 23, 16, 22, 14, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_tako_base_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_tako_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_tako1_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_tako_a1_v[150], 31, 0),
gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 5, 4, 6),
gsSPNTriangles_5b(7, 8, 9, 10, 4, 3, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, act_mus_tako2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(8, 11, 12, 13, 14, 12, 15, 15, 16, 14),
gsSPNTriangles_5b(17, 18, 19, 20, 18, 17, 20, 17, 21, 19, 22, 17),
gsSPNTriangles_5b(11, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 23, 24, 25, 25, 26, 23, 27, 28, 29),
gsSPNTriangles_5b(29, 30, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_tako_a1_v[181], 12, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 1, 4, 0, 4, 1),
gsSPNTriangles_5b(4, 5, 3, 6, 7, 8, 9, 10, 8, 9, 8, 11),
gsSPNTriangles_5b(8, 10, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_tako_a1_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 414, 6260, 2698 } },
	{ act_mus_tako_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
	{ act_mus_tako_sakana_foot_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ act_mus_tako_head_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_tako_a1 = 
	{ ARRAY_COUNT(cKF_je_r_act_mus_tako_a1_tbl), 3, cKF_je_r_act_mus_tako_a1_tbl }
;
