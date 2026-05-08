#include "m_banti.h"

#include <libultra/libultra.h>
#include "sys_matrix.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_common_data.h"

#define banti_MODE_FONT 0
#define banti_MODE_POLY_OPA 1

enum {
    banti_STATE_SHOWN,
    banti_STATE_HIDING,
    banti_STATE_HIDDEN,
    banti_STATE_SHOWING,

    banti_STATE_NUM
};

enum {
    banti_FIELD_MONTH,
    banti_FIELD_DAY,
    banti_FIELD_HOUR10,
    banti_FIELD_HOUR01,
    banti_FIELD_MIN10,
    banti_FIELD_MIN01,

    banti_FIELD_NUM
};

typedef struct banti_s {
    int addressable_type;
    int disabled;
    int addressable_delay_timer;
    int disp_left;
    int move_left;
    float move_timer;
    float disp_ofs_y;
    float disp_vel_y;
    int state;
    int vel_timer;
    u8 month_frame;
    u8 day_frame;
    u8 week_frame;
    u8 ampm_frame;
    u8 hour_upper_frame;
    u8 hour_lower_frame;
    u8 min_upper_frame;
    u8 min_lower_frame;
    lbRTC_time_c displayed_time;
    lbRTC_time_c next_time;
} banti_c;

static banti_c banti;

static Gfx banti_dummy_displayList[] = { gsSPEndDisplayList() };

static BOOL banti_check_disp_condition(GAME_PLAY* play, int chk_capture_mode);

void banti_ct(void) {
    bzero(&banti, sizeof(banti));
    banti.addressable_type = mPlayer_ADDRESSABLE_TRUE;
    banti.disabled = FALSE;
    banti.addressable_delay_timer = 0;
    banti.disp_left = FALSE;
    banti.move_left = FALSE;
    banti.move_timer = 0.0f;

    lbRTC_TimeCopy(&banti.next_time, Common_GetPointer(time.rtc_time));
    lbRTC_TimeCopy(&banti.displayed_time, Common_GetPointer(time.rtc_time));

    if (gamePT != NULL) {
        if (!banti_check_disp_condition((GAME_PLAY*)gamePT, FALSE)) {
            banti.disp_ofs_y = 1300.0f;
            banti.state = banti_STATE_HIDDEN;
        } else {
            banti.disp_ofs_y = 0.0f;
            banti.state = banti_STATE_SHOWN;
        }
    }
}

void banti_dt(void) {
    // nothing
}

static void banti_chk_disp_left(GAME_PLAY* play) {
    ACTOR* playerx = GET_PLAYER_ACTOR_ACTOR(play);
    xyz_t player_pos_screen;

    Game_play_Projection_Trans(play, &playerx->world.position, &player_pos_screen);

    if (player_pos_screen.x >= 180.0f && player_pos_screen.y >= 150.0f) {
        if (banti.move_left == FALSE) {
            banti.move_left = TRUE;
            banti.move_timer = 0.0f;
        }

        banti.move_timer += 1.0f;
        if (banti.move_timer > 10.0f) {
            banti.move_timer = 10.0f;

            switch (banti.state) {
                case banti_STATE_HIDDEN:
                    banti.disp_left = TRUE;
                    banti.disabled = FALSE;
                    break;
                case banti_STATE_SHOWN:
                    if (banti.disp_left == FALSE) {
                        banti.disabled = TRUE;
                    }
                    break;
            }
        }
    } else {
        if (banti.move_left == TRUE) {
            banti.move_left = FALSE;
            banti.move_timer = 0.0f;
        }

        banti.move_timer += 1.0f;
        if (banti.move_timer > 10.0f) {
            banti.move_timer = 10.0f;

            switch (banti.state) {
                case banti_STATE_HIDDEN:
                    banti.disp_left = FALSE;
                    banti.disabled = FALSE;
                    break;
                case banti_STATE_SHOWN:
                    if (banti.disp_left == TRUE) {
                        banti.disabled = TRUE;
                    }
                    break;
            }
        }
    }
}

static int banti_check_capture_submenu(GAME_PLAY* play) {
    int ret = TRUE;

    if (play->submenu.process_status != mSM_PROCESS_WAIT && play->submenu.capture_display_mode == mSM_CAPTURE_DISPLAY_MODE_FILM) {
        ret = FALSE;
    }

    return ret;
}

