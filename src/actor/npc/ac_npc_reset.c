#include "ac_npc_reset.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "m_bgm.h"
#include "ac_resetcenter_indoor.h"
#include "ac_reset_chair.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "libultra/libultra.h"

#define aRST_CHAIR(actor)((RESET_CHAIR_ACTOR*)((actor)->reset_chair_p))

enum {
    aRST_TALK_BYEBYE,
    aRST_TALK_EXIT,
    aRST_TALK_STOP_PLAYER,
    aRST_TALK_AINOTE_0,
    aRST_TALK_AINOTE_1,
    aRST_TALK_END_WAIT,
    aRST_TALK_END_WAIT2,
    aRST_TALK_END_WAIT3,
    aRST_TALK_4_1,
    aRST_TALK_4_2,
    aRST_TALK_4_3,
    aRST_TALK_4_4,
    aRST_TALK_4_5,

    aRST_TALK_NUM
};

enum {
    aRST_THINK_PROC_NONE,
    aRST_THINK_PROC_READY_SAILING,
    aRST_THINK_PROC_SAILING,
    aRST_THINK_PROC_SETTLEMENT,
    aRST_THINK_PROC_HIDE,
    aRST_THINK_PROC_RETURN,
    aRST_THINK_PROC_RESET_AINOTE,
    aRST_THINK_PROC_RACKET_AINOTE,
    aRST_THINK_PROC_HUNT,
    aRST_THINK_PROC_REMAIN,
    aRST_THINK_PROC_TIMER,

    aRST_THINK_PROC_NUM
};

enum {
    aRST_THINK_INIT_PROC_NONE,
    aRST_THINK_INIT_PROC_NORMAL_WAIT,
    aRST_THINK_INIT_PROC_READY_SAILING,
    aRST_THINK_INIT_PROC_SAILING,
    aRST_THINK_INIT_PROC_SETTLEMENT,
    aRST_THINK_INIT_PROC_HIDE,
    aRST_THINK_INIT_PROC_RETURN,
    aRST_THINK_INIT_PROC_END,
    aRST_THINK_INIT_PROC_START,
    aRST_THINK_INIT_PROC_START2,
    aRST_THINK_INIT_PROC_START3,
    aRST_THINK_INIT_PROC_TIMER_SAILING,

    aRST_THINK_INIT_PROC_NUM
};

enum {
    aRST_TALK_REQUEST_NONE,
    aRST_TALK_REQUEST_NORM,
    aRST_TALK_REQUEST_FORCE,

    aRST_TALK_REQUEST_NUM
};

static void aRST_actor_ct(ACTOR* actorx, GAME* game);
static void aRST_actor_dt(ACTOR* actorx, GAME* game);
static void aRST_actor_init(ACTOR* actorx, GAME* game);
static void aRST_actor_save(ACTOR* actorx, GAME* game);
static void aRST_actor_move(ACTOR* actorx, GAME* game);
static void aRST_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Npc_Reset_Profile = {
    mAc_PROFILE_NPC_RESET,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_RESET_MAJIN,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_RESET_ACTOR),
    aRST_actor_ct,
    aRST_actor_dt,
    aRST_actor_init,
    mActor_NONE_PROC1,
    aRST_actor_save,
};

static int aRST_talk_init(ACTOR* actorx, GAME* game);
static int aRST_talk_end_chk(ACTOR* actorx, GAME* game);
static int aRST_change_talk_proc(NPC_RESET_ACTOR* actor, u8 idx);
static int aRST_change_talk_proc_next(NPC_RESET_ACTOR* actor);

static void aRST_setup_think_proc(NPC_RESET_ACTOR* actor, GAME_PLAY* play, u8 think_idx);
static void aRST_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int sched_proc_type);

static void aRST_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aRST_actor_move,
        aRST_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aRST_talk_init,
        aRST_talk_end_chk,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_RESET_ACTOR* actor = (NPC_RESET_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aRST_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actor->npc_class.talk_info.default_animation = aNPC_ANIM_WAIT_R1;
        actor->npc_class.talk_info.turn = aNPC_TALK_TURN_HEAD;
        actor->npc_class.right_hand.umbrella_disabled_flag = TRUE;
        actor->npc_class.palActorIgnoreTimer = -1;
        actor->think_changed = FALSE;
        actor->_B76 = 0;
        actor->npc_class.collision.check_kind = aNPC_BG_CHECK_TYPE_NONE;
        actor->npc_class.head.max_look_angle = DEG2SHORT_ANGLE2(30.0f);
        actor->talk_flag = FALSE;
        actor->reset_mode_E = aRI_get_reset_mode_E();
        
        switch (actorx->npc_id) {
            case SP_NPC_RESET_MAJIN:
                switch (actor->reset_mode_E) {
                    case 4:
                    case 5:
                    case 12:
                    case 13:
                        aRI_delete_boots_of_Reset();
                        Actor_delete(actorx);
                        break;
                    case 11:
                    case 14:
                        Actor_delete(actorx);
                        break;
                    case 3:
                    case 7:
                        actor->talk_flag = 5;
                        break;
                }
                break;
            case SP_NPC_RESET_BROTHER:
                switch (actor->reset_mode_E) {
                    case 0:
                    case 2:
                    case 4:
                    case 6:
                    case 8:
                    case 10:
                    case 12:
                    case 14:
                        mRI_delete_boots_of_Racket();
                        Actor_delete(actorx);
                        break;
                    case 3:
                    case 7:
                        actor->talk_flag = 6;
                        break;
                }
        }

        actorx->talk_distance = 45.0f;
    }
}

