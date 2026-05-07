#include "m_cockroach.h"

#include "m_home.h"
#include "m_house.h"
#include "m_private.h"
#include "m_field_info.h"
#include "m_scene_table.h"
#include "m_common_data.h"

/**
 * @brief Clamps the input cockroach count between [0, mCkRh_MAX_NUM].
 *
 * @param count The new cockroach count
 * @return The clamped cockroach count
 **/
static int mCkRh_CorrectGokiCount(int count) {
    if (count < 0) {
        return 0;
    }

    return (count <= mCkRh_MAX_NUM ? count : mCkRh_MAX_NUM);
}

/**
 * @brief Initializes all house cockroach save data for unclaimed houses
 * when a new Player is created.
 **/
extern void mCkRh_InitGokiSaveData_InitNewPlayer() {
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mHS_get_pl_no_detail(i) == -1) {
            mCkRh_InitGokiSaveData_1Room(i);
        }
    }
}

/**
 * @brief Initializes a single house's cockroach data by house index.
 *
 * @param home_no The house index whose cockroach data will be initialized
 **/
extern void mCkRh_InitGokiSaveData_1Room(int home_no) {
    mCkRh_InitGokiSaveData_1Room_ByHomeData(Save_GetPointer(homes[home_no]));
}

/**
 * @brief Initializes a single house's cockroach data.
 *
 * @param home The mHm_hs_c house whose cockroach data wil be initialized.
 **/
extern void mCkRh_InitGokiSaveData_1Room_ByHomeData(mHm_hs_c* home) {
    home->goki.num = 0;
    home->goki.pad = 0;

    home->goki.time = Common_Get(time.rtc_time);
}

/**
 * @brief Initializes island cottage cockroach data.
 **/
extern void mCkRh_InitGokiSaveData_IslandPlayerRoom(mHm_cottage_c* cottage) {
    cottage->goki.num = 0;
    cottage->goki.pad = 0;
    cottage->goki.time.year = 0;
    cottage->goki.time.month = 0;
    cottage->goki.time.day = 0;
}

/**
 * @brief Initializes all houses' cockroach data even if a player owns it.
 **/
extern void mCkRh_InitGokiSaveData_AllRoom() {
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        mCkRh_InitGokiSaveData_1Room(i);
    }
}

/**
 * @brief Updates the cockroach 'last entered' time for the island cottage.
 *
 * @param scene_id The current scene id
 **/
extern void mCkRh_SetGoingOutCottageTime(int scene_id) {
    if (scene_id == SCENE_COTTAGE_MY) {
        mHm_hs_c* cur_island_house_p = Common_Get(cur_island_house_p);

        if (Common_Get(field_type) == mFI_FIELDTYPE2_PLAYER_ROOM && cur_island_house_p != NULL) {
            cur_island_house_p->island.cottage.goki.time.year = Common_Get(time.rtc_time.year);
            cur_island_house_p->island.cottage.goki.time.month = Common_Get(time.rtc_time.month);
            cur_island_house_p->island.cottage.goki.time.day = Common_Get(time.rtc_time.day);
        }
    }
}

/**
 * @brief Updates the cockroach 'last entered' time for a player's house.
 *
 * @param player_no The index of the player whose cockroach data will be updated
 **/
extern void mCkRh_SavePlayTime(int player_no) {
    if (player_no < PLAYER_NUM) {
        int home_no = mHS_get_arrange_idx(player_no);
        Save_Set(homes[home_no & 3].goki.time, Common_Get(time.rtc_time));
    }
}

/**
 * @brief Returns the inverval in days between the current time and
 * the last time that the player's cockroach 'last enter time'.
 *
 * @param player_no The index of the player whose 'days gap' will be calculated
 * @return When a foriegner, 0, otherwise day interval
 **/
