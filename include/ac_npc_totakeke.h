#ifndef AC_NPC_TOTAKEKE_H
#define AC_NPC_TOTAKEKE_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_item_name.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Npc_Totakeke_Profile;

#define aNTT_REQUEST_STR_LEN mIN_ITEM_NAME_LEN

typedef struct npc_totakeke_s NPC_TOTAKEKE_ACTOR;

typedef struct npc_totakeke_think_data_s aNTT_think_data_c;
typedef struct npc_totakeke_event_save_s aNTT_event_save_c;
typedef struct npc_totakeke_event_common_s aNTT_event_common_c;

typedef void (*aNTT_PROC)(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play);

struct npc_totakeke_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0xB68 */ aNTT_PROC proc;
    /* 0xB6C */ s16 roll_count;
    /* 0xB6E */ s16 roll2_count;
    /* 0xB70 */ s16 roll4_count;
    /* 0xB72 */ s16 show_timer;
    /* 0xB74 */ u8 song;
    /* 0xB75 */ u8 _99f;
    /* 0xB76 */ u8 _9a0;
    /* 0xB77 */ u8 _9a1;
    /* 0xB78 */ u8 _9a2;
    /* 0xB79 */ u8 talk;
    /* 0xB7A */ u8 think;
    /* 0xB7B */ u8 pre_roll_think;
    /* 0xB7C */ u8 post_roll_think;
    /* 0xB7D */ u8 melody_inst;
    /* 0xB7E */ u8 think_proc_id;
    /* 0xB7F */ u8 majin_flag;
    /* 0xB80 */ u8 _9aa;
    /* 0xB81 */ u8 _9ab;
    /* 0xB84 */ mPr_birthday_msg_c* birthday_msg;
    /* 0xB88 */ s16 birthday_player_no;
    /* 0xB8A */ u8 birthday_msg_idx;
    /* 0xB8B */ u8 birthday_msg_num;
    /* 0xB8C */ u8 birthday_section;
};

struct npc_totakeke_think_data_s {
    /* 0x00 */ u8 think_proc_id;
    /* 0x01 */ u8 think_init_idx;
    /* 0x02 */ u8 next_talk;
    /* 0x03 */ u8 talk;
    /* 0x04 */ u8 pre_roll_think;
};

#define aNTT_FLAG_HELLO (1 << 0)
#define aNTT_FLAG_1 (1 << 1)
#define aNTT_FLAG_2 (1 << 2)
#define aNTT_FLAG_3 (1 << 3)
#define aNTT_FLAG_AIRCHECK_RECEIVED (1 << 4)
#define aNTT_FLAG_5 (1 << 5)
#define aNTT_FLAG_6 (1 << 6)
#define aNTT_FLAG_7 (1 << 7)
#define aNTT_FLAG_SP_DELETE_MAJIN (1 << 13)
#define aNTT_FLAG_BIRTHDAY_RECEIVE (1 << 9)
#define aNTT_FLAG_BIRTHDAY_HEADER (1 << 10)
#define aNTT_FLAG_BIRTHDAY_BODY (1 << 11)
#define aNTT_FLAG_BIRTHDAY_FOOTER (1 << 12)
#define aNTT_FLAG_SP_ROLL_DRAW (1 << 14)
#define aNTT_FLAG_SP_ROLL_END (1 << 15)

struct npc_totakeke_event_save_s {
    /* 0x00 */ u16 bitfield;
    /* 0x02 */ u8 request_str[mIN_ITEM_NAME_LEN];
    /* 0x0C */ union {
        u8 roll_flag; // legacy name used by mikanbox
        u8 copyright_alpha;
    };
};

