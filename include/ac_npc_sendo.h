#ifndef AC_NPC_SENDO_H
#define AC_NPC_SENDO_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_home_h.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_sendo_s NPC_SENDO_ACTOR;

typedef void (*aSEN_PROC)(NPC_SENDO_ACTOR*, GAME_PLAY*);

struct npc_sendo_s {
    NPC_ACTOR npc_class;
    u8 action;
    u8 next_action;
    u8 island_count;
    u8 has_my_island;
    aSEN_PROC action_proc;
    int talk_action;
    aSEN_PROC talk_proc;
    u16 kappa_counter;
    f32 anime_progress; // only loaded, never set?
    mHm_hs_c* island_homes[PLAYER_NUM];
    int selected_island;
    mActor_name_t music;
};

extern ACTOR_PROFILE Npc_Sendo_Profile;

#ifdef __cplusplus
}
#endif

#endif
