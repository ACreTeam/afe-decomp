#ifndef AC_NPC_POST_GIRL_H
#define AC_NPC_POST_GIRL_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "bg_post_item.h"
#include "m_card.h"
#include "m_choice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aPG_LOAN_STR_LEN 6
#define aPG_DEPOSIT_STR_LEN 9
#define aPG_CARD_FILE_NUM 6
#define aPG_CARD_EXISTING_FILE_NUM (aPG_CARD_FILE_NUM - 1)
#define aPG_MUSIC_PELLY 3
#define aPG_MUSIC_PHYLLIS 4

extern ACTOR_PROFILE Npc_Post_Girl_Profile;

typedef struct ac_npc_postgirl NPC_POSTGIRL_ACTOR;

typedef void (*aPG_PROC)(NPC_POSTGIRL_ACTOR*, GAME_PLAY*);
typedef void (*aPG_SETUP_PROC)(NPC_POSTGIRL_ACTOR*, GAME_PLAY*, int);
typedef void (*aPG_INIT_PROC)(ACTOR*, GAME*);

#define aPG_STATUS_NONE 0
#define aPG_STATUS_DESK_FULL (1 << 0)
#define aPG_STATUS_DONE_FIRST_JOB (1 << 1)
#define aPG_HAS_BANK_ACCOUNT (1 << 2)

struct ac_npc_postgirl {
    NPC_ACTOR npc_class;
    int action;
    int next_action;
    aPG_PROC process;
    aPG_SETUP_PROC setup_action;
    u8 status;
    u8 dest;
    u8 is_desk_full;
    u8 has_bank_account;
    int loan;
    BG_POST_ITEM_ACTOR* bg_post_item;
    int msg_no;
    mActor_name_t music_item;
    u16 _B8A;
    u8 card_slot_status[mCD_SLOT_NUM];
    u8 card_file_exists[mCD_SLOT_NUM][aPG_CARD_FILE_NUM];
    int card_slot;
    int card_file;
    int error_slot;
    mCD_keep_mail_c* card_mail;
    u8 card_choices[mChoice_CHOICE_NUM];
    u16 _BB2;
    Mail_c saved_mail[mPr_INVENTORY_MAIL_COUNT];
};

enum ac_npc_action {
    aPG_ACTION_ASK_FOR_BUSINESS,
    aPG_ACTION_NONE,
    aPG_ACTION_MSG_WIN_OPEN_WAIT,
    aPG_ACTION_RECEIVE_DEMO_START_WAIT,
    aPG_ACTION_RECEIVE_DEMO_END_WAIT,
    aPG_ACTION_RECEIVE_AFTER_MSG_END_WAIT,
    aPG_ACTION_REFUSE_DEMO_START_WAIT,
    aPG_ACTION_REFUSE_DEMO_STOP_WAIT,
    aPG_ACTION_REFUSE_MSG_END_WAIT,
    aPG_ACTION_REFUSE_DEMO_ANIME_END_WAIT,
    aPG_ACTION_REFUSE_DEMO_AFTER,
    aPG_ACTION_REFUSE_AFTER_MSG_END_WAIT,
    aPG_ACTION_REPAY_BEFORE,
    aPG_ACTION_MSG_WIN_CLOSE_WAIT,
    aPG_ACTION_REPAY_MENU_CLOSE_WAIT,
    aPG_ACTION_REPAY_AFTER_RECOVER,
    aPG_ACTION_REPAY_AFTER,
    aPG_ACTION_CARD_REFUSE_MSG_END_WAIT,
    aPG_ACTION_CARD_CHK_CONDITION_BEFORE,
    aPG_ACTION_CARD_CHK_CONDITION,
    aPG_ACTION_CARD_SELECT_SLOT,
    aPG_ACTION_CARD_SELECT_FILE,
    aPG_ACTION_CARD_LOAD_FILE,
    aPG_ACTION_CARD_MENU_OPEN_WAIT,
    aPG_ACTION_CARD_SAVE_MENU_CLOSE_WAIT,
    aPG_ACTION_CARD_SAVE_START_WAIT,
    aPG_ACTION_CARD_SAVE,
    aPG_ACTION_CARD_CHK_INITIALIZE,
    aPG_ACTION_CARD_INITIALIZE_START_WAIT,
    aPG_ACTION_CARD_INITIALIZE,
    aPG_ACTION_RECEIVE_MENU_OPEN_WAIT,
    aPG_ACTION_RECEIVE_MENU_CLOSE_WAIT,
    aPG_ACTION_CHECK_RECEIVE_AFTER,
    aPG_ACTION_DEPOSIT_BEFORE,
    aPG_ACTION_DEPOSIT_MENU_OPEN_WAIT,
    aPG_ACTION_DEPOSIT_MENU_CLOSE_WAIT,
    aPG_ACTION_DEPOSIT_AFTER_RECOVER,
    aPG_ACTION_DEPOSIT_AFTER,
    aPG_ACTION_LOOP_CHECK,
    aPG_ACTION_MS_PRESENT_START_WAIT,
    aPG_ACTION_NUM
};

#ifdef __cplusplus
}
#endif

#endif
