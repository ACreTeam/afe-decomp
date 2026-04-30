#ifndef AC_NAMEPLATE_H
#define AC_NAMEPLATE_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Nameplate_Profile;

typedef struct nameplate_actor_s{
    STRUCTURE_ACTOR structure_class;
}NAMEPLATE_ACTOR;

#ifdef __cplusplus
}
#endif

#endif
