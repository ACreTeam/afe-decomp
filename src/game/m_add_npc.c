#include "m_add_npc.h"
#include "m_name_table.h"
#include "m_house.h"
#include "m_common_data.h"
#include "libultra/libultra.h"

#define mAN_DATA_TEX_OFS 0x845

extern void mAN_clear_compress_info_table(mActor_name_t npc_id, int* compress_info_table, AddNpcInfo_c* add_npc_info) {
    int bit = 1;
    if (IS_NPC_ADD_NPC(npc_id)) {
        bit <<= (npc_id - NPC_ADD_START);

        if (compress_info_table != NULL) {
            *compress_info_table &= ~bit;
        }

        if (add_npc_info != NULL) {
            add_npc_info->compress_info_table &= ~bit;
        }
    }
}

extern AnimalInfo_c* mAN_getP_animalInfo(mActor_name_t npc_id) {
    AnimalInfo_c* info = NULL;

    if (IS_NPC_ADD_NPC(npc_id)) {
        info = &Common_Get(add_npc_info).info[npc_id - NPC_ADD_START];
    }

    return info;
}

extern void mAN_set_def_animalInfo(Animal_c* animal, mActor_name_t npc_id) {
    AnimalInfo_c* info = mAN_getP_animalInfo(npc_id);

    if (info != NULL) {
        animal->id.npc_id = npc_id;
        animal->id.looks = info->looks;
        animal->cloth = ITM_CLOTH_START + info->shirt_no;
        animal->umbrella_id = info->umbrella_no;
        animal->race = info->race;
        mem_copy(animal->catchphrase, info->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    }
}

extern void mAN_set_new_comer_compress_data(u8* compress_data, PersonalID_c* pid, mActor_name_t npc_id) {
    AddNpcNewComer_c* new_comer = &Save_Get(add_npc).new_comer;

    new_comer->new_comer_set = TRUE;
    new_comer->new_comer_npc_id = npc_id;
    mPr_CopyPersonalID(&new_comer->new_comer_inviter_pid, pid);
    new_comer->new_comer_invite_date.year = Common_Get(time.rtc_time.year);
    new_comer->new_comer_invite_date.month = Common_Get(time.rtc_time.month);
    new_comer->new_comer_invite_date.day = Common_Get(time.rtc_time.day);
    mem_copy(new_comer->new_comer_data, compress_data, mAN_COMPRESS_INFO_TABLE_MAX_SIZE);
}

extern void mAN_clear_new_comer_compress_data(AddNpcNewComer_c* new_comer) {
    new_comer->new_comer_set = FALSE;
}

extern int mAN_get_free_compress_data_idx(int* compress_info_table) {
    int idx = -1;
    int bit = 1;
    int i;

    for (i = 0; i < mAN_ANIMAL_NUM; i++) {
        if ((*compress_info_table & bit) == 0) {
            idx = i;
            break;
        }

        bit <<= 1;
    }

    return idx;
}

static int mAN_get_info_table_idx(u8 id, AddNpcInfo_c* add_npc_info) {
    int idx = -1;
    int bit = 1;
    int i;

    for (i = 0; i < mAN_ANIMAL_NUM; i++) {
        if ((add_npc_info->compress_info_table & bit) == bit && add_npc_info->info[i].id == id) {
            idx = i;
            break;
        }

        bit <<= 1;
    }

    return idx;
}

static int mAN_get_open_size(u8* compress_data) {
    // 'Yaz0', decompress size
    return (compress_data[4] << 24) | (compress_data[5] << 16) | (compress_data[6] << 8) | compress_data[7];
}

static void mAN_decode_data_to_info(AnimalInfo_c* info, u8* data) {
    info->id = data[0];
    mem_copy(info->name, &data[1], ANIMAL_NAME_LEN);
    mem_copy(info->catchphrase, &data[7], ANIMAL_CATCHPHRASE_LEN);
    info->race = data[11];
    info->is_islander = data[12];
    info->looks = data[13];
    info->shirt_no = data[14];
    info->house_type = data[15];
    info->house_variant = data[16];
    info->wall_no = data[17];
    info->floor_no = data[18];
    info->room_base_idx = (data[19] << 8) | data[20];
    info->room_second_idx = (data[21] << 8) | data[22];
    info->umbrella_no = data[23];
    info->song_no = data[24];
    info->voice_melody = (data[25] << 8) | data[26];
    info->love_cloth_type = data[27];
    info->hate_cloth_type = data[28];
    
    // Copy AGB params
    info->agb_param[0] = data[29];
    info->agb_param[1] = data[30];
    info->agb_param[2] = data[31];
    info->agb_param[3] = data[32];
    info->agb_param[4] = data[33];
    info->agb_param[5] = data[34];
    info->agb_param[6] = data[35];
    info->agb_param[7] = data[36];
}

static void mAN_set_tex(AnimalInfo_c* info, u8* data, u32 tex_size) {
    mem_copy(info->texture, data + mAN_DATA_TEX_OFS, tex_size);
}

static void mAN_decode_compress_data(AnimalInfo_c* info, u8* compress_data, u8* data) {
    u32 size = mAN_get_open_size(compress_data);

    decode_szs(compress_data, data);
    mAN_decode_data_to_info(info, data);
    mAN_set_tex(info, data, size - mAN_DATA_TEX_OFS);
}

static int mAN_get_max_open_size(u8* compress_data) {
    int regist_add_npc = Save_Get(add_npc).save.regist_add_npc;
    int bit;
    int i;
    int max_size = 0;

    for (bit = 1, i = 0; i < mAN_ANIMAL_NUM; i++) {
        if ((regist_add_npc & bit) == bit) {
            int size = mAN_get_open_size(compress_data);

            if (max_size < size) {
                max_size = size;
            }
        }

        bit <<= 1;
        compress_data += mAN_COMPRESS_INFO_TABLE_MAX_SIZE;
    }

    return max_size;
}

extern void mAN_regist_add_npc_info(void) {
    GameAlloc* allocator = &gamePT->gamealloc;
    int regist_add_npc = Save_Get(add_npc).save.regist_add_npc;
    int compress_info_table = Common_Get(add_npc_info.compress_info_table);

    if ((regist_add_npc ^ compress_info_table) != 0) {
        u8* compressed_data = Save_Get(add_npc).save.add_npc_compress_info_table[0];
        u8* decompress_buf = NULL;
        int max_open_size = mAN_get_max_open_size(compressed_data);

        if (max_open_size > 0) {
            decompress_buf = (u8*)gamealloc_malloc(allocator, max_open_size);
        }

        if (decompress_buf != NULL) {
            AnimalInfo_c* info = Common_Get(add_npc_info).info;
            int bit;
            int i;

            for (bit = 1, i = 0; i < mAN_ANIMAL_NUM; i++) {
                if ((regist_add_npc & bit) == bit && (compress_info_table & bit) == 0) {
                    mAN_decode_compress_data(info, compressed_data, decompress_buf);
                    compress_info_table |= bit;
                }

                bit <<= 1;
                compressed_data += mAN_COMPRESS_INFO_TABLE_MAX_SIZE;
                info++;
            }

            Common_Get(add_npc_info).compress_info_table = compress_info_table;
            gamealloc_free(allocator, decompress_buf);
        }
    }
}

static void mAN_set_add_npc(Animal_c* animal, u8* name, u8 id, int add_idx, PersonalID_c* inviter_pid) {
    mLd_land_info_c* land_info = Save_GetPointer(land_info);
    
    mAN_set_def_animalInfo(animal, NPC_ADD_START + add_idx);
    animal->moved_in = 2; // invited
    animal->id.land_id = land_info->id;
    mLd_CopyLandName(animal->id.land_name, land_info->name);
    mem_copy(animal->id.name, name, ANIMAL_NAME_LEN);
    animal->id.add_npc_id = id;
    mNpc_SetParentName(animal, inviter_pid);
}

static int mAN_regist_add_npc_same(AddNpcInfo_c* info, AddNpcNewComer_c* new_comer, u8* data) {
    Animal_c* animal = Save_Get(animals);
    
    if (ITEM_NAME_GET_TYPE(new_comer->new_comer_npc_id) == NAME_TYPE_NPC) {
        int idx = mNpc_SearchAnimalinfo(animal, new_comer->new_comer_npc_id, ANIMAL_NUM_MAX);

        if (idx == -1) {
            return mNpc_SearchIslandAnimalinfo(new_comer->new_comer_npc_id, 0xFF);
        }

        return idx;
    } else if (data != NULL) {
        return mAN_get_info_table_idx((u8)data[0], info);
    }

    return 0;
}

static int mAN_check_island_npc(mActor_name_t npc_id, u8* data) {
    int ret = FALSE;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        ret = mNpc_CheckIslandAnimalTableNo(npc_id);
    } else if (data != NULL && data[12] == TRUE) {
        ret = TRUE;
    }

    return ret;
}

