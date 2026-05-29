#include "m_music_ovl.h"

#include "PR/gbi.h"
#include "audio.h"
#include "graph.h"
#include "m_actor_type.h"
#include "m_field_info.h"
#include "m_home_h.h"
#include "m_lib.h"
#include "m_music_ovl_h.h"
#include "m_name_table.h"
#include "m_submenu.h"
#include "m_tag_ovl.h"
#include "m_hand_ovl.h"
#include "m_common_data.h"
#include "m_house.h"
#include "m_font.h"
#include "m_msg.h"
#include "os/OSCache.h"
#include "sys_matrix.h"
#include "m_malloc.h"
#include "m_bgm.h"

static mMU_Ovl_c music_ovl_data;

extern u32* mMU_GetNowSceneMusicRackP(void) {
    static u32 dummy_md_rack[6];

    switch (Save_Get(scene_no)) {
        case SCENE_COTTAGE_MY:
            if (Common_Get(cur_island_house_p) != NULL) {
                return Common_Get(cur_island_house_p)->island.cottage.music_box;
            }

            return dummy_md_rack;
        default:
            if (mFI_GET_ROOMTYPE() == mFI_FIELD_PLAYER0_ROOM) {
                return Save_Get(homes[mFI_GET_PLAYER_ROOM_NO(mFI_GetFieldId())]).music_box;
            }
            return dummy_md_rack;
    }
}

extern int mMU_md_rack_get(int idx) {
    int ret = FALSE;

    if (idx >= 0 && idx < MINIDISK_NUM) {
        ret = ChkMusicBox(mMU_GetNowSceneMusicRackP(), idx);
    }

    return ret;
}

extern void mMU_md_rack_set_on(int idx) {
    if (idx >= 0 && idx < MINIDISK_NUM) {
        SetMusicBox(mMU_GetNowSceneMusicRackP(), idx);
    }
}

extern void mMU_md_rack_set_off(int idx) {
    if (idx >= 0 && idx < MINIDISK_NUM) {
        ClrMusicBox(mMU_GetNowSceneMusicRackP(), idx);
    }
}

extern int mMU_csr_idx_2_md_idx(mMU_Ovl_c* music_ovl, int table_idx) {
    int ret = -1;

    if (music_ovl != NULL) {
        int idx = (table_idx >> 1) + music_ovl->current_row;

        if ((table_idx & 1) == 0) {
            ret = music_ovl->ordering[idx][0];
        } else if (music_ovl->ordering[idx][1] >= 0) {
            ret = MINIDISK_AIRCHECK_NUM + music_ovl->ordering[idx][1];
        } else {
            ret = -1;
        }
    }

    return ret;
}

extern int mMU_mark_chk(mMU_Ovl_c* music_ovl, int idx) {
    if (idx >= 0 && idx < MINIDISK_NUM) {
        if ((music_ovl->md_rack_mark[idx >> 5] & (1 << (idx & 31))) != 0) {
            return TRUE;
        }

        return FALSE;
    }

    return FALSE;
}

static void mMU_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mMU_move_disp_idx_set(mMU_Ovl_c* music_ovl) {
    int count;
    int i;
    int j;

    for (i = 0; i < MINIDISK_AIRCHECK_NUM; i++) {
        for (j = 0; j < 2; j++) {
            music_ovl->ordering[i][j] = -1;
        }
    }

    count = 0;
    for (i = 0; i < MINIDISK_AIRCHECK_NUM; i++) {
        if (mMU_md_rack_get(i) || mMU_md_rack_get(i + MINIDISK_AIRCHECK_NUM)) {
            if (mMU_md_rack_get(i)) {
                music_ovl->ordering[count][0] = i;
            }
            
            if (mMU_md_rack_get(i + MINIDISK_AIRCHECK_NUM)) {
                music_ovl->ordering[count][1] = i;
            }

            count++;
        } else {
            for (j = 0; j < 2; j++) {
                music_ovl->ordering[i][j] = -1;
            }
        }
    }

    music_ovl->rows = count;
}

