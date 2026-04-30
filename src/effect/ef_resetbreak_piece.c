#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eResetbreak_Piece_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eResetbreak_Piece_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eResetbreak_Piece_mv(eEC_Effect_c* effect, GAME* game);
static void eResetbreak_Piece_dw(eEC_Effect_c* effect, GAME* game);

// clang-format off
eEC_PROFILE_c iam_ef_resetbreak_piece = {
    &eResetbreak_Piece_init,
    &eResetbreak_Piece_ct,
    &eResetbreak_Piece_mv,
    &eResetbreak_Piece_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
};
// clang-format on

static void eResetbreak_Piece_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_RESETBREAK_PIECE, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eResetbreak_Piece_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    f32 vel_xz = 0.35f + RANDOM_F(1.5f);
    f32 vel_y = 0.5f + RANDOM_F(1.85f);
    s16 angle = *(s16*)ct_arg + DEG2SHORT_ANGLE(360.0f) + RANDOM(DEG2SHORT_ANGLE2(80.0f)) - DEG2SHORT_ANGLE(180.0f);

    effect->effect_specific[4] = RANDOM(10) * 2 + 60;
    effect->timer = effect->effect_specific[4];
    effect->scale.x = effect->scale.y = effect->scale.z = 0.004f + RANDOM2_F(0.002f);
    effect->position.x += RANDOM2_F(10.0f);
    effect->position.y += 12.0f + RANDOM2_F(10.0f);
    effect->position.z += RANDOM2_F(10.0f);
    effect->offset.x = effect->position.y;
    effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
    effect->offset.y += 3.0f;
    effect->velocity.x = vel_xz * sin_s(angle);
    effect->velocity.z = vel_xz * cos_s(angle);
    effect->velocity.y = vel_y;
    effect->acceleration.y = -0.25f;
    effect->effect_specific[0] = qrand();
    effect->effect_specific[2] = qrand();
    effect->effect_specific[1] = qrand() & 0x1FFF;
    effect->effect_specific[3] = qrand() & 0x1FFF;
}

static void eResetbreak_Piece_mv(eEC_Effect_c* effect, GAME* game) {
    effect->offset.x = effect->position.y;
    effect->offset.z = effect->offset.y;
    effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
    effect->effect_specific[0] += effect->effect_specific[1];
    effect->effect_specific[2] += effect->effect_specific[3];

    if (effect->position.y < effect->offset.y && effect->offset.x >= effect->offset.y && effect->velocity.y < 0.0f) {
        effect->position.y = effect->offset.y;
        effect->velocity.x *= 0.6f;
        effect->velocity.y *= -0.6f;
        effect->velocity.z *= 0.6f;
        effect->effect_specific[1] >>= 1;
        effect->effect_specific[3] >>= 1;
    }

    if (effect->position.y < effect->offset.y && effect->position.y >= effect->offset.z) {
        effect->position.x -= effect->velocity.x;
        effect->position.y -= effect->velocity.y;
        effect->position.z -= effect->velocity.z;
        effect->velocity.x *= -0.6f;
        effect->velocity.z *= -0.6f;
    }
}

extern Gfx ef_isikakera_model[];

static void eResetbreak_Piece_dw(eEC_Effect_c* effect, GAME* game) {
    int a = (effect->timer / (f32)effect->effect_specific[4]) * 255.0f;

    
    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);
    
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateX(effect->effect_specific[0], MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[2], MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, 255, 255, a);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_isikakera_model);

    CLOSE_DISP(game->graph);
}
