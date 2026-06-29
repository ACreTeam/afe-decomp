#include "m_film_ovl.h"

#include "m_submenu_ovl.h"
#include "m_common_data.h"
#include "m_play.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_lib.h"
#include "audio.h"
#include "sys_matrix.h"
#include "m_sdcard.h"
#include "m_choice.h"
#include "m_card.h"
#include "dolphin/os.h"

// TODO: This file needs enum cleanup.

extern void texture_cache_data_and_bss_clear();
extern u8* JW_Get_SDCardBuffer_p(void);
extern int mCD_SaveTiff_sdcard_bg(void);
extern int mSD_sdcard_format(void);
extern int mSD_sdcard_tiff_read(void* buf, int size, int picno);
extern int mSD_tiff_picno_remove(int picno);
extern int mSD_TiffToRGB565(void* src, void* dst);
extern void* mSD_Get_tex_p_inResTIMG(void* p);
extern int mCsd_nowdrive_get(void);
extern Gfx win_syasin_mode[];
extern Gfx win_syasin_model[];
extern Gfx win_syasin_base_model[];
extern Gfx win_syasin_base_error_model[];
extern Gfx win_syasin_kumoT_model[];

typedef struct {
    u8* text;
    int length;
} mFL_Line_c;

typedef struct {
    mFL_Line_c* lines;
    int line_count;
    int next_type;
    int next0;
    int next1;
    int next2;
    int next3;
} mFL_StrbString_c;

typedef struct {
    mFL_Line_c* lines;
    int line_count;
} mFL_SelbString_c;

#include "../src/game/m_film_ovl_data.c_inc"

typedef void (*mFL_proc1)(mFL_Ovl_c*);
typedef int (*mFL_proc2)(Submenu*, mFL_Ovl_c*);
typedef void (*mFL_proc3)(Submenu*, mFL_Ovl_c*);

static void mFL_selb_setupStep(mFL_Ovl_c* film_ovl, int step);
static void mFL_strb_setupStep(mFL_Ovl_c* film_ovl, int step);

static mFL_Ovl_c fl_ovl_data;

static int mFL_scale_calc(f32* scale_p, f32 delta) {
    int res = FALSE;

    *scale_p += delta;
    if (*scale_p > 1.0f) {
        *scale_p = 1.0f;
        res = TRUE;
    } else if (*scale_p < 0.0f) {
        *scale_p = 0.0f;
        res = TRUE;
    }

    return res;
}

static void mFL_setup_strb_strings(mFL_Ovl_c* film_ovl, int idx, int start_line) {
    mFL_StrbString_c* str_data = &fl_strb_str_data[idx];
    mFL_Line_c* line;
    int line_count;
    int render_line_count;
    int i;

    film_ovl->strb_idx = idx;
    film_ovl->strb_line_start = start_line;
    for (i = 0; i < 2; i++) {
        film_ovl->strb_char_count[i] = 0;
    }

    film_ovl->strb_char_timer = 23;
    film_ovl->strb_line_done = FALSE;
    film_ovl->strb_block_done = FALSE;

    line_count = str_data->line_count - start_line;
    if (line_count > 2) {
        line_count = 2;
    }

    render_line_count = line_count;
    for (i = 0; i < render_line_count; i++) {
        line = &str_data->lines[start_line] + i;
        if (line->text == NULL) {
            line_count--;
        }
    }

    film_ovl->strb_line_count = line_count;
    film_ovl->blink_anime = 0.0f;
    film_ovl->blink_alpha = 0;
    film_ovl->mark_enabled = FALSE;
}

static void mFL_strb_chk_block_disp(mFL_Ovl_c* film_ovl, mFL_StrbString_c* str_data, mFL_Line_c* line, int line_count) {
    if (film_ovl->strb_char_count[line_count - 1] >= line[line_count - 1].length) {
        film_ovl->strb_line_done = TRUE;
        film_ovl->mark_enabled = TRUE;

        if (film_ovl->strb_line_start + line_count >= str_data->line_count) {
            film_ovl->strb_block_done = TRUE;
        }
    }
}

