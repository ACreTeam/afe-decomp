#ifndef AC_NPC_STATION_MASTER_H
#define AC_NPC_STATION_MASTER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aSTM_THINK_GET_OFF_WAIT,
    aSTM_THINK_TURN,
    aSTM_THINK_GREET_ARRIVAL,
    aSTM_THINK_GREET_RETURN,
    aSTM_THINK_GREET_FOREIGNER,
    aSTM_THINK_INTRO_WAIT,
    aSTM_THINK_FIRST_JOB_WAIT,
    aSTM_THINK_INTERRUPT_TURN,
    aSTM_THINK_INTERRUPT_MOVE,
    aSTM_THINK_TALK_WAIT,
    aSTM_THINK_FOREIGNER_TALK_WAIT,
    aSTM_THINK_MAKE_TRAIN_BF,
    aSTM_THINK_MAKE_TRAIN,
    aSTM_THINK_TRAIN_ARRIVE_WAIT,
    aSTM_THINK_MOVE_TURN_BF,
    aSTM_THINK_MOVE_TURN,
    aSTM_THINK_MOVE,
    aSTM_THINK_LOOK_PLAYER,
    aSTM_THINK_SAYONARA,
    aSTM_THINK_IN_TRAIN,
    aSTM_THINK_IN_TRAIN2,
    aSTM_THINK_SEE_OFF,
    aSTM_THINK_GAME_END,

    aSTM_THINK_NUM
};

enum {
    aSTM_THINK_INIT_NONE,
    aSTM_THINK_INIT_GET_OFF_WAIT,
    aSTM_THINK_INIT_INTRO_DEMO_WAIT,
    aSTM_THINK_INIT_INTERRUPT_TURN,
    aSTM_THINK_INIT_INTERRUPT_MOVE,
    aSTM_THINK_INIT_MAKE_TRAIN,
    aSTM_THINK_INIT_MAKE_TRAIN_BF,
    aSTM_THINK_INIT_MOVE_TURN,
    aSTM_THINK_INIT_MOVE,
    aSTM_THINK_INIT_LOOK_P,
    aSTM_THINK_INIT_SEE_OFF,
    aSTM_THINK_INIT_GAME_END,

    aSTM_THINK_INIT_IN_TRAIN,

    aSTM_THINK_INIT_NUM
};

enum {
    aSTM_THINK_PROC_NONE,
    aSTM_THINK_PROC_GET_OFF_WAIT,
    aSTM_THINK_PROC_TURN,
    aSTM_THINK_PROC_LOOK_PLAYER,
    aSTM_THINK_PROC_INTERRUPT_TURN,
    aSTM_THINK_PROC_INTERRUPT_MOVE,
    aSTM_THINK_PROC_MAKE_TRAIN_BF,
    aSTM_THINK_PROC_MAKE_TRAIN,
    aSTM_THINK_PROC_TRAIN_ARRIVE_WAIT,
    aSTM_THINK_PROC_MOVE_TURN_BF,
    aSTM_THINK_PROC_MOVE,
    aSTM_THINK_PROC_IN_TRAIN,
    aSTM_THINK_PROC_IN_TRAIN2,
    aSTM_THINK_PROC_SEE_OFF,
    aSTM_THINK_PROC_TALK_WAIT,

    aSTM_THINK_PROC_NUM
};

enum {
    aSTM_TALK_REQUEST_NONE,
    aSTM_TALK_REQUEST_NORM,
    aSTM_TALK_REQUEST_FORCE,

    aSTM_TALK_REQUEST_NUM,
};

typedef struct npc_station_actor_s NPC_STATION_MASTER_ACTOR;

typedef void (*aSTM_TALK_PROC)(NPC_STATION_MASTER_ACTOR*, GAME_PLAY*);

struct npc_station_actor_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0xB68 */ aSTM_TALK_PROC talk_proc;
    /* 0xB6C */ ACTOR* train_actor_p;
    /* 0xB70 */ f32 move_ofs_x;
    /* 0xB74 */ u8 think_idx;
    /* 0xB75 */ u8 next_think_idx;
    /* 0xB76 */ u8 talk_idx;
    /* 0xB77 */ u8 melody_save;
    /* 0xB78 */ u8 think_proc_idx;
    /* 0xB7A */ u16 sound;
    /* 0xB7C */ u16 happening_sound;
    /* 0xB7E */ u8 timer;
    /* 0xB7F */ u8 talk_proc_idx;
    /* 0xB80 */ u8 station_check_res;
    /* 0xB81 */ u8 chan;
    /* 0xB82 */ u8 station_err;
    /* 0xB83 */ u8 check_moving_info;
    /* 0xB84 */ s16 sd_town_idx;
};

extern ACTOR_PROFILE Npc_Station_Master_Profile;

#ifdef __cplusplus
}
#endif

#endif
