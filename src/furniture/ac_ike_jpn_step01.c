#ifdef __INTELLISENSE__
#include "f_furniture.h"
#include "ac_furniture.h"
#include "ac_my_room.h"
#include "sys_matrix.h"
#include "m_common_data.h"
#endif

extern cKF_Skeleton_R_c cKF_bs_r_int_ike_jpn_step01;
extern cKF_Animation_R_c cKF_ba_r_int_ike_jpn_step01;

static void aIkeJpnStep01_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_ike_jpn_step01, &cKF_ba_r_int_ike_jpn_step01, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_int_ike_jpn_step01, NULL);
    keyframe->frame_control.speed = 0.0f;
    cKF_SkeletonInfo_R_play(keyframe);
}

static void aIkeJpnStep01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aMR_CLIP != NULL) {
        aMR_CLIP->open_close_common_move_proc(ftr_actor, my_room_actor, game, 1.0f, 10.0f);
    }
}

static void aIkeJpnStep01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int counter = game->frame_counter;
    Mtx* mtx = ftr_actor->skeleton_mtx[counter & 1];

    OPEN_DISP(game->graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, mtx, NULL, NULL, NULL);
}

static void aIkeJpnStep01_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}


static aFTR_vtable_c aIkeJpnStep01_func = {
	&aIkeJpnStep01_ct,
	&aIkeJpnStep01_mv,
	&aIkeJpnStep01_dw,
	&aIkeJpnStep01_dt,
	NULL,
};

aFTR_PROFILE iam_ike_jpn_step01 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	aFTR_INTERACTION_STORAGE_DRAWERS,
	&aIkeJpnStep01_func,
};
