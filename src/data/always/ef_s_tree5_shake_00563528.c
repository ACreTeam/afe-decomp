#include "types.h"
#include "PR/mbi.h"
#include "c_keyframe.h"

extern Gfx ef_s_tree_leaf_modeset[];

Vtx ef_s_tree5_shake_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_s_tree5_shake_00563528/ef_s_tree5_shake_v.inc"
};

Gfx ef_s_tree5_shake_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(ef_s_tree_leaf_modeset),
gsSPVertex(ef_s_tree5_shake_v, 15, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 2, 1, 0),
gsSP2Triangles(4, 0, 2, 0, 3, 4, 2, 0),
gsSP2Triangles(5, 6, 7, 0, 8, 5, 7, 0),
gsSP2Triangles(9, 8, 7, 0, 9, 7, 6, 0),
gsSP2Triangles(10, 11, 12, 0, 10, 13, 11, 0),
gsSP2Triangles(13, 14, 11, 0, 14, 12, 11, 0),
gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_s_tree5_shake_tbl[] = {
	{ NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 7000, 0 } },
	{ ef_s_tree5_shake_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_s_tree5_shake = 
	{ ARRAY_COUNT(cKF_je_r_ef_s_tree5_shake_tbl), 1, cKF_je_r_ef_s_tree5_shake_tbl }
;
