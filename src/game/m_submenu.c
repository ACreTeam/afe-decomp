#include "m_submenu.h"
#include "m_submenu_ovl.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "m_quest.h"
#include "libultra/libultra.h"
#include "m_sdcard.h"

static mSM_dlftbl_c SubmenuArea_dlftbl[mSM_DLF_NUM] = { { NULL, 0, 0, 0, 0, 0, "submenu_ovl" },
                                                        { NULL, 0, 0, 0, 0, 0, "player_actor" } };

static mSM_dlftbl_c* SubmenuArea_visit = NULL;
static void* SubmenuArea_allocp = NULL;

extern int mSM_COLLECT_INSECT_GET(int idx) {
    u32 ftr_idx = (FTR_SUM_MONSHIRO << 2) + (idx << 2);
    return (Common_Get(now_private)->furniture_collected_bitfield[ftr_idx >> 2 >> 5] &
            (1 << ((ftr_idx >> 2) & 0x1F))) != 0;
}

extern void mSM_COLLECT_INSECT_SET(int idx) {
    u32 ftr_idx = (FTR_SUM_MONSHIRO << 2) + (idx << 2);
    Common_Get(now_private)->furniture_collected_bitfield[ftr_idx >> 2 >> 5] |= (1 << ((ftr_idx >> 2) & 0x1F));
}

static int mSM_CHECK_ALL_INSECT_GET_SUB() {
    int i;
    int n = 0;

    for (i = 0; i < INSECT_ONLY_NUM; i++) {
        if (mSM_COLLECT_INSECT_GET(i) != FALSE) {
            n++;
        }
    }

    return n;
}

extern int mSM_CHECK_ALL_INSECT_GET() {
    if (mSM_CHECK_ALL_INSECT_GET_SUB() == INSECT_ONLY_NUM) {
        return TRUE;
    }

    return FALSE;
}

extern int mSM_CHECK_LAST_INSECT_GET(int idx) {
    int res = FALSE;

    if (mSM_CHECK_ALL_INSECT_GET_SUB() == (INSECT_ONLY_NUM - 1) && mSM_COLLECT_INSECT_GET(idx) == FALSE) {
        res = TRUE;
    }

    return res;
}

extern int mSM_COLLECT_FISH_GET(int idx) {
    u32 ftr_idx = (FTR_SUM_FUNA << 2) + (idx << 2);
    return (Common_Get(now_private)->furniture_collected_bitfield[ftr_idx >> 2 >> 5] &
            (1 << ((ftr_idx >> 2) & 0x1F))) != 0;
}

extern void mSM_COLLECT_FISH_SET(int idx) {
    u32 ftr_idx = (FTR_SUM_FUNA << 2) + (idx << 2);
    Common_Get(now_private)->furniture_collected_bitfield[ftr_idx >> 2 >> 5] |= (1 << ((ftr_idx >> 2) & 0x1F));
}

static int mSM_CHECK_ALL_FISH_GET_SUB() {
    int i;
    int n = 0;

    for (i = 0; i < FISH_NUM; i++) {
        if (mSM_COLLECT_FISH_GET(i) != FALSE) {
            n++;
        }
    }

    return n;
}

extern int mSM_CHECK_ALL_FISH_GET() {
    if (mSM_CHECK_ALL_FISH_GET_SUB() == FISH_NUM) {
        return TRUE;
    }

    return FALSE;
}

extern int mSM_CHECK_LAST_FISH_GET(int idx) {
    int res = FALSE;

    if (mSM_CHECK_ALL_FISH_GET_SUB() == (FISH_NUM - 1) && mSM_COLLECT_FISH_GET(idx) == FALSE) {
        res = TRUE;
    }

    return res;
}

extern int SubmenuArea_IsPlayer() {
    return SubmenuArea_visit == &SubmenuArea_dlftbl[mSM_DLF_PLAYER_ACTOR];
}

static void mSM_load_player_anime(GAME_PLAY* play) {
    // stubbed
}

static void SubmenuArea_DoLink(mSM_dlftbl_c* dlftbl, Submenu* submenu, int dlf_idx) {
    dlftbl->_00 = SubmenuArea_allocp;
    dlftbl->_14 = 0;
    SubmenuArea_visit = dlftbl;
    submenu->overlay_address = dlftbl->_00;
    submenu->next_overlay_address = dlftbl->_00;
}

