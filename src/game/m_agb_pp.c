#include "m_agb_pp.h"
#include "lb_rtc.h"
#include "m_common_data.h"
#include "jsyswrap.h"
#include "m_font.h"
#include "m_npc.h"
#include "libultra/libultra.h"
#include "m_field_make.h"

static u8 mAP_add_npc_data_uncompress_common[0x4000];

static int mAP_get_sunday_index(lbRTC_time_c* time) {
    int i;
    int days;

    days = time->day - 1;
    for (i = 2003; i < time->year; i++) {
        days += lbRTC_IS_LEAPYEAR(i) ? lbRTC_DAYS_PER_LEAP_YEAR : lbRTC_DAYS_PER_YEAR;
    }

    for (i = lbRTC_JANUARY; i < time->month; i++) {
        days += lbRTC_GetDaysByMonth(time->year, (lbRTC_month_t)i);
    }

    return (days / lbRTC_WEEK) % mAP_GAME_NUM;
}

extern void mAP_decide_today_agb_game(void) {
    lbRTC_time_c rtc = Common_Get(time.rtc_time);
    int game;

    switch (rtc.weekday) {
        case lbRTC_MONDAY:
        case lbRTC_THURSDAY:
            game = mAP_GAME_DARUMASANGAKORONDA;
            break;
        case lbRTC_TUESDAY:
        case lbRTC_FRIDAY:
            game = mAP_GAME_DONJANKEN;
            break;
        case lbRTC_WEDNESDAY:
        case lbRTC_SATURDAY:
            game = mAP_GAME_NAKADOJJI;
            break;
        default:
            game = mAP_get_sunday_index(&rtc);
            break;
    }

    JW_Set_request_type_AgbProg(game & 3);
}

static u8* mAP_get_npc_name_string_p(mActor_name_t npc_name) {
    static u8 name_str[ANIMAL_NAME_LEN];

    if (IS_NPC_ADD_NPC(npc_name)) {
        int idx = npc_name - NPC_ADD_START;

        mFont_CopyStrings(name_str, Common_Get(add_npc_info).info[idx].name, ANIMAL_NAME_LEN);
    } else {
        u8* src = mNpc_GetNpcWorldNameP(npc_name);

        if (src != NULL) {
            mFont_CopyStrings(name_str, src, ANIMAL_NAME_LEN);
        } else {
            src = mNpc_GetNpcWorldNameP(NPC_START);
            mFont_CopyStrings(name_str, src, ANIMAL_NAME_LEN);
        }
    }

    return name_str;
}

static u16 mAP_get_npc_distinguish(mActor_name_t npc_name) {
    u16 distinguish;

    if (IS_NPC_ADD_NPC(npc_name)) {
        int idx = npc_name - NPC_ADD_START;

        distinguish = Common_Get(add_npc_info).info[idx].id;
    } else {
        distinguish = npc_name;
    }

    return distinguish;
}

static u8* mAP_get_rom_npc_agb_head_chara_data_p(mActor_name_t npc_name) {
    u8* ret;

    if (ITEM_NAME_GET_TYPE(npc_name) == NAME_TYPE_NPC && (npc_name & 0xFFF) < NPC_ROM_NUM) {
        int idx = npc_name & 0xFFF;
        ret = (u8*)(JW_Get_AgbTargetNpcHead_InAgbArchiveFile0_data_p() + idx * 0x800);
    } else {
        ret = NULL;
    }

    return ret;
}

static u8* mAP_get_npc_agb_head_chara_data_p(mActor_name_t npc_name) {
    if (IS_NPC_ADD_NPC(npc_name)) {
        int idx = npc_name - NPC_ADD_START;

        if ((Save_Get(add_npc).save.regist_add_npc >> idx) & 1) {
            decode_szs(Save_Get(add_npc).save.add_npc_compress_info_table[idx], mAP_add_npc_data_uncompress_common);
            return mAP_add_npc_data_uncompress_common + 0x25;
        }
    }

    return mAP_get_rom_npc_agb_head_chara_data_p(npc_name);
}

