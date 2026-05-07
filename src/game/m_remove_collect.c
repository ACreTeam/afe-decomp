#include "m_remove_collect.h"
#include "m_name_table.h"
#include "_mem.h"

typedef struct item_plus_to_plusplus_s {
    mActor_name_t item_plus;
    mActor_name_t item_plusplus;
} mRC_item_plus_to_plusplus_c;

static mRC_item_plus_to_plusplus_c mRC_item_remove_data[] = {
    {0x2003, EMPTY_NO}, // danger paper
    {0x2019, EMPTY_NO}, // fortune paper
    {0x203E, EMPTY_NO}, // New Year's card
    {0x2301, EMPTY_NO}, // herabuna
    {0x244B, EMPTY_NO}, // tomato juice shirt
    {0x2469, EMPTY_NO}, // familiar shirt
    {0x24B6, EMPTY_NO}, // W shirt
    {0x24BF, EMPTY_NO}, // I <3 GC shirt
    {0x2612, ITM_CARPET67}, // bathhouse tile
    {0x261A, ITM_CARPET68}, // old board floor
    {0x2712, ITM_WALL67}, // bathhouse wall
    {0x271A, ITM_WALL68}, // worn-out mud wall
    {0x2A34, ITM_MINIDISK55}, // K.K. Song
    {0x2A35, ITM_MINIDISK56}, // I Love You
    {0x2A36, ITM_MINIDISK57}, // Two Days Ago
    {0x2D28, ITM_SPIRIT0}, // spirit (1)
    {0x2D29, ITM_SPIRIT1}, // spirit (2)
    {0x2D2A, ITM_SPIRIT2}, // spirit (3)
    {0x2D2B, ITM_SPIRIT3}, // spirit (4)
    {0x2D2C, ITM_SPIRIT4}, // spirit (5)
};

