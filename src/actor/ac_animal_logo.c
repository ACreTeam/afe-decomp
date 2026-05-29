#include "ac_animal_logo.h"

#include "m_common_data.h"
#include "m_malloc.h"
#include "m_event.h"
#include "m_play.h"
#include "m_bgm.h"
#include "m_npc.h"
#include "libc64/qrand.h"
#include "m_name_table.h"
#include "padmgr.h"
#include "audio.h"
#include "Famicom/famicom.h"
#include "m_land.h"
#include "m_titledemo.h"
#include "m_card.h"
#include "m_rcp.h"
#include "m_cpak.h"
#include "sys_matrix.h"
#include "m_time.h"
#include "m_font.h"
#include "libultra/libultra.h"
#include "m_flashrom.h"

#define G_CC_TITLE PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0
#define G_CC_TM 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0
#define G_CC_BACK 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define G_CC_PRESS_START PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0

#define TITLE_WIDTH 64
#define TITLE_HEIGHT 16

#define aAL_IN_FRAMES 121.0f

extern u8 log_win_logo3_tex[];
extern u8 log_win_logo4_tex[];
extern u8 log_win_logo5_tex[];

enum {
    aAL_LOGO_TYPE_DO,
    aAL_LOGO_TYPE_U,
    aAL_LOGO_TYPE_BU,
    aAL_LOGO_TYPE_TU,
    aAL_LOGO_TYPE_NO,
    aAL_LOGO_TYPE_MORI,
    aAL_LOGO_TYPE_MORI_E,

    aAL_LOGO_TYPE_NUM
};

static const u32 aAL_logo_str_env_r[mTD_TITLE_DEMO_NUM] = { 20, 70, 0, 80, 90 };
static const u32 aAL_logo_str_env_g[mTD_TITLE_DEMO_NUM] = { 80, 60, 70, 40, 30 };
static const u32 aAL_logo_str_env_b[mTD_TITLE_DEMO_NUM] = { 0, 120, 120, 100, 40 };

static const u32 aAL_logo_squ_prim_r[mTD_TITLE_DEMO_NUM] = { 180, 210, 150, 240, 255 };
static const u32 aAL_logo_squ_prim_g[mTD_TITLE_DEMO_NUM] = { 255, 180, 240, 160, 140 };
static const u32 aAL_logo_squ_prim_b[mTD_TITLE_DEMO_NUM] = { 90, 255, 255, 255, 120 };

static const u32 aAL_logo_squ_env_r[mTD_TITLE_DEMO_NUM] = { 120, 180, 100, 200, 240};
static const u32 aAL_logo_squ_env_g[mTD_TITLE_DEMO_NUM] = { 200, 150, 180, 120, 120 };
static const u32 aAL_logo_squ_env_b[mTD_TITLE_DEMO_NUM] = { 60, 230, 230, 230, 120 };

static void aAL_actor_ct(ACTOR* actor, GAME* game);
static void aAL_actor_dt(ACTOR* actor, GAME* game);
static void aAL_actor_move(ACTOR* actor, GAME* game);
static void aAL_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Animal_Logo_Profile = {
    mAc_PROFILE_ANIMAL_LOGO,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(ANIMAL_LOGO_ACTOR),
    &aAL_actor_ct,
    &aAL_actor_dt,
    &aAL_actor_move,
    &aAL_actor_draw,
    NULL,
};
// clang-format on

static void flash_rom_and_player_info_clear();
static int decide_next_scene_no();
static void title_action_data_init_start_select(GAME_PLAY* play);

#include "../src/actor/ac_animal_logo_misc.c"

static void aAL_setupAction(ANIMAL_LOGO_ACTOR* actor, GAME* game, int action);
static void aAL_title_decide_p_sel_npc();

