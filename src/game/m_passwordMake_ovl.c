#include "m_passwordMake_ovl.h"

#include "audio.h"
#include "libultra/libultra.h"
#include "m_editor_ovl.h"
#include "m_font.h"
#include "sys_matrix.h"

mPM_Ovl_c pm_ovl_data;

const u8 mPM_moji_color[mPM_ENTRY_NUM][3] = { { 20, 0, 0 }, { 120, 100, 80 } };

static void mPM_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mPM_move_Obey(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  mPM_Ovl_c* passwordMake_ovl;
  u8* dst;

  if (submenu->overlay->menu_info[mSM_OVL_EDITOR].next_proc_status == mSM_PROCESS_END) {
      (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP); // close this submenu overlay too
      dst = (u8*)menu_info->data2;
      passwordMake_ovl = submenu->overlay->passwordMake_ovl;
      mem_copy(dst, passwordMake_ovl->town_name, LAND_NAME_SIZE);
      mem_copy(dst + LAND_NAME_SIZE, passwordMake_ovl->player_name, PLAYER_NAME_LEN);
  }
}

static void mPM_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

static void mPM_passwordMake_ovl_move(Submenu* submenu) {
  static mSM_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = {
    &mPM_move_Move,
    (mSM_MOVE_PROC)none_proc1,
    (mSM_MOVE_PROC)none_proc1,
    &mPM_move_Obey,
    &mPM_move_End
  };
  
  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_PASSWORDMAKE];

  (*menu_info->pre_move_func)(submenu);
  (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx lat_sousa_spT_model[];

static void mPM_set_space(GRAPH* graph, u8* str, int len, int color_idx, f32 x, f32 y) {
    int i;
    
    OPEN_POLY_OPA_DISP(graph);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, mPM_moji_color[color_idx][0], mPM_moji_color[color_idx][1],
                    mPM_moji_color[color_idx][2], 255);
    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 140.0f, MTX_MULT);
    for (i = 0; i < len; i++) {
        if (str[i] == CHAR_SPACE) {
            int width = mFont_GetStringWidth(str, i, FALSE);
            Matrix_push();
            Matrix_translate(width, 0.0f, 0.0f, MTX_MULT);
            Matrix_scale(0.625f, 1.0f, 1.0f, MTX_MULT);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, lat_sousa_spT_model);
            Matrix_pull();
        }
    }
    CLOSE_POLY_OPA_DISP(graph);
}

extern Gfx pas_win_mode[];
extern Gfx pas_win_model[];
extern Gfx pas_win_waku1_model[];
extern Gfx pas_win_waku2_model[];
extern Gfx pas_start_model[];

static void mPM_set_frame_dl(Submenu* submenu, GRAPH* graph, mSM_MenuInfo_c* menu_info, int sel_idx, f32 x, f32 y) {
  static u8 waku_color[mPM_ENTRY_NUM][3] = {
    { 150,  50,  30 },
    { 255, 255, 255 }
  };

  mPM_Ovl_c* passwordMake_ovl = submenu->overlay->passwordMake_ovl;
  Gfx* gfx;
  u8 s;
  u8 t;
  f32 tile_x;
  f32 tile_y;

  Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
  Matrix_translate(x, y, 140.0f, MTX_MULT);

  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  /* Setup RDP settings */
  gSPDisplayList(gfx++, pas_win_mode);

  /* Initialize position matrix */
  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

  /* Setup background tiling offset */
  tile_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
  tile_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
  s = (int)tile_x;
  t = (int)tile_y;
  gDPSetTileSize_Dolphin(gfx++, G_TX_RENDERTILE, s, t, 32, 32);

  /* Draw background */
  gSPDisplayList(gfx++, pas_win_model);

  /* Set town name border color */
  gDPSetPrimColor(gfx++, 0, 255, waku_color[sel_idx][0], waku_color[sel_idx][1], waku_color[sel_idx][2], 255);

  /* Draw town name box */
  gSPDisplayList(gfx++, pas_win_waku1_model);

  /* Set player name border color */
  gDPSetPrimColor(gfx++, 0, 255, waku_color[sel_idx ^ 1][0], waku_color[sel_idx ^ 1][1], waku_color[sel_idx ^ 1][2], 255);

  /* Draw player name box */
  gSPDisplayList(gfx++, pas_win_waku2_model);

  if (sel_idx == mPM_ENTRY_TOWN && mMl_strlen(passwordMake_ovl->town_name, LAND_NAME_SIZE, CHAR_SPACE) != 0) {
    /* If the town box is selected and isn't empty, draw the "Start Button" image */
    Matrix_translate(-3.0f, 0.0f, 140.0f, MTX_MULT);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, pas_start_model);
  }

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);
}

