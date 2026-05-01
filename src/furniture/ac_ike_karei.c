extern cKF_Animation_R_c cKF_ba_r_int_ike_karei;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_karei;

// @ 80629430
static aFTR_rig_c aIkeKarei_key_anime_data = {
    &cKF_bs_r_int_ike_karei,
    &cKF_ba_r_int_ike_karei,
    1.0f,
};

// @ 8062943c
aFTR_PROFILE iam_ike_karei = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aIkeKarei_key_anime_data,
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