static mRC_item_plus_to_plusplus_c mRC_ftr_remove_data[382] = {
    {0x109C, EMPTY_NO}, // zabuton
    {0x10A0, EMPTY_NO}, // bus stop (DnM)
    {0x10B0, EMPTY_NO}, // chest
    {0x10B4, EMPTY_NO}, // rack
    {0x11F8, EMPTY_NO}, // nice speaker
    {0x1200, EMPTY_NO}, // school desk (DnM)
    {0x1204, EMPTY_NO}, // graffiti desk
    {0x1208, EMPTY_NO}, // towel desk
    {0x1240, EMPTY_NO}, // heavy chair
    {0x1244, EMPTY_NO}, // school chair
    {0x1248, EMPTY_NO}, // towel chair
    {0x1250, EMPTY_NO}, // stepstool
    {0x12B0, EMPTY_NO}, // dreadful painting
    {0x12B4, EMPTY_NO}, // lovely painting
    {0x12C4, EMPTY_NO}, // nice painting
    {0x12F0, EMPTY_NO}, // unused dresser
    {0x1314, EMPTY_NO}, // unused monkey
    {0x1344, EMPTY_NO}, // modern den chair
    {0x1418, EMPTY_NO}, // striped cone
    {0x1420, EMPTY_NO}, // cola machine
    {0x1430, EMPTY_NO}, // barricade
    {0x1434, EMPTY_NO}, // fence
    {0x1438, EMPTY_NO}, // plastic fence
    {0x143C, EMPTY_NO}, // fence and sign
    {0x144C, EMPTY_NO}, // brown drum
    {0x1454, EMPTY_NO}, // red drum
    {0x1458, EMPTY_NO}, // juice machine
    {0x1474, EMPTY_NO}, // robotic flagman
    {0x14A0, EMPTY_NO}, // warning sign
    {0x14B0, EMPTY_NO}, // route sign
    {0x14B4, EMPTY_NO}, // men working sign
    {0x14B8, EMPTY_NO}, // caution sign
    {0x14CC, EMPTY_NO}, // unused chair
    {0x18D8, EMPTY_NO}, // tomato juice shirt (ftr)
    {0x1950, EMPTY_NO}, // familiar shirt (ftr)
    {0x1A84, EMPTY_NO}, // W shirt (ftr)
    {0x1AA8, EMPTY_NO}, // I <3 GC shirt (ftr)
    {0x1C68, FTR_START(FTR_SUM_FUNA)},
    {0x1C6C, FTR_START(FTR_SUM_HERA)},
    {0x1C70, FTR_START(FTR_SUM_KOI)},
    {0x1C74, FTR_START(FTR_SUM_NISIKI)},
    {0x1C78, FTR_START(FTR_SUM_NAMAZU)},
    {0x1C7C, FTR_START(FTR_SUM_BASS)},
    {0x1C80, FTR_START(FTR_SUM_BASSM)},
    {0x1C84, FTR_START(FTR_SUM_BASSL)},
    {0x1C88, FTR_START(FTR_SUM_GILL)},
    {0x1C8C, FTR_START(FTR_SUM_OONAMAZU)},
    {0x1C90, FTR_START(FTR_SUM_RAIGYO)},
    {0x1C94, FTR_START(FTR_SUM_NIGOI)},
    {0x1C98, FTR_START(FTR_SUM_UGUI)},
    {0x1C9C, FTR_START(FTR_SUM_OIKAWA)},
    {0x1CA0, FTR_START(FTR_SUM_TANAGO)},
    {0x1CA4, FTR_START(FTR_SUM_DOJYO)},
    {0x1CA8, FTR_START(FTR_SUM_WAKASAGI)},
    {0x1CAC, FTR_START(FTR_SUM_AYU)},
    {0x1CB0, FTR_START(FTR_SUM_YAMAME)},
    {0x1CB4, FTR_START(FTR_SUM_IWANA)},
    {0x1CB8, FTR_START(FTR_SUM_NIJI)},
    {0x1CBC, FTR_START(FTR_SUM_ITO)},
    {0x1CC0, FTR_START(FTR_SUM_SAKE)},
    {0x1CC4, FTR_START(FTR_SUM_KINGYO)},
    {0x1CC8, FTR_START(FTR_SUM_PIRANIA)},
    {0x1CCC, FTR_START(FTR_SUM_AROANA)},
    {0x1CD0, FTR_START(FTR_SUM_UNAGI)},
    {0x1CD4, FTR_START(FTR_SUM_DONKO)},
    {0x1CD8, FTR_START(FTR_SUM_ANGEL)},
    {0x1CDC, FTR_START(FTR_SUM_GUPI)},
    {0x1CE0, FTR_START(FTR_SUM_DEMEKIN)},
    {0x1CE4, FTR_START(FTR_SUM_KASEKI)},
    {0x1CE8, FTR_START(FTR_NOG_ZARIGANI)},
    {0x1CEC, FTR_START(FTR_NOG_KAERU)},
    {0x1CF0, FTR_START(FTR_NOG_MEDAKA)},
    {0x1CF4, FTR_START(FTR_NOG_KURAGE)},
    {0x1CF8, FTR_START(FTR_NOG_SUZUKI)},
    {0x1CFC, FTR_START(FTR_NOG_TAI)},
    {0x1D00, FTR_START(FTR_NOG_ISIDAI)},
    {0x1D04, FTR_START(FTR_NOG_PIRALUKU)},
    {0x1D08, FTR_START(FTR_FUMBRELLA00)},
    {0x1D0C, FTR_START(FTR_FUMBRELLA01)},
    {0x1D10, FTR_START(FTR_FUMBRELLA02)},
    {0x1D14, FTR_START(FTR_FUMBRELLA03)},
    {0x1D18, FTR_START(FTR_FUMBRELLA04)},
    {0x1D1C, FTR_START(FTR_FUMBRELLA05)},
    {0x1D20, FTR_START(FTR_FUMBRELLA06)},
    {0x1D24, FTR_START(FTR_FUMBRELLA07)},
    {0x1D28, FTR_START(FTR_FUMBRELLA08)},
    {0x1D2C, FTR_START(FTR_FUMBRELLA09)},
    {0x1D30, FTR_START(FTR_FUMBRELLA10)},
    {0x1D34, FTR_START(FTR_FUMBRELLA11)},
    {0x1D38, FTR_START(FTR_FUMBRELLA12)},
    {0x1D3C, FTR_START(FTR_FUMBRELLA13)},
    {0x1D40, FTR_START(FTR_FUMBRELLA14)},
    {0x1D44, FTR_START(FTR_FUMBRELLA15)},
    {0x1D48, FTR_START(FTR_FUMBRELLA16)},
    {0x1D4C, FTR_START(FTR_FUMBRELLA17)},
    {0x1D50, FTR_START(FTR_FUMBRELLA18)},
    {0x1D54, FTR_START(FTR_FUMBRELLA19)},
    {0x1D58, FTR_START(FTR_FUMBRELLA20)},
    {0x1D5C, FTR_START(FTR_FUMBRELLA21)},
    {0x1D60, FTR_START(FTR_FUMBRELLA22)},
    {0x1D64, FTR_START(FTR_FUMBRELLA23)},
    {0x1D68, FTR_START(FTR_FUMBRELLA24)},
    {0x1D6C, FTR_START(FTR_FUMBRELLA25)},
    {0x1D70, FTR_START(FTR_FUMBRELLA26)},
    {0x1D74, FTR_START(FTR_FUMBRELLA27)},
    {0x1D78, FTR_START(FTR_FUMBRELLA28)},
    {0x1D7C, FTR_START(FTR_FUMBRELLA29)},
    {0x1D80, FTR_START(FTR_FUMBRELLA30)},
    {0x1D84, FTR_START(FTR_FUMBRELLA31)},
    {0x1DA8, FTR_START(FTR_FAMICOM_COMMON00)},
    {0x1DAC, FTR_START(FTR_FAMICOM_COMMON01)},
    {0x1DB0, FTR_START(FTR_FAMICOM_COMMON02)},
    {0x1DB4, FTR_START(FTR_FAMICOM_COMMON03)},
    {0x1DB8, FTR_START(FTR_FAMICOM_COMMON04)},
    {0x1DBC, FTR_START(FTR_FAMICOM_COMMON05)},
    {0x1DC0, FTR_START(FTR_FAMICOM_COMMON06)},
    {0x1DC4, FTR_START(FTR_FAMICOM_COMMON07)},
    {0x1DC8, FTR_START(FTR_FAMICOM_COMMON08)},
    {0x1DCC, FTR_START(FTR_FAMICOM_COMMON09)},
    {0x1DD0, FTR_START(FTR_FAMICOM_COMMON10)},
    {0x1DD4, FTR_START(FTR_FAMICOM_COMMON11)},
    {0x1DD8, EMPTY_NO}, // Gomoku Narabe
    {0x1DDC, EMPTY_NO}, // Mahjong
    {0x1DE0, FTR_START(FTR_FAMICOM_COMMON14)},
    {0x1DE4, EMPTY_NO}, // Ice Climber
    {0x1DE8, EMPTY_NO}, // Mario Bros
    {0x1DEC, EMPTY_NO}, // Super Mario Bros
    {0x1DF0, EMPTY_NO}, // Legend of Zelda
    {0x1DF4, FTR_START(FTR_KOB_DISKSYSTEM8)},
    {0x1DF8, FTR_START(FTR_SUM_CHIKUON01)},
    {0x1DFC, FTR_START(FTR_SUM_CHIKUON02)},
    {0x1E00, FTR_START(FTR_SUM_JUKEBOX)},
    {0x1E04, FTR_START(FTR_SUM_RADIO01)},
    {0x1E08, FTR_START(FTR_SUM_RADIO02)},
    {0x1E0C, FTR_START(FTR_SUM_CONPO02)},
    {0x1E10, FTR_START(FTR_SUM_STEREO02)},
    {0x1E14, FTR_START(FTR_SUM_LV_STEREO)},
    {0x1E18, FTR_START(FTR_SUM_X_LANP)},
    {0x1E1C, FTR_START(FTR_SUM_X_CHAIR01)},
    {0x1E20, FTR_START(FTR_SUM_X_CHEST03)},
    {0x1E24, FTR_START(FTR_SUM_X_SOFA01)},
    {0x1E28, FTR_START(FTR_SUM_X_BED01)},
    {0x1E2C, FTR_START(FTR_SUM_X_CLK)},
    {0x1E30, FTR_START(FTR_SUM_X_TABLE01)},
    {0x1E34, FTR_START(FTR_SUM_X_PIANO)},
    {0x1E38, FTR_START(FTR_SUM_DOLL11)},
    {0x1E3C, FTR_START(FTR_SUM_ROBOCONPO)},
    {0x1E40, FTR_START(FTR_SUM_SAICONPO)},
    {0x1E44, FTR_START(FTR_SUM_FRUITCLK)},
    {0x1E48, FTR_START(FTR_SUM_ROBOCLK)},
    {0x1E4C, FTR_START(FTR_KON_AMECLOCK)},
    {0x1E50, FTR_START(FTR_KON_ATQCLOCK)},
    {0x1E54, FTR_START(FTR_SUM_RECO01)},
    {0x1E58, FTR_START(FTR_SUM_CASSE01)},
    {0x1E5C, FTR_START(FTR_SUM_MD01)},
    {0x1E60, FTR_START(FTR_KON_GRCLOCK)},
    {0x1E64, FTR_START(FTR_KON_WACLOCK)},
    {0x1E68, FTR_START(FTR_KON_REDCLOCK)},
    {0x1E6C, FTR_START(FTR_KON_BLUECLOCK)},
    {0x1E70, FTR_START(FTR_KON_MIMICLOCK)},
    {0x1E74, FTR_START(FTR_KON_MANEKI01)},
    {0x1E78, FTR_START(FTR_KON_MANEKI02)},
    {0x1E7C, FTR_START(FTR_KON_MUSYA)},
    {0x1E80, FTR_START(FTR_KON_TANUKI)},
    {0x1E84, FTR_START(FTR_KON_KAERU)},
    {0x1E88, FTR_START(FTR_KON_XTREE02)},
    {0x1E8C, FTR_START(FTR_NOG_ROOKW)},
    {0x1E90, FTR_START(FTR_NOG_ROOKB)},
    {0x1E94, FTR_START(FTR_NOG_QUEENW)},
    {0x1E98, FTR_START(FTR_NOG_QUEENB)},
    {0x1E9C, FTR_START(FTR_NOG_BISHOPW)},
    {0x1EA0, FTR_START(FTR_NOG_BISHOPB)},
    {0x1EA4, FTR_START(FTR_NOG_KINGW)},
    {0x1EA8, FTR_START(FTR_NOG_KINGB)},
    {0x1EAC, FTR_START(FTR_NOG_KNIGHTW)},
    {0x1EB0, FTR_START(FTR_NOG_KNIGHTB)},
    {0x1EB4, FTR_START(FTR_NOG_PAWNW)},
    {0x1EB8, FTR_START(FTR_NOG_PAWNB)},
    {0x1EBC, FTR_START(FTR_NOG_XTREE)},
    {0x1EC0, FTR_START(FTR_NOG_TRI_CLOCK01)},
    {0x1EC4, FTR_START(FTR_NOG_TRI_BED01)},
    {0x1EC8, FTR_START(FTR_NOG_TRI_TABLE01)},
    {0x1ECC, FTR_START(FTR_NOG_TRI_SOFA01)},
    {0x1ED0, FTR_START(FTR_NOG_TRI_AUDIO01)},
    {0x1ED4, FTR_START(FTR_NOG_TRI_CHAIR01)},
    {0x1ED8, FTR_START(FTR_NOG_TRI_RACK01)},
    {0x1EDC, FTR_START(FTR_IKE_JPN_TOKONOMA01)},
    {0x1EE0, FTR_START(FTR_IKE_JPN_IRORI01)},
    {0x1EE4, FTR_START(FTR_SUM_KOKUBAN)},
    {0x1EE8, FTR_START(FTR_SUM_BAKETU)},
    {0x1EEC, FTR_START(FTR_DIN_TRIKERA_HEAD)},
    {0x1EF0, FTR_START(FTR_DIN_TRIKERA_TAIL)},
    {0x1EF4, FTR_START(FTR_DIN_TRIKERA_BODY)},
    {0x1EF8, FTR_START(FTR_DIN_TREX_HEAD)},
    {0x1EFC, FTR_START(FTR_DIN_TREX_TAIL)},
    {0x1F00, FTR_START(FTR_DIN_TREX_BODY)},
    {0x1F04, FTR_START(FTR_DIN_BRONT_HEAD)},
    {0x1F08, FTR_START(FTR_DIN_BRONT_TAIL)},
    {0x1F0C, FTR_START(FTR_DIN_BRONT_BODY)},
    {0x1F10, FTR_START(FTR_DIN_STEGO_HEAD)},
    {0x1F14, FTR_START(FTR_DIN_STEGO_TAIL)},
    {0x1F18, FTR_START(FTR_DIN_STEGO_BODY)},
    {0x1F1C, FTR_START(FTR_DIN_PTERA_HEAD)},
    {0x1F20, FTR_START(FTR_DIN_PTERA_RWING)},
    {0x1F24, FTR_START(FTR_DIN_PTERA_LWING)},
    {0x1F28, FTR_START(FTR_DIN_HUTABA_HEAD)},
    {0x1F2C, FTR_START(FTR_DIN_HUTABA_NECK)},
    {0x1F30, FTR_START(FTR_DIN_HUTABA_BODY)},
    {0x1F34, FTR_START(FTR_DIN_MAMMOTH_HEAD)},
    {0x1F38, FTR_START(FTR_DIN_MAMMOTH_BODY)},
    {0x1F3C, FTR_START(FTR_DIN_AMBER)},
    {0x1F40, FTR_START(FTR_DIN_STUMP)},
    {0x1F44, FTR_START(FTR_DIN_AMMONITE)},
    {0x1F48, FTR_START(FTR_DIN_EGG)},
    {0x1F4C, FTR_START(FTR_DIN_TRILOBITE)},
    {0x1F50, FTR_START(FTR_SUM_BLA_LANP)},
    {0x1F54, FTR_START(FTR_KON_SNOWFREEZER)},
    {0x1F58, FTR_START(FTR_KON_SNOWTABLE)},
    {0x1F5C, FTR_START(FTR_KON_SNOWBED)},
    {0x1F60, FTR_START(FTR_TAK_SNOWISU)},
    {0x1F64, FTR_START(FTR_TAK_SNOWLAMP)},
    {0x1F68, FTR_START(FTR_KON_SNOWSOFA)},
    {0x1F6C, FTR_START(FTR_KON_SNOWTV)},
    {0x1F70, FTR_START(FTR_KON_SNOWTANSU)},
    {0x1F74, FTR_START(FTR_KON_SNOWBOX)},
    {0x1F78, FTR_START(FTR_KON_SNOWCLOCK)},
    {0x1F7C, FTR_START(FTR_DIN_TRIKERA_DUMMY)},
    {0x1F80, FTR_START(FTR_DIN_TREX_DUMMY)},
    {0x1F84, FTR_START(FTR_DIN_BRONT_DUMMY)},
    {0x1F88, FTR_START(FTR_DIN_PTERA_DUMMY)},
    {0x1F8C, FTR_START(FTR_DIN_HUTABA_DUMMY)},
    {0x1F90, FTR_START(FTR_DIN_MAMMOTH_DUMMY)},
    {0x1F94, FTR_START(FTR_DIN_STEGO_DUMMYA)},
    {0x1F98, FTR_START(FTR_DIN_STEGO_DUMMYB)},
    {0x1F9C, FTR_START(FTR_DIN_DUMMY)},
    {0x1FA0, FTR_START(FTR_TAK_SYOGI)},
    {0x1FA4, FTR_START(FTR_IKE_JNY_MAKADA01)},
    {0x1FA8, EMPTY_NO}, // mailbox (DnM+)
    {0x1FAC, FTR_START(FTR_IKE_PST_PIG01)},
    {0x1FB0, FTR_START(FTR_IKE_PST_TESYU01)},
    {0x1FB4, FTR_START(FTR_IKE_JNY_AFMEN01)},
    {0x1FB8, FTR_START(FTR_IKE_JNY_ROSIA01)},
    {0x1FBC, EMPTY_NO}, // Legend of Zelda (Disk System)
    {0x1FC0, FTR_START(FTR_IKE_JNY_BOTLE01)},
    {0x1FC4, FTR_START(FTR_IKE_JNY_HARIKO01)},
    {0x1FC8, FTR_START(FTR_IKE_JNY_MOAI01)},
    {0x1FCC, FTR_START(FTR_RADIO_TEST)},
    {0x1FD0, FTR_START(FTR_IKE_JNY_GOJYU01)},
    {0x1FD4, FTR_START(FTR_IKE_JNY_KIBORI01)},
    {0x1FD8, FTR_START(FTR_IKE_JNY_TRUTH01)},
    {0x1FDC, FTR_START(FTR_IKE_JNY_SIRSER01)},
    {0x1FE0, FTR_START(FTR_IKE_JNY_PISA01)},
    {0x1FE4, FTR_START(FTR_TAK_LION)},
    {0x1FE8, FTR_START(FTR_IKE_JNY_SYON01)},
    {0x1FEC, FTR_START(FTR_IKE_JNY_TOWER01)},
    {0x1FF0, FTR_START(FTR_NOG_BALLOON_COMMON0)},
    {0x1FF4, FTR_START(FTR_NOG_BALLOON_COMMON1)},
    {0x1FF8, FTR_START(FTR_NOG_BALLOON_COMMON2)},
    {0x1FFC, FTR_START(FTR_NOG_BALLOON_COMMON3)},
    {0x3000, FTR_START(FTR_NOG_BALLOON_COMMON4)},
    {0x3004, FTR_START(FTR_NOG_BALLOON_COMMON5)},
    {0x3008, FTR_START(FTR_NOG_BALLOON_COMMON6)},
    {0x300C, FTR_START(FTR_NOG_BALLOON_COMMON7)},
    {0x3010, FTR_START(FTR_TAK_MEGAMI)},
    {0x3014, FTR_START(FTR_IKE_JNY_GATE01)},
    {0x3018, FTR_START(FTR_TAK_MONEY)},
    {0x301C, FTR_START(FTR_IKE_JNY_NINGYO01)},
    {0x3020, FTR_START(FTR_NOG_YUBIN)},
    {0x3024, FTR_START(FTR_NOG_MYHOME2)},
    {0x3028, FTR_START(FTR_NOG_MYHOME4)},
    {0x302C, FTR_START(FTR_NOG_KOBAN)},
    {0x3030, FTR_START(FTR_NOG_MUSEUM)},
    {0x3034, FTR_START(FTR_TAK_YOROI)},
    {0x3038, EMPTY_NO}, // moon dumpling
    {0x303C, EMPTY_NO}, // bean set
    {0x3040, EMPTY_NO}, // osechi
    {0x3044, FTR_START(FTR_IKE_K_OTOME01)},
    {0x3048, FTR_START(FTR_NOG_YAMISHOP)},
    {0x304C, FTR_START(FTR_NOG_URANAI)},
    {0x3050, FTR_START(FTR_IKE_JNY_SIRSER201)},
    {0x3054, FTR_START(FTR_IKE_K_TANABATA01)},
    {0x3058, EMPTY_NO}, // spring medal (DnM+)
    {0x305C, EMPTY_NO}, // fall medal (DnM+)
    {0x3060, FTR_START(FTR_NOG_SHOP1)},
    {0x3064, FTR_START(FTR_IKE_JNY_HOUI01)},
    {0x3068, EMPTY_NO}, // long-life noodle
    {0x306C, EMPTY_NO}, // bass boat
    {0x3070, FTR_START(FTR_TAK_TOUDAI)},
    {0x3074, FTR_START(FTR_IKE_K_SUM01)},
    {0x3078, FTR_START(FTR_NOG_S_TREE)},
    {0x307C, FTR_START(FTR_NOG_F_TREE)},
    {0x3080, FTR_START(FTR_NOG_ZASSOU)},
    {0x3084, FTR_START(FTR_TAK_TAILOR)},
    {0x3088, FTR_START(FTR_NOG_DUMP)},
    {0x308C, EMPTY_NO}, // mortar ball
    {0x3090, FTR_START(FTR_NOG_SNOWMAN)},
    {0x3094, FTR_START(FTR_IKE_K_IVEBOY01)},
    {0x3098, EMPTY_NO}, // big catch flag
    {0x309C, FTR_START(FTR_TAK_MOON)},
    {0x30A0, FTR_START(FTR_IKE_K_KID01)},
    {0x30A4, FTR_START(FTR_IID_NINGYOU)},
    {0x30A8, FTR_START(FTR_NOG_STATION00)},
    {0x30AC, FTR_START(FTR_NOG_STATION01)},
    {0x30B0, FTR_START(FTR_NOG_STATION02)},
    {0x30B4, FTR_START(FTR_NOG_STATION03)},
    {0x30B8, FTR_START(FTR_NOG_STATION04)},
    {0x30BC, FTR_START(FTR_NOG_STATION05)},
    {0x30C0, FTR_START(FTR_NOG_STATION06)},
    {0x30C4, FTR_START(FTR_NOG_STATION07)},
    {0x30C8, FTR_START(FTR_NOG_STATION08)},
    {0x30CC, FTR_START(FTR_NOG_STATION09)},
    {0x30D0, FTR_START(FTR_NOG_STATION10)},
    {0x30D4, FTR_START(FTR_NOG_STATION11)},
    {0x30D8, FTR_START(FTR_NOG_STATION12)},
    {0x30DC, FTR_START(FTR_NOG_STATION13)},
    {0x30E0, FTR_START(FTR_NOG_STATION14)},
    {0x30E4, EMPTY_NO}, // shrine model
    {0x30E8, FTR_START(FTR_NOG_FLAT)},
    {0x30EC, FTR_START(FTR_NOG_RAIL)},
    {0x30F0, FTR_START(FTR_NOG_EARTH)},
    {0x30F4, FTR_START(FTR_IKE_K_KID02)},
    {0x30F8, FTR_START(FTR_NOG_MIKANBOX)},
    {0x30FC, FTR_START(FTR_NOG_COLLEGENOTE)},
    {0x3100, FTR_START(FTR_NOG_SCHOOLNOTE)},
    {0x3104, FTR_START(FTR_NOG_SYSTEMNOTE)},
    {0x3108, FTR_START(FTR_NOG_HARDDIARY)},
    {0x310C, FTR_START(FTR_NOG_TUDURINOTE)},
    {0x3110, FTR_START(FTR_IID_DIARY)},
    {0x3114, FTR_START(FTR_IID_FUNEDIARY)},
    {0x3118, FTR_START(FTR_IID_MDIARY)},
    {0x311C, FTR_START(FTR_IID_NEWDIARY)},
    {0x3120, FTR_START(FTR_TAK_NIKKI01)},
    {0x3124, FTR_START(FTR_IKE_NIKKI_FAN1)},
    {0x3128, FTR_START(FTR_IKE_NIKKI_FAN2)},
    {0x312C, FTR_START(FTR_IKE_NIKKI_FAN3)},
    {0x3130, FTR_START(FTR_IKE_NIKKI_FAN4)},
    {0x3134, FTR_START(FTR_IKE_NIKKI_FAN5)},
    {0x3138, FTR_START(FTR_IKE_NIKKI_WAFU1)},
    {0x313C, FTR_START(FTR_GOLD_ITEM0)},
    {0x3140, FTR_START(FTR_GOLD_ITEM1)},
    {0x3144, FTR_START(FTR_GOLD_ITEM2)},
    {0x3148, FTR_START(FTR_GOLD_ITEM3)},
    {0x314C, FTR_START(FTR_UTIWA0)},
    {0x3150, FTR_START(FTR_UTIWA1)},
    {0x3154, FTR_START(FTR_UTIWA2)},
    {0x3158, FTR_START(FTR_UTIWA3)},
    {0x315C, FTR_START(FTR_UTIWA4)},
    {0x3160, FTR_START(FTR_UTIWA5)},
    {0x3164, FTR_START(FTR_UTIWA6)},
    {0x3168, FTR_START(FTR_UTIWA7)},
    {0x316C, FTR_START(FTR_KAZAGURUMA0)},
    {0x3170, FTR_START(FTR_KAZAGURUMA1)},
    {0x3174, FTR_START(FTR_KAZAGURUMA2)},
    {0x3178, FTR_START(FTR_KAZAGURUMA3)},
    {0x317C, FTR_START(FTR_KAZAGURUMA4)},
    {0x3180, FTR_START(FTR_KAZAGURUMA5)},
    {0x3184, FTR_START(FTR_KAZAGURUMA6)},
    {0x3188, FTR_START(FTR_KAZAGURUMA7)},
    {0x318C, FTR_START(FTR_TOOL0)},
    {0x3190, FTR_START(FTR_TOOL1)},
    {0x3194, FTR_START(FTR_TOOL2)},
    {0x3198, FTR_START(FTR_TOOL3)},
    {0x319C, FTR_START(FTR_NOG_NABE)},
    {0x31A0, FTR_START(FTR_IKE_KAMA_DANRO01)},
    {0x31A4, FTR_START(FTR_NOG_KAMAKURA)},
    {0x31A8, FTR_START(FTR_NOG_W_TREE)},
    {0x31AC, FTR_START(FTR_TAK_ICE)},
    {0x31B0, FTR_START(FTR_IKE_ISLAND_HAKO01)},
    {0x31B4, FTR_START(FTR_NOG_BEACHBED)},
    {0x31B8, FTR_START(FTR_NOG_BEACHTABLE)},
    {0x31BC, EMPTY_NO}, // hibachi grill
    {0x31C0, FTR_START(FTR_IID_SURF)},
    {0x31C4, FTR_START(FTR_IID_SNOW)},
    {0x31C8, FTR_START(FTR_TAK_TETRA)},
    {0x31CC, FTR_START(FTR_IKE_ISLAND_UKU01)},
    {0x31D0, FTR_START(FTR_IKE_ISLAND_SENSUI01)},
    {0x31D4, FTR_START(FTR_IID_YUKI)},
    {0x31D8, EMPTY_NO}, // scary painting
    {0x31DC, EMPTY_NO}, // novel painting
    {0x31E0, FTR_START(FTR_TAK_SORI01)},
    {0x31E4, FTR_START(FTR_IID_BENTI)},
    {0x31E8, FTR_START(FTR_TAK_CUBE)},
};

