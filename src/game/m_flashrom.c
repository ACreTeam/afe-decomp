/**
 * @file m_flashrom.c
 * @brief Save game check and error handling functions.
 *
 * This file contains functions related to save game checks, error handling,
 * and related utility functions. The functions are responsible for verifying
 * save data integrity, managing error information, and displaying save data
 * check results and error information.
 *
 * Global Functions:
 *  - mFRm_set_msg_idx()         : Set the message index.
 *  - mFRm_get_msg_idx()         : Get the message index.
 *  - mFRm_ReturnCheckSum()      : Calculate the checksum of the given data.
 *  - mFRm_GetFlatCheckSum()     : Calculate the flat checksum for save data.
 *  - mFRm_CheckSaveData_ID()    : Check if the save data ID matches the expected ID.
 *  - mFRm_CheckSaveData_common(): Check the save data for various conditions.
 *  - mFRm_CheckSaveData()       : Perform a save data check.
 *  - mFRm_ClearSaveCheckData()  : Clear the save check data structure.
 *  - mFRm_SetSaveCheckData()    : Set the save check data structure.
 *  - mFRm_PrintSavedDebug()     : Print a debug indicator if saved debug data is found.
 *  - mFRm_clear_err_info()      : Clear the error information array.
 *  - mFRm_save_data_check()     : Perform a series of save data checks and store errors.
 *  - mFRm_display_errInfo()     : Display error information on the screen.
 *
 * File-local Functions:
 *  - mFRm_get_free_errInfo()    : Find a free slot in the error information array.
 *  - mFRm_set_errInfo()         : Set error information in the error information array.
 *  - mFRm_get_errInfoNum()      : Get the number of errors in the error information array.
 */

/* TODO: finish & include sChk_ZZZ files each programmer wrote */
/* TODO: A few removed functions need to be matched on N64 and included for proper .rodata layout */

#include "m_flashrom.h"

#include "m_common_data.h"
#include "m_time.h"
#include "m_land.h"
#include "m_name_table.h"
#include "m_field_make.h"
#include "m_add_npc.h"
#include "libultra/libultra.h"
#include "zurumode.h"

static int l_mfrm_msg_idx = 0;
static int l_mfrm_now_color = 0;
static mFRm_err_info_c l_mfrm_err_info[mFRm_ERROR_INFO_NUM];
static int l_mfrm_err_debug[] = { 0, 0, 0, 0, 0, 0 };

/**
 * @brief Set the current message index value.
 *
 * This function sets the global message index value to the provided input.
 *
 * @param idx The message index value to be set.
 */
extern void mFRm_set_msg_idx(int idx) {
    l_mfrm_msg_idx = idx;
}

/**
 * @brief Get the current message index value.
 *
 * This function returns the global message index value.
 *
 * @return int The current message index value.
 */
extern int mFRm_get_msg_idx() {
    return l_mfrm_msg_idx;
}

/* @fabricated - necessary for including some strings in .data & taken from DnM */
extern MATCH_FORCESTRIP void mFRm_PrintErrInfo(gfxprint_t* gfxprint) {
    gfxprint_color(gfxprint, 250, 100, 250, 255);
    gfxprint_locate8x8(gfxprint, 22, 3);

    if (l_mfrm_err_debug[0] != 0) {
        gfxprint_printf(gfxprint, "N");
    }

    if (l_mfrm_err_debug[1] != 0) {
        gfxprint_printf(gfxprint, "A");
    }

    if (l_mfrm_err_debug[2] != 0) {
        gfxprint_printf(gfxprint, "W");
    }

    if (l_mfrm_err_debug[3] != 0) {
        gfxprint_printf(gfxprint, "R");
    }

    if (l_mfrm_err_debug[4] != 0) {
        gfxprint_printf(gfxprint, "C");
    }

    if (l_mfrm_err_debug[5] != 0) {
        gfxprint_printf(gfxprint, "O");
    }
}

