#ifndef M_TEXT_H
#define M_TEXT_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mTxt_RESULT_8BIT,
    mTxt_RESULT_9BIT,

    mTxt_RESULT_NUM
};

extern void mTxt_conv_16bit(u8* src, u16* dst, int len);
extern int mTxt_conv_9or8bit(u16* src, u8* dst, int len);
extern u8* mTxt_get_first_buff(void);
extern u8* mTxt_get_second_buff(void);

#ifdef __cplusplus
}
#endif

#endif
