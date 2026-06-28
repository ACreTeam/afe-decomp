#ifndef M_ALARMIN_OVL_H
#define M_ALARMIN_OVL_H

#include "types.h"
#include "m_submenu_ovl.h"
#include "m_alarmIn_ovl_h.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mAL_IDX_HOUR,
    mAL_IDX_MIN,

    mAL_IDX_NUM
};

struct alarmIn_ovl_s {
    s16 delay_values[mAL_IDX_NUM];
    s16 at_values[mAL_IDX_NUM];
    int field;
    u8 _0C[0x10];
};

extern void mAL_alarmIn_ovl_construct(Submenu* submenu);
extern void mAL_alarmIn_ovl_destruct(Submenu* submenu);
extern void mAL_alarmIn_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif
#endif // M_ALARMIN_OVL_H