static void aAL_actor_ct(ACTOR* actor, GAME* game) {
    ANIMAL_LOGO_ACTOR* logo_actor = (ANIMAL_LOGO_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (CLIP(animal_logo_clip) == NULL) {
        CLIP(animal_logo_clip) = (aAL_Clip_c*)zelda_malloc(sizeof(aAL_Clip_c));
        CLIP(animal_logo_clip)->data_init_proc = &title_action_data_init_start_select;
    }

    aAL_setupAction(logo_actor, (GAME*)play, aAL_ACTION_E_PLUS_RIGHT_MOVE_START_WAIT);
}

static void aAL_actor_dt(ACTOR* actor, GAME* game) {
    ANIMAL_LOGO_ACTOR* logo_actor = (ANIMAL_LOGO_ACTOR*)actor;

    if (CLIP(animal_logo_clip) != NULL) {
        zelda_free(CLIP(animal_logo_clip));
        CLIP(animal_logo_clip) = NULL;
    }

    if (mEv_CheckTitleDemo() != mEv_TITLEDEMO_LOGO) {
        mEv_SetTitleDemo(mEv_TITLEDEMO_NONE);
    }

    if (mFRm_CheckSaveData() == TRUE) {
        aAL_title_decide_p_sel_npc();
    }
}

static void aAL_none_proc1(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    // do nothing
}

static void aAL_title_game_data_init_start_select(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    play->fb_fade_type = FADE_TYPE_SELECT;
    play->fb_wipe_type = WIPE_TYPE_FADE_BLACK;
    Common_Set(transition.wipe_type, WIPE_TYPE_FADE_BLACK);
    mBGMPsComp_make_ps_wipe(0x1168);
}

static void aAL_title_decide_p_sel_npc() {
    int selected;
    mActor_name_t npc_name;
    int idx;

    while (TRUE) {
        selected = (int)(fqrand() * (f32)ANIMAL_NUM_MAX);
        if (mNpc_CheckFreeAnimalPersonalID(Save_GetPointer(animals[selected].id)) == FALSE) {
            npc_name = Save_Get(animals[selected].id.npc_id);
            break;
        }
    }

    idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_name, ANIMAL_NUM_MAX);
    mNpc_RegistEventNpc(SP_NPC_P_SEL2, npc_name, npc_name, Save_Get(animals[idx].cloth));
}

static int aAL_wipe_end_check(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int res = FALSE;
    fbdemo_wipe* wipe = &play->fbdemo_wipe;

    if ((*wipe->wipe_procs.isfinished_proc)(&wipe->wipe_data)) {
        res = TRUE;
    }

    return res;
}

static int aAL_chk_start_key() {
    int res = FALSE;

    if (padmgr_isConnectedController(PAD0) && ((gamePT->pads[PAD0].on.button & BUTTON_START) == BUTTON_START ||
                                               (gamePT->pads[PAD0].on.button & BUTTON_A) == BUTTON_A)) {
        res = TRUE;
    }

    return res;
}

static int aAL_chk_start_key2(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    int res = FALSE;

    if (aAL_chk_start_key() == TRUE) {
        aAL_setupAction(actor, game, aAL_ACTION_START_KEY_CHK_START_WAIT);
        res = TRUE;
    }

    return res;
}

static void aAL_logo_rotate_proc(ANIMAL_LOGO_ACTOR* actor) {
    static const float spd_add[] = { 0.307f, 0.307f, 0.307f, 0.307f, 0.307f, 0.132f };
    float* rotation = actor->rotation;
    float* rotation_speed = actor->rotation_speed;
    int logo_piece_count = actor->logo_piece_count;
    int i;

    for (i = 0; i < logo_piece_count; i++) {
        if (*rotation < 0.0f) {
            chase_f(rotation_speed, 1.0f, spd_add[i]);
            *rotation += *rotation_speed;
            if (*rotation > 0.0f) {
                *rotation = 0.0f;
            }
        }

        rotation++;
        rotation_speed++;
    }
}

static int aAL_move_right_e_plus(ANIMAL_LOGO_ACTOR* actor) {
    int finished = FALSE;

    actor->e_pos_x += actor->e_move_right_speed * 0.5f;
    if (actor->e_pos_x > 656.0f) {
        actor->e_pos_x = 656.0f;
        actor->e_move_right_speed = 0.0f;
        finished = TRUE;
    }

    return finished;
}

static void aAL_e_plus_right_move_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    if (aAL_chk_start_key2(actor, game) == FALSE && actor->title_timer <= 0) {
        aAL_setupAction(actor, game, aAL_ACTION_LOGO_ROTATE);
    }
}

