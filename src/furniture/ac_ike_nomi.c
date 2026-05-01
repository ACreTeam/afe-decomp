extern cKF_Skeleton_R_c cKF_bs_r_int_ike_nomi;
extern cKF_Animation_R_c cKF_ba_r_int_ike_nomi;

static int fIN_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
    void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    FTR_ACTOR* ftr_actor = (FTR_ACTOR*)arg;
    GAME_PLAY* play = (GAME_PLAY*)game;

    
    if (ftr_actor != NULL && aFTR_CAN_PLAY_SE(ftr_actor)) {
        xyz_t pos = {10.0f, 0.0f, 0.0f};
        xyz_t wpos;

        if (joint_idx == 5) {
            Matrix_Position(&pos, &wpos);
            ftr_actor->dynamic_work_f[0] = ftr_actor->dynamic_work_f[1];
            ftr_actor->dynamic_work_f[1] = ftr_actor->dynamic_work_f[2];
            ftr_actor->dynamic_work_f[2] = wpos.y;
        }
    }

    return TRUE;
}

static int fIN_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
    void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    return TRUE;
}

static void fIN_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, ftr_actor->skeleton_mtx[game->frame_counter & 1], fIN_DwBefore, fIN_DwAfter, ftr_actor);
}

static void fIN_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_ike_nomi, &cKF_ba_r_int_ike_nomi, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_ike_nomi, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void fIN_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;

    if (ftr_actor->dynamic_work_f[1] - ftr_actor->dynamic_work_f[0] < 0.0f &&
        ftr_actor->dynamic_work_f[2] - ftr_actor->dynamic_work_f[1] > 0.0f) {
        sAdo_OngenTrgStart(0x475, &ftr_actor->position);
    }
}

static void fIN_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fIN_func = {
    fIN_ct,
    fIN_mv,
    fIN_dw,
    fIN_dt,
};

aFTR_PROFILE iam_ike_nomi = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    30.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0x00,
    aFTR_KANKYO_MAP_XLU,
    aFTR_CONTACT_ACTION_NONE,
    aFTR_INTERACTION_INSECT,
    &fIN_func,
};
