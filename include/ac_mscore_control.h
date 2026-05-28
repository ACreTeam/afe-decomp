#ifndef AC_MSCORE_CONTROL_H
#define AC_MSCORE_CONTROL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mscore_control_actor_s MSCORE_CONTROL_ACTOR;

typedef void (*aMSC_ACTION_PROC)(MSCORE_CONTROL_ACTOR*, GAME_PLAY*);

struct mscore_control_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ aMSC_ACTION_PROC action_proc;
    /* 0x178 */ int action;
    /* 0x17C */ int counter;
    /* 0x180 */ u8 read_buf[20];
    /* 0x194 */ u8 melody[16];
};

extern ACTOR_PROFILE Mscore_Control_Profile;

#ifdef __cplusplus
}
#endif

#endif
