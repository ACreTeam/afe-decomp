#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

static void eNM_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eNM_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eNM_mv(eEC_Effect_c* effect, GAME* game);
static void eNM_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_nomi = {
    // clang-format off
    &eNM_init,
    &eNM_ct,
    &eNM_mv,
    &eNM_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eNM_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_NOMI, pos, NULL, game, &angle, item_name, prio, 0, 0);
}

static void eNM_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    f32 rng = RANDOM_F(1.0f);
    static xyz_t acc = { 0.0f, -0.4f, 0.0f };
    xyz_t vel;

    vel.x = -0.1f + RANDOM_F(0.75f);
    vel.y = 3.3f;
    vel.z = 0.0f;

    effect->offset.y += 12.0f;
    if (rng > 0.5f) {
        if (rng > 0.75f) {
            effect->offset.x += -8.0f;
        }

        vel.x *= -1.0f;
    } else {
        if (rng < 0.25f) {
            effect->offset.x += 8.0f;
        }
    }

    effect->scale.x = 0.01f;
    effect->scale.y = 0.01f;
    effect->scale.z = 0.01f;
    effect->timer = 18;
    effect->acceleration = acc;
    effect->velocity = vel;
}

static void eNM_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->timer == 18) {
        sAdo_OngenTrgStart(0x471, &effect->position);
    }

    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->offset, &effect->velocity, &effect->offset);
}

extern Gfx act_m_nomi1T_model[];

static void eNM_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph;
    u8 a = (int)eEC_CLIP->calc_adjust_proc(18 - effect->timer, 24, 18, 255.0f, 0.0f);
    f32 scale;
    
    graph = game->graph;
    _texture_z_light_fog_prim_xlu(graph);
    Matrix_translate(effect->position.x + effect->offset.x, effect->position.y + effect->offset.y, effect->position.z + effect->offset.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, 1);
    Matrix_RotateX(DEG2SHORT_ANGLE2(90.0f), 1);
    scale = 1.0f + ((int)GETREG(MYKREG, 27)) * 0.01f;
    Matrix_scale(effect->scale.x * scale, effect->scale.y * scale, effect->scale.z * scale, MTX_MULT);

    OPEN_DISP(graph);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 0, 0, 0, a);
    gSPDisplayList(NEXT_POLY_XLU_DISP, act_m_nomi1T_model);

    CLOSE_DISP(graph);
}