static BOOL banti_check_disp_condition(GAME_PLAY* play, int chk_capture_mode) {
    BOOL ret = TRUE;

    if (mDemo_CheckDemo() || mEv_IsTitleDemo() || banti.disabled) {
        ret = FALSE;
        banti.addressable_type = mPlayer_ADDRESSABLE_FALSE_MOVEMENT;
    } else if (banti.addressable_type != mPlayer_ADDRESSABLE_TRUE) {
        ret = FALSE;
    } else if ( play->submenu.process_status != mSM_PROCESS_WAIT) {
        switch (play->submenu.capture_display_mode) {
            case mSM_CAPTURE_DISPLAY_MODE_SUBMENU:
                ret = FALSE;
                break;
            
            case mSM_CAPTURE_DISPLAY_MODE_FILM:
                if (chk_capture_mode == TRUE) {
                    ret = FALSE;
                }
                break;
        }
    }

    return ret;
}

static void banti_disp_offset_proc(GAME_PLAY* play) {
    float disp_ofs_y = banti.disp_ofs_y;
    float disp_vel_y = banti.disp_vel_y;
    int vel_timer = banti.vel_timer;

    switch (banti.state) {
        case banti_STATE_SHOWN:
            if (banti_check_disp_condition(play, FALSE) == FALSE) {
                banti.state = banti_STATE_HIDING;
                vel_timer = 0;
                disp_ofs_y = 0.0f;
                disp_vel_y = 15.0f;
            }
            break;
        case banti_STATE_HIDING:
            if (banti_check_capture_submenu(play) == TRUE) {
                vel_timer++;
                if ((vel_timer & 1) == 0) {
                    disp_vel_y *= 2.0f;
                }

                if (disp_vel_y > 450.0f) {
                    disp_vel_y = 450.0f;
                }

                disp_ofs_y += disp_vel_y;
                if (disp_ofs_y >= 1300.0f) {
                    banti.state = banti_STATE_HIDDEN;
                    disp_ofs_y = 1300.0f;
                }
            }
            break;
        case banti_STATE_HIDDEN:
            if (banti_check_disp_condition(play, TRUE) == TRUE) {
                banti.state = banti_STATE_SHOWING;
                vel_timer = 0;
                disp_ofs_y = 1300.0f;
                disp_vel_y = 450.0f;
            }
            break;
        case banti_STATE_SHOWING:
            if (banti_check_capture_submenu(play) == TRUE) {
                vel_timer++;
                if ((vel_timer & 1) == 0) {
                    disp_vel_y /= 2.0f;
                }

                if (disp_vel_y < 15.0f) {
                    disp_vel_y = 15.0f;
                }

                disp_ofs_y -= disp_vel_y;
                if (disp_ofs_y < 0.0f) {
                    banti.state = banti_STATE_SHOWN;
                    disp_ofs_y = 0.0f;
                }
            }
            break;
    }

    banti.disp_ofs_y = disp_ofs_y;
    banti.disp_vel_y = disp_vel_y;
    banti.vel_timer = vel_timer;
}

#define banti_FRAME_CTR_DEC(f) \
do { \
    if ((f) > 0) { \
        (f)--; \
    } \
} while (0)

static void banti_anime_proc(void) {
    banti_FRAME_CTR_DEC(banti.month_frame);
    banti_FRAME_CTR_DEC(banti.day_frame);
    banti_FRAME_CTR_DEC(banti.week_frame);
    banti_FRAME_CTR_DEC(banti.ampm_frame);
    banti_FRAME_CTR_DEC(banti.hour_upper_frame);
    banti_FRAME_CTR_DEC(banti.hour_lower_frame);
    banti_FRAME_CTR_DEC(banti.min_upper_frame);
    banti_FRAME_CTR_DEC(banti.min_lower_frame);
}

