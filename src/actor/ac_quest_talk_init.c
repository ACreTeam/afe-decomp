#include "ac_quest_talk_init.h"

#include "m_common_data.h"
#include "m_quest.h"
#include "m_name_table.h"
#include "m_house.h"
#include "m_item_name.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_string.h"
#include "m_time.h"
#include "m_land.h"
#include "m_shop.h"
#include "ac_my_room.h"
#include "ac_ev_ghost.h"
#include "libultra/libultra.h"
#include "ac_set_ovl_insect.h"
#include "ac_set_ovl_gyoei.h"

enum {
    aQMgr_CHECK_TO,
    aQMgr_CHECK_FROM,

    aQMgr_CHECK_OWN_NUM
};

enum {
    aQMgr_QUEST_TYPE_FJ,
    aQMgr_QUEST_TYPE_QUEST,

    aQMgr_QUEST_TYPE_NUM
};

enum {
    aQMgr_TALK_STEP_SELECT_TALK,
    aQMgr_TALK_STEP_RECONF_OR_NORMAL,
    aQMgr_TALK_STEP_RECONF_OR_NORMAL_CTT,
    aQMgr_TALK_STEP_ROOT_RECONF_OR_NORMAL,
    aQMgr_TALK_STEP_NO_OR_NORMAL,
    aQMgr_TALK_STEP_FULL_ITEM_OR_NORMAL,
    aQMgr_TALK_STEP_RENEW_ERRAND_OR_NORMAL,
    aQMgr_TALK_STEP_NEW_QUEST_OR_NORMAL,
    aQMgr_TALK_STEP_NORMAL,
    aQMgr_TALK_STEP_OCCUR_QUEST,
    aQMgr_TALK_STEP_GIVEUP,
    aQMgr_TALK_STEP_GIVEUP_WAIT_BUTTON,
    aQMgr_TALK_STEP_GIVEUP_OPEN_MENU,
    aQMgr_TALK_STEP_GIVEUP_ITEM,
    aQMgr_TALK_STEP_GIVEUP_NPC_ITEM,
    aQMgr_TALK_STEP_FIN_QUEST_START,
    aQMgr_TALK_STEP_TALK_FIN_QUEST_START_NOT_HAND,
    aQMgr_TALK_STEP_FIN_QUEST_REWARD,
    aQMgr_TALK_STEP_FIN_QUEST_THANKS,
    aQMgr_TALK_STEP_AFTER_REWARD,
    aQMgr_TALK_STEP_AFTER_REWARD_THANKS,
    aQMgr_TALK_STEP_AFTER_REWARD_SELECT,
    aQMgr_TALK_STEP_WAIT_TALK,
    aQMgr_TALK_STEP_OPEN_MENU,
    aQMgr_TALK_STEP_GET_ITEM,
    aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT,
    aQMgr_TALK_STEP_NPC_WAIT_HAND_QBOX,
    aQMgr_TALK_STEP_NPC_WAIT_OPEN_QBOX,
    aQMgr_TALK_STEP_THINK_ITEM,
    aQMgr_TALK_STEP_MSG_LOCK_QBOX,
    aQMgr_TALK_STEP_FIN_QUEST_THANKS_QBOX,
    aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT_LOST,
    aQMgr_TALK_STEP_FIN_QUEST_REWARD_LOST,
    aQMgr_TALK_STEP_RECOVERY_LOST_OR_CANCEL,
    aQMgr_TALK_STEP_REPORT_QBOX_OR_NORMAL,
    aQMgr_TALK_STEP_REACTION_QBOX,
    aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT_CTT,
    aQMgr_TALK_STEP_FIN_QUEST_REWARD_CTT,
    aQMgr_TALK_STEP_CHANGE_WAIT,
    aQMgr_TALK_STEP_RENEW_ERRAND_IRAI_END,
    aQMgr_TALK_STEP_RENEW_ERRAND_IRAI_END_GIVE_ITEM,
    aQMgr_TALK_STEP_CONTEST_HOKA_OR_NORMAL,
    aQMgr_TALK_STEP_FINISH_LETTER,
    aQMgr_TALK_STEP_SICK_BEFORE_SELECT,
    aQMgr_TALK_STEP_SICK_WAIT_BUTTON,
    aQMgr_TALK_STEP_SICK_DISAPPEAR,
    aQMgr_TALK_STEP_SICK_OPEN_MENU,
    aQMgr_TALK_STEP_SICK_HAND_MEDICINE,
    aQMgr_TALK_STEP_SICK_GET_ITEM,
    aQMgr_TALK_STEP_SICK_AFTER_SELECT,
    aQMgr_TALK_STEP_SICK_REWARD,
    aQMgr_TALK_STEP_SICK_REWARD_END,
    aQMgr_TALK_STEP_WAIT,
    aQMgr_TALK_STEP_NO_OR_ISLAND,
    aQMgr_TALK_STEP_FINISH,

    aQMgr_TALK_STEP_NUM
};

static mActor_name_t l_quest_item_list[] = {
    ITM_QST_CAMREA,
    ITM_QST_WATCH,
    ITM_QST_HANDKERCHIEF,
    ITM_QST_GLASSES_CASE,
};

static int l_soccer_reward_msg_kagu[mNpc_LOOKS_NUM] = { 0x0DA3, 0x0DA6, 0x0DA9, 0x0DAC, 0x0DAF, 0x0DB2 };
static int l_soccer_reward_msg_jyutan[mNpc_LOOKS_NUM] = { 0x0DB5, 0x0DB8, 0x0DBB, 0x0DBE, 0x0DC1, 0x0DC4 };
static int l_soccer_reward_msg_kabegami[mNpc_LOOKS_NUM] = { 0x0DC7, 0x0DCA, 0x0DCD, 0x0DD0, 0x0DD3, 0x0DD6 };
static int* l_soccer_reward_msg[aQMgr_QUEST_REWARD_NUM] = {
    l_soccer_reward_msg_kagu,
    NULL,
    NULL,
    l_soccer_reward_msg_jyutan,
    l_soccer_reward_msg_kabegami,
    NULL,
    NULL,
    NULL,
    NULL,
};

static int l_flower_reward_msg_kagu[mNpc_LOOKS_NUM] = { 0x0FD9, 0x0FDC, 0x0FDF, 0x0FE2, 0x0FE5, 0x0FE8 };
static int l_flower_reward_msg_jyutan[mNpc_LOOKS_NUM] = { 0x0FEB, 0x0FEE, 0x0FF1, 0x0FF4, 0x0FF7, 0x0FFA };
static int l_flower_reward_msg_kabegami[mNpc_LOOKS_NUM] = { 0x0FFD, 0x1000, 0x1003, 0x1006, 0x1009, 0x100C };
static int* l_flower_reward_msg[aQMgr_QUEST_REWARD_NUM] = {
    l_flower_reward_msg_kagu,
    NULL,
    NULL,
    l_flower_reward_msg_jyutan,
    l_flower_reward_msg_kabegami,
    NULL,
    NULL,
    NULL,
    NULL,
};

static int l_fish_reward_msg_kagu[mNpc_LOOKS_NUM] = { 0x157A, 0x157D, 0x1580, 0x1583, 0x1586, 0x1589 };
static int l_fish_reward_msg_jyutan[mNpc_LOOKS_NUM] = { 0x1556, 0x1559, 0x155C, 0x155F, 0x1562, 0x1565 };
static int l_fish_reward_msg_kabegami[mNpc_LOOKS_NUM] = { 0x1568, 0x156B, 0x156E, 0x1571, 0x1574, 0x1577 };
static int* l_fish_reward_msg[aQMgr_QUEST_REWARD_NUM] = {
    l_fish_reward_msg_kagu, NULL, NULL, l_fish_reward_msg_jyutan, l_fish_reward_msg_kabegami, NULL, NULL, NULL, NULL,
};

static int l_insect_reward_msg_kagu[mNpc_LOOKS_NUM] = { 0x15F8, 0x15FB, 0x15FE, 0x1601, 0x1604, 0x1607 };
static int l_insect_reward_msg_jyutan[mNpc_LOOKS_NUM] = { 0x15D4, 0x15D7, 0x15DA, 0x15DD, 0x15E0, 0x15E3 };
static int l_insect_reward_msg_kabegami[mNpc_LOOKS_NUM] = { 0x15E6, 0x15E9, 0x15EC, 0x15EF, 0x15F2, 0x15F5 };
static int* l_insect_reward_msg[aQMgr_QUEST_REWARD_NUM] = {
    l_insect_reward_msg_kagu,
    NULL,
    NULL,
    l_insect_reward_msg_jyutan,
    l_insect_reward_msg_kabegami,
    NULL,
    NULL,
    NULL,
    NULL,
};

static int l_grass_reward_msg_kagu[mNpc_LOOKS_NUM] = { 0x1F67, 0x1F6A, 0x1F6D, 0x1F70, 0x1F73, 0x1F76 };
static int l_grass_reward_msg_fuku[mNpc_LOOKS_NUM] = { 0x1F79, 0x1F7C, 0x1F7F, 0x1F82, 0x1F85, 0x1F88 };
static int l_grass_reward_msg_money[mNpc_LOOKS_NUM] = { 0x1F8B, 0x1F8E, 0x1F91, 0x1F94, 0x1F97, 0x1F9A };
static int* l_grass_reward_msg[aQMgr_QUEST_REWARD_NUM] = {
    l_grass_reward_msg_kagu, NULL, l_grass_reward_msg_fuku, NULL, NULL, l_grass_reward_msg_money, NULL, NULL, NULL,
};

static int aQMgr_check_field(void) {
    int ret = FALSE;

    if (mFI_GET_TYPE(mFI_GetFieldId()) == mFI_FIELDTYPE2_FG) {
        ret = TRUE;
    }

    return ret;
}

static int aQMgr_check_field_quest_cancel(u32 type, u32 kind) {
    int ret = FALSE;

    if (aQMgr_check_field() == FALSE && type == mQst_QUEST_TYPE_CONTEST) {
        if (kind == mQst_CONTEST_KIND_GRASS || kind == mQst_CONTEST_KIND_SOCCER || kind == mQst_CONTEST_KIND_FLOWER) {
            ret = TRUE;
        }
    }

    return ret;
}

static int aQMgr_actor_check_own_quest(QUEST_MANAGER_ACTOR* manager, int mode) {
    mQst_base_c* quest_info;
    NPC_ACTOR* client = (NPC_ACTOR*)*manager->client;
    Animal_c* animal = client->npc_info.animal_orig;
    aQMgr_regist_c* regist = manager->regist;
    int res = -1;

    if (animal != NULL) {
        AnmPersonalID_c* pid;
        int i;

        for (i = 0; i < aQMgr_REGIST_NUM; i++, regist++) {
            quest_info = regist->quest_info;
            if (quest_info != NULL) {
                if (mode == aQMgr_CHECK_TO) {
                    pid = &regist->to_id;
                } else {
                    pid = &regist->from_id;
                }

                if (mNpc_CheckCmpAnimalPersonalID(&animal->id, pid) == TRUE) {
                    if (aQMgr_check_field_quest_cancel(quest_info->quest_type, quest_info->quest_kind) == TRUE) {
                        manager->still_reward_but_field_quest_cancel = TRUE;
                    } else {    
                        res = i;
                        break;
                    }
                }
            }
        }
    }

    return res;
}

static int aQMgr_actor_check_own_quest_just(QUEST_MANAGER_ACTOR* manager, u32 type, u32 kind, int mode) {
    mQst_base_c* quest_info;
    NPC_ACTOR* client = (NPC_ACTOR*)*manager->client;
    Animal_c* animal = client->npc_info.animal_orig;
    aQMgr_regist_c* regist = manager->regist;
    int res = -1;

    if (animal != NULL) {
        AnmPersonalID_c* pid;
        int i;

        for (i = 0; i < aQMgr_REGIST_NUM; i++, regist++) {
            quest_info = regist->quest_info;
            if (quest_info != NULL && quest_info->quest_type == type && quest_info->quest_kind == kind) {
                if (mode == aQMgr_CHECK_TO) {
                    pid = &regist->to_id;
                } else {
                    pid = &regist->from_id;
                }

                if (mNpc_CheckCmpAnimalPersonalID(&animal->id, pid) == TRUE) {
                    res = i;
                    break;
                }
            }
        }
    }

    return res;
}

static int aQMgr_actor_check_still_reward(QUEST_MANAGER_ACTOR* manager) {
    mQst_base_c* quest_info;
    Animal_c* animal = ((NPC_ACTOR*)*manager->client)->npc_info.animal_orig;
    aQMgr_regist_c* regist = manager->regist;
    int idx = -1;
    AnmPersonalID_c* anm_id = &animal->id;
    int i;
    PersonalID_c* pid = &Now_Private->player_ID;

    if (anm_id != NULL) {

        for (i = 0; i < aQMgr_REGIST_NUM; i++, regist++) {
            quest_info = regist->quest_info;
            if (quest_info != NULL && quest_info->give_reward == TRUE &&
                mNpc_CheckCmpAnimalPersonalID(anm_id, &regist->to_id) == TRUE &&
                mPr_CheckCmpPersonalID(pid, regist->pid) == TRUE) {
                if (aQMgr_check_field_quest_cancel(quest_info->quest_type, quest_info->quest_kind) == TRUE) {
                    manager->still_reward_but_field_quest_cancel = TRUE;
                } else {
                    idx = i;
                    break;
                }
            }
        }
    }

    return idx;
}

static int aQMgr_actor_check_fin_step(mQst_base_c* quest_info) {
    int res = FALSE;

    if (quest_info->progress == 0) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_check_finish(aQMgr_regist_c* regist, Animal_c* animal) {
    aQMgr_CHECK_FINISH_PROC check_finish_proc = regist->check_finish_proc;
    mQst_base_c* quest_info = regist->quest_info;
    int res = FALSE;

    if (quest_info != NULL) {
        if (check_finish_proc != NULL) {
            res = (*check_finish_proc)(quest_info, animal);
        } else {
            res = aQMgr_actor_check_fin_step(quest_info);
        }
    }

    return res;
}

static int aQMgr_actor_check_limit(aQMgr_regist_c* regist) {
    mQst_base_c* quest_info = regist->quest_info;
    int res = FALSE;

    if (quest_info != NULL) {
        res = mQst_CheckLimitOver(quest_info);
    }

    return res;
}

static int aQMgr_actor_check_errand_from(QUEST_MANAGER_ACTOR* manager) {
    NPC_ACTOR* client = (NPC_ACTOR*)*manager->client;
    int idx = -1;
    Animal_c* animal = client->npc_info.animal_orig;
    aQMgr_regist_c* regist = manager->regist;
    aQMgr_quest_c* quest;
    int count = 0;

    if (animal != NULL) {
        int i;

        for (i = 0; i < aQMgr_REGIST_NUM; i++, regist++) {
            if (count >= manager->regist_use_no) {
                break;
            }

            quest = (aQMgr_quest_c*)regist->quest_info;
            if (quest != NULL) {
                if (quest->base.quest_type == mQst_QUEST_TYPE_ERRAND &&
                    (quest->errand.errand_type == mQst_ERRAND_REQUEST_CONTINUE &&
                     mNpc_CheckCmpAnimalPersonalID(&animal->id, &quest->errand.info.chain.used_ids[0]) == TRUE)) {
                    idx = i;
                    break;
                }

                count++;
            }
        }
    }

    return idx;
}

static int aQMgr_actor_get_errand_next_idx(aQMgr_regist_c* regist) {
    mQst_errand_c* errand;
    int idx = -1;

    if (regist != NULL && regist->quest_info != NULL && regist->animal_idx >= 0 && regist->animal_idx < 5) {
        errand = (mQst_errand_c*)regist->quest_info;

        if (errand->base.quest_type == mQst_QUEST_TYPE_ERRAND) {
            idx = regist->animal_idx;
        }
    }

    return idx;
}

static void aQMgr_actor_set_errand_next(u8* next, aQMgr_regist_c* regist, u8 kind) {
    int idx = aQMgr_actor_get_errand_next_idx(regist);

    if (idx >= 0 && idx < mPr_ERRAND_QUEST_NUM) {
        next[idx] = kind;
    }
}

static u8 aQMgr_actor_get_errand_next(aQMgr_regist_c* regist, u8* next) {
    u8 kind = mQst_ERRAND_REQUEST;
    int idx = aQMgr_actor_get_errand_next_idx(regist);

    if (idx >= 0 && idx < mPr_ERRAND_QUEST_NUM) {
        kind = next[idx];
    }

    return kind;
}

static int aQMgr_actor_check_free_quest(u32 type, u32 kind, Animal_c* animal) {
    Private_c* priv = Now_Private;
    int res = -1;
    int i;

    switch (type) {
        case mQst_QUEST_TYPE_DELIVERY:
            if (kind == mQst_DELIVERY_KIND_LOST_ITEM) {
                if (mQst_CheckFreeQuest(&priv->lost_item_quest.base) == TRUE) {
                    res = 0;
                }
            } else {
                for (i = 0; i < mPr_DELIVERY_QUEST_NUM; i++) {
                    if (mQst_CheckFreeQuest(&priv->deliveries[i].base) == TRUE) {
                        res = i;
                        break;
                    }
                }
            }
            break;
        case mQst_QUEST_TYPE_ERRAND:
            for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
                if (mQst_CheckFreeQuest(&priv->errands[i].base) == TRUE) {
                    res = i;
                    break;
                }
            }
            break;
        case mQst_QUEST_TYPE_CONTEST:
            if (mQst_CheckFreeQuest(&animal->contest_quest.base) == TRUE) {
                res = mNpc_SearchAnimalPersonalID(&animal->id);
            }
            break;
    }

    return res;
}

static void aQMgr_actor_get_free_quest_p(QUEST_MANAGER_ACTOR* manager, u32 type, u32 kind) {
    Animal_c* client_animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    mQst_contest_c* client_contest = &aQMgr_GET_CLIENT_ANIMAL(manager)->contest_quest;
    aQMgr_target_c* target = &manager->target;
    mQst_base_c** free_data_p = &target->free_data_p;
    Private_c* priv = Now_Private;
    int idx;
    int i;

    *free_data_p = NULL;
    idx = aQMgr_actor_check_free_quest(type, kind, client_animal);

    if (idx != -1) {
        switch (type) {
            case mQst_QUEST_TYPE_DELIVERY: {
                if (kind == mQst_DELIVERY_KIND_LOST_ITEM) {
                    *free_data_p = &priv->lost_item_quest.base;
                } else {
                    int free_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);
                    if (free_idx != -1) {
                        if (free_idx != idx) {
                            mQst_delivery_c tmp;

                            mQst_CopyDelivery(&tmp, &priv->deliveries[free_idx]);
                            mQst_CopyDelivery(&priv->deliveries[free_idx], &priv->deliveries[idx]);
                            mQst_CopyDelivery(&priv->deliveries[idx], &tmp);
                            idx = free_idx;
                        }

                        *free_data_p = &priv->deliveries[idx].base;
                        target->quest_inv_item_idx = idx;
                    }
                }
                break;
            }

            case mQst_QUEST_TYPE_ERRAND: {
                *free_data_p = &priv->errands[idx].base;
                break;
            }

            case mQst_QUEST_TYPE_CONTEST: {
                *free_data_p = &client_animal->contest_quest.base;
                break;
            }

            default: {
                idx = -1;
                break;
            }
        }
    }

    target->free_data_idx = idx;
}

typedef int (*aQMgr_CHECK_OCCURED_PROC)(u32);
typedef int (*aQMgr_CHECK_OCCUR_DELIVERY_PROC)(AnmPersonalID_c*, Animal_c*);
typedef int (*aQMgr_CHECK_OCCUR_CONTEST_PROC)(int, Animal_c*);

static int aQMgr_actor_check_occured_delivery(u32 delivery_kind) {
    int ret = -1;
    
    if (delivery_kind == mQst_DELIVERY_KIND_LOST_ITEM) {
        if (mQst_CheckFreeQuest(&Now_Private->lost_item_quest.base) == FALSE) {
            ret = 0;
        }
    } else {
        ret = mQst_GetOccuredDeliveryIdx(delivery_kind);
    }

    return ret;
}

static int aQMgr_actor_check_occured(u32 type, u32 kind) {
    static aQMgr_CHECK_OCCURED_PROC check_proc[] = {
        &aQMgr_actor_check_occured_delivery,
        (aQMgr_CHECK_OCCURED_PROC)NULL,
        &mQst_GetOccuredContestIdx,
    };

    int res = FALSE;

    if (type < ARRAY_COUNT(check_proc) && check_proc[type] != NULL) {
        if ((*check_proc[type])(kind) != -1) {
            res = TRUE;
        }
    }

    return res;
}

