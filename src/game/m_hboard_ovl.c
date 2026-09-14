#include "m_hboard_ovl.h"

#include "m_common_data.h"
#include "m_editor_ovl.h"
#include "m_font.h"
#include "m_text.h"
#include "m_haniwaPortrait_ovl.h"
#include "sys_matrix.h"

static void mHB_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mHB_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  if (submenu->overlay->menu_info[mSM_OVL_EDITOR].next_proc_status == mSM_OVL_PROC_END) {
    (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
  }
}

static void mHB_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

static void mHB_hboard_ovl_move(Submenu* submenu) {
  static mSM_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = {
    &mHB_move_Move,
    (mSM_MOVE_PROC)&none_proc1,
    &mHB_move_Wait,
    (mSM_MOVE_PROC)&none_proc1,
    &mHB_move_End
  };

  mSM_Control_c* control = &submenu->overlay->menu_control;
  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_HBOARD];

  (*menu_info->pre_move_func)(submenu);
  (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);

  switch (menu_info->proc_status) {
    case mSM_OVL_PROC_WAIT:
    {
      (*submenu->overlay->haniwaPortrait_ovl->haniwaPortrait_shape_move_proc)(submenu);
      control->animation_flag = TRUE;
      break;
    }

    case mSM_OVL_PROC_MOVE:
    {
      control->animation_flag = FALSE;
      break;
    }
  }
}

extern Gfx hni_den_model[];

static void mHB_set_frame_dl(GRAPH* graph, mSM_MenuInfo_c* menu_info, f32 x, f32 y) {
  Gfx* gfx;
  
  Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
  Matrix_translate(x, y, 140.0f, MTX_MULT);
  
  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  /* Setup matrix */
  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

  /* Draw background frame */
  gSPDisplayList(gfx++, hni_den_model);

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);
}

static void mHB_set_character(mED_Ovl_c* editor_ovl, GAME* game, f32 x, f32 y, f32* endCode_x, f32* endCode_y) {
    u16* str = editor_ovl->input_wstr;
    int i;
    int remaining = editor_ovl->now_str_len;
    for (i = 0; i < mHB_LINE_NUM; i++) {
        int len;
        int newline = FALSE;
        len = 0;
        while (len < mHB_LINE_WIDTH_MAX / 12 && len < remaining) {
            if (str[len] == CHAR_NEW_LINE) {
                newline = TRUE;
                len++;
                break;
            }
            len++;
        }
        if (len != 0) {
            mFont_SetLineStringsW(game, str, len, x, y, 90, 10, 130, 255, FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
            remaining -= len;
            str += len;
            if (remaining == 0) {
                if (i != mHB_LINE_NUM - 1 && (newline || len == mHB_LINE_WIDTH_MAX / 12)) {
                    *endCode_x = x - 160.0f;
                    *endCode_y = 120.0f - (y + 16.0f);
                } else {
                    *endCode_x = (x + len * 12.0f) - 160.0f;
                    *endCode_y = 120.0f - y;
                }
            }
        }
        y += 16.0f;
    }
}

static void mHB_set_dl_sub(Submenu* submenu, GRAPH* graph, GAME* game, f32 x, f32 y) {
  mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
  f32 endCode_x;
  f32 endCode_y;

  (*submenu->overlay->set_char_matrix_proc)(graph);

  x =  x + 46.0f;
  y = -y + 54.0f;
  endCode_x =  x - 160.0f;
  endCode_y = -y + 120.0f;

  /* Draw text */
  mHB_set_character(editor_ovl, game, x, y, &endCode_x, &endCode_y);

  if (editor_ovl != NULL) {
    /* Draw editor cursor */
    (*submenu->overlay->editor_ovl->cursol_draw)(submenu, game, x + editor_ovl->cursor_line_width + -7.0f, y + editor_ovl->cursor_row * 16.0f);
    
    /* Draw end code */
    (*submenu->overlay->editor_ovl->end_code_draw)(submenu, game, endCode_x, endCode_y);
  }
}

static void mHB_set_dl(Submenu* submenu, GRAPH* graph, GAME* game, mSM_MenuInfo_c* menu_info) {
  f32 x = menu_info->position[0];
  f32 y = menu_info->position[1];

  /* Draw background frame */
  mHB_set_frame_dl(graph, menu_info, x, y);

  /* Draw haniwa */
  (*submenu->overlay->haniwaPortrait_ovl->set_haniwaPortrait_proc)(submenu, menu_info, graph, game, x + 230.0f, -y + 6.0f);

  if (submenu->overlay->editor_ovl != NULL) {
    /* Draw text, cursor, & end code */
    mHB_set_dl_sub(submenu, graph, game, x, y);
  }
}

static void mHB_hboard_ovl_draw(Submenu* submenu, GAME* game) {
  GRAPH* graph = game->graph;
  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_HBOARD];

  (*menu_info->pre_draw_func)(submenu, game);
  mHB_set_dl(submenu, graph, game, menu_info);
}

extern void mHB_hboard_ovl_set_proc(Submenu* submenu) {
  mSM_Control_c* control = &submenu->overlay->menu_control;

  control->menu_move_func = &mHB_hboard_ovl_move;
  control->menu_draw_func = &mHB_hboard_ovl_draw;
}

static void mHB_hboard_ovl_init(Submenu* submenu) {
  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_HBOARD];

  submenu->overlay->menu_control.animation_flag = FALSE;
  menu_info->proc_status = mSM_OVL_PROC_MOVE;
  menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
  menu_info->move_drt = mSM_MOVE_IN_TOP;

  {
      u16* str = (u16*)mTxt_get_first_buff();
      mTxt_conv_16bit(Save_Get(homes[menu_info->data1].haniwa.message), str, 64);
      mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_HBOARD, 16, (u8*)str, mHB_LINE_WIDTH_MAX);
      submenu->overlay->hboard_home_idx = menu_info->data1;
  }
}

extern void mHB_hboard_ovl_construct(Submenu* submenu) {
  if (submenu->overlay->hboard_exists == FALSE) {
    submenu->overlay->hboard_exists = TRUE;
  }

  mHB_hboard_ovl_init(submenu);
  mHB_hboard_ovl_set_proc(submenu);
}

extern void mHB_hboard_ovl_destruct(Submenu* submenu) {
    u16* str = (u16*)mTxt_get_first_buff();
    mTxt_conv_9or8bit(str, Save_Get(homes[submenu->overlay->hboard_home_idx].haniwa.message), 64);
    submenu->overlay->hboard_exists = FALSE;
}
