#ifndef M_SHUTTER_OVL_H
#define M_SHUTTER_OVL_H

#include "types.h"
#include "m_submenu.h"
#include "m_shutter_ovl_h.h"

#ifdef __cplusplus
extern "C" {
#endif

struct shutter_ovl_s {
    s16 timer;
    u8 capture_flag_set;
    u8 state;
    int capture_flag_timer;
    int state_timer;
};

extern void mST_shutter_ovl_construct(Submenu* submenu);
extern void mST_shutter_ovl_destruct(Submenu* submenu);
extern void mST_shutter_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif
#endif // M_SHUTTER_OVL_H