/**
 * @brief Calculate the checksum of the given data.
 *
 * This function calculates the checksum of the provided data by adding
 * all the 16-bit data elements together.
 *
 * @param data A pointer to the data buffer.
 * @param size The size of the data buffer in bytes.
 * @return u16 The calculated checksum.
 */
extern u16 mFRm_ReturnCheckSum(u16* data, int size) {
    u16 checksum = 0;

    // Check if the size is even
    if ((size & 1) == 0) {
        // Calculate the checksum by adding all 16-bit data elements
        while (size != 0) {
            checksum += *data;
            data++;
            size -= sizeof(u16);
        }
    }

    return checksum;
}

/**
 * @brief Calculate the flat checksum of the given data.
 *
 * This function calculates the flat checksum of the provided data by
 * subtracting the current checksum from the calculated checksum and
 * then performing a bitwise complement and incrementing by 1.
 *
 * @param data A pointer to the data buffer.
 * @param size The size of the data buffer in bytes.
 * @param now_checksum The current checksum of the data buffer.
 * @return u16 The calculated flat checksum.
 */
extern u16 mFRm_GetFlatCheckSum(u16* data, int size, u16 now_checksum) {
    // Calculate the checksum
    u16 checksum = mFRm_ReturnCheckSum(data, size) - now_checksum;

    // Perform bitwise complement and increment by 1
    return (u16)(((~checksum & 0xFFFF) + 1) & 0xFFFF);
}

/**
 * @brief Check if the save data ID is valid.
 *
 * This function checks if the provided save_check structure contains a valid
 * save data ID.
 *
 * @param save_check A pointer to the mFRm_chk_t structure containing the save data ID.
 * @return int Returns TRUE if the save data ID is valid, otherwise FALSE.
 */
extern int mFRm_CheckSaveData_ID(mFRm_chk_t* save_check) {
    int ret = FALSE;

    // Check if the save data ID is valid
    if ((save_check->code == mFRm_SAVE_ID)) {
        ret = TRUE;
    }

    return ret;
}

/**
 * @brief Check if the save data is valid.
 *
 * This function checks if the provided save_check structure contains valid save data,
 * comparing the land ID with the provided land_id parameter.
 *
 * @param save_check A pointer to the mFRm_chk_t structure containing the save data.
 * @param land_id The land ID to check against the save data.
 * @return int Returns TRUE if the save data is valid, otherwise FALSE.
 */
extern int mFRm_CheckSaveData_common(mFRm_chk_t* save_check, u16 land_id) {
    int ret = FALSE;

    // Check if the save data ID is valid and land IDs match
    if (mFRm_CheckSaveData_ID(save_check) != 0 && mLd_CHECK_LAND_ID(save_check->land_id) &&
        save_check->land_id == land_id) {
        ret = TRUE;
    }

    return ret;
}

/**
 * @brief Check if the current save data is valid.
 *
 * This function checks if the current save data is valid using mFRm_CheckSaveData_common.
 *
 * @return int Returns TRUE if the save data is valid, otherwise FALSE.
 */
extern int mFRm_CheckSaveData() {
    return mFRm_CheckSaveData_common(Save_GetPointer(save_check), Save_Get(land_info.id));
}

/**
 * @brief Clear the save check data.
 *
 * This function clears the provided save_check structure by setting its fields to their
 * default values.
 *
 * @param save_check A pointer to the mFRm_chk_t structure to be cleared.
 */
extern void mFRm_ClearSaveCheckData(mFRm_chk_t* save_check) {
    // Set the save check data fields to their default values
    save_check->code = -1;
    save_check->land_id = 0xFFFF;
    bcopy((lbRTC_time_c*)&mTM_rtcTime_clear_code, &save_check->time, sizeof(lbRTC_time_c));
    save_check->checksum = 0;
}

/**
 * @brief Set the save check data.
 *
 * This function sets the save check data fields based on the current save data
 * and real-time clock values.
 *
 * @param save_check A pointer to the mFRm_chk_t structure to be set.
 */
