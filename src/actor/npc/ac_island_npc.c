#include "ac_island_npc.h"
#include "m_common_data.h"
#include "m_island.h"
#include "m_player_lib.h"

enum {
    aISN_ACT_LYING,
    aISN_ACT_STAND_UP,
    aISN_ACT_TALK,
    aISN_ACT_WANDER,

    aISN_ACT_NUM
};

static void aISN_actor_ct(ACTOR* actorx, GAME* game);
static void aISN_actor_dt(ACTOR* actorx, GAME* game);
static void aISN_actor_init(ACTOR* actorx, GAME* game);
static void aISN_actor_save(ACTOR* actorx, GAME* game);
static void aISN_actor_move(ACTOR* actorx, GAME* game);
static void aISN_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Island_Npc_Profile = {
    mAc_PROFILE_ISLAND_NPC,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(ISLAND_NPC_ACTOR),
    &aISN_actor_ct,
    &aISN_actor_dt,
    &aISN_actor_init,
    mActor_NONE_PROC1,
    &aISN_actor_save,
};

static void aISN_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int proc_type);
static int aISN_talk_init(ACTOR* actorx, GAME* game);
static int aISN_talk_end_chk(ACTOR* actorx, GAME* game);
static void aISN_setup_isl_think_proc(ISLAND_NPC_ACTOR* actor, GAME_PLAY* play, u8 think_idx);
static void aISN_first_day_talk_request(ACTOR* actorx, GAME* game);
static void aISN_last_day_talk_request(ACTOR* actorx, GAME* game);
static void aISN_norm_talk_request(ACTOR* actorx, GAME* game);
static void aISN_force_talk_request(ACTOR* actorx, GAME* game);

static void aISN_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aISN_actor_move,
        &aISN_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aISN_talk_init,
        aISN_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        ISLAND_NPC_ACTOR* actor = (ISLAND_NPC_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aISN_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actor->npc_class.talk_info.talk_end_check_proc = aISN_talk_end_chk;
        actor->npc_class.npc_info.animal_orig->is_home = FALSE;
    }
}

static void aISN_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aISN_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

#include "../src/actor/npc/ac_island_npc_move.c_inc"

static void aISN_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aISN_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
