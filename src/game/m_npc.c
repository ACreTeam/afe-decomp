#include "m_npc.h"

#include "m_font.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_mail_check.h"
#include "m_mail_check_ovl.h"
#include "m_handbill.h"
#include "m_string.h"
#include "m_shop.h"
#include "m_house.h"
#include "m_event_map_npc.h"
#include "ac_my_room.h"
#include "m_mail_password_check.h"
#include "libultra/libultra.h"
#include "jsyswrap.h"
#include "ac_npc.h"
#include "m_matching.h"
#include "m_text.h"
#include "m_msg.h"

typedef struct sp_actor_name_data_s {
    mActor_name_t sp_npc_id;
    u16 sex;
    int name_str_no;
    int sound_id;
} mNpc_Sp_Npc_Name_c;

static mNpc_Sp_Npc_Name_c l_sp_actor_name[] = {
    // Tom Nook
    { SP_NPC_SHOP_MASTER, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SHOP_MASTERSP, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SHOP_MASTERSP_2, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SHOP_MASTERSP_3, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SHOP_MASTERSP_4, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SHOP_MASTER_NIGHT, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_CONV_MASTER_NIGHT, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SUPER_MASTER_NIGHT, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_DEPART_MASTER_NIGHT, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_CONV_MASTER, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_SUPER_MASTER, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_DEPART_MASTER, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE2, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE_1, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE2_1, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE_2, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE2_2, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE_3, mPr_SEX_MALE, 0x205, 2 },
    { SP_NPC_RCN_GUIDE2_3, mPr_SEX_MALE, 0x205, 2 },
    // Redd
    { SP_NPC_BROKER, mPr_SEX_MALE, 0x206, 2 },
    { SP_NPC_EV_BROKER2, mPr_SEX_MALE, 0x206, 2 },
    { SP_NPC_EV_YOMISE, mPr_SEX_MALE, 0x206, 2 },
    { SP_NPC_EV_YOMISE2, mPr_SEX_MALE, 0x206, 2 },
    // Katrina
    { SP_NPC_GYPSY, mPr_SEX_FEMALE, 0x207, 2 },
    { SP_NPC_EV_MIKO, mPr_SEX_FEMALE, 0x207, 2 },
    // Saharah
    { SP_NPC_CARPETPEDDLER, mPr_SEX_MALE, 0x208, 2 },
    // Wendell
    { SP_NPC_ARTIST, mPr_SEX_MALE, 0x209, 3 },
    // Jingle
    { SP_NPC_SANTA, mPr_SEX_MALE, 0x20A, 2 },
    // Gracie
    { SP_NPC_DESIGNER, mPr_SEX_MALE, 0x20B, 2 },
    // Joan
    { SP_NPC_KABUPEDDLER, mPr_SEX_FEMALE, 0x20C, 8 },
    // Pelly
    { SP_NPC_POST_GIRL, mPr_SEX_FEMALE, 0x20D, 4 },
    // Phyllis
    { SP_NPC_POST_GIRL2, mPr_SEX_FEMALE, 0x20E, 4 },
    // Pete
    { SP_NPC_POST_MAN, mPr_SEX_MALE, 0x20F, 3 },
    // Copper
    { SP_NPC_POLICE, mPr_SEX_MALE, 0x210, 2 },
    // Booker
    { SP_NPC_POLICE2, mPr_SEX_MALE, 0x6D9, 3 },
    // Copper
    { SP_NPC_EV_TAISOU_0, mPr_SEX_MALE, 0x210, 2 },
    // Porter
    { SP_NPC_STATION_MASTER, mPr_SEX_MALE, 0x211, 2 },
    // Jack
    { SP_NPC_HALLOWEEN, mPr_SEX_MALE, 0x212, 3 },
    // Gyroid
    { ACTOR_PROP_HANIWA0, mPr_SEX_OTHER, 0x213, 2 },
    { ACTOR_PROP_HANIWA1, mPr_SEX_OTHER, 0x213, 2 },
    { ACTOR_PROP_HANIWA2, mPr_SEX_OTHER, 0x213, 2 },
    { ACTOR_PROP_HANIWA3, mPr_SEX_OTHER, 0x213, 2 },
    // K.K. Slider
    { SP_NPC_P_SEL, mPr_SEX_OTHER, 0x214, 2 },
    { SP_NPC_TOTAKEKE, mPr_SEX_OTHER, 0x214, 2 },
    { SP_NPC_TOTAKEKE_BIRTHDAY, mPr_SEX_OTHER, 0x214, 2 },
    { SP_NPC_RTC, mPr_SEX_OTHER, 0x214, 2 },
    // Rover
    { SP_NPC_GUIDE, mPr_SEX_MALE, 0x215, 2 },
    { SP_NPC_GUIDE2, mPr_SEX_MALE, 0x215, 2 },
    // Chip
    { SP_NPC_ANGLER, mPr_SEX_MALE, 0x216, 2 },
    // Timmy
    { SP_NPC_MAMEDANUKI0, mPr_SEX_MALE, 0x217, 2 },
    // Tommy
    { SP_NPC_MAMEDANUKI1, mPr_SEX_MALE, 0x218, 2 },
    { SP_NPC_MAMEDANUKI0_NIGHT, mPr_SEX_MALE, 0x217, 2 },
    { SP_NPC_MAMEDANUKI1_NIGHT, mPr_SEX_MALE, 0x218, 2 },
    // Resetti
    { SP_NPC_MAJIN, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN2, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN3, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN4, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN5, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN_D07C, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_MAJIN_D07D, mPr_SEX_MALE, 0x4E0, 2 },
    // Don
    { SP_NPC_MAJIN_BROTHER, mPr_SEX_MALE, 0x6D8, 2 },
    // Resetti
    { SP_NPC_MAJIN_D080, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_EV_MAJIN, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_RESET_MAJIN, mPr_SEX_MALE, 0x4E0, 2 },
    { SP_NPC_RESET_BROTHER, mPr_SEX_MALE, 0x6D8, 2 }, // Don
    // Gulliver
    { SP_NPC_EV_DOZAEMON, mPr_SEX_MALE, 0x4E1, 2 },
    // Snowman
    { ETC_SNOWMAN_BALL_A, mPr_SEX_MALE, 0x4E2, 2 },
    { ETC_SNOWMAN_BALL_B, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN0, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN1, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN2, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN3, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN4, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN5, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN6, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN7, mPr_SEX_MALE, 0x4E2, 2 },
    { SNOWMAN8, mPr_SEX_MALE, 0x4E2, 2 },
    // Tortimer
    { SP_NPC_EV_SONCHO, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_EV_SONCHO2, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_SONCHO_D078, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_SONCHO_D079, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_SONCHO, mPr_SEX_MALE, 0x4E3, 2 },
    { SP_NPC_EV_SPEECH_SONCHO, mPr_SEX_MALE, 0x4E3, 2 },
    // Blathers
    { SP_NPC_CURATOR, mPr_SEX_MALE, 0x4E4, 2 },
    // Mabel
    { SP_NPC_NEEDLEWORK0, mPr_SEX_FEMALE, 0x4E5, 4 },
    // Sabel
    { SP_NPC_NEEDLEWORK1, mPr_SEX_FEMALE, 0x4E6, 4 },
    // Kapp'n
    { SP_NPC_SENDO, mPr_SEX_MALE, 0x4E7, 2 },
    // Wisp
    { SP_NPC_EV_GHOST, mPr_SEX_MALE, 0x4E8, 2 },
    // Blanca
    { SP_NPC_MASK_CAT, mPr_SEX_MALE, 0x4E9, 4 },
    { SP_NPC_MASK_CAT2, mPr_SEX_MALE, 0x4E9, 4 },
    // Franklin
    { SP_NPC_TURKEY, mPr_SEX_MALE, 0x6DA, 2 },
    // Farley
    { SP_NPC_HEM, mPr_SEX_MALE, 0x6DB, 9 }
};

static u8 l_no_name_npc_name[ANIMAL_NAME_LEN] = { CHAR_PP_212, CHAR_PP_142, CHAR_PP_166,
                                                  CHAR_PP_144, CHAR_PP_133, CHAR_PP_066 };
static u8 l_no_ending_npc_ending[ANIMAL_CATCHPHRASE_LEN] = { CHAR_PP_211, CHAR_PP_175, CHAR_PP_157, CHAR_PP_032 };
static u8 l_nomi_npc_ending[ANIMAL_CATCHPHRASE_LEN];

static void mNpc_MakeRandTable(int* table, int count, int swap_num) {
    int a;
    int b;
    int i;
    f32 c = count;

    for (i = 0; i < count; i++) {
        table[i] = i;
    }

    while (swap_num--) {
        int temp;

        a = RANDOM_F(c);
        b = RANDOM_F(c);
        temp = table[a];

        table[a] = table[b];
        table[b] = temp;
    }
}

static void mNpc_ClearBufSpace1(u8* buf, int size) {
    mem_clear(buf, size, CHAR_SPACE);
}

extern void mNpc_AddNowNpcMax(u8* npc_max) {
    if (npc_max[0] < ANIMAL_NUM_MAX) {
        npc_max[0]++;
    }
}

extern void mNpc_SubNowNpcMax(u8* npc_max) {
    if (npc_max[0] > ANIMAL_NUM_MIN) {
        npc_max[0]--;
    }
}

extern void mNpc_ClearAnimalPersonalID(AnmPersonalID_c* pid) {
    pid->npc_id = EMPTY_NO;
    pid->land_id = 0xFFFF;
    pid->looks = mNpc_LOOKS_UNSET;
    mNPS_reset_schedule_area(pid);
    mLd_ClearLandName(pid->land_name);
    mem_clear(pid->name, ANIMAL_NAME_LEN, CHAR_PP_191); // replaced with the smile character?
    pid->add_npc_id = 0;
}

extern int mNpc_CheckFreeAnimalPersonalID(AnmPersonalID_c* pid) {
    int res = FALSE;

    if ((pid->npc_id == EMPTY_NO) || (ITEM_NAME_GET_TYPE(pid->npc_id) != NAME_TYPE_NPC)) {
        res = TRUE;
    }

    return res;
}

extern void mNpc_CopyAnimalPersonalID(AnmPersonalID_c* dst, AnmPersonalID_c* src) {
    if (src != NULL && dst != NULL && ITEM_NAME_GET_TYPE(src->npc_id) == NAME_TYPE_NPC) {
        mem_copy((u8*)dst, (u8*)src, sizeof(AnmPersonalID_c));
    }
}

extern int mNpc_CheckCmpAnimalNameStr(u8* name0, u8* name1) {
    int i;

    for (i = 0; i < ANIMAL_NAME_LEN; i++) {
        if (*name0 != *name1) {
            return FALSE;
        }

        name0++;
        name1++;
    }

    return TRUE;
}

extern int mNpc_CheckCmpAnimalPersonalID(AnmPersonalID_c* pid0, AnmPersonalID_c* pid1) {
    int res = FALSE;

    if (pid0 != NULL && pid1 != NULL && pid0->land_id == pid1->land_id &&
        mLd_CheckCmpLandName(pid0->land_name, pid1->land_name) == TRUE) {
        if (IS_NPC_ADD_NPC(pid1->npc_id) && IS_NPC_ADD_NPC(pid0->npc_id)) {
            if (mNpc_CheckCmpAnimalNameStr(pid0->name, pid1->name) == TRUE && pid0->add_npc_id == pid1->add_npc_id) {
                res = TRUE;
            }
        } else {
            if (!IS_NPC_ADD_NPC(pid1->npc_id) && !IS_NPC_ADD_NPC(pid0->npc_id) && pid0->npc_id == pid1->npc_id &&
                mNpc_CheckCmpAnimalNameStr(pid0->name, pid1->name) == TRUE) {
                res = TRUE;
            }
        }
    }
    return res;
}

extern int mNpc_GetAnimalNum() {
    Animal_c* animal = Save_Get(animals);
    int num = 0;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            num++;
        }

        animal++;
    }

    return num;
}

extern void mNpc_SetParentName(Animal_c* animal, PersonalID_c* parent_id) {
    if (parent_id != NULL && animal != NULL && mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
        mPr_NullCheckPersonalID(parent_id) == FALSE && mPr_NullCheckPersonalID(&animal->parent_id) == TRUE) {
        mPr_CopyPersonalID(&animal->parent_id, parent_id);
    }
}

extern void mNpc_SetParentNameAllAnimal() {
    Private_c* priv = Now_Private;

    if (priv != NULL) {
        PersonalID_c* parent_id = &priv->player_ID;
        Animal_c* animal = Save_Get(animals);
        int i;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            mNpc_SetParentName(animal, parent_id);
            animal++;
        }
    }
}

extern void mNpc_ClearAnimalMail(Anmplmail_c* mail) {
    mail->font = 0xFF;
    mail->paper_type = 0;
    mail->present = EMPTY_NO;
    mem_clear(mail->header, sizeof(mail->header), CHAR_SPACE);
    mem_clear(mail->body, sizeof(mail->body), CHAR_SPACE);
    mem_clear(mail->footer, sizeof(mail->footer), CHAR_SPACE);
    mail->date.year = mTM_rtcTime_ymd_clear_code.year;
    mail->date.month = mTM_rtcTime_ymd_clear_code.month;
    mail->date.day = mTM_rtcTime_ymd_clear_code.day;
}

extern void mNpc_ClearAnimalMemory(Anmmem_c* memory, int num) {
    for (; num != 0; num--) {
        if (memory != NULL) {
            mPr_ClearPersonalID(&memory->memory_player_id);
            lbRTC_TimeCopy(&memory->last_speak_time, &mTM_rtcTime_clear_code);
            mLd_ClearLandName(memory->memuni.land.name);
            memory->memuni.land.id = 0;
            memory->saved_town_tune = 0;
            memory->friendship = 0;
            memory->letter_info.exists = FALSE;
            memory->letter_info.cond = mNpc_LETTER_RANK_BAD;
            memory->letter_info.send_reply = FALSE;
            memory->letter_info.has_present_cloth = FALSE;
            mNpc_ClearAnimalMail(&memory->letter);
        }

        memory++;
    }
}

/* TODO: this probably implies the union is on the memory itself and not a struct inside it */
extern void mNpc_ClearIslandAnimalMemory(Anmmem_c* memory, int num) {
    for (; num != 0; num--) {
        if (memory != NULL) {
            mPr_ClearPersonalID(&memory->memory_player_id);
            lbRTC_TimeCopy(&memory->last_speak_time, &mTM_rtcTime_clear_code);
            bzero(&memory->memuni.island, sizeof(memuni_u));
            memory->saved_town_tune = 0;
            memory->friendship = 0;
            memory->letter_info.exists = FALSE;
            memory->letter_info.cond = mNpc_LETTER_RANK_BAD;
            memory->letter_info.send_reply = FALSE;
            memory->letter_info.has_present_cloth = FALSE;
            mNpc_ClearAnimalMail(&memory->letter);
        }

        memory++;
    }
}

extern void mNpc_CopyAnimalMemory(Anmmem_c* dst, Anmmem_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(Anmmem_c));
}

#ifndef BUGFIXES
extern int mNpc_AddFriendship(Anmmem_c* memory, int amount) {
    int friendship;
    int ret = FALSE;

    /* @BUG - devs checked for memory being NULL *after* deferencing it */
    friendship = memory->friendship + amount;
    if (memory != NULL) {
        if (friendship > 127) {
            memory->friendship = 127;
        } else if (friendship < -128) {
            memory->friendship = -128;
        } else {
            memory->friendship = friendship;
        }

        ret = TRUE;
    }
    return ret;
}
#else
extern int mNpc_AddFriendship(Anmmem_c* memory, int amount) {
    int friendship;
    int ret = FALSE;

    if (memory != NULL) {
        friendship = memory->friendship + amount;

        if (friendship > 127) {
            memory->friendship = 127;
        } else if (friendship < -128) {
            memory->friendship = -128;
        } else {
            memory->friendship = friendship;
        }

        ret = TRUE;
    }
    return ret;
}
#endif

extern int mNpc_AddFriendshipPlayer_id(PersonalID_c* pid, AnmPersonalID_c* anm_id, int amount) {
    Animal_c* animal;
    int ret = FALSE;
    int idx;
    int mem_idx;

    if (pid != NULL && mPr_NullCheckPersonalID(pid) == FALSE) {
        idx = mNpc_SearchAnimalPersonalID(anm_id);

        if (idx != -1) {
            animal = Save_Get(animals) + idx;
            mem_idx = mNpc_GetAnimalMemoryIdx(pid, animal->memories, ANIMAL_MEMORY_NUM);

            if (mem_idx != -1) {
                ret = mNpc_AddFriendship(animal->memories + mem_idx, amount);
            }
        }
    }

    return ret;
}

extern int mNpc_AddFriendshipPlayer(PersonalID_c* pid, mActor_name_t npc_id, int amount) {
    Animal_c* animal;
    int ret = FALSE;
    int idx;
    int mem_idx;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC && pid != NULL && mPr_NullCheckPersonalID(pid) == FALSE) {
        idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_id, ANIMAL_NUM_MAX);

        if (idx != -1) {
            animal = Save_Get(animals) + idx;
            mem_idx = mNpc_GetAnimalMemoryIdx(pid, animal->memories, ANIMAL_MEMORY_NUM);

            if (mem_idx != -1) {
                ret = mNpc_AddFriendship(animal->memories + mem_idx, amount);
            }
        }
    }

    return ret;
}

extern int mNpc_AddFriendshipNowPlayer(AnmPersonalID_c* anm_id, int amount) {
    int ret = FALSE;

    if (Now_Private != NULL) {
        ret = mNpc_AddFriendshipPlayer_id(&Now_Private->player_ID, anm_id, amount);
    }

    return ret;
}

extern int mNpc_CheckFreeAnimalMemory(Anmmem_c* memory) {
    int res = FALSE;

    if (mPr_NullCheckPersonalID(&memory->memory_player_id) == TRUE) {
        res = TRUE;
    }

    return res;
}

extern void mNpc_RenewalAnimalMemory() {
    Private_c* priv;
    Animal_c* animal = Save_Get(animals);
    Anmmem_c* memory;
    int i;
    int j;
    int k;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        memory = animal->memories;

        for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
            if (mNpc_CheckFreeAnimalMemory(memory) == FALSE &&
                mLd_CheckThisLand(memory->memory_player_id.land_name, memory->memory_player_id.land_id) == TRUE) {
                priv = Save_Get(private_data);

                for (k = 0; k < PLAYER_NUM; k++) {
                    if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE &&
                        mPr_CheckCmpPersonalID(&priv->player_ID, &memory->memory_player_id) == TRUE) {
                        break;
                    }

                    priv++;
                }

                if (k == PLAYER_NUM) {
                    mNpc_ClearAnimalMemory(memory, 1); // player was deleted so free the memory
                }
            }

            memory++;
        }

        animal++;
    }
}

extern int mNpc_GetFreeAnimalMemoryIdx(Anmmem_c* memory, int num) {
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == TRUE) {
            res = i;
            break;
        }

        memory++;
    }

    return res;
}

extern int mNpc_GetOldPlayerAnimalMemoryIdx(Anmmem_c* memory, int num) {
    Private_c* priv;
    int res = -1;
    int i;
    int j;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE &&
            mLd_CheckThisLand(memory->memory_player_id.land_name, memory->memory_player_id.land_id) == TRUE) {
            priv = Save_Get(private_data);

            for (j = 0; j < PLAYER_NUM; j++) {
                if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE &&
                    mPr_CheckCmpPersonalID(&priv->player_ID, &memory->memory_player_id) == TRUE) {
                    break;
                }

                priv++;
            }

            /* memory belongs to a player from this town which was deleted */
            if (j == PLAYER_NUM) {
                res = i;
                break;
            }
        }

        memory++;
    }

    return res;
}

extern int mNpc_ForceGetFreeAnimalMemoryIdx(Animal_c* animal, Anmmem_c* memory, int num) {
    Anmmem_c* mem_p = memory;
    Anmmem_c* chosen_mem = NULL;
    int free_idx = mNpc_GetFreeAnimalMemoryIdx(memory, num);
    int i;

    if (free_idx == -1) {
        for (i = 0; i < num; i++) {
            if (mLd_CheckThisLand(memory->memory_player_id.land_name, memory->memory_player_id.land_id) == FALSE) {
                if (chosen_mem != NULL) {
                    if (chosen_mem->letter_info.exists == memory->letter_info.exists) {
                        if (chosen_mem->friendship > memory->friendship) {
                            chosen_mem = memory;
                            free_idx = i;
                        } else if (chosen_mem->friendship == memory->friendship) {
                            if (lbRTC_IsOverTime(&chosen_mem->last_speak_time, &memory->last_speak_time) ==
                                lbRTC_LESS) {
                                chosen_mem = memory;
                                free_idx = i;
                            }
                        }
                    } else if (memory->letter_info.exists == FALSE) {
                        chosen_mem = memory;
                        free_idx = i;
                    }
                } else {
                    chosen_mem = memory;
                    free_idx = i;
                }
            }

            memory++;
        }
    } else {
        chosen_mem = memory + free_idx;
    }

    if (free_idx == -1 || chosen_mem == NULL) {
        free_idx = mNpc_GetOldPlayerAnimalMemoryIdx(mem_p, num);

        if (free_idx == -1) {
            free_idx = 0; // all else failed, so pick the first memory
        }

        chosen_mem = mem_p + free_idx;
    }

    if (chosen_mem != NULL) {
        if (mNpc_CheckIslandAnimalID(&animal->id) == FALSE) {
            mNpc_ClearAnimalMemory(chosen_mem, 1);
        } else {
            mNpc_ClearIslandAnimalMemory(chosen_mem, 1);
        }
    }

    return free_idx;
}

static void mNpc_ClearRelationPoint(s8* relation_point) {
    bzero(relation_point, membersize(Animal_c, animal_relations));
}

static void mNpc_ClearRelationPointOthers(int idx) {
    Animal_c* animal = Save_Get(animals);
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i != idx) {
            animal->animal_relations[idx] = 0;
        }

        animal++;
    }

    mNpc_ClearRelationPoint(Save_Get(animals[idx]).animal_relations);
}

static void mNpc_AddRelationPoint_common(Animal_c* animal, Animal_c* other_animal, int anm_idx, int other_idx,
                                         int amount) {
    int relation = animal->animal_relations[other_idx] + amount;

    if (relation < -120 || amount < -240) {
        relation = -120;
    } else if (relation > 120 || amount > 240) {
        relation = 120;
    }

    animal->animal_relations[other_idx] = relation;
    other_animal->animal_relations[anm_idx] = relation;
}

extern int mNpc_AddRelationPoint_id(AnmPersonalID_c* from_id, AnmPersonalID_c* to_id, int amount) {
    Animal_c* from_animal;
    Animal_c* to_animal;
    int from_idx;
    int to_idx;
    int ret = FALSE;

    if (from_id != NULL && to_id != NULL && mNpc_CheckFreeAnimalPersonalID(from_id) == FALSE &&
        mNpc_CheckFreeAnimalPersonalID(to_id) == FALSE) {
        from_idx = mNpc_SearchAnimalPersonalID(from_id);
        to_idx = mNpc_SearchAnimalPersonalID(to_id);

        if (from_idx != -1 && to_idx != -1 && from_idx != to_idx) {
            from_animal = Save_Get(animals) + from_idx;
            to_animal = Save_Get(animals) + to_idx;
            mNpc_AddRelationPoint_common(from_animal, to_animal, from_idx, to_idx, amount);
            ret = TRUE;
        }
    }

    return ret;
}

extern int mNpc_AddRelationPoint(Animal_c* from_animal, Animal_c* to_animal, int amount) {
    int from_idx;
    int to_idx;
    int ret = FALSE;

    if (from_animal != NULL && to_animal != NULL && mNpc_CheckFreeAnimalPersonalID(&from_animal->id) == FALSE &&
        mNpc_CheckFreeAnimalPersonalID(&to_animal->id) == FALSE) {
        from_idx = mNpc_SearchAnimalPersonalID(&from_animal->id);
        to_idx = mNpc_SearchAnimalPersonalID(&to_animal->id);

        if (from_idx != -1 && to_idx != -1 && from_idx != to_idx) {
            mNpc_AddRelationPoint_common(from_animal, to_animal, from_idx, to_idx, amount);
            ret = TRUE;
        }
    }

    return ret;
}

extern int mNpc_GetRelation(AnmPersonalID_c* from_id, AnmPersonalID_c* to_id) {
    int from_idx;
    int to_idx;
    int matching_point;
    int relation_point;
    int points;
    int ret = mNpc_RELATION_NORMAL;
    int i;

    if (from_id != NULL && to_id != NULL && mNpc_CheckFreeAnimalPersonalID(from_id) == FALSE &&
        mNpc_CheckFreeAnimalPersonalID(to_id) == FALSE) {
        from_idx = mNpc_SearchAnimalPersonalID(from_id);
        to_idx = mNpc_SearchAnimalPersonalID(to_id);

        if (from_idx != -1 && to_idx != -1) {
            static int point_table[mNpc_RELATION_NUM - 1] = { 400, 270, 50, -60 };

            matching_point = mNpc_GetMatchingPoint(from_id, to_id);
            relation_point = Save_Get(animals[from_idx]).animal_relations[to_idx] * 2.5f;
            points = matching_point + relation_point;
            ret = mNpc_RELATION_HATE; // default since if we transit the entire points table, it will be
                                      // mNpc_RELATION_HATE
            for (i = 0; i < ARRAY_COUNT(point_table); i++) {
                if (points >= point_table[i]) {
                    ret = i;
                    break;
                }
            }
        }
    }

    return ret;
}

extern int mNpc_GetRelationAnimal(Animal_c* from_animal, Animal_c* to_animal) {
    int ret = mNpc_RELATION_NORMAL;

    if (from_animal != NULL && to_animal != NULL) {
        ret = mNpc_GetRelation(&from_animal->id, &to_animal->id);
    }

    return ret;
}

extern int mNpc_GetNextRelationPoint(AnmPersonalID_c* from_id, AnmPersonalID_c* to_id) {
    int cur_relation;
    int from_idx;
    int to_idx;
    int matching_point;
    int relation_point;
    int cur_points;
    int points;
    int ret = 0;
    int i;

    if (from_id != NULL && to_id != NULL && mNpc_CheckFreeAnimalPersonalID(from_id) == FALSE &&
        mNpc_CheckFreeAnimalPersonalID(to_id) == FALSE &&
        mNpc_CheckCmpAnimalPersonalID(from_id, to_id) == FALSE) {
        cur_relation = mNpc_GetRelation(from_id, to_id);

        if (cur_relation > mNpc_RELATION_LOVE && cur_relation < mNpc_RELATION_NUM) {
            from_idx = mNpc_SearchAnimalPersonalID(from_id);
            to_idx = mNpc_SearchAnimalPersonalID(to_id);

            if (from_idx != -1 && to_idx != -1) {
                static int point_table[mNpc_RELATION_NUM - 1] = { 400, 270, 50, -60 };
                Animal_c* animal;

                animal = Save_Get(animals) + from_idx;
                relation_point = animal->animal_relations[to_idx];
                matching_point = mNpc_GetMatchingPoint(from_id, to_id);
                cur_points = point_table[cur_relation - 1];
                points = matching_point + (int)(relation_point * 2.5f);
                ret = ((cur_points - points) * 2 + 4) / 5;
            }
        }
    }

    return ret;
}

// @fabricated -- this table is left in but I don't know where else it would go
static int mNpc_GetPrevRelationPoint(Animal_c* from_animal, Animal_c* to_animal) {
    static int point_table[mNpc_RELATION_NUM - 1] = { 240, 170, 120, 70 };
}

extern int mNpc_GetMatchingPoint(AnmPersonalID_c* id0, AnmPersonalID_c* id1) {
    int ret = 0;

    if (id0 != NULL && id1 != NULL && mNpc_CheckFreeAnimalPersonalID(id0) == FALSE &&
        mNpc_CheckFreeAnimalPersonalID(id1) == FALSE) {
        u8 parmas0[12];
        u8 parmas1[12];

        if (mNpc_get_npc_param(parmas0, id0->npc_id) == TRUE &&
            mNpc_get_npc_param(parmas1, id1->npc_id) == TRUE) {
            ret = mMG_paramC_matching_point(parmas0, parmas1);
        }
    }

    return ret;
}