static mActor_name_t mRC_itemP_to_itemPP(mActor_name_t itemP) {
    int i;

    for (i = 0; i < ARRAY_COUNT(mRC_item_remove_data); i++) {
        if (mRC_item_remove_data[i].item_plus == itemP) {
            return (mActor_name_t)mRC_item_remove_data[i].item_plusplus;
        }
    }

    return itemP;
}

static mActor_name_t mRC_ftrP_to_ftrPP(mActor_name_t itemP) {
    int i;

    if (!ITEM_IS_FTR(itemP)) {
        return itemP;
    }

    for (i = 0; i < ARRAY_COUNT(mRC_ftr_remove_data); i++) {
        if (mRC_ftr_remove_data[i].item_plus == itemP) {
            return (mActor_name_t)mRC_ftr_remove_data[i].item_plusplus;
        }
    }

    return itemP;
}

static mActor_name_t mRC_ItemP_to_ItemPP(mActor_name_t itemP) {
    if (ITEM_IS_FTR(itemP)) {
        return mRC_ftrP_to_ftrPP(itemP);
    } else {
        return mRC_itemP_to_itemPP(itemP);
    }
}

static mActor_name_t mRC_wall_idx_to_item_no(int wall_idx) {
    return ITM_WALL_START + wall_idx;
}

