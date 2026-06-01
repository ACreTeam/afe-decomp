#include "ac_quest_talk_fj_init.h"

#include "m_common_data.h"
#include "m_msg.h"

enum {
    aQMgr_FJ_TALK_STEP_SELECT_TALK,
    aQMgr_FJ_TALK_STEP_HINT_OR_HINT,
    aQMgr_FJ_TALK_STEP_HINT_OR_FJ,
    aQMgr_FJ_TALK_STEP_HAND_REWARD,
    aQMgr_FJ_TALK_STEP_GET_ITEM,
    aQMgr_FJ_TALK_STEP_WAIT_BUTTON,
    aQMgr_FJ_TALK_STEP_GET_ITEM_WAIT,
    aQMgr_FJ_TALK_STEP_REWARD_TO,
    aQMgr_FJ_TALK_STEP_LETTER_BEFORE,
    aQMgr_FJ_TALK_STEP_SHOW_LETTER,
    aQMgr_FJ_TALK_STEP_THANKS_LETTER_OPEN_MSG,
    aQMgr_FJ_TALK_STEP_WAIT_NOTHING,
    aQMgr_FJ_TALK_STEP_FINISH,

    aQMgr_FJ_TALK_STEP_NUM
};

static int aQMgr_actor_decide_fj_message_no(aQMgr_target_c* target, int msg_type, int looks) {
    aQMgr_set_data_c* set_data_p = target->set_data_p;
    int msg_no = 0;

    if (set_data_p->msg_start[msg_type] != NULL) {
        msg_no = set_data_p->msg_start[msg_type][looks];
    }

    return msg_no;
}

static void aQMgr_fj_set_msg_no(QUEST_MANAGER_ACTOR* manager) {
    int base_msg;

    if (manager->msg_category != aQMgr_MSG_KIND_NONE) {
        int looks = mNpc_GetNpcLooks(*manager->client);

        manager->category_msg_no_start =
            aQMgr_actor_decide_fj_message_no(&manager->target, manager->msg_category, looks);
    }

    manager->msg_no = manager->category_msg_no_start;
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    manager->category_msg_no_start = 0;
}

static int aQMgr_actor_check_to(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal_orig;
    aQMgr_regist_c* regist = manager->regist;
    int res = -1;

    if (animal != NULL) {
        int i;

        for (i = 0; i < aQMgr_REGIST_NUM; i++) {
            if (regist->quest_info != NULL) {
                if (mNpc_CheckCmpAnimalPersonalID(&animal->id, &regist->to_id) == TRUE) {
                    res = i;
                    break;
                }
            }

            regist++;
        }
    }

    return res;
}

static int aQMgr_fj_check_own_quest(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx = aQMgr_actor_check_to(manager);

    if (regist_idx != -1) {
        mQst_base_c* quest_info = manager->regist[regist_idx].quest_info;

        if (quest_info != NULL) {
            if (quest_info->progress == 0 || quest_info->progress == 1) {
                regist_idx = -1;
            } else {
                mActor_name_t item = ((mQst_errand_c*)quest_info)->item;

                if (item != EMPTY_NO) {
                    int idx = mPr_GetPossessionItemIdxWithCond(Common_Get(now_private), item, mPr_ITEM_COND_QUEST);

                    if (idx == -1) {
                        regist_idx = -1;
                    } else {
                        ((mQst_errand_c*)quest_info)->pockets_idx = idx;
                    }
                }
            }
        } else {
            regist_idx = -1;
        }
    }

    return regist_idx;
}

static int aQMgr_get_select_hellow_no(void) {
    return 0x89 + mQst_GetRandom(10);
}