static int aQMgr_check_fj(void) {
    int ret = FALSE;

    if (mLd_PlayerManKindCheck() == FALSE && mEv_CheckFirstJob() == TRUE) {
        ret = TRUE;
    }

    return ret;
}

static int aQMgr_actor_check_false(AnmPersonalID_c* anm_id, Animal_c* animal) {
    return FALSE;
}

static int aQMgr_actor_check_occur_relation(AnmPersonalID_c* anm_id, Animal_c* animal) {
    Private_c* priv = Now_Private;
    int anm_idx;
    int res = FALSE;

    if (mLd_PlayerManKindCheck() == FALSE && mPr_GetPossessionItemIdx(priv, EMPTY_NO) != -1 &&
        (anm_idx = mNpc_SearchAnimalPersonalID(anm_id), anm_idx != -1) &&
        mNpc_GetAnimalMemoryIdx(&priv->player_ID, Save_Get(animals[anm_idx]).memories, ANIMAL_MEMORY_NUM) != -1) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_check_occur_not_fj(AnmPersonalID_c* anm_id, Animal_c* animal) {
    int ret = FALSE;

    if (aQMgr_check_fj() == FALSE) {
        ret = TRUE;
    }
    return ret;
}

static int aQMgr_actor_check_occur_delivery_remove(AnmPersonalID_c* anm_id, Animal_c* animal) {
    Private_c* priv = Now_Private;
    AnmPersonalID_c* last_removed_animal_id = Save_GetPointer(last_removed_animal_id);
    int res = FALSE;

    if (aQMgr_check_fj() == FALSE && animal != NULL &&
        mNpc_CheckFreeAnimalPersonalID(last_removed_animal_id) == FALSE &&
        mNpc_CheckCmpAnimalPersonalID(last_removed_animal_id, &animal->id) == FALSE &&
        mPr_GetPossessionItemIdx(priv, EMPTY_NO) != -1) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_check_occur_delivery_lost(AnmPersonalID_c* anm_id, Animal_c* animal) {
    int bx = 0;
    int bz = 0;
    int res = FALSE;

    if (aQMgr_check_fj() == FALSE) {
        int valid;

        if (aQMgr_check_field() == TRUE) {
            valid = mQst_GetPlayerBlockNum(&bx, &bz);
        } else {
            bx = animal->home_info.bx;
            bz = animal->home_info.bz;
            valid = TRUE;
        }
        if (valid == TRUE) {
            res = mQst_CheckLostItemPos(bx, bz);
        }
    }

    return res;
}

static int aQMgr_actor_check_occur_delivery(u32 kind, AnmPersonalID_c* anm_id, Animal_c* animal) {
    static aQMgr_CHECK_OCCUR_DELIVERY_PROC check_proc[] = {
        &aQMgr_actor_check_occur_relation,
        &aQMgr_actor_check_occur_relation,
        &aQMgr_actor_check_occur_relation,
        &aQMgr_actor_check_occur_delivery_remove,
        &aQMgr_actor_check_occur_delivery_lost,
    };

    int res = FALSE;

    if (kind < ARRAY_COUNT(check_proc) && check_proc[kind] != NULL) {
        res = (*check_proc[kind])(anm_id, animal);
    }

    return res;
}

static int aQMgr_actor_check_occur_contest_soccer(AnmPersonalID_c* target_anm_id, Animal_c* animal) {
    int ret = FALSE;

    if (aQMgr_check_fj() == FALSE && aQMgr_check_field() == TRUE) {
        ret = TRUE;
    }

    return ret;
}

static int aQMgr_actor_check_occur_contest_flower(AnmPersonalID_c* target_anm_id, Animal_c* animal) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int bx = animal->home_info.bx;
    int bz = animal->home_info.bz;
    int res = FALSE;
    
    if (aQMgr_check_fj() == FALSE && aQMgr_check_field() == TRUE &&
        (((rtc_time->month == lbRTC_FEBRUARY && rtc_time->day >= 25) ||
            (rtc_time->month >= lbRTC_MARCH && rtc_time->month <= lbRTC_AUGUST)))) {
        int null_no_num = mQst_GetNullNoNum(bx, bz);
        int flower_num = mQst_GetFlowerNum(bx, bz);
        if (null_no_num >= 4 && flower_num <= 20) {
            res = TRUE;
        }
    }

    return res;
}

static int aQMgr_actor_check_occur_contest_insect(AnmPersonalID_c* target_anm_id, Animal_c* animal) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int res = FALSE;

    if (aQMgr_check_fj() == FALSE &&
        ((rtc_time->month >= lbRTC_MARCH && rtc_time->month <= lbRTC_OCTOBER) ||
         (rtc_time->month == lbRTC_NOVEMBER && rtc_time->day <= 28))) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_check_occur_contest_letter(AnmPersonalID_c* target_anm_id, Animal_c* animal) {
    int res = FALSE;

    if (mLd_PlayerManKindCheck() == FALSE && aQMgr_check_fj() == FALSE) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_check_occur_contest_shop(AnmPersonalID_c* target_anm_id, Animal_c* animal) {
    mActor_name_t* goods = Save_Get(shop).items;
    int res = FALSE;
    int i;

    if (aQMgr_check_fj() == FALSE && mSP_CheckShopNormalStatus_Quest() == TRUE) {
        for (i = 0; i < mSP_GOODS_COUNT; i++) {
            mActor_name_t item = *goods;

            if (ITEM_IS_FTR(item) || ITEM_IS_CARPET(item) ||
                ITEM_IS_WALL(item) || ITEM_IS_UMBRELLA2(item) ||
                ITEM_IS_CLOTH(item)) {
                res = TRUE;
                break;
            }

            goods++;
        }
    }

    return res;
}

static int aQMgr_actor_check_occur_contest_grass(AnmPersonalID_c* target_anm_id, Animal_c* animal) {
    int bx = 0;
    int bz = 0;
    int res = FALSE;

    if (aQMgr_check_field() == TRUE && mQst_GetPlayerBlockNum(&bx, &bz) == TRUE &&
        bx == animal->home_info.bx && bz == animal->home_info.bz &&
        mQst_GetGrassNum(bx, bz) > 5) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_check_occur_contest(u32 kind, AnmPersonalID_c* target_anm_id, Animal_c* animal) {
    static aQMgr_CHECK_OCCUR_DELIVERY_PROC check_proc[] = {
        &aQMgr_actor_check_occur_contest_soccer,
        &aQMgr_actor_check_occur_contest_flower,
        &aQMgr_actor_check_occur_not_fj,
        &aQMgr_actor_check_occur_contest_insect,
        &aQMgr_actor_check_occur_contest_letter,
        &aQMgr_actor_check_occur_not_fj,
        &aQMgr_actor_check_occur_contest_shop,
        &aQMgr_actor_check_occur_contest_grass,
        &aQMgr_actor_check_false,
    };

    int res = FALSE;

    if (kind < ARRAY_COUNT(check_proc) && check_proc[kind] != NULL) {
        res = (*check_proc[kind])(target_anm_id, animal);
    }

    return res;
}

typedef int (*aQMgr_CHECK_OCCUR_PROC)(u32, AnmPersonalID_c*, Animal_c*);

static int aQMgr_actor_check_occur(u32 type, u32 kind, AnmPersonalID_c* target_anm_id, Animal_c* animal) {
    static aQMgr_CHECK_OCCUR_PROC check_proc[] = {
        &aQMgr_actor_check_occur_delivery,
        (aQMgr_CHECK_OCCUR_PROC)NULL,
        &aQMgr_actor_check_occur_contest,
    };

    int occur = FALSE;

    if (type < ARRAY_COUNT(check_proc) && aQMgr_actor_check_occured(type, kind) == FALSE && aQMgr_actor_check_free_quest(type, kind, animal) != -1) {
        if (check_proc[type] != NULL) {
            occur = (*check_proc[type])(kind, target_anm_id, animal);
        }
    }

    return occur;
}

static int aQMgr_actor_set_free_quest(QUEST_MANAGER_ACTOR* manager, aQMgr_target_c* target) {
    int ret = FALSE;

    aQMgr_actor_get_free_quest_p(manager, target->quest_info.quest_type, target->quest_info.quest_kind);
    if (target->free_data_p != NULL) {
        ret = TRUE;
    }

    return ret;
}

static int aQMgr_actor_decide_quest(QUEST_MANAGER_ACTOR* manager, AnmPersonalID_c* target_anm_id) {
    Animal_c* client_animal = ((NPC_ACTOR*)*manager->client)->npc_info.animal_orig;
    aQMgr_target_c* target = &manager->target;
    int res = FALSE;

    if (client_animal != NULL) {
        int rsv_idx = mQst_GetReserve(target_anm_id, &client_animal->id);
        u32 type;
        u32 kind;

        if (rsv_idx != -1 && mQst_GetReserveQuest(&type, &kind, rsv_idx) == TRUE) {
            if (aQMgr_actor_check_occur(type, kind, target_anm_id, client_animal) == TRUE) {
                target->quest_info.quest_type = type;
                target->quest_info.quest_kind = kind;
                
                if (aQMgr_actor_set_free_quest(manager, target) == TRUE) {
                    res = TRUE;
                }
            } else {
                mQst_Id2InitReserve(&client_animal->id);
                if (mQst_CheckRenewalReserve() == TRUE) {
                    mQst_SetReverveAll();
                }
            }
        }
    }

    return res;
}

static void aQMgr_actor_decide_item(mActor_name_t* item) {
    *item = l_quest_item_list[RANDOM(ARRAY_COUNT(l_quest_item_list))];
}

static void aQMgr_actor_decide_cloth(mActor_name_t* item, mActor_name_t exclude_item) {
    mSP_SelectRandomItem_New(NULL, item, 1, &exclude_item, 1, mSP_KIND_CLOTH, mSP_LISTTYPE_ABC, FALSE);
}

static void aQMgr_actor_set_contest_work_data(int kind, aQMgr_work_data_c* work, Animal_c* animal) {
    switch (kind) {
        case mQst_CONTEST_KIND_FLOWER: {
            work->flower.exist_num = mQst_GetFlowerSeedNum(animal->home_info.bx, animal->home_info.bz);
            work->flower.goal_num = work->flower.exist_num + aQMgr_FLOWER_GOAL_NUM;
            work->flower.remain_num = aQMgr_FLOWER_GOAL_NUM;

            break;
        }
    }
}

static void aQMgr_actor_set_work_data(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    mQst_base_c* quest_info = &target->quest_info;

    switch (quest_info->quest_type) {
        case mQst_QUEST_TYPE_CONTEST:
            aQMgr_actor_set_contest_work_data(quest_info->quest_kind, &target->work,
                                              ((NPC_ACTOR*)*manager->client)->npc_info.animal_orig);
            break;
        case mQst_QUEST_TYPE_DELIVERY:
        case mQst_QUEST_TYPE_ERRAND:
            break;
    }
}

static AnmPersonalID_c* aQMgr_actor_decide_to_random(Animal_c* from_animal, AnmPersonalID_c* anm_id, aQMgr_quest_c* quest) {
    return mNpc_GetOtherAnimalPersonalIDOtherBlock(&from_animal->id, 1, from_animal->home_info.bx, from_animal->home_info.bz, TRUE);
}

static AnmPersonalID_c* aQMgr_actor_decide_to_random_without(Animal_c* from_animal, AnmPersonalID_c* anm_id, aQMgr_quest_c* quest) {
    AnmPersonalID_c exclude_ids[mQst_ERRAND_CHAIN_ANIMAL_NUM + 1];
    int bx = from_animal->home_info.bx;
    int bz = from_animal->home_info.bz;
    int i;

    for (i = 0; i < ARRAY_COUNT(exclude_ids); i++) {
        mNpc_ClearAnimalPersonalID(&exclude_ids[i]);
    }

    if (quest != NULL) {
        for (i = 0; i < mQst_ERRAND_CHAIN_ANIMAL_NUM; i++) {
            mNpc_CopyAnimalPersonalID(&exclude_ids[i], &quest->errand.info.chain.used_ids[i]);
        }
    }

    mNpc_CopyAnimalPersonalID(&exclude_ids[mQst_ERRAND_CHAIN_ANIMAL_NUM], &from_animal->id);
    return mNpc_GetOtherAnimalPersonalIDOtherBlock(exclude_ids, ARRAY_COUNT(exclude_ids), bx, bz, TRUE);
}

static AnmPersonalID_c* aQMgr_actor_decide_to_first_from(Animal_c* from_animal, AnmPersonalID_c* anm_id, aQMgr_quest_c* quest) {
    if (quest != NULL) {
        return &quest->errand.info.chain.used_ids[0];
    }
    return &from_animal->id;
}

static AnmPersonalID_c* aQMgr_actor_decide_to_foreign(Animal_c* from_animal, AnmPersonalID_c* anm_id, aQMgr_quest_c* quest) {
    AnmPersonalID_c* to_id = &Now_Private->stored_anm_id;
    AnmPersonalID_c* ret = NULL;

    if (mNpc_CheckFreeAnimalPersonalID(to_id) == FALSE) {
        ret = to_id;
    }

    return ret;
}

static AnmPersonalID_c* aQMgr_actor_decide_to_last_remove(Animal_c* from_animal, AnmPersonalID_c* anm_id, aQMgr_quest_c* quest) {
    AnmPersonalID_c* to_id = Save_GetPointer(last_removed_animal_id);
    AnmPersonalID_c* ret = NULL;

    if (mNpc_CheckFreeAnimalPersonalID(to_id) == FALSE) {
        ret = to_id;
    }

    return ret;
}

static AnmPersonalID_c* aQMgr_actor_decide_to_self(Animal_c* from_animal, AnmPersonalID_c* anm_id, aQMgr_quest_c* quest) {
    return &from_animal->id;
}

static AnmPersonalID_c* aQMgr_actor_decide_to_reserve(Animal_c* from_animal, AnmPersonalID_c* anm_id, aQMgr_quest_c* quest) {
    AnmPersonalID_c* ret = NULL;
    int idx = mNpc_SearchAnimalPersonalID(anm_id);

    if (idx != -1) {
        ret = &Save_Get(animals[idx]).id;
    }

    return ret;
}

typedef AnmPersonalID_c* (*aQMgr_DECIDE_TO_PROC)(Animal_c*, AnmPersonalID_c*, aQMgr_quest_c*);

static AnmPersonalID_c* aQMgr_actor_decide_to(Animal_c* from_animal, AnmPersonalID_c* anm_id, aQMgr_quest_c* quest, int to_type) {
    static aQMgr_DECIDE_TO_PROC decide_proc[] = {
        &aQMgr_actor_decide_to_random,
        &aQMgr_actor_decide_to_random_without,
        &aQMgr_actor_decide_to_first_from,
        &aQMgr_actor_decide_to_foreign,
        &aQMgr_actor_decide_to_last_remove,
        &aQMgr_actor_decide_to_self,
        &aQMgr_actor_decide_to_reserve,
    };

    AnmPersonalID_c* ret = NULL;

    if (to_type >= 0 && to_type < ARRAY_COUNT(decide_proc)) {
        ret = (*decide_proc[to_type])(from_animal, anm_id, quest);
    }

    return ret;
}

#define aQMgr_FTR_Q013_CANCEL_MAX 409


static mActor_name_t aQMgr_actor_decide_ftr_q013(void) {
    static mActor_name_t cancel_list[aQMgr_FTR_Q013_CANCEL_MAX];
    Private_c* priv = Now_Private;
    int cancel_num = 0;
    mActor_name_t item = EMPTY_NO;
    int i;

    for (i = 0; i < aQMgr_FTR_Q013_CANCEL_MAX; i++) {
        cancel_list[i] = EMPTY_NO;
    }

    if (priv != NULL) {
        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ITEM_IS_FTR(priv->inventory.pockets[i]) && (priv->inventory.pockets[i] < FTR_UMBRELLA_START || priv->inventory.pockets[i] > FTR_UMBRELLA_END) && (priv->inventory.pockets[i] < FTR_CLOTH_START || priv->inventory.pockets[i] > FTR_CLOTH_END) &&
                (priv->inventory.pockets[i] < FTR_INSECT_START || priv->inventory.pockets[i] > FTR_INSECT_END) && (priv->inventory.pockets[i] < FTR_FISH_START || priv->inventory.pockets[i] > FTR_FISH_END) &&
                (priv->inventory.pockets[i] < FTR_DINO_START || priv->inventory.pockets[i] > FTR_DINO_END) && !IS_ITEM_HANIWA(priv->inventory.pockets[i]) &&
                (priv->inventory.pockets[i] < FTR_START(FTR_NOG_COLLEGENOTE) || priv->inventory.pockets[i] > FTR_END(FTR_IKE_NIKKI_WAFU1))) {
                cancel_list[cancel_num] = priv->inventory.pockets[i];
                cancel_num++;
            }
        }

        for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
            if (ITEM_IS_FTR(priv->mail[i].present) && (priv->mail[i].present < FTR_UMBRELLA_START || priv->mail[i].present > FTR_UMBRELLA_END) && (priv->mail[i].present < FTR_CLOTH_START || priv->mail[i].present > FTR_CLOTH_END) &&
                (priv->mail[i].present < FTR_INSECT_START || priv->mail[i].present > FTR_INSECT_END) && (priv->mail[i].present < FTR_FISH_START || priv->mail[i].present > FTR_FISH_END) &&
                (priv->mail[i].present < FTR_DINO_START || priv->mail[i].present > FTR_DINO_END) && !IS_ITEM_HANIWA(priv->mail[i].present) &&
                (priv->mail[i].present < FTR_START(FTR_NOG_COLLEGENOTE) || priv->mail[i].present > FTR_END(FTR_IKE_NIKKI_WAFU1))) {
                cancel_list[cancel_num] = priv->mail[i].present;
                cancel_num++;
            }
        }

        if (mLd_PlayerManKindCheck() == FALSE) {
            mHm_flr_c* floor;
            mHm_lyr_c* layer;
            mActor_name_t* items;
            int j;
            int k;

            floor = Save_Get(homes[mHS_get_arrange_idx(Common_Get(player_no))]).floors;
            
            for (i = 0; i < mHm_ROOM_NUM; i++) {
                layer = &floor->layer_main;

                for (j = 0; j < 2; j++) {
                    items = layer->items[0];

                    for (k = 0; k < UT_TOTAL_NUM; k++) {
                        if (ITEM_IS_FTR(*items) &&
                            (*items < FTR_UMBRELLA_START || *items > FTR_UMBRELLA_END) &&
                            (*items < FTR_CLOTH_START || *items > FTR_CLOTH_END) &&
                            (*items < FTR_INSECT_START || *items > FTR_INSECT_END) &&
                            (*items < FTR_FISH_START || *items > FTR_FISH_END) &&
                            (*items < FTR_DINO_START || *items > FTR_DINO_END) &&
                            !IS_ITEM_HANIWA(*items) &&
                            (*items < FTR_START(FTR_NOG_COLLEGENOTE) || *items > FTR_END(FTR_IKE_NIKKI_WAFU1))) {
                            cancel_list[cancel_num] = *items;
                            cancel_num++;
                        }

                        if (cancel_num >= aQMgr_FTR_Q013_CANCEL_MAX) {
                            break;
                        }

                        items++;
                    }

                    if (cancel_num >= aQMgr_FTR_Q013_CANCEL_MAX) {
                        break;
                    }

                    layer++;
                }

                if (cancel_num >= aQMgr_FTR_Q013_CANCEL_MAX) {
                    break;
                }

                floor++;
            }
        }
    }

    mSP_SelectRandomItem_New(NULL, &item, 1, cancel_list, cancel_num, mSP_KIND_FURNITURE, mSP_LISTTYPE_ABC,
                             FALSE);

    return item;
}

static mActor_name_t aQMgr_actor_decide_shop(void) {
    static u8 cond_table[mSP_GOODS_COUNT];
    mActor_name_t item = ITM_CLOTH_START;
    mActor_name_t* goods = Save_Get(shop).items;
    int count = 0;
    int i;
    int selected;

    bzero(cond_table, mSP_GOODS_COUNT);

    for (i = 0; i < mSP_GOODS_COUNT; i++) {
        if (ITEM_IS_FTR(*goods) || ITEM_IS_CARPET(*goods) || ITEM_IS_WALL(*goods) || ITEM_IS_UMBRELLA2(*goods) || ITEM_IS_CLOTH(*goods)) {
            cond_table[i] = TRUE;
            count++;
        }

        goods++;
    }

    if (count > 0) {
        selected = RANDOM(count);

        for (i = 0; i < mSP_GOODS_COUNT; i++) {
            if (cond_table[i] == TRUE) {
                if (selected <= 0) {
                    item = Save_Get(shop).items[i];
                    break;
                }

                selected--;
            }
        }
    }

    return item;
}

