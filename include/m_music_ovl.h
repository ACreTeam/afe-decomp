#ifndef M_MUSIC_OVL_H
#define M_MUSIC_OVL_H

#include "types.h"
#include "m_music_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_item_name.h"
#include "m_name_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMU_COL_NUM 2
#define mMU_ROW_NUM 7

struct music_ovl_s {
    u8 titles[mMU_ROW_NUM][mIN_ITEM_NAME_LEN];
    s16 ordering[MINIDISK_AIRCHECK_NUM][2]; // [0] = aircheck, [1] = live
    s16 tag_table_idx;
    s16 current_row;
    s16 _pad_162;
    u32 md_rack_mark[6];
    s16 rows;
    u8 cursor_moved;
    u8 _17F;
    u8 alpha;
    // u8 pad_181[3];
};

extern u32* mMU_GetNowSceneMusicRackP(void);
extern int mMU_md_rack_get(int idx);
extern void mMU_md_rack_set_on(int idx);
extern void mMU_md_rack_set_off(int idx);
extern int mMU_csr_idx_2_md_idx(mMU_Ovl_c* music_ovl, int table_idx);
extern int mMU_mark_chk(mMU_Ovl_c* music_ovl, int idx);

extern void mMU_music_ovl_set_proc(Submenu* submenu);
extern void mMU_music_ovl_construct(Submenu* submenu);
extern void mMU_music_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
