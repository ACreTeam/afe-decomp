#include "m_quest.h"

#include "libultra/libultra.h"
#include "m_name_table.h"
#include "m_npc.h"
#include "m_private.h"
#include "m_item_name.h"
#include "m_msg.h"
#include "m_shop.h"
#include "m_handbill.h"
#include "m_house.h"
#include "m_event.h"
#include "m_common_data.h"
#include "m_player_lib.h"

typedef struct grab_s {
    mActor_name_t item;
    int pocket_idx;
    int type;
    mQst_delivery_c delivery;
} mQst_grab_c;

static lbRTC_day_t l_delivery_limit[] = { 2, 2, 2, 4, 1 };

static lbRTC_day_t l_errand_limit[mQst_ERRAND_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static lbRTC_day_t l_contest_limit[mQst_CONTEST_KIND_NUM] = {
    1,  // mQst_CONTEST_KIND_SOCCER
    3,  // mQst_CONTEST_KIND_FLOWER
    3,  // mQst_CONTEST_KIND_FISH
    3,  // mQst_CONTEST_KIND_INSECT
    2,  // mQst_CONTEST_KIND_LETTER
    3,  // mQst_CONTEST_KIND_FTR
    1,  // mQst_CONTEST_KIND_SHOP
    1,  // mQst_CONTEST_KIND_GRASS
    10, // mQst_CONTEST_KIND_SICK
};

static lbRTC_day_t l_contest_fin_limit[mQst_CONTEST_KIND_NUM] = {
    3, // mQst_CONTEST_KIND_SOCCER
    3, // mQst_CONTEST_KIND_FLOWER
    3, // mQst_CONTEST_KIND_FISH
    3, // mQst_CONTEST_KIND_INSECT
    2, // mQst_CONTEST_KIND_LETTER
    3, // mQst_CONTEST_KIND_FTR
    0, // mQst_CONTEST_KIND_SHOP
    3, // mQst_CONTEST_KIND_GRASS
    3, // mQst_CONTEST_KIND_SICK
};

static lbRTC_day_t* l_limit_table[mQst_QUEST_TYPE_NUM] = { l_delivery_limit, l_errand_limit, l_contest_limit };

static int l_limit_table_max[mQst_QUEST_TYPE_NUM] = {
    mQst_DELIVERY_KIND_NUM, // mQst_QUEST_TYPE_DELIVERY
    mQst_ERRAND_NUM,        // mQst_QUEST_TYPE_ERRAND
    mQst_CONTEST_KIND_NUM,  // mQst_QUEST_TYPE_CONTEST
};

extern void mQst_ClearQuestInfo(mQst_base_c* quest) {
    bzero(quest, sizeof(mQst_base_c));
    quest->quest_type = mQst_QUEST_TYPE_NONE;
}

extern void mQst_ClearDelivery(mQst_delivery_c* delivery, int num) {
    int i;

    for (i = 0; i < num; i++) {
        bzero(delivery, sizeof(mQst_delivery_c));
        mQst_ClearQuestInfo(&delivery->base);
        mNpc_ClearAnimalPersonalID(&delivery->recipient);
        mNpc_ClearAnimalPersonalID(&delivery->sender);
        mNpc_ClearAnimalPersonalID(&delivery->_34);
        mLd_ClearLandName(delivery->_48);
        mLd_ClearLandName(delivery->_4E);
        delivery->_56 = 1;
        delivery->item = EMPTY_NO;

        delivery++;
    }
}

extern void mQst_ClearErrand(mQst_errand_c* errand, int num) {
    int i;

    for (i = 0; i < num; i++) {
        bzero(errand, sizeof(mQst_errand_c));
        mQst_ClearQuestInfo(&errand->base);
        mNpc_ClearAnimalPersonalID(&errand->recipient);
        mNpc_ClearAnimalPersonalID(&errand->sender);

        errand->item = EMPTY_NO;
        errand->pockets_idx = -1;
        errand->errand_type = mQst_ERRAND_TYPE_NONE;

        bzero(&errand->info, sizeof(mQst_errand_info_u));

        errand++;
    }
}

extern void mQst_ClearContest(mQst_contest_c* contest) {
    bzero(contest, sizeof(mQst_contest_c));
    mQst_ClearQuestInfo(&contest->base);
    contest->requested_item = EMPTY_NO;
    mPr_ClearPersonalID(&contest->player_id);
    contest->type = mQst_QUEST_TYPE_ALL_NUM;
    bzero(&contest->info, sizeof(mQst_contest_info_u));
}

extern void mQst_ClearNotSaveQuest(mQst_not_saved_c* not_saved) {
    bzero(not_saved, sizeof(mQst_not_saved_c));
}

extern void mQst_CopyQuestInfo(mQst_base_c* dst, mQst_base_c* src) {
    dst->quest_type = src->quest_type;
    dst->quest_kind = src->quest_kind;
    dst->time_limit_enabled = src->time_limit_enabled;
    dst->progress = src->progress;
    dst->give_reward = src->give_reward;

    lbRTC_TimeCopy(&dst->time_limit, &src->time_limit);
}

extern void mQst_CopyDelivery(mQst_delivery_c* dst, mQst_delivery_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(mQst_delivery_c));
}

extern void mQst_CopyErrand(mQst_errand_c* dst, mQst_errand_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(mQst_errand_c));
}

extern int mQst_CheckFreeQuest(mQst_base_c* quest) {
    int res = FALSE;
    if (quest != NULL && quest->quest_type == mQst_QUEST_TYPE_NONE) {
        res = TRUE;
    }

    return res;
}