static void mPM_set_character(Submenu* submenu, GAME* game, int sel_idx, f32 x, f32 y) {
    static u8 title_str[] = { CHAR_PP_004, CHAR_PP_007, CHAR_PP_124, CHAR_PP_010, CHAR_PP_006,
                              CHAR_PP_194, CHAR_PP_006, CHAR_PP_036, CHAR_PP_018, CHAR_PP_023 };
    static const u8 countory_title_str[] = { CHAR_PP_035, CHAR_PP_123 };
    static const u8 person_title_str[] = { CHAR_PP_020, CHAR_PP_030, CHAR_PP_003 };
    static f32 cursol_baseX[mPM_ENTRY_NUM] = { 102.0f, 133.0f };
    static f32 cursol_baseY[mPM_ENTRY_NUM] = { 68.0f, 96.0f };
    mPM_Ovl_c* passwordMake_ovl = submenu->overlay->passwordMake_ovl;
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    int sel_idx2;
    f32 cursor_x;
    f32 cursor_y;
    mFont_SetLineStrings(game, title_str, sizeof(title_str), x + 122.0f, 32.0f - y, 255, 255, 255, 255, FALSE, FALSE,
                         1.0f, 1.0f, mFont_MODE_POLY);
    mFont_SetLineStrings(game, (u8*)countory_title_str, sizeof(countory_title_str), x + 179.0f, 70.0f - y,
                         mPM_moji_color[1][0], mPM_moji_color[1][1], mPM_moji_color[1][2], 255, FALSE, FALSE, 0.875f,
                         0.875f, mFont_MODE_POLY);
    mFont_SetLineStrings(game, (u8*)person_title_str, sizeof(person_title_str), x + 97.0f, 98.0f - y,
                         mPM_moji_color[1][0], mPM_moji_color[1][1], mPM_moji_color[1][2], 255, FALSE, FALSE, 0.875f,
                         0.875f, mFont_MODE_POLY);
    mFont_SetLineStrings(game, passwordMake_ovl->town_name, passwordMake_ovl->lengths[mPM_ENTRY_TOWN], x + 102.0f,
                         68.0f - y, mPM_moji_color[sel_idx][0], mPM_moji_color[sel_idx][1], mPM_moji_color[sel_idx][2],
                         255, FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
    mFont_SetLineStrings(game, passwordMake_ovl->player_name, passwordMake_ovl->lengths[mPM_ENTRY_PLAYER], x + 133.0f,
                         96.0f - y, mPM_moji_color[sel_idx ^ 1][0], mPM_moji_color[sel_idx ^ 1][1],
                         mPM_moji_color[sel_idx ^ 1][2], 255, FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
    sel_idx2 = passwordMake_ovl->selected_idx;
    cursor_x = (f32)editor_ovl->cursor_line_width + (x + cursol_baseX[sel_idx2]) + -7.0f;
    cursor_y = -y + cursol_baseY[sel_idx2];
    (*submenu->overlay->editor_ovl->cursol_draw)(submenu, game, cursor_x, cursor_y);
}

static void mPM_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
  f32 x = menu_info->position[0];
  f32 y = menu_info->position[1];
  mPM_Ovl_c* passwordMake_ovl = submenu->overlay->passwordMake_ovl;
  GRAPH* graph = game->graph;
  int sel_idx = passwordMake_ovl->selected_idx;

  mPM_set_frame_dl(submenu, graph, menu_info, sel_idx, x, y);
  mPM_set_space(graph, passwordMake_ovl->town_name, passwordMake_ovl->lengths[mPM_ENTRY_TOWN], sel_idx, x + -52.0f,
                y + 43.0f);
  mPM_set_space(graph, passwordMake_ovl->player_name, passwordMake_ovl->lengths[mPM_ENTRY_PLAYER], sel_idx ^ 1,
                x + -21.0f, y + 15.0f);
  (*submenu->overlay->set_char_matrix_proc)(graph);
  mPM_set_character(submenu, game, sel_idx, x, y);
}

static void mPM_passwordMake_ovl_draw(Submenu* submenu, GAME* game) {
  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_PASSWORDMAKE];

  (*menu_info->pre_draw_func)(submenu, game);
  mPM_set_dl(submenu, game, menu_info);
}

extern void mPM_passwordMake_ovl_set_proc(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  overlay->menu_control.menu_move_func = &mPM_passwordMake_ovl_move;
  overlay->menu_control.menu_draw_func = &mPM_passwordMake_ovl_draw;
}

static void mPM_passwordMake_ovl_init(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_PASSWORDMAKE];
  mPM_Ovl_c* passwordMake_ovl = overlay->passwordMake_ovl;

  overlay->menu_control.animation_flag = FALSE;
  menu_info->proc_status = mSM_OVL_PROC_MOVE;
  menu_info->next_proc_status = mSM_OVL_PROC_OBEY;
  menu_info->move_drt = mSM_MOVE_IN_TOP;

  /* Open the editor overlay on top of this submenu */
  mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_PASSWORDMAKE, 0, passwordMake_ovl->town_name, 80);
}

extern void mPM_passwordMake_ovl_construct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  if (overlay->passwordMake_ovl == NULL) {
    bzero(&pm_ovl_data, sizeof(mPM_Ovl_c));
    overlay->passwordMake_ovl = &pm_ovl_data;
    mem_clear(overlay->passwordMake_ovl->town_name, LAND_NAME_SIZE, CHAR_SPACE);
    mem_clear(overlay->passwordMake_ovl->player_name, PLAYER_NAME_LEN, CHAR_SPACE);
  }

  mPM_passwordMake_ovl_init(submenu);
  mPM_passwordMake_ovl_set_proc(submenu);
}

extern void mPM_passwordMake_ovl_destruct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  overlay->passwordMake_ovl = NULL;
}