extern void mFRm_SetSaveCheckData(mFRm_chk_t* save_check) {
    u16 land_id = Save_Get(land_info.id);

    // Set the save check data fields
    save_check->code = mFRm_SAVE_ID;
    save_check->land_id = land_id;
    lbRTC_TimeCopy(&save_check->time, &common_data.time.rtc_time);
}

static int mFRm_check_clear_fg(mActor_name_t item) {
    int ret = FALSE;

    switch (ITEM_NAME_GET_TYPE(item)) {
        case NAME_TYPE_ITEM0:
            if (ITEM_IS_BURIED_PITFALL_HOLE(item) || ITEM_IS_SIGNBOARD(item)) {
                ret = TRUE;
            }
            break;
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1:
            ret = TRUE;
            break;
        case NAME_TYPE_ITEM1:
            ret = TRUE;
            break;
        default:
            if (item == RSV_FE1F) {
                ret = TRUE;
            }
            break;
    }

    return ret;
}

static void mFRm_toEmptyLand_fg_common(mFM_fg_c* fg, u16* deposit, int count) {
    mActor_name_t* item_p;
    int i;
    int uz;
    int ux;

    for (i = 0; i < count; i++) {
        item_p = fg->items[0];
        for (uz = 0; uz < UT_Z_NUM; uz++) {
            for (ux = 0; ux < UT_X_NUM; ux++) {
                if (mFRm_check_clear_fg(*item_p) == TRUE) {
                    *item_p = EMPTY_NO;
                    mFI_BlockDepositOFF(deposit, ux, uz);
                }

                item_p++;
            }
        }

        deposit += UT_Z_NUM;
        fg++;
    }
}

static void mFRm_toEmptyLand_change_tree(mFM_fg_c* fg, int count) {
    mActor_name_t* item_p;
    int i;
    int ux;
    int uz;

    for (i = 0; i < count; i++) {
        item_p = fg->items[0];
        for (uz = 0; uz < UT_Z_NUM; uz++) {
            for (ux = 0; ux < UT_X_NUM; ux++) {
                switch (*item_p) {
                    case GOLD_TREE_SHOVEL:
                        *item_p = GOLD_TREE;
                        break;
                    case TREE_100BELLS:
                    case TREE_1000BELLS:
                    case TREE_10000BELLS:
                    case TREE_30000BELLS:
                        *item_p = TREE;
                        break;
                }

                item_p++;
            }
        }

        fg++;
    }
}

static void mFRm_toEmptyLand_fg(mFM_fg_c* fg, u16* deposit) {
    mFRm_toEmptyLand_fg_common(fg, deposit, FG_BLOCK_TOTAL_NUM);
    mFRm_toEmptyLand_change_tree(fg, FG_BLOCK_TOTAL_NUM);
}

static void mFRm_toEmptyLand_haniwa(Haniwa_c* haniwa) {
    Haniwa_Item_c* item_p = haniwa->items;
    int i;

    for (i = 0; i < HANIWA_ITEM_HOLD_NUM; i++) {
        item_p->item = EMPTY_NO;
        item_p->exchange_type = mHm_HANIWA_TRADE_0;
        item_p->extra_data = 0;
        item_p++;
    }
}

static void mFRm_toEmptyLand_floor(mHm_flr_c* floor) {
    mHm_lyr_c* layer;
    mActor_name_t* item_p;
    int i;
    int j;
    
    floor->tempo_beat.tempo = 0;
    floor->tempo_beat.beat = 0;
    layer = &floor->layer_main;
    for (i = 0; i < mHm_LAYER_NUM; i++) {
        item_p = layer->items[0];

        for (j = 0; j < UT_TOTAL_NUM; j++) {
            if (mFRm_check_clear_fg(*item_p) == TRUE) {
                *item_p = EMPTY_NO;
            }

            item_p++;
        }

        layer->ftr_switch = 0;
        for (j = 0; j < ARRAY_COUNT(layer->haniwa_step); j++) {
            layer->haniwa_step[j] = 0;
        }

        layer++;
    }
}

