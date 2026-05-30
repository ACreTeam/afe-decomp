#ifndef AC_RESET_CHAIR_H
#define AC_RESET_CHAIR_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aRC_ACT_WAIT,
    aRC_ACT_SAILING,
    aRC_ACT_HIDE,
    aRC_ACT_RETURN,

    aRC_ACT_NUM
};

typedef struct reset_chair_actor_s RESET_CHAIR_ACTOR;

struct reset_chair_actor_s {
    ACTOR actor_class;
    u8 act_idx;
    u8 next_act_idx;
    u8 sailing_state;
    u8 reset_mode_E;
    s16 timer;
    f32 ofs_z;
};

extern ACTOR_PROFILE Reset_Chair_Profile;

#ifdef __cplusplus
}
#endif

#endif /* AC_RESET_CHAIR_H */
