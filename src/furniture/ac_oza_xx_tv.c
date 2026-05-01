#include "boot.h"
#ifdef __INTELLISENSE__
#include "ac_furniture.h"
#include "audio.h"
#include "sys_matrix.h"
#endif

static void aOzaXxTv_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void aOzaXxTv_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (ftr_actor->switch_bit) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((u32)ftr_actor, NA_ONGEN_POS_SE_TV, &ftr_actor->position);
        }

        ftr_actor->tex_animation.frame += game->graph->delta_time_60fps_mult;
        // if ((int)ftr_actor->tex_animation.frame >= 10 || (int)ftr_actor->tex_animation.frame < 0) {
        //     ftr_actor->tex_animation.frame = 0;
        // }
        if ((int)ftr_actor->tex_animation.frame >= 60 || (int)ftr_actor->tex_animation.frame < 0) {
            ftr_actor->tex_animation.frame = 0;
        }
    }

    if (ftr_actor->switch_changed_flag) {
        if (ftr_actor->switch_bit) {
            sAdo_OngenTrgStart(NA_SE_LIGHT_ON, &ftr_actor->position);
        } else {
            sAdo_OngenTrgStart(NA_SE_LIGHT_OFF, &ftr_actor->position);
        }
    }
}

// extern u8 int_sum_tv02_front1_TA_tex_txt[];
// extern u8 int_sum_tv02_front2_TA_tex_txt[];
// extern u8 int_sum_tv02_front3_TA_tex_txt[];

// static u8* aOzaXxTv_on_anime[] = {
//     // clang-format off
//     int_sum_tv02_front2_TA_tex_txt,
//     int_sum_tv02_front2_TA_tex_txt,
//     int_sum_tv02_front3_TA_tex_txt,
//     int_sum_tv02_front3_TA_tex_txt,
//     int_sum_tv02_front3_TA_tex_txt,
//     // clang-format on
// };

extern Gfx int_oza_xx_tv_model[];
extern Gfx int_oza_xx_tv_off_model[];
extern Gfx int_oza_xx_tv_on_model[];

// static void aOzaXxTv_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
//     Gfx* model;

//     OPEN_POLY_OPA_DISP(game->graph);

//     gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

//     if (ftr_actor->switch_bit) {
//         int frame = (int)ftr_actor->tex_animation.frame >> 1;

//         gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, aOzaXxTv_on_anime[frame]);
//         model = int_oza_xx_tv_on_model;
//     } else {
//         model = int_oza_xx_tv_off_model;
//     }

//     gSPDisplayList(POLY_OPA_DISP++, int_oza_xx_tv_model);
//     gSPDisplayList(POLY_OPA_DISP++, model);

//     CLOSE_POLY_OPA_DISP(game->graph);
// }

static void aOzaXxTv_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    Gfx* model;

    OPEN_POLY_OPA_DISP(game->graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (ftr_actor->switch_bit) {
        int frame = (int)ftr_actor->tex_animation.frame >> 1;

        gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, ALIGN_NEXT((u32)HotStartEntry, 32) + RANDOM(10) * 0xF000 + (frame * 0x400));
        model = int_oza_xx_tv_on_model;
    } else {
        model = int_oza_xx_tv_off_model;
    }

    gSPDisplayList(POLY_OPA_DISP++, int_oza_xx_tv_model);
    gSPDisplayList(POLY_OPA_DISP++, model);

    CLOSE_POLY_OPA_DISP(game->graph);
}

static void aOzaXxTv_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aOzaXxTv_func = {
    // clang-format off
    &aOzaXxTv_ct,
    &aOzaXxTv_mv,
    &aOzaXxTv_dw,
    &aOzaXxTv_dt,
    NULL,
    // clang-format on
};

aFTR_PROFILE iam_oza_xx_tv = {
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
	aFTR_INTERACTION_START_DISABLED,
	&aOzaXxTv_func,
};