static void banti_chk_anime_start(void) {
    int disp_hour;
    int hour;
    int disp_fig;
    int fig;
    int disp_pm;
    int now_pm;

    if (banti.month_frame == 0 && banti.displayed_time.month != Common_Get(time.rtc_time.month)) {
        banti.month_frame = 30;
    }

    if (banti.day_frame == 0 && banti.displayed_time.day != Common_Get(time.rtc_time.day)) {
        banti.day_frame = 30;
        banti.week_frame = 30;
    }

    if ((banti.displayed_time.hour >= 12)) {
        disp_pm = TRUE;
    } else {
        disp_pm = FALSE;
    }

    if ((Common_Get(time.rtc_time.hour) >= 12)) {
        now_pm = TRUE;
    } else {
        now_pm = FALSE;
    }
    
    if (now_pm != disp_pm) {
        banti.ampm_frame = 30;
    }

    if (banti.displayed_time.hour == 0 || banti.displayed_time.hour == 12) {
        disp_hour = 12;
    } else if (banti.displayed_time.hour > 11) {
        disp_hour = banti.displayed_time.hour - 12;
    } else {
        disp_hour = banti.displayed_time.hour;
    }
    
    if (Common_Get(time.rtc_time.hour) == 0 || Common_Get(time.rtc_time.hour) == 12) {
        hour = 12;
    } else if (Common_Get(time.rtc_time.hour) > 11) {
        hour = Common_Get(time.rtc_time.hour) - 12;
    } else {
        hour = Common_Get(time.rtc_time.hour);
    }

    disp_fig = (int)disp_hour / 10;
    fig = (int)hour / 10;
    if (banti.hour_upper_frame == 0 && disp_fig != fig) {
        banti.hour_upper_frame = 30;
    }

    disp_fig = (int)disp_hour % 10;
    fig = (int)hour % 10;
    if (banti.hour_lower_frame == 0 && disp_fig != fig) {
        banti.hour_lower_frame = 30;
    }

    disp_fig = (int)banti.displayed_time.min / 10;
    fig = (int)Common_Get(time.rtc_time.min) / 10;
    if (banti.min_upper_frame == 0 && disp_fig != fig) {
        banti.min_upper_frame = 30;
    }

    disp_fig = (int)banti.displayed_time.min % 10;
    fig = (int)Common_Get(time.rtc_time.min) % 10;
    if (banti.min_lower_frame == 0 && disp_fig != fig) {
        banti.min_lower_frame = 30;
    }
}

#define banti_ANIM() ( \
    (banti.month_frame != 0) | \
    (banti.day_frame != 0) | \
    (banti.week_frame != 0) | \
    (banti.ampm_frame != 0) | \
    (banti.hour_upper_frame != 0) | \
    (banti.hour_lower_frame != 0) | \
    (banti.min_upper_frame != 0) | \
    (banti.min_lower_frame != 0) \
)

static void banti_time_check(void) {
    BOOL current = banti_ANIM();

    if (!current) {
        banti_chk_anime_start();
    }

    banti_anime_proc();

    if (current != banti_ANIM()) {
        if (!current) {
            lbRTC_TimeCopy(&banti.next_time, Common_GetPointer(time.rtc_time));
        } else {
            lbRTC_TimeCopy(&banti.displayed_time, &banti.next_time);
        }
    }
}

void banti_move(GAME_PLAY* play) {
    int addressable;
    
    banti_chk_disp_left(play);
    addressable = mPlib_Get_address_able_display();

    if (banti.addressable_type != addressable) {
        BOOL update_addressable = FALSE;

        banti.addressable_delay_timer++;
        if (addressable == mPlayer_ADDRESSABLE_FALSE_READY_NET) {
            if (banti.addressable_delay_timer > 18) {
                update_addressable = TRUE;
            }
        } else if (banti.addressable_type != mPlayer_ADDRESSABLE_TRUE) {
            if (banti.addressable_delay_timer > 76 || addressable == mPlayer_ADDRESSABLE_FALSE_TALKING) {
                update_addressable = TRUE;
            }
        } else {
            if (banti.addressable_delay_timer > 50 || addressable == mPlayer_ADDRESSABLE_FALSE_TALKING) {
                update_addressable = TRUE;
            }
        }

        if (update_addressable == TRUE) {
            banti.addressable_delay_timer = 0;
            banti.addressable_type = addressable;
        }
    } else {
        banti.addressable_delay_timer = 0;
    }

    banti_disp_offset_proc(play);
    banti_time_check();
}

static Gfx* banti_get_DL_pointer(GRAPH* graph, int mode) {
    OPEN_DISP(graph);
    if (mode == banti_MODE_POLY_OPA) {
        return NOW_POLY_OPA_DISP;
    } else {
        return NOW_FONT_DISP;
    }
    CLOSE_DISP(graph);
}

static void banti_set_DL_pointer(GRAPH* graph, Gfx* gfx, int mode) {
    OPEN_DISP(graph);
    if (mode == banti_MODE_POLY_OPA) {
        SET_POLY_OPA_DISP(gfx);
    } else {
        SET_FONT_DISP(gfx);
    }
    CLOSE_DISP(graph);
}

