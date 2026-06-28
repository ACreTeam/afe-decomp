#ifndef M_SUBMENU_OVL_H
#define M_SUBMENU_OVL_H

#include "types.h"
#include "m_submenu_ovl_h.h"
#include "m_submenu.h"
#include "graph.h"
#include "m_mail.h"
#include "PR/mbi.h"
#include "PreRender.h"
#include "m_map_ovl_h.h"
#include "m_bank_ovl_h.h"
#include "m_music_ovl_h.h"
#include "m_warning_ovl_h.h"
#include "m_editor_ovl_h.h"
#include "m_passwordChk_ovl_h.h"
#include "m_passwordMake_ovl_h.h"
#include "m_board_ovl_h.h"
#include "m_diary_ovl_h.h"
#include "m_address_ovl_h.h"
#include "m_editEndChk_ovl_h.h"
#include "m_haniwaPortrait_ovl_h.h"
#include "m_timeIn_ovl_h.h"
#include "m_repay_ovl_h.h"
#include "m_notice_ovl_h.h"
#include "m_birthday_ovl_h.h"
#include "m_tag_ovl_h.h"
#include "m_catalog_ovl_h.h"
#include "m_hand_ovl_h.h"
#include "m_inventory_ovl_h.h"
#include "m_player.h"
#include "m_cpmail_ovl_h.h"
#include "m_cporiginal_ovl_h.h"
#include "m_haniwa_ovl_h.h"
#include "m_mailbox_ovl_h.h"
#include "m_needlework_ovl_h.h"
#include "m_gba_ovl_h.h"
#include "m_cpedit_ovl_h.h"
#include "m_cpwarning_ovl_h.h"
#include "m_mscore_ovl_h.h"
#include "m_calendar_ovl_h.h"
#include "m_design_ovl_h.h"
#include "m_shutter_ovl_h.h"
#include "m_alarmIn_ovl_h.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mSM_OVL_PROC_MOVE,
    mSM_OVL_PROC_PLAY,
    mSM_OVL_PROC_WAIT,
    mSM_OVL_PROC_OBEY,
    mSM_OVL_PROC_END,

    mSM_OVL_PROC_NUM
};

#define mSM_OVL_FLAG_NONE (0)
#define mSM_OVL_FLAG_0 (1 << 0)
#define mSM_OVL_FLAG_USE_ITEM (1 << 1)
#define mSM_OVL_FLAG_USE_TAG (1 << 2)
#define mSM_OVL_FLAG_USE_HAND (1 << 3)
#define mSM_OVL_FLAG_USE_HANIWA_PORTRAIT (1 << 4)

typedef void (*mSM_OVL_CT_PROC)(Submenu*);
typedef void (*mSM_OVL_DT_PROC)(Submenu*);
typedef void (*mSM_OVL_SET_PROC)(Submenu*);

typedef struct submenu_ovl_dlftbl_s {
    int _00;
    int _04;
    u8* seg_start;
    u8* seg_end;
    mSM_OVL_CT_PROC ct_proc;
    mSM_OVL_DT_PROC dt_proc;
    mSM_OVL_SET_PROC set_proc;
    int in_ram_flag;
} mSM_Ovl_dlftbl_c;

typedef struct submenu_segment_s {
    int _00;
    s16 player_main_anime_idx;
    s16 player_item_anime_idx;
    s16 change_player_main_anime_idx;
    s16 player_anime_timer;
    s16 player_umbrella_bank_idx;
    s16 umbrella_ids[2];
    s8 player_part_table[mPlayer_JOINT_NUM + 1];
    int dlftbl_loaded_num;
    mSM_Ovl_dlftbl_c* dlftbl_loaded_tbl[8];
} mSM_Segment_c;

typedef struct submenu_menu_info_s {
    int menu_type;
    int proc_status;

    int pre_menu_type;
    SUBMENU_PROC pre_move_func;
    SUBMENU_GAME_PROC pre_draw_func;

    int next_menu_type;

    f32 position[2];
    f32 speed[2];

    char* _28;
    int open_flag;

    int next_proc_status;
    s16 move_drt;
    s16 move_flag;

    int data0;
    int data1;
    void* data2;
    int data3;
} mSM_MenuInfo_c;

typedef void (*mSM_HAND_MOVE_FUNC)(Submenu*);
typedef void (*mSM_HAND_DRAW_FUNC)(Submenu*, GAME*);
typedef void (*mSM_TAG_MOVE_FUNC)(Submenu*, mSM_MenuInfo_c*);
typedef void (*mSM_TAG_DRAW_FUNC)(Submenu*, GAME*, int);

typedef struct submenu_control_s {
    SUBMENU_PROC menu_move_func;
    SUBMENU_GAME_PROC menu_draw_func;

    mSM_HAND_MOVE_FUNC hand_move_func;
    mSM_HAND_DRAW_FUNC hand_draw_func;

    mSM_TAG_MOVE_FUNC tag_move_func;
    mSM_TAG_DRAW_FUNC tag_draw_func;

    int stick_release;
    u32 trigger;
    u32 last_trigger;
    s16 repeat_timer;
    s16 texture_movement_angle;
    f32 texture_pos[2];
    int animation_flag;
} mSM_Control_c;

