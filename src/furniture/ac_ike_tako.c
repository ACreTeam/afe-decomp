extern cKF_Animation_R_c cKF_ba_r_int_ike_tako;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_tako;

// @ 80629470
static aFTR_rig_c aIkeTako_key_anime_data = {
    &cKF_bs_r_int_ike_tako,
    &cKF_ba_r_int_ike_tako,
    1.0f,
};

// @ 8062947c
aFTR_PROFILE iam_ike_tako = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aIkeTako_key_anime_data,
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
