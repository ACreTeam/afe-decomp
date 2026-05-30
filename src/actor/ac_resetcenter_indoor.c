#include "ac_resetcenter_indoor.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

#define aRI_CLIP ((RESETCENTER_INDOOR_ACTOR*)CLIP(resetcenter_indoor_clip))

static xyz_t l_tv_position = { 100.0f, 60.0f, 220.0f };
static xyz_t l_light_position = { 140.0f, 200.0f, 140.0f };

static void Resetcenter_Indoor_Actor_ct(ACTOR* actorx, GAME* game);
static void Resetcenter_Indoor_Actor_dt(ACTOR* actorx, GAME* game);
static void Resetcenter_Indoor_Actor_move(ACTOR* actorx, GAME* game);
static void Resetcenter_Indoor_Actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Resetcenter_Indoor_Profile = {
    mAc_PROFILE_RESETCENTER_INDOOR,
    ACTOR_PART_FG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(RESETCENTER_INDOOR_ACTOR),
    Resetcenter_Indoor_Actor_ct,
    Resetcenter_Indoor_Actor_dt,
    Resetcenter_Indoor_Actor_move,
    Resetcenter_Indoor_Actor_draw,
    NULL,
};

static void aRI_make_point_light(RESETCENTER_INDOOR_ACTOR* actor, GAME_PLAY* play) {
    actor->tv.pointlight_idx = mEnv_ReservePointLight(play, &l_tv_position, 120, 150, 180, 114);
}

static void aRI_tv_ct(RESETCENTER_INDOOR_ACTOR* actor, GAME_PLAY* play) {
    actor->tv.pos = l_tv_position;
    actor->tv._14 = 30.0f;
    actor->tv.rnd = 15.0f;
    aRI_make_point_light(actor, play);
}

static void aRI_tv_sound(void) {
    // static u8 tv_sfx[] = { 0x04, 0x05, 0x06, 0x5E }; // temp until e+ sfx is added
    static u8 sound; // used as a unique ID for sAdo_OngenPos

    sAdo_OngenPos((u32)&sound, 0x61, &l_tv_position);
    // sAdo_OngenPos((u32)&sound, tv_sfx[RANDOM(ARRAY_COUNT(tv_sfx))], &l_tv_position); // Temp sfx until we get the correct one added
}

static void aRI_tv_move(aRI_tv_c* tv) {
    s16 angle = tv->angle;
    f32 mult = 0.3f + ((1.0f + sin_s(angle)) * 0.5f) * 0.5f;
    s16 rnd;

    mEnv_OperateReservedPointLight_Color(tv->pointlight_idx, (int)(120 * mult), (int)(150 * mult), (int)(180 * mult));
    aRI_tv_sound();
    rnd = tv->counter & 0x3F;

    if (rnd >= 1 && rnd < 4) {
        tv->angle += 0x1838;
    } else if (rnd >= 10 && rnd < 14) {
        tv->angle += 0x0E74;
    } else if (rnd >= 20 && rnd < 24) {
        tv->angle += 0x16A8;
    } else if (rnd >= 27 && rnd < 31) {
        tv->angle += 0x0FA0;
    } else if (rnd >= 35 && rnd < 39) {
        tv->angle += 0x1388;
    } else if (rnd >= 42 && rnd < 45) {
        tv->angle += 0x0FA0;
    } else if (rnd >= 47 && rnd < 51) {
        tv->angle += 0x157C;
    } else if (rnd >= 57 && rnd < 61) {
        tv->angle += 0x0E74;
    } else {
        tv->angle += 0x07D0;
    }

    if (angle < 0 && tv->angle >= 0) {
        tv->rnd = RANDOM_F(15.0f);
        tv->counter++;
    }
}

static void aRI_delete_point_light(RESETCENTER_INDOOR_ACTOR* actor, GAME_PLAY* play) {
    actor->tv.pointlight_idx = mEnv_CancelReservedPointLight(actor->tv.pointlight_idx, play);
}

static void aRI_tv_dt(RESETCENTER_INDOOR_ACTOR* actor, GAME_PLAY* play) {
    aRI_delete_point_light(actor, play);
}

// door

static void aRI_door_ct(aRI_door_c* door) {
    door->target = 1.0f;
}

