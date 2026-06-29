#ifndef M_FILM_OVL_H
#define M_FILM_OVL_H

#include "types.h"
#include "m_submenu.h"

#ifdef __cplusplus
extern "C" {
#endif

struct film_ovl_s {
    /* 0x00 */ u8 strb_block_done;
    /* 0x01 */ u8 strb_line_done;
    /* 0x02 */ u8 _02[0x02];
    /* 0x04 */ int strb_line_count;
    /* 0x08 */ int strb_line_start;
    /* 0x0C */ int strb_char_count[2];
    /* 0x14 */ int strb_char_timer;
    /* 0x18 */ f32 blink_anime;
    /* 0x1C */ int blink_alpha;
    /* 0x20 */ u8 mark_enabled;
    /* 0x21 */ u8 card_busy;
    /* 0x22 */ u8 selb_decided;
    /* 0x23 */ u8 mode;
    /* 0x24 */ int strb_idx;
    /* 0x28 */ int next_strb_idx;
    /* 0x2C */ f32 strb_scale;
    /* 0x30 */ int strb_step;
    /* 0x34 */ int next_strb_step;
    /* 0x38 */ int drive_a;
    /* 0x3C */ int drive_b;
    /* 0x40 */ int drive_c;
    /* 0x44 */ int selb_idx;
    /* 0x48 */ f32 selb_scale;
    /* 0x4C */ int selb_step;
    /* 0x50 */ int selb_param;
    /* 0x54 */ int selb_cursor;
    /* 0x58 */ f32 selb_item_x;
    /* 0x5C */ f32 selb_item_y;
    /* 0x60 */ f32 selb_width;
    /* 0x64 */ f32 selb_height;
    /* 0x68 */ f32 selb_mark_x;
    /* 0x6C */ f32 selb_mark_y;
    /* 0x70 */ int card_count;
    /* 0x74 */ int card_status;
    /* 0x78 */ int card_result;
    /* 0x7C */ void* sdcard_buf;
    /* 0x80 */ void* prbuf;
}; /* sizeof == 0x84 */

extern void mFL_film_ovl_construct(Submenu* submenu);
extern void mFL_film_ovl_destruct(Submenu* submenu);
extern void mFL_film_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif
#endif // M_FILM_OVL_H
