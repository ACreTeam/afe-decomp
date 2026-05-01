static void fTC_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fTC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void fTC_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

extern Gfx obj_shop_cracker_1T_mat_model[];
extern Gfx obj_shop_cracker_1T_gfx_model[];

static void fTC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, obj_shop_cracker_1T_mat_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, obj_shop_cracker_1T_gfx_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fTC_func = {
    &fTC_ct, &fTC_mv, &fTC_dw, &fTC_dt, NULL,
};

aFTR_PROFILE iam_tool_cracker = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fTC_func,
    // clang-format on
};