static void aRST_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aRST_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aRST_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aRST_set_request_act(NPC_RESET_ACTOR* actor, u8 priority, u8 act_idx, u8 act_type, u16 act_obj, s16 move_x, s16 move_z) {
    int ret = FALSE;

    if (priority >= actor->npc_class.request.act_priority) {
        u16 arg_data[aNPC_REQUEST_ARG_NUM];

        bzero(arg_data, sizeof(arg_data));
        arg_data[0] = act_obj;
        arg_data[2] = move_x;
        arg_data[3] = move_z;

        actor->npc_class.request.act_priority = priority;
        actor->npc_class.request.act_idx = act_idx;
        actor->npc_class.request.act_type = act_type;
        mem_copy((u8*)actor->npc_class.request.act_args, (u8*)arg_data, sizeof(arg_data));
        actor->reset_chair_p = NULL;
        ret = TRUE;
    }

    return ret;
}

static void aRST_set_position(ACTOR* actorx, GAME* game) {
    NPC_RESET_ACTOR* actor = (NPC_RESET_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    switch (actorx->npc_id) {
        case SP_NPC_RESET_BROTHER:
            actorx->world.position.y = 55.5f;
            actorx->world.position.z = actorx->home.position.z + 5.0f;
            break;
        default:
            if (actor->reset_chair_p == NULL) {
                actor->reset_chair_p = Actor_info_name_search(&play->actor_info, mAc_PROFILE_RESET_CHAIR, ACTOR_PART_ITEM);
            }

            if (actor->reset_chair_p != NULL) {
                actorx->world.position = actor->reset_chair_p->world.position;
                actorx->world.position.x += 140.0f;
                actorx->world.position.y += 55.5f;
                actorx->world.position.z += 145.0f;
            }
            break;
    }
}

static int aRST_check_look_range(ACTOR* actorx, GAME* game) {
    NPC_RESET_ACTOR* actor = (NPC_RESET_ACTOR*)actorx;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    s16 dAngle = search_position_angleY(&actorx->world.position, &playerx->eye.position);
    s16 curAngle = (s16)actorx->shape_info.rotation.y;
    
    dAngle -= curAngle;

    if (actorx->player_distance_xz >= 120.0f) {
        return 0;
    }

    if (ABS(dAngle) >= DEG2SHORT_ANGLE2(60.0f)) {
        return 0;
    }

    if (ABS(dAngle) >= actor->npc_class.head.max_look_angle) {
        return 1;
    }

    return 2;
}

static void aRST_head_proc(ACTOR* actorx, GAME* game) {
    static xyz_t l_tv_position = { 100.0f, 60.0f, 220.0f };
    static xyz_t l_lmp_position = { 160.0f, 180.0f, 160.0f };
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    NPC_RESET_ACTOR* actor = (NPC_RESET_ACTOR*)actorx;
    xyz_t look_pos;

    actor->npc_class.head.lock_flag = aNPC_HEAD_LOCK_X;
    switch (actor->talk_flag) {
        case 0:
            if (actor->look_range < 2) {
                NPC_CLIP->set_head_request_act_proc((NPC_ACTOR*)actor, 1, aNPC_HEAD_TARGET_POS, NULL, &l_tv_position);
            }
            return;
        case 1:
            actor->npc_class.head.lock_flag = aNPC_HEAD_LOCK_BOTH;
            return;
        case 2:
            look_pos = l_tv_position;
            break;
        case 3:
            look_pos = l_lmp_position;
            break;
        case 5:
            look_pos = actorx->world.position;
            look_pos.x += 100.0f;
            look_pos.z += 10.0f;
            break;
        case 6:
            look_pos = actorx->world.position;
            look_pos.x -= 100.0f;
            look_pos.z += 10.0f;
            break;
        case 4:
            look_pos = playerx->world.position;
            break;
        default:
            return;
    }

    NPC_CLIP->set_head_request_act_proc((NPC_ACTOR*)actor, 4, aNPC_HEAD_TARGET_POS, NULL, &look_pos);
}

#include "../src/actor/npc/ac_npc_reset_talk.c_inc"
#include "../src/actor/npc/ac_npc_reset_schedule.c_inc"

static void aRST_actor_move(ACTOR* actorx, GAME* game) {
    NPC_RESET_ACTOR* actor = (NPC_RESET_ACTOR*)actorx;

    actor->look_range = aRST_check_look_range((ACTOR*)actor, game);
    NPC_CLIP->move_proc((ACTOR*)actor, game);
    aRST_set_position((ACTOR*)actor, game);
    aRST_head_proc((ACTOR*)actor, game);
}

static void aRST_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