static int aQMgr_actor_decide_quest_item(mActor_name_t* item, aQMgr_quest_c* quest, mActor_name_t animal_cloth, mActor_name_t set_item, int item_type) {
    int ret = FALSE;

    switch (item_type) {
        case aQMgr_QUEST_ITEM_RANDOM: {
            aQMgr_actor_decide_item(item);
            ret = TRUE;
        } break;

        case aQMgr_QUEST_ITEM_CLOTH: {
            aQMgr_actor_decide_cloth(item, animal_cloth);
            ret = TRUE;
        } break;

        case aQMgr_QUEST_ITEM_FROM_DATA: {
            *item = set_item;
            ret = TRUE;
        } break;

        case aQMgr_QUEST_ITEM_CURRENT_ITEM: {
            if (quest != NULL) {
                *item = quest->errand.item;
                ret = TRUE;
            } else {
                *item = ITM_CLOTH001;
            }
        } break;

        case aQMgr_QUEST_ITEM_NONE: {
            *item = EMPTY_NO;
            ret = TRUE;
        } break;

        case aQMgr_QUEST_ITEM_QBOX: {
            *item = mQst_GetQBoxItem();
            ret = TRUE;
        } break;

        case aQMgr_QUEST_ITEM_Q013: {
            *item = aQMgr_actor_decide_ftr_q013();
            ret = TRUE;
        } break;

        case aQMgr_QUEST_ITEM_SHOP: {
            *item = aQMgr_actor_decide_shop();
            ret = TRUE;
        } break;

        case aQMgr_QUEST_ITEM_INSECT_NOW: {
            *item = aSOI_get_insect_now();
            if (!ITEM_IS_INSECT(*item)) {
                *item = ITM_INSECT_START;
            }

            ret = TRUE;
        } break;

        case aQMgr_QUEST_ITEM_FISH_NOW: {
            *item = aSOG_get_fish_now();
            if (!ITEM_IS_FISH(*item)) {
                *item = ITM_FISH_START;
            }

            ret = TRUE;
        } break;
    }

    return ret;
}

static int aQMgr_actor_set_quest_data(QUEST_MANAGER_ACTOR* manager, aQMgr_quest_c* quest, AnmPersonalID_c* anm_id) {
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    AnmPersonalID_c* from_id = &aQMgr_GET_CLIENT_ANIMAL(manager)->id;
    aQMgr_target_c* target = &manager->target;
    aQMgr_set_data_c* set_data_p = target->set_data_p;
    int ret = FALSE;
    int i;

    if (set_data_p != NULL) {
        target->from_id = from_id;
        target->to_id = aQMgr_actor_decide_to(animal, anm_id, quest, set_data_p->to_type);

        if (target->to_id != NULL) {
            if (set_data_p->to_type == aQMgr_QUEST_TARGET_RANDOM_EXCLUDED) {
                target->errand_type = mQst_ERRAND_TYPE_CHAIN;
            }

            if (aQMgr_actor_decide_quest_item(&target->quest_item, quest, animal->cloth, set_data_p->item, set_data_p->src_item_type) == TRUE) {
                ret = TRUE;
                target->quest_item_cond = set_data_p->item_cond;

                if (set_data_p->handover_item == TRUE) {
                    int idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

                    if (idx != -1) {
                        target->quest_inv_item_idx = idx;
                    } else {
                        target->quest_inv_item_idx = -1;
                        ret = FALSE;
                    }
                } else {
                    target->quest_inv_item_idx = -1;
                }

                if (set_data_p->day_limit != 0) {
                    lbRTC_TimeCopy(&target->limit, Common_GetPointer(time.rtc_time));
                    lbRTC_Add_DD(&target->limit, set_data_p->day_limit);

                    if (target->quest_info.quest_type == mQst_QUEST_TYPE_CONTEST && target->quest_info.quest_kind == mQst_CONTEST_KIND_SHOP) {
                        target->limit.hour = 0;
                        target->limit.min = 0;
                        target->limit.sec = 0;
                    }

                    target->quest_info.time_limit_enabled = TRUE;
                } else {
                    target->quest_info.time_limit_enabled = FALSE;
                }

                target->quest_info.progress = set_data_p->last_step;
                aQMgr_actor_set_work_data(manager);
            }
        }
    }

    return ret;
}

static void aQMgr_actor_new_quest(QUEST_MANAGER_ACTOR* manager, int* sel_regist_idx, int regist_idx) {
    AnmPersonalID_c target_anm_id;
    aQMgr_quest_c* quest = NULL;
    aQMgr_regist_c* regist;
    u32 stage = 0;
    int quest_exist;

    if (regist_idx != -1) {
        int next_type;
        u8 next;

        regist = &manager->regist[regist_idx];
        quest = (aQMgr_quest_c*)regist->quest_info; // TODO: maybe quest_info should be aQMgr_quest_c* here?
        manager->target.quest_info.quest_type = quest->base.quest_type;
        next_type = 0;
        next = aQMgr_actor_get_errand_next(regist, manager->errand_next);

        if (next == 0) {
            next_type = RANDOM(2);
        } else if (next <= 2) {
            next_type = next - 1;
        }

        aQMgr_actor_set_errand_next(manager->errand_next, regist, next_type + 1);

        if (next_type == 0) {
            stage = 0;
        } else {
            stage = quest->base.progress - 1;
        }

        manager->target.free_data_p = (mQst_base_c*)quest; // TODO: Again, should this be aQMgr_quest_c*?
        manager->target.free_data_idx = regist->animal_idx;
        *sel_regist_idx = regist_idx;
        quest_exist = TRUE;
    } else {
        mNpc_ClearAnimalPersonalID(&target_anm_id);
        quest_exist = aQMgr_actor_decide_quest(manager, &target_anm_id);
    }

    if (quest_exist == TRUE) {
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_SET_DATA);
        quest_exist = aQMgr_actor_set_quest_data(manager, quest, &target_anm_id);
        if (quest_exist == TRUE) {
            if (regist_idx != -1) {
                aQMgr_regist_c* regist = manager->regist + regist_idx;

                manager->target.from_id = &aQMgr_GET_CLIENT_ANIMAL(manager)->id;

                if (stage != 0) {
                    manager->target.quest_info.progress = stage;
                }

                aQMgr_actor_set_errand_next(manager->errand_next, regist, 0);
            }
        } else {
            quest_exist = FALSE;
        }
    }

    if (quest_exist == FALSE) {
        manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
        mQst_ClearQuestInfo(&manager->target.quest_info);
        manager->target.free_data_p = NULL;
        manager->target.free_data_idx = -1;
    }
}

static void aQMgr_actor_set_lost_item(mActor_name_t* item) {
    int bx = 0, bz = 0;

    if (mQst_GetPlayerBlockNum(&bx, &bz) == TRUE) {
        mQst_SetLostItem(item, bx, bz);
    }
}

static void aQMgr_actor_set_delivery(aQMgr_target_c* target, AnmPersonalID_c* from_id) {
    mQst_delivery_c* delivery = (mQst_delivery_c*)target->free_data_p;

    mQst_CopyQuestInfo(&delivery->base, &target->quest_info);

    switch (delivery->base.quest_kind) {
        case mQst_DELIVERY_KIND_LOST_ITEM:
            aQMgr_actor_set_lost_item(&target->quest_item);
            break;
        case mQst_DELIVERY_KIND_LOST:
            mLd_CopyLandName(delivery->_48, Save_Get(last_removed_animal_mem_town_name));
            mLd_CopyLandName(delivery->_4E, Save_Get(land_info).name);

            if (target->to_id != NULL) {
                mNpc_CopyAnimalPersonalID(&delivery->recipient, target->to_id);
            }
            break;
        default:
            if (target->to_id != NULL) {
                mNpc_CopyAnimalPersonalID(&delivery->recipient, target->to_id);
            }
            break;
    }

    delivery->item = target->quest_item;
    if (from_id != NULL) {
        mNpc_CopyAnimalPersonalID(&delivery->sender, from_id);
    }
    delivery->base.time_limit = target->limit;
}

static void aQMgr_actor_set_errand(aQMgr_target_c* target, AnmPersonalID_c* from_id) {
    mQst_errand_c* errand = (mQst_errand_c*)target->free_data_p;
    AnmPersonalID_c* pids = errand->info.chain.used_ids;
    int i;

    mQst_CopyQuestInfo(&errand->base, &target->quest_info);
    mNpc_CopyAnimalPersonalID(&errand->sender, from_id);
    mNpc_CopyAnimalPersonalID(&errand->recipient, target->to_id);
    errand->base.time_limit = target->limit;
    errand->item = target->quest_item;
    errand->pockets_idx = target->quest_inv_item_idx;
    errand->errand_type = target->errand_type;

    switch (target->errand_type) {
        case mQst_ERRAND_TYPE_CHAIN: {
            // Copy this villager as a 'chain step' animal
            for (i = 0; i < mQst_ERRAND_CHAIN_ANIMAL_NUM; i++, pids++) {
                if (mNpc_CheckFreeAnimalPersonalID(pids) == TRUE) {
                    mNpc_CopyAnimalPersonalID(pids, from_id);
                    break;
                }
            }

            // Update that an entry in the chain has been used
            errand->info.chain.used_num++;
            break;
        }
    }
}

static void aQMgr_actor_set_contest(aQMgr_target_c* target, Animal_c* animal) {
    mQst_contest_c* contest = (mQst_contest_c*)target->free_data_p;

    mQst_CopyQuestInfo(&contest->base, &target->quest_info);
    contest->base.time_limit = target->limit;
    contest->requested_item = target->quest_item;

    switch (target->quest_info.quest_kind) {
        case mQst_CONTEST_KIND_SOCCER:
            break;

        case mQst_CONTEST_KIND_FLOWER: {
            contest->type = mQst_CONTEST_DATA_FLOWER;
            contest->info.flower_data.flowers_requested = target->work.flower.goal_num;
            break;
        }

        case mQst_CONTEST_KIND_FISH:
            break;
        case mQst_CONTEST_KIND_INSECT:
            break;

        case mQst_CONTEST_KIND_LETTER: {
            contest->type = mQst_CONTEST_DATA_LETTER;
            contest->info.letter_data.score = 0;
            contest->info.letter_data.present = EMPTY_NO;
            contest->info.letter_data.remail_status = mQst_REMAIL_STATUS_PENDING;
            break;
        }

        case mQst_CONTEST_KIND_GRASS: {
            contest->type = mQst_CONTEST_DATA_GRASS;
            contest->info.grass_data.start_grass_num = mQst_GetGrassNum(animal->home_info.bx, animal->home_info.bz);
            break;
        }
    }
}

static void aQMgr_actor_set_quest_info(QUEST_MANAGER_ACTOR* manager) {
    Private_c* priv = Now_Private;
    AnmPersonalID_c* from_id = &aQMgr_GET_CLIENT_ANIMAL(manager)->id;
    aQMgr_target_c* target = &manager->target;
    int type = target->quest_info.quest_type;

    switch (type) {
        case mQst_QUEST_TYPE_DELIVERY:
            aQMgr_actor_set_delivery(target, from_id);
            break;
        case mQst_QUEST_TYPE_ERRAND:
            aQMgr_actor_set_errand(target, from_id);
            break;
        case mQst_QUEST_TYPE_CONTEST:
            aQMgr_actor_set_contest(target, aQMgr_GET_CLIENT_ANIMAL(manager));
            break;
    }

    if (target->quest_inv_item_idx != -1) {
        mPr_SetPossessionItem(priv, target->quest_inv_item_idx, target->quest_item, target->quest_item_cond);
    }
}

static void aQMgr_actor_set_free_str(QUEST_MANAGER_ACTOR* manager, int regist_idx) {
    u8 str1[ANIMAL_NAME_LEN];
    u8 str0[ANIMAL_NAME_LEN];
    u8 str2[mIN_ITEM_NAME_LEN];

    aQMgr_target_c* target = &manager->target;
    aQMgr_regist_c* regist = NULL;

    if (regist_idx != -1) {
        regist = manager->regist + regist_idx;
    }

    if (target->from_id != NULL) {
        mNpc_GetNpcWorldNameAnm(str0, target->from_id);
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0, str0, sizeof(str0));
    }

    if (target->to_id != NULL) {
        mNpc_GetNpcWorldNameAnm(str1, target->to_id);
        mMsg_Set_free_str_cl(mMsg_Get_base_window_p(), mMsg_FREE_STR1, str1, sizeof(str1), 1);

        if (regist == NULL) {
            if (target->quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY && target->quest_info.quest_kind == mQst_DELIVERY_KIND_LOST) {
                mLd_SetFreeStrLandMuraName(Save_Get(last_removed_animal_mem_town_name), mMsg_FREE_STR3);
            } else {
                mLd_SetFreeStrLandMuraName(target->to_id->land_name, mMsg_FREE_STR3);
            }
        } else {
            mQst_base_c* quest_info = regist->quest_info;

            if (quest_info != NULL && quest_info->quest_type == mQst_QUEST_TYPE_DELIVERY && quest_info->quest_kind == mQst_DELIVERY_KIND_LOST) {
                mLd_SetFreeStrLandMuraName(((mQst_delivery_c*)quest_info)->_48, mMsg_FREE_STR3);
            } else {
                mLd_SetFreeStrLandMuraName(target->to_id->land_name, mMsg_FREE_STR3);
            }
        }
    }

    if (target->quest_item != EMPTY_NO) {
        mIN_copy_name_str(str2, target->quest_item);

        if (target->quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY && target->quest_info.quest_kind <= mQst_DELIVERY_KIND_LOST) {
            static u8 present_str[mMsg_FREE_STRING_LEN];

            mString_Load_StringFromRom(present_str, sizeof(present_str), 0x75B);
            mMsg_SET_FREE_STR_CL_ART(mMsg_FREE_STR2, present_str, sizeof(present_str), 2, target->quest_item);
        } else {
            mMsg_SET_FREE_STR_CL_ART(mMsg_FREE_STR2, str2, sizeof(str2), 2, target->quest_item);
        }

        mMsg_SET_ITEM_STR_ART(mMsg_ITEM_STR1, str2, sizeof(str2), target->quest_item);
    }

    if (target->from_id != NULL) {
        if (regist == NULL) {
            if (target->quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY && target->quest_info.quest_kind == mQst_DELIVERY_KIND_LOST) {
                mLd_SetFreeStrLandMuraName(Save_Get(land_info).name, mMsg_FREE_STR4);
            } else {
                mLd_SetFreeStrLandMuraName(target->from_id->land_name, mMsg_FREE_STR4);
            }
        } else {
            mQst_base_c* quest_info = regist->quest_info;

            if (quest_info != NULL && quest_info->quest_type == mQst_QUEST_TYPE_DELIVERY && quest_info->quest_kind == mQst_DELIVERY_KIND_LOST) {
                mLd_SetFreeStrLandMuraName(((mQst_delivery_c*)quest_info)->_4E, mMsg_FREE_STR4);
            } else {
                mLd_SetFreeStrLandMuraName(target->from_id->land_name, mMsg_FREE_STR4);
            }
        }
    }

    if (regist != NULL) {
        // @BUG - double 'NULL' check
        if (regist != NULL) {
            mQst_errand_c* errand = (mQst_errand_c*)regist->quest_info;

            if (errand != NULL && errand->base.quest_type == mQst_QUEST_TYPE_ERRAND) {
                AnmPersonalID_c* anm_id = &errand->info.chain.used_ids[0];

                if (mNpc_CheckFreeAnimalPersonalID(anm_id) == FALSE) {
                    mNpc_GetNpcWorldNameAnm(str1, anm_id);
                    mMsg_Set_free_str_cl(mMsg_Get_base_window_p(), mMsg_FREE_STR5, str1, sizeof(str1), 1);
                }
            }
        }
    }
}

static void aQMgr_actor_set_free_str_reward(aQMgr_target_c* target) {
    u8 str[mMsg_FREE_STRING_LEN];

    if (target->reward_kind == aQMgr_QUEST_REWARD_MONEY) {
        mFont_UnintToString(str, sizeof(str), target->pay, 10, TRUE, FALSE, FALSE);
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR9, str, sizeof(str));
    } else {
        mQst_SetItemNameStr(target->reward_item, mMsg_ITEM_STR0);
    }
}

static u32 aQMgr_actor_get_rate(int money_power) {
    // spread, base
    static f32 rate_table[][2] = {
        { 0.3000f, 0.0f },    // [  0,  29]
        { 0.7000f, -40.0f },  // [ 30,  99]
        { 2.7000f, -440.0f }, // [100, 367]
        { 1.3000f, -20.0f },  // [370, 498]
        { 1.0000f, 100.0f },  // [500, 599]
        { 0.6000f, 300.0f },  // [600, 659]
        { 0.0012f, 660.0f }   // [660, 660]
    };

    u32 rate = 0;

    if (money_power > 0) {
        f32 base;
        f32 scale;
        int idx = money_power / 100;

        if (idx >= ARRAY_COUNT(rate_table)) {
            idx = ARRAY_COUNT(rate_table) - 1;
        }

        base = rate_table[idx][1];
        scale = rate_table[idx][0];
        rate = base + scale * (f32)money_power;
    }

    return rate;
}

static u32 aQMgr_actor_get_pay(u32 base_pay) {
    f32 scale = 100.0f;
    static f32 plus_minus[2] = { 1.0f, -1.0f };
    int dir_idx = RANDOM(2);
    f32 percent = fqrand();
    f32 dir = plus_minus[dir_idx];
    u32 pay;
    f32 pay_f;
    f32 final_pay;

    scale += dir * 10.0f * percent;

    pay = aQMgr_actor_get_rate(mPr_GetMoneyPower());

    if (pay > 700) {
        pay = 700;
    }

    // min:  (~90.0 * 100) / 10000 = ~0.91x (max percent = ~1.1x)
    // max: (~109.9 * 760) / 10000 = ~8.36x (min percent = ~6.916x)
    pay_f = 100.0f;
    pay_f += pay;
    final_pay = (scale * pay_f) / 10000.0f;
    final_pay = base_pay * final_pay;
    return final_pay;
}

static int aQMgr_actor_hand_reward(aQMgr_target_c* target) {
    Private_c* priv = Now_Private;
    int reward_kind = target->reward_kind;
    int inv_idx = target->quest_inv_item_idx;
    int res = FALSE;

    if (reward_kind == aQMgr_QUEST_REWARD_MONEY) {
        u32 money = priv->inventory.wallet;

        money += target->pay;
        if (money > mPr_WALLET_MAX) {
            if (money <= (mPr_WALLET_MAX + mPr_GetPossessionItemSum(priv, EMPTY_NO) * 30000)) {
                if (inv_idx != -1 && priv->inventory.pockets[inv_idx] == EMPTY_NO) {
                    mPr_SetPossessionItem(priv, inv_idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
                    money -= 30000;
                }

                while (money > mPr_WALLET_MAX) {
                    inv_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);

                    if (inv_idx != -1) {
                        mPr_SetPossessionItem(priv, inv_idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
                        money -= 30000;
                    } else {
                        money = mPr_WALLET_MAX; // ran out of space
                        break;
                    }
                }

                priv->inventory.wallet = money; // remaining money goes in the wallet
                res = TRUE;
            }
        } else {
            priv->inventory.wallet = money;
            res = TRUE;
        }
    } else if (reward_kind != -1) {
        if (inv_idx != -1 && priv->inventory.pockets[inv_idx] == EMPTY_NO) {
            mPr_SetPossessionItem(priv, inv_idx, target->reward_item, mPr_ITEM_COND_NORMAL);
            res = TRUE;
        } else {
            inv_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);

            if (inv_idx != -1) {
                mPr_SetPossessionItem(priv, inv_idx, target->reward_item, mPr_ITEM_COND_NORMAL);
                res = TRUE;
            }
        }
    }

    return res;
}

static void aQMgr_actor_get_errand_reward(u8* reward_percents, u32* payment, u8 npc_num) {
    static u8 errand_reward[4][aQMgr_QUEST_REWARD_NUM] = {
        { 0, 75, 25, 0, 0, 0, 0, 0 },   // 75% stationery, 25% clothing
        { 25, 25, 25, 0, 0, 25, 0, 0 }, // 25% ftr, 25% stationery, 25% clothing, 25% money
        { 50, 0, 25, 0, 0, 25, 0, 0 },  // 50% ftr, 25% clothing, 25% money
        { 65, 0, 0, 5, 5, 25, 0, 0 },   // 65% ftr, 5% carpet, 5% wallpaper, 25% money
    };
    u32 reward_pay[4] = { 0, 500, 750, 1000 }; // someone forgot a `static` qualifier here
    u8* reward_p;
    int i;

    npc_num--;
    if (npc_num >= ARRAY_COUNT(reward_pay)) {
        npc_num = ARRAY_COUNT(reward_pay) - 1;
    }

    reward_p = errand_reward[npc_num];
    for (i = 0; i < aQMgr_QUEST_REWARD_NUM; i++) {
        *reward_percents++ = *reward_p++;
    }

    *payment = reward_pay[npc_num];
}