static int mAN_regist_add_npc_get_idx(int* regist_add_npc, AddNpcInfo_c* info) {
    Animal_c* animal = Save_Get(animals);
    int idx;
    int ignore_idx;

    ignore_idx = -1;
    idx = mNpc_GetFreeAnimalInfo(Save_Get(animals), ANIMAL_NUM_MAX);
    if (idx == -1) {
        if (Save_Get(scene_no) == SCENE_PLAYERSELECT_2) {
            ignore_idx = Common_Get(player_select_animal_no);
        }

        idx = mNpc_GetGoodbyAnimalIdx(ignore_idx);
        if (idx != -1) {
            animal += idx;

            mNpc_DestroyHouse(&animal->home_info);
            mNpc_SetGoodbyAnimalMail(&animal->id);
            mNpc_SendRegisteredGoodbyMail();

            if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
                mAN_clear_compress_info_table(animal->id.npc_id, regist_add_npc, info);
            }

            mNpc_ClearAnimalInfo(animal);
            mNpc_SubNowNpcMax(Save_GetPointer(now_npc_max));
        }
    }

    return idx;
}

static int mAN_regist_add_npc_get_idx_island(AddNpcNewComer_c* new_comer) {
    Private_c* priv = Save_Get(private_data);
    int idx = -1;

    if (mPr_NullCheckPersonalID(&new_comer->new_comer_inviter_pid) == FALSE) {
        int i;

        for (i = 0; i < PLAYER_NUM; i++) {
            if (mPr_CheckCmpPersonalID(&new_comer->new_comer_inviter_pid, &priv->player_ID) == TRUE) {
                idx = mHS_get_arrange_idx(i);
                break;
            }

            priv++;
        }
    }

    return idx;
}

