extern cKF_Animation_R_c cKF_ba_r_int_ike_hari;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_hari;

// @ 80629330
static aFTR_rig_c aIkeHari_key_anime_data = {
    &cKF_bs_r_int_ike_hari,
    &cKF_ba_r_int_ike_hari,
    1.0f,
};

// @ 8062933c
aFTR_PROFILE iam_ike_hari = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aIkeHari_key_anime_data,
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