static u16* mAP_get_rom_npc_agb_pal_data_p(mActor_name_t npc_name) {
    if (ITEM_NAME_GET_TYPE(npc_name) == NAME_TYPE_NPC && (npc_name & 0xFFF) < NPC_ROM_NUM) {
        int idx = npc_name & 0xFFF;
        return (u16*)(JW_Get_AgbTargetNpcPal_InAgbArchiveFile0_data_p() + idx * 0x20);
    }

    return NULL;
}

static u16* mAP_get_npc_agb_pal_data_p(mActor_name_t npc_name) {
    if (IS_NPC_ADD_NPC(npc_name)) {
        u8* head_chara_data_p = mAP_get_npc_agb_head_chara_data_p(npc_name);

        return (u16*)(head_chara_data_p + 0x800);
    }

    return mAP_get_rom_npc_agb_pal_data_p(npc_name);
}

static u8* mAP_get_rom_npc_agb_body_chara_data_p(mActor_name_t npc_name) {
    if (ITEM_NAME_GET_TYPE(npc_name) == NAME_TYPE_NPC && (npc_name & 0xFFF) < NPC_ROM_NUM) {
        int idx = npc_name & 0xFFF;
        int body_type = npc_def_list[idx].agb_body_type & 31;
        return (u8*)(JW_Get_AgbTargetNpcBody_InAgbArchiveFile0_data_p() + body_type * 0x800);
    }

    return NULL;
}

static u8* mAP_get_npc_agb_body_chara_data_p(mActor_name_t npc_name) {
    if (IS_NPC_ADD_NPC(npc_name)) {
        int idx = npc_name - NPC_ADD_START;
        int body_type = Common_Get(add_npc_info).info[idx].race & 31;

        return (u8*)(JW_Get_AgbTargetNpcBody_InAgbArchiveFile0_data_p() + body_type * 0x800);
    }

    return mAP_get_rom_npc_agb_body_chara_data_p(npc_name);
}

static u8* mAP_get_player_agb_head_chara_data_p(s8 sex, s8 face) {
    return (u8*)(JW_Get_AgbTargetPlayerHead_InAgbArchiveFile0_data_p() + (s8)(sex & 1) * 0x4000 +
                 (s8)(face & 7) * 0x800);
}

static u8* mAP_get_player_agb_body_chara_data_p(s8 sex) {
    return (u8*)(JW_Get_AgbTargetPlayerBody_InAgbArchiveFile0_data_p() + (s8)(sex & 1) * 0x800);
}

static u16* mAP_get_player_agb_pal_data_p(s8 gender, s8 face) {
    return (u16*)(JW_Get_AgbTargetPlayerPal_InAgbArchiveFile0_data_p() + (s8)(gender & 1) * 0x100 +
                  (s8)(face & 7) * 0x20);
}

extern int mAP_select_agb_game_npc(mActor_name_t* npc_name_tbl, int count) {
    Animal_c* animal;
    Animal_c* animals;
    int max;
    u32 sel_bitfield;
    int picked_count;
    int i;
    int j;
    int sel;
    int check_count;

    animals = Save_Get(animals);
    max = mNpc_GetAnimalNum();
    sel_bitfield = 0;
    picked_count = 0;

    for (i = 0; i < count; i++) {
        sel = RANDOM(max);
        check_count = 0;

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            animal = &animals[j];

            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE && ((sel_bitfield >> j) & 1) == 0) {
                if (sel == check_count) {
                    max--;
                    sel_bitfield |= (1 << j);
                    npc_name_tbl[i] = animal->id.npc_id;
                    picked_count++;
                    break;
                }

                check_count++;
            }
        }
    }

    return picked_count == count;
}