static void mFRm_toEmptyLand_cottage(mHm_cottage_c* cottage) {
    int i;
    
    mFRm_toEmptyLand_floor(&cottage->room);
    for (i = 0; i < ARRAY_COUNT(cottage->music_box); i++) {
        cottage->music_box[i] = 0;
    }
}

static void mFRm_toEmptyLand_island(Island_c* island) {
    if (island->house_idx != -1) {
        mFRm_toEmptyLand_fg_common(island->fgblock[0], (u16*)island->deposit, mISL_FG_BLOCK_X_NUM * mISL_FG_BLOCK_Z_NUM);
        mFRm_toEmptyLand_cottage(&island->cottage);
    }
}

static void mFRm_toEmptyLand_home(mHm_hs_c* home) {
    mHm_flr_c* floor;
    int i;
    int j;

    for (i = 0; i < mHS_HOUSE_NUM; i++) {
        if (mPr_NullCheckPersonalID(&home->ownerID) == FALSE) {
            floor = home->floors;
            for (j = 0; j < mHm_ROOM_NUM; j++) {
                mFRm_toEmptyLand_floor(floor);
                floor++;
            }

            for (j = 0; j < ARRAY_COUNT(home->music_box); j++) {
                home->music_box[j] = 0;
            }

            mFRm_toEmptyLand_haniwa(&home->haniwa);
            mMl_clear_mail_box(home->mailbox, HOME_MAILBOX_SIZE);
            mFRm_toEmptyLand_island(&home->island);
        }

        home++;
    }
}

static void mFRm_toEmptyLand_policebox(PoliceBox_c* policebox) {
    if (policebox != NULL) {
        mActor_name_t* item_p = policebox->keep_items;
        int i;

        for (i = 0; i < ARRAY_COUNT(policebox->keep_items); i++) {
            *item_p = EMPTY_NO;
            item_p++;
        }
    }
}

extern void mFRm_toEmptyLand(Save_t* save) {
    mFRm_toEmptyLand_fg(save->fg[0], (u16*)save->deposit);
    mFRm_toEmptyLand_home(save->homes);
    mFRm_toEmptyLand_policebox(&save->police_box);
}

static void mFRm_insert_event_info(Save_t* dst, Save_t* src) {
    int sched = FALSE;

    if (dst != NULL && src != NULL) {
        if (dst->event_save_data.flags & (1 << mEv_GET_SUBTYPE(mEv_SAVED_RENEWSHOP))) {
            sched = TRUE;
        }

        dst->event_save_data.flags = src->event_save_data.flags;
        if (sched == TRUE) {
            dst->event_save_data.flags |= (1 << mEv_GET_SUBTYPE(mEv_SAVED_RENEWSHOP));
        } else {
            dst->event_save_data.flags &= ~(1 << mEv_GET_SUBTYPE(mEv_SAVED_RENEWSHOP));
        }
    }
}

static int mFRm_search_id(AnmPersonalID_c* id, AnmPersonalID_c* chk_id, int count) {
    int ret = -1;
    int i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckCmpAnimalPersonalID(id, chk_id) == TRUE) {
            ret = i;
            break;
        }

        chk_id++;
    }

    return ret;
}

