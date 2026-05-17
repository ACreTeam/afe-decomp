#include "m_bank_ovl.h"

#include "m_name_table.h"
#include "audio.h"
#include "sys_matrix.h"
#include "m_font.h"
#include "m_lib.h"
#include "m_common_data.h"

static int aNSM_sack_amount[MONEY_NUM] = { 100, 1000, 10000, 30000 };

static mActor_name_t aNSM_itemNo[MONEY_NUM] = { ITM_MONEY_100, ITM_MONEY_1000, ITM_MONEY_10000, ITM_MONEY_30000 };

static void mBN_now_bell_2_bell(mBN_Ovl_c* bank_ovl) {
    int diff = bank_ovl->now_bell - bank_ovl->player_bell;
    bank_ovl->bell = ABS(diff);
}

static int mBN_cursol_2_keta(int cursol) {
    int keta = 1;

    while (cursol++ < mBN_CURSOL_MAX) {
        keta *= 10;
    }

    return keta;
}

static int mBN_total_item_bell() {
    int i;
    int total_item_bell = 0;

    for (i = 0; i < MONEY_NUM; i++) {
        int possess = mPr_GetPossessionItemSumWithCond(Now_Private, aNSM_itemNo[i], mPr_ITEM_COND_NORMAL);

        total_item_bell += possess * aNSM_sack_amount[i];
    }

    return total_item_bell;
}

