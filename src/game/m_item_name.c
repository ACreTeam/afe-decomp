#include "m_item_name.h"

#include "m_name_table.h"
#include "m_lib.h"
#include "m_room_type.h"
#include "m_actor_type.h"
#include "m_font.h"
#include "ac_my_room.h"
#include "m_common_data.h"

/**
 * @brief Copies an item name from src to dst.
 *
 * @param dst Destination item name buffer
 * @param src Source item name buffer
 **/
static void mIN_dma_itemName(u8* dst, u8* src) {
    mem_copy(dst, src, mIN_ITEM_NAME_LEN);
}

/**
 * @brief Retrieves and copies an item name to a destination buffer from an item no.
 *
 * @param dst The item name destination buffer
 * @param item The item no whose name will be retrieved
 **/
extern void mIN_copy_name_str(u8* dst, mActor_name_t item) {
    // clang-format off
    static u8* itemName_table[ITEM1_CAT_NUM] = {
        itemName_paper,
        itemName_money,
        itemName_tool,
        itemName_fish,
        itemName_cloth,
        itemName_etc,
        itemName_carpet,
        itemName_wall,
        itemName_fruit,
        itemName_plant,
        itemName_minidisk,
        itemName_dummy,
        itemName_ticket,
        itemName_insect,
        itemName_hukubukuro,
        itemName_kabu
    };
    // clang-format on

    static u8 unknown_ftr_str[mIN_ITEM_NAME_LEN] = {
        CHAR_PP_005, CHAR_PP_233, CHAR_PP_063, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
        CHAR_PP_032, CHAR_PP_032
    };

    u8 item_name[mIN_ITEM_NAME_LEN];
    u32 itm = item;
    mActor_name_t item_no = mRmTp_FtrItemNo2Item1ItemNo(item, FALSE);

    switch (ITEM_NAME_GET_TYPE(item_no)) {
        case NAME_TYPE_ITEM1: {
            mIN_dma_itemName(item_name, itemName_table[ITEM_NAME_GET_CAT(item_no)] +
                                            ITEM_NAME_GET_INDEX(item_no) * mIN_ITEM_NAME_LEN);
            mem_copy(dst, item_name, mIN_ITEM_NAME_LEN);
            break;
        }

        case NAME_TYPE_FTR0: {
            if (aMR_check_valid_furniture(item_no) == TRUE) {
                mIN_dma_itemName(item_name, ftrName_table + ((item_no / 4) & 0x3FF) * mIN_ITEM_NAME_LEN);
                mem_copy(dst, item_name, mIN_ITEM_NAME_LEN);
            } else {
                mem_copy(dst, unknown_ftr_str, mIN_ITEM_NAME_LEN);
            }
            break;
        }

        case NAME_TYPE_FTR1: {
            if (aMR_check_valid_furniture(item_no) == TRUE) {
                mIN_dma_itemName(item_name, ftrName2_table + ((item_no / 4) & 0x3FF) * mIN_ITEM_NAME_LEN);
                mem_copy(dst, item_name, mIN_ITEM_NAME_LEN);
            } else {
                mem_copy(dst, unknown_ftr_str, mIN_ITEM_NAME_LEN);
            }
            break;
        }

        default: {
            if (ITEM_IS_SIGNBOARD(item_no)) {
                mIN_dma_itemName(item_name,
                                    itemName_table[ITEM1_CAT_ETC] + (ITM_SIGNBOARD & 0xFF) * mIN_ITEM_NAME_LEN);
                mem_copy(dst, item_name, mIN_ITEM_NAME_LEN);
            } else if (item_no == EMPTY_NO) {
                mem_clear(dst, mIN_ITEM_NAME_LEN, CHAR_SPACE);
            }
            break;
        }
    }
}

/**
 * @brief Copies a cloth name string to a destination buffer from a cloth item no and a design index.
 *
 * @param dst The cloth name destination buffer
 * @param cloth The cloth item no whose name will be retrieved
 * @param design_idx The design index whose name will be retrieved
 **/
extern void mIN_copy_cloth_name_str(u8* dst, mActor_name_t cloth, u8 design_idx) {
    cloth = mRmTp_FtrItemNo2Item1ItemNo(cloth, FALSE);

    if (cloth == RSV_CLOTH) {
        mem_copy(dst, Now_Private->my_org[design_idx & 7].name, mIN_ITEM_NAME_LEN);
    } else if (cloth == RSV_CLOTH1) {
        mem_copy(dst, Save_Get(needlework).original_design[design_idx & 7].name, mIN_ITEM_NAME_LEN);
    } else {
        mIN_copy_name_str(dst, cloth);
    }
}

/**
 * @brief Gets the artticle type for a given item.
 *
 * @param item The item no whose article type will be retrieved
 * @return mIN_ARTICLE_* item article
 **/
extern int mIN_get_item_article(mActor_name_t item) {
    int article = mIN_ARTICLE_NONE;

    return article;
}