static void aQMgr_talk_fj_select_talk(QUEST_MANAGER_ACTOR* manager) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    aQMgr_choice_c* choice = &manager->choice;
    int regist_idx;

    manager->mail_memory = NULL;
    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
    choice->choice_num = 2;
    regist_idx = aQMgr_fj_check_own_quest(manager);

    if (regist_idx != -1) {
        aQMgr_regist_c* regist = &manager->regist[regist_idx];

        if (regist->quest_info != NULL) {
            if (regist->quest_info->quest_type == mQst_QUEST_TYPE_ERRAND &&
                regist->quest_info->quest_kind == mQst_ERRAND_FIRSTJOB_SEND_LETTER) {
                regist_idx = -1;
            } else {
                choice->choice_ids[0] = 0x68;
                choice->choice_ids[1] = aQMgr_get_select_hellow_no();
                choice->choice_num = 3;
                choice->talk_action = -1;
                manager->talk_step = aQMgr_FJ_TALK_STEP_HINT_OR_FJ;
                manager->regist_idx = regist_idx;
                (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_TARGET);
                manager->target.quest_inv_item_idx =
                    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_ITEM_IDX);
            }
        }
    }

    if (regist_idx == -1) {
        choice->choice_ids[0] = aQMgr_get_select_hellow_no();
        choice->choice_num = 2;
        choice->talk_action = -1;
        manager->talk_step = aQMgr_FJ_TALK_STEP_HINT_OR_HINT;
        manager->regist_idx = regist_idx;
    }

    choice->choice_ids[choice->choice_num - 1] = 0x16A + mQst_GetRandom(5);
    if (manager->get_common_msg_proc != NULL) {
        manager->category_msg_no_start = (*manager->get_common_msg_proc)(manager, aQMgr_GET_COMMON_MSG_TYPE_SELECT);
    } else {
        manager->category_msg_no_start = 0x2A6;
    }
    mChoice_no_b_set(mChoice_Get_base_window_p());
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_CHOICE_STR);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static int l_msg_kaiwa_yame[mNpc_LOOKS_NUM] = { 0x254A, 0x254D, 0x2550, 0x2553, 0x2556, 0x2559 };

static void aQMgr_talk_fj_hint_or_hint(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == manager->choice.choice_num - 1) {
        int looks = mNpc_GetNpcLooks(*manager->client);

        manager->msg_category = aQMgr_MSG_KIND_NONE;
        manager->category_msg_no_start = 0;
        manager->msg_no = l_msg_kaiwa_yame[looks];
        manager->msg_no += mQst_GetIdxTalkSelect(0x7D, 0x80, looks);
        manager->choice.talk_action = -1;
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
    } else {
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CHANGE_TALK_NORMAL);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_talk_fj_hint_or_fj(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        mMsg_request_main_disappear_wait_type2(mMsg_Get_base_window_p());
        manager->msg_category = aQMgr_MSG_KIND_COMPLETE_INIT;
        aQMgr_fj_set_msg_no(manager);
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
        manager->talk_step = aQMgr_FJ_TALK_STEP_HAND_REWARD;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
    } else if (manager->choice.talk_action == 1) {
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CHANGE_TALK_NORMAL);
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    } else {
        int looks = mNpc_GetNpcLooks(*manager->client);

        manager->choice.talk_action = -1;
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        manager->category_msg_no_start = 0;
        manager->msg_no = l_msg_kaiwa_yame[looks];
        manager->msg_no += mQst_GetIdxTalkSelect(0x7D, 0x80, looks);
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
    }

    manager->choice.talk_action = -1;
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_fj_hand_reward(QUEST_MANAGER_ACTOR* manager) {
    Submenu* submenu = manager->submenu;
    int item_idx = manager->target.quest_inv_item_idx;

    mSM_open_submenu_new2(submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_QUEST, item_idx, NULL, 1);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    manager->talk_step = aQMgr_FJ_TALK_STEP_GET_ITEM;
}

