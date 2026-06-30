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
extern int mCsd_exitence_chk(void);
extern void mCsd_tiff_write_start(void);
extern void mCsd_mura_write_start(void);
extern void mCsd_mura_read_start(void);
extern void mCsd_sd_format_start(void);
extern void mCsd_sd_tiff_read_start(void);
extern void mCsd_sd_mura_allcount_get_start(void);
extern void mCsd_sd_mura_nextname_get_start(void);
extern int mCsd_sd_format_wait(void);
extern int mCsd_thread_result_chk(void);
extern int mCsd_nowdrive_get(void);
extern void mCsd_nowdrive_set(int nowdrive);
extern int mCsd_sdcard_slot_chk(void);
extern int mSD_tiff_remove_all(void);
extern int mSD_tiff_nextnumber_get(int* number, int* count);
extern int mSD_mura_remove_all(void);
extern int mSD_mura_make_directory(void);
extern int mSD_mura_specification_remove(const u8* eng_name);

#ifdef __cplusplus
}
#endif

#endif