static void mBN_bank_ok(Submenu* submenu, mSM_MenuInfo_c* menu, mBN_Ovl_c* bank_ovl) {
    int total_item_bell;
    int remain_item_bell;
    int sack_idx;
    int i;

    if (bank_ovl->bank_bell < 0) {
        bank_ovl->bank_bell = 0;
    }

    if (bank_ovl->bank_bell > mBN_DEPOSIT_MAX) {
        bank_ovl->bank_bell = mBN_DEPOSIT_MAX;
    }

    Now_Private->bank_account = bank_ovl->bank_bell;

    total_item_bell = mBN_total_item_bell();
    i = 0;

    /* Replace all money sack items with EMPTY_NO */
    while (bank_ovl->now_bell < total_item_bell && i < MONEY_NUM) {
        sack_idx =
            mPr_GetPossessionItemIdxWithCond(Now_Private, aNSM_itemNo[i], mPr_ITEM_COND_NORMAL);
        if (sack_idx == -1) {
            i++; /* move onto next sack amount */
        } else {
            mPr_SetPossessionItem(Now_Private, sack_idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
        }

        total_item_bell = mBN_total_item_bell(); /* update total bell count in sacks */
    }
    
    /* Replace non-30k bell bags with 30k bell bags */
    remain_item_bell = bank_ovl->now_bell - mBN_total_item_bell();
    i = 0;

    while (remain_item_bell > mPr_WALLET_MAX && i < MONEY_NUM - 1) {
        sack_idx =
            mPr_GetPossessionItemIdxWithCond(Now_Private, aNSM_itemNo[i], mPr_ITEM_COND_NORMAL);

        if (sack_idx == -1) {
            i++;
        } else {
            mPr_SetPossessionItem(Now_Private, sack_idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
            remain_item_bell -= 30000 - aNSM_sack_amount[i];
        }
    }

    /* Add 30k bell bags to the inventory where empty spaces are */
    i = 0;
    while (remain_item_bell > mPr_WALLET_MAX && i < 1) {
        int sack_idx = mPr_GetPossessionItemIdxWithCond(Now_Private, EMPTY_NO, mPr_ITEM_COND_NORMAL);

        if (sack_idx == -1) {
            i++;
        } else {
            mPr_SetPossessionItem(Now_Private, sack_idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
            remain_item_bell -= 30000;
        }
    }

    total_item_bell = bank_ovl->now_bell;
    total_item_bell -= mBN_total_item_bell();

    if (total_item_bell < 0) {
        total_item_bell = 0;
    } else if (total_item_bell > mPr_WALLET_MAX) {
        total_item_bell = mPr_WALLET_MAX;
    }

    Now_Private->inventory.wallet = total_item_bell;
    (*submenu->overlay->move_chg_base_proc)(menu, mSM_MOVE_OUT_TOP);
    sAdo_SysTrgStart(NA_SE_MENU_EXIT);
}

static void mBN_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu) {
    (*submenu->overlay->move_Move_proc)(submenu, menu);
}

static void mBN_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    int trigger = overlay->menu_control.trigger;
    mBN_Ovl_c* bank_ovl = overlay->bank_ovl;

    if (trigger & BUTTON_B) {
        (*overlay->move_chg_base_proc)(menu, mSM_MOVE_OUT_TOP);
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    } else if (trigger & BUTTON_START) {
        mBN_bank_ok(submenu, menu, bank_ovl);
    } else {
        int cursol = bank_ovl->cursol;

        if (cursol == mBN_CUSROL_OK) {
            if (trigger & BUTTON_A) {
                mBN_bank_ok(submenu, menu, bank_ovl);
            } else if (trigger & (BUTTON_CLEFT | BUTTON_CUP)) {
                bank_ovl->cursol = cursol - 1;
                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
        } else if ((trigger & BUTTON_CLEFT) && cursol > 0) {
            bank_ovl->cursol = cursol - 1;
            sAdo_SysTrgStart(NA_SE_CURSOL);
        } else if (trigger & BUTTON_CRIGHT) {
            bank_ovl->cursol += 1;
            sAdo_SysTrgStart(NA_SE_CURSOL);
        } else if ((trigger & BUTTON_CDOWN) || (trigger & BUTTON_CUP)) {
            int keta = mBN_cursol_2_keta(cursol);

            if (trigger & BUTTON_CUP) {
                if (bank_ovl->now_bell < keta) {
                    keta = bank_ovl->now_bell;
                }

                if (keta + bank_ovl->bank_bell > mBN_DEPOSIT_MAX) {
                    keta = mBN_DEPOSIT_MAX - bank_ovl->bank_bell;
                }

                if (keta == 0) {
                    sAdo_SysTrgStart(MONO(3));
                    return;
                }

                if (bank_ovl->now_bell > bank_ovl->player_bell && (bank_ovl->now_bell - keta) < bank_ovl->player_bell) {
                    keta = bank_ovl->now_bell - bank_ovl->player_bell;
                }

                bank_ovl->bank_bell += keta;
                bank_ovl->now_bell -= keta;
            } else {
                if (bank_ovl->bank_bell < keta) {
                    keta = bank_ovl->bank_bell;
                }

                if ((bank_ovl->now_bell + keta) > bank_ovl->player_max_bell) {
                    keta = bank_ovl->player_max_bell - bank_ovl->now_bell;
                }

                if (keta == 0) {
                    sAdo_SysTrgStart(MONO(3));
                    return;
                }

                if (bank_ovl->now_bell < bank_ovl->player_bell && (bank_ovl->now_bell + keta) > bank_ovl->player_bell) {
                    keta = bank_ovl->player_bell - bank_ovl->now_bell;
                }

                bank_ovl->bank_bell -= keta;
                bank_ovl->now_bell += keta;
            }

            mBN_now_bell_2_bell(bank_ovl);
            sAdo_SysTrgStart(0x426);
        }
    }
}

static void mBN_move_End(Submenu* submenu, mSM_MenuInfo_c* menu) {
    (*submenu->overlay->move_End_proc)(submenu, menu);
}

static void mBN_bank_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[5] = {
        &mBN_move_Move, &mBN_move_Play, (mSM_MOVE_PROC)&none_proc1, (mSM_MOVE_PROC)&none_proc1, &mBN_move_End,
    };

    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu = &overlay->menu_info[mSM_OVL_BANK];

    (*menu->pre_move_func)(submenu);
    (*ovl_move_proc[menu->proc_status])(submenu, menu);
}

extern Gfx tyo_win_mode[];
extern Gfx tyo_win_model[];
extern Gfx tyo_win_moji2T_model[];
extern Gfx tyo_win_moji3T_model[];
extern Gfx bank_model_before[];
extern Gfx tyo_win_w1T_model[];
extern Gfx tyo_win_w2T_model[];
extern Gfx tyo_win_w3T_model[];
extern Gfx tyo_win_w4T_model[];
extern Gfx tyo_win_w5T_model[];
extern Gfx tyo_win_w6T_model[];
extern Gfx tyo_win_w7T_model[];
extern Gfx tyo_win_w8T_model[];
extern Gfx tyo_win_w9T_model[];
extern Gfx tyo_win_w10T_model[];
extern Gfx tyo_win_wakuT_model[];
extern Gfx tyo_win_fukiT_model[];
extern Gfx tyo_win_iconT_model[];
extern Gfx tyo_win_moji1_model[];

static void mBN_set_frame_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    GRAPH* g = game->graph;
    mBN_Ovl_c* bank_ovl = submenu->overlay->bank_ovl;
    u8 s;
    u8 t;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(menu->position[0], menu->position[1], 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(g);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(g), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, bank_model_before);
    s = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
    t = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, 0, s, t, 32, 32);

    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w1T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w2T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w3T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w4T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w5T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w6T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w7T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w8T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w9T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_w10T_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_wakuT_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_fukiT_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_iconT_model);
    gSPDisplayList(POLY_OPA_DISP++, tyo_win_moji1_model);

    if (bank_ovl->now_bell <= bank_ovl->player_bell) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 165, 50, 50, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 100, 80, 80, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 165, 155, 155, 255);
    }

    gSPDisplayList(POLY_OPA_DISP++, tyo_win_moji2T_model);

    if (bank_ovl->now_bell >= bank_ovl->player_bell) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 20, 205, 20, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 70, 95, 70, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 155, 165, 155, 255);
    }

    gSPDisplayList(POLY_OPA_DISP++, tyo_win_moji3T_model);

    CLOSE_POLY_OPA_DISP(g);
}

