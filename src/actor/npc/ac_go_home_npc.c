#include "ac_go_home_npc.h"

#include "m_common_data.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_string.h"

static void aGHN_actor_ct(ACTOR* actorx, GAME* game);
static void aGHN_actor_dt(ACTOR* actorx, GAME* game);
static void aGHN_actor_init(ACTOR* actorx, GAME* game);
static void aGHN_actor_move(ACTOR* actorx, GAME* game);
static void aGHN_actor_draw(ACTOR* actorx, GAME* game);
static void aGHN_actor_save(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Go_Home_Npc_Profile = {
    mAc_PROFILE_GO_HOME_NPC,   ACTOR_PART_NPC, ACTOR_STATE_NONE, EMPTY_NO,         ACTOR_OBJ_BANK_KEEP,
    sizeof(GO_HOME_NPC_ACTOR), &aGHN_actor_ct, &aGHN_actor_dt,   &aGHN_actor_init, mActor_NONE_PROC1,
    &aGHN_actor_save
};

static void aGHN_talk_request(ACTOR* actorx, GAME* game);
static int aGHN_talk_init(ACTOR* actorx, GAME* game);
static int aGHN_talk_end_chk(ACTOR* actorx, GAME* game);

static void aGHN_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = { &aGHN_actor_move, &aGHN_actor_draw,   3, &aGHN_talk_request,
                                      &aGHN_talk_init,  &aGHN_talk_end_chk, 0 };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_CLIP->ct_proc(actorx, game, &ct_data);

        /* If the player has already spoken to the NPC, despawn them */
        if ((Common_Get(spnpc_first_talk_flags) & (1 << aNPC_SPNPC_BIT_GOHOME_NPC)) != 0) {
            Actor_delete(actorx);
        }
    }
}

static void aGHN_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_MASK_NPC, actorx);
}

static void aGHN_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

#include "../src/actor/npc/ac_go_home_npc_move.c_inc"

static void aGHN_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aGHN_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
