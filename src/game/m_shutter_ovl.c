#include "m_shutter_ovl.h"
#include "m_submenu_ovl.h"
#include "m_bgm.h"
#include "sys_matrix.h"
#include "audio.h"

static mST_Ovl_c st_ovl_data;

static void mST_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mST_Ovl_c* shutter_ovl = submenu->overlay->shutter_ovl;
    u32 timer = shutter_ovl->timer;

    if (shutter_ovl->state != 1) {
        timer += 0x830;

        if (timer > 0x8000) {
            menu_info->proc_status = menu_info->next_proc_status;
            timer = 0x8000;
        } else if (shutter_ovl->state == 0 && timer >= 0x4000) {
            shutter_ovl->state = 1;
            timer = 0x4000;
        }
    } else {
        shutter_ovl->state_timer--;
        if (shutter_ovl->state_timer <= 0) {
            shutter_ovl->state = 2;
        }
    }

    shutter_ovl->timer = timer;
}

static void mST_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mST_Ovl_c* shutter_ovl = submenu->overlay->shutter_ovl;

    if (shutter_ovl->capture_flag_set == FALSE) {
        shutter_ovl->capture_flag_timer--;
        if (shutter_ovl->capture_flag_timer <= 0) {
            u32 cur_mode;

            shutter_ovl->capture_flag_set = TRUE;
            cur_mode = submenu->capture_display_mode;
            mSM_open_submenu(submenu, mSM_OVL_FILM, 0, -1);
            submenu->capture_display_mode = cur_mode;
            menu_info->proc_status = mSM_OVL_PROC_WAIT;
        }
    }
}

static void mST_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* film_menu_info = &submenu->overlay->menu_info[mSM_OVL_FILM];

    if (film_menu_info->next_proc_status == mSM_OVL_PROC_END) {
        menu_info->proc_status = mSM_OVL_PROC_END;
    }
}

static void mST_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
    mBGMPsComp_pause(mBGM_PAUSE_STOP);
}

static void mST_shutter_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[] = {
        mST_move_Move,
        mST_move_Play,
        mST_move_Wait,
        (mSM_MOVE_PROC)none_proc1,
        mST_move_End,
    };

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_SHUTTER];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx ef_shutter_mode[];
extern Gfx ef_shutter_model[];

void mST_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    mST_Ovl_c* shutter_ovl = submenu->overlay->shutter_ovl;
    GRAPH* graph;
    float pos_x;
    float pos_y;
    s16 rot_ofs;
    float sin;
    int i;
    s16 rot;

    graph = game->graph;
    pos_x = menu_info->position[0];
    pos_y = menu_info->position[1];
    sin = sin_s(shutter_ovl->timer);
    rot = (s16)(sin * DEG2SHORT_ANGLE3(45.0f));
    
    OPEN_POLY_OPA_DISP(graph);
    
    gSPDisplayList(POLY_OPA_DISP++, ef_shutter_mode);
    
    rot_ofs = 0;
    for (i = 0; i < 8; i++) {
        Matrix_RotateZ(rot_ofs + rot, MTX_LOAD);
        Matrix_scale(16.0f, 16.0f, 1.0f, MTX_MULT);
        Matrix_translate(pos_x + (1.0f - sin) * 240.0f, pos_y, 140.0f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, ef_shutter_model);
        rot_ofs += DEG2SHORT_ANGLE2(45.0f);
    }
    
    CLOSE_POLY_OPA_DISP(graph);
}

static void mST_shutter_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_SHUTTER];

    menu_info->pre_draw_func(submenu, game);
    mST_set_dl(submenu, game, menu_info);
}

extern void mST_shutter_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* ctrl = &submenu->overlay->menu_control;

    ctrl->menu_move_func = mST_shutter_ovl_move;
    ctrl->menu_draw_func = mST_shutter_ovl_draw;
}

static void mST_shutter_ovl_init(Submenu* submenu) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_SHUTTER];
    mST_Ovl_c* shutter_ovl = submenu->overlay->shutter_ovl;

    submenu->overlay->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    shutter_ovl->timer = 0;
    shutter_ovl->capture_flag_set = FALSE;
    shutter_ovl->capture_flag_timer = 40;
    shutter_ovl->state = 0;
    shutter_ovl->state_timer = 8;
    sAdo_SysTrgStart(0x46B);
    mBGMPsComp_pause(mBGM_PAUSE_1);
}

extern void mST_shutter_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->shutter_ovl == NULL) {
        mem_clear((u8*)&st_ovl_data, sizeof(mST_Ovl_c), 0);
        overlay->shutter_ovl = &st_ovl_data;
    }

    mST_shutter_ovl_init(submenu);
    mST_shutter_ovl_set_proc(submenu);
}

extern void mST_shutter_ovl_destruct(Submenu* submenu) {
    submenu->overlay->shutter_ovl = NULL;
}
