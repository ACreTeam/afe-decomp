#ifndef AC_SHOP_LEVEL_H
#define AC_SHOP_LEVEL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct shop_level_actor_s SHOP_LEVEL_ACTOR;

struct shop_level_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x0174 */ int bx;
    /* 0x0178 */ int bz;
    /* 0x017C */ int update;
};

extern ACTOR_PROFILE Shop_Level_Profile;

#ifdef __cplusplus
}
#endif

#endif
