#include "m_text.h"
#include "m_font.h"

static u8 mTxt_buff[2][992];

static void mTxt_9bit_to_16bit(u8* src, u16* dst, int len) {
    int read_ofs;
    int i;

    for (i = read_ofs = 0; i < len; i++) {
        *dst = src[read_ofs + 1];

        if (*src & (1 << (7 - read_ofs))) {
            *dst |= 0x100;
        }

        dst++;

        if (read_ofs < 7) {
            read_ofs++;
        } else {
            read_ofs = 0;
            src += 9;
        }
    }
}

static void mTxt_8bit_to_16bit(u8* src, u16* dst, int len) {
    int i;

    for (i = 0; i < len; i++) {
        *dst = src[i];
        dst++;
    }
}

extern void mTxt_conv_16bit(u8* src, u16* dst, int len) {
    if (src[0] == CHAR_PP_127 && src[1] == mFont_CONT_CODE_9BIT) {
        mTxt_9bit_to_16bit(src + 2, dst, len);
    } else {
        mTxt_8bit_to_16bit(src, dst, len);
    }
}

static void mTxt_conv_9bit_local(u16* src, u8* dst, int len) {
    u32 ofs;
    int write_ofs;
    int i;

    i = write_ofs = 0;
    dst[0] = CHAR_PP_127; // control code
    dst[1] = mFont_CONT_CODE_9BIT; // 9bit control code
    dst += 2;

    for (; i < len; i++) {
        if (write_ofs == 0) {
            *dst = 0; // initialize 9bit code byte
        }
        
        ofs = write_ofs;
        ofs++;
        dst[ofs] = *src;

        if (*src & 0x100) {
            *dst |= (u8)(1 << (7 - write_ofs));
        }

        src++;
        if (write_ofs < 7) {
            write_ofs++;
        } else {
            write_ofs = 0;
            dst += 9;
        }
    }
}

static void mTxt_conv_8bit_local(u16* src, u8* dst, int len) {
    int i;

    for (i = 0; i < len; i++) {
        *dst = *src;
        dst++;
        src++;
    }
}

static int mTxt_ableCheck_8bit(u16* src, int len) {
    int i;

    for (i = 0; i < len; i++) {
        if (*src >= 0x100) {
            return FALSE;
        }

        src++;
    }

    return TRUE;
}

extern int mTxt_conv_9or8bit(u16* src, u8* dst, int len) {
    if (mTxt_ableCheck_8bit(src, len)) {
        mTxt_conv_8bit_local(src, dst, len);
        return mTxt_RESULT_8BIT;
    } else {
        mTxt_conv_9bit_local(src, dst, len);
        return mTxt_RESULT_9BIT;
    }
}

extern u8* mTxt_get_first_buff(void) {
    return mTxt_buff[0];
}

extern u8* mTxt_get_second_buff(void) {
    return mTxt_buff[1];
}
