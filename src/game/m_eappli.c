#include "m_eappli.h"

#include "m_common_data.h"
#include "m_private.h"
#include "lb_rtc.h"
#include "m_scene_table.h"
#include "m_malloc.h"
#include "jsyswrap.h"

extern void mEA_InitLetterCardE() {
    mPr_carde_data_c* carde_data = &Now_Private->ecard_letter_data;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    /* only reset if current date isn't same as last scan date */
    u16 year = carde_data->letter_send_date.year;
    u8 month = carde_data->letter_send_date.month;
    u8 day = carde_data->letter_send_date.day;
    if (rtc_time->year != year || rtc_time->month != month || rtc_time->day != day) {
        int i;
        for (i = 0; i < mEA_ECARD_LETTER_NUM; i++) {
            carde_data->card_letters_sent[i] = 0;
        }
    }
}

extern int mEA_CheckLetterCardE(int card_no) {
    mPr_carde_data_c* card_data = &Now_Private->ecard_letter_data;
    int index = card_no < mEA_CARDE_TOTAL_NUM ? card_no : mEA_CARDE_TOTAL_NUM - 1;

    if (index == mEA_CARDE_TOTAL_NUM - 1) {
        return ((card_data->card_letters_sent[index >> 3] >> (index & 7)) & 1) ? 2 : 0;
    }

    return (card_data->card_letters_sent[index >> 3] >> (index & 7)) & 1;
}

extern void mEA_SetLetterCardE(int card_no) {
    mPr_carde_data_c* card_data = &Now_Private->ecard_letter_data;
    int index = card_no < mEA_CARDE_TOTAL_NUM ? card_no : mEA_CARDE_TOTAL_NUM - 1;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    card_data->card_letters_sent[index >> 3] |= 1 << (index & 7);
    card_data->letter_send_date.year = rtc_time->year;
    card_data->letter_send_date.month = rtc_time->month;
    card_data->letter_send_date.day = rtc_time->day;
}

extern void mEA_GetCardDLProgram() {
    if (Save_Get(scene_no) != SCENE_TITLE_DEMO && Common_Get(carde_program_p) == NULL) {
        Common_Set(carde_program_size, JW_GetResSizeFileNo(RESOURCE_EAPPLI));
        Common_Set(carde_program_p, (u8*)zelda_malloc_align(Common_Get(carde_program_size), 32));
        _JW_GetResourceAram(JW_GetAramAddress(RESOURCE_EAPPLI),
                            Common_Get(carde_program_p), Common_Get(carde_program_size));
    }
}

extern void mEA_CleanCardDLProgram() {
    if (Common_Get(carde_program_p) != NULL) {
        zelda_free(Common_Get(carde_program_p));
        Common_Set(carde_program_p, NULL);
        Common_Set(carde_program_size, 0);
    }
}

extern u8* mEA_dl_carde_program_p() {
    return Common_Get(carde_program_p);
}

extern size_t mEA_dl_carde_program_size() {
    return Common_Get(carde_program_size);
}

static void mEA_get_character_card_header(u8* series, int* card_set_idx, int* index, u8* card_data) {
    static char series_code[] = "ABCDEFGHIJKLMNOP";
    u16 info = (card_data[1] << 8) | card_data[0];

    *series = series_code[(info >> 12) & 0xF];
    *card_set_idx = (info >> 11) & 1; // Part of two-set cards like Pelly & Phyllis or Timmy & Tommy
    *index = info & 0x1FF;
}

typedef struct animal_carde_info_s {
    u16 id;
    mActor_name_t npc_id;
    u8 paper_idx;
    mActor_name_t present;
} mEA_animal_carde_info_c;

#define mEA_CARD(series, card_set_idx, index) ((((u32)(series) - 'A') & 0xF) << 12) | (((card_set_idx) & 1) << 11) | ((index) & 0x1FF)

