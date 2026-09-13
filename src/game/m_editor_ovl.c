#include "m_editor_ovl.h"

#include "m_ledit_ovl.h"
#include "m_debug.h"

#include "audio.h"
#include "m_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_string.h"
#include "m_diary.h"
#include "m_passwordChk_ovl.h"
#include "m_passwordMake_ovl.h"
#include "m_board_ovl.h"
#include "m_diary_ovl.h"
#include "m_address_ovl.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#define mED_CHARS_PER_PAGE 5

static u16 mED_ornament_table[256] = {
    0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
    0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x00F6, 0x00F7, 0x00F8,
    0x00F9, 0x00FA, 0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029,
    0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
    0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 0x0040, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065,
    0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F, 0x0070, 0x0071, 0x0072, 0x0073,
    0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x005B, 0x005C, 0x00C9, 0x00CA, 0x005F, 0x00CB, 0x0041,
    0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x007B, 0x007C, 0x007D,
    0x007E, 0x007F, 0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095,
    0x00B4, 0x00B5, 0x00B6, 0x00A2, 0x0090, 0x0087, 0x0088, 0x00BE, 0x008A, 0x008B, 0x00CE, 0x00CF, 0x00D0, 0x00D1,
    0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00A5, 0x00A6, 0x00A7,
    0x00A8, 0x00A9, 0x00DD, 0x00DE, 0x00DF, 0x00E0, 0x00E1, 0x00AF, 0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x008C, 0x008D,
    0x008E, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x0089, 0x00BF, 0x00C0, 0x00C1, 0x00C2, 0x00C3,
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x005D, 0x005E, 0x0060, 0x0011, 0x00CD, 0x0096, 0x0097, 0x0098, 0x0099,
    0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F, 0x00A0, 0x00A1, 0x008F, 0x00A3, 0x00A4, 0x00E2, 0x00E3, 0x00E4,
    0x00E5, 0x00E6, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B,
    0x000C, 0x000D, 0x000E, 0x000F, 0x0010, 0x00CC, 0x0012, 0x0013, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF, 0x0019,
    0x001A, 0x001B, 0x001C, 0x001D,
};

static u16 mED_hiragana_table[50] = { 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009,
                                      0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F, 0x0010, 0x0011, 0x0012, 0x0013,
                                      0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D,
                                      0x001E, 0x001F, 0x0023, 0x0024, 0x005B, 0x005D, 0x005E, 0x0060, 0x0090, 0x002A,
                                      0x007B, 0x007C, 0x007D, 0x007E, 0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x0084, 0x0081 };

static u16 mED_katakana_table[50] = { 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A,
                                      0x009B, 0x009C, 0x009D, 0x009E, 0x009F, 0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4,
                                      0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE,
                                      0x00AF, 0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x0090, 0x002A,
                                      0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x0086, 0x00BD, 0x0084, 0x0081 };

static u16 mED_kigou_table[30] = { 0x0084, 0x0081, 0x0085, 0x0020, 0x00CD, 0x0090, 0x002A, 0x003F, 0x0021, 0x0026,
                                   0x0082, 0x0083, 0x0028, 0x0029, 0x0025, 0x002C, 0x002E, 0x0027, 0x0022, 0x003A,
                                   0x002B, 0x002F, 0x003B, 0x005C, 0x00BF, 0x003C, 0x003E, 0x005F, 0x0040, 0x002D };

static u16 mED_number_table[10] = { 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x0030 };

static u16 mED_alphabet_table[30] = { 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A,
                                      0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054,
                                      0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x002C, 0x002E, 0x00CD, 0x0020 };

static u16 mED_alphabet_table2[30] = { 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A,
                                       0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054,
                                       0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005F, 0x0080, 0x0080, 0x0080 };

static u16 mED_emoji_table[35] = { 0x0104, 0x0106, 0x0105, 0x0107, 0x0108, 0x00BF, 0x0100, 0x0101, 0x0102,
                                   0x0103, 0x0109, 0x010A, 0x010B, 0x010C, 0x010D, 0x0110, 0x0111, 0x0112,
                                   0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119, 0x011A, 0x011B,
                                   0x011C, 0x011D, 0x011E, 0x003D, 0x002D, 0x010E, 0x010F, 0x011F };

static int shift_total[mED_SHIFT_NUM] = { 5, 6 };
static int page_num_max[mED_SHIFT_MODE_NUM] = { 10, 30, 10, 30, 10, 35 };

extern u8 lat_sousa_2b1_tex_rgb_i4[];
extern u8 lat_sousa_2b2_tex_rgb_i4[];

static u8* lat_sousa_button_pallet_tbl[] = { lat_sousa_2b1_tex_rgb_i4, lat_sousa_2b2_tex_rgb_i4 };

static int mED_get_col_line_width(mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl, s16* cursor_col, s16* cursor_row,
                                  s16* cursor_line_width, int max);

static u16 mED_get_str_data(mED_Ovl_c* editor_ovl, int idx) {
    if (editor_ovl->is_wide_string == TRUE) {
        return editor_ovl->input_wstr[idx];
    } else {
        return (u16)editor_ovl->input_str[idx];
    }
}

static void mED_set_str_data(mED_Ovl_c* editor_ovl, int idx, u16 data) {
    if (editor_ovl->is_wide_string == TRUE) {
        editor_ovl->input_wstr[idx] = data;
    } else {
        editor_ovl->input_str[idx] = (u8)data;
    }
}

static int mED_strlen(mED_Ovl_c* editor_ovl, int count, u16 ignore_char) {
    int i;

    for (i = count - 1; count != 0; i--, count--) {
        if (mED_get_str_data(editor_ovl, i) != ignore_char) {
            return count;
        }
    }

    return 0;
}

static void mED_input_multi_line_R_make_forecastW(mED_Ovl_c* editor_ovl, u16* output, int output_length) {
    int i;
    u16* src = editor_ovl->input_wstr;

    for (i = 0; i < editor_ovl->cursor_idx; i++) {
        *output++ = *src++;
    }

    *output++ = editor_ovl->now_code;
    for (; i < output_length; i++) {
        *output++ = *src++;
    }
}

static void mED_input_multi_line_R_make_forecast(mED_Ovl_c* editor_ovl, u8* output, u16* output_wstr,
                                                 int output_length) {
    if (editor_ovl->is_wide_string == TRUE) {
        mED_input_multi_line_R_make_forecastW(editor_ovl, output_wstr, output_length);
    } else {
        int i;
        u8* src = editor_ovl->input_str;

        for (i = 0; i < editor_ovl->cursor_idx; i++) {
            *output++ = *src++;
        }

        *output++ = editor_ovl->now_code;
        for (; i < output_length; i++) {
            *output++ = *src++;
        }
    }
}

static int mED_input_multi_line_R_chk_cond(mED_Ovl_c* editor_ovl, u8* str, u16* wstr, mSM_MenuInfo_c* menu_info) {
    u8* src_str = editor_ovl->input_str;
    u16* src_wstr = editor_ovl->input_wstr;
    s16 rows;
    s16 cols;
    s16 line_width;
    int res;

    editor_ovl->input_str = str;
    editor_ovl->input_wstr = wstr;
    res = mED_get_col_line_width(menu_info, editor_ovl, &cols, &rows, &line_width, editor_ovl->now_str_len + 1);
    editor_ovl->input_str = src_str;
    editor_ovl->input_wstr = src_wstr;
    return res;
}

static int mED_get_shift_total(mED_Ovl_c* editor_ovl) {
    int ret = 5;

    if (editor_ovl->is_wide_string == TRUE) {
        ret = 6;
    }

    return ret;
}

static int mED_get_code(mED_Ovl_c* editor_ovl, int base, int stick_area, int first) {
    static u16* page_data_table[mED_SHIFT_MODE_NUM] = {
        mED_hiragana_table, mED_kigou_table, mED_katakana_table, mED_alphabet_table, mED_number_table, mED_emoji_table,
    };

    static u16* page_data_table2[mED_SHIFT_MODE_NUM] = {
        mED_hiragana_table, mED_kigou_table, mED_katakana_table, mED_alphabet_table2, mED_number_table, mED_emoji_table,
    };

    static int offset_max[mED_SHIFT_MODE_NUM] = { 50, 30, 50, 30, 10, 35 };

    int shift_mode = editor_ovl->shift_mode;
    int idx;

    switch (shift_mode) {
        case mED_SHIFT_MODE_HIRAGANA:
        case mED_SHIFT_MODE_KATAKANA:
            if (first) {
                idx = (base + stick_area) * mED_CHARS_PER_PAGE;
            } else {
                idx = base * mED_CHARS_PER_PAGE + stick_area;
            }
            break;
        default:
            idx = base + stick_area;
            break;
    }

    idx %= offset_max[shift_mode];
    if (editor_ovl->latin_shift_mode == mED_SHIFT_UPPER) {
        return page_data_table2[shift_mode][idx];
    } else {
        return page_data_table[shift_mode][idx];
    }
}