static void SubmenuArea_DoUnlink(mSM_dlftbl_c* dlftbl, Submenu* submenu) {
    if (dlftbl->_00 != NULL) {
        submenu->overlay_address = dlftbl->_00;
        submenu->next_overlay_address = dlftbl->_00;
        dlftbl->_14 = 0;
        dlftbl->_00 = NULL;
        SubmenuArea_visit = NULL;
    }
}

static int mSM_ovlptr_dllcnv_sub(void* proc, mSM_dlftbl_c* dlftbl, Submenu* submenu, int dlf_idx) {
    if (dlf_idx == mSM_DLF_SUBMENU_OVL || dlf_idx == mSM_DLF_PLAYER_ACTOR) {
        SubmenuArea_DoLink(dlftbl, submenu, dlf_idx);
        return TRUE;
    }

    return FALSE;
}

extern void* mSM_ovlptr_dllcnv(void* proc, Submenu* submenu, int dlf_idx) {
    if (SubmenuArea_visit != NULL) {
        return; // ??
    } else if (mSM_ovlptr_dllcnv_sub(proc, SubmenuArea_dlftbl, submenu, dlf_idx) == FALSE) {
        return NULL;
    }

    return proc;
}

extern void mSM_submenu_ovlptr_init(GAME_PLAY* play) {
    SubmenuArea_allocp = (void*)1;
    SubmenuArea_visit = NULL;
}

extern void mSM_submenu_ovlptr_cleanup(Submenu* submenu) {
    if (SubmenuArea_visit != NULL) {
        SubmenuArea_DoUnlink(SubmenuArea_visit, submenu);
        SubmenuArea_visit = NULL;
    }

    SubmenuArea_allocp = NULL;
}

extern void load_player(Submenu* submenu) {
    mSM_dlftbl_c* dlftbl = &SubmenuArea_dlftbl[mSM_DLF_PLAYER_ACTOR];

    if (SubmenuArea_visit != dlftbl) {
        if (SubmenuArea_visit != NULL) {
            SubmenuArea_DoUnlink(SubmenuArea_visit, submenu);
        }

        SubmenuArea_DoLink(dlftbl, submenu, mSM_DLF_PLAYER_ACTOR);
    }
}

extern void mSM_submenu_ct(Submenu* submenu) {
    bzero(submenu, sizeof(Submenu));
    submenu->process_status = mSM_PROCESS_WAIT;
    submenu->wait_timer = 0;

    if (Common_Get(submenu_disabled) == TRUE) {
        submenu->start_refuse = TRUE;
        Common_Set(submenu_disabled, FALSE);
    }

    submenu->move_proc = (SUBMENU_PROC)&none_proc1;
    submenu->draw_proc = (SUBMENU_GAME_PROC)&none_proc1;
}

extern void mSM_submenu_dt(Submenu* submenu) {
    // stubbed
}

extern void mSM_open_submenu(Submenu* submenu, int type, int arg0, int arg1) {
    mSM_open_submenu_new2(submenu, type, arg0, arg1, NULL, 0);
}

extern void mSM_open_submenu_new(Submenu* submenu, int type, int arg0, int arg1, void* arg2) {
    mSM_open_submenu_new2(submenu, type, arg0, arg1, arg2, 0);
}

extern void mSM_open_submenu_new2(Submenu* submenu, int type, int arg0, int arg1, void* arg2, int arg3) {
    submenu->menu_type = type;
    submenu->param0 = arg0;
    submenu->param1 = arg1;
    submenu->param2 = arg2;
    submenu->param3 = arg3;
    submenu->capture_display_mode = mSM_CAPTURE_DISPLAY_MODE_SUBMENU;
}

static void mSM_Reset_player_btn_type1(GAME_PLAY* play) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

    if (player != NULL) {
        player->a_btn_pressed = FALSE;
        player->a_btn_triggers_submenu = TRUE;
    }
}

static void mSM_Reset_player_btn_type2(GAME_PLAY* play) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

    if (player != NULL) {
        player->a_btn_triggers_submenu = TRUE;
    }
}

