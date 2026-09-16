#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

u16 mus_ike_hirame_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_hirame/mus_ike_hirame_pal.inc"
};

u8 act_mus_hirame_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_hirame/act_mus_hirame_body_tex_txt.inc"
};

Vtx act_mus_hirame_a1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_ike_hirame/act_mus_hirame_a1_v.inc"
};

Gfx act_mus_hirame_sakana_body_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_mus_hirame_a1_v, 10, 0),
gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_hirame_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hirame_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_hirame_a1_v[10], 20, 10),
gsSPNTrianglesInit_5b(12, 4, 11, 10, 5, 13, 12, 5, 15, 14),
gsSPNTriangles_5b(9, 6, 16, 9, 17, 18, 7, 8, 19, 8, 20, 21),
gsSPNTriangles_5b(4, 22, 8, 9, 23, 5, 0, 24, 25, 1, 26, 27),
gsSPNTriangles_5b(4, 29, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_hirame_a1_v[30], 4, 10),
gsSPNTrianglesInit_5b(4, 4, 3, 10, 2, 5, 11, 3, 0, 12),
gsSPNTriangles_5b(1, 2, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_mus_hirame_a1_v[34], 32, 0),
gsSPNTrianglesInit_5b(32, 0, 1, 2, 0, 3, 4, 5, 6, 7),
gsSPNTriangles_5b(8, 9, 10, 8, 10, 11, 12, 13, 14, 0, 4, 1),
gsSPNTriangles_5b(15, 16, 17, 11, 10, 18, 19, 12, 14, 14, 20, 11),
gsSPNTriangles_5b(14, 13, 21, 22, 23, 24, 16, 25, 26, 24, 21, 27),
gsSPNTriangles_5b(28, 17, 16, 24, 27, 22, 26, 28, 16, 17, 3, 0),
gsSPNTriangles_5b(20, 14, 21, 21, 24, 20, 17, 0, 15, 29, 19, 14),
gsSPNTriangles_5b(14, 18, 29, 2, 5, 0, 15, 7, 30, 8, 11, 20),
gsSPNTriangles_5b(7, 15, 0, 7, 6, 31, 7, 31, 30, 7, 0, 5),
gsSPNTriangles_5b(18, 14, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_hirame_sakana_head_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_hirame_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_hirame_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_hirame_a1_v[66], 10, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 2, 6, 0),
gsSPNTriangles_5b(4, 7, 5, 0, 8, 1, 5, 9, 3, 0, 0, 0),
gsSPVertex(&act_mus_hirame_a1_v[76], 31, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 2, 6, 7),
gsSPNTriangles_5b(8, 9, 3, 2, 10, 6, 9, 11, 3, 1, 10, 2),
gsSPNTriangles_5b(12, 13, 14, 3, 11, 4, 15, 16, 17, 3, 16, 8),
gsSPNTriangles_5b(7, 18, 2, 19, 14, 2, 17, 20, 15, 2, 18, 19),
gsSPNTriangles_5b(20, 21, 22, 5, 20, 3, 2, 14, 0, 0, 0, 0),
gsSPNTrianglesInit_5b(4, 23, 24, 25, 26, 27, 28, 25, 24, 29),
gsSPNTriangles_5b(30, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_hirame_a1_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 65534, 1203 } },
	{ act_mus_hirame_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ act_mus_hirame_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1300, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_hirame_a1 = 
	{ ARRAY_COUNT(cKF_je_r_act_mus_hirame_a1_tbl), 2, cKF_je_r_act_mus_hirame_a1_tbl }
;