static void mFL_strb_string_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mFL_Ovl_c* film_ovl = overlay->film_ovl;
    int idx = film_ovl->strb_idx;

    if (idx != -1 && film_ovl->strb_scale >= 1.0f) {
        u32 trigger = overlay->menu_control.trigger;
        mFL_StrbString_c* str_data = &fl_strb_str_data[idx];

        if (film_ovl->strb_line_done == TRUE) {
            if (film_ovl->strb_block_done == FALSE && (trigger & (BUTTON_START | BUTTON_B | BUTTON_A)) != 0) {
                sAdo_SysTrgStart(0xB);
                mFL_setup_strb_strings(film_ovl, film_ovl->strb_idx, film_ovl->strb_line_start + 2);
            }
        } else {
            int start_line_idx = film_ovl->strb_line_start;
            mFL_Line_c* start_line = &str_data->lines[start_line_idx];
            int line_count = film_ovl->strb_line_count;
            int wait = film_ovl->strb_char_timer;
            int i;

            wait--;
            if (wait <= 0) {
                // @BUG: multiple issues here.
                //       - devs should use start_line[i].text, and this reads the *next* character
                //       - devs should use strb_line_count instead of a constant '2'
#ifndef BUGFIXES
                for (i = 0; i < 2; i++) {
                    if (film_ovl->strb_char_count[i] < start_line[i].length) {
                        // @BUG: devs should use start_line[i].text, and this reads the *next* character
                        film_ovl->strb_char_count[i]++;
                        sAdo_VoiceSe(mMsg_sound_voice_get(start_line->text[film_ovl->strb_char_count[i]]), 0, 32);
                        break;
                    }
                }
#else
                for (i = 0; i < film_ovl->strb_line_count; i++) {
                    if (film_ovl->strb_char_count[i] < start_line[i].length) {
                        sAdo_VoiceSe(mMsg_sound_voice_get(start_line[i].text[film_ovl->strb_char_count[i]]), 0, 32);
                        film_ovl->strb_char_count[i]++;
                        break;
                    }
                }
#endif

                wait = 2;
            }

            film_ovl->strb_char_timer = wait;

            if ((trigger & BUTTON_B) != 0) {
                for (i = 0; i < line_count; i++) {
                    if (film_ovl->strb_char_count[i] < start_line[i].length) {
                        film_ovl->strb_char_count[i] = start_line[i].length;
                    }
                }
            }

            mFL_strb_chk_block_disp(film_ovl, str_data, start_line, line_count);
        }
    }
}

static void mFL_blink_mark_next(mFL_Ovl_c* film_ovl) {
    f32 t;

    film_ovl->blink_anime += 1.0f;
    if (film_ovl->blink_anime >= 60.0f) {
        film_ovl->blink_anime = 0.0f;
    }

    t = (film_ovl->blink_anime - 30.0f) / 30.0f;
    if (t <= 0.0f) {
        t = 1.0f + t;
    } else {
        t = 1.0f - t;
    }

    if (t < 0.0f) {
        t = 0.0f;
    } else if (t > 1.0f) {
        t = 1.0f;
    }

    film_ovl->blink_alpha = (int)(255.0f * t);
}

static void mFL_setup_selb_strings(mFL_Ovl_c* film_ovl, int idx) {
    mFL_SelbString_c* str_data;
    mFL_Line_c* line;
    int max_len;
    int line_count;
    int i;
    f32 width;
    f32 height;

    film_ovl->selb_idx = idx;
    str_data = &fl_selb_str_data[idx];
    line = str_data->lines;
    line_count = str_data->line_count;
    max_len = -1;

    for (i = 0; i < line_count; i++) {
        if (line->length > max_len) {
            max_len = line->length;
        }

        line++;
    }

    width = (max_len * 12 - 24) / 96.0f;
    height = (line_count * 16 - 32) / 32.0f;

    film_ovl->selb_width = 0.41666666f + 0.5833334f * width;
    film_ovl->selb_height = 0.6857143f + 0.3142857f * height;
    film_ovl->selb_item_x = -35.0f * width;
    film_ovl->selb_item_y = 20.057142f * height;
    film_ovl->selb_mark_x = -10.0f + -48.0f * width;
    film_ovl->selb_mark_y = -20.057142f * height;
}

static int mFL_save_card(mFL_Ovl_c* film_ovl) {
    int status = film_ovl->card_status;

    if (status == 0x26) {
        if (film_ovl->card_result == 0x26) {
            film_ovl->card_result = mCD_SaveTiff_sdcard_bg();
        }
        film_ovl->card_count -= 1;
        if (film_ovl->card_count > 0) {
            status = 0x26;
        } else {
            status = film_ovl->card_result;
        }
        film_ovl->card_status = status;
    }

    return status;
}

static int mFL_initialize_card(mFL_Ovl_c* film_ovl) {
    int status = film_ovl->card_status;

    if (status == 0x26) {
        film_ovl->card_count -= 1;
        if (film_ovl->card_count <= 0) {
            status = mSD_sdcard_format();
        }
    }

    film_ovl->card_status = status;
    return status;
}

static int mFL_read_film(Submenu* submenu, mSM_MenuInfo_c* menu) {
    mFL_Ovl_c* film_ovl = submenu->overlay->film_ovl;
    int status = film_ovl->card_status;

    if (status == 0x26) {
        if (film_ovl->sdcard_buf == NULL) {
            status = 0x29;
        } else {
            status = mSD_sdcard_tiff_read(film_ovl->sdcard_buf, 0xE3D00, menu->data1);
        }
        film_ovl->card_status = status;
    }

    return status;
}

