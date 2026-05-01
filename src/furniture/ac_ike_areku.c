extern cKF_Skeleton_R_c cKF_bs_r_int_ike_areku;
extern cKF_Animation_R_c cKF_ba_r_int_ike_areku;

static aFTR_rig_c aIkeAreku_key_anime_data = {
    &cKF_bs_r_int_ike_areku,
    &cKF_ba_r_int_ike_areku,
    1.0f,
};

aFTR_PROFILE iam_ike_areku = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aIkeAreku_key_anime_data,
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