static void aQMgr_talk_fj_get_item(QUEST_MANAGER_ACTOR* manager) {
    if (manager->handover_item) {
        manager->msg_category = aQMgr_MSG_KIND_COMPLETE_INIT;
        manager->talk_step = aQMgr_FJ_TALK_STEP_GET_ITEM_WAIT;
        mQst_SetItemNameStr(manager->handover_item, mMsg_ITEM_STR0);
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_APPEAR_WAIT;
        aQMgr_fj_set_msg_no(manager);
    } else {
        manager->regist_idx = -1;
        manager->target.free_data_p = NULL;
        manager->msg_category = aQMgr_MSG_KIND_NONE;

        if (manager->get_common_msg_proc != NULL) {
            manager->category_msg_no_start =
                (*manager->get_common_msg_proc)(manager, aQMgr_GET_COMMON_MSG_TYPE_CANCEL_ITEM);
        } else {
            manager->category_msg_no_start = 0x4AB;
        }
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    }

    mMsg_ChangeMsgData(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_request_main_appear_wait_type1(mMsg_Get_base_window_p());
    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_fj_get_item_wait(QUEST_MANAGER_ACTOR* manager) {
    if (manager->target.quest_info.quest_kind == mQst_ERRAND_FIRSTJOB_DELIVER_AXE ||
        manager->target.quest_info.quest_kind == mQst_ERRAND_FIRSTJOB_DELIVER_AXE2) {
        manager->talk_step = aQMgr_FJ_TALK_STEP_WAIT_BUTTON;
    } else {
        manager->talk_step = aQMgr_FJ_TALK_STEP_REWARD_TO;
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT_MSG_WAIT;
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_fj_wait_button(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_FJ_TALK_STEP_LETTER_BEFORE;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_CHECK_BUTTON;
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_fj_reward_to(QUEST_MANAGER_ACTOR* manager) {
    int item_idx = manager->target.quest_inv_item_idx;
    int regist_idx = manager->regist_idx;

    manager->regist[regist_idx].quest_info->progress = 0;
    mNpc_ClearAnimalPersonalID(&((mQst_errand_c*)manager->regist[regist_idx].quest_info)->recipient);
    mPr_SetPossessionItem(Common_Get(now_private), item_idx, manager->target.quest_item, mPr_ITEM_COND_NORMAL);
    manager->msg_category = aQMgr_MSG_KIND_COMPLETE_END;
    aQMgr_fj_set_msg_no(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_fj_letter_before(QUEST_MANAGER_ACTOR* manager) {
    mMsg_request_main_disappear_wait_type2(mMsg_Get_base_window_p());
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
    manager->talk_step = aQMgr_FJ_TALK_STEP_SHOW_LETTER;
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_fj_show_letter(QUEST_MANAGER_ACTOR* manager) {
    Submenu* submenu = manager->submenu;
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal_orig;
    static Mail_c show_mail;

    mMl_clear_mail(&show_mail);
    mNpc_AnimalMail2Mail(&show_mail, &(*manager->memory)->letter, &(*manager->memory)->memory_player_id, &animal->id);
    mSM_open_submenu_new(submenu, mSM_OVL_BOARD, mSM_BD_OPEN_READ, 0, &show_mail);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    manager->talk_step = aQMgr_FJ_TALK_STEP_THANKS_LETTER_OPEN_MSG;
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_fj_thanks_letter_open_msg(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx = manager->regist_idx;

    manager->regist[regist_idx].quest_info->progress = 0;
    mNpc_ClearAnimalPersonalID(&((mQst_errand_c*)manager->regist[regist_idx].quest_info)->recipient);
    manager->msg_category = aQMgr_MSG_KIND_COMPLETE_END;
    manager->talk_step = aQMgr_FJ_TALK_STEP_FINISH;
    mMsg_request_main_appear_wait_type1(mMsg_Get_base_window_p());
    aQMgr_fj_set_msg_no(manager);
    mMsg_ChangeMsgData(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_fj_wait_nothing(QUEST_MANAGER_ACTOR* manager) {
}

static void aQMgr_talk_fj_finish(QUEST_MANAGER_ACTOR* manager) {
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CLEAR_TALK_INFO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

typedef void (*aQMgr_FJ_TALK_PROC)(QUEST_MANAGER_ACTOR*);

extern void aQMgr_talk_first_job_init(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_FJ_TALK_PROC talk_proc[aQMgr_FJ_TALK_STEP_NUM] = { &aQMgr_talk_fj_select_talk,
                                                                    &aQMgr_talk_fj_hint_or_hint,
                                                                    &aQMgr_talk_fj_hint_or_fj,
                                                                    &aQMgr_talk_fj_hand_reward,
                                                                    &aQMgr_talk_fj_get_item,
                                                                    &aQMgr_talk_fj_wait_button,
                                                                    &aQMgr_talk_fj_get_item_wait,
                                                                    &aQMgr_talk_fj_reward_to,
                                                                    &aQMgr_talk_fj_letter_before,
                                                                    &aQMgr_talk_fj_show_letter,
                                                                    &aQMgr_talk_fj_thanks_letter_open_msg,
                                                                    &aQMgr_talk_fj_wait_nothing,
                                                                    &aQMgr_talk_fj_finish };
    int talk_step = manager->talk_step;
    int choice_no = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());

    mChoice_Clear_ChoseNum(mChoice_Get_base_window_p());
    manager->choice.talk_action = choice_no;
    (*talk_proc[talk_step])(manager);
    manager->talk_state = aQMgr_TALK_STATE_SUB;
}