static void aRI_door_move(aRI_door_c* door) {
    f32 step;

    if (door->target == 1.0f) {
        step = 0.3f;
    } else {
        step = 0.25f;
    }

    add_calc(&door->alpha_percent, door->target, step, 1.0f, 0.005f);
}

static void aRI_door_dt(aRI_door_c* door) {
    door->target = 1.0f;
}

// light
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_molcenter_light01;
extern cKF_Animation_R_c cKF_ba_r_int_ike_molcenter_light01;

static void aRI_light_ct(aRI_light_c* light, GAME_PLAY* play) {
    cKF_SkeletonInfo_R_c* kf_p;
    u8 prim_r;
    u8 prim_g;
    u8 prim_b;
    
    mEnv_GetRoomPrimColor(&prim_r, &prim_g, &prim_b, play);
    light->prim_r = prim_r;
    light->prim_g = prim_g;
    light->prim_b = prim_b;
    light->state = 0;
    light->pointlight_idx = mEnv_ReservePointLight(play, &l_light_position, 0, 0, 0, 1000);
    
    kf_p = &light->kf;
    cKF_SkeletonInfo_R_ct(kf_p, &cKF_bs_r_int_ike_molcenter_light01, &cKF_ba_r_int_ike_molcenter_light01, light->work, light->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(kf_p, &cKF_ba_r_int_ike_molcenter_light01, NULL);
    kf_p->frame_control.speed = 0.0f;
    cKF_SkeletonInfo_R_play(kf_p);
}

static void aRI_light_move(aRI_light_c* light, GAME_PLAY* play) {
    u8 prim_r;
    u8 prim_g;
    u8 prim_b;
    f32 orig_prim_r;
    f32 mult;
    
    mEnv_GetRoomPrimColor(&prim_r, &prim_g, &prim_b, play);
    orig_prim_r = prim_r;

    if (light->state == 1) {
        light->counter += 0x180;

        if ((light->light_color & 1) == 0) {
            if ((int)light->prim_r == prim_r && (int)light->prim_g == prim_g && (int)light->prim_b == prim_b) {
                light->light_color++;
            }
        } else {
            prim_r = 210;
            prim_g = 60;
            prim_b = 60;

            if ((int)light->prim_r == prim_r && (int)light->prim_g == prim_g && (int)light->prim_b == prim_b) {
                light->light_color++;
            }
        }
    }

    add_calc(&light->prim_r, prim_r, 0.25f, 10.0f, 0.1f);
    add_calc(&light->prim_g, prim_g, 0.25f, 10.0f, 0.1f);
    add_calc(&light->prim_b, prim_b, 0.25f, 10.0f, 0.1f);

    mult = (light->prim_r - orig_prim_r) / (210 - orig_prim_r);
    mEnv_OperateReservedPointLight_Color(light->pointlight_idx, (int)(210 * mult), (int)(60 * mult), (int)(60 * mult));
}

static void aRI_light_dt(aRI_light_c* light, GAME_PLAY* play) {
    light->pointlight_idx = mEnv_CancelReservedPointLight(light->pointlight_idx, play);
}

static void aRI_get_room_prim_color(u8* r, u8* g, u8* b, RESETCENTER_INDOOR_ACTOR* actor) {
    *r = (int)actor->light.prim_r;
    *g = (int)actor->light.prim_g;
    *b = (int)actor->light.prim_b;
}

static void Resetcenter_Indoor_Actor_ct(ACTOR* actorx, GAME* game) {
    RESETCENTER_INDOOR_ACTOR* actor = (RESETCENTER_INDOOR_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aRI_CLIP = actor;
    aRI_tv_ct(actor, play);
    aRI_door_ct(&actor->door);
    aRI_light_ct(&actor->light, play);
    Common_Get(event_common).resetcenter_flags = 0;
    if (Common_Get(door_data).door_actor_name != RSV_NO) {
        if (aRI_get_reset_mode() == 4 || Now_Private->reset_center_flags & (1 << 5)) {
            Now_Private->reset_center_flags &= ~(1 << 5);
            aRI_next_mode();
        }
    }
}

static void Resetcenter_Indoor_Actor_dt(ACTOR* actorx, GAME* game) {
    RESETCENTER_INDOOR_ACTOR* actor = (RESETCENTER_INDOOR_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aRI_CLIP = NULL;
    aRI_tv_dt(actor, play);
    aRI_door_dt(&actor->door);
    aRI_light_dt(&actor->light, play);
}

static void Resetcenter_Indoor_Actor_move(ACTOR* actorx, GAME* game) {
    RESETCENTER_INDOOR_ACTOR* actor = (RESETCENTER_INDOOR_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aRI_tv_move(&actor->tv);
    aRI_door_move(&actor->door);
    aRI_light_move(&actor->light, play);
}

extern Gfx rom_futoumei_model[];
extern Gfx rom_futoumeiT_model[];
extern Gfx rom_boots_cmo_model[];
extern Gfx rom_boots_cmb_model[];

static void aRI_draw_normal(RESETCENTER_INDOOR_ACTOR* actor, GAME* game) {
    Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, rom_futoumei_model);
    gSPDisplayList(NEXT_POLY_XLU_DISP, rom_futoumeiT_model);

    if (!actor->nodraw_cmo_boots) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, rom_boots_cmo_model);
    }

    if (!actor->nodraw_cmb_boots) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, rom_boots_cmb_model);
    }

    CLOSE_DISP(game->graph);
}