static void aQMgr_actor_get_grass_reward(u8* reward_percents, u8* src_reward_percents, int grass_num) {
    static int idx_table[] = { aQMgr_QUEST_REWARD_CLOTH, aQMgr_QUEST_REWARD_MONEY };
    int thresh;
    int i;

    for (i = 0; i < aQMgr_QUEST_REWARD_NUM; i++) {
        reward_percents[i] = *src_reward_percents++;
    }

    thresh = grass_num << 1;
    for (i = 0; i < ARRAY_COUNT(idx_table); i++) {
        u8 n_percent;

        if (thresh > reward_percents[idx_table[i]]) {
            n_percent = reward_percents[idx_table[i]];
            reward_percents[idx_table[i]] = 0;
        } else {
            n_percent = thresh;
            reward_percents[idx_table[i]] -= n_percent;
        }

        if (n_percent + reward_percents[0] > 100) {
            reward_percents[0] = 100;
        } else {
            reward_percents[0] += n_percent;
        }
    }
}

static mActor_name_t aQMgr_actor_get_other_pl_cloth() {
    Private_c* priv = Now_Private;
    mActor_name_t other_pl_cloth = ITM_CLOTH001;

    if (priv != NULL) {
        aQMgr_actor_decide_cloth(&other_pl_cloth, priv->cloth.item);
    }

    return other_pl_cloth;
}

static void aQMgr_actor_set_reward(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx = manager->regist_idx;
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    aQMgr_target_c* target = &manager->target;
    aQMgr_set_data_c* set_data_p = target->set_data_p;
    u32 pay = 0;
    u8 reward_percentages[aQMgr_QUEST_REWARD_NUM];
    u8* reward_percent_p;
    u8 prob_tbl[100];
    int prob_idx;
    int j;
    int i;

    if (regist_idx >= 0 && regist_idx < aQMgr_REGIST_NUM) {
        if (target->quest_info.quest_type == mQst_QUEST_TYPE_ERRAND) {
            aQMgr_actor_get_errand_reward(
                reward_percentages, &pay,
                ((mQst_errand_c*)manager->regist[regist_idx].quest_info)->info.chain.used_num);
            reward_percent_p = reward_percentages;
        } else if (target->quest_info.quest_type == mQst_QUEST_TYPE_CONTEST && target->quest_info.quest_kind == mQst_CONTEST_KIND_GRASS) {
            aQMgr_actor_get_grass_reward(reward_percentages, set_data_p->reward_percentages, ((mQst_contest_c*)manager->regist[regist_idx].quest_info)->info.grass_data.start_grass_num);
            pay = set_data_p->max_pay;
            reward_percent_p = reward_percentages;
        } else {
            pay = set_data_p->max_pay;
            reward_percent_p = set_data_p->reward_percentages;
        }
    } else {
        pay = set_data_p->max_pay;
        reward_percent_p = set_data_p->reward_percentages;
    }

    target->reward_kind = mQst_GetRandom100(reward_percent_p, aQMgr_QUEST_REWARD_NUM);
    switch (target->reward_kind) {
        case aQMgr_QUEST_REWARD_MONEY:
            pay = aQMgr_actor_get_pay(pay);
            target->pay = pay;
            target->reward_item = ITM_MONEY_1000;
            break;
        case aQMgr_QUEST_REWARD_WORN_CLOTH:
            if (animal != NULL) {
                if (manager->cloth == RSV_CLOTH1) {
                    target->reward_item = aQMgr_actor_get_other_pl_cloth();
                    target->reward_kind = aQMgr_QUEST_REWARD_CLOTH;
                } else {
                    target->reward_item = manager->cloth;
                }
            } else {
                target->reward_item = ITM_CLOTH001;
            }
            break;
        case aQMgr_QUEST_REWARD_HANIWA:
            mSP_RandomHaniwaSelect(&target->reward_item, 1);
            break;
        default:
            mQst_GetGoods_common(&target->reward_item, &animal->id, target->reward_kind, NULL, 0, mSP_LISTTYPE_ABC);
            break;
    }
}

static void aQMgr_talk_quest_clear_quest(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx = manager->regist_idx;

    if (regist_idx != -1) {
        aQMgr_regist_c* regist = manager->regist + regist_idx;
        aQMgr_quest_c* quest = (aQMgr_quest_c*)regist->quest_info;

        switch (quest->base.quest_type) {
            case mQst_QUEST_TYPE_DELIVERY:
                mQst_ClearDelivery(&quest->delivery, 1);
                break;
            case mQst_QUEST_TYPE_ERRAND:
                mQst_ClearErrand(&quest->errand, 1);
                break;
            case mQst_QUEST_TYPE_CONTEST:
                mQst_ClearContest(&quest->contest);
                break;
        }
    }
}

static void aQMgr_actor_talk_finish(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    aQMgr_quest_c* free_quest = (aQMgr_quest_c*)target->free_data_p;
    int regist_idx = manager->regist_idx;

    if (regist_idx != -1) {
        aQMgr_talk_quest_clear_quest(manager);
        (*manager->clear_regist_proc)(manager->regist, aQMgr_REGIST_NUM);
    }

    if (free_quest != NULL) {
        int idx = 0;
        (*manager->regist_quest_proc)(manager, &idx, free_quest, target->free_data_idx);
    }
}

static void aQMgr_talk_quest_start_choice_random(int* choice_no, int start, int num) {
    *choice_no = start + mQst_GetRandom(num);
}

static void aQMgr_talk_quest_select_get_choice(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_choice_c* choice = &manager->choice;
    int talk_step = manager->talk_step;
    aQMgr_target_c* target = &manager->target;
    int choice_num = 3;
    int type = target->quest_info.quest_type;
    int kind = target->quest_info.quest_kind;

    switch (talk_step) {
        case aQMgr_TALK_STEP_RENEW_ERRAND_OR_NORMAL: {
            choice->choice_ids[0] = 0x97; // "I'm picking up!"
            choice->choice_ids[1] = 0x89; // "Let's talk!"
            break;
        }

        case aQMgr_TALK_STEP_RECONF_OR_NORMAL: {
            if (type == mQst_QUEST_TYPE_CONTEST) {
                switch (kind) {
                    case mQst_CONTEST_KIND_FISH:
                    case mQst_CONTEST_KIND_INSECT:
                    case mQst_CONTEST_KIND_FTR:
                    case mQst_CONTEST_KIND_SHOP:
                        choice->choice_ids[0] = 0x2B3; // "What did you want again?"
                        aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x89, 10);
                        break;
                    default:
                        aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x89, 10);
                        choice_num = 2;
                        break; 
                }
            } else if (type == mQst_QUEST_TYPE_DELIVERY && kind == mQst_DELIVERY_KIND_LOST_ITEM) {
                choice->choice_ids[0] = 0x2B3; // "What did you want again?"
                aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x89, 10);
                choice_num = 3;
            } else {
                aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x89, 10);
                choice_num = 2;
            }
            break;
        }

        case aQMgr_TALK_STEP_FIN_QUEST_START: {
            choice->choice_ids[0] = 0x68; // "Delivery!"

            if (type == mQst_QUEST_TYPE_DELIVERY) {
                switch (kind) {
                    case mQst_DELIVERY_KIND_LOST:
                        choice->choice_ids[0] = 0x2AB; // "Letter!"
                        break;
                    case mQst_DELIVERY_KIND_LOST_ITEM:
                        choice->choice_ids[0] = 0x2B1; // "Lose anything?"
                        break;
                    default:
                        choice->choice_ids[0] = 0x68; // "Delivery!"
                        break;
                }
            } else if (type == mQst_QUEST_TYPE_ERRAND) {
                choice->choice_ids[0] = 0x97; // "I'm picking up!"
            } else if (type == mQst_QUEST_TYPE_CONTEST) {
                switch (kind) {
                    case mQst_CONTEST_KIND_FISH:
                        choice->choice_ids[0] = 0xEA; // "I brought fish."
                        break;
                    case mQst_CONTEST_KIND_INSECT:
                        choice->choice_ids[0] = 0xEB; // "I caught a bug!"
                        break;
                    case mQst_CONTEST_KIND_FTR:
                    case mQst_CONTEST_KIND_SHOP:
                        choice->choice_ids[0] = 0x2B4; // "Brought it!"
                        break;
                    default:
                        choice->choice_ids[0] = 0x68; // "Delivery!"
                        break;
                }
            }

            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x89, 10);
            break;
        }

        case aQMgr_TALK_STEP_TALK_FIN_QUEST_START_NOT_HAND:
        case aQMgr_TALK_STEP_AFTER_REWARD:
        case aQMgr_TALK_STEP_AFTER_REWARD_SELECT: {
            switch (kind) {
                case mQst_CONTEST_KIND_SOCCER:
                    choice->choice_ids[0] = 0x2B0; // "About the ball..."
                    break;
                case mQst_CONTEST_KIND_FLOWER:
                    choice->choice_ids[0] = 0x2B2; // "About the flowers..."
                    break;
                case mQst_CONTEST_KIND_GRASS:
                    choice->choice_ids[0] = 0x2AF; // "About the weeds..."
                    break;
                default:
                    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x89, 10);
                    break;
            }

            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x89, 10);
            break;
        }

        case aQMgr_TALK_STEP_CONTEST_HOKA_OR_NORMAL: {
            switch (kind) {
                case mQst_CONTEST_KIND_LETTER:
                    choice->choice_ids[0] = 0x89; // "Let's talk!"
                    break;
                default:
                    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x89, 10);
                    break;
            }

            choice_num = 2;
            break;
        }

        case aQMgr_TALK_STEP_FINISH_LETTER: {
            choice->choice_ids[0] = 0x89; // "Let's talk!"
            choice_num = 2;
            break;
        }

        case aQMgr_TALK_STEP_FULL_ITEM_OR_NORMAL: {
            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x7F, 10);
            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x89, 10);
            break;
        }

        case aQMgr_TALK_STEP_SICK_BEFORE_SELECT: {
            choice->choice_ids[0] = 0x2AC; // "Medicine!"
            choice->choice_ids[1] = 0x22C; // "Are you OK?"
            break;
        }

        case aQMgr_TALK_STEP_SICK_AFTER_SELECT: {
            choice->choice_ids[0] = 0x2AE; // "About the medicine..."
            choice_num = 2;
            break;
        }

        case aQMgr_TALK_STEP_REPORT_QBOX_OR_NORMAL: {
            choice->choice_ids[0] = 0x323; // "Delivered it!"
            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x89, 10);
            choice_num = 3;
            break;
        }

        default: {
            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x89, 10);
            choice_num = 2;
            break;
        }
    }

    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[choice_num - 1], 0x16A, 5);
    choice->talk_action = -1;
    choice->choice_num = choice_num;
}

static void aQMgr_talk_quest_select_get_choice_island(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_choice_c* choice = &manager->choice;

    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x89, 10);
    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x16A, 5);
    choice->talk_action = -1;
    choice->choice_num = 2;
}

static void aQMgr_talk_quest_start_choice(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_choice_c* choice = &manager->choice;

    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x43, 10);
    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x4D, 10);
    choice->choice_num = 2;
    choice->talk_action = -1;
}

static void aQMgr_talk_quest_finish_firstjob_open_quest() {
    mQst_errand_c* errand = mQst_GetFirstJobData();
    u32 event_id = mEv_SAVED_FIRSTJOB_PLR0 + Common_Get(player_no);

    if (mLd_PlayerManKindCheck() == FALSE && mEv_CheckEvent(event_id) == TRUE && errand != NULL &&
        errand->base.quest_type == mQst_QUEST_TYPE_ERRAND && errand->base.quest_kind == mQst_ERRAND_FIRSTJOB_OPEN &&
        errand->base.progress == 2 && errand->errand_type == mQst_ERRAND_TYPE_FIRST_JOB) {
        errand->base.progress = 0;
    }
}

static void aQMgr_talk_quest_set_cancel_msg_com(QUEST_MANAGER_ACTOR* manager, int base_cancel_msg, int talk_sel_lower, int talk_sel_upper, int looks) {
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    manager->category_msg_no_start = 0;
    manager->msg_no = base_cancel_msg;
    manager->msg_no += mQst_GetIdxTalkSelect(talk_sel_lower, talk_sel_upper, looks);
    manager->choice.talk_action = -1;
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_talk_quest_set_cancel_msg(QUEST_MANAGER_ACTOR* manager) {
    static int cancel_msg_table[mNpc_LOOKS_NUM] = { 0x254A, 0x254D, 0x2550, 0x2553, 0x2556, 0x2559 };
    int looks = mNpc_GetNpcLooks(*manager->client);
    int msg_no = cancel_msg_table[looks];

    aQMgr_talk_quest_set_cancel_msg_com(manager, msg_no, 0x7D, 0x80, looks);
}

static void aQMgr_talk_quest_set_cancel_msg_island(QUEST_MANAGER_ACTOR* manager) {
    static int cancel_msg_table[mNpc_LOOKS_NUM] = { 0x359D, 0x35A0, 0x35A3, 0x35A6, 0x35A9, 0x35AC };
    int looks = mNpc_GetNpcLooks(*manager->client);
    int msg_no = cancel_msg_table[looks];

    aQMgr_talk_quest_set_cancel_msg_com(manager, msg_no, 0x115, 0x118, looks);
}

static void aQMgr_talk_quest_change_normal_or_hint(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == manager->choice.choice_num - 1) {
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        aQMgr_talk_quest_set_cancel_msg(manager);
    } else {
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 1);
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CHANGE_TALK_NORMAL);
    }
}

static int l_contest_hoka_msg_q007[mNpc_LOOKS_NUM] = { 0x0E21, 0x0E24, 0x0E27, 0x0E2A, 0x0E2D, 0x0E30 };
static int l_contest_hoka_msg_q009[mNpc_LOOKS_NUM] = { 0x1057, 0x105A, 0x105D, 0x1060, 0x1063, 0x1066 };
static int l_contest_hoka_msg_q011[mNpc_LOOKS_NUM] = { 0x1544, 0x1547, 0x154A, 0x154D, 0x1550, 0x1553 };
static int l_contest_hoka_msg_q012[mNpc_LOOKS_NUM] = { 0x15C2, 0x15C5, 0x15C8, 0x15CB, 0x15CE, 0x15D1 };
static int l_contest_hoka_msg_q010[mNpc_LOOKS_NUM] = { 0x1AF3, 0x1AF6, 0x1AF9, 0x1AFC, 0x1AFF, 0x1B02 };
static int l_contest_hoka_msg_q013[mNpc_LOOKS_NUM] = { 0x2431, 0x2434, 0x2437, 0x243A, 0x243D, 0x2440 };
static int l_contest_hoka_msg_q006[mNpc_LOOKS_NUM] = { 0x2032, 0x2035, 0x2038, 0x203B, 0x203E, 0x2041 };

static int* l_contest_hoka_msg_no[mQst_CONTEST_KIND_NUM] = {
    l_contest_hoka_msg_q007,
    l_contest_hoka_msg_q009,
    l_contest_hoka_msg_q011,
    l_contest_hoka_msg_q012,
    l_contest_hoka_msg_q010,
    l_contest_hoka_msg_q013,
    NULL,
    l_contest_hoka_msg_q006,
    NULL,
};

static int aQMgr_talk_quest_get_contest_hoka_msg_no(mQst_contest_c* contest, Animal_c* animal, int looks) {
    static int hoka_kare_table[mNpc_LOOKS_NUM] = { 0x1069, 0x106C, 0x106F, 0x1072, 0x1075, 0x1078 };
    static int hoka_haeta_table[mNpc_LOOKS_NUM] = { 0x2044, 0x2047, 0x204A, 0x204D, 0x2050, 0x2053 };
    u32 kind = contest->base.quest_kind;
    int hoka_msg_no = 0;

    switch (kind) {
        case mQst_CONTEST_KIND_FLOWER:
            if (contest->info.flower_data.flowers_requested > mQst_GetFlowerSeedNum(animal->home_info.bx, animal->home_info.bz)) {
                hoka_msg_no = hoka_kare_table[looks];
            }
            break;
        case mQst_CONTEST_KIND_GRASS:
            if (mQst_GetGrassNum(animal->home_info.bx, animal->home_info.bz) > 0) {
                hoka_msg_no = hoka_haeta_table[looks];
            }
            break;
    }

    if (hoka_msg_no == 0 && l_contest_hoka_msg_no[kind] != NULL) {
        hoka_msg_no = l_contest_hoka_msg_no[kind][looks];
    }

    return hoka_msg_no;
}

static void aQMgr_talk_quest_set_work(aQMgr_work_data_c* work, int type, int kind) {
    // stubbed
}
static int q005_byouki_msg_lv1[mNpc_LOOKS_NUM] = {0x3F91, 0x3FAF, 0x3FCD, 0x3FEB, 0x4009, 0x4027};
static int q005_byouki_msg_lv2[mNpc_LOOKS_NUM] = {0x4045, 0x4063, 0x4081, 0x409F, 0x40BD, 0x40DB};
static int q005_byouki_msg_lv3[mNpc_LOOKS_NUM] = {0x40F9, 0x4117, 0x4135, 0x4153, 0x4171, 0x418F};
static int q005_byouki_msg_lv4[mNpc_LOOKS_NUM] = {0x41AD, 0x41CB, 0x41E9, 0x4207, 0x4225, 0x4243};
static int q005_byouki_msg_lv5[mNpc_LOOKS_NUM] = {0x4261, 0x427F, 0x429D, 0x42BB, 0x42D9, 0x42F7};

static int* q005_byouki_msg_table[mNpc_SICK_LV_NUM] = {
    q005_byouki_msg_lv5,
    q005_byouki_msg_lv4,
    q005_byouki_msg_lv3,
    q005_byouki_msg_lv2,
    q005_byouki_msg_lv1,
};

static int q005_shitsumon_msg_lv1[mNpc_LOOKS_NUM] = {0x4456, 0x4462, 0x446E, 0x447A, 0x4486, 0x4492};
static int q005_shitsumon_msg_lv2[mNpc_LOOKS_NUM] = {0x4498, 0x449E, 0x44A4, 0x44AA, 0x44B0, 0x44B6};
static int q005_shitsumon_msg_lv3[mNpc_LOOKS_NUM] = {0x52C5, 0x52CB, 0x52D1, 0x52D7, 0x52DD, 0x52E3};
static int q005_shitsumon_msg_lv4[mNpc_LOOKS_NUM] = {0x52E9, 0x52EF, 0x52F5, 0x52FB, 0x5301, 0x5307};
static int q005_shitsumon_msg_lv5[mNpc_LOOKS_NUM] = {0x530D, 0x5313, 0x5319, 0x531F, 0x5325, 0x532B};

static int* q005_shitsumon_msg_table[mNpc_SICK_LV_NUM] = {
    q005_shitsumon_msg_lv5,
    q005_shitsumon_msg_lv4,
    q005_shitsumon_msg_lv3,
    q005_shitsumon_msg_lv2,
    q005_shitsumon_msg_lv1,
};

static int q005_osewasama_msg[mNpc_LOOKS_NUM] = {0x040A, 0x040D, 0x0410, 0x0413, 0x0416, 0x0419};
static int q005_hokanohito_msg[mNpc_LOOKS_NUM] = {0x2B73, 0x2B76, 0x2B79, 0x2B7C, 0x2B7F, 0x2B82};
static int q001_aketadaro_msg[mNpc_LOOKS_NUM] = {0x0013, 0x0016, 0x0019, 0x001C, 0x001F, 0x0022};
static int q002_aketadaro_msg[mNpc_LOOKS_NUM] = {0x0304, 0x0307, 0x030A, 0x030D, 0x0310, 0x0313};
static int q003_aketadaro_msg[mNpc_LOOKS_NUM] = {0x1134, 0x1137, 0x113A, 0x113D, 0x1140, 0x1143};

static int aQMgr_actor_get_select_msg_no(QUEST_MANAGER_ACTOR* manager) {
    int msg_no = 0x2A6;

    if (manager->get_common_msg_proc != NULL) {
        msg_no = (*manager->get_common_msg_proc)(manager, aQMgr_GET_COMMON_MSG_TYPE_SELECT);
    }

    return msg_no;
}

static int aQMgr_select_talk_check_reward(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_actor_check_still_reward(manager);
}

static int aQMgr_select_talk_check_sick(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_actor_check_own_quest_just(manager, mQst_QUEST_TYPE_CONTEST, mQst_CONTEST_KIND_SICK, aQMgr_CHECK_TO);
}

