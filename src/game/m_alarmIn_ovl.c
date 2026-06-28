#include "m_alarmIn_ovl.h"
#include "m_submenu_ovl.h"
#include "sys_matrix.h"
#include "audio.h"
#include "m_common_data.h"
#include "m_haniwaPortrait_ovl.h"
#include "m_font.h"

static mAL_Ovl_c al_ovl_data;

static void mAL_window_close(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mAL_Ovl_c* alarmIn_ovl = submenu->overlay->alarmIn_ovl;

    (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
    if (menu_info->data0 == mHm_HANIWA_ALARM_MODE_ON_PLAY) {
        if (Common_Get(player_no) < PLAYER_NUM) {
            HaniwaAlarmInfo_c* alarm = &Save_Get(homes[mHS_get_arrange_idx(Common_Get(player_no))]).haniwa.alarm_info;

            alarm->enabled = TRUE;
            alarm->mode = mHm_HANIWA_ALARM_MODE_ON_PLAY;
            alarm->hour = alarmIn_ovl->delay_values[mAL_IDX_HOUR];
            alarm->minute = alarmIn_ovl->delay_values[mAL_IDX_MIN];
        }
    } else {
        if (Common_Get(player_no) < PLAYER_NUM) {
            HaniwaAlarmInfo_c* alarm = &Save_Get(homes[mHS_get_arrange_idx(Common_Get(player_no))]).haniwa.alarm_info;

            alarm->enabled = TRUE;
            alarm->mode = mHm_HANIWA_ALARM_MODE_AT_TIME;
            alarm->hour = alarmIn_ovl->at_values[mAL_IDX_HOUR];
            alarm->minute = alarmIn_ovl->at_values[mAL_IDX_MIN];
        }
    }

    sAdo_SysTrgStart(NA_SE_MENU_EXIT);
}

static void mAL_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mAL_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    u32 trigger = submenu->overlay->menu_control.trigger;
    mAL_Ovl_c* alarmIn_ovl = submenu->overlay->alarmIn_ovl;
    int field = alarmIn_ovl->field;

    if (trigger & BUTTON_START) {
        mAL_window_close(submenu, menu_info);
    } else if (menu_info->data0 == mHm_HANIWA_ALARM_MODE_ON_PLAY) {
        if (trigger & (BUTTON_B | BUTTON_CLEFT)) {
            if (field >= 1) {
                sAdo_SysTrgStart(MONO(NA_SE_3));
                alarmIn_ovl->field--;
            }
        } else if (trigger & (BUTTON_A | BUTTON_CRIGHT)) {
            if (field == mAL_IDX_NUM) {
                if (trigger & BUTTON_A) {
                    mAL_window_close(submenu, menu_info);
                }
            } else {
                alarmIn_ovl->field++;
                sAdo_SysTrgStart(NA_SE_SENTAKU_KETTEI);
            }
        } else if (field != mAL_IDX_NUM) {
            if (trigger & (BUTTON_CDOWN | BUTTON_CUP)) {
                if (trigger & BUTTON_CUP) {
                    alarmIn_ovl->delay_values[field]++;
                    if (field == mAL_IDX_HOUR) {
                        if (alarmIn_ovl->delay_values[field] > 5) {
                            alarmIn_ovl->delay_values[field] = 0;
                        }
                    } else if (field == mAL_IDX_MIN) {
                        if (alarmIn_ovl->delay_values[field] > 59) {
                            alarmIn_ovl->delay_values[field] = 0;
                        }
                    }
                } else if (trigger & BUTTON_CDOWN) {
                    alarmIn_ovl->delay_values[field]--;
                    if (field == mAL_IDX_HOUR) {
                        if (alarmIn_ovl->delay_values[field] < 0) {
                            alarmIn_ovl->delay_values[field] = 5;
                        }
                    } else if (field == mAL_IDX_MIN) {
                        if (alarmIn_ovl->delay_values[field] < 0) {
                            alarmIn_ovl->delay_values[field] = 59;
                        }
                    }
                }

                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
        }
    } else {
        if (trigger & (BUTTON_B | BUTTON_CLEFT)) {
            if (field >= 1) {
                sAdo_SysTrgStart(MONO(NA_SE_3));
                alarmIn_ovl->field--;
            }
        } else if (trigger & (BUTTON_A | BUTTON_CRIGHT)) {
            if (field == mAL_IDX_NUM) {
                if (trigger & BUTTON_A) {
                    mAL_window_close(submenu, menu_info);
                }
            } else {
                alarmIn_ovl->field++;
                sAdo_SysTrgStart(NA_SE_SENTAKU_KETTEI);
            }
        } else if (field != mAL_IDX_NUM) {
            if (trigger & (BUTTON_CDOWN | BUTTON_CUP)) {
                if (trigger & BUTTON_CUP) {
                    alarmIn_ovl->at_values[field]++;
                    if (field == mAL_IDX_HOUR) {
                        if (alarmIn_ovl->at_values[field] > 23) {
                            alarmIn_ovl->at_values[field] = 0;
                        }
                    } else if (field == mAL_IDX_MIN) {
                        if (alarmIn_ovl->at_values[field] > 59) {
                            alarmIn_ovl->at_values[field] = 0;
                        }
                    }
                } else if (trigger & BUTTON_CDOWN) {
                    alarmIn_ovl->at_values[field]--;
                    if (field == mAL_IDX_HOUR) {
                        if (alarmIn_ovl->at_values[field] < 0) {
                            alarmIn_ovl->at_values[field] = 23;
                        }
                    } else if (field == mAL_IDX_MIN) {
                        if (alarmIn_ovl->at_values[field] < 0) {
                            alarmIn_ovl->at_values[field] = 59;
                        }
                    }
                }

                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
        }
    }
}

static void mAL_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

static void mAL_alarmIn_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = {
        &mAL_move_Move, &mAL_move_Play, (mSM_MOVE_PROC)&none_proc1, (mSM_MOVE_PROC)&none_proc1, &mAL_move_End,
    };

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_ALARMIN];
    Submenu_Overlay_c* overlay;

    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);

    overlay = submenu->overlay;
    if (menu_info->proc_status == mSM_OVL_PROC_PLAY) {
        overlay->haniwaPortrait_ovl->haniwaPortrait_shape_move_proc(submenu);
        overlay->menu_control.animation_flag = TRUE;
    } else {
        overlay->menu_control.animation_flag = FALSE;
    }
}