extern Gfx rom_tvlight_model[];

static void aRI_draw_tvlight(RESETCENTER_INDOOR_ACTOR* actor, GAME* game) {
    int alpha = actor->tv.rnd + (RANDOM_F(1.0f) + 1.0f) * 0.5f * (actor->tv._14 - actor->tv.rnd);

    Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(NEXT_POLY_XLU_DISP); // why do we pipesync on emu64???
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 90, 90, 90, (u8)alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, rom_tvlight_model);

    CLOSE_DISP(game->graph);
}

static int aRI_draw_light_before(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    RESETCENTER_INDOOR_ACTOR* actor = (RESETCENTER_INDOOR_ACTOR*)arg;

    if (joint_idx != 0) {
        joint_rot->x += actor->light.counter;
    }

    return TRUE;
}

extern Gfx rom_lightbase_model[];

static void aRI_draw_light(RESETCENTER_INDOOR_ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    xyz_t pos = { 160.0f, 160.0f, 160.0f };
    Mtx* kf_mtx = actor->light.mtx[game->frame_counter & 1];

    Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

    OPEN_DISP(game->graph);
    
    gSPMatrix(NEXT_BG_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_BG_OPA_DISP, rom_lightbase_model);
    
    CLOSE_DISP(game->graph);
    
    Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
    Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

    Setpos_HiliteReflect_init(&pos, play);
    Setpos_HiliteReflect_xlu_init(&pos, play);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, &actor->light.kf, kf_mtx, aRI_draw_light_before, NULL, actor);
}

extern Gfx rom_door_model[];

static void aRI_draw_door(RESETCENTER_INDOOR_ACTOR* actor, GAME* game) {
    u8 r;
    u8 g;
    u8 b;

    aRI_get_room_prim_color(&r, &g, &b, actor);
    Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(NEXT_POLY_XLU_DISP); // why do we pipesync on emu64???
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, r, g, b, (int)(actor->door.alpha_percent * 255));
    gSPDisplayList(NEXT_POLY_XLU_DISP, rom_door_model);

    CLOSE_DISP(game->graph);
}

static void aRI_set_bg_disp_prim_color(RESETCENTER_INDOOR_ACTOR* actor, GAME* game) {
    u8 r;
    u8 g;
    u8 b;

    aRI_get_room_prim_color(&r, &g, &b, actor);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_BG_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(NEXT_BG_OPA_DISP);
    gDPSetPrimColor(NEXT_BG_OPA_DISP, 0, 128, r, g, b, 255);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(NEXT_POLY_OPA_DISP);
    gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 128, r, g, b, 255);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(NEXT_POLY_XLU_DISP);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, r, g, b, 255);

    CLOSE_DISP(game->graph);
}

static void Resetcenter_Indoor_Actor_draw(ACTOR* actorx, GAME* game) {
    RESETCENTER_INDOOR_ACTOR* actor = (RESETCENTER_INDOOR_ACTOR*)actorx;

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);
    _texture_z_light_fog_prim_bg(game->graph);
    aRI_set_bg_disp_prim_color(actor, game);
    aRI_draw_normal(actor, game);
    aRI_draw_door(actor, game);
    aRI_draw_light(actor, game);
    aRI_draw_tvlight(actor, game);
}