static void mMU_item_name_set(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;
    int idx;
    int i;

    for (i = 0; i < mMU_ROW_NUM; i++) {
        mem_clear(music_ovl->titles[i], mIN_ITEM_NAME_LEN, CHAR_SPACE);
        idx = music_ovl->ordering[i + music_ovl->current_row][0];
        if (idx < 0) {
            idx = music_ovl->ordering[i + music_ovl->current_row][1];
        }

        if (idx >= 0) {
            mIN_copy_name_str(music_ovl->titles[i], ITM_MINIDISK_START + idx);
        }
    }
}

static void mMU_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;

    if (!menu_info->open_flag) {
        submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_MUSIC_MAIN, mTG_TYPE_NONE, music_ovl->tag_table_idx, 0.0f, 0.0f);
        submenu->overlay->hand_ovl->set_hand_func(submenu);
        submenu->overlay->hand_ovl->info.pos[0] += 4.0f;
        submenu->overlay->hand_ovl->info.pos[1] += 5.0f;
        menu_info->open_flag = TRUE;
    } else {
        submenu->overlay->menu_control.tag_move_func(submenu, menu_info);
        music_ovl->tag_table_idx = submenu->overlay->tag_ovl->get_table_idx_proc(&submenu->overlay->tag_ovl->tags[0]);
        if (music_ovl->cursor_moved) {
            mMU_move_disp_idx_set(submenu->overlay->music_ovl);
            music_ovl->cursor_moved = FALSE;
        }
    }
}

static void mMU_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* next_menu = &submenu->overlay->menu_info[menu_info->next_menu_type];
    
    if (next_menu->proc_status == mSM_OVL_PROC_MOVE && next_menu->next_proc_status == mSM_OVL_PROC_END) {
        submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
        menu_info->proc_status = mSM_OVL_PROC_PLAY;
    }
}

static void mMU_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

static void mMU_music_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[] = {
        // clang-format off
        mMU_move_Move,
        mMU_move_Play,
        mMU_move_Wait,
        (mSM_MOVE_PROC)none_proc1,
        mMU_move_End,
        // clang-format on
    };
    
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_MUSIC];
    mSM_Control_c* ctrl = &submenu->overlay->menu_control;
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
    if (menu_info->proc_status == mSM_OVL_PROC_PLAY) {
        ctrl->animation_flag = TRUE;
    } else {
        ctrl->animation_flag = FALSE;
    }

    music_ovl->_17F = (music_ovl->_17F + 1) % 30;
    if (music_ovl->_17F < 15) {
        music_ovl->alpha = (int)(255.0f * (f32)music_ovl->_17F / 15.0f);
    } else {
        music_ovl->alpha = (int)(255.0f * (f32)(30 - music_ovl->_17F) / 15.0f);
    }
}

extern Gfx mus_win_model_before[];
extern Gfx mus_win_model[];
extern Gfx mus_win_ueT_model[];
extern Gfx mus_win_ue2T_model[];
extern Gfx mus_tag_nes_model[];
extern Gfx mus_icon_model_before[];
extern Gfx mus_icon_model[];
extern Gfx mus_mark_before[];
extern Gfx mus_mark_model[];
extern Gfx mus_win_shirushi1T_model[];
extern Gfx mus_clg_win_cbT_model[];
extern Gfx mus_icon_model_before[];
extern Gfx mus_icon_model[];
extern Gfx icon_music_live2T_model_before[];
extern Gfx icon_music_live2T_model[];