static int mFL_erase_film(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    int status = film_ovl->card_status;

    if (status == 0x26) {
        Submenu_Overlay_c* overlay = submenu->overlay;

        if (film_ovl->card_result == 0x26) {
            film_ovl->card_result = mSD_tiff_picno_remove(overlay->menu_info[mSM_OVL_FILM].data1);
        }
        film_ovl->card_count -= 1;
        if (film_ovl->card_count > 0) {
            status = 0x26;
        } else {
            status = film_ovl->card_result;
        }
        film_ovl->card_status = status;
    }

    return status;
}

static void mFL_setup_card_proc_before(mFL_Ovl_c* film_ovl) {
    film_ovl->card_status = 0x26;
    film_ovl->card_result = 0x26;
    film_ovl->card_busy = TRUE;
    film_ovl->card_count = 0x70;
    sAdo_SysLevStart(0x47);
}

static void mFL_setup_card_proc_after(mFL_Ovl_c* film_ovl) {
    film_ovl->card_busy = FALSE;
    sAdo_SysLevStop(0x47);
}

static void mFL_selb_open(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    if (mFL_scale_calc(&film_ovl->selb_scale, 0.09803922f) == TRUE) {
        mFL_selb_setupStep(film_ovl, 2);
    }
}

static void mFL_selb_select(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    u32 trigger;
    mFL_SelbString_c* str_data;
    int count;

    trigger = submenu->overlay->menu_control.trigger;
    str_data = &fl_selb_str_data[film_ovl->selb_idx];
    count = str_data->line_count;
    
    if ((trigger & BUTTON_A) != 0) {
        u16 se_no = 2;

        switch (film_ovl->selb_idx) {
        case 0:
            if (film_ovl->selb_cursor == 0) {
                se_no = 2;
            } else {
                se_no = 0x8005;
            }
            break;
        case 1:
            if (film_ovl->selb_cursor == 0) {
                se_no = 0x8005;
            } else {
                se_no = 2;
            }
            break;
        case 2:
            if (film_ovl->selb_cursor == 0) {
                se_no = 0x33;
            } else {
                se_no = 0x8005;
            }
            break;
        case 3:
            if (film_ovl->selb_cursor == 0) {
                se_no = 0x435;
            } else if (film_ovl->selb_cursor == 1) {
                se_no = 0x33;
            } else {
                se_no = 0x8005;
            }
            break;
        }

        sAdo_SysTrgStart(se_no);
        mFL_selb_setupStep(film_ovl, 3);
    } else if ((trigger & BUTTON_B) != 0) {
        if (film_ovl->selb_idx != 1) {
            sAdo_SysTrgStart(0x8005);
            film_ovl->selb_cursor = count - 1;
            film_ovl->selb_decided = TRUE;
            mFL_selb_setupStep(film_ovl, 3);
        }
    } else if ((trigger & BUTTON_CUP) != 0) {
        film_ovl->selb_cursor--;
        if (film_ovl->selb_cursor < 0) {
            film_ovl->selb_cursor = 0;
        } else {
            sAdo_SysTrgStart(1);
        }
    } else if ((trigger & BUTTON_CDOWN) != 0) {
        film_ovl->selb_cursor++;
        if (film_ovl->selb_cursor >= count) {
            film_ovl->selb_cursor = count - 1;
        } else {
            sAdo_SysTrgStart(1);
        }
    }
}

static void mFL_selb_close(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    if (mFL_scale_calc(&film_ovl->selb_scale, -0.09803922f) == 1) {
        film_ovl->selb_step = 0;
    }
}

static void mFL_selb_close_wait_init(mFL_Ovl_c* film_ovl) {
    film_ovl->mark_enabled = TRUE;
}

static void mFL_selb_open_init(mFL_Ovl_c* film_ovl) {
    film_ovl->mark_enabled = FALSE;
    film_ovl->selb_cursor = 0;
    mFL_setup_selb_strings(film_ovl, film_ovl->selb_param);
    sAdo_SysTrgStart(0xC);
}

static void mFL_selb_select_init(mFL_Ovl_c* film_ovl) {
    film_ovl->selb_cursor = 0;
}

static void mFL_selb_setupStep(mFL_Ovl_c* film_ovl, int step) {
    static mFL_proc1 selb_init_proc[4] = {
        &mFL_selb_close_wait_init,
        &mFL_selb_open_init,
        &mFL_selb_select_init,
        (mFL_proc1)&none_proc1,
    };

    film_ovl->selb_step = step;
    (*selb_init_proc[step])(film_ovl);
}

