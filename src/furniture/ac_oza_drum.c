extern Gfx int_oza_drum_model[];

static void fOD_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fOD_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aMR_CLIP != NULL) {
        aMR_CLIP->sound_melody_proc(ftr_actor, my_room_actor, 16);
    }
}

static void fOD_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void fOD_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fOD_func = {
    &fOD_ct, &fOD_mv, &fOD_dw, &fOD_dt, NULL,
};

aFTR_PROFILE iam_oza_drum = {
    int_oza_drum_model,
    NULL,
    NULL,
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
    &fOD_func,
};