#define mSM_MAP_CHK_BANNED_SCENE(scene_no) ((scene_no) == SCENE_COTTAGE_MY || (scene_no) == SCENE_COTTAGE_NPC)

static int mSM_check_open_map_new(GAME_PLAY* play) {
    ACTOR* playerx;
    int bx, bz;
    int ret = FALSE;

    if (mSM_CHECK_OPEN_MAP() == TRUE) {
        playerx = GET_PLAYER_ACTOR_ACTOR(play);
        if (playerx != NULL && mSM_MAP_CHK_BANNED_SCENE(Save_Get(scene_no)) == FALSE) {
            mFI_Wpos2BlockNum(&bx, &bz, playerx->world.position);
            if (mFI_CheckBlockKind_OR(bx, bz, mRF_BLOCKKIND_OCEAN) == FALSE) {
                ret = TRUE;
            }
        }
    }

    return ret;
}

static int mSM_check_open_INVENTORY(GAME_PLAY* play) {
    int ret = FALSE;

    if (chkTrigger(mSM_INV_BUTTON_0) || chkTrigger(mSM_INV_BUTTON_1)) {
        if (!Common_Get(reset_flag) && !play->submenu.start_refuse && play->submenu.start_refuse_timer == 0 &&
            mPlib_able_submenu_type1((GAME*)play) && mEv_CheckFirstIntro() == FALSE) {
            ret = TRUE;
        }
    }

    return ret;
}

static int mSM_check_open_MAP(GAME_PLAY* play) {
    int ret = FALSE;

    if (mSM_check_open_map_new(play) == TRUE && !Common_Get(reset_flag) && play->submenu.start_refuse == FALSE &&
        play->submenu.start_refuse_timer == 0 && mPlib_able_submenu_type1((GAME*)play) &&
        mEv_CheckFirstIntro() == FALSE) {
        ret = TRUE;
    }

    return ret;
}

static int mSM_check_open_FG(GAME_PLAY* play) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);
    int ret = FALSE;

    if (player != NULL && player->a_btn_pressed == TRUE && !Common_Get(reset_flag) &&
        play->submenu.start_refuse == FALSE && play->submenu.start_refuse_timer == 0 &&
        mPlib_able_submenu_type1((GAME*)play)) {
        s16 y_dir = player->actor_class.shape_info.rotation.y;

        y_dir -= DEG2SHORT_ANGLE(-180.0f);
        if (ABS(y_dir) < DEG2SHORT_ANGLE(45.0f)) {
            ret = TRUE;
        }
    }

    return ret;
}

static int mSM_check_open_SHUTTER_condition(GAME_PLAY* play) {
    int ret = FALSE;

    if (mPlib_able_shutter_type1((GAME*)play) && !mSM_Check_unable_shutter_label(play) && mCsd_sdcard_sweet_chk()) {
        ret = TRUE;
    }

    return ret;
}

static int mSM_check_open_SHUTTER(GAME_PLAY* play) {
    int ret = FALSE;

    if (chkTrigger(BUTTON_Z) && mSM_check_open_SHUTTER_condition(play)) {
        mCsd_exitence_chk_start();
        ret = TRUE;
    }

    return ret;
}

extern void mSM_submenu_ctrl(GAME_PLAY* play) {
    Submenu* submenu = &play->submenu;

    if (submenu->process_status != mSM_PROCESS_WAIT) {
        return;
    }

    if (play->fb_fade_type != FADE_TYPE_NONE) {
        return;
    }

    if (play->fb_wipe_mode != WIPE_MODE_NONE) {
        return;
    }

    if (mSM_check_open_INVENTORY(play) == TRUE) {
        mSM_open_submenu(submenu, mSM_OVL_INVENTORY, 0, 0);
        mSM_Reset_player_btn_type2(play);
    } else if (mSM_check_open_MAP(play) == TRUE) {
        mSM_open_submenu(submenu, mSM_OVL_MAP, 1, 0);
        mSM_Reset_player_btn_type2(play);
    } else if (mSM_check_open_FG(play) == TRUE) {
        switch (GET_PLAYER_ACTOR(play)->item_in_front) {
            case MESSAGE_BOARD1:
            case MESSAGE_BOARD0:
                mSM_open_submenu(submenu, mSM_OVL_NOTICE, 0, 0);
                mSM_Reset_player_btn_type1(play);
                break;
            case MAP_BOARD1:
            case MAP_BOARD0:
                mSM_open_submenu(submenu, mSM_OVL_MAP, 0, 0);
                mSM_Reset_player_btn_type1(play);
                break;
            case MUSIC_BOARD1:
            case MUSIC_BOARD0:
                mSM_open_submenu(submenu, mSM_OVL_MSCORE, 0, 0);
                mSM_Reset_player_btn_type1(play);
                break;
        }
    } else if (mSM_check_open_SHUTTER(play) == TRUE) {
        mSM_open_submenu(submenu, mSM_OVL_SHUTTER, 0, 0);
        submenu->capture_display_mode = mSM_CAPTURE_DISPLAY_MODE_FILM;
    }

    if (submenu->menu_type != mSM_OVL_NONE) {
        submenu->process_status = mSM_PROCESS_PREWAIT;
        submenu->mode = mSM_MODE_PRERENDER_INIT;
        SetGameFrame(1);
    }
}

