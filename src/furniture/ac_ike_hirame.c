extern cKF_Animation_R_c cKF_ba_r_int_ike_hirame;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_hirame;

// @ 80629370
static aFTR_rig_c aIkeHirame_key_anime_data = {
    &cKF_bs_r_int_ike_hirame,
    &cKF_ba_r_int_ike_hirame,
    1.0f,
};

// @ 8062937c
aFTR_PROFILE iam_ike_hirame = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aIkeHirame_key_anime_data,
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