static void banti_evw_anime(Gfx** gfx_pp, GAME_PLAY* play, int mode, EVW_ANIME_DATA* evw_anime, int frame) {
    GRAPH* graph = play->game.graph;
    Gfx* g;
    u32 cur_frame = play->game_frame;

    // This is an absolute dogshit hack.
    play->game_frame = 30 - frame;

    OPEN_DISP(graph);
    
    g = NOW_POLY_OPA_DISP;
    SET_POLY_OPA_DISP(*gfx_pp);
    Evw_Anime_Set(play, evw_anime);
    *gfx_pp = NOW_POLY_OPA_DISP;
    if (mode != banti_MODE_POLY_OPA) {
        SET_POLY_OPA_DISP(g);
    }

    CLOSE_DISP(graph);

    play->game_frame = cur_frame;
}

extern u8 clk_yobi_1_tex_rgb_ia8[];
extern u8 clk_yobi_2_tex_rgb_ia8[];
extern u8 clk_yobi_3_tex_rgb_ia8[];
extern u8 clk_yobi_4_tex_rgb_ia8[];
extern u8 clk_yobi_5_tex_rgb_ia8[];
extern u8 clk_yobi_6_tex_rgb_ia8[];
extern u8 clk_yobi_7_tex_rgb_ia8[];
extern u8 clk_yobi_b_1_tex_rgb_i4[];
extern u8 clk_yobi_b_2_tex_rgb_i4[];
extern u8 clk_yobi_b_3_tex_rgb_i4[];
extern u8 clk_yobi_b_4_tex_rgb_i4[];
extern u8 clk_yobi_b_5_tex_rgb_i4[];
extern u8 clk_yobi_b_6_tex_rgb_i4[];
extern u8 clk_yobi_b_7_tex_rgb_i4[];

extern EVW_ANIME_DATA clk_yobi_a_evw_anime[];
extern Gfx clk_yobi_aT_model[];
extern Gfx clk_yobi_b_model[];

static void banti_draw_yobi(Gfx** gfx_pp, GAME_PLAY* play, int mode) {
    static u8* week_tex_table[lbRTC_WEEK] = {
        clk_yobi_1_tex_rgb_ia8,
        clk_yobi_2_tex_rgb_ia8,
        clk_yobi_3_tex_rgb_ia8,
        clk_yobi_4_tex_rgb_ia8,
        clk_yobi_5_tex_rgb_ia8,
        clk_yobi_6_tex_rgb_ia8,
        clk_yobi_7_tex_rgb_ia8,
    };

    static u8* week_tex_b_table[lbRTC_WEEK] = {
        clk_yobi_b_1_tex_rgb_i4,
        clk_yobi_b_2_tex_rgb_i4,
        clk_yobi_b_3_tex_rgb_i4,
        clk_yobi_b_4_tex_rgb_i4,
        clk_yobi_b_5_tex_rgb_i4,
        clk_yobi_b_6_tex_rgb_i4,
        clk_yobi_b_7_tex_rgb_i4,
    };
    gDPSetPrimColor((*gfx_pp)++, 0, 255, 255, 255, 225, 255);

    if (banti.week_frame == 0) {
        gSPSegment((*gfx_pp)++, ANIME_2_TXT_SEG, banti_dummy_displayList);
    } else {
        if (banti.next_time.weekday == lbRTC_SUNDAY) {
            gDPSetEnvColor((*gfx_pp)++, 200, 60, 50, 255);
        } else {
            gDPSetEnvColor((*gfx_pp)++, 70, 140, 50, 255);
        }

        gSPSegment((*gfx_pp)++, ANIME_2_TXT_SEG, week_tex_b_table[banti.next_time.weekday]);
        gSPDisplayList((*gfx_pp)++, clk_yobi_b_model);
        banti_evw_anime(gfx_pp, play, mode, clk_yobi_a_evw_anime, banti.week_frame);
    }

    gSPSegment((*gfx_pp)++, ANIME_1_TXT_SEG, week_tex_table[banti.displayed_time.weekday]);
    if (banti.displayed_time.weekday == lbRTC_SUNDAY) {
        gDPSetEnvColor((*gfx_pp)++, 200, 60, 50, 255);
    } else {
        gDPSetEnvColor((*gfx_pp)++, 70, 140, 50, 255);
    }
    gSPDisplayList((*gfx_pp)++, clk_yobi_aT_model);
}

