#ifndef M_ALARMIN_OVL_H
#define M_ALARMIN_OVL_H

#include "types.h"
#include "m_submenu.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct alarmIn_ovl_s mAI_Ovl_c;

// TODO: finish

static void mAL_alarmIn_ovl_construct(Submenu* submenu);
static void mAL_alarmIn_ovl_destruct(Submenu* submenu);
static void mAL_alarmIn_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif
#endif // M_ALARMIN_OVL_H
