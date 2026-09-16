#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "c_keyframe.h"

extern Gfx ef_w_tree_leaf_modeset[];
extern Gfx ef_w_tree_trunk_modeset[];
extern u8 obj_w_tree_cutS_tex_txt[];

Vtx ef_w_tree3_cutL_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_w_tree3_cutL_leaf/ef_w_tree3_cutL_v.inc"
};

Gfx ef_w_tree3_cutL_leaf_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(ef_w_tree_leaf_modeset),
gsSPVertex(ef_w_tree3_cutL_v, 5, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(0, 2, 4, 0, 3, 4, 2, 0),
gsSPEndDisplayList(),
};

Gfx ef_w_tree3_cutL_trunk_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(ef_w_tree_trunk_modeset),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_w_tree_cutS_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&ef_w_tree3_cutL_v[5], 6, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSP2Triangles(1, 4, 5, 0, 1, 3, 4, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_w_tree3_cutL_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 65036, 0, 0 } },
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
	{ ef_w_tree3_cutL_trunk_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } },
	{ ef_w_tree3_cutL_leaf_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_w_tree3_cutL = 
	{ ARRAY_COUNT(cKF_je_r_ef_w_tree3_cutL_tbl), 2, cKF_je_r_ef_w_tree3_cutL_tbl }
;