static void aAL_logo_rotate(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    static float check_posX_table[] = {
        182.5f,
        216.1f,
        249.7f,
        283.3f,
        313.3f,
        346.9f,
    };

    if (aAL_chk_start_key2(actor, game) == FALSE) {
        int idx = actor->logo_piece_count;

        if (aAL_move_right_e_plus(actor) == TRUE) {
            aAL_setupAction(actor, game, aAL_ACTION_E_PLUS_LEFT_MOVE_START_WAIT);
        } else if (actor->logo_piece_count < 6) {
            if (actor->e_pos_x >= check_posX_table[idx]) {
                if (actor->logo_piece_count == 5) {
                    actor->rotation[idx] = -630.0f;
                    actor->rotation_speed[idx] = 13.0f;
                } else {
                    actor->rotation[idx] = -270.0f;
                    actor->rotation_speed[idx] = 13.0f;
                }

                actor->logo_piece_count++;
            }
        }
    }
}

static void aAL_e_plus_left_move_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    if (aAL_chk_start_key2(actor, game) == FALSE && actor->title_timer <= 0) {
        aAL_setupAction(actor, game, aAL_ACTION_PURURUN_START_WAIT);
    }
}

static void aAL_pururun_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    if (aAL_chk_start_key2(actor, game) == FALSE) {
        actor->e_pos_x += actor->e_move_right_speed * 0.5f;
        if (actor->e_pos_x <= 421.0f) {
            aAL_setupAction(actor, game, aAL_ACTION_PURURUN_END_WAIT);
        }
    }
}

static void aAL_pururun_end_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    if (aAL_chk_start_key2(actor, game) == FALSE) {
        float* speed = &actor->e_move_right_speed;

        if (actor->_1BE == 0) {
            chase_f(speed, actor->_1E8, 45.0f);
        } else {
            chase_f(speed, actor->_1E8, 150.0f);
        }

        actor->e_pos_x += *speed;
        actor->_1EC = (actor->e_pos_x + 11190.883f) / 11190.883f;
        actor->_1F0 = 1.0f / (1.0f + (actor->_1EC - 1.0f) * 0.3f);

        if (actor->e_pos_x * actor->_1E8 > 0.0f) {
            actor->_1E8 *= -0.85f;
            actor->_1BE = 1;

            if (ABS(actor->_1E8) < 50.0f) {
                aAL_setupAction(actor, game, aAL_ACTION_START_KEY_CHK_START_WAIT);
            }
        }
    }
}

static void aAL_start_key_chk_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    if (padmgr_isConnectedController(PAD0) && actor->title_timer <= 0 && famicom_mount_archive_end_check()) {
        aAL_setupAction(actor, game, aAL_ACTION_GAME_START_WAIT);
    }
}

static void aAL_game_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 start_opacity;
    s16 t;
    s16 new_opacity_timer;

    new_opacity_timer = actor->start_opacity_timer;
    new_opacity_timer += (s16)(32768.0f / (actor->start_opacity_timer > 0 ? 50.0f : 22.0f));
    start_opacity = 127.5f * sin_s(new_opacity_timer) + 127.5f; // 127.5f + 127.5f * [0, 1] = [127.5f, 255.0f] (opacity)

    if (start_opacity > 255.0f) {
        start_opacity = 255.0f;
    } else if (start_opacity < 0.0f) {
        start_opacity = 0.0f;
    }

    actor->press_start_opacity = start_opacity;
    actor->start_opacity_timer = new_opacity_timer;

    if (play->fb_fade_type == FADE_TYPE_SELECT_END) {
        aAL_setupAction(actor, game, aAL_ACTION_9);
    } else if (((gamePT->pads[PAD0].on.button & BUTTON_START) == BUTTON_START ||
                (gamePT->pads[PAD0].on.button & BUTTON_A) == BUTTON_A) &&
               mLd_CheckStartFlag() == TRUE && aAL_wipe_end_check(game) == TRUE && mTD_tdemo_button_ok_check()) {
        aAL_setupAction(actor, game, aAL_ACTION_FADE_OUT_START_WAIT);
    }
}

static void aAL_fade_out_start_wait(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    if (actor->title_timer <= 0) {
        aAL_title_game_data_init_start_select(actor, game);
        aAL_setupAction(actor, game, aAL_ACTION_8);
    }
}

static void aAL_e_plus_right_move_start_wait_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    actor->logo_piece_count = 0;
    actor->title_timer = 74;
    actor->_1EC = 1.0f;
    actor->_1F0 = 1.0f;
    actor->copyright_opacity = 0;
    actor->titledemo_no = mTD_get_titledemo_no();
    actor->_1C4 = 0;
    mCD_set_aram_save_data();
    lbRTC_GetTime(Common_GetPointer(time.rtc_time));
    Common_Set(player_no, 0);
    Common_Set(player_data_mode, 0);
    Common_Set(scene_from_title_demo, -1);
}

