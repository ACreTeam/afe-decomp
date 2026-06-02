#include "ac_quest_talk_greeting.h"

#include "m_common_data.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_string.h"

enum {
    aQMgr_FEEL_RAGE,
    aQMgr_FEEL_SAD,
    aQMgr_FEEL_SLEEP,
    aQMgr_FEEL_4,
    aQMgr_FEEL_5,
    aQMgr_FEEL_UZAI,
    aQMgr_FEEL_UZA2,

    aQMgr_FEEL_NUM
};

enum {
    aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO,             // first meeting
    aQMgr_MEET_TIME_HELLO_AGAIN,                     // more than first time spoken to today
    aQMgr_MEET_TIME_FIRST_HELLO,                     // first time spoken to today
    aQMgr_MEET_TIME_A_LONG_TIME,                     // first time spoken to 'in a long time'
    aQMgr_MEET_TIME_A_REALLY_LONG_TIME,              // first time spoken to 'in a really long time'
    aQMgr_MEET_TIME_FIRST_HELLO_FOREIGN_TOWN,        // first time spoken to today in a foreign town
    aQMgr_MEET_TIME_A_LONG_TIME_FOREIGN_TOWN,        // first time spoken to 'in a long time' in a foreign town
    aQMgr_MEET_TIME_A_REALLY_LONG_TIME_FOREIGN_TOWN, // first time spoken to 'in a really long time' in a foreign town

    aQMgr_MEET_TIME_NUM
};

enum {
    aQMgr_RANDOM_STRING_TYPE_FREE,
    aQMgr_RANDOM_STRING_TYPE_ITEM,

    aQMgr_RANDOM_STRING_TYPE_NUM
};

typedef struct idx_group_s {
    int lower_bound;
    int upper_bound;
} aQMgr_idx_group_c;

typedef struct idx_group_msg_s {
    int** msg_tbl;
    aQMgr_idx_group_c** idx_group_tbl;
} aQMgr_idx_group_msg_c;

typedef struct def_str_s {
    int str_type;
    int str_no;
    int type;
} aQMgr_def_str_c;

enum {
    aQMgr_STR_TYPE_FISH,
    aQMgr_STR_TYPE_INSECT,
    aQMgr_STR_TYPE_SPORTS,
    aQMgr_STR_TYPE_FOOD,
    aQMgr_STR_TYPE_DRINKS,
    aQMgr_STR_TYPE_COLORS,
    aQMgr_STR_TYPE_PLACES,
    aQMgr_STR_TYPE_GAMES,
    aQMgr_STR_TYPE_BOOKS,
    aQMgr_STR_TYPE_SWEETS,
    aQMgr_STR_TYPE_HOUSEHOLD_ITEMS,

    aQMgr_STR_TYPE_NUM
};

static int l_hello_fine_msg_tbl[8] = {
    0x04BD, 0x054D, 0x0505, 0x05DD, 0x066D, 0x0595, 0x0625, 0x06B5,
};

static aQMgr_idx_group_c l_hello_fine_idx_tbl[8] = {
    {0x0006, 0x0009},
    {0x006B, 0x006E},
    {0x003E, 0x0041},
    {0x0041, 0x0044},
    {0x0044, 0x0047},
    {0x0047, 0x004A},
    {0x004A, 0x004D},
    {0x004D, 0x0050},
};

static int l_hello_fine_island_msg_tbl[8] = {
    0x3458, 0x3507, 0x34EF, 0x354F, 0x354F, 0x354F, 0x354F, 0x354F,
};

static aQMgr_idx_group_c l_hello_fine_island_idx_tbl[8] = {
    {0x00FD, 0x00FE},
    {0x00FE, 0x0101},
    {0x0101, 0x0102},
    {0x0102, 0x0103},
    {0x0102, 0x0103},
    {0x0102, 0x0103},
    {0x0102, 0x0103},
    {0x0102, 0x0103},
};

static int l_hello_rain_msg_tbl[8] = {
    0x04BD, 0x0C1B, 0x0BD3, 0x05DD, 0x066D, 0x0595, 0x0625, 0x06B5,
};

static aQMgr_idx_group_c l_hello_rain_idx_tbl[8] = {
    {0x0006, 0x0009},
    {0x0071, 0x0074},
    {0x0053, 0x0056},
    {0x0041, 0x0044},
    {0x0044, 0x0047},
    {0x0047, 0x004A},
    {0x004A, 0x004D},
    {0x004D, 0x0050},
};

static int l_hello_snow_msg_tbl[8] = {
    0x04BD, 0x0CAB, 0x0C63, 0x05DD, 0x066D, 0x0595, 0x0625, 0x06B5,
};

static aQMgr_idx_group_c l_hello_snow_idx_tbl[8] = {
    {0x0006, 0x0009},
    {0x0074, 0x0077},
    {0x0056, 0x0059},
    {0x0041, 0x0044},
    {0x0044, 0x0047},
    {0x0047, 0x004A},
    {0x004A, 0x004D},
    {0x004D, 0x0050},
};

static int l_grad_hello_msg_tbl[8] = {
    0x1224, 0x12B4, 0x126C, 0x126C, 0x126C, 0x126C, 0x126C, 0x126C,
};

static aQMgr_idx_group_c l_grad_hello_idx_tbl[8] = {
    {0x000F, 0x0012},
    {0x006E, 0x0071},
    {0x0050, 0x0053},
    {0x0050, 0x0053},
    {0x0050, 0x0053},
    {0x0050, 0x0053},
    {0x0050, 0x0053},
    {0x0050, 0x0053},
};

static int l_indoor_hello_msg_tbl[8] = {
    0x20D4, 0x226C, 0x2224, 0x22FC, 0x22B4, 0x21DC, 0x2194, 0x214C,
};

static aQMgr_idx_group_c l_indoor_hello_idx_tbl[8] = {
    {0x0012, 0x0015},
    {0x0077, 0x007A},
    {0x0059, 0x005C},
    {0x005C, 0x005F},
    {0x005F, 0x0062},
    {0x0068, 0x006B},
    {0x0062, 0x0065},
    {0x0065, 0x0068},
};

static int l_hello_rage_msg[6] = {
    0x0CF3, 0x0CF8, 0x0CFD, 0x0D02, 0x0D07, 0x0D0C
};

static aQMgr_idx_group_c l_hello_rage_idx[1] = {{0x001E, 0x0023}};

static int l_hello_rage_island_msg[6] = {
    0x3476, 0x3479, 0x347C, 0x347F, 0x3482, 0x3485
};

static aQMgr_idx_group_c l_hello_rage_island_idx[1] = {{0x0103, 0x0106}};

static int l_hello_sad_msg[6] = {
    0x0D11, 0x0D16, 0x0D1B, 0x0D20, 0x0D25, 0x0D2A
};

static aQMgr_idx_group_c l_hello_sad_idx[1] = {{0x0023, 0x0028}};

static int l_hello_sad_island_msg[6] = {
    0x3488, 0x348B, 0x348E, 0x3491, 0x3494, 0x3497
};