static void mSM_move_Wait(Submenu* submenu) {
    if (submenu->wait_timer != 0) {
        submenu->wait_timer--;
    }

    if (submenu->start_refuse_timer != 0) {
        submenu->start_refuse_timer--;
    }
}

static void mSM_move_PREWait(Submenu* submenu) {
    if (submenu->mode >= mSM_MODE_PRERENDER_DONE) {
        submenu->process_status = mSM_PROCESS_LINKWAIT;
    }
}

static void mSM_extMemberInit(Submenu* submenu) {
    submenu->open_flag = TRUE;

    if (submenu->menu_type != mSM_OVL_SHUTTER && submenu->menu_type != mSM_OVL_FILM) {
        Submenu_Item_c* item;
        int i;

        submenu->after_mode = 7;
        submenu->unk_F4 = 0;
        mMl_clear_mail(&submenu->mail);
        submenu->item_p = &submenu->items[0];
        submenu->item_num = mPr_POCKETS_SLOT_COUNT;
        submenu->receive_mail_bitfield = 0;
        item = submenu->item_p;
        for (i = 0; i < submenu->item_num; i++) {
            item->item = EMPTY_NO;
            item->slot_no = mPr_POCKETS_SLOT_COUNT;
            item++;
        }
    }
}

static void mSM_move_LINKWait(Submenu* submenu) {
    Submenu_Item_c* item;
    mSM_dlftbl_c* dlftbl = &SubmenuArea_dlftbl[mSM_DLF_SUBMENU_OVL];
    int i;

    if (SubmenuArea_visit != dlftbl) {
        if (SubmenuArea_visit != NULL) {
            SubmenuArea_DoUnlink(SubmenuArea_visit, submenu);
        }

        SubmenuArea_DoLink(dlftbl, submenu, mSM_DLF_SUBMENU_OVL);
        submenu->move_proc = (SUBMENU_PROC)mSM_ovlptr_dllcnv(&mSM_menu_ovl_init, submenu, mSM_DLF_SUBMENU_OVL);
        submenu->draw_proc = (SUBMENU_GAME_PROC)&none_proc1;
        submenu->process_status = mSM_PROCESS_PLAY;
        mSM_extMemberInit(submenu);

        if (submenu->mode != mSM_MODE_OTHER) {
            if ((submenu->menu_type == mSM_OVL_LEDIT && submenu->param0 == 0) ||
                Common_Get(now_private)->gender == mPr_SEX_MALE) {
                sAdo_SpecChange(5);
            } else {
                sAdo_SpecChange(6);
            }

            sAdo_SetVoiceMode(0);
        }
    }
}

static void mSM_move_Play(Submenu* submenu) {
    (*submenu->move_proc)(submenu);
}

