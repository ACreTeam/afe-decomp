#include "ac_quest_manager.h"

#include "m_common_data.h"
#include "m_msg.h"
#include "m_melody.h"
#include "ac_quest_talk_greeting.h"
#include "ac_quest_talk_init.h"
#include "ac_quest_talk_fj_init.h"
#include "ac_quest_talk_normal_init.h"
#include "ac_quest_talk_island.h"
#include "m_soncho.h"
#include "gfxalloc.h"
#include "m_player_lib.h"
#include "libultra/libultra.h"
#include "m_malloc.h"
#include "zurumode.h"
#include "m_flashrom.h"
#include "m_debug.h"
#include "padmgr.h"

enum {
    aQMgr_MODE_NORMAL,                      /* 0 */
    aQMgr_MODE_SELECT_TALK,                 /* 1 - default talk */
    aQMgr_MODE_MOVE_TALK,                   /* 2 */
    aQMgr_MODE_TALK_FIN,                    /* 3 */
    aQMgr_MODE_TALK_START_KAMAKURA_HELLO,   /* 4 - SP_NPC_EV_KAMAKURA_0 + hello */
    aQMgr_MODE_TALK_START_KAMAKURA,         /* 5 - SP_NPC_EV_KAMAKURA_0 */
    aQMgr_MODE_TALK_START_GROUP_HELLO,      /* 6 - chk_group_talk + hello */
    aQMgr_MODE_TALK_START_GROUP,            /* 7 - chk_group_talk */
    aQMgr_MODE_TALK_START_SUMMERCAMP_HELLO, /* 8 - SP_NPC_EV_SUMMERCAMP_0 + hello */
    aQMgr_MODE_TALK_START_SUMMERCAMP,       /* 9 - SP_NPC_EV_SUMMERCAMP_0 */
    aQMgr_MODE_TALK_START_AITEKARA_MSG,     /* 10 - aitekara_msg_flag */

    aQMgr_MODE_NUM /* 11 */
};

static ACTOR* l_client_p = NULL;
static u8 l_quest_manager_mode = aQMgr_MODE_NORMAL;
static Anmmem_c* l_quest_memory_p = NULL;
static QUEST_MANAGER_ACTOR* l_quest_actor_p = NULL;
static int l_quest_manager_hello = FALSE;
static int l_aQMgr_hand_start = FALSE;

static int l_msg_quest_irai_end[mNpc_LOOKS_NUM] = {0x024C, 0x024F, 0x0252, 0x0255, 0x0258, 0x025B};
static int l_msg_quest_kyohi[mNpc_LOOKS_NUM] = {0x025E, 0x0261, 0x0264, 0x0267, 0x026A, 0x026D};
static int l_msg_quest_uchikiri_end[mNpc_LOOKS_NUM] = {0x02B8, 0x02BB, 0x02BE, 0x02C1, 0x02C4, 0x02C7};
static int l_msg_quest_uchikiri_end_soft[mNpc_LOOKS_NUM] = {0x02CA, 0x02CD, 0x02D0, 0x02D3, 0x02D6, 0x02D9};
static int l_msg_q001_irai1[mNpc_LOOKS_NUM] = {0x0151, 0x0154, 0x0157, 0x015A, 0x015D, 0x0160};
static int l_msg_q001_kakunin1[mNpc_LOOKS_NUM] = {0x0163, 0x0166, 0x0169, 0x016C, 0x016F, 0x0172};
static int l_msg_q001_orei1[mNpc_LOOKS_NUM] = {0x0175, 0x0178, 0x017B, 0x017E, 0x0181, 0x0184};
static int l_msg_q001_uchikiri1[mNpc_LOOKS_NUM] = {0x0187, 0x018A, 0x018D, 0x0190, 0x0193, 0x0196};
static int l_msg_q002_irai1[mNpc_LOOKS_NUM] = {0x0199, 0x019C, 0x019F, 0x01A2, 0x01A5, 0x01A8};
static int l_msg_q002_kakunin1[mNpc_LOOKS_NUM] = {0x01AB, 0x01AE, 0x01B1, 0x01B4, 0x01B7, 0x01BA};
static int l_msg_q002_orei1[mNpc_LOOKS_NUM] = {0x01BD, 0x01C0, 0x01C3, 0x01C6, 0x01C9, 0x01CC};
static int l_msg_q002_uchikiri1[mNpc_LOOKS_NUM] = {0x01CF, 0x01D2, 0x01D5, 0x01D8, 0x01DB, 0x01DE};
static int l_msg_q003_irai1[mNpc_LOOKS_NUM] = {0x01E1, 0x01E4, 0x01E7, 0x01EA, 0x01ED, 0x01F0};
static int l_msg_q003_kakunin1[mNpc_LOOKS_NUM] = {0x005B, 0x005E, 0x0061, 0x0064, 0x0067, 0x006A};
static int l_msg_q003_orei1[mNpc_LOOKS_NUM] = {0x01F3, 0x01F6, 0x01F9, 0x01FC, 0x01FF, 0x0202};
static int l_msg_q003_uchikiri1[mNpc_LOOKS_NUM] = {0x034C, 0x034F, 0x0352, 0x0355, 0x0358, 0x035B};
static int l_msg_q004_irai1[mNpc_LOOKS_NUM] = {0x0205, 0x0208, 0x020B, 0x020E, 0x0211, 0x0214};
static int l_msg_q004_kakunin1[mNpc_LOOKS_NUM] = {0x0217, 0x021A, 0x021D, 0x0220, 0x0223, 0x0226};
static int l_msg_q004_orei1[mNpc_LOOKS_NUM] = {0x10BF, 0x10C2, 0x10C5, 0x10C8, 0x10CB, 0x10CE};
static int l_msg_q004_orei_end[mNpc_LOOKS_NUM] = {0x0EB1, 0x0EB4, 0x0EB7, 0x0EBA, 0x0EBD, 0x0EC0};
static int l_msg_q004_uchikiri1[mNpc_LOOKS_NUM] = {0x023A, 0x023D, 0x0240, 0x0243, 0x0246, 0x0249};
static int l_msg_q005_orei1[mNpc_LOOKS_NUM] = {0x03F8, 0x03FB, 0x03FE, 0x0401, 0x0404, 0x0407};
static int l_msg_q005_orei_end[mNpc_LOOKS_NUM] = {0x03E6, 0x03E9, 0x03EC, 0x03EF, 0x03F2, 0x03F5};
static int l_msg_q005_motenaiyo[mNpc_LOOKS_NUM] = {0x035E, 0x0361, 0x0364, 0x0367, 0x036A, 0x036D};
static int l_msg_q005_watashitenai[mNpc_LOOKS_NUM] = {0x0370, 0x0373, 0x0376, 0x0379, 0x037C, 0x037F};
static int l_msg_q005_akitsukure[mNpc_LOOKS_NUM] = {0x0382, 0x0385, 0x0388, 0x038B, 0x038E, 0x0391};
static int l_msg_q008_irai1[mNpc_LOOKS_NUM] = {0x0E33, 0x0E36, 0x0E39, 0x0E3C, 0x0E3F, 0x0E42};
static int l_msg_q008_irai2[mNpc_LOOKS_NUM] = {0x5726, 0x5729, 0x572C, 0x572F, 0x5732, 0x5735};
static int l_msg_q008_orei1[mNpc_LOOKS_NUM] = {0x0E45, 0x0E48, 0x0E4B, 0x0E4E, 0x0E51, 0x0E54};
static int l_msg_q008_hokanohito[mNpc_LOOKS_NUM] = {0x0ED5, 0x0ED8, 0x0EDB, 0x0EDE, 0x0EE1, 0x0EE4};
static int l_msg_q008_orei_end[mNpc_LOOKS_NUM] = {0x0E8D, 0x0E90, 0x0E93, 0x0E96, 0x0E99, 0x0E9C};\
static int l_msg_arubaito_ftr_orei[mNpc_LOOKS_NUM] = {0x08EF, 0x08F1, 0x08F3, 0x08F5, 0x08F7, 0x08F9};
static int l_msg_arubaito_ftr_orei_end[mNpc_LOOKS_NUM] = {0x08F0, 0x08F2, 0x08F4, 0x08F6, 0x08F8, 0x08FA};
static int l_msg_arubaito_cpt_orei[mNpc_LOOKS_NUM] = {0x08FB, 0x08FD, 0x08FF, 0x0901, 0x0903, 0x0905};
static int l_msg_arubaito_cpt_orei_end[mNpc_LOOKS_NUM] = {0x08FC, 0x08FE, 0x0900, 0x0902, 0x0904, 0x0906};
static int l_msg_arubaito_axe_orei[mNpc_LOOKS_NUM] = {0x0907, 0x0909, 0x090B, 0x090D, 0x090F, 0x0911};
static int l_msg_arubaito_axe_orei_end[mNpc_LOOKS_NUM] = {0x0908, 0x090A, 0x090C, 0x090E, 0x0910, 0x0912};
static int l_msg_q007_irai1[mNpc_LOOKS_NUM] = {0x0D79, 0x0D7C, 0x0D7F, 0x0D82, 0x0D85, 0x0D88};
static int l_msg_q007_orei1[mNpc_LOOKS_NUM] = {0x0D91, 0x0D94, 0x0D97, 0x0D9A, 0x0D9D, 0x0DA0};
static int l_msg_q007_orei_end[mNpc_LOOKS_NUM] = {0x0DD9, 0x0DDC, 0x0DDF, 0x0DE2, 0x0DE5, 0x0DE8};
static int l_msg_q007_watashitenai[mNpc_LOOKS_NUM] = {0x0DFD, 0x0E00, 0x0E03, 0x0E06, 0x0E09, 0x0E0C};
static int l_msg_q007_motenaiyo[mNpc_LOOKS_NUM] = {0x0DEB, 0x0DEE, 0x0DF1, 0x0DF4, 0x0DF7, 0x0DFA};
static int l_msg_q007_akitsukure[mNpc_LOOKS_NUM] = {0x0E0F, 0x0E12, 0x0E15, 0x0E18, 0x0E1B, 0x0E1E};
static int l_msg_q009_irai1[mNpc_LOOKS_NUM] = {0x0FB5, 0x0FB8, 0x0FBB, 0x0FBE, 0x0FC1, 0x0FC4};
static int l_msg_q009_orei1[mNpc_LOOKS_NUM] = {0x0FC7, 0x0FCA, 0x0FCD, 0x0FD0, 0x0FD3, 0x0FD6};
static int l_msg_q009_orei_end[mNpc_LOOKS_NUM] = {0x100F, 0x1012, 0x1015, 0x1018, 0x101B, 0x101E};
static int l_msg_q009_watashitenai[mNpc_LOOKS_NUM] = {0x1033, 0x1036, 0x1039, 0x103C, 0x103F, 0x1042};
static int l_msg_q009_motenaiyo[mNpc_LOOKS_NUM] = {0x1021, 0x1024, 0x1027, 0x102A, 0x102D, 0x1030};
static int l_msg_q009_akitsukure[mNpc_LOOKS_NUM] = {0x1045, 0x1048, 0x104B, 0x104E, 0x1051, 0x1054};
static int l_msg_q010_irai1[mNpc_LOOKS_NUM] = {0x1AE1, 0x1AE4, 0x1AE7, 0x1AEA, 0x1AED, 0x1AF0};
static int l_msg_q010_okuttayo[mNpc_LOOKS_NUM] = {0x1B17, 0x1B1A, 0x1B1D, 0x1B20, 0x1B23, 0x1B26};
static int l_msg_q011_irai1[mNpc_LOOKS_NUM] = {0x158C, 0x158F, 0x1592, 0x1595, 0x1598, 0x159B};\
static int l_msg_q011_irai2[mNpc_LOOKS_NUM] = {0x5166, 0x5169, 0x516C, 0x516F, 0x5172, 0x5175};
static int l_msg_q011_orei1[mNpc_LOOKS_NUM] = {0x159E, 0x15A1, 0x15A4, 0x15A7, 0x15AA, 0x15AD};
static int l_msg_q011_orei_end[mNpc_LOOKS_NUM] = {0x15B0, 0x15B3, 0x15B6, 0x15B9, 0x15BC, 0x15BF};
static int l_msg_q012_irai1[mNpc_LOOKS_NUM] = {0x160A, 0x160D, 0x1610, 0x1613, 0x1616, 0x1619};
static int l_msg_q012_irai2[mNpc_LOOKS_NUM] = {0x5178, 0x517B, 0x517E, 0x5181, 0x5184, 0x5187};
static int l_msg_q012_orei1[mNpc_LOOKS_NUM] = {0x161C, 0x161F, 0x1622, 0x1625, 0x1628, 0x162B};
static int l_msg_q012_orei_end[mNpc_LOOKS_NUM] = {0x162E, 0x1631, 0x1634, 0x1637, 0x163A, 0x163D};
static int l_msg_q013_irai2[mNpc_LOOKS_NUM] = {0x0F92, 0x0F95, 0x0F98, 0x0F9B, 0x0F9E, 0x0FA1};
static int l_msg_q013_orei1[mNpc_LOOKS_NUM] = {0x241F, 0x2422, 0x2425, 0x2428, 0x242B, 0x242E};
static int l_msg_q013_orei_end[mNpc_LOOKS_NUM] = {0x2455, 0x2458, 0x245B, 0x245E, 0x2461, 0x2464};
static int l_msg_q014_irai2[mNpc_LOOKS_NUM] = {0x249D, 0x24A0, 0x24A3, 0x24A6, 0x24A9, 0x24AC};
static int l_msg_q014_orei1[mNpc_LOOKS_NUM] = {0x24AF, 0x24B2, 0x24B5, 0x24B8, 0x24BB, 0x24BE};
static int l_msg_q014_orei_end[mNpc_LOOKS_NUM] = {0x24E5, 0x24E8, 0x24EB, 0x24EE, 0x24F1, 0x24F4};
static int l_msg_q006_irai1[mNpc_LOOKS_NUM] = {0x0A74, 0x0A77, 0x0A7A, 0x0A7D, 0x0A80, 0x0A83};
static int l_msg_q006_orei1[mNpc_LOOKS_NUM] = {0x0A98, 0x0A9B, 0x0A9E, 0x0AA1, 0x0AA4, 0x0AA7};
static int l_msg_q006_orei_end[mNpc_LOOKS_NUM] = {0x2020, 0x2023, 0x2026, 0x2029, 0x202C, 0x202F};
static int l_msg_q006_watashitenai[mNpc_LOOKS_NUM] = {0x0AAA, 0x0AAD, 0x0AB0, 0x0AB3, 0x0AB6, 0x0AB9};
static int l_msg_q006_motenaiyo[mNpc_LOOKS_NUM] = {0x0A86, 0x0A89, 0x0A8C, 0x0A8F, 0x0A92, 0x0A95};
static int l_msg_q006_akitsukure[mNpc_LOOKS_NUM] = {0x1F55, 0x1F58, 0x1F5B, 0x1F5E, 0x1F61, 0x1F64};