// clang-format off
static mEA_animal_carde_info_c mEA_carde_convert_dat[mEA_CHARACTER_PLUS_CARDE_NUM] = {
    { mEA_CARD('A', 0,   1), SP_NPC_TOTAKEKE      , 0x10, FTR_START(FTR_NOG_MIKANBOX) },
    { mEA_CARD('A', 0,   2), SP_NPC_GUIDE         , 0x00, FTR_START(FTR_SUM_GLOBE01) },
    { mEA_CARD('A', 0,   3), SP_NPC_STATION_MASTER, 0x37, FTR_START(FTR_NOG_RAIL) },
    { mEA_CARD('A', 0,   4), SP_NPC_SHOP_MASTER   , 0x37, FTR_START(FTR_KON_MASAJI) },
    { mEA_CARD('A', 0,   5), SP_NPC_EV_SONCHO     , 0x3E, FTR_START(FTR_NKH_TABLE02) },
    { mEA_CARD('A', 0,   6), SP_NPC_MAJIN         , 0x03, FTR_START(FTR_IKU_SAWHOUSEV) },
    { mEA_CARD('A', 0,   7), SP_NPC_CURATOR       , 0x18, FTR_START(FTR_SUM_CONT_CHEST01) },
    { mEA_CARD('A', 0,   8), SP_NPC_NEEDLEWORK1   , 0x20, FTR_START(FTR_SUM_MISIN01) },
    { mEA_CARD('A', 0,   9), SP_NPC_NEEDLEWORK0   , 0x2B, FTR_START(FTR_SUM_CONT_CHEST02) },
    { mEA_CARD('A', 0,  10), SP_NPC_SENDO         , 0x2B, FTR_START(FTR_KON_LOCKER) },
    { mEA_CARD('A', 0,  11), NPC_BOB              , 0x37, FTR_START(FTR_KOB_NCUBE) },
    { mEA_CARD('A', 0,  12), NPC_MITZI            , 0x28, FTR_START(FTR_SUM_RATAN_CHEST03) },
    { mEA_CARD('A', 0,  13), NPC_PUNCHY           , 0x31, FTR_START(FTR_KON_MILK) },
    { mEA_CARD('A', 0,  14), NPC_ANKHA            , 0x23, FTR_START(FTR_SUM_WHI_CHEST01) },
    { mEA_CARD('A', 0,  15), NPC_PAOLO            , 0x04, FTR_START(FTR_IKE_JPN_IRORI01) },
    { mEA_CARD('A', 0,  16), NPC_ELINA            , 0x26, FTR_START(FTR_KON_TUBO) },
    { mEA_CARD('A', 0,  17), NPC_TEDDY            , 0x04, FTR_START(FTR_SUM_DESK01) },
    { mEA_CARD('A', 0,  18), NPC_PORTIA           , 0x24, FTR_START(FTR_SUM_WHI_MIRROR) },
    { mEA_CARD('A', 0,  19), NPC_PEANUT           , 0x28, FTR_START(FTR_ARI_KITCHEN01) },
    { mEA_CARD('A', 0,  20), NPC_BLISS            , 0x00, ITM_CLOTH026 },
    { mEA_CARD('A', 0,  21), NPC_BUNNIE           , 0x1B, FTR_START(FTR_SUM_DOLL02) },
    { mEA_CARD('A', 0,  22), NPC_OHARE            , 0x00, FTR_START(FTR_SUM_CONPO01) },
    { mEA_CARD('A', 0,  23), NPC_BILL             , 0x1B, FTR_START(FTR_SUM_PET01) },
    { mEA_CARD('A', 0,  24), NPC_JOEY             , 0x3E, FTR_START(FTR_KON_MASAJI) },
    { mEA_CARD('A', 0,  25), NPC_MAELLE           , 0x24, FTR_START(FTR_SUM_OLDSOFA01) },
    { mEA_CARD('A', 0,  26), NPC_BIFF             , 0x07, FTR_START(FTR_SUM_GUITAR02) },
    { mEA_CARD('A', 0,  27), NPC_LOBO             , 0x36, FTR_START(FTR_SUM_GLOBE01) },
    { mEA_CARD('A', 0,  28), NPC_DOBIE            , 0x36, FTR_START(FTR_KON_CHOUZU03) },
    { mEA_CARD('A', 0,  29), NPC_RASHER           , 0x03, FTR_START(FTR_SUM_BLA_TABLE01) },
    { mEA_CARD('A', 0,  30), NPC_PIGLEG           , 0x29, FTR_START(FTR_NOG_FAN01) },
    { mEA_CARD('A', 0,  31), NPC_RHODA            , 0x24, FTR_START(FTR_SUM_WHI_MIRROR) },
    { mEA_CARD('A', 0,  32), NPC_PLUCKY           , 0x27, FTR_START(FTR_SUM_LOG_CHAIR02) },
    { mEA_CARD('A', 0,  33), NPC_TAD              , 0x25, FTR_START(FTR_ARI_ISU01) },
    { mEA_CARD('A', 0,  34), NPC_DRIFT            , 0x27, FTR_START(FTR_ARI_TABLE01) },
    { mEA_CARD('A', 0,  35), NPC_CHEVRE           , 0x2B, FTR_START(FTR_SUM_DOLL02) },
    { mEA_CARD('A', 0,  36), NPC_BANGLE           , 0x28, FTR_START(FTR_KON_AMECLOCK) },
    { mEA_CARD('A', 0,  37), NPC_ROWAN            , 0x23, FTR_START(FTR_SUM_LOG_TABLE01) },
    { mEA_CARD('A', 0,  38), NPC_BUCK             , 0x18, FTR_START(FTR_SUM_ASI_CHEST01) },
    { mEA_CARD('A', 0,  39), NPC_ANNALISE         , 0x23, FTR_START(FTR_SUM_WHI_LANP) },
    { mEA_CARD('A', 0,  40), NPC_BLUEBEAR         , 0x25, FTR_START(FTR_SUM_GUITAR03) },
    { mEA_CARD('A', 0,  41), NPC_JUNE             , 0x1D, FTR_START(FTR_SUM_POPCHAIR02) },
    { mEA_CARD('A', 0,  42), NPC_CHERI            , 0x28, FTR_START(FTR_SUM_TOTEMP03) },
    { mEA_CARD('A', 0,  43), NPC_APOLLO           , 0x07, FTR_START(FTR_SUM_BILLIADS) },
    { mEA_CARD('A', 0,  44), NPC_CUBE             , 0x25, FTR_START(FTR_SUM_POPCHAIR02) },
    { mEA_CARD('A', 0,  45), NPC_BOOMER           , 0x29, FTR_START(FTR_TAK_ASTRO) },
    { mEA_CARD('A', 0,  46), NPC_FLASH            , 0x27, FTR_START(FTR_SUM_BLUE_BENCH01) },
    { mEA_CARD('A', 0,  47), NPC_YODEL            , 0x04, FTR_START(FTR_NKH_TABLE01) },
    { mEA_CARD('A', 0,  48), NPC_FAITH            , 0x1B, ITM_CRACKER },
    { mEA_CARD('A', 0,  49), NPC_BUD              , 0x26, FTR_START(FTR_SUM_CONGA01) },
    { mEA_CARD('A', 0,  50), NPC_FLOSSIE          , 0x08, FTR_START(FTR_SUM_GRE_TABLE01) },
    { mEA_CARD('A', 0,  51), NPC_PINKY            , 0x1D, FTR_START(FTR_KON_TUBO3) },
    { mEA_CARD('A', 0,  52), NPC_NIBBLES          , 0x26, FTR_START(FTR_SUM_MIZUNOMI) },
    { mEA_CARD('A', 0,  53), NPC_DOTTY            , 0x27, FTR_START(FTR_TAK_APOLLO1) },
    { mEA_CARD('A', 0,  54), NPC_SCOOT            , 0x31, FTR_START(FTR_ARI_REIZOU01) },
    { mEA_CARD('A', 0,  55), NPC_BORIS            , 0x03, FTR_START(FTR_SUM_KISHA) },
    { mEA_CARD('A', 0,  56), NPC_GOOSE            , 0x31, FTR_START(FTR_SUM_CONT_BED01) },
    { mEA_CARD('A', 0,  57), NPC_ADMIRAL          , 0x3E, FTR_START(FTR_KON_MUSYA) },
    { mEA_CARD('A', 0,  58), NPC_KODY             , 0x20, FTR_START(FTR_SUM_TOTEMP02) },
    { mEA_CARD('A', 0,  59), NPC_PIERCE           , 0x29, ITM_CLOTH086 },
    { mEA_CARD('A', 0,  60), NPC_PUCK             , 0x10, FTR_START(FTR_SUM_BLUE_CLK) },
    { mEA_CARD('A', 0,  61), NPC_BONES            , 0x20, FTR_START(FTR_SUM_CHAIR01) },
    { mEA_CARD('A', 0,  62), NPC_DORA             , 0x36, FTR_START(FTR_SUM_MISIN01) },
    { mEA_CARD('A', 0,  63), NPC_SPIKE            , 0x07, FTR_START(FTR_TAK_TEKKIN) },
    { mEA_CARD('A', 0,  64), NPC_JANE             , 0x08, FTR_START(FTR_SUM_LICCALANP) },
    { mEA_CARD('A', 0,  65), SP_NPC_SHOP_MASTER   , 0x37, ITM_CLOTH016 },
    { mEA_CARD('A', 0,  66), SP_NPC_POST_GIRL     , 0x00, FTR_START(FTR_SUM_UWA_VASE02) },
    { mEA_CARD('A', 0,  67), SP_NPC_POLICE        , 0x04, FTR_START(FTR_KOB_PIPEISU) },
    { mEA_CARD('A', 0,  68), SP_NPC_CARPETPEDDLER , 0x06, ITM_CARPET45 },
    { mEA_CARD('A', 0,  69), SP_NPC_KABUPEDDLER   , 0x1F, FTR_START(FTR_KON_MASAJI) },
    { mEA_CARD('A', 0,  70), SP_NPC_SANTA         , 0x16, ITM_CLOTH037 },
    { mEA_CARD('A', 0,  71), SP_NPC_BROKER        , 0x36, FTR_START(FTR_NKH_LIGHT01) },
    { mEA_CARD('A', 0,  72), NPC_OLIVIA           , 0x24, FTR_START(FTR_SUM_WHI_MIRROR) },
    { mEA_CARD('A', 0,  73), NPC_STINKY           , 0x3B, FTR_START(FTR_SUM_KOKUBAN) },
    { mEA_CARD('A', 0,  74), NPC_PURRL            , 0x1B, FTR_START(FTR_SUM_PET01) },
    { mEA_CARD('A', 0,  75), NPC_ELOISE           , 0x08, FTR_START(FTR_SUM_GRE_LANP01) },
    { mEA_CARD('A', 0,  76), NPC_EUNICE           , 0x20, FTR_START(FTR_SUM_TV01) },
    { mEA_CARD('A', 0,  77), NPC_BAABARA          , 0x0C, FTR_START(FTR_SUM_OLDCLK01) },
    { mEA_CARD('A', 0,  78), NPC_DOZER            , 0x30, FTR_START(FTR_SUM_CLBED02) },
    { mEA_CARD('A', 0,  79), NPC_GRIZZLY          , 0x03, FTR_START(FTR_NKH_BOX01) },
    { mEA_CARD('A', 0,  80), NPC_COOKIE           , 0x28, FTR_START(FTR_SUM_UWA_VASE02) },
    { mEA_CARD('A', 0,  81), NPC_BUTCH            , 0x23, FTR_START(FTR_SUM_BLA_DESK01) },
    { mEA_CARD('A', 0,  82), NPC_FILBERT          , 0x35, FTR_START(FTR_SUM_SABO02) },
    { mEA_CARD('A', 0,  83), NPC_SALLY            , 0x2B, FTR_START(FTR_SUM_FRUITCHEST03) },
    { mEA_CARD('A', 0,  84), NPC_DOC              , 0x29, FTR_START(FTR_SUM_KOKUBAN) },
    { mEA_CARD('A', 0,  85), NPC_COCO             , 0x36, FTR_START(FTR_IKE_JPN_TANSU01) },
    { mEA_CARD('A', 0,  86), NPC_POMPOM           , 0x25, FTR_START(FTR_ARI_KITCHEN01) },
    { mEA_CARD('A', 0,  87), NPC_DERWIN           , 0x31, FTR_START(FTR_NOG_DARUMAL) },
    { mEA_CARD('A', 0,  88), NPC_BUBBLES          , 0x0E, FTR_START(FTR_SUM_FRUITCHAIR03) },
    { mEA_CARD('A', 0,  89), NPC_CHIEF            , 0x2C, FTR_START(FTR_KON_WACLOCK) },
    { mEA_CARD('A', 0,  90), NPC_SAMSON           , 0x01, FTR_START(FTR_SUM_MIZUNOMI) },
    { mEA_CARD('A', 0,  91), NPC_LIMBERG          , 0x1F, FTR_START(FTR_KON_CHOUZU02) },
    { mEA_CARD('A', 0,  92), NPC_CURLY            , 0x32, FTR_START(FTR_SUM_SABO01) },
    { mEA_CARD('A', 0,  93), NPC_LUCY             , 0x2B, FTR_START(FTR_SUM_KAGAMOCHI) },
    { mEA_CARD('A', 0,  94), NPC_AVA              , 0x3C, FTR_START(FTR_SUM_LOG_TABLE02) },
    { mEA_CARD('A', 0,  95), NPC_LEIGH            , 0x06, FTR_START(FTR_SUM_LOG_BED01) },
    { mEA_CARD('A', 0,  96), NPC_CHUCK            , 0x03, FTR_START(FTR_SUM_GRE_CHAIR01) },
    { mEA_CARD('A', 0,  97), NPC_PATTY            , 0x09, FTR_START(FTR_SUM_RATAN_CHEST03) },
    { mEA_CARD('A', 0,  98), NPC_JAY              , 0x18, FTR_START(FTR_SUM_CHIKUON01) },
    { mEA_CARD('A', 0,  99), NPC_MIDGE            , 0x1E, FTR_START(FTR_SUM_LICCALANP) },
    { mEA_CARD('A', 0, 100), NPC_PUDDLES          , 0x27, FTR_START(FTR_SUM_FRUITTV01) },
    { mEA_CARD('A', 0, 101), NPC_LILY             , 0x0D, FTR_START(FTR_NOG_FAN01) },
    { mEA_CARD('A', 0, 102), NPC_CAMOFROG         , 0x00, FTR_START(FTR_DIN_TRIKERA_HEAD) },
    { mEA_CARD('A', 0, 103), NPC_BOOTS            , 0x31, FTR_START(FTR_SUM_ASI_CHAIR01) },
    { mEA_CARD('A', 0, 104), NPC_IGGY             , 0x36, FTR_START(FTR_NKH_TABLE02) },
    { mEA_CARD('A', 0, 105), NPC_TYBALT           , 0x20, FTR_START(FTR_KOB_PIPEISU) },
    { mEA_CARD('A', 0, 106), NPC_CYRANO           , 0x36, FTR_START(FTR_SUM_TAIKO01) },
    { mEA_CARD('A', 0, 107), NPC_YUKA             , 0x09, FTR_START(FTR_SUM_BOOKCHT01) },
    { mEA_CARD('A', 0, 108), NPC_ELMER            , 0x1B, FTR_START(FTR_SUM_CHIKUON01) },
    { mEA_CARD('A', 0, 109), NPC_PEACHES          , 0x25, FTR_START(FTR_IKE_JPN_KOTATU01) },
    { mEA_CARD('A', 0, 110), NPC_VLADIMIR         , 0x03, FTR_START(FTR_KOB_RIKA_DESK) },
    { mEA_CARD('A', 0, 111), NPC_PONCHO           , 0x32, FTR_START(FTR_SUM_CLASSICTABLE01) },
    { mEA_CARD('A', 0, 112), NPC_PEEWEE           , 0x07, FTR_START(FTR_SUM_TAIKO01) },
    { mEA_CARD('A', 0, 113), NPC_SPROCKET         , 0x3B, FTR_START(FTR_SUM_SHOUKAKI) },
    { mEA_CARD('A', 0, 114), NPC_MARCY            , 0x28, FTR_START(FTR_SUM_WC01) },
    { mEA_CARD('A', 0, 115), NPC_KITT             , 0x17, FTR_START(FTR_SUM_CLASSICCHEST02) },
    { mEA_CARD('A', 0, 116), NPC_BUZZ             , 0x23, FTR_START(FTR_SUM_GUITAR03) },
    { mEA_CARD('A', 0, 117), NPC_ROALD            , 0x26, FTR_START(FTR_TAK_SHUTTLE) },
    { mEA_CARD('A', 0, 118), NPC_AURORA           , 0x10, FTR_START(FTR_SUM_SUBERI01) },
    { mEA_CARD('A', 0, 119), NPC_OLIVE            , 0x1B, FTR_START(FTR_SUM_OKIAGARI01) },
    { mEA_CARD('A', 0, 120), SP_NPC_SHOP_MASTER   , 0x37, FTR_START(FTR_KON_TAIJU) },
    { mEA_CARD('A', 0, 121), SP_NPC_POST_GIRL2    , 0x00, FTR_START(FTR_SUM_UWA_VASE01) },
    { mEA_CARD('A', 0, 122), SP_NPC_POLICE2       , 0x04, FTR_START(FTR_KOB_LOCKER1) },
    { mEA_CARD('A', 0, 123), SP_NPC_ARTIST        , 0x0A, FTR_START(FTR_IKE_ART_SYA) },
    { mEA_CARD('A', 0, 124), SP_NPC_GYPSY         , 0x2C, FTR_START(FTR_IKE_JNY_AFMEN01) },
    { mEA_CARD('A', 0, 125), SP_NPC_EV_DOZAEMON   , 0x00, FTR_START(FTR_IKE_JNY_BOTLE01) },
    { mEA_CARD('A', 0, 126), NPC_TANGY            , 0x25, FTR_START(FTR_SUM_FRUITCHAIR01) },
    { mEA_CARD('A', 0, 127), NPC_MONIQUE          , 0x24, FTR_START(FTR_SUM_SOFE03) },
    { mEA_CARD('A', 0, 128), NPC_KITTY            , 0x17, FTR_START(FTR_SUM_SOFE02) },
    { mEA_CARD('A', 0, 129), NPC_OPAL             , 0x14, FTR_START(FTR_KON_TUBO3) },
    { mEA_CARD('A', 0, 130), NPC_STELLA           , 0x0C, FTR_START(FTR_TAK_METRO) },
    { mEA_CARD('A', 0, 131), NPC_CASHMERE         , 0x11, FTR_START(FTR_SUM_ASI_SCREEN01) },
    { mEA_CARD('A', 0, 132), NPC_CHOW             , 0x02, FTR_START(FTR_SUM_BIWA01) },
    { mEA_CARD('A', 0, 133), NPC_GOLDIE           , 0x1E, FTR_START(FTR_SUM_SOFE03) },
    { mEA_CARD('A', 0, 134), NPC_BEA              , 0x3C, FTR_START(FTR_SUM_GRE_LANP01) },
    { mEA_CARD('A', 0, 135), NPC_RICKY            , 0x22, FTR_START(FTR_SUM_CONT_SOFA02) },
    { mEA_CARD('A', 0, 136), NPC_BLAIRE           , 0x20, FTR_START(FTR_SUM_SLOT) },
    { mEA_CARD('A', 0, 137), NPC_GASTON           , 0x35, FTR_START(FTR_KOB_RIKA_DESK) },
    { mEA_CARD('A', 0, 138), NPC_CLAUDE           , 0x12, FTR_START(FTR_SUM_BON_SATUKI) },
    { mEA_CARD('A', 0, 139), NPC_WEBER            , 0x31, FTR_START(FTR_TAK_ROCKET1) },
    { mEA_CARD('A', 0, 140), NPC_MALLARY          , 0x29, FTR_START(FTR_SUM_ART05) },
    { mEA_CARD('A', 0, 141), NPC_BERTHA           , 0x0B, FTR_START(FTR_SUM_TEKIN01) },
    { mEA_CARD('A', 0, 142), NPC_WOLFGANG         , 0x34, FTR_START(FTR_SUM_GUITAR03) },
    { mEA_CARD('A', 0, 143), NPC_CHICO            , 0x1D, FTR_START(FTR_KON_TUBO2) },
    { mEA_CARD('A', 0, 144), NPC_ANICOTTI         , 0x2E, FTR_START(FTR_SUM_KITCHAIR01) },
    { mEA_CARD('A', 0, 145), NPC_TRUFFLES         , 0x0E, FTR_START(FTR_SUM_UWA_CUP01) },
    { mEA_CARD('A', 0, 146), NPC_COBB             , 0x21, FTR_START(FTR_DIN_AMBER) },
    { mEA_CARD('A', 0, 147), NPC_BETTY            , 0x11, FTR_START(FTR_IKE_JPN_STEP01) },
    { mEA_CARD('A', 0, 148), NPC_HANK             , 0x26, FTR_START(FTR_SUM_BLA_LANP) },
    { mEA_CARD('A', 0, 149), NPC_STU              , 0x2D, FTR_START(FTR_SUM_BLUE_CHAIR01) },
    { mEA_CARD('A', 0, 150), NPC_BELLE            , 0x06, ITM_WALL24 },
    { mEA_CARD('A', 0, 151), NPC_ANCHOVY          , 0x1A, FTR_START(FTR_SUM_SLOT) },
    { mEA_CARD('A', 0, 152), NPC_OTIS             , 0x2E, FTR_START(FTR_KON_SISIODOSI) },
    { mEA_CARD('A', 0, 153), NPC_JEREMIAH         , 0x0D, FTR_START(FTR_ARI_ISU01) },
    { mEA_CARD('A', 0, 154), NPC_HUCK             , 0x0D, FTR_START(FTR_KON_TUITATE) },
    { mEA_CARD('A', 0, 155), NPC_RIBBOT           , 0x3B, FTR_START(FTR_TAK_APOLLO1) },
    { mEA_CARD('A', 0, 156), NPC_LIZ              , 0x28, ITM_CLOTH034 },
    { mEA_CARD('A', 0, 157), NPC_VELMA            , 0x30, FTR_START(FTR_SUM_GLOBE01) },
    { mEA_CARD('A', 0, 158), NPC_ROLF             , 0x10, FTR_START(FTR_SUM_BLA_SOFA02) },
    { mEA_CARD('A', 0, 159), NPC_SNOOTY           , 0x36, FTR_START(FTR_NKH_WALL01) },
    { mEA_CARD('A', 0, 160), NPC_SYDNEY           , 0x1B, FTR_START(FTR_SUM_RADIO01) },
    { mEA_CARD('A', 0, 161), NPC_WINNIE           , 0x32, FTR_START(FTR_SUM_LICCACHAIR) },
    { mEA_CARD('A', 0, 162), NPC_CLEO             , 0x0C, ITM_CARPET50 },
    { mEA_CARD('A', 0, 163), NPC_REX              , 0x3A, FTR_START(FTR_SUM_PL_BENJYAMI) },
    { mEA_CARD('A', 0, 164), NPC_MAPLE            , 0x38, FTR_START(FTR_SUM_DOLL02) },
    { mEA_CARD('A', 0, 165), NPC_HORNSBY          , 0x27, ITM_CARPET32 },
    { mEA_CARD('A', 0, 166), NPC_CESAR            , 0x07, FTR_START(FTR_SUM_WHI_SOFA01) },
    { mEA_CARD('A', 0, 167), NPC_RIO              , 0x2A, FTR_START(FTR_SUM_CONGA01) },
    { mEA_CARD('A', 0, 168), NPC_CARRIE           , 0x09, FTR_START(FTR_KON_GRCLOCK) },
    { mEA_CARD('A', 0, 169), NPC_MATHILDA         , 0x2C, ITM_CLOTH216 },
    { mEA_CARD('A', 0, 170), NPC_QUETZAL          , 0x34, FTR_START(FTR_SUM_TOTEMP01) },
    { mEA_CARD('A', 0, 171), NPC_HOPPER           , 0x03, FTR_START(FTR_SUM_TARU01) },
    { mEA_CARD('A', 0, 172), NPC_URSALA           , 0x08, FTR_START(FTR_SUM_CLBED02) },
    { mEA_CARD('A', 0, 173), NPC_LULU             , 0x28, FTR_START(FTR_NOG_TRI_BED01) },
    { mEA_CARD('A', 0, 174), NPC_PANGO            , 0x18, FTR_START(FTR_SUM_PL_ANANAS) },
    { mEA_CARD('A', 0, 175), SP_NPC_SHOP_MASTER   , 0x37, FTR_START(FTR_KON_TUITATE) },
    { mEA_CARD('A', 0, 176), SP_NPC_MAMEDANUKI0   , 0x37, FTR_START(FTR_SUM_UWA_POTO01) },
    { mEA_CARD('A', 0, 177), SP_NPC_ANGLER        , 0x0F, FTR_START(FTR_IKU_BUSSTOP) },
    { mEA_CARD('A', 0, 178), SP_NPC_MASK_CAT      , 0x00, ITM_CLOTH038 },
    { mEA_CARD('A', 0, 179), NPC_KABUKI           , 0x15, ITM_CARPET10 },
    { mEA_CARD('A', 0, 180), NPC_ELLIE            , 0x09, FTR_START(FTR_SUM_RADIO02) },
    { mEA_CARD('A', 0, 181), NPC_GROUCHO          , 0x07, FTR_START(FTR_SUM_GOLFBAG01) },
    { mEA_CARD('A', 0, 182), NPC_MADDIE           , 0x2B, FTR_START(FTR_SUM_OLDSOFA01) },
    { mEA_CARD('A', 0, 183), NPC_STATIC           , 0x27, FTR_START(FTR_SUM_CONPO01) },
    { mEA_CARD('A', 0, 184), NPC_SNAKE            , 0x36, FTR_START(FTR_KON_ISI03) },
    { mEA_CARD('A', 0, 185), NPC_ROCCO            , 0x03, FTR_START(FTR_SUM_TARU01) },
    { mEA_CARD('A', 0, 186), NPC_CANDI            , 0x32, FTR_START(FTR_SUM_SOFE01) },
    { mEA_CARD('A', 0, 187), NPC_SUE_E            , 0x23, FTR_START(FTR_SUM_HARP) },
    { mEA_CARD('A', 0, 188), NPC_T_BONE           , 0x0E, ITM_CARPET32 },
    { mEA_CARD('A', 0, 189), NPC_TWIGGY           , 0x1E, ITM_WALL22 },
    { mEA_CARD('A', 0, 190), NPC_JAMBETTE         , 0x24, FTR_START(FTR_NOG_TRI_SOFA01) },
    { mEA_CARD('A', 0, 191), NPC_SVEN             , 0x1F, FTR_START(FTR_KON_TUKUE) },
    { mEA_CARD('A', 0, 192), NPC_GONZO            , 0x1F, FTR_START(FTR_TAK_CONE01) },
    { mEA_CARD('A', 0, 193), NPC_LEOPOLD          , 0x04, ITM_CARPET01 },
    { mEA_CARD('A', 0, 194), NPC_CUPCAKE          , 0x01, ITM_CARPET00 },
    { mEA_CARD('A', 0, 195), NPC_QUEENIE          , 0x2C, FTR_START(FTR_NOG_PAWNB) },
    { mEA_CARD('A', 0, 196), NPC_FRIGA            , 0x0C, FTR_START(FTR_SUM_RATAN_SCREEN) },
    { mEA_CARD('A', 0, 197), SP_NPC_SHOP_MASTER   , 0x37, FTR_START(FTR_NOG_STATION00) },
    { mEA_CARD('A', 0, 198), SP_NPC_POST_MAN      , 0x00, FTR_START(FTR_TAK_ASTRO) },
    { mEA_CARD('A', 0, 199), SP_NPC_POLICE        , 0x04, FTR_START(FTR_KOB_LOCKER1) },
    { mEA_CARD('A', 0, 200), SP_NPC_MAMEDANUKI1   , 0x37, FTR_START(FTR_NOG_STATION03) },
    { mEA_CARD('A', 0, 201), SP_NPC_DESIGNER      , 0x04, FTR_START(FTR_SUM_GOLFBAG03) },
    { mEA_CARD('A', 0, 202), SP_NPC_BROKER        , 0x2F, FTR_START(FTR_KON_TUBO3) },
    { mEA_CARD('A', 0, 203), SP_NPC_HALLOWEEN     , 0x1C, FTR_START(FTR_SUM_HAL_LANP01) },
    { mEA_CARD('A', 0, 204), NPC_KIKI             , 0x3C, FTR_START(FTR_TAK_TABLE02) },
    { mEA_CARD('A', 0, 205), NPC_TABBY            , 0x11, FTR_START(FTR_SUM_TV01) },
    { mEA_CARD('A', 0, 206), NPC_TOM              , 0x34, FTR_START(FTR_SUM_ASI_TABLE02) },
    { mEA_CARD('A', 0, 207), NPC_DIZZY            , 0x2E, FTR_START(FTR_SUM_MEZACLOCK) },
    { mEA_CARD('A', 0, 208), NPC_VESTA            , 0x10, FTR_START(FTR_SUM_STOVE01) },
    { mEA_CARD('A', 0, 209), NPC_TUTU             , 0x28, FTR_START(FTR_KON_MASAJI) },
    { mEA_CARD('A', 0, 210), NPC_BISKIT           , 0x09, ITM_WALL41 },
    { mEA_CARD('A', 0, 211), NPC_LUCKY            , 0x21, FTR_START(FTR_SUM_BON_TURU) },
    { mEA_CARD('A', 0, 212), NPC_HAZEL            , 0x2D, FTR_START(FTR_SUM_UWA_CUP01) },
    { mEA_CARD('A', 0, 213), NPC_MINT             , 0x25, FTR_START(FTR_SUM_BLUE_CLK) },
    { mEA_CARD('A', 0, 214), NPC_GABI             , 0x2B, FTR_START(FTR_TAK_METRO) },
    { mEA_CARD('A', 0, 215), NPC_GENJI            , 0x36, FTR_START(FTR_KON_CHOUZU01) },
    { mEA_CARD('A', 0, 216), NPC_FRECKLES         , 0x32, FTR_START(FTR_KON_MILK) },
    { mEA_CARD('A', 0, 217), NPC_DEENA            , 0x1B, FTR_START(FTR_SUM_TAKKYU) },
    { mEA_CARD('A', 0, 218), NPC_ROLLO            , 0x0F, FTR_START(FTR_KON_TUKUE) },
    { mEA_CARD('A', 0, 219), NPC_FREYA            , 0x30, FTR_START(FTR_SUM_BLA_CHAIR02) },
    { mEA_CARD('A', 0, 220), NPC_PENNY            , 0x17, FTR_START(FTR_TAK_HOLE01) },
    { mEA_CARD('A', 0, 221), NPC_RIZZO            , 0x15, FTR_START(FTR_NKH_WALL01) },
    { mEA_CARD('A', 0, 222), NPC_SPORK            , 0x0E, FTR_START(FTR_TAK_YAJI) },
    { mEA_CARD('A', 0, 223), NPC_HUGH             , 0x29, FTR_START(FTR_SUM_WC02) },
    { mEA_CARD('A', 0, 224), NPC_EGBERT           , 0x18, FTR_START(FTR_SUM_SOFE03) },
    { mEA_CARD('A', 0, 225), NPC_OXFORD           , 0x03, FTR_START(FTR_TAK_HOLE01) },
    { mEA_CARD('A', 0, 226), NPC_BESSIE           , 0x20, FTR_START(FTR_SUM_PL_GOMUNOKI) },
    { mEA_CARD('A', 0, 227), NPC_PIPER            , 0x14, FTR_START(FTR_SUM_RATAN_MIRROR) },
    { mEA_CARD('A', 0, 228), NPC_TWIRP            , 0x39, FTR_START(FTR_KON_JIHANKI02) },
    { mEA_CARD('A', 0, 229), NPC_ACE              , 0x1A, FTR_START(FTR_TAK_ASTRO) },
    { mEA_CARD('A', 0, 230), NPC_EMERALD          , 0x0D, FTR_START(FTR_SUM_GRE_CHAIR01) },
    { mEA_CARD('A', 0, 231), NPC_COUSTEAU         , 0x1D, FTR_START(FTR_SUM_ASI_CHEST02) },
    { mEA_CARD('A', 0, 232), NPC_PRINCE           , 0x0A, FTR_START(FTR_IKU_BUSSTOP) },
    { mEA_CARD('A', 0, 233), NPC_ALLI             , 0x2A, FTR_START(FTR_SUM_MISIN01) },
    { mEA_CARD('A', 0, 234), NPC_BILLY            , 0x1F, FTR_START(FTR_KON_TUBO) },
    { mEA_CARD('A', 0, 235), NPC_ZOE              , 0x26, FTR_START(FTR_SUM_FRUITCHAIR04) },
    { mEA_CARD('A', 0, 236), NPC_OZZIE            , 0x31, FTR_START(FTR_IKE_JPN_IRORI01) },
    { mEA_CARD('A', 0, 237), NPC_ED               , 0x2C, FTR_START(FTR_SUM_BLA_DESK01) },
    { mEA_CARD('A', 0, 238), NPC_OCTAVIAN         , 0x3F, FTR_START(FTR_TAK_UFO) },
    { mEA_CARD('A', 0, 239), NPC_AZIZ             , 0x32, FTR_START(FTR_SUM_PL_SHUROCI) },
    { mEA_CARD('A', 0, 240), NPC_MURPHY           , 0x31, FTR_START(FTR_KOB_MASTERSWORD) },
    { mEA_CARD('A', 0, 241), NPC_PUDGE            , 0x05, FTR_START(FTR_SUM_GUITAR01) },
    { mEA_CARD('A', 0, 242), NPC_TIARA            , 0x3A, FTR_START(FTR_SUM_PL_BENJYAMI) },
    { mEA_CARD('A', 0, 243), NPC_SANDY            , 0x35, FTR_START(FTR_TAK_APOLLO1) },
    { mEA_CARD('A', 0, 244), NPC_ASTRID           , 0x27, FTR_START(FTR_SUM_GUITAR03) },
    { mEA_CARD('A', 0, 245), NPC_AMELIA           , 0x3B, ITM_CARPET13 },
    { mEA_CARD('A', 0, 246), NPC_GWEN             , 0x24, FTR_START(FTR_SUM_OLDSOFA01) },
    { mEA_CARD('A', 0, 247), NPC_AXEL             , 0x0E, FTR_START(FTR_SUM_PL_SHUROCI) },
    { mEA_CARD('A', 0, 248), NPC_NATE             , 0x38, FTR_START(FTR_KON_MASAJI) },
    { mEA_CARD('A', 0, 249), NPC_BITTY            , 0x08, FTR_START(FTR_SUM_PL_KUROTON) },
    { mEA_CARD('A', 0, 250), NPC_GRUFF            , 0x03, FTR_START(FTR_SUM_GUITAR03) },
    { mEA_CARD('A', 0, 251), NPC_HUGGY            , 0x11, FTR_START(FTR_SUM_LICCASOFA) },
    { mEA_CARD('A', 0, 252), SP_NPC_GYPSY         , 0x19, FTR_START(FTR_SUM_KADOMATU) },
    { mEA_CARD('A', 0, 253), SP_NPC_EV_GHOST      , 0x29, FTR_START(FTR_NOG_STATION02) },
    { mEA_CARD('A', 0, 254), SP_NPC_MAJIN_BROTHER , 0x03, FTR_START(FTR_IKU_JACK) },
    { mEA_CARD('A', 0, 255), NPC_ROSIE            , 0x12, FTR_START(FTR_KON_AMECLOCK) },
    { mEA_CARD('A', 0, 256), NPC_WOOLIO           , 0x01, FTR_START(FTR_SUM_PL_HIRASABO) },
    { mEA_CARD('A', 0, 257), NPC_DAISY            , 0x0B, FTR_START(FTR_SUM_SHOUKAKI) },
    { mEA_CARD('A', 0, 258), NPC_PECAN            , 0x28, ITM_WALL35 },
    { mEA_CARD('A', 0, 259), NPC_PIPPY            , 0x1A, FTR_START(FTR_KON_MAT) },
    { mEA_CARD('A', 0, 260), NPC_PATE             , 0x31, FTR_START(FTR_SUM_WHI_LANP) },
    { mEA_CARD('A', 0, 261), NPC_FANG             , 0x30, FTR_START(FTR_KON_TUBO3) },
    { mEA_CARD('A', 0, 262), NPC_CARMEN           , 0x3C, FTR_START(FTR_SUM_FRUITBED01) },
    { mEA_CARD('A', 0, 263), NPC_HAMBO            , 0x04, FTR_START(FTR_NOG_DARUMAS) },
    { mEA_CARD('A', 0, 264), NPC_HECTOR           , 0x35, FTR_START(FTR_NOG_DARUMAL) },
    { mEA_CARD('A', 0, 265), NPC_PETUNIA          , 0x23, FTR_START(FTR_SUM_UWA_VASE01) },
    { mEA_CARD('A', 0, 266), NPC_ROBIN            , 0x06, FTR_START(FTR_SUM_CLASSICCHEST02) },
    { mEA_CARD('A', 0, 267), NPC_WART_JR          , 0x22, ITM_CARPET16 },
    { mEA_CARD('A', 0, 268), NPC_ALFONSO          , 0x31, FTR_START(FTR_SUM_ASI_CHAIR02) },
    { mEA_CARD('A', 0, 269), NPC_NOSEGAY          , 0x1B, FTR_START(FTR_IKE_ART_ANG) },
    { mEA_CARD('A', 0, 270), NPC_SAVANNAH         , 0x3A, ITM_WALL28 },
    { mEA_CARD('A', 0, 271), NPC_TANK             , 0x3B, FTR_START(FTR_SUM_ASI_CHAIR01) },
    { mEA_CARD('A', 0, 272), NPC_LOUIE            , 0x2D, FTR_START(FTR_SUM_TOTEMP03) },
    { mEA_CARD('A', 0, 273), NPC_VALISE           , 0x20, FTR_START(FTR_SUM_CELLO01) },
    { mEA_CARD('B', 0,   1), SP_NPC_MAJIN         , 0x03, FTR_START(FTR_KON_YUBUNE) },
    { mEA_CARD('B', 1,   1), SP_NPC_MAJIN_BROTHER , 0x03, FTR_START(FTR_IKE_JPN_SAI01) },
    { mEA_CARD('B', 0,   2), SP_NPC_NEEDLEWORK1   , 0x20, FTR_START(FTR_IKE_JPN_SAI01) },
    { mEA_CARD('B', 1,   2), SP_NPC_NEEDLEWORK0   , 0x2B, FTR_START(FTR_SUM_CONT_CHAIR01) },
    { mEA_CARD('B', 0,   3), SP_NPC_POST_GIRL2    , 0x00, FTR_START(FTR_SUM_KITCHAIR01) },
    { mEA_CARD('B', 1,   3), SP_NPC_POST_GIRL     , 0x00, FTR_START(FTR_SUM_RATAN_BED01) },
    { mEA_CARD('B', 0,   4), SP_NPC_MAMEDANUKI1   , 0x37, FTR_START(FTR_NOG_STATION04) },
    { mEA_CARD('B', 1,   4), SP_NPC_MAMEDANUKI0   , 0x37, FTR_START(FTR_NOG_STATION05) },
    { mEA_CARD('G', 0,   1), SP_NPC_POLICE        , 0x04, FTR_START(FTR_KOB_PIPEISU) },
    { mEA_CARD('G', 1,   1), SP_NPC_POLICE2       , 0x04, FTR_START(FTR_KOB_LOCKER1) },
    { mEA_CARD('E', 0,   3), SP_NPC_SENDO         , 0x2B, FTR_START(FTR_KON_MAT) },
    { mEA_CARD('E', 0,   4), SP_NPC_MAJIN         , 0x03, FTR_START(FTR_KON_MASAJI) },
    { mEA_CARD('E', 0,   5), SP_NPC_GUIDE         , 0x00, ITM_CLOTH216 },
    { mEA_CARD('E', 0,   6), SP_NPC_MASK_CAT      , 0x00, FTR_START(FTR_KON_OKE) },
    { mEA_CARD('E', 0,   7), SP_NPC_TOTAKEKE      , 0x10, FTR_START(FTR_SUM_GUITAR02) },
    { mEA_CARD('E', 0,   8), SP_NPC_STATION_MASTER, 0x37, FTR_START(FTR_NOG_RAIL) },
    { mEA_CARD('E', 0,   9), SP_NPC_SHOP_MASTER   , 0x37, ITM_CLOTH016 },
    { mEA_CARD('E', 0,  10), SP_NPC_EV_SONCHO     , 0x3E, FTR_START(FTR_KON_TUBO2) },
    { mEA_CARD('E', 0,  11), SP_NPC_CURATOR       , 0x18, FTR_START(FTR_KON_TUBO) },
    { mEA_CARD('E', 0,  12), SP_NPC_NEEDLEWORK1   , 0x20, ITM_CLOTH200 },
    { mEA_CARD('E', 0,  13), SP_NPC_NEEDLEWORK0   , 0x2B, ITM_CLOTH254 },
    { mEA_CARD('E', 0,  14), SP_NPC_POST_GIRL     , 0x00, FTR_START(FTR_ARI_KITCHEN01) },
    { mEA_CARD('E', 0,  15), SP_NPC_POST_MAN      , 0x00, FTR_START(FTR_SUM_MEZACLOCK) },
    { mEA_CARD('E', 0,  16), SP_NPC_POLICE        , 0x04, FTR_START(FTR_KOB_JIMUISU) },
    { mEA_CARD('E', 0,  17), SP_NPC_POLICE2       , 0x04, FTR_START(FTR_IKU_BUSSTOP) },
    { mEA_CARD('E', 0,  18), SP_NPC_POST_GIRL2    , 0x00, FTR_START(FTR_SUM_DOLL04) },
    // @BUG - Rev0 improperly assigns Gracie's card to 'A' series
#if VERSION == VER_GAEJ01_00 && !defined(BUGFIXES)
    { mEA_CARD('A', 0,  19), SP_NPC_DESIGNER      , 0x04, ITM_CLOTH029 },
#else
    { mEA_CARD('E', 0,  19), SP_NPC_DESIGNER      , 0x04, ITM_CLOTH029 },
#endif
    { mEA_CARD('E', 0,  20), SP_NPC_CARPETPEDDLER , 0x06, ITM_CARPET00 },
    { mEA_CARD('E', 0,  21), SP_NPC_KABUPEDDLER   , 0x1F, FTR_START(FTR_SUM_BON_BOKE) },
    { mEA_CARD('E', 0,  22), SP_NPC_ARTIST        , 0x0A, ITM_WALL10 },
    { mEA_CARD('E', 0,  23), SP_NPC_GYPSY         , 0x2C, FTR_START(FTR_KON_TUBO3) },
    { mEA_CARD('E', 0,  24), SP_NPC_EV_DOZAEMON   , 0x00, FTR_START(FTR_SUM_TOTEMP03) },
    { mEA_CARD('E', 0,  25), SP_NPC_MAMEDANUKI0   , 0x37, FTR_START(FTR_SUM_PL_GOMUNOKI) },
    { mEA_CARD('E', 0,  26), SP_NPC_MAMEDANUKI1   , 0x37, FTR_START(FTR_SUM_PL_KUROTON) },
};
// clang-format on

