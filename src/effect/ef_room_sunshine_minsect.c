#include "ef_room_sunshine_minsect.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_collision_bg.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static void Ef_Room_Sunshine_Minsect_actor_ct(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_Minsect_actor_dt(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_MinsectL_actor_draw(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_MinsectL_actor_move(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_MinsectR_actor_draw(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_MinsectR_actor_move(ACTOR* actor, GAME* play);

extern Gfx rom_museum4_pp_ue_model[];
extern Gfx rom_museum4_pp_model[];
extern Gfx obj_museum4_pp_shine_l_model[];
extern Gfx obj_museum4_pp_shine_l_modelT[];
extern Gfx obj_museum4_pp_shine_r_model[];
extern Gfx obj_museum4_pp_shine_r_modelT[];

u8 draw_status;

ACTOR_PROFILE Room_Sunshine_Minsect_Profile = {
    mAc_PROFILE_ROOM_SUNSHINE_MINSECT,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_EF_MINSECT,
    sizeof(ROOMSUNSHINEMINSECT_ACTOR),
    Ef_Room_Sunshine_Minsect_actor_ct,
    NONE_ACTOR_PROC,
    Ef_Room_Sunshine_MinsectR_actor_move,
    Ef_Room_Sunshine_MinsectR_actor_draw,
    NULL,
};

static void Ef_Room_Sunshine_Minsect_actor_ct(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEMINSECT_ACTOR* minsect = (ROOMSUNSHINEMINSECT_ACTOR*)actor;
    xyz_t pos;

    minsect->ef_sunshine_class.unk_174 = 0;
    draw_status = 0;
    if (minsect->ef_sunshine_class.actor_class.actor_specific == 0) {
        minsect->ef_sunshine_class.actor_class.mv_proc = Ef_Room_Sunshine_MinsectL_actor_move;
        minsect->ef_sunshine_class.actor_class.dw_proc = Ef_Room_Sunshine_MinsectL_actor_draw;
    } else {
        minsect->ef_sunshine_class.actor_class.world.position.x -= 1.0f;
    }

    minsect->ef_sunshine_class.actor_class.world.position.y =
        mCoBG_GetBgY_OnlyCenter_FromWpos(minsect->ef_sunshine_class.actor_class.world.position, 0.0f);

    minsect->ef_sunshine_class.actor_class.scale.x = 0.01f;
    minsect->ef_sunshine_class.actor_class.scale.y = 0.01f;
    minsect->ef_sunshine_class.actor_class.scale.z = 0.01f;
    minsect->ef_sunshine_class.actor_class.cull_radius = 10000.0f;

    switch (minsect->ef_sunshine_class.actor_class.actor_specific) {
        case 0:
            minsect->ef_sunshine_class.actor_class.mv_proc = Ef_Room_Sunshine_MinsectL_actor_move;
            minsect->ef_sunshine_class.actor_class.dw_proc = Ef_Room_Sunshine_MinsectL_actor_draw;
            minsect->ef_sunshine_class.actor_class.world.position.x += 5.0f;
            minsect->ef_sunshine_class.actor_class.world.position.x -= 6.0f;
            break;
        case 1:
            minsect->ef_sunshine_class.actor_class.world.position.x -= 5.0f;
            minsect->ef_sunshine_class.actor_class.world.position.x += 6.0f;
            break;
    }
}

static f32 calc_scale_Ef_Room_Sunshine_Minsect(int flag, int sec) {

    if (flag == 0) {
        return 0.01f * (1.5f * sin_s((sec << 14) / 28800.0f));
    } else {
        return 0.01f * (1.5f * sin_s((sec << 14) / 14400.0f));
    }
}

