#include "m_island.h"

#include "m_field_info.h"
#include "m_common_data.h"
#include "m_random_field.h"
#include "m_malloc.h"
#include "libultra/libultra.h"
#include "jsyswrap.h"

static Island_c l_keepIsland;
static u16 l_keepIslandComb[mISL_FG_BLOCK_X_NUM * mISL_FG_BLOCK_Z_NUM];

extern void mISL_ClearKeepIsland() {
    bzero(&l_keepIsland, sizeof(l_keepIsland));
}

static void mISL_KeepIslandComb(u16* dst, mFM_combination_c* combi, int count) {
    while (count != 0 && dst != NULL && combi != NULL) {
        count--;
        dst[0] = combi[0].combination_type;
        dst++;
        combi++;
    }
}

extern void mISL_ChangeBG() {
    int island_x_blocks[mISL_FG_BLOCK_X_NUM];

    mFI_GetIslandBlockNumX(island_x_blocks);

    if (island_x_blocks[0] > 0 && island_x_blocks[1] < (BLOCK_X_NUM - 1)) {
        mISL_KeepIslandComb(l_keepIslandComb, Save_GetPointer(combi_table[mISL_BLOCK_Z][island_x_blocks[0]]),
                            mISL_FG_BLOCK_X_NUM);
        mRF_IslandBgData_To_VillageData();
        mFM_RestoreIslandBG(island_x_blocks, mISL_FG_BLOCK_X_NUM);

        if (Common_Get(cur_island_house_p) != NULL) {
            mFM_RestoreIslandFG(Common_Get(cur_island_house_p)->island.fgblock[0], (u16*)Common_Get(cur_island_house_p)->island.deposit, island_x_blocks, mISL_FG_BLOCK_X_NUM);
        }
    }
}

extern void mISL_RestoreIsland() {
    // stubbed
}

static void mISL_clear(Island_c* island) {
    bzero(island, sizeof(Island_c));
    island->house_idx = -1;
    island->bg_data[0] = 0xFF;
    island->bg_data[1] = 0xFF;
    island->last_song_to_island = 0xFF;
    island->last_song_from_island = 0xFF;
    mNpc_ClearIslandAnimalInfo(&island->animal);
}

extern void mISL_init(Island_c* island) {
    mISL_clear(island);
    mLd_ClearLandName(island->name);
    bcopy(Save_GetPointer(land_info), &island->landinfo, sizeof(mLd_land_info_c));
    mHm_InitCottage(&island->cottage);
    island->grass_tex_type = Save_Get(bg_tex_idx);
}

extern void mISL_SetHouseIdx(int player_no) {
    if (player_no >= 0 && player_no < PLAYER_NUM) {
        PersonalID_c* pid = &Save_Get(private_data[player_no]).player_ID;

        if (mPr_NullCheckPersonalID(pid) == FALSE) {
            int arrange_idx = mHS_get_arrange_idx(player_no);
            mHm_hs_c* house = Save_GetPointer(homes[arrange_idx]);

            if (mPr_CheckCmpPersonalID(pid, &house->ownerID) == TRUE) {
                house->island.house_idx = arrange_idx;
            }
        }
    }
}

extern int mISL_GetNpcDayType(Island_c *island) {
    int day_type = mISL_NPC_DAY_TYPE_NOT_EXIST;

    if (island != NULL) {
        lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
        lbRTC_ymd_c appear_date = island->islander_spawn_date;

        if (lbRTC_IsEqualDate(appear_date.year, appear_date.month, appear_date.day, rtc_time->year, rtc_time->month, rtc_time->day) == lbRTC_EQUAL) {
            day_type = mISL_NPC_DAY_TYPE_APPEARED_TODAY;
        } else if (lbRTC_IsEqualDate(appear_date.year, appear_date.month, appear_date.day, 0xFFFF, 0xFF, 0xFF) == lbRTC_EQUAL) {
            day_type = mISL_NPC_DAY_TYPE_NORMAL;
        } else if (lbRTC_IsEqualDate(appear_date.year, appear_date.month, appear_date.day, 0x8000, 0x80, 0x80) == lbRTC_EQUAL) {
            day_type = mISL_NPC_DAY_TYPE_LEAVING_TOMORROW;
        }
    }

    return day_type;
}