static aQMgr_idx_group_c l_hello_sad_island_idx[1] = {{0x0106, 0x0109}};

static int l_hello_sleep_msg[6] = {
    0x0D2F, 0x0D34, 0x0D39, 0x0D3E, 0x0D43, 0x0D48
};

static aQMgr_idx_group_c l_hello_sleep_idx[1] = {{0x0028, 0x002D}};

static int l_hello_uzai_msg[6] = {
    0x2E7D, 0x2E88, 0x2E78, 0x2E93, 0x2E98, 0x2EA3
};

static aQMgr_idx_group_c l_hello_uzai_idx[1] = {{0x002D, 0x0032}};

static int l_hello_uzai_island_msg[6] = {
    0x349A, 0x349D, 0x34A0, 0x34A3, 0x34A6, 0x34A9
};

static aQMgr_idx_group_c l_hello_uzai_island_idx[1] = {{0x0109, 0x010C}};

static int* l_normal_talk_feel_msg_table[7] = {
    l_hello_rage_msg, l_hello_sad_msg, l_hello_sleep_msg, NULL, NULL, l_hello_uzai_msg, l_hello_uzai_msg
};

static aQMgr_idx_group_c* l_normal_talk_feel_idx_table[7] = {
    l_hello_rage_idx, l_hello_sad_idx, l_hello_sleep_idx, NULL, NULL, l_hello_uzai_idx, l_hello_uzai_idx
};

static int* l_island_talk_feel_msg_table[7] = {
    l_hello_rage_island_msg, l_hello_sad_island_msg, l_hello_sleep_msg, NULL, NULL, l_hello_uzai_island_msg, l_hello_uzai_island_msg
};

static aQMgr_idx_group_c* l_island_talk_feel_idx_table[7] = {
    l_hello_rage_island_idx, l_hello_sad_island_idx, l_hello_sleep_idx, NULL, NULL, l_hello_uzai_island_idx, l_hello_uzai_island_idx
};

static aQMgr_idx_group_msg_c l_talk_feel_msg_table[2] = {
    {l_normal_talk_feel_msg_table, l_normal_talk_feel_idx_table},
    {l_island_talk_feel_msg_table, l_island_talk_feel_idx_table},
};

static int l_q005_aisatu_msg[6] = {
    0x4450, 0x445C, 0x4468, 0x4474, 0x4480, 0x448C
};

#if 0
// clang-format off
static int l_hello_fine_msg_tbl[] = { MSG_1213, MSG_1357, MSG_1285, MSG_1501, MSG_1645, MSG_1429, MSG_1573, MSG_1717 };
static int l_hello_fine_island_msg_tbl[] = { MSG_13400, MSG_13575, MSG_13551, MSG_13647, MSG_13647, MSG_13647, MSG_13647, MSG_13647 };
static int l_hello_rain_msg_tbl[] = { MSG_1213, MSG_3099, MSG_3027, MSG_1501, MSG_1645, MSG_1429, MSG_1573, MSG_1717 };
static int l_hello_snow_msg_tbl[] = { MSG_1213, MSG_3243, MSG_3171, MSG_1501, MSG_1645, MSG_1429, MSG_1573, MSG_1717 };
static int l_grad_hello_msg_tbl[] = { MSG_4644, MSG_4788, MSG_4716, MSG_4716, MSG_4716, MSG_4716, MSG_4716, MSG_4716 };
static int l_indoor_hello_msg_tbl[] = { MSG_8404, MSG_8812, MSG_8740, MSG_8956, MSG_8884, MSG_8668, MSG_8596, MSG_8524 };

static int l_hello_rage_msg[] = { MSG_3315, MSG_3320, MSG_3325, MSG_3330, MSG_3335, MSG_3340 };
static int l_hello_rage_island_msg[] = { MSG_13430, MSG_13433, MSG_13436, MSG_13439, MSG_13442, MSG_13445 };
static int l_hello_sad_msg[] = { MSG_3345, MSG_3350, MSG_3355, MSG_3360, MSG_3365, MSG_3370 };
static int l_hello_sad_island_msg[] = { MSG_13448, MSG_13451, MSG_13454, MSG_13457, MSG_13460, MSG_13463 };
static int l_hello_sleep_msg[] = { MSG_3375, MSG_3380, MSG_3385, MSG_3390, MSG_3395, MSG_3400 };
static int l_hello_uzai_msg[] = { MSG_11901, MSG_11912, MSG_11896, MSG_11923, MSG_11928, MSG_11939 };
static int l_hello_uzai_island_msg[] = { MSG_13466, MSG_13469, MSG_13472, MSG_13475, MSG_13478, MSG_13481 };
// clang-format on
#endif

static void aQMgr_actor_set_day_str(int day, int str_no) {
    if (day >= 0) {
        u8 str[mMsg_FREE_STRING_LEN];

        mFont_UnintToString(str, sizeof(str), day, 10, TRUE, FALSE, FALSE);
        mMsg_Set_free_str(mMsg_Get_base_window_p(), str_no, str, sizeof(str));
    }
}

static int aQMgr_actor_get_my_hello_msg_com(aQMgr_GET_TIME_KIND_PROC get_time_kind_proc, int base_msg, int looks,
                                            int hour, int kind_count) {
    int msg_no = base_msg + looks * kind_count * 4;
    int time_kind = (*get_time_kind_proc)(hour);

    msg_no += time_kind * kind_count;
    msg_no += mQst_GetRandom(kind_count);
    return msg_no;
}

static int aQMgr_actor_get_my_hello_msg_new(aQMgr_GET_TIME_KIND_PROC get_time_kind_proc, int base_msg, int looks, int hour, int lower_bound, int upper_bound) {
    int msg_no;
    int kind_count;
    int time_kind;

    kind_count = upper_bound - lower_bound;
    msg_no = base_msg + looks * kind_count * 4;
    time_kind = (*get_time_kind_proc)(hour);
    msg_no += time_kind * kind_count;
    msg_no += mQst_GetIdxTalkSelect(lower_bound, upper_bound, looks);
    return msg_no;
}

static int aQMgr_get_random_msg_no(int base_msg, int looks, int kind_count) {
    int msg_no = base_msg + mQst_GetRandom(kind_count) + looks * kind_count;

    return msg_no;
}

static int aQMgr_get_random_msg_no_new(int base_msg, int looks, int lower_bound, int upper_bound) {
    int msg_no;
    int kind_count;

    kind_count = upper_bound - lower_bound;
    msg_no = base_msg + looks * kind_count + mQst_GetIdxTalkSelect(lower_bound, upper_bound, looks);
    return msg_no;
}

static void aQMgr_clear_memory(Animal_c* animal, Anmmem_c* memory) {
    PersonalID_c* pid = &Now_Private->player_ID;

    if (memory != NULL) {
        int mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

        if (mem_idx != -1) {
            memory += mem_idx;

            if (mNpc_CheckIslandAnimal(animal) == TRUE) {
                mNpc_ClearIslandAnimalMemory(memory, 1);
            } else {
                mNpc_ClearAnimalMemory(memory, 1);
            }
        }
    }
}