static void mED_set_stick_area(Submenu* submenu) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    float r = gamePT->mcon.adjusted_pR;

    editor_ovl->last_stick_area = editor_ovl->stick_area;
    if (r < 0.2f) {
        editor_ovl->stick_area = mED_STICK_AREA_CENTER;
    } else {
        int angle = gamePT->mcon.move_angle;

        if (angle < DEG2SHORT_ANGLE2(-157.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_LEFT;
        } else if (angle >= DEG2SHORT_ANGLE(-157.5f) && angle < DEG2SHORT_ANGLE2(-112.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_BOTTOM_LEFT;
        } else if (angle < DEG2SHORT_ANGLE2(-67.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_BOTTOM;
        } else if (angle < DEG2SHORT_ANGLE2(-22.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_BOTTOM_RIGHT;
        } else if (angle < DEG2SHORT_ANGLE2(22.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_RIGHT;
        } else if (angle < DEG2SHORT_ANGLE2(67.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_TOP_RIGHT;
        } else if (angle < DEG2SHORT_ANGLE2(112.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_TOP;
        } else if (angle < DEG2SHORT_ANGLE2(157.5f)) {
            editor_ovl->stick_area = mED_STICK_AREA_TOP_LEFT;
        } else {
            editor_ovl->stick_area = mED_STICK_AREA_LEFT;
        }
    }

    if (editor_ovl->last_stick_area != editor_ovl->stick_area) {
        int stick_area = editor_ovl->stick_area;

        editor_ovl->stick_area_changed = TRUE;
        if ((int)editor_ovl->stick_area >= mED_STICK_AREA_NUM ||
            (int)editor_ovl->stick_area < mED_STICK_AREA_BOTTOM_RIGHT) {
            if ((editor_ovl->shift_mode != mED_SHIFT_MODE_HIRAGANA &&
                 editor_ovl->shift_mode != mED_SHIFT_MODE_KATAKANA) ||
                editor_ovl->consonant_num != -1) {
                sAdo_SysTrgStart(0x40F);
            } else {
                sAdo_SysTrgStart(0x411);
            }
        }
    } else {
        editor_ovl->stick_area_changed = FALSE;
    }
}

static int mED_check_move_cursol(mED_Ovl_c* editor_ovl) {
    u32 buttons = (getButton() | getTrigger()) & (BUTTON_B | BUTTON_DRIGHT | BUTTON_DLEFT | BUTTON_DDOWN | BUTTON_DUP);
    int res = 0;

    if (buttons == BUTTON_NONE) {
        editor_ovl->last_buttons = 0;
        editor_ovl->button_repeat_timer = 30;
        editor_ovl->button_repeat_accel_timer = 26;
        editor_ovl->button_repeat_started = 0;
    } else {
        if (buttons == editor_ovl->last_buttons) {
            if (editor_ovl->button_repeat_started == 1 && editor_ovl->button_repeat_accel_timer != 0) {
                editor_ovl->button_repeat_accel_timer--;
            }

            if (editor_ovl->button_repeat_timer != 0) {
                editor_ovl->button_repeat_timer--;
                return mED_COMMAND_9;
            }

            if (editor_ovl->button_repeat_accel_timer == 0) {
                editor_ovl->button_repeat_timer = 2;
                editor_ovl->button_repeat_speed = 3;
            } else {
                editor_ovl->button_repeat_timer = 6;
                editor_ovl->button_repeat_started = 1;
                editor_ovl->button_repeat_speed = 2;
            }
        } else {
            editor_ovl->last_buttons = buttons;
            editor_ovl->button_repeat_timer = 30;
            editor_ovl->button_repeat_accel_timer = 26;
            editor_ovl->button_repeat_started = 0;
        }

        if ((buttons & BUTTON_B) != 0) {
            res = mED_COMMAND_BACKSPACE;
        } else if ((buttons & BUTTON_DLEFT) != 0) {
            res = mED_COMMAND_CURSOL_LEFT;
        } else if ((buttons & BUTTON_DDOWN) != 0) {
            res = mED_COMMAND_CURSOL_LOWER;
        } else if ((buttons & BUTTON_DUP) != 0) {
            res = mED_COMMAND_CURSOL_UPPER;
        } else if ((buttons & BUTTON_DRIGHT) != 0) {
            res = mED_COMMAND_CURSOL_RIGHT;
        }
    }

    return res;
}

static int mED_check_shift_mode(mED_Ovl_c* editor_ovl) {
    int res = FALSE;

    if (chkTrigger(BUTTON_Y)) {
        editor_ovl->shift_mode++;
        if (editor_ovl->latin_shift_mode == mED_SHIFT_UPPER) {
            if (editor_ovl->shift_mode > mED_SHIFT_MODE_NUMBER) {
                editor_ovl->shift_mode = mED_SHIFT_MODE_ALPHABET;
            }
        } else {
            int total = mED_get_shift_total(editor_ovl);

            editor_ovl->page_top_num = 0;
            editor_ovl->consonant_num = -1;
            if (editor_ovl->shift_mode >= total) {
                editor_ovl->shift_mode = mED_SHIFT_MODE_HIRAGANA;
            }
        }

        res = TRUE;
    }

    return res;
}

static int mED_check_page_mode(mED_Ovl_c* editor_ovl) {
    if ((editor_ovl->stick_area == mED_STICK_AREA_BOTTOM &&
         (chkTrigger(BUTTON_A) || editor_ovl->stick_area_changed == TRUE)) ||
        (editor_ovl->consonant_num != -1 && chkTrigger(BUTTON_B))) {
        if (editor_ovl->consonant_num == -1) {
            editor_ovl->page_top_num += 3;
            editor_ovl->rotate_timer = 6;
        } else {
            editor_ovl->consonant_num = -1;
        }

        return TRUE;
    }

    return FALSE;
}

static int mED_area_to_consonant(mED_Ovl_c* editor_ovl) {
    int stick_area = editor_ovl->stick_area;
    int consonant = -1;

    if (stick_area >= mED_STICK_AREA_LEFT && stick_area <= mED_STICK_AREA_RIGHT) {
        consonant = editor_ovl->stick_area + editor_ovl->page_top_num;
    }

    return consonant;
}

static int mED_input_consonant_num(mED_Ovl_c* editor_ovl) {
    int ret = FALSE;

    if (editor_ovl->shift_mode == mED_SHIFT_MODE_HIRAGANA || editor_ovl->shift_mode == mED_SHIFT_MODE_KATAKANA) {
        if (editor_ovl->consonant_num == -1) {
            int consonant_num = mED_area_to_consonant(editor_ovl);

            if (consonant_num != -1 && chkTrigger(BUTTON_A)) {
                editor_ovl->consonant_num = consonant_num;
                ret = TRUE;
            }
        }
    }

    return ret;
}

static int mED_get_now_code(mED_Ovl_c* editor_ovl) {
    int stick_area = editor_ovl->stick_area;
    int shift_mode = editor_ovl->shift_mode;
    int ret = -1;

    if ((stick_area >= mED_STICK_AREA_LEFT && stick_area <= mED_STICK_AREA_RIGHT) &&
        ((shift_mode != mED_SHIFT_MODE_HIRAGANA && shift_mode != mED_SHIFT_MODE_KATAKANA) ||
         editor_ovl->consonant_num != -1)) {
        int base_idx;

        if (editor_ovl->consonant_num == -1) {
            base_idx = editor_ovl->page_top_num;
        } else {
            base_idx = editor_ovl->consonant_num;
        }

        ret = mED_get_code(editor_ovl, base_idx, stick_area, FALSE);
    }

    return ret;
}

static int mED_check_now_code(mED_Ovl_c* editor_ovl) {
    int res = FALSE;

    if (chkTrigger(BUTTON_A)) {
        int code = mED_get_now_code(editor_ovl);

        if (code != -1) {
            editor_ovl->now_code = code;
            editor_ovl->consonant_num = -1;
            res = TRUE;
        }
    } else if (chkTrigger(BUTTON_R)) {
        editor_ovl->now_code = CHAR_SPACE;
        res = TRUE;
    }

    return res;
}

static int mED_check_output_code(mED_Ovl_c* editor_ovl) {
    int res = mED_COMMAND_NONE;
    if (mED_check_shift_mode(editor_ovl)) {
        sAdo_SysTrgStart(0x37);
    } else if (mED_check_page_mode(editor_ovl)) {
        sAdo_SysTrgStart(0x38);
    } else if (mED_input_consonant_num(editor_ovl)) {
        sAdo_SysTrgStart(0x32);
    } else if (mED_check_now_code(editor_ovl)) {
        res = mED_COMMAND_OUTPUT_CODE;
    }
    return res;
}

static void mED_set_command(Submenu* submenu) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    if (chkTrigger(BUTTON_START)) {
        editor_ovl->command = mED_COMMAND_END_EDIT;
    } else if (chkTrigger(BUTTON_X)) {
        editor_ovl->command = mED_COMMAND_EXCHANGE_CODE;
    } else {
        editor_ovl->command = mED_check_move_cursol(editor_ovl);

        if (editor_ovl->command == mED_COMMAND_NONE) {
            editor_ovl->command = mED_check_output_code(editor_ovl);
        }
    }
}

static int mED_get_col_line_width(mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl, s16* cursor_col, s16* cursor_row,
                                  s16* cursor_line_width, int max) {
    int idx = 0;
    int i;
    s16 prev_col = 0;
    s16 prev_width = 0;
    *cursor_row = 0;
    *cursor_col = 0;
    *cursor_line_width = 0;
    for (i = 0; i < max; i++) {
        int line = mED_LINE_OK;
        s16 width = *cursor_line_width;
        if (width + mFont_TEX_CHAR_WIDTH > editor_ovl->line_width) {
            prev_col = *cursor_col;
            prev_width = width;
            *cursor_col = 1;
            *cursor_line_width = mFont_TEX_CHAR_WIDTH;
            (*cursor_row)++;
            line = mED_LINE_WIDTH_OVER;
        }
        if (mED_get_str_data(editor_ovl, idx) == CHAR_NEW_LINE) {
            prev_col = *cursor_col;
            prev_width = *cursor_line_width;
            *cursor_col = 0;
            *cursor_line_width = 0;
            (*cursor_row)++;
            line = mED_LINE_NEWLINE;
        }
        if (line == mED_LINE_OK) {
            (*cursor_col)++;
            *cursor_line_width += mFont_TEX_CHAR_WIDTH;
        }
        if (*cursor_row >= editor_ovl->max_line_no) {
            *cursor_col = prev_col + 1;
            *cursor_row = editor_ovl->max_line_no - 1;
            *cursor_line_width = prev_width;
            return line == mED_LINE_OK ? mED_LINE_NUM_OVER : line;
        }
        idx++;
    }
    return mED_LINE_OK;
}

static void mED_check_line_over(mED_Ovl_c* editor_ovl) {
    if (editor_ovl->max_line_no > 1 && editor_ovl->cursor_row < editor_ovl->max_line_no - 1 &&
        editor_ovl->cursor_line_width + mFont_TEX_CHAR_WIDTH > editor_ovl->line_width) {
        editor_ovl->cursor_col = 0;
        editor_ovl->cursor_line_width = 0;
        editor_ovl->cursor_row++;
    }
}

static void mED_set_idxcol_inLineWidth(mED_Ovl_c* editor_ovl) {
    int idx = 0;
    int i;
    int cursor_col;
    int width;
    int lines;
    int prev_col;
    int prev_width;
    int prev_line;
    int row;
    cursor_col = 0;
    lines = 0;
    width = 0;
    prev_col = 0;
    prev_line = 0;
    prev_width = 0;
    row = editor_ovl->cursor_row;
    for (i = 0; i < editor_ovl->now_str_len; i++) {
        if (width + mFont_TEX_CHAR_WIDTH > editor_ovl->line_width) {
            prev_line = lines + 1;
            prev_col = 0;
            prev_width = 0;
            width = mFont_TEX_CHAR_WIDTH;
            cursor_col = 1;
            lines++;
        } else {
            width += mFont_TEX_CHAR_WIDTH;
        }
        if (mED_get_str_data(editor_ovl, idx) == CHAR_NEW_LINE) {
            width = 0;
            cursor_col = 0;
            lines++;
        }
        if (lines > row) {
            if (prev_line == row) {
                width = prev_width;
                cursor_col = prev_col;
            }
            break;
        } else if (lines == row) {
            int desired = editor_ovl->cursor_line_width;
            if (width >= desired) {
                if (prev_line == row && desired - prev_width < width - desired) {
                    width = prev_width;
                    cursor_col = prev_col;
                    i--;
                }
                cursor_col++;
                i++;
                break;
            }
        }
        prev_col = cursor_col;
        prev_line = lines;
        prev_width = width;
        idx++;
        cursor_col++;
    }
    editor_ovl->cursor_line_width = width;
    editor_ovl->cursor_idx = i;
    editor_ovl->cursor_col = cursor_col;
}

static void mED_init(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static s16 edit_line[mED_TYPE_NUM] = { 6, 4, 6, 1, 1, mDI_ENTRY_SIZE / 16, 1, 1, 1 };

    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    editor_ovl->stick_area = mED_STICK_AREA_CENTER;
    editor_ovl->last_stick_area = mED_STICK_AREA_CENTER;
    editor_ovl->stick_area_changed = FALSE;
    editor_ovl->shift_mode = mED_SHIFT_MODE_HIRAGANA;
    editor_ovl->page_top_num = 0;
    editor_ovl->consonant_num = -1;
    editor_ovl->command = mED_COMMAND_NONE;
    editor_ovl->now_code = 0;
    editor_ovl->anim_frame = 0;
    editor_ovl->max_line_no = edit_line[menu_info->data0];
    editor_ovl->input_str = NULL;
    editor_ovl->input_wstr = NULL;
    switch (menu_info->data0) {
        case mED_TYPE_BOARD:
        case mED_TYPE_HBOARD:
        case mED_TYPE_NOTICE:
        case mED_TYPE_DIARY:
            editor_ovl->input_wstr = (u16*)menu_info->data2;
            editor_ovl->is_wide_string = TRUE;
            break;
        default:
            editor_ovl->input_str = (u8*)menu_info->data2;
            editor_ovl->is_wide_string = FALSE;
            break;
    }
    editor_ovl->line_width = menu_info->data3;

    if (menu_info->data1 > 0) {
        editor_ovl->input_length = menu_info->data1;

        if (menu_info->data0 == mED_TYPE_DIARY) {
            editor_ovl->now_str_len =
                mED_strlen(editor_ovl, editor_ovl->input_length * editor_ovl->max_line_no, CHAR_SPACE);
        } else {
            editor_ovl->now_str_len =
                mED_strlen(editor_ovl, editor_ovl->input_length * editor_ovl->max_line_no, CHAR_SPACE);
        }
    } else {
        int type = menu_info->data0;

        if (type == mED_TYPE_BOARD) {
            editor_ovl->input_length = MAIL_BODY_LEN / mBD_BODY_LINE_NUM;
            editor_ovl->now_str_len = submenu->overlay->board_ovl->lengths[mBD_FIELD_BODY];
        } else if (type == mED_TYPE_PASSWORDMAKE) {
            editor_ovl->input_length = LAND_NAME_SIZE;
            editor_ovl->now_str_len = submenu->overlay->passwordMake_ovl->lengths[mPM_ENTRY_TOWN];
        } else if (type == mED_TYPE_PASSWORDCHK) {
            editor_ovl->input_length = mPC_STR_SIZE;
            editor_ovl->now_str_len = mPC_STR_SIZE;
        }
    }

    if (menu_info->data0 == mED_TYPE_DIARY) {
        mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;

        if (menu_info->data1 > 0) {
            editor_ovl->cursor_idx = editor_ovl->now_str_len;
            mED_get_col_line_width(menu_info, editor_ovl, &editor_ovl->cursor_col, &editor_ovl->cursor_row,
                                   &editor_ovl->cursor_line_width, editor_ovl->cursor_idx);
        } else {
            editor_ovl->cursor_idx = diary_ovl->cursor_idx;
            editor_ovl->cursor_col = diary_ovl->_48;
            editor_ovl->cursor_row = diary_ovl->_46;
            mED_set_idxcol_inLineWidth(editor_ovl);
        }
    } else {
        editor_ovl->cursor_idx = 0;
        editor_ovl->cursor_col = 0;
        editor_ovl->cursor_row = 0;
        editor_ovl->cursor_line_width = 0;
    }

    editor_ovl->exchange_code = -1;
}

static void mED_set_se(Submenu* submenu) {
    static u16 se_no[mED_COMMAND_NUM] = {
        0x0000, 0x0035, 0x0035, 0x0035, 0x0035, 0x005F, 0x1034, 0x0036, 0x0033, 0x0000
    };

    static u8 mED_exchange_se_list[TOTAL_CHARS] = {
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE,
        TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  FALSE,
        FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
        TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE
    };

    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    int command = editor_ovl->command;

    if (command == mED_COMMAND_OUTPUT_CODE) {
        int voice = mMsg_sound_voice_get(editor_ovl->now_code);

        if ((u32)(voice - 0x4F) <= 3 || (u32)(voice - 0x54) <= 1 || voice == -1) {
            voice = 0x4E;
        }

        sAdo_VoiceSe(voice, 0, 32);
    } else if (command == mED_COMMAND_EXCHANGE_CODE) {
        int exchange_code = editor_ovl->exchange_code;

        if (exchange_code != -1 && mED_exchange_se_list[exchange_code] != FALSE) {
            int voice = mMsg_sound_voice_get(exchange_code);

            sAdo_VoiceSe(voice, 0, 32);
        } else {
            sAdo_SysTrgStart(0x36);
        }
    } else {
        sAdo_SysTrgStart(se_no[command]);
    }
}

static void mED_output_code(mED_Ovl_c* editor_ovl) {
    int idx = editor_ovl->now_str_len;
    int i;
    for (i = editor_ovl->now_str_len; i > editor_ovl->cursor_idx; idx--) {
        mED_set_str_data(editor_ovl, idx, mED_get_str_data(editor_ovl, idx - 1));
        i--;
    }
    editor_ovl->cursor_idx++;
    editor_ovl->now_str_len++;
    mED_set_str_data(editor_ovl, idx, editor_ovl->now_code);
    editor_ovl->se_flag = TRUE;
}

static int mED_get_single_line_width(mED_Ovl_c* editor_ovl) {
    int idx = 0;
    int i;
    int width = 0;
    for (i = editor_ovl->now_str_len; i > 0; i--) {
        width += mFont_TEX_CHAR_WIDTH;
        if (mED_get_str_data(editor_ovl, idx) == CHAR_NEW_LINE) {
            break;
        }
        idx++;
    }
    return width;
}

static void mED_input_single_line(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    if (editor_ovl->latin_shift_mode == TRUE) {
        switch (editor_ovl->now_code) {
            case CHAR_SPACE:
            case CHAR_MESSAGE_TAG:
                editor_ovl->now_code = CHAR_NEW_LINE;
                break;
        }
    }
    if (editor_ovl->now_code != CHAR_NEW_LINE) {
        int width = mED_get_single_line_width(editor_ovl);
        if (editor_ovl->now_str_len < editor_ovl->input_length &&
            width + mFont_TEX_CHAR_WIDTH <= editor_ovl->line_width) {
            mED_output_code(editor_ovl);
        }
    }
}

static void mED_input_multi_line_R(Submenu* submenu, mED_Ovl_c* editor_ovl, u8* buf, u16* wbuf) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_EDITOR];
    int count = editor_ovl->input_length * editor_ovl->max_line_no;
    if (count > editor_ovl->now_str_len) {
        mED_input_multi_line_R_make_forecast(editor_ovl, buf, wbuf, count);
        switch (mED_input_multi_line_R_chk_cond(editor_ovl, buf, wbuf, menu_info)) {
            case mED_LINE_OK:
                mED_output_code(editor_ovl);
                break;
        }
    }
}

static void mED_input_multi_line(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    u8 buf[mDI_ENTRY_SIZE];
    u16 wbuf[mDI_ENTRY_SIZE + 2];
    mED_input_multi_line_R(submenu, editor_ovl, buf, wbuf);
}

static void mED_input_pw_make_line(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    if (editor_ovl->now_code != CHAR_NEW_LINE) {
        int width = mED_get_single_line_width(editor_ovl);
        if (editor_ovl->now_str_len < editor_ovl->input_length &&
            width + mFont_TEX_CHAR_WIDTH <= editor_ovl->line_width) {
            mED_output_code(editor_ovl);
        }
    }
}

static void mED_input_pw_chk_line_sub(u8* str, int idx, u8 code) {
    u8* src = str + mPC_STR_SIZE - 2;
    u8* dst = str + mPC_STR_SIZE - 1;
    int i;
    for (i = mPC_STR_SIZE - 1 - idx; i > 0; i--) {
        *dst-- = *src--;
    }
    str[idx] = code;
}

static void mED_input_pw_chk_line(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    u8 last;
    mPC_Ovl_c* passwordChk_ovl = submenu->overlay->passwordChk_ovl;
    if (editor_ovl->now_code != CHAR_NEW_LINE) {
        if (passwordChk_ovl->line1[mPC_STR_SIZE - 1] == CHAR_SPACE &&
            editor_ovl->cursor_idx < editor_ovl->input_length) {
            last = editor_ovl->input_str[mPC_STR_SIZE - 1];
            mED_input_pw_chk_line_sub(editor_ovl->input_str, editor_ovl->cursor_idx, editor_ovl->now_code);
            if (passwordChk_ovl->selected_line == 0) {
                mED_input_pw_chk_line_sub(passwordChk_ovl->line1, 0, last);
            }
            editor_ovl->cursor_idx++;
            if (editor_ovl->cursor_idx >= editor_ovl->input_length) {
                if (passwordChk_ovl->selected_line == 0) {
                    passwordChk_ovl->selected_line = 1;
                    editor_ovl->input_str = passwordChk_ovl->line1;
                    editor_ovl->cursor_idx = 0;
                } else {
                    editor_ovl->cursor_idx = editor_ovl->input_length;
                }
            }
            editor_ovl->se_flag = TRUE;
        } else {
            sAdo_SysTrgStart(0x1003);
        }
    } else {
        sAdo_SysTrgStart(0x1003);
    }
}

static void mED_move_cursol_right(Submenu* submenu, mED_Ovl_c* editor_ovl, int line_type) {
    s16 now_str_len;
    s16 cursor_idx;

    cursor_idx = editor_ovl->cursor_idx;
    now_str_len = editor_ovl->now_str_len;

    if (cursor_idx < now_str_len && now_str_len > 0) {
        editor_ovl->cursor_idx = cursor_idx + 1;
        editor_ovl->se_flag = TRUE;
    } else if (cursor_idx == now_str_len) {
        editor_ovl->now_code = CHAR_SPACE;

        switch (line_type) {
            case mED_LINETYPE_MULTI:
                mED_input_multi_line(submenu, editor_ovl);
                break;
            case mED_LINETYPE_SINGLE:
                mED_input_single_line(submenu, editor_ovl);
                break;
            case mED_LINETYPE_PW:
                mED_input_pw_make_line(submenu, editor_ovl);
                break;
        }

        if (editor_ovl->se_flag != FALSE) {
            editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
        }
    }
}

static void mED_move_cursol_left(mED_Ovl_c* editor_ovl) {
    if (editor_ovl->cursor_idx > 0) {
        editor_ovl->cursor_idx--;
        editor_ovl->se_flag = TRUE;
    }
}

static void mED_move_cursol_upper(mED_Ovl_c* editor_ovl) {
    if (editor_ovl->cursor_row > 0) {
        editor_ovl->cursor_row--;
        mED_set_idxcol_inLineWidth(editor_ovl);
        editor_ovl->se_flag = TRUE;
    }
}

static void mED_move_cursol_lower(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    s16 a;
    s16 b;
    s16 c;

    mED_get_col_line_width(&submenu->overlay->menu_info[mSM_OVL_EDITOR], editor_ovl, &a, &b, &c,
                           editor_ovl->now_str_len);

    if (editor_ovl->cursor_row < b) {
        editor_ovl->cursor_row++;
        mED_set_idxcol_inLineWidth(editor_ovl);
        editor_ovl->se_flag = TRUE;
    } else if (editor_ovl->cursor_idx == editor_ovl->now_str_len) {
        editor_ovl->now_code = CHAR_NEW_LINE;
        mED_input_multi_line(submenu, editor_ovl);

        if (editor_ovl->se_flag != FALSE) {
            editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
        }
    }
}

static void mED_end_edit_func(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_BOTTOM); // transition off the bottom of the screen
    submenu->overlay->editor_ovl->se_flag = TRUE;
}

static void mED_backspace_func(mED_Ovl_c* editor_ovl) {
    int idx;
    int i;
    if (editor_ovl->cursor_idx != 0) {
        editor_ovl->cursor_idx--;
        editor_ovl->now_str_len--;
        idx = editor_ovl->cursor_idx;
        for (i = editor_ovl->cursor_idx; i < editor_ovl->now_str_len; idx++) {
            mED_set_str_data(editor_ovl, idx, mED_get_str_data(editor_ovl, idx + 1));
            i++;
        }
        mED_set_str_data(editor_ovl, idx, CHAR_SPACE);
        editor_ovl->se_flag = TRUE;
    }
}

static void mED_backspace_func_pw_chk_sub(int idx, u8* str) {
    mem_copy(str + idx, str + idx + 1, mPC_STR_SIZE - 1 - idx);
    str[mPC_STR_SIZE - 1] = CHAR_SPACE;
}

static void mED_backspace_func_pw_chk(Submenu* submenu, mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl,
                                      mPC_Ovl_c* passwordChk_ovl) {
    if (editor_ovl->cursor_idx != 0) {
        editor_ovl->cursor_idx--;
        mED_backspace_func_pw_chk_sub(editor_ovl->cursor_idx, editor_ovl->input_str);
        if (passwordChk_ovl->selected_line == 0) {
            passwordChk_ovl->line0[mPC_STR_SIZE - 1] = passwordChk_ovl->line1[0];
            mED_backspace_func_pw_chk_sub(0, passwordChk_ovl->line1);
        }
        editor_ovl->se_flag = TRUE;
    } else if (passwordChk_ovl->selected_line == 1) {
        u8 first = passwordChk_ovl->line1[0];
        mED_backspace_func_pw_chk_sub(0, passwordChk_ovl->line1);
        passwordChk_ovl->selected_line = 0;
        editor_ovl->input_str = passwordChk_ovl->line0;
        editor_ovl->cursor_idx = editor_ovl->input_length - 1;
        editor_ovl->input_str[editor_ovl->cursor_idx] = first;
        editor_ovl->se_flag = TRUE;
    } else if (mMl_strlen(passwordChk_ovl->line0, mPC_STR_SIZE, CHAR_SPACE) == 0 &&
               mMl_strlen(passwordChk_ovl->line1, mPC_STR_SIZE, CHAR_SPACE) == 0) {
        mED_end_edit_func(submenu, menu_info);
    }
}

static int mED_get_exchange_code(mED_Ovl_c* editor_ovl) {
    int exchange = -1;
    if (editor_ovl->cursor_idx != 0) {
        int code = mED_get_str_data(editor_ovl, editor_ovl->cursor_idx - 1);
        if (code >= TOTAL_CHARS) {
            return -1;
        } else {
            int ornament = editor_ovl->latin_shift_mode == TRUE ? code : mED_ornament_table[code];
            if (code != ornament) {
                exchange = ornament;
            }
        }
    }
    return exchange;
}

static int mED_get_exchange_code_pw_chk(Submenu* submenu, mED_Ovl_c* editor_ovl) {
    mPC_Ovl_c* passwordChk_ovl = submenu->overlay->passwordChk_ovl;
    int code;
    int exchange = -1;
    if (editor_ovl->cursor_idx != 0) {
        code = mED_get_str_data(editor_ovl, editor_ovl->cursor_idx - 1);
    } else if (passwordChk_ovl->selected_line == 1) {
        code = passwordChk_ovl->line0[editor_ovl->input_length - 1];
    } else {
        return -1;
    }
    if (code >= TOTAL_CHARS) {
        return -1;
    } else {
        int ornament = editor_ovl->latin_shift_mode == TRUE ? code : mED_ornament_table[code];
        if (code != ornament) {
            exchange = ornament;
        }
    }
    return exchange;
}

static int mED_exchange_code_func(mED_Ovl_c* editor_ovl) {
    if (editor_ovl->exchange_code != -1) {
        editor_ovl->se_flag = TRUE;
        mED_set_str_data(editor_ovl, editor_ovl->cursor_idx - 1, editor_ovl->exchange_code);
    }
    return editor_ovl->se_flag;
}

static int mED_exchange_code_func_pw_chk(mED_Ovl_c* editor_ovl, mPC_Ovl_c* passwordChk_ovl) {
    if (editor_ovl->exchange_code != -1) {
        editor_ovl->se_flag = TRUE;
        if (editor_ovl->cursor_idx == 0 && passwordChk_ovl->selected_line == 1) {
            passwordChk_ovl->line0[editor_ovl->input_length - 1] = editor_ovl->exchange_code;
        } else {
            mED_set_str_data(editor_ovl, editor_ovl->cursor_idx - 1, editor_ovl->exchange_code);
        }
    }
    return editor_ovl->se_flag;
}

static void mED_clear_input_data(mED_Ovl_c* editor_ovl) {
    int idx = 0;
    int i;
    for (i = 0; i < editor_ovl->input_length; i++) {
        mED_set_str_data(editor_ovl, idx, CHAR_SPACE);
        idx++;
    }
    editor_ovl->now_str_len = 0;
    editor_ovl->cursor_col = 0;
    editor_ovl->cursor_idx = 0;
    editor_ovl->cursor_line_width = 0;
}

static int mED_all_space_check(Submenu* submenu, mED_Ovl_c* editor_ovl, mSM_MenuInfo_c* menu_info) {
    if (menu_info->data0 != mED_TYPE_LEDIT && menu_info->data0 != mED_TYPE_LEDIT_LATIN) {
        return FALSE;
    } else {
        int res;

        if (submenu->overlay->menu_info[mSM_OVL_LEDIT].data0 == mLE_TYPE_EPHRASE) {
            if (mem_cmp(submenu->overlay->menu_info[mSM_OVL_LEDIT].data2, editor_ovl->input_str,
                        editor_ovl->input_length) == 0) {
                res = FALSE;
            } else {
                res = TRUE;
            }
        } else {
            res = FALSE;
        }

        if (res == FALSE) {
            int i;

            for (i = 0; i < editor_ovl->now_str_len; i++) {
                if (mED_get_str_data(editor_ovl, i) != CHAR_SPACE) {
                    return FALSE;
                }
            }
        }

        mED_clear_input_data(editor_ovl);
        return TRUE;
    }
}

static int mED_ng_word_check(mED_Ovl_c* editor_ovl, mSM_MenuInfo_c* menu_info) {
    return FALSE;
}

static void mED_edit_func_multi_line(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_cursol_left(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_LOWER:
            mED_move_cursol_lower(submenu, editor_ovl);
            break;
        case mED_COMMAND_CURSOL_UPPER:
            mED_move_cursol_upper(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_cursol_right(submenu, editor_ovl, mED_LINETYPE_MULTI);
            break;
        case mED_COMMAND_END_EDIT:
            mED_end_edit_func(submenu, menu_info);
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func(editor_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_multi_line(submenu, editor_ovl);
            break;
    }
}

static void mED_edit_func_single_line(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_cursol_left(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_LOWER:
            break;
        case mED_COMMAND_CURSOL_UPPER:
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_cursol_right(submenu, editor_ovl, mED_LINETYPE_SINGLE);
            break;
        case mED_COMMAND_END_EDIT:
            if (mED_all_space_check(submenu, editor_ovl, menu_info) != FALSE) {
                sAdo_SysTrgStart(0x1003);
            } else if (mED_ng_word_check(editor_ovl, menu_info) != FALSE) {
                sAdo_SysTrgStart(0x1003);
            } else {
                mED_end_edit_func(submenu, menu_info);
            }
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func(editor_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_single_line(submenu, editor_ovl);
            break;
    }
}

static void mED_edit_func_letter_header_kill_space(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mED_Ovl_c* editor_ovl = overlay->editor_ovl;
    mBD_Ovl_c* board_ovl = overlay->board_ovl;

    if ((overlay->menu_info[mSM_OVL_BOARD].data0 == mSM_BD_OPEN_WRITE_ISLAND ||
         overlay->menu_info[mSM_OVL_BOARD].data0 == mSM_BD_OPEN_WRITE_BIRTHDAY)) {
        s16 len = mED_strlen(editor_ovl, editor_ovl->input_length, CHAR_SPACE);
        s16 cursor_col = editor_ovl->cursor_col;

        if (cursor_col > len) {
            len = cursor_col;
        }

        editor_ovl->now_str_len = len;
    } else {
        s16 len = mED_strlen(editor_ovl, editor_ovl->input_length, CHAR_SPACE);
        int header_back_start = board_ovl->mail.content.header_back_start;
        int min_len = editor_ovl->cursor_col;
        int res;

        if (len > header_back_start) {
            res = len;
        } else {
            res = header_back_start;
        }

        if (res > min_len) {
            res = header_back_start;

            if (len > header_back_start) {
                res = len;
            }
        } else {
            res = min_len;
        }

        editor_ovl->now_str_len = res;
    }
}

static void mED_edit_func_letter_header(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mED_Ovl_c* editor_ovl = overlay->editor_ovl;
    mBD_Ovl_c* board_ovl = overlay->board_ovl;

    if ((overlay->menu_info[mSM_OVL_BOARD].data0 == mSM_BD_OPEN_WRITE_ISLAND ||
         overlay->menu_info[mSM_OVL_BOARD].data0 == mSM_BD_OPEN_WRITE_BIRTHDAY)) {
        mED_edit_func_single_line(submenu, menu_info);
    } else if (board_ovl->header_pos != mBD_HEADER_POS_ON_NAME) {
        s16 len = editor_ovl->now_str_len;

        if (board_ovl->mail.content.header_back_start == editor_ovl->cursor_idx &&
            ((board_ovl->header_pos == mBD_HEADER_POS_PRE_NAME && editor_ovl->command == mED_COMMAND_CURSOL_RIGHT) ||
             (board_ovl->header_pos == mBD_HEADER_POS_POST_NAME &&
              (editor_ovl->command == mED_COMMAND_CURSOL_LEFT || editor_ovl->command == mED_COMMAND_BACKSPACE)))) {
            board_ovl->header_pos = mBD_HEADER_POS_ON_NAME;
            editor_ovl->se_flag = TRUE;
        } else {
            mED_edit_func_single_line(submenu, menu_info);

            if (board_ovl->header_pos == mBD_HEADER_POS_PRE_NAME) {
                if (len > editor_ovl->now_str_len) {
                    board_ovl->mail.content.header_back_start--;
                } else if (len < editor_ovl->now_str_len) {
                    board_ovl->mail.content.header_back_start++;
                }
            }
        }
    }

    mED_edit_func_letter_header_kill_space(submenu);
}

static void mED_break_space_code(mED_Ovl_c* editor_ovl) {
    u16 str[MAIL_FOOTER_LEN];
    u16* dst = editor_ovl->input_wstr;
    mem_copy((u8*)str, (u8*)(dst + 1), (MAIL_FOOTER_LEN - 1) * sizeof(u16));
    str[MAIL_FOOTER_LEN - 1] = CHAR_SPACE;
    mem_copy((u8*)dst, (u8*)str, sizeof(str));
}

static void mED_input_footer_line_sub(Submenu* submenu, mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl) {
    int width = editor_ovl->now_str_len * mFont_TEX_CHAR_WIDTH + mFont_TEX_CHAR_WIDTH;
    if (editor_ovl->now_str_len + 1 <= editor_ovl->input_length) {
        if (width <= editor_ovl->line_width) {
            mED_output_code(editor_ovl);
        } else if (mED_get_str_data(editor_ovl, 0) == CHAR_SPACE &&
                   width - mFont_TEX_CHAR_WIDTH < editor_ovl->line_width) {
            mED_break_space_code(editor_ovl);
            editor_ovl->now_str_len--;
            mED_output_code(editor_ovl);
        }
    } else if (mED_get_str_data(editor_ovl, 0) == CHAR_SPACE && width - mFont_TEX_CHAR_WIDTH < editor_ovl->line_width) {
        mED_break_space_code(editor_ovl);
        editor_ovl->now_str_len--;
        mED_output_code(editor_ovl);
    }
}

static void mED_input_footer_line(Submenu* submenu, mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl) {
    switch (editor_ovl->now_code) {
        case CHAR_NEW_LINE:
            break;
        case CHAR_SPACE:
            if (editor_ovl->cursor_idx != 0) {
                mED_input_footer_line_sub(submenu, menu_info, editor_ovl);
            }
            break;
        default:
            mED_input_footer_line_sub(submenu, menu_info, editor_ovl);
            break;
    }
}

static void mED_move_footer_cursol_right(Submenu* submenu, mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl) {
    s16 str_len;
    s16 cursor_idx;

    cursor_idx = editor_ovl->cursor_idx;
    str_len = editor_ovl->now_str_len;

    if (cursor_idx < str_len && str_len > 0) {
        if (cursor_idx == 0 && mED_get_str_data(editor_ovl, 0) == CHAR_SPACE) {
            int idx = 0;
            int i;

            editor_ovl->now_str_len--;
            for (i = 0; i < editor_ovl->now_str_len; idx++) {
                mED_set_str_data(editor_ovl, idx, mED_get_str_data(editor_ovl, idx + 1));
                i++;
            }

            mED_set_str_data(editor_ovl, idx, CHAR_SPACE);
            editor_ovl->se_flag = TRUE;
        } else {
            editor_ovl->cursor_idx++;
            editor_ovl->se_flag = TRUE;
        }
    } else if (cursor_idx == str_len) {
        editor_ovl->now_code = CHAR_SPACE;
        mED_input_footer_line(submenu, menu_info, editor_ovl);

        if (editor_ovl->se_flag) {
            editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
        }
    }
}

static void mED_move_footer_cursol_left(Submenu* submenu, mSM_MenuInfo_c* menu_info, mED_Ovl_c* editor_ovl) {
    if (editor_ovl->cursor_idx > 0) {
        editor_ovl->cursor_idx--;
        editor_ovl->se_flag = TRUE;
    } else if (editor_ovl->now_str_len < editor_ovl->input_length) {
        editor_ovl->now_code = CHAR_SPACE;
        mED_input_footer_line(submenu, menu_info, editor_ovl);
        editor_ovl->cursor_idx = 0;

        if (editor_ovl->se_flag) {
            editor_ovl->command = mED_COMMAND_OUTPUT_CODE;
        }
    }
}

static void mED_edit_func_letter_footer(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_footer_cursol_left(submenu, menu_info, editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_footer_cursol_right(submenu, menu_info, editor_ovl);
            break;
        case mED_COMMAND_END_EDIT:
            if (mED_all_space_check(submenu, editor_ovl, menu_info)) {
                sAdo_SysTrgStart(0x1003);

            } else {
                mED_end_edit_func(submenu, menu_info);
            }
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func(editor_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_footer_line(submenu, menu_info, editor_ovl);
            break;
    }
}

static void mED_move_letter_table(mED_Ovl_c* editor_ovl, mBD_Ovl_c* board_ovl, Submenu* submenu) {
    static s16 letter_table_col[mBD_FIELD_NUM] = { MAIL_HEADER_LEN, MAIL_BODY_LEN / mBD_BODY_LINE_NUM,
                                                   MAIL_FOOTER_LEN };
    static s16 letter_table_width[mBD_FIELD_NUM] = { 120, 192, 192 };

    u8 field = board_ovl->field;
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];
    int next_field;
    int upper;

    if (field == mBD_FIELD_HEADER && board_ovl->header_pos == mBD_HEADER_POS_ON_NAME) {
        return;
    }

    if (editor_ovl->command == mED_COMMAND_CURSOL_UPPER) {
        next_field = field - 1;
        upper = TRUE;
    } else if (editor_ovl->command == mED_COMMAND_CURSOL_LOWER) {
        next_field = field + 1;
        upper = FALSE;
    } else {
        return;
    }

    if (next_field < 0 || next_field >= mBD_FIELD_NUM) {
        return;
    }

    editor_ovl->se_flag = TRUE;
    board_ovl->field = next_field;
    board_ovl->header_pos = mBD_HEADER_POS_PRE_NAME;
    editor_ovl->input_length = letter_table_col[next_field];
    editor_ovl->line_width = letter_table_width[next_field];
    menu_info->data3 = letter_table_width[next_field];

    if (next_field == mBD_FIELD_BODY) {
        editor_ovl->max_line_no = mBD_BODY_LINE_NUM;
        editor_ovl->input_wstr = (u16*)board_ovl->mail.content.text.all + MAIL_HEADER_LEN;

        if (upper == TRUE) {
            editor_ovl->cursor_idx = -1;
        } else {
            editor_ovl->cursor_idx = 0;
        }
    } else {
        editor_ovl->max_line_no = 1;
        editor_ovl->cursor_idx = 0;

        if (next_field == mBD_FIELD_HEADER) {
            editor_ovl->input_wstr = (u16*)board_ovl->mail.content.text.split.header;
        } else {
            editor_ovl->input_wstr = (u16*)board_ovl->mail.content.text.all + MAIL_HEADER_LEN + MAIL_BODY_LEN;
        }
    }

    editor_ovl->now_str_len = board_ovl->lengths[next_field];

    if (editor_ovl->cursor_idx == -1) {
        editor_ovl->cursor_idx = editor_ovl->now_str_len;
    }
}

typedef void (*mED_BASE_FUNC)(Submenu*, mSM_MenuInfo_c*);

static void mED_edit_func_letter(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mED_BASE_FUNC letter_base_func[mBD_FIELD_NUM] = { &mED_edit_func_letter_header, &mED_edit_func_multi_line,
                                                             &mED_edit_func_letter_footer };

    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;
    int field = board_ovl->field;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    (*letter_base_func[field])(submenu, menu_info);
    board_ovl->lengths[field] = editor_ovl->now_str_len;

    if (editor_ovl->se_flag == FALSE) {
        mED_move_letter_table(editor_ovl, board_ovl, submenu);
    }
}

static void mED_edit_func_diary(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    /* @unused */
    static mED_BASE_FUNC letter_base_func[mBD_FIELD_NUM] = { &mED_edit_func_letter_header, &mED_edit_func_multi_line,
                                                             &mED_edit_func_single_line };

    mDI_Ovl_c* diary_ovl = submenu->overlay->diary_ovl;
    int field = diary_ovl->field;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_cursol_left(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_LOWER:
            mED_move_cursol_lower(submenu, editor_ovl);
            break;
        case mED_COMMAND_CURSOL_UPPER:
            mED_move_cursol_upper(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_cursol_right(submenu, editor_ovl, mED_LINETYPE_MULTI);
            break;
        case mED_COMMAND_END_EDIT:
            mED_end_edit_func(submenu, menu_info);
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func(editor_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_multi_line(submenu, editor_ovl);
            break;
    }

    diary_ovl->entry_len[field] = editor_ovl->now_str_len;
}

static void mED_move_pw_make_table(mED_Ovl_c* editor_ovl, mPM_Ovl_c* passwordMake_ovl) {
    static s16 pm_make_table_col[mPM_ENTRY_NUM] = { LAND_NAME_SIZE, PLAYER_NAME_LEN };
    int next_idx;

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LOWER: {
            if (passwordMake_ovl->selected_idx == mPM_ENTRY_TOWN) {
                editor_ovl->now_str_len = mED_strlen(editor_ovl, editor_ovl->input_length, CHAR_SPACE);
                editor_ovl->cursor_idx = editor_ovl->now_str_len;
                passwordMake_ovl->lengths[mPM_ENTRY_TOWN] = editor_ovl->now_str_len;

                if (editor_ovl->now_str_len == 0) {
                    sAdo_SysTrgStart(0x1003);
                    return;
                }
            }

            next_idx = passwordMake_ovl->selected_idx + 1;
            break;
        }

        case mED_COMMAND_CURSOL_UPPER:
        case mED_COMMAND_BACKSPACE:
            next_idx = passwordMake_ovl->selected_idx - 1;
            break;

        default:
            return;
    }

    if (next_idx < 0 || next_idx >= mPM_ENTRY_NUM) {
        return;
    }

    editor_ovl->se_flag = TRUE;
    passwordMake_ovl->selected_idx = (u8)next_idx;
    editor_ovl->input_length = pm_make_table_col[next_idx];
    editor_ovl->line_width = editor_ovl->input_length * mFont_TEX_CHAR_WIDTH;

    switch (next_idx) {
        case mPM_ENTRY_TOWN:
            editor_ovl->input_str = passwordMake_ovl->town_name;
            break;
        case mPM_ENTRY_PLAYER:
            editor_ovl->input_str = passwordMake_ovl->player_name;
            break;
    }

    editor_ovl->max_line_no = 1;
    editor_ovl->now_str_len = passwordMake_ovl->lengths[next_idx];

    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_UPPER:
        case mED_COMMAND_CURSOL_LOWER:
            mED_set_idxcol_inLineWidth(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            editor_ovl->cursor_idx = 0;
            break;
        case mED_COMMAND_CURSOL_LEFT:
        default:
            editor_ovl->cursor_idx = editor_ovl->now_str_len;
            break;
    }
}

static void mED_edit_func_pw_make(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int selected_idx;
    mPM_Ovl_c* passwordMake_ovl;
    mED_Ovl_c* editor_ovl;
    editor_ovl = submenu->overlay->editor_ovl;
    passwordMake_ovl = submenu->overlay->passwordMake_ovl;
    selected_idx = passwordMake_ovl->selected_idx;
    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            mED_move_cursol_left(editor_ovl);
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            mED_move_cursol_right(submenu, editor_ovl, mED_LINETYPE_PW);
            break;
        case mED_COMMAND_END_EDIT:
            if (mED_strlen(editor_ovl, editor_ovl->input_length, CHAR_SPACE) == 0) {
                if (editor_ovl->cursor_idx == 0) {
                    submenu->item_p->slot_no = FALSE;
                    mED_end_edit_func(submenu, menu_info);
                    editor_ovl->se_flag = FALSE;
                    sAdo_SysTrgStart(2);
                } else {
                    editor_ovl->cursor_idx = 0;
                    editor_ovl->now_str_len = 0;
                    sAdo_SysTrgStart(0x1003);
                }
            } else if (passwordMake_ovl->selected_idx == mPM_ENTRY_TOWN) {
                editor_ovl->command = mED_COMMAND_CURSOL_LOWER;
            } else {
                submenu->item_p->slot_no = TRUE;
                mED_end_edit_func(submenu, menu_info);
                editor_ovl->se_flag = FALSE;
            }
            break;
        case mED_COMMAND_BACKSPACE:
            if (editor_ovl->cursor_idx == 0 && selected_idx == mPM_ENTRY_TOWN) {
                int town_len = mED_strlen(editor_ovl, editor_ovl->input_length, CHAR_SPACE);
                int player_len = mMl_strlen(passwordMake_ovl->player_name, PLAYER_NAME_LEN, CHAR_SPACE);
                if (town_len == 0 || player_len == 0) {
                    submenu->item_p->slot_no = FALSE;
                    mED_end_edit_func(submenu, menu_info);
                }
            } else {
                mED_backspace_func(editor_ovl);
            }
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func(editor_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_pw_make_line(submenu, editor_ovl);
            break;
    }
    passwordMake_ovl->lengths[selected_idx] = editor_ovl->now_str_len;
    if (editor_ovl->se_flag == FALSE)
        mED_move_pw_make_table(editor_ovl, passwordMake_ovl);
}

static int mED_move_pw_chk_table(mED_Ovl_c* editor_ovl, mPC_Ovl_c* passwordChk_ovl, u8 command) {
    int next_line;
    switch (command) {
        case mED_COMMAND_CURSOL_LOWER:
            next_line = passwordChk_ovl->selected_line + 1;
            break;
        case mED_COMMAND_CURSOL_UPPER:
            next_line = passwordChk_ovl->selected_line - 1;
            break;
        default:
            return FALSE;
    }
    if (next_line < 0 || next_line >= mPC_LINE_COUNT)
        return FALSE;
    if (next_line == 0 && editor_ovl->cursor_idx >= editor_ovl->input_length) {
        next_line = 1;
        editor_ovl->cursor_idx = 0;
    }
    editor_ovl->se_flag = TRUE;
    passwordChk_ovl->selected_line = (u8)next_line;
    switch (next_line) {
        case 0:
            editor_ovl->input_str = passwordChk_ovl->line0;
            break;
        case 1:
            editor_ovl->input_str = passwordChk_ovl->line1;
            break;
    }
    return TRUE;
}

static void mED_edit_func_pw_chk(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mPC_Ovl_c* passwordChk_ovl = submenu->overlay->passwordChk_ovl;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    switch (editor_ovl->command) {
        case mED_COMMAND_CURSOL_LEFT:
            if (editor_ovl->cursor_idx > 0) {
                editor_ovl->cursor_idx--;
                editor_ovl->se_flag = TRUE;
            } else if (mED_move_pw_chk_table(editor_ovl, passwordChk_ovl, mED_COMMAND_CURSOL_UPPER)) {
                editor_ovl->cursor_idx = editor_ovl->input_length - 1;
            } else {
                sAdo_SysTrgStart(0x1003);
            }
            break;
        case mED_COMMAND_CURSOL_RIGHT:
            if ((passwordChk_ovl->selected_line == 1 && editor_ovl->cursor_idx < editor_ovl->input_length) ||
                (passwordChk_ovl->selected_line == 0 && editor_ovl->cursor_idx < editor_ovl->input_length - 1)) {
                editor_ovl->cursor_idx++;
                editor_ovl->se_flag = TRUE;
            } else if (mED_move_pw_chk_table(editor_ovl, passwordChk_ovl, mED_COMMAND_CURSOL_LOWER)) {
                editor_ovl->cursor_idx = 0;
            } else {
                sAdo_SysTrgStart(0x1003);
            }
            break;
        case mED_COMMAND_END_EDIT:
            mED_end_edit_func(submenu, menu_info);
            editor_ovl->se_flag = FALSE;
            sAdo_SysTrgStart(2);
            break;
        case mED_COMMAND_BACKSPACE:
            mED_backspace_func_pw_chk(submenu, menu_info, editor_ovl, passwordChk_ovl);
            break;
        case mED_COMMAND_EXCHANGE_CODE:
            mED_exchange_code_func_pw_chk(editor_ovl, passwordChk_ovl);
            break;
        case mED_COMMAND_OUTPUT_CODE:
            mED_input_pw_chk_line(submenu, editor_ovl);
            break;
    }
    if (editor_ovl->se_flag == FALSE)
        mED_move_pw_chk_table(editor_ovl, passwordChk_ovl, editor_ovl->command);
}

static void mED_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

typedef void (*mED_EDIT_FUNC)(Submenu*, mSM_MenuInfo_c*);

static void mED_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mED_EDIT_FUNC mED_edit_func[mED_TYPE_NUM] = { &mED_edit_func_letter,      &mED_edit_func_multi_line,
                                                         &mED_edit_func_multi_line,  &mED_edit_func_single_line,
                                                         &mED_edit_func_single_line, &mED_edit_func_diary,
                                                         &mED_edit_func_pw_make,     &mED_edit_func_pw_chk,
                                                         &mED_edit_func_single_line };

    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    mBD_Ovl_c* board_ovl;

    editor_ovl->se_flag = FALSE;
    if (submenu->overlay->address_ovl != NULL &&
        submenu->overlay->menu_info[mSM_OVL_ADDRESS].next_proc_status == mSM_OVL_PROC_WAIT) {
        editor_ovl->stick_area = mED_STICK_AREA_CENTER;
        editor_ovl->stick_area_changed = FALSE;
        editor_ovl->command = mED_COMMAND_NONE;
        editor_ovl->last_buttons =
            (getButton() | getTrigger()) & (BUTTON_B | BUTTON_DRIGHT | BUTTON_DLEFT | BUTTON_DDOWN | BUTTON_DUP);
        editor_ovl->button_repeat_timer = 30;
        editor_ovl->button_repeat_accel_timer = 26;
        editor_ovl->button_repeat_started = 0;

        if (submenu->overlay->address_ovl->editor_move_down) {
            board_ovl = submenu->overlay->board_ovl;

            if (board_ovl != NULL) {
                submenu->overlay->address_ovl->editor_move_down = FALSE;
                editor_ovl->command = mED_COMMAND_CURSOL_LOWER;
                mED_move_letter_table(editor_ovl, board_ovl, submenu);
                editor_ovl->exchange_code = mED_get_exchange_code(editor_ovl);
            }
        }
    } else {
        editor_ovl->cursol_opacity_step++;

        if (editor_ovl->cursol_opacity_step == 40) {
            editor_ovl->cursol_opacity_step = 0;
        }

        mED_set_stick_area(submenu);
        if (editor_ovl->rotate_timer != 0) {
            if (editor_ovl->stick_area_changed == TRUE && editor_ovl->stick_area != mED_STICK_AREA_CENTER) {
                editor_ovl->rotate_timer = 0;
                while (editor_ovl->page_top_num % mED_CHARS_PER_PAGE != 0) {
                    editor_ovl->page_top_num++;
                }
                if (editor_ovl->page_top_num == page_num_max[editor_ovl->shift_mode]) {
                    editor_ovl->page_top_num = 0;
                }
            } else {
                editor_ovl->rotate_timer--;
                if (editor_ovl->rotate_timer == 2) {
                    editor_ovl->page_top_num += 2;
                    if (editor_ovl->page_top_num == page_num_max[editor_ovl->shift_mode]) {
                        editor_ovl->page_top_num = 0;
                    }
                }
                return;
            }
        }
        mED_set_command(submenu);
        (*mED_edit_func[menu_info->data0])(submenu, menu_info);

        if (editor_ovl->consonant_num == -1) {
            if (editor_ovl->anim_frame != 0)
                editor_ovl->anim_frame--;
        } else if (editor_ovl->anim_frame < 5) {
            editor_ovl->anim_frame++;
        }
        if (editor_ovl->se_flag) {
            mED_set_se(submenu);
            if (menu_info->data0 == mED_TYPE_PASSWORDCHK) {
                editor_ovl->exchange_code = mED_get_exchange_code_pw_chk(submenu, editor_ovl);
            } else {
                editor_ovl->exchange_code = mED_get_exchange_code(editor_ovl);
            }

            if (editor_ovl->command == mED_COMMAND_CURSOL_RIGHT || editor_ovl->command == mED_COMMAND_CURSOL_LEFT ||
                editor_ovl->command == mED_COMMAND_CURSOL_UPPER || editor_ovl->command == mED_COMMAND_CURSOL_LOWER ||
                editor_ovl->command == mED_COMMAND_BACKSPACE || editor_ovl->command == mED_COMMAND_OUTPUT_CODE) {
                editor_ovl->cursol_opacity_step = 0;
            }
        }
    }

    mED_get_col_line_width(menu_info, editor_ovl, &editor_ovl->cursor_col, &editor_ovl->cursor_row,
                           &editor_ovl->cursor_line_width, editor_ovl->cursor_idx);
    mED_check_line_over(editor_ovl);
}

static void mED_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (submenu->menu_type != menu_info->next_menu_type) {
        menu_info->proc_status = mSM_OVL_PROC_PLAY;
    }
}

static void mED_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->editor_ovl->cursor_col = 0;
    (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

typedef void (*mED_OVL_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mED_editor_ovl_move(Submenu* submenu) {
    static mED_OVL_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = { &mED_move_Move, &mED_move_Play, &mED_move_Wait,
                                                                 (mED_OVL_MOVE_PROC)&none_proc1, &mED_move_End };

    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];

    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern u8 lat_sousa_b3_tex[];
extern u8 lat_sousa_b32_tex[];
extern Gfx lat_sousa_b3_model[];
extern u8 lat_sousa_b2_tex[];
extern u8 lat_sousa_b22_tex[];
extern Gfx lat_sousa_b2_model[];
extern Gfx lat_sousa_b1_model[];
extern Gfx lat_sousa_waku3T_model[];
extern Gfx lat_sousa_waku2T_model[];
extern u8 lat_sousa_w1_tex_rgb_ia8[];
extern u8 lat_sousa_w2_tex_rgb_ia8[];
extern u8 lat_sousa_w3_tex_rgb_ia8[];
extern Gfx lat_sousa_waku1T_model[];
extern u8 lat_sousa_jyu1_tex_rgb_ia8[];
extern u8 lat_sousa_jyu2_tex_rgb_ia8[];
extern u8 lat_sousa_jyu3_tex_rgb_ia8[];
extern u8 lat_sousa_jyu4_tex_rgb_ia8[];
extern u8 lat_sousa_jyu5_tex_rgb_ia8[];
extern Gfx lat_sousa_jyuT_model[];
extern u8 lat_sousa_x_tex_rgb_ia8[];
extern u8 lat_sousa_x2_tex_rgb_ia8[];
extern u8 lat_sousa_y_tex_rgb_ia8[];
extern u8 lat_sousa_y2_tex_rgb_ia8[];
extern Gfx lat_sousa_model[];
extern Gfx lat_sousa_kirikae2T_model[];
extern Gfx lat_sousa_kirikaeT_model[];
extern Gfx lat_sousa_hiraT_model[];
extern Gfx lat_sousa_kigouT_model[];
extern Gfx lat_sousa_kataT_model[];
extern Gfx lat_sousa_eiT_model[];
extern Gfx lat_sousa_suT_model[];
extern Gfx lat_sousa_hira2T_model[];
extern Gfx lat_sousa_kigou2T_model[];
extern Gfx lat_sousa_kata2T_model[];
extern Gfx lat_sousa_ei2T_model[];
extern Gfx lat_sousa_su2T_model[];
extern Gfx lat_sousa_emoji2T_model[];
extern Gfx lat_sousa_teiT_model[];
extern Gfx lat_sousa_henT_model[];
extern Gfx lat_sousa_henkanT_model[];
extern Gfx lat_sousa_word_combine[];
extern Gfx lat_sousa_henyajiT_model[];
extern u8 lat_sousa_st5_tex_rgb_ia8[];
extern u8 lat_sousa_st4_tex_rgb_ia8[];
extern u8 lat_sousa_st2_tex_rgb_ia8[];
extern u8 lat_sousa_st6_tex_rgb_ia8[];
extern u8 lat_sousa_st3_tex_rgb_ia8[];
extern u8 lat_sousa_st1_tex_rgb_ia8[];
extern Gfx lat_sousa_other_combine[];
extern Gfx lat_sousa_stT_model[];
extern Gfx lat_sousa_yajiT_model[];
extern Gfx lat_sousa_mode[];
extern Gfx lat_sousa_sousaT_model[];
extern Gfx lat_sousa_2cycle_combine[];

enum {
    mED_MODEL_OUTER_PRIM,
    mED_MODEL_OUTER_ENV,
    mED_MODEL_MIDDLE_PRIM,
    mED_MODEL_MIDDLE_ENV,
    mED_MODEL_INNER_PRIM,
    mED_MODEL_INNER_ENV,
    mED_MODEL_ARROW,
    mED_MODEL_COLOR_NUM
};

static void mED_KeyDraw_A_button(GRAPH* graph) {
    static u8* lat_sousa_a_button_tbl[] = { lat_sousa_b3_tex, lat_sousa_b32_tex };
    int key = 0;
    Gfx* gfx;
    if (chkButton(BUTTON_A))
        key = 1;
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPSegment(gfx++, G_MWO_SEGMENT_8, lat_sousa_button_pallet_tbl[key]);
    gSPSegment(gfx++, G_MWO_SEGMENT_9, lat_sousa_a_button_tbl[key]);
    gSPDisplayList(gfx++, lat_sousa_b3_model);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_KeyDraw_B_button(GRAPH* graph) {
    static u8* lat_sousa_b_button_tbl[] = { lat_sousa_b2_tex, lat_sousa_b22_tex };
    int key = 0;
    Gfx* gfx;
    if (chkButton(BUTTON_B))
        key = 1;
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPSegment(gfx++, G_MWO_SEGMENT_8, lat_sousa_button_pallet_tbl[key]);
    gSPSegment(gfx++, G_MWO_SEGMENT_9, lat_sousa_b_button_tbl[key]);
    gSPDisplayList(gfx++, lat_sousa_b2_model);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_KeyDraw_START_button(GRAPH* graph) {
    Gfx* gfx;
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPDisplayList(gfx++, lat_sousa_b1_model);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_KeyDraw_Inside_circle(GRAPH* graph, mED_Ovl_c* editor_ovl, rgba_t* color) {
    s16 consonant = editor_ovl->consonant_num;
    Gfx* gfx;
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gDPSetPrimColor(gfx++, 0, 255, color[mED_MODEL_INNER_PRIM].r, color[mED_MODEL_INNER_PRIM].g,
                    color[mED_MODEL_INNER_PRIM].b, 255);
    gDPSetEnvColor(gfx++, color[mED_MODEL_INNER_ENV].r, color[mED_MODEL_INNER_ENV].g, color[mED_MODEL_INNER_ENV].b,
                   255);
    gSPDisplayList(gfx++, lat_sousa_waku3T_model);
    if (consonant != -1) {
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 255, color[mED_MODEL_MIDDLE_PRIM].r, color[mED_MODEL_MIDDLE_PRIM].g,
                        color[mED_MODEL_MIDDLE_PRIM].b, 255);
        gDPSetEnvColor(gfx++, color[mED_MODEL_MIDDLE_ENV].r, color[mED_MODEL_MIDDLE_ENV].g,
                       color[mED_MODEL_MIDDLE_ENV].b, 255);
        gSPDisplayList(gfx++, lat_sousa_waku2T_model);
    }
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_KeyDraw_Outside_circle(GRAPH* graph, mED_Ovl_c* editor_ovl, rgba_t* color) {
    static u8* lat_sousa_waku1_tex_tbl[] = { lat_sousa_w1_tex_rgb_ia8, lat_sousa_w2_tex_rgb_ia8,
                                             lat_sousa_w3_tex_rgb_ia8 };
    int shift = editor_ovl->shift_mode;
    s16 consonant = editor_ovl->consonant_num;
    Gfx* gfx;
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    if (shift == mED_SHIFT_MODE_HIRAGANA || shift == mED_SHIFT_MODE_KATAKANA) {
        int frame = editor_ovl->anim_frame >> 1;
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 255, color[mED_MODEL_OUTER_PRIM].r, color[mED_MODEL_OUTER_PRIM].g,
                        color[mED_MODEL_OUTER_PRIM].b, 255);
        gDPSetEnvColor(gfx++, color[mED_MODEL_OUTER_ENV].r, color[mED_MODEL_OUTER_ENV].g, color[mED_MODEL_OUTER_ENV].b,
                       255);
        gSPSegment(gfx++, G_MWO_SEGMENT_9, lat_sousa_waku1_tex_tbl[frame]);
        gSPDisplayList(gfx++, lat_sousa_waku1T_model);
    }
    if (consonant == -1) {
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 255, color[mED_MODEL_MIDDLE_PRIM].r, color[mED_MODEL_MIDDLE_PRIM].g,
                        color[mED_MODEL_MIDDLE_PRIM].b, 255);
        gDPSetEnvColor(gfx++, color[mED_MODEL_MIDDLE_ENV].r, color[mED_MODEL_MIDDLE_ENV].g,
                       color[mED_MODEL_MIDDLE_ENV].b, 255);
        gSPDisplayList(gfx++, lat_sousa_waku2T_model);
    }
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_KeyDraw_J_key(GRAPH* graph) {
    static u8* lat_sousa_jyu_button_tbl[] = { lat_sousa_jyu1_tex_rgb_ia8, lat_sousa_jyu2_tex_rgb_ia8,
                                              lat_sousa_jyu3_tex_rgb_ia8, lat_sousa_jyu4_tex_rgb_ia8,
                                              lat_sousa_jyu5_tex_rgb_ia8 };
    int key = 0;
    Gfx* gfx;
    if (chkButton(BUTTON_DLEFT))
        key = 2;
    else if (chkButton(BUTTON_DDOWN))
        key = 1;
    else if (chkButton(BUTTON_DUP))
        key = 4;
    else if (chkButton(BUTTON_DRIGHT))
        key = 3;
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPSegment(gfx++, G_MWO_SEGMENT_8, lat_sousa_jyu_button_tbl[key]);
    gSPDisplayList(gfx++, lat_sousa_jyuT_model);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_KeyDraw_XY_button(GRAPH* graph, mED_Ovl_c* editor_ovl) {
    static u8* lat_sousa_x_button_tbl[] = { lat_sousa_x_tex_rgb_ia8, lat_sousa_x2_tex_rgb_ia8 };
    static u8* lat_sousa_y_button_tbl[] = { lat_sousa_y_tex_rgb_ia8, lat_sousa_y2_tex_rgb_ia8 };
    int x = 0;
    int y = 0;
    Gfx* gfx;
    if (chkButton(BUTTON_X))
        x = 1;
    if (chkButton(BUTTON_Y))
        y = 1;
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPSegment(gfx++, G_MWO_SEGMENT_8, lat_sousa_x_button_tbl[x]);
    gSPSegment(gfx++, G_MWO_SEGMENT_9, lat_sousa_y_button_tbl[y]);
    gSPDisplayList(gfx++, lat_sousa_model);
    if (editor_ovl->is_wide_string == TRUE) {
        gSPDisplayList(gfx++, lat_sousa_kirikae2T_model);
    } else {
        gSPDisplayList(gfx++, lat_sousa_kirikaeT_model);
    }
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_KeyDraw_Strings(GRAPH* graph, mED_Ovl_c* editor_ovl) {
    static Gfx* displayList_table[mED_SHIFT_MODE_EMOJI] = { lat_sousa_hiraT_model, lat_sousa_kigouT_model,
                                                            lat_sousa_kataT_model, lat_sousa_eiT_model,
                                                            lat_sousa_suT_model };
    static Gfx* displayList_table2[mED_SHIFT_MODE_NUM] = { lat_sousa_hira2T_model, lat_sousa_kigou2T_model,
                                                           lat_sousa_kata2T_model, lat_sousa_ei2T_model,
                                                           lat_sousa_su2T_model,   lat_sousa_emoji2T_model };
    int shift = editor_ovl->shift_mode;
    int code = mED_get_now_code(editor_ovl);
    Gfx* gfx;
    int i;
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    switch (code) {
        case -1:
        case CHAR_MESSAGE_TAG:
            gSPDisplayList(gfx++, lat_sousa_teiT_model);
            break;
    }
    if (editor_ovl->latin_shift_mode != TRUE) {
        if (editor_ovl->exchange_code == -1) {
            gDPSetPrimColor(gfx++, 0, 255, 20, 20, 175, 255);
        } else {
            gDPSetPrimColor(gfx++, 0, 255, 120, 20, 20, 255);
        }
        gSPDisplayList(gfx++, lat_sousa_henT_model);
        if (editor_ovl->exchange_code == -1) {
            gSPDisplayList(gfx++, lat_sousa_henkanT_model);
        } else {
            gSPDisplayList(gfx++, lat_sousa_word_combine);
            gSPDisplayList(gfx++, lat_sousa_henyajiT_model);
        }
    }
    gSPDisplayList(gfx++, lat_sousa_word_combine);
    gDPSetPrimColor(gfx++, 0, 255, 225, 45, 0, 255);
    if (editor_ovl->is_wide_string == TRUE) {
        gSPDisplayList(gfx++, displayList_table2[shift]);
        gDPSetPrimColor(gfx++, 0, 255, 205, 135, 80, 255);
        for (i = 0; i < mED_SHIFT_MODE_NUM; i++) {
            if (i != shift) {
                gSPDisplayList(gfx++, displayList_table2[i]);
            }
        }
    } else {
        gSPDisplayList(gfx++, displayList_table[shift]);
        gDPSetPrimColor(gfx++, 0, 255, 205, 135, 80, 255);
        for (i = 0; i < mED_SHIFT_MODE_EMOJI; i++) {
            if (i != shift) {
                gSPDisplayList(gfx++, displayList_table[i]);
            }
        }
    }
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_KeyDraw_3D_stick(GRAPH* graph, mED_Ovl_c* editor_ovl, rgba_t* color) {
    static u8* lat_sousa_st_tex_tbl[mED_STICK_AREA_NUM] = { lat_sousa_st5_tex_rgb_ia8, lat_sousa_st4_tex_rgb_ia8,
                                                            lat_sousa_st2_tex_rgb_ia8, lat_sousa_st4_tex_rgb_ia8,
                                                            lat_sousa_st5_tex_rgb_ia8, lat_sousa_st6_tex_rgb_ia8,
                                                            lat_sousa_st3_tex_rgb_ia8, lat_sousa_st6_tex_rgb_ia8,
                                                            lat_sousa_st1_tex_rgb_ia8 };
    int stick = editor_ovl->stick_area;
    Gfx* gfx;
    Matrix_push();
    Matrix_translate(-74.0f, 23.2f, 0.0f, MTX_MULT);
    if (stick >= mED_STICK_AREA_TOP_RIGHT && stick <= mED_STICK_AREA_BOTTOM_RIGHT) {
        Matrix_RotateY(DEG2SHORT_ANGLE(-180.0f), MTX_MULT);
    }
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gfx++, G_MWO_SEGMENT_8, lat_sousa_st_tex_tbl[stick]);
    gDPSetTextureAdjustMode(gfx++, G_TA_DOLPHIN);
    gSPDisplayList(gfx++, lat_sousa_other_combine);
    gSPDisplayList(gfx++, lat_sousa_stT_model);
    gDPSetTextureAdjustMode(gfx++, G_TA_N64);
    Matrix_pull();
    gSPDisplayList(gfx++, lat_sousa_word_combine);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(gfx++, 0, 255, color[mED_MODEL_ARROW].r, color[mED_MODEL_ARROW].g, color[mED_MODEL_ARROW].b, 255);
    gSPDisplayList(gfx++, lat_sousa_yajiT_model);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_KeyDraw(mED_Ovl_c* editor_ovl, GRAPH* graph, f32 x, f32 y) {
    static rgba_t model_color[3][mED_MODEL_COLOR_NUM] = { { { 130, 60, 50, 255 },
                                                            { 40, 70, 40, 255 },
                                                            { 85, 100, 255, 255 },
                                                            { 0, 10, 75, 255 },
                                                            { 100, 90, 175, 255 },
                                                            { 50, 50, 75, 255 },
                                                            { 255, 255, 30, 255 } },
                                                          { { 140, 50, 40, 255 },
                                                            { 95, 55, 30, 255 },
                                                            { 55, 90, 225, 255 },
                                                            { 0, 10, 65, 255 },
                                                            { 155, 50, 155, 255 },
                                                            { 20, 40, 20, 255 },
                                                            { 195, 125, 255, 255 } },
                                                          { { 160, 40, 30, 255 },
                                                            { 130, 40, 20, 255 },
                                                            { 40, 80, 185, 255 },
                                                            { 0, 10, 55, 255 },
                                                            { 180, 50, 70, 255 },
                                                            { 40, 50, 20, 255 },
                                                            { 170, 255, 170, 255 } } };
    rgba_t* color = model_color[editor_ovl->anim_frame >> 1];
    Gfx* gfx;
    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 0.0f, MTX_MULT);
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, lat_sousa_mode);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPDisplayList(gfx++, lat_sousa_word_combine);
    gSPDisplayList(gfx++, lat_sousa_sousaT_model);
    gSPDisplayList(gfx++, lat_sousa_2cycle_combine);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
    mED_KeyDraw_A_button(graph);
    mED_KeyDraw_B_button(graph);
    mED_KeyDraw_START_button(graph);
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPDisplayList(gfx++, lat_sousa_other_combine);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
    mED_KeyDraw_Inside_circle(graph, editor_ovl, color);
    mED_KeyDraw_Outside_circle(graph, editor_ovl, color);
    mED_KeyDraw_J_key(graph);
    mED_KeyDraw_XY_button(graph, editor_ovl);
    mED_KeyDraw_Strings(graph, editor_ovl);
    mED_KeyDraw_3D_stick(graph, editor_ovl, color);
}

extern Gfx lat_sousa_spT_model[];

enum {
    mED_RING_COLOR_SELECTED,
    mED_RING_COLOR_BACK,
    mED_RING_COLOR_FRONT,
    mED_RING_COLOR_OUTER,
    mED_RING_COLOR_NUM = mED_RING_COLOR_OUTER + 3
};

static void mED_StringsDraw_RingSingle(GAME* game, u16* str, int color, int ring, f32 x, f32 y, f32 scale) {
    static rgba_t rstr_color[mED_RING_COLOR_NUM] = { { 255, 255, 255, 255 }, { 110, 155, 255, 255 },
                                                     { 105, 205, 225, 255 }, { 215, 120, 215, 255 },
                                                     { 235, 135, 235, 255 }, { 255, 150, 255, 255 } };
    rgba_t* col = &rstr_color[color];
    switch (*str) {
        case CHAR_MESSAGE_TAG:
            break;
        case CHAR_SPACE: {
            GRAPH* graph = game->graph;
            Gfx* gfx;
            OPEN_DISP(graph);
            gfx = NOW_POLY_OPA_DISP;
            Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
            Matrix_translate(x - 160.0f, -(y - 120.0f), 0.0f, MTX_MULT);
            if (ring != FALSE) {
                Matrix_scale(scale, scale, 1.0f, MTX_MULT);
            } else {
                Matrix_scale(scale * 0.75f, scale, 1.0f, MTX_MULT);
            }
            Matrix_translate(7.0f, -9.0f, 0.0f, MTX_MULT);
            gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(gfx++, 0, 255, col->r, col->g, col->b, 255);
            gSPDisplayList(gfx++, lat_sousa_spT_model);
            gSPMatrix(gfx++, &Mtx_clear, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            SET_POLY_OPA_DISP(gfx);
            CLOSE_DISP(graph);
            break;
        }
        default:
            mFont_SetLineStringsW(game, str, 1, x, y, col->r, col->g, col->b, 255, FALSE, FALSE, scale, scale,
                                  mFont_MODE_POLY);
            break;
    }
}

static void mED_StringsDraw_forRingInReturn(GAME* game, f32 x, f32 y) {
    static f32 pos[3][2] = { { 147.5f, 208.0f }, { 161.0f, 213.0f }, { 175.5f, 208.0f } };
    static u8 return_str[3] = { CHAR_PP_091, CHAR_PP_245, CHAR_PP_125 };
    int i;
    f32* point = pos[0];
    u8* str = return_str;
    for (i = 0; i < 3; str++) {
        mFont_SetLineStrings(game, str, 1, point[0] + x, point[1] - y, 225, 135, 225, 255, FALSE, FALSE, 0.875f, 0.875f,
                             mFont_MODE_POLY);
        i++;
        point += 2;
    }
}

static void mED_StringsDraw_forRingIn(mED_Ovl_c* editor_ovl, GAME* game, f32 x, f32 y) {
    static f32 pos[2][10][2] = { { { 131.2f, 181.0f },
                                   { 139.4f, 162.0f },
                                   { 160.2f, 154.2f },
                                   { 180.7f, 161.6f },
                                   { 188.2f, 181.0f },
                                   { 183.5f, 199.0f },
                                   { 174.0f, 207.0f },
                                   { 162.0f, 212.0f },
                                   { 150.5f, 207.0f },
                                   { 140.5f, 199.0f } },
                                 { { 134.5f, 171.0f },
                                   { 148.5f, 157.0f },
                                   { 171.0f, 157.0f },
                                   { 185.5f, 171.0f },
                                   { 188.5f, 193.0f },
                                   { 179.5f, 203.3f },
                                   { 168.6f, 209.5f },
                                   { 155.9f, 209.5f },
                                   { 145.0f, 203.3f },
                                   { 135.5f, 193.0f } } };
    u16 str[10];
    f32* point;
    int i;
    int color;
    f32 scale;
    if (editor_ovl->rotate_timer == 0 || (editor_ovl->rotate_timer > 2 && editor_ovl->rotate_timer <= 4)) {
        point = pos[0][0];
    } else {
        point = pos[1][0];
    }
    for (i = 0; i < 10; i++) {
        str[i] = mED_get_code(editor_ovl, editor_ovl->page_top_num, i, TRUE);
    }
    for (i = 0; i < 10; point += 2) {
        if (point[1] > pos[0][0][1]) {
            color = mED_RING_COLOR_BACK;
            scale = 0.75f;
        } else {
            scale = 1.125f;
            if (i == editor_ovl->stick_area)
                color = mED_RING_COLOR_SELECTED;
            else
                color = mED_RING_COLOR_FRONT;
        }
        mED_StringsDraw_RingSingle(game, &str[i], color, TRUE, GETREG(TAKREG, 40) * 0.1f + (point[0] + x),
                                   GETREG(TAKREG, 41) * 0.1f + (point[1] - y), scale);
        i++;
    }
}

static void mED_StringsDraw_forRingOut(mED_Ovl_c* editor_ovl, GAME* game, f32 x, f32 y) {
    static f32 pos[3][mED_CHARS_PER_PAGE][2] = {
        { { 122.5f, 163.0f }, { 137.5f, 145.5f }, { 162.0f, 139.5f }, { 187.0f, 146.0f }, { 202.0f, 163.0f } },
        { { 121.375f, 169.0f },
          { 135.375f, 148.25f },
          { 160.875f, 139.75f },
          { 187.125f, 148.5f },
          { 200.375f, 169.0f } },
        { { 119.5f, 174.0f }, { 132.5f, 150.0f }, { 159.0f, 139.0f }, { 186.5f, 150.0f }, { 198.0f, 174.0f } }
    };
    static f32 scale_kind[3] = { 0.875f, 1.0f, 1.25f };
    u16 str[mED_CHARS_PER_PAGE];
    u8 stick;
    int consonant;
    int frame;
    int i;
    int base;
    int j;
    f32* point;
    f32 scale;
    int color;
    frame = editor_ovl->anim_frame >> 1;
    consonant = editor_ovl->consonant_num;
    stick = editor_ovl->stick_area;
    point = pos[frame][0];
    scale = scale_kind[frame];
    if (consonant == -1)
        base = stick + editor_ovl->page_top_num;
    else
        base = consonant;
    for (i = 0; i < mED_CHARS_PER_PAGE; i++) {
        str[i] = mED_get_code(editor_ovl, base, i, FALSE);
    }
    for (j = 0; j < mED_CHARS_PER_PAGE; point += 2) {
        if (j == stick && consonant != -1)
            color = mED_RING_COLOR_SELECTED;
        else
            color = frame + mED_RING_COLOR_OUTER;
        mED_StringsDraw_RingSingle(game, &str[j], color, TRUE, point[0] + x, point[1] - y, scale);
        j++;
    }
}

static void mED_StringsDraw_forNormal(Submenu* submenu, GAME* game, f32 x, f32 y) {
    u16 str[1];
    int code = mED_get_now_code(submenu->overlay->editor_ovl);
    if (code != -1) {
        str[0] = code;
        mED_StringsDraw_RingSingle(game, str, mED_RING_COLOR_SELECTED, FALSE, x + 239.0f, 168.0f - y, 1.0f);
    }
}

static void mED_StringsDraw_forOrnament(mED_Ovl_c* editor_ovl, GAME* game, f32 x, f32 y) {
    if (editor_ovl->exchange_code != -1) {
        u16 previous;
        u16 code = editor_ovl->exchange_code;
        f32 text_y = 120.0f - ((y + 8.0f) - 6.0f);
        f32 text_x = 160.0f + (51.0f + x);
        previous = mED_get_str_data(editor_ovl, editor_ovl->cursor_idx - 1);
        mFont_SetLineStringsW(game, &previous, 1, text_x + 8.0f, text_y, 255, 175, 255, 255, FALSE, FALSE, 1.0f, 1.0f,
                              mFont_MODE_POLY);
        mFont_SetLineStringsW(game, &code, 1, text_x + 18.0f + 16.0f, text_y, 255, 255, 255, 255, FALSE, FALSE, 1.0f,
                              1.0f, mFont_MODE_POLY);
    }
}

static int mED_StringsDrawCheck_forRingOut(mED_Ovl_c* editor_ovl) {
    int ret = TRUE;
    if ((editor_ovl->shift_mode != mED_SHIFT_MODE_HIRAGANA && editor_ovl->shift_mode != mED_SHIFT_MODE_KATAKANA) ||
        (editor_ovl->consonant_num == -1 && editor_ovl->stick_area >= mED_CHARS_PER_PAGE)) {
        ret = FALSE;
    }
    return ret;
}

static void mED_StringsDraw(Submenu* submenu, mED_Ovl_c* editor_ovl, GAME* game, f32 x, f32 y) {
    (*submenu->overlay->set_char_matrix_proc)(game->graph);
    if (editor_ovl->consonant_num == -1) {
        mED_StringsDraw_forRingIn(editor_ovl, game, x - 80.0f, y + 22.0f);
    } else {
        mED_StringsDraw_forRingInReturn(game, x - 80.0f, y + 22.0f);
    }
    if (mED_StringsDrawCheck_forRingOut(editor_ovl)) {
        mED_StringsDraw_forRingOut(editor_ovl, game, x - 80.0f, (y + 18.0f) - GETREG(TAKREG, 41) * 0.1f);
    }
    mED_StringsDraw_forNormal(submenu, game, x, y);
    mED_StringsDraw_forOrnament(editor_ovl, game, x + 18.0f, y - 10.0f);
}

static void mED_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    GRAPH* graph = game->graph;

    mED_KeyDraw(editor_ovl, graph, menu_info->position[0], menu_info->position[1]);
    mED_StringsDraw(submenu, editor_ovl, game, menu_info->position[0], menu_info->position[1]);
}

extern Gfx lat_end_cordT_model[];

static void mED_endCode_draw(Submenu* submenu, GAME* game, f32 x, f32 y) {
    GRAPH* graph = game->graph;
    Gfx* gfx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 140.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, lat_end_cordT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mED_cursol_draw(Submenu* submenu, GAME* game, f32 x, f32 y) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    int cursol_opacity_step = editor_ovl->cursol_opacity_step;
    int a;

    if (cursol_opacity_step > 20) {
        cursol_opacity_step = 40 - cursol_opacity_step;
    }

    a = ((20 - cursol_opacity_step) * 255) / 20;
    mFont_SetMarkChar(game, mFont_MARKTYPE_CURSOR, x, y, 195, 80, 80, a, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
}

static void mED_editor_ovl_draw(Submenu* submenu, GAME* game) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];

    (*menu_info->pre_draw_func)(submenu, game);
    mED_set_dl(submenu, menu_info, game);

    if (menu_info->pre_menu_type == mSM_OVL_ADDRESS && submenu->overlay->address_ovl->display_list != NULL) {
        OPEN_DISP(game->graph);

        gSPDisplayList(NOW_POLY_OPA_DISP++, submenu->overlay->address_ovl->display_list);

        CLOSE_DISP(game->graph);
    }
}

extern void mED_editor_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->menu_control.menu_move_func = &mED_editor_ovl_move;
    overlay->menu_control.menu_draw_func = &mED_editor_ovl_draw;
}

static void mED_editor_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];
    (*overlay->move_chg_base_proc)(menu_info, mSM_MOVE_IN_BOTTOM);
    switch (menu_info->data0) {
        case mED_TYPE_CP_TITLE:
        case mED_TYPE_LEDIT:
        case mED_TYPE_HBOARD:
            overlay->editor_ovl->latin_shift_mode = FALSE;
            sAdo_SysTrgStart(0x59);
            break;
        case mED_TYPE_LEDIT_LATIN:
            overlay->editor_ovl->shift_mode = mED_SHIFT_MODE_ALPHABET;
            overlay->editor_ovl->latin_shift_mode = TRUE;
            sAdo_SysTrgStart(0x59);
            break;
        default:
            overlay->editor_ovl->latin_shift_mode = FALSE;
            break;
    }
}

static mED_Ovl_c edit_ovl_data;

extern void mED_editor_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_EDITOR];

    if (overlay->editor_ovl == NULL) {
        mem_clear((u8*)&edit_ovl_data, sizeof(mED_Ovl_c), 0);
        overlay->editor_ovl = &edit_ovl_data;
    }

    mED_init(submenu, menu_info);
    mED_editor_ovl_init(submenu);
    mED_editor_ovl_set_proc(submenu);
    submenu->overlay->editor_ovl->end_code_draw = &mED_endCode_draw;
    submenu->overlay->editor_ovl->cursol_draw = &mED_cursol_draw;
}

extern void mED_editor_ovl_destruct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->editor_ovl = NULL;
}
