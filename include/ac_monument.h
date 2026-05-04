#ifndef AC_MONUMENT_H
#define AC_MONUMENT_H

#include "types.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aMNM_TYPE_CLOCK,
    aMNM_TYPE_GASLIGHT,
    aMNM_TYPE_WINDMILL,
    aMNM_TYPE_FLOWERCLOCK,
    aMNM_TYPE_HELIPORT,
    aMNM_TYPE_WINDPOWER,
    aMNM_TYPE_DOKAN,
    aMNM_TYPE_STONEHENGE,
    aMNM_TYPE_BIGEGG,
    aMNM_TYPE_FOOTPOINT,
    aMNM_TYPE_NAZKA,
    aMNM_TYPE_BIGMUSH,
    aMNM_TYPE_SIGN,
    aMNM_TYPE_WELL,
    aMNM_TYPE_FOUNTAIN,

    aMNM_TYPE_NUM
};

typedef struct actor_monument_s MONUMENT_ACTOR;

typedef void (*MONUMENT_PROC)(MONUMENT_ACTOR*, GAME_PLAY*);

struct actor_monument_s {
    STRUCTURE_ACTOR structure_class;
};

extern ACTOR_PROFILE Monument_Profile;

#ifdef __cplusplus
}
#endif

#endif