static int aQMgr_get_comp_fish_and_insect_msg(mNpc_NpcList_c* npclist, int looks) {
    static int msg_table[] = { MSG_10700, MSG_10718 };
    static int msg_idx[][2] = { { 21, 24 }, { 24, 27 } };
    int rnd = mQst_GetRandom(4);
    int msg_no = aQMgr_get_random_msg_no_new(msg_table[rnd & 1], looks, msg_idx[rnd & 1][0], msg_idx[rnd & 1][1]);

    if ((rnd & 1) == 0) {
        mNpc_SetInsectCompleteTalk(npclist);
        mPr_SetInsectCompleteTalk();
    } else {
        mNpc_SetFishCompleteTalk(npclist);
        mPr_SetFishCompleteTalk();
    }

    npclist->conversation_flags.beesting = FALSE;
    return msg_no;
}

static int aQMgr_get_comp_fish_msg(mNpc_NpcList_c* npclist, int looks) {
    int msg_no = aQMgr_get_random_msg_no_new(MSG_10718, looks, 24, 27);
    
    mNpc_SetFishCompleteTalk(npclist);
    mPr_SetFishCompleteTalk();
    npclist->conversation_flags.beesting = FALSE;
    return msg_no;
}

static int aQMgr_get_comp_insect_msg(mNpc_NpcList_c* npclist, int looks) {
    int msg_no = aQMgr_get_random_msg_no_new(MSG_10700, looks, 21, 24);
    
    mNpc_SetInsectCompleteTalk(npclist);
    mPr_SetInsectCompleteTalk();
    npclist->conversation_flags.beesting = FALSE;
    return msg_no;
}

static int aQMgr_get_bee_msg(mNpc_NpcList_c* npclist, int looks, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc) {
    int msg_no = aQMgr_actor_get_my_hello_msg_new(get_time_kind_proc, MSG_6987, looks, Common_Get(time.rtc_time.hour), 27, 30);

    npclist->conversation_flags.beesting = FALSE;
    return msg_no;
}

static int aQMgr_get_honey_chase_msg(NPC_ACTOR* nactorx, int meet_time_type) {
    Animal_c* animal = nactorx->npc_info.animal_orig;
    mNpc_NpcList_c* npclist = nactorx->npc_info.list;
    int looks = mNpc_GetNpcLooks((ACTOR*)nactorx);
    int msg_no = aQMgr_get_random_msg_no_new(MSG_10988, looks, 3, 6);

    if (meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        aQMgr_clear_memory(animal, animal->memories);
    }

    npclist->conversation_flags.beesting = FALSE;
    return msg_no;
}

static int aQMgr_get_hello_msg_npc_feel(int feel, int looks, int island_msg_flag) {
    aQMgr_idx_group_msg_c* talk_feel_msg_table_p;
    int* feel_msg_tbl_p;
    aQMgr_idx_group_c* feel_idx_tbl_p;
    int rng_msg;
    int msg_no;

    feel -= mNpc_FEEL_ANGRY; // Remove happy & normal

    if (feel < 0 || feel >= aQMgr_FEEL_NUM) {
        feel = 0;
    }

    talk_feel_msg_table_p = &l_talk_feel_msg_table[island_msg_flag];
    feel_msg_tbl_p = talk_feel_msg_table_p->msg_tbl[feel];
    feel_idx_tbl_p = talk_feel_msg_table_p->idx_group_tbl[feel];
    if (feel_msg_tbl_p == NULL) {
        feel_msg_tbl_p = l_hello_rage_msg;
        feel_idx_tbl_p = l_hello_rage_idx;
    }

    rng_msg = mQst_GetIdxTalkSelect(feel_idx_tbl_p->lower_bound, feel_idx_tbl_p->upper_bound, looks);
    msg_no = rng_msg + feel_msg_tbl_p[looks];
    return msg_no;
}

static void aQMgr_set_random_string(int str_no, int base_str, float str_count, int str_type) {
    u8 str[mMsg_FREE_STRING_LEN];
    int str_idx = base_str + RANDOM(str_count);

    mString_Load_StringFromRom(str, mMsg_FREE_STRING_LEN, str_idx);
    switch (str_type) {
        case aQMgr_RANDOM_STRING_TYPE_FREE:
            mMsg_SET_FREE_STR(str_no, str, mMsg_FREE_STRING_LEN);
            break;
        case aQMgr_RANDOM_STRING_TYPE_ITEM:
            mMsg_SET_ITEM_STR(str_no, str, mMsg_FREE_STRING_LEN);
            break;
    }
}

static void aQMgr_set_default_string(aQMgr_def_str_c* def_str, int count) {
    static int base_str_num[] = {
        0x06A1, // aQMgr_STR_TYPE_FISH
        0x0679, // aQMgr_STR_TYPE_INSECT
        0x0334, // aQMgr_STR_TYPE_SPORTS
        0x0314, // aQMgr_STR_TYPE_FOOD
        0x0414, // aQMgr_STR_TYPE_DRINKS
        0x0434, // aQMgr_STR_TYPE_COLORS
        0x0464, // aQMgr_STR_TYPE_PLACES
        0x02F4, // aQMgr_STR_TYPE_GAMES
        0x04A0, // aQMgr_STR_TYPE_BOOKS
        0x0760, // aQMgr_STR_TYPE_SWEETS
        0x07A3, // aQMgr_STR_TYPE_HOUSEHOLD_ITEMS
    };

    for (; count != 0; count--) {
        int type = def_str->type;

        if (type < 0 || type >= aQMgr_STR_TYPE_NUM) {
            type = 0;
        }

        aQMgr_set_random_string(def_str->str_no, base_str_num[type], 32, def_str->str_type);
        def_str++;
    }
}

typedef struct month_day_s {
    lbRTC_month_t month;
    lbRTC_day_t day;
} aQMgr_month_day_c;

static void aQMgr_set_constellation_string(int str_type, int str_no) {
    static aQMgr_month_day_c constellation_table[lbRTC_MONTHS_MAX] = {
        {lbRTC_JANUARY, 19},
        {lbRTC_FEBRUARY, 18},
        {lbRTC_MARCH, 20},
        {lbRTC_APRIL, 19},
        {lbRTC_MAY, 20},
        {lbRTC_JUNE, 21},
        {lbRTC_JULY, 22},
        {lbRTC_AUGUST, 22},
        {lbRTC_SEPTEMBER, 22},
        {lbRTC_OCTOBER, 23},
        {lbRTC_NOVEMBER, 21},
        {lbRTC_DECEMBER, 21},
    };

    u8 str[mMsg_FREE_STRING_LEN];
    mPr_birthday_c* birthday_p = &Now_Private->birthday;
    aQMgr_month_day_c* constellation_p = constellation_table;
    int constellation = 0;
    int i;

    for (i = 0; i < ARRAY_COUNT(constellation_table); i++) {
        if (birthday_p->month < constellation_p->month || (birthday_p->month == constellation_p->month && birthday_p->day <= constellation_p->day)) {
            constellation = i;
            break;
        }

        constellation_p++;
    }

    constellation -= 3;
    if (constellation < 0) {
        constellation += lbRTC_MONTHS_MAX;
    }

    mString_Load_StringFromRom(str, sizeof(str), 0x494 + constellation);

    switch (str_type) {
        case aQMgr_RANDOM_STRING_TYPE_FREE:
            mMsg_SET_FREE_STR(str_no, str, sizeof(str));
            break;
        case aQMgr_RANDOM_STRING_TYPE_ITEM:
            mMsg_SET_ITEM_STR(str_no, str, sizeof(str));
            break;
    }
}

