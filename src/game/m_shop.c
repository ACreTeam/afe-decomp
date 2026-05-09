#include "m_shop.h"

#include "game.h"
#include "m_cockroach.h"
#include "m_collision_bg.h"
#include "m_common_data.h"
#include "m_event.h"
#include "m_handbill.h"
#include "m_house.h"
#include "m_item_name.h"
#include "m_name_table.h"
#include "m_room_type.h"
#include "m_fg_type.h"
#include "m_player_lib.h"
#include "libultra/libultra.h"

extern mActor_name_t* mSP_ftr_list[];
extern mActor_name_t* mSP_binsen_list[];
extern mActor_name_t* mSP_cloth_list[];
extern mActor_name_t* mSP_carpet_list[];
extern mActor_name_t* mSP_wall_list[];

static mActor_name_t diary_listA[6] = { ITM_DIARY01, ITM_DIARY04, ITM_DIARY07, ITM_DIARY10, ITM_DIARY13, EMPTY_NO };
static mActor_name_t diary_listB[6] = { ITM_DIARY02, ITM_DIARY05, ITM_DIARY08, ITM_DIARY11, ITM_DIARY14, EMPTY_NO };
static mActor_name_t diary_listC[7] = { ITM_DIARY03, ITM_DIARY06, ITM_DIARY09, ITM_DIARY12,
                                        ITM_DIARY15, ITM_DIARY00, EMPTY_NO };

static mActor_name_t* mSP_diary_list[mSP_LIST_NUM] = {
    diary_listA, diary_listB, diary_listC, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL,        NULL,        NULL,        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};

static mActor_name_t** mSP_goods_list_table[mSP_KIND_MAX] = {
    mSP_ftr_list, mSP_binsen_list, mSP_cloth_list, mSP_carpet_list, mSP_wall_list, mSP_diary_list,
};

static void mSP_InitItemTable(mActor_name_t* item_table, int count) {
    int i;

    if (item_table == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        *item_table++ = EMPTY_NO;
    }
}

static mActor_name_t* mSP_SelectListFromPriority(mActor_name_t** lists, u8* priorities, int list_type) {
    mActor_name_t* list = NULL;

    switch (list_type) {
        case mSP_LISTTYPE_EVENT:
            list = lists[mSP_LIST_EVENT];
            break;
        case mSP_LISTTYPE_TRAIN:
            list = lists[mSP_LIST_TRAIN];
            break;
        case mSP_LISTTYPE_LOTTERY:
            list = lists[mSP_LIST_LOTTERY];
            break;
        case mSP_LISTTYPE_HALLOWEEN:
            list = lists[mSP_LIST_HALLOWEEN];
            break;
        case mSP_LISTTYPE_HALLOWEEN2:
            list = lists[mSP_LIST_HALLOWEEN2];
            break;
        case mSP_LISTTYPE_PRESENT:
            list = lists[mSP_LIST_PRESENT];
            break;
        case mSP_LISTTYPE_CHRISTMAS:
            list = lists[mSP_LIST_CHRISTMAS];
            break;
        case mSP_LISTTYPE_SNOW:
            list = lists[mSP_LIST_SNOW];
            break;
        case mSP_LISTTYPE_JONASON:
            list = lists[mSP_LIST_JONASON];
            break;
        case mSP_LISTTYPE_POSTOFFICE:
            list = lists[mSP_LIST_POSTOFFICE];
            break;
        case mSP_LISTTYPE_NINTENDO64:
            list = lists[mSP_LIST_NINTENDO64];
            break;
        case mSP_LISTTYPE_SPECIALPRESENT:
            list = lists[mSP_LIST_SPECIALPRESENT];
            break;
        case mSP_LISTTYPE_ISLAND:
            list = lists[mSP_LIST_ISLAND];
            break;
        case mSP_LISTTYPE_ISLANDFAMICOM:
            list = lists[mSP_LIST_ISLANDFAMICOM];
            break;
        case mSP_LISTTYPE_HOMEPAGE:
            list = lists[mSP_LIST_HOMEPAGE];
            break;
        case mSP_LISTTYPE_EVENTPRESENTCHUMON:
            list = lists[mSP_LIST_EVENTPRESENTCHUMON];
            break;
        case mSP_LISTTYPE_KAMAKURA:
            list = lists[mSP_LIST_KAMAKURA];
            break;
        case mSP_LISTTYPE_HARVEST:
            list = lists[mSP_LIST_HARVEST];
            break;
        case mSP_LISTTYPE_MARIO:
            list = lists[mSP_LIST_MARIO];
            break;
        case mSP_LISTTYPE_TENT:
            list = lists[mSP_LIST_TENT];
            break;

        case mSP_LISTTYPE_ABC:
        default: {
            int i;

            for (i = 0; i < 3; i++, priorities++) {
                if (list_type == priorities[0]) {
                    switch (i) {
                        case mSP_LISTTYPE_COMMON:
                            list = lists[mSP_LIST_A];
                            break;
                        case mSP_LISTTYPE_UNCOMMON:
                            list = lists[mSP_LIST_B];
                            break;
                        case mSP_LISTTYPE_RARE:
                            list = lists[mSP_LIST_C];
                            break;
                    }
                }
            }
            break;
        }
    }

    if (list == NULL) {
        list = lists[mSP_LIST_A];
    }

    return list;
}

static void mSP_SetSeasonFTR_local_rnd(mActor_name_t* item_tbl, int count, mActor_name_t* src_item_tbl, int src_count) {
    u8 use_tbl[100];
    int placed_count;
    int i;

    if (count > ARRAY_COUNT(use_tbl) || src_count > ARRAY_COUNT(use_tbl) || count > src_count) {
        return;
    }

    for (i = 0; i < ARRAY_COUNT(use_tbl); i++) {
        use_tbl[i] = FALSE;
    }

    placed_count = 0;
    while (placed_count < count) {
        int rnd_idx = RANDOM(src_count);
        if (use_tbl[rnd_idx] == FALSE) {
            item_tbl[placed_count] = src_item_tbl[rnd_idx];
            use_tbl[rnd_idx] = TRUE;
            placed_count++;
        }
    }
}

static void mSP_SetSeasonFTR_local_december(mActor_name_t* item_table, int count, mActor_name_t ftr0,
                                            mActor_name_t ftr1) {
    if (count > 1) {
        item_table[0] = ftr0;
        item_table[1] = ftr1;
    } else if (fqrand() < 0.5f) {
        item_table[0] = ftr0;
    } else {
        item_table[0] = ftr1;
    }
}

static void mSP_SetSeasonFTR(mActor_name_t* item_table, int count) {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_month_t month = rtc_time.month;
    lbRTC_day_t day = rtc_time.day;

    if (count > 0 && month == lbRTC_DECEMBER) {
        if (day <= 24) {
            mSP_SetSeasonFTR_local_december(item_table, count, FTR_START(FTR_NOG_XTREE), FTR_START(FTR_KON_XTREE02));
        } else if (day >= 26) {
            static mActor_name_t candidacy_table[] = { FTR_START(FTR_SUM_KADOMATU), FTR_START(FTR_SUM_KAGAMOCHI),
                                                       FTR_START(FTR_YAZ_CANDLE), FTR_START(FTR_YOS_KFLAG) };

            if (count > 1) {
                count = 2;
            }

            mSP_SetSeasonFTR_local_rnd(item_table, count, candidacy_table, ARRAY_COUNT(candidacy_table));
        }
    }
}

static mActor_name_t* mSP_GetItemList(mActor_name_t** lists, u8* priorities, int list_type) {
    if (list_type == mSP_LISTTYPE_ABC) {
        int abc_roll = RANDOM(100);
        int goods_power = mPr_GetGoodsPower();
        int rare_chance;
        int uncommon_chance;

        if (goods_power < 0) {
            uncommon_chance = goods_power + 40; /* [10%, 39%] */
            rare_chance = 5;                    /* always 5% chance */
                                                /* common_chance = [85%, 66%] */
        } else {
            rare_chance = goods_power + 5;      /* [5%, 55%] */
            uncommon_chance = rare_chance + 35; /* always 35% chance */
                                                /* common_chance = [60%, 10%]*/
        }

        if (abc_roll < rare_chance) {
            return mSP_SelectListFromPriority(lists, priorities, mSP_LISTTYPE_RARE);
        } else if (abc_roll < uncommon_chance) {
            return mSP_SelectListFromPriority(lists, priorities, mSP_LISTTYPE_UNCOMMON);
        } else {
            return mSP_SelectListFromPriority(lists, priorities, mSP_LISTTYPE_COMMON);
        }
    } else {
        return mSP_SelectListFromPriority(lists, priorities, list_type);
    }
}