static int mCkRh_DaysGapCompareWithSaveTime(int player_no) {
    int homeid;
    lbRTC_time_c goki_time;
    int interval;

    if (player_no < PLAYER_NUM) {
        homeid = mHS_get_arrange_idx(player_no) & 3;
        goki_time.year = Save_Get(homes[homeid].goki.time.year);
        goki_time.month = Save_Get(homes[homeid].goki.time.month);
        goki_time.day = Save_Get(homes[homeid].goki.time.day);
        goki_time.weekday = lbRTC_Week(goki_time.year, goki_time.month, goki_time.day);
        goki_time.hour = 1;
        goki_time.min = 1;
        goki_time.sec = 1;

        interval = lbRTC_GetIntervalDays(&goki_time, Common_GetPointer(time.rtc_time));
    } else {
        interval = 0;
    }

    return interval;
}

/**
 * @brief Gets the day interval between current time and the island cottage
 * cockroach last enter time.
 *
 * @param cottage The island cottage whose cockroach data will be compared
 * @return days between current time and last island cottage enter time
 **/
static int mCkRh_DaysGapCompareWithCottageSaveTime(mHm_cottage_c* cottage) {
    lbRTC_time_c goki_time;

    goki_time.year = cottage->goki.time.year;
    goki_time.month = cottage->goki.time.month;
    goki_time.day = cottage->goki.time.day;
    goki_time.weekday = lbRTC_Week(goki_time.year, goki_time.month, goki_time.day);
    goki_time.hour = 1;
    goki_time.min = 1;
    goki_time.sec = 1;

    return lbRTC_GetIntervalDays(&goki_time, Common_GetPointer(time.rtc_time));
}

/**
 * @brief Determines and updates the saved cockroach number for a player.
 *
 * The minimum day interval between the current time and the cockroach's
 * 'last entered time' is 7 days. The amount you get scales linearly,
 * starting with 1 new cockroach on day 7, 2 new on day 8, ...
 *
 * The maximum number of cockroaches is clamped to mCkRh_MAX_NUM which stock
 * is 10 cockroaches.
 *
 * @param player_no The inex of the player whose cockroach data will be updated
 **/
extern void mCkRh_DecideNowGokiFamilyCount(int player_no) {
    int count;
    int day_gap;
    int home_no;
    int goki_num;

    /* player must live in town */
    if (player_no < mPr_FOREIGNER) {
        day_gap = mCkRh_DaysGapCompareWithSaveTime(player_no);
        home_no = mHS_get_arrange_idx(player_no) & 3;
        if (day_gap > mCkRh_INTERVAL_DAYS) {
            goki_num = Save_Get(homes[home_no].goki.num);
            count = goki_num > 0 ? day_gap : day_gap - mCkRh_INTERVAL_DAYS;
            Save_Set(homes[home_no].goki.num, mCkRh_CorrectGokiCount(count + goki_num));
        }

        if (Save_Get(homes[home_no]).size_info.next_size >= mHm_HOMESIZE_ISLAND && Save_Get(homes[home_no]).island.cottage.goki.time.year != 0) {
            day_gap = mCkRh_DaysGapCompareWithCottageSaveTime(&Save_Get(homes[home_no]).island.cottage);
            if (day_gap > mCkRh_INTERVAL_DAYS) {
                goki_num = Save_Get(homes[home_no].island.cottage.goki.num);
                count = goki_num > 0 ? day_gap : day_gap - mCkRh_INTERVAL_DAYS;
                Save_Set(homes[home_no].island.cottage.goki.num, mCkRh_CorrectGokiCount(count + goki_num));
            }
        }
    }
}

/**
 * @brief Adds a specific amount of cockroaches to the current player's house.
 *
 * @param count The number of cockroaches to add (total clamped to mCkRh_MAX_NUM)
 * @param scene_no The current scene id
 * @return TRUE/FALSE cockroach data was updated
 **/
