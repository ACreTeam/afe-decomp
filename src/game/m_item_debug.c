#include "m_item_debug.h"

#include "libultra/libultra.h"
#include "game.h"
#include "m_room_type.h"
#include "padmgr.h"
#include "m_name_table.h"
#include "m_private.h"
#include "m_common_data.h"

typedef struct item_debug_s {
    int enabled;
    int category;
    int index;
} ItemDebug_c;

static char* mItemDebug_category_name_table[mItemDebug_CATEGORY_NUM] = {
    "\xC5\xBC", // mItemDebug_CATEGORY_NONE
    "FTR",      // mItemDebug_CATEGORY_FTR
    "PPR",      // mItemDebug_CATEGORY_PPR
    "MNY",      // mItemDebug_CATEGORY_MNY
    "TOL",      // mItemDebug_CATEGORY_TOL
    "FSH",      // mItemDebug_CATEGORY_FSH
    "CLT",      // mItemDebug_CATEGORY_CLT
    "ELS",      // mItemDebug_CATEGORY_ELS
    "CPT",      // mItemDebug_CATEGORY_CPT
    "WLL",      // mItemDebug_CATEGORY_WLL
    "FOD",      // mItemDebug_CATEGORY_FOD
    "PLT",      // mItemDebug_CATEGORY_PLT
    "MSC",      // mItemDebug_CATEGORY_MSC
    "DRY",      // mItemDebug_CATEGORY_DRY
    "LOT",      // mItemDebug_CATEGORY_LOT
    "IST",      // mItemDebug_CATEGORY_IST
    "HPY",      // mItemDebug_CATEGORY_HPY
    "KAB",      // mItemDebug_CATEGORY_KAB
};

static mActor_name_t mItemDebug_category_start_no_table[mItemDebug_CATEGORY_NUM] = {
    EMPTY_NO,             // mItemDebug_CATEGORY_NONE
    FTR0_NO_START,        // mItemDebug_CATEGORY_FTR
    ITM_PAPER_START,      // mItemDebug_CATEGORY_PPR
    ITM_MONEY_START,      // mItemDebug_CATEGORY_MNY
    ITM_TOOL_START,       // mItemDebug_CATEGORY_TOL
    ITM_FISH_START,       // mItemDebug_CATEGORY_FSH
    ITM_CLOTH_START,      // mItemDebug_CATEGORY_CLT
    ITM_ETC_START,        // mItemDebug_CATEGORY_ELS
    ITM_CARPET_START,     // mItemDebug_CATEGORY_CPT
    ITM_WALL_START,       // mItemDebug_CATEGORY_WLL
    ITM_FOOD_START,       // mItemDebug_CATEGORY_FOD
    ITM_ENV_START,        // mItemDebug_CATEGORY_PLT
    ITM_MINIDISK_START,   // mItemDebug_CATEGORY_MSC
    ITM_DIARY_START,      // mItemDebug_CATEGORY_DRY
    ITM_TICKET_START,     // mItemDebug_CATEGORY_LOT
    ITM_INSECT_START,     // mItemDebug_CATEGORY_IST
    ITM_HUKUBUKURO_START, // mItemDebug_CATEGORY_HPY
    ITM_KABU_START,       // mItemDebug_CATEGORY_KAB
};

static int mItemDebug_category_max_table[mItemDebug_CATEGORY_NUM] = {
    0,              // mItemDebug_CATEGORY_NONE
    FTR_NUM,        // mItemDebug_CATEGORY_FTR
    PAPER_NUM,      // mItemDebug_CATEGORY_PPR
    MONEY_NUM,      // mItemDebug_CATEGORY_MNY
    TOOL_NUM,       // mItemDebug_CATEGORY_TOL
    FISH_NUM,       // mItemDebug_CATEGORY_FSH
    CLOTH_NUM,      // mItemDebug_CATEGORY_CLT
    ETC_NUM,        // mItemDebug_CATEGORY_ELS
    CARPET_NUM,     // mItemDebug_CATEGORY_CPT
    WALL_NUM,       // mItemDebug_CATEGORY_WLL
    FRUIT_NUM,      // mItemDebug_CATEGORY_FOD
    PLANT_NUM,      // mItemDebug_CATEGORY_PLT
    MINIDISK_NUM,   // mItemDebug_CATEGORY_MSC
    DIARY_NUM,      // mItemDebug_CATEGORY_DRY
    TICKET_NUM,     // mItemDebug_CATEGORY_LOT
    INSECT_NUM,     // mItemDebug_CATEGORY_IST
    HUKUBUKURO_NUM, // mItemDebug_CATEGORY_HPY
    KABU_NUM,       // mItemDebug_CATEGORY_KAB
};