static int mSP_GoodsExistAlready(mActor_name_t* goods_table, int count, mActor_name_t item) {
    int i;

    if (goods_table != NULL) {
        for (i = 0; i < count; i++) {
            if (goods_table[i] == item) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

extern int mSP_CollectCheck(mActor_name_t item) {
    mActor_name_t ftr_item = mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(item, FALSE);
    u32* bitfield;
    int idx;

    bitfield = NULL;

    switch (ITEM_NAME_GET_TYPE(ftr_item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            bitfield = Common_Get(now_private)->furniture_collected_bitfield;
            idx = mNT_ftr_item_no_to_ftr_idx(ftr_item);
            break;
        }

        case NAME_TYPE_ITEM1: {
            switch (ITEM_NAME_GET_CAT(ftr_item)) {
                case ITEM1_CAT_PAPER: {
                    bitfield = Common_Get(now_private)->paper_collected_bitfield;
                    idx = (ftr_item - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
                    break;
                }

                case ITEM1_CAT_WALL: {
                    bitfield = Common_Get(now_private)->wall_collected_bitfield;
                    idx = ftr_item - ITM_WALL_START;
                    break;
                }

                case ITEM1_CAT_CARPET: {
                    bitfield = Common_Get(now_private)->carpet_collected_bitfield;
                    idx = ftr_item - ITM_CARPET_START;
                    break;
                }

                case ITEM1_CAT_MINIDISK: {
                    bitfield = Common_Get(now_private)->music_collected_bitfield;
                    idx = ftr_item - ITM_MINIDISK_START;
                    break;
                }
            }

            break;
        }
    }

    if (bitfield == NULL) {
        return FALSE;
    }

    return ((1 << (idx & 0x1F)) & bitfield[idx >> 5]) != 0;
}

static int mSP_CountElementInCommonList(mActor_name_t* list) {
    int count = 0;

    for (; list[0] != EMPTY_NO; list++, count++) {}

    return count;
}

static int mSP_CountElementInCommonList_collect(mActor_name_t* list, int* selected_idx, int uncollected_only) {
    int count = 0;
    int selected;
    int idx = 0;
    mActor_name_t* list_p;

    if (uncollected_only == FALSE) {
        count = mSP_CountElementInCommonList(list);
        *selected_idx = RANDOM(count);
        return count;
    }

    /* Count all uncollected items in the list */
    for (list_p = list; list_p[0] != EMPTY_NO; list_p++) {
        if (mSP_CollectCheck(list_p[0]) == FALSE) {
            count++;
        }
    }

    if (count == 0) {
        *selected_idx = 0;
        return 0;
    }

    selected = RANDOM(count);
    *selected_idx = 0;
    for (list_p = list; list_p[0] != EMPTY_NO; list_p++) {
        if (mSP_CollectCheck(list_p[0]) == FALSE) {
            if (idx == selected) {
                break;
            }

            idx++;
        }

        (*selected_idx)++;
    }

    return count;
}

static int mSP_get_cloth_season() {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_month_t month = rtc_time.month;
    int res;

    switch (month) {
        case lbRTC_JANUARY:
            res = mSP_CLOTH_SEASON_WINTER;
            break;

        case lbRTC_FEBRUARY: {
            if (rtc_time.day > 24) {
                res = mSP_CLOTH_SEASON_SPRING;
            } else {
                res = mSP_CLOTH_SEASON_WINTER;
            }

            break;
        }

        case lbRTC_MARCH:
        case lbRTC_APRIL:
            res = mSP_CLOTH_SEASON_SPRING;
            break;

        case lbRTC_MAY: {
            if (rtc_time.day > 26) {
                res = mSP_CLOTH_SEASON_SUMMER;
            } else {
                res = mSP_CLOTH_SEASON_SPRING;
            }

            break;
        }

        case lbRTC_JUNE:
        case lbRTC_JULY:
            res = mSP_CLOTH_SEASON_SUMMER;
            break;

        case lbRTC_AUGUST: {
            if (rtc_time.day > 26) {
                res = mSP_CLOTH_SEASON_AUTUMN;
            } else {
                res = mSP_CLOTH_SEASON_SUMMER;
            }

            break;
        }

        case lbRTC_SEPTEMBER:
        case lbRTC_OCTOBER:
            res = mSP_CLOTH_SEASON_AUTUMN;
            break;

        case lbRTC_NOVEMBER: {
            if (rtc_time.day > 26) {
                res = mSP_CLOTH_SEASON_WINTER;
            } else {
                res = mSP_CLOTH_SEASON_AUTUMN;
            }

            break;
        }

        case lbRTC_DECEMBER:
            res = mSP_CLOTH_SEASON_WINTER;
            break;
    }

    return res;
}

extern u8 cloth_season_cnt[];

static int mSP_CountElementInClothList(int* selected) {
    u8* count_p = cloth_season_cnt;
    int cloth_season = mSP_get_cloth_season();
    int cloth_count = count_p[mSP_CLOTH_SEASON_ANY] + count_p[cloth_season];

    selected[0] = RANDOM(cloth_count); // random cloth selected

    if (selected[0] >= cloth_season_cnt[mSP_CLOTH_SEASON_ANY]) {
        int i;

        /* seasonal cloths are sequential in the item lists, so add previous season counts to the selected index */
        for (i = mSP_CLOTH_SEASON_SPRING; i < cloth_season; i++) {
            selected[0] += count_p[i];
        }
    }

    return cloth_count;
}

static int mSP_CountElementInClothList_collect(mActor_name_t* list, int* selected, int uncollected_only) {
    u8* count_p = cloth_season_cnt;

    if (uncollected_only == FALSE) {
        return mSP_CountElementInClothList(selected);
    } else {
        int cloth_season;
        int count;
        mActor_name_t* list_p;
        mActor_name_t* list_p2;
        int uncollected_num;
        int n;
        int s;
        int i;
        cloth_season = mSP_get_cloth_season();
        uncollected_num = 0;
        count = 0;

        for (list_p = list; count < count_p[mSP_CLOTH_SEASON_ANY] && list_p != NULL; list_p++) {
            if (mSP_CollectCheck(list_p[0]) == FALSE) {
                uncollected_num++;
            }

            count++;
        }

        n = count_p[mSP_CLOTH_SEASON_ANY];
        for (i = mSP_CLOTH_SEASON_SPRING; i < cloth_season; i++) {
            n += count_p[i]; // add intermediate season counts
        }

        i = n;
        s = n + count_p[cloth_season];
        list_p2 = list + (int)n;
        for (list_p = list_p2; i < s && list_p != NULL; list_p++) {
            if (mSP_CollectCheck(list_p[0]) == FALSE) {
                uncollected_num++;
            }

            i++;
        }

        if (uncollected_num == 0) {
            selected[0] = 0;
            return 0;
        } else {
            int selected_idx = RANDOM(uncollected_num);

            count = 0;
            selected[0] = 0;
            for (; count < count_p[mSP_CLOTH_SEASON_ANY] && list != NULL && selected_idx > 0; list++) {
                if (mSP_CollectCheck(list[0]) == FALSE) {
                    selected_idx--;
                }

                selected[0]++;
                count++;
            }

            i = n;
            for (; i < s && list_p2 != NULL && selected_idx > 0; list_p2++) {
                if (mSP_CollectCheck(list_p2[0]) == FALSE) {
                    selected_idx--;
                }

                selected[0]++;
                i++;
            }
        }

        return uncollected_num;
    }
}

static void mSP_SetDummyItem(mActor_name_t* items_table, int count, int kind) {
    mActor_name_t dummy_table[mSP_KIND_MAX] = {
        FTR_START(FTR_SUM_CLCHEST03), ITM_PAPER00, ITM_CLOTH000, ITM_CARPET00, ITM_WALL00, ITM_DIARY00
    };

    mActor_name_t dummy_item = dummy_table[kind];
    int i;

    for (i = 0; i < count; i++) {
        items_table[i] = dummy_item;
    }
}

extern void mSP_SelectRandomItem_New(GAME* game, mActor_name_t* goods_table, int goods_count,
                                     mActor_name_t* goods_exist_table, int goods_exist_count, int category,
                                     int list_type, int uncollected_only) {
    mSP_InitItemTable(goods_table, goods_count);

    if (goods_count != 0 && goods_table != NULL) {
        u8 abc_priorities[3];
        mActor_name_t** goods_seg_p = mSP_goods_list_table[category];
        int i = 0;

        mSP_GetListPriorityABC(abc_priorities, category);

        while (i < goods_count) {
            mActor_name_t* item_list_p = mSP_GetItemList(goods_seg_p, abc_priorities, list_type);
            int list_item_count;
            int selected_idx;

            if (category == mSP_KIND_CLOTH && (list_type == mSP_LISTTYPE_ABC || list_type == mSP_LIST_A ||
                                               list_type == mSP_LIST_B || list_type == mSP_LIST_C)) {
                list_item_count = mSP_CountElementInClothList_collect(item_list_p, &selected_idx, uncollected_only);
            } else {
                list_item_count = mSP_CountElementInCommonList_collect(item_list_p, &selected_idx, uncollected_only);
            }

            if (list_item_count == 0) {
                return;
            }

            if (mSP_GoodsExistAlready(goods_table, goods_count, item_list_p[selected_idx]) == FALSE &&
                mSP_GoodsExistAlready(goods_exist_table, goods_exist_count, item_list_p[selected_idx]) == FALSE &&
                Save_Get(shop).rare_item != item_list_p[selected_idx]) {
                goods_table[i] = item_list_p[selected_idx];
                i++;
            } else if (list_item_count < goods_count + goods_exist_count) {
                /* forcibly add duplicate items if the list size is less than total possible goods */
                goods_table[i] = item_list_p[selected_idx];
                i++;
            }
        }
    } else {
        mSP_SetDummyItem(goods_table, goods_count, category);
    }
}

extern int mSP_ShopSaleReport(mActor_name_t sold_item, mActor_name_t* goods_table, int goods_count,
                              mActor_name_t rsv_item) {
    mActor_name_t* event_items = Save_Get(event_save_data).special.event.bargin.items;
    int i;

    if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT) {
        for (i = 0; i < mEv_BARGIN_ITEM_NUM; i++) {
            if (event_items[i] == sold_item) {
                event_items[i] = rsv_item;
            }
        }
    }

    for (i = goods_count - 1; i >= 0; i--) {
        if (sold_item == goods_table[i]) {
            goods_table[i] = rsv_item;
            return FALSE;
        }
    }

    if (sold_item == Save_Get(shop).rare_item) {
        Save_Get(shop).rare_item = rsv_item;
        return FALSE;
    }

    return FALSE;
}

static u16 binsen_price_table[256] = {
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0000, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0000,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0000, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0000, 0x0028,
};

static u16 tool_price_table[104] = {
    0x01F4, 0x0190, 0x01F4, 0x01F4, 0x00DC, 0x01E0, 0x0168, 0x0140, 0x0122, 0x01EA, 0x014A, 0x0122, 0x0122,
    0x01A4, 0x017C, 0x017C, 0x0154, 0x0040, 0x01A4, 0x017C, 0x00BE, 0x00E6, 0x00F0, 0x0058, 0x01E0, 0x015E,
    0x0154, 0x00FA, 0x0078, 0x01EA, 0x01EA, 0x017C, 0x0168, 0x01E0, 0x0064, 0x0122, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0190, 0x03D4, 0x03D4, 0x03D4, 0x03D4, 0x03D4, 0x03D4, 0x03D4,
    0x03D4, 0x03D4, 0x03D4, 0x03D4, 0x03D4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0050, 0x0050, 0x0050, 0x01E0, 0x01E0,
    0x01E0, 0x01E0, 0x01E0, 0x01E0, 0x0320, 0x0320, 0x0258, 0x0258, 0x0258, 0x0258, 0x0258, 0x0320, 0x03E8,
    0x0208, 0x0078, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x04B0,
};

static u16 fish_price_table[48] = {
    0x01E0, 0x0258, 0x04B0, 0x1F40, 0x0320, 0x0320, 0x04B0, 0x2EE0, 0x01E0, 0x2EE0, 0x6590, 0x0320,
    0x0320, 0x0320, 0x1450, 0x04B0, 0x04B0, 0x1450, 0x1450, 0x9C40, 0x0A28, 0xEA60, 0x0A28, 0x1450,
    0x6590, 0x9C40, 0x1F40, 0x04B0, 0x2EE0, 0x1450, 0x1450, 0xEA60, 0x03E8, 0x03E8, 0x04B0, 0x0190,
    0x0280, 0x2EE0, 0x4E20, 0x9C40, 0x0320, 0x0C80, 0x0640, 0x9C40, 0x0320, 0x0708, 0x1770, 0x01E0,
};

static u16 cloth_price_table[255] = {
    0x0168, 0x0168, 0x0168, 0x0186, 0x0168, 0x014A, 0x01A4, 0x0122, 0x017C, 0x017C, 0x0168, 0x01AE, 0x0168, 0x014A,
    0x01AE, 0x014A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x015E, 0x017C, 0x0190, 0x1900, 0x1900, 0x1900, 0x1900, 0x1900, 0x1900, 0x0000, 0x0172, 0x0186, 0x017C, 0x0172,
    0x0172, 0x0172, 0x1A90, 0x0140, 0x1518, 0x01A4, 0x01CC, 0x01CC, 0x16A8, 0x0154, 0x1C20, 0x0186, 0x1838, 0x017C,
    0x017C, 0x017C, 0x017C, 0x017C, 0x0154, 0x0154, 0x0154, 0x0154, 0x0154, 0x0154, 0x0154, 0x0154, 0x0154, 0x0140,
    0x0140, 0x0140, 0x017C, 0x017C, 0x017C, 0x0154, 0x0140, 0x0140, 0x019A, 0x01AE, 0x0186, 0x017C, 0x017C, 0x015E,
    0x0140, 0x0140, 0x0172, 0x0154, 0x0154, 0x0168, 0x0168, 0x0122, 0x1400, 0x015E, 0x015E, 0x1770, 0x0172, 0x0172,
    0x0168, 0x017C, 0x0154, 0x0154, 0x0154, 0x007B, 0x0140, 0x01E0, 0x0140, 0x0186, 0x017C, 0x0122, 0x0168, 0x0168,
    0x0168, 0x0168, 0x0168, 0x01A4, 0x01E0, 0x0122, 0x0104, 0x0140, 0x0186, 0x0172, 0x01E0, 0x0168, 0x0168, 0x0208,
    0x0208, 0x017C, 0x01A4, 0x01A4, 0x0122, 0x0168, 0x0154, 0x0186, 0x0186, 0x0168, 0x0309, 0x1900, 0x0172, 0x015E,
    0x0168, 0x0154, 0x0186, 0x0168, 0x017C, 0x017C, 0x017C, 0x017C, 0x017C, 0x017C, 0x0140, 0x0140, 0x0140, 0x017C,
    0x0168, 0x0186, 0x017C, 0x0172, 0x017C, 0x017C, 0x0172, 0x0172, 0x0168, 0x0168, 0x0168, 0x0140, 0x01CC, 0x017C,
    0x01A4, 0x0190, 0x0172, 0x0186, 0x00FA, 0x00FA, 0x00FA, 0x00FA, 0x00FA, 0x00FA, 0x00FA, 0x015E, 0x0168, 0x0032,
    0x015E, 0x0190, 0x1388, 0x01E0, 0x01AE, 0x1838, 0x1838, 0x0168, 0x0186, 0x017C, 0x0186, 0x017C, 0x015E, 0x017C,
    0x017C, 0x017C, 0x01CC, 0x014A, 0x014A, 0x014A, 0x0154, 0x0080, 0x1900, 0x01A4, 0x01A4, 0x01AE, 0x01A4, 0x0140,
    0x0168, 0x00B4, 0x00B4, 0x0140, 0x00B4, 0x017C, 0x0154, 0x0140, 0x01A4, 0x1838, 0x0186, 0x1900, 0x1900, 0x1900,
    0x1900, 0x0154, 0x0154, 0x0140, 0x017C, 0x0172, 0x0168, 0x015E, 0x014A, 0x015E, 0x0168, 0x015E, 0x017C, 0x0172,
    0x017C, 0x0168, 0x1900, 0x0186, 0x0190, 0x1A90, 0x014A, 0x015E, 0x0140, 0x1838, 0x1770, 0x0154, 0x16A8, 0x015E,
    0x01A4, 0x1A90, 0x014A
};

static u16 carpet_price_table[69] = { 0x0870, 0x08FC, 0x0690, 0x0320, 0x0690, 0x0320, 0x1770, 0x07BC, 0x071C, 0x1F40,
                                      0x047E, 0x0320, 0x0532, 0x0604, 0x1964, 0x1F40, 0x1B58, 0xA118, 0x1A90, 0x0604,
                                      0x062C, 0x0B22, 0x06D6, 0x0604, 0x0690, 0x8AE0, 0x0370, 0x1C20, 0x0884, 0x0762,
                                      0x0834, 0x053C, 0x0550, 0x04CE, 0x0320, 0x0ABE, 0x0BA4, 0x04CE, 0x0564, 0x056E,
                                      0x0BA4, 0x0604, 0x05C8, 0x1A90, 0x2580, 0x07A8, 0x1A90, 0xBF40, 0x1C20, 0x1E78,
                                      0x08FC, 0x092E, 0x2134, 0x206C, 0x065E, 0x02D0, 0x1C20, 0x1C20, 0x071C, 0x0C80,
                                      0x2008, 0x0550, 0x0500, 0x0514, 0x1F40, 0x2710, 0x12C0, 0x1A90, 0x0370 };

static u16 wall_price_table[69] = { 0x07A8, 0x0834, 0x0460, 0x0320, 0x058C, 0x0370, 0x1770, 0x0758, 0x058C, 0x1B58,
                                    0x0884, 0x06D6, 0x0460, 0x04B0, 0x15E0, 0x1DB0, 0x1900, 0xA118, 0x1770, 0x041A,
                                    0x04EC, 0x08C0, 0x05AA, 0x05AA, 0x05C8, 0x8AE0, 0x0320, 0x1900, 0x07A8, 0x06F4,
                                    0x062C, 0x047E, 0x047E, 0x0460, 0x04B0, 0x0992, 0x0A64, 0x041A, 0x04E2, 0x04B0,
                                    0x08C0, 0x0528, 0x0320, 0x1B58, 0x23F0, 0x05BE, 0x1A90, 0xBF40, 0x1F40, 0x1CE8,
                                    0x0834, 0x0866, 0x1D4C, 0x1C20, 0x05DC, 0x0320, 0x1B58, 0x2328, 0x0690, 0x08CA,
                                    0x23F0, 0x0528, 0x04D8, 0x0500, 0x1F40, 0x2328, 0x12C0, 0x1770, 0x0320 };

static u16 food_price_table[8] = {
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x4E20, 0x0064, 0x0258,
};

static u16 plant_price_table[11] = { 0x003C, 0x003C, 0x0078, 0x0078, 0x0078, 0x0078,
                                     0x0078, 0x0078, 0x0078, 0x0078, 0x0078 };

static u16 md_price_table[140] = {
    0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014,
    0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014,
    0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014,
    0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014,
    0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0014,
    0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014
};

static u16 diary_price_table[16] = {
    0x00B4, 0x00C8, 0x04EC, 0x05AA, 0x0118, 0x0366, 0x03D4, 0x0370,
    0x04E2, 0x04B0, 0x0140, 0x0140, 0x0140, 0x0140, 0x0140, 0x035C,
};

static u16 insect_price_table[] = {
    0x0140, 0x0140, 0x0320, 0x1F40, 0x04B0, 0x0640, 0x0D48, 0x0320, 0x4650, 0x0208, 0x0140, 0x0320, 0x4650, 0x0320,
    0x1518, 0x0208, 0x0208, 0x06B8, 0x0190, 0x0140, 0x1518, 0x1F40, 0x2EE0, 0x0320, 0x0208, 0x0320, 0x06B8, 0x03E8,
    0x0014, 0x1F40, 0x1F40, 0x9C40, 0x03E8, 0x0320, 0x0208, 0x03E8, 0x03E8, 0x04B0, 0x0140, 0x0208, 0x2EE0, 0x0640,
    0x03E8, 0xAFC8, 0x0258, 0x0118, 0x0320, 0x04B0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

static u16* l_binsen_price_info = binsen_price_table;
static u16* l_cloth_price_info = cloth_price_table;
static u16* l_carpet_price_info = carpet_price_table;
static u16* l_wall_price_info = wall_price_table;
static u16* l_tool_price_info = tool_price_table;
static u16* l_plant_price_info = plant_price_table;
static u16* l_fish_price_info = fish_price_table;
static u16* l_food_price_info = food_price_table;
static u16* l_md_price_info = md_price_table;
static u16* l_diary_price_info = diary_price_table;
static u16* l_insect_price_info = insect_price_table;

static u16** l_price_info[ITEM1_CAT_NUM] = {
    &l_binsen_price_info,
    NULL,
    &l_tool_price_info,
    &l_fish_price_info,
    &l_cloth_price_info,
    NULL,
    &l_carpet_price_info,
    &l_wall_price_info,
    &l_food_price_info,
    &l_plant_price_info,
    &l_md_price_info,
    &l_diary_price_info,
    NULL,
    &l_insect_price_info,
    NULL,
    NULL,
};

static u16 ftr_price_table[] = {
    0xA118, 0x0A00, 0x0780, 0x04B0, 0xBF40, 0x0EEC, 0x08C0, 0x09B0, 0x08C0, 0x08FC, 0x0578, 0x0BEA, 0x0960, 0x0A00,
    0x0884, 0xBF40, 0x0DC0, 0x0960, 0x0870, 0x0870, 0xA118, 0x0910, 0x0640, 0x0AA0, 0x0A00, 0x0870, 0x08CA, 0x0960,
    0x0866, 0x0898, 0x0884, 0x0514, 0x08CA, 0x0578, 0x04B0, 0x0320, 0x03E8, 0x04B0, 0x0672, 0x021C, 0x0352, 0x04B0,
    0x0640, 0x04B0, 0x0578, 0x0578, 0x0802, 0x0708, 0x04B0, 0x07BC, 0x07D0, 0x0640, 0x0640, 0x0640, 0x0640, 0x06A4,
    0x0708, 0x0A00, 0x0898, 0x0640, 0x0320, 0x0D20, 0x0708, 0x0898, 0x0640, 0x0A00, 0x0578, 0x0D20, 0x076C, 0x0320,
    0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x04B0, 0x0834, 0x09EC, 0x0640, 0x0578, 0x0578, 0x0578, 0x0578, 0x0514,
    0x06A4, 0x0870, 0x0708, 0x08C0, 0x0708, 0x07D0, 0x0DAC, 0x0640, 0x08E8, 0x0640, 0x07D0, 0x0884, 0x0898, 0x0640,
    0x0640, 0x0640, 0x0C30, 0x03E8, 0x0960, 0x07D0, 0x0708, 0x0A00, 0x07D0, 0x0578, 0x08FC, 0x06A4, 0x071C, 0x0640,
    0x0AF0, 0x0960, 0x076C, 0x0708, 0x0640, 0x0514, 0x0320, 0x0320, 0x0320, 0x0A50, 0x0258, 0x0898, 0x06A4, 0x0834,
    0x0514, 0x0000, 0x04B0, 0x04B0, 0x04B0, 0x06A4, 0x06A4, 0x09D8, 0x0898, 0x0708, 0x0A14, 0x0708, 0x0834, 0x07BC,
    0x07BC, 0x044C, 0x0898, 0x08FC, 0x04B0, 0x0320, 0x04B0, 0x076C, 0x0708, 0x07BC, 0x0320, 0x0320, 0x04B0, 0x0898,
    0x03E8, 0x076C, 0x076C, 0x076C, 0x09C4, 0x0578, 0x0578, 0x0578, 0x04B0, 0x0708, 0x07BC, 0x08E8, 0x0708, 0x0960,
    0x0992, 0x0546, 0x0708, 0x07A8, 0x07A8, 0x07A8, 0x07A8, 0x07A8, 0x07A8, 0x07A8, 0x07A8, 0x07A8, 0x07A8, 0x07A8,
    0x07A8, 0x07A8, 0x07A8, 0x07A8, 0x07C6, 0x0514, 0x0000, 0x05DC, 0x0640, 0x0708, 0x06A4, 0x07D0, 0x0640, 0x0578,
    0x02BC, 0x02BC, 0x0309, 0x076C, 0x0578, 0x0708, 0x0708, 0x0514, 0x04B0, 0x08CA, 0x08FC, 0x076C, 0x0910, 0x07BC,
    0x0A14, 0x09B0, 0x0A3C, 0x0708, 0x0834, 0x076C, 0x04B0, 0x0834, 0x076C, 0x0708, 0x0870, 0x0708, 0x04B0, 0x08F2,
    0x0960, 0x0708, 0x06A4, 0x0960, 0x09B0, 0x08E8, 0x08FC, 0x0834, 0x04B0, 0x0514, 0x04B0, 0x04B0, 0x07D0, 0x0514,
    0x0514, 0x0514, 0x05DC, 0x0514, 0x04B0, 0x0514, 0x0514, 0x04B0, 0x06A4, 0x03E8, 0x0708, 0x0708, 0x0708, 0x0640,
    0x0708, 0x076C, 0x0640, 0x04B0, 0x0320, 0x0640, 0x05DC, 0x06A4, 0x044C, 0x0320, 0x0320, 0x0258, 0x06A4, 0x06A4,
    0x0708, 0x0640, 0x04B0, 0x04B0, 0x0578, 0x0578, 0x06A4, 0x03E8, 0x0CB2, 0x0320, 0x0320, 0x0320, 0x06A4, 0x04B0,
    0x0578, 0x044C, 0x0514, 0x0514, 0x0708, 0x08FC, 0x01F4, 0x01F4, 0x0898, 0x0960, 0x0708, 0x0ED8, 0x0730, 0x0320,
    0x06D6, 0x0000, 0x0708, 0x0258, 0x076C, 0x09C4, 0x0578, 0x0320, 0x0640, 0x07BC, 0xA118, 0x101C, 0xA118, 0x0000,
    0xA118, 0xA118, 0xA118, 0x0C80, 0x0A28, 0x0870, 0x0834, 0x0898, 0x0960, 0x094C, 0x0A14, 0x0960, 0x0AF0, 0xA118,
    0xA118, 0x09EC, 0x0640, 0x0708, 0x06A4, 0x0708, 0x0258, 0x04B0, 0x0B40, 0x0258, 0x07D0, 0x0708, 0x0640, 0x0960,
    0x6400, 0x0A00, 0x0640, 0x0258, 0x0924, 0x0640, 0x0578, 0xA118, 0x07D0, 0x0898, 0x05DC, 0x076C, 0x0AF0, 0x05DC,
    0x06A4, 0x0C30, 0x0ADC, 0x0C80, 0x0C1C, 0x0960, 0x0834, 0x07D0, 0x076C, 0x012C, 0x01E0, 0x030C, 0x03D4, 0x02A8,
    0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0,
    0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0,
    0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0,
    0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0,
    0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0,
    0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0,
    0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0,
    0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0,
    0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0, 0x0CF0,
    0x0CF0, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C,
    0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x012C, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
    0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0BB8, 0x0BB8, 0x0BB8, 0x0BB8, 0x0BB8, 0x0BB8,
    0x0BB8, 0x0BB8, 0x0BB8, 0x0BB8, 0x0BB8, 0x0BB8, 0x0BB8, 0x0BB8, 0x0BB8, 0x9C40, 0x9C40, 0x9C40, 0x9C40, 0x0BB8,
    0x0730, 0x0A14, 0x0F0A, 0x05DC, 0x05DC, 0x0ABE, 0x5DC0, 0x07BC, 0xBF40, 0xBF40, 0xBF40, 0xBF40, 0xBF40, 0xBF40,
    0xBF40, 0xBF40, 0x0320, 0x0898, 0x0866, 0x04B0, 0x0578, 0x0708, 0x092E, 0x07D0, 0x02BC, 0x0640, 0x05DC, 0x0708,
    0x0514, 0x044C, 0x0514, 0x06A4, 0x06A4, 0x1194, 0x07D0, 0x0546, 0x09B0, 0x0AF0, 0x0AF0, 0x5AA0, 0x5AA0, 0x0AF0,
    0x0AF0, 0x5AA0, 0x5AA0, 0x0AF0, 0x0AF0, 0x03E8, 0x03E8, 0x0514, 0x05C8, 0x0834, 0x0898, 0x0898, 0x076C, 0x0578,
    0x0708, 0x09C4, 0x0640, 0x0578, 0x0384, 0x55F0, 0x4650, 0x4E20, 0x5DC0, 0x4E20, 0x55F0, 0x4E20, 0x3E80, 0x4650,
    0x4E20, 0x3E80, 0x4650, 0x3E80, 0x4650, 0x4650, 0x3E80, 0x4650, 0x4650, 0x2EE0, 0x2710, 0x12C0, 0x0FA0, 0x1130,
    0x15E0, 0x1450, 0x0578, 0x8AE0, 0x8AE0, 0x8AE0, 0x8AE0, 0x8AE0, 0x8AE0, 0x8AE0, 0x8AE0, 0x8AE0, 0x8AE0, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1388, 0x0AA0, 0x0FA0, 0x1180, 0x0500, 0x1130,
    0x0F50, 0x9C40, 0x0D20, 0x0910, 0x1DB0, 0x5DC0, 0x1400, 0x0AA0, 0x1DB0, 0x1C20, 0x23F0, 0x23F0, 0x1450, 0x11F8,
    0x0028, 0x0028, 0x0028, 0x0028, 0x0028, 0x0050, 0x0050, 0x0050, 0x23F0, 0x23F0, 0x15E0, 0x1DB0, 0xFA00, 0x8CA0,
    0xFA00, 0xB3B0, 0xBB80, 0x1CE8, 0x1C20, 0x1C20, 0x1C20, 0x28A0, 0x9C40, 0x9C40, 0x12C0, 0x0785, 0x3B60, 0x3B60,
    0xB3B0, 0x0500, 0x0FA0, 0x12C0, 0x6A40, 0x04E2, 0x0578, 0x0578, 0x0370, 0xBB80, 0x52D0, 0x1770, 0x2EE0, 0x2710,
    0x3200, 0x7D00, 0x4E20, 0x2710, 0xFA00, 0xFA00, 0xFA00, 0xFA00, 0xFA00, 0xFA00, 0xFA00, 0xFA00, 0xFA00, 0xFA00,
    0xFA00, 0xFA00, 0xFA00, 0xFA00, 0xFA00, 0xA978, 0x04B0, 0x0578, 0x04B0, 0x09C4, 0x0050, 0x00B4, 0x00C8, 0x04EC,
    0x05AA, 0x0118, 0x0366, 0x03D4, 0x0370, 0x04E2, 0x04B0, 0x0140, 0x0140, 0x0140, 0x0140, 0x0140, 0x035C, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0564, 0x0898, 0x092E, 0x0578, 0x03D4,
    0x2710, 0x073A, 0x0640, 0x062C, 0x0578, 0x0578, 0x06E0, 0x0640, 0x0C80, 0x035C, 0x0000, 0x0000, 0x04B0, 0x0078,
    0x09C4, 0x0352, 0x1068, 0x0352, 0x033E, 0x0352, 0x04D8, 0x04D8, 0x0528, 0x0352, 0x2648, 0x041A, 0x0366, 0x23F0,
    0x062C, 0x033E, 0x20D0, 0x0384, 0x22C4, 0x04B0, 0x16A8, 0x0834, 0x05AA, 0x06E0, 0x094C, 0x049C, 0x0898, 0x0898,
    0x03DE, 0x0640, 0x0758, 0x0366, 0x0654, 0x07D0, 0x0334, 0x08F2, 0x0528, 0x02A8, 0x0200, 0x04EC, 0x05A0, 0x1194,
    0x05FA, 0x0FA0, 0x0640, 0x0528, 0x0D34, 0x05FA, 0xDAC0, 0xDAC0, 0x0208, 0x03FC, 0x0348, 0x0884, 0x0370, 0x044C,
    0x1B58, 0x1B58, 0x3414, 0x0ED8, 0x0E60, 0x056E, 0x3414, 0x3414, 0x3414, 0x3414, 0x3414, 0x3414, 0x0400, 0x0400,
    0x3414, 0x0400, 0x3414, 0x0400, 0x3414, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x037A, 0x0400, 0x04CE, 0x0A8C,
    0x041A, 0x157C, 0x1A90, 0x1A90, 0x049C, 0x0528, 0x0BAE, 0x0C76, 0x0E06, 0x0550, 0x08C0, 0x0D84, 0x0668, 0x09F6,
    0x07BC, 0x1C20, 0x03A2, 0x03A2, 0x03A2, 0x038E, 0x038E, 0x038E, 0x03AC, 0x03AC, 0x03AC, 0x049C, 0x0AC8, 0x0514,
    0x0D34, 0x07A8, 0x05BE, 0x0758, 0x06FE, 0x0640, 0x0762, 0x0078, 0x0064, 0x01A4, 0x0410, 0x0500, 0x0848, 0x1130,
    0x0064, 0x021C, 0x03C0, 0x05A0, 0x07A8, 0x0C80, 0x00C8, 0x0258, 0x0370, 0x0460, 0x05F0, 0x0E10, 0x003C, 0x0154,
    0x0370, 0x0000,
};

extern u32 mSP_ItemNo2ItemPrice(mActor_name_t item_no) {
    static u32 shell_price_table[ITM_SHELL_END - ITM_SHELL_START] = { 160, 80, 600, 120, 240, 1800, 1400, 1000 };

    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_year_t year = rtc_time.year;
    u32 price = 0;

    item_no = mRmTp_FtrItemNo2Item1ItemNo(item_no, FALSE);
    if (item_no == ITM_HUKUBUKURO_BAG) {
        return year;
    }

    if (item_no >= ITM_SHELL0 && item_no <= ITM_SHELL7) {
        u32 idx = item_no - ITM_SHELL0;

        return shell_price_table[idx % 8];
    }

    if (item_no == ITM_SIGNBOARD) {
        return mSP_SIGNBOARD_PRICE;
    }

    switch (ITEM_NAME_GET_TYPE(item_no)) {
        case NAME_TYPE_ITEM1: {
            u16** price_list_pp = l_price_info[ITEM_NAME_GET_CAT(item_no)];

            if (price_list_pp != NULL) {
                int idx = item_no & 0xFF;
                u16* price_list_p = *price_list_pp;

                if (item_no >= ITM_PAPER_START && item_no <= (ITM_PAPER_END - 1)) {
                    int paper_idx = (item_no - ITM_PAPER_START);

                    idx = (item_no - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
                    price = price_list_p[idx];
                    price = price * ((paper_idx / 64) + 1);
                    return price;
                }

                if (item_no == ITM_FOOD_APPLE || item_no == ITM_FOOD_CHERRY || item_no == ITM_FOOD_PEAR ||
                    item_no == ITM_FOOD_PEACH || item_no == ITM_FOOD_ORANGE) {
                    if (Save_Get(fruit) != item_no) {
                        return mSP_FOREIGN_FRUIT_PRICE;
                    }
                }

                return price_list_p[idx];
            }

            break;
        }

        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            int ftr_idx = mNT_ftr_item_no_to_ftr_idx(item_no);
            return ftr_price_table[ftr_idx];
        }

        default: {
            return 0;
        }
    }

    return 0;
}

extern u32 mSP_ItemNo2ItemPrice_Tanu(mActor_name_t item_no) {
    u32 price = mSP_ItemNo2ItemPrice(item_no);

    if (mSP_ShopOpen() == mSP_SHOP_STATUS_OPENEVENT) {
        price *= 0.8f;
    }

    if (mSP_force_opend()) {
        price *= 1.2f;
    }

    return price;
}

extern u32 mSP_ItemNo2ItemPrice_TakeBack(mActor_name_t item_no) {
    u32 price = mSP_ItemNo2ItemPrice(item_no);

    price /= mSP_SELL_BUY_RATIO;
    if (mSP_force_opend()) {
        price *= 0.7f;
    }
    return price;
}

extern int mSP_SearchItemCategoryPriority(mActor_name_t item_no, int category, int list_type, GAME* game) {
    u8 abc_priorities[3];
    mActor_name_t** lists_p = mSP_goods_list_table[category];
    mActor_name_t* list_p;
    int count;
    int i;

    mSP_GetListPriorityABC(abc_priorities, category);
    list_p = mSP_GetItemList(lists_p, abc_priorities, list_type);
    count = mSP_CountElementInCommonList(list_p);

    if (list_p != NULL) {
        for (i = 0; i < count; i++) {
            if (item_no == list_p[i]) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

static int mSP_ItemNo2GoodsListCategory(mActor_name_t item_no) {
    if (ITEM_IS_FTR(item_no)) {
        return mSP_KIND_FURNITURE;
    } else if (item_no >= ITM_PAPER_START && item_no <= ITM_PAPER_END - 1) {
        return mSP_KIND_PAPER;
    } else if (item_no >= ITM_CLOTH_START && item_no < ITM_CLOTH_END) {
        return mSP_KIND_CLOTH;
    } else if (item_no >= ITM_WALL_START && item_no < ITM_WALL_END) {
        return mSP_KIND_WALLPAPER;
    } else if (item_no >= ITM_CARPET_START && item_no < ITM_CARPET_END) {
        return mSP_KIND_CARPET;
    } else if (item_no >= ITM_DIARY_START && item_no <= (ITM_DIARY_END - 1)) {
        return mSP_KIND_DIARY;
    }

    return -1;
}

static u8 l_zakka_goods[mSP_GOODS_TYPE_NUM] = {
    1, // stationery
    1, // clothing
    1, // ABC ftr
    0, // rare ftr
    1, // carpet
    1, // wallpaper
    1, // ??
    0, // ??
    1, // saplings
    2, // tools
    1  // plants
};

static u8 l_conbini_goods[mSP_GOODS_TYPE_NUM] = {
    2, // stationery
    2, // clothing
    2, // ABC ftr
    0, // rare ftr
    1, // carpet
    1, // wallpaper
    1, // ??
    0, // ??
    1, // saplings
    3, // tools
    2  // plants
};

static u8 l_super_goods[mSP_GOODS_TYPE_NUM] = {
    2, // stationery
    3, // clothing
    3, // ABC ftr
    1, // rare ftr
    2, // carpet
    2, // wallpaper
    1, // ??
    0, // ??
    2, // saplings
    2, // tools
    3  // plants
};

static u8 l_dsuper_goods[mSP_GOODS_TYPE_NUM] = {
    4, // stationery
    5, // clothing
    5, // ABC ftr
    1, // rare ftr
    3, // carpet
    3, // wallpaper
    1, // ??
    0, // ??
    3, // saplings
    3, // tools
    4  // plants
};

static u8* l_goods_count_table[mSP_SHOP_TYPE_NUM] = { l_zakka_goods, l_conbini_goods, l_super_goods, l_dsuper_goods };

static void mSP_MakeRandomGoodsList(GAME* game, int* count, mActor_name_t* goods_list) {
    int shop_level = mSP_GetShopLevel();
    u8* goods_count = l_goods_count_table[shop_level];
    Shop_c* shop = Save_GetPointer(shop);
    mActor_name_t rare;

    /* roll rare furniture if the shop has one */
    if (goods_count[mSP_GOODS_TYPE_RARE_FTR] != 0) {
        mSP_SelectRandomItem_New(game, &rare, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, FALSE);
    } else {
        rare = EMPTY_NO;
    }

    Save_Get(shop).rare_item = rare;

    /* roll ABC list furniture */
    mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_FTR], NULL, 0, mSP_KIND_FURNITURE,
                             mSP_LISTTYPE_ABC, FALSE);
    mSP_SetSeasonFTR(goods_list + count[0],
                     goods_count[mSP_GOODS_TYPE_FTR]); // replace with seasonal furniture if necessary
    count[0] += goods_count[mSP_GOODS_TYPE_FTR];

    /* check for grab bag sale */
    if (mSP_Chk_HukubukuroSail()) {
        shop->flowers_candy_grab_bag_count += (s8)goods_count[mSP_GOODS_TYPE_PAPER];
        if (shop_level >= mSP_SHOP_TYPE_SUPER) {
            shop->flowers_candy_grab_bag_count += 1;
        }
    } else {
        /* no grab bag sale, so roll paper & diaries */
        mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_PAPER], NULL, 0,
                                 mSP_KIND_PAPER, mSP_LISTTYPE_ABC, FALSE);
        count[0] += goods_count[mSP_GOODS_TYPE_PAPER];

        /* only roll diaries for Nookway or higher */
        if (shop_level >= mSP_SHOP_TYPE_SUPER) {
            mSP_SelectRandomItem_New(game, goods_list + count[0], 1, NULL, 0, mSP_KIND_DIARY, mSP_LISTTYPE_ABC, FALSE);
            count[0] += 1;
        }
    }

    /* roll clothing */
    mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_CLOTH], NULL, 0, mSP_KIND_CLOTH,
                             mSP_LISTTYPE_ABC, FALSE);
    count[0] += goods_count[mSP_GOODS_TYPE_CLOTH];

    /* roll carpets */
    mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_CARPET], NULL, 0, mSP_KIND_CARPET,
                             mSP_LISTTYPE_ABC, FALSE);
    count[0] += goods_count[mSP_GOODS_TYPE_CARPET];

    /* roll wallpaper */
    mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_WALL], NULL, 0, mSP_KIND_WALLPAPER,
                             mSP_LISTTYPE_ABC, FALSE);
    count[0] += goods_count[mSP_GOODS_TYPE_WALL];
}