static void aAL_logo_rotate_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    actor->e_pos_x = -16.0f;
    actor->e_move_right_speed = 32.0f;
}

static void aAL_e_plus_left_move_start_wait_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    actor->title_timer = 52;
}

static void aAL_pururun_start_wait_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    actor->e_pos_x = 474.0f;
    actor->e_move_right_speed = -12.0f;
}

static void aAL_pururun_end_wait_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    actor->e_pos_x = 0.0f;
    actor->_1BE = 0;
    actor->e_move_right_speed = -600.0f;
    actor->_1E8 = 510.0f;
}

static void aAL_start_key_chk_start_wait_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    float* rotation = actor->rotation;
    int i;

    actor->logo_piece_count = 6;
    for (i = 0; i < 6; i++) {
        *rotation = 0.0f;
        rotation++;
    }
    actor->_1EC = 1.0f;
    actor->_1F0 = 1.0f;
    actor->e_pos_x = 0.0f;
    actor->copyright_opacity = 255;
    actor->title_timer = aAL_TIMER;
}

static void aAL_fade_out_start_wait_init(ANIMAL_LOGO_ACTOR* actor, GAME* game) {
    sAdo_SysTrgStart(0x44D);
    actor->title_timer = aAL_FADEOUT_TIMER;
    actor->press_start_opacity = 255.0f;
}

static void aAL_setupAction(ANIMAL_LOGO_ACTOR* actor, GAME* game, int action) {
    static const ANIMAL_LOGO_ACTION_PROC init_proc[aAL_ACTION_NUM] = {
        &aAL_e_plus_right_move_start_wait_init,
        &aAL_logo_rotate_init,
        &aAL_e_plus_left_move_start_wait_init,
        &aAL_pururun_start_wait_init,
        &aAL_pururun_end_wait_init,
        &aAL_start_key_chk_start_wait_init,
        (ANIMAL_LOGO_ACTION_PROC)&none_proc1,
        &aAL_fade_out_start_wait_init,
        (ANIMAL_LOGO_ACTION_PROC)&none_proc1,
        (ANIMAL_LOGO_ACTION_PROC)&none_proc1,
    };

    static const ANIMAL_LOGO_ACTION_PROC process[aAL_ACTION_NUM] = {
        &aAL_e_plus_right_move_start_wait,
        &aAL_logo_rotate,
        &aAL_e_plus_left_move_start_wait,
        &aAL_pururun_start_wait,
        &aAL_pururun_end_wait,
        &aAL_start_key_chk_start_wait,
        &aAL_game_start_wait,
        &aAL_fade_out_start_wait,
        &aAL_none_proc1,
        &aAL_none_proc1,
    };

    (*init_proc[action])(actor, game);
    actor->action = action;
    actor->action_proc = process[action];
}

static void aAL_actor_move(ACTOR* actor, GAME* game) {
    ANIMAL_LOGO_ACTOR* logo_actor = (ANIMAL_LOGO_ACTOR*)actor;

    lbRTC_Sampling();
    aAL_logo_rotate_proc(logo_actor);
    if (logo_actor->title_timer > 0) {
        logo_actor->title_timer--;
    }

    (*logo_actor->action_proc)(logo_actor, game);
}

extern Gfx logo_type_doT_model[];
extern Gfx logo_type_uT_model[];
extern Gfx logo_type_buT_model[];
extern Gfx logo_type_tuT_model[];
extern Gfx logo_type_noT_model[];
extern Gfx logo_type_moriT_model[];
extern Gfx logo_type_mori_epT_model[];
extern Gfx logo_back_doT_model[];
extern Gfx logo_back_uT_model[];
extern Gfx logo_back_buT_model[];
extern Gfx logo_back_tuT_model[];
extern Gfx logo_back_noT_model[];
extern Gfx logo_back_moriT_model[];
extern Gfx logo_back_mori_epT_model[];
extern Gfx logo_type2_mori_epT_model[];
extern Gfx logo_point_mori_ep_model[];

