#ifndef AC_NPC_RCN_GUIDE_H
#define AC_NPC_RCN_GUIDE_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aNRG_TALK_DEMAND_PAYMENT_TALK_P,
    aNRG_TALK_DEMAND_PAYMENT,
    aNRG_TALK_MENU_OPEN_WAIT,
    aNRG_TALK_MENU_CLOSE_WAIT,
    aNRG_TALK_DEMO_START_WAIT,
    aNRG_TALK_DEMO_END_WAIT,
    aNRG_TALK_FINISHED,

    aNRG_TALK_NUM
};

enum {
    aNRC_THINK_CALL,
    aNRC_THINK_CALL_PLUS,
    aNRC_THINK_APPROACH,
    aNRG_THINK_INTRODUCE,
    aNRG_THINK_INTRODUCE_PLUS,
    aNRC_THINK_TURN,
    aNRC_THINK_TAKE_WITH,
    aNRC_THINK_EXPLAIN,
    aNRC_THINK_DECIDE_HOUSE_WAIT,
    aNRC_THINK_STOP_WADE,
    aNRC_THINK_BEFORE_OPEN_DOOR_TALK,
    aNRC_THINK_BEFORE_OPEN_DOOR_TALK2,
    aNRC_THINK_ENTER_WAIT,
    aNRC_THINK_RESTART_WAIT,
    aNRC_THINK_RESTART_TALK,
    aNRC_THINK_DECIDE_HOUSE,
    aNRC_THINK_DECIDE_HOUSE_PLUS,
    aNRC_THINK_EXIT_TURN,
    aNRC_THINK_EXIT,
    aNRC_THINK_WAIT,

    aNRC_THINK_NUM
};

enum {
    aNRG_FORCE_TALK_CALL,
    aNRG_FORCE_TALK_CALL_PLUS,
    aNRG_FORCE_TALK_INTRODUCE,
    aNRG_FORCE_TALK_INTRODUCE_PLUS,
    aNRG_FORCE_TALK_EXPLAIN,
    aNRG_FORCE_TALK_STOP_WADE,
    aNRG_FORCE_TALK_BEFORE_OPEN_DOOR_TALK,
    aNRG_FORCE_TALK_BEFORE_OPEN_DOOR2_TALK,
    aNRG_FORCE_TALK_HOUSE_TAKEN,
    aNRG_FORCE_TALK_HOUSE_VACANT,
    aNRG_FORCE_TALK_HOUSE_VACANT_PLUS,

    aNRG_FORCE_TALK_NUM
};

enum {
    aNRG_NORM_TALK_DECIDE_HOUSE,

    aNRG_NORM_TALK_NUM
};

typedef struct npc_rcn_guide_s NPC_RCN_GUIDE_ACTOR;

typedef void (*aNRG_THINK_PROC)(NPC_RCN_GUIDE_ACTOR*, GAME_PLAY*);
typedef void (*aNRG_TALK_PROC)(NPC_RCN_GUIDE_ACTOR*, GAME_PLAY*);

/* sizeof(NPC_RCN_GUIDE_ACTOR) == 0x9B4 */
struct npc_rcn_guide_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int think_idx;
    /* 0x998 */ int next_think_idx;
    /* 0x99C */ aNRG_THINK_PROC think_proc;
    /* 0x9A0 */ int talk_idx;
    /* 0x9A4 */ aNRG_TALK_PROC talk_proc;
    /* 0x9A8 */ u8 talk_proc_idx;
    /* 0x9A9 */ u8 path;
    /* 0x9AA */ u8 melody_copy;
    /* 0x9AC */ int shop_bx;
    /* 0x9B0 */ int shop_bz;
};

extern ACTOR_PROFILE Npc_Rcn_Guide_Profile;

#ifdef __cplusplus
}
#endif

#endif