static void mSP_SelectTool(mActor_name_t* goods_list, int* count, int tool_num, int shop_level) {
    static int table[4] = { ITM_SHOVEL, ITM_NET, ITM_ROD, ITM_AXE };

    int tools_added = 0;
    u16 paint_idx = Save_Get(shop).shop_info.paint_color;
    u32 sales_sum = Save_Get(shop).sales_sum;
    f32 tool_max;

    /* tool lockout based on sales sum is only applicable to Nook's Cranny */
    if (shop_level > mSP_SHOP_TYPE_ZAKKA) {
        tool_max = 4; /* shove, net, rod, axe */
    } else if (sales_sum < mSP_NET_SALES_SUM) {
        tool_max = 1; /* shovel only */
    } else if (sales_sum < mSP_ROD_SALES_SUM) {
        tool_max = 2; /* shovel, net */
    } else if (sales_sum < mSP_AXE_SALES_SUM) {
        tool_max = 3; /* shovel, net, rod */
    } else {
        tool_max = 4; /* shove, net, rod, axe */
    }

    if (tool_num > (int)tool_max) {
        tool_num = (int)tool_max;
    }

    /*
      This implementation kind of sucks.
      At best case there's a (1/4)^4 (~0.4%) chance of
      rolling all four unique tools in a single go.
    */
    while (tools_added < tool_num) {
        int idx = RANDOM(tool_max);
        mActor_name_t tool = table[idx];

        /* Don't allow duplicate tools */
        if (mSP_GoodsExistAlready(goods_list, count[0], tool) == FALSE) {
            goods_list[(int)count[0]] = tool;
            tools_added++;
            count[0]++;
        }
    }

    /* Add paint & signboard if shop is Nookway or greater */
    if (shop_level >= mSP_SHOP_TYPE_SUPER) {
        if ((u16)paint_idx >= PAINT_NUM) {
            paint_idx = 0; /* wrap over to beginning */
        }

        goods_list[count[0]] = ITM_RED_PAINT + paint_idx;
        paint_idx++;
        Save_Get(shop).shop_info.paint_color = paint_idx;

        count[0]++;
        goods_list[count[0]] = ITM_SIGNBOARD;
        count[0]++;
    }

    /* Add umbrella */
    mSP_RandomUmbSelect(goods_list + count[0], 1);
    count[0]++;

    // add medicine
    goods_list[count[0]] = ITM_MEDICINE;
    count[0]++;
}

