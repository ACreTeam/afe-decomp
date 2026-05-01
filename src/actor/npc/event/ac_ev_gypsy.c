#include "ac_ev_gypsy.h"

#include "m_choice.h"
#include "m_common_data.h"
#include "m_item_name.h"
#include "m_msg.h"
#include "m_play.h"
#include "m_string.h"

enum {
    aEGPS_ACTION_TALK_END_WAIT,
    aEGPS_ACTION_CALL_IN,
    aEGPS_ACTION_DECIDE_RESULT,
    aEGPS_ACTION_DECIDE_RESULT2,

    aEGPS_ACTION_NUM
};

enum {
    aEGPS_STR_TYPE_ADJECTIVE,
    aEGPS_STR_TYPE_NOUN,
    aEGPS_STR_TYPE_VERB,
    aEGPS_STR_TYPE_PLACE,

    aEGPS_STR_TYPE_NUM
};

static void aEGPS_actor_ct(ACTOR*, GAME*);
static void aEGPS_actor_dt(ACTOR*, GAME*);
static void aEGPS_actor_move(ACTOR*, GAME*);
static void aEGPS_actor_draw(ACTOR*, GAME*);
static void aEGPS_actor_save(ACTOR*, GAME*);
static void aEGPS_actor_init(ACTOR*, GAME*);

ACTOR_PROFILE Ev_Gypsy_Profile = {
    // clang-format off
    mAc_PROFILE_EV_GYPSY,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_GYPSY,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_GYPSY_ACTOR),
    &aEGPS_actor_ct,
    &aEGPS_actor_dt,
    &aEGPS_actor_init,
    &none_proc2,
    &aEGPS_actor_save,
    // clang-format on
};

static void aEGPS_talk_request(ACTOR* actorx, GAME* game);
static int aEGPS_talk_init(ACTOR* actorx, GAME* game);
static int aEGPS_talk_end_chk(ACTOR* actorx, GAME* game);
static void aEGPS_setupAction(EV_GYPSY_ACTOR* gypsy, GAME_PLAY* play, int action);

static void aEGPS_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aEGPS_actor_move,
        &aEGPS_actor_draw,
        aNPC_CT_SCHED_TYPE_STAND,
        &aEGPS_talk_request,
        &aEGPS_talk_init,
        &aEGPS_talk_end_chk,
        0,
    };

    EV_GYPSY_ACTOR* gypsy = (EV_GYPSY_ACTOR*)actorx;
    aEv_gypsy_event_c* event;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actorx->talk_distance = 80.0f;
        actorx->status_data.weight = 255;
        actorx->world.position.x += 20.0f;
        gypsy->setup_talk_proc = &aEGPS_setupAction;

        event = (aEv_gypsy_event_c*)mEv_get_common_area(mEv_EVENT_GYPSY, 0);
        if (event == NULL) {
            event = (aEv_gypsy_event_c*)mEv_reserve_common_area(mEv_EVENT_GYPSY, 0);
        }
        gypsy->event_p = event;
    }
}

static void aEGPS_actor_save(ACTOR* actorx, GAME* game) {
    EV_GYPSY_ACTOR* gypsy = (EV_GYPSY_ACTOR*)actorx;

    if (!mDemo_IS_EVENT_DEMO(Common_Get(start_demo_request).type)) {
        aEv_gypsy_event_c* event = gypsy->event_p;
        if (event != NULL) {
            event->fortune_given = FALSE;
        }
    }

    NPC_CLIP->save_proc(actorx, game);
}

static void aEGPS_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_GYPSY, actorx);
}

#include "../src/actor/npc/event/ac_ev_gypsy_move.c_inc"

static void aEGPS_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aEGPS_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