extern int mNpc_GetAnimal_relation(Animal_c* src_animal, int desired_relation) {
    Animal_c* animal = Save_Get(animals);
    int count = 0;
    int mask = 0;
    int src_idx;
    int random_idx;
    int ret = -1;
    int i;

    if (src_animal != NULL) {
        src_idx = mNpc_SearchAnimalPersonalID(&src_animal->id);

        if (src_idx != -1) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (i != src_idx && mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
                    mNpc_GetRelation(&animal->id, &src_animal->id) == desired_relation) {
                    count++;
                    mask |= 1 << i;
                }

                animal++;
            }

            if (count > 0) {
                random_idx = mQst_GetRandom(count);

                for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                    if (((mask >> i) & 1) == 1) {
                        if (random_idx == 0) {
                            ret = i;
                            break;
                        }

                        random_idx--;
                    }
                }
            }
        }
    }

    return ret;
}

extern int mNpc_GetAnimal_relation_point(Animal_c* src_animal, int points) {
    Animal_c* animal = Save_Get(animals);
    int cur_points = 240;
    int src_idx;
    int relation;
    int diff;
    int ret = -1;
    int i;

    if (src_animal != NULL) {
        src_idx = mNpc_SearchAnimalPersonalID(&src_animal->id);

        if (src_idx != -1) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (i != src_idx && mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                    relation = src_animal->animal_relations[i];

                    if (relation <= points) {
                        diff = points - relation;
                    } else {
                        diff = relation - points;
                    }

                    if (diff <= cur_points) {
                        ret = i;
                        cur_points = diff;
                    }
                }

                animal++;
            }
        }
    }

    return ret;
}

static void mNpc_SetAnimalMemory_NotSetDay(PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmmem_c* memory) {
    if (memory != NULL) {
        if (mNpc_CheckIslandAnimalID(anm_id) == FALSE) {
            mNpc_ClearAnimalMemory(memory, 1);
        } else {
            mNpc_ClearIslandAnimalMemory(memory, 1);
        }

        mPr_CopyPersonalID(&memory->memory_player_id, pid);
        memory->friendship = 1;
    }
}

extern void mNpc_SetAnimalMemory(PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmmem_c* memory) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    if (memory != NULL) {
        mNpc_SetAnimalMemory_NotSetDay(pid, anm_id, memory);
        lbRTC_TimeCopy(&memory->last_speak_time, rtc_time);
    }
}

extern int mNpc_GetAnimalMemoryIdx(PersonalID_c* pid, Anmmem_c* memory, int num) {
    int res = -1;
    int i;

    if (pid != NULL && memory != NULL) {
        for (i = 0; i < num; i++) {
            if (mPr_CheckCmpPersonalID(&memory->memory_player_id, pid) == TRUE) {
                res = i;
                break;
            }

            memory++;
        }
    }

    return res;
}

extern void mNpc_SetAnimalLastTalk(Animal_c* animal) {
    Private_c* priv = Now_Private;
    Anmmem_c* memory = NULL;

    if (priv != NULL && animal != NULL) {
        int memory_idx = mNpc_GetAnimalMemoryIdx(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

        if (memory_idx != -1) {
            memory = animal->memories + memory_idx;
        } else {
            memory_idx = mNpc_ForceGetFreeAnimalMemoryIdx(animal, animal->memories, ANIMAL_MEMORY_NUM);

            if (memory_idx != -1) {
                memory = animal->memories + memory_idx;
                mNpc_SetAnimalMemory(&priv->player_ID, &animal->id, memory);
            }
        }

        if (memory != NULL) {
            lbRTC_TimeCopy(&memory->last_speak_time, Common_GetPointer(time.rtc_time));

            if (mNpc_CheckIslandAnimalID(&animal->id) == FALSE) {
                mLd_CopyLandName(memory->memuni.land.name, Save_Get(land_info).name);
                memory->memuni.land.id = Save_Get(land_info).id;
            }

            memory->saved_town_tune = Save_Get(melody);
        }
    }
}

extern void mNpc_SetAnimalPersonalID2Memory(AnmPersonalID_c* anm_id) {
    Private_c* priv = Now_Private;

    if (priv != NULL) {
        int anm_idx = mNpc_SearchAnimalPersonalID(anm_id);

        if (anm_idx != -1) {
            Animal_c* animal = Save_Get(animals) + anm_idx;
            int mem_idx = mNpc_GetAnimalMemoryIdx(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

            if (mem_idx == -1) {
                int free_idx = mNpc_ForceGetFreeAnimalMemoryIdx(animal, animal->memories, ANIMAL_MEMORY_NUM);

                if (free_idx != -1) {
                    mNpc_SetAnimalMemory_NotSetDay(&priv->player_ID, &animal->id, animal->memories + free_idx);
                }
            }
        }
    }
}

extern int mNpc_GetHighestFriendshipIdx(Anmmem_c* memory, int num) {
    s8 max = 0;
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            if (max <= memory->friendship) {
                max = memory->friendship;
                res = i;
            }
        }

        memory++;
    }

    return res;
}

extern int mNpc_GetHighestFriendshipIdx_native(Anmmem_c* memory, int num) {
    s8 max = 0;
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE &&
            mLd_CheckThisLand(memory->memory_player_id.land_name, memory->memory_player_id.land_id) == TRUE) {
            if (max <= memory->friendship) {
                max = memory->friendship;
                res = i;
            }
        }

        memory++;
    }

    return res;
}

static int mNpc_SelectBestFriend(Anmmem_c** best_friend_mem, Anmmem_c* memory, s8* best_friend_friendship) {
    int res = FALSE;
    Anmmem_c* best_friend;

    if (memory->friendship > best_friend_friendship[0]) {
        best_friend_friendship[0] = memory->friendship;
        best_friend_mem[0] = memory;
        res = TRUE;
    } else if (memory->friendship == best_friend_friendship[0]) {
        best_friend = best_friend_mem[0];

        if (best_friend != NULL) {
            if (best_friend->letter_info.exists == memory->letter_info.exists) {
                if (lbRTC_IsOverTime(&best_friend->last_speak_time, &memory->last_speak_time) == lbRTC_LESS) {
                    best_friend_mem[0] = memory;
                    res = TRUE;
                }
            } else if (memory->letter_info.exists == TRUE) {
                best_friend_mem[0] = memory;
                res = TRUE;
            }
        } else {
            best_friend_mem[0] = memory;
            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_GetAnimalMemoryBestFriend(Anmmem_c* memory, int num) {
    Anmmem_c* memory_p = memory;
    Anmmem_c* best_friend = NULL;
    s8 best_friendship = 0;
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE &&
            mNpc_SelectBestFriend(&best_friend, memory, &best_friendship) == TRUE) {
            res = i;
        }

        memory++;
    }

    memory = memory_p;
    if (res != -1) {
        memory = &memory[res];

        if (memory->friendship < 80) {
            res = -1; // minimum best friend friendship value failed
        }
    }

    return res;
}

static int mNpc_GetAnimalMemoryFriend_Land_Sex(Anmmem_c* memory, int num, int sex) {
    Anmmem_c* best_friend = NULL;
    s8 best_friendship = 0;
    int priv_idx;
    int res = -1;
    int i;

    for (i = 0; i < num; i++) {
        if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
            priv_idx = mPr_GetPrivateIdx(&memory->memory_player_id);

            if (priv_idx != -1 && Save_Get(private_data[priv_idx]).gender == sex &&
                mNpc_SelectBestFriend(&best_friend, memory, &best_friendship) == TRUE) {
                res = i;
            }
        }

        memory++;
    }

    return res;
}

extern void mNpc_ClearAnimalInfo(Animal_c* animal) {
    bzero(animal, sizeof(Animal_c));
    mNpc_ClearAnimalPersonalID(&animal->id);
    mNpc_ClearAnimalMemory(animal->memories, ANIMAL_MEMORY_NUM);
    animal->cloth = EMPTY_NO;
    animal->home_info.type_unused = 0;
    animal->home_info.bx = 0xFF;
    animal->home_info.bz = 0xFF;
    animal->home_info.ux = 0xFF;
    animal->home_info.uz = 0xFF;
    mNpc_ClearBufSpace1(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    mQst_ClearContest(&animal->contest_quest);
    mLd_ClearLandName(animal->anmuni.previous_land_name);
    animal->anmuni.previous_land_id = 0;
    animal->remove_info = 0;
    animal->is_home = TRUE;
    mPr_ClearPersonalID(&animal->parent_id);
}

extern void mNpc_ClearIslandAnimalInfo(Animal_c* animal) {
    bzero(animal, sizeof(Animal_c));
    mNpc_ClearAnimalPersonalID(&animal->id);
    mNpc_ClearIslandAnimalMemory(animal->memories, ANIMAL_MEMORY_NUM);
    animal->cloth = EMPTY_NO;
    animal->home_info.type_unused = 0;
    animal->home_info.bx = 0xFF;
    animal->home_info.bz = 0xFF;
    animal->home_info.ux = 0xFF;
    animal->home_info.uz = 0xFF;
    mNpc_ClearBufSpace1(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    mQst_ClearContest(&animal->contest_quest);
    animal->remove_info = 0;
    animal->is_home = TRUE;
    mPr_ClearPersonalID(&animal->parent_id);
}

extern void mNpc_ClearAnyAnimalInfo(Animal_c* animal, int count) {
    int i;

    for (i = 0; i < count; i++) {
        mNpc_ClearAnimalInfo(animal);
        animal++;
    }
}

extern int mNpc_CheckFreeAnimalInfo(Animal_c* animal) {
    int res = FALSE;

    if ((animal->home_info.bx == 0xFF && animal->home_info.bz == 0xFF) &&
        ITEM_NAME_GET_TYPE(animal->id.npc_id) != NAME_TYPE_NPC) {
        res = TRUE;
    }

    return res;
}

extern int mNpc_GetFreeAnimalInfo(Animal_c* animal, int count) {
    int res = -1;
    int i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == TRUE) {
            res = i;
            break;
        }

        animal++;
    }

    return res;
}

extern int mNpc_UseFreeAnimalInfo(Animal_c* animal, int count) {
    int free_idx = mNpc_GetFreeAnimalInfo(animal, count);

    if (free_idx != -1) {
        mNpc_ClearAnimalInfo(animal + free_idx);
        // mNpc_ResetAnimalRelation(free_idx);
    }

    return free_idx;
}

extern void mNpc_CopyAnimalInfo(Animal_c* dst, Animal_c* src) {
    if (dst != NULL && src != NULL) {
        mem_copy((u8*)dst, (u8*)src, sizeof(Animal_c));
    }
}

extern int mNpc_SearchAnimalinfo(Animal_c* animal, mActor_name_t npc_id, int count) {
    int i;

    animal = animal + (count - 1);
    for (i = count - 1; i >= 0; i--) {
        if (animal->id.npc_id == npc_id) {
            return i;
        }

        animal--;
    }

    return -1;
}

extern int mNpc_SearchIslandAnimalinfo(mActor_name_t npc_id, u8 npc_add_id) {
    mHm_hs_c* home = Save_Get(homes);
    int ret = -1;
    int i;

    for (i = 0; i < mHS_HOUSE_NUM; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&home->island.animal.id) == FALSE) {
            if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
                if (home->island.animal.id.npc_id == npc_id) {
                    ret = i;
                    break;
                }
            } else {
                if (npc_id == EMPTY_NO && home->island.animal.id.add_npc_id == npc_add_id) {
                    ret = i;
                    break;
                }
            }
        }

        home++;
    }

    return ret;
}

extern Animal_c* mNpc_GetAnimalInfoP(mActor_name_t npc_id) {
    Animal_c* animal = NULL;
    int idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_id, ANIMAL_NUM_MAX);

    if (idx != -1) {
        animal = Save_Get(animals) + idx;
    }

    return animal;
}

extern int mNpc_SearchAnimalPersonalID_com(AnmPersonalID_c* anm_pid, Animal_c* animal, int count) {
    int res = -1;
    int i;

    if (anm_pid != NULL && animal != NULL && !mNpc_CheckFreeAnimalPersonalID(anm_pid)) {
        for (i = 0; i < count; i++) {
            if (mNpc_CheckCmpAnimalPersonalID(anm_pid, &animal->id) == TRUE) {
                res = i;
                break;
            }

            animal++;
        }
    }

    return res;
}

extern int mNpc_SearchAnimalPersonalID(AnmPersonalID_c* anm_pid) {
    return mNpc_SearchAnimalPersonalID_com(anm_pid, Save_Get(animals), ANIMAL_NUM_MAX);
}

extern AnmPersonalID_c* mNpc_GetOtherAnimalPersonalIDOtherBlock(AnmPersonalID_c* pids, int count, int bx, int bz,
                                                                int check_flag) {
    Animal_c* animal;
    AnmPersonalID_c* other_id;
    int npc_max;
    int homes_in_block;
    int ids = count;
    u16 bitfield;
    int j;
    int i;

    other_id = NULL;
    animal = Save_Get(animals);
    npc_max = mNpc_GetAnimalNum();
    homes_in_block = 0;
    ids = count;
    bitfield = 0xFFFF;

    if (bx == 0xFF || bz == 0xFF) {
        check_flag = FALSE;
    }

    if (pids == NULL && count != 0) {
        count = 0;
    }

    /* clear any uninitialized personal ids */
    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(pids + i) == TRUE) {
            ids--;
            bitfield &= ~(1 << i);
        }
    }

    /* clear any npcs who are in the list and live in the acre */
    if (check_flag == TRUE) {
        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if (animal->home_info.bx == bx && animal->home_info.bz == bz) {
                homes_in_block++;

                for (i = 0; i < count; i++) {
                    if (((bitfield >> i) & 1) == 1 && mNpc_CheckCmpAnimalPersonalID(&animal->id, &pids[i]) == TRUE) {
                        ids--;
                        bitfield &= ~(1 << i);
                        break;
                    }
                }
            }

            animal++;
        }
    }

    if (npc_max > (ids + homes_in_block) && count < ANIMAL_NUM_MAX) {
        int valid;
        int t;

        animal = Save_Get(animals);
        homes_in_block = RANDOM((npc_max - ids) - homes_in_block);

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            i = 0;
            valid = TRUE;

            if (!mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
                for (npc_max = 0; npc_max < count; npc_max++) {
                    if (((bitfield >> npc_max) & 1) == 1 &&
                        !mNpc_CheckCmpAnimalPersonalID(&animal->id, &pids[npc_max])) {
                        i++;
                    }
                }

                if (i != ids) {
                    valid = FALSE;
                } else if (check_flag == TRUE && animal->home_info.bx == bx && animal->home_info.bz == bz) {
                    if (homes_in_block > 0) {
                        homes_in_block--;
                    }

                    valid = FALSE;
                }

                if (valid == TRUE) {
                    if (homes_in_block == 0) {
                        other_id = &animal->id;
                        break;
                    } else {
                        homes_in_block--;
                    }
                }
            }

            animal++;
        }
    }

    return other_id;
}

extern AnmPersonalID_c* mNpc_GetOtherAnimalPersonalID(AnmPersonalID_c* pids, int count) {
    return mNpc_GetOtherAnimalPersonalIDOtherBlock(pids, count, 0, 0, FALSE);
}

extern void mNpc_SetAnimalThisLand(Animal_c* animal, int count) {
    mLd_land_info_c* land_info = Save_GetPointer(land_info);

    for (; count != 0; count--) {
        if (!mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
            animal->id.land_id = land_info->id;
            mLd_CopyLandName(animal->id.land_name, land_info->name);
        }

        animal++;
    }
}

extern int mNpc_GetSameLooksNum(u8 looks) {
    Animal_c* animal = Save_Get(animals);
    int i;
    int num = 0;

    if (looks < mNpc_LOOKS_UNSET) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (looks == animal->id.looks) {
                num++;
            }

            animal++;
        }
    }

    return num;
}

extern int mNpc_GetSameRaceNum(u8 race) {
    Animal_c* animal = Save_Get(animals);
    int i;
    int num = 0;

    if (race < mNpc_SPECIES_NUM) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (race == animal->race) {
                num++;
            }

            animal++;
        }
    }

    return num;
}

extern int mNpc_CheckNpcExistBlock(int idx, int check_bx, int check_bz) {
    int bx;
    int bz;
    int res = FALSE;

    if (idx >= 0 && idx < (ANIMAL_NUM_MAX + 1)) {
        mNpc_NpcList_c* list = Common_GetPointer(npclist[idx]);

        if (mFI_Wpos2BlockNum(&bx, &bz, list->position) == TRUE && bx == check_bx && bz == check_bz) {
            res = TRUE;
        }
    }

    return res;
}

extern void mNpc_Mail2AnimalMail(Anmplmail_c* animal_mail, Mail_c* mail) {
    mem_copy(animal_mail->body, mail->content.text.split.body, MAIL_BODY_FULL_LEN);
    mem_copy(animal_mail->header, mail->content.text.split.header, MAIL_HEADER_FULL_LEN);
    mem_copy(animal_mail->footer, mail->content.text.split.footer, MAIL_FOOTER_FULL_LEN);

    animal_mail->header_back_start = mail->content.header_back_start;
    animal_mail->font = mail->content.font;
    animal_mail->present = mail->present;
    animal_mail->paper_type = mail->content.paper_type;
}

extern void mNpc_AnimalMail2Mail(Mail_c* mail, Anmplmail_c* animal_mail, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    mem_copy(mail->content.text.split.body, animal_mail->body, MAIL_BODY_FULL_LEN);
    mem_copy(mail->content.text.split.header, animal_mail->header, MAIL_HEADER_FULL_LEN);
    mem_copy(mail->content.text.split.footer, animal_mail->footer, MAIL_FOOTER_FULL_LEN);

    mail->content.header_back_start = animal_mail->header_back_start;
    mail->content.font = animal_mail->font;
    mail->present = animal_mail->present;
    mail->content.paper_type = animal_mail->paper_type;

    if (pid != NULL) {
        mPr_CopyPersonalID(&mail->header.sender.personalID, pid);
        mail->header.sender.type = mMl_NAME_TYPE_PLAYER;
    }

    if (anm_id != NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.recipient, anm_id);
    }
}

static u16 l_mnpc_body[MAIL_BODY_LEN];

static int mNpc_CheckMailChar(u16 c) {
    if ((c == CHAR_EXCLAMATION) || (c == CHAR_QUOTATION) || (c == CHAR_UNDERSCORE) || (c == CHAR_HYPHEN) ||
        (c == CHAR_SYMBOL_ANNOYED) || ((c >= CHAR_PERCENT) && (c <= CHAR_AT_SIGN)) ||
        ((c >= CHAR_CONTROL_CODE) && (c <= CHAR_INTERPUNCT))) {
        return TRUE;
    }

    return FALSE;
}

extern int mNpc_CheckNormalMail_sub(int* char_num, u16* body) {
    u16 last_char = CHAR_SPACE;
    int run_len = 1;
    int consecutive_chars = FALSE;
    int t = 0;
    int i;

    char_num[0] = 0;

    for (i = 0; i < MAIL_BODY_LEN; i++) {
        if (body[0] != CHAR_SPACE) {

            if (last_char == body[0]) {
                run_len++;

                if (run_len >= 3) {
                    if (mNpc_CheckMailChar(body[0]) == TRUE) {
                        if (run_len >= 8) {
                            consecutive_chars = TRUE;
                            break;
                        }
                    } else {
                        consecutive_chars = TRUE;
                        break;
                    }
                }
            } else {
                run_len = 0;
                last_char = body[0];
            }

            char_num[0]++;
        }

        body++;
        t++;
    }

    for (i = t; i < MAIL_BODY_LEN; i++) {
        if (body[0] != CHAR_SPACE) {
            char_num[0]++;
        }

        body++;
    }

    return consecutive_chars;
}

extern u8 mNpc_CheckNormalMail_length(int* len, u8* body) {
    int hit_chars;
    u8 rank = mNpc_LETTER_RANK_NUM;
    int hit_rate;
    int run_on;

    mMlW_clear_buf(l_mnpc_body, MAIL_BODY_LEN, CHAR_SPACE);
    mTxt_conv_16bit(body, l_mnpc_body, MAIL_BODY_LEN);
    hit_rate = mMC_get_mail_hit_rate(&hit_chars, l_mnpc_body, NULL);
    run_on = mNpc_CheckNormalMail_sub(len, l_mnpc_body);

    if (hit_chars < 3) {
        if (len[0] < 5) {
            rank = mNpc_LETTER_RANK_BAD;
        } else if (run_on == TRUE) {
            rank = mNpc_LETTER_RANK_BAD;
        }
    } else if (hit_rate >= 30) {
        rank = mNpc_LETTER_RANK_OK;
    } else if (run_on == TRUE) {
        rank = mNpc_LETTER_RANK_BAD;
    }

    return rank;
}

static u8 mNpc_CheckNormalMail(u8* body) {
    int len = 0;

    return mNpc_CheckNormalMail_length(&len, body);
}

static int mNpc_SetMailCondThisLand(Anmmem_c* memory, u8* body) {
    u8 letter_rank;

    memory->letter.date.year = Common_Get(time.rtc_time).year;
    memory->letter.date.month = Common_Get(time.rtc_time).month;
    memory->letter.date.day = Common_Get(time.rtc_time).day;

    letter_rank = mNpc_CheckNormalMail(body);

    if (letter_rank < mNpc_LETTER_RANK_NUM) {
        memory->letter_info.cond = letter_rank;
        memory->letter_info.send_reply = TRUE;
    }

    return letter_rank;
}

static int mNpc_SetMailCondOtherLand(Animal_c* animal, u8* body) {
    u8 letter_rank = mNpc_CheckNormalMail(body);

    if (letter_rank < mNpc_LETTER_RANK_NUM) {
        Private_c* priv = Now_Private;
        Anmremail_c* remail = &priv->remail;

        remail->date.year = Common_Get(time.rtc_time).year;
        remail->date.month = Common_Get(time.rtc_time).month;
        remail->date.day = Common_Get(time.rtc_time).day;
        remail->flags.cond = letter_rank;
        remail->flags.looks = animal->id.looks;

        mNpc_GetNpcWorldNameAnm(remail->name, &animal->id);
        mLd_CopyLandName(remail->land_name, mLd_GetLandName());
    }

    return letter_rank;
}

static int mNpc_SetRemailCond(Animal_c* animal, Anmmem_c* memory, u8* body) {
    if (mLd_PlayerManKindCheck() == FALSE) {
        return mNpc_SetMailCondThisLand(memory, body);
    } else {
        return mNpc_SetMailCondOtherLand(animal, body);
    }
}

static int mNpc_SetPresentCloth(Animal_c* animal, PersonalID_c* player_id, mActor_name_t cloth) {
    Anmmem_c* mem;
    int res = FALSE;

    if (animal != NULL && player_id != NULL && ITEM_NAME_GET_TYPE(cloth) == NAME_TYPE_ITEM1 &&
        ITEM_NAME_GET_CAT(cloth) == ITEM1_CAT_CLOTH && !mNpc_CheckFreeAnimalPersonalID(&animal->id) &&
        !mPr_NullCheckPersonalID(player_id)) {
        int memory_idx = mNpc_GetAnimalMemoryIdx(player_id, animal->memories, ANIMAL_MEMORY_NUM);

        if (memory_idx != -1) {
            Anmmem_c* m = &animal->memories[memory_idx];

            if (m->friendship > 30) {
                Anmmem_c* memory = animal->memories;
                int i;

                for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
                    if (i == memory_idx) {
                        memory->letter_info.has_present_cloth = TRUE;
                    } else {
                        memory->letter_info.has_present_cloth = FALSE;
                    }

                    memory->letter_info.wearing_present_cloth = FALSE;
                    memory++;
                }

                animal->present_cloth = cloth;
                res = TRUE;
            }
        }
    }

    return res;
}

extern int mNpc_SendMailtoNpc(Mail_c* mail) {
    int res = FALSE;
    Anmmem_c* memory;
    int anm_idx;
    Animal_c* anm;
    Animal_c* animal;
    int letter_rank;
    int memory_idx;
    Anmplmail_c* plmail;
    AnmPersonalID_c anm_id;

    if (mMl_get_npcinfo_from_mail_name(&anm_id, &mail->header.recipient) == TRUE) {
        anm = Save_Get(animals);
        anm_idx = mNpc_SearchAnimalPersonalID(&anm_id);

        if (anm_idx != -1) {
            animal = anm + anm_idx;
            memory = NULL;
            memory_idx = mNpc_GetAnimalMemoryIdx(&mail->header.sender.personalID, animal->memories, ANIMAL_MEMORY_NUM);

            if (memory_idx == -1) {
                memory_idx = mNpc_ForceGetFreeAnimalMemoryIdx(anm, animal->memories, ANIMAL_MEMORY_NUM);

                if (memory_idx >= 0) {
                    memory = animal->memories + memory_idx;
                    mPr_CopyPersonalID(&memory->memory_player_id, &mail->header.sender.personalID);
                }
            } else {
                mNpc_SetPresentCloth(animal, &mail->header.sender.personalID, mail->present);
            }

            if (memory_idx >= 0 && memory_idx < ANIMAL_MEMORY_NUM) {
                memory = animal->memories + memory_idx;
                plmail = &memory->letter;
                memory->letter_info.exists = TRUE;
                mNpc_ClearAnimalMail(plmail);
                mNpc_Mail2AnimalMail(plmail, mail);
                letter_rank = mNpc_SetRemailCond(animal, memory, mail->content.text.split.body);
            }

            if (mEv_CheckFirstJob() == TRUE) {
                mQst_errand_c* first_job = mQst_GetFirstJobData();

                if (first_job != NULL &&
                    (first_job->base.quest_kind == mQst_ERRAND_FIRSTJOB_SEND_LETTER ||
                     first_job->base.quest_kind == mQst_ERRAND_FIRSTJOB_SEND_LETTER2) &&
                    first_job->base.progress != 0 && mNpc_CheckFreeAnimalPersonalID(&first_job->recipient) == FALSE) {
                    first_job->base.progress = 3;

                    if (memory != NULL) {
                        memory->letter_info.send_reply = FALSE;
                    }
                }
            } else {
                int friendship = 0;

                if (mLd_PlayerManKindCheck() == FALSE) {
                    int occur_idx = mQst_GetOccuredContestIdx(mQst_CONTEST_KIND_LETTER);
                    if (occur_idx == anm_idx) {
                        mQst_SetReceiveLetter(&animal->contest_quest, &mail->header.sender.personalID,
                                              mail->content.text.split.body, mail->present);

                        if (memory != NULL) {
                            memory->letter_info.send_reply = FALSE;
                        }
                    }
                }

                friendship += 3;

                if (letter_rank == mNpc_LETTER_RANK_BAD) {
                    friendship += -5;
                }

                if (mail->present != EMPTY_NO) {
                    friendship += 3;
                }

                if (memory != NULL) {
                    mNpc_AddFriendship(memory, friendship);
                }
            }

            res = TRUE;
        }
    }

    return res;
}

extern void mNpc_ClearRemail(Anmremail_c* remail) {
    remail->date = mTM_rtcTime_ymd_clear_code;
    mPr_ClearPlayerName(remail->name);
    mLd_ClearLandName(remail->land_name);
    remail->flags.cond = mNpc_LETTER_RANK_BAD;
    remail->flags.looks = 0x7F;
}

static void mNpc_GetRemailPresent(mActor_name_t* present) {
    static int category_table[2] = { mSP_KIND_FURNITURE, mSP_KIND_CLOTH };

    mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, category_table[RANDOM(4) & 1], mSP_LISTTYPE_ABC, FALSE);
}

static int mNpc_GetHandbillz(Mail_c* mail, int super_num, int mail_a_num, int mail_b_num, int mail_c_num, int ps_num) {
    static u8 tmp_super[MAIL_HEADER2_LEN];
    static u8 tmp_ps[MAIL_FOOTER2_LEN];

    mHandbillz_Info_c handbill_info;
    int res;

    handbill_info.super_buf_p = tmp_super;
    handbill_info.super_buf_size = MAIL_HEADER2_LEN;
    handbill_info.mail_buf_p = mail->content.text.split.body;
    handbill_info.mail_buf_size = MAIL_BODY_LEN;
    handbill_info.ps_buf_p = tmp_ps;
    handbill_info.ps_buf_size = MAIL_FOOTER2_LEN;
    handbill_info.super_no = super_num;
    handbill_info.maila_no = mail_a_num;
    handbill_info.mailb_no = mail_b_num;
    handbill_info.mailc_no = mail_c_num;
    handbill_info.ps_no = ps_num;

    res = mHandbillz_load(&handbill_info);
    if (res == TRUE) {
        mail->content.header_back_start = handbill_info.header_back_start;
        mem_copy(mail->content.text.split.header, tmp_super, MAIL_HEADER_LEN);
        mem_copy(mail->content.text.split.footer, tmp_ps, MAIL_FOOTER_LEN);
    }

    return res;
}

