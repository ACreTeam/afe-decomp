#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "libultra/libultra.h"

extern u8 ef_dust01_0[];
extern u8 ef_dust01_1[];
extern u8 ef_dust01_2[];
extern u8 ef_dust01_3[];

static u8* eResetbreak_dust_texture_table[] = {
    ef_dust01_0,
    ef_dust01_1,
    ef_dust01_2,
    ef_dust01_3,
};

static void eResetbreak_Dust_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eResetbreak_Dust_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eResetbreak_Dust_mv(eEC_Effect_c* effect, GAME* game);
static void eResetbreak_Dust_dw(eEC_Effect_c* effect, GAME* game);

// clang-format off
eEC_PROFILE_c iam_ef_resetbreak_dust = {
    &eResetbreak_Dust_init,
    &eResetbreak_Dust_ct,
    &eResetbreak_Dust_mv,
    &eResetbreak_Dust_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
};
// clang-format on

static void eResetbreak_Dust_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_RESETBREAK_DUST, pos, NULL, game, NULL, item_name, prio, angle, arg1);
}

static void eResetbreak_Dust_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 angle = effect->arg0;
    f32 scale = 0.018f + RANDOM_F(0.0053999983f);
    f32 vel_z = 0.15f + RANDOM_F(0.15f);

    bzero(&effect->velocity, sizeof(effect->velocity));
    effect->velocity.z = vel_z;
    bzero(&effect->acceleration, sizeof(effect->acceleration));
    effect->acceleration.y = 0.1f;
    effect->scale.x = scale;
    effect->scale.y = scale;
    effect->scale.z = scale;
    eEC_CLIP->vector_rotate_y_proc(&effect->velocity, SHORT2RAD_ANGLE2(angle));
    effect->timer = 36;
}

static void eResetbreak_Dust_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
}

static u8 eRBD_2tile_texture[9][2] = {
    {0x00, 0x00},
    {0x00, 0x01},
    {0x01, 0x01},
    {0x01, 0x02},
    {0x02, 0x02},
    {0x02, 0x03},
    {0x03, 0x03},
    {0x03, 0x03},
    {0x03, 0x03},
};

static u8 eResetbreak_dust_alpha_pattern[9] = {
    0xFF, 0xFF, 0xFF, 0xE3, 0xC8, 0xC8, 0xC8, 0xC8,
    0x00
};

extern Gfx ef_dust01_modelT[];

static void eResetbreak_Dust_dw(eEC_Effect_c* effect, GAME* game) {
    static u8 prim_f_pattern[] = { 0, 127, 255, 127 };
    s16 counter = 36 - effect->timer;
    s16 idx = counter >> 2;
    u8 tex0_idx = eRBD_2tile_texture[idx][0];
    u8 tex1_idx = eRBD_2tile_texture[idx][1];

    OPEN_DISP(game->graph);

    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, eResetbreak_dust_texture_table[tex0_idx & 3]);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, eResetbreak_dust_texture_table[tex1_idx & 3]);
    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, prim_f_pattern[idx & 3], 255, 255, 255, eResetbreak_dust_alpha_pattern[idx]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_dust01_modelT);

    CLOSE_DISP(game->graph);
}
