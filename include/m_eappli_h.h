#ifndef M_EAPPLI_H_H
#define M_EAPPLI_H_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mEA_CHARACTER_PLUS_CARDE_NUM 307
#define mEA_FAMICOM_CARDE_NUM 20
#define mEA_CHARACTER_EPLUS_CARDE_NUM 120
#define mEA_CARDE_TOTAL_NUM (mEA_CHARACTER_PLUS_CARDE_NUM + mEA_FAMICOM_CARDE_NUM + mEA_CHARACTER_EPLUS_CARDE_NUM)

#define mEA_CARD_LETTER_NO_INVALID -1
#define mEA_CARD_LETTER_NO_EMBEDDED -2

#define mEA_ECARD_LETTER_NUM ((mEA_CARDE_TOTAL_NUM + 7) / 8) // 56

#ifdef __cplusplus
}
#endif
#endif // M_EAPPLI_H_H