static void mSP_SelectPlant(mActor_name_t* goods_list, int* count, int flower_count, int sapling_count,
                            const int shop_level) {
    u8 flower_use[FLOWER_NUM];
    int i;

    if (mSP_CheckHallowinDay()) {
        for (i = 0; i < flower_count; i++) {
            goods_list[count[0]] = ITM_FOOD_CANDY;
            count[0]++;
        }
        flower_count = sapling_count;
        sapling_count = 0;
    } else if (mSP_CheckCrackerDay()) {
        for (i = 0; i < flower_count; i++) {
            goods_list[count[0]] = ITM_CRACKER;
            count[0]++;
        }
        flower_count = sapling_count;
        sapling_count = 0;
    }

    if (shop_level >= mSP_SHOP_TYPE_SUPER && sapling_count > 0) {
        goods_list[count[0]] = ITM_CEDAR_SAPLING;
        sapling_count--;
        count[0] += 1;
    }

    for (i = sapling_count; i > 0; i--) {
        goods_list[count[0]] = ITM_SAPLING;
        count[0] += 1;
    }

    for (i = 0; i < FLOWER_NUM; i++) {
        flower_use[i] = FALSE;
    }

    while (flower_count > 0) {
        int idx = RANDOM(FLOWER_NUM);

        if (flower_use[idx] == FALSE) {
            goods_list[count[0]] = ITM_WHITE_PANSY_BAG + idx;
            flower_use[idx] = TRUE;
            flower_count--;
            count[0] += 1;
        }
    }
}