static void mFL_selb_proc(Submenu* submenu) {
    static mFL_proc3 selb_proc[4] = {
        (mFL_proc3)&none_proc1,
        &mFL_selb_open,
        &mFL_selb_select,
        &mFL_selb_close,
    };

    mFL_Ovl_c* film_ovl = submenu->overlay->film_ovl;

    (*selb_proc[film_ovl->selb_step])(submenu, film_ovl);

    if (film_ovl->selb_decided == 1) {
        submenu->overlay->menu_control.trigger &= ~0x4000;
        film_ovl->selb_decided = 0;
    }
}

static int mFL_strb_open(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    if (mFL_scale_calc(&film_ovl->strb_scale, 0.055555556f) == 1) {
        if (film_ovl->next_strb_idx != -1) {
            mFL_setup_strb_strings(film_ovl, film_ovl->next_strb_idx, 0);
        }
        mFL_strb_setupStep(film_ovl, film_ovl->next_strb_step);
    }

    return 1;
}

static int mFL_strb_chk_card_exist(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    int idx;
    switch (mCsd_exitence_chk()) {
    case mCD_RESULT_SUCCESS:
        idx = 0;
        break;
    default:
        idx = 0xB;
        break;
    }

    mFL_setup_strb_strings(film_ovl, idx, 0);
    mFL_strb_setupStep(film_ovl, 3);

    return 1;
}

static int mFL_strb_str_line_end_wait(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    if (film_ovl->strb_block_done == TRUE) {
        mFL_StrbString_c* str_data = &fl_strb_str_data[film_ovl->strb_idx];

        if (str_data->next_type == 0) {
            mFL_strb_setupStep(film_ovl, str_data->next0);
        } else if ((submenu->overlay->menu_control.trigger & (BUTTON_START | BUTTON_B | BUTTON_A)) != 0) {
            int play_se = FALSE;

            switch (str_data->next_type) {
            case 1:
                film_ovl->selb_param = str_data->next0;
                mFL_selb_setupStep(film_ovl, 1);
                mFL_strb_setupStep(film_ovl, 4);
                break;
            case 2:
                film_ovl->selb_param = str_data->next0;
                mFL_selb_setupStep(film_ovl, 1);
                mFL_strb_setupStep(film_ovl, 5);
                break;
            case 3:
                film_ovl->selb_param = str_data->next0;
                mFL_selb_setupStep(film_ovl, 1);
                mFL_strb_setupStep(film_ovl, 6);
                break;
            case 4:
                if (film_ovl->drive_a == 0) {
                    mFL_setup_strb_strings(film_ovl, str_data->next0, 0);
                } else {
                    mFL_setup_strb_strings(film_ovl, str_data->next1, 0);
                }
                play_se = TRUE;
                break;
            case 5:
                if (film_ovl->drive_b == 0) {
                    mFL_setup_strb_strings(film_ovl, str_data->next0, 0);
                } else {
                    mFL_setup_strb_strings(film_ovl, str_data->next1, 0);
                }
                play_se = TRUE;
                break;
            case 6:
                if (film_ovl->drive_c == 0) {
                    mFL_setup_strb_strings(film_ovl, str_data->next0, 0);
                } else {
                    mFL_setup_strb_strings(film_ovl, str_data->next1, 0);
                }
                play_se = TRUE;
                break;
            case 7:
                mFL_strb_setupStep(film_ovl, 11);
                break;
            case 8:
                mFL_setup_strb_strings(film_ovl, str_data->next0, 0);
                play_se = TRUE;
                break;
            }

            if (play_se == TRUE) {
                sAdo_SysTrgStart(0xB);
            }
        }
    }

    return TRUE;
}

static int mFL_strb_select_wait(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    if (film_ovl->selb_step == 3) {
        mFL_StrbString_c* str_data = &fl_strb_str_data[film_ovl->strb_idx];
        int step = 10;
        int idx;

        switch (film_ovl->selb_cursor) {
        case 0:
            idx = str_data->next1;
            break;
        default:
            idx = str_data->next2;
            break;
        }

        if (idx != -1) {
            step = 3;
            mFL_setup_strb_strings(film_ovl, idx, 0);
        }

        mFL_strb_setupStep(film_ovl, step);
    }

    return TRUE;
}

static int mFL_strb_select_preview_wait(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    if (film_ovl->selb_step == 3) {
        switch (film_ovl->selb_cursor) {
        case 0:
            submenu->param3 = 1;
            break;
        default:
            submenu->param3 = 0;
            break;
        }
        mFL_strb_setupStep(film_ovl, 10);
    }

    return TRUE;
}

static int mFL_strb_select_erase_wait(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    if (film_ovl->selb_step == 3) {
        mFL_StrbString_c* str_data = &fl_strb_str_data[film_ovl->strb_idx];
        int step = 10;

        switch (film_ovl->selb_cursor) {
        case 0:
            submenu->param3 = 1;
            step = 3;
            mFL_setup_strb_strings(film_ovl, str_data->next1, 0);
            break;
        case 1:
            submenu->param3 = 1;
            break;
        default:
            submenu->param3 = 0;
            break;
        }

        mFL_strb_setupStep(film_ovl, step);
    }

    return TRUE;
}