static int aQMgr_select_talk_check_to(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_actor_check_own_quest(manager, aQMgr_CHECK_TO);
}

static int aQMgr_select_talk_check_from_lost(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_actor_check_own_quest_just(manager, mQst_QUEST_TYPE_DELIVERY, mQst_DELIVERY_KIND_LOST_ITEM, aQMgr_CHECK_FROM);
}

static int aQMgr_select_talk_check_from_opened_qbox(QUEST_MANAGER_ACTOR* manager) {
    int ret_idx = -1;
    int quest_kind;

    for (quest_kind = mQst_DELIVERY_KIND_NORMAL; quest_kind < mQst_DELIVERY_KIND_LOST; quest_kind++) {
        int idx = aQMgr_actor_check_own_quest_just(manager, mQst_QUEST_TYPE_DELIVERY, quest_kind, aQMgr_CHECK_FROM);

        if (idx != -1 && manager->regist[idx].quest_info != NULL && manager->regist[idx].quest_info->progress == 1) {
            ret_idx = idx;
            break;
        }
    }

    return ret_idx;
}

static int aQMgr_select_talk_check_from(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_actor_check_own_quest(manager, aQMgr_CHECK_FROM);
}

static int aQMgr_select_talk_check_errand_from(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_actor_check_errand_from(manager);
}

static void aQMgr_select_talk_sub_reward(QUEST_MANAGER_ACTOR* manager, int* regist_idx, int* sel_regist_idx, int* new_quest) {
    mQst_base_c* quest = NULL;
    u32 quest_type = mQst_QUEST_TYPE_DELIVERY;
    u32 quest_kind = mQst_DELIVERY_KIND_LOST;

    if (*regist_idx != -1) {
        aQMgr_regist_c* regist = &manager->regist[*regist_idx];
        quest = regist->quest_info;
        if (quest != NULL) {
            quest_type = quest->quest_type;
            quest_kind = quest->quest_kind;
        }
    }

    if (quest_type == mQst_QUEST_TYPE_CONTEST) {
        switch (quest_kind) {
            case mQst_CONTEST_KIND_SICK:
                manager->msg_category = aQMgr_MSG_KIND_AFTER_REWARD;
                manager->talk_step = aQMgr_TALK_STEP_SICK_REWARD;
                manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
                break;
            default:
                manager->msg_category = aQMgr_MSG_KIND_NONE;
                manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
                manager->talk_step = aQMgr_TALK_STEP_AFTER_REWARD_SELECT;
                manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
                break;
        }
    } else {
        manager->msg_category = aQMgr_MSG_KIND_AFTER_REWARD;
        manager->talk_step = aQMgr_TALK_STEP_AFTER_REWARD;
    }
}

static int aQMgr_check_sick_other_talk(mNpc_SickInfo_c* sick_info, Animal_c* animal, PersonalID_c* pid) {
    Anmmem_c* memory = animal->memories;
    int ret = FALSE;
    int memory_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);
    
    if (memory_idx != -1) {
        memory += memory_idx;
        if (
            lbRTC_IsEqualTime(&sick_info->recovery_time, &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) == FALSE &&
            lbRTC_IsEqualTime(&sick_info->recovery_time, &mTM_rtcTime_zero_code, lbRTC_CHECK_ALL) == FALSE &&
            lbRTC_IsEqualTime(&memory->last_speak_time, &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) == FALSE &&
            lbRTC_IsOverTime(&sick_info->recovery_time, &memory->last_speak_time) == -1) {
            ret = TRUE;
        }
    }

    return ret;
}

static int aQMgr_get_sick_select_msg(int sick_lv, int looks, int ofs) {
    if (sick_lv < 0 || sick_lv >= mNpc_SICK_LV_NUM) {
        sick_lv = mNpc_SICK_LV1;
    }

    return ofs + q005_shitsumon_msg_table[sick_lv][looks];
}

static int aQMgr_get_sick_msg(int sick_lv, int looks, int ofs) {
    if (sick_lv < 0 || sick_lv >= mNpc_SICK_LV_NUM) {
        sick_lv = mNpc_SICK_LV1;
    }

    return ofs + q005_byouki_msg_table[sick_lv][looks];
}

static void aQMgr_select_talk_sub_sick(QUEST_MANAGER_ACTOR* manager, int* regist_idx, int* sel_regist_idx, int* new_quest) {
    aQMgr_regist_c* regist;
    mNpc_SickInfo_c* sick_info;
    Animal_c* animal;
    Private_c* priv;
    mQst_contest_c* quest;
    int looks;
    int sick_lv;
    int color;
    int next_sick_lv;

    animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    priv = Now_Private;
    sick_info = Save_GetPointer(sick_info);
    looks = mNpc_GetNpcLooks(*manager->client);
    regist = manager->regist + *regist_idx;
    quest = (mQst_contest_c*)regist->quest_info;
    sick_lv = sick_info->sick_level;
    color = 0;

    manager->msg_category = aQMgr_MSG_KIND_NONE;
    if (aQMgr_actor_check_finish(regist, animal) == TRUE) {
        if (mPr_GetPossessionItemIdx(priv, EMPTY_NO) != -1) {
            manager->msg_category = aQMgr_MSG_KIND_COMPLETE_INIT;
            manager->talk_step = aQMgr_TALK_STEP_SICK_REWARD;
        } else {
            if (regist->quest_info->give_reward == FALSE) {
                manager->msg_category = aQMgr_MSG_KIND_REWARD_FULL_ITEM;
            }

            quest->base.give_reward = TRUE;
            manager->talk_step = aQMgr_TALK_STEP_WAIT;
        }
    } else if (aQMgr_actor_check_limit(regist) == FALSE) {
        if (quest->base.progress == 0 || quest->base.progress == 1) {
            if (mPr_CheckCmpPersonalID(&quest->player_id, &priv->player_ID) == FALSE &&
                aQMgr_check_sick_other_talk(sick_info, animal, &priv->player_ID) == TRUE) {
                if (mNpc_CheckSickPersonalID(sick_info, &priv->player_ID) == TRUE) {
                    manager->category_msg_no_start = q005_osewasama_msg[looks];
                } else {
                    manager->category_msg_no_start = q005_hokanohito_msg[looks];
                }

                mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR12, quest->player_id.player_name, PLAYER_NAME_LEN);
                manager->talk_step = aQMgr_TALK_STEP_WAIT;
                if (quest->base.progress == 0) {
                    mNpc_HealSick(sick_info);
                }

                *new_quest = FALSE;
            } else {
                manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                mQst_ClearQuestInfo(&manager->target.quest_info);
                manager->target.free_data_p = NULL;
                manager->target.free_data_idx = -1;
                *new_quest = FALSE;
                manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
            }
        } else if (sick_info->gave_medicine == FALSE) {
            manager->category_msg_no_start = aQMgr_get_sick_select_msg(sick_lv, looks, 0);
            manager->talk_step = aQMgr_TALK_STEP_SICK_BEFORE_SELECT;
        } else {
            manager->talk_step = aQMgr_TALK_STEP_SICK_AFTER_SELECT;
            if (sick_lv > mNpc_SICK_LV5 && sick_lv <= mNpc_SICK_LV_NOT_SICK) {
                next_sick_lv = mNpc_CheckSoonRecoverySick(Save_GetPointer(sick_info)) != TRUE ? sick_lv - 1 : mNpc_SICK_LV1;

                manager->category_msg_no_start = aQMgr_get_sick_select_msg(next_sick_lv, looks, 3);
                if (mPr_CheckCmpPersonalID(&sick_info->id_gave_medicine[next_sick_lv], &Now_Private->player_ID) == TRUE) {
                    color = 3;
                }

                mMsg_Set_free_str_cl(mMsg_Get_base_window_p(), mMsg_FREE_STR12, sick_info->id_gave_medicine[next_sick_lv].player_name, PLAYER_NAME_LEN, color);
            }
        }
    } else {
        manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
        mQst_ClearQuestInfo(&manager->target.quest_info);
        manager->target.free_data_p = NULL;
        manager->target.free_data_idx = -1;
        *new_quest = FALSE;
        manager->regist_idx = *regist_idx;
        aQMgr_actor_talk_finish(manager);
        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
    }
}

static void aQMgr_select_talk_reconf_or_normal(QUEST_MANAGER_ACTOR* manager, int quest_type, int quest_kind, int* new_quest) {
    int rng = RANDOM(100);
    if ((quest_type == mQst_QUEST_TYPE_CONTEST &&
         ((quest_kind == mQst_CONTEST_KIND_FISH || quest_kind == mQst_CONTEST_KIND_INSECT ||
          quest_kind == mQst_CONTEST_KIND_FTR || quest_kind == mQst_CONTEST_KIND_SHOP))) ||
        (quest_type == mQst_QUEST_TYPE_DELIVERY && quest_kind == mQst_DELIVERY_KIND_LOST_ITEM) ||
        rng < 10) {
        manager->talk_step = aQMgr_TALK_STEP_RECONF_OR_NORMAL;
    } else {
        manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
        mQst_ClearQuestInfo(&manager->target.quest_info);
        manager->target.free_data_p = NULL;
        manager->target.free_data_idx = -1;
        *new_quest = FALSE;
    }
}

static void aQMgr_select_talk_sub_to(QUEST_MANAGER_ACTOR* manager, int* regist_idx, int* sel_regist_idx, int* new_quest) {
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    aQMgr_regist_c* regist = manager->regist + *regist_idx;
    mQst_base_c* quest = regist->quest_info;
    int bx;
    int bz;

    if (quest->quest_type == mQst_QUEST_TYPE_ERRAND && ((mQst_errand_c*)quest)->errand_type == mQst_ERRAND_TYPE_FIRST_JOB) {
        manager->talk_state = aQMgr_TALK_STATE_INIT;
        manager->talk_change_type = aQMgr_TALK_KIND_FIRST_JOB;
        manager->talk_step = aQMgr_TALK_STEP_SELECT_TALK;
        *new_quest = FALSE;
        mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    } else if (aQMgr_actor_check_finish(regist, animal) == TRUE) {
        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
        if (quest->quest_type == mQst_QUEST_TYPE_CONTEST) {
            mQst_contest_c* contest = (mQst_contest_c*)quest;

            switch (quest->quest_kind) {
                case mQst_CONTEST_KIND_LETTER: {
                    int remail_status = contest->info.letter_data.remail_status;
                    if (remail_status == mQst_REMAIL_STATUS_PENDING ||
                        (remail_status == mQst_REMAIL_STATUS_FAILED && mQst_CheckOfferTalk(mQst_CONTEST_KIND_LETTER) == TRUE)) {
                        manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                        mQst_ClearQuestInfo(&manager->target.quest_info);
                        manager->target.free_data_p = NULL;
                        manager->target.free_data_idx = -1;
                        *new_quest = FALSE;
                    } else if (remail_status == mQst_REMAIL_STATUS_SENT) {
                        manager->talk_step = aQMgr_TALK_STEP_FINISH_LETTER;
                    } else {
                        manager->talk_step = aQMgr_TALK_STEP_CONTEST_HOKA_OR_NORMAL;
                        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
                    }
                } break;

                case mQst_CONTEST_KIND_SOCCER:
                case mQst_CONTEST_KIND_FLOWER:
                case mQst_CONTEST_KIND_GRASS: {
                    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR12, contest->player_id.player_name, PLAYER_NAME_LEN);
                    manager->talk_step = aQMgr_TALK_STEP_TALK_FIN_QUEST_START_NOT_HAND;
                } break;

                default: {
                    manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_START;
                } break;
            }
        } else {
            manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_START;
        }
    } else {
        switch (quest->quest_type) {
            case mQst_QUEST_TYPE_DELIVERY:
            if (quest->quest_kind < mQst_DELIVERY_KIND_LOST && quest->progress == 0) {
                manager->talk_step = aQMgr_TALK_STEP_REPORT_QBOX_OR_NORMAL;
            }
            break;
            case mQst_QUEST_TYPE_ERRAND:
                manager->talk_step = aQMgr_TALK_STEP_RENEW_ERRAND_OR_NORMAL;
                *sel_regist_idx = *regist_idx;
                *regist_idx = -1;
                break;
            case mQst_QUEST_TYPE_CONTEST: {
                mQst_contest_c* contest = (mQst_contest_c*)quest;

                if (aQMgr_actor_check_limit(manager->regist + *regist_idx) == FALSE) {
                    if (quest->progress == 0) {
                        if (mPr_CheckCmpPersonalID(&contest->player_id, &Now_Private->player_ID) == TRUE) {
                                manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                                mQst_ClearQuestInfo(&manager->target.quest_info);
                                manager->target.free_data_p = NULL;
                                manager->target.free_data_idx = -1;
                                *new_quest = FALSE;
                        } else if (mPr_NullCheckPersonalID(&contest->player_id) == FALSE) {
                            // @BUG - devs erroneously used quest_type instead of quest_kind here
#ifndef BUGFIXES
                            if (quest->quest_type == mQst_CONTEST_KIND_GRASS) {
#else
                            if (quest->quest_kind == mQst_CONTEST_KIND_GRASS) {
#endif  
                                if (mQst_GetPlayerBlockNum(&bx, &bz) == TRUE && animal->home_info.bx == bx && animal->home_info.bz == bz) {
                                    manager->talk_step = aQMgr_TALK_STEP_CONTEST_HOKA_OR_NORMAL;
                                } else {
                                    manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                                    mQst_ClearQuestInfo(&manager->target.quest_info);
                                    manager->target.free_data_p = NULL;
                                    manager->target.free_data_idx = -1;
                                    *new_quest = FALSE;
                                }
                            } else {
                            manager->talk_step = aQMgr_TALK_STEP_CONTEST_HOKA_OR_NORMAL;
                            }
                        } else {
                            manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                            mQst_ClearQuestInfo(&manager->target.quest_info);
                            manager->target.free_data_p = NULL;
                            manager->target.free_data_idx = -1;
                            *new_quest = FALSE;
                        }
                    } else if (mPr_NullCheckPersonalID(&contest->player_id) == TRUE) {
                        switch (quest->quest_kind) {
                            case mQst_CONTEST_KIND_LETTER:
                                if (mLd_PlayerManKindCheck() == NATIVE) {
                                    aQMgr_select_talk_reconf_or_normal(manager, quest->quest_type, quest->quest_kind, new_quest);
                                } else {
                                    manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                                    mQst_ClearQuestInfo(&manager->target.quest_info);
                                    manager->target.free_data_p = NULL;
                                    manager->target.free_data_idx = -1;
                                    *new_quest = FALSE;
                                }
                            break;
                            case mQst_CONTEST_KIND_FISH:
                            case mQst_CONTEST_KIND_INSECT:
                            case mQst_CONTEST_KIND_FTR:
                            case mQst_CONTEST_KIND_SHOP:
                                if (mQst_CheckOfferTalk(quest->quest_kind) == FALSE) {
                                    manager->talk_step = aQMgr_TALK_STEP_RECONF_OR_NORMAL_CTT;
                                } else {
                                    aQMgr_select_talk_reconf_or_normal(manager, quest->quest_type, quest->quest_kind, new_quest);
                                }
                            break;
                            case mQst_CONTEST_KIND_GRASS: {
                                if (mQst_GetPlayerBlockNum(&bx, &bz) == TRUE && animal->home_info.bx == bx && animal->home_info.bz == bz) {
                                    aQMgr_select_talk_reconf_or_normal(manager, quest->quest_type, quest->quest_kind, new_quest);
                                } else {
                                    manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                                    mQst_ClearQuestInfo(&manager->target.quest_info);
                                    manager->target.free_data_p = NULL;
                                    manager->target.free_data_idx = -1;
                                    *new_quest = FALSE;
                                }
                            } break;
                            default: {
                                aQMgr_select_talk_reconf_or_normal(manager, quest->quest_type, quest->quest_kind, new_quest);
                                break;
                            }
                        }
                    } else {
                        manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                        mQst_ClearQuestInfo(&manager->target.quest_info);
                        manager->target.free_data_p = NULL;
                        manager->target.free_data_idx = -1;
                        *new_quest = FALSE;
                    }
                } else {
                    manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                    mQst_ClearQuestInfo(&manager->target.quest_info);
                    manager->target.free_data_p = NULL;
                    manager->target.free_data_idx = -1;
                    *new_quest = FALSE;
                    manager->regist_idx = *regist_idx;
                    aQMgr_actor_talk_finish(manager);
                }
            } break;
        }
        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
    }

}

static void aQMgr_select_talk_sub_from_lost(QUEST_MANAGER_ACTOR* manager, int* regist_idx, int* sel_regist_idx, int* new_quest) {
    aQMgr_regist_c* regist = manager->regist + *regist_idx;
    mQst_base_c* quest = regist->quest_info;

    if (quest->progress >= 2) {
        aQMgr_select_talk_reconf_or_normal(manager, quest->quest_type, quest->quest_kind, new_quest);
        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
    } else {
        manager->talk_step = aQMgr_TALK_STEP_RECOVERY_LOST_OR_CANCEL;
        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
    }

}

static void aQMgr_select_talk_sub_from_opened_qbox(QUEST_MANAGER_ACTOR* manager, int* regist_idx, int* sel_regist_idx, int* new_quest) {
    int looks = mNpc_GetNpcLooks(*manager->client);
    aQMgr_regist_c* regist = manager->regist + *regist_idx;
    mQst_delivery_c* delivery = (mQst_delivery_c*)regist->quest_info;
    int quest_kind = mQst_DELIVERY_KIND_NORMAL;

    // @BUG - devs forgot static qualifier
#ifndef BUGFIXES
    int* opened_qbox_msg[mQst_DELIVERY_KIND_LOST] = {
        q001_aketadaro_msg,
        q002_aketadaro_msg,
        q003_aketadaro_msg,
    };
#else
    static int* opened_qbox_msg[mQst_DELIVERY_KIND_LOST] = {
        q001_aketadaro_msg,
        q002_aketadaro_msg,
        q003_aketadaro_msg,
    };
#endif

    if (delivery != NULL) {
        u8 name[ANIMAL_NAME_LEN];

        mNpc_GetNpcWorldNameAnm(name, &delivery->_34);
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR1, name, ANIMAL_NAME_LEN);
        quest_kind = delivery->base.quest_kind;
    }

    if (quest_kind < mQst_DELIVERY_KIND_NORMAL || quest_kind >= mQst_DELIVERY_KIND_LOST) {
        quest_kind = mQst_DELIVERY_KIND_NORMAL;
    }

    manager->talk_step = aQMgr_TALK_STEP_WAIT;
    manager->category_msg_no_start = opened_qbox_msg[quest_kind][looks];
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    manager->regist_idx = *regist_idx;
    aQMgr_actor_talk_finish(manager);
    *new_quest = FALSE;
}

static void aQMgr_select_talk_sub_from(QUEST_MANAGER_ACTOR* manager, int* regist_idx, int* sel_regist_idx, int* new_quest) {
    aQMgr_regist_c* regist = manager->regist + *regist_idx;
    mQst_base_c* quest = regist->quest_info;

    if (aQMgr_actor_check_limit(regist) == FALSE) {
        aQMgr_select_talk_reconf_or_normal(manager, quest->quest_type, quest->quest_kind, new_quest);
        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
    } else {
        manager->talk_step = aQMgr_TALK_STEP_GIVEUP;
        manager->msg_category = aQMgr_MSG_KIND_FAILURE_INIT;
    }
}

static void aQMgr_select_talk_sub_errand_from(QUEST_MANAGER_ACTOR* manager, int* regist_idx, int* sel_regist_idx, int* new_quest) {
    aQMgr_regist_c* regist = manager->regist + *regist_idx;

    if (aQMgr_actor_check_limit(regist) == FALSE) {
        manager->talk_step = aQMgr_TALK_STEP_ROOT_RECONF_OR_NORMAL;
        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
    } else {
        manager->talk_step = aQMgr_TALK_STEP_GIVEUP;
        manager->msg_category = aQMgr_MSG_KIND_FAILURE_INIT;
    }
}

static void aQMgr_select_talk_sub_normal(QUEST_MANAGER_ACTOR* manager, int* new_quest) {
    int rng = RANDOM(100);

    if (manager->still_reward_but_field_quest_cancel == FALSE && rng < 30) {
        manager->talk_step = aQMgr_TALK_STEP_NEW_QUEST_OR_NORMAL;
        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
    } else {
        manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
        manager->category_msg_no_start = aQMgr_actor_get_select_msg_no(manager);
        mQst_ClearQuestInfo(&manager->target.quest_info);
        manager->target.free_data_p = NULL;
        manager->target.free_data_idx = -1;
        *new_quest = FALSE;
    }
}

typedef int (*aQMgr_SELECT_TALK_CHECK_PROC)(QUEST_MANAGER_ACTOR*);
typedef void (*aQMgr_SELECT_TALK_PROC)(QUEST_MANAGER_ACTOR*, int*, int*, int*);

