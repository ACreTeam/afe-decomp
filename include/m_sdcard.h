#ifndef M_SDCARD_H
#define M_SDCARD_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void S_CRV32SET(int v);
extern void mSD_static_clear(void);
extern int mCsd_sdcard_sweet_chk(void);
extern int mCsd_sdcard_selectslot_sweet_chk(s32 chan);
extern void mCsd_exitence_chk_start(void);
extern void mCsd_nowdrive_set(int nowdrive);

#ifdef __cplusplus
}
#endif

#endif