static void mSP_MakeGoodsList(GAME* game) {
    int count = 0;
    mActor_name_t* shop_items = Save_Get(shop).items;
    Shop_c* shop = Save_GetPointer(shop);
    int shop_level = mSP_GetShopLevel();
    u8* goods_count = l_goods_count_table[shop_level];
    u8 tool_count = goods_count[mSP_GOODS_TYPE_TOOL];
    u8 flower_count = goods_count[mSP_GOODS_TYPE_PLANT];
    u8 sapling_count = goods_count[mSP_GOODS_TYPE_SAPLING];

    if (mSP_CheckFukubikiDay() == FALSE) {
        if (mSP_Chk_HukubukuroSail() != FALSE) {
            shop->flowers_candy_grab_bag_count = 0;
        }

        mSP_MakeRandomGoodsList(game, &count, shop_items);

        if (mSP_Chk_HukubukuroSail() != FALSE) {
            shop->flowers_candy_grab_bag_count += (s8)tool_count;
            shop->flowers_candy_grab_bag_count += (s8)flower_count;
            shop->flowers_candy_grab_bag_count += (s8)sapling_count;
            shop->flowers_candy_grab_bag_count++; // add medicine

            if (shop_level >= mSP_SHOP_TYPE_SUPER) {
                shop->flowers_candy_grab_bag_count++; // add signboard & paint
                shop->flowers_candy_grab_bag_count++;
            }

            for (; shop->flowers_candy_grab_bag_count > 0; shop->flowers_candy_grab_bag_count--) {
                shop_items[count] = ITM_HUKUBUKURO_BAG;
                count++;
            }

            mSP_RandomUmbSelect(shop_items + count, 1);
        } else {
            mSP_SelectTool(shop_items, &count, tool_count, shop_level & 3);
            mSP_SelectPlant(shop_items, &count, flower_count, sapling_count, shop_level & 3);
        }
    }
}

static void mSP_MakeLotteryList(GAME* game) {
    mActor_name_t* lottery_items = Save_Get(shop).lottery_items;
    mActor_name_t unobtained_lottery_item;

    mSP_SelectRandomItem_New(game, &unobtained_lottery_item, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY,
                             TRUE);

    if (unobtained_lottery_item == EMPTY_NO) {
        mSP_SelectRandomItem_New(game, lottery_items, mSP_LOTTERY_ITEM_COUNT, NULL, 0, mSP_KIND_FURNITURE,
                                 mSP_LISTTYPE_LOTTERY, FALSE);
    } else {
        mSP_SelectRandomItem_New(game, lottery_items + 1, mSP_LOTTERY_ITEM_COUNT - 1, &unobtained_lottery_item, 1,
                                 mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY, FALSE);

        lottery_items[0] = unobtained_lottery_item;
    }
}

extern int mSP_CheckExchangeDay2() {
    Shop_c* shop = Save_GetPointer(shop);
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    int res =
        lbRTC_IsEqualTime(&rtc_time, &shop->exchange_time, lbRTC_CHECK_DAYS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_YEARS);

    return res == lbRTC_EQUAL;
}

extern int mSP_CheckExchangeMonth() {
    Shop_c* shop = Save_GetPointer(shop);
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    int res = lbRTC_IsEqualTime(&rtc_time, &shop->exchange_time, lbRTC_CHECK_MONTHS | lbRTC_CHECK_YEARS);

    return res == lbRTC_EQUAL;
}

extern void mSP_NewExchangeDay() {
    Save_Get(shop).exchange_time = Common_Get(time.rtc_time);
}

/* @unused size: 0x104 */
// ? mSP_SearchRareFurniture(...)

extern void mSP_ShopRareLeaflet(int house_no, int shop_level, mActor_name_t item, int send_proc) {
    static int rare_leaflet_bunmen[mSP_SHOP_TYPE_NUM][2] = { { 18, 18 }, { 19, 19 }, { 21, 20 }, { 23, 22 } };

    if (Save_Get(homes[house_no]).ownerID.land_id != 0xFFFF) {
        int free_mail_idx = mMl_chk_mail_free_space(Save_Get(homes[house_no]).mailbox, HOME_MAILBOX_SIZE);
        int pl_no = mHS_get_pl_no(house_no) & 3;
        int type = RANDOM(10) & 1;

        if (mEv_ArbeitPlayer(pl_no) != TRUE) {
            u8 item_name_str[mIN_ITEM_NAME_LEN];
            Mail_c leaflet;
            int header_back_start;

            mIN_copy_name_str(item_name_str, item);
            mHandbill_Set_free_str(mHandbill_FREE_STR7, item_name_str, mIN_ITEM_NAME_LEN);
            mMl_clear_mail(&leaflet);
            mHandbill_Load_HandbillFromRom(leaflet.content.text.split.header, &header_back_start,
                                           leaflet.content.text.split.footer, leaflet.content.text.split.body,
                                           rare_leaflet_bunmen[shop_level][type]);
            leaflet.content.font = mMl_FONT_RECV;
            leaflet.content.header_back_start = header_back_start;
            leaflet.content.mail_type = mMl_TYPE_SHOP_SALE_LEAFLET;
            leaflet.content.paper_type = (u8)ITM_PAPER55; // simple paper

            switch (send_proc) {
                case mPO_SENDTYPE_MAIL: {
                    mPO_receipt_proc(&leaflet, mPO_SENDTYPE_LEAFLET);

                    break;
                }

                default: {
                    if (free_mail_idx >= 0) {
                        mPr_CopyPersonalID(&leaflet.header.recipient.personalID,
                                           &Save_Get(private_data[mHS_get_pl_no(house_no) & 3]).player_ID);
                        leaflet.header.recipient.type = mMl_NAME_TYPE_PLAYER;

                        mMl_copy_mail(Save_Get(homes[house_no]).mailbox + free_mail_idx, &leaflet);
                    }

                    break;
                }
            }
        }
    }
}

extern void mSP_SetShopRareFurnitureLeaflet(int player_no, mActor_name_t* goods_list, int goods_count, GAME* game) {
    const int p = player_no;

    if (p >= 0 && p < mPr_FOREIGNER) {
        int shop_level = mSP_GetShopLevel();
        mActor_name_t rare_item = EMPTY_NO;
        int arrange_idx = mHS_get_arrange_idx(p);
        lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

        if (p != mHS_get_pl_no_detail(arrange_idx)) {
            mCkRh_SavePlayTime(p);
            return;
        }

        /* Check if we're on the last day of the month */
        if (Common_Get(time.rtc_time).day ==
            lbRTC_GetDaysByMonth(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month)) {
            mCkRh_SavePlayTime(p);
        } else if (mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == TRUE) {
            mCkRh_SavePlayTime(p); // shop was already 'renewed' today
        } else {
            u16 bargain_day = mEv_get_bargain_day();
            lbRTC_time_c goki_time;
            mHm_hs_c* home;

            if (bargain_day != 0) {
                u32 month = mEv_TO_MONTH(bargain_day);
                u32 day = mEv_TO_DAY(bargain_day);
                if (Common_Get(time.rtc_time).month == month && Common_Get(time.rtc_time).day == day) {
                    mCkRh_SavePlayTime(p); // shop 'bargin' event is active
                    return;
                }
            }

            goki_time = Save_Get(homes[arrange_idx]).goki.time;
            lbRTC_Add_DD(&goki_time, 1);
            home = Save_GetPointer(homes[arrange_idx]);

            /* check if the current date & time is past the renew time */
            if (home->goki.time.year == rtc_time->year && home->goki.time.month == rtc_time->month &&
                home->goki.time.day == rtc_time->day)
                return;

            if (goki_time.year == rtc_time->year && goki_time.month == rtc_time->month &&
                goki_time.day == rtc_time->day && goki_time.hour < mTM_FIELD_RENEW_HOUR)
                return;

            if (rtc_time->hour < mTM_FIELD_RENEW_HOUR || rtc_time->hour > mSP_GetShopCloseTime())
                return;

            if (mSP_SearchItemCategoryPriority(Save_Get(shop).rare_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, game)) {
                rare_item = Save_Get(shop).rare_item;
            } else {
                int i;

                /* spotlight item in shop wasn't the rare item, so check all
                 * the goods for one */
                for (i = 0; i < goods_count; i++) {
                    if (mSP_ItemNo2GoodsListCategory(goods_list[i]) == mSP_KIND_FURNITURE) {
                        int is_rare_item =
                            mSP_SearchItemCategoryPriority(goods_list[i], mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, game);

                        if (is_rare_item != FALSE) {
                            rare_item = goods_list[i];

                            break;
                        }
                    }
                }
            }

            /* check if a rare item was found, and if so, send the notice
             * leaflet to the player */
            if (rare_item != EMPTY_NO) {
                int arrange_idx = mHS_get_arrange_idx(p);

                if (mHS_get_pl_no_detail(arrange_idx) != -1) {
                    mSP_ShopRareLeaflet(arrange_idx, shop_level, rare_item, mPO_SENDTYPE_LEAFLET);
                    mCkRh_SavePlayTime(p);
                }
            }
        }
    }
}

extern void mSP_SetRenewalLeaflet_AppoDay() {
    static int leaflet_idx_appoday[mSP_SHOP_TYPE_NUM] = { 0x1B, 0x1B, 0x1C, 0x1D };
    Mail_c leaflet;
    Mail_ct_c* content = &leaflet.content;
    int header_back_start;

    if (Save_Get(shop).shop_info.upgrading_today && mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == FALSE) {
        int shop_level = mSP_GetRealShopLevel();
        int i;

        for (i = 0; i < mHS_HOUSE_NUM; i++) {
            int player_no = mHS_get_pl_no(i) & 3;
            int free_mail_idx = mMl_chk_mail_free_space(Save_Get(homes[i]).mailbox, HOME_MAILBOX_SIZE);

            if (free_mail_idx >= 0 && Save_Get(homes[i]).ownerID.land_id != 0xFFFF &&
                mEv_ArbeitPlayer(player_no) == FALSE) {

                mMl_clear_mail(&leaflet);
                mHandbill_Load_HandbillFromRom(content->text.split.header, &header_back_start,
                                               content->text.split.footer, content->text.split.body,
                                               leaflet_idx_appoday[shop_level]);
                leaflet.content.font = mMl_FONT_RECV;
                leaflet.content.header_back_start = header_back_start;
                leaflet.content.mail_type = mMl_TYPE_SHOP_SALE_LEAFLET;
                leaflet.content.paper_type = (u8)ITM_PAPER55; // simple paper

                mPr_CopyPersonalID(&leaflet.header.recipient.personalID,
                                   &Save_Get(private_data[mHS_get_pl_no(i) & 3]).player_ID);
                leaflet.header.recipient.type = mMl_NAME_TYPE_PLAYER;

                mMl_copy_mail(Save_Get(homes[i]).mailbox + free_mail_idx, &leaflet);
            }
        }

        Save_Get(shop).shop_info.upgrading_today = FALSE;
    }
}

extern void mSP_ExchangeLineUp_InGame(GAME* game) {
    if (mSP_CheckExchangeDay2()) {
        if (mSP_CheckExchangeMonth()) {
            mSP_LotteryLineUp_GameAlloc(game);
        }

        mSP_NewExchangeDay();
        mSP_ExchangeLineUp_GameAlloc(game);
        Save_Get(shop).shop_info.not_loaded_before = TRUE;
        mSP_SetShopRareFurnitureLeaflet(Common_Get(player_no), Save_Get(shop).items, mSP_GOODS_COUNT, game);
    }
}

extern void mSP_PlusSales(u32 sum) {
    Save_Get(shop).sales_sum += sum;

    if (mSP_GetShopLevel() == mSP_SHOP_TYPE_ZAKKA) {
        if (Save_Get(shop).sales_sum > mSP_COMBINI_SUM) {
            Save_Get(shop).sales_sum = mSP_COMBINI_SUM;
        }
    } else if (mSP_GetShopLevel() == mSP_SHOP_TYPE_COMBINI) {
        if (Save_Get(shop).sales_sum > mSP_SUPER_SUM) {
            Save_Get(shop).sales_sum = mSP_SUPER_SUM;
        }
    } else if (mSP_GetShopLevel() == mSP_SHOP_TYPE_SUPER) {
        if (Save_Get(shop).sales_sum > mSP_DSUPER_SUM) {
            Save_Get(shop).sales_sum = mSP_DSUPER_SUM;
        }
    }
}

/* @unused size: 0x74 */
// extern int mSP_GetVisitorCount()

extern int mSP_SetNewVisitor() {
    if (mLd_PlayerManKindCheck()) {
        Save_Get(shop).visitor_flag = TRUE;
        return TRUE;
    }

    return FALSE;
}

extern u32 mSP_GetSalesSum() {
    return Save_Get(shop).sales_sum;
}

extern int mSP_GetShopLevel() {
    return Save_Get(shop).shop_info.shop_level;
}

extern int mSP_RenewShopLevel() {
    if (Save_Get(shop).shop_info.shop_level != (u8)mSP_GetRealShopLevel()) {
        Save_Get(shop).shop_info.shop_level = mSP_GetRealShopLevel();
        return TRUE;
    }

    return FALSE;
}

extern int mSP_GetRealShopLevel() {
    u32 sales_sum = mSP_GetSalesSum();

    if (sales_sum >= mSP_DSUPER_SUM && Save_Get(shop).visitor_flag != FALSE) {
        return mSP_SHOP_TYPE_DSUPER;
    } else if (sales_sum >= mSP_SUPER_SUM) {
        return mSP_SHOP_TYPE_SUPER;
    }

    return sales_sum >= mSP_COMBINI_SUM ? mSP_SHOP_TYPE_COMBINI : mSP_SHOP_TYPE_ZAKKA;
}

extern int mSP_GetGoodsPercent(int priority) {
    int goods_power = mPr_GetGoodsPower();

    if (priority >= 0 && priority <= mSP_PRIORITY_RARE) {
        int rare;
        int uncommon;

        if (goods_power < 0) {
            uncommon = goods_power + 35 + 5;
            rare = 5;
        } else {
            rare = goods_power + 5;
            uncommon = rare + 35;
        }

        switch (priority) {
            case mSP_PRIORITY_COMMON:
                return 100 - uncommon;
            case mSP_PRIORITY_UNCOMMON:
                return uncommon - rare;
            case mSP_PRIORITY_RARE:
                return rare;
            default:
                return 0;
        }
    } else {
        return 0;
    }
}