static int mFL_strb_save_end_wait(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    int status = mFL_save_card(film_ovl);

    if (status != 0x26) {
        mFL_setup_card_proc_after(film_ovl);
        if ((submenu->overlay->menu_control.trigger & (BUTTON_START | BUTTON_B | BUTTON_A)) != 0) {
            int idx = 10;
            int drive = mCsd_nowdrive_get();

            film_ovl->drive_a = drive;
            film_ovl->drive_b = 0;

            switch (status) {
            case 0:
                idx = 2;
                break;
            case 0x22:
                idx = 3;
                break;
            case 0x25:
                if (drive == 0) {
                    idx = 0x15;
                } else {
                    idx = 0x16;
                }
                break;
            case 0x32:
                if (drive == 0) {
                    idx = 0x17;
                } else {
                    idx = 0x18;
                }
                break;
            case 0x24:
                if (drive == 0) {
                    idx = 0x10;
                } else {
                    idx = 0x11;
                }
                break;
            case 0x30:
                idx = drive == 0 ? 0x1A : 0x1B;
                film_ovl->drive_a = 0;
                break;
            case 0x28:
                idx = drive == 0 ? 0x1A : 0x1B;
                film_ovl->drive_a = 1;
                break;
            case 0x29:
            case 0x2E:
                if (drive == 0) {
                    idx = 0x1C;
                } else {
                    idx = 0x1D;
                }   
                break;
            case 0x23:
                if (drive == 0) {
                    idx = 0xE;
                } else {
                    idx = 0xF;
                }
                break;
            case 0x33:
                idx = 0x23;
                break;
            }

            sAdo_SysTrgStart(0xB);
            mFL_setup_strb_strings(film_ovl, idx, 0);
            mFL_strb_setupStep(film_ovl, 3);
        }
    }

    return TRUE;
}

static int mFL_strb_initialize_end_wait(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    int status = mFL_initialize_card(film_ovl);

    if (status != 0x26) {
        if ((submenu->overlay->menu_control.trigger & (BUTTON_START | BUTTON_B | BUTTON_A)) != 0) {
            int idx = 0x12;
            int drive = mCsd_nowdrive_get();

            film_ovl->drive_a = drive;
            film_ovl->drive_b = 1;

            switch (status) {
            case 0x21:
                idx = 7;
                break;
            case 0x22:
                idx = 3;
                break;
            case 0x25:
                if (drive == 0) {
                    idx = 0x15;
                } else {
                    idx = 0x16;
                }
                break;
            case 0x32:
                if (drive == 0) {
                    idx = 0x17;
                } else {
                    idx = 0x18;
                }
                break;
            case 0x29:
            case 0x2E:
                idx = 0x12;
                break;
            }

            sAdo_SysTrgStart(0xB);
            mFL_setup_strb_strings(film_ovl, idx, 0);
            mFL_strb_setupStep(film_ovl, 3);
        }

        mFL_setup_card_proc_after(film_ovl);
    }

    return TRUE;
}

static int mFL_strb_erase_end_wait(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    int status = mFL_erase_film(submenu, film_ovl);

    if (status != 0x26) {
        mFL_setup_card_proc_after(film_ovl);
        if ((submenu->overlay->menu_control.trigger & (BUTTON_START | BUTTON_B | BUTTON_A)) != 0) {
            int drive = mCsd_nowdrive_get();
            int idx;

            switch (status) {
            case 0:
                submenu->param3 = 2;
                idx = 0x2B;
                break;
            case 0x22:
                idx = 0x2C;
                break;
            case 0x25:
                if (drive == 0) {
                    idx = 0x15;
                } else {
                    idx = 0x16;
                }
                break;
            case 0x32:
                if (drive == 0) {
                    idx = 0x17;
                } else {
                    idx = 0x18;
                }
                break;
            default:
                if (drive == 0) {
                    idx = 0x1C;
                } else {
                    idx = 0x1D;
                }
                break;
            }

            sAdo_SysTrgStart(0xB);
            mFL_setup_strb_strings(film_ovl, idx, 0);
            mFL_strb_setupStep(film_ovl, 3);
        }
    }

    return TRUE;
}

static int mFL_strb_close_se_off(Submenu* submenu, mFL_Ovl_c* film_ovl) {
    int ret = TRUE;

    if (mFL_scale_calc(&film_ovl->strb_scale, -0.055555556f) == 1) {
        ret = FALSE;
        film_ovl->strb_step = 0;
    }

    return ret;
}

