#ifndef M_SHUTTER_OVL_H
#define M_SHUTTER_OVL_H

#include "types.h"
#include "m_submenu.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct shutter_ovl_s mST_Ovl_c;

// TODO: finish

static void mST_shutter_ovl_construct(Submenu* submenu);
static void mST_shutter_ovl_destruct(Submenu* submenu);
static void mST_shutter_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif
#endif // M_SHUTTER_OVL_H