static void mSM_move_End(Submenu* submenu) {
    mSM_dlftbl_c* dlftbl = &SubmenuArea_dlftbl[mSM_DLF_SUBMENU_OVL];
    GAME_PLAY* play = (GAME_PLAY*)gamePT;

    (*submenu->move_proc)(submenu);
    submenu->process_status = mSM_PROCESS_WAIT;
    submenu->menu_type = mSM_OVL_NONE;
    submenu->wait_timer = 2;
    submenu->open_flag = FALSE;
    SetGameFrame(1);

    if (submenu->mode != mSM_MODE_OTHER) {
        mMsg_Window_c* msg_win = mMsg_Get_base_window_p();
        submenu->mode = mSM_MODE_IDLE;
        mSc_dmacopy_all_exchange_bank(&play->object_exchange);
        SubmenuArea_DoUnlink(dlftbl, submenu);
        load_player(submenu);
        mSM_load_player_anime(play);
        submenu->start_refuse_timer = 1;

        if (submenu->after_mode == 15) {
            mPlib_request_main_demo_wait_from_submenu((ACTOR*)submenu->overlay->menu_info[mSM_OVL_MSCORE].data2);
        }

        if (mMsg_Check_main_hide(msg_win) == FALSE && mMsg_Check_not_series_main_wait(msg_win)) {
            mMsg_sound_spec_change_voice(msg_win);
        }
    }
}

extern void mSM_submenu_move(Submenu* submenu) {
    static SUBMENU_PROC move_proc[mSM_PROCESS_NUM] = { &mSM_move_Wait, &mSM_move_PREWait, &mSM_move_LINKWait,
                                                       &mSM_move_Play, &mSM_move_End };

    (*move_proc[submenu->process_status])(submenu);
}

extern void mSM_submenu_draw(Submenu* submenu, GAME* game) {
    if (submenu->mode >= mSM_MODE_PRERENDER_DONE && submenu->process_status == mSM_PROCESS_PLAY &&
        SubmenuArea_visit == &SubmenuArea_dlftbl[mSM_DLF_SUBMENU_OVL]) {
        (*submenu->draw_proc)(submenu, game);
    }
}

static int mSM_check_item_for_furniture(int slot_no, int param_2) {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item = priv->inventory.pockets[slot_no];
    int cat = ITEM_NAME_GET_CAT(item);
    int res = FALSE;

    if (item != EMPTY_NO && (mPr_CHK_ITEM_COND(priv->inventory.item_conditions, slot_no)) == mPr_ITEM_COND_NORMAL &&
        ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 && cat != ITEM1_CAT_FISH && cat != ITEM1_CAT_KABU &&
        cat != ITEM1_CAT_INSECT && item != ITM_KNIFE_AND_FORK &&
        !(item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12)) {
        res = TRUE;
    }

    return res;
}

static int mSM_check_item_for_quest(int slot_no, int param_2) {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item = priv->inventory.pockets[slot_no];
    int res = FALSE;

    if (item != EMPTY_NO && !(item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12) &&
        item != ITM_KNIFE_AND_FORK && !(item >= ITM_SPIRIT0 && item <= ITM_SPIRIT4)) {
        res = TRUE;
    }

    return res;
}

static int mSM_check_item_for_sell(int slot_no, int param_2) {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item = priv->inventory.pockets[slot_no];
    int res = FALSE;

    if (item != EMPTY_NO && mPr_CHK_ITEM_COND(priv->inventory.item_conditions, slot_no) == mPr_ITEM_COND_NORMAL &&
        (ITEM_NAME_GET_TYPE(item) != NAME_TYPE_ITEM1 || ITEM_NAME_GET_CAT(item) != ITEM1_CAT_MONEY) &&
        !(item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12) && item != ITM_KNIFE_AND_FORK &&
        !(item >= ITM_SPIRIT0 && item <= ITM_SPIRIT4)) {
        res = TRUE;
    }

    return res;
}

static int mSM_check_item_for_give(int slot_no, int param_2) {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item = priv->inventory.pockets[slot_no];
    int res = FALSE;

    if (item != EMPTY_NO && mPr_CHK_ITEM_COND(priv->inventory.item_conditions, slot_no) == mPr_ITEM_COND_NORMAL &&
        !(item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12) && item != ITM_KNIFE_AND_FORK &&
        !(item >= ITM_SPIRIT0 && item <= ITM_SPIRIT4)) {
        res = TRUE;
    }

    return res;
}