static void mFL_strb_open_init(mFL_Ovl_c* film_ovl) {
    sAdo_SysTrgStart(0x8004);
}

static void mFL_strb_save_end_wait_init(mFL_Ovl_c* film_ovl) {
    mFL_setup_card_proc_before(film_ovl);
}

static void mFL_strb_initialize_end_wait_init(mFL_Ovl_c* film_ovl) {
    mFL_setup_card_proc_before(film_ovl);
}

static void mFL_strb_erase_end_wait_init(mFL_Ovl_c* film_ovl) {
    mFL_setup_card_proc_before(film_ovl);
}

static void mFL_strb_close_se_off_init(mFL_Ovl_c* film_ovl) {
    int i;

    film_ovl->mark_enabled = FALSE;
    for (i = 0; i < 2; i++) {
        film_ovl->strb_char_count[i] = 0;
    }
}

static void mFL_strb_close_init(mFL_Ovl_c* film_ovl) {
    mFL_strb_close_se_off_init(film_ovl);
    sAdo_SysTrgStart(0x8005);
}

static void mFL_strb_setupStep(mFL_Ovl_c* film_ovl, int step) {
    static mFL_proc1 strb_init_proc[12] = {
        (mFL_proc1)&none_proc1,
        &mFL_strb_open_init,
        (mFL_proc1)&none_proc1,
        (mFL_proc1)&none_proc1,
        (mFL_proc1)&none_proc1,
        (mFL_proc1)&none_proc1,
        (mFL_proc1)&none_proc1,
        &mFL_strb_save_end_wait_init,
        &mFL_strb_initialize_end_wait_init,
        &mFL_strb_erase_end_wait_init,
        &mFL_strb_close_se_off_init,
        &mFL_strb_close_init,
    };

    film_ovl->strb_step = step;
    (*strb_init_proc[step])(film_ovl);
}

static int mFL_strb_proc(Submenu* submenu) {
    static mFL_proc2 strb_proc[12] = {
        (mFL_proc2)&none_proc1,
        &mFL_strb_open,
        &mFL_strb_chk_card_exist,
        &mFL_strb_str_line_end_wait,
        &mFL_strb_select_wait,
        &mFL_strb_select_preview_wait,
        &mFL_strb_select_erase_wait,
        &mFL_strb_save_end_wait,
        &mFL_strb_initialize_end_wait,
        &mFL_strb_erase_end_wait,
        &mFL_strb_close_se_off,
        &mFL_strb_close_se_off,
    };

    mFL_Ovl_c* film_ovl = submenu->overlay->film_ovl;
    int ret = (*strb_proc[film_ovl->strb_step])(submenu, film_ovl);

    mFL_strb_string_proc(submenu);

    if (film_ovl->strb_line_done == 1) {
        mFL_blink_mark_next(film_ovl);
    }

    return ret;
}

static void mFL_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu) {
    (*submenu->overlay->move_Move_proc)(submenu, menu);
}

static void mFL_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu) {
    mFL_selb_proc(submenu);
    if (mFL_strb_proc(submenu) == 0) {
        (*submenu->overlay->move_chg_base_proc)(menu, mSM_MOVE_OUT_RIGHT);
    }
}

static void mFL_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu) {
    int status = mFL_read_film(submenu, menu);

    if (status != 0x26) {
        mFL_Ovl_c* film_ovl = submenu->overlay->film_ovl;

        switch (status) {
        case 0:
            film_ovl->prbuf = (void*)ALIGN_NEXT((u32)film_ovl->sdcard_buf + 0xE3D00, 32);
            if (mSD_TiffToRGB565(film_ovl->sdcard_buf, film_ovl->prbuf) == 0) {
                film_ovl->next_strb_idx = 0x26;
            } else {
                film_ovl->prbuf = mSD_Get_tex_p_inResTIMG(film_ovl->prbuf);
                DCStoreRange(film_ovl->prbuf, 0x96020);
                texture_cache_data_and_bss_clear();
#ifdef BUGFIXES
                if (film_ovl->mode == 1) {
                    film_ovl->next_strb_idx = 0x29;
                } else {
                    film_ovl->next_strb_idx = 0x27;
                }
#endif
            }

            // @BUG: devs overwrite 'next_strb_idx' here, and should use the value set above when
            // the TiffToRGB565 route fails.
#ifndef BUGFIXES
            if (film_ovl->mode == 1) {
                film_ovl->next_strb_idx = 0x29;
            } else {
                film_ovl->next_strb_idx = 0x27;
            }
#endif
            break;

        case 0x2B:
            film_ovl->next_strb_idx = 0x26;
            break;

        default:
            if (film_ovl->mode == 1) {
                film_ovl->next_strb_idx = 0x2E;
            } else {
                film_ovl->next_strb_idx = 0x28;
            }
            break;
        }

        mFL_strb_setupStep(film_ovl, 1);
        (*submenu->overlay->move_chg_base_proc)(menu, mSM_MOVE_IN_RIGHT);
    }
}