extern int mEA_animal_carde_info_to_save_idx(u16 info) {
    int idx = mEA_CARDE_TOTAL_NUM - 1;
    u16 swapped_info = (((u16)info >> 8) & 0xFF) | (((u16)info & 0xFF) << 8);
    u8 series;
    int card_set_idx;
    int index;
    int i;
    
    mEA_get_character_card_header(&series, &card_set_idx, &index, (u8*)&info);
    switch (series) {
        case 'A':
        case 'B':
        case 'E':
        case 'G':
            for (i = 0; i < mEA_CHARACTER_PLUS_CARDE_NUM; i++) {
                if (mEA_carde_convert_dat[i].id == swapped_info) {
                    idx = i;
                    break;
                }
            }
            break;
        case 'N':
            if (index <= mEA_FAMICOM_CARDE_NUM) {
                idx = mEA_CHARACTER_PLUS_CARDE_NUM + index - 1;
            }
            break;
        case 'C':
            idx = MIN(mEA_CHARACTER_PLUS_CARDE_NUM + mEA_FAMICOM_CARDE_NUM + index - 1, mEA_CARDE_TOTAL_NUM - 1);
            break;
    }

    return idx;
}

extern int mEA_animal_carde_info_to_paper_idx(u16 info) {
    u16 swapped_info = (((u16)info >> 8) & 0xFF) | (((u16)info & 0xFF) << 8);
    int i;

    for (i = 0; i < mEA_CHARACTER_PLUS_CARDE_NUM; i++) {
        if (mEA_carde_convert_dat[i].id == swapped_info) {
            return mEA_carde_convert_dat[i].paper_idx & 0x3F;
        }
    }

    return -1;
}

