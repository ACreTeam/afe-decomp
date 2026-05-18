#include "m_string.h"

#include "m_msg.h"
#include "jsyswrap.h"
#include "m_lib.h"
#include "m_font.h"
#include "m_mail.h"

static u32 String_rom_start;

extern void mString_aram_init() {
    String_rom_start = JW_GetAramAddress(RESOURCE_STRING);
}

extern void mString_Load_StringFromRom(u8* dst, int dst_len, int str_no) {
    mMsg_bmg_info_c bmg_info;

    mMsgLoad_bmg_init(&bmg_info, String_rom_start, str_no, dst, dst_len);
    if (mMsgLoad_bmg_load(&bmg_info)) {
        mem_clear(dst + bmg_info.load_size, dst_len - bmg_info.load_size, CHAR_SPACE);
    }
}

extern int mString_Load_YearStringFromRom(u8* dst, lbRTC_year_t year) {
    int len;

    if (year < lbRTC_YEAR_MIN || year > lbRTC_YEAR_MAX) {
        year = GAME_YEAR_MIN;
    }

    len = mFont_UnintToString(dst, mMsg_FREE_STRING_LEN, year, mMsg_FREE_STRING_LEN, TRUE, FALSE, FALSE);
    mString_Load_StringFromRom(dst + len, mMsg_FREE_STRING_LEN - len, 3);
    return mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
}

extern int mString_Load_MonthStringFromRom(u8* dst, lbRTC_month_t month) {
    int len;

    if (month < lbRTC_JANUARY || month > lbRTC_DECEMBER) {
        month = lbRTC_JANUARY;
    }

    len = mFont_UnintToString(dst, mMsg_FREE_STRING_LEN, month, mMsg_FREE_STRING_LEN, TRUE, FALSE, FALSE);
    mString_Load_StringFromRom(dst + len, mMsg_FREE_STRING_LEN - len, 4);
    return mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
}

extern int mString_Load_WeekStringFromRom(u8* dst, lbRTC_weekday_t weekday) {
    if (weekday > lbRTC_SATURDAY) {
        weekday = lbRTC_SUNDAY;
    }

    mString_Load_StringFromRom(dst, mMsg_FREE_STRING_LEN, mString_WEEKDAY_START + weekday);
    return mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
}

extern int mString_Load_DayStringFromRom(u8* dst, lbRTC_day_t day) {
    int len;

    if (day < 1 || day > 31) {
        day = 1;
    }

    len = mFont_UnintToString(dst, mMsg_FREE_STRING_LEN, day, mMsg_FREE_STRING_LEN, TRUE, FALSE, FALSE);
    mString_Load_StringFromRom(dst + len, mMsg_FREE_STRING_LEN - len, 5);
    return mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
}

extern int mString_Load_HourStringFromRom(u8* dst, lbRTC_hour_t hour) {
    int len;
    int num_len;
    int str_no;

    if (hour > 23) {
        hour = 0;
    }

    if (hour < 12) {
        str_no = 1;
    } else {
        str_no = 2;
    }

    mString_Load_StringFromRom(dst, mMsg_FREE_STRING_LEN, str_no);
    len = mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
    num_len = mFont_UnintToString(dst + len, mMsg_FREE_STRING_LEN - len, hour % 12, mMsg_FREE_STRING_LEN - len, TRUE, FALSE, FALSE);
    mString_Load_StringFromRom(dst + (len + num_len), mMsg_FREE_STRING_LEN - (len + num_len), 6);
    return mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
}

extern int mString_Load_MinStringFromRom(u8* dst, lbRTC_min_t min) {
    int len;

    if (min > 59) {
        min = 0;
    }

    len = mFont_UnintToString(dst, mMsg_FREE_STRING_LEN, min, mMsg_FREE_STRING_LEN, TRUE, FALSE, FALSE);
    mString_Load_StringFromRom(dst + len, mMsg_FREE_STRING_LEN - len, min % 10 + 0x5DE);
    return mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
}

extern int mString_Load_SecStringFromRom(u8* dst, lbRTC_sec_t sec) {
    int len;

    if (sec > 59) {
        sec = 0;
    }

    len = mFont_UnintToString(dst, mMsg_FREE_STRING_LEN, sec, mMsg_FREE_STRING_LEN, TRUE, FALSE, FALSE);
    mString_Load_StringFromRom(dst + len, mMsg_FREE_STRING_LEN - len, 8);
    return mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
}

extern int mString_Load_NumberStringAddUnitFromRom(u8* dst, u16 num, int str_no) {
    int num_len = mFont_UnintToString(dst, mMsg_FREE_STRING_LEN, num, mMsg_FREE_STRING_LEN, TRUE, FALSE, FALSE);

    /* Add the unit */
    mString_Load_StringFromRom(dst + num_len, mMsg_FREE_STRING_LEN - num_len, str_no);
    return mMsg_Get_Length_String(dst, mMsg_FREE_STRING_LEN);
}