static int mRC_item_no_to_wall_idx(mActor_name_t item_no) {
    return item_no - ITM_WALL_START;
}

static mActor_name_t mRC_carpet_idx_to_item_no(int carpet_idx) {
    return ITM_CARPET_START + carpet_idx;
}

static int mRC_item_no_to_carpet_idx(mActor_name_t item_no) {
    return item_no - ITM_CARPET_START;
}

static mActor_name_t mRC_paper_idx_to_item_no(int paper_idx) {
    return ITM_PAPER_START + paper_idx;
}

static int mRC_item_no_to_paper_idx(mActor_name_t item_no) {
    return PAPER2TYPE(item_no - ITM_PAPER_START);
}

static mActor_name_t mRC_music_idx_to_item_no(int music_idx) {
    return ITM_MINIDISK_START + music_idx;
}

static int mRC_item_no_to_music_idx(mActor_name_t item_no) {
    return item_no - ITM_MINIDISK_START;
}

static mActor_name_t mRC_ftr_idx_to_item_no(int ftr_idx) {
    return mNT_ftr_idx_to_ftr_item_no(ftr_idx, 0);
}

static int mRC_item_no_to_ftr_idx(mActor_name_t item_no) {
    return mNT_ftr_item_no_to_ftr_idx(item_no);
}

