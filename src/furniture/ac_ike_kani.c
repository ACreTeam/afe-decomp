extern cKF_Animation_R_c cKF_ba_r_int_ike_kani;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_kani;

static aFTR_rig_c aIkeKani_key_anime_data = {
    &cKF_bs_r_int_ike_kani,
    &cKF_ba_r_int_ike_kani,
    1.0f,
};

aFTR_PROFILE iam_ike_kani = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aIkeKani_key_anime_data,
    NULL,
    30.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0x00,
    aFTR_KANKYO_MAP_XLU,
    aFTR_CONTACT_ACTION_NONE,
    aFTR_INTERACTION_INSECT,
    NULL,
};