extern Gfx ain_win_jikoku_mode[];
extern Gfx ain_win_jikoku_model[];

static void mAL_set_frame_dl(Submenu* submenu, GRAPH* graph, float x, float y) {
    float tex_x;
    float tex_y;
    u8 s;
    u8 t;

    Matrix_translate(x * 16.0f, y * 16.0f, 140.0f, MTX_LOAD);
    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, ain_win_jikoku_mode);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPTileSync(POLY_OPA_DISP++);
    tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
    tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
    s = tex_x;
    t = tex_y;
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, s, t, 32, 32);
    gSPDisplayList(POLY_OPA_DISP++, ain_win_jikoku_model);

    CLOSE_POLY_OPA_DISP(graph);
}

static void mAL_set_character(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game, float x, float y) {
    // clang-format off
    // タイマーはどうしまヒ?
    static const u8 title_timer[] = { CHAR_PP_160, CHAR_PP_146, CHAR_PP_175, CHAR_PP_144, CHAR_PP_025, CHAR_PP_245, CHAR_PP_002, CHAR_PP_011, CHAR_PP_030, CHAR_PP_171, CHAR_PP_063 };
    // じこくはどうしまヒ?
    static const u8 title_time[] = { CHAR_PP_237, CHAR_PP_009, CHAR_PP_007, CHAR_PP_025, CHAR_PP_245, CHAR_PP_002, CHAR_PP_011, CHAR_PP_030, CHAR_PP_171, CHAR_PP_063 };
    // おわり
    static const u8 str_end[] = { CHAR_PP_004, CHAR_PP_193, CHAR_PP_124 };
    // あそびはじめて
    static const u8 mes1_timer[] = { CHAR_PP_000, CHAR_PP_014, CHAR_PP_247, CHAR_PP_025, CHAR_PP_237, CHAR_PP_036, CHAR_PP_018 };
    // じかん
    static const u8 mes2_timer[] = { CHAR_PP_237, CHAR_PP_005, CHAR_PP_195 };
    // ふんごに
    static const u8 mes3_timer[] = { CHAR_PP_027, CHAR_PP_195, CHAR_PP_235, CHAR_PP_021 };
    // おつたえしまヒ
    static const u8 mes4_timer[] = { CHAR_PP_004, CHAR_PP_017, CHAR_PP_015, CHAR_PP_003, CHAR_PP_011, CHAR_PP_030, CHAR_PP_171 };
    // じ
    static const u8 str_time_mes1[] = { CHAR_PP_237 };
    // ふんに
    static const u8 str_time_mes2[] = { CHAR_PP_027, CHAR_PP_195, CHAR_PP_021 };
    // おつたえしまヒ
    static const u8 str_time_mes3[] = { CHAR_PP_004, CHAR_PP_017, CHAR_PP_015, CHAR_PP_003, CHAR_PP_011, CHAR_PP_030, CHAR_PP_171 };
    // clang-format on

    mAL_Ovl_c* alarmIn_ovl = submenu->overlay->alarmIn_ovl;
    s16 digits[2][2];
    float base_x;
    float base_y;
    float mes_x;
    float mes_y;
    float mes_x2;
    float mes_y2;
    rgba_t color;

    if (menu_info->data0 == mHm_HANIWA_ALARM_MODE_ON_PLAY) {
        mFont_SetLineStrings(game, (u8*)title_timer, sizeof(title_timer), 160.0f + x + -84.0f, 120.0f - y + -42.0f, 255, 255, 255, 255,
                             FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
        mes_x = 160.0f + x + -85.0f;
        mes_y = 120.0f - y + -7.0f;
        mFont_SetLineStrings(game, (u8*)mes1_timer, sizeof(mes1_timer), mes_x, mes_y, 75, 40, 75, 255,
                             FALSE, FALSE, 0.75f, 0.75f, mFont_MODE_POLY);
        mes_x2 = mes_x + 12.0f;
        mes_y2 = mes_y + 19.0f;
        mFont_SetLineStrings(game, (u8*)mes2_timer, sizeof(mes2_timer), mes_x2, mes_y2, 75, 40, 75, 255,
                             FALSE, FALSE, 0.75f, 0.75f, mFont_MODE_POLY);
        mes_x2 = mes_x + 64.0f;
        mFont_SetLineStrings(game, (u8*)mes3_timer, sizeof(mes3_timer), mes_x2, mes_y2, 75, 40, 75, 255,
                             FALSE, FALSE, 0.75f, 0.75f, mFont_MODE_POLY);
        mes_x2 = mes_x + 104.0f;
        mFont_SetLineStrings(game, (u8*)mes4_timer, sizeof(mes4_timer), mes_x2, mes_y2, 75, 40, 75, 255,
                             FALSE, FALSE, 0.75f, 0.75f, mFont_MODE_POLY);
    } else {
        base_x = 160.0f + x;
        base_y = 120.0f - y;

        mFont_SetLineStrings(game, (u8*)title_time, sizeof(title_time), base_x + -80.0f, base_y + -42.0f, 255, 255, 255, 255,
                             FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);

        mes_x = (base_x + -85.0f) + 29.0f;
        mes_y = (base_y + -7.0f) + 17.0f;
        mFont_SetLineStrings(game, (u8*)str_time_mes1, sizeof(str_time_mes1), mes_x, mes_y, 75, 40, 75,
                             255, FALSE, FALSE, 0.75f, 0.75f, mFont_MODE_POLY);
        mes_x = (base_x + -85.0f) + 12.0f;
        mes_y = (base_y + -7.0f) + 19.0f;
        mes_x2 = (base_x + -85.0f) + 12.0f + 51.0f;
        mes_y2 = (base_y + -7.0f) + 19.0f + -2.0f;
        mFont_SetLineStrings(game, (u8*)str_time_mes2, sizeof(str_time_mes2), mes_x2, mes_y2, 75, 40, 75,
                             255, FALSE, FALSE, 0.75f, 0.75f, mFont_MODE_POLY);
        mes_x2 = (base_x + -85.0f) + 12.0f + 82.0f;
        mFont_SetLineStrings(game, (u8*)str_time_mes3, sizeof(str_time_mes3), mes_x2, mes_y2, 75, 40, 75,
                             255, FALSE, FALSE, 0.75f, 0.75f, mFont_MODE_POLY);
    }

    if (menu_info->data0 == mHm_HANIWA_ALARM_MODE_ON_PLAY) {
        static const s16 sumNumData[2] = { 1, 2 };
        static const xy_t set_pos[2] = {
            { 75.0f, 131.0f },
            { 117.0f, 131.0f },
        };
        int i;
        int digit_idx;
        s16 value;
        for (i = 0; i < mAL_IDX_NUM; i++) {
            value = alarmIn_ovl->delay_values[i];
            for (digit_idx = 0; digit_idx < 2; digit_idx++) {
                digits[i][digit_idx] = value / pow(10.0, 1 - digit_idx);
                value -= digits[i][digit_idx] * pow(10.0, 1 - digit_idx);
            }
        }

        for (i = 0; i < mAL_IDX_NUM; i++) {
            if (alarmIn_ovl->field == i) {
                color.r = 255;
                color.g = 0;
                color.b = 0;
                color.a = 255;
            } else {
                color.r = 60;
                color.g = 90;
                color.b = 255;
                color.a = 255;
            }

            for (digit_idx = 0; digit_idx < sumNumData[i]; digit_idx++) {
                u8 str[1];
                int digit_ofs = digit_idx + (2 - sumNumData[i]);

                str[0] = digits[i][digit_ofs] + '0';
                mFont_SetLineStrings(game, str, 1, x + set_pos[i].x + (digit_idx * 12) * 0.875f, -y + set_pos[i].y, color.r, color.g, color.b, color.a, FALSE, FALSE, 0.875f, 0.875f,
                                        mFont_MODE_POLY);
            }
        }
    } else {
        static const s16 sumNumData[2] = { 2, 2 };
        static const xy_t set_pos[2] = {
            { 82.0f, 129.0f },
            { 116.0f, 129.0f },
        };
        int i;
        s16 value;
        int digit_idx;
        for (i = 0; i < mAL_IDX_NUM; i++) {
            value = alarmIn_ovl->at_values[i];
            for (digit_idx = 0; digit_idx < 2; digit_idx++) {
                digits[i][digit_idx] = value / pow(10.0, 1 - digit_idx);
                value -= digits[i][digit_idx] * pow(10.0, 1 - digit_idx);
            }
        }

        for (i = 0; i < mAL_IDX_NUM; i++) {
            if (alarmIn_ovl->field == i) {
                color.r = 255;
                color.g = 0;
                color.b = 0;
                color.a = 255;
            } else {
                color.r = 60;
                color.g = 90;
                color.b = 255;
                color.a = 255;
            }

            for (digit_idx = 0; digit_idx < sumNumData[i]; digit_idx++) {
                u8 str[1];
                int digit_ofs = digit_idx + (2 - sumNumData[i]);

                str[0] = digits[i][digit_ofs] + '0';
                mFont_SetLineStrings(game, str, 1, x + set_pos[i].x + (digit_idx * 12) * 0.875f,
                    -y + set_pos[i].y, color.r, color.g, color.b, color.a, FALSE, FALSE, 0.875f, 0.875f,
                                        mFont_MODE_POLY);
            }
        }
    }

    if (alarmIn_ovl->field == mAL_IDX_NUM) {
        color.r = 255;
        color.g = 0;
        color.b = 0;
        color.a = 255;
    } else {
        color.r = 60;
        color.g = 90;
        color.b = 255;
        color.a = 255;
    }

    mes_x = 160.0f + x;
    mes_y = 120.0f - y;
    mes_x2 = mes_x + 40.0f;
    mes_y2 = mes_y + 30.0f;

    mFont_SetLineStrings(game, (u8*)str_end, sizeof(str_end), mes_x2, mes_y2, color.r, color.g, color.b, color.a, FALSE, FALSE,
                        0.785f, 0.875f, mFont_MODE_POLY);
}

static void mAL_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    float x = menu_info->position[0];
    float y = menu_info->position[1];
    GRAPH* graph = game->graph;

    mAL_set_frame_dl(submenu, graph, x, y);
    submenu->overlay->haniwaPortrait_ovl->set_haniwaPortrait_proc(submenu, menu_info, graph, game, 200.0f + x, 63.0f - menu_info->position[1]);
    submenu->overlay->set_char_matrix_proc(graph);
    mAL_set_character(submenu, menu_info, game, x, y);
}