extern u8 clk_ampm_am_tex_rgb_ia8[];
extern u8 clk_ampm_pm_tex_rgb_ia8[];
extern u8 clk_ampm_b_am_tex_rgb_i4[];
extern u8 clk_ampm_b_pm_tex_rgb_i4[];

extern EVW_ANIME_DATA clk_ampm_a_evw_anime[];
extern Gfx clk_ampm_aT_model[];
extern Gfx clk_ampm_b_model[];

static void banti_draw_ampm(Gfx** gfx_pp, GAME_PLAY* play, int mode) {
    static u8* tex_table[] = { clk_ampm_am_tex_rgb_ia8, clk_ampm_pm_tex_rgb_ia8 };
    static u8* tex_b_table[] = { clk_ampm_b_am_tex_rgb_i4, clk_ampm_b_pm_tex_rgb_i4 };

    int hour_idx = banti.displayed_time.hour >= 12;

    gDPSetPrimColor((*gfx_pp)++, 0, 255, 255, 255, 225, 255);

    if (banti.ampm_frame == 0) {
        gSPSegment((*gfx_pp)++, ANIME_2_TXT_SEG, banti_dummy_displayList);
    } else {
        int next_hour_idx = banti.next_time.hour >= 12;

        gSPSegment((*gfx_pp)++, ANIME_2_TXT_SEG, tex_b_table[next_hour_idx]);
        if (next_hour_idx == 0) {
            gDPSetEnvColor((*gfx_pp)++, 230, 120, 0, 255);
        } else {
            gDPSetEnvColor((*gfx_pp)++, 140, 70, 180, 255);
        }

        gSPDisplayList((*gfx_pp)++, clk_ampm_b_model);
        banti_evw_anime(gfx_pp, play, mode, clk_ampm_a_evw_anime, banti.ampm_frame);
    }

    gSPSegment((*gfx_pp)++, ANIME_1_TXT_SEG, tex_table[hour_idx]);
    if (hour_idx == 0) {
        gDPSetEnvColor((*gfx_pp)++, 230, 120, 0, 255);
    } else {
        gDPSetEnvColor((*gfx_pp)++, 140, 70, 180, 255);
    }
    gSPDisplayList((*gfx_pp)++, clk_ampm_aT_model);
}