/* @unused ? mItemDebug_ItemDebugCt(...) */

static int mItemDebug_FurnitureCanUse(int ftr_idx) {
    if (ftr_idx >= 0 && ftr_idx < FTR_NUM) {
        u8* birth_info_p = mRmTp_CheckFtrBirthInfoTop();

        if (aMR_check_valid_furniture(mNT_ftr_idx_to_ftr_item_no(ftr_idx, mRmTp_DIRECT_SOUTH)) == FALSE) {
            return FALSE;
        }

        switch (birth_info_p[ftr_idx]) {
            case mRmTp_BIRTH_TYPE_FTR_CLOTH:
            case mRmTp_BIRTH_TYPE_FTR_UMBRELLA:
            case mRmTp_BIRTH_TYPE_UNOBTAINABLE:
            case mRmTp_BIRTH_TYPE_MY_ORIGINAL:
            case mRmTp_BIRTH_TYPE_FTR_DIARY:
                return FALSE;
            default:
                break;
        }

        return TRUE;
    }

    return FALSE;
}

static ItemDebug_c l_mItemDebug_work_data;

extern void mItemDebug_ItemDebugMain() {
    if ((gamePT->pads[PAD2].on.button & BUTTON_START) == BUTTON_START) {
        l_mItemDebug_work_data.enabled = (l_mItemDebug_work_data.enabled + 1) & 1;

        if (l_mItemDebug_work_data.enabled != FALSE) {
            bzero(&l_mItemDebug_work_data, sizeof(ItemDebug_c));
            l_mItemDebug_work_data.enabled = TRUE;
        } else {
            bzero(&l_mItemDebug_work_data, sizeof(ItemDebug_c));
        }
    }

    if (l_mItemDebug_work_data.enabled != FALSE) {
        int category;

        if ((gamePT->pads[PAD2].on.button & BUTTON_DUP) == BUTTON_DUP) {
            l_mItemDebug_work_data.index = 0;
            l_mItemDebug_work_data.category++;

            if (l_mItemDebug_work_data.category > mItemDebug_CATEGORY_KAB) {
                l_mItemDebug_work_data.category = 0;
            }
        }

        category = l_mItemDebug_work_data.category;

        if (category == mItemDebug_CATEGORY_FTR) {
            aMR_DeleteFurniture_MarioClub(gamePT);
        }

        if (category != mItemDebug_CATEGORY_NONE) {
            if ((gamePT->pads[PAD2].on.button & BUTTON_DRIGHT) == BUTTON_DRIGHT) {
                /* Holding B increments by 10, holding A increments by 100 */
                if ((gamePT->pads[PAD2].now.button & BUTTON_B) == BUTTON_B) {
                    l_mItemDebug_work_data.index += 10;
                } else if ((gamePT->pads[PAD2].now.button & BUTTON_A) == BUTTON_A) {
                    l_mItemDebug_work_data.index += 100;
                } else {
                    l_mItemDebug_work_data.index++;
                }

                if (l_mItemDebug_work_data.index > mItemDebug_category_max_table[category] - 1) {
                    l_mItemDebug_work_data.index = 0;
                }
            } else if ((gamePT->pads[PAD2].on.button & BUTTON_DLEFT) == BUTTON_DLEFT) {
                /* Holding B increments by 10, holding A increments by 100 */
                if ((gamePT->pads[PAD2].now.button & BUTTON_B) == BUTTON_B) {
                    l_mItemDebug_work_data.index -= 10;
                } else if ((gamePT->pads[PAD2].now.button & BUTTON_A) == BUTTON_A) {
                    l_mItemDebug_work_data.index -= 100;
                } else {
                    l_mItemDebug_work_data.index--;
                }

                if (l_mItemDebug_work_data.index < 0) {
                    l_mItemDebug_work_data.index = 0;
                }
            }
        }

        if ((gamePT->pads[PAD2].on.button & BUTTON_DDOWN) == BUTTON_DDOWN && category != mItemDebug_CATEGORY_NONE) {
            int slot_idx = mPr_GetPossessionItemIdxWithCond(Common_Get(now_private), EMPTY_NO, mPr_ITEM_COND_NORMAL);
            mActor_name_t item;

            if (category != mItemDebug_CATEGORY_FTR) {
                item = mItemDebug_category_start_no_table[category] + l_mItemDebug_work_data.index;
            } else {
                if (mItemDebug_FurnitureCanUse(l_mItemDebug_work_data.index)) {
                    item = mNT_ftr_idx_to_ftr_item_no(l_mItemDebug_work_data.index, mRmTp_DIRECT_SOUTH);
                } else {
                    return;
                }
            }

            if (slot_idx != -1) {
                mPr_SetPossessionItem(Common_Get(now_private), slot_idx, item, mPr_ITEM_COND_NORMAL);
            }
        }

        // Set all items collected
        if ((gamePT->pads[PAD2].on.button & BUTTON_X) == BUTTON_X && Now_Private != NULL) {
            Private_c* priv = Now_Private;
            int i;
            for (i = 0; i < ARRAY_COUNT(priv->furniture_collected_bitfield); i++) {
                priv->furniture_collected_bitfield[i] = 0xFFFFFFFF; // Set all bits to 1
            }

            // Remove the first fish & insect, assumedly to allow for
            // collecting the golden rod & golden net during testing.
            BITCLR(priv->furniture_collected_bitfield[23], 18); // FTR_SUM_MONSHIRO
            BITCLR(priv->furniture_collected_bitfield[25], 2);  // FTR_SUM_FUNA

            for (i = 0; i < ARRAY_COUNT(priv->wall_collected_bitfield); i++) {
                priv->wall_collected_bitfield[i] = 0xFFFFFFFF;   // Set all bits to 1
                priv->carpet_collected_bitfield[i] = 0xFFFFFFFF; // Set all bits to 1
            }

            for (i = 0; i < ARRAY_COUNT(priv->paper_collected_bitfield); i++) {
                priv->paper_collected_bitfield[i] = 0xFFFFFFFF; // Set all bits to 1
            }

            for (i = 0; i < ARRAY_COUNT(priv->music_collected_bitfield); i++) {
                priv->music_collected_bitfield[i] = 0xFFFFFFFF; // Set all bits to 1
            }
        }
    }
}