static void mNpc_SetRemailFreeString(PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail) {
    static int base_str_no[11] = {
        0x314, // food
        0x334, // sports
        0x2F4, // hobby games
        0x6A1, // fish
        0x679, // insects
        0x354, // food tastes (sweet, spicy, ...)
        0x374, // feelings
        0x394, // music genres
        0x3D4, // food satisfaction feelings (delicious, stuffed, satisfying, ...)
        0x3F4, // "good" descriptors (brilliant, splendid, ...)
        0x3B4  // "bad" descriptors (unimpressive, awful, ...)
    };

    /* number of string entries per type */
    static f32 rand_max_table[11] = { 32.0f, 32.0f, 32.0f, 40.0f, 40.0f, 32.0f, 32.0f, 32.0f, 32.0f, 32.0f, 32.0f };

    u8 free_str[mMsg_FREE_STRING_LEN];
    AnmPersonalID_c* other_id;
    int i;

    mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);

    if (remail == NULL) {
        mNpc_GetNpcWorldNameAnm(free_str, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR1, free_str, ANIMAL_NAME_LEN);
        other_id = mNpc_GetOtherAnimalPersonalID(anm_id, 1);

        if (other_id != NULL) {
            mNpc_GetNpcWorldNameAnm(free_str, other_id);
            mHandbill_Set_free_str(mHandbill_FREE_STR2, free_str, ANIMAL_NAME_LEN);
        }
    } else {
        mHandbill_Set_free_str(mHandbill_FREE_STR1, remail->name, ANIMAL_NAME_LEN); // foreign npc name
        other_id = mNpc_GetOtherAnimalPersonalID(NULL, 0);
        mNpc_GetNpcWorldNameAnm(free_str, other_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR2, free_str, ANIMAL_NAME_LEN);          // random player town npc name
        mHandbill_Set_free_str(mHandbill_FREE_STR14, remail->land_name, LAND_NAME_SIZE); // foreign town name
        mHandbill_Set_free_str(mHandbill_FREE_STR15, mLd_GetLandName(), LAND_NAME_SIZE); // player town name
    }

    for (i = 0; i < ARRAY_COUNT(base_str_no); i++) {
        int rand = RANDOM_F(rand_max_table[i]);

        mString_Load_StringFromRom(free_str, ARRAY_COUNT(free_str), base_str_no[i] + rand);
        mHandbill_Set_free_str(mHandbill_FREE_STR3 + i, free_str, ARRAY_COUNT(free_str));
    }
}

static void mNpc_GetRemailGoodData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail,
                                   u8 foreign) {
    static int this_start_no[mNpc_LOOKS_NUM] = { 0x020, 0x040, 0x000, 0x060, 0x080, 0x0A0 };

    static int ohter_start_no[mNpc_LOOKS_NUM] = { 0x0E0, 0x100, 0x0C0, 0x120, 0x140, 0x160 };

    static int* start_no_table[2] = { this_start_no, ohter_start_no };

    mActor_name_t present = EMPTY_NO;
    int msg_no;
    int* msg_tbl;
    int looks;
    int give_present;

    if (remail == NULL) {
        looks = anm_id->looks;
    } else {
        looks = remail->flags.looks;
    }

    msg_tbl = start_no_table[foreign];

    give_present = RANDOM(4) & 1;
    if (give_present == 0) {
        mNpc_GetRemailPresent(&present);
    }

    mNpc_SetRemailFreeString(pid, anm_id, remail);
    msg_no = msg_tbl[looks];
    mNpc_GetHandbillz(mail, msg_no + RANDOM(32), msg_no + RANDOM(32), msg_no + RANDOM(16) + give_present * 16,
                      msg_no + RANDOM(32), msg_no + RANDOM(32));
    mail->present = present;
}

static void mNpc_GetRemailWrongData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail,
                                    u8 foreign) {
    static int mail_no[2] = { 0xC5, 0xD8 };
    static u8 tmp_super[MAIL_HEADER2_LEN];
    static u8 tmp_ps[MAIL_FOOTER2_LEN];

    int looks;
    int header_back_start;
    int msg_no;

    if (remail == NULL) {
        looks = anm_id->looks;
    } else {
        looks = remail->flags.looks;
    }

    mNpc_SetRemailFreeString(pid, anm_id, remail);
    msg_no = mail_no[foreign] + looks * 3;
    msg_no += RANDOM(3);
    mHandbill_Load_HandbillFromRom(tmp_super, &header_back_start, tmp_ps, mail->content.text.split.body, msg_no);
    mail->content.header_back_start = header_back_start;
    mem_copy(mail->content.text.split.header, tmp_super, MAIL_HEADER_LEN);
    mem_copy(mail->content.text.split.footer, tmp_ps, MAIL_FOOTER_LEN);
    mail->present = EMPTY_NO;
}

typedef void (*mNPC_GET_REMAIL_PROC)(Mail_c*, PersonalID_c*, AnmPersonalID_c*, Anmremail_c*, u8);

static void mNpc_GetRemailData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail, int cond,
                               u8 foreign) {
    static mNPC_GET_REMAIL_PROC get_remail[mNpc_LETTER_RANK_NUM] = { &mNpc_GetRemailWrongData,
                                                                     &mNpc_GetRemailGoodData };

    mActor_name_t paper;
    int paper_no;

    (*get_remail[cond])(mail, pid, anm_id, remail, foreign);
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_MAIL;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;

    if (remail == NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.sender, anm_id);
    } else {
        mPr_CopyPlayerName(mail->header.sender.personalID.player_name, remail->name);
        mLd_CopyLandName(mail->header.sender.personalID.land_name, remail->land_name);
        mail->header.sender.type = mMl_NAME_TYPE_NPC;
    }

    mSP_SelectRandomItem_New(NULL, &paper, 1, NULL, 0, mSP_KIND_PAPER, mSP_LISTTYPE_ABC, FALSE);
    mail->content.paper_type = (paper - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
}

static Mail_c l_npc_mail;

static int mNpc_SendRemailPostOffice(PersonalID_c* pid, AnmPersonalID_c* anm_id, Anmremail_c* remail, int cond,
                                     u8 foreign) {
    Mail_c* mail = &l_npc_mail;
    int res = FALSE;

    if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
        mMl_clear_mail(mail);
        mNpc_GetRemailData(mail, pid, anm_id, remail, cond, foreign);
        res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
    }

    return res;
}

static int mNpc_CheckLetterTime(lbRTC_ymd_c* letter_date, lbRTC_time_c* rtc_time) {
    int res = FALSE;

    if (letter_date->day != 0xFF && (letter_date->year != rtc_time->year || letter_date->month != rtc_time->month ||
                                     letter_date->day != rtc_time->day)) {
        res = TRUE;
    }

    return res;
}

extern void mNpc_Remail() {
    Animal_c* animal;
    Anmmem_c* memory;
    Anmremail_c* remail;
    Private_c* priv;
    lbRTC_time_c* rtc_time;
    mNpc_SickInfo_c* sick_info;
    int sick_idx;

    animal = Save_Get(animals);
    priv = Now_Private;
    rtc_time = Common_GetPointer(time.rtc_time);
    sick_info = Save_GetPointer(sick_info);

    if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE && mLd_PlayerManKindCheck() == FALSE) {
        int i;

        sick_idx = mNpc_GetSickAnimalIdx_com(sick_info);

        /* process replies from town villagers first */
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (i != sick_idx && mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                int mem_idx = mNpc_GetAnimalMemoryIdx(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

                if (mem_idx != -1) {
                    memory = animal->memories + mem_idx;

                    if (memory->letter_info.send_reply &&
                        mNpc_CheckLetterTime(&memory->letter.date, rtc_time) == TRUE) {
                        if (mNpc_SendRemailPostOffice(&priv->player_ID, &animal->id, NULL, memory->letter_info.cond,
                                                      FALSE) != TRUE) {
                            break;
                        }

                        memory->letter_info.send_reply = FALSE;
                    }
                }
            }

            animal++;
        }

        /* process info from the last foreign villager (if any) */
        remail = &priv->remail;
        if (remail->flags.looks != 0x7F &&
            mNpc_SendRemailPostOffice(&priv->player_ID, &animal->id, remail, remail->flags.cond, TRUE) == TRUE) {
            mNpc_ClearRemail(remail);
        }
    }
}

extern u8 mNpc_GetPaperType() {
    mActor_name_t paper;

    mSP_SelectRandomItem_New(NULL, &paper, 1, NULL, 0, mSP_KIND_PAPER, mSP_LISTTYPE_ABC, FALSE);
    return (paper - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
}

extern void mNpc_LoadMailDataCommon2(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, mActor_name_t present,
                                     u8 paper_type, int mail_no) {
    u8 super[MAIL_HEADER2_LEN];
    u8 ps[MAIL_FOOTER2_LEN];
    int header_back_start;

    mMl_clear_mail(mail);
    mHandbill_Load_HandbillFromRom2(super, MAIL_HEADER2_LEN, &header_back_start, ps, MAIL_FOOTER2_LEN,
                                    mail->content.text.split.body, mail_no);
    mem_copy(mail->content.text.split.header, super, MAIL_HEADER_LEN);
    mem_copy(mail->content.text.split.footer, ps, MAIL_FOOTER_LEN);
    mail->content.header_back_start = header_back_start;
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_MAIL;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
    mMl_set_mail_name_npcinfo(&mail->header.sender, anm_id);
    mail->present = present;
    mail->content.paper_type = paper_type;
}

static void mNpc_GetEventPresent(mActor_name_t* present, int type) {
    static int priority_table[mNpc_EVENT_MAIL_FRIEND_NUM] = { mSP_LISTTYPE_RARE, mSP_LISTTYPE_UNCOMMON,
                                                              mSP_LISTTYPE_COMMON };

    static int category_table[mNpc_EVENT_MAIL_FRIEND_NUM] = { mSP_KIND_FURNITURE, mSP_KIND_FURNITURE, mSP_KIND_CLOTH };

    mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, category_table[type], priority_table[type], FALSE);
}

static void mNpc_GetEventMail(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, int type, int looks) {
    static u8 animal_name[ANIMAL_NAME_LEN];

    mActor_name_t present;

    mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(animal_name, anm_id);
    mHandbill_Set_free_str(mHandbill_FREE_STR6, animal_name, ANIMAL_NAME_LEN);
    mNpc_GetEventPresent(&present, type);
    mNpc_LoadMailDataCommon2(mail, pid, anm_id, present, mNpc_GetPaperType(),
                             0x60 + looks * mNpc_EVENT_MAIL_FRIEND_NUM + type);
}

static int mNpc_SendEventPresentMail(PersonalID_c* pid, int player_no, AnmPersonalID_c* anm_id, int type) {
    Mail_c* mail = &l_npc_mail;
    mHm_hs_c* home;
    int looks = anm_id->looks;
    int res = FALSE;

    home = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

    if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
        int free_idx;

        mMl_clear_mail(mail);
        free_idx = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);

        if (free_idx != -1) {
            mNpc_GetEventMail(mail, pid, anm_id, type, looks);
            mMl_copy_mail(home->mailbox + free_idx, mail);
            res = TRUE;
        } else if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
            mNpc_GetEventMail(mail, pid, anm_id, type, looks);
            res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
        }
    }

    return res;
}

static void mNpc_SendEventPresentMailSex(int* selected, u8* type, Animal_c* animal, int animal_sex) {
    int best_friend_idx = mNpc_GetAnimalMemoryBestFriend(animal->memories, ANIMAL_MEMORY_NUM);
    int other_sex_best_friend_idx =
        mNpc_GetAnimalMemoryFriend_Land_Sex(animal->memories, ANIMAL_MEMORY_NUM, (~animal_sex) & 1);

    if (best_friend_idx != -1 && other_sex_best_friend_idx == best_friend_idx) {
        selected[0] = other_sex_best_friend_idx;
        type[0] = mNpc_EVENT_MAIL_BEST_FRIEND;
    } else if (other_sex_best_friend_idx != -1) {
        selected[0] = other_sex_best_friend_idx;

        if (animal->memories[other_sex_best_friend_idx].friendship >= 80) {
            type[0] = mNpc_EVENT_MAIL_OK_FRIEND;
        } else {
            type[0] = mNpc_EVENT_MAIL_NOT_FRIEND;
        }
    }
}

/* this used to be mNpc_SendEventPresentMail_common in DnM and DnM+ (handled both valentine's day & white day) */

extern int mNpc_SendVtdayMail() {
    u8 types[ANIMAL_NUM_MAX];
    int other_sex_best_friends[ANIMAL_NUM_MAX];
    Animal_c* animal_p;
    int sent;
    u8 player_bitfield;
    int mem_idx;
    PersonalID_c* pid;
    int player_no;
    int i;
    int j;

    animal_p = Save_Get(animals);
    sent = 0;
    player_bitfield = 0b1111;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        other_sex_best_friends[i] = -1;

        if (mNpc_CheckFreeAnimalPersonalID(&animal_p->id) == FALSE) {
            mNpc_SendEventPresentMailSex(&other_sex_best_friends[i], &types[i], animal_p, mNpc_GetAnimalSex(animal_p));
        }

        animal_p++;
    }

    for (i = 0; i < mNpc_EVENT_MAIL_FRIEND_NUM; i++) {
        animal_p = Save_Get(animals);

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if (other_sex_best_friends[j] >= 0 && types[j] == i) {
                pid = &animal_p->memories[other_sex_best_friends[j]].memory_player_id;
                player_no = mPr_GetPrivateIdx(pid);

                if (((player_bitfield >> player_no) & 1) == 1) {
                    if (mNpc_SendEventPresentMail(pid, player_no, &animal_p->id, i) == TRUE) {
                        other_sex_best_friends[j] = -1;
                        sent++;
                    } else {
                        player_bitfield &=
                            ~(1 << player_no); // remove player from bitfield because they can't receive letters
                    }
                }
            }

            if (player_bitfield == 0) {
                return sent; // all players cannot receive any further mail
            }

            animal_p++;
        }
    }

    return sent;
}

static void mNpc_GetBirthdayPresent(mActor_name_t* present) {
    static u8 category_table[5] = { mSP_KIND_FURNITURE, mSP_KIND_FURNITURE, mSP_KIND_CLOTH, mSP_KIND_CLOTH, 0xFF };

    int selected = category_table[RANDOM(ARRAY_COUNT(category_table))];

    if (selected == 0xFF) {
        mSP_RandomUmbSelect(present, 1);
    } else {
        mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, selected, mSP_LISTTYPE_RARE, FALSE);
    }
}

static void mNpc_GetBirthdayCard(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    static u8 animal_name[ANIMAL_NAME_LEN];

    u8 item_name[mIN_ITEM_NAME_LEN];
    int mail_no = 0xEA + anm_id->looks * 3 + RANDOM(3);
    mActor_name_t present;

    mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(animal_name, anm_id);
    mHandbill_Set_free_str(mHandbill_FREE_STR1, animal_name, ANIMAL_NAME_LEN);
    mNpc_GetBirthdayPresent(&present);
    mIN_copy_name_str(item_name, present);
    mHandbill_Set_free_str(mHandbill_FREE_STR2, item_name, mIN_ITEM_NAME_LEN);
    mNpc_LoadMailDataCommon2(mail, pid, anm_id, present, mNpc_GetPaperType(), mail_no);
}

static int mNpc_SendBirthdayCard(PersonalID_c* pid, int player_no, AnmPersonalID_c* anm_id) {
    Mail_c* mail = &l_npc_mail;
    mHm_hs_c* home;
    int free_idx;
    int res = FALSE;

    home = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

    if (mPr_NullCheckPersonalID(pid) == FALSE && mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
        mMl_clear_mail(mail);
        free_idx = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);

        if (free_idx != -1) {
            mNpc_GetBirthdayCard(mail, pid, anm_id);
            mMl_copy_mail(home->mailbox + free_idx, mail);
            res = TRUE;
        } else if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE) {
            mNpc_GetBirthdayCard(mail, pid, anm_id);
            res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
        }
    }

    return res;
}

extern int mNpc_CheckFriendship(PersonalID_c* pid, Animal_c* animal) {
    int best_idx;
    int idx = -1;

    if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
        best_idx = mNpc_GetHighestFriendshipIdx(animal->memories, ANIMAL_MEMORY_NUM);

        if (best_idx != -1 && mPr_CheckCmpPersonalID(pid, &animal->memories[best_idx].memory_player_id) &&
            Now_Private->birthday_present_npc != animal->id.npc_id) {
            idx = best_idx;
        }
    }

    return idx;
}

extern int mNpc_CheckFriendship_native(PersonalID_c* pid, Animal_c* animal) {
    int best_idx;
    int idx = -1;

    if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
        best_idx = mNpc_GetHighestFriendshipIdx_native(animal->memories, ANIMAL_MEMORY_NUM);

        if (best_idx != -1 && mPr_CheckCmpPersonalID(pid, &animal->memories[best_idx].memory_player_id) &&
            Now_Private->birthday_present_npc != animal->id.npc_id) {
            idx = best_idx;
        }
    }

    return idx;
}

/* @unused */
/*
extern int mNpc_SendEventBirthdayCard(PersonalID_c* pid) {
  return FALSE; // seemingly stubbed
}
*/

extern int mNpc_SendEventBirthdayCard2(PersonalID_c* pid, int player_no) {
    Animal_c* animal = Save_Get(animals);
    int res = FALSE;
    int i;

    if (pid != NULL && mLd_CheckThisLand(pid->land_name, pid->land_id) == TRUE) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFriendship_native(pid, animal) != -1 && mNpc_SendBirthdayCard(pid, player_no, &animal->id) == TRUE) {
                res = TRUE;
            }

            animal++;
        }

        if (Now_Private->celebrated_birthday_year != Common_Get(time.rtc_time).year) {
            Now_Private->birthday_present_npc = EMPTY_NO;
            Now_Private->celebrated_birthday_year = Common_Get(time.rtc_time).year;
        }
    }

    return res;
}

static void mNpc_GetXmasCardData(Mail_c* mail, PersonalID_c* pid) {
    int header_back_start;

    mHandbill_Load_HandbillFromRom(mail->content.text.split.header, &header_back_start, mail->content.text.split.footer,
                                   mail->content.text.split.body, 0xD7);
    mail->content.header_back_start = header_back_start;
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_XMAS;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, pid);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
    mail->present = FTR_START(FTR_FAMICOM_COMMON13);
    mail->content.paper_type = 22; // festive paper
}

extern int mNpc_SendEventXmasCard(PersonalID_c* pid, int player_no) {
    Mail_c* mail = &l_npc_mail;
    mHm_hs_c* home;
    int res = FALSE;

    if (mPr_NullCheckPersonalID(pid) == FALSE) {
        home = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

        if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
            int free_space = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);

            if (free_space != -1) {
                mMl_clear_mail(mail);
                mNpc_GetXmasCardData(mail, pid);
                mMl_copy_mail(home->mailbox + free_space, mail);
                res = TRUE;
            }
        }
    }

    return res;
}

extern int mNpc_GetPresentClothMemoryIdx(Anmmem_c* memory) {
    int i;
    int res = -1;

    if (memory != NULL) {
        for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
            if (memory->letter_info.wearing_present_cloth == TRUE) {
                res = i;
                break;
            }

            memory++;
        }
    }

    return res;
}

extern int mNpc_GetPresentClothMemoryIdx_rnd(Anmmem_c* memory) {
    Anmmem_c* mem_p = memory;
    int selected;
    int cloth_mem = 0;
    int res = -1;
    int i;

    if (memory != NULL) {
        for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
            if (mNpc_CheckFreeAnimalMemory(memory) == FALSE && memory->letter_info.wearing_present_cloth == TRUE) {
                cloth_mem++;
            }

            memory++;
        }

        if (cloth_mem > 0) {
            selected = RANDOM(cloth_mem);
            memory = mem_p;
            for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
                if (mNpc_CheckFreeAnimalMemory(memory) == FALSE && memory->letter_info.wearing_present_cloth == TRUE) {
                    if (selected <= 0) {
                        res = i;
                        break;
                    } else {
                        selected--;
                    }
                }

                memory++;
            }
        }
    }

    return res;
}

extern int mNpc_CheckTalkPresentCloth(Animal_c* animal) {
    int res = FALSE;

    if (animal != NULL && mNpc_GetPresentClothMemoryIdx(animal->memories) != -1) {
        res = TRUE;
    }

    return res;
}

extern void mNpc_ChangePresentCloth() {
    Animal_c* animal = Save_Get(animals);
    Anmmem_c* memory;
    mActor_name_t present_cloth;
    int i;
    int j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        present_cloth = animal->present_cloth;

        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE && present_cloth != EMPTY_NO &&
            ITEM_NAME_GET_TYPE(present_cloth) == NAME_TYPE_ITEM1 &&
            ITEM_NAME_GET_CAT(present_cloth) == ITEM1_CAT_CLOTH) {
            memory = animal->memories;

            for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
                if (mNpc_CheckFreeAnimalMemory(memory) == FALSE && memory->letter_info.has_present_cloth == TRUE) {
                    memory->letter_info.wearing_present_cloth = TRUE;
                    memory->letter_info.has_present_cloth = FALSE;
                    animal->cloth = present_cloth;
                    break;
                }

                memory++;
            }
        }

        animal++;
    }
}

extern u8* mNpc_GetWordEnding(ACTOR* actor) {
    NPC_ACTOR* npc;
    Animal_c* animal;
    u8* word_ending;

    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
        npc = (NPC_ACTOR*)actor;
        animal = npc->npc_info.animal_orig;

        if (npc->insect_actor != NULL) {
            mString_Load_StringFromRom(l_nomi_npc_ending, ANIMAL_CATCHPHRASE_LEN, 0x738 + RANDOM(16));
            word_ending = l_nomi_npc_ending;
        } else if (animal != NULL) {
            word_ending = animal->catchphrase;
        } else {
            word_ending = l_no_ending_npc_ending;
        }
    } else {
        word_ending = l_no_ending_npc_ending;
    }

    return word_ending;
}

extern u8* mNpc_GetWordEnding_forTag(ACTOR* actorx) {
    u8* word_ending;

    if (actorx != NULL && actorx->part == ACTOR_PART_NPC) {
        NPC_ACTOR* npc = (NPC_ACTOR*)actorx;
        Animal_c* animal = npc->npc_info.animal_orig;

        if (animal != NULL) {
            word_ending = animal->catchphrase;
        } else {
            word_ending = l_no_ending_npc_ending;
        }
    } else {
        word_ending = l_no_ending_npc_ending;
    }

    return word_ending;
}

extern void mNpc_ResetWordEnding(ACTOR* actorx) {
    if (actorx != NULL && actorx->part == ACTOR_PART_NPC) {
        NPC_ACTOR* npc = (NPC_ACTOR*)actorx;
        Animal_c* animal = npc->npc_info.animal_orig;

        if (animal != NULL) {
            if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
                AnimalInfo_c* info = mAN_getP_animalInfo(animal->id.npc_id);

                if (info != NULL) {
                    mem_copy(animal->catchphrase, info->catchphrase, ANIMAL_CATCHPHRASE_LEN);
                }
            } else {
                mString_Load_StringFromRom(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN,
                                           npc_def_list[animal->id.npc_id & 0xFFF].catchphrase_str_idx);
            }
        }
    }
}

extern int mNpc_GetFreeEventNpcIdx() {
    mNpc_EventNpc_c* event_npc = Common_Get(event_npc);
    int i;

    for (i = 0; i < mNpc_EVENT_NPC_NUM; i++) {
        if (event_npc->in_use == FALSE) {
            return i;
        }

        event_npc++;
    }

    return -1;
}

extern int mNpc_RegistEventNpc(mActor_name_t event_id, mActor_name_t texture_id, mActor_name_t npc_id,
                               mActor_name_t cloth_id) {
    int free_idx = mNpc_GetFreeEventNpcIdx();
    int res = FALSE;

    if (free_idx != -1) {
        mNpc_EventNpc_c* event_npc = Common_GetPointer(event_npc[free_idx]);

        if (cloth_id != EMPTY_NO) {
            if (((cloth_id == RSV_CLOTH) || (cloth_id >= ITM_CLOTH_START && cloth_id < ITM_CLOTH_END) ||
                 cloth_id == RSV_CLOTH1) == FALSE) {
                cloth_id = ITM_CLOTH000;
            }
        }

        event_npc->event_id = event_id;
        event_npc->texture_id = texture_id;
        event_npc->npc_id = npc_id;
        event_npc->cloth_id = cloth_id;
        event_npc->exists = FALSE;
        event_npc->in_use = TRUE;

        res = TRUE;
    }

    return res;
}

extern void mNpc_UnRegistEventNpc(mNpc_EventNpc_c* npc) {
    mNpc_EventNpc_c* event_npc = Common_Get(event_npc);
    int i;

    for (i = 0; i < mNpc_EVENT_NPC_NUM; i++) {
        if (event_npc == npc) {
            bzero(npc, sizeof(mNpc_EventNpc_c));
            break;
        }

        event_npc++;
    }
}

extern void mNpc_ClearEventNpc() {
    bzero(Common_Get(event_npc), mNpc_EVENT_NPC_NUM * sizeof(mNpc_EventNpc_c));
}

extern mNpc_EventNpc_c* mNpc_GetSameEventNpc(mActor_name_t event_id) {
    mNpc_EventNpc_c* event_npc = Common_Get(event_npc);
    int i;

    for (i = 0; i < mNpc_EVENT_NPC_NUM; i++) {
        if (event_npc->event_id == event_id) {
            return event_npc;
        }

        event_npc++;
    }

    return NULL;
}

extern int mNpc_GetFreeMaskNpcIdx() {
    mNpc_MaskNpc_c* mask_npc = Common_Get(mask_npc);
    int i;

    for (i = 0; i < mNpc_MASK_NPC_NUM; i++) {
        if (mask_npc->in_use == FALSE) {
            return i;
        }

        mask_npc++;
    }

    return -1;
}

extern int mNpc_RegistMaskNpc(mActor_name_t mask_id, mActor_name_t npc_id, mActor_name_t cloth_id) {
    int free_idx = mNpc_GetFreeMaskNpcIdx();
    int res = FALSE;

    if (free_idx != -1) {
        mNpc_MaskNpc_c* mask_npc = Common_GetPointer(mask_npc[free_idx]);

        if (cloth_id != EMPTY_NO) {
            if (((cloth_id == RSV_CLOTH) || (cloth_id >= ITM_CLOTH_START && cloth_id < ITM_CLOTH_END) ||
                 cloth_id == RSV_CLOTH1) == FALSE) {
                cloth_id = ITM_CLOTH000;
            }
        }

        mask_npc->mask_id = mask_id;
        mask_npc->npc_id = npc_id;
        mask_npc->exists = FALSE;
        mask_npc->in_use = TRUE;

        if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
            int animal_idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_id, ANIMAL_NUM_MAX);

            if (animal_idx != -1) {
                mNpc_CopyAnimalInfo(&mask_npc->animal_data, Save_GetPointer(animals[animal_idx]));
            } else {
                int idx;

                mNpc_ClearAnimalInfo(&mask_npc->animal_data);
                mNpc_SetDefAnimal(&mask_npc->animal_data, npc_id, npc_def_list);

                idx = npc_id & 0xFFF;
                mNpc_LoadNpcNameString(mask_npc->animal_data.id.name, idx);
            }

            if (cloth_id == EMPTY_NO) {
                mask_npc->cloth_id = mask_npc->animal_data.cloth;
            } else {
                mask_npc->cloth_id = cloth_id;
            }
        } else {
            mask_npc->cloth_id = cloth_id;
        }

        res = TRUE;
    }

    return res;
}

extern void mNpc_UnRegistMaskNpc(mNpc_MaskNpc_c* npc) {
    mNpc_MaskNpc_c* mask_npc = Common_Get(mask_npc);
    int i;

    for (i = 0; i < mNpc_MASK_NPC_NUM; i++) {
        if (mask_npc == npc) {
            bzero(npc, sizeof(mNpc_MaskNpc_c));
            break;
        }

        mask_npc++;
    }
}

extern void mNpc_ClearMaskNpc() {
    bzero(Common_Get(mask_npc), mNpc_MASK_NPC_NUM * sizeof(mNpc_MaskNpc_c));
}

extern mNpc_MaskNpc_c* mNpc_GetSameMaskNpc(mActor_name_t mask_id) {
    mNpc_MaskNpc_c* mask_npc = Common_Get(mask_npc);
    int i;

    for (i = 0; i < mNpc_MASK_NPC_NUM; i++) {
        if (mask_npc->mask_id == mask_id) {
            return mask_npc;
        }

        mask_npc++;
    }

    return NULL;
}