static int mAN_set_island_reserve_pos(mActor_name_t* fg_p, Anmhome_c* home) {
    int island_bx_tbl[mISL_FG_BLOCK_X_NUM];
    int ret = FALSE;
    int i;

    mFI_GetIslandBlockNumX(island_bx_tbl);
    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (*fg_p == RESERVE_ISLANDER_COTTAGE) {
            home->bx = island_bx_tbl[0];
            home->bz = mISL_BLOCK_Z;
            home->ux = i & 0xF;
            home->uz = (i >> 4) + 1;
            ret = TRUE;
            break;
        }

        fg_p++;
    }

    return ret;
}

extern void mAN_set_cd(AddNpcSave_c* add_npc_p, u8* compress_data, int add_npc_idx) {
    int regist_add_npc = add_npc_p->regist_add_npc;
    int bit = 1;

    if (add_npc_idx >= 0 && add_npc_idx < mAN_ANIMAL_NUM) {
        mem_copy(add_npc_p->add_npc_compress_info_table[add_npc_idx], compress_data, mAN_COMPRESS_INFO_TABLE_MAX_SIZE);
        bit <<= add_npc_idx;
        add_npc_p->regist_add_npc = regist_add_npc | bit;
    }
}

static void mAN_regist_add_npc_live_in(Animal_c* animal, AddNpcSave_c* add_npc_p, AddNpcInfo_c* info, AddNpcNewComer_c* new_comer, int data_size, int is_islander, u8* data) {
    int compress_info_table = info->compress_info_table;
    int bit = 1;

    if (ITEM_NAME_GET_TYPE(new_comer->new_comer_npc_id) == 0) {
        int add_idx = mAN_get_free_compress_data_idx(&add_npc_p->regist_add_npc);

        if (add_idx != -1) {
            AnimalInfo_c* animal_info = &info->info[add_idx];

            mAN_set_cd(add_npc_p, new_comer->new_comer_data, add_idx);
            mAN_decode_data_to_info(animal_info, data);
            mAN_set_tex(animal_info, data, data_size - mAN_DATA_TEX_OFS);
            bit <<= add_idx;
            info->compress_info_table = compress_info_table | bit;
            mAN_set_add_npc(animal, &data[1], data[0], add_idx, &new_comer->new_comer_inviter_pid);

            if (is_islander == FALSE) {
                mNpc_AddNowNpcMax(Save_GetPointer(now_npc_max));
            }
        }
    } else {
        mNpc_SetDefAnimal_name(animal, new_comer->new_comer_npc_id);
        mNpc_SetNpcNameID(animal, 1);
        mNpc_SetHaveAppeared(animal->id.npc_id);
        animal->moved_in = 2; // invited
        mNpc_SetParentName(animal, &new_comer->new_comer_inviter_pid);
        if (is_islander == FALSE) {
            mNpc_AddNowNpcMax(Save_GetPointer(now_npc_max));
        }
    }
}

