#include "m_monument.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "_mem.h"
#include "libultra/libultra.h"
#include "m_string.h"
#include "m_msg.h"

extern int mMM_check_order(void) {
    int ret = mMM_ORDER_PENDING;
    if (Save_Get(monument_order).name == EMPTY_NO) {
        ret = mMM_ORDER_NONE;
    }

    return ret;
}

extern int mMM_set_order(mMM_order_c* order) {
    int ret = FALSE;

    if (Save_Get(monument_order).name == EMPTY_NO) {
        mActor_name_t* fg_p = mFI_BkNum2UtFGTop_field(order->bx, order->bz);

        if (fg_p != NULL) {
            int monument_count = Save_Get(monument_count);
            int ut = order->ux + order->uz * UT_X_NUM;
            mActor_name_t item = fg_p[ut];

            if (IS_ITEM_MONUMENT(item)) {
                mFI_SetFGStructure_common(item, order->bx, order->bz, order->ux, order->uz, mFI_SET_STRUCTURE_REMOVE);
            } else if (!IS_ITEM_RSV_MONUMENT(item)) {
                monument_count++;
            }

            // Put up monument reserve sign
            fg_p[ut] = order->name - MONUMENT_PARK_CLOCK + RESERVE_PARK_CLOCK;

            if (monument_count > mMM_MONUMENT_MAX) {
                monument_count = mMM_MONUMENT_MAX;
            }
            Save_Set(monument_count, monument_count);
        }

        memcpy(Save_GetPointer(monument_order), order, sizeof(mMM_order_c));
        ret = TRUE;
    }

    return ret;
}

extern void mMM_clear_order(void) {
    bzero(Save_GetPointer(monument_order), sizeof(mMM_order_c));
}

extern int mMM_set_monument(void) {
    int ret = FALSE;

    if (mMM_check_order() == mMM_ORDER_PENDING) {
        mMM_order_c* order = Save_GetPointer(monument_order);

        if (mFI_SetFGStructure_common(order->name, order->bx, order->bz, order->ux, order->uz, mFI_SET_STRUCTURE_SET) ==
            TRUE) {
            mMM_clear_order();
            ret = TRUE;
        }
    }

    return ret;
}

typedef struct monument_candidate_s {
    u8 ux;
    u8 uz;
    mActor_name_t name;
} mMM_candidate_c;

extern int mMM_clear_monument(mMM_order_c* order) {
    int ret = FALSE;
    mActor_name_t* fg_p = mFI_BkNum2UtFGTop_field(order->bx, order->bz);

    if (fg_p != NULL) {
        int ut = order->ux + order->uz * UT_X_NUM;
        mActor_name_t item = fg_p[ut];

        if (IS_ITEM_MONUMENT(item) || IS_ITEM_RSV_MONUMENT(item)) {
            if (mFI_SetFGStructure_common(order->name, order->bx, order->bz, order->ux, order->uz, mFI_SET_STRUCTURE_REMOVE) == TRUE) {
                int monument_count = Save_Get(monument_count);
                monument_count--;
                if (monument_count < 0) {
                    monument_count = 0;
                }
                Save_Set(monument_count, monument_count);
                ret = TRUE;
            }
        }
    }

    return ret;
}

#define MAX_CANDIDATE_COUNT 3

extern int mMM_make_candidate_place_list(mMM_order_c* order, int count) {
    int list_size = 0;
    int bx;
    int bz;
    
    mMM_candidate_c candidate[MAX_CANDIDATE_COUNT];

    if (order != NULL) {
        bzero(order, count * sizeof(mMM_order_c));

        for (bz = 1; bz < FG_BLOCK_Z_NUM + 1; bz++) {
            for (bx = 1; bx < FG_BLOCK_X_NUM + 1; bx++) {
                mActor_name_t* fg_p = mFI_BkNum2UtFGTop_field(bx, bz);
                
                if (fg_p != NULL) {
                    int candidate_count = 0;
                    int ux;
                    int uz;

                    for (uz = 0; uz < UT_Z_NUM; uz++) {
                        for (ux = 0; ux < UT_X_NUM; ux++) {
                            if (mNT_IS_RESERVE(*fg_p)) {
                                candidate[candidate_count].ux = ux;
                                candidate[candidate_count].uz = uz;
                                candidate[candidate_count].name = *fg_p;
                                candidate_count++;
                                if (candidate_count >= MAX_CANDIDATE_COUNT) {
                                    ux = UT_X_NUM;
                                    uz = UT_Z_NUM;
                                }
                            } else if (IS_ITEM_MONUMENT(*fg_p) || IS_ITEM_RSV_MONUMENT(*fg_p)) {
                                candidate_count = 0;
                                list_size++;

                                order->bx = bx;
                                order->bz = bz;
                                order->ux = ux;
                                order->uz = uz;
                                order->name = *fg_p;
                                order++;
                                if (list_size >= count) {
                                    return list_size;
                                }

                                ux = UT_X_NUM;
                                uz = UT_Z_NUM;
                            }

                            fg_p++;
                        }
                    }

                    while (candidate_count != 0) {
                        candidate_count--;
                        list_size++;

                        order->bx = bx;
                        order->bz = bz;
                        order->ux = candidate[candidate_count].ux;
                        order->uz = candidate[candidate_count].uz;
                        order->name = candidate[candidate_count].name;
                        order++;
                        if (list_size >= count) {
                            return list_size;
                        }
                    }
                }
            }
        }
    }

    return list_size;
}