extern u32 mAP_make_send_data(u8* buf, mActor_name_t npc0_name, mActor_name_t npc1_name, mActor_name_t npc2_name,
                              mActor_name_t npc3_name, mActor_name_t npc4_name, int sex, int face, PersonalID_c* pid) {
    u8* buf_start_p = buf;
    u8 param_buf[8];
    u16 distinguish;
    u32 size;

    bcopy(mAP_get_npc_agb_head_chara_data_p(npc0_name), buf, 0x800);
    bcopy(mAP_get_npc_agb_body_chara_data_p(npc0_name), buf + 0x800, 0x800);
    bcopy(mAP_get_npc_agb_head_chara_data_p(npc1_name), buf + 0x1000, 0x800);
    bcopy(mAP_get_npc_agb_body_chara_data_p(npc1_name), buf + 0x1800, 0x800);
    bcopy(mAP_get_npc_agb_head_chara_data_p(npc2_name), buf + 0x2000, 0x800);
    bcopy(mAP_get_npc_agb_body_chara_data_p(npc2_name), buf + 0x2800, 0x800);
    bcopy(mAP_get_npc_agb_head_chara_data_p(npc3_name), buf + 0x3000, 0x800);
    bcopy(mAP_get_npc_agb_body_chara_data_p(npc3_name), buf + 0x3800, 0x800);
    bcopy(mAP_get_npc_agb_head_chara_data_p(npc4_name), buf + 0x4000, 0x800);
    bcopy(mAP_get_npc_agb_body_chara_data_p(npc4_name), buf + 0x4800, 0x800);
    bcopy(mAP_get_player_agb_head_chara_data_p(sex, face), buf + 0x5000, 0x800);
    bcopy(mAP_get_player_agb_body_chara_data_p(sex), buf + 0x5800, 0x800);
    bcopy(mAP_get_npc_agb_pal_data_p(npc0_name), buf + 0x6000, 0x20);
    bcopy(mAP_get_npc_agb_pal_data_p(npc1_name), buf + 0x6020, 0x20);
    bcopy(mAP_get_npc_agb_pal_data_p(npc2_name), buf + 0x6040, 0x20);
    bcopy(mAP_get_npc_agb_pal_data_p(npc3_name), buf + 0x6060, 0x20);
    bcopy(mAP_get_npc_agb_pal_data_p(npc4_name), buf + 0x6080, 0x20);
    bcopy(mAP_get_player_agb_pal_data_p(sex, face), buf + 0x60A0, 0x20);
    mNpc_get_npc_param(param_buf, npc0_name);
    bcopy(param_buf, buf + 0x60C0, 8);
    mNpc_get_npc_param(param_buf, npc1_name);
    bcopy(param_buf, buf + 0x60C8, 8);
    mNpc_get_npc_param(param_buf, npc2_name);
    bcopy(param_buf, buf + 0x60D0, 8);
    mNpc_get_npc_param(param_buf, npc3_name);
    bcopy(param_buf, buf + 0x60D8, 8);
    mNpc_get_npc_param(param_buf, npc4_name);
    bcopy(param_buf, buf + 0x60E0, 8);

    buf = mAP_set_world_info4(buf + 0x60E8);
    mFont_CopyStrings(buf, mAP_get_npc_name_string_p(npc0_name), ANIMAL_NAME_LEN);
    mFont_CopyStrings(buf + ANIMAL_NAME_LEN, mAP_get_npc_name_string_p(npc1_name), ANIMAL_NAME_LEN);
    mFont_CopyStrings(buf + ANIMAL_NAME_LEN * 2, mAP_get_npc_name_string_p(npc2_name), ANIMAL_NAME_LEN);
    mFont_CopyStrings(buf + ANIMAL_NAME_LEN * 3, mAP_get_npc_name_string_p(npc3_name), ANIMAL_NAME_LEN);
    mFont_CopyStrings(buf + ANIMAL_NAME_LEN * 4, mAP_get_npc_name_string_p(npc4_name), ANIMAL_NAME_LEN);
    mFont_CopyStrings(buf + ANIMAL_NAME_LEN * 5, Now_Private->player_ID.player_name, PLAYER_NAME_LEN);

    distinguish = mAP_get_npc_distinguish(npc0_name);
    bcopy(&distinguish, buf + ANIMAL_NAME_LEN * 5 + PLAYER_NAME_LEN, sizeof(u16));
    distinguish = mAP_get_npc_distinguish(npc1_name);
    bcopy(&distinguish, buf + ANIMAL_NAME_LEN * 5 + PLAYER_NAME_LEN + sizeof(u16), sizeof(u16));
    distinguish = mAP_get_npc_distinguish(npc2_name);
    bcopy(&distinguish, buf + ANIMAL_NAME_LEN * 5 + PLAYER_NAME_LEN + sizeof(u16) * 2, sizeof(u16));
    distinguish = mAP_get_npc_distinguish(npc3_name);
    bcopy(&distinguish, buf + ANIMAL_NAME_LEN * 5 + PLAYER_NAME_LEN + sizeof(u16) * 3, sizeof(u16));
    distinguish = mAP_get_npc_distinguish(npc4_name);
    bcopy(&distinguish, buf + ANIMAL_NAME_LEN * 5 + PLAYER_NAME_LEN + sizeof(u16) * 4, sizeof(u16));
    bcopy(pid, buf + ANIMAL_NAME_LEN * 5 + PLAYER_NAME_LEN + sizeof(u16) * 5, sizeof(PersonalID_c));
    size =
        ((u32)buf + ANIMAL_NAME_LEN * 5 + PLAYER_NAME_LEN + sizeof(u16) * 5 + sizeof(PersonalID_c)) - (u32)buf_start_p;
    return ALIGN_PREV(size + 4, 4);
}