extern int mISL_CheckAppearIslandNpc_com(mHm_hs_c* home, PersonalID_c* pid) {
    int ret = FALSE;

    if (home != NULL && pid != NULL) {
        Island_c* island = &home->island;

        if (mNpc_CheckFreeAnimalPersonalID(&island->animal.id) == FALSE) {
            int day_type = mISL_GetNpcDayType(island);

            if ((day_type == mISL_NPC_DAY_TYPE_NOT_EXIST && mPr_CheckCmpPersonalID(&home->ownerID, pid) == TRUE) || day_type != mISL_NPC_DAY_TYPE_NOT_EXIST) {
                ret = TRUE;
            }   
        }
    }

    return ret;
}

extern int mISL_CheckAppearIslandNpc(void) {
    mHm_hs_c* house = Common_Get(cur_island_house_p);
    int ret = FALSE;

    if (Now_Private != NULL && house != NULL) {
        if (mISL_CheckAppearIslandNpc_com(house, &Now_Private->player_ID) == TRUE) {
            ret = TRUE;
        }
    }

    return ret;
}

static u32 l_misl_check_land = 0;
static u8 l_misl_count_table_island[mISL_PLAYER_ACTION_NUM];
static u8 l_misl_count_table_land[mISL_VILLAGE_PLAYER_ACTION_NUM];
static u8 l_misl_count_max_table_island[mISL_PLAYER_ACTION_NUM] = {
    10, // 
    4, // 
    1, // 
    10, // 
    1, // 
    5, // 
    3, // 
    10, // 
    5, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
};
static u8 l_misl_count_max_table_land[mISL_VILLAGE_PLAYER_ACTION_NUM] = {
    7, // 
    4, // 
    1, // 
    6, // 
    1, // 
    5, // 
    1, // 
    5, // 
    3, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
    1, // 
#if VERSION == GAEJ01_00
    1, //
#else
    10, // 
#endif
    1, // 
    1, // 
    1, // 
};

static u32* mISL_GetCheckP_island(PersonalID_c* pid) {
    Anmmem_c* memory = NULL;
    u32* check_p = NULL;

    if (Common_Get(cur_island_house_p) != NULL) {
        memory = Common_Get(cur_island_house_p)->island.animal.memories;
    }

    if (pid != NULL && mPr_NullCheckPersonalID(pid) == FALSE && memory != NULL) {
        int idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

        if (idx != -1) {
            check_p = &memory[idx].memuni.island.check;
        }
    }

    return check_p;
}

extern void mISL_ClearNowPlayerAction_island(void) {
    Private_c* priv = Common_Get(now_private);

    if (priv != NULL) {
        u32* check_p = mISL_GetCheckP_island(&priv->player_ID);

        if (check_p != NULL) {
            check_p[0] = 0;
        }

        bzero(l_misl_count_table_island, sizeof(l_misl_count_table_island));
    }
}

extern void mISL_ClearNowPlayerAction_land(void) {
    l_misl_check_land = 0;
    bzero(l_misl_count_table_land, sizeof(l_misl_count_table_land));
}

extern void mISL_UnsetPlayerAction(PersonalID_c* pid, u32 action) {
    u32* check_p = NULL;
    u8* count_p = l_misl_count_table_island;
    int check_count = 0;
    int i;

    if (mFI_CheckInIsland() == TRUE) {
        if (pid != NULL) {
            check_p = mISL_GetCheckP_island(pid);
            count_p = l_misl_count_table_island;
            check_count = ARRAY_COUNT(l_misl_count_table_island);
        }
    } else {
        check_p = &l_misl_check_land;
        count_p = l_misl_count_table_land;
        check_count = ARRAY_COUNT(l_misl_count_table_land);
    }

    if (check_p != NULL) {
        *check_p &= ~action;
        for (i = 0; i < check_count; i++) {
            if (((action >> i) & 1) != 0) {
                count_p[i] = 0;
            }
        }
    }
}

