#ifndef AC_ANIMAL_LOGO_H
#define AC_ANIMAL_LOGO_H

#include "types.h"
#include "game.h"
#include "m_actor.h"
#include "m_lib.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*aAL_DATA_INIT_PROC)(GAME_PLAY*);

typedef struct animal_logo_clip_s {
    aAL_DATA_INIT_PROC data_init_proc;
} aAL_Clip_c;

#define aAL_BACK_FADEIN_RATE 20
#define aAL_BACK_FADEIN_MAX 220

#define aAL_TIMER 60
#define aAL_FADEOUT_TIMER 26

#define aAL_COPYRIGHT_ALPHA_RATE 63

typedef struct actor_animal_logo_s ANIMAL_LOGO_ACTOR;

typedef void (*ANIMAL_LOGO_ACTION_PROC)(ANIMAL_LOGO_ACTOR*, GAME*);

struct actor_animal_logo_s {
    ACTOR actor_class;
    
    int action;
    ANIMAL_LOGO_ACTION_PROC action_proc;

    int title_timer;
    int logo_piece_count;
    float rotation[6];
    float rotation_speed[6];

    // s16 back_opacity;
    int copyright_opacity;
    f32 press_start_opacity;
    s16 start_opacity_timer;
    u8 _1BE;
    int titledemo_no;
    int _1C4;

    int _[6];

    float e_pos_x;
    float e_move_right_speed;
    float _1E8;
    float _1EC;
    float _1F0;
};

enum {
    aAL_ACTION_E_PLUS_RIGHT_MOVE_START_WAIT,
    aAL_ACTION_LOGO_ROTATE,
    aAL_ACTION_E_PLUS_LEFT_MOVE_START_WAIT,
    aAL_ACTION_PURURUN_START_WAIT,
    aAL_ACTION_PURURUN_END_WAIT,
    aAL_ACTION_START_KEY_CHK_START_WAIT,
    aAL_ACTION_GAME_START_WAIT,
    aAL_ACTION_FADE_OUT_START_WAIT,
    aAL_ACTION_8,
    aAL_ACTION_9,

    aAL_ACTION_NUM
};

extern ACTOR_PROFILE Animal_Logo_Profile;

#ifdef __cplusplus
}
#endif

#endif