typedef mActor_name_t (*mRC_IDX2ITEM_PROC)(int idx);
typedef int (*mRC_ITEM2IDX_PROC)(mActor_name_t item_no);

static void mRC_remove_cb(u32* pp_cb, u32* p_cb, int p_count, mRC_IDX2ITEM_PROC idx2item, mRC_ITEM2IDX_PROC item2idx) {
    int i;

    for (i = 0; i < p_count; i++) {
        if ((p_cb[i >> 5] >> (i & 0x1F)) & 1) {
            mActor_name_t itemP = idx2item(i);
            mActor_name_t itemPP = mRC_ItemP_to_ItemPP(itemP);

            if (itemPP != EMPTY_NO) {
                int idxPP = item2idx(itemPP);
                pp_cb[idxPP >> 5] |= 1 << (idxPP & 0x1F);
            }
        }
    }
}

extern void mRC_remove_collect_data_P_to_PP(Private_c* pp_priv, u8* p_priv) {
    int i;

    mRC_remove_cb(pp_priv->furniture_collected_bitfield, (u32*)(p_priv + 0xB3C), 1172, mRC_ftr_idx_to_item_no, mRC_item_no_to_ftr_idx);
    mRC_remove_cb(pp_priv->wall_collected_bitfield, (u32*)(p_priv + 0xBD0), 64, mRC_wall_idx_to_item_no, mRC_item_no_to_wall_idx);
    mRC_remove_cb(pp_priv->carpet_collected_bitfield, (u32*)(p_priv + 0xBD8), 64, mRC_carpet_idx_to_item_no, mRC_item_no_to_carpet_idx);
    mRC_remove_cb(pp_priv->paper_collected_bitfield, (u32*)(p_priv + 0xBE0), 64, mRC_paper_idx_to_item_no, mRC_item_no_to_paper_idx);
    mRC_remove_cb(pp_priv->music_collected_bitfield, (u32*)(p_priv + 0xBE8), 64, mRC_music_idx_to_item_no, mRC_item_no_to_music_idx);
    memcpy(pp_priv->my_org, (u8*)(p_priv + 0xC40), sizeof(pp_priv->my_org));

    for (i = 0; i < mPr_ORIGINAL_DESIGN_COUNT; i++) {
        pp_priv->my_org[i].attr = RANDOM(mNT_STYLE_NUM);
    }
}