extern int mAP_receive_data_to_agb_game_type(u8* data) {
    return data[0x3E];
}

extern int mAP_receive_data_to_agb_game_result(u8* data) {
    return data[0x3F] & 7;
}

extern void mAP_receive_data_to_agb_friendship(s8* npc0_friendship, s8* npc1_friendship, s8* npc2_friendship,
                                               s8* npc3_friendship, s8* npc4_friendship, u8* data) {
    *npc0_friendship = data[0x40];
    *npc1_friendship = data[0x41];
    *npc2_friendship = data[0x42];
    *npc3_friendship = data[0x43];
    *npc4_friendship = data[0x44];
}

extern void mAP_receive_data_to_agb_npc_name(u8* dst, u8* data, int idx) {
    mFont_CopyStrings(dst, data + idx * ANIMAL_NAME_LEN, ANIMAL_NAME_LEN);
}

extern void mAP_receive_data_to_agb_distinguish(u16* npc0_distinguish, u16* npc1_distinguish, u16* npc2_distinguish,
                                                u16* npc3_distinguish, u16* npc4_distinguish, u8* data) {
    bcopy(data + 0x24, npc0_distinguish, sizeof(u16));
    bcopy(data + 0x26, npc1_distinguish, sizeof(u16));
    bcopy(data + 0x28, npc2_distinguish, sizeof(u16));
    bcopy(data + 0x2A, npc3_distinguish, sizeof(u16));
    bcopy(data + 0x2C, npc4_distinguish, sizeof(u16));
}

extern void mAP_receive_data_to_agb_personalID(PersonalID_c* pid, u8* data) {
    bcopy(data + 0x2E, pid, sizeof(PersonalID_c));
}

extern int mAP_receive_data_to_update_already(u8* data) {
    return data[0x45] != 0;
}

extern int mAP_receive_data_to_topic_npc_receive_index(u8* data) {
    int idx = data[0x46];
    int npc_num = mAP_agb_game_type_to_npc_num(mAP_receive_data_to_agb_game_type(data));

    return idx < npc_num ? idx : 0;
}

extern int mAP_agb_game_type_to_npc_num(int game_type) {
    static int agb_game_npc_num[] = { 4, 5, 5 };

    return agb_game_npc_num[game_type & 3];
}

extern u8* mAP_set_world_info4(u8* buf) {
    int pal;

    if (Common_Get(time.bgitem_profile) == mAc_PROFILE_BGCHERRYITEM) {
        pal = 12;
    } else {
        pal = mFM_GetBgPalIdx() % 12;
    }
    buf[0] = pal;
    buf[1] = Save_Get(bg_tex_idx) % mFM_BG_TEX_NUM;
    buf[2] = Common_Get(time.season) == mTM_SEASON_WINTER;
    buf[3] = 0;
    return buf + 4;
}
