#ifndef AC_NPC_RESET_H
#define AC_NPC_RESET_H

#include "types.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_reset_actor_s NPC_RESET_ACTOR;

typedef void (*aRST_THINK_PROC)(NPC_RESET_ACTOR* actor, GAME_PLAY* play);

struct npc_reset_actor_s {
    NPC_ACTOR npc_class;
    aRST_THINK_PROC think_proc;
    ACTOR* reset_chair_p;
    u8 think_idx;
    u8 think_after_talk_idx;
    u8 unused0;
    u8 talk_proc_idx;
    u8 msg_type;
    u8 think_changed;
    u8 _B76; // not actually 0xB76 in AC
    u8 talk_flag;
    u8 reset_mode_E;
    u8 look_range;
    u8 sailing_state;
    s16 timer;
};

extern ACTOR_PROFILE Npc_Reset_Profile;

#ifdef __cplusplus
}
#endif

#endif /* AC_NPC_RESET_H */