extern Gfx clk_day_aT_model[];
extern EVW_ANIME_DATA clk_day_a_evw_anime[];
extern Gfx clk_day_b_model[];
extern Gfx clk_hour01_aT_model[];
extern EVW_ANIME_DATA clk_hour01_a_evw_anime[];
extern Gfx clk_hour01_b_model[];
extern Gfx clk_hour10_aT_model[];
extern EVW_ANIME_DATA clk_hour10_a_evw_anime[];
extern Gfx clk_hour10_b_model[];
extern Gfx clk_min01_aT_model[];
extern EVW_ANIME_DATA clk_min01_a_evw_anime[];
extern Gfx clk_min01_b_model[];
extern Gfx clk_min10_aT_model[];
extern EVW_ANIME_DATA clk_min10_a_evw_anime[];
extern Gfx clk_min10_b_model[];
extern Gfx clk_month_aT_model[];
extern EVW_ANIME_DATA clk_month_a_evw_anime[];
extern Gfx clk_month_b_model[];
extern u8 clk_num_00_tex_rgb_ia8[];
extern u8 clk_num_01_tex_rgb_ia8[];
extern u8 clk_num_02_tex_rgb_ia8[];
extern u8 clk_num_03_tex_rgb_ia8[];
extern u8 clk_num_04_tex_rgb_ia8[];
extern u8 clk_num_05_tex_rgb_ia8[];
extern u8 clk_num_06_tex_rgb_ia8[];
extern u8 clk_num_07_tex_rgb_ia8[];
extern u8 clk_num_08_tex_rgb_ia8[];
extern u8 clk_num_09_tex_rgb_ia8[];
extern u8 clk_num_10_tex_rgb_ia8[];
extern u8 clk_num_11_tex_rgb_ia8[];
extern u8 clk_num_12_tex_rgb_ia8[];
extern u8 clk_num_13_tex_rgb_ia8[];
extern u8 clk_num_14_tex_rgb_ia8[];
extern u8 clk_num_15_tex_rgb_ia8[];
extern u8 clk_num_16_tex_rgb_ia8[];
extern u8 clk_num_17_tex_rgb_ia8[];
extern u8 clk_num_18_tex_rgb_ia8[];
extern u8 clk_num_19_tex_rgb_ia8[];
extern u8 clk_num_20_tex_rgb_ia8[];
extern u8 clk_num_21_tex_rgb_ia8[];
extern u8 clk_num_22_tex_rgb_ia8[];
extern u8 clk_num_23_tex_rgb_ia8[];
extern u8 clk_num_24_tex_rgb_ia8[];
extern u8 clk_num_25_tex_rgb_ia8[];
extern u8 clk_num_26_tex_rgb_ia8[];
extern u8 clk_num_27_tex_rgb_ia8[];
extern u8 clk_num_28_tex_rgb_ia8[];
extern u8 clk_num_29_tex_rgb_ia8[];
extern u8 clk_num_30_tex_rgb_ia8[];
extern u8 clk_num_31_tex_rgb_ia8[];
extern u8 clk_num_xx_tex_rgb_ia8[];
extern u8 clk_num_b_00_tex_rgb_i4[];
extern u8 clk_num_b_01_tex_rgb_i4[];
extern u8 clk_num_b_02_tex_rgb_i4[];
extern u8 clk_num_b_03_tex_rgb_i4[];
extern u8 clk_num_b_04_tex_rgb_i4[];
extern u8 clk_num_b_05_tex_rgb_i4[];
extern u8 clk_num_b_06_tex_rgb_i4[];
extern u8 clk_num_b_07_tex_rgb_i4[];
extern u8 clk_num_b_08_tex_rgb_i4[];
extern u8 clk_num_b_09_tex_rgb_i4[];
extern u8 clk_num_b_10_tex_rgb_i4[];
extern u8 clk_num_b_11_tex_rgb_i4[];
extern u8 clk_num_b_12_tex_rgb_i4[];
extern u8 clk_num_b_13_tex_rgb_i4[];
extern u8 clk_num_b_14_tex_rgb_i4[];
extern u8 clk_num_b_15_tex_rgb_i4[];
extern u8 clk_num_b_16_tex_rgb_i4[];
extern u8 clk_num_b_17_tex_rgb_i4[];
extern u8 clk_num_b_18_tex_rgb_i4[];
extern u8 clk_num_b_19_tex_rgb_i4[];
extern u8 clk_num_b_20_tex_rgb_i4[];
extern u8 clk_num_b_21_tex_rgb_i4[];
extern u8 clk_num_b_22_tex_rgb_i4[];
extern u8 clk_num_b_23_tex_rgb_i4[];
extern u8 clk_num_b_24_tex_rgb_i4[];
extern u8 clk_num_b_25_tex_rgb_i4[];
extern u8 clk_num_b_26_tex_rgb_i4[];
extern u8 clk_num_b_27_tex_rgb_i4[];
extern u8 clk_num_b_28_tex_rgb_i4[];
extern u8 clk_num_b_29_tex_rgb_i4[];
extern u8 clk_num_b_30_tex_rgb_i4[];
extern u8 clk_num_b_31_tex_rgb_i4[];
extern u8 clk_num_b_xx_tex_rgb_i4[];

typedef struct disp_s {
    Gfx* a_model;
    EVW_ANIME_DATA* evw_anime;
    Gfx* b_model;
} Banti_time_disp_c;