extern mActor_name_t mEA_animal_carde_info_to_npc_no(u16 info) {
    u16 swapped_info = (((u16)info >> 8) & 0xFF) | (((u16)info & 0xFF) << 8);
    mActor_name_t npc_id = EMPTY_NO;
    int i;

    for (i = 0; i < mEA_CHARACTER_PLUS_CARDE_NUM; i++) {
        if (mEA_carde_convert_dat[i].id == swapped_info) {
            npc_id = mEA_carde_convert_dat[i].npc_id;
            break;
        }
    }

    return npc_id;
}

extern mActor_name_t mEA_animal_carde_info_to_present(u16 info) {
    u16 swapped_info = (((u16)info >> 8) & 0xFF) | (((u16)info & 0xFF) << 8);
    mActor_name_t present = EMPTY_NO;
    int i;
    
    for (i = 0; i < mEA_CHARACTER_PLUS_CARDE_NUM; i++) {
        if (mEA_carde_convert_dat[i].id == swapped_info) {
            present = mEA_carde_convert_dat[i].present;
            break;
        }
    }

    return present;
}

extern int mEA_animal_carde_info_to_letter_no(u16 info) {
    u16 swapped_info = (((u16)info >> 8) & 0xFF) | (((u16)info & 0xFF) << 8);
    u8 series;
    int card_set_idx;
    int index;
    int i;
    
    mEA_get_character_card_header(&series, &card_set_idx, &index, (u8*)&info);
    if (series != 'C' && series != 'N') {
        for (i = 0; i < mEA_CHARACTER_PLUS_CARDE_NUM; i++) {
            if (mEA_carde_convert_dat[i].id == swapped_info) {
                return i;
            }
        }

        return mEA_CARD_LETTER_NO_INVALID; // not a valid character card
    }

    return mEA_CARD_LETTER_NO_EMBEDDED; // embedded in the card data
}

