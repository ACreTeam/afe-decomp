#include "types.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

extern Gfx ef_f_tree_leaf_modeset[];

Vtx ef_f_tree4_shake_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_f_tree4_shake_leaf/ef_f_tree4_shake_v.inc"
};

Gfx ef_f_tree4_shake_leaf_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(ef_f_tree_leaf_modeset),
gsSPVertex(ef_f_tree4_shake_v, 10, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
gsSP2Triangles(4, 2, 1, 0, 4, 3, 2, 0),
gsSP2Triangles(5, 6, 7, 0, 6, 8, 7, 0),
gsSP2Triangles(5, 7, 9, 0, 8, 9, 7, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_f_tree4_shake_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 6000, 0 } },
	{ ef_f_tree4_shake_leaf_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_f_tree4_shake = 
	{ ARRAY_COUNT(cKF_je_r_ef_f_tree4_shake_tbl), 1, cKF_je_r_ef_f_tree4_shake_tbl }
;