static int aQMgr_get_hello_msg_npc_feel_group_talk(int speaker_feel, int speaker_looks, int listener_looks, Animal_c* speaker_animal, Animal_c* listener_animal, NPC_ACTOR* speak_nactorx, NPC_ACTOR* listen_nactorx) {
    static int good_msg_tbl[mNpc_LOOKS_NUM] = {0x451F, 0x48FD, 0x4D8F, 0x4759, 0x45F1, 0x4D03};
    static int normal_msg_tbl[mNpc_LOOKS_NUM] = {0x4565, 0x4989, 0x4C77, 0x47E5, 0x4637, 0x4E1B};
    static int bad_msg_tbl[mNpc_LOOKS_NUM] = {0x45AB, 0x4A15, 0x4EA7, 0x4871, 0x467D, 0x4F33};
    static aQMgr_def_str_c def_str[11] = {
        {aQMgr_RANDOM_STRING_TYPE_FREE, 2, aQMgr_STR_TYPE_FISH},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 3, aQMgr_STR_TYPE_INSECT},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 4, aQMgr_STR_TYPE_SPORTS},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 5, aQMgr_STR_TYPE_FOOD},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 6, aQMgr_STR_TYPE_DRINKS},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 7, aQMgr_STR_TYPE_COLORS},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 8, aQMgr_STR_TYPE_PLACES},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 9, aQMgr_STR_TYPE_GAMES},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 10, aQMgr_STR_TYPE_BOOKS},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 12, aQMgr_STR_TYPE_SWEETS},
        {aQMgr_RANDOM_STRING_TYPE_FREE, 13, aQMgr_STR_TYPE_HOUSEHOLD_ITEMS},
    };
    mMsg_Window_c* msg_p;
    int base_msg_no;
    int lower_idx;
    int upper_idx;
    int idx;
    int relation;
    int msg_no = -1;

    switch (speaker_feel) {
        case mNpc_FEEL_NORMAL:
        case mNpc_FEEL_HAPPY: {
            relation = mNpc_GetRelationAnimal(speaker_animal, listener_animal);

            switch (relation) {
                case mNpc_RELATION_LOVE:
                case mNpc_RELATION_LIKE:
                    base_msg_no = good_msg_tbl[speaker_looks];
                    lower_idx = 239;
                    upper_idx = 242;
                    break;

                case mNpc_RELATION_NORMAL:
                    base_msg_no = normal_msg_tbl[speaker_looks];
                    lower_idx = 242;
                    upper_idx = 245;
                    break;

                default:
                    base_msg_no = bad_msg_tbl[speaker_looks];
                    lower_idx = 245;
                    upper_idx = 248;
                    break;
            }

            msg_no = base_msg_no + listener_looks * (upper_idx - lower_idx);
            idx = mQst_GetIdxTalkSelect(lower_idx, upper_idx, speaker_looks);
            if (idx % 3 < 2) {
                speak_nactorx->talk_info.look_target = (1 << 4) | (1 << 0);
                listen_nactorx->talk_info.look_target = (1 << 4) | (1 << 0);
            } else {
                speak_nactorx->talk_info.look_target = (0 << 4) | (0 << 0);
                listen_nactorx->talk_info.look_target = (0 << 4) | (0 << 0);
            }

            msg_no += idx;

            msg_p = mMsg_Get_base_window_p();
            mMsg_Set_free_str(msg_p, mMsg_FREE_STR0, (u8*)speaker_animal->id.name, ANIMAL_NAME_LEN);
            mMsg_Set_free_str(msg_p, mMsg_FREE_STR1, (u8*)listener_animal->id.name, ANIMAL_NAME_LEN);

            aQMgr_set_constellation_string(aQMgr_RANDOM_STRING_TYPE_FREE, 11);
            aQMgr_set_default_string(def_str, ARRAY_COUNT(def_str));
        } break;
    }

    return msg_no;
}

static int aQMgr_get_aitekara_msg(mNpc_NpcList_c* list, int looks) {
    static int l_aitekara_msg[mNpc_LOOKS_NUM] = { 0x46C3, 0x2B85, 0x2BB2, 0x117C, 0x46D2, 0x2D1D };
    static aQMgr_def_str_c def_str[] = {
        { aQMgr_RANDOM_STRING_TYPE_ITEM, mMsg_ITEM_STR1, aQMgr_STR_TYPE_SWEETS },
        { aQMgr_RANDOM_STRING_TYPE_ITEM, mMsg_ITEM_STR2, aQMgr_STR_TYPE_HOUSEHOLD_ITEMS },
        { aQMgr_RANDOM_STRING_TYPE_ITEM, mMsg_ITEM_STR3, aQMgr_STR_TYPE_FOOD },
        { aQMgr_RANDOM_STRING_TYPE_ITEM, mMsg_ITEM_STR4, aQMgr_STR_TYPE_SPORTS },
    };
    
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    int msg_no = l_aitekara_msg[looks];
    u8 str[mMsg_FREE_STRING_LEN];
    u8 cloth_name[mIN_ITEM_NAME_LEN];
    int cloth_type;

    msg_no += mQst_GetIdxTalkSelect(248, 253, looks);
    list->conversation_flags.beesting = FALSE;

    cloth_type = mNT_get_cloth_type(Now_Private->cloth.item, Now_Private->cloth.idx);

    // String0 = player cloth style
    mString_Load_StringFromRom(str, sizeof(str), 0x748 + cloth_type - mNT_STYLE_COOL);
    mMsg_Set_free_str(msg_p, mMsg_FREE_STR0, str, sizeof(str));

    // String1 = shop type
    mString_Load_StringFromRom(str, sizeof(str), 0x454 + mSP_GetShopLevel());
    mMsg_Set_free_str(msg_p, mMsg_FREE_STR1, str, sizeof(str));

    // String2 = constellation
    aQMgr_set_constellation_string(aQMgr_RANDOM_STRING_TYPE_FREE, mMsg_FREE_STR2);

    // ItemString0 = player cloth name
    mIN_copy_cloth_name_str(cloth_name, Now_Private->cloth.item, Now_Private->cloth.idx);
    mMsg_Set_item_str(msg_p, mMsg_ITEM_STR0, cloth_name, sizeof(cloth_name));

    aQMgr_set_default_string(def_str, ARRAY_COUNT(def_str));

    return msg_no;
}

