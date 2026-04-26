#ifndef M_PLAY_H
#define M_PLAY_H

#include "types.h"
#include "game.h"
#include "libultra/ultratypes.h"
#include "m_view.h"
#include "m_camera2.h"
#include "m_submenu.h"
#include "m_kankyo.h"
#include "m_lights.h"
#include "m_pause.h"
#include "m_field_info.h"
#include "m_event.h"
#include "m_fbdemo_wipe.h"
#include "m_collision_obj.h"
#include "m_play_h.h"
#include "m_scene.h"
#include "PreRender.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    FADE_TYPE_NONE,
    FADE_TYPE_IN,
    FADE_TYPE_OUT,
    FADE_TYPE_OUT_START_EMU,
    FADE_TYPE_OUT_RETURN_TITLE,
    FADE_TYPE_OUT_GAME_END_TRAIN,
    FADE_TYPE_OUT_GAME_END,
    FADE_TYPE_LOCK,
    FADE_TYPE_SELECT,
    FADE_TYPE_DEMO,
    FADE_TYPE_SELECT_END,
    FADE_TYPE_EVENT,
    FADE_TYPE_OTHER_ROOM,
    FADE_TYPE_OUT_NO_RESTART,

    FADE_TYPE_NUM
};

enum {
    WIPE_TYPE_NORMAL,
    WIPE_TYPE_TRIFORCE,
    WIPE_TYPE_FADE_WHITE,
    WIPE_TYPE_FADE_BLACK,
    WIPE_TYPE_CIRCLE_LEFT,
    WIPE_TYPE_CIRCLE_RIGHT,
    WIPE_TYPE_EVENT,

    WIPE_TYPE_NUM
};

enum {
    WIPE_MODE_NONE,
    WIPE_MODE_CREATE,
    WIPE_MODE_INIT,
    WIPE_MODE_MOVE,

    WIPE_MODE_NUM
};

enum {
    FBDEMO_MODE_NONE,
    FBDEMO_MODE_CREATE,
    FBDEMO_MODE_INIT,
    FBDEMO_MODE_MOVE,

    FBDEMO_MODE_NUM
};

typedef int (*DRAW_CHK_PROC)(ACTOR*, GAME_PLAY*);
typedef void (*PLAY_WIPE_PROC)(GAME_PLAY*);

/* sizeof(struct game_play_s) == 0x25A0 */
struct game_play_s {
    /* 0x0000 */ GAME game;
    /* 0x00E4 */ s16 scene_id;
    /* 0x00E8 */ mFI_block_tbl_c block_table;
    /* 0x00F8 */ mFI_block_tbl_c last_block_table;
    /* 0x0108 */ u8 _0104[0x010C - 0x0104];
    /* 0x0110 */ Scene_Word_u* current_scene_data;
    /* 0x0114 */ Object_Exchange_c object_exchange;
    /* 0x1A6C */ // u8 pad[4]; // view is aligned to 8 bytes
    /* 0x1A70 */ View view;
    /* 0x1B90 */ Camera2 camera;
    /* 0x1CC8 */ Kankyo kankyo;
    /* 0x1D98 */ Global_light global_light;
    /* 0x1DA8 */ pause_t pause;
    /* 0x1DB0 */ Actor_info actor_info;
    /* 0x1DF4 */ Submenu submenu;
    /* 0x1F44 */ s8 submenu_ground_idx;
    /* 0x1F48 */ char* submenu_ground_tex[2];
    /* 0x1F50 */ char* submenu_ground_pallet[2];
    /* 0x1F58 */ PreRender prerender;
    /* 0x1FA0 */ Door_info_c door_info;
    /* 0x1FA8 */ int next_scene_no;
    /* 0x1FAC */ MtxF projection_matrix;
    /* 0x1FEC */ MtxF billboard_matrix;
    /* 0x202C */ Mtx* billboard_mtx_p;
    /* 0x2030 */ u32 game_frame;
    /* 0x2034 */ u8 _2094;
    /* 0x2035 */ u8 actor_data_num;
    /* 0x2036 */ u8 ctrl_actor_data_num;
    /* 0x2037 */ u8 obj_bank_data_num;
    /* 0x2038 */ Actor_data* player_data;
    /* 0x203C */ Actor_data* actor_data;
    /* 0x2040 */ s16* ctrl_actor_data;
    /* 0x2044 */ s16* obj_bank_data;
    /* 0x2048 */ int _20A8;
    /* 0x204C */ Event_c event;
    /* 0x2070 */ u8 fb_fade_type;
    /* 0x2071 */ u8 fb_wipe_type;
    /* 0x2072 */ u8 fb_mode;
    /* 0x2073 */ u8 fb_wipe_mode;
    /* 0x2078 */ fbdemo_wipe fbdemo_wipe;
    /* 0x22B8 */ fbdemo_fade color_fade;
    /* 0x22C8 */ CollisionCheck_c collision_check;
    /* 0x2398 */ DRAW_CHK_PROC draw_chk_proc; // only used by mikanbox actor
    /* 0x239C */ rgba8888 fade_color_value;
    /* 0x23A0 */ Scene_data_status_c* scene_data_status;
    /* 0x23A4 */ u8 _23A4[0x25A0 - 0x23A4];
};

extern void play_cleanup(GAME*);
extern void play_init(GAME*);
extern void play_main(GAME*);

#ifdef __cplusplus
}
#endif

#endif
