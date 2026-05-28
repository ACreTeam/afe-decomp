#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "libultra/libultra.h"

static void eResetbreak_Parts_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eResetbreak_Parts_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eResetbreak_Parts_mv(eEC_Effect_c* effect, GAME* game);
static void eResetbreak_Parts_dw(eEC_Effect_c* effect, GAME* game);

// clang-format off
eEC_PROFILE_c iam_ef_resetbreak_parts = {
    &eResetbreak_Parts_init,
    &eResetbreak_Parts_ct,
    &eResetbreak_Parts_mv,
    &eResetbreak_Parts_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
};
// clang-format on

static void eResetbreak_Parts_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_RESETBREAK_PARTS, pos, NULL, game, NULL, item_name, prio, angle, arg0);
}

static void eResetbreak_Parts_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    f32 rnd;
    f32 scale;
    f32 vel;
    f32 base;
    float angle_base;
    s16 angle1;
    s16 angle0;

    rnd = fqrand();

    if (effect->arg1 == 1) {
        rnd = 0.0f;
    }

    angle1 = (s16)(
        (f32)(DEG2SHORT_ANGLE2(45.0f) + GETREG(MYKREG, 58)) +
        rnd *
            ((f32)(DEG2SHORT_ANGLE2(87.1875f) + GETREG(MYKREG, 56)) -
             (f32)(DEG2SHORT_ANGLE2(45.0f) + GETREG(MYKREG, 58)))
    );

    vel = (5.1f + GETREG(MYKREG, 57) * 0.1f) +
          rnd * ((9.0f + GETREG(MYKREG, 55) * 0.1f) -
                 (5.1f + GETREG(MYKREG, 57) * 0.1f));

    scale = rnd * (0.76f * 0.01f) + 0.0024f;

    angle0 = effect->arg0;

    effect->velocity.y = vel * sin_s(angle1);
    effect->velocity.x = (vel * cos_s(angle1)) * sin_s(angle0);
    effect->velocity.z = (vel * cos_s(angle1)) * cos_s(angle0);

    effect->scale.x = scale;
    effect->scale.y = scale;
    effect->scale.z = scale;

    bzero(&effect->acceleration, sizeof(effect->acceleration));
    effect->acceleration.y = -0.5f;

    effect->effect_specific[0] = 0;
    effect->effect_specific[1] = (s16)(RANDOM_F(4608.0f) + -2304.0f);

    effect->timer = 80;
    effect->offset.x = rnd;
}

static void eResetbreak_Parts_mv(eEC_Effect_c* effect, GAME* game) {
    f32 y = mCoBG_GetShadowBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
    f32 rnd = effect->offset.x;

    effect->effect_specific[0] += effect->effect_specific[1];
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
    if (effect->position.y <= y + rnd * 10.0f && effect->velocity.y <= 0.0f) {
        effect->velocity.x *= 0.5f;
        effect->velocity.z *= 0.5f;
        effect->velocity.y = -(effect->velocity.y * 0.7f);
        effect->effect_specific[1] >>= 1;
    }

    if (ABS(effect->velocity.y) < 0.01f) {
        bzero(&effect->velocity, sizeof(effect->velocity));
        bzero(&effect->acceleration, sizeof(effect->acceleration));
        effect->effect_specific[1] = 0;
    }
}

extern Gfx ef_isibakuhatu_model[];

static void eResetbreak_Parts_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int a = (effect->timer / 80.0f) * 255.0f;

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_RotateY(effect->effect_specific[0], MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, 255, 255, (u8)a);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_isibakuhatu_model);

    CLOSE_DISP(game->graph);
}
