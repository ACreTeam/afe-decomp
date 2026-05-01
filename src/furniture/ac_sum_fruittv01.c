#ifdef __INTELLISENSE__
#include "f_furniture.h"
#include "ac_furniture.h"
#include "ac_my_room.h"
#endif

static void fSFT_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fSFT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (ftr_actor->switch_bit) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((u32)ftr_actor, 6, &ftr_actor->position);
        }
    }

    if (ftr_actor->switch_changed_flag) {
        if (ftr_actor->switch_bit) {
            sAdo_OngenTrgStart(0x16, &ftr_actor->position);
        } else {
            sAdo_OngenTrgStart(0x17, &ftr_actor->position);
        }
    }
}

extern u8 int_sum_fruittv01_front1_TA_tex_txt[];
extern u8 int_sum_fruittv01_front2_TA_tex_txt[];
extern u8 int_sum_fruittv01_front3_TA_tex_txt[];
extern u8 int_sum_fruittv01_front4_TA_tex_txt[];

extern Gfx int_sum_fruittv01_on_model[];
extern Gfx int_sum_fruittv01_off_model[];

static u8* fSFT_on_anime[] = {
    int_sum_fruittv01_front2_TA_tex_txt, int_sum_fruittv01_front2_TA_tex_txt, int_sum_fruittv01_front2_TA_tex_txt,
    int_sum_fruittv01_front2_TA_tex_txt, int_sum_fruittv01_front3_TA_tex_txt, int_sum_fruittv01_front3_TA_tex_txt,
    int_sum_fruittv01_front3_TA_tex_txt, int_sum_fruittv01_front3_TA_tex_txt, int_sum_fruittv01_front4_TA_tex_txt,
    int_sum_fruittv01_front4_TA_tex_txt, int_sum_fruittv01_front4_TA_tex_txt, int_sum_fruittv01_front4_TA_tex_txt,
    int_sum_fruittv01_front4_TA_tex_txt,
};

static void fSFT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (ftr_actor->switch_bit) {
        GAME_PLAY* play = (GAME_PLAY*)game;
        u32 ctr_ofs;
        int frame;
        u8* tex;
    
        if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
            ctr_ofs = play->game_frame;
        } else {
            ctr_ofs = play->game.frame_counter;
        }

        tex = fSFT_on_anime[((ctr_ofs >> 1) % ARRAY_COUNT(fSFT_on_anime))];
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, tex);
    } else {
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, int_sum_fruittv01_front1_TA_tex_txt);
    }

    gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_fruittv01_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_fruittv01_off_model);

    CLOSE_DISP(game->graph);
}

static void fSFT_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fSFT_func = {
    &fSFT_ct, &fSFT_mv, &fSFT_dw, &fSFT_dt, NULL,
};

aFTR_PROFILE iam_sum_fruittv01 = {
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
    aFTR_INTERACTION_START_DISABLED,
    &fSFT_func,
    // clang-format on
};
