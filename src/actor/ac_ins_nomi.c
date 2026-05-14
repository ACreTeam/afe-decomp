#include "ac_ins_nomi.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "ac_set_ovl_insect.h"
#include "sys_matrix.h"

enum {
    aINM_ACT_AVOID,
    aINM_ACT_LET_ESCAPE,
    aINM_ACT_WAIT,

    aINM_ACT_NUM
};

static void aINM_actor_move(ACTOR* actorx, GAME* game);
static void aINM_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

extern void aINM_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int action;

    switch (insect->type) {
        case aINS_INSECT_TYPE_FLEA:
            insect->item = ITM_INSECT45;
            break;
    }

    actorx->mv_proc = aINM_actor_move;
    if (actorx->actor_specific == 0) {
        actorx->drawn = FALSE;
        actorx->shape_info.draw_shadow = FALSE;
        action = aINM_ACT_WAIT;
    } else {
        actorx->drawn = TRUE;
        insect->s32_work2 = 2;
        action = aINM_ACT_LET_ESCAPE;
    }

    aINM_setupAction(insect, action, game);
}

static void aINM_set_escape_angle(ACTOR* actorx, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    actorx->position_speed.y = 4.0f;
    if (playerx != NULL) {
        int angle = RANDOM_CENTER(DEG2SHORT_ANGLE2(180.0f));
        angle += playerx->shape_info.rotation.y;
        actorx->world.angle.y = angle;
    }
}

static void aINM_set_effect(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    ACTOR* parent = actorx->parent_actor;
    xyz_t pos;

    if (insect->tools_actor.init_matrix == TRUE) {
        Matrix_push();
        Matrix_put(&insect->tools_actor.matrix_work);
        Matrix_Position_Zero(&pos);
        Matrix_pull();
    } else {
        xyz_t_move(&pos, &actorx->world.position);
    }

    eEC_CLIP->effect_make_proc(eEC_EFFECT_NOMI, pos, 1, 0, game, parent->npc_id, 0, 0);
}

static void aINM_let_escape(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (actorx->bg_collision_check.result.on_ground) {
        sAdo_OngenTrgStart(0x471, &actorx->world.position);
        actorx->position_speed.y = 4.0f;
        aINM_set_escape_angle(actorx, game);
    } else {
        s32 timer = insect->s32_work2;

        if (timer > 0) {
            timer--;

            if (timer == 0) {
                sAdo_OngenTrgStart(0x471, &actorx->world.position);
            }
        }

        insect->s32_work2 = timer;
    }
}

static void aINM_wait(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    ACTOR* parent = actorx->parent_actor;

    if (insect->tools_actor.init_matrix == TRUE) {
        Matrix_push();
        Matrix_put(&insect->tools_actor.matrix_work);
        Matrix_Position_Zero(&actorx->world.position);
        Matrix_pull();
    }

    if (parent == NULL) {
        insect->insect_flags.destruct = TRUE;
    } else if (parent->shape_info.draw_shadow == TRUE) {
        insect->f32_work2 -= 1.0f;

        if (insect->f32_work2 <= 0.0f) {
            aINM_set_effect(actorx, game);
            insect->s32_work1--;
            if (insect->s32_work1 <= 0) {
                if (RANDOM_F(1.0f) < 0.4f) {
                    insect->s32_work1 = 2 + RANDOM(2);
                } else {
                    insect->s32_work1 = 1;
                }

                insect->f32_work2 = 60.0f + RANDOM_F(30.0f);
            } else {
                insect->f32_work2 = 18.0f + RANDOM_F(9.0f);
            }
        }
    }
}

static void aINM_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    actorx->gravity = 0.4f;
    actorx->max_velocity_y = -20.0f;
    actorx->position_speed.y = 3.3f;
    actorx->speed = 1.0f;
    aINM_set_escape_angle(actorx, game);
    insect->_1E0 = 0.0f;
    insect->insect_flags.catch_disabled = TRUE;
    insect->insect_flags.ignore_escape_pending = TRUE;
}

typedef void (*aINM_INIT_PROC)(aINS_INSECT_ACTOR* insect, GAME* game);

static void aINM_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aINM_INIT_PROC init_proc[] = {
        // clang-format off
        (aINM_INIT_PROC)none_proc1,
        aINM_let_escape_init,
        (aINM_INIT_PROC)none_proc1,
        // clang-format on
    };

    static aINS_ACTION_PROC act_proc[] = {
        // clang-format off
        (aINS_ACTION_PROC)none_proc1,
        aINM_let_escape,
        aINM_wait,
        // clang-format on
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

static void aINM_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    ACTOR* parent;
    u32 catch_label = mPlib_Get_item_net_catch_label();

    if (catch_label == (u32)actorx) {
        actorx->drawn = TRUE;
        aINM_setupAction(insect, aINM_ACT_LET_ESCAPE, game);
        parent = actorx->parent_actor;

        if (parent != NULL) {
            if (NPC_CLIP != NULL && NPC_CLIP->set_insect_actor_proc != NULL) {
                NPC_CLIP->set_insect_actor_proc((NPC_ACTOR*)parent, NULL);
            }

            actorx->parent_actor = NULL;
        }
    } else {
        (*insect->action_proc)(actorx, game);
    }
}
