#ifndef AC_NPC_P_SEL2_H
#define AC_NPC_P_SEL2_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aNPS2_TALK_SETUP_YURE,
    aNPS2_TALK_SETUP_SOUND,
    aNPS2_TALK_SETUP_VOICE,
    aNPS2_TALK_SETUP_VOICE_OK,
    aNPS2_TALK_WHATS_HAPPEN,
    aNPS2_TALK_CHK_OPTION,
    aNPS2_TALK_CHK_OPTION2,
    aNPS2_TALK_CHK_CLR_VILLAGE_DATA_CARTRIDGE,
    aNPS2_TALK_CLR_VILLAGE_DATA_CARTRIDGE,
    aNPS2_TALK_CHK_CLR_PL_DATA,
    aNPS2_TALK_CHK_CLR_PL_DATA2,
    aNPS2_TALK_CHK_CLR_PL_DATA3,
    aNPS2_TALK_CHK_CLR_PL_DATA4,
    aNPS2_TALK_CHK_CLR_PASSPORT_FILE,
    aNPS2_TALK_CLR_PASSPORT_FILE,
    aNPS2_TALK_CLR_PL_DATA,
    aNPS2_TALK_TI_MENU_OPEN_MSG_WAIT,
    aNPS2_TALK_TI_MENU_OPEN_WAIT,
    aNPS2_TALK_TI_MENU_CLOSE_WAIT,
    aNPS2_TALK_SELECT_PLAYER,
    aNPS2_TALK_SELECT_CARD_PLAYER,
    aNPS2_TALK_CHK_FUZAI_PLAYER,
    aNPS2_TALK_CHK_KITAKU_PLAYER,
    aNPS2_TALK_START_TYPE0,
    aNPS2_TALK_START_TYPE1,
    aNPS2_TALK_START_TYPE2,
    aNPS2_TALK_START_TYPE3,
    aNPS2_TALK_RETURN_TITLE,
    aNPS2_TALK_CHK_MAKE_SDCARD,
    aNPS2_TALK_COMMON_MESSAGE_WAIT,
    aNPS2_TALK_MAKE_SDCARD,
    aNPS2_TALK_CHK_BREAKING_1,
    aNPS2_TALK_MSG_WAIT_BREAKING_1,
    aNPS2_TALK_BREAKING_1_0,
    aNPS2_TALK_BREAKING_1_1,
    aNPS2_TALK_CHK_BREAKING_2,
    aNPS2_TALK_MSG_WAIT_BREAKING_2,
    aNPS2_TALK_BREAKING_2,
    aNPS2_TALK_CHK_KANJI,
    aNPS2_TALK_CHK_OPTION_SDCARD,
    aNPS2_TALK_CHK_SDCARD_DELETE,
    aNPS2_TALK_CHK_SDCARD_FORMAT,
    aNPS2_TALK_MSG_WAIT_SDCARD_FORMAT,
    aNPS2_TALK_SDCARD_FORMAT,
    aNPS2_TALK_CHK_DELETE_ALL_V,
    aNPS2_TALK_MSG_WAIT_DELETE_ALL_V,
    aNPS2_TALK_DELETE_ALL_V,
    aNPS2_TALK_CHK_DELETE_ALL_P,
    aNPS2_TALK_MSG_WAIT_DELETE_ALL_P,
    aNPS2_TALK_DELETE_ALL_P,
    aNPS2_TALK_COMMON_MESSAGE_WAIT_NO_SOUND,
    aNPS2_TALK_DELETE_SEL_V_FIRST,
    aNPS2_TALK_CHK_DELETE_SEL_V,
    aNPS2_TALK_MSG_WAIT_DELETE_SEL_V,
    aNPS2_TALK_DELETE_SEL_V,
    aNPS2_TALK_DELETE_SEL_P_FIRST,
    aNPS2_TALK_DELETE_SEL_P_SBMN_W,
    aNPS2_TALK_DELETE_SEL_P_SBMN_E,
    aNPS2_TALK_MSG_WAIT_RESERVE_SDCARD,
    aNPS2_TALK_RESERVE_SDCARD,
    aNPS2_TALK_CHK_REPAYMENT_BG,
    aNPS2_TALK_CHK_REPAYMENT_VILLAGE,
    aNPS2_TALK_MSG_WAIT_REPAYMENT_VILLAGE,
    aNPS2_TALK_REPAYMENT_VILLAGE,
    aNPS2_TALK_CANNOT_REPAYMENT_VILLAGE,
    aNPS2_TALK_WAIT,

    aNPS2_TALK_NUM
};

enum {
    aNPS2_SD_CONTEXT_TIFF, // images
    aNPS2_SD_CONTEXT_MURA, // town

    aNPS2_SD_CONTEXT_NUM
};

typedef struct npc_p_sel2_s NPC_P_SEL2_ACTOR;

typedef void (*aNPS2_TALK_PROC)(NPC_P_SEL2_ACTOR*, GAME_PLAY*);

struct npc_p_sel2_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0xB68 */ int talk_idx;
    /* 0xB6C */ aNPS2_TALK_PROC talk_proc;
    /* 0xB70 */ int talk_end_flag;
    /* 0xB74 */ int player_sum;
    /* 0xB78 */ int player_no;
    /* 0xB7C */ int card_file_idx;
    /* 0xB80 */ int base_message;
    /* 0xB84 */ int base_message2;
    /* 0xB88 */ int base_message3;
    /* 0xB8C */ int base_message4;
    /* 0xB90 */ int base_message5;
    /* 0xB94 */ int base_message6;
    /* 0xB98 */ int card_player_num;
    /* 0xB9C */ int card_player_idx;
    /* 0xBA0 */ int card_player_next_choice_idx;
    /* 0xBA4 */ int passport_slot;
    /* 0xBA8 */ int sd_slot_no;
    /* 0xBAC */ int sd_action;
    /* 0xBB0 */ int sd_file_count;
    /* 0xBB4 */ int sd_tiff_number;
    /* 0xBB8 */ u8 start_flag;
    /* 0xBB9 */ u8 sd_action_timer;
    /* 0xBBA */ u8 flags;
    /* 0xBBB */ u8 _BBB_sd;
    /* 0xBBC */ u8 sd_result;
};

extern ACTOR_PROFILE Npc_P_Sel2_Profile;

#ifdef __cplusplus
}
#endif

#endif
