extern cKF_Animation_R_c cKF_ba_r_int_ike_fun;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_fun;

static aFTR_rig_c aIkeFun_key_anime_data = {
    &cKF_bs_r_int_ike_fun,
    &cKF_ba_r_int_ike_fun,
    1.0f,
};

aFTR_PROFILE iam_ike_fun = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aIkeFun_key_anime_data,
    NULL,
    30.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0x00,
    aFTR_KANKYO_MAP_XLU,
    aFTR_CONTACT_ACTION_NONE,
    aFTR_INTERACTION_INSECT,
    NULL
};