static void mBN_set_num_str(f32 x, f32 y, GAME* game, u32 num, f32 scale, rgba_t* color) {
    u8 str[9];
    f32 width;

    mFont_UnintToString(str, 9, num, 9, FALSE, FALSE, FALSE);
    width = mFont_GetStringWidth(str, 9, TRUE);
    x -= scale * width;

    mFont_SetLineStrings(game, str, 9, x, y, color->r, color->g, color->b, 255, FALSE, FALSE, scale, scale,
                         mFont_MODE_POLY);
}

static void mBN_set_character_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    static u8 kingaku_str[] = { CHAR_PP_006, CHAR_PP_195, CHAR_PP_231, CHAR_PP_007, CHAR_PP_194, CHAR_PP_001,
                                CHAR_PP_126, CHAR_PP_018, CHAR_PP_023 };
    static u8 end_str[] = { CHAR_PP_004, CHAR_PP_193, CHAR_PP_124 };
    static rgba_t normal_col = { 0, 50, 255, 255 };
    static rgba_t select_col = { 195, 20, 20, 255 };
    static rgba_t bank_bell_col = { 170, 60, 145, 255 };
    static rgba_t now_bell_col = { 115, 50, 215, 255 };

    mBN_Ovl_c* bank_ovl;
    int cursol;
    f32 width;
    f32 digit_x;
    int i;
    u8 str[6];
    f32 pos_x = menu->position[0];
    f32 pos_y = menu->position[1];

    bank_ovl = submenu->overlay->bank_ovl;

    (*submenu->overlay->set_char_matrix_proc)(game->graph);
    mFont_SetLineStrings(game, kingaku_str, sizeof(kingaku_str), 134.0f + pos_x, 66.0f - pos_y, 255, 255, 255, 255,
                         FALSE, FALSE, 0.9375f, 0.9375f, mFont_MODE_POLY);

    mBN_set_num_str(227.5f + pos_x, 157.0f - pos_y, game, bank_ovl->bank_bell, 0.875f, &bank_bell_col);
    mBN_set_num_str(229.0f + pos_x, 98.0f - pos_y, game, bank_ovl->now_bell, 0.875f, &now_bell_col);

    cursol = bank_ovl->cursol;
    mFont_UnintToString(str, 6, bank_ovl->bell, 6, FALSE, TRUE, FALSE);
    width = mFont_GetStringWidth(str, 6, TRUE);

    /* Draw each digit one by one */
    digit_x = 229.0f + (pos_x - width);
    for (i = 0; i < 6; i++) {
        rgba_t* color = cursol == i ? &select_col : &normal_col;

        mFont_SetLineStrings(game, str + i, 1, digit_x, 124.0f - pos_y, color->r, color->g, color->b, 255, FALSE, FALSE,
                             1.0f, 1.0f, mFont_MODE_POLY);

        width = mFont_GetStringWidth(str + i, 1, TRUE);
        digit_x += width;
    }

    {
        rgba_t* color = bank_ovl->cursol < mBN_CUSROL_OK ? &normal_col : &select_col;

        mFont_SetLineStrings(game, end_str, sizeof(end_str), 221.5f + pos_x, 139.0f - pos_y, color->r, color->g,
                             color->b, 255, FALSE, FALSE, 0.875f, 0.875f, mFont_MODE_POLY);
    }
}