extern int mCkRh_PlussGokiN_NowRoom(int count, int scene_no) {
    mHm_hs_c* island_house_p = Common_Get(cur_island_house_p);
    
    if (Common_Get(field_type) == mFI_FIELDTYPE2_PLAYER_ROOM) {
        int player_no = Common_Get(player_no);
        int home_id = mHS_get_arrange_idx(player_no) & 3;
        
        if (scene_no == SCENE_COTTAGE_MY && island_house_p != NULL) {
            u8* goki_num = &island_house_p->island.cottage.goki.num;
            *goki_num = mCkRh_CorrectGokiCount(count + *goki_num);
            return TRUE;
        } else {
            if (mFI_IS_PLAYER_ROOM(mFI_GetFieldId())) {
                Save_Set(homes[home_id].goki.num, mCkRh_CorrectGokiCount(count + Save_Get(homes[home_id].goki.num)));
                return TRUE;
            }
        }
    }

    return FALSE;
}

/**
 * @brief Removes a specific amount of cockroaches to the current player's house.
 *
 * @param count The number of cockroaches to remove (minimum clamped to 0)
 * @param scene_no The current scene id
 * @return TRUE/FALSE cockroach data was updated
 **/
extern int mCkRh_MinusGokiN_NowRoom(int count, int scene_no) {
    return mCkRh_PlussGokiN_NowRoom(-count, scene_no);
}

/**
 * @brief Gets the cockroach count for the current scene id.
 *
 * @return
 *  - in player house: house cockroach count
 *  - in island octtage: island cottage cockroach count
 *  - elsewhere: 0
 **/
extern int mCkRh_NowSceneGokiFamilyCount() {
    mHm_hs_c* island_house_p = Common_Get(cur_island_house_p);

    if (Save_Get(scene_no) == SCENE_COTTAGE_MY && island_house_p != NULL) {
        return mCkRh_CorrectGokiCount(island_house_p->island.cottage.goki.num);
    } else if (mFI_IS_PLAYER_ROOM(mFI_GetFieldId())) {
        // @BUG - Failure mode is -1 which is not a valid house index.
        int house_idx = mFI_IS_PLAYER_ROOM(mFI_GetFieldId()) != FALSE ? mFI_GET_PLAYER_ROOM_NO(mFI_GetFieldId()) : -1;

#ifdef BUGFIXES
        if (house_idx == -1) {
            return 0;
        }
#endif
        
        return mCkRh_CorrectGokiCount(Save_Get(homes[house_idx].goki.num));
    }

    return 0;
}

/**
 * @brief Initializes the 'can_look_goki_count' variable to 0.
 *
 * This variable controls how many cockroaches are currently
 * visible to the player in a room.
 **/
extern void mCkRh_InitCanLookGokiCount() {
    Common_Set(can_look_goki_count, 0);
}

/**
 * @brief Changes the 'can_look_goki_count' variable by 'count'.
 *
 * 'can_look_goki_count' is clamped between
 *
 * @param count The number of visible cockroaches to add/remove
 * @return TRUE/FALSE were number of visible cockroaches updated?
 **/
extern int mCkRh_CalcCanLookGokiCount(int count) {
    int new_count = count + mCkRh_GetCanLookGokiCount();

    if (new_count < 0) {
        Common_Set(can_look_goki_count, 0);
        return FALSE;
    }

    if (new_count > mCkRh_CAN_LOOK_GOKI_NUM) {
        Common_Set(can_look_goki_count, mCkRh_CAN_LOOK_GOKI_NUM);
        return FALSE;
    }

    Common_Set(can_look_goki_count, new_count);
    return TRUE;
}

/**
 * @brief Retrieves the 'can_look_gooki_count' value.
 *
 * @return number of cockroaches currently visible to the player
 **/
extern int mCkRh_GetCanLookGokiCount() {
    return CLAMP(Common_Get(can_look_goki_count), 0, mCkRh_CAN_LOOK_GOKI_NUM);
}