static void mMU_set_title_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    static const rgba_t select = { 255, 215, 50, 255 };
    static const rgba_t unselect = { 115, 110, 70, 255 };

    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;
    const rgba_t* color_p;
    int i;
    int table_idx;
    int idx;

    submenu->overlay->set_char_matrix_proc(game->graph);
    table_idx = music_ovl->tag_table_idx >> 1;

    mMU_item_name_set(submenu, menu_info);
    for (i = 0; i < mMU_ROW_NUM; i++) {
        idx = music_ovl->ordering[i + music_ovl->current_row][0];
        if (idx < 0) {
            idx = music_ovl->ordering[i + music_ovl->current_row][1];
        }

        color_p = i == table_idx ? &select : &unselect;

        if (idx >= 0) {
            mFont_SetLineStrings(
                game,
                music_ovl->titles[i], mIN_ITEM_NAME_LEN,
                menu_info->position[0] + 79.0f, menu_info->position[1] + 56.0f + i * 20.0f,
                color_p->r, color_p->g, color_p->b, color_p->a,
                FALSE, FALSE,
                0.875f, 0.875f,
                mFont_MODE_POLY
            );
        }
    }
}

static void mMU_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;
    GRAPH* graph = game->graph;
    int k;
    u8 i;
    u8 j;
    f32 tex_x;
    f32 tex_y;
    f32 x;
    f32 y;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, mus_win_model_before);

    // apply G_TEXTURE_IMAGE_FRAC
    tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
    tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
    i = (int)tex_x;
    j = (int)tex_y;
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, i, j, 32, 32);

    gSPDisplayList(POLY_OPA_DISP++, mus_win_model);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0, 255, 255, music_ovl->alpha);

    if (music_ovl->current_row > 0) {
        // Up arrow
        Matrix_push();
        Matrix_translate(-28.0f, 74.0f, 0.0f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, mus_win_shirushi1T_model);
        Matrix_pull();
    }

    if (music_ovl->current_row + mMU_ROW_NUM < music_ovl->rows) {
        // Down arrow, rotated 180 degrees
        Matrix_push();
        Matrix_translate(-28.0f, -82.0f, 0.0f, MTX_MULT);
        Matrix_RotateZ(DEG2SHORT_ANGLE(-180.0f), MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, mus_win_shirushi1T_model);
        Matrix_pull();
    }

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(menu_info->position[0] + 20.0f, menu_info->position[1], 140.0f, MTX_MULT);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_OPA_DISP++, mus_clg_win_cbT_model);

    // Draw aircheck icons
    {
        // these might go after the gSPDisplayList macro
        x = 49.0f + menu_info->position[0];
        y = 56.0f + menu_info->position[1];

        gSPDisplayList(POLY_OPA_DISP++, mus_icon_model_before);

        Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
        Matrix_translate(x, y, 140.0f, MTX_MULT);

        for (k = 0; k < mMU_ROW_NUM; k++) {
            int idx = music_ovl->ordering[k + music_ovl->current_row][0];

            if (idx >= 0 && mMU_md_rack_get(idx)) {
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, mus_icon_model);
            }

            Matrix_translate(0.0f, -20.0f, 0.0f, MTX_MULT);
        }
    }

    // Draw live icons
    {
        x = 75.0f + menu_info->position[0];
        y = 56.0f + menu_info->position[1];

        gSPDisplayList(POLY_OPA_DISP++, icon_music_live2T_model_before);

        Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
        Matrix_translate(x, y, 140.0f, MTX_MULT);

        for (k = 0; k < mMU_ROW_NUM; k++) {
            int idx = music_ovl->ordering[k + music_ovl->current_row][1];
            
            if (idx >= 0 && mMU_md_rack_get(idx + MINIDISK_AIRCHECK_NUM)) {
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, icon_music_live2T_model);
            }

            Matrix_translate(0.0f, -20.0f, 0.0f, MTX_MULT);
        }
    }

    // Draw selection marks
    {
        int frame;

        gSPDisplayList(POLY_OPA_DISP++, mus_mark_before);

        frame = game->frame_counter % 20;
        if (frame > 10) {
            frame = 20 - frame;
        }

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0, 95 + frame * 9, 0, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, frame * 6, 210 + (frame * 9) / 2, frame * 6, 255);

        // Draw aircheck marks
        Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
        Matrix_translate(menu_info->position[0] + 49.0f, menu_info->position[1] + 56.0f, 140.0f, MTX_MULT);

        for (k = 0; k < mMU_ROW_NUM; k++) {
            s16 idx = music_ovl->ordering[k + music_ovl->current_row][0];
            if (idx >= 0 && mMU_mark_chk(music_ovl, idx)) {
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, mus_mark_model);
            }

            Matrix_translate(0.0f, -20.0f, 0.0f, MTX_MULT);
        }

        // Draw live marks
        Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
        Matrix_translate(menu_info->position[0] + 75.0f, menu_info->position[1] + 56.0f, 140.0f, MTX_MULT);

        for (k = 0; k < mMU_ROW_NUM; k++) {
            s16 idx = music_ovl->ordering[k + music_ovl->current_row][1];
            if (idx >= 0 && mMU_mark_chk(music_ovl, idx + MINIDISK_AIRCHECK_NUM)) {
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, mus_mark_model);
            }

            Matrix_translate(0.0f, -20.0f, 0.0f, MTX_MULT);
        }
    }
    
    CLOSE_POLY_OPA_DISP(graph);
}

