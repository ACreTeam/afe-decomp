#ifndef AC_ISLAND_NPC_H
#define AC_ISLAND_NPC_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct island_npc_actor_s ISLAND_NPC_ACTOR;
typedef void (*aISN_PROC)(ISLAND_NPC_ACTOR*, GAME_PLAY*);

struct island_npc_actor_s {
    NPC_ACTOR npc_class;
    /* 0xB68 */ u8 think_act;
    /* 0xB69 */ u8 think_after_talk_idx;
    /* 0xB6A */ u8 _B6A;
    /* 0xB6B */ u8 day_type;
    /* 0xB6C */ aISN_PROC think_act_proc;
    /* 0xB70 */ int _B70;
};

extern ACTOR_PROFILE Island_Npc_Profile;

#ifdef __cplusplus
}
#endif
#endif // AC_ISLAND_NPC_H
