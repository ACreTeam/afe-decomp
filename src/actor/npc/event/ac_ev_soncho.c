#include "ac_ev_soncho.h"

#include "m_common_data.h"

typedef struct soncho_event_save_s {
    u16 _00;
    u8 msg_no;
} aESC_event_save_c;

static void aESC_actor_ct(ACTOR* actorx, GAME* game);
static void aESC_actor_dt(ACTOR* actorx, GAME* game);
static void aESC_actor_init(ACTOR* actorx, GAME* game);
static void aESC_actor_draw(ACTOR* actorx, GAME* game);
static void aESC_actor_save(ACTOR* actorx, GAME* game);
static void aESC_actor_move(ACTOR* actorx, GAME* game);

static void aESC_talk_request(ACTOR* actorx, GAME* game);
static int aESC_talk_init(ACTOR* actorx, GAME* game);
static int aESC_talk_end_chk(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ev_Soncho_Profile = {
    mAc_PROFILE_EV_SONCHO,
    ACTOR_PART_NPC,
    0,
    SP_NPC_EV_SONCHO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EVENT_SONCHO_ACTOR),
    &aESC_actor_ct,
    &aESC_actor_dt,
    &aESC_actor_init,
    mActor_NONE_PROC1, // @BUG - devs forgot to swap to none_proc2
    &aESC_actor_save,
};
// clang-format on

static aNPC_ct_data_c ct_data = {
    &aESC_actor_move,
    &aESC_actor_draw,
    aNPC_CT_SCHED_TYPE_WALK_WANDER,
    &aESC_talk_request,
    &aESC_talk_init,
    &aESC_talk_end_chk,
    1,
};

static void aESC_actor_ct(ACTOR* actorx, GAME* game) {
    EVENT_SONCHO_ACTOR* soncho_actor = (EVENT_SONCHO_ACTOR*)actorx;
    aESC_event_save_c* soncho_event = (aESC_event_save_c*)mEv_get_save_area(mEv_EVENT_SONCHO_BRIDGE_MAKE, 34);

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        soncho_actor->npc_class.palActorIgnoreTimer = -1;
        soncho_actor->npc_class.draw.sub_anim_type = aNPC_SUB_ANIM_TUE;

        if (soncho_event == NULL) {
            soncho_event = (aESC_event_save_c*)mEv_reserve_save_area(mEv_EVENT_SONCHO_BRIDGE_MAKE, 34);
            soncho_event->_00 = 0;
            soncho_event->msg_no = RANDOM(5);
        }

        if (Save_Get(bridge).pending) {
            Actor_delete(actorx);
        }
    }
}

static void aESC_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aESC_actor_dt(ACTOR* actorx, GAME* game) {
    mEv_actor_dying_message(mEv_EVENT_SONCHO_BRIDGE_MAKE, actorx);
    NPC_CLIP->dt_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_soncho_talk.c_inc"

static void aESC_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aESC_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
