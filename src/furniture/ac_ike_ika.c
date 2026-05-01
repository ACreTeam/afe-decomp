extern cKF_Animation_R_c cKF_ba_r_int_ike_ika;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_ika;

// @ 806293b0
static aFTR_rig_c aIkeIka_key_anime_data = {
    &cKF_bs_r_int_ike_ika,
    &cKF_ba_r_int_ike_ika,
    1.0f,
};

// @ 806293bc
aFTR_PROFILE iam_ike_ika = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aIkeIka_key_anime_data,
    NULL,
    30.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0x00,
    aFTR_KANKYO_MAP_XLU,
    aFTR_CONTACT_ACTION_NONE,
    aFTR_INTERACTION_FISH,
    NULL,
};
