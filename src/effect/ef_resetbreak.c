#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_name_table.h"

static void eResetbreak_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eResetbreak_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eResetbreak_mv(eEC_Effect_c* effect, GAME* game);
static void eResetbreak_dw(eEC_Effect_c* effect, GAME* game);

// clang-format off
eEC_PROFILE_c iam_ef_resetbreak = {
    &eResetbreak_init,
    &eResetbreak_ct,
    &eResetbreak_mv,
    &eResetbreak_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
};
// clang-format on

static void eResetbreak_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_RESETBREAK, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void aResetbreak_make_rock_parts(eEC_Effect_c* effect, GAME* game) {
    s16 angle;
    int i;

    eEC_CLIP->effect_make_proc(eEC_EFFECT_RESETBREAK_PARTS, effect->position, effect->prio, 0, game, effect->item_name, 1, 0);
    for (i = 0, angle = 0; i < 10; i++) {
        xyz_t pos = effect->position;

        pos.y += 10.0f + RANDOM_F(5.0f);
        pos.z += 10.0f;
        eEC_CLIP->effect_make_proc(eEC_EFFECT_RESETBREAK_PARTS, pos, effect->prio, (s16)angle, game, effect->item_name, 0, 0);
        angle += DEG2SHORT_ANGLE2(36.0f);
    }
}

static void aResetbreak_make_dust(eEC_Effect_c* effect, GAME* game, int dir) {
    xyz_t pos = effect->position;
    int angle = RANDOM(65536);
    s16 angle_s = angle + (s16)(dir * DEG2SHORT_ANGLE2(90.0f));

    pos.y += 10.0f + RANDOM_F(15.0f);
    pos.x += 18.0f * sin_s(angle_s);
    pos.z += 10.0f + 20.0f * cos_s(angle_s);
    eEC_CLIP->effect_make_proc(eEC_EFFECT_RESETBREAK_DUST, pos, effect->prio, angle_s, game, effect->item_name, 0, 0);
}

static void aResetbreak_make_rock_piece(eEC_Effect_c* effect, GAME* game) {
    int i;

    for (i = 0; i < 5; i++) {
        s16 angle = i * DEG2SHORT_ANGLE(72.0f);
        xyz_t pos = effect->position;

        pos.y += 15.0f;
        eEC_CLIP->effect_make_proc(eEC_EFFECT_RESETBREAK_PIECE, pos, effect->prio, angle, game, effect->item_name, 0, 0);
    }
}

static void eResetbreak_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    switch (effect->arg0) {
        case 0:
            effect->timer = 23;
            break;
        case 1:
            sAdo_OngenTrgStart(0x473, &effect->position);
            aResetbreak_make_rock_parts(effect, game);
            effect->timer = 23;
            break;

    }
}

static void eResetbreak_mv(eEC_Effect_c* effect, GAME* game) {
    int counter = (23 - effect->timer);
    int idx = counter & 7;

    switch (effect->arg0) {
        case 0:
            if (counter == 22) {
                mActor_name_t item;

                if (IS_ITEM_CRACKED_STONE((mActor_name_t)effect->arg1)) {
                    item = (mActor_name_t)effect->arg1;
                } else {
                    item = C_ROCK_A;
                }

                mFI_SetFG_common(item, effect->position, TRUE);
                sAdo_OngenTrgStart(0x472, &effect->position);
                aResetbreak_make_rock_piece(effect, game);
                effect->timer = 0;
            }
            break;
        case 1:
            aResetbreak_make_dust(effect, game, idx);
            break;
    }
}

static void eResetbreak_dw(eEC_Effect_c* effect, GAME* game) {
    // nothing
}