static u8 calc_alpha_Ef_Room_SunshineMinsect() {
    f32 ret;
    int sec;

    if (Common_Get(time.now_sec) < 14400) {
        ret = 120.0f * ((14400 - Common_Get(time.now_sec)) / 14400.0f);
    } else if (Common_Get(time.now_sec) < 72000) {
        // any other number matches codegen, but 43200 breaks
        int sec;
        int now_sec = Common_Get(time.now_sec);

        sec = mTM_TIME2SEC(8, 0, 0) - (now_sec - mTM_TIME2SEC(12, 0, 0) >= 0 ? now_sec - mTM_TIME2SEC(12, 0, 0) : -(now_sec - mTM_TIME2SEC(12, 0, 0)));
        ret = 255.0f * (sec / (float)mTM_TIME2SEC(8, 0, 0));
    } else {
        ret = 120.0f * ((mTM_TIME2SEC(4, 0, 0) - (mTM_TIME2SEC(24, 0, 0) - Common_Get(time.now_sec))) / (f32)mTM_TIME2SEC(4, 0, 0));
    }

    if ((Common_Get(weather) == mEnv_WEATHER_RAIN) || (Common_Get(weather) == mEnv_WEATHER_SNOW)) {
        ret *= 0.6f;
    }

    return (int)ret;
}

static void Ef_Room_Sunshine_MinsectL_actor_move(ACTOR* actor, GAME* game) {
    if (Common_Get(time.now_sec) < mTM_TIME2SEC(4, 0, 0)) {
        actor->scale.x =
            calc_scale_Ef_Room_Sunshine_Minsect(1, Common_Get(time.now_sec));
    } else if (Common_Get(time.now_sec) >= mTM_TIME2SEC(12, 0, 0) && Common_Get(time.now_sec) < mTM_TIME2SEC(20, 0, 0)) {
        actor->scale.x =
            calc_scale_Ef_Room_Sunshine_Minsect(0, Common_Get(time.now_sec) - mTM_TIME2SEC(12, 0, 0));
    } else {
        actor->scale.x = 0.0f;
    }

    actor->world.position.y = actor->home.position.y;
    actor->world.position.y += 0.01f * GETREG(TAKREG, 64);
}

static void Ef_Room_Sunshine_MinsectR_actor_move(ACTOR* actor, GAME* game) {
    if (Common_Get(time.now_sec) >= mTM_TIME2SEC(4, 0, 0) && Common_Get(time.now_sec) < mTM_TIME2SEC(12, 0, 0)) {
        actor->scale.x =
            -calc_scale_Ef_Room_Sunshine_Minsect(0, mTM_TIME2SEC(12, 0, 0) - Common_Get(time.now_sec));
    } else if (Common_Get(time.now_sec) >= mTM_TIME2SEC(20, 0, 0)) {
        actor->scale.x =
            -calc_scale_Ef_Room_Sunshine_Minsect(1, mTM_TIME2SEC(24, 0, 0) - Common_Get(time.now_sec));
    } else {
        actor->scale.x = 0.0f;
    }
    actor->world.position.y = actor->home.position.y;
    actor->world.position.y += 0.01f * GETREG(TAKREG, 64);
}

static void setup_mode_Ef_Room_Sunshine_Minsect(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    OPEN_DISP(play->game.graph);

    Matrix_translate(actor->world.position.x, actor->world.position.y, actor->world.position.z, MTX_LOAD);
    Matrix_scale(actor->scale.x, actor->scale.y, actor->scale.z, MTX_MULT);

    gDPPipeSync(NEXT_POLY_XLU_DISP);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDPPipeSync(NEXT_SHADOW_DISP);
    gSPMatrix(NEXT_SHADOW_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    {
        u8* color;
        int calc;
        if ((Common_Get(time.now_sec) >= mTM_TIME2SEC(4, 0, 0)) &&
            (Common_Get(time.now_sec) < mTM_TIME2SEC(20, 0, 0))) {
            color = play->kankyo.base_light.sun_color_window;
        } else {
            color = play->kankyo.base_light.moon_color_window;
        }

        calc = calc_alpha_Ef_Room_SunshineMinsect() * mKK_windowlight_alpha_get();
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, calc, color[0], color[1], color[2], 75);
        gDPSetPrimColor(NEXT_SHADOW_DISP, 0, calc, color[0], color[1], color[2], 75);
    }

    CLOSE_DISP(play->game.graph);
}