static int aQMgr_get_meet_time(Animal_c* animal, Anmmem_c* memory, int* months, int* weeks) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int mem_idx;
    int type = 1;
    int foreigner = FALSE;

    if (memory != NULL) {
        lbRTC_time_c* last_spoken_time;
        int days;

        mem_idx = mNpc_GetAnimalMemoryIdx(&Now_Private->player_ID, memory, ANIMAL_MEMORY_NUM);
        if (mem_idx == -1) {
            return aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO;
        }

        memory += mem_idx;
        last_spoken_time = &memory->last_speak_time;
        if (mTM_IsTimeCleared(last_spoken_time)) {
            return aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO;
        }

        if (lbRTC_IsOverTime(rtc_time, last_spoken_time) == lbRTC_OVER) {
            return aQMgr_MEET_TIME_HELLO_AGAIN;
        }

        days = lbRTC_GetIntervalDays(last_spoken_time, rtc_time);
        if (animal != NULL && mNpc_CheckIslandAnimal(animal) == FALSE &&
            mLd_CheckThisLand(memory->memuni.land.name, memory->memuni.land.id) == FALSE) {
            foreigner = TRUE;
        }

        if (days >= 60) {
            int years;

            type = foreigner == FALSE ? aQMgr_MEET_TIME_A_REALLY_LONG_TIME
                                      : aQMgr_MEET_TIME_A_REALLY_LONG_TIME_FOREIGN_TOWN;
            years = days / 365;
            *months = years * lbRTC_MONTHS_MAX;
            *months += (days % 365) / 30;
            *weeks = days / lbRTC_WEEK;
        } else if (days >= 14) {
            type = foreigner == FALSE ? aQMgr_MEET_TIME_A_LONG_TIME : aQMgr_MEET_TIME_A_LONG_TIME_FOREIGN_TOWN;
            *weeks = days / lbRTC_WEEK;
        } else if (days >= 1) {
            if (foreigner == FALSE) {
                type = aQMgr_MEET_TIME_FIRST_HELLO;
            } else {
                type = aQMgr_MEET_TIME_FIRST_HELLO_FOREIGN_TOWN;
            }
        } else {
            type = aQMgr_MEET_TIME_HELLO_AGAIN;
        }
    }

    return type;
}

static void aQMgr_set_memory(Animal_c* animal, Anmmem_c* memory) {
    PersonalID_c* pid = &Now_Private->player_ID;

    if (memory != NULL) {
        int mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

        if (mem_idx == -1) {
            mem_idx = mNpc_ForceGetFreeAnimalMemoryIdx(animal, memory, ANIMAL_MEMORY_NUM);

            if (mem_idx != -1) {
                memory += mem_idx;
                mNpc_SetAnimalMemory(pid, &animal->id, memory);
            }
        }
    }
}

static int aQMgr_get_hello_msg_npc_feel_normal(Animal_c* animal, int looks, int last_meet_time_type,
                                               aQMgr_GET_TIME_KIND_PROC get_time_kind_proc) {
    static int* hello_msg_tbl[] = { l_hello_fine_msg_tbl, l_hello_rain_msg_tbl, l_hello_snow_msg_tbl,
                                    l_hello_fine_msg_tbl, };
    static aQMgr_idx_group_c* hello_idx_tbl[] = { l_hello_fine_idx_tbl, l_hello_rain_idx_tbl, l_hello_snow_idx_tbl,
                                                    l_hello_fine_idx_tbl, };
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int* hello_msg_tbl_p;
    aQMgr_idx_group_c* hello_idx_tbl_p;
    int hello_msg;
    int msg_no;
    int weather = Common_Get(weather);
    int anm_idx = mNpc_SearchAnimalPersonalID(&animal->id);

    if (mNpc_CheckOverImpatient(anm_idx, looks) == TRUE) {
        int over_impatient = mNpc_GetOverImpatient(anm_idx, looks);

        msg_no = MSG_2640;
        msg_no += looks * 6 + over_impatient * 3;
        msg_no += mQst_GetIdxTalkSelect(122, 125, looks);
    } else if (last_meet_time_type == aQMgr_MEET_TIME_FIRST_HELLO &&
               mEv_IsEventActive(mEv_EVENT_SPRING_CLEANING) == TRUE) {
        msg_no = aQMgr_get_random_msg_no(MSG_15297, looks, 3);
    } else if (last_meet_time_type == aQMgr_MEET_TIME_FIRST_HELLO &&
               mEv_IsEventActive(mEv_EVENT_APRILFOOLS_DAY) == TRUE) {
        msg_no = aQMgr_get_random_msg_no(MSG_15236, looks, 3);
    } else {
        mActor_name_t field_type = mFI_GET_TYPE(mFI_GetFieldId());

        if (field_type == mFI_FIELD_ROOM0 || field_type == mFI_FIELD_NPCROOM0) {
            hello_msg = l_indoor_hello_msg_tbl[last_meet_time_type];
            hello_idx_tbl_p = &l_indoor_hello_idx_tbl[last_meet_time_type];
        } else {
            hello_idx_tbl_p = hello_idx_tbl[weather];
            hello_msg_tbl_p = hello_msg_tbl[weather];
            hello_msg = hello_msg_tbl_p[last_meet_time_type];
            hello_idx_tbl_p = &hello_idx_tbl_p[last_meet_time_type];
        }

        msg_no = aQMgr_actor_get_my_hello_msg_new(get_time_kind_proc, hello_msg, looks, rtc_time->hour, hello_idx_tbl_p->lower_bound, hello_idx_tbl_p->upper_bound);
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_npc_feel_normal_island(Animal_c* animal, int looks, int last_meet_time_type,
                                                      aQMgr_GET_TIME_KIND_PROC get_time_kind_proc) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int msg_no = -1;

    if (last_meet_time_type == aQMgr_MEET_TIME_FIRST_HELLO) {
        if (mEv_IsEventActive(mEv_EVENT_SPRING_CLEANING) == TRUE) {
            msg_no = aQMgr_get_random_msg_no(MSG_15315, looks, 3);
        } else if (mEv_IsEventActive(mEv_EVENT_APRILFOOLS_DAY) == TRUE) {
            msg_no = aQMgr_get_random_msg_no(MSG_15254, looks, 3);
        }
    }

    if (msg_no == -1) {
        int hello_msg = l_hello_fine_island_msg_tbl[last_meet_time_type];
        msg_no = aQMgr_actor_get_my_hello_msg_new(get_time_kind_proc, hello_msg, looks, rtc_time->hour, l_hello_fine_island_idx_tbl[last_meet_time_type].lower_bound, l_hello_fine_island_idx_tbl[last_meet_time_type].upper_bound);
    }

    return msg_no;
}

static int aQMgr_get_thanks_cloth_msg(Animal_c* animal, int looks) {
    PersonalID_c* pid = &Now_Private->player_ID;
    int msg_no = MSG_11752;

    if (pid != NULL && animal != NULL) {
        Anmmem_c* memory = animal->memories;
        int cloth_mem_idx = mNpc_GetPresentClothMemoryIdx_rnd(memory);
        int mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);
        int cloth_msg;
        int lower_idx;
        int upper_idx;

        memory += cloth_mem_idx;
        if (cloth_mem_idx == mem_idx) {
            // This player gave the cloth
            cloth_msg = MSG_11770;
            lower_idx = 56;
            upper_idx = 59;
        } else {
            // Another player gave the cloth
            pid = &memory->memory_player_id;
            cloth_msg = MSG_11752;
            lower_idx = 59;
            upper_idx = 62;
        }

        msg_no = aQMgr_get_random_msg_no_new(cloth_msg, looks, lower_idx, upper_idx);
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR13, pid->player_name, PLAYER_NAME_LEN);
        mQst_SetItemNameStr(animal->present_cloth, mMsg_ITEM_STR0);
        memory->letter_info.wearing_present_cloth = FALSE;
        animal->present_cloth = EMPTY_NO;
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_npc_feel_grad(int last_meet_time_type, int looks,
                                             aQMgr_GET_TIME_KIND_PROC get_time_kind_proc) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int msg_no = -1;

    if (last_meet_time_type == aQMgr_MEET_TIME_FIRST_HELLO) {
        if (mEv_IsEventActive(mEv_EVENT_SPRING_CLEANING) == TRUE) {
            msg_no = aQMgr_get_random_msg_no(MSG_15297, looks, 3);
        } else if (mEv_IsEventActive(mEv_EVENT_APRILFOOLS_DAY) == TRUE) {
            msg_no = aQMgr_get_random_msg_no(MSG_15236, looks, 3);
        }
    }

    if (msg_no == -1) {
        int hello_msg = l_grad_hello_msg_tbl[last_meet_time_type];

        msg_no = aQMgr_actor_get_my_hello_msg_new(get_time_kind_proc, hello_msg, looks, rtc_time->hour, l_grad_hello_idx_tbl[last_meet_time_type].lower_bound, l_grad_hello_idx_tbl[last_meet_time_type].upper_bound);
    }

    return msg_no;
}