static void aAL_logo_draw(ANIMAL_LOGO_ACTOR* actor, GRAPH* graph, s16 piece) {
    static const Gfx init_disp[] = {
        gsSPTexture(0, 0, 0, 0, G_ON),
        gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2),
        gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, ENVIRONMENT),
        gsSPEndDisplayList(),
    };

    static const Gfx init_disp2[] = {
        gsDPSetCombineMode(G_CC_BLENDPEDECALA, G_CC_BLENDPEDECALA),
        gsSPLoadGeometryMode(G_CULL_BACK),
        gsSPEndDisplayList(),
    };

    static const Gfx init_disp3[] = {
        gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
        gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
        gsSPEndDisplayList(),
    };

    static Gfx* aAL_logo_dl[] = {
        logo_back_doT_model,
        logo_back_uT_model,
        logo_back_buT_model,
        logo_back_tuT_model,
        logo_back_noT_model,
        logo_back_moriT_model,
        logo_back_mori_epT_model,
    };

    static Gfx* aAL_logo_dl2[] = {
        logo_type_doT_model,
        logo_type_uT_model,
        logo_type_buT_model,
        logo_type_tuT_model,
        logo_type_noT_model,
        logo_type_moriT_model,
        logo_type_mori_epT_model,
    };

    static const float posX[aAL_LOGO_TYPE_NUM - 1] = {
        10.373291f, // aAL_LOGO_TYPE_DO
        43.973297f, // aAL_LOGO_TYPE_U
        77.573288f, // aAL_LOGO_TYPE_BU
        111.17328f, // aAL_LOGO_TYPE_TU
        141.17328f, // aAL_LOGO_TYPE_NO
        174.77328f, // aAL_LOGO_TYPE_MORI
    };

    int titledemo_no = actor->titledemo_no;
    float pos_x = (-141.0f + (172.12671f + actor->_1EC * posX[piece]) - 160.0f) * 16.0f;
    u8 prim_r, prim_g, prim_b;
    u8 env_r, env_g, env_b;
    u8 s_env_r, s_env_g, s_env_b;

    Matrix_push();
    Matrix_translate(pos_x, 896.0f, 0.0f, MTX_MULT);
    Matrix_RotateY(DEG2SHORT_ANGLE2(actor->rotation[piece]), MTX_MULT);
    Matrix_scale(actor->_1EC * 0.16208267f, actor->_1F0 * 0.16208267f, 0.16208267f, MTX_MULT);

    OPEN_FONT_DISP(graph);

    gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (piece == aAL_LOGO_TYPE_MORI && actor->action >= aAL_ACTION_PURURUN_END_WAIT) {
        piece++;
    }

    {
        gSPDisplayList(FONT_DISP++, init_disp);
        gDPSetPrimColor(FONT_DISP++, 0, 255, aAL_logo_squ_prim_r[titledemo_no], aAL_logo_squ_prim_g[titledemo_no], aAL_logo_squ_prim_b[titledemo_no], 60);
        gDPSetEnvColor(FONT_DISP++, aAL_logo_squ_env_r[titledemo_no], aAL_logo_squ_env_g[titledemo_no], aAL_logo_squ_env_b[titledemo_no], 150);
        gSPDisplayList(FONT_DISP++, aAL_logo_dl[piece]);
    }

    {
        gSPDisplayList(FONT_DISP++, init_disp2);
        gDPSetPrimColor(FONT_DISP++, 0, 255, 255, 250, 39, 255);
        gDPSetEnvColor(FONT_DISP++, aAL_logo_str_env_r[titledemo_no], aAL_logo_str_env_g[titledemo_no], aAL_logo_str_env_b[titledemo_no], 255);
        gSPDisplayList(FONT_DISP++, aAL_logo_dl2[piece]);
    }

    if (piece == aAL_LOGO_TYPE_MORI_E) {
        gDPSetPrimColor(FONT_DISP++, 0, 255, 255, 204, 0, 255);
        gSPDisplayList(FONT_DISP++, logo_type2_mori_epT_model);
        gSPDisplayList(FONT_DISP++, init_disp3);
        gSPDisplayList(FONT_DISP++, logo_point_mori_ep_model);
    }

    CLOSE_FONT_DISP(graph);

    Matrix_pull();
}

extern Gfx logo_back_epT_model[];
extern Gfx logo_type2_epT_model[];
extern Gfx logo_point_ep_model[];

