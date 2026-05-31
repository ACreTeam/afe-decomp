#ifndef AC_NPC_MAMEDANUKI_H
#define AC_NPC_MAMEDANUKI_H

#include "types.h"
#include "ac_npc.h"
#include "m_private.h"

// Wrap for proper action enums
#define aNSC_MAMEDANUKI
#include "ac_npc_shop_common.h"
#undef aNSC_MAMEDANUKI

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aNMD_ZONE_0,
    aNMD_ZONE_1,
    aNMD_ZONE_2,
    aNMD_ZONE_3,

    aNMD_ZONE_NUM
};

typedef NPC_SHOP_COMMON_ACTOR NPC_MAMEDANUKI_ACTOR;

extern ACTOR_PROFILE Npc_Mamedanuki_Profile;

#ifdef __cplusplus
}
#endif

#endif