static void aQMgr_set_feel_normal(ACTOR* actorx) {
    int kind = NPC_CLIP->get_demo_kind_proc(actorx);
    mDemo_Set_OrderValue(kind, 0, 0xFF);
    mDemo_Set_OrderValue(kind, 2, 5);
}

static int aQMgr_get_hello_msg_how_do_you_do(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                             int last_meet_time_type) {
    Animal_c* animal = client->npc_info.animal_orig;
    mNpc_NpcList_c* npclist = client->npc_info.list;
    int feel = animal->mood;
    int looks = mNpc_GetNpcLooks((ACTOR*)client);
    mLd_land_info_c* land_info = Save_GetPointer(land_info);
    int msg_no;

    if (animal->moved_in == mNpc_MOVE_IN_TYPE_INVITED) {
        if (mAN_check_pwdInfoTable(animal->id.npc_id) != -1 && mLd_PlayerManKindCheck() == NATIVE && mLd_CheckCmpLand(animal->id.land_name, animal->id.land_id, land_info->name, land_info->id) == TRUE) {
            mNpc_AddFriendshipNowPlayer(&animal->id, 50);
            mAN_unregist_pwdInfoTable(animal->id.npc_id);
            msg_no = aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, MSG_11350, looks, Common_Get(time.rtc_time).hour, 3);
        } else if (mPr_CheckCmpPersonalID(&animal->parent_id, &Now_Private->player_ID) == TRUE) {
            msg_no = aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, MSG_9718, looks, Common_Get(time.rtc_time).hour, 3);
        } else {
            msg_no = aQMgr_actor_get_my_hello_msg_new(get_time_kind_proc, MSG_11573, looks, Common_Get(time.rtc_time).hour, 9, 12);
        }
    } else if (animal->moved_in == mNpc_MOVE_IN_TYPE_GROW) {
        msg_no = aQMgr_actor_get_my_hello_msg_new(get_time_kind_proc, MSG_11573, looks, Common_Get(time.rtc_time).hour, 9, 12);
    } else if (mLd_CheckThisLand(animal->id.land_name, animal->id.land_id) == FALSE) {
        msg_no =
            aQMgr_actor_get_my_hello_msg_new(get_time_kind_proc, MSG_11666, looks, Common_Get(time.rtc_time).hour, 12, 15);
    } else if (feel == mNpc_FEEL_HAPPY) {
        msg_no = aQMgr_get_hello_msg_npc_feel_grad(last_meet_time_type, looks, get_time_kind_proc);
    } else {
        msg_no = aQMgr_get_hello_msg_npc_feel_normal(animal, looks, last_meet_time_type, get_time_kind_proc);

        if (msg_no != -1 && (feel == mNpc_FEEL_ANGRY || feel == mNpc_FEEL_SAD || feel == mNpc_FEEL_SLEEPY ||
                             feel == mNpc_FEEL_UZAI_0 || feel == mNpc_FEEL_UZAI_1)) {
            aQMgr_set_feel_normal((ACTOR*)client);
        }
    }

    if (npclist != NULL) {
        npclist->conversation_flags.beesting = FALSE;
    }

    return msg_no;
}

static int aQMgr_check_possession_item(mActor_name_t ignore_item) {
    static u8 category[] = { ITEM1_CAT_CARPET, ITEM1_CAT_WALL };
    Private_c* priv = Now_Private;
    int res = FALSE;

    if (mPr_GetPossessionItemIdxFGTypeWithCond_cancel(priv, NAME_TYPE_FTR0, mPr_ITEM_COND_NORMAL, ignore_item) != -1 ||
        mPr_GetPossessionItemIdxFGTypeWithCond_cancel(priv, NAME_TYPE_FTR1, mPr_ITEM_COND_NORMAL, ignore_item) != -1) {
        res = TRUE;
    } else {
        u8* category_p = category;
        int i;

        for (i = 0; i < ARRAY_COUNT(category); i++) {
            if (mPr_GetPossessionItemIdxItem1CategoryWithCond_cancel(priv, *category_p, mPr_ITEM_COND_NORMAL,
                                                                     ignore_item) != -1) {
                res = TRUE;
                break;
            }

            category_p++;
        }
    }

    return res;
}

static void aQMgr_set_place_str(int bx, int bz) {
    static u8 str0[mMsg_FREE_STRING_LEN];
    static u8 str1[mMsg_FREE_STRING_LEN];

    mem_clear(str0, sizeof(str0), CHAR_SPACE);
    if (bx == 0) {
        mString_Load_StringFromRom(str0, sizeof(str0), 0x75C);
    } else {
        str0[0] = '0' + bx;
        mString_Load_StringFromRom(str0 + 1, sizeof(str0) - 1, 0x75A);
    }
    
    mem_clear(str1, sizeof(str1), CHAR_SPACE);
    if (bz == 0) {
        mString_Load_StringFromRom(str1, sizeof(str1), 0x75C);
    } else {
        str1[0] = '0' + bz;
        mString_Load_StringFromRom(str1 + 1, sizeof(str1) - 1, 0x759);
    }

    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR1, str0, sizeof(str0)); // column
    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0, str1, sizeof(str1)); // row
}