static void banti_draw_time_sub(Gfx** gfx_pp, GAME_PLAY* play, int disp, int next, BOOL zero_empty_flag, int field, int frame, int mode) {
    static u8* num_a_tex_table[33] = {
        clk_num_00_tex_rgb_ia8,
        clk_num_01_tex_rgb_ia8,
        clk_num_02_tex_rgb_ia8,
        clk_num_03_tex_rgb_ia8,
        clk_num_04_tex_rgb_ia8,
        clk_num_05_tex_rgb_ia8,
        clk_num_06_tex_rgb_ia8,
        clk_num_07_tex_rgb_ia8,
        clk_num_08_tex_rgb_ia8,
        clk_num_09_tex_rgb_ia8,
        clk_num_10_tex_rgb_ia8,
        clk_num_11_tex_rgb_ia8,
        clk_num_12_tex_rgb_ia8,
        clk_num_13_tex_rgb_ia8,
        clk_num_14_tex_rgb_ia8,
        clk_num_15_tex_rgb_ia8,
        clk_num_16_tex_rgb_ia8,
        clk_num_17_tex_rgb_ia8,
        clk_num_18_tex_rgb_ia8,
        clk_num_19_tex_rgb_ia8,
        clk_num_20_tex_rgb_ia8,
        clk_num_21_tex_rgb_ia8,
        clk_num_22_tex_rgb_ia8,
        clk_num_23_tex_rgb_ia8,
        clk_num_24_tex_rgb_ia8,
        clk_num_25_tex_rgb_ia8,
        clk_num_26_tex_rgb_ia8,
        clk_num_27_tex_rgb_ia8,
        clk_num_28_tex_rgb_ia8,
        clk_num_29_tex_rgb_ia8,
        clk_num_30_tex_rgb_ia8,
        clk_num_31_tex_rgb_ia8,
        clk_num_xx_tex_rgb_ia8,
    };

    static u8* num_tex_b_table[33] = {
        clk_num_b_00_tex_rgb_i4,
        clk_num_b_01_tex_rgb_i4,
        clk_num_b_02_tex_rgb_i4,
        clk_num_b_03_tex_rgb_i4,
        clk_num_b_04_tex_rgb_i4,
        clk_num_b_05_tex_rgb_i4,
        clk_num_b_06_tex_rgb_i4,
        clk_num_b_07_tex_rgb_i4,
        clk_num_b_08_tex_rgb_i4,
        clk_num_b_09_tex_rgb_i4,
        clk_num_b_10_tex_rgb_i4,
        clk_num_b_11_tex_rgb_i4,
        clk_num_b_12_tex_rgb_i4,
        clk_num_b_13_tex_rgb_i4,
        clk_num_b_14_tex_rgb_i4,
        clk_num_b_15_tex_rgb_i4,
        clk_num_b_16_tex_rgb_i4,
        clk_num_b_17_tex_rgb_i4,
        clk_num_b_18_tex_rgb_i4,
        clk_num_b_19_tex_rgb_i4,
        clk_num_b_20_tex_rgb_i4,
        clk_num_b_21_tex_rgb_i4,
        clk_num_b_22_tex_rgb_i4,
        clk_num_b_23_tex_rgb_i4,
        clk_num_b_24_tex_rgb_i4,
        clk_num_b_25_tex_rgb_i4,
        clk_num_b_26_tex_rgb_i4,
        clk_num_b_27_tex_rgb_i4,
        clk_num_b_28_tex_rgb_i4,
        clk_num_b_29_tex_rgb_i4,
        clk_num_b_30_tex_rgb_i4,
        clk_num_b_31_tex_rgb_i4,
        clk_num_b_xx_tex_rgb_i4,
    };

    static Banti_time_disp_c time_disp_table[6] = {
        {clk_month_aT_model, clk_month_a_evw_anime, clk_month_b_model},
        {clk_day_aT_model, clk_day_a_evw_anime, clk_day_b_model},
        {clk_hour10_aT_model, clk_hour10_a_evw_anime, clk_hour10_b_model},
        {clk_hour01_aT_model, clk_hour01_a_evw_anime, clk_hour01_b_model},
        {clk_min10_aT_model, clk_min10_a_evw_anime, clk_min10_b_model},
        {clk_min01_aT_model, clk_min01_a_evw_anime, clk_min01_b_model},
    };

    Banti_time_disp_c* disp_tbl = &time_disp_table[field];

    if (zero_empty_flag == TRUE) {
        if (disp == 0) {
            disp = 32; // XX
        }

        if (next == 0) {
            next = 32; // XX
        }
    }

    if (frame == 0) {
        gSPSegment((*gfx_pp)++, ANIME_2_TXT_SEG, banti_dummy_displayList);
    } else {
        gSPSegment((*gfx_pp)++, ANIME_1_TXT_SEG, num_tex_b_table[next]);
        gSPDisplayList((*gfx_pp)++, disp_tbl->b_model);
        banti_evw_anime(gfx_pp, play, mode, disp_tbl->evw_anime, frame);
    }

    gSPSegment((*gfx_pp)++, ANIME_1_TXT_SEG, num_a_tex_table[disp]);
    gSPDisplayList((*gfx_pp)++, disp_tbl->a_model);
}

