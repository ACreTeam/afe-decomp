#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "libultra/libultra.h"

static void ePO_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void ePO_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void ePO_mv(eEC_Effect_c* effect, GAME* game);
static void ePO_dw(eEC_Effect_c* effect, GAME* game);

// clang-format off
eEC_PROFILE_c iam_ef_presentopen = {
    &ePO_init,
    &ePO_ct,
    &ePO_mv,
    &ePO_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
};
// clang-format on

static void ePO_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_PRESENTOPEN, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void ePO_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 8;
}

static void ePO_mv(eEC_Effect_c* effect, GAME* game) {
    s16 counter = 8 - effect->timer;
    int i;

    switch (counter) {
        case 0: {
            static s16 pluss_angle[5] = {
                DEG2SHORT_ANGLE2(0.0f),    DEG2SHORT_ANGLE2(0.0f),   DEG2SHORT_ANGLE2(90.0f),
                DEG2SHORT_ANGLE2(-180.0f), DEG2SHORT_ANGLE2(-90.0f),
            };
            for (i = 0; i < ARRAY_COUNT(pluss_angle); i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_PRESENTOPEN_PARTS, effect->position, effect->prio, pluss_angle[i],
                                           game, effect->item_name, i, 0);
            }
        } break;

        case 4: {
            static s16 angle[4] = {
                DEG2SHORT_ANGLE2(90.0f),
                DEG2SHORT_ANGLE2(-45.0f),
                DEG2SHORT_ANGLE2(22.5f),
                DEG2SHORT_ANGLE2(-90.0f),
            };
            xyz_t position = effect->position;
            position.z += 5.0f;

            for (i = 0; i < 2; i++) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, position, effect->prio, angle[i & 3], game, effect->item_name, 0, 4);
            }
        } break;
    }
}

static void ePO_dw(eEC_Effect_c* effect, GAME* game) {
    // nothing
}
