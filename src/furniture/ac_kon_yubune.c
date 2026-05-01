#ifdef __INTELLISENSE__
#include "f_furniture.h"
#include "ac_furniture.h"
#include "ac_my_room.h"
#include "sys_matrix.h"
#include "m_common_data.h"
#include "m_debug.h"
#endif

extern Gfx int_kon_yubune_on_model[];
extern Gfx int_kon_yubune_onT_model[];
extern Gfx int_kon_yubune_alphaT_model[];

#define fKY_MIN_TIME (f32)(20 + GETREG(TAKREG, 72))
#define fKY_MAX_TIME (f32)(40 + GETREG(TAKREG, 73))

static void fKY_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->dynamic_work_s[0] < 0) {
            xyz_t pos = ftr_actor->position;
            
            pos.y += 18.0f + GETREG(TAKREG, 70);
            eEC_CLIP->effect_make_proc(eEC_EFFECT_FURO_YUGE, pos, 1, 0, game, RSV_NO, 60 + GETREG(TAKREG, 71), 0);
            ftr_actor->dynamic_work_s[0] = (int)(fKY_MIN_TIME + RANDOM_F(fKY_MAX_TIME - fKY_MIN_TIME));
        } else {
            ftr_actor->dynamic_work_s[0]--;
        }
    }
}

static aFTR_vtable_c fKY_func = {
	NULL,
	&fKY_mv,
	NULL,
	NULL,
	NULL,
};

aFTR_PROFILE iam_kon_yubune = {
	int_kon_yubune_on_model,
	int_kon_yubune_onT_model,
	int_kon_yubune_alphaT_model,
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
	2,
	0,
	0,
	&fKY_func,
};