static void banti_draw_time(Gfx** gfx_pp, GAME_PLAY* play, int mode) {
    int disp_hour;
    int next_hour;
    
    gDPSetPrimColor((*gfx_pp)++, 0, 255, 255, 255, 240, 255);
    gDPSetEnvColor((*gfx_pp)++, 110, 70, 70, 255);

    disp_hour = banti.displayed_time.hour;
    if (disp_hour == 0 || disp_hour == 12) {
        disp_hour = 12;
    } else if (disp_hour > 11) {
        disp_hour -= 12;
    }

    next_hour = banti.next_time.hour;
    if (next_hour == 0 || next_hour == 12) {
        next_hour = 12;
    } else if (next_hour > 11) {
        next_hour -= 12;
    }

    banti_draw_time_sub(gfx_pp, play, banti.displayed_time.month, banti.next_time.month, FALSE, banti_FIELD_MONTH, banti.month_frame, mode);
    banti_draw_time_sub(gfx_pp, play, banti.displayed_time.day, banti.next_time.day, FALSE, banti_FIELD_DAY, banti.day_frame, mode);
    banti_draw_time_sub(gfx_pp, play, disp_hour / 10, next_hour / 10, TRUE, banti_FIELD_HOUR10, banti.hour_upper_frame, mode);
    banti_draw_time_sub(gfx_pp, play, disp_hour % 10, next_hour % 10, FALSE, banti_FIELD_HOUR01, banti.hour_lower_frame, mode);
    banti_draw_time_sub(gfx_pp, play, banti.displayed_time.min / 10, banti.next_time.min / 10, FALSE, banti_FIELD_MIN10, banti.min_upper_frame, mode);
    banti_draw_time_sub(gfx_pp, play, banti.displayed_time.min % 10, banti.next_time.min % 10, FALSE, banti_FIELD_MIN01, banti.min_lower_frame, mode);
}

extern Gfx clk_win_mode[];
extern Gfx clk_itaT_model[];
extern Gfx clk_etc_model[];
extern Gfx clk_sec_model[];

void banti_draw(GAME_PLAY* play) {
    if (mFI_GET_ROOMTYPE() == mFI_FIELD_FG && mEv_CheckFirstIntro() != TRUE) {
        GRAPH* graph = play->game.graph;
        int mode = banti_MODE_FONT;
        Mtx* m = GRAPH_ALLOC_TYPE(graph, Mtx, 1);
        Gfx* gfx;
        
        if (play->submenu.process_status != mSM_PROCESS_WAIT && play->submenu.mode > mSM_MODE_PRERENDER_WAIT) {
            mode = banti_MODE_POLY_OPA;
        }

        if (m != NULL) {
            mFont_CulcOrthoMatrix(m);
            OPEN_DISP(graph);

            if (mode == banti_MODE_POLY_OPA) {
                gSPMatrix(NEXT_POLY_OPA_DISP, m, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION)
            } else {
                gSPMatrix(NEXT_FONT_DISP, m, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION)
            }

            CLOSE_DISP(graph);
        }

        if (banti.disp_left == TRUE) {
            Matrix_translate(-1430.0f, -1240.0f - banti.disp_ofs_y, 0.0f, MTX_LOAD);
        } else {
            Matrix_translate(1430.0f, -1240.0f - banti.disp_ofs_y, 0.0f, MTX_LOAD);
        }
        
        Matrix_scale(0.41f, 0.41f, 0.41f, MTX_MULT);

        gfx = banti_get_DL_pointer(graph, mode);
        gSPDisplayList(gfx++, clk_win_mode);
        gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_CLD_SURF2);
        gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        banti_draw_yobi(&gfx, play, mode);
        banti_draw_ampm(&gfx, play, mode);
        banti_draw_time(&gfx, play, mode);
        gDPSetPrimColor(gfx++, 0, 255, 255, 180, 80, 255);
        gSPDisplayList(gfx++, clk_itaT_model);
        gDPSetPrimColor(gfx++, 0, 255, 120, 70, 0, 255);
        gSPDisplayList(gfx++, clk_etc_model);

        if ((Common_Get(time.rtc_time.sec) & 1) == 1 || mCD_castingoff_mura_chk() == TRUE) {
            gDPSetPrimColor(gfx++, 0, 255, 120, 70, 0, 255);
            gSPDisplayList(gfx++, clk_sec_model);
        }

        banti_set_DL_pointer(graph, gfx, mode);
    }
}