extern u8 mNpc_GetRace(ACTOR* actorx) {
    u8 race = mNpc_SPECIES_NUM;

    if (actorx != NULL && ITEM_NAME_GET_TYPE(actorx->npc_id) == NAME_TYPE_NPC) {
        NPC_ACTOR* npc = (NPC_ACTOR*)actorx;
        Animal_c* animal = npc->npc_info.animal_orig;

        if (animal != NULL) {
            race = animal->race;
        }
    }

    return race;
}

extern u8 mNpc_GetLooks(mActor_name_t npc_id) {
    u8 looks = mNpc_LOOKS_GIRL;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        if (IS_NPC_ADD_NPC(npc_id)) {
            AnimalInfo_c* info = mAN_getP_animalInfo(npc_id);

            if (info != NULL) {
                looks = info->looks;
            }
        } else {
            looks = npc_looks_table[npc_id & 0xFFF];
        }
    }

    return looks;
}

static void mNpc_SetDefAnimalInfo(Animal_c* animal, mActor_name_t npc_id, u8 looks, mNpc_Default_Data_c* def_data) {
    mLd_land_info_c* land_info = Save_GetPointer(land_info);

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        if (IS_NPC_ADD_NPC(npc_id)) {
            mAN_set_def_animalInfo(animal, npc_id);
        } else {
            animal->id.npc_id = npc_id;
            animal->id.looks = looks;
            animal->cloth = def_data->cloth;
            animal->umbrella_id = def_data->umbrella;
            animal->race = def_data->race;
            mString_Load_StringFromRom(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN, def_data->catchphrase_str_idx);
        }

        animal->id.land_id = land_info->id;
        mLd_CopyLandName(animal->id.land_name, land_info->name);
    }
}

extern u8 mNpc_GetDefAnimalClothLAttr(Animal_c* animal) {
    u8 cloth_l_attr = mNT_STYLE_COOL;

    if (ITEM_NAME_GET_TYPE(animal->id.npc_id) == NAME_TYPE_NPC) {
        if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
            AnimalInfo_c* info = mAN_getP_animalInfo(animal->id.npc_id);
            if (info != NULL) {
                cloth_l_attr = info->love_cloth_type;
            }
        } else {
            int idx = animal->id.npc_id & 0xFFF;

            if (idx >= 0 && idx < NPC_ROM_NUM) {
                cloth_l_attr = npc_def_list[idx].love_cloth_type;
            }
        }
    }

    return cloth_l_attr;
}

extern u8 mNpc_GetDefAnimalClothHAttr(Animal_c* animal) {
    u8 cloth_h_attr = mNT_STYLE_COOL;

    if (ITEM_NAME_GET_TYPE(animal->id.npc_id) == NAME_TYPE_NPC) {
        if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
            AnimalInfo_c* info = mAN_getP_animalInfo(animal->id.npc_id);
            if (info != NULL) {
                cloth_h_attr = info->hate_cloth_type;
            }
        } else {
            int idx = animal->id.npc_id & 0xFFF;

            if (idx >= 0 && idx < NPC_ROM_NUM) {
                cloth_h_attr = npc_def_list[idx].hate_cloth_type;
            }
        }
    }

    return cloth_h_attr;
}

extern void mNpc_SetDefAnimalCloth(Animal_c* animal) {
    if (ITEM_NAME_GET_TYPE(animal->id.npc_id) == NAME_TYPE_NPC) {
        if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
            AnimalInfo_c* info = mAN_getP_animalInfo(animal->id.npc_id);
            if (info != NULL) {
                // @BUG - devs forgot to add the shirt index to the start of the shirt items
#if VERSION == VER_GAEJ01_00 && !defined(BUGFIXES)
                animal->cloth = info->shirt_no;
#else
                animal->cloth = ITM_CLOTH_START + info->shirt_no;
#endif
                animal->cloth_original_id = 0xFF;
            }
        } else {
            int idx = animal->id.npc_id & 0xFFF;

            if (idx >= 0 && idx < NPC_ROM_NUM) {
                animal->cloth = npc_def_list[idx].cloth;
                animal->cloth_original_id = 0xFF;
            }
        }
    }
}

extern void mNpc_SetDefAnimalUmbrella(Animal_c* animal) {
    if (ITEM_NAME_GET_TYPE(animal->id.npc_id) == NAME_TYPE_NPC) {
        if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
            AnimalInfo_c* info = mAN_getP_animalInfo(animal->id.npc_id);
            if (info != NULL) {
                animal->umbrella_id = info->umbrella_no;
            }
        } else {
            int idx = animal->id.npc_id & 0xFFF;

            if (idx >= 0 && idx < NPC_ROM_NUM) {
                animal->umbrella_id = npc_def_list[idx].umbrella;
            }
        }
    }
}

extern void mNpc_SetDefAnimal(Animal_c* animal, mActor_name_t npc_id, mNpc_Default_Data_c* def_data) {
    int idx = npc_id & 0xFFF;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        mNpc_SetDefAnimalInfo(animal, npc_id, npc_looks_table[idx], &def_data[idx]);
    }
}

extern void mNpc_SetDefAnimal_name(Animal_c* animal, mActor_name_t npc_id) {
    int idx = npc_id & 0xFFF;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        mNpc_SetDefAnimalInfo(animal, npc_id, npc_looks_table[idx], &npc_def_list[idx]);
    }
}

extern void mNpc_SetHaveAppeared(mActor_name_t npc_id) {
    u8* used_tbl = Save_Get(npc_used_tbl);
    int idx;
    int i;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        idx = npc_id & 0xFFF;
        i = idx / 8;

        if (i < ARRAY_COUNT(Save_Get(npc_used_tbl))) {
            used_tbl += i;
            idx = idx & 7u;
            *used_tbl |= 1 << idx;
        }
    }
}

static int mNpc_GetHaveAppeared_idx(int idx) {
    u8* used_tbl = Save_Get(npc_used_tbl);
    int i = idx / 8;
    int res = TRUE;

    if (i < ARRAY_COUNT(Save_Get(npc_used_tbl))) {
        used_tbl += i;
        res = (*used_tbl >> (idx & 7u)) & 1;
    }

    return res;
}

static int mNpc_GetDefGrowPermission(int idx, s8* grow_list, int count) {
    int res = mNpc_GROW_MOVE_IN;

    if (idx >= 0 && idx < count) {
        res = grow_list[idx];
    }

    return res;
}

static int mNpc_GetDefGrowPermissionIdx(int idx) {
    return mNpc_GetDefGrowPermission(idx, npc_grow_list, NPC_ROM_NUM);
}

extern int mNpc_GetDefGrowPermissionName(mActor_name_t npc_id) {
    int ret = -1;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        ret = mNpc_GetDefGrowPermissionIdx(npc_id & 0xFFF);
    }

    return ret;
}

static int mNpc_GetLooks2NotHaveAppearedNum(u8 looks) {
    u8* looks_tbl;
    s8* grow_list = npc_grow_list;
    int num = 0;
    int i;

    if (looks < mNpc_LOOKS_NUM) {
        looks_tbl = npc_looks_table;

        for (i = 0; i < NPC_ROM_NUM; i++) {
            if (looks == looks_tbl[0]) {
                int grow_type = mNpc_GetDefGrowPermission(i, grow_list, NPC_ROM_NUM);

                if (mNpc_GetHaveAppeared_idx(i) == FALSE &&
                    (grow_type == mNpc_GROW_STARTER || grow_type == mNpc_GROW_MOVE_IN)) {
                    num++;
                }
            }

            looks_tbl++;
        }
    }

    return num;
}

static void mNpc_ResetHaveAppeared_common(u8* npc_used_tbl, Animal_c* animal) {
    int i;

    bzero(npc_used_tbl, sizeof(Save_Get(npc_used_tbl)));
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            mNpc_SetHaveAppeared(animal->id.npc_id);
        }

        animal++;
    }
}

static void mNpc_ResetHaveAppeared() {
    s8* grow_list = npc_grow_list;
    int i;

    for (i = 0; i < NPC_ROM_NUM; i++) {
        u32 grow_perm = mNpc_GetDefGrowPermission(i, grow_list, NPC_ROM_NUM);

        if (mNpc_GetHaveAppeared_idx(i) == FALSE && grow_perm <= mNpc_GROW_MOVE_IN) {
            break;
        }
    }

    /* All animals have appeared in town (islanders excluded) */
    if (i == NPC_ROM_NUM) {
        mNpc_ResetHaveAppeared_common(Save_Get(npc_used_tbl), Save_Get(animals));
    }
}

static void mNpc_DecideLivingNpcMax(Animal_c* animal, u8 count, int malloc_flag) {
    static int fakeTable[NPC_ROM_NUM];

    mNpc_Default_Data_c* def_list;
    s8* grow_list;
    u8 looks_bitfield = 0;
    int i = 0;
    int animal_idx = 0;

    bzero(fakeTable, sizeof(fakeTable));
    mNpc_MakeRandTable(fakeTable, NPC_ROM_NUM, NPC_ROM_NUM);
    def_list = npc_def_list;
    grow_list = npc_grow_list;

    while (count != 0) {
        if (animal == NULL) {
            break;
        }

        if (animal->id.npc_id == EMPTY_NO) {
            int idx = fakeTable[i];
            mActor_name_t npc_id = NPC_START | idx;
            int grow_perm = mNpc_GetDefGrowPermission(idx, grow_list, NPC_ROM_NUM);

            if (grow_perm == mNpc_GROW_STARTER) {
                int looks = npc_looks_table[idx];

                if (((looks_bitfield >> looks) & 1) == 0) {
                    mNpc_SetDefAnimal(animal, npc_id, def_list);
                    looks_bitfield |= (1 << looks);
                    mNpc_SetHaveAppeared(npc_id);
                    animal++;
                    animal_idx++;
                    count--;
                }
            } else if (grow_perm == -1) {
                mNpc_SetHaveAppeared(npc_id);
            }
        } else {
            animal++;
            ;
            animal_idx++;
            count--;
        }

        i++;
    }
}

extern void mNpc_SetAnimalTitleDemo(mNpc_demo_npc_c* demo_npc, Animal_c* animal, GAME* game) {
    mNpc_Default_Data_c* def_list = npc_def_list;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        mNpc_SetDefAnimal(animal, demo_npc->npc_name, def_list);
        animal->home_info.type_unused = 0;
        animal->home_info.bx = demo_npc->block_x;
        animal->home_info.bz = demo_npc->block_z;
        animal->home_info.ux = demo_npc->ut_x;
        animal->home_info.uz = demo_npc->ut_z;

        animal++;
        demo_npc++;
    }
}

extern int mNpc_GetReservedUtNum(int* ut_x, int* ut_z, mActor_name_t* item) {
    f32 reserve_num = 0.0f;
    int rand;
    int res = FALSE;
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (mNT_IS_RESERVE(*item) || *item == DUMMY_RESERVE) {
            reserve_num++;
        }

        item++;
    }

    if (reserve_num > 0.0f) {
        item -= UT_TOTAL_NUM;
        rand = RANDOM(reserve_num);

        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (mNT_IS_RESERVE(*item) || *item == DUMMY_RESERVE) {
                if (rand == 0) {
                    *ut_x = i % UT_Z_NUM;
                    *ut_z = i / UT_X_NUM;
                    res = TRUE;

                    break;
                } else {
                    rand--;
                }
            }

            item++;
        }
    }

    return res;
}

extern void mNpc_MakeReservedListBeforeFieldct(Anmhome_c* reserved, int reserved_num, u8* reserved_count) {
    mFM_fg_c* fg = Save_GetPointer(fg[0][0]);
    Anmhome_c* reserved_p = reserved;
    mActor_name_t* item;
    u8 num = 0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < reserved_num; i++) {
        reserved->bx = -1;
        reserved->bz = -1;
        reserved->ux = -1;
        reserved->uz = -1;
        reserved++;
    }

    reserved = reserved_p;
    for (i = 0; i < FG_BLOCK_Z_NUM; i++) {
        for (j = 0; j < FG_BLOCK_X_NUM; j++) {
            item = &fg->items[0][0];

            for (k = 0; k < UT_Z_NUM; k++) {
                for (l = 0; l < UT_X_NUM; l++) {
                    if (mNT_IS_RESERVE(*item)) {
                        num++;
                        reserved->bx = j + 1;
                        reserved->bz = i + 1;
                        reserved->ux = l;
                        reserved->uz = k;
                        reserved++;
                        if (num >= reserved_num) {
                            *reserved_count = num;
                            return;
                        }
                    }

                    item++;
                }
            }

            fg++;
        }
    }

    *reserved_count = num;
}

extern void mNpc_MakeReservedListAfterFieldct(Anmhome_c* reserved, int reserved_num, u8* reserved_count, u8 bx_max,
                                              u8 bz_max) {
    mFM_block_info_c* block_info = mFI_GetBlockTopP();
    Anmhome_c* reserved_p = reserved;
    mActor_name_t* item;
    u8 num = 0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < reserved_num; i++) {
        reserved->bx = -1;
        reserved->bz = -1;
        reserved->ux = -1;
        reserved->uz = -1;
        reserved++;
    }

    reserved = reserved_p;
    for (i = 0; i < bz_max; i++) {
        for (j = 0; j < bx_max; j++) {
            if (block_info != NULL) {
                item = block_info->fg_info.items_p;

                if (item != NULL) {
                    for (k = 0; k < UT_Z_NUM; k++) {
                        for (l = 0; l < UT_X_NUM; l++) {
                            if (mNT_IS_RESERVE(*item)) {
                                num++;
                                reserved->bx = j;
                                reserved->bz = i;
                                reserved->ux = l;
                                reserved->uz = k;
                                reserved++;
                                if (num >= reserved_num) {
                                    *reserved_count = num;
                                    return;
                                }
                            }

                            item++;
                        }
                    }
                }
            }

            block_info++;
        }
    }

    *reserved_count = num;
}

static void mNpc_BuildHouse(mActor_name_t* item_data, u16* deposit_data, mActor_name_t set_item, int x, int z) {
    static int ut_d[9][2] = {
        { 0, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { -1, 0 }, { 1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 },
    };

    static mActor_name_t set_fg[9] = {
        EMPTY_NO, // npc house id
        ACTOR_PROP_VILLAGER_SIGNBOARD,
        RSV_NO,
        RSV_NO,
        RSV_NO,
        RSV_NO,
        RSV_NO,
        RSV_NO,
        RSV_NO,
    };

    if (item_data != NULL && x > 0 && x < (UT_X_NUM - 1) && z > 0 && z < (UT_Z_NUM - 1)) {
        mActor_name_t* fg_p;
        int ux;
        int uz;
        int i;

        set_fg[0] = set_item;
        for (i = 0; i < ARRAY_COUNT(set_fg); i++) {
            ux = ut_d[i][0] + x;
            uz = ut_d[i][1] + z;
            fg_p = &item_data[uz * UT_X_NUM + ux];

            mPB_keep_item(*fg_p);
            mSN_ClearSnowman(fg_p);

            if (deposit_data != NULL) {
                mFI_BlockDepositOFF(deposit_data, ux, uz);
            }

            *fg_p = set_fg[i];
        }

        set_fg[0] = EMPTY_NO;
    }
}

static void mNpc_BuildHouseBeforeFieldct(mActor_name_t npc_id, int bx, int bz, int ut_x, int ut_z) {
    mActor_name_t house = npc_id - NPC_START + NPC_HOUSE_START;
    u16* deposit;
    mFM_fg_c* fg;

    if (bx >= 0 && bx < FG_BLOCK_X_NUM && bz >= 0 && bz < FG_BLOCK_Z_NUM) {
        deposit = mFI_GetDepositP(bx + 1, bz + 1);
        fg = Save_GetPointer(fg[bz][bx]);

        mNpc_BuildHouse((mActor_name_t*)fg->items, deposit, house, ut_x, ut_z);
    }
}

extern void mNpc_DestroyHouse_block(mFM_fg_c* fg, Anmhome_c* home) {
    u8 bx = home->bx - 1;
    u8 bz = home->bz - 1;
    u8 ux = home->ux;
    u8 uz = home->uz - 1;

    if (bx < FG_BLOCK_X_NUM && bz < FG_BLOCK_Z_NUM && ux > 0 && ux < (UT_X_NUM - 1) && uz > 0 && uz < (UT_Z_NUM - 1)) {
        mActor_name_t reserve_no = mFM_GetReseveName_com(home->bx, home->bz, fg);
        int ut = uz * UT_X_NUM + ux;
        mFM_fg_c* fg_p = &fg[bz * FG_BLOCK_X_NUM + bx];
        mActor_name_t* items = fg_p->items[0];

        items[ut] = reserve_no;
        items[ut + UT_X_NUM - 1] = EMPTY_NO;
        items[ut + UT_X_NUM] = EMPTY_NO;
        items[ut + UT_X_NUM + 1] = EMPTY_NO;
        items[ut - 1] = EMPTY_NO;
        items[ut + 1] = EMPTY_NO;
        items[ut - UT_X_NUM - 1] = EMPTY_NO;
        items[ut - UT_X_NUM] = EMPTY_NO;
        items[ut - UT_X_NUM + 1] = EMPTY_NO;
    }
}

extern void mNpc_DestroyHouse(Anmhome_c* home) {
    mNpc_DestroyHouse_block((mFM_fg_c*)Save_Get(fg), home);
}

static void mNpc_SetNpcHome(Animal_c* animal, Anmhome_c* reserved, u8 reserved_num) {
    static int fakeTable[60];

    Anmhome_c* home;
    int* fake_table_p = fakeTable;
    int n = 0;
    int i;
    int idx;

    if (reserved_num > ARRAY_COUNT(fakeTable)) {
        reserved_num = ARRAY_COUNT(fakeTable);
    }

    if (reserved_num > 0) {
        bzero(fake_table_p, sizeof(fakeTable));
        mNpc_MakeRandTable(fake_table_p, reserved_num, ARRAY_COUNT(fakeTable) / 2);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (ITEM_NAME_GET_TYPE(animal->id.npc_id) == NAME_TYPE_NPC && animal->home_info.bx == 0xFF &&
                animal->home_info.bz == 0xFF) {
                idx = fake_table_p[n];

                if (idx >= reserved_num) {
                    while ((fake_table_p[n] >= reserved_num) && n < reserved_num) {
                        n++;
                    }

                    if (n >= reserved_num) {
                        return;
                    }

                    idx = fake_table_p[n];
                }

                if (idx < reserved_num) {
                    home = &reserved[idx];

                    animal->home_info.bx = home->bx;
                    animal->home_info.bz = home->bz;
                    animal->home_info.ux = home->ux;
                    animal->home_info.uz = home->uz + 1;
                    mNpc_BuildHouseBeforeFieldct(animal->id.npc_id, animal->home_info.bx - 1, animal->home_info.bz - 1,
                                                 animal->home_info.ux, home->uz);
                }

                n++;
            }

            if (n >= reserved_num) {
                break;
            }

            animal++;
        }
    }
}

extern void mNpc_InitNpcData() {
    static Anmhome_c reserved[60];
    Animal_c* animals = Save_Get(animals);
    u8 reserved_num = 0;

    mNpc_MakeReservedListBeforeFieldct(reserved, ARRAY_COUNT(reserved), &reserved_num);
    if (Save_Get(reserve_sign_count) == 0) {
        Save_Set(reserve_sign_count, reserved_num);
    }
    mNpc_SetNpcHome(animals, reserved, reserved_num);
}

extern void mNpc_InitNpcList(mNpc_NpcList_c* npclist, int count) {
    int i;

    if (npclist != NULL) {
        bzero(npclist, count * sizeof(mNpc_NpcList_c));

        for (i = 0; i < count; i++) {
            npclist->name = EMPTY_NO;
            npclist->field_name = RSV_NO;
            // mQst_ClearQuestInfo(&npclist->quest_info);
            npclist->house_data.type = 0xFF;
            npclist->house_data.palette = 0xFF;
            npclist->house_data.wall_id = 0xFF;
            npclist->house_data.floor_id = 0xFF;
            npclist->house_data.main_layer_id = 203;

            npclist++;
        }
    }
}

extern void mNpc_SetNpcList(mNpc_NpcList_c* npclist, Animal_c* animal, int count, int malloc_flag) {
    xyz_t pos;
    mActor_name_t npc_id;
    int i;
    mNpc_NpcHouseData_c* house_list = npc_house_list;
    int idx;

    for (i = 0; i < count; i++) {
        npc_id = animal->id.npc_id;

        if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC && animal->home_info.bx != 0xFF) {
            idx = npc_id & 0x0FFF;
            npclist->name = npc_id;

            npclist->house_position.x = animal->home_info.bx * mFI_BK_WORLDSIZE_X_F;
            npclist->house_position.z = animal->home_info.bz * mFI_BK_WORLDSIZE_Z_F;
            mFI_UtNum2PosXZInBk(&pos.x, &pos.z, animal->home_info.ux, animal->home_info.uz);
            npclist->house_position.x += pos.x;
            npclist->house_position.z += pos.z;
            npclist->house_position.y = 0.0f;

            npclist->position.x = npclist->house_position.x;
            npclist->position.y = npclist->house_position.y;
            npclist->position.z = npclist->house_position.z;

            npclist->appear_flag = TRUE;
            npclist->reward_furniture = EMPTY_NO;

            if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
                AnimalInfo_c* info = mAN_getP_animalInfo(animal->id.npc_id);
                npclist->house_data.type = info->house_type;
                npclist->house_data.palette = info->house_variant;
                npclist->house_data.wall_id = info->wall_no;
                npclist->house_data.floor_id = info->floor_no;
                npclist->house_data.main_layer_id = info->room_base_idx;
                npclist->house_data.secondary_layer_id = info->room_second_idx;
            } else {
                npclist->house_data.type = house_list[idx].type;
                npclist->house_data.palette = house_list[idx].palette;
                npclist->house_data.wall_id = house_list[idx].wall_id;
                npclist->house_data.floor_id = house_list[idx].floor_id;
                npclist->house_data.main_layer_id = house_list[idx].main_layer_id;
                npclist->house_data.secondary_layer_id = house_list[idx].secondary_layer_id;
            }
        }

        npclist++;
        animal++;
    }
}

extern void mNpc_SetNpcinfo(ACTOR* actor, s8 npc_info_idx) {
    if (actor->part == ACTOR_PART_NPC) {
        NPC_ACTOR* npc = (NPC_ACTOR*)actor;
        mActor_name_t npc_id = actor->npc_id;

        if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_SPNPC) {
            mNpc_EventNpc_c* event_npc = mNpc_GetSameEventNpc(npc_id);

            if (event_npc != NULL) {
                npc_info_idx = mNpc_SearchAnimalinfo(Save_Get(animals), event_npc->npc_id, ANIMAL_NUM_MAX);
            }
        }

        if (npc_info_idx >= 0 && npc_info_idx < ANIMAL_NUM_MAX) {
            npc->npc_info.animal_orig = Save_GetPointer(animals[npc_info_idx]);
            npc->npc_info.list = Common_GetPointer(npclist[npc_info_idx]);
        } else if (npc_info_idx == -ANIMAL_NUM_MAX) {
            if (Common_Get(cur_island_house_p) != NULL) {
                npc->npc_info.animal_orig = &Common_Get(cur_island_house_p)->island.animal;
            }
            npc->npc_info.list = Common_GetPointer(island_npclist[0]);
        } else {
            mNpc_MaskNpc_c* mask_npc = mNpc_GetSameMaskNpc(npc_id);

            if (mask_npc != NULL) {
                if (ITEM_NAME_GET_TYPE(mask_npc->npc_id) == NAME_TYPE_NPC) {
                    npc->npc_info.animal_orig = &mask_npc->animal_data;
                    npc->npc_info.list = NULL;
                } else {
                    npc->npc_info.animal_orig = NULL;
                    npc->npc_info.list = NULL;
                }
            } else {
                npc->npc_info.animal_orig = NULL;
                npc->npc_info.list = NULL;
            }
        }

        npc->npc_info.animal = npc->npc_info.animal_orig;
    }
}

static void mNpc_AddNpc_inNpcRoom(mFM_move_actor_c* move_actor, int move_actor_idx, u8 bx, u8 bz) {
    u32 owner_id = Common_Get(house_owner_name);
    mActor_name_t id = owner_id;

    if (id != RSV_NO) {
        if (id != EMPTY_NO && mEvNM_CheckJointEvent(owner_id) != TRUE) {
            int idx = mNpc_SearchAnimalinfo(Save_Get(animals), id, ANIMAL_NUM_MAX);

            if (idx != -1) {
                move_actor->name_id = id;
                move_actor->ut_x = 4;
                move_actor->ut_z = 7;
                move_actor->npc_info_idx = idx;
                move_actor->arg = -1;
                mFI_SetMoveActorBitData_ON(move_actor_idx, bx, bz);
            }
        }
    }
}

static void mNpc_AddNpc_inNpcRoomIsland(mFM_move_actor_c* move_actor, int move_actor_idx, u8 bx, u8 bz) {
    if (Common_Get(cur_island_house_p) != NULL) {
        move_actor->name_id = Common_Get(cur_island_house_p)->island.animal.id.npc_id;
        move_actor->ut_x = 4;
        move_actor->ut_z = 7;
        move_actor->npc_info_idx = -ANIMAL_NUM_MAX;
        move_actor->arg = -1;
        mFI_SetMoveActorBitData_ON(move_actor_idx, bx, bz);
    }
}

static void mNpc_AddNpc_inKamakura(mFM_move_actor_c* move_actor, int move_actor_idx, u8 bx, u8 bz) {
    u8* kamakura_event = (u8*)mEv_get_save_area(mEv_EVENT_KAMAKURA, 15);

    if (kamakura_event != NULL) {
        int idx = *kamakura_event;
        mActor_name_t npc_id = Save_Get(animals[idx]).id.npc_id;

        mEvMN_GetEventNpcName(&npc_id, mEv_EVENT_KAMAKURA, idx, 0);
        move_actor->name_id = npc_id;
        move_actor->ut_x = 4;
        move_actor->ut_z = 7;
        move_actor->npc_info_idx = idx;
        move_actor->arg = -1;
        mFI_SetMoveActorBitData_ON(move_actor_idx, bx, bz);
    }
}

extern void mNpc_AddNpc_inBlock(mFM_move_actor_c* move_actor_list, u8 bx, u8 bz) {
    int scene = Save_Get(scene_no);

    if ((scene == SCENE_NPC_HOUSE || scene == SCENE_KAMAKURA || scene == SCENE_COTTAGE_NPC) &&
        move_actor_list != NULL) {
        mActor_name_t field_id = mFI_GetFieldId(); // unused
        int move_actor_idx = mFI_GetMoveActorListIdx(move_actor_list, mFM_MOVE_ACTOR_NUM, EMPTY_NO);

        if (move_actor_idx != -1 && move_actor_idx < ANIMAL_NUM_MAX) {
            move_actor_list += move_actor_idx;

            switch (scene) {
                case SCENE_NPC_HOUSE:
                    mNpc_AddNpc_inNpcRoom(move_actor_list, move_actor_idx, bx, bz);
                    break;
                case SCENE_COTTAGE_NPC:
                    mNpc_AddNpc_inNpcRoomIsland(move_actor_list, move_actor_idx, bx, bz);
                    break;
                case SCENE_KAMAKURA:
                    mNpc_AddNpc_inKamakura(move_actor_list, move_actor_idx, bx, bz);
                    break;
            }
        }
    }
}

extern void mNpc_RenewalNpcRoom(s16* wall_floor) {
    mActor_name_t field_id = mFI_GetFieldId();
    mActor_name_t owner_id = Common_Get(house_owner_name);
    int island_wall = 0;
    int island_floor = 0;
    u8 wall = 0;
    u8 floor = 0;
    int island_room_ftr_num;

    if (Save_Get(scene_no) == SCENE_COTTAGE_NPC) {
        wall = 8;   // exotic wall
        floor = 32; // bamboo flooring
        island_room_ftr_num = mNpc_GetIslandRoomFtrNum();

        if (island_room_ftr_num >= 2 && Common_Get(cur_island_house_p) != NULL) {
            mNpc_GetIslandWallFloorIdx(&island_wall, &island_floor,
                                       Common_Get(cur_island_house_p)->island.animal.id.npc_id);
            wall = island_wall;

            if (island_room_ftr_num >= 5) {
                floor = island_floor;
            }
        }
    } else if (mFI_GET_TYPE(field_id) == mFI_FIELD_NPCROOM0 && owner_id != EMPTY_NO && owner_id != RSV_NO) {
        int idx = mNpc_SearchAnimalinfo(Save_Get(animals), owner_id, ANIMAL_NUM_MAX);
        mNpc_NpcList_c* npclist;

        if (idx == -1) {
            idx = 0;
        }

        npclist = Common_GetPointer(npclist[idx]);

        wall = npclist->house_data.wall_id;
        floor = npclist->house_data.floor_id;
    }

    wall_floor[0] = (wall << 8) | floor;
}