// They reused 'i' in the inner loop in rev0, rev1 fixes this.
#if VERSION == VER_GAEJ01_00
static void mFRm_mergeAnimalMemory(Animal_c* dst, Animal_c* src, Private_c* priv) {
    int src_idx;
    int dst_mem_idx;
    int src_mem_idx;
    int i;
    Anmmem_c* dst_memory;
    Anmmem_c* src_memory;
    // int j;

    if (dst != NULL && src != NULL && priv != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&dst->id) == FALSE) {
                src_idx = mNpc_SearchAnimalPersonalID_com(&dst->id, src, ANIMAL_NUM_MAX);

                if (src_idx != -1) {
                    for (i = 0; i < PLAYER_NUM; i++) {
                        if (mPr_NullCheckPersonalID(&priv[i].player_ID) == FALSE) {
                            src_mem_idx =
                                mNpc_GetAnimalMemoryIdx(&priv[i].player_ID, src[src_idx].memories, ANIMAL_MEMORY_NUM);

                            if (src_mem_idx != -1) {
                                src_memory = &src[src_idx].memories[src_mem_idx];
                                dst_mem_idx =
                                    mNpc_GetAnimalMemoryIdx(&priv[i].player_ID, dst->memories, ANIMAL_MEMORY_NUM);

                                if (dst_mem_idx != -1) {
                                    dst_memory = &dst->memories[dst_mem_idx];
                                    mem_copy((u8*)&dst_memory->letter_info, (u8*)&src_memory->letter_info, sizeof(Anmlet_c));
                                    mem_copy((u8*)&dst_memory->letter, (u8*)&src_memory->letter, sizeof(Anmplmail_c));
                                } else {
                                    dst_mem_idx =
                                        mNpc_ForceGetFreeAnimalMemoryIdx(dst, dst->memories, ANIMAL_MEMORY_NUM);
                                    if (dst_mem_idx != -1) {
                                        mNpc_CopyAnimalMemory(&dst->memories[dst_mem_idx], src_memory);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            dst++;
        }
    }
}
#else
static void mFRm_mergeAnimalMemory(Animal_c* dst, Animal_c* src, Private_c* priv) {
    int src_idx;
    int dst_mem_idx;
    int src_mem_idx;
    Anmmem_c* dst_memory;
    Anmmem_c* src_memory;
    int i;
    int j;

    if (dst != NULL && src != NULL && priv != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&dst->id) == FALSE) {
                src_idx = mNpc_SearchAnimalPersonalID_com(&dst->id, src, ANIMAL_NUM_MAX);

                if (src_idx != -1) {
                    for (j = 0; j < PLAYER_NUM; j++) {
                        if (mPr_NullCheckPersonalID(&priv[j].player_ID) == FALSE) {
                            src_mem_idx =
                                mNpc_GetAnimalMemoryIdx(&priv[j].player_ID, src[src_idx].memories, ANIMAL_MEMORY_NUM);

                            if (src_mem_idx != -1) {
                                src_memory = &src[src_idx].memories[src_mem_idx];
                                dst_mem_idx =
                                    mNpc_GetAnimalMemoryIdx(&priv[j].player_ID, dst->memories, ANIMAL_MEMORY_NUM);

                                if (dst_mem_idx != -1) {
                                    dst_memory = &dst->memories[dst_mem_idx];
                                    mem_copy((u8*)&dst_memory->letter_info, (u8*)&src_memory->letter_info, sizeof(Anmlet_c));
                                    mem_copy((u8*)&dst_memory->letter, (u8*)&src_memory->letter, sizeof(Anmplmail_c));
                                } else {
                                    dst_mem_idx =
                                        mNpc_ForceGetFreeAnimalMemoryIdx(dst, dst->memories, ANIMAL_MEMORY_NUM);
                                    if (dst_mem_idx != -1) {
                                        mNpc_CopyAnimalMemory(&dst->memories[dst_mem_idx], src_memory);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            dst++;
        }
    }
}
#endif

extern void mFRm_mergeAnimal(Save_t* dst, Save_t* src, AnmPersonalID_c* anm_id) {
    if (dst != NULL && src != NULL && anm_id != NULL) {
        Animal_c* animal = dst->animals;
        Animal_c* src_animal = src->animals;
        int i;

        mFM_SetBlockKindLoadCombi(NULL);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                int src_idx = mNpc_SearchAnimalPersonalID_com(&animal->id, src_animal, ANIMAL_NUM_MAX);

                if (src_idx == -1 && mFRm_search_id(&animal->id, anm_id, ANIMAL_NUM_MAX) != -1) {
                    mNpc_DestroyHouse_block((mFM_fg_c*)dst->fg, &animal->home_info);

                    if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
                        mAN_clear_compress_info_table(animal->id.npc_id, &dst->add_npc.save.regist_add_npc, NULL);
                    }

                    mNpc_ClearAnimalInfo(animal);
                    mNpc_SubNowNpcMax(&dst->now_npc_max);
                }
            }

            animal++;
        }

        mFRm_mergeAnimalMemory(dst->animals, src->animals, src->private_data);
    }

    mFRm_insert_event_info(dst, src);
}

/**
 * @brief Print the saved debug information.
 *
 * This function prints an 'X' to the screen if the saved debug information is available.
 *
 * @param gfxprint A pointer to the gfxprint_t structure for screen printing.
 */
extern void mFRm_PrintSavedDebug(gfxprint_t* gfxprint) {
    // Check if the saved debug information is available
    if (Save_Get(saved_rom_debug) == TRUE) {
        // Set the print color and location
        gfxprint_color(gfxprint, 50, 250, 100, 255);
        gfxprint_locate8x8(gfxprint, 29, 3);
        // Print an 'X' to the screen
        gfxprint_printf(gfxprint, "X");
    }
}

/* Color table for displaying error information */
static u32 l_mfrm_color_table[7][3] = {
    { 0, 0, 0 },       /* Black */
    { 255, 0, 0 },     /* Red */
    { 255, 255, 255 }, /* White */
    { 0, 190, 0 },     /* Green */
    { 100, 100, 100 }, /* Gray */
    { 0, 0, 255 },     /* Blue */
    { 255, 0, 255 }    /* Magenta */
};

/**
 * @brief Clear the error information.
 *
 * This function clears the error information by setting all error numbers
 * to mFRm_NO_ERROR_NO.
 */
extern void mFRm_clear_err_info() {
    int i;
    // Zero out the error information array
    bzero(l_mfrm_err_info, sizeof(mFRm_err_info_c) * mFRm_ERROR_INFO_NUM);

    // Set all error numbers to mFRm_NO_ERROR_NO
    for (i = 0; i < mFRm_ERROR_INFO_NUM; i++) {
        l_mfrm_err_info[i].err_no = mFRm_NO_ERROR_NO;
    }
}

/**
 * @brief Get a free error information slot.
 *
 * This function returns a pointer to the first available error information slot.
 *
 * @param err_info A pointer to the error information array.
 * @param count The number of error information slots.
 * @return mFRm_err_info_c* A pointer to the first available error information slot or NULL if none are available.
 */
static mFRm_err_info_c* mFRm_get_free_errInfo(mFRm_err_info_c* err_info, int count) {
    mFRm_err_info_c* ret = NULL;

    // Iterate through the error information slots
    while (count != 0) {
        // Check if the current slot is available
        if (err_info->err_no == mFRm_NO_ERROR_NO) {
            ret = err_info;
            break;
        }
        err_info++;
        count--;
    }
    return ret;
}

/**
 * @brief Set the error information for a specific process.
 *
 * This function sets the error information for the specified process index and error number.
 *
 * @param err_info A pointer to the error information array.
 * @param proc_idx The process index for which the error occurred.
 * @param err_no The error number to be set.
 */
static void mFRm_set_errInfo(mFRm_err_info_c* err_info, int proc_idx, int err_no) {
    // Get a free error information slot
    mFRm_err_info_c* free = mFRm_get_free_errInfo(err_info, mFRm_ERROR_INFO_NUM);

    // Set the error information if a free slot is available
    if (free != NULL) {
        free->err_no = err_no;
        free->proc_idx = proc_idx;
    }
}

/**
 * @brief Get the number of error information slots with errors.
 *
 * This function returns the number of error information slots with error numbers
 * different from mFRm_NO_ERROR_NO.
 *
 * @param err_info A pointer to the error information array.
 * @param count The number of error information slots.
 * @return int The number of error information slots with errors.
 */
static int mFRm_get_errInfoNum(mFRm_err_info_c* err_info, int count) {
    int ret = 0;

    // Loop through the error information slots
    while (count != 0) {
        // Increment the count if the error number is not mFRm_NO_ERROR_NO
        if (err_info->err_no != mFRm_NO_ERROR_NO) {
            ret++;
        }
        err_info++;
        count--;
    }
    return ret;
}

#define mFRm_ERRORLINE(line) mFRm_set_errInfo(l_mfrm_err_info, (line), l_mfrm_now_color)
#define mFRm_ERROR() mFRm_ERRORLINE(__LINE__)

#include "../src/save_check.c_inc"
#include "../src/save_check_gen.c_inc"
#include "../src/save_check_MYK.c_inc"
#include "../src/save_check_NSW.c_inc"
#include "../src/save_check_take.c_inc"
#include "../src/save_check_YSD.c_inc"
#include "../src/save_check_komatu.c_inc"

/**
 * @brief Perform save data checks.
 *
 * This function performs save data checks for different procedures and
 * increments the color index upon each check.
 */
extern void mFRm_save_data_check() {
    // Define save data check procedures
    static save_check_proc* proc[] = { &sChk_check_save_data,     &sChk_check_save_gen,  &sChk_CheckSaveData_MYK,
                                       &sChk_CheckSaveData_NSW,   &sChk_check_save_take, &sChk_CheckSaveData_YSD,
                                       &sChk_CheckSaveData_komatu };

    int i = 0;
    mFRm_err_info_c* err_info = l_mfrm_err_info;
    l_mfrm_now_color = 0;

    // If zurumode_flag is greater or equal to 2 and scene_no is 7, perform save data checks
    if ((zurumode_flag >= 2) && (Save_Get(scene_no) == 7)) {
        // If there are no errors, perform the save data checks
        if (mFRm_get_errInfoNum(err_info, mFRm_ERROR_INFO_NUM) == 0) {
            while (i < 7) {
                (*proc[i])();
                l_mfrm_now_color++;
                i++;
            }
        }
    }
}

/**
 * @brief Display error information on the screen.
 *
 * This function displays the error information on the screen if there are
 * any errors and if the zurumode_flag is greater than or equal to 2.
 *
 * @param gfxprint A pointer to the gfxprint_t structure for screen printing.
 */
extern void mFRm_display_errInfo(gfxprint_t* gfxprint) {
    mFRm_err_info_c* err_info = l_mfrm_err_info;
    int i;

    // If zurumode_flag is greater or equal to 2 and scene_no is 7, display
    // error information
    if ((zurumode_flag >= 2) && (Save_Get(scene_no) == 7)) {
        gfxprint_locate8x8(gfxprint, 37, 17);
        gfxprint_color(gfxprint, 255, 255, 255, 255);
        gfxprint_printf(gfxprint, "-");

        // If there are errors, display them on the screen
        if (mFRm_get_errInfoNum(err_info, mFRm_ERROR_INFO_NUM) > 0) {
            for (i = 0; i < 10; i++) {
                gfxprint_locate8x8(gfxprint, 30, i + 18);

                // Break the loop if no error is found
                if (err_info->err_no == mFRm_NO_ERROR_NO) {
                    break;
                }

                // Set the color for displaying the error information
                gfxprint_color(gfxprint, l_mfrm_color_table[err_info->err_no][0],
                               l_mfrm_color_table[err_info->err_no][1], l_mfrm_color_table[err_info->err_no][2], 255);

                // Display the error information
                gfxprint_printf(gfxprint, "x%dx %d", err_info->err_no, err_info->proc_idx);
                err_info++;
            }
        }
    }
}