static int mSM_check_item_for_take(int slot_no, int param_2) {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item = priv->inventory.pockets[slot_no];
    int cat = ITEM_NAME_GET_CAT(item);
    int res = FALSE;

    if (item != EMPTY_NO && mPr_CHK_ITEM_COND(priv->inventory.item_conditions, slot_no) == mPr_ITEM_COND_NORMAL &&
        !(item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12) && item != ITM_KNIFE_AND_FORK &&
        !(item >= ITM_SPIRIT0 && item <= ITM_SPIRIT4) &&
        (param_2 == 0 || (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 &&
                          ((cat == ITEM1_CAT_FISH && param_2 == 1) || (cat == ITEM1_CAT_INSECT && param_2 == 2))))) {
        res = TRUE;
    }

    return res;
}

static int mSM_check_item_for_minidisk(int slot_no, int param_2) {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item = priv->inventory.pockets[slot_no];

    if (mPr_CHK_ITEM_COND(priv->inventory.item_conditions, slot_no) == mPr_ITEM_COND_NORMAL &&
        ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(item) == ITEM1_CAT_MINIDISK) {
        return TRUE;
    }

    return FALSE;
}

extern int mSM_check_item_for_shrine1(int slot_no) {
    u32 cond = mPr_CHK_ITEM_COND(Now_Private->inventory.item_conditions, slot_no);

    return cond == mPr_ITEM_COND_QUEST || cond == 4 || cond == 8;
}

extern int mSM_check_item_for_shrine2(int slot_no) {
    return mQst_CheckLimitbyPossessionIdx(slot_no);
}

static int mSM_check_item_for_shrine(int slot_no, int param_2) {
    if (mSM_check_item_for_shrine1(slot_no) && mSM_check_item_for_shrine2(slot_no)) {
        return TRUE;
    }

    return FALSE;
}

static int mSM_check_item_for_entrust(int slot_no, int param_2) {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item = priv->inventory.pockets[slot_no];
    int res = FALSE;

    if (item == EMPTY_NO ||
        mPr_CHK_ITEM_COND(priv->inventory.item_conditions, slot_no) == mPr_ITEM_COND_NORMAL &&
            (ITEM_NAME_GET_TYPE(item) != NAME_TYPE_ITEM1 || ITEM_NAME_GET_CAT(item) != ITEM1_CAT_MONEY) &&
            !(item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12) && item != ITM_KNIFE_AND_FORK &&
            !(item >= ITM_SPIRIT0 && item <= ITM_SPIRIT4)) {
        res = TRUE;
    }

    return res;
}

static int mSM_check_item_for_exchange(int slot_no, int exchange_id) {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item = priv->inventory.pockets[slot_no];
    int res = FALSE;

    if (item != EMPTY_NO && mPr_CHK_ITEM_COND(priv->inventory.item_conditions, slot_no) == mPr_ITEM_COND_NORMAL &&
        item != ITM_SIGNBOARD && item != ITM_KNIFE_AND_FORK &&
        !(item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12)) {
        if ((ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(item) == ITEM1_CAT_FISH) &&
            (ITEM_NAME_GET_TYPE(exchange_id) != NAME_TYPE_ITEM1 || ITEM_NAME_GET_CAT(exchange_id) != ITEM1_CAT_FISH)) {
            PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();
            xyz_t water_pos;

            if (mCoBG_SearchWaterLimitDistN(&water_pos, player->actor_class.world.position,
                                            player->actor_class.shape_info.rotation.y, 120.0f, 12) == FALSE) {
                return FALSE;
            }

            xyz_t_move(&((GAME_PLAY*)gamePT)->submenu.water_pos, &water_pos);
        }

        res = TRUE;
    }

    return res;
}

static int mSM_check_item_for_curator(int slot_no, int param_2) {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item = priv->inventory.pockets[slot_no];
    int res = FALSE;

    if (item != EMPTY_NO && mPr_CHK_ITEM_COND(priv->inventory.item_conditions, slot_no) == mPr_ITEM_COND_NORMAL &&
        item != ITM_KNIFE_AND_FORK && !(item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12)) {
        res = TRUE;
    }

    return res;
}

typedef int (*mSM_INVENTORY_CHECK_PROC)(int, int);