extern void mItemDebug_ItemDebugDraw(gfxprint_t* gfxprint) {
    int category = l_mItemDebug_work_data.category;

    if (l_mItemDebug_work_data.enabled != FALSE) {
        gfxprint_color(gfxprint, 225, 225, 255, 255);

        if (Common_Get(cur_island_house_p) != NULL &&
            mPr_CheckCmpPersonalID(&Common_Get(cur_island_house_p)->ownerID, &Now_Private->player_ID) == FALSE) {
            gfxprint_color(gfxprint, 225, 0, 0, 255);
        }

        gfxprint_locate8x8(gfxprint, 3, 20);

        if (category != mItemDebug_CATEGORY_NONE) {
            if (category == mItemDebug_CATEGORY_FTR) {
                if (mItemDebug_FurnitureCanUse(l_mItemDebug_work_data.index)) {
                    gfxprint_printf(gfxprint, "%s:%d", mItemDebug_category_name_table[category],
                                    l_mItemDebug_work_data.index);
                } else {
                    gfxprint_printf(gfxprint, "%s:---(%d)", mItemDebug_category_name_table[category],
                                    l_mItemDebug_work_data.index);
                }
            } else {
                gfxprint_printf(gfxprint, "%s:%d", mItemDebug_category_name_table[category],
                                l_mItemDebug_work_data.index);
            }
        } else {
            gfxprint_printf(gfxprint, "\xC5\xBC");
        }
    }
}