extern int mQst_CheckLimitOver(mQst_base_c* quest) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    lbRTC_time_c temp;
    int res = FALSE;

    if (quest->time_limit_enabled == TRUE) {
        if (lbRTC_IsOverTime(&quest->time_limit, rtc_time) == lbRTC_OVER) {
            res = TRUE;
        } else if (quest->quest_type < mQst_QUEST_TYPE_NONE) {
            if (lbRTC_GetIntervalDays(&quest->time_limit, rtc_time) >= mQst_MAX_TIME_LIMIT_DAYS) {
                res = TRUE;
            } else {
                int type = quest->quest_type;
                int kind = quest->quest_kind;

                if ((u32)quest->quest_kind < l_limit_table_max[type]) {
                    int days = l_limit_table[type][quest->quest_kind];

                    if (type == mQst_QUEST_TYPE_CONTEST) {
                        if (quest->progress == 0) {
                            u8* limit = l_contest_fin_limit;
                            if (kind == mQst_CONTEST_KIND_SICK) {
                                days = limit[kind];
                            } else {
                                days += limit[kind];
                            }
                        } else if (kind == mQst_CONTEST_KIND_LETTER) {
                            if (quest->progress == 1) {
                                days += l_contest_fin_limit[kind];
                            }
                        }
                    } else if (type == mQst_QUEST_TYPE_DELIVERY) {
                        switch (kind) {
                            case mQst_DELIVERY_KIND_NORMAL:
                            case mQst_DELIVERY_KIND_FOREIGN:
                            case mQst_DELIVERY_KIND_REMOVE:
                                if (quest->progress == 0) {
                                    days += 3;
                                } else if (quest->progress == 1) {
                                    days += 7;
                                }
                                break;
                            case mQst_DELIVERY_KIND_LOST_ITEM:
                                if (quest->progress != 0) {
                                    days += 3;
                                }
                                break;
                        }
                    }

                    lbRTC_TimeCopy(&temp, &quest->time_limit);
                    lbRTC_Sub_DD(&temp, days);

                    if (lbRTC_IsOverTime(rtc_time, &temp) == lbRTC_OVER &&
                        lbRTC_IsEqualTime(rtc_time, &temp, lbRTC_CHECK_ALL) == FALSE) {
                        res = TRUE;
                    }
                }
            }
        }
    }

    return res;
}

extern int mQst_GetContestAddDay(u32 kind) {
    int add_days = 0;

    if (kind < mQst_CONTEST_KIND_NUM) {
        add_days = l_contest_fin_limit[kind];
    }

    return add_days;
}

extern int mQst_GetOccuredDeliveryIdx(int delivery_kind) {
    int idx = -1;
    int i;
    mQst_delivery_c* delivery = Now_Private->deliveries;

    for (i = 0; i < mPr_DELIVERY_QUEST_NUM; i++) {
        if (mQst_CheckFreeQuest(&delivery->base) == FALSE && delivery->base.quest_type == mQst_QUEST_TYPE_DELIVERY &&
            (u32)delivery->base.quest_kind == delivery_kind) {
            idx = i;
            break;
        }

        delivery++;
    }

    return idx;
}

static int mQst_GetDeliveryIdxbyItemIdx(int idx) {
    int d_idx = -1;

    if (idx >= 0 && idx < mPr_POCKETS_SLOT_COUNT && mQst_CheckFreeQuest(&Now_Private->deliveries[idx].base) == FALSE) {
        d_idx = idx;
    }

    return d_idx;
}

static int mQst_GetErrandIdxbyItemIdx(int idx) {
    int d_idx = -1;
    int i;
    mQst_errand_c* errand;
    mActor_name_t item;

    if (idx >= 0 && idx < mPr_POCKETS_SLOT_COUNT) {
        Private_c* priv = Now_Private;

        if (mPr_CHK_ITEM_COND(priv->inventory.item_conditions, idx) == mPr_ITEM_COND_QUEST) {
            errand = priv->errands;
            item = priv->inventory.pockets[idx];

            for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
                if (mQst_CheckFreeQuest(&errand->base) == FALSE && errand->pockets_idx == idx && errand->item == item) {
                    d_idx = i;
                    break;
                }

                errand++;
            }
        }
    }

    return d_idx;
}

extern int mQst_ClearQuestbyPossessionIdx(int idx) {
    int res = FALSE;

    if (idx >= 0 && idx < mPr_POCKETS_SLOT_COUNT) {
        Private_c* priv = Now_Private;

        if (mPr_CHK_ITEM_COND(priv->inventory.item_conditions, idx) == mPr_ITEM_COND_LOST_ITEM) {
            mQst_ClearDelivery(&priv->lost_item_quest, 1);
        } else if (mQst_GetDeliveryIdxbyItemIdx(idx) != -1) {
            mQst_ClearDelivery(priv->deliveries + idx, 1);
            res = TRUE;
        } else {
            int errand_idx = mQst_GetErrandIdxbyItemIdx(idx);

            if (errand_idx != -1) {
                mQst_ClearErrand(priv->errands + errand_idx, 1);
                res = TRUE;
            }
        }
    }

    return res;
}

extern int mQst_CheckLimitbyPossessionIdx(int idx) {
    int res = FALSE;

    if (idx >= 0 && idx < mPr_POCKETS_SLOT_COUNT) {
        int i;
        mQst_delivery_c* delivery = Now_Private->deliveries + idx;
        mQst_errand_c* errand = Now_Private->errands;
        mQst_delivery_c* lost_item_quest = &Now_Private->lost_item_quest;
        mActor_name_t item = Now_Private->inventory.pockets[idx];
        int item_cond = Now_Private->inventory.item_conditions[idx];

        if (item != EMPTY_NO) {
            if ((item_cond & 0xF) == mPr_ITEM_COND_LOST_ITEM) {
                if (mQst_CheckFreeQuest(&lost_item_quest->base) == FALSE && lost_item_quest->base.progress == 0 &&
                    mQst_CheckLimitOver(&lost_item_quest->base) == TRUE) {
                    res = TRUE;
                }
            } else {
                if (mQst_CheckFreeQuest(&delivery->base) == FALSE) {
                    switch (delivery->base.quest_kind) {
                        case mQst_DELIVERY_KIND_NORMAL:
                        case mQst_DELIVERY_KIND_FOREIGN:
                        case mQst_DELIVERY_KIND_REMOVE:
                            if (delivery->base.progress == 2 && mQst_CheckLimitOver(&delivery->base) == TRUE) {
                                res = TRUE;
                            }
                            break;
                        case mQst_DELIVERY_KIND_LOST_ITEM:
                            if (delivery->base.progress == 0 && mQst_CheckLimitOver(&delivery->base) == TRUE) {
                                res = TRUE;
                            }
                            break;
                        default:
                            if (mQst_CheckLimitOver(&delivery->base) == TRUE) {
                                res = TRUE;
                            }
                            break;
                    }
                }

                if (res == FALSE) {
                    for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
                        if (mQst_CheckFreeQuest(&errand->base) == FALSE && errand->pockets_idx == idx &&
                            item == errand->item && mQst_CheckLimitOver(&errand->base) == TRUE) {
                            res = TRUE;
                            break;
                        }

                        errand++;
                    }
                }
            }
        }
    }

    return res;
}