static int aQMgr_get_harvestfestival_msg(mNpc_NpcList_c* npclist, int looks) {
    static u8 str0[mMsg_FREE_STRING_LEN];
    static u8 str1[mMsg_FREE_STRING_LEN];

    int msg_no;
    int bx = 0;
    int bz = 0;
    int ev_bx = 0;
    int ev_bz = 0;
    mEv_place_data_c* harvestfestival_place = mEv_get_common_place(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, 81);

    msg_no = aQMgr_get_random_msg_no_new(MSG_15200, looks, 138, 141);
    if (harvestfestival_place != NULL) {
        if (harvestfestival_place->block.x > 0 && harvestfestival_place->block.x < 7) {
            ev_bx = harvestfestival_place->block.x;
        }

        if (harvestfestival_place->block.z > 0 && harvestfestival_place->block.z < 8) {
            ev_bz = harvestfestival_place->block.z;
        }
    }

    if (mFI_Wpos2BlockNum(&bx, &bz, npclist->position) == TRUE) {
        if (bx == ev_bx) {
            ev_bx = 0;
        }

        if (bz == ev_bz) {
            ev_bz = 0;
        }
    }

    aQMgr_set_place_str(ev_bx, ev_bz);
    return msg_no;
}

static int aQMgr_get_harvestfestival_island_msg(int looks) {
    static u8 str0[mMsg_FREE_STRING_LEN];
    static u8 str1[mMsg_FREE_STRING_LEN];

    int msg_no;
    int ev_bx = 0;
    int ev_bz = 0;
    mEv_place_data_c* harvestfestival_place = mEv_get_common_place(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, 81);

    msg_no = aQMgr_get_random_msg_no_new(MSG_15218, looks, 286, 289);
    if (harvestfestival_place != NULL) {
        if (harvestfestival_place->block.x > 0 && harvestfestival_place->block.x < 7) {
            ev_bx = harvestfestival_place->block.x;
        }

        if (harvestfestival_place->block.z > 0 && harvestfestival_place->block.z < 8) {
            ev_bz = harvestfestival_place->block.z;
        }
    }

    aQMgr_set_place_str(ev_bx, ev_bz);
    return msg_no;
}

