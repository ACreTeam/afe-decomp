#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

u16 mus_ike_aji_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_aji/mus_ike_aji_pal.inc"
};

u8 act_mus_aji_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/mus_ike_aji/act_mus_aji_body_tex_txt.inc"
};

Vtx act_mus_aji_a1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/mus_ike_aji/act_mus_aji_a1_v.inc"
};

Gfx act_mus_aji_sakana_body_model[] ATTRIBUTE_ALIGN(8) = {
gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_mus_aji_a1_v, 7, 0),
gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_aji_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_aji_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPVertex(&act_mus_aji_a1_v[7], 14, 7),
gsSPNTrianglesInit_5b(10, 0, 7, 2, 3, 8, 1, 3, 10, 9),
gsSPNTriangles_5b(2, 12, 11, 3, 14, 13, 2, 16, 15, 3, 4, 17),
gsSPNTriangles_5b(4, 2, 18, 4, 19, 5, 6, 20, 4, 0, 0, 0),
gsSPVertex(&act_mus_aji_a1_v[21], 22, 0),
gsSPNTrianglesInit_5b(22, 0, 1, 2, 0, 3, 4, 5, 0, 2),
gsSPNTriangles_5b(6, 7, 8, 9, 10, 11, 0, 4, 1, 12, 3, 0),
gsSPNTriangles_5b(11, 13, 14, 14, 9, 11, 13, 11, 6, 15, 12, 0),
gsSPNTriangles_5b(11, 16, 7, 0, 5, 15, 7, 6, 11, 11, 10, 16),
gsSPNTriangles_5b(17, 15, 5, 7, 18, 8, 7, 16, 19, 20, 12, 15),
gsSPNTriangles_5b(7, 19, 18, 21, 20, 15, 17, 21, 15, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_mus_aji_sakana_head_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, mus_ike_aji_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, act_mus_aji_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_mus_aji_a1_v[43], 17, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 2, 3, 4, 5, 3, 6),
gsSPNTriangles_5b(7, 4, 8, 8, 9, 10, 4, 3, 11, 12, 13, 14),
gsSPNTriangles_5b(15, 9, 12, 11, 3, 13, 11, 9, 8, 12, 9, 11),
gsSPNTriangles_5b(8, 4, 11, 11, 13, 12, 8, 10, 7, 14, 15, 12),
gsSPNTriangles_5b(1, 3, 2, 13, 3, 5, 5, 6, 16, 0, 0, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_mus_aji_a1_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 56, 65486, 1095 } },
	{ act_mus_aji_sakana_head_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ act_mus_aji_sakana_body_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1196, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_mus_aji_a1 = 
	{ ARRAY_COUNT(cKF_je_r_act_mus_aji_a1_tbl), 2, cKF_je_r_act_mus_aji_a1_tbl }
;
