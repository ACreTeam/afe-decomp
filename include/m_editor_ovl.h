#ifndef M_EDITOR_OVL_H
#define M_EDITOR_OVL_H

#include "types.h"
#include "m_editor_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mED_COLUMNS 10
#define mED_ROWS 4

#define mED_NG_WORD_START 0x74A
#define mED_NG_WORD_NUM 14

enum {
    mED_TYPE_BOARD,
    mED_TYPE_HBOARD,
    mED_TYPE_NOTICE,
    mED_TYPE_LEDIT,
    mED_TYPE_CP_TITLE,
    mED_TYPE_DIARY,
    mED_TYPE_PASSWORDMAKE,
    mED_TYPE_PASSWORDCHK,
    mED_TYPE_LEDIT_LATIN,

    mED_TYPE_NUM
};

enum {
    mED_STICK_AREA_LEFT,
    mED_STICK_AREA_TOP_LEFT,
    mED_STICK_AREA_TOP,
    mED_STICK_AREA_TOP_RIGHT,
    mED_STICK_AREA_RIGHT,
    mED_STICK_AREA_BOTTOM_RIGHT,
    mED_STICK_AREA_BOTTOM,
    mED_STICK_AREA_BOTTOM_LEFT,
    mED_STICK_AREA_CENTER,

    mED_STICK_AREA_NUM
};

enum {
    mED_COMMAND_NONE,
    mED_COMMAND_CURSOL_RIGHT,
    mED_COMMAND_CURSOL_LEFT,
    mED_COMMAND_CURSOL_UPPER,
    mED_COMMAND_CURSOL_LOWER,
    mED_COMMAND_END_EDIT,
    mED_COMMAND_BACKSPACE,
    mED_COMMAND_EXCHANGE_CODE,
    mED_COMMAND_OUTPUT_CODE,
    mED_COMMAND_9,

    mED_COMMAND_NUM
};

enum {
    mED_SHIFT_LOWER,
    mED_SHIFT_UPPER,

    mED_SHIFT_NUM
};

enum {
    mED_ARRANGE_QWERTY,
    mED_ARRANGE_ALPHA,

    mED_ARRANGE_NUM
};

enum {
    mED_INPUT_MODE_LETTER,
    mED_INPUT_MODE_SIGN,
    mED_INPUT_MODE_MARK,

    mED_INPUT_MODE_NUM
};

enum {
    mED_LINETYPE_SINGLE,
    mED_LINETYPE_MULTI,
    mED_LINETYPE_PW,

    mED_LINETYPE_NUM
};

enum {
    mED_LINE_OK,
    mED_LINE_NEWLINE,
    mED_LINE_WIDTH_OVER,
    mED_LINE_NUM_OVER,

    mED_LINE_NUM
};

enum {
    mED_SHIFT_MODE_HIRAGANA,
    mED_SHIFT_MODE_KIGOU,
    mED_SHIFT_MODE_KATAKANA,
    mED_SHIFT_MODE_ALPHABET,
    mED_SHIFT_MODE_NUMBER,
    mED_SHIFT_MODE_EMOJI,

    mED_SHIFT_MODE_NUM
};

typedef void (*mED_ENDCODE_DRAW_PROC)(Submenu*, GAME*, f32, f32);
typedef void (*mED_CURSOL_DRAW_PROC)(Submenu*, GAME*, f32, f32);

struct editor_ovl_s {
    /* 0x00 */ u8 stick_area;
    /* 0x01 */ u8 last_stick_area;
    /* 0x02 */ u8 stick_area_changed;
    /* 0x03 */ u8 rotate_timer;
    /* 0x04 */ u8 shift_mode;
    /* 0x05 */ u8 page_top_num;
    /* 0x06 */ s16 consonant_num;
    /* 0x08 */ u32 last_buttons;
    /* 0x0C */ s16 cursol_opacity_step;
    /* 0x0E */ u8 button_repeat_started;
    /* 0x0F */ u8 button_repeat_accel_timer;
    /* 0x10 */ u8 button_repeat_timer;
    /* 0x11 */ u8 command;
    /* 0x12 */ u16 now_code;
    /* 0x14 */ u8 anim_frame;
    /* 0x15 */ u8 se_flag;
    /* 0x16 */ s16 cursor_idx;
    /* 0x18 */ s16 input_length;
    /* 0x1A */ s16 max_line_no;
    /* 0x1C */ s16 line_width;
    /* 0x1E */ s16 now_str_len;
    /* 0x20 */ s16 exchange_code;
    /* 0x22 */ s16 cursor_col;
    /* 0x24 */ s16 cursor_row;
    /* 0x26 */ s16 cursor_line_width;
    /* 0x28 */ u8* input_str;
    /* 0x2C */ u16* input_wstr; // wide string
    /* 0x30 */ mED_ENDCODE_DRAW_PROC end_code_draw;
    /* 0x34 */ mED_CURSOL_DRAW_PROC cursol_draw;
    /* 0x38 */ u8 button_repeat_speed;
    /* 0x39 */ u8 is_wide_string;
    /* 0x3A */ u8 latin_shift_mode;
};

extern void mED_editor_ovl_set_proc(Submenu* submenu);
extern void mED_editor_ovl_construct(Submenu* submenu);
extern void mED_editor_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