extern void mISL_UnsetNowPlayerAction(u32 action) {
    if (Now_Private != NULL) {
        mISL_UnsetPlayerAction(&Now_Private->player_ID, action);
    }
}

extern void mISL_SetPlayerAction(PersonalID_c* pid, u32 action) {
    u32* check_p = NULL;
    u8* count_p = l_misl_count_table_island;
    u8* count_max_p = l_misl_count_max_table_island;
    int count = 0;

    if (mFI_CheckInIsland() == TRUE) {
        if (pid != NULL) {
            check_p = mISL_GetCheckP_island(pid);
            count_p = l_misl_count_table_island;
            count_max_p = l_misl_count_max_table_island;
            count = ARRAY_COUNT(l_misl_count_table_island);
        }
    } else {
        check_p = &l_misl_check_land;
        count_p = l_misl_count_table_land;
        count_max_p = l_misl_count_max_table_land;
        count = ARRAY_COUNT(l_misl_count_table_land);
    }

    if (check_p != NULL) {
        int i;

        for (i = 0; i < count; i++) {
            if (((action >> i) & 1) != 0) {
                count_p[i]++;
            }

            if (count_max_p[i] <= count_p[i]) {
                check_p[0] |= (1 << i);
                count_p[i] = count_max_p[i];
            }
        }
    }
}

extern void mISL_SetNowPlayerAction(u32 action) {
    if (Now_Private != NULL) {
        mISL_SetPlayerAction(&Now_Private->player_ID, action);
    }
}

extern int mISL_CheckPlayerAction(PersonalID_c* pid, u32 action) {
    u32* check_p = NULL;
    int check_count = 0;
    int res = FALSE;

    if (mFI_CheckInIsland() == TRUE) {
        if (pid != NULL) {
            check_p = mISL_GetCheckP_island(pid);
            check_count = ARRAY_COUNT(l_misl_count_table_island);
        }
    } else {
        check_p = &l_misl_check_land;
        check_count = ARRAY_COUNT(l_misl_count_table_land);
    }

    if (check_p != NULL && (check_p[0] & action) != 0) {
        res = TRUE;
    }

    return res;
}

extern int mISL_CheckNowPlayerAction(u32 action) {
    int res = FALSE;

    if (Now_Private != NULL) {
        res = mISL_CheckPlayerAction(&Now_Private->player_ID, action);
    }

    return res;
}

extern void mISL_MoveNowPlayerAction(void) {
    mActor_name_t field_id = mFI_GetFieldId();
    int destiny;

    if (Now_Private != NULL && mFI_GET_TYPE(field_id) == mFI_FIELDTYPE2_FG) {
        mISL_ClearNowPlayerAction_land();
        destiny = Now_Private->destiny.type;

        if (destiny >= mPr_DESTINY_BAD_LUCK && destiny < mPr_DESTINY_NUM) {
            static int destiny_pact[] = {
                mISL_PLAYER_ACTION_DESTINY_BAD_LUCK, // mPr_DESTINY_BAD_LUCK
                mISL_PLAYER_ACTION_DESTINY_MONEY_LUCK, // mPr_DESTINY_MONEY_LUCK
                mISL_PLAYER_ACTION_DESTINY_GOODS_LUCK, // mPr_DESTINY_GOODS_LUCK
            };
            mISL_SetNowPlayerAction(destiny_pact[destiny - mPr_DESTINY_BAD_LUCK]);
        }
    }
}

extern int mISL_GetNowPlayerActionNum_land(void) {
    int num = 0;
    int i;

    for (i = 0; i < ARRAY_COUNT(l_misl_count_table_land); i++) {
        if ((l_misl_check_land >> i) & 1) {
            num++;
        }
    }

    return num;
}