static void aAL_e_plus_draw(ANIMAL_LOGO_ACTOR* actor, GRAPH* graph) {
    static const Gfx init_disp[] = {
        gsSPTexture(0, 0, 0, 0, G_ON),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2),
        gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, ENVIRONMENT),
        gsSPEndDisplayList(),
    };
    
    static const Gfx init_disp2[] = {
        gsDPSetCombineMode(G_CC_BLENDPEDECALA, G_CC_BLENDPEDECALA),
        gsSPEndDisplayList(),
    };

    static const Gfx init_disp3[] = {
        gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
        gsSPEndDisplayList(),
    };

    int titledemo_no = actor->titledemo_no;
    float pos_x = ((-141.0f + actor->e_pos_x) - 160.0f) * 16.0f;

    Matrix_push();
    Matrix_translate(pos_x, 896.0f, 0.0f, MTX_MULT);
    Matrix_scale(actor->_1EC * 0.16208267f, actor->_1F0 * 0.16208267f, 0.16208267f, MTX_MULT);

    OPEN_FONT_DISP(graph);

    gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    
    gSPDisplayList(FONT_DISP++, init_disp);
    gDPSetPrimColor(FONT_DISP++, 0, 255, aAL_logo_squ_prim_r[titledemo_no], aAL_logo_squ_prim_g[titledemo_no], aAL_logo_squ_prim_b[titledemo_no], 60);
    gDPSetEnvColor(FONT_DISP++, aAL_logo_squ_env_r[titledemo_no], aAL_logo_squ_env_g[titledemo_no], aAL_logo_squ_env_b[titledemo_no], 150);
    gSPDisplayList(FONT_DISP++, logo_back_epT_model);

    gSPDisplayList(FONT_DISP++, init_disp2);
    gDPSetPrimColor(FONT_DISP++, 0, 255, 255, 230, 0, 255);
    gDPSetEnvColor(FONT_DISP++, aAL_logo_str_env_r[titledemo_no], aAL_logo_str_env_g[titledemo_no], aAL_logo_str_env_b[titledemo_no], 255);
    gSPDisplayList(FONT_DISP++, logo_type2_epT_model);

    gSPDisplayList(FONT_DISP++, init_disp3);
    gDPSetPrimColor(FONT_DISP++, 0, 255, 255, 255, 255, 255);
    gSPDisplayList(FONT_DISP++, logo_point_ep_model);

    CLOSE_FONT_DISP(graph);

    Matrix_pull();
}

extern Gfx logo_tmT_model[];
extern Gfx logo_nin_copyT_model[];

static void aAL_tm_and_copyright_draw(ANIMAL_LOGO_ACTOR* actor, GRAPH* graph) {
    static const Gfx init_disp[] = {
        gsSPTexture(0, 0, 0, 0, G_ON),
        gsSPLoadGeometryMode(G_CULL_BACK),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2),
        gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
        gsSPEndDisplayList(),
    };

    actor->copyright_opacity += aAL_COPYRIGHT_ALPHA_RATE;
    if (actor->copyright_opacity >= 255) {
        actor->copyright_opacity = 255;
    }

    Matrix_push();
    Matrix_translate(2080.0f, 656.0f, 0.0f, MTX_MULT);
    Matrix_scale(0.16208267f, 0.16208267f, 0.16208267f, MTX_MULT);

    OPEN_FONT_DISP(graph);

    gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(FONT_DISP++, init_disp);
    gSPDisplayList(FONT_DISP++, logo_tmT_model);
    
    Matrix_pull();

    Matrix_push();
    Matrix_translate(32.0f, -1376.0f, 0.0f, MTX_MULT);
    Matrix_scale(0.16208267f, 0.16208267f, 0.16208267f, MTX_MULT);
    
    gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(FONT_DISP++, 0, 255, 255, 255, 255, actor->copyright_opacity);
    gSPDisplayList(FONT_DISP++, logo_nin_copyT_model);

    CLOSE_FONT_DISP(graph);

    Matrix_pull();
}

