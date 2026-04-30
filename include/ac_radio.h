#ifndef AC_RADIO_H
#define AC_RADIO_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Radio_Profile;

typedef struct radio_actor_s RADIO_ACTOR;
typedef void (*RADIO_PROC)(RADIO_ACTOR*, GAME_PLAY*);

struct radio_actor_s{
    STRUCTURE_ACTOR structure_class;
};

#ifdef __cplusplus
}
#endif

#endif
