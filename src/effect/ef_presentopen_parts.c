#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "libultra/libultra.h"

static void ePOP_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void ePOP_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void ePOP_mv(eEC_Effect_c* effect, GAME* game);
static void ePOP_dw(eEC_Effect_c* effect, GAME* game);

// clang-format off
eEC_PROFILE_c iam_ef_presentopen_parts = {
    &ePOP_init,
    &ePOP_ct,
    &ePOP_mv,
    &ePOP_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
};
// clang-format on

static void ePOP_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_PRESENTOPEN_PARTS, pos, NULL, game, NULL, item_name, prio, arg0, angle);
}

static void ePOP_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 angle = effect->arg1;
    f32 rng = RANDOM_F(1.0f);
    f32 vel_xz;
    f32 vel_x;
    f32 vel_z;
    
    if ((effect->arg0 == 0 || effect->arg0 == 5) != FALSE) {
        vel_xz = 0.0f;
    } else {
        vel_xz = 0.2f + rng * 0.2f;
    }

    vel_x = vel_xz * sin_s(angle);
    vel_z = vel_xz * cos_s(angle);

    effect->effect_specific[0] = angle;
    effect->timer = 80;
    bzero(&effect->velocity, sizeof(effect->velocity));
    bzero(&effect->acceleration, sizeof(effect->acceleration));
    effect->velocity.x = vel_x;
    effect->velocity.z = vel_z;
    effect->velocity.y = 1.2f;
    effect->acceleration.y = -0.05f;
    effect->scale.x = 0.01f;
    effect->scale.y = 0.01f;
    effect->scale.z = 0.01f;
    effect->effect_specific[1] = 0;
    effect->effect_specific[2] = (s16)(rng * 368.0f + 512.0f);
}

static void ePOP_mv(eEC_Effect_c* effect, GAME* game) {
    s16 counter = 80 - effect->timer;

    if (counter >= 5) {
        effect->effect_specific[1] += effect->effect_specific[2];
    }

    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
}

extern Gfx ef_present1_model[];
extern Gfx ef_present2_model[];
extern Gfx ef_present3_model[];
extern Gfx ef_present4_model[];
extern Gfx ef_present5_model[];

static Gfx* ePOP_model_table[] = {
    ef_present1_model,
    ef_present2_model,
    ef_present3_model,
    ef_present4_model,
    ef_present5_model,
};

static void ePOP_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int a;
    float scale;
    
    if (effect->arg0 >= 0 && (u32)effect->arg0 < 5) {
        s16 timer = effect->timer;
        s16 counter = 80 - timer;

        if (counter < 45) {
            a = 255;
        } else {
            a = (effect->timer / 45.0f) * 255.0f;
        }
        
        OPEN_DISP(game->graph);

        _texture_z_light_fog_prim_xlu(game->graph);
        Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
        Matrix_RotateY(effect->effect_specific[0], MTX_MULT);
        Matrix_RotateX(effect->effect_specific[1], MTX_MULT);
        Matrix_RotateY(-effect->effect_specific[0], MTX_MULT);
        scale = 1.0f + GETREG(MYKREG, 27) * 0.01f;
        Matrix_scale(effect->scale.x * scale, effect->scale.y * scale, effect->scale.z * scale, MTX_MULT);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, 255, 255, a);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ePOP_model_table[effect->arg0]);

        CLOSE_DISP(game->graph);
    }
}