static void setup_mode_Ef_Room_Sunshine_Minsect_decal(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    OPEN_DISP(play->game.graph);

    Matrix_translate(actor->world.position.x, actor->world.position.y, actor->world.position.z, MTX_LOAD);
    Matrix_scale(actor->scale.x, actor->scale.y, actor->scale.z, MTX_MULT);

    gDPPipeSync(NEXT_POLY_OPA_DISP);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    {
        u8* color;
        int calc;

        if ((Common_Get(time.now_sec) >= 14400) && (Common_Get(time.now_sec) < 72000)) {
            color = play->kankyo.base_light.sun_color_window;
        } else {
            color = play->kankyo.base_light.moon_color_window;
        }
        calc = calc_alpha_Ef_Room_SunshineMinsect() * mKK_windowlight_alpha_get();
        gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, calc, color[0], color[1], color[2], 75);
    }

    CLOSE_DISP(play->game.graph);
}

static void BG_draw_Minsect(ACTOR* actor, GAME* game) {
    if (!(draw_status & 4)) {
        draw_status |= 4;
    }

    if ((draw_status & 1) && (draw_status & 2)) {
        draw_status = 0;
    }

    OPEN_DISP(game->graph);
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_LOAD);
    Global_kankyo_set_room_prim(game);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, rom_museum4_pp_ue_model);
    CLOSE_DISP(game->graph);
}

static void BG_draw_Minsect_niwa(ACTOR* actor, GAME* game) {
    OPEN_DISP(game->graph);

    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_LOAD);
    Global_kankyo_set_room_prim(game);

    gSPMatrix(NEXT_BG_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_BG_OPA_DISP, rom_museum4_pp_model);

    CLOSE_DISP(game->graph);
}

static void Ef_Room_Sunshine_MinsectL_actor_draw(ACTOR* actor, GAME* game) {
    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_shadow(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    draw_status |= 1;

    if (mKK_windowlight_alpha_get() < 0.0001f) {
        if ((draw_status & 1) && (draw_status & 2) && !(draw_status & 4)) {
            BG_draw_Minsect_niwa(actor, game);
            BG_draw_Minsect(actor, game);
        }
    } else if (0.0f == actor->scale.x) {
        if ((draw_status & 1) && (draw_status & 2) && !(draw_status & 4)) {
            BG_draw_Minsect_niwa(actor, game);
            BG_draw_Minsect(actor, game);
        }
    } else {
        OPEN_DISP(game->graph);

        BG_draw_Minsect_niwa(actor, game);
        setup_mode_Ef_Room_Sunshine_Minsect(actor, game);

        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum4_pp_shine_l_model);
        setup_mode_Ef_Room_Sunshine_Minsect_decal(actor, game);

        if (REGADDR(TAKREG, 0) == 0) {
            gSPDisplayList(NEXT_SHADOW_DISP, obj_museum4_pp_shine_l_modelT);
        }
        BG_draw_Minsect(actor, game);

        CLOSE_DISP(game->graph);
    }
}

static void Ef_Room_Sunshine_MinsectR_actor_draw(ACTOR* actor, GAME* game) {
    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_shadow(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    draw_status |= 2;

    if (mKK_windowlight_alpha_get() < 0.0001f) {
        if ((draw_status & 1) && (draw_status & 2) && !(draw_status & 4)) {
            BG_draw_Minsect_niwa(actor, game);
            BG_draw_Minsect(actor, game);
        }
    } else if (0.0f == actor->scale.x) {
        if ((draw_status & 1) && (draw_status & 2) && !(draw_status & 4)) {
            BG_draw_Minsect_niwa(actor, game);
            BG_draw_Minsect(actor, game);
        }
    } else {
        OPEN_DISP(game->graph);

        BG_draw_Minsect_niwa(actor, game);
        setup_mode_Ef_Room_Sunshine_Minsect(actor, game);

        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum4_pp_shine_r_model);
        setup_mode_Ef_Room_Sunshine_Minsect_decal(actor, game);

        if (REGADDR(TAKREG, 0) == 0) {
            gSPDisplayList(NEXT_SHADOW_DISP, obj_museum4_pp_shine_r_modelT);
        }
        BG_draw_Minsect(actor, game);

        CLOSE_DISP(game->graph);
    }
}