// clip

extern int aRI_request_appear_door(void) {
    static xyz_t door_pos = { 140.0f, 40.0f, 80.0f };

    if (aRI_CLIP != NULL) {
        aRI_CLIP->door.target = 1.0f;
        sAdo_OngenTrgStart(0x41, &door_pos);
        return TRUE;
    }

    return FALSE;
}

extern int aRI_request_disappear_door(void) {
    if (aRI_CLIP != NULL) {
        aRI_CLIP->door.target = 0.0f;
        return TRUE;
    }

    return FALSE;
}

extern f32 aRI_get_door_alpha_percent(void) {
    if (aRI_CLIP != NULL) {
        return aRI_CLIP->door.alpha_percent;
    }

    return 0.0f;
}

extern int aRI_request_light_on(void) {
    if (aRI_CLIP != NULL) {
        aRI_CLIP->light.state = 1;
        sAdo_SysLevStart(0x62); // TODO: e+ sfx
        return TRUE;
    }

    return FALSE;
}

extern int aRI_request_light_off(void) {
    if (aRI_CLIP != NULL) {
        aRI_CLIP->light.state = 0;
        sAdo_SysLevStop(0x62); // TODO: e+ sfx
        return TRUE;
    }

    return FALSE;
}

extern void aRI_set_resetcenter_prim_color(GAME* game) {
    if (aRI_CLIP != NULL) {
        u8 r;
        u8 g;
        u8 b;

        aRI_get_room_prim_color(&r, &g, &b, aRI_CLIP);

        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_BG_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(NEXT_BG_OPA_DISP);
        gDPSetPrimColor(NEXT_BG_OPA_DISP, 0, 128, r, g, b, 255);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(NEXT_POLY_OPA_DISP);
        gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 128, r, g, b, 255);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(NEXT_POLY_XLU_DISP);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, r, g, b, 255);

        CLOSE_DISP(game->graph);
    }
}

extern int aRI_delete_boots_of_Reset(void) {
    if (aRI_CLIP != NULL) {
        aRI_CLIP->nodraw_cmo_boots = TRUE;
        return TRUE;
    }

    return FALSE;
}

extern int mRI_delete_boots_of_Racket(void) {
    if (aRI_CLIP != NULL) {
        aRI_CLIP->nodraw_cmb_boots = TRUE;
        return TRUE;
    }

    return FALSE;
}

extern int aRI_get_reset_mode(void) {
    static int mode_table_0[] = { 2, 4, 6 };
    static int mode_table_1[] = { 2, 3, 4, 5, 6, 7 };
    int count = Now_Private->reset_center_flags & 0xF;

    if (!(Now_Private->reset_center_flags & (1 << 6))) {
        Now_Private->reset_center_flags &= ~0xF;
        return 0;
    }

    if (Now_Private->reset_count >= 5) {
        if (!(Now_Private->reset_center_flags & (1 << 5))) {
            Now_Private->reset_center_flags &= ~0xF;
            return 1;
        }

        if (count >= ARRAY_COUNT(mode_table_1)) {
            Now_Private->reset_center_flags &= ~0xF;
            count = 0;
        }

        return mode_table_1[count];
    }

    if (count >= ARRAY_COUNT(mode_table_0)) {
        Now_Private->reset_center_flags &= ~0xF;
        count = 0;
    }

    return mode_table_0[count];
}

extern int aRI_get_reset_mode_E(void) {
    int mode = aRI_get_reset_mode();

    if (Now_Private->reset_center_flags & (1 << 5)) {
        mode += 8;
    }

    return mode;
}

extern void aRI_next_mode(void) {
    int count;

    switch (aRI_get_reset_mode()) {
        case 0:
            Now_Private->reset_center_flags |= (1 << 6);
            break;
        case 1:
            Now_Private->reset_center_flags |= (1 << 7);
            break;
        default:
            count = (Now_Private->reset_center_flags & 0xF) + 1;
            Now_Private->reset_center_flags &= ~0xF;
            Now_Private->reset_center_flags |= count;
            break;
    }
}
