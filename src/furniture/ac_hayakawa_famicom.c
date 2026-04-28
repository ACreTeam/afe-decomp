static void fHF_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fHF_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    (*Common_Get(clip).my_room_clip->famicom_emu_common_move_proc)(ftr_actor, my_room_actor, game, 20, -1);
}

extern Gfx int_kob_disksystem8_on_model[];
extern Gfx int_kob_disksystem8_onT_model[];

static void fHF_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);

    gSPDisplayList(NEXT_POLY_OPA_DISP, int_kob_disksystem8_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_kob_disksystem8_onT_model);

    CLOSE_DISP(game->graph);
}

static void fHF_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fHF_dma(mActor_name_t ftr_name, u8* data) {
    // nothing
}

static aFTR_vtable_c fHF_func = {
    &fHF_ct, &fHF_mv, &fHF_dw, &fHF_dt, &fHF_dma,
};

aFTR_PROFILE iam_hayakawa_famicom = {
    // clang-format off
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    18.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0,
    0,
    0,
    aFTR_INTERACTION_FAMICOM,
    &fHF_func,
    // clang-format on
};