static void mFL_move_End(Submenu* submenu, mSM_MenuInfo_c* menu) {
    (*submenu->overlay->move_End_proc)(submenu, menu);
}

static void mFL_film_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[5] = {
        &mFL_move_Move, &mFL_move_Play, &mFL_move_Wait, (mSM_MOVE_PROC)&none_proc1, &mFL_move_End,
    };

    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu = &overlay->menu_info[mSM_OVL_FILM];

    (*menu->pre_move_func)(submenu);
    (*ovl_move_proc[menu->proc_status])(submenu, menu);
}

static void mFL_set_film_frame_dl(mFL_Ovl_c* film_ovl, GRAPH* graph, f32 pos_x, f32 pos_y) {
    void* prbuf = film_ovl->prbuf;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, win_syasin_mode);
    gSPDisplayList(POLY_OPA_DISP++, win_syasin_model);

    if (prbuf != NULL) {
        gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, prbuf);
        gSPDisplayList(POLY_OPA_DISP++, win_syasin_base_model);
    } else {
        gSPDisplayList(POLY_OPA_DISP++, win_syasin_base_error_model);
    }

    CLOSE_POLY_OPA_DISP(graph);
}

static void mFL_set_strb_frame_dl(mFL_Ovl_c* film_ovl, GRAPH* graph, f32 pos_x, f32 pos_y) {
    float scale = film_ovl->strb_scale;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y + -77.0f, 140.0f, MTX_MULT);
    Matrix_scale(scale, scale, 1.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, win_syasin_mode);
    gSPDisplayList(POLY_OPA_DISP++, win_syasin_kumoT_model);

    CLOSE_POLY_OPA_DISP(graph);
}

static void mFL_set_strb_strings(Submenu* submenu, GAME* game, f32 pos_x, f32 pos_y) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mFL_Ovl_c* film_ovl = overlay->film_ovl;
    GRAPH* graph = game->graph;

    if (film_ovl->strb_idx != -1) {
        mFL_StrbString_c* str_data;
        mFL_Line_c* line;
        float x;
        float y;
        float scale;
        int i;

        scale = film_ovl->strb_scale;
        submenu->overlay->set_char_matrix_proc(graph);
        str_data = &fl_strb_str_data[film_ovl->strb_idx];
        line = &str_data->lines[film_ovl->strb_line_start];
        x = (160.0f + pos_x) + (-96.0f * scale);
        y = (193.0f - pos_y) + (-16.0f * scale);

        // @BUG: devs should've used strb_line_count instead of a constant '2'
#ifndef BUGFIXES
        for (i = 0; i < 2; i++) {
            if (line->text != NULL && film_ovl->strb_char_count[i] > 0) {
                mFont_SetLineStrings(game, line->text, film_ovl->strb_char_count[i], x, y, 255, 255, 255, 255, FALSE,
                                     TRUE, scale, scale, 0);
            }
            y += 16.0f * scale;
            line++;
        }
#else
        for (i = 0; i < film_ovl->strb_line_count; i++) {
            if (line->text != NULL && film_ovl->strb_char_count[i] > 0) {
                mFont_SetLineStrings(game, line->text, film_ovl->strb_char_count[i], x, y, 255, 255, 255, 255, FALSE,
                                    TRUE, scale, scale, 0);
            }
            y += 16.0f * scale;
            line++;
        }
#endif

        if (film_ovl->mark_enabled == TRUE && film_ovl->card_busy == FALSE) {
            mFont_SetMarkChar(game, 3, 256.0f, 209.0f, 0, 0, 255, film_ovl->blink_alpha, FALSE, 1.0f, 1.0f, 0);
        }
    }
}

static void mFL_set_selb_frame_dl(mFL_Ovl_c* film_ovl, GRAPH* graph, f32 pos_x, f32 pos_y) {
    float scale = film_ovl->selb_scale;
    float x = pos_x + 80.0f + film_ovl->selb_item_x * scale;
    float y = pos_y + -72.0f + film_ovl->selb_item_y * scale;

    Matrix_translate(x * 16.0f, y * 16.0f, 140.0f, MTX_LOAD);
    Matrix_scale(film_ovl->selb_width * scale, film_ovl->selb_height * scale, 1.0f,
                 MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, mChoice_init_disp);
    gSPDisplayList(POLY_OPA_DISP++, con_sentaku2_modelT);

    CLOSE_POLY_OPA_DISP(graph);
}