static void mAN_regist_add_npc_sub(AddNpcSave_c* add_npc_p, AddNpcInfo_c* info, AddNpcNewComer_c* new_comer) {
    GameAlloc* allocator = &gamePT->gamealloc;
    int idx;
    u8* decompress_buf = NULL;
    int is_islander;
    int size = 0;

    if (ITEM_NAME_GET_TYPE(new_comer->new_comer_npc_id) != NAME_TYPE_NPC) {
        size = mAN_get_open_size(new_comer->new_comer_data);

        if (size > 0) {
            decompress_buf = (u8*)gamealloc_malloc(allocator, size);
        }

        if (decompress_buf != NULL) {
            decode_szs(new_comer->new_comer_data, decompress_buf);
        }
    }

    if (mAN_regist_add_npc_same(info, new_comer, decompress_buf) == -1) {
        is_islander = mAN_check_island_npc(new_comer->new_comer_npc_id, decompress_buf);

        if (is_islander == TRUE) {
            idx = mAN_regist_add_npc_get_idx_island(new_comer);

            if (idx != -1) {
                Island_c* island = &Save_Get(homes[idx]).island;
                Animal_c* animal = &Save_Get(homes[idx]).island.animal;

                if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                    mNpc_EraseIslandAnimal(idx);
                }

                mAN_set_island_reserve_pos(island->fgblock[0][0].items[0], &animal->home_info);
                bzero(&island->islander_spawn_date, sizeof(lbRTC_ymd_c));
                Common_Set(islander_start_ux, -1);
                Common_Set(islander_start_uz, -1);
            }
        } else {
            idx = mAN_regist_add_npc_get_idx(&add_npc_p->regist_add_npc, info);
        }

        if (idx != -1) {
            Animal_c* animal;

            if (is_islander == TRUE) {
                animal = &Save_Get(homes[idx]).island.animal;
            } else {
                animal = Save_GetPointer(animals[idx]);
            }

            mAN_regist_add_npc_live_in(animal, add_npc_p, info, new_comer, size, is_islander, decompress_buf);
        }
    }

    if (decompress_buf != NULL) {
        gamealloc_free(allocator, decompress_buf);
    }
}