// @BUG - Rev0 improperly checks which cards are special NPCs
#if VERSION == VER_GAEJ01_00 && !defined(BUGFIXES)
extern int mEA_animal_carde_info_to_check_special_npc(u16 info) {
    u16 swapped_info = (((u16)info >> 8) & 0xFF) | (((u16)info & 0xFF) << 8);
    u8 series;
    int card_set_idx;
    int index;
    int i;
    mActor_name_t npc_id;
    int ret;
    
    mEA_get_character_card_header(&series, &card_set_idx, &index, (u8*)&info);
    switch (series) {
        case 'N': // all NES cards are special NPCs
            return TRUE;

        case 'A':
            npc_id = mEA_animal_carde_info_to_npc_no(info);
            if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_SPNPC) {
                return TRUE;
            }

            break;
        }
        
    return FALSE;
}
#else
extern int mEA_animal_carde_info_to_check_special_npc(u16 info) {
    u16 swapped_info = (((u16)info >> 8) & 0xFF) | (((u16)info & 0xFF) << 8);
    u8 series;
    int card_set_idx;
    int index;
    int i;
    mActor_name_t npc_id;
    
    mEA_get_character_card_header(&series, &card_set_idx, &index, (u8*)&info);
    switch (series) {
        case 'C': // all e+ character cards are not special NPCs
            return FALSE;

        case 'N': // all NES cards are special NPCs
            return TRUE;

        case 'A':
        case 'B':
        case 'E':
        case 'G':
            npc_id = mEA_animal_carde_info_to_npc_no(info);
            if (npc_id == EMPTY_NO) {
                return TRUE;
            } else if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_SPNPC) {
                return TRUE;
            }

            return FALSE;
    }

    return TRUE;
}
#endif