extern int mMM_get_monument_price(mActor_name_t monument) {
    static int price_table[] = {
        18000, // MONUMENT_PARK_CLOCK
        14000, // MONUMENT_GAS_LAMP
        27000, // MONUMENT_WINDMILL
        28000, // MONUMENT_FLOWER_CLOCK
        15000, // MONUMENT_HELIPAD
        18000, // MONUMENT_WIND_TURBINE
        17000, // MONUMENT_PIPE_STACK
        26000, // MONUMENT_STONEHENGE
        32000, // MONUMENT_EGG
        13000, // MONUMENT_FOOTPRINTS
        20000, // MONUMENT_GEOGLYPH
        24000, // MONUMENT_MUSHROOM
        13000, // MONUMENT_GUIDEPOST
        14000, // MONUMENT_WELL
        30000, // MONUMENT_FOUNTAIN
        0,     // @BUG - devs added an extra price
    };

    int price = 0;

    if (IS_ITEM_MONUMENT(monument)) {
        price = price_table[monument - MONUMENT_PARK_CLOCK];
    }

    return price;
}

extern mActor_name_t mMM_get_monument_name(int idx) {
    static mActor_name_t name_table[mMM_MONUMENT_SET_NUM][3] = {
        {MONUMENT_STONEHENGE, MONUMENT_GEOGLYPH, MONUMENT_WELL},
        {MONUMENT_PARK_CLOCK, MONUMENT_WINDMILL, MONUMENT_HELIPAD},
        {MONUMENT_GAS_LAMP, MONUMENT_WIND_TURBINE, MONUMENT_FLOWER_CLOCK},
        {MONUMENT_FOUNTAIN, MONUMENT_GUIDEPOST, MONUMENT_PIPE_STACK},
        {MONUMENT_MUSHROOM, MONUMENT_FOOTPRINTS, MONUMENT_EGG},
    };

    int set = Save_Get(monument_set);
    if (set < 0 || set >= mMM_MONUMENT_SET_NUM) {
        set = 0;
    }

    if (idx < 0 || idx >= 3) {
        idx = 0;
    }

    return name_table[set][idx];
}

extern int mMM_get_monument_idx(mActor_name_t monument) {
    int ret = -1;

    if (IS_ITEM_MONUMENT(monument)) {
        ret = monument - MONUMENT_PARK_CLOCK;
    }

    return ret;
}

static mActor_name_t mMM_check_monument_in_block(int bx, int bz) {
    mActor_name_t ret = EMPTY_NO;
    mActor_name_t* fg_p = mFI_BkNum2UtFGTop_field(bx, bz);
    
    if (fg_p != NULL) {
        int i;

        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (IS_ITEM_MONUMENT(*fg_p)) {
                ret = *fg_p;
                break;
            } else if (IS_ITEM_DUMMY_MONUMENT(*fg_p)) {
                ret = *fg_p - DUMMY_MONUMENT_PARK_CLOCK + MONUMENT_PARK_CLOCK;
                break;
            }

            fg_p++;
        }
    }

    return ret;
}

extern mActor_name_t mMM_check_monument_in_npc_house_block(ACTOR* actorx) {
    mActor_name_t ret = EMPTY_NO;

    if (actorx != NULL && ITEM_NAME_GET_TYPE(actorx->npc_id) == NAME_TYPE_NPC) {
        Animal_c* animal = mNpc_GetAnimalInfoP(actorx->npc_id);

        if (animal != NULL) {
            ret = mMM_check_monument_in_block(animal->home_info.bx, animal->home_info.bz);
        }
    }

    return ret;
}

extern void mMM_set_monument_name_str(mActor_name_t monument, int str_no) {
    u8 name[mString_DEFAULT_STR_SIZE];
    int idx = mMM_get_monument_idx(monument);

    if (idx == -1) {
        idx = 0;
    }

    mString_Load_StringFromRom(name, sizeof(name), 0x78C + idx);
    mMsg_Set_item_str(mMsg_Get_base_window_p(), str_no, name, sizeof(name));
}