extern void mAN_regist_add_npc(void) {
    AddNpc_c* add_npc;
    AddNpcSave_c* add_npc_save;
    AddNpcInfo_c* add_npc_info;
    AddNpcNewComer_c* new_comer;

    add_npc = Save_GetPointer(add_npc);
    add_npc_save = &add_npc->save;
    new_comer = &add_npc->new_comer;
    add_npc_info = Common_GetPointer(add_npc_info);
    if (new_comer->new_comer_set == TRUE) {
        const lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
        lbRTC_ymd_c* invite_date = &new_comer->new_comer_invite_date;

        if(lbRTC_IsEqualDate(
            rtc_time->year, rtc_time->month, rtc_time->day,
            invite_date->year, invite_date->month, invite_date->day
        ) != lbRTC_EQUAL) {
#if VERSION >= VER_GAEJ01_01
            if (new_comer->new_comer_npc_id == EMPTY_NO || ITEM_NAME_GET_TYPE(new_comer->new_comer_npc_id) == NAME_TYPE_NPC) {
                mAN_regist_add_npc_sub(add_npc_save, add_npc_info, new_comer);
            }
#else
            mAN_regist_add_npc_sub(add_npc_save, add_npc_info, new_comer);
#endif

            mNpc_RenewRemoveHistory();
            lbRTC_TimeCopy(Save_GetPointer(last_grow_time), rtc_time);
            mAN_clear_new_comer_compress_data(new_comer);
        }
    }
}

extern void mAN_load_add_npc_name_string(u8* name_buf, int id) {
    AnimalInfo_c* info = &Common_Get(add_npc_info).info[id - (u8)NPC_ADD_START];

    bcopy(info->name, name_buf, ANIMAL_NAME_LEN);
}

extern void mAN_set_draw_data(aNPC_draw_data_c* draw_data, mActor_name_t npc_id) {
    AnimalInfo_c* info = mAN_getP_animalInfo(npc_id);
    aNPC_draw_tex_data_c* tex_data = &draw_data->tex_data;
    mNpc_RaceData_c* race_data = &npc_race_data_tbl[info->race];
    u8* tex_p = Common_Get(add_npc_info).info[npc_id - NPC_ADD_START].texture;
    int i;

    tex_data->palette = (u16*)tex_p;
    tex_p += 16 * sizeof(u16);
    
    for (i = 0; i < aNPC_EYE_TEX_NUM; i++) {
        tex_data->eye_texture[i] = tex_p;
        tex_p += (32 * 16) / 2;
    }

    if (race_data->mouth_tex_pos >= 0) {
        for (i = 0; i < aNPC_MOUTH_TEX_NUM; i++) {
            tex_data->mouth_texture[i] = tex_p;
            tex_p += (32 * 16) / 2;
        }
    }

    tex_data->texture = tex_p;
    tex_data->eye_tex_pos = race_data->eye_tex_pos;
    tex_data->mouth_tex_pos = race_data->mouth_tex_pos;
    tex_data->cloth_tex_pos = race_data->cloth_tex_pos;
    draw_data->model_skeleton = race_data->skeleton;
    draw_data->scale = race_data->scale;
    draw_data->talk_type = race_data->talk_anm_type;
    draw_data->species_sub_idx = 0xFF;
    draw_data->umbrella_type = info->umbrella_no;
    draw_data->eye_height = race_data->eye_height;
    draw_data->voice_type = info->voice_melody;
    draw_data->col_radius = race_data->col_radius;
    draw_data->col_height = race_data->col_height;
    draw_data->accessory_type = -1;
    draw_data->accessory_joint = -1;
}

extern u8* mAN_getP_AnmAgbParam(mActor_name_t npc_id) {
    int idx = npc_id - NPC_ADD_START;

    if (idx < 0 || idx >= mAN_ANIMAL_NUM) {
        idx = 0;
    }

    return Common_Get(add_npc_info).info[idx].agb_param;
}