static void mMU_music_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_MUSIC];

    menu_info->pre_draw_func(submenu, game);
    mMU_set_dl(submenu, menu_info, game);
    mMU_set_title_dl(submenu, menu_info, game);
    submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_MUSIC);
}

static void mMU_music_draw_init(mSM_MenuInfo_c* menu_info) {
    menu_info->proc_status = mSM_OVL_PROC_PLAY;
}

extern void mMU_music_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_Control_c* ctrl = &ovl->menu_control;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_MUSIC];

    ctrl->menu_move_func = mMU_music_ovl_move;
    ctrl->menu_draw_func = mMU_music_ovl_draw;
    if (ovl->hand_ovl != NULL && menu_info->next_proc_status != mSM_OVL_PROC_END) {
        submenu->overlay->hand_ovl->set_hand_func(submenu);
    }
}

static void mMU_music_ovl_init(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;
    int md_row_idx;
    mActor_name_t md_item;
    int i;
    int rows;
    int is_live;
    int md_idx;

    music_ovl->rows = 0;
    mMU_move_disp_idx_set(music_ovl);
    music_ovl->current_row = 0;
    music_ovl->tag_table_idx = 0;

    md_item = ITM_MINIDISK_START + menu_info->data0;
    if (ITEM_IS_MINIDISK(md_item)) {
        md_row_idx = -1;
        rows = 0;
        
        if (ITEM_IS_MINIDISK_AIRCHECK(md_item)) {
            md_idx = menu_info->data0;
            is_live = FALSE;
        } else {
            is_live = TRUE;
            md_idx = menu_info->data0 - MINIDISK_AIRCHECK_NUM;
        }

        for (i = 0; i < MINIDISK_AIRCHECK_NUM; i++) {
            if (mMU_md_rack_get(i) || mMU_md_rack_get(i + MINIDISK_AIRCHECK_NUM)) {
                if (i == md_idx) {
                    md_row_idx = rows;
                    break;
                }

                rows++;
            }
        }

        if (md_row_idx != -1) {
            if (music_ovl->rows < mMU_ROW_NUM) {
                music_ovl->current_row = 0;
            } else if (md_row_idx < 3) {
                music_ovl->current_row = 0;
            } else if (md_row_idx > music_ovl->rows - 4) {
                music_ovl->current_row = music_ovl->rows - mMU_ROW_NUM;
            } else {
                music_ovl->current_row = md_row_idx - 3;
            }

            music_ovl->tag_table_idx = is_live + (md_row_idx - music_ovl->current_row) * mMU_COL_NUM;
        }
    }

    submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_IN_LEFT);
}

extern void mMU_music_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_MUSIC];

    if (ovl->music_ovl == NULL) {
        mem_clear((u8*)&music_ovl_data, sizeof(music_ovl_data), 0);
        ovl->music_ovl = &music_ovl_data;
        mMU_music_draw_init(menu_info);
    }

    mMU_music_ovl_init(submenu, menu_info);
    mMU_music_ovl_set_proc(submenu);
}

extern void mMU_music_ovl_destruct(Submenu* submenu) {
    submenu->overlay->music_ovl = NULL;
}