static mQst_grab_c l_mqst_grab;

static void mQst_ClearGrabItemInfo_common(mQst_grab_c* grab) {
    grab->item = RSV_NO;
    grab->pocket_idx = -1;
    grab->type = mQst_QUEST_TYPE_NONE;
    mQst_ClearDelivery(&grab->delivery, 1);
}

extern void mQst_ClearGrabItemInfo() {
    mQst_ClearGrabItemInfo_common(&l_mqst_grab);
}

static void mQst_SetDeliveryFreePos(mQst_delivery_c* src, mQst_delivery_c* dst, int count) {
    int i;

    if (mQst_CheckFreeQuest(&src->base) == FALSE && src->base.quest_kind != mQst_DELIVERY_KIND_LOST_ITEM) {
        for (i = 0; i < count; i++) {
            if (mQst_CheckFreeQuest(&dst->base) == TRUE) {
                mQst_CopyDelivery(dst, src);
                break;
            }

            dst++;
        }
    }
}

extern void mQst_CheckGrabItem(mActor_name_t item, int pocket_idx) {
    mQst_delivery_c* src_delivery;
    mQst_delivery_c* delivery = Now_Private->deliveries;
    mQst_errand_c* errand = Now_Private->errands;
    u8* item_cond = Now_Private->inventory.item_conditions;
    mQst_grab_c* grab = &l_mqst_grab;
    int i;

    if (pocket_idx >= 0 && pocket_idx < mPr_POCKETS_SLOT_COUNT) {
        mQst_SetDeliveryFreePos(&grab->delivery, delivery, mPr_DELIVERY_QUEST_NUM);
        mQst_ClearGrabItemInfo_common(grab);
        src_delivery = delivery + pocket_idx;

        if (mQst_CheckFreeQuest(&src_delivery->base) == FALSE &&
            (delivery[0].base.quest_type != mQst_QUEST_TYPE_DELIVERY ||
             delivery[0].base.quest_kind >= mQst_DELIVERY_KIND_LOST || delivery[0].base.progress > 1)) {
            grab->item = item;
            grab->pocket_idx = pocket_idx;
            grab->type = mQst_QUEST_TYPE_DELIVERY;
        }

        mQst_CopyDelivery(&grab->delivery, src_delivery);
        mQst_ClearDelivery(src_delivery, 1);

        if ((u32)grab->type == mQst_QUEST_TYPE_NONE &&
            mPr_CHK_ITEM_COND(item_cond, pocket_idx) == mPr_ITEM_COND_QUEST) {

            for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
                if (mQst_CheckFreeQuest(&errand->base) == FALSE && errand->pockets_idx == pocket_idx &&
                    errand->item == item) {
                    grab->item = item;
                    grab->pocket_idx = i;
                    grab->type = mQst_QUEST_TYPE_ERRAND;

                    break;
                }

                errand++;
            }
        }

        if ((u32)grab->type == mQst_QUEST_TYPE_NONE && item != EMPTY_NO) {
            grab->item = item;
        }
    }
}

extern void mQst_CheckPutItem(mActor_name_t item, int pocket_idx) {
    Private_c* priv = Now_Private;
    mQst_delivery_c t_delivery;
    mQst_delivery_c* deliveries = priv->deliveries;
    mQst_errand_c* errands = priv->errands;
    mQst_grab_c* grab = &l_mqst_grab;
    u32 grab_type;
    mActor_name_t slot_item;
    int grab_idx = grab->pocket_idx;

    if (pocket_idx >= 0 && pocket_idx < mPr_POCKETS_SLOT_COUNT) {
        slot_item = priv->inventory.pockets[pocket_idx];

        if (grab->item != RSV_NO && item == grab->item) {
            grab_type = grab->type;

            mQst_CopyDelivery(&t_delivery, &grab->delivery);
            mQst_ClearGrabItemInfo_common(grab);
            mQst_CheckGrabItem(slot_item, pocket_idx);
            mQst_CopyDelivery(deliveries + pocket_idx, &t_delivery);

            if (grab_type == mQst_QUEST_TYPE_ERRAND && grab_idx != -1) {
                errands[grab_idx].pockets_idx = pocket_idx;
            }
        } else {
            mQst_CheckGrabItem(slot_item, pocket_idx);
        }
    }
}

extern void mQst_PutItem_menu_end(void) {
    mQst_grab_c* grab = &l_mqst_grab;
    mQst_delivery_c* delivery = Now_Private->deliveries;
    int i;

    if (mQst_CheckFreeQuest(&grab->delivery.base) == FALSE) {
        for (i = 0; i < mPr_DELIVERY_QUEST_NUM; i++) {
            if (mQst_CheckFreeQuest(&delivery->base) == TRUE) {
                mQst_CopyDelivery(delivery, &grab->delivery);
                mQst_ClearGrabItemInfo_common(grab);
                break;
            }

            // @BUG - devs forgot to increment the delivery pointer
#ifdef BUGFIXES
            delivery++;
#endif
        }
    }
}

