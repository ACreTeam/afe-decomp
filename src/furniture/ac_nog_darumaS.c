#ifdef __INTELLISENSE__
#include "f_furniture.h"
#include "ac_furniture.h"
#include "ac_my_room.h"
#include "sys_matrix.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#endif

extern u8 int_nog_darumaS_eye1_TA_tex_txt[];
extern u8 int_nog_darumaS_eye2_TA_tex_txt[];
extern Gfx int_nog_darumaS_model[];

static void aNogDarumaS_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void aNogDarumaS_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void aNogDarumaS_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (ftr_actor->switch_bit) {
        gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, int_nog_darumaS_eye2_TA_tex_txt);
    } else {
        gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, int_nog_darumaS_eye1_TA_tex_txt);
    }
    
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_darumaS_model);
    CLOSE_DISP(game->graph);
}

static void aNogDarumaS_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}


static aFTR_vtable_c aNogDarumaS_func = {
	&aNogDarumaS_ct,
	&aNogDarumaS_mv,
	&aNogDarumaS_dw,
	&aNogDarumaS_dt,
	NULL,
};

aFTR_PROFILE iam_nog_darumaS = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&aNogDarumaS_func,
};