static void mAL_alarmIn_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_ALARMIN];

    menu_info->pre_draw_func(submenu, game);
    mAL_set_dl(submenu, game, menu_info);
}

extern void mAL_alarmIn_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* control = &submenu->overlay->menu_control;

    control->menu_move_func = &mAL_alarmIn_ovl_move;
    control->menu_draw_func = &mAL_alarmIn_ovl_draw;
}

static void mAL_alarmIn_ovl_init(Submenu* submenu) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_ALARMIN];
    mAL_Ovl_c* alarmIn_ovl = submenu->overlay->alarmIn_ovl;
    mHm_hs_c* home = Save_GetPointer(homes[mHS_get_arrange_idx(Common_Get(player_no))]);

    if (menu_info->data0 == mHm_HANIWA_ALARM_MODE_ON_PLAY) {
        if (home->haniwa.alarm_info.mode == mHm_HANIWA_ALARM_MODE_ON_PLAY) {
            alarmIn_ovl->delay_values[mAL_IDX_HOUR] = home->haniwa.alarm_info.hour;
            alarmIn_ovl->delay_values[mAL_IDX_MIN] = home->haniwa.alarm_info.minute;
        } else {
            // default delay is 5 minutes
            alarmIn_ovl->delay_values[mAL_IDX_HOUR] = 0;
            alarmIn_ovl->delay_values[mAL_IDX_MIN] = 5;
        }
    } else {
        if (home->haniwa.alarm_info.mode == mHm_HANIWA_ALARM_MODE_AT_TIME) {
            alarmIn_ovl->at_values[mAL_IDX_HOUR] = home->haniwa.alarm_info.hour;
            alarmIn_ovl->at_values[mAL_IDX_MIN] = home->haniwa.alarm_info.minute;
        } else {
            // default alarm time is 3:00PM
            alarmIn_ovl->at_values[mAL_IDX_HOUR] = 15;
            alarmIn_ovl->at_values[mAL_IDX_MIN] = 0;
        }
    }

    alarmIn_ovl->field = mAL_IDX_HOUR;
    submenu->overlay->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    menu_info->move_drt = mSM_MOVE_IN_TOP;
}

extern void mAL_alarmIn_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->alarmIn_ovl == NULL) {
        mem_clear((u8*)&al_ovl_data, sizeof(al_ovl_data), 0);
        overlay->alarmIn_ovl = &al_ovl_data;
    }

    mAL_alarmIn_ovl_init(submenu);
    mAL_alarmIn_ovl_set_proc(submenu);
}

extern void mAL_alarmIn_ovl_destruct(Submenu* submenu) {
    submenu->overlay->alarmIn_ovl = NULL;
}