extern int mQst_CheckNpcExistbyItemIdx(int idx, int sender_or_receipient) {
    int res = FALSE;

    if (idx >= 0 && idx < mPr_POCKETS_SLOT_COUNT) {
        Private_c* priv = Now_Private;
        if (mPr_CHK_ITEM_COND(priv->inventory.item_conditions, idx) == mPr_ITEM_COND_LOST_ITEM) {
            if (sender_or_receipient == mQst_CHECK_NPC_RECEIPIENT) {
                if (mNpc_SearchAnimalPersonalID(&priv->lost_item_quest.recipient) != -1) {
                    res = TRUE;
                }
            } else {
                if (mNpc_SearchAnimalPersonalID(&priv->lost_item_quest.sender) != -1) {
                    res = TRUE;
                }
            }
        } else {
            int delivery_idx = mQst_GetDeliveryIdxbyItemIdx(idx);

            if (delivery_idx != -1) {
                mQst_delivery_c* delivery = priv->deliveries + delivery_idx;

                if ((delivery->base.quest_kind < mQst_DELIVERY_KIND_LOST && delivery->base.progress == 2) ||
                    delivery->base.quest_kind >= mQst_DELIVERY_KIND_LOST) {
                    if (sender_or_receipient == mQst_CHECK_NPC_RECEIPIENT) {
                        if (mNpc_SearchAnimalPersonalID(&delivery->recipient) != -1) {
                            res = TRUE;
                        }
                    } else {
                        if (mNpc_SearchAnimalPersonalID(&delivery->sender) != -1) {
                            res = TRUE;
                        }
                    }
                }
            } else {
                int errand_idx = mQst_GetErrandIdxbyItemIdx(idx);

                if (errand_idx != -1) {
                    mQst_errand_c* errand = Now_Private->errands + errand_idx;
                    if (sender_or_receipient == mQst_CHECK_NPC_RECEIPIENT) {
                        if (mNpc_SearchAnimalPersonalID(&errand->recipient) != -1) {
                            res = TRUE;
                        }
                    } else {
                        if (mNpc_SearchAnimalPersonalID(&errand->sender) != -1) {
                            res = TRUE;
                        }
                    }
                }
            }
        }
    }

    return res;
}

extern int mQst_GetToFromName(u8* to_name, u8* from_name, int idx) {
    mQst_delivery_c* delivery;
    mQst_errand_c* errand;
    int delivery_idx;
    int errand_idx;
    int res = FALSE;

    if (idx >= 0 && idx < mPr_POCKETS_SLOT_COUNT) {
        if (mQst_GetLostOwnerName(to_name, Now_Private->inventory.pockets[idx]) == TRUE) {
            mPr_CopyPlayerName(from_name, to_name);
            res = TRUE;
        } else {
            delivery_idx = mQst_GetDeliveryIdxbyItemIdx(idx);

            if (delivery_idx != -1) {
                delivery = Now_Private->deliveries + delivery_idx;

                mNpc_GetNpcWorldNameAnm(to_name, &delivery->recipient);
                mNpc_GetNpcWorldNameAnm(from_name, &delivery->sender);

                res = TRUE;
            } else {
                errand_idx = mQst_GetErrandIdxbyItemIdx(idx);

                if (errand_idx != -1) {
                    errand = Now_Private->errands + errand_idx;

                    mNpc_GetNpcWorldNameAnm(to_name, &errand->recipient);

                    if (mEv_CheckFirstJob() == TRUE && errand->errand_type == mQst_ERRAND_TYPE_FIRST_JOB) {
                        mNpc_GetActorWorldName(from_name, SP_NPC_SHOP_MASTER);
                    } else {
                        mNpc_GetNpcWorldNameAnm(from_name, &errand->sender);
                    }

                    res = TRUE;
                }
            }
        }
    }

    return res;
}

extern int mQst_GetOccuredContestIdx(int kind) {
    Animal_c* animal = Save_Get(animals);
    int res = -1;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
            animal->contest_quest.base.quest_type == mQst_QUEST_TYPE_CONTEST &&
            (u32)animal->contest_quest.base.quest_kind == kind) {
            res = i;
            break;
        }

        animal++;
    }

    return res;
}

extern int mQst_GetFreeContestIdx(Animal_c* animal, int count) {
    int res = -1;
    int i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
            mQst_CheckFreeQuest(&animal->contest_quest.base) == TRUE) {
            res = i;
            break;
        }

        animal++;
    }

    return res;
}

extern int mQst_GetFlowerSeedNum(int block_x, int block_z) {
    return mFI_GetItemNumOnBlockInField(block_x, block_z, FLOWER_LEAVES_PANSIES0, FLOWER_TULIP2);
}

extern int mQst_GetFlowerNum(int block_x, int block_z) {
    return mFI_GetItemNumOnBlockInField(block_x, block_z, FLOWER_PANSIES0, FLOWER_TULIP2);
}

extern int mQst_GetGrassNum(int block_x, int block_z) {
    return mFI_GetItemNumOnBlockInField(block_x, block_z, GRASS_A, GRASS_C);
}

extern int mQst_GetNullNoNum(int block_x, int block_z) {
    return mFI_GetItemNumOnBlockInField(block_x, block_z, EMPTY_NO, EMPTY_NO);
}

extern void mQst_SetItemNameStr(mActor_name_t item, int string_no) {
    u8 name[mIN_ITEM_NAME_LEN];

    if (item != EMPTY_NO) {
        int article_no;

        mIN_copy_name_str(name, item);
        article_no = mIN_get_item_article(item);
        mMsg_Set_item_str_art(mMsg_Get_base_window_p(), string_no, name, mIN_ITEM_NAME_LEN, article_no);
    }
}

