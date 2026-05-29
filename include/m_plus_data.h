#ifndef M_PLUS_DATA_H
#define M_PLUS_DATA_H

#include "types.h"
#include "m_personal_id.h"
#include "m_private.h"
#include "m_needlework.h"
#include "m_flashrom_h.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct private_plus_s {
    PersonalID_c player_ID;
    s8 gender;
    s8 face;
    u8 _0012[0xAC5 - 0x0012];
    u8 hint_count;
    mPr_cloth_c cloth;
    u8 _0ACA[0xAE0 - 0x0ACA];
    mPr_birthday_c birthday;
    u8 _0AE4[0xB0C - 0x0AE4];
    u8 _0B0C;
    u8 _0B0D[0xB3C - 0x0B0D];
    u32 ftr_collection[ALIGN_NEXT(1172, 32) / 32];
    u32 wall_collection[ALIGN_NEXT(64, 32) / 32];
    u32 carpet_collection[ALIGN_NEXT(64, 32) / 32];
    u32 paper_collection[ALIGN_NEXT(64, 32) / 32];
    u32 music_collection[ALIGN_NEXT(55, 32) / 32];
    u8 _0BF0[0xC40 - 0x0BF0];
    mNW_original_design_c my_org[mPr_ORIGINAL_DESIGN_COUNT];
    u8 _1D40[0x1E00 - 0x1D40];
} PrivatePlus_c;

typedef struct plus_conv_data_s {
    mFRm_chk_t save_check;
    PrivatePlus_c private_plus[PLAYER_NUM];
} PlusConvData_c;

typedef struct save_plus_s {
    mFRm_chk_t save_check;
    PrivatePlus_c private_plus[PLAYER_NUM];
    u8 _07820[0x1E000 - 0x07820];
} SavePlus_c;

#ifdef __cplusplus
}
#endif
#endif // M_PLUS_DATA_H