// clang-format off
static aQMgr_set_data_c l_set_delivery_data[mQst_DELIVERY_KIND_NUM] = {
    {aQMgr_QUEST_TARGET_NUM        , 2, 2, TRUE , aQMgr_QUEST_ITEM_CLOTH    , EMPTY_NO      , mPr_ITEM_COND_QBOX  , {0x28, 0x00, 0x28, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00}, 0, {l_msg_q001_irai1, l_msg_quest_irai_end, l_msg_q001_kakunin1, l_msg_quest_kyohi, l_msg_q001_orei1, NULL, l_msg_q001_uchikiri1, l_msg_quest_uchikiri_end, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_NUM        , 2, 2, TRUE , aQMgr_QUEST_ITEM_QBOX     , EMPTY_NO      , mPr_ITEM_COND_QBOX  , {0x28, 0x00, 0x28, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00}, 0, {l_msg_q002_irai1, l_msg_quest_irai_end, l_msg_q002_kakunin1, l_msg_quest_kyohi, l_msg_q002_orei1, NULL, l_msg_q002_uchikiri1, l_msg_quest_uchikiri_end, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_NUM        , 2, 2, TRUE , aQMgr_QUEST_ITEM_QBOX     , EMPTY_NO      , mPr_ITEM_COND_QBOX  , {0x28, 0x00, 0x28, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00}, 0, {l_msg_q003_irai1, l_msg_quest_irai_end, l_msg_q003_kakunin1, l_msg_quest_kyohi, l_msg_q003_orei1, NULL, l_msg_q003_uchikiri1, l_msg_quest_uchikiri_end, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_LAST_REMOVE, 4, 0, TRUE , aQMgr_QUEST_ITEM_FROM_DATA, ITM_QST_LETTER, mPr_ITEM_COND_QUEST , {0x28, 0x00, 0x00, 0x1E, 0x1E, 0x00, 0x00, 0x00, 0x00}, 1000, {l_msg_q004_irai1, l_msg_quest_irai_end, l_msg_q004_kakunin1, l_msg_quest_kyohi, l_msg_q004_orei1, l_msg_q004_orei_end, l_msg_q004_uchikiri1, l_msg_quest_uchikiri_end_soft, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT     , 1, 3, FALSE, aQMgr_QUEST_ITEM_NONE     , EMPTY_NO      , mPr_ITEM_COND_NORMAL, {0x23, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x19}, 300, {l_msg_q008_irai1, l_msg_quest_irai_end, l_msg_q008_irai2, NULL, l_msg_q008_orei1, l_msg_q008_orei_end, l_msg_q008_hokanohito, NULL, NULL, NULL, NULL, NULL, NULL}},
};

static aQMgr_set_data_c l_set_errand_data[mQst_ERRAND_NUM] = {
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, l_msg_arubaito_ftr_orei, l_msg_arubaito_ftr_orei_end, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, l_msg_arubaito_cpt_orei, l_msg_arubaito_cpt_orei_end, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, l_msg_arubaito_axe_orei, l_msg_arubaito_axe_orei_end, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, l_msg_arubaito_axe_orei, l_msg_arubaito_axe_orei_end, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {aQMgr_QUEST_TARGET_CLIENT, 0, 0, FALSE, aQMgr_QUEST_ITEM_CURRENT_ITEM, EMPTY_NO, mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 100, 0x00}, 0, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
};

static aQMgr_set_data_c l_set_contest_data[mQst_CONTEST_KIND_NUM] = {
    /* mQst_CONTEST_KIND_SOCCER */ {aQMgr_QUEST_TARGET_CLIENT,  1, 2, FALSE, aQMgr_QUEST_ITEM_NONE      , EMPTY_NO    , mPr_ITEM_COND_NORMAL, {0x28, 0x00, 0x00, 0x1E, 0x1E, 0x00, 0x00, 0x00, 0x00}, 0, {l_msg_q007_irai1, NULL, l_msg_q007_irai1, l_msg_quest_kyohi, l_msg_q007_orei1, l_msg_q007_orei_end, NULL, l_msg_quest_uchikiri_end_soft, NULL, l_msg_q007_watashitenai, l_msg_q007_orei_end, l_msg_q007_motenaiyo, l_msg_q007_akitsukure}},
    /* mQst_CONTEST_KIND_FLOWER */ {aQMgr_QUEST_TARGET_CLIENT,  3, 1, FALSE, aQMgr_QUEST_ITEM_NONE      , EMPTY_NO    , mPr_ITEM_COND_NORMAL, {0x3C, 0x00, 0x00, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00}, 0, {l_msg_q009_irai1, NULL, l_msg_q009_irai1, l_msg_quest_kyohi, l_msg_q009_orei1, l_msg_q009_orei_end, NULL, l_msg_quest_uchikiri_end_soft, NULL, l_msg_q009_watashitenai, l_msg_q009_orei_end, l_msg_q009_motenaiyo, l_msg_q009_akitsukure}},
    /* mQst_CONTEST_KIND_FISH   */ {aQMgr_QUEST_TARGET_CLIENT,  3, 1, FALSE, aQMgr_QUEST_ITEM_FISH_NOW  , EMPTY_NO    , mPr_ITEM_COND_NORMAL, {0x50, 0x00, 0x00, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00}, 0, {l_msg_q011_irai1, NULL, l_msg_q011_irai2, l_msg_quest_kyohi, l_msg_q011_orei1, l_msg_q011_orei_end, NULL, l_msg_quest_uchikiri_end_soft, NULL, NULL, NULL, NULL, NULL}},
    /* mQst_CONTEST_KIND_INSECT */ {aQMgr_QUEST_TARGET_CLIENT,  3, 1, FALSE, aQMgr_QUEST_ITEM_INSECT_NOW, EMPTY_NO    , mPr_ITEM_COND_NORMAL, {0x50, 0x00, 0x00, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00}, 0, {l_msg_q012_irai1, NULL, l_msg_q012_irai2, l_msg_quest_kyohi, l_msg_q012_orei1, l_msg_q012_orei_end, NULL, l_msg_quest_uchikiri_end_soft, NULL, NULL, l_msg_q012_orei_end, NULL, NULL}},
    /* mQst_CONTEST_KIND_LETTER */ {aQMgr_QUEST_TARGET_CLIENT,  2, 2, FALSE, aQMgr_QUEST_ITEM_NONE      , EMPTY_NO    , mPr_ITEM_COND_NORMAL, {0x50, 0x00, 0x00, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00}, 0, {l_msg_q010_irai1, NULL, l_msg_q010_irai1, l_msg_quest_kyohi, l_msg_q010_okuttayo, NULL, NULL, l_msg_quest_uchikiri_end_soft, NULL, NULL, NULL, NULL, NULL}},
    /* mQst_CONTEST_KIND_FTR    */ {aQMgr_QUEST_TARGET_CLIENT,  3, 1, FALSE, aQMgr_QUEST_ITEM_Q013      , EMPTY_NO    , mPr_ITEM_COND_NORMAL, {0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 0, {NULL, NULL, l_msg_q013_irai2, l_msg_quest_kyohi, l_msg_q013_orei1, l_msg_q013_orei_end, NULL, l_msg_quest_uchikiri_end_soft, NULL, NULL, NULL, NULL, NULL}},
    /* mQst_CONTEST_KIND_SHOP   */ {aQMgr_QUEST_TARGET_CLIENT,  1, 1, FALSE, aQMgr_QUEST_ITEM_SHOP      , EMPTY_NO    , mPr_ITEM_COND_NORMAL, {0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 0, {NULL, NULL, l_msg_q014_irai2, l_msg_quest_kyohi, l_msg_q014_orei1, l_msg_q014_orei_end, NULL, l_msg_quest_uchikiri_end_soft, NULL, NULL, NULL, NULL, NULL}},
    /* mQst_CONTEST_KIND_GRASS  */ {aQMgr_QUEST_TARGET_CLIENT,  1, 1, FALSE, aQMgr_QUEST_ITEM_NONE      , EMPTY_NO    , mPr_ITEM_COND_NORMAL, {0x00, 0x00, 0x32, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00}, 300, {l_msg_q006_irai1, NULL, l_msg_q006_irai1, l_msg_quest_kyohi, l_msg_q006_orei1, l_msg_q006_orei_end, NULL, l_msg_quest_uchikiri_end_soft, NULL, l_msg_q006_watashitenai, l_msg_q006_orei_end, l_msg_q006_motenaiyo, l_msg_q006_akitsukure}},
    /* mQst_CONTEST_KIND_SICK   */ {aQMgr_QUEST_TARGET_CLIENT, 10, 1, FALSE, aQMgr_QUEST_ITEM_FROM_DATA , ITM_MEDICINE, mPr_ITEM_COND_NORMAL, {0x28, 0x00, 0x00, 0x1E, 0x1E, 0x00, 0x00, 0x00, 0x00}, 300, {NULL, NULL, NULL, NULL, l_msg_q005_orei1, l_msg_q005_orei_end, NULL, NULL, NULL, l_msg_q005_watashitenai, NULL, l_msg_q005_motenaiyo, l_msg_q005_akitsukure}},
};
//clang-format on

static aQMgr_set_data_c* l_set_data[mQst_QUEST_TYPE_NUM] = {
    l_set_delivery_data,
    l_set_errand_data,
    l_set_contest_data,
};

static void aQMgr_move_own_delvery_qbox(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static void aQMgr_move_own_delivery_lost(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);

static int aQMgr_actor_check_fin_qbox(mQst_base_c* quest_info, Animal_c* animal);

static aQMgr_CHECK_LIMIT_PROC l_delivery_proc[mQst_DELIVERY_KIND_NUM] = {
    &aQMgr_move_own_delvery_qbox,
    &aQMgr_move_own_delvery_qbox,
    &aQMgr_move_own_delvery_qbox,
    NULL,
    &aQMgr_move_own_delivery_lost,
};

static aQMgr_CHECK_FINISH_PROC l_delivery_check[mQst_DELIVERY_KIND_NUM] = {
    &aQMgr_actor_check_fin_qbox,
    &aQMgr_actor_check_fin_qbox,
    &aQMgr_actor_check_fin_qbox,
    NULL,
    NULL,
};

static void aQMgr_move_own_errand_cloth(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static void aQMgr_move_own_errand_seed(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static void aQMgr_move_own_errand_letter(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static void aQMgr_move_own_errand_hello(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);

static void aQMgr_actor_contest_check_limit(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist) ;
static int aQMgr_actor_check_fin_fruit(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_soccer(mQst_base_c* quest_info, Animal_c* animal);
static void aQMgr_actor_contest_snowman_clear(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static int aQMgr_actor_check_fin_snowman(mQst_base_c* quest_info, Animal_c* animal);
static void aQMgr_actor_contest_flower_clear(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static int aQMgr_actor_check_flower(mQst_contest_c* contest, int bx, int bz);
static int aQMgr_actor_check_fin_flower(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_fish(mQst_base_c* quest_info, Animal_c* animal);
static void aQMgr_actor_contest_insect_clear(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static int aQMgr_actor_check_fin_insect(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_contest_letter(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_contest_ftr(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_contest_shop(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_grass(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_contest_sick(mQst_base_c* quest_info, Animal_c* animal);

static void aQMgr_save_contest_flower(aQMgr_regist_c* regist);
static void aQMgr_save_contest(aQMgr_regist_c* regist);

static aQMgr_CHECK_LIMIT_PROC l_errand_proc[mQst_ERRAND_NUM] = {
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    &aQMgr_move_own_errand_cloth,
    &aQMgr_move_own_errand_seed,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    &aQMgr_move_own_errand_letter,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    &aQMgr_move_own_errand_letter,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    &aQMgr_move_own_errand_hello,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
};

static aQMgr_CHECK_LIMIT_PROC l_contest_proc[mQst_CONTEST_KIND_NUM] = {
    &aQMgr_actor_contest_check_limit,
    &aQMgr_actor_contest_flower_clear,
    &aQMgr_actor_contest_check_limit,
    &aQMgr_actor_contest_insect_clear,
    &aQMgr_actor_contest_check_limit,
    &aQMgr_actor_contest_check_limit,
    &aQMgr_actor_contest_check_limit,
    &aQMgr_actor_contest_check_limit,
    NULL,
};

static aQMgr_CHECK_FINISH_PROC l_contest_check[mQst_CONTEST_KIND_NUM] = {
    &aQMgr_actor_check_fin_soccer,
    &aQMgr_actor_check_fin_flower,
    &aQMgr_actor_check_fin_fish,
    &aQMgr_actor_check_fin_insect,
    &aQMgr_actor_check_fin_contest_letter,
    &aQMgr_actor_check_fin_contest_ftr,
    &aQMgr_actor_check_fin_contest_shop,
    &aQMgr_actor_check_fin_grass,
    &aQMgr_actor_check_fin_contest_sick,
};

static int l_proc_max[mQst_QUEST_TYPE_NUM] = { mQst_DELIVERY_KIND_NUM, mQst_ERRAND_NUM, mQst_CONTEST_KIND_NUM };

static int aQMgr_check_quest_target(mQst_delivery_c* delivery_info, mQst_delivery_c* lost_info, AnmPersonalID_c* anm_id) {
    int i;
    int ret = FALSE;
    
    if (mQst_CheckFreeQuest(&lost_info->base) == FALSE &&
        (mNpc_CheckCmpAnimalPersonalID(&lost_info->recipient, anm_id) == TRUE ||
        mNpc_CheckCmpAnimalPersonalID(&lost_info->sender, anm_id) == TRUE)) {
        ret = TRUE;
    }

    if (ret == FALSE) {
        for (i = 0; i < mPr_DELIVERY_QUEST_NUM; i++) {
            if (mQst_CheckFreeQuest(&delivery_info->base) == FALSE &&
                (mNpc_CheckCmpAnimalPersonalID(&delivery_info->recipient, anm_id) == TRUE ||
                mNpc_CheckCmpAnimalPersonalID(&delivery_info->sender, anm_id) == TRUE)) {
                ret = TRUE;
                break;
            }

            delivery_info++;
        }
    }

    return ret;
}

static void aQMgr_actor_force_set_memory(Animal_c* animal) {
    Private_c* priv = Now_Private;

    if (animal != NULL && priv != NULL && mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE && mNpc_CheckIslandAnimalID(&animal->id) == FALSE) {
        Anmmem_c* memory = animal->memories;
        int mem_idx = mNpc_GetAnimalMemoryIdx(&priv->player_ID, memory, ANIMAL_MEMORY_NUM);

        if (mem_idx == -1 && aQMgr_check_quest_target(priv->deliveries, &priv->lost_item_quest, &animal->id) == TRUE) {
            mem_idx = mNpc_ForceGetFreeAnimalMemoryIdx(animal, memory, ANIMAL_MEMORY_NUM);

            if (mem_idx != -1) {
                memory += mem_idx;
                mNpc_SetAnimalMemory(&priv->player_ID, &animal->id, memory);
                lbRTC_Sub_DD(&memory->last_speak_time, 1);
            }
        }
    }
}

static void aQMgr_actor_set_memory(ACTOR* client) {
    Animal_c* animal;

    if (client != NULL && client->part == ACTOR_PART_NPC) {
        animal = ((NPC_ACTOR*)client)->npc_info.animal_orig;
    }
    else {
        animal = NULL;
    }

    if (animal != NULL) {
        Anmmem_c* memory = animal->memories;
        int memory_idx = mNpc_GetAnimalMemoryIdx(&Now_Private->player_ID, memory, ANIMAL_MEMORY_NUM);

        if (memory_idx != -1) {
            memory += memory_idx;
            l_quest_memory_p = memory;
        }
        else {
            l_quest_memory_p = NULL;
        }
    }
}

static void aQMgr_actor_set_hello_free_str(Animal_c* animal) {
    int mem_idx = mNpc_GetAnimalMemoryIdx(&Now_Private->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

    if (mem_idx != -1 && mNpc_CheckIslandAnimal(animal) == FALSE) {
        mLd_SetFreeStrLandMuraName(animal->memories[mem_idx].memuni.land.name, mMsg_FREE_STR6);
    }

    if (mNpc_CheckIslandAnimal(animal) == FALSE) {
        mLd_SetFreeStrLandMuraName(animal->anmuni.previous_land_name, mMsg_FREE_STR10);
    }

    mLd_SetFreeStrLandMuraName(animal->id.land_name, mMsg_FREE_STR11);
}

static void aQMgr_relation_add_random(void) {
    AnmPersonalID_c* from_id;
    AnmPersonalID_c* to_id;

    from_id = mNpc_GetOtherAnimalPersonalID(NULL, 0);
    if (from_id != NULL) {
        to_id = mNpc_GetOtherAnimalPersonalID(from_id, 1);
        if (to_id != NULL) {
            static int add_tbl[] = { 0, 0, 1, -1 };
            mNpc_AddRelationPoint_id(from_id, to_id, add_tbl[RANDOM(ARRAY_COUNT(add_tbl)) % ARRAY_COUNT(add_tbl)]);
        }
    }
}

static int aQMgr_take_hello_msg_no(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal_orig;
    PersonalID_c* pid = &Now_Private->player_ID;

    if (animal != NULL) {
        if (mNpc_GetAnimalMemoryIdx(pid, animal->memories, ANIMAL_MEMORY_NUM) == -1) {
            l_quest_manager_hello = TRUE;
        }
        else {
            l_quest_manager_hello = FALSE;
        }
    }
    else {
        l_quest_manager_hello = TRUE;
    }

    return aQMgr_get_hello_msg_no(manager, client, manager->get_time_kind_proc, manager->give_item);
}

static void aQMgr_set_talk_info(ACTOR* client) {
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal_orig;
    QUEST_MANAGER_ACTOR* manager = l_quest_actor_p;
    NPC_ACTOR* pal_actor = NULL;
    int msg_no;

    l_client_p = client;

    if (aNPC_IS_NRM_NPC(((NPC_ACTOR*)client))) {
        ACTOR* pal_actorx = ((NPC_ACTOR*)client)->palActor;

        if (pal_actorx != NULL && aNPC_IS_NRM_NPC((NPC_ACTOR*)pal_actorx)) {
            pal_actor = (NPC_ACTOR*)pal_actorx;
        }
    }

    NPC_CLIP->regist_talk_actor_list_proc(((NPC_ACTOR*)client), pal_actor);
    aQMgr_actor_force_set_memory(animal);
    aQMgr_actor_set_hello_free_str(animal);
    msg_no = aQMgr_take_hello_msg_no(manager);
    mDemo_Set_msg_num(msg_no);

    if (animal->mood == mNpc_FEEL_SLEEPY) {
        animal->mood = mNpc_FEEL_NORMAL;
        ((NPC_ACTOR*)client)->condition_info.feel_tim = 0;
    }

    if (animal != NULL) {
        manager->cloth = animal->cloth;
    }

    aQMgr_relation_add_random();

    if (ZURUMODE2_ENABLED()) {
        mNpc_SetTalkAnimalIdx_fdebug(&animal->id);
    }
}

static int aQMgr_actor_talk_request(ACTOR* client) {
    int res = FALSE;

    if (client != NULL && l_quest_manager_mode == aQMgr_MODE_NORMAL) {
        if (mDemo_Check(mDemo_TYPE_TALK, client) == FALSE) {
            mDemo_Request(mDemo_TYPE_TALK, client, &aQMgr_set_talk_info);
        }
        else if (mDemo_Check_ListenAble() == FALSE) {
            res = TRUE;
        }
    }

    return res;
}

static int aQMgr_actor_talk_start(ACTOR* client) {
    QUEST_MANAGER_ACTOR* manager = l_quest_actor_p;
    int res = FALSE;

    if (client != NULL && l_quest_manager_mode == aQMgr_MODE_NORMAL && mDemo_Check(mDemo_TYPE_TALK, client) == TRUE &&
        mDemo_Check_ListenAble() == FALSE && mDemo_Check_SpeakerAble() == TRUE && client == l_client_p) {
        mDemo_Set_ListenAble();

        if (client->npc_id == SP_NPC_EV_KAMAKURA_0) {
            if (l_quest_manager_hello == TRUE) {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_KAMAKURA_HELLO;
            } else {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_KAMAKURA;
            }
        } else if (client->npc_id == SP_NPC_EV_SUMMERCAMP_0) {
            if (l_quest_manager_hello == TRUE) {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_SUMMERCAMP_HELLO;
                Common_Set(npc_is_summercamper, TRUE);
            } else {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_SUMMERCAMP;
            }
        } else if (NPC_CLIP->chk_group_talk_proc((NPC_ACTOR*)client) == TRUE) {
            if (l_quest_manager_hello == TRUE) {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_GROUP_HELLO;
            } else {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_GROUP;
            }
        } else if (manager != NULL && manager->aitekara_msg_flag == TRUE) {
            l_quest_manager_mode = aQMgr_MODE_TALK_START_AITEKARA_MSG;
            manager->aitekara_msg_flag = FALSE;
        } else {
            l_quest_manager_mode = aQMgr_MODE_SELECT_TALK;
        }

        aQMgr_actor_set_memory(client);
        mMld_ActorMakeMelody(client);
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_talk_check(ACTOR* client) {
    int res = FALSE;

    if (client != NULL && l_client_p == client && l_quest_manager_mode == aQMgr_MODE_TALK_FIN && mDemo_Get_talk_actor() != client) {
        l_client_p = NULL;
        l_quest_manager_mode = aQMgr_MODE_NORMAL;
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_looks2name(u8* buf, u8 looks) {
    QUEST_MANAGER_ACTOR* manager = l_quest_actor_p;
    int ret = FALSE;

    if (buf != NULL && manager != NULL) {
        int idx = mNpc_GetLooks2Name_idx(buf, looks);

        if (idx != -1) {
            manager->talk_about_animal_idx = idx;
            ret = TRUE;
        }
    }

    return ret;
}

static int aQMgr_actor_race2name(u8* buf, u8 race) {
    QUEST_MANAGER_ACTOR* manager = l_quest_actor_p;
    int ret = FALSE;
    
    if (buf != NULL && manager != NULL) {
        int idx = mNpc_GetRace2Name_idx(buf, race);

        if (idx != -1) {
            manager->talk_about_animal_idx = idx;
            ret = TRUE;
        }
    }

    return ret;
}

static int aQMgr_actor_add_relation(ACTOR* client, int amount) {
    QUEST_MANAGER_ACTOR* manager = l_quest_actor_p;
    int ret = FALSE;

    if (client != NULL && manager != NULL && manager->talk_about_animal_idx != -1) {
        Animal_c* client_animal = ((NPC_ACTOR*)client)->npc_info.animal_orig;
        Animal_c* talk_animal = Save_GetPointer(animals[manager->talk_about_animal_idx]);

        if (client_animal != NULL && talk_animal != NULL) {
            ret = mNpc_AddRelationPoint(client_animal, talk_animal, amount);
        }
    }

    return ret;
}

static int aQMgr_get_time_kind(int hour) {
    int res = aQMgr_TIME_MORNING;
    
    if (hour >= 10 && hour < 17) {
        res = aQMgr_TIME_DAY;
    }
    else if (hour >= 17 && hour < 24) {
        res = aQMgr_TIME_EVENING;
    }
    else if (hour >= 0 && hour < 5) {
        res = aQMgr_TIME_NIGHT;
    }

    return res;
}

static void aQMgr_clear_talk_init_ovl(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_init_proc = NULL;
}

static int aQMgr_talk_common_talk_init_ovl(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_TALK_INIT_PROC talk_init_table[aQMgr_TALK_KIND_NUM] = {
        &aQMgr_actor_move_talk_init,
        &aQMgr_talk_first_job_init,
        &aQMgr_talk_normal_init,
        &aQMgr_talk_island_init
    };

    int type = manager->talk_type;
    
    if (type < 0 || type >= aQMgr_TALK_KIND_NUM) {
        type = aQMgr_TALK_KIND_QUEST;
    }

    manager->talk_init_proc = talk_init_table[type];
    return TRUE;
}

static void aQMgr_actor_change_talk_init_ovl(QUEST_MANAGER_ACTOR* manager) {
    if (manager->talk_change_type < aQMgr_TALK_KIND_NUM) {
        manager->talk_type = manager->talk_change_type;
        if ((*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_TALK_INIT_OVL) == TRUE) {
            manager->talk_change_type = aQMgr_TALK_KIND_NUM;
            manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NO_WAIT;
        }
    }
}

static void aQMgr_actor_clear_regist(aQMgr_regist_c* regist, int count) {
    for (; count != 0; count--) {
        regist->check_limit_proc = (aQMgr_CHECK_LIMIT_PROC)&none_proc1;
        regist->check_finish_proc = NULL;
        regist->quest_info = NULL;
        regist->pid = NULL;
        mNpc_ClearAnimalPersonalID(&regist->from_id);
        mNpc_ClearAnimalPersonalID(&regist->to_id);
        regist->animal_idx = -1;
        regist++;
    }
}

static int aQMgr_actor_check_fin_item(mQst_base_c* quest_info, Animal_c* animal) {
    mQst_contest_c* contest = (mQst_contest_c*)quest_info;
    int res = FALSE;

    if (mPr_GetPossessionItemIdxWithCond(Now_Private, contest->requested_item, mPr_ITEM_COND_NORMAL) != -1) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_free_regist(QUEST_MANAGER_ACTOR* manager, int start_idx) {
    aQMgr_regist_c* regist = &manager->regist[start_idx];
    int idx = -1;

    if (manager->regist_use_no < aQMgr_REGIST_NUM) {
        int i;

        for (i = start_idx; i < aQMgr_REGIST_NUM; i++) {
            if (regist->quest_info == NULL) {
                idx = i;
                break;
            }

            regist++;
        }
    }

    return idx;
}

static void aQMgr_actor_regist_quest(QUEST_MANAGER_ACTOR* manager, int* idx, aQMgr_quest_c* quest, int animal_idx) {
    mQst_base_c* quest_info = &quest->base;
    u32 type = quest_info->quest_type;

    if (type < mQst_QUEST_TYPE_NUM) {
        *idx = aQMgr_actor_free_regist(manager, *idx);

        if (*idx != -1) {
            int kind = quest_info->quest_kind;
            int max_kind = l_proc_max[type];

            if (kind >= 0 && kind < max_kind) {
                aQMgr_regist_c* regist = &manager->regist[*idx];
                AnmPersonalID_c* from_id;
                AnmPersonalID_c* to_id;
                Animal_c* animal;

                if (type == mQst_QUEST_TYPE_CONTEST) {
                    animal = &Save_Get(animals[animal_idx]);
                    regist->pid = &quest->contest.player_id;
                    regist->check_limit_proc = l_contest_proc[kind];
                    regist->check_finish_proc = l_contest_check[kind];
                    from_id = &animal->id;
                    to_id = &animal->id;
                }
                else {
                    if (type == mQst_QUEST_TYPE_ERRAND) {
                        regist->check_limit_proc = l_errand_proc[kind];
                    } else {
                        regist->check_limit_proc = l_delivery_proc[kind];
                        regist->check_finish_proc = l_delivery_check[kind];
                    }

                    from_id = &quest->delivery.sender;
                    to_id = &quest->delivery.recipient;
                    regist->pid = &Now_Private->player_ID;
                }

                mNpc_CopyAnimalPersonalID(&regist->from_id, from_id);
                mNpc_CopyAnimalPersonalID(&regist->to_id, to_id);

                regist->quest_info = quest_info;

                switch (type) {
                    case mQst_QUEST_TYPE_DELIVERY:
                        if (animal_idx != -1) {
                            regist->item = Now_Private->inventory.pockets[animal_idx];
                        } else if (kind == mQst_DELIVERY_KIND_LOST_ITEM) {
                            regist->item = quest->delivery.item;
                        }
                        break;
                    case mQst_QUEST_TYPE_ERRAND:
                        regist->item = quest->errand.item;
                        break;
                    case mQst_QUEST_TYPE_CONTEST:
                        regist->item = quest->contest.requested_item;
                        break;
                }

                regist->animal_idx = animal_idx;
                manager->regist_use_no++;
            }
        }
    }
}

static void aQMgr_talk_clear_talk_order(aQMgr_order_c* demo_order) {
    demo_order->type = mDemo_TYPE_NONE;
    demo_order->value = 0;
}

static int aQMgr_talk_common_clear_talk_info(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target_p = &manager->target;
    aQMgr_choice_c* choice_p = &manager->choice;
    int i;

    *manager->memory = NULL;
    manager->talk_step = 0;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->handover_item = EMPTY_NO;
    manager->msg_no = 0;
    manager->category_msg_no_start = 0;
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    
    mQst_ClearQuestInfo(&target_p->quest_info);
    target_p->from_id = NULL;
    target_p->to_id = NULL;
    target_p->quest_inv_item_idx = -1;
    target_p->quest_item = EMPTY_NO;
    target_p->quest_item_cond = mPr_ITEM_COND_NORMAL;
    target_p->reward_kind = -1;
    target_p->reward_item = EMPTY_NO;
    target_p->pay = 0;
    target_p->set_data_p = NULL;
    target_p->free_data_idx = -1;
    target_p->free_data_p = NULL;
    target_p->errand_type = mQst_ERRAND_TYPE_NONE;
    bzero(&target_p->work, sizeof(target_p->work));

    choice_p->choice_num = 0;
    choice_p->talk_action = -1;

    for (i = 0; i < mChoice_CHOICE_NUM; i++) {
        choice_p->choice_ids[i] = -1;
    }

    manager->regist_idx = -1;
    manager->talk_type = aQMgr_TALK_KIND_QUEST;
    manager->talk_change_type = aQMgr_TALK_KIND_NUM;
    manager->talk_about_animal_idx = -1;
    manager->still_reward_but_field_quest_cancel = FALSE;
    aQMgr_talk_clear_talk_order(&manager->demo_order);
    return TRUE;
}

static int aQMgr_talk_common_get_item_idx(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx = manager->regist_idx;
    aQMgr_regist_c* regist = &manager->regist[regist_idx];
    mQst_base_c* quest_info = regist->quest_info;
    int idx = -1;

    if (quest_info != NULL) {
        int type = quest_info->quest_type;
        int kind = quest_info->quest_kind;
        mActor_name_t item;
        Private_c* priv;

        switch (type) {
            case mQst_QUEST_TYPE_DELIVERY:
                idx = regist->animal_idx; // reused here I guess
                break;
            case mQst_QUEST_TYPE_ERRAND:
                idx = ((mQst_errand_c*)quest_info)->pockets_idx;
                break;
            case mQst_QUEST_TYPE_CONTEST:
                item = ((mQst_contest_c*)quest_info)->requested_item;
                priv = Now_Private;
                idx = mPr_GetPossessionItemIdxWithCond(priv, item, mPr_ITEM_COND_NORMAL);
                break;
        }
    }

    return idx;
}

static int aQMgr_talk_common_set_choice_str(QUEST_MANAGER_ACTOR* manager) {
    u8 str[mChoice_CHOICE_NUM][mChoice_CHOICE_STRING_LEN];
    u8* str_p_tbl[mChoice_CHOICE_NUM];
    aQMgr_choice_c* choice_p = &manager->choice;
    int i;

    if (choice_p->choice_num > 0) {
        for (i = 0; i < mChoice_CHOICE_NUM; i++) {
            str_p_tbl[i] = NULL;
        }

        for (i = 0; i < choice_p->choice_num; i++) {
            if (i >= mChoice_CHOICE_NUM) {
                break;
            }

            mChoice_Load_ChoseStringFromRom(mChoice_Get_base_window_p(), str[i], choice_p->choice_ids[i], NULL);
            str_p_tbl[i] = str[i];
        }

        //clang-format off
        mChoice_Set_choice_data(
            mChoice_Get_base_window_p(),
            str_p_tbl[0], mChoice_CHOICE_STRING_LEN,
            str_p_tbl[1], mChoice_CHOICE_STRING_LEN,
            str_p_tbl[2], mChoice_CHOICE_STRING_LEN,
            str_p_tbl[3], mChoice_CHOICE_STRING_LEN,
                    NULL, mChoice_CHOICE_STRING_LEN,
                    NULL, mChoice_CHOICE_STRING_LEN
        );
        //clang-format on
    }

    return TRUE;
}

static int aQMgr_talk_common_get_set_data_p(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    mQst_base_c* quest_info = &target->quest_info;
    aQMgr_set_data_c* set_data_p = NULL;

    if (quest_info != NULL) {
        int type = quest_info->quest_type;
        int kind = quest_info->quest_kind;

        set_data_p = &l_set_data[type][kind];
    }

    target->set_data_p = set_data_p;
    return TRUE;
}

static void aQMgr_actor_init_quest(QUEST_MANAGER_ACTOR* manager) {
    mQst_delivery_c* delivery = Now_Private->deliveries;
    mQst_delivery_c* lost_item_quest = &Now_Private->lost_item_quest;
    mQst_errand_c* errand = Now_Private->errands;
    Animal_c* animal = Save_Get(animals);
    int free_idx = 0;
    int lost_item_idx = -1;
    int i;

    for (i = 0; i < mPr_DELIVERY_QUEST_NUM; i++) {
        if (free_idx == -1) {
            break;
        }

        aQMgr_actor_regist_quest(manager, &free_idx, (aQMgr_quest_c*)delivery, i);
        delivery++;
    }

    for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
        if (free_idx == -1) {
            break;
        }

        aQMgr_actor_regist_quest(manager, &free_idx, (aQMgr_quest_c*)errand, i);
        errand++;
    }

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (free_idx == -1) {
            break;
        }

        aQMgr_actor_regist_quest(manager, &free_idx, (aQMgr_quest_c*)&animal->contest_quest, i);
        animal++;
    }

    if (free_idx != -1 && Now_Private != NULL) {        
        if (lost_item_quest->base.progress == 0) {
            mActor_name_t* pockets_p = Now_Private->inventory.pockets;
            u8* cond_p = Now_Private->inventory.item_conditions;

            for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
                if (IS_ITEM_LOST_ITEM(*pockets_p) && (*cond_p & 0xF) == mPr_ITEM_COND_LOST_ITEM) {
                    lost_item_idx = i;
                    break;
                }

                pockets_p++;
                cond_p++;
            }
        }

        aQMgr_actor_regist_quest(manager, &free_idx, (aQMgr_quest_c*)lost_item_quest, lost_item_idx);
    }
}

static void aQMgr_actor_regist_quest_move(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_regist_c* regist = manager->regist;
    int i;

    for (i = aQMgr_REGIST_NUM; i != 0; i--) {
        if (regist->quest_info != NULL) {
            if (regist->check_limit_proc != NULL) {
                (*regist->check_limit_proc)(manager, regist);
            }
        }

        regist++;
    }
}

static void aQMgr_actor_move_wait(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_actor_init_quest(manager);
    aQMgr_actor_regist_quest_move(manager);
    (*manager->clear_regist_proc)(manager->regist, aQMgr_REGIST_NUM);
    manager->regist_idx = -1;
    manager->regist_use_no = 0;
    mNpc_TalkInfoMove();
}

static void aQMgr_actor_move_talk_fin(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_actor_init_quest(manager);
    aQMgr_actor_regist_quest_move(manager);
    (*manager->clear_regist_proc)(manager->regist, aQMgr_REGIST_NUM);
    manager->regist_idx = -1;
    manager->regist_use_no = 0;
}

static int aQMgr_actor_get_my_msg(int base_msg) {
    int msg_no = base_msg;
    msg_no += mQst_GetRandom(3);
    
    return msg_no;
}

static int aQMgr_actor_decide_quest_message_no(aQMgr_target_c* target, int msg_type, int looks) {
    aQMgr_set_data_c* set_data_p = target->set_data_p;
    int* msg_start_p = set_data_p->msg_start[msg_type];
    int msg_no = 0;
    
    if (msg_start_p != NULL) {
        msg_no = msg_start_p[looks];
    }

    return msg_no;
}

static int aQMgr_talk_common_set_msg_no(QUEST_MANAGER_ACTOR* manager) {
    int base_msg;
    int msg_no;

    if (manager->msg_category != aQMgr_MSG_KIND_NONE) {
        int looks = mNpc_GetNpcLooks(*manager->client);
        manager->category_msg_no_start = aQMgr_actor_decide_quest_message_no(&manager->target, manager->msg_category, looks);
    }

    base_msg = manager->category_msg_no_start;
    if (base_msg != 15 && base_msg != 0) {
        
        msg_no = aQMgr_actor_get_my_msg(base_msg);
    }
    else {
        msg_no = base_msg;
    }

    manager->msg_no = msg_no;
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    manager->category_msg_no_start = 0;
    return TRUE;
}

static int aQMgr_talk_common_regist_set_target(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    aQMgr_regist_c* regist = &manager->regist[manager->regist_idx];
    mQst_base_c* quest_info = &target->quest_info;
    mQst_base_c* src_info = regist->quest_info;

    quest_info->quest_type = src_info->quest_type;
    quest_info->quest_kind = src_info->quest_kind;

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_SET_DATA);
    
    target->quest_item = regist->item;
    target->to_id = &regist->to_id;
    target->from_id = &regist->from_id;
    return TRUE;
}

static int aQMgr_talk_common_change_talk_normal(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_state = aQMgr_TALK_STATE_INIT;
    manager->talk_change_type = aQMgr_TALK_KIND_NORMAL;
    manager->talk_step = 0;
    manager->choice.talk_action = -1;
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    return TRUE;
}

static int aQMgr_talk_common_change_talk_island(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_state = aQMgr_TALK_STATE_INIT;
    manager->talk_change_type = aQMgr_TALK_KIND_ISLAND;
    manager->talk_step = 0;
    manager->choice.talk_action = -1;
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    return TRUE;
}

static int aQMgr_set_npc_putaway(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (CLIP(handOverItem_clip)->request_mode == aHOI_REQUEST_TRANS_WAIT) {
        int order = NPC_CLIP->get_demo_kind_proc(*manager->client);

        mDemo_Set_OrderValue(order, 3, 3);
        res = TRUE;
    }

    return res;
}

static int aQMgr_talk_common_set_npc_takeout(QUEST_MANAGER_ACTOR* manager, mActor_name_t item) {
    int order = NPC_CLIP->get_demo_kind_proc(*manager->client);

    mDemo_Set_OrderValue(order, 3, 2);
    mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 0, item);
    mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 1, 7);

    if (manager->target.quest_item_cond == mPr_ITEM_COND_QBOX) {
        mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 2, 3);
    } else {
        mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 2, 0);
    }
    return TRUE;
}

static int aQMgr_talk_common_set_npc_takeout_item(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_common_set_npc_takeout(manager, manager->target.quest_item);
    return TRUE;
}

static int aQMgr_talk_common_set_npc_takeout_reward(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_common_set_npc_takeout(manager, manager->target.reward_item);
    return TRUE;
}

static int aQMgr_check_npc_hand_item() {
    int res = FALSE;

    if (l_aQMgr_hand_start == FALSE && CLIP(handOverItem_clip)->master_actor != NULL) {
        l_aQMgr_hand_start = TRUE;
    }

    if (l_aQMgr_hand_start && CLIP(handOverItem_clip)->master_actor == NULL) {
        mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
        l_aQMgr_hand_start = FALSE;
        res = TRUE;
    }

    return res;
}

static int l_aqmgr_select_msg[] = {0x02A6, 0x02A9, 0x02AC, 0x02AF, 0x02B2, 0x02B5};
static int l_aqmgr_cancel_item_msg[] = {0x04AB, 0x04AE, 0x04B1, 0x04B4, 0x04B7, 0x04BA};

static int aQMgr_talk_common_get_common_msg(QUEST_MANAGER_ACTOR* mgr, int type) {
    static int* msg_table_p[aQMgr_GET_COMMON_MSG_TYPE_NUM] = { l_aqmgr_select_msg, l_aqmgr_cancel_item_msg };
    int looks = mNpc_GetNpcLooks(*mgr->client);
    int msg_no;

    if (!(type >= 0 && type < aQMgr_GET_COMMON_MSG_TYPE_NUM)) {
        type = 0;
    } 
    
    msg_no = msg_table_p[type][looks];
    return msg_no;
}

static int aQMgr_actor_common_check_select_msg(QUEST_MANAGER_ACTOR* manager) {
    int ret = FALSE;
    int i;

    for (i = 0; i < ARRAY_COUNT(l_aqmgr_select_msg); i++) {
        if (manager->category_msg_no_start == l_aqmgr_select_msg[i]) {
            ret = TRUE;
            break;
        }
    }

    return ret;
}

typedef int (*aQMgr_COMMON_PROC)(QUEST_MANAGER_ACTOR*);

static int aQMgr_talk_common_proc(QUEST_MANAGER_ACTOR* manager, int proc) {
    static aQMgr_COMMON_PROC common_proc[aQMgr_TALK_COMMON_NUM] = {
        &aQMgr_talk_common_regist_set_target,
        &aQMgr_talk_common_get_item_idx,
        &aQMgr_talk_common_set_msg_no,
        &aQMgr_talk_common_clear_talk_info,
        &aQMgr_talk_common_set_choice_str,
        &aQMgr_talk_common_get_set_data_p,
        &aQMgr_talk_common_set_npc_takeout_item,
        &aQMgr_talk_common_set_npc_takeout_reward,
        &aQMgr_talk_common_talk_init_ovl,
        &aQMgr_talk_common_change_talk_normal,
        &aQMgr_talk_common_change_talk_island
    };

    return (*common_proc[proc])(manager);
}

static void aQMgr_move_own_delvery_qbox(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist) {
    if (regist != NULL && regist->quest_info != NULL) {
        mQst_delivery_c* delivery = (mQst_delivery_c*)regist->quest_info;
        switch (delivery->base.progress) {
            case 0:
            case 1:
                if (mLd_PlayerManKindCheck() == NATIVE && mQst_CheckLimitOver(&delivery->base) == TRUE && mNpc_SearchAnimalPersonalID(&delivery->sender) == -1) {
                    mQst_ClearDelivery(delivery, 1);
                }
                break;
        }
    }
}

static void aQMgr_move_own_delivery_lost(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist) {
    int bx = 1;
    int bz = 1;

    if (regist != NULL && regist->quest_info != NULL) {
        mQst_delivery_c* delivery = (mQst_delivery_c*)regist->quest_info;
        switch (delivery->base.progress) {
            case 3:
                if (mQst_CheckLostClearTime(&delivery->base.time_limit, Common_GetPointer(time.rtc_time)) == TRUE &&
                    mQst_GetLostBkNum(&bx, &bz) == TRUE && (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE2_FG || mFI_CheckBgDma(bx, bz) == FALSE)) {
                    mQst_ClearLostQuest();
                }
                break;

            case 1:
                if (mQst_CheckLimitOver(&delivery->base) == TRUE) {
                    mQst_ClearDelivery(delivery, 1);
                }
                break;
        }
    }
}

static int aQMgr_actor_check_fin_qbox(mQst_base_c* quest_info, Animal_c* animal) {
    int ret = FALSE;
    if (quest_info->progress == 2) {
        ret = TRUE;
    }
    return ret;
}

#include "../src/actor/ac_quest_errand.c_inc"
#include "../src/actor/ac_quest_contest.c_inc"

static void aQMgr_clear_talk_wait_info(aQMgr_talk_wait_info_c* wait_info) {
    bzero(wait_info, sizeof(aQMgr_talk_wait_info_c));
}

static int aQMgr_actor_move_talk_sub_no_wait(QUEST_MANAGER_ACTOR* manager) {
    return TRUE;
}

static int aQMgr_actor_move_talk_sub_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
        if (manager->wait_info.flags[2] == FALSE) {
            manager->wait_info.flags[2] = TRUE;
            res = TRUE;
        }
    }
    else {
        manager->wait_info.flags[2] = FALSE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_msg_disappear_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (mMsg_Check_main_wait(mMsg_Get_base_window_p()) == TRUE) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_msg_appear_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (mMsg_Check_not_series_main_wait(mMsg_Get_base_window_p()) == TRUE) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_button_wait(QUEST_MANAGER_ACTOR* manager) {int res = FALSE;
    if (mMsg_Check_MainNormal(mMsg_Get_base_window_p()) == FALSE) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_hand_item_wait(QUEST_MANAGER_ACTOR* manager) {
    Submenu* submenu = manager->submenu;
    int res = FALSE;

    if (submenu->open_flag == FALSE) {
        manager->handover_item = submenu->item_p->item;
        res = TRUE;

        if (manager->mail_memory != NULL) {
            mNpc_Mail2AnimalMail(&manager->mail_memory->letter, &manager->mail);
            manager->mail_memory->letter_info.exists = TRUE;
        }
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_npc_hand_item_wait(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_set_npc_putaway(manager);
}

static int aQMgr_actor_move_talk_sub_item_wait(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_check_npc_hand_item();
}

static int aQMgr_actor_move_talk_sub_demo_order_wait(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_order_c* order = &manager->demo_order;
    int res = FALSE;
    int i;
    
    for (i = 0; i < mDemo_ORDER_VALUE_MAX; i++) {
        u16 value = mDemo_Get_OrderValue(mDemo_ORDER_QUEST, i);

        if (value != 0) {
            order->type = i;
            order->value = value;
            mDemo_Set_OrderValue(mDemo_ORDER_QUEST, i, 0);
            res = TRUE;
            break;
        }
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_npc_hand_item_wait_msg_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;
    
    if (manager->wait_info.flags[0] == FALSE) {
        manager->wait_info.flags[0] = aQMgr_set_npc_putaway(manager);
        mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    }

    if (manager->wait_info.flags[1] == FALSE) {
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
            manager->wait_info.flags[1] = TRUE;
        }
    }

    if (manager->wait_info.flags[0] == TRUE && manager->wait_info.flags[1] == TRUE) {
        manager->wait_info.flags[0] = FALSE;
        manager->wait_info.flags[1] = FALSE;
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_item_wait_end(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;
    
    if (manager->wait_info.flags[0] == FALSE) {
        manager->wait_info.flags[0] = aQMgr_set_npc_putaway(manager);
    }

    if (manager->wait_info.flags[0] == TRUE) {
        manager->wait_info.flags[1] = aQMgr_check_npc_hand_item();
    }

    if (manager->wait_info.flags[0] == TRUE && manager->wait_info.flags[1] == TRUE) {
        manager->wait_info.flags[0] = FALSE;
        manager->wait_info.flags[1] = FALSE;
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_item_player_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;
    
    if (manager->wait_info.flags[0] == FALSE) {
        manager->wait_info.flags[0] = aQMgr_check_npc_hand_item();
    }

    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    if (manager->wait_info.flags[0] == TRUE && mPlib_check_player_actor_main_index_RecieveMove(gamePT) == FALSE) {
        mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
        manager->wait_info.flags[0] = FALSE;
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_open_qbox_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;
    
    if (manager->wait_info.flags[0] == FALSE && mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 7) != 0) {
        mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 7, 0);
        manager->wait_info.flags[0] = TRUE;
    }

    if (manager->wait_info.flags[1] == FALSE && mMsg_CHECK_MAINNORMALCONTINUE() == TRUE) {
        mMsg_SET_LOCKCONTINUE();
        manager->wait_info.flags[1] = TRUE;
    }

    if (manager->wait_info.flags[0] == TRUE && manager->wait_info.flags[1] == TRUE) {
        manager->wait_info.flags[0] = FALSE;
        manager->wait_info.flags[1] = FALSE;
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_wait_choice(QUEST_MANAGER_ACTOR* manager) {
    int ret = FALSE;
    int choice = mChoice_GET_CHOSENUM();

    if (choice != -1) {
        ret = TRUE;
    }

    return ret;
}

static void aQMgr_select_talk(QUEST_MANAGER_ACTOR* manager) {
    u32 event_id;
    Animal_c* animal = ((NPC_ACTOR*)*manager->client)->npc_info.animal_orig;

    event_id = mEv_SAVED_FJOPENQUEST_PLR0 + Common_Get(player_no);
    aQMgr_actor_init_quest(manager);
    aQMgr_clear_talk_wait_info(&manager->wait_info);

    if ((animal != NULL && mNpc_CheckIslandAnimal(animal) == TRUE) || (mLd_PlayerManKindCheck() == FALSE && mEv_CheckEvent(event_id) == TRUE)) {
        manager->talk_type = aQMgr_TALK_KIND_QUEST;
    }
    else if (mEv_CheckFirstJob() == TRUE) {
        manager->talk_type = aQMgr_TALK_KIND_FIRST_JOB;
    }
    else {
        manager->talk_type = aQMgr_TALK_KIND_QUEST;
    }

    *manager->mode = aQMgr_MODE_MOVE_TALK;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_TALK_INIT_OVL);
}

static int aQMgr_talk_init(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (manager->talk_init_proc != NULL) {
        (*manager->talk_init_proc)(manager);
        res = TRUE;
    }

    return res;
}

typedef int (*aQMgr_TALK_SUB_PROC)(QUEST_MANAGER_ACTOR*);

static int aQMgr_talk_sub(QUEST_MANAGER_ACTOR* manager) {
    int sub_mode = manager->sub_talk_state;
    static aQMgr_TALK_SUB_PROC talk_sub_proc[aQMgr_TALK_SUB_STATE_NUM] = { 
        &aQMgr_actor_move_talk_sub_wait,
        &aQMgr_actor_move_talk_sub_msg_disappear_wait,
        &aQMgr_actor_move_talk_sub_msg_appear_wait,
        &aQMgr_actor_move_talk_sub_button_wait,
        &aQMgr_actor_move_talk_sub_hand_item_wait,
        &aQMgr_actor_move_talk_sub_npc_hand_item_wait,
        &aQMgr_actor_move_talk_sub_item_wait,
        &aQMgr_actor_move_talk_sub_demo_order_wait,
        &aQMgr_actor_move_talk_sub_no_wait,
        &aQMgr_actor_move_talk_sub_npc_hand_item_wait_msg_wait,
        &aQMgr_actor_move_talk_sub_item_wait_end,
        &aQMgr_actor_move_talk_sub_item_player_wait,
        &aQMgr_actor_move_talk_sub_open_qbox_wait,
        &aQMgr_actor_move_talk_sub_wait_choice,
    };

    int res = (*talk_sub_proc[sub_mode])(manager);

    if (res == TRUE) {
        manager->talk_state = aQMgr_TALK_STATE_INIT;
    }

    return res;
}

typedef int (*aQMgr_TALK_PROC)(QUEST_MANAGER_ACTOR*);

static void aQMgr_move_talk(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    
    if (mDemo_Get_talk_actor() == client) {
        static aQMgr_TALK_PROC talk_proc[aQMgr_TALK_STATE_NUM] = {
            &aQMgr_talk_init,
            &aQMgr_talk_sub,
        };
        int sub_res;

        aQMgr_actor_change_talk_init_ovl(manager);
        sub_res = (*talk_proc[aQMgr_TALK_STATE_SUB])(manager);
        mDemo_Set_OrderValue(mDemo_ORDER_QUEST, 0, 0);

        if (sub_res == TRUE) {
            (*talk_proc[aQMgr_TALK_STATE_INIT])(manager);
        }

        aQMgr_talk_clear_talk_order(&manager->demo_order);
    }

    if (mDemo_CheckDemo() == FALSE || mDemo_Check(mDemo_TYPE_TALK, client) == FALSE) {
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CLEAR_TALK_INFO);
        *manager->mode = aQMgr_MODE_TALK_FIN;
        manager->aitekara_msg_flag = FALSE;
        aQMgr_clear_talk_init_ovl(manager);

        if (client != NULL && client->part == ACTOR_PART_NPC) {
            Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal_orig;

            if (animal != NULL) {
                Anmmem_c* memory;
                int memory_idx = mNpc_GetAnimalMemoryIdx(&Now_Private->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

                if (memory_idx != -1) {
                    memory = animal->memories + memory_idx;
                    lbRTC_TimeCopy(&memory->last_speak_time, Common_GetPointer(time.rtc_time));

                    if (mNpc_CheckIslandAnimal(animal) == FALSE) {
                        mLd_CopyLandName(memory->memuni.land.name, Save_Get(land_info).name);
                        memory->memuni.land.id = Save_Get(land_info).id;
                    }

                    memory->saved_town_tune = Save_Get(melody);
                }
            }
        }

        {
            Animal_c* animal = ((NPC_ACTOR*)*manager->client)->npc_info.animal_orig;
            int animal_idx = mNpc_SearchAnimalPersonalID(&animal->id);

            if (mNpc_CheckIslandAnimal(animal) == TRUE) {
                mNpc_TalkEndMove(mNpc_ISLANDER_NO, animal->id.looks);
            }
            else {
                mNpc_TalkEndMove(animal_idx, animal->id.looks);
            }
        }
    }
}

static void aQMgr_talk_start_kamakura_common(QUEST_MANAGER_ACTOR* manager, u8 step) {
    aQMgr_clear_talk_wait_info(&manager->wait_info);
    *manager->mode = aQMgr_MODE_MOVE_TALK;
    manager->talk_step = step;
    manager->talk_type = aQMgr_TALK_KIND_NORMAL;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_TALK_INIT_OVL);
    aQMgr_talk_init(manager);
}

static void aQMgr_talk_start_kamakura_hello(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 8);
}

static void aQMgr_talk_start_kamakura(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 9);
}

static void aQMgr_talk_start_summercamp_hello(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 13);
}

static void aQMgr_talk_start_summercamp(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 14);
}

static void aQMgr_talk_start_group_hello(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 10);
}

static void aQMgr_talk_start_group(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 11);
}

static void aQMgr_talk_start_aitekara(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 15);
}

typedef void (*aQMgr_MOVE_PROC)(QUEST_MANAGER_ACTOR*);
static void aQMgr_actor_move_main(ACTOR* actorx, GAME* game) {
    QUEST_MANAGER_ACTOR* manager = (QUEST_MANAGER_ACTOR*)actorx;
    static aQMgr_MOVE_PROC move_proc[aQMgr_MODE_NUM] = {
        &aQMgr_actor_move_wait,
        &aQMgr_select_talk,
        &aQMgr_move_talk,
        &aQMgr_actor_move_talk_fin,
        &aQMgr_talk_start_kamakura_hello,
        &aQMgr_talk_start_kamakura,
        &aQMgr_talk_start_group_hello,
        &aQMgr_talk_start_group,
        &aQMgr_talk_start_summercamp_hello,
        &aQMgr_talk_start_summercamp,
        &aQMgr_talk_start_aitekara,
    };

    u8 mode = *manager->mode;

    if (mEv_IsNotTitleDemo()) {
        (*move_proc[mode])(manager);
    }

    {
        GRAPH* graph = game->graph;
        gfxprint_t gfxprint;
        Gfx* gfx;
        gfxprint_t* gfxprint_p = &gfxprint;
        Gfx* gfx_work;

        if (ZURUMODE2_ENABLED()) {
            gfxprint_init(gfxprint_p);
            
            OPEN_DISP(graph);
            gfx = NOW_POLY_OPA_DISP;
            gfx_work = gfxopen(gfx);

            gSPDisplayList(NEXT_OVERLAY_DISP, gfx_work);
            gfxprint_open(gfxprint_p, gfx_work);
            gfxprint_color(gfxprint_p, 245, 50, 50, 255);
            gfxprint_locate8x8(gfxprint_p, 22, 3);
            gfxprint_printf(gfxprint_p, "msg no :");
            gfxprint_locate8x8(gfxprint_p, 30, 3);
            gfxprint_printf(gfxprint_p, "%5d", mFRm_get_msg_idx());

            if (REGADDR(GENREG, 49) == 0 && REGADDR(mREG, 29) > 0) {
                gfxprint_color(gfxprint_p, 245, 50, 50, 255);
                gfxprint_locate8x8(gfxprint_p, 25, 4);
                gfxprint_printf(gfxprint_p, "kanji : %d", REGADDR(mREG, 29) - 1);
            }
                
            if (mNpc_GetSickAnimalIdx() != -1) {
                int sick_idx = mNpc_GetSickAnimalIdx();
                Animal_c* sick_animal = Save_GetPointer(animals[sick_idx]);

                gfxprint_color(gfxprint_p, 240, 255, 240, 255);
                gfxprint_locate8x8(gfxprint_p, 30, 5);
                gfxprint_printf(gfxprint_p, "%d %d", sick_animal->home_info.bx, sick_animal->home_info.bz);
            }

            {
                mEv_gst_common_c* ghost_common = (mEv_gst_common_c*)mEv_get_common_area(mEv_EVENT_GHOST, 55);

                if (ghost_common != NULL) {
                    int i;
                    
                    gfxprint_color(gfxprint_p, 45, 250, 50, 255);

                    for (i = 0; i < mEv_GHOST_HITODAMA_NUM; i++) {
                        gfxprint_locate8x8(gfxprint_p, 30, 19 + i);
                        gfxprint_printf(gfxprint_p, "%3d,%3d", ghost_common->hitodama_block_data.block_x[i], ghost_common->hitodama_block_data.block_z[i]);
                    }
                }
            }

            {
                mAGrw_AllGrow_c* allgrow = Save_GetPointer(allgrow_ss_pos_info);
                mAGrw_SSPosInfo_c* reset_stone_pos = &Save_Get(allgrow_ss_pos_info).reset_stone_pos;
                lbRTC_ymd_c ymd;

                ymd.year = Common_Get(time.rtc_time.year);
                ymd.month = Common_Get(time.rtc_time.month);
                ymd.day = Common_Get(time.rtc_time.day);
                if (lbRTC_GetIntervalDays2(&ymd, &allgrow->reset_stone_date) == 0 && mAGrw_CheckFreeSSPosInfo_com(reset_stone_pos) == FALSE) {
                    gfxprint_color(gfxprint_p, 250, 250, 250, 255);
                    gfxprint_locate8x8(gfxprint_p, 30, 25);
                    gfxprint_printf(gfxprint_p, "%3d,%3d", reset_stone_pos->block_x, reset_stone_pos->block_z);
                }
            }

#if VERSION >= VER_GAEJ01_01
            {
                int bx = 0;
                int bz = 0;

                gfxprint_color(gfxprint_p, 250, 250, 250, 255);
                gfxprint_locate8x8(gfxprint_p, 28, 26);
                
                if (mQst_GetLostBkNum(&bx, &bz) == TRUE) {
                    mActor_name_t* fg_p = Save_Get(fg[bz - 1][bx - 1]).items[0];
                    int ux = 0;
                    int uz = 0;
                    int i;

                    for (i = 0; i < UT_TOTAL_NUM; i++) {
                        if (IS_ITEM_LOST_ITEM(*fg_p)) {
                            ux = i & 0xF;
                            uz = (i >> 4) & 0xF;
                            break;
                        }

                        fg_p++;
                    }

                    gfxprint_printf(gfxprint_p, "%1d,%1d,%02d,%02d", bx, bz, ux, uz);
                } else {
                    gfxprint_printf(gfxprint_p, "-,-,--,--");
                }
            }
#endif

            gfx_work = gfxprint_close(gfxprint_p);
            gSPEndDisplayList(gfx_work++);
            gfxclose(gfx, gfx_work);
            SET_POLY_OPA_DISP(gfx_work);
            CLOSE_DISP(graph);

            gfxprint_cleanup(gfxprint_p);

            if ((gamePT->pads[PAD2].on.button & BUTTON_Z) == BUTTON_Z) {
                int prev_remove_idx = Save_Get(remove_animal_idx);
                Save_Set(remove_animal_idx, 0xFF);
                mNpc_SetRemoveAnimalNo(Save_GetPointer(remove_animal_idx), Save_Get(animals), prev_remove_idx);
            }
        }
    }
}

static void aQMgr_actor_ct(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    QUEST_MANAGER_ACTOR* manager = (QUEST_MANAGER_ACTOR*)actorx;

    if (CLIP(quest_manager_clip) == NULL) {
        CLIP(quest_manager_clip) = (aQMgr_Clip_c*)zelda_malloc(sizeof(aQMgr_Clip_c));
    }

    CLIP(quest_manager_clip)->talk_request_proc = &aQMgr_actor_talk_request;
    CLIP(quest_manager_clip)->talk_start_proc = &aQMgr_actor_talk_start;
    CLIP(quest_manager_clip)->talk_check_proc = &aQMgr_actor_talk_check;
    CLIP(quest_manager_clip)->looks2name_proc = &aQMgr_actor_looks2name;
    CLIP(quest_manager_clip)->race2name_proc = &aQMgr_actor_race2name;
    CLIP(quest_manager_clip)->add_relation_proc = &aQMgr_actor_add_relation;

    l_client_p = NULL;
    l_quest_manager_mode = aQMgr_MODE_NORMAL;
    l_quest_memory_p = NULL;
    l_quest_actor_p = NULL;
    l_quest_manager_hello = FALSE;

    manager->client = &l_client_p;
    manager->memory = &l_quest_memory_p;
    manager->submenu = &play->submenu;
    manager->mode = &l_quest_manager_mode;
    manager->talk_state = aQMgr_TALK_STATE_INIT;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    
    aQMgr_talk_common_clear_talk_info(manager);
    aQMgr_actor_clear_regist(manager->regist, aQMgr_REGIST_NUM);
    manager->regist_idx = -1;
    manager->regist_use_no = 0;
    aQMgr_actor_contest_sick_clear();
    aQMgr_actor_init_quest(manager);
    manager->talk_common_proc = &aQMgr_talk_common_proc;
    manager->clear_regist_proc = &aQMgr_actor_clear_regist;
    manager->regist_quest_proc = &aQMgr_actor_regist_quest;
    manager->get_time_kind_proc = &aQMgr_get_time_kind;
    manager->get_common_msg_proc = &aQMgr_talk_common_get_common_msg;
    manager->check_select_msg_proc = &aQMgr_actor_common_check_select_msg;
    bzero(manager->errand_next, sizeof(manager->errand_next));
    manager->clip = NULL;
    aQMgr_clear_talk_init_ovl(manager);
    aQMgr_clear_talk_wait_info(&manager->wait_info);
    l_aQMgr_hand_start = FALSE;
    l_quest_actor_p = (QUEST_MANAGER_ACTOR*)actorx; // l_quest_actor_p is probably just ACTOR*
    mem_clear(manager->last_strings, sizeof(manager->last_strings), 0xFF);
    manager->give_item = EMPTY_NO;
    manager->talk_about_animal_idx = -1;
    manager->still_reward_but_field_quest_cancel = FALSE;
    manager->aitekara_msg_flag = FALSE;
}

static void aQMgr_actor_dt(ACTOR* actorx, GAME* game) {
    QUEST_MANAGER_ACTOR* manager = (QUEST_MANAGER_ACTOR*)actorx;

    if (CLIP(quest_manager_clip) != NULL) {
        zelda_free(CLIP(quest_manager_clip));
        CLIP(quest_manager_clip) = NULL;
    }

    if (manager->clip != NULL) {
        zelda_free(manager->clip);
    }
}

typedef void (*aQMgr_SAVE_PROC)(aQMgr_regist_c*);

static void aQMgr_actor_save(ACTOR* actorx, GAME* game) {
    QUEST_MANAGER_ACTOR* manager = (QUEST_MANAGER_ACTOR*)actorx;
    aQMgr_regist_c* regist = manager->regist;
    static aQMgr_SAVE_PROC save_proc[mQst_QUEST_TYPE_NUM] = {
        (aQMgr_SAVE_PROC)&none_proc1,
        (aQMgr_SAVE_PROC)&none_proc1,
        &aQMgr_save_contest
    };
    int i;

    aQMgr_actor_init_quest(manager);
    for (i = 0; i < aQMgr_REGIST_NUM; i++) {
        if (regist->quest_info != NULL) {
            int type = regist->quest_info->quest_type;

            if (type >= 0 && type < mQst_QUEST_TYPE_NUM) {
                (*save_proc[type])(regist);
            }
        }

        regist++;
    }
}

ACTOR_PROFILE Quest_Manager_Profile = {
    mAc_PROFILE_QUEST_MANAGER,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(QUEST_MANAGER_ACTOR),
    &aQMgr_actor_ct,
    &aQMgr_actor_dt,
    &aQMgr_actor_move_main,
    mActor_NONE_PROC1,
    &aQMgr_actor_save
};