extern void mQst_SetItemNameFreeStr(mActor_name_t item, int string_no) {
    u8 name[mIN_ITEM_NAME_LEN];

    if (item != EMPTY_NO) {
        int article_no;

        mIN_copy_name_str(name, item);
        article_no = mIN_get_item_article(item);
        mMsg_Set_free_str_art(mMsg_Get_base_window_p(), string_no, name, mIN_ITEM_NAME_LEN, article_no);
    }
}

static mActor_name_t mQst_GetPresent(int rank) {
    int category = -1;
    int list = -1;
    mActor_name_t item = 0;

    switch (rank) {
        case mQst_LETTER_RANK_3:
        case mQst_LETTER_RANK_7:
            category = mSP_KIND_CLOTH;
            list = mSP_LISTTYPE_ABC;
            break;

        case mQst_LETTER_RANK_4:
            category = mSP_KIND_FURNITURE;
            list = mSP_LISTTYPE_ABC;
            break;

        case mQst_LETTER_RANK_5: {
            list = mSP_LISTTYPE_ABC;

            if ((mQst_GetRandom(4) & 1) == 0) {
                category = mSP_KIND_CARPET;
            } else {
                category = mSP_KIND_WALLPAPER;
            }

            break;
        }

        case mQst_LETTER_RANK_6:
            item = Save_Get(fruit);
            break;

        case mQst_LETTER_RANK_8:
            category = mSP_KIND_CLOTH;
            list = mSP_LISTTYPE_RARE;
            break;

        case mQst_LETTER_RANK_9:
            item = mFI_GetOtherFruit();
            break;

        case mQst_LETTER_RANK_10:
            category = mSP_KIND_FURNITURE;
            list = mSP_LISTTYPE_RARE;
            break;

        case mQst_LETTER_RANK_11: {
            list = mSP_LISTTYPE_RARE;

            if ((mQst_GetRandom(4) & 1) == 0) {
                category = mSP_KIND_CARPET;
            } else {
                category = mSP_KIND_WALLPAPER;
            }

            break;
        }
    }

    if (category != -1 && list != -1) {
        mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, category, list, FALSE);
    }

    return item;
}

static void mQst_GetRemailData(Mail_c* letter, PersonalID_c* recipient_id, AnmPersonalID_c* sender_id, int rank,
                               mActor_name_t present) {
    int handbill_no;
    int looks = sender_id->looks;
    u8 name_buf[mIN_ITEM_NAME_LEN];
    u8 header[MAIL_HEADER2_LEN];
    u8 footer[MAIL_FOOTER2_LEN];
    int header_back_pos;

    mMl_clear_mail(letter);
    handbill_no = 0x75 + (rank * mNpc_LOOKS_NUM + looks);
    mNpc_GetNpcWorldNameAnm(name_buf, sender_id);
    mHandbill_Set_free_str(mHandbill_FREE_STR6, name_buf, ANIMAL_NAME_LEN);

    if (present != EMPTY_NO) {
        mIN_copy_name_str(name_buf, present);
        mHandbill_Set_free_str(mHandbill_FREE_STR0, name_buf, mIN_ITEM_NAME_LEN);
    }

    mHandbill_Load_HandbillFromRom2(header, MAIL_HEADER2_LEN, &header_back_pos, footer, MAIL_FOOTER2_LEN,
                                    letter->content.text.split.body, handbill_no);
    mem_copy(letter->content.text.split.header, header, MAIL_HEADER_LEN);
    mem_copy(letter->content.text.split.footer, footer, MAIL_FOOTER_LEN);
    letter->content.header_back_start = header_back_pos;
    letter->content.font = mMl_FONT_RECV;
    letter->content.mail_type = 0;

    mPr_CopyPersonalID(&letter->header.recipient.personalID, recipient_id);
    letter->header.recipient.type = mMl_NAME_TYPE_PLAYER;

    mMl_set_mail_name_npcinfo(&letter->header.sender, sender_id);

    letter->content.paper_type = (ITM_PAPER22 - ITM_PAPER_START); // festive paper
    letter->present = present;
}

extern int mQst_SendRemail(mQst_contest_c* contest, AnmPersonalID_c* sender_id) {
    PersonalID_c* recipient_id = &contest->player_id;
    mHm_hs_c* house;
    int res = FALSE;

    if (mPr_NullCheckPersonalID(recipient_id) == FALSE) {
        int priv_idx = mPr_GetPrivateIdx(recipient_id);

        if (priv_idx != -1) {
            house = Save_GetPointer(homes[mHS_get_arrange_idx(priv_idx)]);

            if (mPr_CheckCmpPersonalID(recipient_id, &house->ownerID) == TRUE) {
                int free_mail_idx = mMl_chk_mail_free_space(house->mailbox, HOME_MAILBOX_SIZE);

                if (free_mail_idx != -1) {
                    Mail_c letter;

                    mQst_GetRemailData(&letter, recipient_id, sender_id, contest->info.letter_data.score,
                                       contest->info.letter_data.present);
                    mMl_copy_mail(&house->mailbox[free_mail_idx], &letter);

                    res = TRUE;
                }
            }
        }
    }

    return res;
}

extern void mQst_SendRemailAll(void) {
    Animal_c* animal = Save_Get(animals);
    mQst_contest_c* contest;
    lbRTC_time_c limit;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            contest = &animal->contest_quest;

            if (mQst_CheckFreeQuest(&contest->base) == FALSE && contest->base.quest_type == mQst_QUEST_TYPE_CONTEST &&
                contest->base.quest_kind == mQst_CONTEST_KIND_LETTER && contest->base.progress == 1 &&
                mPr_NullCheckPersonalID(&contest->player_id) == FALSE && contest->type == mQst_CONTEST_DATA_LETTER &&
                contest->info.letter_data.remail_status != mQst_REMAIL_STATUS_SENT) {
                lbRTC_TimeCopy(&limit, &contest->base.time_limit);
                lbRTC_Sub_DD(&limit, 2);

                if (lbRTC_IsEqualTime(&limit, Common_GetPointer(time.rtc_time), lbRTC_CHECK_DATE) == FALSE) {
                    if (mQst_SendRemail(contest, &animal->id) == TRUE) {
                        lbRTC_Add_DD(&contest->base.time_limit, 2);
                        contest->info.letter_data.remail_status = mQst_REMAIL_STATUS_SENT;
                    } else {
                        contest->info.letter_data.remail_status = mQst_REMAIL_STATUS_FAILED;
                    }
                }
            }
        }

        animal++;
    }
}

