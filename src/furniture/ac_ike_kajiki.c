extern cKF_Animation_R_c cKF_ba_r_int_ike_kajiki;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_kajiki;

// @ 806293f0
static aFTR_rig_c aIkeKajiki_key_anime_data = {
    &cKF_bs_r_int_ike_kajiki,
    &cKF_ba_r_int_ike_kajiki,
    1.0f,
};

// @ 806293fc
aFTR_PROFILE iam_ike_kajiki = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aIkeKajiki_key_anime_data,
    NULL,
    30.0f,
    0.01f,
    aFTR_SHAPE_TYPEB_0,
    mCoBG_FTR_TYPEB_0,
    0x00,
    aFTR_KANKYO_MAP_XLU,
    aFTR_CONTACT_ACTION_NONE,
    aFTR_INTERACTION_FISH,
    NULL,
};