typedef void (*mSM_RETURN_FUNC_PROC)(Submenu*, mSM_MenuInfo_c*);
typedef void (*mSM_MOVE_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);
typedef void (*mSM_MOVE_END_PROC)(Submenu*, mSM_MenuInfo_c*);
typedef void (*mSM_MOVE_CHG_BASE_PROC)(mSM_MenuInfo_c*, int);
typedef void (*mSM_SET_CHAR_MATRIX_PROC)(GRAPH*);
typedef void (*mSM_CBUF_COPY_PROC)(GRAPH*, PreRender*, int, int, int);
typedef void (*mSM_SET_DRAWMODE_PROC)(GRAPH*, PreRender*, f32, f32, s16);
typedef void (*mSM_DRAW_ITEM_PROC)(GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, mActor_name_t item, int present_flag,
                                   int color_flag, int anim_frame, int shadow_flag, int mark_flag);
typedef void (*mSM_DRAW_MAIL_PROC)(GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, Mail_c* mail, int color_flag,
                                   int shadow_flag, int mark_flag);
typedef void (*mSM_SETUP_VIEW_PROC)(Submenu*, GRAPH*, int);
typedef void (*mSM_CHANGE_VIEW_PROC)(GRAPH*, f32, f32, f32, f32, s16, int, int);

typedef void (*mSM_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

/* sizeof(struct submenu_overlay_s) == 0xAE8 */
struct submenu_overlay_s {
    /* TODO: finish */
    /* 0x000 */ mSM_Segment_c segment;
    /* 0x054 */ mSM_MenuInfo_c menu_info[mSM_OVL_NUM];
    /* 0x9E4 */ mSM_Control_c menu_control;
    /* 0xA18 */ mSM_RETURN_FUNC_PROC return_func_proc;
    /* 0xA1C */ mSM_MOVE_MOVE_PROC move_Move_proc;
    /* 0xA20 */ mSM_MOVE_END_PROC move_End_proc;
    /* 0xA24 */ mSM_MOVE_CHG_BASE_PROC move_chg_base_proc;
    /* 0xA28 */ mSM_SET_CHAR_MATRIX_PROC set_char_matrix_proc;
    /* 0xA2C */ mSM_CBUF_COPY_PROC cbuf_copy_proc;
    /* 0xA30 */ mSM_SET_DRAWMODE_PROC set_drawMode_proc;
    /* 0xA34 */ mSM_DRAW_ITEM_PROC draw_item_proc;
    /* 0xA38 */ mSM_DRAW_MAIL_PROC draw_mail_proc;
    /* 0xA3C */ mSM_SETUP_VIEW_PROC setup_view_proc;
    /* 0xA40 */ void* unused_func_A40;
    /* 0xA44 */ mSM_CHANGE_VIEW_PROC change_view_proc;
    /* 0xA48 */ void* _A48;
    /* 0xA4C */ void* _A4C;
    /* 0xA50 */ void* _A50;
    /* 0xA54 */ mTG_Ovl_c* tag_ovl;
    /* 0xA58 */ mHD_Ovl_c* hand_ovl;
    /* 0xA5C */ mHP_Ovl_c* haniwaPortrait_ovl;
    /* 0xA60 */ mIV_Ovl_c* inventory_ovl;
    /* 0xA64 */ mED_Ovl_c* editor_ovl;
    /* 0xA68 */ mBD_Ovl_c* board_ovl;
    /* 0xA6C */ mAD_Ovl_c* address_ovl;
    /* 0xA70 */ mMB_Ovl_c* mailbox_ovl;
    /* 0xA74 */ mHW_Ovl_c* haniwa_ovl;
    /* 0xA78 */ mTI_Ovl_c* timeIn_ovl;
    /* 0xA7C */ mEE_Ovl_c* editEndChk_ovl;
    /* 0xA80 */ mWR_Ovl_c* warning_ovl;
    /* 0xA84 */ mRP_Ovl_c* repay_ovl;
    /* 0xA88 */ mMS_Ovl_c* mscore_ovl;
    /* 0xA8C */ mMP_Ovl_c* map_ovl;
    /* 0xA90 */ mNT_Ovl_c* notice_ovl;
    /* 0xA94 */ mBR_Ovl_c* birthday_ovl;
    /* 0xA98 */ mCM_Ovl_c* cpmail_ovl;
    /* 0xA9C */ mCW_Ovl_c* cpwarning_ovl;
    /* 0xAA0 */ mCE_Ovl_c* cpedit_ovl;
    /* 0xAA4 */ mCL_Ovl_c* catalog_ovl;
    /* 0xAA8 */ mMU_Ovl_c* music_ovl;
    /* 0xABC */ mBN_Ovl_c* bank_ovl;
    /* 0xAB0 */ mNW_Ovl_c* needlework_ovl;
    /* 0xAB4 */ mCO_Ovl_c* cporiginal_ovl;
    /* 0xAB8 */ mDE_Ovl_c* design_ovl;
    /* 0xABC */ mGB_Ovl_c* gba_ovl;
    /* 0xAC0 */ mDI_Ovl_c* diary_ovl;
    /* 0xAC4 */ mCD_Ovl_c* calendar_ovl;
    /* 0xAC8 */ mPM_Ovl_c* passwordMake_ovl;
    /* 0xACC */ mPC_Ovl_c* passwordChk_ovl;
    /* 0xAD0 */ mAL_Ovl_c* alarmIn_ovl;
    /* 0xAD4 */ mST_Ovl_c* shutter_ovl;
    /* 0xAD8 */ void* film_ovl;
    /* 0xADC */ u8 hboard_exists;
    /* 0xADD */ u8 le_exists;
    /* 0xADE */ u8 _ADE;
    /* 0xADF */ u8 _ADF;
    /* 0xAE0 */ int _AE0;
    /* 0xAE4 */ Mtx* projection_matrix;
};

extern void mSM_menu_ovl_init(Submenu* submenu);
extern void mSM_draw_original(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, mActor_name_t item,
                              int color_flag);

#ifdef __cplusplus
}
#endif

#endif