struct npc_totakeke_event_common_s {
    /* 0x00 */ u16 foreigner_bitfield;
    /* 0x02 */ u16 _02;
    /* 0x04 */ u8 request_str;
    /* 0x05 */ u16 _05;
    /* 0x07 */ u8 _07;
    /* 0x08 */ u8 _08;
    /* 0x09 */ u8 _09;
    /* 0x0a */ u8 _0a;
    /* 0x0b */ u8 _0b;
    /* 0x0c */ u8 _0c;
    /* 0x0d */ u8 _0d;
    /* 0x0e */ u8 _0e;
    /* 0x0f */ u8 _0f;
};

enum aNTT_think_callback {
    aNTT_PROC_NONE,
    aNTT_PROC_WAIT,
    aNTT_PROC_ROLL,
    aNTT_PROC_ROLL1,
    aNTT_PROC_ROLL2,
    aNTT_PROC_ROLL4,
    aNTT_PROC_ROLL_END,
    aNTT_PROC_BIRTHDAY_START,
    aNTT_PROC_BIRTHDAY_MSG,
    aNTT_PROC_NUM
};

enum aNTT_think_init {
    aNTT_INIT_NONE,
    aNTT_INIT_ROLL,
    aNTT_INIT_ROLL1,
    aNTT_INIT_ROLL2,
    aNTT_INIT_ROLL3,
    aNTT_INIT_ROLL_END,
    aNTT_INIT_CALL,
    aNTT_INIT_BIRTHDAY
};

enum aNTT_talk_request { aNTT_REQUEST_NONE, aNTT_REQUEST_NORMAL, aNTT_REQUEST_FORCE, aNTT_REQUEST_NUM };

enum aNTT_birthday_section {
    aNTT_BIRTHDAY_START,
    aNTT_BIRTHDAY_INTRO,
    aNTT_BIRTHDAY_HEADER_IN,
    aNTT_BIRTHDAY_HEADER_OUT,
    aNTT_BIRTHDAY_BODY_IN,
    aNTT_BIRTHDAY_BODY_OUT,
    aNTT_BIRTHDAY_FOOTER_IN,
    aNTT_BIRTHDAY_NEXT_MSG,
    aNTT_BIRTHDAY_FOOTER_OUT,
    aNTT_BIRTHDAY_FINISH,
    aNTT_BIRTHDAY_OUTRO,
    aNTT_BIRTHDAY_END
};

enum aNTT_talk_proc {
    aNTT_TALK_NONE,
    aNTT_TALK_SELECT0,
    aNTT_TALK_SELECT1,
    aNTT_TALK_STOP_PLAYER,
    aNTT_TALK_SUBMENU,
    aNTT_TALK_SUBMENU2,
    aNTT_TALK_GIVE,
    aNTT_TALK_BIRTHDAY_1_CHK,
    aNTT_TALK_BIRTHDAY_2_CHK,
    aNTT_TALK_BIRTHDAY_MSG_WAIT,
    aNTT_TALK_BIRTHDAY_SUBMENU_WAIT,
    aNTT_TALK_SELECT2,
    aNTT_TALK_NUM
};

enum aNTT_think_proc {
    aNTT_THINK_NONE,
    aNTT_THINK_WAIT,
    aNTT_THINK_ROLL,
    aNTT_THINK_ROLL1,
    aNTT_THINK_ROLL2,
    aNTT_THINK_ROLL4,
    aNTT_THINK_ROLL_END,
    aNTT_THINK_7,
    aNTT_THINK_8,
    aNTT_THINK_9,
    aNTT_THINK_BIRTHDAY_ROLL,
    aNTT_THINK_BIRTHDAY_START,
    aNTT_THINK_BIRTHDAY_MSG,
    aNTT_THINK_BIRTHDAY_END,
    aNTT_THINK_GIVE_MERODY,
    aNTT_THINK_POCKETS_FULL,
    aNTT_THINK_GIVE_LATER,
    aNTT_THINK_BIRTHDAY_FINISHED,
    aNTT_THINK_CARD_NOT_SCANNED,
    aNTT_THINK_NUM
};

#ifdef __cplusplus
}
#endif

#endif