static int aQMgr_actor_talk_select_talk_sub(QUEST_MANAGER_ACTOR* manager, int* sel_regist_idx, int* new_quest) {
    static aQMgr_SELECT_TALK_CHECK_PROC check_proc[] = {
        aQMgr_select_talk_check_reward,
        aQMgr_select_talk_check_sick,
        aQMgr_select_talk_check_to,
        aQMgr_select_talk_check_from_lost,
        aQMgr_select_talk_check_from_opened_qbox,
        aQMgr_select_talk_check_from,
        aQMgr_select_talk_check_errand_from,
    };
    static aQMgr_SELECT_TALK_PROC select_proc[] = {
        aQMgr_select_talk_sub_reward,
        aQMgr_select_talk_sub_sick,
        aQMgr_select_talk_sub_to,
        aQMgr_select_talk_sub_from_lost,
        aQMgr_select_talk_sub_from_opened_qbox,
        aQMgr_select_talk_sub_from,
        aQMgr_select_talk_sub_errand_from,
    };
    int regist_idx = -1;
    int i;

    for (i = 0; i < ARRAY_COUNT(check_proc); i++) {
        regist_idx = (*check_proc[i])(manager);
        if (regist_idx != -1) {
            (*select_proc[i])(manager, &regist_idx, sel_regist_idx, new_quest);
            break;
        }
    }

    if (regist_idx == -1) {
        aQMgr_select_talk_sub_normal(manager, new_quest);
    }

    return regist_idx;
}