static u8 mQst_GetMailRank(u8* body, mActor_name_t present) {
    u8 rank = mQst_LETTER_RANK_MIN;
    int length = 0;
    u8 score_bonus = mNpc_CheckNormalMail_length(&length, body);

    if (length >= mQst_LETTER_GOOD_LENGTH) {
        rank = mQst_LETTER_RANK_2;
    } else if (length >= mQst_LETTER_OKAY_LENGTH) {
        rank = mQst_LETTER_RANK_1;
    }

    if (score_bonus >= mNpc_LETTER_RANK_OK) {
        rank += mQst_LETTER_SCORE_BONUS;
    }

    if (present != EMPTY_NO) {
        rank += mQst_LETTER_PRESENT_BONUS;
    }

    return rank;
}

extern void mQst_SetReceiveLetter(mQst_contest_c* contest, PersonalID_c* sender_id, u8* body, mActor_name_t present) {
    if (contest->base.quest_type == mQst_QUEST_TYPE_CONTEST && contest->base.quest_kind == mQst_CONTEST_KIND_LETTER &&
        mPr_NullCheckPersonalID(&contest->player_id) == TRUE && contest->base.progress == 2) {
        mPr_CopyPersonalID(&contest->player_id, sender_id);
        contest->base.progress = 1;
        contest->info.letter_data.score = mQst_GetMailRank(body, present);
        contest->info.letter_data.present = mQst_GetPresent(contest->info.letter_data.score);
        contest->info.letter_data.remail_status = mQst_REMAIL_STATUS_PENDING;
    }
}

extern int mQst_GetPlayerBlockNum(int* bx, int* bz) {
    ACTOR* playerx = GET_PLAYER_ACTOR_NOW_ACTOR();
    int ret = FALSE;

    if (playerx != NULL) {
        ret = mFI_Wpos2BlockNum(bx, bz, playerx->world.position);
    }

    return ret;
}

static u16 l_mqst_offer = 0;

extern void mQst_ClearOfferTalk(void) {
    l_mqst_offer = 0;
}

extern void mQst_SetOfferTalk(int idx) {
    if (idx >= 0 && idx < mQst_CONTEST_KIND_NUM) {
        l_mqst_offer |= 1 << idx;
    }
}

extern int mQst_CheckOfferTalk(int idx) {
    int ret = FALSE;

    if (idx >= 0 && idx < mQst_CONTEST_KIND_NUM && ((l_mqst_offer >> idx) & 1) == 1) {
        ret = TRUE;
    }

    return ret;
}

extern mQst_errand_c* mQst_GetFirstJobData() {
    mQst_errand_c* errand = Now_Private->errands;
    mQst_errand_c* errand_p = errand;
    int i;
    int j;
    mQst_errand_c* selected_errand = NULL;

    /* Try to find any current 'first job' errand quest */
    for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
        if (errand_p->base.quest_type == mQst_QUEST_TYPE_ERRAND &&
            errand_p->errand_type == mQst_ERRAND_TYPE_FIRST_JOB) {
            selected_errand = errand_p;
            break;
        }

        errand_p++;
    }

    if (selected_errand == NULL) {
        /* Try to find a free quest slot */

        for (j = 0; j < mPr_ERRAND_QUEST_NUM; j++) {
            if (mQst_CheckFreeQuest(&errand->base) == TRUE) {
                selected_errand = errand;
                break;
            }

            errand++;
        }
    }

    return selected_errand; /* This can be NULL */
}

static int mQst_CheckFirstJobQuest(mQst_errand_c* errand) {
    if (errand != NULL && errand->base.quest_type == mQst_QUEST_TYPE_ERRAND &&
        errand->errand_type == mQst_ERRAND_TYPE_FIRST_JOB) {
        return TRUE;
    }

    return FALSE;
}

extern int mQst_CheckFirstJobQuestbyItemIdx(int idx) {
    int res = FALSE;

    if (idx >= 0 && idx < mPr_POCKETS_SLOT_COUNT) {
        int errand_idx = mQst_GetErrandIdxbyItemIdx(idx);

        if (errand_idx != -1) {
            res = mQst_CheckFirstJobQuest(Now_Private->errands + errand_idx);
        }
    }

    return res;
}

extern int mQst_CheckFirstJobFin(mQst_errand_c* errand) {
    int res = FALSE;

    if (errand->base.progress == 0) {
        res = TRUE;
    }

    return res;
}

extern int mQst_CheckRemoveTarget(mQst_errand_c* errand) {
    int res = FALSE;

    if (errand != NULL &&
        mNpc_SearchAnimalPersonalID_com(&errand->recipient, Save_Get(animals), ANIMAL_NUM_MAX) == -1) {
        res = TRUE;
    }

    return res;
}

extern void mQst_SetFirstJobStart(mQst_errand_c* errand) {
    int i;

    if (errand != NULL) {
        mQst_ClearErrand(errand, 1);
        errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
        errand->base.quest_kind = mQst_ERRAND_FIRSTJOB_START;
        errand->base.progress = 0;
        errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;

        for (i = 0; i < mQst_ERRAND_FIRST_JOB_ANIMAL_NUM; i++) {
            mNpc_ClearAnimalPersonalID(errand->info.first_job.used_ids + i);
        }
    }
}