static mActor_name_t mAN_npc_num_2_npc_name(u8 id) {
    AnimalInfo_c* info = Common_Get(add_npc_info).info;
    int compress_info_table = Common_Get(add_npc_info.compress_info_table);
    mActor_name_t npc_id = EMPTY_NO;
    int bit = 1;
    int i;

    for (i = 0; i < mAN_ANIMAL_NUM; i++) {
        if ((compress_info_table & bit) != 0 && info->id == id) {
            npc_id = NPC_ADD_START + i;
            break;
        }

        bit <<= 1;
        info++;
    }

    return npc_id;
}

static int mAN_check_npc_regist_pwdInfoTable(u8 id) {
    mActor_name_t npc_id = mAN_npc_num_2_npc_name(id);
    int ret = FALSE;

    if (npc_id != EMPTY_NO) {
        Animal_c* animal = mNpc_GetAnimalInfoP(npc_id);

        if (animal != NULL && mNpc_GetAnimalMemoryIdx(&Now_Private->player_ID, animal->memories, ANIMAL_MEMORY_NUM) != -1) {
            ret = TRUE;
        }
    }

    return ret;
}

static int mAN_get_same_pwdInfoIdx(u8 id) {
    mPr_pwdInfo_c* pwdInfo = Now_Private->pwdInfo;
    int idx = -1;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (pwdInfo->used == TRUE && pwdInfo->card_id == id) {
            idx = i;
            break;
        }

        pwdInfo++;
    }

    return idx;
}

static int mAN_get_free_pwdInfoIdx(void) {
    mPr_pwdInfo_c* pwdInfo = Now_Private->pwdInfo;
    int idx = -1;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (pwdInfo->used == FALSE) {
            idx = i;
            break;
        }

        pwdInfo++;
    }

    return idx;
}

static void mAN_adjust_pwdInfoTable(int idx) {
    mPr_pwdInfo_c* src = &Now_Private->pwdInfo[idx + 1];
    mPr_pwdInfo_c* dst = &Now_Private->pwdInfo[idx];
    int i;

    for (i = idx; i < ANIMAL_NUM_MAX - 1; i++) {
        mem_copy((u8*)dst, (u8*)src, sizeof(mPr_pwdInfo_c));
        src++;
        dst++;
    }
}

extern void mAN_regist_pwdInfoTable(u8 id) {
    if (mAN_check_npc_regist_pwdInfoTable(id) == FALSE && mAN_get_same_pwdInfoIdx(id) == -1) {
        int idx = mAN_get_free_pwdInfoIdx();
        mPr_pwdInfo_c* pwdInfo;

        if (idx == -1) {
            // bump out the oldest entry
            mAN_adjust_pwdInfoTable(0);
            idx = 14;
        }

        pwdInfo = &Now_Private->pwdInfo[idx];
        pwdInfo->used = TRUE;
        pwdInfo->card_id = id;
    }
}

extern int mAN_check_pwdInfoTable(mActor_name_t npc_id) {
    int ret = -1;

    if (IS_NPC_ADD_NPC(npc_id)) {
        AnimalInfo_c* info = mAN_getP_animalInfo(npc_id);
        mPr_pwdInfo_c* pwdInfo;
        u8 id;
        int i;

        // @BUG - id is not initialized if info is NULL
        if (info != NULL) {
            id = info->id;
        }

        pwdInfo = Now_Private->pwdInfo;
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (pwdInfo->used == TRUE && pwdInfo->card_id == id) {
                ret = i;
                break;
            }
            pwdInfo++;
        }
    }

    return ret;
}

extern int mAN_unregist_pwdInfoTable(mActor_name_t npc_id) {
    if (IS_NPC_ADD_NPC(npc_id)) {
        int idx = mAN_check_pwdInfoTable(npc_id);

        if (idx != -1) {
            if (idx != ANIMAL_NUM_MAX - 1) {
                mAN_adjust_pwdInfoTable(idx);
            }

            bzero(&Now_Private->pwdInfo[ANIMAL_NUM_MAX - 1], sizeof(mPr_pwdInfo_c));
        }
    }

    return 0;
}
