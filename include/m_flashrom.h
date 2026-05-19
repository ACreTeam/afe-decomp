#ifndef M_FLASHROM_H
#define M_FLASHROM_H

#include "types.h"
#include "m_flashrom_h.h"
#include "libu64/gfxprint.h"
#include "m_time.h"
#include "m_common_data.h"

#ifdef __cplusplus
extern "C" {
#endif

extern MATCH_FORCESTRIP void mFRm_PrintErrInfo(gfxprint_t* gfxprint);
extern void mFRm_set_msg_idx(int idx);
extern int mFRm_get_msg_idx();
extern u16 mFRm_ReturnCheckSum(u16* data, int size);
extern u16 mFRm_GetFlatCheckSum(u16* data, int size, u16 now_checksum);
extern int mFRm_CheckSaveData_ID(mFRm_chk_t* save_check);
extern int mFRm_CheckSaveData_common(mFRm_chk_t* save_check, u16 land_id);
extern int mFRm_CheckSaveData();
extern void mFRm_ClearSaveCheckData(mFRm_chk_t* save_check);
extern void mFRm_SetSaveCheckData(mFRm_chk_t* save_check);
extern void mFRm_PrintSavedDebug(gfxprint_t* gfxprint);
extern void mFRm_clear_err_info();
extern void mFRm_save_data_check();
extern void mFRm_display_errInfo(gfxprint_t* gfxprint);
extern void mFRm_toEmptyLand(Save_t* save);
extern void mFRm_mergeAnimal(Save_t* dst, Save_t* src, AnmPersonalID_c* anm_id);

#if VERSION == GAEJ01_00
#define mFRm_LINE(r0, r1) (r0)
#else
#define mFRm_LINE(r0, r1) (r1)
#endif

#ifdef __cplusplus
}
#endif

#endif