extern void mNpc_RenewalSetNpc(ACTOR* actor) {
    NPC_ACTOR* npc = (NPC_ACTOR*)actor;
    Animal_c* animal;

    if (npc->npc_info.list != NULL) {
        mActor_name_t field_id = mFI_GetFieldId();
        mNpc_NpcList_c* npclist = npc->npc_info.list;
        xyz_t* npc_pos = &npclist->position;

        if (mFI_GET_TYPE(field_id) == mFI_FIELD_FG) {
            xyz_t_move(npc_pos, &actor->world.position);
            npclist->appear_flag = TRUE;

            if (Common_Get(cur_island_house_p) != NULL) {
                animal = &Common_Get(cur_island_house_p)->island.animal;

                if (actor->npc_id == animal->id.npc_id) {
                    int bnum = mFI_GetBlockNum(actor->block_x, actor->block_z);
                    mFM_move_actor_c* move_actor_list = g_fdinfo->block_info[bnum].fg_info.move_actors;

                    if (move_actor_list != NULL) {
                        int move_actor_idx =
                            mFI_GetMoveActorListIdx(move_actor_list, mFM_MOVE_ACTOR_NUM, actor->npc_id);

                        if (move_actor_idx != -1) {
                            int bx;
                            int bz;
                            int ut_x;
                            int ut_z;

                            if (mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &ut_x, &ut_z, npclist->position) == FALSE) {
                                ut_x = animal->home_info.ux;
                                ut_z = animal->home_info.uz;
                            } else if (mNpc_CheckNpcSet(bx, bz, ut_x, ut_z) == FALSE &&
                                       mNpc_GetMakeUtNuminBlock_area(&ut_x, &ut_z, bx, bz, 0) == FALSE) {
                                ut_x = animal->home_info.ux;
                                ut_z = animal->home_info.uz;
                            }

                            move_actor_list[move_actor_idx].ut_x = ut_x;
                            move_actor_list[move_actor_idx].ut_z = ut_z;
                        }
                    }

                    mFI_MyMoveActorBitData_ON(actor);
                }
            }
        }
    } else {
        mFI_MyMoveActorBitData_ON(actor);
    }
}

extern int mNpc_GetFriendAnimalNum(PersonalID_c* pid) {
    Animal_c* animal = Save_Get(animals);
    int num = 0;
    int i;

    if (pid != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE &&
                mNpc_GetAnimalMemoryIdx(pid, animal->memories, ANIMAL_MEMORY_NUM) != -1) {
                num++;
            }

            animal++;
        }
    }

    return num;
}

extern int mNpc_CheckFriendAllAnimal(PersonalID_c* pid) {
    int now_npc_max = mNpc_GetAnimalNum();
    int friend_num = mNpc_GetFriendAnimalNum(pid);

    if (now_npc_max <= friend_num) {
        return TRUE;
    }

    return FALSE;
}

static int mNpc_CheckSelectFurniture(mActor_name_t item) {
    int res = FALSE;

    if (!(item >= FTR_CLOTH_START && item <= FTR_CLOTH_END) &&                              // Clothing (furniture)
        !(item >= FTR_UMBRELLA_START && item <= FTR_UMBRELLA_END) &&                        // Umbrellas (furniture)
        !(item >= FTR_INSECT_START && item <= FTR_INSECT_END) &&                            // Insects (furniture)
        !(item >= FTR_FISH_START && item <= FTR_FISH_END) &&                                // Fish (furniture)
        !(item >= HANIWA_START && item <= HANIWA_END) &&                                    // Gyroids
        !(item >= FTR_DINO_START && item <= FTR_DINO_END) &&                                // Idenitfied fossils
        !(item >= FTR_START(FTR_FAMICOM_COMMON00) && item <= FTR_END(FTR_FAMICOM_COMMON18)) // NES/Famicom games
    ) {
        res = TRUE;
    }

    return res;
}

static mActor_name_t mNpc_DecideNpcFurniture(mFM_fg_data_c** fg_data_table, mNpc_NpcList_c* npclist, int fg_base_id) {
    int data_idx = npclist->house_data.main_layer_id - fg_base_id;
    mActor_name_t* fg_items;
    u8 num = 0;
    int ut_z;
    int ut_x;

    if (data_idx < 0) {
        data_idx = 0;
    }

    fg_items = fg_data_table[data_idx]->items[0];

    for (ut_z = 0; ut_z < 10; ut_z++) {
        for (ut_x = 0; ut_x < 10; ut_x++) {
            if (ITEM_IS_FTR(*fg_items) && mNpc_CheckSelectFurniture(*fg_items) == TRUE) {
                num++;
            }

            fg_items++;
        }

        fg_items += UT_X_NUM - 10;
    }

    if (num != 0) {
        num = RANDOM(num);

        fg_items = fg_data_table[data_idx]->items[0];
        for (ut_z = 0; ut_z < 10; ut_z++) {
            for (ut_x = 0; ut_x < 10; ut_x++) {
                if (ITEM_IS_FTR(*fg_items) && mNpc_CheckSelectFurniture(*fg_items) == TRUE) {
                    if (num <= 0) {
                        return *fg_items;
                    } else {
                        num--;
                    }
                }

                fg_items++;
            }

            fg_items += UT_X_NUM - 10;
        }
    }

    return EMPTY_NO;
}

extern void mNpc_SetNpcFurnitureRandom(mFM_fg_data_c** fg_data_table, int fg_base_id) {
    mNpc_NpcList_c* npclist = Common_Get(npclist);
    Animal_c* animal = Save_Get(animals);
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            npclist->reward_furniture = mNpc_DecideNpcFurniture(fg_data_table, npclist, fg_base_id);
        }

        npclist++;
        animal++;
    }
}

extern mActor_name_t mNpc_GetNpcFurniture(AnmPersonalID_c* anm_id) {
    mActor_name_t furniture = EMPTY_NO;
    int idx = mNpc_SearchAnimalPersonalID(anm_id);

    if (idx != -1) {
        furniture = Common_Get(npclist[idx]).reward_furniture;
    }

    return furniture;
}

static InAnimal_c l_mnpc_remove_in;

extern void mNpc_ClearInAnimal() {
    bzero(&l_mnpc_remove_in, sizeof(InAnimal_c));
    mNpc_ClearAnimalInfo(&l_mnpc_remove_in.animal);
}

extern InAnimal_c* mNpc_GetInAnimalP(void) {
    return &l_mnpc_remove_in;
}

extern void mNpc_RenewRemoveHistory(void) {
    mTM_set_renew_time(Save_GetPointer(force_remove_date), Common_GetPointer(time.rtc_time));
}

static int mNpc_DecideRemoveAnimalNo(Animal_c* animal, int ignored_idx, int sick_animal) {
    u8 candidate_table[ANIMAL_NUM_MAX];
    int candidates = 0;
    int selected_animal = -1;
    int i;

    bzero(candidate_table, sizeof(candidate_table));

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i != ignored_idx && i != sick_animal && !mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
            candidate_table[i] = TRUE;
            candidates++;
        }

        animal++;
    }

    if (candidates > 0) {
        int selected = RANDOM(candidates);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (candidate_table[i] == TRUE) {
                if (selected <= 0) {
                    selected_animal = i;
                    break;
                } else {
                    selected--;
                }
            }
        }
    }

    return selected_animal;
}

/**
 * Finds the most common appearance/looks among current animals.
 * Counts appearances and returns the most frequently occurring looks type.
 *
 * @param animal Pointer to first animal to analyze
 * @return Most common looks type among current animals
 */
static int mNpc_GetMaxLooks(Animal_c* animal) {
    u8 looks_count[mNpc_LOOKS_NUM];
    int max_looks = mNpc_LOOKS_NUM;
    int max_looks_count = 0;
    int i;

    bzero(looks_count, sizeof(looks_count));
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (!mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
            int looks = animal->id.looks;

            if (looks >= mNpc_LOOKS_NUM) {
                looks = mNpc_LOOKS_GIRL;
            }

            looks_count[looks]++;

            if (looks_count[looks] > max_looks_count) {
                max_looks = looks;
                max_looks_count = looks_count[looks];
            } else if (looks_count[looks] == max_looks_count) {
                max_looks = mNpc_LOOKS_NUM;
            }
        }

        animal++;
    }

    return max_looks;
}

enum {
    mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_NONE,
    mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_HAS_LETTER,
    mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_HAS_LETTER_AND_MAX_LOOKS,
    mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_NO_LETTER,

    mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_NUM
};

/**
 * Decides which animal to remove based on letter and appearance criteria.
 * Prioritizes animals without letters, then considers appearance diversity.
 *
 * @param animal Pointer to first animal to consider
 * @param ignore_idx Index of animal to ignore in selection
 * @param sick_animal Index of sick animal to ignore
 * @return Index of animal selected for removal, or -1 if none found
 */
static int mNpc_DecideRemoveAnimalNo_letter_looks(Animal_c* animal, int ignore_idx, int sick_animal) {
    u8 candidate_table[ANIMAL_NUM_MAX];
    Private_c* priv = Now_Private;
    int selected_animal = -1;
    int has_letter_num = 0;
    int has_letter_and_max_looks_num = 0;
    int no_memory_or_no_letter_num = 0;
    int selected = -1;
    int target_type = mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_NONE;
    int max_looks;
    int i;

    bzero(candidate_table, sizeof(candidate_table));
    max_looks = mNpc_GetMaxLooks(animal);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i != ignore_idx && i != sick_animal && !mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
            int mem_idx = -1;

            if (priv != NULL && !mPr_NullCheckPersonalID(&priv->player_ID)) {
                mem_idx = mNpc_GetAnimalMemoryIdx(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);
            }

            if (mem_idx != -1 && animal->memories[mem_idx].letter_info.exists == TRUE) {
                candidate_table[i] = mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_HAS_LETTER;
                has_letter_num++;

                if (max_looks == animal->id.looks) {
                    candidate_table[i] = mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_HAS_LETTER_AND_MAX_LOOKS;
                    has_letter_and_max_looks_num++;
                }
            } else {
                if (max_looks == animal->id.looks) {
                    candidate_table[i] = mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_NO_LETTER;
                    no_memory_or_no_letter_num++;
                }
            }
        }

        animal++;
    }

    if (has_letter_and_max_looks_num > 0) {
        selected = RANDOM(has_letter_and_max_looks_num);
        target_type = mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_HAS_LETTER_AND_MAX_LOOKS;
    } else if (has_letter_num > 0) {
        selected = RANDOM(has_letter_num);
        target_type = mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_HAS_LETTER;
    } else if (no_memory_or_no_letter_num > 0) {
        selected = RANDOM(no_memory_or_no_letter_num);
        target_type = mNpc_DECIDE_REMOVE_ANIMAL_NO_LETTER_LOOKS_NO_LETTER;
    }

    if (selected != -1) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (candidate_table[i] == target_type) {
                if (selected <= 0) {
                    selected_animal = i;
                    break;
                } else {
                    selected--;
                }
            }
        }
    }

    return selected_animal;
}

/**
 * Determines which sex has fewer animals in the town.
 * Counts males and females to find the underrepresented gender.
 *
 * @return Sex with fewer animals (mPr_SEX_MALE, mPr_SEX_FEMALE, or mPr_SEX_OTHER if equal)
 */
static int mNpc_GetMinSex(void) {
    Animal_c* animal = Save_Get(animals);
    int res = mPr_SEX_OTHER;
    int males = 0;
    int females = 0;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            switch (mNpc_GetAnimalSex(animal)) {
                case mPr_SEX_MALE:
                    males++;
                    break;
                case mPr_SEX_FEMALE:
                    females++;
                    break;
            }
        }

        animal++;
    }

    /* TODO: is this bugged? Shouldn't this check be inverted? */
    if (males > females) {
        res = mPr_SEX_MALE;
    } else if (males < females) {
        res = mPr_SEX_FEMALE;
    }

    return res;
}

/**
 * Decides which animal to remove based on sex balance.
 * Prioritizes removing animals of the more common sex to maintain gender balance.
 *
 * @param animal Pointer to first animal to consider
 * @param ignore_idx Index of animal to ignore in selection
 * @param sick_animal Index of sick animal to ignore
 * @return Index of animal selected for removal, or -1 if none found
 */
static int mNpc_DecideRemoveAnimalNo_sex(Animal_c* animal, int ignore_idx, int sick_animal) {
    u8 candidate_tbl[ANIMAL_NUM_MAX];
    int opposite_sex_num = 0;
    int min_sex = mNpc_GetMinSex();
    int selected_animal = -1;
    int i;

    if (min_sex != mPr_SEX_OTHER) {
        bzero(candidate_tbl, sizeof(candidate_tbl));

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (i != ignore_idx && i != sick_animal && !mNpc_CheckFreeAnimalPersonalID(&animal->id) &&
                mNpc_GetLooks2Sex(animal->id.looks) != min_sex) {
                candidate_tbl[i] = TRUE;
                opposite_sex_num++;
            }

            animal++;
        }

        if (opposite_sex_num > 0) {
            int selected = RANDOM(opposite_sex_num);

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (candidate_tbl[i] == TRUE) {
                    if (selected <= 0) {
                        selected_animal = i;
                        break;
                    } else {
                        selected--;
                    }
                }
            }
        }
    }

    return selected_animal;
}

/**
 * Sets which animal should be removed from the town.
 * Uses a multi-tiered approach: first by letter/looks, then by sex balance, finally random.
 *
 * @param remove_animal_no Output parameter for the animal index to remove
 * @param animal Pointer to first animal to consider
 * @param ignored_idx Index of animal to ignore in selection
 */
extern void mNpc_SetRemoveAnimalNo(u8* remove_animal_no, Animal_c* animal, int ignored_idx) {
    mNpc_SickInfo_c* sick_info = Save_GetPointer(sick_info);
    int npc_num = mNpc_GetAnimalNum();

    if (npc_num > ANIMAL_NUM_MIN && *remove_animal_no == 0xFF) {
        int sick_animal = mNpc_SearchAnimalPersonalID(&sick_info->id);

        // First, try to pick an animal which is in the max looks group and has received a letter from the current
        // player, one which simply has a letter from the current , or randomly between all villagers the player has
        // spoken to.
        int remove_no = mNpc_DecideRemoveAnimalNo_letter_looks(animal, ignored_idx, sick_animal);

        if (remove_no == -1) {
            // Next, try to pick an animal which at least is in the sex group with the most members
            remove_no = mNpc_DecideRemoveAnimalNo_sex(animal, ignored_idx, sick_animal);

            if (remove_no == -1) {
                // Finally, forcefully find an animal to remove
                remove_no = mNpc_DecideRemoveAnimalNo(animal, ignored_idx, sick_animal);
            }
        }

        if (remove_no != -1) {
            *remove_animal_no = remove_no;
        }
    }
}

/**
 * Finds the animal with the longest time since last interaction with the player.
 * Used for selecting animals that haven't been spoken to recently.
 *
 * @param animal Pointer to first animal to consider
 * @param ignore_idx Index of animal to ignore in selection
 * @param sick_animal Index of sick animal to ignore
 * @return Index of animal with longest time since interaction, or -1 if none found
 */
static int mNpc_GetRemotenessAnimalIdx(Animal_c* animal, int ignore_idx, int sick_animal) {
    Private_c* priv = Now_Private;
    Anmmem_c* memory;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int selected_animal = -1;
    u32 longest_interval = 0;
    u32 interval;
    int mem_idx;
    int i;

    if (priv != NULL && !mPr_NullCheckPersonalID(&priv->player_ID)) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (i != ignore_idx && i != sick_animal && !mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
                mem_idx = mNpc_GetAnimalMemoryIdx(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

                if (mem_idx != -1) {
                    memory = &animal->memories[mem_idx];

                    if (!lbRTC_IsEqualTime(&mTM_rtcTime_clear_code, &memory->last_speak_time, lbRTC_CHECK_ALL)) {

                        if (lbRTC_IsOverTime(&memory->last_speak_time, rtc_time) == lbRTC_OVER) {
                            interval = lbRTC_IntervalTime(rtc_time, &memory->last_speak_time);
                        } else {
                            interval = lbRTC_IntervalTime(&memory->last_speak_time, rtc_time);
                        }

                        if (longest_interval < interval) {
                            selected_animal = i;
                            longest_interval = interval;
                        } else if (longest_interval == interval) {
                            selected_animal = -1;
                        }
                    }
                }
            }

            animal++;
        }
    }

    return selected_animal;
}

/**
 * Finds an animal with the most common appearance/looks in the town.
 * Selects from animals with the max looks value for removal consideration.
 *
 * @param animal Pointer to first animal to consider
 * @param ignore_idx Index of animal to ignore in selection
 * @param sick_animal Index of sick animal to ignore
 * @return Index of animal with max looks, or -1 if none found
 */
static int mNpc_GetMaxLooksAnimal(Animal_c* animal, int ignore_idx, int sick_animal) {
    u8 select_tbl[ANIMAL_NUM_MAX];
    int looks_num = 0;
    int max_looks = mNpc_GetMaxLooks(animal);
    int selected_animal = -1;
    int i;

    if (max_looks != mNpc_LOOKS_NUM) {
        bzero(select_tbl, sizeof(select_tbl));

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (i != ignore_idx && i != sick_animal && !mNpc_CheckFreeAnimalPersonalID(&animal->id) &&
                animal->id.looks == max_looks) {
                select_tbl[i] = TRUE;
                looks_num++;
            }

            animal++;
        }

        if (looks_num > 0) {
            int selected = RANDOM(looks_num);

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (select_tbl[i] == TRUE) {
                    if (selected <= 0) {
                        selected_animal = i;
                        break;
                    } else {
                        selected--;
                    }
                }
            }
        }
    }

    return selected_animal;
}

/**
 * Finds the animal with the lowest total friendship across all memories.
 * Used for selecting animals with the least social connections for removal.
 *
 * @param animal Pointer to first animal to consider
 * @param ignore_idx Index of animal to ignore in selection
 * @param sick_animal Index of sick animal to ignore
 * @return Index of animal with lowest total friendship, or -1 if none found
 */
static int mNpc_GetTotalFriendshipMinAnimal(Animal_c* animal, int ignore_idx, int sick_animal) {
    int selected_animal;
    int lowest_friendship_count;
    Anmmem_c* memory;
    int friendship;
    int lowest_friendship;
    u8 lowest_friendship_table[ANIMAL_NUM_MAX];
    int i;
    int j;

    lowest_friendship_count = 0;
    // This results in 1905 (127 * 15). Since friendship is signed this would be the max value.
    // I think they meant to write 127 * ANIMAL_MEMORY_NUM perhaps? That would've been 127 * 7 or 889.
    lowest_friendship = 127 * ANIMAL_NUM_MAX;
    selected_animal = -1;

    bzero(lowest_friendship_table, sizeof(lowest_friendship_table));
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i != ignore_idx && i != sick_animal && !mNpc_CheckFreeAnimalPersonalID(&animal->id)) {
            memory = animal->memories;
            friendship = 0;

            for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
                if (!mPr_NullCheckPersonalID(&memory->memory_player_id)) {
                    friendship += memory->friendship;
                }

                memory++;
            }

            if (friendship < lowest_friendship) {
                selected_animal = i;
                lowest_friendship = friendship;
                bzero(lowest_friendship_table, sizeof(lowest_friendship_table));
                lowest_friendship_table[i] = TRUE;
                lowest_friendship_count = 1;
            } else if (friendship == lowest_friendship) {
                selected_animal = -1;
                lowest_friendship_table[i] = TRUE;
                lowest_friendship_count++;
            }
        }

        animal++;
    }

    if (selected_animal == -1 && lowest_friendship_count > 0) {
        int selected = RANDOM(lowest_friendship_count);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (lowest_friendship_table[i] == TRUE) {
                if (selected <= 0) {
                    selected_animal = i;
                    break;
                } else {
                    selected--;
                }
            }
        }
    }

    return selected_animal;
}

/**
 * Gets the index of an animal to say goodbye to (for removal).
 * Uses a multi-tiered approach: remoteness, personality balance, friendship, then random.
 *
 * @param ignored_idx Index of animal to ignore in selection
 * @return Index of animal selected for goodbye/removal
 */
extern int mNpc_GetGoodbyAnimalIdx(int ignored_idx) {
    Animal_c* animal = Save_Get(animals);
    int sick_animal = mNpc_SearchAnimalPersonalID(&Save_Get(sick_info).id);
    int selected_animal;

    // First, try finding the animal who the current player hasn't spoken to in the longest time.
    // Animals who the player has never spoken to are excluded from this check.
    selected_animal = mNpc_GetRemotenessAnimalIdx(animal, ignored_idx, sick_animal);

    if (selected_animal == -1) {
        // If no animal was selected, get a random animal from the
        // largest personality group in the town. If multiple personality
        // groups are tied for the max, this step returns -1.
        selected_animal = mNpc_GetMaxLooksAnimal(animal, ignored_idx, sick_animal);
    }

    if (selected_animal == -1) {
        // If no animal was selected, get a random animal with the lowest combined friendship
        // from all of their player memory slots. This can include memories of players from
        // other towns as well.
        selected_animal = mNpc_GetTotalFriendshipMinAnimal(animal, ignored_idx, sick_animal);
    }

    if (selected_animal == -1) {
        // Finally, if no villager was chosen at this point, pick a random villager.
        selected_animal = mNpc_DecideRemoveAnimalNo(animal, ignored_idx, sick_animal);
    }

    return selected_animal;
}

typedef struct animal_goodbye_mail_s {
    AnmPersonalID_c id;
    u8 deliver_to_bitfield;
} Anm_GoodbyMail_c;

static Anm_GoodbyMail_c l_mnpc_goodby_mail;

static void mNpc_ClearGoodbyMail(Anm_GoodbyMail_c* goodby_mail) {
    mNpc_ClearAnimalPersonalID(&goodby_mail->id);
    goodby_mail->deliver_to_bitfield = 0;
}

extern void mNpc_FirstClearGoodbyMail() {
    mNpc_ClearGoodbyMail(&l_mnpc_goodby_mail);
}

static void mNpc_SetGoodbyAnimalMail_common(Anm_GoodbyMail_c* goodby_mail, AnmPersonalID_c* anm_id) {
    Private_c* priv = Save_Get(private_data);
    int i;

    if (anm_id != NULL && mNpc_CheckFreeAnimalPersonalID(anm_id) == FALSE) {
        mNpc_ClearGoodbyMail(goodby_mail);
        mNpc_CopyAnimalPersonalID(&goodby_mail->id, anm_id);

        for (i = 0; i < PLAYER_NUM; i++) {
            if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE) {
                goodby_mail->deliver_to_bitfield |= (1 << i);
            }

            priv++;
        }
    }
}

extern void mNpc_SetGoodbyAnimalMail(AnmPersonalID_c* anm_id) {
    mNpc_SetGoodbyAnimalMail_common(&l_mnpc_goodby_mail, anm_id);
}

static int mNpc_SetGoodbyMailData(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    static u8 animal_name[ANIMAL_NAME_LEN];

    u8 looks = anm_id->looks;
    int mail_no;
    int res = FALSE;

    if (looks < mNpc_LOOKS_NUM) {
        mail_no = 0x20E + looks * 3;
        mail_no += mQst_GetRandom(3);
        mNpc_GetNpcWorldNameAnm(animal_name, anm_id);
        mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR1, animal_name, ANIMAL_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR3, Save_Get(land_info).name, LAND_NAME_SIZE);
        mNpc_LoadMailDataCommon2(mail, pid, anm_id, EMPTY_NO, mNpc_GetPaperType(), mail_no);
        res = TRUE;
    }

    return res;
}

static int mNpc_SendGoodbyAnimalMailOne(Mail_c* mail, PersonalID_c* pid, int player_no, Anm_GoodbyMail_c* goodby_mail) {
    int free_space;
    mHm_hs_c* home;
    int res = FALSE;

    home = Save_GetPointer(homes[mHS_get_arrange_idx(player_no)]);

    if (mPr_NullCheckPersonalID(pid) == FALSE && mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
        free_space = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);

        if (free_space != -1) {
            if (mNpc_SetGoodbyMailData(mail, pid, &goodby_mail->id) == TRUE) {
                mMl_copy_mail(home->mailbox + free_space, mail);
                res = TRUE;
            }
        } else if (mPO_get_keep_mail_sum() < mPO_MAIL_STORAGE_SIZE &&
                   mNpc_SetGoodbyMailData(mail, pid, &goodby_mail->id) == TRUE) {
            res = mPO_receipt_proc(mail, mPO_SENDTYPE_MAIL);
        }
    }

    return res;
}

static void mNpc_SendGoodbyAnimalMail(Anm_GoodbyMail_c* goodby_mail) {
    Private_c* priv = Save_Get(private_data);
    int i;

    if (mNpc_CheckFreeAnimalPersonalID(&goodby_mail->id) == FALSE) {
        for (i = 0; i < PLAYER_NUM; i++) {
            if (((goodby_mail->deliver_to_bitfield >> i) & 1) == 1) {
                mMl_clear_mail(&l_npc_mail);

                if (mNpc_SendGoodbyAnimalMailOne(&l_npc_mail, &priv->player_ID, i, goodby_mail) == TRUE) {
                    goodby_mail->deliver_to_bitfield &= ~(1 << i); // player received goodbye letter
                }
            }

            priv++;
        }

        if (goodby_mail->deliver_to_bitfield == 0) {
            mNpc_ClearGoodbyMail(goodby_mail); // all players received goodbye letter
        }
    }
}

extern void mNpc_SendRegisteredGoodbyMail() {
    mNpc_SendGoodbyAnimalMail(&l_mnpc_goodby_mail);
}

/**
 * Handles animal removal and transfer between towns.
 * Manages the complex logic of removing animals, sending goodbye mail, and setting up new arrivals.
 *
 * @param transferring_animal Animal data for the animal being transferred
 * @param moving_out TRUE if an animal is moving out, FALSE if one is moving in
 */