static void aQMgr_actor_talk_select_talk(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx;
    int sel_regist_idx;
    int new_quest;

    sel_regist_idx = -1;
    new_quest = TRUE;
    regist_idx = aQMgr_actor_talk_select_talk_sub(manager, &sel_regist_idx, &new_quest);
    if ((manager->check_select_msg_proc != NULL && (*manager->check_select_msg_proc)(manager) == TRUE) ||
        manager->talk_step == 0x2B || manager->talk_step == 0x31) {
        mChoice_no_b_set(mChoice_Get_base_window_p());
    }

    if (new_quest == TRUE) {
        if (regist_idx != -1) {
            manager->regist_idx = regist_idx;
            (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_TARGET);
            if (manager->talk_step != aQMgr_TALK_STEP_AFTER_REWARD) {
                manager->target.quest_inv_item_idx = (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_ITEM_IDX);
            }
        } else {
            aQMgr_actor_new_quest(manager, &regist_idx, sel_regist_idx);
        }

        if (manager->target.quest_info.quest_type != mQst_QUEST_TYPE_NONE) {
            aQMgr_talk_quest_set_work(&manager->target.work, manager->target.quest_info.quest_type,
                                      manager->target.quest_info.quest_kind);
            aQMgr_actor_set_free_str(manager, regist_idx);
        }

        manager->regist_idx = regist_idx;
    }

    aQMgr_talk_quest_select_get_choice(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_select_talk_island(QUEST_MANAGER_ACTOR* manager) {
    manager->category_msg_no_start = 0x3567 + mNpc_GetNpcLooks(*manager->client) * 3;
    mChoice_no_b_set(mChoice_Get_base_window_p());
    aQMgr_talk_quest_select_get_choice_island(manager);
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_NO_OR_ISLAND;
}

static void aQMgr_actor_talk_select_talk_2(QUEST_MANAGER_ACTOR* manager) {
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);

    manager->mail_memory = NULL;
    if (mNpc_CheckIslandAnimal(animal) == TRUE) {
        aQMgr_actor_talk_select_talk_island(manager);
    } else {
        aQMgr_actor_talk_select_talk(manager);
    }
}

static void aQMgr_actor_talk_reconf_or_normal(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx = manager->regist_idx;
    aQMgr_target_c* target = &manager->target;
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    if (manager->choice.talk_action == 0) {
        if (target->quest_info.quest_type == mQst_QUEST_TYPE_CONTEST && target->quest_info.quest_kind == mQst_CONTEST_KIND_GRASS && regist_idx != -1) {
            mQst_contest_c* contest = (mQst_contest_c*)manager->regist[regist_idx].quest_info;

            if (contest != NULL && contest->type == mQst_CONTEST_DATA_GRASS) {
                int grass_num = mQst_GetGrassNum(animal->home_info.bx, animal->home_info.bz);
                
                if (contest->info.grass_data.start_grass_num < grass_num) {
                    contest->info.grass_data.start_grass_num = grass_num;
                }
            }
        }
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_RECONF;
        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_sick_before_select(QUEST_MANAGER_ACTOR* manager) {
    mNpc_SickInfo_c* sick_info;
    int looks;
    int friendship;
    int sick_msg_type;

    sick_info = Save_GetPointer(sick_info);
    looks = mNpc_GetNpcLooks(*manager->client);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    friendship = 0;
    manager->talk_step = aQMgr_TALK_STEP_WAIT;
    
    switch (manager->choice.talk_action) {
        case mChoice_CHOICE0:
            if (manager->target.quest_inv_item_idx != -1) {
                sick_msg_type = 0xC;
                manager->talk_step = aQMgr_TALK_STEP_SICK_WAIT_BUTTON;
            } else {
                sick_msg_type = 9;
                friendship = -2;
            }
            break;
        case mChoice_CHOICE1:
            sick_msg_type = 6;
            break;
        default:
            sick_msg_type = 3;
            friendship = -1;
            break;
    }

    if (*manager->memory != NULL) {
        mNpc_AddFriendship(*manager->memory, friendship);
    }

    manager->category_msg_no_start = aQMgr_get_sick_msg(sick_info->sick_level, looks, sick_msg_type);
    manager->choice.talk_action = -1;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
}

static void aQMgr_actor_talk_sick_wait_button(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_SICK_DISAPPEAR;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_CHECK_BUTTON;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_sick_disappear(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_SICK_OPEN_MENU;
    mMsg_request_main_disappear_wait_type2(mMsg_Get_base_window_p());
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
}

static void aQMgr_actor_talk_sick_open_menu(QUEST_MANAGER_ACTOR* manager) {
    mSM_open_submenu_new2(manager->submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_QUEST, manager->target.quest_inv_item_idx,
                          NULL, mSM_IV_ITEM_NORMAL);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_SICK_HAND_MEDICINE;
}

static void aQMgr_actor_talk_sick_hand_medicine(QUEST_MANAGER_ACTOR* manager) {
    mNpc_SickInfo_c* sick_info;
    int looks;
    int msg;
    int friendship;
    int sick_msg_type;
    u8 sick_lv;

    sick_info = Save_GetPointer(sick_info);
    looks = mNpc_GetNpcLooks(*manager->client);
    sick_lv = sick_info->sick_level;
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    if (manager->handover_item != EMPTY_NO) {
        sick_msg_type = 0x12;
        manager->talk_step = aQMgr_TALK_STEP_SICK_GET_ITEM;
        mQst_SetItemNameFreeStr(manager->handover_item, mMsg_FREE_STR2);
        mNpc_PrescribeForSickAnimal(sick_info, &Now_Private->player_ID, Common_GetPointer(time.rtc_time));
        friendship = 5;
    } else {
        sick_msg_type = 0xF;
        manager->talk_step = aQMgr_TALK_STEP_WAIT;
        friendship = -10;
    }

    if (*manager->memory != NULL) {
        mNpc_AddFriendship(*manager->memory, friendship);
    }

    msg = aQMgr_get_sick_msg(sick_lv, looks, sick_msg_type);
    manager->category_msg_no_start = msg;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_ChangeMsgData(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_request_main_appear_wait_type1(mMsg_Get_base_window_p());
    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_APPEAR_WAIT;
}

static void aQMgr_actor_talk_sick_get_item(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_WAIT;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT_MSG_WAIT;
}

static void aQMgr_actor_talk_sick_after_select(QUEST_MANAGER_ACTOR* manager) {
    mNpc_SickInfo_c* sick_info = Save_GetPointer(sick_info);
    int looks = mNpc_GetNpcLooks(*manager->client);

    switch (manager->choice.talk_action) {
        case mChoice_CHOICE0:
            manager->category_msg_no_start = aQMgr_get_sick_msg(sick_info->sick_level, looks, 0x18);
            manager->choice.talk_action = -1;
            (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
            mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
            manager->talk_step = aQMgr_TALK_STEP_WAIT;
            mMsg_Set_ForceNext(mMsg_Get_base_window_p());
            break;
        default:
            mMsg_Set_ForceNext(mMsg_Get_base_window_p());
            aQMgr_talk_quest_set_cancel_msg(manager);
            break;
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_sick_reward(QUEST_MANAGER_ACTOR* manager) {
    static int q005_houbi_rare_msg[mNpc_LOOKS_NUM] = { 0x03D4, 0x03D7, 0x03DA, 0x03DD, 0x03E0, 0x03E3 };
    static int category_list[3] = { mSP_KIND_FURNITURE, mSP_KIND_CARPET, mSP_KIND_WALLPAPER };
    int regist_idx;
    int looks;
    mQst_base_c* quest;
    aQMgr_target_c* target;
    aQMgr_regist_c* regist;
    lbRTC_time_c* rtc_time;

    looks = mNpc_GetNpcLooks(*manager->client);
    rtc_time = Common_GetPointer(time.rtc_time);
    target = &manager->target;
    regist_idx = manager->regist_idx;
    regist = manager->regist + regist_idx;
    target->reward_item = mSP_GetRandomItemABC(category_list, ARRAY_COUNT(category_list));

    if (ITEM_IS_FTR(target->reward_item)) {
        target->reward_kind = aQMgr_QUEST_REWARD_FTR;
    } else if (ITEM_IS_CARPET(target->reward_item)) {
        target->reward_kind = aQMgr_QUEST_REWARD_CARPET;
    } else {
        target->reward_kind = aQMgr_QUEST_REWARD_WALLPAPER;
    }

    if (aQMgr_actor_hand_reward(target) == TRUE) {
        aQMgr_actor_set_free_str_reward(target);
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        manager->category_msg_no_start = q005_houbi_rare_msg[looks];
        quest = regist->quest_info;
        if (quest != NULL) {
            quest->progress = 0;
            quest->give_reward = FALSE;
            lbRTC_TimeCopy(&quest->time_limit, rtc_time);
            lbRTC_Add_DD(&quest->time_limit, 3);
        }

        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 3);
        }

        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
        manager->talk_step = aQMgr_TALK_STEP_SICK_REWARD_END;
        sAdo_SysTrgStart(0x12F);
    } else {
        manager->msg_category = aQMgr_MSG_KIND_REWARD_FULL_ITEM2;
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    }

    manager->regist_idx = -1;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_sick_reward_end(QUEST_MANAGER_ACTOR* manager) {
    manager->msg_category = aQMgr_MSG_KIND_COMPLETE_END;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_REWARD);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_WAIT;
    aQMgr_actor_talk_finish(manager);
}

static int aQMgr_actor_check_ftr_in_home(mActor_name_t item, int player_no) {
    mHm_flr_c* floor;
    mHm_lyr_c* layer;
    mActor_name_t* items;
    int ret = FALSE;

    if (mPr_NullCheckPersonalID(&Save_Get(private_data[player_no].player_ID)) == FALSE) {
        int house_idx = mHS_get_arrange_idx(player_no);
        int room;
        
        floor = Save_Get(homes[house_idx]).floors;
        for (room = 0; room < mHm_ROOM_NUM; room++) {
            int layer_idx;
            
            layer = &floor->layer_main;
            for (layer_idx = 0; layer_idx < 2; layer_idx++) {
                int i;
                
                items = layer->items[0];
                for (i = 0; i < UT_TOTAL_NUM; i++, items++) {
                    if (aMR_CorrespondFurniture(item, *items) == TRUE) {
                        ret = TRUE;
                        break;
                    }
                }

                if (i < UT_TOTAL_NUM) {
                    break;
                }

                layer++;
            }

            if (layer_idx < 2) {
                break;
            }

            floor++;
        }
    }

    return ret;
}

static int aQMgr_actor_check_ftr_your(mActor_name_t item) {
    int ret = FALSE;

    if (mLd_PlayerManKindCheck() == FALSE) {
        ret = aQMgr_actor_check_ftr_in_home(item, Common_Get(player_no));
    }

    return ret;
}

static int aQMgr_actor_check_ftr_hoka_R(mActor_name_t item) {
    int ret = FALSE;
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (i != Common_Get(player_no)) {
            ret = aQMgr_actor_check_ftr_in_home(item, i);
            if (ret == TRUE) {
                mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR14, Save_Get(private_data[i]).player_ID.player_name,
                        PLAYER_NAME_LEN);
                break;
            }
        }
    }

    return ret;
}

static int aQMgr_actor_check_ftr_hoka_M(mActor_name_t item) {
    PersonalID_c* personal_id;
    int ret = FALSE;
    int player_no;

    for (player_no = 0; player_no < PLAYER_NUM; player_no++) {
        if (player_no != Common_Get(player_no)) {
            personal_id = &Save_Get(private_data[player_no]).player_ID;

            if (mPr_NullCheckPersonalID(personal_id) == FALSE) {
                mActor_name_t* pockets = Save_Get(private_data[player_no]).inventory.pockets;
                int i;

                for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, pockets++) {
                    if (aMR_CorrespondFurniture(item, *pockets) == TRUE) {
                        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR14, personal_id->player_name,
                                          PLAYER_NAME_LEN);
                        ret = TRUE;
                    }
                }
            }
        }
    }

    return ret;
}

static int aQMgr_actor_check_ftr_true(mActor_name_t item) {
    return TRUE;
}

static int l_q013_irai_your[mNpc_LOOKS_NUM] = {0x0F5C, 0x0F5F, 0x0F62, 0x0F65, 0x0F68, 0x0F6B};
static int l_q013_irai_hoka_R[mNpc_LOOKS_NUM] = {0x0F6E, 0x0F71, 0x0F74, 0x0F77, 0x0F7A, 0x0F7D};
static int l_q013_irai_hoka_M[mNpc_LOOKS_NUM] = {0x0F80, 0x0F83, 0x0F86, 0x0F89, 0x0F8C, 0x0F8F};
static int l_q013_irai1[mNpc_LOOKS_NUM] = {0x0F4A, 0x0F4D, 0x0F50, 0x0F53, 0x0F56, 0x0F59};

typedef int (*aQMgr_CHECK_FTR_PROC)(mActor_name_t);

static int aQMgr_actor_get_q013_irai_msg(mActor_name_t item, int looks) {
    static int* msg_table_p[] = {
        l_q013_irai_your,
        l_q013_irai_hoka_R,
        l_q013_irai_hoka_M,
        l_q013_irai1,
    };
    static aQMgr_CHECK_FTR_PROC check_proc[] = {
        &aQMgr_actor_check_ftr_your,
        &aQMgr_actor_check_ftr_hoka_R,
        &aQMgr_actor_check_ftr_hoka_M,
        &aQMgr_actor_check_ftr_true,
    };

    int msg_no = 0x0F4A;
    int i;

    for (i = 0; i < ARRAY_COUNT(check_proc); i++) {
        if ((*check_proc[i])(item) == TRUE) {
            msg_no = msg_table_p[i][looks];
            break;
        }
    }

    return msg_no;
}

static int l_q014_irai_room[mNpc_LOOKS_NUM] = {0x2467, 0x246A, 0x246D, 0x2470, 0x2473, 0x2476};
static int l_q014_irai_style[mNpc_LOOKS_NUM] = {0x2479, 0x247C, 0x247F, 0x2482, 0x2485, 0x2488};
static int l_q014_irai_other[mNpc_LOOKS_NUM] = {0x248B, 0x248E, 0x2491, 0x2494, 0x2497, 0x249A};

static int aQMgr_actor_get_q014_irai_msg(mActor_name_t item, int looks) {
    int msg = l_q014_irai_other[looks];

    if (ITEM_IS_FTR(item)) {
        msg = l_q014_irai_room[looks];
    } else if (ITEM_IS_CLOTH(item) || ITEM_IS_UMBRELLA2(item)) {
        msg = l_q014_irai_style[looks];
    }

    return msg;
}

static void aQMgr_actor_talk_reconf_or_normal_ctt(QUEST_MANAGER_ACTOR* manager) {
    int looks;
    int msg;

    looks = mNpc_GetNpcLooks(*manager->client);
    if (manager->choice.talk_action == 0) {
        if (manager->target.quest_item != EMPTY_NO) {
            manager->msg_category = aQMgr_MSG_KIND_REQUEST_INIT;
            switch (manager->target.quest_info.quest_kind) {
                case mQst_CONTEST_KIND_FTR:
                    msg = aQMgr_actor_get_q013_irai_msg(manager->target.quest_item, looks);
                    manager->category_msg_no_start = msg;
                    manager->msg_category = aQMgr_MSG_KIND_NONE;
                    break;
                case mQst_CONTEST_KIND_SHOP:
                    msg = aQMgr_actor_get_q014_irai_msg(manager->target.quest_item, looks);
                    manager->category_msg_no_start = msg;
                    manager->msg_category = aQMgr_MSG_KIND_NONE;
                    break;
            }

            mQst_SetOfferTalk(manager->target.quest_info.quest_kind);
            mQst_SetItemNameStr(manager->target.quest_item, mMsg_ITEM_STR1);
        }

        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_root_reconf_or_normal(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        manager->category_msg_no_start = 0x03D4;
        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_no_or_normal(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 1);
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CHANGE_TALK_NORMAL);
    } else {
        mMsg_SET_FORCENEXT();
        aQMgr_talk_quest_set_cancel_msg(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_no_or_island(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 1);
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CHANGE_TALK_ISLAND);
    } else {
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        aQMgr_talk_quest_set_cancel_msg_island(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_full_item_or_normal(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        if (manager->target.set_data_p == NULL) {
            manager->category_msg_no_start = 0x0440;
        } else {
            manager->msg_category = aQMgr_MSG_KIND_FULL_ITEM;
        }

        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_renew_errand_or_normal(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_INIT;
        aQMgr_actor_set_quest_info(manager);
        (*manager->clear_regist_proc)(manager->regist, aQMgr_REGIST_NUM);
        manager->regist_idx = -1;
        aQMgr_talk_quest_start_choice(manager);
        mChoice_no_b_set(mChoice_Get_base_window_p());
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());

        if (manager->target.free_data_p->quest_type == mQst_QUEST_TYPE_ERRAND &&
            manager->target.free_data_p->progress == 0) {
            manager->talk_step = aQMgr_TALK_STEP_RENEW_ERRAND_IRAI_END_GIVE_ITEM;
        } else {
            manager->talk_step = aQMgr_TALK_STEP_RENEW_ERRAND_IRAI_END;
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_renew_errand_irai_end_give_item(QUEST_MANAGER_ACTOR* manager) {
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_renew_errand_irai_end(QUEST_MANAGER_ACTOR* manager) {
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_new_quest_or_normal(QUEST_MANAGER_ACTOR* manager) {
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    int looks = mNpc_GetNpcLooks(*manager->client);
    u8 item_name[mIN_ITEM_NAME_LEN];
    mActor_name_t item;

    if (manager->choice.talk_action == 0) {
        aQMgr_talk_quest_finish_firstjob_open_quest();
        manager->talk_step = aQMgr_TALK_STEP_OCCUR_QUEST;
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_INIT;

        if (manager->target.quest_info.quest_type == mQst_QUEST_TYPE_CONTEST) {
            switch (manager->target.quest_info.quest_kind) {
                case mQst_CONTEST_KIND_FTR:
                    manager->msg_category = aQMgr_MSG_KIND_NONE;
                    manager->category_msg_no_start = aQMgr_actor_get_q013_irai_msg(manager->target.quest_item, looks);
                    mQst_SetOfferTalk(mQst_CONTEST_KIND_FTR);
                    break;
                case mQst_CONTEST_KIND_SHOP:
                    manager->msg_category = aQMgr_MSG_KIND_NONE;
                    manager->category_msg_no_start = aQMgr_actor_get_q014_irai_msg(manager->target.quest_item, looks);
                    mQst_SetOfferTalk(mQst_CONTEST_KIND_SHOP);
                    break;
                case mQst_CONTEST_KIND_FISH:
                case mQst_CONTEST_KIND_INSECT:
                    mQst_SetOfferTalk(manager->target.quest_info.quest_kind);
                    break;
            }
        }

        if (manager->target.quest_info.quest_type == mQst_QUEST_TYPE_CONTEST ||
            (manager->target.quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY &&
             manager->target.quest_info.quest_kind == mQst_DELIVERY_KIND_LOST_ITEM)) {
            aQMgr_actor_set_quest_info(manager);
            mQst_Id2InitReserve(&animal->id);
            if (mQst_CheckRenewalReserve() == TRUE) {
                mQst_SetReverveAll();
            }

            if (manager->target.quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY &&
                manager->target.quest_info.quest_kind == mQst_DELIVERY_KIND_LOST_ITEM) {
                item = manager->target.quest_item;
                if (item != EMPTY_NO) {
                    mIN_copy_name_str(item_name, item);
                    mMsg_Set_free_str_cl_art(mMsg_Get_base_window_p(), mMsg_FREE_STR2, item_name, mIN_ITEM_NAME_LEN, 2,
                                             mIN_get_item_article(manager->target.quest_item));
                    mMsg_Set_item_str_art(mMsg_Get_base_window_p(), mMsg_ITEM_STR1, item_name, mIN_ITEM_NAME_LEN,
                                          mIN_get_item_article(manager->target.quest_item));
                }
            }
        }

        aQMgr_talk_quest_start_choice(manager);
        mChoice_no_b_set(mChoice_Get_base_window_p());
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_occur_quest(QUEST_MANAGER_ACTOR* manager) {
    int talk_action = manager->choice.talk_action;
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);

    if (talk_action == 0) {
        mQst_base_c* quest_info;

        manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
        aQMgr_actor_set_quest_info(manager);
        mQst_Id2InitReserve(&animal->id);
        if (mQst_CheckRenewalReserve() == TRUE) {
            mQst_SetReverveAll();
        }

        quest_info = manager->target.free_data_p;
        if (quest_info->quest_type != mQst_QUEST_TYPE_ERRAND || (quest_info->quest_type == mQst_QUEST_TYPE_ERRAND && quest_info->progress == 0)) {
            manager->talk_step = aQMgr_TALK_STEP_WAIT_TALK;
            manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NO_WAIT;
            if (quest_info->quest_type != mQst_QUEST_TYPE_ERRAND) {
                sAdo_SysTrgStart(0x12E);
            }
        } else {
            manager->talk_step = aQMgr_TALK_STEP_FINISH;
            manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else if (talk_action == 1) {
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_REJECT;
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);

        /* If the player rejects a quest then apply a friendship penalty */
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, -3);
        }
    } else if (talk_action == 2) {
        aQMgr_talk_quest_set_cancel_msg(manager);
    } else {
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
        aQMgr_actor_set_quest_info(manager);
        mQst_Id2InitReserve(&animal->id);
        if (mQst_CheckRenewalReserve() == TRUE) {
            mQst_SetReverveAll();
        }
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    }

    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
}

static void aQMgr_talk_quest_wait_talk(QUEST_MANAGER_ACTOR* manager) {
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_PLAYER_WAIT;
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
    aQMgr_actor_talk_finish(manager);
    manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_giveup(QUEST_MANAGER_ACTOR* manager) {
    if (manager->target.quest_inv_item_idx != -1) {
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_CHECK_BUTTON;
        manager->talk_step = aQMgr_TALK_STEP_GIVEUP_WAIT_BUTTON;
    }

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_quest_giveup_wait_button(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_GIVEUP_OPEN_MENU;
    mMsg_request_main_disappear_wait_type2(mMsg_Get_base_window_p());
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
}

static void aQMgr_talk_quest_giveup_open_menu(QUEST_MANAGER_ACTOR* manager) {
    mSM_open_submenu_new2(manager->submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_QUEST, manager->target.quest_inv_item_idx,
                          NULL, mSM_IV_ITEM_PUT_AWAY);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_GIVEUP_ITEM;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}


static void aQMgr_talk_quest_giveup_item(QUEST_MANAGER_ACTOR* manager) {
    static int shiburuna_table[mNpc_LOOKS_NUM] = { 0x0499, 0x049C, 0x049F, 0x04A2, 0x04A5, 0x04A8 };
    aQMgr_set_data_c* set_data = (aQMgr_set_data_c*)manager->target.set_data_p;
    int base_msg;
    int friendship = 0;
    int looks = mNpc_GetNpcLooks(*manager->client);

    if (manager->handover_item != EMPTY_NO) {
        manager->msg_category = aQMgr_MSG_KIND_FAILURE_END;
        manager->talk_step = aQMgr_TALK_STEP_GIVEUP_NPC_ITEM;
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_APPEAR_WAIT;

        if (set_data != NULL && *manager->memory != NULL && set_data->msg_start[aQMgr_MSG_KIND_FAILURE_END] != NULL) {
            base_msg = *set_data->msg_start[aQMgr_MSG_KIND_FAILURE_END];

            switch (base_msg) {
                case 0x2B8:
                    friendship = -5;
                    break;
                case 0x2CA:
                    friendship = -1;
                    break;
            }

            mNpc_AddFriendship(*manager->memory, friendship);
        }
    } else {
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        manager->category_msg_no_start = shiburuna_table[looks];
        manager->talk_step = aQMgr_TALK_STEP_GIVEUP;
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    }

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_ChangeMsgData(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_request_main_appear_wait_type1(mMsg_Get_base_window_p());
    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
}

static void aQMgr_talk_quest_giveup_npc_item(QUEST_MANAGER_ACTOR* manager) {
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT_MSG_WAIT;
    aQMgr_actor_talk_finish(manager);
    manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;
}

static void aQMgr_actor_talk_fin_quest_start(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        mMsg_Set_LockContinue(mMsg_Get_base_window_p());
        mMsg_request_main_disappear_wait_type2(mMsg_Get_base_window_p());

        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
        manager->talk_step = aQMgr_TALK_STEP_OPEN_MENU;
        manager->choice.talk_action = -1;
        manager->msg_category = aQMgr_MSG_KIND_COMPLETE_INIT;

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    }
}

static void aQMgr_talk_quest_talk_fin_not_hand(QUEST_MANAGER_ACTOR* manager) {
    Private_c* priv = Now_Private;
    int regist_idx = manager->regist_idx;
    aQMgr_regist_c* regist = &manager->regist[regist_idx];

    if (manager->choice.talk_action == 0) {
        if (mPr_GetPossessionItemIdx(priv, EMPTY_NO) != -1) {
            manager->msg_category = aQMgr_MSG_KIND_COMPLETE_INIT;
            manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_REWARD;
        } else {
            mQst_base_c* quest = regist->quest_info;

            if (quest != NULL) {
                if (quest->give_reward == FALSE) {
                    manager->msg_category = aQMgr_MSG_KIND_REWARD_FULL_ITEM;
                }

                mPr_CopyPersonalID(&((mQst_contest_c*)regist->quest_info)->player_id,
                                   &Now_Private->player_ID);
                quest = regist->quest_info;
                quest->give_reward = TRUE;
            }

            manager->talk_step = aQMgr_TALK_STEP_WAIT;
        }

        manager->choice.talk_action = -1;

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_talk_quest_open_menu(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    Submenu* submenu = manager->submenu;
    int item_idx = target->quest_inv_item_idx;

    if (target->quest_info.quest_type == mQst_QUEST_TYPE_CONTEST) {
        mSM_open_submenu_new2(submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_QUEST, item_idx, NULL, mSM_IV_ITEM_PUT_AWAY);
    } else {
        int mode;

        if (Now_Private != NULL && mPr_CHK_ITEM_COND(Now_Private->inventory.item_conditions, item_idx) == mPr_ITEM_COND_QBOX) {
            mode = mSM_IV_ITEM_WAIT;
        } else if (ITEM_NAME_GET_TYPE(target->quest_item) == NAME_TYPE_ITEM1 &&
            ITEM_NAME_GET_CAT(target->quest_item) == ITEM1_CAT_CLOTH) {
            mode = mSM_IV_ITEM_NORMAL;
        } else {
            mode = mSM_IV_ITEM_PUT_AWAY;
        }

        mSM_open_submenu_new2(submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_QUEST, item_idx, NULL, mode);
    }

    manager->talk_step = aQMgr_TALK_STEP_GET_ITEM;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_quest_get_item(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;

    if (manager->handover_item != EMPTY_NO) {
        manager->msg_category = aQMgr_MSG_KIND_COMPLETE_INIT;
        if (target->quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY) {
            switch (target->quest_info.quest_kind) {
                case mQst_DELIVERY_KIND_NORMAL:
                case mQst_DELIVERY_KIND_FOREIGN:
                case mQst_DELIVERY_KIND_REMOVE:
                    manager->talk_step = aQMgr_TALK_STEP_NPC_WAIT_HAND_QBOX;
                    break;
                case mQst_DELIVERY_KIND_LOST_ITEM:
                    manager->talk_step = aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT_LOST;
                    break;
                default:
                    manager->talk_step = aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT;
                    break;
            }
        } else if (target->quest_info.quest_type == mQst_QUEST_TYPE_CONTEST) {
            switch (target->quest_info.quest_kind) {
                case mQst_CONTEST_KIND_SHOP:
                case mQst_CONTEST_KIND_FTR:
                    manager->talk_step = aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT_CTT;
                    break;
                default:
                    manager->talk_step = aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT;
                    break;
            }
        } else {
            manager->talk_step = aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT;
        }

        mQst_SetItemNameFreeStr(manager->handover_item, mMsg_FREE_STR2);
        if (ITEM_NAME_GET_TYPE(target->quest_item) == NAME_TYPE_ITEM1 &&
            ITEM_NAME_GET_CAT(target->quest_item) == ITEM1_CAT_CLOTH) {
            Common_Set(npc_chg_cloth, target->quest_item);
        }
    } else {
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        if (manager->get_common_msg_proc != NULL) {
            manager->category_msg_no_start =
                (*manager->get_common_msg_proc)(manager, aQMgr_GET_COMMON_MSG_TYPE_CANCEL_ITEM);
        } else {
            manager->category_msg_no_start = 0x4AB;
        }

        manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, -1);
        }
    }

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_ChangeMsgData(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_request_main_appear_wait_type1(mMsg_Get_base_window_p());
    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_APPEAR_WAIT;
}

static void aQMgr_talk_quest_npc_get_item_wait(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_REWARD;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT_MSG_WAIT;
}

static void aQMgr_talk_quest_npc_get_item_wait_ctt(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_REWARD_CTT;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT_MSG_WAIT;
}

static void aQMgr_talk_quest_npc_wait_hand_qbox(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_NPC_WAIT_OPEN_QBOX;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT;
}

static void aQMgr_talk_quest_npc_wait_open_qbox(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_THINK_ITEM;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_OPEN_QBOX_WAIT;
}

static int aQMgr_think_cloth_level(mActor_name_t item, Animal_c* animal) {
    u8 cloth_type = mNT_get_cloth_type(item, 0);
    int level = 1;

    if (cloth_type == mNpc_GetDefAnimalClothLAttr(animal)) {
        level = 0;
    } else if (cloth_type == mNpc_GetDefAnimalClothHAttr(animal)) {
        level = 2;
    }

    return level;
}

static int aQMgr_think_npc_level_normal(AnmPersonalID_c* from_id, AnmPersonalID_c* to_id) {
    int level = 1;
    int relation = mNpc_GetRelation(from_id, to_id);

    if (relation < 2) {
        level = 0;
    } else if (relation > 2) {
        level = 2;
    }

    return level;
}

static int aQMgr_think_npc_level_love(AnmPersonalID_c* from_id, AnmPersonalID_c* to_id) {
    int level = 1;
    int relation = mNpc_GetRelation(from_id, to_id);

    if (relation < 1) {
        level = 0;
    } else if (relation > 1) {
        level = 2;
    }

    return level;
}

static int aQMgr_actor_get_item_level(QUEST_MANAGER_ACTOR* manager) {
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    int level = 0;

    switch (manager->target.quest_info.quest_kind) {
        case mQst_DELIVERY_KIND_NORMAL:
            level = aQMgr_think_cloth_level(manager->target.quest_item, animal);
            break;
        case mQst_DELIVERY_KIND_REMOVE:
            if (manager->target.from_id != NULL) {
                level = aQMgr_think_npc_level_love(&animal->id, manager->target.from_id);
            }
            break;
        case mQst_DELIVERY_KIND_FOREIGN:
            if (manager->target.from_id != NULL) {
                level = aQMgr_think_npc_level_normal(&animal->id, manager->target.from_id);
            }
            break;
    }

    return level;
}

static void aQMgr_actor_set_reward_qbox(QUEST_MANAGER_ACTOR* manager) {
    static int category_table[3] = { mSP_KIND_FURNITURE, mSP_KIND_CLOTH, mSP_KIND_PAPER };
    static int category_table_love[3] = { mSP_KIND_FURNITURE, mSP_KIND_FURNITURE, mSP_KIND_CLOTH };
    static int priority_table_love[3] = { mSP_LISTTYPE_RARE, mSP_LISTTYPE_UNCOMMON, mSP_LISTTYPE_COMMON };
    static int reward_kind[3] = { aQMgr_QUEST_REWARD_FTR, aQMgr_QUEST_REWARD_CLOTH, aQMgr_QUEST_REWARD_STATIONERY };
    static int reward_kind_love[3] = { aQMgr_QUEST_REWARD_FTR, aQMgr_QUEST_REWARD_FTR, aQMgr_QUEST_REWARD_CLOTH };

    aQMgr_target_c* target = &manager->target;
    u32 quest_kind = target->quest_info.quest_kind;
    int list_type = mSP_LISTTYPE_ABC;
    int category;
    int item_level = aQMgr_actor_get_item_level(manager);

    if (quest_kind == mQst_DELIVERY_KIND_REMOVE) {
        list_type = priority_table_love[item_level];
        category = category_table_love[item_level];
        target->reward_kind = reward_kind_love[item_level];
    } else {
        category = category_table[item_level];
        target->reward_kind = reward_kind[item_level];
    }

    mSP_SelectRandomItem_New(NULL, &target->reward_item, 1, NULL, 0, category, list_type, FALSE);
}

static int l_q001_think_cloth_suki[mNpc_LOOKS_NUM] = {0x0025, 0x0028, 0x002B, 0x002E, 0x0031, 0x0034};
static int l_q001_think_cloth_futsu[mNpc_LOOKS_NUM] = {0x0037, 0x003A, 0x003D, 0x0040, 0x0043, 0x0046};
static int l_q001_think_cloth_kirai[mNpc_LOOKS_NUM] = {0x0049, 0x004C, 0x004F, 0x0052, 0x0055, 0x0058};
static int* l_q001_think_msg[3] = { l_q001_think_cloth_suki, l_q001_think_cloth_futsu, l_q001_think_cloth_kirai };

static int l_q002_think_item_suki[mNpc_LOOKS_NUM] = {0x0316, 0x0319, 0x031C, 0x031F, 0x0322, 0x0325};
static int l_q002_think_item_futsu[mNpc_LOOKS_NUM] = {0x0328, 0x032B, 0x032E, 0x0331, 0x0334, 0x0337};
static int l_q002_think_item_kirai[mNpc_LOOKS_NUM] = {0x033A, 0x033D, 0x0340, 0x0343, 0x0346, 0x0349};
static int* l_q002_think_msg[3] = { l_q002_think_item_suki, l_q002_think_item_futsu, l_q002_think_item_kirai };

static int l_q003_think_item_suki[mNpc_LOOKS_NUM] = {0x1146, 0x1149, 0x114C, 0x114F, 0x1152, 0x1155};
static int l_q003_think_item_futsu[mNpc_LOOKS_NUM] = {0x1158, 0x115B, 0x115E, 0x1161, 0x1164, 0x1167};
static int l_q003_think_item_kirai[mNpc_LOOKS_NUM] = {0x116A, 0x116D, 0x1170, 0x1173, 0x1176, 0x1179};
static int* l_q003_think_msg[3] = { l_q003_think_item_suki, l_q003_think_item_futsu, l_q003_think_item_kirai };

static void aQMgr_actor_talk_think_item(QUEST_MANAGER_ACTOR* manager) {
    static int** msg_table[3] = { l_q001_think_msg, l_q002_think_msg, l_q003_think_msg };
    static int relation_add_after[3] = { 48, 20, -48 };
    static int love_add_table[5] = { 2, 28, 12, 12, 12 };

    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    int looks = mNpc_GetNpcLooks(*manager->client);
    aQMgr_target_c* target = &manager->target;
    int item_level;
    u32 kind = target->quest_info.quest_kind;
    int regist_idx = manager->regist_idx;
    int cloth_type = mNT_get_cloth_type(target->quest_item, 0);
    u8 cloth_type_str[mString_DEFAULT_STR_SIZE];
    aQMgr_regist_c* regist;
    mQst_base_c* quest;
    int relation_point;

    relation_point = 2;
    if (kind >= mQst_DELIVERY_KIND_LOST) {
        kind = mQst_DELIVERY_KIND_NORMAL;
    }

    if (animal != NULL) {
        relation_point = mNpc_GetRelation(target->from_id, &animal->id);
    }

    if (relation_point < 0 || relation_point >= mNpc_RELATION_NUM) {
        relation_point = mNpc_RELATION_NORMAL;
    }

    switch (kind) {
        case mQst_DELIVERY_KIND_NORMAL:
            item_level = aQMgr_actor_get_item_level(manager);
            if (animal != NULL) {
                mNpc_AddRelationPoint_id(target->from_id, &animal->id, relation_add_after[item_level]);
            }
            break;
        case mQst_DELIVERY_KIND_FOREIGN:
            if (animal != NULL) {
                int amount = mNpc_GetNextRelationPoint(target->from_id, &animal->id);
                mNpc_AddRelationPoint_id(target->from_id, &animal->id, amount);
            }
            item_level = aQMgr_actor_get_item_level(manager);
            break;
        case mQst_DELIVERY_KIND_REMOVE:
            if (animal != NULL) {
                mNpc_AddRelationPoint_id(target->from_id, &animal->id, love_add_table[relation_point]);
            }
            item_level = aQMgr_actor_get_item_level(manager);
            break;
        default:
            item_level = aQMgr_actor_get_item_level(manager);
            break;
    }

    if (kind == mQst_DELIVERY_KIND_NORMAL) {
        mString_Load_StringFromRom(cloth_type_str, sizeof(cloth_type_str), cloth_type + 0x748);
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR13, cloth_type_str, sizeof(cloth_type_str));
    }

    manager->msg_category = aQMgr_MSG_KIND_NONE;
    manager->category_msg_no_start = msg_table[kind][item_level][looks];
    regist = &manager->regist[regist_idx];
    aQMgr_actor_set_reward_qbox(manager);
    aQMgr_actor_hand_reward(target);
    aQMgr_actor_set_free_str_reward(target);
    if (*manager->memory != NULL) {
        mNpc_AddFriendship(*manager->memory, 3);
    }

    quest = regist->quest_info;
    if (quest != NULL) {
        mQst_delivery_c* delivery = (mQst_delivery_c*)quest;

        quest->progress = 0;
        lbRTC_Add_DD(&quest->time_limit, 3);
        manager->regist_idx = -1;
        mNpc_CopyAnimalPersonalID(&delivery->_34, &delivery->recipient);
        mNpc_CopyAnimalPersonalID(&delivery->recipient, &delivery->sender);
        delivery->_56 = item_level;
    }

    sAdo_SysTrgStart(0x12F);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
    manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_THANKS_QBOX;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_msg_lock_qbox(QUEST_MANAGER_ACTOR* manager) {
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_THANKS_QBOX;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_talk_quest_npc_get_item_wait_lost(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_REWARD_LOST;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT_MSG_WAIT;
}

static int q008_houbi_haniwa[mNpc_LOOKS_NUM] = {0x0E69, 0x0E6C, 0x0E6F, 0x0E72, 0x0E75, 0x0E78};
static int q008_houbi_kagu[mNpc_LOOKS_NUM] = {0x0E57, 0x0E5A, 0x0E5D, 0x0E60, 0x0E63, 0x0E66};
static int q008_houbi_okane[mNpc_LOOKS_NUM] = {0x0E7B, 0x0E7E, 0x0E81, 0x0E84, 0x0E87, 0x0E8A};
static int q004_reward_kagu[mNpc_LOOKS_NUM] = {0x0282, 0x0285, 0x0288, 0x028B, 0x028E, 0x0291};
static int q004_reward_jyutan[mNpc_LOOKS_NUM] = {0x0294, 0x0297, 0x029A, 0x029D, 0x02A0, 0x02A3};
static int q004_reward_kabegami[mNpc_LOOKS_NUM] = {0x0E9F, 0x0EA2, 0x0EA5, 0x0EA8, 0x0EAB, 0x0EAE};

static void aQMgr_actor_talk_fin_quest_reward_lost(QUEST_MANAGER_ACTOR* manager) {
    int looks = mNpc_GetNpcLooks(*manager->client);
    aQMgr_target_c* target = &manager->target;
    int regist_idx = manager->regist_idx;
    aQMgr_regist_c* regist = &manager->regist[regist_idx];

    aQMgr_actor_set_reward(manager);
    if (aQMgr_actor_hand_reward(target) == TRUE) {
        aQMgr_actor_set_free_str_reward(target);
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        switch (target->reward_kind) {
            case aQMgr_QUEST_REWARD_HANIWA:
                manager->category_msg_no_start = q008_houbi_haniwa[looks];
                break;
            case aQMgr_QUEST_REWARD_MONEY:
                manager->category_msg_no_start = q008_houbi_okane[looks];
                break;
            default:
                manager->category_msg_no_start = q008_houbi_kagu[looks];
                break;
        }

        manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_THANKS;
        sAdo_SysTrgStart(0x12F);
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 3);
        }
    } else {
        manager->msg_category = aQMgr_MSG_KIND_REWARD_FULL_ITEM;
        regist->quest_info->give_reward = TRUE;
        manager->regist_idx = -1;
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_recovery_lost_or_cancel(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx = manager->regist_idx;

    if (manager->choice.talk_action == 0) {
        aQMgr_regist_c* regist = &manager->regist[regist_idx];
        mQst_base_c* quest = regist->quest_info;

        if (quest != NULL) {
            u8 name[ANIMAL_NAME_LEN];
            AnmPersonalID_c* pid = mNpc_GetOtherAnimalPersonalID(&((mQst_delivery_c*)quest)->sender, 1);

            if (pid != NULL) {
                mNpc_GetNpcWorldNameAnm(name, pid);
                mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR12, name, ANIMAL_NAME_LEN);
            }
        }

        manager->msg_category = aQMgr_MSG_KIND_FAILURE_INIT;
        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
        aQMgr_actor_talk_finish(manager);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_fin_quest_reward(QUEST_MANAGER_ACTOR* manager) {
    static int** reward_table_p[] = {
        l_soccer_reward_msg,
        l_flower_reward_msg,
        l_fish_reward_msg,
        l_insect_reward_msg,
        NULL,
        NULL,
        NULL,
        l_grass_reward_msg,
        NULL,
    };
    static int* reward_msg_p[] = {
        q004_reward_kagu,
        NULL,
        NULL,
        q004_reward_jyutan,
        q004_reward_kabegami,
        NULL,
        NULL,
        NULL,
        NULL,
    };

    int looks = mNpc_GetNpcLooks(*manager->client);
    int regist_idx = manager->regist_idx;
    mQst_base_c* quest;
    aQMgr_regist_c* regist = &manager->regist[regist_idx];
    aQMgr_target_c* target = &manager->target;

    aQMgr_actor_set_reward(manager);

    if (aQMgr_actor_hand_reward(target) == TRUE) {
        aQMgr_actor_set_free_str_reward(target);
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        quest = regist->quest_info;
        if (quest != NULL) {
            if (quest->quest_type == mQst_QUEST_TYPE_CONTEST) {
                u32 quest_kind = quest->quest_kind;

                if (quest_kind >= mQst_CONTEST_KIND_NUM) {
                    quest->quest_kind = mQst_CONTEST_KIND_LETTER;
                }

                if (reward_table_p[quest_kind][target->reward_kind] != NULL) {
                    manager->category_msg_no_start = reward_table_p[quest_kind][target->reward_kind][looks];
                }

                if (quest->progress != 0) {
                    quest->progress--;
                    lbRTC_Add_DD(&quest->time_limit, mQst_GetContestAddDay(quest->quest_kind));
                }
            } else if (quest->quest_type == mQst_QUEST_TYPE_DELIVERY &&
                       reward_msg_p[target->reward_kind] != NULL) {
                manager->category_msg_no_start = reward_msg_p[target->reward_kind][looks];
            }
        }

        manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_THANKS;
        quest = regist->quest_info;
        quest->give_reward = FALSE;
        sAdo_SysTrgStart(0x12F);
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 3);
        }
    } else {
        manager->msg_category = aQMgr_MSG_KIND_REWARD_FULL_ITEM;
        quest = regist->quest_info;
        quest->give_reward = TRUE;
        manager->regist_idx = -1;
    }

    quest = regist->quest_info;
    if (quest != NULL && quest->quest_type == mQst_QUEST_TYPE_CONTEST) {
        mPr_CopyPersonalID(&((mQst_contest_c*)quest)->player_id, &Now_Private->player_ID);
        manager->regist_idx = -1;
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_set_reward_ftr(QUEST_MANAGER_ACTOR* manager) {
    manager->target.reward_item = aEGH_not_collect_get();
    manager->target.reward_kind = aQMgr_QUEST_REWARD_FTR;
}

static int aQMgr_actor_set_reward_shop(QUEST_MANAGER_ACTOR* manager) {
    int ret = TRUE;
    int price = mSP_ItemNo2ItemPrice(manager->target.quest_item);
    // pay is random value between [50%, 150%) of price, rounded to the nearest 10
    u32 pay = ((int)(u32)((fqrand() + 0.5f) * price) / 10) * 10;

    if (pay > price) {
        ret = FALSE;
    }

    manager->target.pay = pay;
    manager->target.reward_item = ITM_MONEY_1000;
    manager->target.reward_kind = aQMgr_QUEST_REWARD_MONEY;
    return ret;
}

static int l_q013_houbi[mNpc_LOOKS_NUM] = {0x2443, 0x2446, 0x2449, 0x244C, 0x244F, 0x2452};
static int l_q014_houbi_high[mNpc_LOOKS_NUM] = {0x24C1, 0x24C4, 0x24C7, 0x24CA, 0x24CD, 0x24D0};
static int l_q014_houbi_low[mNpc_LOOKS_NUM] = {0x24D3, 0x24D6, 0x24D9, 0x24DC, 0x24DF, 0x24E2};
static int* l_q014_houbi_msg[2] = { l_q014_houbi_high, l_q014_houbi_low };

static void aQMgr_actor_talk_fin_quest_reward_ctt(QUEST_MANAGER_ACTOR* manager) {
    int looks = mNpc_GetNpcLooks(*manager->client);
    aQMgr_target_c* target = &manager->target;
    int regist_idx = manager->regist_idx;
    aQMgr_regist_c* regist = &manager->regist[regist_idx];
    int reward_level = TRUE;

    if (target->quest_info.quest_kind == mQst_CONTEST_KIND_FTR) {
        aQMgr_actor_set_reward_ftr(manager);
    } else {
        reward_level = aQMgr_actor_set_reward_shop(manager);
    }

    aQMgr_actor_hand_reward(target);
    aQMgr_actor_set_free_str_reward(target);
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    if (target->quest_info.quest_kind == mQst_CONTEST_KIND_FTR) {
        manager->category_msg_no_start = l_q013_houbi[looks];
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 3);
        }

        manager->regist_idx = -1;
        if (regist->quest_info->progress != 0) {
            regist->quest_info->progress--;
            lbRTC_Add_DD(&regist->quest_info->time_limit, mQst_GetContestAddDay(target->quest_info.quest_kind));
            mPr_CopyPersonalID(&((mQst_contest_c*)regist->quest_info)->player_id, &Now_Private->player_ID);
        }
    } else {
        manager->category_msg_no_start = l_q014_houbi_msg[reward_level][looks];
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 10);
        }
    }

    manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_THANKS;
    sAdo_SysTrgStart(0x12F);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static int l_quest_suki_end[mNpc_LOOKS_NUM] = {0x006D, 0x0070, 0x0073, 0x0076, 0x0079, 0x007C};
static int l_quest_futsu_end[mNpc_LOOKS_NUM] = {0x007F, 0x0082, 0x0085, 0x0088, 0x008B, 0x008E};
static int l_quest_kirai_end[mNpc_LOOKS_NUM] = {0x0091, 0x0094, 0x0097, 0x009A, 0x009D, 0x00A0};

static void aQMgr_actor_talk_fin_quest_thanks_qbox(QUEST_MANAGER_ACTOR* manager) {
    static int* msg_table_p[3] = { l_quest_suki_end, l_quest_futsu_end, l_quest_kirai_end };
    int looks = mNpc_GetNpcLooks(*manager->client);
    int item_level = aQMgr_actor_get_item_level(manager);

    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    manager->category_msg_no_start = msg_table_p[item_level][looks];
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_REWARD);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_fin_quest_thanks(QUEST_MANAGER_ACTOR* manager) {
    manager->msg_category = aQMgr_MSG_KIND_COMPLETE_END;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_REWARD);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_after_reward_select(QUEST_MANAGER_ACTOR* manager) {
    switch (manager->choice.talk_action) {
        case mChoice_CHOICE0:
            manager->msg_category = aQMgr_MSG_KIND_AFTER_REWARD;
            manager->talk_step = aQMgr_TALK_STEP_AFTER_REWARD;
            (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
            mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
            mMsg_Set_ForceNext(mMsg_Get_base_window_p());
            break;
        default:
            aQMgr_talk_quest_change_normal_or_hint(manager);
            manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
            break;
    }

    manager->choice.talk_action = -1;
}

static void aQMgr_actor_talk_after_reward(QUEST_MANAGER_ACTOR* manager) {
    mQst_base_c* quest;
    aQMgr_regist_c* regist;
    int looks = mNpc_GetNpcLooks(*manager->client);
    int regist_idx = manager->regist_idx;
    u32 kind;

    aQMgr_actor_set_reward(manager);

    if (aQMgr_actor_hand_reward(&manager->target) == TRUE) {
        aQMgr_actor_set_free_str_reward(&manager->target);
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        regist = &manager->regist[regist_idx];
        quest = regist->quest_info;

        if (quest != NULL && quest->quest_type == mQst_QUEST_TYPE_CONTEST) {
            // missing static qualifier
            int** reward_msg_table[mQst_CONTEST_KIND_NUM] = {
                l_soccer_reward_msg,
                l_flower_reward_msg,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                l_grass_reward_msg,
                NULL,
            };

            // @BUG: devs forgot to update 'kind' variable when out of bounds
            kind = quest->quest_kind;
            if (kind >= mQst_CONTEST_KIND_NUM) {
                quest->quest_kind = mQst_CONTEST_KIND_LETTER;
#ifdef BUGFIXES
                kind = mQst_CONTEST_KIND_LETTER;
#endif
            }

            if (reward_msg_table[kind][manager->target.reward_kind] != NULL) {
                manager->category_msg_no_start =
                    reward_msg_table[kind][manager->target.reward_kind][looks];
            }

            if (quest->progress != 0) {
                quest->progress--;
                lbRTC_Add_DD(&quest->time_limit, mQst_GetContestAddDay(quest->quest_kind));
            }

            manager->regist_idx = -1;
        }

        regist->quest_info->give_reward = FALSE;

        manager->talk_step = aQMgr_TALK_STEP_AFTER_REWARD_THANKS;
        sAdo_SysTrgStart(0x12F);
    } else {
        manager->msg_category = aQMgr_MSG_KIND_REWARD_FULL_ITEM2;
    }

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_after_reward_thanks(QUEST_MANAGER_ACTOR* manager) {
    manager->msg_category = aQMgr_MSG_KIND_AFTER_REWARD_THANKS;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_REWARD);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_quest_contest_hoka_or_normal(QUEST_MANAGER_ACTOR* manager) {
    static int post_mite_table[mNpc_LOOKS_NUM] = {0x1B05, 0x1B08, 0x1B0B, 0x1B0E, 0x1B11, 0x1B14};
    aQMgr_regist_c* regist;
    int looks = mNpc_GetNpcLooks(*manager->client);

    regist = &manager->regist[manager->regist_idx];
    if (manager->choice.talk_action == 0) {
        aQMgr_talk_quest_finish_firstjob_open_quest();
        manager->target.free_data_p = NULL;
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR12,
                          ((mQst_contest_c*)regist->quest_info)->player_id.player_name, PLAYER_NAME_LEN);
        if (regist->quest_info->quest_type == mQst_QUEST_TYPE_CONTEST &&
            regist->quest_info->quest_kind == mQst_CONTEST_KIND_LETTER) {
            if (mPr_CheckCmpPersonalID(&((mQst_contest_c*)regist->quest_info)->player_id,
                                       &Now_Private->player_ID) == FALSE) {
                manager->category_msg_no_start = aQMgr_talk_quest_get_contest_hoka_msg_no(
                    (mQst_contest_c*)regist->quest_info, aQMgr_GET_CLIENT_ANIMAL(manager), looks);
            } else {
                manager->category_msg_no_start = post_mite_table[looks];
            }

            mQst_SetOfferTalk(4);
        } else {
            manager->category_msg_no_start = aQMgr_talk_quest_get_contest_hoka_msg_no(
                (mQst_contest_c*)regist->quest_info, aQMgr_GET_CLIENT_ANIMAL(manager), looks);
            manager->target.free_data_p = NULL;
            aQMgr_actor_talk_finish(manager);
        }

        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static int l_q001_houkoku[6] = {0x039E, 0x03A7, 0x03B0, 0x03B9, 0x03C2, 0x03CB};
static int l_q002_houkoku[6] = {0x041C, 0x0425, 0x042E, 0x0437, 0x0440, 0x0449};
static int l_q003_houkoku[6] = {0x0452, 0x045B, 0x0464, 0x046D, 0x0476, 0x047F};

static void aQMgr_talk_quest_report_qbox_or_normal(QUEST_MANAGER_ACTOR* manager) {
    static int* msg_talble_p[3] = {l_q001_houkoku, l_q002_houkoku, l_q003_houkoku};
    static u8 str[mIN_ITEM_NAME_LEN];
    int looks = mNpc_GetNpcLooks(*manager->client);
    int regist_idx;
    aQMgr_regist_c* regist;
    int kind = manager->target.quest_info.quest_kind;

    if (kind >= mQst_DELIVERY_KIND_LOST) {
        kind = mQst_DELIVERY_KIND_NORMAL;
    }

    regist_idx = manager->regist_idx;
    regist = &manager->regist[regist_idx];
    if (manager->choice.talk_action == 0) {
        aQMgr_talk_quest_finish_firstjob_open_quest();
        manager->target.free_data_p = NULL;
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        manager->category_msg_no_start = msg_talble_p[kind][looks];
        if (regist->quest_info != NULL) {
            mQst_delivery_c* delivery = (mQst_delivery_c*)regist->quest_info;
            u8 name[ANIMAL_NAME_LEN];

            mNpc_GetNpcWorldNameAnm(name, &delivery->_34);
            mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR1, name, ANIMAL_NAME_LEN);
            if (delivery->item != EMPTY_NO) {
                mIN_copy_name_str(str, delivery->item);
                mMsg_Set_item_str_art(mMsg_Get_base_window_p(), mMsg_ITEM_STR1, str, mIN_ITEM_NAME_LEN,
                                      mIN_get_item_article(delivery->item));
            }
        }

        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT_CHOICE;
        manager->talk_step = aQMgr_TALK_STEP_REACTION_QBOX;
        manager->choice.choice_num = 0;
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    }
}

static void aQMgr_talk_quest_reaction_qbox(QUEST_MANAGER_ACTOR* manager) {
    AnmPersonalID_c* anm_id = &aQMgr_GET_CLIENT_ANIMAL(manager)->id;
    int regist_idx = manager->regist_idx;
    int amount = -6;

    if (manager->choice.talk_action != -1 && regist_idx != -1) {
        aQMgr_regist_c* regist = &manager->regist[regist_idx];
        if (regist->quest_info != NULL &&
            manager->choice.talk_action == ((mQst_delivery_c*)regist->quest_info)->_56) {
            amount = 3;
        }
    }

    mNpc_AddFriendshipPlayer_id(&Now_Private->player_ID, anm_id, amount);
    manager->target.free_data_p = NULL;
    aQMgr_actor_talk_finish(manager);
    manager->choice.talk_action = -1;
    manager->talk_step = aQMgr_TALK_STEP_WAIT;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_talk_quest_change_wait(QUEST_MANAGER_ACTOR* manager) {
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_finish_letter(QUEST_MANAGER_ACTOR* manager) {
    static int okuttayo_table[mNpc_LOOKS_NUM] = {0x1B17, 0x1B1A, 0x1B1D, 0x1B20, 0x1B23, 0x1B26};
    static int okuttayo_hokanohito_table[mNpc_LOOKS_NUM] = {0x1B29, 0x1B2C, 0x1B2F, 0x1B32, 0x1B35, 0x1B38};
    int looks = mNpc_GetNpcLooks(*manager->client);
    
    if (manager->choice.talk_action == 0) {
        aQMgr_regist_c* regist = &manager->regist[manager->regist_idx];
        mQst_contest_c* contest = (mQst_contest_c*)regist->quest_info;
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR12, contest->player_id.player_name, PLAYER_NAME_LEN);

        if (mPr_CheckCmpPersonalID(&contest->player_id, &Now_Private->player_ID) == TRUE) {
            manager->category_msg_no_start = okuttayo_table[looks];
        } else {
            manager->category_msg_no_start = okuttayo_hokanohito_table[looks];
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
        manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;
        manager->target.free_data_p = NULL;
        aQMgr_actor_talk_finish(manager);
    } else {
        aQMgr_talk_quest_set_cancel_msg(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
}

typedef void (*aQMgr_QUEST_TALK_PROC)(QUEST_MANAGER_ACTOR*);

extern void aQMgr_actor_move_talk_init(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_QUEST_TALK_PROC talk_proc[] = {
        aQMgr_actor_talk_select_talk_2,
        aQMgr_actor_talk_reconf_or_normal,
        aQMgr_actor_talk_reconf_or_normal_ctt,
        aQMgr_actor_talk_root_reconf_or_normal,
        aQMgr_actor_talk_no_or_normal,
        aQMgr_actor_talk_full_item_or_normal,
        aQMgr_actor_talk_renew_errand_or_normal,
        aQMgr_actor_talk_new_quest_or_normal,
        aQMgr_actor_talk_finish,
        aQMgr_actor_talk_occur_quest,
        aQMgr_actor_talk_giveup,
        aQMgr_talk_quest_giveup_wait_button,
        aQMgr_talk_quest_giveup_open_menu,
        aQMgr_talk_quest_giveup_item,
        aQMgr_talk_quest_giveup_npc_item,
        aQMgr_actor_talk_fin_quest_start,
        aQMgr_talk_quest_talk_fin_not_hand,
        aQMgr_actor_talk_fin_quest_reward,
        aQMgr_actor_talk_fin_quest_thanks,
        aQMgr_actor_talk_after_reward,
        aQMgr_actor_talk_after_reward_thanks,
        aQMgr_actor_talk_after_reward_select,
        aQMgr_talk_quest_wait_talk,
        aQMgr_talk_quest_open_menu,
        aQMgr_talk_quest_get_item,
        aQMgr_talk_quest_npc_get_item_wait,
        aQMgr_talk_quest_npc_wait_hand_qbox,
        aQMgr_talk_quest_npc_wait_open_qbox,
        aQMgr_actor_talk_think_item,
        aQMgr_actor_talk_msg_lock_qbox,
        aQMgr_actor_talk_fin_quest_thanks_qbox,
        aQMgr_talk_quest_npc_get_item_wait_lost,
        aQMgr_actor_talk_fin_quest_reward_lost,
        aQMgr_actor_talk_recovery_lost_or_cancel,
        aQMgr_talk_quest_report_qbox_or_normal,
        aQMgr_talk_quest_reaction_qbox,
        aQMgr_talk_quest_npc_get_item_wait_ctt,
        aQMgr_actor_talk_fin_quest_reward_ctt,
        aQMgr_talk_quest_change_wait,
        aQMgr_actor_talk_renew_errand_irai_end,
        aQMgr_actor_talk_renew_errand_irai_end_give_item,
        aQMgr_talk_quest_contest_hoka_or_normal,
        aQMgr_actor_talk_finish_letter,
        aQMgr_actor_talk_sick_before_select,
        aQMgr_actor_talk_sick_wait_button,
        aQMgr_actor_talk_sick_disappear,
        aQMgr_actor_talk_sick_open_menu,
        aQMgr_actor_talk_sick_hand_medicine,
        aQMgr_actor_talk_sick_get_item,
        aQMgr_actor_talk_sick_after_select,
        aQMgr_actor_talk_sick_reward,
        aQMgr_actor_talk_sick_reward_end,
        (aQMgr_QUEST_TALK_PROC)none_proc1,
        aQMgr_actor_talk_no_or_island,
        aQMgr_actor_talk_finish,
    };

    int step = manager->talk_step;
    int choice = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());

    if (manager->choice.choice_num > 0) {
        mChoice_Clear_ChoseNum(mChoice_Get_base_window_p());
    }

    manager->choice.talk_action = choice;
    (*talk_proc[step])(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_CHOICE_STR);

    if (manager->talk_change_type >= aQMgr_TALK_KIND_NUM) {
        manager->talk_state = aQMgr_TALK_STATE_SUB;
    }
}
