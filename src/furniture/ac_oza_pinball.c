extern Gfx int_oza_pinball_model[];
extern Gfx int_mdl_gras_model[];

static void fOP_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fOP_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (ftr_actor->switch_changed_flag) {
        aMR_contact_info_c* contact_info = aMR_GetContactInfoLayer1();

        if (contact_info->contact_direction == aMR_CONTACT_DIR_LEFT) {
            sAdo_OngenTrgStart(0x47C, &ftr_actor->position);
        }
    }
}

static void fOP_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void fOP_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fOP_func = {
    &fOP_ct, &fOP_mv, &fOP_dw, &fOP_dt, NULL,
};

aFTR_PROFILE iam_oza_pinball = {
    int_oza_pinball_model,
    NULL,
    int_mdl_gras_model,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    18.0f,
    0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
    0x00,
    0x00,
    0x00,
    0x0000,
    &fOP_func,
};