extern void mNpc_GetRemoveAnimal(Animal_c* transferring_animal, u8* compress_data, int moving_out) {
    Private_c* priv = Now_Private;
    AnmPersonalID_c* last_remove_animal_id = Save_GetPointer(last_removed_animal_id);
    u8* now_npc_max = Save_GetPointer(now_npc_max);
    int new_animal;
    Animal_c* animal2;
    Animal_c* animal = Save_Get(animals);
    int free_animal_idx;
    u8* remove_animal_idx = Save_GetPointer(remove_animal_idx);
    int compress_idx;
    int i;

    new_animal = TRUE;

    if (mLd_PlayerManKindCheck() == NATIVE) {
        if (moving_out == TRUE && *remove_animal_idx < ANIMAL_NUM_MAX && transferring_animal != NULL) {
            animal2 = Save_GetPointer(animals[*remove_animal_idx]);
            animal2->removing = FALSE;
            mNpc_CopyAnimalInfo(transferring_animal, animal2);
            mNpc_DestroyHouse(&animal2->home_info);

            if (IS_NPC_ADD_NPC(animal2->id.npc_id)) {
                mem_copy(compress_data,
                         Save_Get(add_npc).save.add_npc_compress_info_table[animal2->id.npc_id - NPC_ADD_START],
                         mAN_COMPRESS_INFO_TABLE_MAX_SIZE);
                mAN_clear_compress_info_table(animal2->id.npc_id, &Save_Get(add_npc).save.regist_add_npc,
                                              Common_GetPointer(add_npc_info));
            }

            mNpc_ClearAnimalInfo(animal2);
            mNpc_ClearRelationPointOthers(*remove_animal_idx);
            *remove_animal_idx = 0xFF;
            mNpc_SubNowNpcMax(now_npc_max);
        }
    } else {
        if (transferring_animal != NULL && mNpc_CheckFreeAnimalInfo(transferring_animal) == FALSE &&
            transferring_animal->removing == FALSE) {
            mActor_name_t* summercamper_id;

            if (IS_NPC_ADD_NPC(transferring_animal->id.npc_id)) {
                for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                    if (IS_NPC_ADD_NPC(animal->id.npc_id) &&
                        transferring_animal->id.add_npc_id == animal->id.add_npc_id) {
                        new_animal = FALSE;
                        break;
                    }

                    animal++;
                }

                if (IS_NPC_ADD_NPC(last_remove_animal_id->npc_id) &&
                    transferring_animal->id.add_npc_id == last_remove_animal_id->add_npc_id) {
                    new_animal = FALSE;
                }
            } else {
                /* The incoming animal cannot be present in the town already */
                for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                    if (transferring_animal->id.npc_id == animal->id.npc_id) {
                        new_animal = FALSE;
                        break;
                    }

                    animal++;
                }

                /* The last animal who left the town cannot be the next animal to transfer in */
                if (transferring_animal->id.npc_id == last_remove_animal_id->npc_id) {
                    new_animal = FALSE;
                }
            }

            /* Ensure that the animal moving in is not the same one that's currently visiting as a summer camper */
            summercamper_id = (mActor_name_t*)mEv_get_save_area(mEv_EVENT_SUMMER_CAMPER, 0);
            if (summercamper_id != NULL) {
                if (ITEM_NAME_GET_TYPE(summercamper_id[0]) == NAME_TYPE_NPC) {
                    mActor_name_t id = transferring_animal->id.npc_id;

                    if (id == summercamper_id[0]) {
                        new_animal = FALSE;
                    }
                }
            }

            if (mCD_castingoff_mura_chk() == TRUE) {
                new_animal = FALSE;
            }
        } else {
            /* The new animal was unintialized or was scheduled to move out */
            new_animal = FALSE;
        }

        if (new_animal == TRUE) {
            animal = Save_Get(animals);

            /* Try to find an unused slot in the animal data */
            free_animal_idx = mNpc_GetFreeAnimalInfo(Save_Get(animals), ANIMAL_NUM_MAX);

            if (free_animal_idx == -1) {
                /* No slot, so we're going to replace a villager from in town */
                free_animal_idx = mNpc_GetGoodbyAnimalIdx(-1);

                if (free_animal_idx == -1) {
                    /* Final fallback, delete the first villager */
                    free_animal_idx = 0;
                }

                animal += free_animal_idx;
                mNpc_DestroyHouse(&animal->home_info);
                mNpc_SetGoodbyAnimalMail_common(&l_mnpc_goodby_mail, &animal->id);
                mNpc_SendRegisteredGoodbyMail();

                if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
                    mAN_clear_compress_info_table(animal->id.npc_id, &Save_Get(add_npc).save.regist_add_npc,
                                                  Common_GetPointer(add_npc_info));
                }

                mNpc_SubNowNpcMax(now_npc_max);
            } else {
                animal += free_animal_idx;
            }

            if (IS_NPC_ADD_NPC(transferring_animal->id.npc_id)) {
                AddNpc_c* add_npc = Save_GetPointer(add_npc);

                compress_idx = mAN_get_free_compress_data_idx(&add_npc->save.regist_add_npc);
                if (compress_idx != -1) {
                    transferring_animal->id.npc_id = NPC_ADD_START + compress_idx;
                    mAN_set_cd(&add_npc->save, compress_data, compress_idx);
                    mAN_regist_add_npc_info();
                }
            } else {
                compress_idx = 0;
            }

            if (compress_idx != -1) {
                mNpc_ClearAnimalInfo(animal);
                mNpc_CopyAnimalInfo(animal, transferring_animal);
                animal->home_info.bx = 0xFF;
                animal->home_info.bz = 0xFF;
                animal->home_info.ux = 0xFF;
                animal->home_info.uz = 0xFF;
                mLd_CopyLandName(animal->anmuni.previous_land_name, Now_Private->player_ID.land_name);
                animal->anmuni.previous_land_id = Now_Private->player_ID.land_id;
                mQst_ClearContest(&animal->contest_quest);
                mMpswd_ClearHPMail(animal->hp_mail, ANIMAL_HP_MAIL_NUM);
                transferring_animal->removing = TRUE;
                mNpc_CopyAnimalPersonalID(&priv->animal_memory.npc_id, &animal->id);
                mLd_CopyLandName(priv->animal_memory.land_name, mLd_GetLandName());
                mNpc_SetHaveAppeared(animal->id.npc_id);
                mNpc_ClearRelationPointOthers(free_animal_idx);
                mNpc_RenewRemoveHistory();
                mNpc_AddNowNpcMax(now_npc_max);
            }
        }
    }
}

extern void mNpc_ClearJustRemoveAnimal(void) {
    AddNpc_c* add_npc;
    u8* now_npc_max;
    Animal_c* animal;
    Anmhome_c* home;
    int i;

    animal = Save_Get(animals);
    add_npc = Save_GetPointer(add_npc);
    now_npc_max = Save_GetPointer(now_npc_max);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            home = &animal->home_info;
            if (home->bx == 0xFF && home->bz == 0xFF) {
                if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
                    mAN_clear_compress_info_table(animal->id.npc_id, &add_npc->save.regist_add_npc,
                                                  Common_GetPointer(add_npc_info));
                }

                mNpc_ClearAnimalInfo(animal);
                mNpc_SubNowNpcMax(now_npc_max);
            }
        }

        animal++;
    }
}

static int mNpc_CheckBuildHouse(int bx, int bz, u8 ut_x, u8 ut_z) {
    int res = FALSE;

    if (bx >= 0 && bx < FG_BLOCK_X_NUM && bz >= 0 && bz < FG_BLOCK_Z_NUM && ut_x < UT_X_NUM && ut_z < UT_Z_NUM) {
        mActor_name_t item = Save_Get(fg[bz][bx]).items[ut_z][ut_x];

        if (mNT_IS_RESERVE(item)) {
            res = TRUE;
        }
    }

    return res;
}

extern void mNpc_SetReturnAnimal(InAnimal_c* in_animal) {
    Anmhome_c* home_info;
    Animal_c* animals = Save_Get(animals);
    Animal_c* found_animal = NULL;
    u8* now_npc_max = Save_GetPointer(now_npc_max);
    Anmret_c* return_animal_p = Save_GetPointer(return_animal);
    int found_animal_idx;
    int ignored_idx = -1;
    int add_npc_idx = 0;

    if (mLd_PlayerManKindCheck() == FALSE && mNpc_CheckFreeAnimalInfo(&in_animal->animal) == FALSE) {
        if (in_animal->animal.removing == FALSE) {
            found_animal_idx = mNpc_SearchAnimalPersonalID_com(&in_animal->animal.id, animals, ANIMAL_NUM_MAX);

            if (found_animal_idx != -1) {
                found_animal = &animals[found_animal_idx];
                mNpc_DestroyHouse(&found_animal->home_info);
                (*now_npc_max)--;

                if (Save_Get(remove_animal_idx) == found_animal_idx) {
                    Save_Set(remove_animal_idx, 0xFF);
                }

                if (IS_NPC_ADD_NPC(found_animal->id.npc_id)) {
                    mAN_clear_compress_info_table(found_animal->id.npc_id, &Save_Get(add_npc).save.regist_add_npc,
                                                  Common_GetPointer(add_npc_info));
                }
            } else if (mNpc_GetAnimalNum() >= ANIMAL_NUM_MAX) {
                if (Save_Get(scene_no) == SCENE_PLAYERSELECT_2) {
                    /* Don't remove the animal we just saw on the player select screen */
                    ignored_idx = Common_Get(player_select_animal_no);
                }

                found_animal_idx = mNpc_GetGoodbyAnimalIdx(ignored_idx);

                if (found_animal_idx == -1) {
                    found_animal_idx = 0; // fallback
                }

                found_animal = &animals[found_animal_idx];
                mNpc_SetGoodbyAnimalMail_common(&l_mnpc_goodby_mail, &found_animal->id);
                mNpc_DestroyHouse(&found_animal->home_info);

                if (IS_NPC_ADD_NPC(found_animal->id.npc_id)) {
                    mAN_clear_compress_info_table(found_animal->id.npc_id, &Save_Get(add_npc).save.regist_add_npc,
                                                  Common_GetPointer(add_npc_info));
                }

                (*now_npc_max)--;

                if (Save_Get(remove_animal_idx) == found_animal_idx) {
                    Save_Set(remove_animal_idx, 0xFF);
                }
            } else {
                found_animal_idx = mNpc_GetFreeAnimalInfo(animals, ANIMAL_NUM_MAX);

                if (found_animal_idx != -1) {
                    found_animal = &animals[found_animal_idx];
                }
            }

            if (found_animal != NULL) {
                mNpc_ClearAnimalInfo(found_animal);

                if (IS_NPC_ADD_NPC(in_animal->animal.id.npc_id)) {
                    add_npc_idx = mAN_get_free_compress_data_idx(&Save_Get(add_npc).save.regist_add_npc);
                    if (add_npc_idx != -1) {
                        in_animal->animal.id.npc_id = NPC_ADD_START + add_npc_idx;
                        mAN_set_cd(&Save_Get(add_npc).save, in_animal->compress_data, add_npc_idx);
                        mAN_regist_add_npc_info();
                    }
                }

                if (add_npc_idx != -1) {
                    mNpc_CopyAnimalInfo(found_animal, &in_animal->animal);
                    mNpc_ClearRelationPointOthers(found_animal_idx);
                    home_info = &found_animal->home_info;

                    if (mNpc_CheckBuildHouse(home_info->bx - 1, home_info->bz - 1, home_info->ux, home_info->uz - 1) ==
                        TRUE) {
                        mNpc_BuildHouseBeforeFieldct(found_animal->id.npc_id, home_info->bx - 1, home_info->bz - 1,
                                                     home_info->ux, home_info->uz - 1);
                    } else {
                        home_info->bx = 0xFF;
                        home_info->bz = 0xFF;
                        home_info->ux = 0xFF;
                        home_info->uz = 0xFF;
                    }

                    (*now_npc_max)++;

                    if ((*now_npc_max) > ANIMAL_NUM_MAX) {
                        (*now_npc_max) = ANIMAL_NUM_MAX;
                    }
                }
            }
        } else {
            if (ITEM_NAME_GET_TYPE(in_animal->animal.id.npc_id) == NAME_TYPE_NPC &&
                !IS_NPC_ADD_NPC(in_animal->animal.id.npc_id)) {
                return_animal_p->npc_id = in_animal->animal.id.npc_id;
                return_animal_p->talk_bit = 0b000;
                return_animal_p->exist = FALSE;
                lbRTC_TimeCopy(&return_animal_p->renew_time, Common_GetPointer(time.rtc_time));
            }
            mNpc_CopyAnimalPersonalID(Save_GetPointer(last_removed_animal_id), &in_animal->animal.id);
            if (Now_Private != NULL) {
                mLd_CopyLandName(Save_Get(last_removed_animal_mem_town_name), Now_Private->animal_memory.land_name);
            }
        }

        mNpc_ClearAnimalInfo(&in_animal->animal);
    }
}

extern void mNpc_AddActor_inBlock(mFM_move_actor_c* move_actor_list, u8 bx, u8 bz) {
    mNpc_AddNpc_inBlock(move_actor_list, bx, bz);
}

extern void mNpc_LoadNpcNameString(u8* dst, int name_id) {
    static u8 dma_area[64] ATTRIBUTE_ALIGN(32);
    u32 addr;
    u32 ofs;
    u32 base_addr;

    if (name_id >= NPC_ROM_NUM) {
        mAN_load_add_npc_name_string(dst, name_id);
        return;
    }

    mem_clear(dma_area, sizeof(dma_area), CHAR_SPACE);
    addr = JW_GetAramAddress(RESOURCE_NPC_NAME_STR_TABLE);

    if (name_id < 0xFFF && dst != NULL && addr != 0) {
        ofs = (name_id)*ANIMAL_NAME_LEN; /* offset into dma table */
        base_addr = ALIGN_PREV(ofs, 32); /* align it to the nearest 32 bytes for DMA */

        _JW_GetResourceAram(base_addr + addr, dma_area, sizeof(dma_area)); // DMA transfer from ARAM
        bcopy(dma_area + (ofs - base_addr), dst, ANIMAL_NAME_LEN);         // perform final copy
    }
}

extern void mNpc_SetNpcNameID(Animal_c* animal, int num) {
    int i;

    for (i = 0; i < num; i++) {
        if (animal != NULL && ITEM_NAME_GET_TYPE(animal->id.npc_id) == NAME_TYPE_NPC) {
            mNpc_LoadNpcNameString(animal->id.name, animal->id.npc_id & 0xFFF);
        }

        animal++;
    }
}

static u8* mNpc_GetNpcWorldNamePTableNo(mActor_name_t npc_id) {
    static u8 npc_name[ANIMAL_NAME_LEN];
    u8* world_name_p = NULL;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        if (IS_NPC_ADD_NPC(npc_id)) {
            int idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_id, ANIMAL_NUM_MAX);

            if (idx != -1) {
                world_name_p = Save_Get(animals)[idx].id.name;
            }
        } else if ((u8)(npc_id & 0xFF) < 0xFF) {
            mNpc_LoadNpcNameString(npc_name, npc_id & 0xFF);
            world_name_p = npc_name;
        }
    }

    return world_name_p;
}

extern void mNpc_GetNpcWorldNameTableNo(u8* dst, mActor_name_t npc_id) {
    u8* world_name_p = mNpc_GetNpcWorldNamePTableNo(npc_id);

    if (world_name_p == NULL) {
        world_name_p = l_no_name_npc_name;
    }

    mPr_CopyPlayerName(dst, world_name_p);
}

typedef struct npc_name_cache_s {
    mActor_name_t npc_id;
    u8 name[ANIMAL_NAME_LEN];
    u8 npc_type; // 0? = Special NPC, 1 = Regular NPC
} mNpc_NameCache_c;

static mNpc_NameCache_c l_npc_name_cache;

extern void mNpc_ClearCacheName() {
    mPr_ClearPlayerName(l_npc_name_cache.name);
    l_npc_name_cache.npc_id = RSV_NO;
    l_npc_name_cache.npc_type = 0;
}

static int mNpc_GetCacheName(u8* dst, mActor_name_t npc_id, u8 npc_type) {
    int res = FALSE;

    if (npc_id == l_npc_name_cache.npc_id && dst != NULL && npc_type == l_npc_name_cache.npc_type) {
        mPr_CopyPlayerName(dst, l_npc_name_cache.name);
        res = TRUE;
    }

    return res;
}

static void mNpc_SetCacheName(u8* name, mActor_name_t npc_id, u8 npc_type) {
    mNpc_NameCache_c* name_cache = &l_npc_name_cache;

    if (name != NULL) {
        mPr_CopyPlayerName(name_cache->name, name);
        name_cache->npc_id = npc_id;
        name_cache->npc_type = npc_type;
    }
}

extern void mNpc_GetNpcWorldNameAnm(u8* dst, AnmPersonalID_c* anm_id) {
    u8 animal_name[ANIMAL_NAME_LEN];
    u8* name = l_no_name_npc_name;

    if (anm_id != NULL) {
        if (mNpc_CheckFreeAnimalPersonalID(anm_id) == FALSE) {
            name = anm_id->name;
        }
    }

    mPr_CopyPlayerName(dst, name);
}

static u8* mNpc_GetActorWorldNameP(mActor_name_t npc_id) {
    static u8 load_name[ANIMAL_NAME_LEN];

    mNpc_Sp_Npc_Name_c* sp_npc_name = l_sp_actor_name;
    u8* name_p = NULL;
    int i;

    if (npc_id != RSV_NO && mNpc_GetCacheName(load_name, npc_id, mNpc_NAME_TYPE_NPC) != FALSE) {
        name_p = load_name;
    } else if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        mNpc_GetNpcWorldNameTableNo(load_name, npc_id);
        name_p = load_name;
        mNpc_SetCacheName(load_name, npc_id, mNpc_NAME_TYPE_NPC);
    } else {
        for (i = 0; i < ARRAY_COUNT(l_sp_actor_name); i++) {
            if (npc_id == sp_npc_name->sp_npc_id) {
                mString_Load_StringFromRom(load_name, ANIMAL_NAME_LEN, sp_npc_name->name_str_no);
                name_p = load_name;
                mNpc_SetCacheName(load_name, npc_id, mNpc_NAME_TYPE_NPC);

                break;
            }

            sp_npc_name++;
        }
    }

    return name_p;
}

extern void mNpc_GetActorWorldName(u8* dst, mActor_name_t npc_id) {
    u8* name_p = mNpc_GetActorWorldNameP(npc_id);

    if (name_p == NULL) {
        name_p = l_no_name_npc_name;
    }

    mPr_CopyPlayerName(dst, name_p);
}

extern u8* mNpc_GetNpcWorldNameP(mActor_name_t npc_id) {
    u8* name_p = mNpc_GetNpcWorldNamePTableNo(npc_id);

    if (name_p == NULL) {
        name_p = mNpc_GetActorWorldNameP(npc_id);

        if (name_p == NULL) {
            name_p = l_no_name_npc_name;
        }
    }

    return name_p;
}

extern void mNpc_GetNpcWorldName(u8* dst, ACTOR* actor) {
    u8 npc_name[ANIMAL_NAME_LEN];
    u8* name_p = l_no_name_npc_name;

    if (dst != NULL && actor != NULL) {
        if (actor->part == ACTOR_PART_NPC) {
            NPC_ACTOR* npc = (NPC_ACTOR*)actor;
            Animal_c* animal = npc->npc_info.animal_orig;

            if (animal != NULL) {
                mNpc_GetNpcWorldNameAnm(npc_name, &animal->id);
            } else {
                mActor_name_t npc_id;
                mNpc_EventNpc_c* event_npc;
                mNpc_MaskNpc_c* mask_npc;

                event_npc = mNpc_GetSameEventNpc(actor->npc_id);

                if (event_npc != NULL) {
                    npc_id = event_npc->npc_id;
                } else {
                    mask_npc = mNpc_GetSameMaskNpc(actor->npc_id);

                    if (mask_npc != NULL) {
                        npc_id = mask_npc->npc_id;
                    } else {
                        npc_id = actor->npc_id;
                    }
                }

                if (npc_id == SP_NPC_EV_GHOST) {
                    u8 arg = actor->actor_specific;

                    if (mNpc_GetCacheName(npc_name, npc_id, arg) == FALSE) {
                        if (arg != 1) {
                            /* Load the ?????? name */
                            mString_Load_StringFromRom(npc_name, ANIMAL_NAME_LEN, 0x6D7);
                            mNpc_SetCacheName(npc_name, npc_id, arg);
                        } else {
                            mNpc_GetActorWorldName(npc_name, npc_id);
                        }
                    }
                } else {
                    mNpc_GetActorWorldName(npc_name, npc_id);
                }
            }
        } else {
            mNpc_GetActorWorldName(npc_name, actor->npc_id);
        }

        name_p = npc_name;
    }

    mPr_CopyPlayerName(dst, name_p);
}

extern void mNpc_GetRandomAnimalName(u8* dst) {
    Animal_c* animal = Save_Get(animals);
    Animal_c* animal_p = animal;
    u16 candidate_bitfield = 0;
    int candidate_num = 0;
    int i;

    if (dst != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal_p) == FALSE) {
                candidate_bitfield |= (1 << i);
                candidate_num++;
            }

            animal_p++;
        }

        if (candidate_num > 0) {
            int selected = RANDOM(candidate_num);

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (((candidate_bitfield >> i) & 1) == 1) {
                    if (selected == 0) {
                        mNpc_GetNpcWorldNameAnm(dst, &animal->id);
                        break;
                    } else {
                        selected--;
                    }
                }

                animal++;
            }
        }
    }
}

extern void mNpc_GetAnimalPlateName(u8* dst, xyz_t wpos) {
    Animal_c* animal = Save_Get(animals);
    int bx;
    int bz;
    int ut_x;
    int ut_z;

    if (mFI_Wpos2BkandUtNuminBlock(&bx, &bz, &ut_x, &ut_z, wpos) == TRUE) {
        if (mFI_CheckBlockKind_OR(bx, bz, mRF_BLOCKKIND_OCEAN) == TRUE) {
            if (Common_Get(cur_island_house_p) != NULL) {
                mNpc_GetNpcWorldNameAnm(dst, &Common_Get(cur_island_house_p)->island.animal.id);
            }
        } else {
            int i;

            ut_x++;

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {

                if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                    Anmhome_c* home = &animal->home_info;

                    if (home->bx == bx && home->bz == bz && home->ux == ut_x && home->uz == ut_z) {
                        mNpc_GetNpcWorldNameAnm(dst, &animal->id);
                        break;
                    }
                }

                animal++;
            }
        }
    }
}

extern int mNpc_GetNpcLooks(ACTOR* actor) {
    int looks = mNpc_LOOKS_BOY;

    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
        NPC_ACTOR* npc = (NPC_ACTOR*)actor;

        if (npc->npc_info.animal_orig != NULL) {
            looks = npc->npc_info.animal_orig->id.looks;
        }
    }

    return looks;
}

static int mNpc_GetActorSex(mActor_name_t npc_id) {
    mNpc_Sp_Npc_Name_c* sp_name_info = l_sp_actor_name;
    int sex = mPr_SEX_MALE;
    int i;

    for (i = 0; i < ARRAY_COUNT(l_sp_actor_name); i++) {
        if (npc_id == sp_name_info->sp_npc_id) {
            sex = sp_name_info->sex;
            break;
        }

        sp_name_info++;
    }

    return sex;
}

extern int mNpc_GetLooks2Sex(int looks) {
    int sex = mPr_SEX_OTHER;

    if (looks == mNpc_LOOKS_GIRL || looks == mNpc_LOOKS_KO_GIRL || looks == mNpc_LOOKS_NANIWA_LADY) {
        sex = mPr_SEX_FEMALE;
    } else if (looks == mNpc_LOOKS_BOY || looks == mNpc_LOOKS_SPORT_MAN || looks == mNpc_LOOKS_GRIM_MAN) {
        sex = mPr_SEX_MALE;
    }

    return sex;
}

extern int mNpc_GetAnimalSex(Animal_c* animal) {
    int sex = mPr_SEX_OTHER;

    if (animal != NULL) {
        sex = mNpc_GetLooks2Sex(animal->id.looks);
    }

    return sex;
}

extern int mNpc_GetNpcSex(ACTOR* actor) {
    if (actor != NULL && actor->part == ACTOR_PART_NPC) {
        NPC_ACTOR* npc = (NPC_ACTOR*)actor;

        return mNpc_GetAnimalSex(npc->npc_info.animal_orig);
    }

    return mNpc_GetActorSex(actor->npc_id);
}

static int mNpc_GetNpcSoundSpecNotAnimal(mActor_name_t npc_id) {
    mNpc_Sp_Npc_Name_c* sp_name_info = l_sp_actor_name;
    int sound_spec = 2;
    int i;

    for (i = 0; i < ARRAY_COUNT(l_sp_actor_name); i++) {
        if (npc_id == sp_name_info->sp_npc_id) {
            sound_spec = sp_name_info->sound_id;
            break;
        }

        sp_name_info++;
    }

    return sound_spec;
}

extern int mNpc_GetNpcSoundSpec(ACTOR* actor) {
    static int spec_table[mNpc_LOOKS_NUM] = { 4, 4, 2, 2, 3, 4 };

    int sound_spec = 2;

    if (actor != NULL) {
        if (actor->part == ACTOR_PART_NPC) {
            NPC_ACTOR* npc = (NPC_ACTOR*)actor;

            if (npc->npc_info.animal_orig != NULL) {
                int looks = npc->npc_info.animal_orig->id.looks;

                if (looks >= mNpc_LOOKS_NUM) {
                    looks = mNpc_LOOKS_BOY;
                }

                sound_spec = spec_table[looks];
            } else {
                sound_spec = mNpc_GetNpcSoundSpecNotAnimal(actor->npc_id);
            }
        } else {
            sound_spec = mNpc_GetNpcSoundSpecNotAnimal(actor->npc_id);
        }
    }

    return sound_spec;
}

static void mNpc_InitRemoveHistory() {
    lbRTC_ymd_c* ymd = Save_GetPointer(force_remove_date);

    ymd->year = 0xFFFF;
    ymd->month = 0xFF;
    ymd->day = 0xFF;
}

extern void mNpc_InitNpcAllInfo(int malloc_flag) {
    Animal_c* animals = Save_Get(animals);

    Save_Set(now_npc_max, mNpc_LOOKS_NUM);
    Save_Set(remove_animal_idx, 0xFF);
    mNpc_InitRemoveHistory();
    mNpc_ClearAnimalPersonalID(Save_GetPointer(last_removed_animal_id));
    mLd_ClearLandName(Save_Get(last_removed_animal_mem_town_name));
    mNpc_ClearAnyAnimalInfo(animals, ANIMAL_NUM_MAX);
    mNpc_DecideLivingNpcMax(animals, mNpc_LOOKS_NUM, malloc_flag);
    mNpc_SetNpcNameID(animals, ANIMAL_NUM_MAX);
}

static int mNpc_CheckGrowFieldRank() {
    static int npc_grow_prob[mFAs_FIELDRANK_NUM] = { 40, 50, 60, 70, 80, 90, 100 };

    int rank = mFAs_GetFieldRank();
    int res = FALSE;

    if (rank >= 0 && rank < mFAs_FIELDRANK_NUM) {
        if (RANDOM(100) < npc_grow_prob[rank]) {
            res = TRUE;
        }
    }

    return res;
}

static int mNpc_CheckGrow() {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    lbRTC_time_c* last_grow_time = Save_GetPointer(last_grow_time);
    int res = FALSE;

    if (mNpc_GetAnimalNum() < ANIMAL_NUM_MAX) {
        if (lbRTC_IsEqualTime(&mTM_rtcTime_clear_code, last_grow_time, lbRTC_CHECK_ALL) == TRUE) {
            lbRTC_TimeCopy(last_grow_time, rtc_time); // first initialization
        } else if (mNpc_CheckGrowFieldRank() == TRUE) {
            u32 interval;

            if (lbRTC_IsOverTime(last_grow_time, rtc_time) == lbRTC_OVER) {
                interval = lbRTC_IntervalTime(rtc_time, last_grow_time);
            } else {
                interval = lbRTC_IntervalTime(last_grow_time, rtc_time);
            }

            if (interval >= (lbRTC_HOURS_PER_DAY * lbRTC_MINUTES_PER_HOUR) && /* Only one new villager per day */
                mLd_PlayerManKindCheck() == FALSE && /* Player must be from the town being loaded */
                mNpc_CheckFriendAllAnimal(&Now_Private->player_ID) ==
                    TRUE /* The player loading must have talked to all current villagers */
            ) {
                res = TRUE;
            }
        }
    }

    return res;
}

static u8 mNpc_GetMinLooks(u8* min_looks_bitfield, int* min_looks_num) {
    int min_looks_animals;
    u8 min_looks;
    u8 i;

    min_looks_bitfield[0] = 0;
    min_looks_num[0] = 0;
    min_looks_animals = ANIMAL_NUM_MAX;
    min_looks = mNpc_LOOKS_UNSET;

    for (i = 0; i < mNpc_LOOKS_NUM; i++) {
        int not_appear_num = mNpc_GetLooks2NotHaveAppearedNum(i);

        if (not_appear_num > 0) {
            int same_looks_num = mNpc_GetSameLooksNum(i);

            if (min_looks_animals > same_looks_num) {
                min_looks_animals = same_looks_num;
                min_looks = i;
                min_looks_bitfield[0] = 0;
                min_looks_bitfield[0] |= (1 << i);
                min_looks_num[0] = 1;
            } else if (min_looks_animals == same_looks_num) {
                min_looks_bitfield[0] |= (1 << i);
                min_looks_num[0]++;
            }
        }
    }

    if (min_looks_bitfield[0] == 0 && min_looks_num[0] == 0) {
        /* All animals have appeared before, so reset the list */
        mNpc_ResetHaveAppeared_common(Save_Get(npc_used_tbl), Save_Get(animals));

        for (i = 0; i < mNpc_LOOKS_NUM; i++) {
            min_looks_bitfield[0] |= (1 << i);
            min_looks_num[0]++;
        }
    }

    if (min_looks_num[0] > 1) {
        min_looks = mNpc_LOOKS_UNSET;
    }

    return min_looks;
}