extern void mSP_PrintNowShopSalesSum(gfxprint_t* gfxprint) {
    if (mFI_CheckFieldData()) {
        int shop_level = mSP_GetShopLevel();
        int status = mSP_ShopOpen();
        u32 sales_sum = mSP_GetSalesSum();
        u32 working_sum;

        switch (shop_level) {
            case mSP_SHOP_TYPE_ZAKKA:
                working_sum = sales_sum;
                break;
            case mSP_SHOP_TYPE_COMBINI:
                working_sum = sales_sum - mSP_COMBINI_SUM;
                break;
            case mSP_SHOP_TYPE_SUPER:
                working_sum = sales_sum - mSP_SUPER_SUM;
                break;
            default:
                working_sum = sales_sum - mSP_DSUPER_SUM;
                break;
        }

        gfxprint_color(gfxprint, 200, 200, 250, 255);
        gfxprint_locate8x8(gfxprint, 3, 12);

        if (mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == FALSE) {
            gfxprint_printf(gfxprint, "%d %d %s", shop_level, working_sum, mSP_ShopStatus2String(status));

            gfxprint_color(gfxprint, 200, 200, 250, 255);
            gfxprint_printf(gfxprint, "A%2d,%2d,%2d,%2d,%2d",
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_FURNITURE].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_WALLPAPER].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CARPET].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CLOTH].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_PAPER].a));
        } else {
            gfxprint_color(gfxprint, 200, 100, 100, 255);
            gfxprint_printf(gfxprint, "%d %d %s->%d.%d.%d", shop_level, working_sum, mSP_ShopStatus2String(status),
                            Save_Get(shop).renewal_time.year, Save_Get(shop).renewal_time.month,
                            Save_Get(shop).renewal_time.day);

            gfxprint_color(gfxprint, 200, 200, 250, 255);
            gfxprint_printf(gfxprint, " A%2d,%2d,%2d,%2d,%2d",
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_FURNITURE].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_WALLPAPER].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CARPET].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CLOTH].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_PAPER].a));
        }

        gfxprint_color(gfxprint, 200, 200, 250, 255);
        gfxprint_locate8x8(gfxprint, 3, 13);
        gfxprint_printf(gfxprint, "B%2d,%2d,%2d,%2d,%2d",
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_FURNITURE].b),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_WALLPAPER].b),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CARPET].b),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CLOTH].b),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_PAPER].b));
        gfxprint_printf(gfxprint, "C%2d,%2d,%2d,%2d,%2d",
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_FURNITURE].c),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_WALLPAPER].c),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CARPET].c),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CLOTH].c),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_PAPER].c));
    }
}

extern void mSP_GetListPriorityABC(u8* abc_priorities, int category) {
    mSP_goods_priority_list_c* priorities = Save_Get(shop).priority_lists;

    abc_priorities[0] = priorities[category].a;
    abc_priorities[1] = priorities[category].b;
    abc_priorities[2] = priorities[category].c;
}

static void mSP_SetExchangeDay() {
    Save_Get(shop).exchange_time = Common_Get(time.rtc_time);
}

static void mSP_InitGoods() {
    Shop_c* shop = Save_GetPointer(shop);
    mActor_name_t* items = shop->items;
    int i;

    for (i = 0; i < mSP_GOODS_COUNT; i++) {
        *items++ = EMPTY_NO;
    }
}

static void mSP_InitEventGoods(void) {
    Shop_c* shop = Save_GetPointer(shop);
    mActor_name_t* event_goods = shop->event_goods;
    int i;

    for (i = 0; i < mSP_GOODS_COUNT; i++) {
        *event_goods++ = EMPTY_NO;
    }
}

extern void mSP_ExchangeLineUp_ZeldaMalloc() {
    mSP_InitGoods();
    mSP_MakeGoodsList(NULL);
    mSP_SetExchangeDay();
}

extern void mSP_LotteryLineUp_ZeldaMalloc() {
    mSP_MakeLotteryList(NULL);
}

extern void mSP_ExchangeLineUp_GameAlloc(GAME* game) {
    mSP_InitGoods();
    mSP_MakeGoodsList(game);
    mSP_SetExchangeDay();
}

extern void mSP_LotteryLineUp_GameAlloc(GAME* game) {
    mSP_MakeLotteryList(game);
}

extern void mSP_InitShopSaveData() {
    Shop_c* shop = Save_GetPointer(shop);
    mActor_name_t* lottery_items = shop->lottery_items;
    int i = 0;

    mPr_ClearPersonalID(&shop->unused_id);
    mSP_InitGoods();
    Save_Get(shop).rare_item = EMPTY_NO;

    for (i = 0; i < mSP_LOTTERY_ITEM_COUNT; i++) {
        lottery_items[0] = EMPTY_NO;
        lottery_items++;
    }

    Save_Get(shop).flowers_candy_grab_bag_count = 0;
    shop->sales_sum = 0;
    shop->exchange_time = Common_Get(time.rtc_time);
    shop->exchange_time.month--;
    shop->shop_info.shop_level = mSP_SHOP_TYPE_ZAKKA;
    shop->renewal_time = shop->exchange_time;
    shop->shop_info.upgrading_today = FALSE;
    Save_Get(shop).visitor_flag = FALSE;
}

static void mSP_DecideUniqueCommonList(mSP_goods_priority_list_c* priority_list) {
    static mSP_goods_priority_list_c priority_candidate[6] = {
        { mSP_PRIORITY_COMMON, mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_RARE, 0 },
        { mSP_PRIORITY_COMMON, mSP_PRIORITY_RARE, mSP_PRIORITY_UNCOMMON, 0 },
        { mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_COMMON, mSP_PRIORITY_RARE, 0 },
        { mSP_PRIORITY_RARE, mSP_PRIORITY_COMMON, mSP_PRIORITY_UNCOMMON, 0 },
        { mSP_PRIORITY_RARE, mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_COMMON, 0 },
        { mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_RARE, mSP_PRIORITY_COMMON, 0 }
    };

    priority_list[0] = priority_candidate[RANDOM(6)];
}

static void mSP_DecideGoodsCommonList() {
    mSP_goods_priority_list_c* priority_lists = Save_Get(shop).priority_lists;

    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_FURNITURE]);
    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_PAPER]);
    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_CLOTH]);
    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_CARPET]);
    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_WALLPAPER]);

    // @BUG - diaries are not rolled but have been given a shop kind
}

extern void mSP_ShopGameStartCt(GAME* game) {
    mSP_DecideGoodsCommonList();
    mSP_InitShopSaveData();
    mSP_ExchangeLineUp_InGame(game);
}

extern mActor_name_t mSP_GetNowShopBgNum() {
    switch (Save_Get(scene_no)) {
        case SCENE_SHOP0: {
            if (mSP_force_opend() == FALSE && Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return BG_TYPE_ROM_SHOP1_FUKU;
            }

            return BG_TYPE_ROM_SHOP1;
        }

        case SCENE_CONVENI: {
            if (mSP_force_opend() == FALSE && Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return BG_TYPE_ROM_SHOP2_FUKU;
            }

            return BG_TYPE_ROM_SHOP2;
        }

        case SCENE_SUPER: {
            if (mSP_force_opend() == FALSE && Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return BG_TYPE_ROM_SHOP3_FUKU;
            }

            return BG_TYPE_ROM_SHOP3;
        }

        case SCENE_DEPART: {
            if (mSP_force_opend() == FALSE && Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return BG_TYPE_ROM_SHOP4_FUKU;
            }

            return BG_TYPE_ROM_SHOP4_1;
        }

        case SCENE_DEPART_2:
            return BG_TYPE_ROM_SHOP4_2;

        default:
            return BG_TYPE_ROM_SHOP2;
    }
}

static int mSP_what_special_sale;

extern int mSP_WhatSpecialSale() {
    return mSP_what_special_sale;
}

extern mActor_name_t mSP_GetNowShopFgNum() {
    int event_kind = Save_Get(event_save_data).special.event.bargin.kind;

    switch (Save_Get(scene_no)) {
        case SCENE_SHOP0: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return FG_TYPE_ROM_SHOP1_FUKU;
            }

            return FG_TYPE_ROM_SHOP1;
        }

        case SCENE_CONVENI: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return FG_TYPE_ROM_SHOP2_FUKU;
            }

            return FG_TYPE_ROM_SHOP2;
        }

        case SCENE_SUPER: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return FG_TYPE_ROM_SHOP3_FUKU;
            }

            return FG_TYPE_ROM_SHOP3;
        }

        case SCENE_DEPART: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return FG_TYPE_ROM_SHOP4_1_FUKU;
            }

            return FG_TYPE_ROM_SHOP4_1;
        }

        case SCENE_DEPART_2: {
            return FG_TYPE_ROM_SHOP4_2;
        }

        default:
            return FG_TYPE_ROM_SHOP4_1;
    }
}

extern lbRTC_hour_t mSP_GetShopOpenTime() {
    static lbRTC_hour_t shop_open_time_table[mSP_SHOP_TYPE_NUM] = { 9, 7, 9, 9 };

    int shop_level = mSP_GetShopLevel();

    if (Common_Get(time.rtc_time).day ==
        lbRTC_GetDaysByMonth(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month)) {
        return 10; // lottery starts at 10AM
    } else {
        return shop_open_time_table[shop_level];
    }
}

extern lbRTC_hour_t mSP_GetShopCloseTime() {
    static lbRTC_hour_t shop_close_time_table[mSP_SHOP_TYPE_NUM] = { 22, 23, 22, 22 };

    return shop_close_time_table[mSP_GetShopLevel()];
}

extern lbRTC_hour_t mSP_GetShopCloseTime_Bgm() {
    static lbRTC_hour_t shop_close_time_table[mSP_SHOP_TYPE_NUM] = { 22, 23, 22, 22 };

    return shop_close_time_table[mSP_GetShopLevel()];
}

extern int mSP_InRenewal() {
    if (mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == TRUE) {
        lbRTC_time_c renew_time = Save_Get(shop).renewal_time;
        lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

        lbRTC_Sub_DD(&renew_time, 1);

        if (lbRTC_IsOverTime(&renew_time, rtc_time) == lbRTC_OVER ||
            lbRTC_IsEqualTime(rtc_time, &renew_time, lbRTC_CHECK_YEARS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_DAYS) !=
                FALSE) {
            return TRUE;
        }
    }

    return FALSE;
}

/* @unused size: 0xF0 */
// int mSP_CheckSpecialSalesSoldOut(...)

extern int mSP_ShopOpen() {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_hour_t now_hour = rtc_time.hour;

    if (mEv_CheckFirstJob()) {
        return mSP_SHOP_STATUS_OPEN; // shop is forcefully open during chores
    }

    if (mEv_CheckEvent(mEv_SPNPC_SHOP) == TRUE) {
        lbRTC_time_c bargin_time = Save_Get(event_save_data).special.event.bargin.start_time;

        if (bargin_time.day == rtc_time.day) {
            lbRTC_time_c end_time = Save_Get(event_save_data).special.event.bargin.end_time;
            lbRTC_time_c start_time_pre = bargin_time;
            lbRTC_time_c end_time_post = end_time;
            now_hour = rtc_time.hour;

            lbRTC_Sub_hh(&start_time_pre, 1);
            lbRTC_Add_hh(&end_time_post, 1);

            if (now_hour >= mTM_FIELD_RENEW_HOUR && now_hour < mSP_GetShopOpenTime()) {
                return mSP_SHOP_STATUS_PRE;
            }

            if (now_hour < mTM_FIELD_RENEW_HOUR || now_hour >= mSP_GetShopCloseTime()) {
                return mSP_SHOP_STATUS_END;
            }

            if (lbRTC_IsOverTime(&start_time_pre, &rtc_time) == lbRTC_LESS) {
                return mSP_SHOP_STATUS_OPEN;
            }

            if (lbRTC_IsOverTime(&bargin_time, &rtc_time) == lbRTC_LESS) {
                return mSP_SHOP_STATUS_PREEVENT;
            }

            if (lbRTC_IsOverTime(&end_time, &rtc_time) == lbRTC_LESS) {
                return mSP_SHOP_STATUS_OPENEVENT;
            }

            if (lbRTC_IsOverTime(&end_time_post, &rtc_time) == lbRTC_LESS) {
                return mSP_SHOP_STATUS_ENDEVENT;
            }

            return mSP_SHOP_STATUS_OPEN;
        }
    }

    if (mSP_InRenewal() != FALSE) {
        return mSP_SHOP_STATUS_RENEW;
    }

    if (now_hour >= mSP_GetShopOpenTime() && now_hour < mSP_GetShopCloseTime()) {
        return mSP_SHOP_STATUS_OPEN;
    }

    if (now_hour >= mTM_FIELD_RENEW_HOUR && now_hour < mSP_GetShopOpenTime()) {
        return mSP_SHOP_STATUS_PRE;
    }

    if (Common_Get(shop_force_open_door_flag) == TRUE &&
        (now_hour >= mSP_GetShopCloseTime() || now_hour < (mTM_FIELD_RENEW_HOUR - 1))) {
        return mSP_SHOP_STATUS_OPEN;
    }

    return mSP_SHOP_STATUS_END;
}

typedef mActor_name_t (*mSP_get_random_item_common_func_t)(int idx);