extern void mQst_SetFirstJobChangeCloth(mQst_errand_c* errand, mActor_name_t item) {
    if (errand == NULL) {
        return;
    }

    errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
    errand->base.quest_kind = mQst_ERRAND_FIRSTJOB_CHANGE_CLOTH;
    errand->base.time_limit_enabled = FALSE;
    errand->base.progress = 2;
    errand->base.give_reward = FALSE;

    errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;
    errand->item = item;
}

extern void mQst_SetFirstJobSeed(mQst_errand_c* errand) {
    if (errand == NULL) {
        return;
    }

    errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
    errand->base.quest_kind = mQst_ERRAND_FIRSTJOB_PLANT_FLOWER;
    errand->base.time_limit_enabled = FALSE;
    errand->base.progress = 2;
    errand->base.give_reward = FALSE;

    errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;
}

extern void mQst_SetFirstJobHello(mQst_errand_c* errand) {
    if (errand == NULL) {
        return;
    }

    errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
    errand->base.quest_kind = mQst_ERRAND_FIRSTJOB_INTRODUCTIONS;
    errand->base.time_limit_enabled = FALSE;
    errand->base.progress = 2;
    errand->base.give_reward = FALSE;

    errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;
}

extern void mQst_SetFirstJobFurniture(mQst_errand_c* errand, AnmPersonalID_c* pid, mActor_name_t item, int slot) {
    if (errand != NULL) {
        errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
        errand->base.quest_kind = mQst_ERRAND_FIRSTJOB_DELIVER_FTR;
        errand->base.time_limit_enabled = FALSE;
        errand->base.progress = 2;
        errand->base.give_reward = FALSE;

        mNpc_CopyAnimalPersonalID(&errand->recipient, pid);
        mNpc_CopyAnimalPersonalID(&errand->info.first_job.used_ids[0], pid);
        errand->info.first_job.used_num = 1;
        errand->pockets_idx = slot;
        errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;
        errand->item = item;
    }
}

static void mQst_SetFirstJobLetter_common(mQst_errand_c* errand, AnmPersonalID_c* pid, u8 kind) {
    if (errand != NULL) {
        errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
        errand->base.quest_kind = (u32)kind;
        errand->base.time_limit_enabled = FALSE;
        errand->base.progress = 2;
        errand->base.give_reward = FALSE;

        mNpc_CopyAnimalPersonalID(&errand->recipient, pid);
        errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;
        mNpc_CopyAnimalPersonalID(&errand->info.first_job.used_ids[1], pid);
        errand->info.first_job.used_num = 2;
    }
}

extern void mQst_SetFirstJobLetter(mQst_errand_c* errand, AnmPersonalID_c* pid) {
    mQst_SetFirstJobLetter_common(errand, pid, mQst_ERRAND_FIRSTJOB_SEND_LETTER);
}

extern void mQst_SetFirstJobLetter2(mQst_errand_c* errand, AnmPersonalID_c* pid) {
    mQst_SetFirstJobLetter_common(errand, pid, mQst_ERRAND_FIRSTJOB_SEND_LETTER2);
}

extern void mQst_SetFirstJobOpenQuest(mQst_errand_c* errand) {
    if (errand != NULL) {
        errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
        errand->base.quest_kind = mQst_ERRAND_FIRSTJOB_OPEN;
        errand->base.time_limit_enabled = FALSE;
        errand->base.progress = 2;
        errand->base.give_reward = FALSE;

        mNpc_ClearAnimalPersonalID(&errand->recipient);
        errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;
        mEv_EventON(mEv_SAVED_FJOPENQUEST_PLR0 + Common_Get(player_no));
    }
}

extern void mQst_SetFirstJobCarpet(mQst_errand_c* errand, AnmPersonalID_c* pid, mActor_name_t item, int slot) {
    if (errand != NULL) {
        errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
        errand->base.quest_kind = mQst_ERRAND_FIRSTJOB_DELIVER_CARPET;
        errand->base.time_limit_enabled = FALSE;
        errand->base.progress = 2;
        errand->base.give_reward = FALSE;

        mNpc_CopyAnimalPersonalID(&errand->recipient, pid);
        errand->pockets_idx = slot;
        errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;
        errand->item = item;
    }
}

static void mQst_SetFirstJobAxe_common(mQst_errand_c* errand, AnmPersonalID_c* pid, mActor_name_t item, int slot,
                                       u8 kind) {
    if (errand != NULL) {
        errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
        errand->base.quest_kind = kind;
        errand->base.time_limit_enabled = FALSE;
        errand->base.progress = 2;
        errand->base.give_reward = FALSE;

        mNpc_CopyAnimalPersonalID(&errand->recipient, pid);
        errand->pockets_idx = slot;
        errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;
        errand->item = item;
    }
}

extern void mQst_SetFirstJobAxe(mQst_errand_c* errand, AnmPersonalID_c* pid, mActor_name_t item, int slot) {
    mQst_SetFirstJobAxe_common(errand, pid, item, slot, mQst_ERRAND_FIRSTJOB_DELIVER_AXE);
}

extern void mQst_SetFirstJobAxe2(mQst_errand_c* errand, AnmPersonalID_c* pid, mActor_name_t item, int slot) {
    mQst_SetFirstJobAxe_common(errand, pid, item, slot, mQst_ERRAND_FIRSTJOB_DELIVER_AXE2);
}

extern void mQst_SetFirstJobNotice(mQst_errand_c* errand) {
    if (errand != NULL) {
        errand->base.quest_type = mQst_QUEST_TYPE_ERRAND;
        errand->base.quest_kind = mQst_ERRAND_FIRSTJOB_POST_NOTICE;
        errand->base.time_limit_enabled = FALSE;
        errand->base.progress = 2;
        errand->base.give_reward = FALSE;

        mNpc_ClearAnimalPersonalID(&errand->recipient);
        errand->errand_type = mQst_ERRAND_TYPE_FIRST_JOB;
    }
}