extern int mSM_check_open_inventory_itemlist(int type, int param_2) {
    static mSM_INVENTORY_CHECK_PROC check_process[mSM_IV_OPEN_NUM] = {
        NULL,
        NULL,
        &mSM_check_item_for_entrust,
        NULL,
        &mSM_check_item_for_quest,
        &mSM_check_item_for_sell,
        &mSM_check_item_for_give,
        NULL,
        &mSM_check_item_for_take,
        &mSM_check_item_for_furniture,
        &mSM_check_item_for_minidisk,
        &mSM_check_item_for_shrine,
        NULL,
        &mSM_check_item_for_exchange,
        NULL,
        &mSM_check_item_for_curator,
        NULL,
    };

    mSM_INVENTORY_CHECK_PROC check_proc = check_process[type];
    int i;
    int res = 0;

    if (check_proc == NULL) {
        return 0xFFFF; /* all slots are valid */
    }

    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        if ((*check_proc)(i, param_2) != FALSE) {
            res |= (1 << i); // slot is valid
        }
    }

    return res;
}

static char* mSM_Object_Exchange_keep_new(GAME_PLAY* play, s16 bank_id, size_t size) {
    Object_Exchange_c* exchange = &play->object_exchange;
    Object_Bank_c* bank = &exchange->banks[exchange->bank_idx];

    bank->bank_id = bank_id;
    bank->dma_start = exchange->next_bank_ram_address;
    bank->ram_start = exchange->next_bank_ram_address;
    bank->size = size;

    if (exchange->bank_idx < mSc_OBJECT_BANK_NUM - 1) {
        exchange->next_bank_ram_address = (char*)ALIGN_NEXT((u32)(exchange->next_bank_ram_address + size), 16);
        exchange->bank_idx++;
    }

    return bank->dma_start;
}

static void mSM_Object_Exchange_keep_new_MenuTexAndPallet(GAME_PLAY* play, int idx) {
    char* tex_p = mSM_Object_Exchange_keep_new(play, ACTOR_OBJ_BANK_14, (32 * 32) / 2);
    char* pal_p = mSM_Object_Exchange_keep_new(play, ACTOR_OBJ_BANK_15, 16 * sizeof(u16));

    play->submenu_ground_tex[idx] = tex_p;
    play->submenu_ground_pallet[idx] = pal_p;
    mPlib_Load_PlayerTexAndPallet(tex_p, pal_p, Common_Get(now_private)->backgound_texture - ITM_CLOTH_START);
}

extern void mSM_Object_Exchange_keep_new_Menu(GAME_PLAY* play) {
    play->submenu_ground_idx = 0;
    mSM_Object_Exchange_keep_new_MenuTexAndPallet(play, 0);
    mSM_Object_Exchange_keep_new_MenuTexAndPallet(play, 1);
}

extern u8* mSM_Get_ground_tex_p(GAME_PLAY* play) {
    int idx = play->submenu_ground_idx;

    if (idx < 0) {
        return NULL;
    }

    return (u8*)play->submenu_ground_tex[idx];
}

extern u16* mSM_Get_ground_pallet_p(GAME_PLAY* play) {
    int idx = play->submenu_ground_idx;

    if (idx < 0) {
        return NULL;
    }

    return (u16*)play->submenu_ground_pallet[idx];
}

extern u32 mSM_Get_unable_shutter_label(GAME_PLAY* play) {
    return play->submenu.unable_shutter_label;
}

extern int mSM_Check_unable_shutter_label(GAME_PLAY* play) {
    // @BUG - dev likely fat-fingered the minus key when assigning the variable
#ifndef BUGFIXES
    u32 current_label = -mSM_Get_unable_shutter_label(play);
#else
    u32 current_label = mSM_Get_unable_shutter_label(play);
#endif

    return current_label != 0;
}

extern int mSM_CheckOwner_unable_shutter_label(GAME_PLAY* play, u32 label) {
    u32 current_label = mSM_Get_unable_shutter_label(play);
    return current_label == label;
}

extern int mSM_CheckAbleChange_unable_shutter_label(GAME_PLAY* play, u32 label) {
    u32 current_label = mSM_Get_unable_shutter_label(play); // @unused

    if (mSM_CheckOwner_unable_shutter_label(play, label) || !mSM_Check_unable_shutter_label(play)) {
        return TRUE;
    }

    return FALSE;
}

extern void mSM_Set_unable_shutter_label(GAME_PLAY* play, u32 label) {
    play->submenu.unable_shutter_label = label;
}