static void mSP_get_random_item_common(mActor_name_t* item_list, int count, int max_idx,
                                       mSP_get_random_item_common_func_t get_item_func) {
    int i;

    for (i = 0; i < count; i++) {
        item_list[i] = EMPTY_NO;
    }

    if (max_idx != 0) {
        for (i = 0; i < count; i++) {
            int set = FALSE;

            while (!set) {
                mActor_name_t item = get_item_func(RANDOM(max_idx));

                if (!mSP_GoodsExistAlready(item_list, count, item)) {
                    item_list[i] = item;
                    set = TRUE;
                } else if (count > max_idx) {
                    item_list[i] = item;
                    set = TRUE;
                }
            }
        }
    }
}

static mActor_name_t mSP_haniwa_idx_to_item(int idx) {
    return HANIWA_START + (mActor_name_t)FTR_NO_2_IDX(idx);
}

/**
 * @brief Select random haniwa items
 * @param haniwa_list Output list for haniwa items
 * @param count Number of haniwa to select
 *
 * Selects random haniwa items, avoiding duplicates when possible.
 * If count exceeds available haniwa, allows duplicates.
 */
extern void mSP_RandomHaniwaSelect(mActor_name_t* haniwa_list, int count) {
    mSP_get_random_item_common(haniwa_list, count, HANIWA_NUM, mSP_haniwa_idx_to_item);
}

static mActor_name_t mSP_windmill_idx_to_item(int idx) {
    return ITM_YELLOW_PINWHEEL + (idx & 7);
}

extern void mSP_RandomWindMillSelect(mActor_name_t* item_list, int count) {
    mSP_get_random_item_common(item_list, count, 8, mSP_windmill_idx_to_item);
}

static mActor_name_t mSP_fan_idx_to_item(int idx) {
    return ITM_BLUEBELL_FAN + (idx & 7);
}

extern void mSP_RandomFanSelect(mActor_name_t* item_list, int count) {
    mSP_get_random_item_common(item_list, count, 8, mSP_fan_idx_to_item);
}

static mActor_name_t mSP_balloon_idx_to_item(int idx) {
    return (mActor_name_t)mNT_ftr_idx_to_ftr_item_no(FTR_NOG_BALLOON_COMMON0 + (idx & 7), mRmTp_DIRECT_SOUTH);
}

extern void mSP_RandomBalloonSelect(mActor_name_t* item_list, int count) {
    mSP_get_random_item_common(item_list, count, 8, mSP_balloon_idx_to_item);
}

static mActor_name_t mSP_umb_idx_to_item(int idx) {
    return ITM_UMBRELLA00 + idx;
}

/**
 * @brief Select random umbrella items
 * @param umb_list Output list for umbrellas
 * @param count Number of umbrellas to select
 *
 * Selects random umbrellas, avoiding duplicates when possible.
 * If count exceeds available umbrellas, allows duplicates.
 */
extern void mSP_RandomUmbSelect(mActor_name_t* item_list, int count) {
    mSP_get_random_item_common(item_list, count, UMBRELLA_NUM, mSP_umb_idx_to_item);
}

extern mActor_name_t mSP_GetRandomStationToyItemNo() {
    static mActor_name_t train[2] = { FTR_START(FTR_IKE_K_KID01), FTR_START(FTR_IKE_K_KID02) };

    return mNT_ftr_idx_to_ftr_item_no(FTR_NOG_STATION00 + RANDOM(15), mRmTp_DIRECT_SOUTH);
}

static int mSP_CountBirth(u8 birth_type) {
    int count = 0;
    u8* birth_type_p = mRmTp_CheckFtrBirthInfoTop();
    int i;

    for (i = 0; i < FTR_NUM; i++) {
        if (birth_type_p[0] == birth_type) {
            count++;
        }

        birth_type_p++;
    }

    return count;
}

static mActor_name_t mSP_FtrBirthIdx2ItemNo(u8 birth_type, int birth_idx) {
    int count = 0;
    u8* birth_type_p = mRmTp_CheckFtrBirthInfoTop();
    int i;

    for (i = 0; i < FTR_NUM; i++) {
        if (birth_type_p[0] == birth_type) {
            if (count == birth_idx) {
                return mNT_ftr_idx_to_ftr_item_no(i, mRmTp_DIRECT_SOUTH);
            }

            count++;
        }

        birth_type_p++;
    }

    return FTR_START(FTR_DIN_TREX_HEAD);
}

extern mActor_name_t mSP_RandomOneFossilSelect(int multi_fossil) {
    u8 birth_type = multi_fossil == FALSE ? mRmTp_BIRTH_TYPE_SINGLE_FOSSIL : mRmTp_BIRTH_TYPE_MULTI_FOSSIL;
    int count = mSP_CountBirth(birth_type);

    return mSP_FtrBirthIdx2ItemNo(birth_type, RANDOM(count));
}

extern int mSP_CheckFukubikiDay() {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_year_t year = rtc_time.year;
    lbRTC_month_t month = rtc_time.month;
    lbRTC_day_t day = rtc_time.day;
    lbRTC_day_t days_in_month = lbRTC_GetDaysByMonth(year, month);

    return days_in_month == day;
}

extern int mSP_SetGoods2ReservedPoint(mActor_name_t goods, mActor_name_t reserved_no) {
    mActor_name_t* shop_fg = mFI_BkNumtoUtFGTop(0, 0);
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (reserved_no == shop_fg[0]) {
            mFI_UtNumtoFGSet_common(goods, i % UT_X_NUM, i / UT_X_NUM, FALSE);
            return TRUE;
        }

        shop_fg++;
    }

    return FALSE;
}

extern int mSP_Chk_HukubukuroSail() {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_year_t year = rtc_time.year;
    lbRTC_month_t month = rtc_time.month;
    lbRTC_day_t day = rtc_time.day;

    if (month == lbRTC_NOVEMBER) {
        int black_friday = lbRTC_Weekly_day(year, lbRTC_NOVEMBER, 4, lbRTC_THURSDAY) + 1;

        if (black_friday == day) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mSP_CheckHallowinDay() {
    int res = FALSE;
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_month_t month = rtc_time.month;
    lbRTC_day_t day = rtc_time.day;

    if (month == lbRTC_OCTOBER && day >= 16 && day <= 30) {
        res = TRUE;
    }

    return res;
}

extern int mSP_CheckCrackerDay(void) {
    int res = FALSE;
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_month_t month = rtc_time.month;
    lbRTC_day_t day = rtc_time.day;

    if (month == lbRTC_DECEMBER && day >= 16 && day <= 30) {
        res = TRUE;
    }

    return res;
}

extern int mSP_CheckShopNormalStatus_Quest(void) {
    int open_type = mSP_ShopOpen();

    if (mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == TRUE || mEv_CheckEvent(mEv_SPNPC_SHOP) == TRUE ||
        mSP_CheckFukubikiDay() || mSP_Chk_HukubukuroSail() || mSP_CheckHallowinDay() || mSP_CheckCrackerDay()) {
        return FALSE;
    }

    if (open_type == mSP_SHOP_STATUS_PRE || open_type == mSP_SHOP_STATUS_END || open_type == mSP_SHOP_STATUS_RENEW) {
        return FALSE;
    }

    return TRUE;
}

extern void mSP_SetTanukiShopStatus() {
    if (mSP_ShopOpen() == mSP_SHOP_STATUS_OPENEVENT) {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_EVENT);
    } else if (mSP_CheckFukubikiDay()) {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_FUKUBIKI);
    } else if (mSP_Chk_HukubukuroSail()) {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_HUKUBUKURO_SALE);
    } else if (mSP_CheckHallowinDay()) {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_HALLOWEEN);
    } else if (mSP_CheckCrackerDay()) {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_CRACKER);
    } else {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_NORMAL);
    }

    if (Common_Get(shop_force_open_door_flag) == TRUE) {
        Common_Set(shop_force_opend, TRUE);
    } else {
        Common_Set(shop_force_opend, FALSE);
    }
}

static u32 mSP_sack_amount[MONEY_NUM] = { 100, 1000, 10000, 30000 };

static mActor_name_t mSP_itemNo[MONEY_NUM] = { ITM_MONEY_100, ITM_MONEY_1000, ITM_MONEY_10000, ITM_MONEY_30000 };

extern int mSP_money_check(u32 amount) {
    u32 money = Common_Get(now_private)->inventory.wallet;
    int res = FALSE;

    if (money < amount) {
        int i;

        for (i = 0; i < MONEY_NUM; i++) {
            int sack_num =
                mPr_GetPossessionItemSumWithCond(Common_Get(now_private), mSP_itemNo[i], mPr_ITEM_COND_NORMAL);

            money += sack_num * mSP_sack_amount[i];
            if (money >= amount) {
                res = TRUE;
                break;
            }
        }
    } else {
        res = TRUE;
    }

    return res;
}

static u32 mSP_get_sell_price_sub(u32 money, u32 amount) {
    u32 sack_num;
    int i;

    for (i = 0; i < MONEY_NUM; i++) {
        for (sack_num = mPr_GetPossessionItemSumWithCond(Common_Get(now_private), mSP_itemNo[i], mPr_ITEM_COND_NORMAL);
             sack_num != 0; sack_num--) {
            int sack_idx =
                mPr_GetPossessionItemIdxWithCond(Common_Get(now_private), mSP_itemNo[i], mPr_ITEM_COND_NORMAL);

            mPr_SetPossessionItem(Common_Get(now_private), sack_idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
            money += mSP_sack_amount[i];

            if (money >= amount) {
                return money - amount;
            }
        }
    }

    return 0;
}

extern void mSP_get_sell_price(u32 amount) {
    u32 money = Common_Get(now_private)->inventory.wallet;

    if (money < amount) {
        money = mSP_get_sell_price_sub(money, amount);
    } else {
        money -= amount;
    }

    Common_Get(now_private)->inventory.wallet = money;
}

static int mSP_GetNonePossessionItemCount_InList(mActor_name_t* list, int category, u32* collect_bitfield) {
    mActor_name_t* list_p;

    if (list != NULL) {
        int count = 0;

        for (list_p = list; list_p[0] != EMPTY_NO; list_p++) {
            int collect_idx;

            if (category == mSP_KIND_FURNITURE) {
                collect_idx = mNT_ftr_item_no_to_ftr_idx(list_p[0]);
            } else if (category == mSP_KIND_CARPET) {
                collect_idx = list_p[0] - ITM_CARPET_START;
            } else {
                collect_idx = list_p[0] - ITM_WALL_START;
            }

            if (((collect_bitfield[collect_idx >> 5] >> (collect_idx & 0x1F)) & 1) == 0) {
                count++;
            }
        }

        return count;
    }

    return 0;
}

static mActor_name_t mSP_GetNonePossessionItem_InList(mActor_name_t* list, int category, u32* collect_bitfield) {
    int none_count = mSP_GetNonePossessionItemCount_InList(list, category, collect_bitfield);

    if (none_count != 0 && list != NULL) {
        int selected_idx = RANDOM(none_count);
        mActor_name_t* list_p;
        int count = 0;

        for (list_p = list; list_p[0] != EMPTY_NO; list_p++) {
            int collect_idx;

            if (category == mSP_KIND_FURNITURE) {
                collect_idx = mNT_ftr_item_no_to_ftr_idx(list_p[0]);
            } else if (category == mSP_KIND_CARPET) {
                collect_idx = list_p[0] - ITM_CARPET_START;
            } else {
                collect_idx = list_p[0] - ITM_WALL_START;
            }

            if (((collect_bitfield[collect_idx >> 5] >> (collect_idx & 0x1F)) & 1) == 0) {
                if (selected_idx == count) {
                    return list_p[0];
                } else {
                    count++;
                }
            }
        }
    }

    return EMPTY_NO;
}

static mActor_name_t mSP_GetNonePossessionItem_InLotteryFurniture(int player_no) {
    return mSP_GetNonePossessionItem_InList(mSP_ftr_list[mSP_LIST_LOTTERY], mSP_KIND_FURNITURE,
                                            (player_no >= 0 && player_no < PLAYER_NUM)
                                                ? Save_Get(private_data[player_no]).furniture_collected_bitfield
                                                : Common_Get(now_private)->furniture_collected_bitfield);
}

static mActor_name_t mSP_GetNonePossessionItem_InEventFurniture(int player_no) {
    return mSP_GetNonePossessionItem_InList(mSP_ftr_list[mSP_LIST_EVENT], mSP_KIND_FURNITURE,
                                            (player_no >= 0 && player_no < PLAYER_NUM)
                                                ? Save_Get(private_data[player_no]).furniture_collected_bitfield
                                                : Common_Get(now_private)->furniture_collected_bitfield);
}

typedef mActor_name_t (*mSP_GET_NONE_POSSESSION_ITEM_PROC)(int);

static mActor_name_t mSP_CarryOutAlternativeRandomSelect(mSP_GET_NONE_POSSESSION_ITEM_PROC proc0,
                                                         mSP_GET_NONE_POSSESSION_ITEM_PROC proc1, int player_no) {
    int rng = RANDOM(100);

    if ((rng & 1)) {
        mActor_name_t item = (*proc0)(player_no);

        if (item == EMPTY_NO) {
            item = (*proc1)(player_no);

            if (item != EMPTY_NO) {
                return item;
            }
        } else {
            return item;
        }
    } else {
        mActor_name_t item = (*proc1)(player_no);

        if (item == EMPTY_NO) {
            item = (*proc0)(player_no);

            if (item != EMPTY_NO) {
                return item;
            }
        } else {
            return item;
        }
    }

    return EMPTY_NO;
}

static mActor_name_t mSP_CarryOutAlternativeRandomSelect_NoneNULL(int category0, int list0, int category1, int list1) {
    int rng = RANDOM(100);
    mActor_name_t item;

    if ((rng & 1)) {
        mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, category0, list0, FALSE);
        return item;
    } else {
        mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, category1, list1, FALSE);
        return item;
    }
}