static void aAL_press_start_draw(ANIMAL_LOGO_ACTOR* actor, GRAPH* graph) {
    static const u32 draw_pos_x[3] = { 79, 143, 207 };
    static const u32 draw_pos_y[3] = { 154, 154, 154 };

    static const u32 ps_prim_r[5] = { 70, 60, 60, 40, 40 };
    static const u32 ps_prim_g[5] = { 40, 50, 40, 50, 50 };
    static const u32 ps_prim_b[5] = { 40, 30, 60, 70, 60 };

    static const u32 ps_env_r[5] = { 255, 255, 255, 120, 165 };
    static const u32 ps_env_g[5] = { 90, 135, 100, 205, 245 };
    static const u32 ps_env_b[5] = { 30, 0, 255, 245, 0 };

    Gfx* gfx;
    int titledemo_no;
    f32 alpha;
    titledemo_no = actor->titledemo_no;
    alpha = actor->press_start_opacity;

    OPEN_DISP(graph);

    gfx = NOW_FONT_DISP;
    gDPSetPrimColor(gfx++, 0, 255, ps_prim_r[titledemo_no], ps_prim_g[titledemo_no], ps_prim_b[titledemo_no],
                    (u32)alpha);
    gDPSetEnvColor(gfx++, ps_env_r[titledemo_no], ps_env_g[titledemo_no], ps_env_b[titledemo_no], 0);
    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_THRESHOLD | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gSPLoadGeometryMode(gfx++, 0);
    gDPSetCombineMode(gfx++, G_CC_PRESS_START, G_CC_PRESS_START);

    gDPLoadTextureTile(gfx++, log_win_logo3_tex, G_IM_FMT_IA, G_IM_SIZ_8b, TITLE_WIDTH, TITLE_HEIGHT, 0, 0,
                       TITLE_WIDTH - 1, TITLE_HEIGHT - 1, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                       G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gfx = gfx_gSPTextureRectangle1(gfx, draw_pos_x[0] << 2, draw_pos_y[0] << 2, (TITLE_WIDTH + draw_pos_x[0]) << 2,
                                   (TITLE_HEIGHT + draw_pos_y[0]) << 2, 0, 0 << 5, 0 << 5, 1 << 10, 1 << 10);

    gDPLoadTextureTile(gfx++, log_win_logo4_tex, G_IM_FMT_IA, G_IM_SIZ_8b, TITLE_WIDTH, TITLE_HEIGHT, 0, 0,
                       TITLE_WIDTH - 1, TITLE_HEIGHT - 1, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                       G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gfx = gfx_gSPTextureRectangle1(gfx, draw_pos_x[1] << 2, draw_pos_y[1] << 2, (TITLE_WIDTH + draw_pos_x[1]) << 2,
                                   (TITLE_HEIGHT + draw_pos_y[1]) << 2, 0, 0 << 5, 0 << 5, 1 << 10, 1 << 10);

    gDPLoadTextureTile(gfx++, log_win_logo5_tex, G_IM_FMT_IA, G_IM_SIZ_8b, TITLE_WIDTH, TITLE_HEIGHT, 0, 0,
                                    TITLE_WIDTH - 1, TITLE_HEIGHT - 1, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                                    G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
             
    gfx = gfx_gSPTextureRectangle1(gfx, draw_pos_x[2] << 2, draw_pos_y[2] << 2, (TITLE_WIDTH + draw_pos_x[2]) << 2,
                                (TITLE_HEIGHT + draw_pos_y[2]) << 2, 0, 0 << 5, 0 << 5, 1 << 10, 1 << 10);

    SET_FONT_DISP(gfx);

    CLOSE_DISP(graph);
}

static void aAL_actor_draw(ACTOR* actor, GAME* game) {
    ANIMAL_LOGO_ACTOR* logo_actor = (ANIMAL_LOGO_ACTOR*)actor;
    GRAPH* graph = game->graph;
    s16 i;

    mFont_SetMatrix(graph, mFont_MODE_FONT);

    for (i = 0; i < logo_actor->logo_piece_count; i++) {
        aAL_logo_draw(logo_actor, graph, i);
    }

    if (logo_actor->action < aAL_ACTION_PURURUN_END_WAIT) {
        aAL_e_plus_draw(logo_actor, graph);
    }

    if (logo_actor->action >= aAL_ACTION_START_KEY_CHK_START_WAIT) {
        aAL_tm_and_copyright_draw(logo_actor, graph);
    }

    mFont_SetMode(graph, mFont_MODE_FONT);
    if (padmgr_isConnectedController(PAD0)) {
        switch (logo_actor->action) {
            case aAL_ACTION_GAME_START_WAIT:
            case aAL_ACTION_FADE_OUT_START_WAIT:
            case aAL_ACTION_8:
                aAL_press_start_draw(logo_actor, graph);
                break;
        }
    }

    mFont_UnSetMatrix(graph, mFont_MODE_FONT);
    game_debug_draw_last(game, graph);
    game_draw_last(graph);
}