static int mNpc_GrowLooksNpcIdx(u8 looks) {
    static u8 candidate_table[ALIGN_NEXT(NPC_ROM_NUM, 8) / 8];

    u8* looks_table = npc_looks_table;
    s8* grow_list = npc_grow_list;
    int npc_idx;
    int candidates;
    int res;
    int i;
    int j;
    int selected;

    npc_idx = 0;
    candidates = 0;
    res = -1;

    if (looks < mNpc_LOOKS_UNSET) {
        bzero(candidate_table, sizeof(candidate_table));

        for (i = 0; i < ARRAY_COUNT(candidate_table); i++) {
            for (j = 0; j < 8; j++) {
                if (looks == *looks_table) {
                    int grow_perm = mNpc_GetDefGrowPermission(npc_idx, grow_list, NPC_ROM_NUM);

                    if ((mNpc_SearchAnimalinfo(Save_Get(animals), npc_idx | NPC_START, ANIMAL_NUM_MAX) == -1) &&
                        (mNpc_GetHaveAppeared_idx(npc_idx) == FALSE) &&
                        (grow_perm == mNpc_GROW_STARTER || grow_perm == mNpc_GROW_MOVE_IN)) {
                        candidates++;
                        candidate_table[i] |= 1 << j;
                    }
                }

                npc_idx++;
                looks_table++;

                if (npc_idx >= NPC_ROM_NUM) {
                    break;
                }
            }

            if (npc_idx >= NPC_ROM_NUM) {
                break;
            }
        }
    }

    if (candidates > 0) {
        looks_table = npc_looks_table;
        selected = RANDOM(candidates);
        npc_idx = 0;

        for (i = 0; i < ARRAY_COUNT(candidate_table); i++) {
            if (npc_idx >= NPC_ROM_NUM) {
                break;
            }

            for (j = 0; j < 8; looks_table++, npc_idx++, j++) {
                if (npc_idx >= NPC_ROM_NUM) {
                    break;
                }

                if (((candidate_table[i] >> j) & 1) == 1) {
                    if (selected <= 0) {
                        res = npc_idx;
                        break;
                    } else {
                        selected--;
                    }
                }
            }

            if (res != -1) {
                break;
            }
        }
    }

    return res;
}

static void mNpc_SetAnimalInfoNpcIdx(Animal_c* animal, int idx) {
    if (idx >= 0 && idx < NPC_ROM_NUM) {
        mNpc_SetDefAnimalInfo(animal, NPC_START | idx, npc_looks_table[idx], &npc_def_list[idx]);
    }
}

static int mNpc_SetGrowNpc(u8 looks) {
    Animal_c* animal = Save_Get(animals);
    int idx = mNpc_UseFreeAnimalInfo(animal, ANIMAL_NUM_MAX);
    int npc_idx;

    if (idx != -1) {
        animal += idx;
        npc_idx = mNpc_GrowLooksNpcIdx(looks);

        if (npc_idx != -1) {
            mNpc_SetAnimalInfoNpcIdx(animal, npc_idx);
            mNpc_SetHaveAppeared(animal->id.npc_id);
            animal->moved_in = mNpc_MOVE_IN_TYPE_GROW;
        } else {
            idx = -1;
        }
    }

    return idx;
}

extern void mNpc_Grow() {
    int selected;
    int grow_idx;

    if (mNpc_CheckGrow() == TRUE) {
        lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
        lbRTC_time_c* last_grow_time = Save_GetPointer(last_grow_time);
        u8 min_looks_bitfield;
        int min_looks_num;
        u8 min_looks;
        u8 selected_looks;

        mNpc_ResetHaveAppeared();
        lbRTC_TimeCopy(last_grow_time, rtc_time);

        min_looks = mNpc_GetMinLooks(&min_looks_bitfield, &min_looks_num);
        selected_looks = min_looks;

        /* Multiple personalities are tied for minimum */
        if (min_looks == mNpc_LOOKS_UNSET) {
            int min_sex = mNpc_GetMinSex();
            u8 min_looks_bitfield_save;
            int min_looks_num_save;
            u8 looks;

            if (min_sex != mPr_SEX_OTHER) {
                min_looks_bitfield_save = min_looks_bitfield;
                min_looks_num_save = min_looks_num;

                /* Clear any tied minimum personalities which are of the greater sex */
                for (looks = 0; looks < mNpc_LOOKS_NUM; looks++) {
                    if (((min_looks_bitfield >> looks) & 1) == 1 && mNpc_GetLooks2Sex(looks) != min_sex) {
                        min_looks_bitfield &= ~(1 << looks);
                        min_looks_num--;
                    }
                }

                if (min_looks_num == 0 || min_looks_num == min_looks_num_save) {
                    /* Either all personalities were cleared or none were, so restore the prior state */
                    min_looks_bitfield = min_looks_bitfield_save;
                    min_looks_num = min_looks_num_save;
                }
            }

            selected = RANDOM(min_looks_num);

            for (looks = 0; looks < mNpc_LOOKS_NUM; looks++) {
                if (((min_looks_bitfield >> looks) & 1) == 1) {
                    if (selected <= 0) {
                        selected_looks = looks;
                        break;
                    } else {
                        selected--;
                    }
                }
            }
        }

        if (selected_looks >= mNpc_LOOKS_NUM) {
            selected_looks = mNpc_LOOKS_GIRL;
        }

        grow_idx = mNpc_SetGrowNpc(selected_looks);

        if (grow_idx >= 0 && grow_idx < ANIMAL_NUM_MAX) {
            mNpc_SetNpcNameID(Save_GetPointer(animals[grow_idx]), 1);
            mNpc_AddNowNpcMax(Save_GetPointer(now_npc_max));
            mNpc_RenewRemoveHistory();
        }
    }
}

extern void mNpc_ForceRemove() {
    lbRTC_time_c force_remove_time;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    lbRTC_ymd_c* force_remove_date = Save_GetPointer(force_remove_date);
    Animal_c* animal = Save_Get(animals);
    int interval;
    int animal_num = mNpc_GetAnimalNum();
    int ignored_idx = -1;
    int idx;

    if (animal_num == ANIMAL_NUM_MAX && force_remove_date->year != 0xFFFF && force_remove_date->month != 0xFF &&
        force_remove_date->day != 0xFF) {
        mTM_ymd_2_time(&force_remove_time, force_remove_date);

        if (lbRTC_IsOverTime(&force_remove_time, rtc_time) == lbRTC_OVER) {
            interval = lbRTC_GetIntervalDays(&force_remove_time, rtc_time);
        } else {
            interval = lbRTC_GetIntervalDays(rtc_time, &force_remove_time);
        }

        if (interval >= mNpc_MINIMUM_DAYS_BEFORE_FORCE_REMOVAL) {
            if (Save_Get(scene_no) == SCENE_PLAYERSELECT_2) {
                ignored_idx = Common_Get(player_select_animal_no);
            }

            idx = mNpc_GetGoodbyAnimalIdx(ignored_idx);

            if (idx != -1) {
                animal += idx;

                if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                    mNpc_DestroyHouse(&animal->home_info);
                    mNpc_SetGoodbyAnimalMail_common(&l_mnpc_goodby_mail, &animal->id);
                    mNpc_SendRegisteredGoodbyMail();

                    if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
                        mAN_clear_compress_info_table(animal->id.npc_id, &Save_Get(add_npc).save.regist_add_npc,
                                                      Common_GetPointer(add_npc_info));
                    }

                    mNpc_ClearAnimalInfo(animal);
                    mNpc_SubNowNpcMax(Save_GetPointer(now_npc_max));
                    mNpc_RenewRemoveHistory();
                }
            }
        }
    }
}

extern int mNpc_DecideMaskNpc_summercamp(mActor_name_t* npc_id) {
    static int looks_table[mNpc_LOOKS_NUM];

    u8 looks;
    int i;
    int res = FALSE;

    if (npc_id != NULL) {
        npc_id[0] = EMPTY_NO;
        mNpc_ResetHaveAppeared();
        mNpc_MakeRandTable(looks_table, mNpc_LOOKS_NUM, NPC_ROM_NUM); // why are we swapping this 'NPC_NUM' times???

        for (i = 0; i < mNpc_LOOKS_NUM; i++) {
            looks = looks_table[i];

            if (mNpc_GetLooks2NotHaveAppearedNum(looks) > 0) {
                int idx = mNpc_GrowLooksNpcIdx(looks);

                if (idx != -1) {
                    npc_id[0] = NPC_START | idx;
                    /* This makes summer campers impossible to appear by 'natural growth' in your town
                       unless you've seen every non-islander in your town as a villager or summer camper... */
                    mNpc_SetHaveAppeared(npc_id[0]);
                    res = TRUE;

                    break;
                }
            }
        }
    }

    return res;
}

extern int mNpc_RegistMaskNpc_summercamp(mActor_name_t mask_id, mActor_name_t npc_id, mActor_name_t cloth_id) {
    int free_mask_idx = mNpc_GetFreeMaskNpcIdx();
    int res = FALSE;

    if (free_mask_idx != -1) {
        mNpc_MaskNpc_c* mask_npc = Common_GetPointer(mask_npc[free_mask_idx]);

        if (cloth_id != EMPTY_NO) {
            if (((cloth_id == RSV_CLOTH) || (cloth_id >= ITM_CLOTH_START && cloth_id < ITM_CLOTH_END) ||
                 cloth_id == RSV_CLOTH1) == FALSE) {
                cloth_id = ITM_CLOTH_START;
            }
        }

        if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
            mask_npc->mask_id = mask_id;
            mask_npc->npc_id = npc_id;
            mask_npc->exists = FALSE;
            mask_npc->in_use = TRUE;
            mNpc_ClearAnimalInfo(&mask_npc->animal_data);
            mNpc_SetDefAnimal(&mask_npc->animal_data, npc_id, npc_def_list);
            mNpc_LoadNpcNameString(mask_npc->animal_data.id.name, npc_id & 0xFFF);

            if (cloth_id == EMPTY_NO) {
                mask_npc->cloth_id = mask_npc->animal_data.cloth;
            } else {
                mask_npc->cloth_id = cloth_id;
            }

            if (Common_Get(npc_is_summercamper) == TRUE) {
                mNpc_ClearAnimalMemory(mask_npc->animal_data.memories, 1);
                mNpc_SetAnimalMemory(&Now_Private->player_ID, &mask_npc->animal_data.id,
                                     &mask_npc->animal_data.memories[0]);
            }

            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_CheckNpcSet_fgcol(mActor_name_t fg_item, u32 attribute) {
    int res = FALSE;

    if (mFI_CheckFGNpcOn(fg_item)) {
        res = mCoBG_Attr2CheckPlaceNpc(attribute);
    }

    return res;
}

/**
 * Checks if an NPC can be placed on a foreground item based on collision attributes.
 * Validates that the foreground item supports NPC placement and the collision allows it.
 *
 * @param fg_item Foreground item ID to check
 * @param attribute Collision attribute of the location
 * @param type mFM_CLEAR_TYPE_* type to check
 * @return TRUE if NPC can be placed, FALSE otherwise
 */
extern int mNpc_CheckNpcSet_fgcol_easy(mActor_name_t fg_item, u32 attribute, int chk_type) {
    int res = FALSE;

    if (mFI_CheckFGNpcOn(fg_item) || mFM_check_player_clear_item(fg_item, chk_type) == TRUE) {
        res = mCoBG_Attr2CheckPlaceNpc(attribute);
    }

    return res;
}

static int mNpc_CheckNpcSet_fgcol_hard(mActor_name_t fg_item, u32 attribute) {
    int res = FALSE;

    if (mFI_CheckFGNpcOn(fg_item) && (attribute <= mCoBG_ATTRIBUTE_GRASS2 ||
                                      (attribute >= mCoBG_ATTRIBUTE_SOIL0 && attribute <= mCoBG_ATTRIBUTE_SOIL2) ||
                                      attribute == mCoBG_ATTRIBUTE_STONE)) {
        res = TRUE;
    }

    return res;
}

extern int mNpc_CheckNpcSet(int bx, int bz, int ut_x, int ut_z) {
    mCoBG_Collision_u* collision = mFI_GetBkNum2ColTop(bx, bz);
    mActor_name_t* items = mFI_BkNumtoUtFGTop(bx, bz);
    int res = FALSE;

    if (collision != NULL && items != NULL) {
        res = mNpc_CheckNpcSet_fgcol(items[ut_z * UT_X_NUM + ut_x],
                                     collision[ut_z * UT_X_NUM + ut_x].data.unit_attribute);
    }

    return res;
}

/**
 * Checks if an NPC can be placed at the specified block and unit coordinates.
 * Retrieves collision and item data for the location and validates NPC placement.
 *
 * @param bx Block X coordinate
 * @param bz Block Z coordinate
 * @param ut_x Unit X coordinate within block
 * @param ut_z Unit Z coordinate within block
 * @param chk_type mFM_CLEAR_TYPE_* type to check
 * @return TRUE if NPC can be placed at location, FALSE otherwise
 */
extern int mNpc_CheckNpcSet_easy(int bx, int bz, int ut_x, int ut_z, int chk_type) {
    mCoBG_Collision_u* collision = mFI_GetBkNum2ColTop(bx, bz);
    mActor_name_t* items = mFI_BkNumtoUtFGTop(bx, bz);
    int res = FALSE;

    if (collision != NULL && items != NULL) {
        res = mNpc_CheckNpcSet_fgcol_easy(items[ut_z * UT_X_NUM + ut_x],
                                          collision[ut_z * UT_X_NUM + ut_x].data.unit_attribute, chk_type);
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock_hard_area(int* ut_x, int* ut_z, int bx, int bz, int restrict_area) {
    int now_ut_x;
    int now_ut_z;
    mCoBG_Collision_u* col;
    mActor_name_t* items;
    int min_ut_x;
    int min_ut_z;
    int res;
    u32 center;
    int i;
    int j;

    col = mFI_GetBkNum2ColTop(bx, bz);
    items = mFI_BkNumtoUtFGTop(bx, bz);
    min_ut_x = UT_X_NUM;
    min_ut_z = UT_Z_NUM;
    res = FALSE;

    if (restrict_area < 0 || restrict_area > 9) {
        return FALSE;
    }

    if (items != NULL && col != NULL) {
        for (i = restrict_area; i < UT_Z_NUM - restrict_area; i++) {
            for (j = restrict_area; j < UT_X_NUM - restrict_area; j++) {
                if (mNpc_CheckNpcSet_fgcol_hard(items[i * UT_X_NUM + j], col[i * UT_X_NUM + j].data.unit_attribute) ==
                    TRUE) {
                    /* Check that the height of each point on the unit is equal*/
                    if (col[i * UT_X_NUM + j].data.center == col[i * UT_X_NUM + j].data.top_left &&
                        col[i * UT_X_NUM + j].data.center == col[i * UT_X_NUM + j].data.bot_left &&
                        col[i * UT_X_NUM + j].data.center == col[i * UT_X_NUM + j].data.bot_right &&
                        col[i * UT_X_NUM + j].data.center == col[i * UT_X_NUM + j].data.top_right) {

                        now_ut_x = 8 - j;
                        now_ut_z = 8 - i;

                        now_ut_x = ABS(now_ut_x);
                        now_ut_z = ABS(now_ut_z);

                        if (min_ut_x > now_ut_x && min_ut_z > now_ut_z) {
                            *ut_x = j;
                            *ut_z = i;
                            min_ut_x = now_ut_x;
                            min_ut_z = now_ut_z;
                            res = TRUE;
                        }
                    }
                }
            }
        }
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock_area(int* ut_x, int* ut_z, int bx, int bz, int restrict_area) {
    static u16 fg_flag[UT_Z_NUM];

    mCoBG_Collision_u* col_top;
    mActor_name_t* fg_top;
    u16* fg_flag_p = fg_flag;
    int candidates;
    int res;
    int i;
    int j;
    int rand;

    col_top = mFI_GetBkNum2ColTop(bx, bz);
    fg_top = mFI_BkNumtoUtFGTop(bx, bz);
    candidates = 0;
    res = FALSE;

    if (restrict_area < 0 || restrict_area > 9) {
        return FALSE;
    }

    bzero(fg_flag, sizeof(fg_flag));

    if (fg_top != NULL && col_top != NULL) {
        for (i = restrict_area; i < UT_Z_NUM - restrict_area; i++) {
            for (j = restrict_area; j < UT_X_NUM - restrict_area; j++) {
                if (mNpc_CheckNpcSet_fgcol(fg_top[i * UT_X_NUM + j], col_top[i * UT_X_NUM + j].data.unit_attribute) ==
                    TRUE) {
                    *fg_flag_p |= 1 << j;
                    candidates++;
                }
            }

            fg_flag_p++;
        }
    }

    fg_flag_p = fg_flag;
    if (candidates > 0) {
        rand = RANDOM(candidates);

        for (i = restrict_area; i < UT_Z_NUM - restrict_area; i++) {
            for (j = restrict_area; j < UT_X_NUM - restrict_area; j++) {
                if (((*fg_flag_p >> j) & 1) == 1) {
                    if (rand == 0) {
                        *ut_x = j;
                        *ut_z = i;
                        res = TRUE;

                        break;
                    } else {
                        rand--;
                    }
                }
            }

            if (res == TRUE) {
                break;
            }

            fg_flag_p++;
        }
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock(int* ut_x, int* ut_z, int bx, int bz) {
    return mNpc_GetMakeUtNuminBlock_area(ut_x, ut_z, bx, bz, 1); // can't spawn in the outer-most square of units
}

static int mNpc_CheckNpcSet_height(int bx, int bz, int ut_x, int ut_z, mActor_name_t item, mCoBG_Collision_u* col) {
    int res = FALSE;

    if (col != NULL && mNpc_CheckNpcSet_fgcol(item, col->data.unit_attribute)) {
        xyz_t wpos;

        mFI_BkandUtNum2Wpos(&wpos, bx, bz, ut_x, ut_z);

        if (mCoBG_ExistHeightGap_KeepAndNow(wpos) == FALSE) {
            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock33(int* make_ut_x, int* make_ut_z, int ut_x, int ut_z, int bx, int bz) {
    static int ut_xnum_table[9] = { 0, 1, -1, 0, 1, -1, 0, 1, -1 };
    static int ut_znum_table[9] = { 0, 0, 0, 1, 1, 1, -1, -1, -1 };

    mCoBG_Collision_u* col_top;
    mActor_name_t* fg_top;
    int res;
    int x;
    int z;
    int idx;
    int i;

    col_top = mFI_GetBkNum2ColTop(bx, bz);
    fg_top = mFI_BkNumtoUtFGTop(bx, bz);
    res = FALSE;

    if (col_top != NULL && fg_top != NULL) {
        for (i = 0; i < 9; i++) {
            x = ut_x + ut_xnum_table[i];
            z = ut_z + ut_znum_table[i];

            if (x >= 1 && x < (UT_X_NUM - 1) && z >= 1 && z < (UT_Z_NUM - 1)) {
                idx = z * UT_X_NUM + x;

                if (mNpc_CheckNpcSet_height(bx, bz, x, z, fg_top[idx], &col_top[idx]) == TRUE) {
                    make_ut_x[0] = x;
                    make_ut_z[0] = z;
                    res = TRUE;

                    break;
                }
            }
        }
    }

    return res;
}

extern int mNpc_GetMakeUtNuminBlock_hide_hard_area(int* ut_x, int* ut_z, int bx, int bz, int restrict_area) {
    static u16 hide_ut_bit[UT_Z_NUM];

    int now_ut_z;
    int now_ut_x;
    mCoBG_Collision_u* col_top;
    mActor_name_t* fg_top;
    int min_ut_x;
    int min_ut_z;
    int res;
    int i;
    int j;

    col_top = mFI_GetBkNum2ColTop(bx, bz);
    fg_top = mFI_BkNumtoUtFGTop(bx, bz);
    min_ut_x = UT_X_NUM;
    min_ut_z = UT_Z_NUM;
    res = FALSE;

    if (restrict_area < 0 || restrict_area > 9) {
        return FALSE;
    }

    if (fg_top != NULL && col_top != NULL) {
        bzero(hide_ut_bit, sizeof(hide_ut_bit));
        mAGrw_SetHideUtInfo(hide_ut_bit, fg_top);

        for (i = restrict_area; i < UT_Z_NUM - restrict_area; i++) {
            for (j = restrict_area; j < UT_X_NUM - restrict_area; j++) {
                if (mNpc_CheckNpcSet_fgcol_hard(fg_top[i * UT_X_NUM + j],
                                                col_top[i * UT_X_NUM + j].data.unit_attribute) == TRUE) {
                    /* Check that the height of each point on the unit is equal*/
                    if (col_top[i * UT_X_NUM + j].data.center == col_top[i * UT_X_NUM + j].data.top_left &&
                        col_top[i * UT_X_NUM + j].data.center == col_top[i * UT_X_NUM + j].data.bot_left &&
                        col_top[i * UT_X_NUM + j].data.center == col_top[i * UT_X_NUM + j].data.bot_right &&
                        col_top[i * UT_X_NUM + j].data.center == col_top[i * UT_X_NUM + j].data.top_right &&
                        ((hide_ut_bit[i] >> j) & 1) == 1) {

                        now_ut_x = 8 - j;
                        now_ut_z = 8 - i;

                        now_ut_x = ABS(now_ut_x);
                        now_ut_z = ABS(now_ut_z);

                        if (min_ut_x > now_ut_x && min_ut_z > now_ut_z) {
                            *ut_x = j;
                            *ut_z = i;
                            min_ut_x = now_ut_x;
                            min_ut_z = now_ut_z;
                            res = TRUE;
                        }
                    }
                }
            }
        }
    }

    return res;
}

typedef struct npc_temper_s {
    u16 unlock_timer;
    u8 over_impatient_num;
    u8 talk_num_max;
} mNpc_Temper_c;

typedef struct npc_talk_info_s {
    u16 timer;
    u8 talk_num;
    u8 quest_request;
    u16 unlock_timer;
    u16 reset_timer;
} mNpc_Talk_Info_c;

static mNpc_Talk_Info_c l_npc_talk_info[ANIMAL_NUM_MAX + mISL_ISLANDER_NUM];
static mNpc_Temper_c l_npc_temper[mNpc_FEEL_NUM] = {
    { 4000, 12, 15 }, // mNpc_FEEL_NORMAL
    { 3000, 10, 13 }, // mNpc_FEEL_HAPPY
    { 4000, 12, 15 }, // mNpc_FEEL_ANGRY
    { 4000, 10, 13 }, // mNpc_FEEL_SAD
    { 5000, 9, 12 },  // mNpc_FEEL_SLEEPY
    { 5000, 9, 12 }   // mNpc_FEEL_PITFALL
};

extern void mNpc_ClearTalkInfo() {
    mNpc_Talk_Info_c* talk_info_p = l_npc_talk_info;
    int i;

    bzero(talk_info_p, sizeof(l_npc_talk_info));
}

static void mNpc_TimerCountDown(mNpc_Talk_Info_c* talk_info) {
    if (talk_info->timer > 0) {
        talk_info->timer--;
    }
}

static void mNpc_SetUnlockTimer(u16* unlock_timer, u16* reset_timer, int looks) {
    unlock_timer[0] = l_npc_temper[looks].unlock_timer;
    reset_timer[0] = unlock_timer[0];
}

static int mNpc_CountTalkNum(int animal_idx, int looks) {
    int res = FALSE;

    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info)) {
        mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];

        if (talk_info->talk_num < l_npc_temper[looks].talk_num_max && talk_info->timer > 0) {
            talk_info->talk_num++;
            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_CheckOverImpatient(int animal_idx, int looks) {
    int res = FALSE;

    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info)) {
        mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];

        if (talk_info->talk_num >= l_npc_temper[looks].over_impatient_num) {
            res = TRUE;
        }
    }

    return res;
}

extern int mNpc_GetOverImpatient(int animal_idx, int looks) {
    int patience = mNpc_PATIENCE_NORMAL;

    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info)) {
        mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];

        if (talk_info->talk_num >= l_npc_temper[looks].over_impatient_num) {
            if (talk_info->talk_num >= l_npc_temper[looks].talk_num_max) {
                patience = mNpc_PATIENCE_ANNOYED; // refuse to talk
            } else {
                patience = mNpc_PATIENCE_MILDLY_ANNOYED; // dialog shows mild annoyance
            }
        }
    }

    return patience;
}

static void mNpc_UnlockTimerCountDown(mNpc_Talk_Info_c* talk_info) {
    if (talk_info != NULL && talk_info->unlock_timer > 0 && talk_info->unlock_timer > (talk_info->reset_timer - 1000)) {
        talk_info->unlock_timer--;
    }
}

extern void mNpc_TalkInfoMove() {
    mNpc_Talk_Info_c* talk_info_p = l_npc_talk_info;
    int i;

    if (mFI_CheckPlayerWade(mFI_WADE_START) == TRUE) {
        for (i = 0; i < ARRAY_COUNT(l_npc_talk_info); i++) {
            talk_info_p->reset_timer = talk_info_p->unlock_timer;
            talk_info_p++;
        }
    }

    talk_info_p = l_npc_talk_info;
    for (i = 0; i < ARRAY_COUNT(l_npc_talk_info); i++) {
        mNpc_TimerCountDown(talk_info_p);
        mNpc_UnlockTimerCountDown(talk_info_p);

        if (talk_info_p->unlock_timer == 0 && talk_info_p->reset_timer > 0) {
            talk_info_p->talk_num = 0;
            talk_info_p->reset_timer = 0;
        }

        talk_info_p++;
    }
}

extern void mNpc_TalkEndMove(int animal_idx, int looks) {
    if (animal_idx >= 0 && animal_idx < ARRAY_COUNT(l_npc_talk_info) && looks >= 0 && looks < mNpc_LOOKS_NUM) {
        mNpc_Talk_Info_c* talk_info = &l_npc_talk_info[animal_idx];
        talk_info->timer = 1000;

        if (mNpc_CountTalkNum(animal_idx, looks) == TRUE && mNpc_CheckOverImpatient(animal_idx, looks) == TRUE) {
            mNpc_SetUnlockTimer(&talk_info->unlock_timer, &talk_info->reset_timer, looks);
        }
    }
}

extern int mNpc_GetNpcFloorNo() {
    mActor_name_t field_id = mFI_GetFieldId();
    mActor_name_t owner_name = Common_Get(house_owner_name);
    int floor_no = -1;

    if (mFI_GET_TYPE(field_id) == mFI_FIELD_NPCROOM0) {
        if (owner_name != EMPTY_NO && owner_name != RSV_NO) {
            int idx = mNpc_SearchAnimalinfo(Save_Get(animals), owner_name, ANIMAL_NUM_MAX);

            if (idx != -1) {
                floor_no = Common_Get(npclist[idx]).house_data.floor_id;
            } else if (Common_Get(cur_island_house_p) != NULL &&
                       ITEM_NAME_GET_TYPE(Common_Get(cur_island_house_p)->island.animal.id.npc_id) == NAME_TYPE_NPC) {
                floor_no = Common_Get(island_npclist[0]).house_data.floor_id;
            }
        }
    }

    return floor_no;
}

extern int mNpc_GetNpcWallNo() {
    mActor_name_t field_id = mFI_GetFieldId();
    mActor_name_t owner_name = Common_Get(house_owner_name);
    int wall_no = -1;

    if (mFI_GET_TYPE(field_id) == mFI_FIELD_NPCROOM0) {
        if (owner_name != EMPTY_NO && owner_name != RSV_NO) {
            int idx = mNpc_SearchAnimalinfo(Save_Get(animals), owner_name, ANIMAL_NUM_MAX);

            wall_no = Common_Get(npclist[idx]).house_data.wall_id;
        }
    }

    return wall_no;
}

/**
 * Gets the name of an animal and copies it to a buffer.
 * Uses the NPC world name if available, otherwise uses the fallback name.
 *
 * @param name_p Pointer to buffer to store animal name
 * @param animal Pointer to animal to get name of
 * @return TRUE if name was copied, FALSE if no animal or fallback name used
 */
static int mNpc_GetAnimal2Name(u8* name_p, Animal_c* animal) {
    int ret = FALSE;

    if (animal != NULL) {
        mNpc_GetNpcWorldNameAnm(name_p, &animal->id);
        ret = TRUE;
    } else {
        mPr_CopyPlayerName(name_p, l_no_name_npc_name);
    }

    return ret;
}

/**
 * Gets a pointer to an animal by appearance.
 * Searches for an animal with the specified appearance and returns a pointer to it if found.
 *
 * @param looks Appearance to search for
 * @param skip_count Number of animals to skip
 * @return Pointer to animal with matching appearance, or NULL if not found
 */
static Animal_c* mNpc_GetLooks2AnimalP(u8 looks, int skip_count) {
    Animal_c* animal_p = Save_Get(animals);
    Animal_c* animal = NULL;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (!mNpc_CheckFreeAnimalPersonalID(&animal_p->id) && animal_p->id.looks == looks) {
            if (skip_count <= 0) {
                animal = animal_p;
                break;
            } else {
                skip_count--;
            }
        }

        animal_p++;
    }

    return animal;
}

/**
 * Gets the name index of an NPC based on their appearance.
 * Searches for an NPC with the specified appearance and returns their personal ID if found.
 *
 * @param name_p Pointer to buffer to store NPC name
 * @param looks Appearance to search for
 * @return Personal ID of NPC with matching appearance, or -1 if not found
 */
extern int mNpc_GetLooks2Name_idx(u8* name_p, u8 looks) {
    int ret = -1;
    int looks_num = mNpc_GetSameLooksNum(looks);

    if (looks_num != 0) {
        Animal_c* animal_p = mNpc_GetLooks2AnimalP(looks, RANDOM(looks_num));

        if (mNpc_GetAnimal2Name(name_p, animal_p) == TRUE) {
            ret = mNpc_SearchAnimalPersonalID(&animal_p->id);
        }
    } else {
        mPr_CopyPlayerName(name_p, l_no_name_npc_name);
    }

    return ret;
}

/**
 * Gets a pointer to an animal by race.
 * Searches for an animal with the specified race and returns a pointer to it if found.
 *
 * @param race Race to search for
 * @param skip_count Number of animals to skip
 * @return Pointer to animal with matching race, or NULL if not found
 */
static Animal_c* mNpc_GetRace2AnimalP(u8 race, int skip_count) {
    Animal_c* animal_p = Save_Get(animals);
    Animal_c* animal = NULL;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal_p->id) == FALSE && animal_p->race == race) {
            if (skip_count <= 0) {
                animal = animal_p;
                break;
            } else {
                skip_count--;
            }
        }

        animal_p++;
    }

    return animal;
}

/**
 * Gets the name index of an NPC based on their race.
 * Searches for an NPC with the specified race and returns their personal ID if found.
 *
 * @param name_p Pointer to buffer to store NPC name
 * @param race Race to search for
 * @return Personal ID of NPC with matching race, or -1 if not found
 */
extern int mNpc_GetRace2Name_idx(u8* name_p, u8 race) {
    int ret = -1;
    int race_num = mNpc_GetSameRaceNum(race);

    if (race_num > 0) {
        Animal_c* animal_p = mNpc_GetRace2AnimalP(race, RANDOM(race_num));

        if (mNpc_GetAnimal2Name(name_p, animal_p) == TRUE) {
            ret = mNpc_SearchAnimalPersonalID(&animal_p->id);
        }
    } else {
        mPr_CopyPlayerName(name_p, l_no_name_npc_name);
    }

    return ret;
}

extern s8 mNpc_GetActor2NowPlayerFriendship(ACTOR* actorx) {
    Animal_c* animal = mNpc_GetAnimalInfoP(actorx->npc_id);
    s8 friendship = -128;

    if (animal != NULL && mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
        int mem_idx = mNpc_GetAnimalMemoryIdx(&Now_Private->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

        if (mem_idx != -1) {
            friendship = animal->memories[mem_idx].friendship;
        }
    }

    return friendship;
}

extern void mNpc_SetTalkBee(void) {
    if (Common_Get(player_bee_swell_flag) != TRUE) {
        Animal_c* animal = Save_Get(animals);
        mNpc_NpcList_c* npclist = Common_Get(npclist);
        int i;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                npclist->conversation_flags.beesting = TRUE;
            }

            animal++;
            npclist++;
        }

        Common_Get(island_npclist[0]).conversation_flags.beesting = TRUE;
    }
}