extern int mQst_GetRandom(int max) {
    return RANDOM(max);
}

extern void mQst_GetGoods_common(mActor_name_t* item, AnmPersonalID_c* pid, int category, mActor_name_t* exist_table,
                                 int exist_num, int list) {
    int generate_random_item = 1;

    if (category == mSP_KIND_FURNITURE) {
        generate_random_item = RANDOM(10);
    }

    /* 1/10 chance to roll an item from the villager's house if the "goods" kind is furniture */
    if (generate_random_item != 0) {
        mSP_SelectRandomItem_New(NULL, item, 1, exist_table, exist_num, category, list, FALSE);
    } else {
        *item = mNpc_GetNpcFurniture(pid);

        if (*item == EMPTY_NO) {
            mSP_SelectRandomItem_New(NULL, item, 1, exist_table, exist_num, category, list, FALSE);
        }
    }
}

extern int mQst_CheckSoccerTarget(ACTOR* actor) {
    int res = FALSE;

    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
        int npc_idx = mQst_GetOccuredContestIdx(mQst_CONTEST_KIND_SOCCER);

        if (npc_idx != -1) {
            Animal_c* animal = Save_GetPointer(animals[npc_idx]);

            if (animal->contest_quest.base.progress == 2) {
                res = mNpc_CheckCmpAnimalPersonalID(&animal->id, &((NPC_ACTOR*)actor)->npc_info.animal->id);
            }
        }
    }

    return res;
}

extern void mQst_NextSoccer(ACTOR* actor) {
    mQst_contest_c* contest;
    int looks = mNpc_LOOKS_GIRL;
    NPC_ACTOR* npc_actor = (NPC_ACTOR*)actor;
    int npc_idx = mQst_GetOccuredContestIdx(mQst_CONTEST_KIND_SOCCER);

    if (npc_idx != -1 && npc_actor != NULL) {
        contest = &Save_Get(animals[npc_idx]).contest_quest;

        if (contest->base.progress == 2 && Common_Get(clip).npc_clip != NULL) {
            Animal_c* animal = npc_actor->npc_info.animal;

            if (animal != NULL) {
                looks = animal->id.looks;
            }

            if ((*Common_Get(clip).npc_clip->force_call_req_proc)(npc_actor, 0x0D8B + looks) == TRUE) {
                contest->base.progress = 1;
                mPr_CopyPersonalID(&contest->player_id, &Now_Private->player_ID);
            }
        }
    }
}

/* @unused int? mQst_CheckBallKeep(...?) */

extern void mQst_NextSnowman(xyz_t snowman_pos) {
    int npc_idx = mQst_GetOccuredContestIdx(0);
    int block_x;
    int block_z;

    if (npc_idx != -1) {
        mQst_contest_c* contest;
        Animal_c* animal = Save_GetPointer(animals[npc_idx]);

        contest = &animal->contest_quest;

        if (contest->base.progress == 1) {
            if (mFI_Wpos2BlockNum(&block_x, &block_z, snowman_pos) == TRUE && animal->home_info.block_x == block_x &&
                animal->home_info.block_z == block_z) {
                mPr_CopyPersonalID(&contest->player_id, &Now_Private->player_ID);
            }
        }
    }
}

extern void mQst_BackSnowman(xyz_t snowman_pos) {
    int npc_idx = mQst_GetOccuredContestIdx(0);
    int block_x;
    int block_z;

    if (npc_idx != -1) {
        mQst_contest_c* contest;
        Animal_c* animal = Save_GetPointer(animals[npc_idx]);

        contest = &animal->contest_quest;

        if (contest->base.progress == 1) {
            if (mFI_Wpos2BlockNum(&block_x, &block_z, snowman_pos) == TRUE && animal->home_info.block_x == block_x &&
                animal->home_info.block_z == block_z) {
                mPr_ClearPersonalID(&contest->player_id);
            }
        }
    }
}

extern void mQst_PrintQuestInfo(gfxprint_t* gfxprint) {
    Private_c* priv = Now_Private;
    mQst_delivery_c* delivery;
    mQst_errand_c* errand;
    Animal_c* animal = Save_Get(animals);
    int i;

    if (priv != NULL) {
        delivery = priv->deliveries;
        errand = priv->errands;
    } else {
        delivery = Save_Get(private_data[0]).deliveries;
        errand = Save_Get(private_data[0]).errands;
    }

    gfxprint_color(gfxprint, 220, 50, 50, 255);
    gfxprint_locate8x8(gfxprint, 3, 4);

    for (i = 0; i < mPr_DELIVERY_QUEST_NUM; i++) {
        if (i < 5 || i >= 10) {
            gfxprint_color(gfxprint, 220, 50, 50, 255);
        } else {
            gfxprint_color(gfxprint, 50, 50, 220, 255);
        }

        if (delivery[i].base.quest_type == mQst_QUEST_TYPE_DELIVERY) {
            gfxprint_printf(gfxprint, "%x", delivery[i].base.quest_kind);
        } else {
            gfxprint_printf(gfxprint, "*");
        }
    }

    gfxprint_color(gfxprint, 50, 50, 220, 255);

    for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
        if (errand[i].base.quest_type == mQst_QUEST_TYPE_ERRAND) {
            gfxprint_printf(gfxprint, "%x", errand[i].base.quest_kind);
        } else {
            gfxprint_printf(gfxprint, "*");
        }
    }

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i < 5 || i >= 10) {
            gfxprint_color(gfxprint, 220, 50, 50, 255);
        } else {
            gfxprint_color(gfxprint, 50, 50, 220, 255);
        }

        if (animal[i].contest_quest.base.quest_type == mQst_QUEST_TYPE_CONTEST) {
            gfxprint_printf(gfxprint, "%x", animal[i].contest_quest.base.quest_kind);
        } else {
            gfxprint_printf(gfxprint, "*");
        }
    }
}
