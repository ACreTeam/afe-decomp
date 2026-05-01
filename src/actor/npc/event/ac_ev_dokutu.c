#include "ac_ev_dokutu.h"

#include "m_common_data.h"

static void aEVD_actor_ct(ACTOR* actorx, GAME* game);
static void aEVD_actor_dt(ACTOR* actorx, GAME* game);
static void aEVD_actor_init(ACTOR* actorx, GAME* game);
static void aEVD_actor_save(ACTOR* actorx, GAME* game);
static void aEVD_actor_move(ACTOR* actorx, GAME* game);
static void aEVD_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Ev_Dokutu_Profile = {
    // clang-format off
    mAc_PROFILE_EV_DOKUTU,
    ACTOR_PART_NPC,
    0,
    SP_NPC_EV_DOKUTU,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EVENT_DOKUTU_ACTOR),
    &aEVD_actor_ct,
    &aEVD_actor_dt,
    &aEVD_actor_init,
    &none_proc2,
    &aEVD_actor_save,
    // clang-format on
};

static void aEVD_talk_request(ACTOR* actorx, GAME* game);
static int aEVD_talk_init(ACTOR* actorx, GAME* game);
static int aEVD_talk_end_chk(ACTOR* actorx, GAME* game);

static void aEVD_actor_ct(ACTOR* actorx, GAME* game) {
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        static aNPC_ct_data_c ct_data = {
            &aEVD_actor_move,
            &aEVD_actor_draw,
            aNPC_CT_SCHED_TYPE_WANDER,
            &aEVD_talk_request,
            &aEVD_talk_init,
            &aEVD_talk_end_chk,
            0,
        };

        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aEVD_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aEVD_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aEVD_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aEVD_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_dokutu_talk.c_inc"

static void aEVD_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