extern void mNpc_ClearTalkBee(void) {
    mNpc_NpcList_c* npclist = Common_Get(npclist);
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        npclist->conversation_flags.beesting = FALSE;
        npclist++;
    }

    Common_Get(island_npclist[0]).conversation_flags.beesting = FALSE;
}

extern u8 mNpc_GetFishCompleteTalk(mNpc_NpcList_c* npclist) {
    u8 res = TRUE;

    if (npclist != NULL) {
        res = npclist->conversation_flags.fish_complete;
    }

    return res;
}

extern u8 mNpc_GetInsectCompleteTalk(mNpc_NpcList_c* npclist) {
    u8 res = TRUE;

    if (npclist != NULL) {
        res = npclist->conversation_flags.insect_complete;
    }

    return res;
}

extern void mNpc_SetFishCompleteTalk(mNpc_NpcList_c* npclist) {
    if (npclist != NULL) {
        npclist->conversation_flags.fish_complete = TRUE;
    }
}

extern void mNpc_SetInsectCompleteTalk(mNpc_NpcList_c* npclist) {
    if (npclist != NULL) {
        npclist->conversation_flags.insect_complete = TRUE;
    }
}

extern void mNpc_SetNpcHomeYpos() {
    Animal_c* animal = Save_Get(animals);
    mNpc_NpcList_c* npclist = Common_Get(npclist);
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            npclist->house_position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(npclist->house_position, 0.0f);
        }

        animal++;
        npclist++;
    }
}

extern int mNpc_SetActionTalkMemory(Anmmem_c* memory, int action) {
    int ret = FALSE;

    if (memory != NULL) {
        memory->action_talk |= (1 << action);
        ret = TRUE;
    }

    return ret;
}

extern int mNpc_SetActionTalk(Anmmem_c* memory, PersonalID_c* pid, int action) {
    int ret = FALSE;

    if (memory != NULL && pid != NULL) {
        int mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

        if (mem_idx != -1) {
            memory += mem_idx;
            ret = mNpc_SetActionTalkMemory(memory, action);
        }
    }

    return ret;
}

extern void mNpc_UnsetActionTalkMemory(Anmmem_c* memory, int action) {
    if (memory != NULL) {
        memory->action_talk &= ~(1 << action);
    }
}

extern int mNpc_CheckActionTalk(Anmmem_c* memory, int action) {
    int ret = FALSE;

    if (memory != NULL) {
        if (memory->action_talk & (1 << action)) {
            ret = TRUE;
        }
    }

    return ret;
}

extern int mNpc_GetActionTalkNum(Anmmem_c* memory) {
    int num = 0;
    int i;

    if (memory != NULL) {
        for (i = 0; i < mISL_VILLAGE_PLAYER_ACTION_NUM; i++) {
            if (mNpc_CheckActionTalk(memory, i) == TRUE) {
                num++;
            }
        }
    }

    return num;
}

extern u32 mNpc_GetMDIdx(mActor_name_t npc_id) {
    int idx = -1;
    mActor_name_t md_item = mNpc_GetMD(npc_id);

    if (md_item != EMPTY_NO) {
        idx = md_item - ITM_MINIDISK_START;
    }

    return idx;
}

extern mActor_name_t mNpc_GetMD(mActor_name_t npc_id) {
    mActor_name_t md_item = EMPTY_NO;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        if (IS_NPC_ADD_NPC(npc_id)) {
            AnimalInfo_c* info = mAN_getP_animalInfo(npc_id);

            if (info != NULL) {
                md_item = ITM_MINIDISK_START + info->song_no;
            }
        } else {
            int idx = npc_id & 0xFFF;

            if (idx < NPC_ROM_NUM) {
                md_item = npc_md_list[idx];
            }
        }
    }

    return md_item;
}

extern mActor_name_t mNpc_GetNowMD(void) {
    return Common_Get(now_md);
}

extern void mNpc_ClearSick(mNpc_SickInfo_c* sick_info) {
    int i;

    bzero(sick_info, sizeof(mNpc_SickInfo_c));
    mNpc_ClearAnimalPersonalID(&sick_info->id);
    lbRTC_TimeCopy(&sick_info->heal_time, &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(&sick_info->sick_level_change_time, &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(&sick_info->recovery_time, &mTM_rtcTime_clear_code);

    for (i = 0; i < mNpc_SICK_LV_NUM; i++) {
        mPr_ClearPersonalID(&sick_info->id_gave_medicine[i]);
    }

    sick_info->healed = FALSE;
    sick_info->gave_medicine = FALSE;
    sick_info->sick_level = mNpc_SICK_LV_NOT_SICK;
}

extern void mNpc_HealSick(mNpc_SickInfo_c* sick_info) {
    int sick_villager_idx;

    mNpc_ClearSick(sick_info);
    sick_villager_idx = mQst_GetOccuredContestIdx(mQst_CONTEST_KIND_SICK);
    if (sick_villager_idx != -1) {
        Animal_c* animal = Save_GetPointer(animals[sick_villager_idx]);

        mQst_ClearContest(&animal->contest_quest);
    }
}

extern int mNpc_GetSickAnimalIdx_com(mNpc_SickInfo_c* sick_info) {
    int idx = -1;

    if (mNpc_CheckFreeAnimalPersonalID(&sick_info->id) == FALSE && sick_info->sick_level < mNpc_SICK_LV_NOT_SICK) {
        idx = mNpc_SearchAnimalPersonalID(&sick_info->id);
    }

    return idx;
}

extern int mNpc_GetSickAnimalIdx(void) {
    return mNpc_GetSickAnimalIdx_com(Save_GetPointer(sick_info));
}

extern int mNpc_GetSickLevel(void) {
    return Save_Get(sick_info).sick_level;
}

extern int mNpc_CheckSickAnimal(Animal_c* animal) {
    int ret = FALSE;

    if (animal != NULL) {
        int sick_idx = mNpc_GetSickAnimalIdx();

        if (sick_idx != -1) {
            int idx = mNpc_SearchAnimalPersonalID(&animal->id);

            if (sick_idx == idx) {
                ret = TRUE;
            }
        }
    }

    return ret;
}

extern void mNpc_InitSickAnimal(mNpc_SickInfo_c* sick_info, AnmPersonalID_c* anm_id, lbRTC_time_c* time) {
    mNpc_ClearSick(sick_info);
    mNpc_CopyAnimalPersonalID(&sick_info->id, anm_id);
    lbRTC_TimeCopy(&sick_info->heal_time, time);
    lbRTC_TimeCopy(&sick_info->sick_level_change_time, time);
    sick_info->sick_level = mNpc_SICK_LV4;
}

static void mNpc_CompleteRecoverySickAnimal(mNpc_SickInfo_c* sick_info) {
    bzero(&sick_info->recovery_time, sizeof(lbRTC_time_c));
    sick_info->healed = FALSE;
}

extern int mNpc_PrescribeForSickAnimal(mNpc_SickInfo_c* sick_info, PersonalID_c* pid, lbRTC_time_c* time) {
    int sick_lv = sick_info->sick_level;

    if (mPr_NullCheckPersonalID(pid) == FALSE && sick_info->gave_medicine == FALSE) {
        if (mNpc_GetSickAnimalIdx_com(sick_info) != -1 && mNpc_CheckSoonRecoverySick(sick_info) == FALSE) {
            mPr_CopyPersonalID(&sick_info->id_gave_medicine[sick_info->sick_level], pid);
            lbRTC_TimeCopy(&sick_info->sick_level_change_time, time);
            sick_info->gave_medicine = TRUE;
            sick_info->sick_level++;
            if (sick_info->sick_level == mNpc_SICK_LV_NOT_SICK) {
                mNpc_CompleteRecoverySickAnimal(sick_info);
                sick_info->sick_level = mNpc_SICK_LV1;
            }

            sick_lv = sick_info->sick_level;
        }
    }

    return sick_lv;
}

extern int mNpc_CheckSoonRecoverySick(mNpc_SickInfo_c* sick_info) {
    int ret = FALSE;

    if (lbRTC_IsEqualTime(&sick_info->recovery_time, &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) == FALSE) {
        ret = TRUE;
    }

    return ret;
}

extern void mNpc_HealingSick(mNpc_SickInfo_c* sickInfo) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    if (mNpc_GetSickAnimalIdx_com(sickInfo) != -1 && sickInfo->sick_level != mNpc_SICK_LV_NOT_SICK) {
        if (lbRTC_IsOverTime(&sickInfo->heal_time, rtc_time) == lbRTC_OVER) {
            if (lbRTC_GetIntervalDays(&sickInfo->heal_time, rtc_time) >= 10) {
                mNpc_HealSick(sickInfo);
            } else if (mNpc_CheckSoonRecoverySick(sickInfo) == TRUE && sickInfo->healed == FALSE) {
                sickInfo->healed = TRUE;
                sickInfo->sick_level = mNpc_SICK_LV_NOT_SICK;
                lbRTC_TimeCopy(&sickInfo->recovery_time, rtc_time);
            }
        } else {
            mNpc_HealSick(sickInfo);
        }
    }
}

extern void mNpc_GetWorseSickAnimal(mNpc_SickInfo_c* sick_info) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    if (mNpc_GetSickAnimalIdx_com(sick_info) != -1 && sick_info->sick_level != mNpc_SICK_LV_NOT_SICK) {
        if (lbRTC_IsEqualTime(&sick_info->sick_level_change_time, &mTM_rtcTime_clear_code, lbRTC_CHECK_ALL) == TRUE &&
            lbRTC_GetIntervalDays(&sick_info->heal_time, rtc_time) >= 2) {
            sick_info->sick_level = mNpc_SICK_LV5;
            lbRTC_TimeCopy(&sick_info->sick_level_change_time, rtc_time);
        } else {
            if (lbRTC_IsOverTime(&sick_info->sick_level_change_time, rtc_time) == lbRTC_OVER) {
                int interval_days = lbRTC_GetIntervalDays(&sick_info->sick_level_change_time, rtc_time);

                if (interval_days >= 1) {
                    sick_info->gave_medicine = FALSE;
                }

                if (interval_days >= 2) {
                    if (sick_info->sick_level >= mNpc_SICK_LV4) {
                        sick_info->sick_level--;
                    } else {
                        sick_info->sick_level = mNpc_SICK_LV5;
                    }
                    lbRTC_TimeCopy(&sick_info->sick_level_change_time, rtc_time);
                }
            } else {
                sick_info->sick_level = mNpc_SICK_LV5;
                lbRTC_TimeCopy(&sick_info->sick_level_change_time, rtc_time);
            }
        }
    }
}

extern int mNpc_CheckSickPersonalID(mNpc_SickInfo_c* sick_info, PersonalID_c* pid) {
    int ret = FALSE;

    if (sick_info != NULL && pid != NULL && mPr_NullCheckPersonalID(pid) == FALSE) {
        int i;

        for (i = 0; i < mNpc_SICK_LV_NUM; i++) {
            if (mPr_CheckCmpPersonalID(pid, &sick_info->id_gave_medicine[i]) == TRUE) {
                ret = TRUE;
                break;
            }
        }
    }

    return ret;
}

extern int mNpc_CheckCmpSickAnimalName(u8* name) {
    mNpc_SickInfo_c* sick_info = Save_GetPointer(sick_info);
    int ret = FALSE;

    if (name != NULL) {
        int sick_animal_idx = mNpc_GetSickAnimalIdx_com(sick_info);

        if (sick_animal_idx != -1) {
            Animal_c* animal = Save_GetPointer(animals[sick_animal_idx]);

            ret = mNpc_CheckCmpAnimalNameStr(name, animal->id.name);
        }
    }

    return ret;
}

#include "../src/game/m_npc_island.c_inc"

extern void mNpc_PrintRemoveInfo(gfxprint_t* gfxprint) {
    Animal_c* remove_anm = NULL;
    Animal_c* in_anm = &mNpc_GetInAnimalP()->animal;
    u8 remove_idx = Save_Get(remove_animal_idx);

    gfxprint_color(gfxprint, 200, 150, 50, 255);
    gfxprint_locate8x8(gfxprint, 3, 10);

    if (remove_idx < ANIMAL_NUM_MAX) {
        remove_anm = Save_GetPointer(animals[remove_idx]);
    }

    if (in_anm != NULL) {
        gfxprint_printf(gfxprint, "%4x      %4x", remove_idx, in_anm->id.npc_id);
    } else {
        gfxprint_printf(gfxprint, "%4x      ----", remove_idx);
    }

    gfxprint_locate8x8(gfxprint, 8, 10);

    if (remove_anm != NULL) {
        if (IS_NPC_ADD_NPC(remove_anm->id.npc_id)) {
            gfxprint_color(gfxprint, 0xf0, 0xfa, 0xf0, 255);
            gfxprint_printf(gfxprint, "%4d", remove_anm->id.add_npc_id);
        } else {
            gfxprint_printf(gfxprint, "%4x", remove_anm->id.npc_id);
        }
    } else {
        gfxprint_printf(gfxprint, "----");
    }
}

static int l_mnpc_display = 0;

typedef struct npc_add_debug_s {
    int add_switch;
    u16 memory;
    u8 count;
    u8 add_bit;
    u8 edit_bit;
    int mtype;
    int disp_add;
} mNpc_Add_Debug_c;

static mNpc_Add_Debug_c l_mnpc_addd;

static void mNpc_PrintFriendship_fdebug_1(gfxprint_t* gfxprint) {
    int add_switch = l_mnpc_addd.add_switch;
    int i;

    gfxprint_color(gfxprint, 250, 100, 170, 255);
    gfxprint_locate8x8(gfxprint, 3, 18);

    if (add_switch == 0) {
        gfxprint_printf(gfxprint, "----------------------- %d", l_mnpc_addd.add_switch);
    } else if (add_switch == 1) {
        gfxprint_printf(gfxprint, "*********************** %d", l_mnpc_addd.add_switch);
    } else if (add_switch == 2) {
        gfxprint_printf(gfxprint, ">>>>>>>>>>>>>>>>>>>>>>> %d", l_mnpc_addd.add_switch);
    } else {
        gfxprint_printf(gfxprint, "%2d    ", l_mnpc_addd.count);
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            gfxprint_printf(gfxprint, "%1d", (l_mnpc_addd.memory >> i) & 1);
        }

        gfxprint_locate8x8(gfxprint, 3, 19);
        gfxprint_printf(gfxprint, "add bit ");
        for (i = 0; i < 8; i++) {
            gfxprint_printf(gfxprint, "%1d", (l_mnpc_addd.add_bit >> i) & 1);
        }

        gfxprint_printf(gfxprint, "  edit bit ");
        for (i = 0; i < 8; i++) {
            gfxprint_printf(gfxprint, "%1d", (l_mnpc_addd.edit_bit >> i) & 1);
        }

        gfxprint_locate8x8(gfxprint, 3, 20);
        gfxprint_printf(gfxprint, "mtype %d  disp_add 0x%x", l_mnpc_addd.mtype, l_mnpc_addd.disp_add);
    }
}

static int l_mnpc_animal_idx = -1;
static int l_mnpc_island_animal_idx = -1;

extern void mNpc_SetTalkAnimalIdx_fdebug(AnmPersonalID_c* anm_id) {
    if (anm_id != NULL) {
        l_mnpc_animal_idx = mNpc_SearchAnimalPersonalID(anm_id);

        if (l_mnpc_animal_idx == -1) {
            l_mnpc_island_animal_idx = mNpc_SearchIslandAnimalinfo(anm_id->npc_id, anm_id->add_npc_id);
        }
    }
}

static void mNpc_PrintFavoriteCloth_fdebug(gfxprint_t* gfxprint) {
    static const char* str_tbl[mNT_STYLE_NUM + 1] = {
        "ｶｯｺｲｲ",
        "ｶﾜｲｲ",
        "ﾎﾟｯﾌﾟﾅ",
        "ｻﾜﾔｶﾅ",
        "ｵｼｬﾚﾅ",
        "ｵﾁﾂｲﾀ",
        "ｼﾌﾞｲ",
        "ﾊﾃﾞﾅ",
        "ｷﾊﾞﾂﾅ",
        "ｷﾐｮｳﾅ",
        "ｾｯﾃｲﾅｼ",
    };
    Animal_c* animal = NULL;

    if (l_mnpc_animal_idx >= 0 && l_mnpc_animal_idx < ANIMAL_NUM_MAX) {
        animal = Save_GetPointer(animals[l_mnpc_animal_idx]);
    } else if (l_mnpc_island_animal_idx >= 0 && l_mnpc_island_animal_idx < PLAYER_NUM) {
        animal = Save_GetPointer(homes[l_mnpc_island_animal_idx].island.animal);
    }

    if (animal != NULL && mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
        int lcloth = mNpc_GetDefAnimalClothLAttr(animal);
        int hcloth = mNpc_GetDefAnimalClothHAttr(animal);

        if (lcloth < 0 || lcloth >= mNT_STYLE_NUM) {
            lcloth = mNT_STYLE_NUM;
        }

        if (hcloth < 0 || hcloth >= mNT_STYLE_NUM) {
            hcloth = mNT_STYLE_NUM;
        }

        gfxprint_color(gfxprint, 250, 150, 150, 255);
        gfxprint_locate8x8(gfxprint, 3, 24);
        gfxprint_printf(gfxprint, "c: %d %s", lcloth, str_tbl[lcloth]);
        gfxprint_locate8x8(gfxprint, 3, 25);
        gfxprint_printf(gfxprint, "c: %d %s", hcloth, str_tbl[hcloth]);
    }
}

static void mNpc_PrintReserveQuest(gfxprint_t* gfxprint) {
    static int delivery_idx[mQst_DELIVERY_KIND_NUM] = { 1, 2, 3, 4, 8 };
    static int contest_idx[mQst_CONTEST_KIND_NUM] = { 7, 9, 11, 12, 10, 13, 14, 6, 5 };
    static int disp_x_tbl[3] = { 3, 14, 25 };

    Animal_c* animal;
    int y;
    int idx;
    int x;
    int i;

    animal = Save_Get(animals);
    y = 23;
    x = 0;
    for (i = 0; i < ANIMAL_NUM_MAX; i++, animal++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            AnmPersonalID_c anm_id;
            int rsv_idx;
            u32 quest_type;
            u32 quest_kind;

            rsv_idx = mQst_GetReserve(&anm_id, &animal->id);
            idx = 255;

            if (rsv_idx != -1) {
                quest_type = mQst_QUEST_TYPE_ERRAND;

                if (mQst_GetReserveQuest(&quest_type, &quest_kind, rsv_idx) == TRUE) {
                    switch (quest_type) {
                        case mQst_QUEST_TYPE_DELIVERY:
                            if (quest_kind < mQst_DELIVERY_KIND_NUM) {
                                idx = delivery_idx[quest_kind];
                            }
                            break;
                        case mQst_QUEST_TYPE_CONTEST:
                            if (quest_kind < mQst_CONTEST_KIND_NUM) {
                                idx = contest_idx[quest_kind];
                            }
                            break;
                    }
                }
            }

            gfxprint_locate8x8(gfxprint, disp_x_tbl[x % ARRAY_COUNT(disp_x_tbl)], y);
            if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
                gfxprint_color(gfxprint, 250, 250, 250, 255);
                gfxprint_printf(gfxprint, "%3d %3d", animal->id.add_npc_id, idx);
            } else {
                gfxprint_color(gfxprint, 60, 60, 250, 255);
                gfxprint_printf(gfxprint, "%3d %3d", animal->id.npc_id & 0xFFF, idx);
            }

            x++;
            if (x % ARRAY_COUNT(disp_x_tbl) == 0) {
                y++;
            }
        }
    }
}

extern void mNpc_PrintRelation_fdebug(gfxprint_t* gfxprint) {
    static int disp_x_tbl[2] = { 2, 21 };
    s8* relations;
    Animal_c* animal;
    Animal_c* animal2;
    int y;
    int disp_count;
    int animal_idx;

    y = 14;
    disp_count = 0;
    animal2 = Save_Get(animals);

    if (l_mnpc_animal_idx >= 0 && l_mnpc_animal_idx < ANIMAL_NUM_MAX) {
        animal = &animal2[l_mnpc_animal_idx];
        relations = animal->animal_relations;

        for (animal_idx = 0; animal_idx < ANIMAL_NUM_MAX; animal_idx++) {
            if (animal_idx != l_mnpc_animal_idx && mNpc_CheckFreeAnimalPersonalID(&animal2->id) == FALSE) {
                gfxprint_locate8x8(gfxprint, disp_x_tbl[disp_count & 1], y);

                if (IS_NPC_ADD_NPC(animal2->id.npc_id)) {
                    gfxprint_color(gfxprint, 250, 250, 250, 255);
                    gfxprint_printf(gfxprint, "%2d %3d %3d %3d %1d", animal_idx, animal2->id.add_npc_id,
                        mNpc_GetMatchingPoint(&animal->id, &animal2->id), (int)*relations, mNpc_GetRelation(&animal->id, &animal2->id));
                } else {
                    gfxprint_color(gfxprint, 60, 60, 250, 255);
                    gfxprint_printf(gfxprint, "%2d %3d %3d %3d %1d", animal_idx, animal2->id.npc_id & 0xFFF,
                        mNpc_GetMatchingPoint(&animal->id, &animal2->id), (int)*relations, mNpc_GetRelation(&animal->id, &animal2->id));
                }

                disp_count++;
                if ((disp_count & 1) == 0) {
                    y++;
                }
            }

            relations++;
            animal2++;
        }
    }

    if (disp_count == 0) {
        gfxprint_color(gfxprint, 60, 60, 250, 255);
        gfxprint_locate8x8(gfxprint, 2, 14);
        gfxprint_printf(gfxprint, "no information -");
    }

    mNpc_PrintReserveQuest(gfxprint);
}

static void mNpc_PrintFriendship_fdebug_0(gfxprint_t* gfxprint) {
    Anmmem_c* memory;
    Private_c* priv;
    int x = 3;
    int y = 19;
    int i;

    if (l_mnpc_animal_idx >= 0 && l_mnpc_animal_idx < ANIMAL_NUM_MAX) {
        memory = Save_Get(animals[l_mnpc_animal_idx]).memories;

        if (memory != NULL) {
            gfxprint_color(gfxprint, 250, 100, 170, 255);
            gfxprint_locate8x8(gfxprint, 3, 18);
            priv = Now_Private;

            if (priv != NULL) {
                gfxprint_printf(gfxprint, "%4x ", priv->player_ID.player_id);
            } else {
                gfxprint_printf(gfxprint, "**** ");
            }

            gfxprint_color(gfxprint, 50, 150, 50, 255);

            for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
                if (i == 4) {
                    y++;
                    x = 3;
                }

                gfxprint_locate8x8(gfxprint, x, y);
                if (mNpc_CheckFreeAnimalMemory(memory) == FALSE) {
                    gfxprint_printf(gfxprint, "%4x %3d ", memory->memory_player_id.player_id, memory->friendship);
                } else {
                    gfxprint_printf(gfxprint, "**** *** ");
                }

                memory++;
                x += 9;
            }
        }
    }

    mNpc_PrintFavoriteCloth_fdebug(gfxprint);
}

typedef void (*mNpc_PRINT_FRIENDSHIP_PROC)(gfxprint_t*);

extern void mNpc_PrintFriendship_fdebug(gfxprint_t* gfxprint) {
    static mNpc_PRINT_FRIENDSHIP_PROC print_proc[2] = { &mNpc_PrintFriendship_fdebug_0,
                                                        &mNpc_PrintFriendship_fdebug_1 };

    (*print_proc[l_mnpc_display & 1])(gfxprint);
}

extern int mNpc_get_npc_param(u8* buf, mActor_name_t npc_name) {
    static u8 tmp[32] ATTRIBUTE_ALIGN(32);
    int res_size;
    int npc_idx;
    u32 aram_ofs;
    int param_ofs;
    u32 aram_addr;
    u8* src;

    bzero(buf, 0xC);

    if ((npc_name >> 12) == (NPC_START >> 12)) {
        npc_idx = npc_name & 0xFFF;
        res_size = JW_GetResSizeFileNo(RESOURCE_ANIMAL_PARAM) >> 3;
        aram_ofs = (npc_idx >> 2);
        param_ofs = (npc_idx & 3) << 3;

        if (IS_NPC_ADD_NPC(npc_name)) {
            src = mAN_getP_AnmAgbParam(npc_name);
            mem_copy(buf, src, 0xC);
        } else {
            if (npc_idx >= res_size) {
                JW_GetAramAddress(RESOURCE_ANIMAL_PARAM);
                return FALSE;
            }

            aram_addr = JW_GetAramAddress(RESOURCE_ANIMAL_PARAM) + aram_ofs * 0x20;
            _JW_GetResourceAram(aram_addr, tmp, 0x20);
            buf[0] = tmp[param_ofs];
            buf[1] = tmp[param_ofs + 1];
            buf[2] = tmp[param_ofs + 2];
            buf[3] = tmp[param_ofs + 3];
            buf[4] = tmp[param_ofs + 4];
            buf[5] = tmp[param_ofs + 5];
            buf[6] = tmp[param_ofs + 6];
            buf[7] = tmp[param_ofs + 7];
        }

        return TRUE;
    }

    return FALSE;
}
