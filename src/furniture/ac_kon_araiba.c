#ifdef __INTELLISENSE__
#include "f_furniture.h"
#include "ac_furniture.h"
#include "ac_my_room.h"
#include "sys_matrix.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#endif

extern Gfx int_kon_araiba_env_model[];
extern Gfx int_kon_araiba_on_model[];
extern Gfx int_kon_araiba_onT_model[];

static void aKonAraiba_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);
    _texture_z_light_fog_prim(game->graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_kon_araiba_onT_model);
    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c aKonAraiba_func = {
	NULL,
	NULL,
	&aKonAraiba_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_kon_araiba = {
	int_kon_araiba_env_model,
	int_kon_araiba_on_model,
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
	0,
	1,
	0,
	0,
	&aKonAraiba_func,
};