static void mFL_set_selb_strings(Submenu* submenu, GAME* game, f32 pos_x, f32 pos_y) {
    static f32 offset_y[] = { -16.0f, 0.0f, 16.0f };
    static rgba_t color[] = {
        { 180, 150, 110, 255 },
        { 120, 50, 50, 255 },
    };
    mFL_Ovl_c* film_ovl = submenu->overlay->film_ovl;
    GRAPH* graph = game->graph;
    mFL_SelbString_c* str_data;
    mFL_Line_c* line;
    f32 scale;
    f32 x;
    f32 y;
    int i;

    scale = film_ovl->selb_scale;
    submenu->overlay->set_char_matrix_proc(graph);

    str_data = &fl_selb_str_data[film_ovl->selb_idx];
    line = str_data->lines;

    x = 80.0f + (160.0f + pos_x) + (film_ovl->selb_item_x + film_ovl->selb_mark_x) * scale;
    y = 120.0f - ((-72.0f + pos_y) + (film_ovl->selb_item_y - film_ovl->selb_mark_y) * scale);

    for (i = 0; i < str_data->line_count; i++) {
        int idx;

        if (i == film_ovl->selb_cursor) {
            idx = 1;
        } else {
            idx = 0;
        }

        mFont_SetLineStrings(game, line->text, line->length, x, y + offset_y[i] * scale, color[idx].r, color[idx].g,
                             color[idx].b, color[idx].a, FALSE, TRUE, scale, scale, 0);
        line++;
    }

    if (film_ovl->selb_step != 0) {
        mFont_SetMarkChar(game, 4, x + -16.0f * scale, y + offset_y[film_ovl->selb_cursor] * scale, 0, 195, 185, 255,
                          FALSE, scale, scale, 0);
    }
}

static void mFL_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    mFL_Ovl_c* film_ovl = submenu->overlay->film_ovl;
    f32 pos_x = menu->position[0];
    f32 pos_y = menu->position[1];
    GRAPH* graph = game->graph;

    mFL_set_film_frame_dl(film_ovl, graph, pos_x, pos_y);
    mFL_set_strb_frame_dl(film_ovl, graph, pos_x, pos_y);
    mFL_set_strb_strings(submenu, game, pos_x, pos_y);
    mFL_set_selb_frame_dl(film_ovl, graph, pos_x, pos_y);
    mFL_set_selb_strings(submenu, game, pos_x, pos_y);
}

static void mFL_film_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu = &submenu->overlay->menu_info[mSM_OVL_FILM];

    (*menu->pre_draw_func)(submenu, game);
    mFL_set_dl(submenu, game, menu);
}

extern void mFL_film_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->menu_control.menu_move_func = &mFL_film_ovl_move;
    overlay->menu_control.menu_draw_func = &mFL_film_ovl_draw;
}

static void mFL_film_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu = &overlay->menu_info[mSM_OVL_FILM];
    mFL_Ovl_c* film_ovl = overlay->film_ovl;
    int next_step;
    u8 voice_mode;

    overlay->menu_control.animation_flag = 0;
    film_ovl->strb_idx = -1;
    film_ovl->card_status = 0x26;

    switch (menu->data0) {
    case 0:
        menu->proc_status = mSM_OVL_PROC_MOVE;
        menu->next_proc_status = mSM_OVL_PROC_PLAY;
        menu->move_drt = 1;
        film_ovl->drive_c = 0;
        film_ovl->next_strb_idx = -1;
        film_ovl->prbuf = getP_prbuf();
        film_ovl->mode = 0;
        next_step = 2;
        mFL_strb_setupStep(film_ovl, 1);
        break;
    case 1:
        menu->proc_status = mSM_OVL_PROC_WAIT;
        film_ovl->drive_c = 1;
        film_ovl->sdcard_buf = JW_Get_SDCardBuffer_p();
        film_ovl->mode = 1;
        next_step = 3;
        break;
    case 2:
        menu->proc_status = mSM_OVL_PROC_WAIT;
        film_ovl->drive_c = 0;
        film_ovl->sdcard_buf = JW_Get_SDCardBuffer_p();
        film_ovl->mode = 2;
        next_step = 3;
        break;
    }

    film_ovl->next_strb_step = next_step;

    voice_mode = 1;
    if (Save_Get(config).voice_mode == 2) {
        voice_mode = 2;
    }
    sAdo_SetVoiceMode(voice_mode);
}

extern void mFL_film_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->film_ovl == NULL) {
        mem_clear((u8*)&fl_ovl_data, sizeof(mFL_Ovl_c), 0);
        overlay->film_ovl = &fl_ovl_data;
    }

    mFL_film_ovl_init(submenu);
    mFL_film_ovl_set_proc(submenu);
}

extern void mFL_film_ovl_destruct(Submenu* submenu) {
    submenu->overlay->film_ovl = NULL;

    mMsg_sound_spec_change_voice(mMsg_Get_base_window_p());
    mMsg_sound_voice_mode(mMsg_Get_base_window_p());
}