static void mBN_bank_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu = &submenu->overlay->menu_info[mSM_OVL_BANK];

    (*menu->pre_draw_func)(submenu, game);
    mBN_set_frame_dl(submenu, game, menu);
    mBN_set_character_dl(submenu, game, menu);
}

extern void mBN_bank_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->menu_control.menu_move_func = &mBN_bank_ovl_move;
    overlay->menu_control.menu_draw_func = &mBN_bank_ovl_draw;
}

static void mBN_bank_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mBN_Ovl_c* bank_ovl = overlay->bank_ovl;
    int i;

    overlay->menu_control.animation_flag = FALSE;
    overlay->menu_info[mSM_OVL_BANK].proc_status = 0;
    overlay->menu_info[mSM_OVL_BANK].next_proc_status = 1;
    overlay->menu_info[mSM_OVL_BANK].move_drt = 5;

    bank_ovl->now_bell = Now_Private->inventory.wallet;
    bank_ovl->now_bell += mBN_total_item_bell();
    bank_ovl->player_bell = bank_ovl->now_bell;

    mBN_now_bell_2_bell(bank_ovl);
    bank_ovl->player_max_bell = mPr_WALLET_MAX;

    for (i = 0; i < MONEY_NUM; i++) {
        int sack_sum = mPr_GetPossessionItemSumWithCond(Now_Private, aNSM_itemNo[i], mPr_ITEM_COND_NORMAL);

        bank_ovl->player_max_bell += sack_sum * aNSM_sack_amount[3];
    }

    {
        int sack_sum = mPr_GetPossessionItemSumWithCond(Now_Private, EMPTY_NO, mPr_ITEM_COND_NORMAL);

        bank_ovl->player_max_bell += sack_sum * aNSM_sack_amount[3];
    }
    bank_ovl->bank_bell = Now_Private->bank_account;
    bank_ovl->cursol = 0;
}

static mBN_Ovl_c bn_ovl_data;

extern void mBN_bank_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->bank_ovl == NULL) {
        mem_clear((u8*)&bn_ovl_data, sizeof(mBN_Ovl_c), 0);
        overlay->bank_ovl = &bn_ovl_data;
    }

    mBN_bank_ovl_init(submenu);
    mBN_bank_ovl_set_proc(submenu);
}

extern void mBN_bank_ovl_destruct(Submenu* submenu) {
    submenu->overlay->bank_ovl = NULL;
}
