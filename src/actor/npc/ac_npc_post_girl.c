#include "ac_npc_post_girl.h"

#include "m_msg.h"
#include "m_play.h"
#include "m_font.h"
#include "m_private.h"
#include "m_common_data.h"
#include "m_submenu.h"
#include "m_house.h"
#include "m_home_h.h"
#include "m_player.h"
#include "m_malloc.h"
#include "m_item_name.h"
#include "m_string.h"
#include "libultra/libultra.h"

static void aPG_Set_continue_msg_num(NPC_POSTGIRL_ACTOR* postgirl, int msg);
static void aPG_setupAction(NPC_POSTGIRL_ACTOR* postgirl, GAME_PLAY* play, int action);
static void aPG_actor_ct(ACTOR* actorx, GAME* game);
static void aPG_actor_dt(ACTOR* actorx, GAME* game);
static void aPG_actor_init(ACTOR* actorx, GAME* game);
static void aPG_actor_move(ACTOR* actorx, GAME* game);
static void aPG_actor_draw(ACTOR* actorx, GAME* game);
static void aPG_actor_save(ACTOR* actorx, GAME* game);
static void aPG_talk_request(ACTOR* actorx, GAME* game);
static int aPG_talk_init(ACTOR* actorx, GAME* game);
static int aPG_talk_end_chk(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Post_Girl_Profile = {
    mAc_PROFILE_NPC_POST_GIRL,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_POST_GIRL,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_POSTGIRL_ACTOR),
    aPG_actor_ct,
    aPG_actor_dt,
    aPG_actor_init,
    mActor_NONE_PROC1,
    aPG_actor_save,
};
// clang-format on

static void aPG_actor_ct(ACTOR* actorx, GAME* game) {
    NPC_POSTGIRL_ACTOR* postgirl = (NPC_POSTGIRL_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    static aNPC_ct_data_c ct_data = {
        aPG_actor_move, aPG_actor_draw, aNPC_CT_SCHED_TYPE_STAND, aPG_talk_request, aPG_talk_init, aPG_talk_end_chk, 1
    };
    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        postgirl->npc_class.draw.draw_type = actorx->npc_id == SP_NPC_POST_GIRL ? 0 : 1;
        actorx->talk_distance = 85.0f;
        actorx->world.position.x -= 20.0f;
        postgirl->setup_action = aPG_setupAction;
        postgirl->bg_post_item =
            (BG_POST_ITEM_ACTOR*)Actor_info_name_search(&play->actor_info, mAc_PROFILE_BGPOSTITEM, ACTOR_PART_ITEM);
        {
            int music_source = aPG_MUSIC_PELLY;
            if (actorx->npc_id == SP_NPC_POST_GIRL2) {
                music_source = aPG_MUSIC_PHYLLIS;
            }
            postgirl->music_item = mNT_get_new_music_live_version(music_source);
        }
        postgirl->card_mail = (mCD_keep_mail_c*)zelda_malloc_align(sizeof(mCD_keep_mail_c), 32);
        if (mLd_PlayerManKindCheck() == NATIVE) {
            mHm_rmsz_c* size_info = &Save_Get(homes)[mHS_get_arrange_idx(Common_Get(player_no))].size_info;
            if (Now_Private->inventory.loan == 0 && size_info->size >= mHm_HOMESIZE_UPPER &&
                size_info->next_size >= mHm_HOMESIZE_ISLAND && size_info->renew == FALSE) {
                postgirl->has_bank_account = TRUE;
            }
        }
    }
}

static void aPG_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

static void aPG_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_POSTGIRL_ACTOR* postgirl = (NPC_POSTGIRL_ACTOR*)actorx;
    if (postgirl->is_desk_full == TRUE) {
        Common_Get(force_mail_delivery_flag) = TRUE;
    }
    if (postgirl->card_mail != NULL) {
        zelda_free(postgirl->card_mail);
        postgirl->card_mail = NULL;
    }
    CLIP(npc_clip)->dt_proc(actorx, game);
}

static void aPG_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aPG_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_post_girl.c_inc"