static int aQMgr_get_hello_msg_no_normal(QUEST_MANAGER_ACTOR* manager, NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                         int last_meet_time_type) {
    Animal_c* animal = client->npc_info.animal_orig;
    mNpc_NpcList_c* npclist = client->npc_info.list;
    mNpc_SickInfo_c* sick_info = Save_GetPointer(sick_info);
    int destiny = Now_Private->destiny.type;
    int feel = animal->mood;
    int looks = mNpc_GetNpcLooks((ACTOR*)client);
    int sick_idx = mNpc_GetSickAnimalIdx_com(sick_info);
    int anm_idx = mNpc_SearchAnimalPersonalID(&animal->id);
    int msg_no;

    if (anm_idx == sick_idx) {
        int base_msg = l_q005_aisatu_msg[looks];

        if (sick_info->gave_medicine == TRUE) {
            base_msg += 3;
        }
        msg_no = base_msg + mQst_GetRandom(3);
    } else if (feel == mNpc_FEEL_PITFALL) {
        msg_no = aQMgr_get_random_msg_no_new(MSG_8327, looks, 0, 3);

        if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
            aQMgr_clear_memory(animal, animal->memories);
        }

        npclist->conversation_flags.beesting = FALSE;
    } else if (Common_Get(player_bee_chase_flag)) {
        msg_no = aQMgr_get_honey_chase_msg(client, last_meet_time_type);
    } else if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        msg_no = aQMgr_get_hello_msg_how_do_you_do(client, get_time_kind_proc, last_meet_time_type);
    } else if (mPr_GetFishCompTalkPermission() == TRUE && mNpc_GetFishCompleteTalk(npclist) != TRUE &&
               mPr_GetInsectCompTalkPermission() == TRUE && mNpc_GetInsectCompleteTalk(npclist) != TRUE) {
        msg_no = aQMgr_get_comp_fish_and_insect_msg(npclist, looks);
    } else if (mNpc_GetInsectCompleteTalk(npclist) != TRUE && mPr_GetInsectCompTalkPermission() == TRUE) {
        msg_no = aQMgr_get_comp_insect_msg(npclist, looks);
    } else if (mNpc_GetFishCompleteTalk(npclist) != TRUE && mPr_GetFishCompTalkPermission() == TRUE) {
        msg_no = aQMgr_get_comp_fish_msg(npclist, looks);
    } else if (npclist->conversation_flags.beesting == TRUE) {
        msg_no = aQMgr_get_bee_msg(npclist, looks, get_time_kind_proc);
    } else if (feel == mNpc_FEEL_ANGRY || feel == mNpc_FEEL_SAD || feel == mNpc_FEEL_SLEEPY ||
               feel == mNpc_FEEL_UZAI_0 || feel == mNpc_FEEL_UZAI_1) {
        msg_no = aQMgr_get_hello_msg_npc_feel(feel, looks, FALSE);
    } else if (destiny == mPr_DESTINY_UNPOPULAR) {
        msg_no = aQMgr_get_random_msg_no_new(MSG_1869, looks, 50, 53);
    } else if (mNpc_GetPresentClothMemoryIdx(animal->memories) != -1) {
        msg_no = aQMgr_get_thanks_cloth_msg(animal, looks);
    } else if (client->action.idx == aNPC_ACT_SAY_HELLO) {
        msg_no = aQMgr_get_aitekara_msg(npclist, looks);
        if (manager != NULL) {
            manager->aitekara_msg_flag = TRUE;
        }
    } else if (mEv_IsEventActive(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN) == TRUE) {
        msg_no = aQMgr_get_harvestfestival_msg(npclist, looks);
    } else if (feel == mNpc_FEEL_HAPPY) {
        msg_no = aQMgr_get_hello_msg_npc_feel_grad(last_meet_time_type, looks, get_time_kind_proc);
    } else {
        msg_no = aQMgr_get_hello_msg_npc_feel_normal(animal, looks, last_meet_time_type, get_time_kind_proc);
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_no_normal_group_talk(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
    int last_meet_time_type) {
    ACTOR* client_actorx;
    ACTOR* other_actorx;
    NPC_ACTOR* other_npc;
    Animal_c* animal;
    Animal_c* other_animal;
    mNpc_NpcList_c* npclist;
    int feel;
    int looks;
    int other_looks;
    int other_meet_weeks;
    int other_meet_months;
    int msg_no;

    client_actorx = (ACTOR*)client;
    animal = client->npc_info.animal_orig;
    npclist = client->npc_info.list;
    feel = animal->mood;
    looks = mNpc_GetNpcLooks(client_actorx);
    other_actorx = NPC_CLIP->get_talk_actor_list_proc(1);
    other_npc = (NPC_ACTOR*)other_actorx;
    other_animal = other_npc->npc_info.animal_orig;
    other_looks = mNpc_GetNpcLooks(other_actorx);
    other_meet_weeks = -1; 
    other_meet_months = -1;

    aQMgr_get_meet_time(other_animal, other_animal->memories, &other_meet_months, &other_meet_weeks);

    if (Common_Get(player_bee_chase_flag)) {
        msg_no = aQMgr_get_honey_chase_msg((NPC_ACTOR*)client_actorx, last_meet_time_type);
    } else if (mPr_GetFishCompTalkPermission() == TRUE && mNpc_GetFishCompleteTalk(npclist) != TRUE &&
               mPr_GetInsectCompTalkPermission() == TRUE && mNpc_GetInsectCompleteTalk(npclist) != TRUE) {
        msg_no = aQMgr_get_comp_fish_and_insect_msg(npclist, looks);
    } else if (mNpc_GetInsectCompleteTalk(npclist) != TRUE && mPr_GetInsectCompTalkPermission() == TRUE) {
        msg_no = aQMgr_get_comp_insect_msg(npclist, looks);
    } else if (mNpc_GetFishCompleteTalk(npclist) != TRUE && mPr_GetFishCompTalkPermission() == TRUE) {
        msg_no = aQMgr_get_comp_fish_msg(npclist, looks);
    } else if (npclist->conversation_flags.beesting == TRUE) {
        msg_no = aQMgr_get_bee_msg(npclist, looks, get_time_kind_proc);
    } else {
        msg_no = aQMgr_get_hello_msg_npc_feel_group_talk(feel, looks, other_looks, animal,
                                                         other_animal, client, other_npc);
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_no_kamakura(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                           int last_meet_time_type, mActor_name_t ignore_item) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    static int hello_msg[] = { MSG_6367, MSG_6376, MSG_6358, MSG_6385, MSG_6394, MSG_6403 };
    int looks = mNpc_GetNpcLooks((ACTOR*)client);
    int msg_no;

    if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        msg_no = aQMgr_get_random_msg_no(MSG_265, looks, 3);
    } else {
        int hello_type = 0;

        if (mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) != -1 &&
            Now_Private->inventory.wallet >= aQMgr_GREETING_GAME_BELL_MIN) {
            hello_type |= aQMgr_GREETING_GAME_TYPE_MONEY;
        }

        if (aQMgr_check_possession_item(ignore_item) == TRUE) {
            hello_type |= aQMgr_GREETING_GAME_TYPE_ITEM;
        }

        if (hello_type == aQMgr_GREETING_GAME_TYPE_ALL) {
            int rng = RANDOM(2);

            msg_no = 1 + hello_msg[looks] + rng;
        } else {
            msg_no = hello_msg[looks] + hello_type;
        }
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_no_summercamp(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                             int last_meet_time_type, mActor_name_t ignore_item) {
    static int msg_table[] = { MSG_16002, MSG_16032, MSG_16063, MSG_16093, MSG_16123, MSG_16153 };
    int looks = mNpc_GetNpcLooks((ACTOR*)client);
    int hello_type = 0;
    int msg_no;

    if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        msg_no =
            aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, MSG_15930, looks, Common_Get(time.rtc_time).hour, 3);
    } else {
        if (mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) != -1 &&
            Now_Private->inventory.wallet >= aQMgr_GREETING_GAME_BELL_MIN) {
            hello_type |= aQMgr_GREETING_GAME_TYPE_MONEY;
        }

        if (aQMgr_check_possession_item(ignore_item) == TRUE) {
            hello_type |= aQMgr_GREETING_GAME_TYPE_ITEM;
        }

        if (hello_type == aQMgr_GREETING_GAME_TYPE_ALL) {
            int rng = RANDOM(2);

            msg_no = 1 + msg_table[looks] + rng;
        } else {
            msg_no = msg_table[looks] + hello_type;
        }
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_no_island(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                         int last_meet_time_type) {
    Animal_c* animal = client->npc_info.animal_orig;
    mNpc_NpcList_c* npclist = client->npc_info.list;
    int destiny = Now_Private->destiny.type;
    int feel = animal->mood;
    int looks = mNpc_GetNpcLooks((ACTOR*)client);
    int msg_no;

    if (feel == mNpc_FEEL_PITFALL) {
        msg_no = aQMgr_get_random_msg_no_new(MSG_13382, looks, 268, 271);

        if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
            aQMgr_clear_memory(animal, animal->memories);
        }

        npclist->conversation_flags.beesting = FALSE;
    } else if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        msg_no = aQMgr_get_hello_msg_npc_feel_normal_island(animal, looks, last_meet_time_type, get_time_kind_proc);
        npclist->conversation_flags.beesting = FALSE;
    } else if (npclist->conversation_flags.beesting == TRUE) {
        msg_no = aQMgr_get_random_msg_no(MSG_13424, looks, 1);
        npclist->conversation_flags.beesting = FALSE;
    } else if (feel == mNpc_FEEL_ANGRY || feel == mNpc_FEEL_SAD || feel == mNpc_FEEL_SLEEPY ||
               feel == mNpc_FEEL_UZAI_0 || feel == mNpc_FEEL_UZAI_1) {
        msg_no = aQMgr_get_hello_msg_npc_feel(feel, looks, TRUE);
    } else if (destiny == mPr_DESTINY_UNPOPULAR) {
        msg_no = aQMgr_get_random_msg_no_new(MSG_13520, looks, 271, 274);
    } else if (mEv_IsEventActive(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN) == TRUE) {
        msg_no = aQMgr_get_harvestfestival_island_msg(looks);
    } else {
        msg_no = aQMgr_get_hello_msg_npc_feel_normal_island(animal, looks, last_meet_time_type, get_time_kind_proc);
    }

    return msg_no;
}

extern int aQMgr_get_hello_msg_no(QUEST_MANAGER_ACTOR* mgr, ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc, mActor_name_t give_item) {
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal_orig;
    int msg_no;
    int weeks = -1;
    int months = -1;
    int last_meet_time_type = aQMgr_get_meet_time(animal, animal->memories, &months, &weeks);

    if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        aQMgr_set_memory(animal, animal->memories);
    }

    aQMgr_actor_set_day_str(months, mMsg_FREE_STR7);
    aQMgr_actor_set_day_str(weeks, mMsg_FREE_STR8);

    if (mNpc_CheckIslandAnimal(animal) == TRUE) {
        msg_no = aQMgr_get_hello_msg_no_island((NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type);
    } else if (client->npc_id == SP_NPC_EV_KAMAKURA_0) {
        msg_no =
            aQMgr_get_hello_msg_no_kamakura((NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type, give_item);
    } else if (client->npc_id == SP_NPC_EV_SUMMERCAMP_0) {
        msg_no =
            aQMgr_get_hello_msg_no_summercamp((NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type, give_item);
    } else if (NPC_CLIP->chk_group_talk_proc((NPC_ACTOR*)client) == TRUE) {
        msg_no = aQMgr_get_hello_msg_no_normal_group_talk((NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type);

        if (msg_no == -1) {
            msg_no = aQMgr_get_hello_msg_no_normal(mgr, (NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type);
        }
    } else {
        msg_no = aQMgr_get_hello_msg_no_normal(mgr, (NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type);
    }

    return msg_no;
}