/* @unused size: 0xB8 */
// extern mActor_name_t mSP_SelectNpcBirthdayPresent(...)
static void mSP_SelectNpcBirthdayPresent() {
    // necessary to include for data
    static int priority[6][3] = {
        { mSP_PRIORITY_COMMON, mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_RARE },
        { mSP_PRIORITY_COMMON, mSP_PRIORITY_RARE,
          mSP_PRIORITY_RARE }, // lol based on this, I think it should've been common, rare, uncommon
        { mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_COMMON, mSP_PRIORITY_RARE },
        { mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_RARE, mSP_PRIORITY_COMMON },
        { mSP_PRIORITY_RARE, mSP_PRIORITY_COMMON, mSP_PRIORITY_UNCOMMON },
        { mSP_PRIORITY_RARE, mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_COMMON }
    };
}

extern mActor_name_t mSP_SelectFishingPresent(int player_no) {
    mActor_name_t item = mSP_CarryOutAlternativeRandomSelect(&mSP_GetNonePossessionItem_InLotteryFurniture,
                                                             &mSP_GetNonePossessionItem_InEventFurniture, player_no);

    if (item != EMPTY_NO) {
        return item;
    }

    return mSP_CarryOutAlternativeRandomSelect_NoneNULL(mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY, mSP_KIND_FURNITURE,
                                                        mSP_LISTTYPE_EVENT);
}

mActor_name_t mSP_gc_famicom_table[] = {
    FTR_START(FTR_FAMICOM_COMMON00), FTR_START(FTR_FAMICOM_COMMON01), FTR_START(FTR_FAMICOM_COMMON02),
    FTR_START(FTR_FAMICOM_COMMON03), FTR_START(FTR_FAMICOM_COMMON04), FTR_START(FTR_FAMICOM_COMMON05),
    FTR_START(FTR_FAMICOM_COMMON06), FTR_START(FTR_FAMICOM_COMMON13), FTR_START(FTR_FAMICOM_COMMON09),
    FTR_START(FTR_FAMICOM_COMMON11), FTR_START(FTR_FAMICOM_COMMON12),
};

extern const char* mSP_ShopStatus2String(int status) {
    static char dummy[] = "hahaha";

    static char* str_table[mSP_SHOP_STATUS_NUM] = { "Pre", "End", "Opn", "Rnw", "PreEv", "EndEv", "OpnEv" };

    if (status >= 0 && status < mSP_SHOP_STATUS_NUM) {
        return str_table[status];
    }

    return dummy;
}

extern int mSP_GetBargainNum(int category, int shop_level) {
    static u8 ftr_num_table[4] = { 1, 2, 4, 5 };
    static u8 carpet_num_table[4] = { 1, 1, 2, 3 };
    static u8 wall_num_table[4] = { 1, 1, 2, 3 };
    static u8 cloth_num_table[4] = { 1, 2, 3, 5 };
    static u8 cracker_goods[4] = { 3, 4, 4, 5 };
    static u8 windmill_goods[4] = { 1, 2, 3, 4 };
    static u8 fan_goods[4] = { 1, 2, 3, 4 };
    static u8 balloon_goods[4] = { 1, 1, 3, 5 };

    static u8* item_num_table[8] = {
        ftr_num_table,    // mSP_BARGAIN_FTR
        carpet_num_table, // mSP_BARGAIN_CARPET
        wall_num_table,   // mSP_BARGAIN_WALL
        cloth_num_table,  // mSP_BARGAIN_CLOTH
        cracker_goods,    // mSP_BARGAIN_CRACKER
        windmill_goods,   // mSP_BARGAIN_WINDMILL
        fan_goods,        // mSP_BARGAIN_FAN
        balloon_goods,    // mSP_BARGAIN_BALLOON
    };

    return item_num_table[category][shop_level];
}

static void mSP_SetEventGoods(int* count, mActor_name_t* goods_list) {
    mActor_name_t* event_goods = Save_Get(event_save_data).special.event.bargin.items;
    int i;

    for (i = 0; i < mEv_BARGIN_ITEM_NUM && event_goods[i] != EMPTY_NO; i++) {
        goods_list[*count] = event_goods[i];
        (*count)++;
    }
}

extern void mSP_MakeBargainGoods(void) {
    mEv_bargin_c* bargin_p = &Save_Get(event_save_data).special.event.bargin;
    int shop_level = mSP_GetShopLevel();
    mActor_name_t* goods_list = Save_Get(shop).event_goods;
    int count = 0;
    int num;
    int i;

    mSP_InitEventGoods();
    mSP_SetEventGoods(&count, goods_list + count);

    if (bargin_p->kind != mSP_KIND_FURNITURE) {
        num = mSP_GetBargainNum(mSP_BARGAIN_FTR, shop_level);
        mSP_SelectRandomItem_New(NULL, goods_list + count, num, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, FALSE);
        count += num;
    }
    if (bargin_p->kind != mSP_KIND_CLOTH) {
        num = mSP_GetBargainNum(mSP_BARGAIN_CLOTH, shop_level);
        mSP_SelectRandomItem_New(NULL, goods_list + count, num, NULL, 0, mSP_KIND_CLOTH, mSP_LISTTYPE_RARE, FALSE);
        count += num;
    }
    if (bargin_p->kind != mSP_KIND_WALLPAPER) {
        num = mSP_GetBargainNum(mSP_BARGAIN_WALL, shop_level);
        mSP_SelectRandomItem_New(NULL, goods_list + count, num, NULL, 0, mSP_KIND_WALLPAPER, mSP_LISTTYPE_RARE, FALSE);
        count += num;
    }
    if (bargin_p->kind != mSP_KIND_CARPET) {
        num = mSP_GetBargainNum(mSP_BARGAIN_CARPET, shop_level);
        mSP_SelectRandomItem_New(NULL, goods_list + count, num, NULL, 0, mSP_KIND_CARPET, mSP_LISTTYPE_RARE, FALSE);
        count += num;
    }

    num = mSP_GetBargainNum(mSP_BARGAIN_CRACKER, shop_level);
    for (i = 0; i < num; i++) {
        goods_list[count] = ITM_CRACKER;
        count++;
    }

    num = mSP_GetBargainNum(mSP_BARGAIN_WINDMILL, shop_level);
    mSP_RandomWindMillSelect(goods_list + count, num);
    count += num;

    num = mSP_GetBargainNum(mSP_BARGAIN_FAN, shop_level);
    mSP_RandomFanSelect(goods_list + count, num);
    count += num;

    num = mSP_GetBargainNum(mSP_BARGAIN_BALLOON, shop_level);
    mSP_RandomBalloonSelect(goods_list + count, num);
    count += num;

    mSP_RandomUmbSelect(goods_list + count, 1);
}

extern mActor_name_t mSP_get_old_password_furniture(void) {
    static mActor_name_t oldpasswd_table[] = { FTR_START(FTR_NOG_SIGNATURE), FTR_START(FTR_NOG_DISH),
                                               FTR_START(FTR_NOG_BILLBOARD) };

    return oldpasswd_table[RANDOM(ARRAY_COUNT(oldpasswd_table))];
}

extern int mSP_get_no_use_num(u32* use_bitfield, int count) {

    if (use_bitfield != NULL) {
        int i;
        int no_use_num = 0;

        for (i = 0; i < count; i++) {
            if (((use_bitfield[i >> 5] >> (i & 31)) & 1) == 0) {
                no_use_num++;
            }
        }

        return no_use_num;
    }

    return 0;
}

extern void mSP_set_use(u32* use_bitfield, int idx, int count) {
    if (use_bitfield != NULL) {
        int i;
        int shift;
        int no_use_num = 0;

        for (i = 0; i < count; i++) {
            shift = i & 31;
            if (((use_bitfield[i >> 5] >> shift) & 1) == 0) {
                if (no_use_num == idx) {
                    use_bitfield[i >> 5] |= 1 << shift;
                }

                no_use_num++;
            }
        }
    }
}

extern mActor_name_t mSP_GetRandomItemABC(const int* kinds, const int kind_count) {
    u32 use_bitfield = 0;
    mActor_name_t item;
    int selected;
    int no_use_num;
    int i = 0;

    while (i++ < kind_count) {
        no_use_num = mSP_get_no_use_num(&use_bitfield, kind_count);
        if (no_use_num > 0) {
            selected = RANDOM(no_use_num);
            mSP_set_use(&use_bitfield, selected, kind_count);
            mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, kinds[selected], mSP_LISTTYPE_ABC, TRUE);

            if (item != EMPTY_NO) {
                return item;
            }
        }
    }

    mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, kinds[RANDOM(kind_count)], mSP_LISTTYPE_ABC, FALSE);
    return item;
}

typedef struct shop_check_door_work_s {
    ACTOR* shop_actor;
    xyz_t pos;
    int hit_count;
    u32 open_timer;
} mSP_check_door_work_c;

static mSP_check_door_work_c mSP_DoorHitDat;

/**
 * @brief Initialize door check work
 *
 * Initializes the door check work structure.
 */
static void mSP_init_check_door_work(void) {
    // OSReport("mSP_init_check_door_work\n");
    bzero(&mSP_DoorHitDat, sizeof(mSP_DoorHitDat));
}

/**
 * @brief Initialize door check system
 *
 * Initializes the door check system when entering the field.
 */
extern void mSP_init_check_door(void) {
    if (Save_Get(scene_no) == SCENE_FG) {
        mSP_init_check_door_work();
        Common_Set(prev_shop_force_open_door_flag, Common_Get(shop_force_open_door_flag));
    }
}

/**
 * @brief Start door check for an actor
 * @param actor Shop actor
 * @param pos Actor position
 *
 * Starts checking if the player is hitting the shop door
 * to potentially force it open.
 */
extern void mSP_start_check_door(ACTOR* actor, xyz_t* pos) {
    mSP_init_check_door_work();
    mSP_DoorHitDat.shop_actor = actor;
    mSP_DoorHitDat.pos = *pos;
    Common_Set(shop_force_open_door_flag, FALSE);
    // OSReport("mSP_start_check_door\n");
}

/**
 * @brief Check if tool hit is special
 * @param pos Position to check
 * @param game Game context
 * @return TRUE if special hit, FALSE otherwise
 *
 * Checks if the player's tool hit intersects with the shop area.
 */
static int mSP_tool_hit_special_check(xyz_t* pos, GAME* game) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (playerx != NULL) {
        xyz_t chk_pos = playerx->world.position;
        f32 vec1_s[2];
        f32 vec1_e[2];
        f32 vec0_s[2];
        f32 vec0_e[2];

        chk_pos.x += 50.0f * sin_s(playerx->shape_info.rotation.y);
        chk_pos.z += 50.0f * cos_s(playerx->shape_info.rotation.y);

        vec0_s[0] = chk_pos.x;
        vec0_s[1] = chk_pos.z;

        vec0_e[0] = playerx->world.position.x;
        vec0_e[1] = playerx->world.position.z;

        vec1_s[0] = pos->x - 60.0f;
        vec1_s[1] = pos->z - 60.0f;

        vec1_e[0] = pos->x + 60.0f;
        vec1_e[1] = pos->z + 60.0f;

        return mCoBG_GetCrossJudge_2Vector(vec0_s, vec0_e, vec1_s, vec1_e);
    }

    return FALSE;
}

/**
 * @brief Check door during gameplay
 * @param game Game context
 * @param actorx Shop actor
 *
 * Main door check function that:
 * - Resets if shop is open
 * - Counts hits when shop is closed
 * - Forces shop open after enough hits
 * - Handles special conditions
 */
extern void mSP_checking_door(GAME* game, ACTOR* actorx) {
    int status = mSP_ShopOpen();

    if (mSP_DoorHitDat.shop_actor == actorx) {
        if (mDemo_CheckDemoType() == mDemo_TYPE_SCROLL) {
            xyz_t pos = mSP_DoorHitDat.pos;
            mSP_start_check_door(mSP_DoorHitDat.shop_actor, &pos);
        }
        if ((status == mSP_SHOP_STATUS_OPEN || status == mSP_SHOP_STATUS_OPENEVENT) &&
            !Common_Get(shop_force_open_door_flag)) {
            xyz_t pos = mSP_DoorHitDat.pos; // These feel like mSP_start_check_door's pos value should be pass-by-value,
            // but that does not match.
            mSP_start_check_door(mSP_DoorHitDat.shop_actor, &pos);
        } else if (!Common_Get(shop_force_open_door_flag) && status == mSP_SHOP_STATUS_END) {
            xyz_t reflect_pos;

            if (mPlib_Check_reflect(game, &reflect_pos) == TRUE &&
                mSP_tool_hit_special_check(&mSP_DoorHitDat.pos, game) && !mSP_CheckFukubikiDay() &&
                mSP_DoorHitDat.hit_count < mSP_DOOR_HIT_OPEN_NUM) {
                mSP_DoorHitDat.hit_count++;
                mSP_DoorHitDat.open_timer = 0;
            }

            if (mSP_DoorHitDat.hit_count >= mSP_DOOR_HIT_OPEN_NUM) {
                if (mSP_DoorHitDat.open_timer < mSP_DOOR_HIT_OPEN_TIMER) {
                    mSP_DoorHitDat.open_timer++;
                } else {
                    Common_Set(shop_force_open_door_flag, TRUE);
                }
            }
        }
    }
}

/**
 * @brief End door check
 *
 * Ends the door check system.
 */
extern void mSP_end_check_door(void) {
    mSP_init_check_door_work();
}

/**
 * @brief Check if shop is force opened
 * @return TRUE if force opened, FALSE otherwise
 *
 * Returns the current force open status.
 */
extern int mSP_force_opend(void) {
    return Common_Get(shop_force_opend);
}

#include "../src/game/m_item_debug.c"
