#ifdef __INTELLISENSE__
#include "f_furniture.h"
#include "ac_furniture.h"
#include "ac_my_room.h"
#include "sys_matrix.h"
#endif

extern Gfx int_ike_jpn_irori01_on_model[];
extern Gfx int_ike_jpn_irori01_onT_model[];
extern Gfx int_ike_jpn_irori01_offT_model[];

static void aIkeJpnIrori_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void aIkeJpnIrori_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void aIkeJpnIrori_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_ike_jpn_irori01_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_ike_jpn_irori01_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_ike_jpn_irori01_offT_model);
    CLOSE_DISP(game->graph);
}

static void aIkeJpnIrori_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aIkeJpnIrori_func = {
	&aIkeJpnIrori_ct,
	&aIkeJpnIrori_mv,
	&aIkeJpnIrori_dw,
	&aIkeJpnIrori_dt,
	NULL,
};

aFTR_PROFILE iam_ike_jpn_irori01 = {
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
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	&aIkeJpnIrori_func,
};
