#include "m_mark_room.h"

#include "m_item_name.h"
#include "m_name_table.h"
#include "m_room_type.h"
#include "m_handbill.h"
#include "m_common_data.h"
#include "m_font.h"
#include "m_string.h"
#include "m_house.h"

typedef struct series_info_s {
    u8 type;
    u8 num_ftr;
    u8 wall_floor_idx;
} mMkRm_series_info_c;

static mMkRm_series_info_c mMkRm_series_info[mMkRm_SERIES_NUM] = {
    { mMkRm_SERIES_TYPE_BASE, 0, 8 },   // mMkRm_SERIES_EXOTIC
    { mMkRm_SERIES_TYPE_BASE, 0, 7 },   // mMkRm_SERIES_LOVELY
    { mMkRm_SERIES_TYPE_BASE, 0, 1 },   // mMkRm_SERIES_CLASSIC
    { mMkRm_SERIES_TYPE_BASE, 0, 22 },  // mMkRm_SERIES_RANCH
    { mMkRm_SERIES_TYPE_BASE, 0, 24 },  // mMkRm_SERIES_CABANA
    { mMkRm_SERIES_TYPE_BASE, 0, 20 },  // mMkRm_SERIES_BLUE
    { mMkRm_SERIES_TYPE_BASE, 0, 23 },  // mMkRm_SERIES_MODERN
    { mMkRm_SERIES_TYPE_BASE, 0, 21 },  // mMkRm_SERIES_REGAL
    { mMkRm_SERIES_TYPE_BASE, 0, 19 },  // mMkRm_SERIES_GREEN
    { mMkRm_SERIES_TYPE_BASE, 0, 13 },  // mMkRm_SERIES_CABIN
    { mMkRm_SERIES_TYPE_BASE, 0, 17 },  // mMkRm_SERIES_SPOOKY
    { mMkRm_SERIES_TYPE_BASE, 0, 47 },  // mMkRm_SERIES_JINGLE
    { mMkRm_SERIES_TYPE_BASE, 0, 54 },  // mMkRm_SERIES_KIDDIE
    { mMkRm_SERIES_TYPE_THEME, 0, 9 },  // mMkRm_SERIES_GARDEN
    { mMkRm_SERIES_TYPE_THEME, 0, 16 }, // mMkRm_SERIES_ROCKGARDEN
    { mMkRm_SERIES_TYPE_THEME, 0, 68 }, // mMkRm_SERIES_JAPANESE
    { mMkRm_SERIES_TYPE_THEME, 0, 14 }, // mMkRm_SERIES_CONSTRUCTION
    { mMkRm_SERIES_TYPE_THEME, 0, 15 }, // mMkRm_SERIES_SPACE
    { mMkRm_SERIES_TYPE_THEME, 0, 67 }, // mMkRm_SERIES_PUBLICBATH
    { mMkRm_SERIES_TYPE_THEME, 0, 6 },  // mMkRm_SERIES_SCHOOL
    { mMkRm_SERIES_TYPE_THEME, 0, 53 }, // mMkRm_SERIES_CHESS
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_BONSAI
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_WRITING
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_VASE
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_VENDING
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_NINTENDO
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_DARUMA
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_CACTUS
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_BEAR
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_FIGURE
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_TOTEMPOLE
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_GUITAR
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_DRUM
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_STRINGS
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_OFFICE
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_TRICERA
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_TREX
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_BRONT
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_STEGO
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_PTERA
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_PLESIO
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_MAMMOTH
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_ROBOT
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_APPLE
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_CITRUS
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_MELON
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_PEAR
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_LUCKY
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_PINE
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_FROGGY
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_IRIS
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_TULIP
    { mMkRm_SERIES_TYPE_SET, 0, 255 },  // mMkRm_SERIES_DAFFODIL
    { mMkRm_SERIES_TYPE_ONE, 0, 255 },  // mMkRm_SERIES_OTHER
    { mMkRm_SERIES_TYPE_BASE, 0, 25 },  // mMkRm_SERIES_SNOWMAN
    { mMkRm_SERIES_TYPE_THEME, 0, 18 }, // mMkRm_SERIES_WESTERN
    { mMkRm_SERIES_TYPE_THEME, 0, 26 }, // mMkRm_SERIES_BACKYARD
    { mMkRm_SERIES_TYPE_BASE, 0, 66 },  // mMkRm_SERIES_HARVEST
    { mMkRm_SERIES_TYPE_THEME, 0, 65 }, // mMkRm_SERIES_BOXING
    { mMkRm_SERIES_TYPE_THEME, 0, 64 }  // mMkRm_SERIES_MARIO
};

static u8 mMkRm_series_name[mMkRm_SERIES_NUM][mIN_ITEM_NAME_LEN] = {
    { CHAR_PP_145, CHAR_PP_212, CHAR_PP_145, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_183, CHAR_PP_223, CHAR_PP_184, CHAR_PP_144, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_156, CHAR_PP_143, CHAR_PP_152, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_150, CHAR_PP_189, CHAR_PP_164, CHAR_PP_184, CHAR_PP_144, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_184, CHAR_PP_215, CHAR_PP_144, CHAR_PP_164, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_000, CHAR_PP_004, CHAR_PP_001, CHAR_PP_192, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_179, CHAR_PP_169, CHAR_PP_152, CHAR_PP_187, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_187, CHAR_PP_146, CHAR_PP_180, CHAR_PP_185, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_031, CHAR_PP_245, CHAR_PP_124, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_187, CHAR_PP_208, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_170, CHAR_PP_187, CHAR_PP_147, CHAR_PP_136, CHAR_PP_189, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_152, CHAR_PP_184, CHAR_PP_157, CHAR_PP_175, CHAR_PP_157, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_150, CHAR_PP_183, CHAR_PP_172, CHAR_PP_185, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_021, CHAR_PP_193, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_005, CHAR_PP_126, CHAR_PP_010, CHAR_PP_195, CHAR_PP_012, CHAR_PP_001, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_193, CHAR_PP_027, CHAR_PP_002, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_009, CHAR_PP_002, CHAR_PP_237, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_002, CHAR_PP_016, CHAR_PP_202, CHAR_PP_002, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_013, CHAR_PP_195, CHAR_PP_019, CHAR_PP_002, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_231, CHAR_PP_204, CHAR_PP_009, CHAR_PP_002, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_161, CHAR_PP_138, CHAR_PP_157, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_250, CHAR_PP_195, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_249, CHAR_PP_195, CHAR_PP_006, CHAR_PP_203, CHAR_PP_002, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_017, CHAR_PP_250, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_237, CHAR_PP_025, CHAR_PP_195, CHAR_PP_006, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_021, CHAR_PP_195, CHAR_PP_018, CHAR_PP_195, CHAR_PP_245, CHAR_PP_002, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_241, CHAR_PP_125, CHAR_PP_030, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_155, CHAR_PP_225, CHAR_PP_163, CHAR_PP_189, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_007, CHAR_PP_030, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_009, CHAR_PP_008, CHAR_PP_011, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_164, CHAR_PP_144, CHAR_PP_163, CHAR_PP_177, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_207, CHAR_PP_160, CHAR_PP_144, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_220, CHAR_PP_183, CHAR_PP_177, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_234, CHAR_PP_195, CHAR_PP_231, CHAR_PP_007, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_237, CHAR_PP_035, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_164, CHAR_PP_184, CHAR_PP_153, CHAR_PP_183, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_163, CHAR_PP_136, CHAR_PP_183, CHAR_PP_169, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_145, CHAR_PP_226, CHAR_PP_164, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_157, CHAR_PP_163, CHAR_PP_210, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_228, CHAR_PP_163, CHAR_PP_183, CHAR_PP_169, CHAR_PP_220, CHAR_PP_189, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_172, CHAR_PP_160, CHAR_PP_221, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_175, CHAR_PP_189, CHAR_PP_179, CHAR_PP_157, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_187, CHAR_PP_225, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_184, CHAR_PP_189, CHAR_PP_210, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_005, CHAR_PP_195, CHAR_PP_006, CHAR_PP_017, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_157, CHAR_PP_146, CHAR_PP_150, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_182, CHAR_PP_147, CHAR_PP_165, CHAR_PP_156, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_030, CHAR_PP_023, CHAR_PP_006, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_226, CHAR_PP_146, CHAR_PP_189, CHAR_PP_236, CHAR_PP_001, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_150, CHAR_PP_148, CHAR_PP_185, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_011, CHAR_PP_192, CHAR_PP_001, CHAR_PP_004, CHAR_PP_025, CHAR_PP_020, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_000, CHAR_PP_005, CHAR_PP_001, CHAR_PP_004, CHAR_PP_025, CHAR_PP_020, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_006, CHAR_PP_001, CHAR_PP_192, CHAR_PP_024, CHAR_PP_025, CHAR_PP_020, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_014, CHAR_PP_024, CHAR_PP_015, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_094, CHAR_PP_006, CHAR_PP_241, CHAR_PP_125, CHAR_PP_030, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_147, CHAR_PP_138, CHAR_PP_157, CHAR_PP_160, CHAR_PP_189, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_206, CHAR_PP_144, CHAR_PP_219, CHAR_PP_189, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_170, CHAR_PP_144, CHAR_PP_224, CHAR_PP_157, CHAR_PP_164, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_228, CHAR_PP_187, CHAR_PP_186, CHAR_PP_157, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
    { CHAR_PP_175, CHAR_PP_184, CHAR_PP_149, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032, CHAR_PP_032,
      CHAR_PP_032, CHAR_PP_032 },
};

static int mMkRm_birth_point_table[mRmTp_BIRTH_TYPE_NUM] = {
    51,   /* mRmTp_BIRTH_TYPE_GRP_A */
    51,   /* mRmTp_BIRTH_TYPE_GRP_B */
    51,   /* mRmTp_BIRTH_TYPE_GRP_C */
    412,  /* mRmTp_BIRTH_TYPE_EVENT */
    1000, /* mRmTp_BIRTH_TYPE_BIRTHDAY */
    1031, /* mRmTp_BIRTH_TYPE_HALLOWEEN */
    821,  /* mRmTp_BIRTH_TYPE_HANIWA */
    1029, /* mRmTp_BIRTH_TYPE_LOTTERY */
    3,    /* mRmTp_BIRTH_TYPE_FTR_CLOTH */
    3,    /* mRmTp_BIRTH_TYPE_FTR_UMBRELLA */
    3,    /* mRmTp_BIRTH_TYPE_FTR_INSECT */
    3,    /* mRmTp_BIRTH_TYPE_FTR_FISH */
    300,  /* mRmTp_BIRTH_TYPE_SINGLE_FOSSIL */
    1000, /* mRmTp_BIRTH_TYPE_MULTI_FOSSIL */
    700,  /* mRmTp_BIRTH_TYPE_XMAS */
    1224, /* mRmTp_BIRTH_TYPE_SANTA */
    0,    /* mRmTp_BIRTH_TYPE_UNOBTAINABLE */
    888,  /* mRmTp_BIRTH_TYPE_SNOWMAN */
    1031, /* mRmTp_BIRTH_TYPE_HALLOWEEN_TRICK */
    1111, /* mRmTp_BIRTH_TYPE_POST_OFFICE */
    1111, /* mRmTp_BIRTH_TYPE_MARK_ROOM */
    1111, /* mRmTp_BIRTH_TYPE_SONCHO */
    412,  /* mRmTp_BIRTH_TYPE_JONASON */
    1000, /* mRmTp_BIRTH_TYPE_UNUSED_23 */
    1983, /* mRmTp_BIRTH_TYPE_FAMICOM_EREADER */
    1300, /* mRmTp_BIRTH_TYPE_ISLAND */
    1983, /* mRmTp_BIRTH_TYPE_FAMICOM_ISLAND */
    3,    /* mRmTp_BIRTH_TYPE_MY_ORIGINAL */
    1983, /* mRmTp_BIRTH_TYPE_FAMICOM_CODE */
    1111, /* mRmTp_BIRTH_TYPE_MUSEUM */
    412,  /* mRmTp_BIRTH_TYPE_SONCHO_LIGHTHOUSE_QUEST */
    0,    /* mRmTp_BIRTH_TYPE_FTR_DIARY */
    412,  /* mRmTp_BIRTH_TYPE_GROUNDHOG */
    412,  /* mRmTp_BIRTH_TYPE_KAMAKURA */
    1000, /* mRmTp_BIRTH_TYPE_NINTENDO_CODE */
    1177, /* mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL */
    1400, /* mRmTp_BIRTH_TYPE_UNUSED_36 */
    412,  /* mRmTp_BIRTH_TYPE_SUMMER_CAMPER */
    1400, /* mRmTp_BIRTH_TYPE_GBA_MINIGAME */
    412,  /* mRmTp_BIRTH_TYPE_OLD_NPC_CODE */
};

typedef struct mark_room_ftr_info_s {
    u8 series : 6;
    u16 group_idx : 10; /* for base series, 0-4 are "necessities" */
    u8 has_face : 1;    /* has a "face" */
    u8 is_lucky : 1;
    u8 birth_type : 6;
    u8 surface_type : 2;
    /* u8 pad:6; */
} mMkRm_ftr_info_c;

#include "../src/game/m_mark_room_ovl_data.c_inc"

static u8 mMkRm_wall_from[WALL_NUM] = {
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
};

static u8 mMkRm_floor_from[CARPET_NUM] = {
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
};

static int mMkRm_unit_max_table[mHm_HOMESIZE_NUM - 2] = { 5, 7, 9, 9 };

static int mMkRm_letter_no_table[64] = {
    52, 53, 54, 55, 56, 57, 58, 59, -1,  -1, -1, -1, -1, -1, -1, -1, 60, 61, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, 62, 63, 64, 65, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, 66, 67, 68, 69, 544, 70, 71, 72, -1, -1, -1, -1, -1, -1, -1, -1,
};

static void mMkRm_GetSeriesName(u8* buf, int series) {
    if (series < 0) {
        return;
    }

    if (series >= mMkRm_SERIES_NUM) {
        return;
    }

    {
        const u8* src = mMkRm_series_name[series];
        int i;

        for (i = 0; i < mIN_ITEM_NAME_LEN; i++) {
            *buf++ = *src++;
        }
    }
}

static mActor_name_t mMkRm_GetRemainOneFtr(int idx, int series) {
    int i;

    for (i = 0; i < FTR_NUM; i++) {
        int ftr_series = mMkRm_ftr_info[i].series;
        int group_idx = mMkRm_ftr_info[i].group_idx;

        if (ftr_series == series && group_idx == idx) {
            return mNT_ftr_idx_to_ftr_item_no(i, mRmTp_DIRECT_SOUTH);
        }
    }

    return EMPTY_NO;
}

static void mMkRm_ProcAfterSending(mHm_hs_c* house, int handbill_no) {
    if (handbill_no == mHandbill_HRA_REWARD0) {
        house->flags.hra_reward0 = TRUE;
    } else if (handbill_no == mHandbill_HRA_REWARD1) {
        house->flags.hra_reward1 = TRUE;
    }
}

static u64 mMkRm_letter_bit;

static int mMkRm_DecideLetterNo(mActor_name_t* present, mHm_hs_c* house, int points, int room_size) {
    int idx;
    int letter_idx = RANDOM(3);

    if (points >= mMkRm_REWARD0_POINTS && house->flags.hra_reward0 == FALSE) {
        present[0] = FTR_START(FTR_NOG_MYHOME2);
        return mHandbill_HRA_REWARD0;
    } else if (points >= mMkRm_REWARD1_POINTS && house->flags.hra_reward1 == FALSE) {
        present[0] = FTR_START(FTR_NOG_MYHOME4);
        return mHandbill_HRA_REWARD1;
    } else {
        int i;

        for (i = 15; i >= 0; i--) {
            idx = i + letter_idx * 16;

            if (((mMkRm_letter_bit >> idx) & 1) != 0 && mMkRm_letter_no_table[idx] != -1) {
                return mMkRm_letter_no_table[idx];
            }
        }

        if (points < 1) {
            return 0x42;
        } else if (points < 20000) {
            switch (room_size) {
                case mHm_ROOMTYPE_SMALL:
                    return 0x43;
                case mHm_ROOMTYPE_MEDIUM:
                    return 0x44;
                case mHm_ROOMTYPE_LARGE:
                    return 0x45;
                case mHm_ROOMTYPE_COTTAGE:
                    return 0x220;
                default:
                    return 0x220;
            }
        } else if (points < mMkRm_REWARD0_POINTS) {
            return 0x46;
        } else {
            return points < mMkRm_REWARD1_POINTS ? 0x47 : 0x48;
        }
    }
}

static mActor_name_t mMkRm_GetSetItemNo(mActor_name_t base_item, mActor_name_t theme_item) {
    if (base_item != EMPTY_NO) {
        return base_item;
    }

    if (theme_item != EMPTY_NO) {
        return theme_item;
    }

    return EMPTY_NO;
}

static int mMkRm_CountCharactor(u8* str, int len, int forward) {
    int i;

    if (forward == FALSE) {
        for (i = 0; i < len; i++) {
            if (*str == CHAR_SPACE) {
                return i + 1;
            }

            str++;
        }
    } else {
        i = len - 1;

        str += i;
        for (; i >= 0; i--, str--) {
            if (str[0] != CHAR_SPACE) {
                return i + 1;
            }
        }
    }

    return len;
}

static void mMkRm_SendMarkLetter(mHm_hs_c* house, int points, int room_size, u8* series_name, mActor_name_t base_item,
                                 mActor_name_t theme_item) {
    int header_back_start;
    mActor_name_t present;
    u8 year_str[4];
    u8 month_str[2];
    u8 day_str[2];
    u8 item_str[mIN_ITEM_NAME_LEN];
    u8 points_str[10];

    Mail_c letter;
    int free_idx;
    int handbill_no;
    lbRTC_time_c time;

    free_idx = mMl_chk_mail_free_space(house->mailbox, HOME_MAILBOX_SIZE);
    present = EMPTY_NO;
    handbill_no = mMkRm_DecideLetterNo(&present, house, points, room_size);
    time = Common_Get(time.rtc_time);

    mFont_UnintToString(points_str, 10, points, 10, FALSE, FALSE, FALSE);
    mHandbill_Set_free_str(mHandbill_FREE_STR0, points_str, 10);

    {
        mActor_name_t set_item_no = mMkRm_GetSetItemNo(base_item, theme_item);
        int character;

        mIN_copy_name_str(item_str, set_item_no);
        character = mMkRm_CountCharactor(item_str, mIN_ITEM_NAME_LEN, FALSE);
        mHandbill_Set_free_str(mHandbill_FREE_STR1, item_str, character);
    }

    {
        int character = mMkRm_CountCharactor(series_name, mIN_ITEM_NAME_LEN, FALSE);

        mHandbill_Set_free_str(mHandbill_FREE_STR2, series_name, character);
    }

    mFont_UnintToString(year_str, 4, time.year, 4, FALSE, FALSE, FALSE);
    mHandbill_Set_free_str(mHandbill_FREE_STR3, year_str, 4);

    mFont_UnintToString(month_str, 2, time.month, 2, FALSE, FALSE, FALSE);
    mHandbill_Set_free_str(mHandbill_FREE_STR4, month_str, 2);

    mFont_UnintToString(day_str, 2, time.day, 2, TRUE, FALSE, FALSE);
    mHandbill_Set_free_str(mHandbill_FREE_STR5, day_str, 2);

    mMl_clear_mail(&letter);
    mHandbill_Load_HandbillFromRom(letter.content.text.split.header, &header_back_start,
                                   letter.content.text.split.footer, letter.content.text.split.body, handbill_no);
    letter.content.font = mMl_FONT_RECV;
    letter.content.header_back_start = header_back_start;
    letter.content.mail_type = mMl_TYPE_HRA;
    letter.content.paper_type = 51; /* wing paper */
    letter.present = present;
    mMl_set_to_plname(&letter, &Common_Get(now_private)->player_ID);

    if (free_idx >= 0) {
        mMl_copy_mail(house->mailbox + free_idx, &letter);
        mMkRm_ProcAfterSending(house, handbill_no);
    } else {
        letter.header.recipient.type = mMl_NAME_TYPE_PLAYER;

        if (mPO_receipt_proc(&letter, mPO_SENDTYPE_MAIL)) {
            mMkRm_ProcAfterSending(house, handbill_no);
        }
    }
}

static void mMkRm_ForbidMinusPoint(int* points) {
    if (points[0] < 0) {
        points[0] = 0;
    }
}

static mActor_name_t ftr_fg_table1[UT_TOTAL_NUM];
static u32 mMkRm_search_table[mMkRm_SERIES_NUM];
static mActor_name_t ftr_fg_table2[UT_TOTAL_NUM];

static void mMkRm_EvaluateLetsClean(int* points, mActor_name_t** layer_ut_info, int ut_max) {
    int layer;
    int remove_points = 0;
    mActor_name_t* ut_info;
    int ut_x;
    int ut_z;

    for (layer = mCoBG_LAYER0; layer < mCoBG_LAYER2; layer++) {
        ut_info = layer_ut_info[layer];

        if (ut_info != NULL) {
            for (ut_z = 1; ut_z < ut_max; ut_z++) {
                for (ut_x = 1; ut_x < ut_max; ut_x++) {
                    mActor_name_t item = ut_info[(ut_z * UT_Z_NUM) + ut_x];

                    switch (layer) {
                        case mCoBG_LAYER0: {
                            if (!ITEM_IS_FTR(item) && item != RSV_NO && item != EMPTY_NO && item != RSV_WALL_NO &&
                                item != RSV_DOOR && item != EXIT_DOOR && item != RSV_FE1F && item != RSV_FE1C) {
                                remove_points++;
                            }

                            break;
                        }

                        case mCoBG_LAYER1: {
                            if (!ITEM_IS_FTR(item) && item != RSV_NO && item != EMPTY_NO && item != RSV_WALL_NO &&
                                item != RSV_DOOR && item != EXIT_DOOR && item != RSV_FE1F && item != RSV_FE1C &&
                                !IS_ITEM_DIARY(item)) {
                                item = ftr_fg_table1[(ut_z * UT_Z_NUM) + ut_x];

                                /* Check that the item below is furniture which has a surface (prevents storage from
                                 * taking away points)*/
                                if (item != EMPTY_NO && ITEM_IS_FTR(item) &&
                                    mMkRm_ftr_info[mNT_ftr_item_no_to_ftr_idx(item)].surface_type ==
                                        mMkRm_SURFACE_TYPE_SURFACE) {
                                    remove_points++;
                                }
                            }

                            break;
                        }
                    }
                }
            }
        }
    }

    if (remove_points != 0) {
        points[0] -= remove_points;
        mMkRm_letter_bit |= mMkRm_LETTER_BIT_LETS_CLEAN;
    }
}

static void mMkRm_EvaluateCompleteObstacle(int* points, mActor_name_t** layer_ut_info, int ut_max, int theme_completed,
                                           int theme_idx) {
    int obstacles = 0;

    if (theme_completed == TRUE && theme_idx != -1) {
        int layer;

        for (layer = mCoBG_LAYER0; layer < mCoBG_LAYER2; layer++) {
            mActor_name_t* ut_info = layer_ut_info[layer];

            if (ut_info != NULL) {
                int ut_x;
                int ut_z;

                for (ut_z = 1; ut_z < ut_max; ut_z++) {
                    for (ut_x = 1; ut_x < ut_max; ut_x++) {
                        mActor_name_t item = ut_info[(ut_z * UT_Z_NUM) + ut_x];

                        if (ITEM_IS_FTR(item)) {
                            int ftr_no = mNT_ftr_item_no_to_ftr_idx(item);
                            int series = mMkRm_ftr_info[ftr_no].series;

                            if (series != theme_idx) {
                                obstacles++;
                            }
                        }
                    }
                }
            }
        }
    }

    if (obstacles != 0 && theme_completed != FALSE) {
        points[0] -= obstacles * mMkRm_THEME_OBSTACLE_PENALTY;
        mMkRm_letter_bit |= mMkRm_LETTER_BIT_THEME_OBSTACLE;
    }
}

static int mMkRm_CheckEdgeZone(int ut_x, int ut_z, int direction, int room_size) {
    switch (direction) {
        case mRmTp_DIRECT_SOUTH: {
            if (room_size == mHm_ROOMTYPE_SMALL) {
                if (ut_z == 4) {
                    return TRUE;
                }
            } else if (room_size == mHm_ROOMTYPE_MEDIUM) {
                if (ut_z == 6) {
                    return TRUE;
                }
            } else if (room_size == mHm_ROOMTYPE_LARGE || room_size == mHm_ROOMTYPE_COTTAGE) {
                if (ut_z == 8) {
                    return TRUE;
                }
            }

            return FALSE;
        }

        case mRmTp_DIRECT_EAST: {
            if (room_size == mHm_ROOMTYPE_SMALL) {
                if (ut_x == 4) {
                    return TRUE;
                }
            } else if (room_size == mHm_ROOMTYPE_MEDIUM) {
                if (ut_x == 6) {
                    return TRUE;
                }
            } else if (room_size == mHm_ROOMTYPE_LARGE || room_size == mHm_ROOMTYPE_COTTAGE) {
                if (ut_x == 8) {
                    return TRUE;
                }
            }

            return FALSE;
        }

        case mRmTp_DIRECT_NORTH: {
            return ut_z == 1;
        }

        case mRmTp_DIRECT_WEST: {
            return ut_x == 1;
        }
    }

    return FALSE;
}

static void mMkRm_EvaluateDirect(int* points, mActor_name_t** layer_ut_info, int ut_max, int room_size) {
    mRmTp_FtrPlaceInfoOne_t place_info[mRmTp_FTR_UNIT_MAX];
    int facing_wall = 0;
    int ut_x;
    int ut_z;
    int layer;

    for (layer = mCoBG_LAYER0; layer < mCoBG_LAYER2; layer++) {
        mActor_name_t* ut_info = layer_ut_info[layer];

        if (ut_info != NULL) {
            mActor_name_t item;

            for (ut_z = 1; ut_z < ut_max; ut_z++) {
                for (ut_x = 1; ut_x < ut_max; ut_x++) {
                    item = ut_info[(ut_z * UT_Z_NUM) + ut_x];

                    if (ITEM_IS_FTR(item)) {
                        int ftr_idx = mNT_ftr_item_no_to_ftr_idx(item);
                        int has_face = mMkRm_ftr_info[ftr_idx].has_face;

                        if (has_face) {
                            int dir = FTR_GET_ROTATION(item);
                            int i;

                            mRmTp_GetFurnitureData(item, ut_x, ut_z, place_info);

                            /* Check each possible spot a multi-space furniture may take up */
                            for (i = 0; i < mRmTp_FTR_UNIT_MAX; i++) {
                                int is_facing_wall = FALSE;

                                if (place_info[i].exists && /* furniture exists in this location */
                                    mMkRm_CheckEdgeZone(place_info[i].ut_x, place_info[i].ut_z, dir, room_size)) {
                                    is_facing_wall = TRUE;
                                    facing_wall++;
                                }

                                if (is_facing_wall == TRUE) {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (facing_wall > 0) {
        points[0] -= facing_wall * mMkRm_FACING_WALL_PENALTY;
        mMkRm_letter_bit |= mMkRm_LETTER_BIT_BAD_DIRECTION;
    }
}

static void mMkRm_EvaluateLuckyFurniture(int* points, mActor_name_t** layer_ut_info, int ut_max) {
    int layer;
    int lucky = 0;
    int ut_x;
    int ut_z;
    mActor_name_t* ut_info;

    for (layer = mCoBG_LAYER0; layer < mCoBG_LAYER2; layer++) {
        ut_info = layer_ut_info[layer];

        if (ut_info != NULL) {
            mActor_name_t item;

            for (ut_z = 1; ut_z < ut_max; ut_z++) {
                for (ut_x = 1; ut_x < ut_max; ut_x++) {
                    item = ut_info[(ut_z * UT_Z_NUM) + ut_x];

                    if (ITEM_IS_FTR(item) && mMkRm_ftr_info[mNT_ftr_item_no_to_ftr_idx(item)].is_lucky) {
                        lucky++;
                    }
                }
            }
        }
    }

    points[0] += lucky * mMkRm_LUCKY_BONUS;
}

static int mMkRm_EvaluateSetSeriesComplete(int* points) {
    int i;
    int set_series_complete = FALSE;

    for (i = 0; i < mMkRm_SERIES_NUM; i++) {
        int type = mMkRm_series_info[i].type;

        if (type == mMkRm_SERIES_TYPE_SET) {
            int ftr_in_set = mMkRm_series_info[i].num_ftr;

            if (ftr_in_set != 0) {
                u32 perfect_bit;
                int j;
                u32 complete_bit = mMkRm_search_table[i];
                int bits;

#ifndef IMPROVEMENTS
                perfect_bit = 0;

                for (j = 0; j < ftr_in_set; j++) {
                    perfect_bit |= (1 << j);
                }
#else
                perfect_bit = (1 << ftr_in_set) - 1;
#endif

                bits = complete_bit & perfect_bit;
                if (perfect_bit == bits) {
                    points[0] += ftr_in_set * mMkRm_SET_SERIES_COMPLETE_BONUS;
                    mMkRm_letter_bit |= mMkRm_LETTER_BIT_SET_SERIES_COMPLETE;
                    set_series_complete = TRUE;
                }
            }
        }
    }

    return set_series_complete;
}

static int mMkRm_EvaluateThemeSeriesComplete(int* points, int* complete_theme, mActor_name_t* theme_recommendation_item,
                                             u8* series_name, int wall_num, int floor_num) {
    int i;

    for (i = 0; i < mMkRm_SERIES_NUM; i++) {
        int type = mMkRm_series_info[i].type;

        if (type == mMkRm_SERIES_TYPE_THEME) {
            int ftr_in_theme = mMkRm_series_info[i].num_ftr;

            if (ftr_in_theme != 0) {
                u32 perfect_bit;
                int j;
                u32 complete_bit = mMkRm_search_table[i];
                int wall_floor_idx = mMkRm_series_info[i].wall_floor_idx;
#ifndef IMPROVEMENTS
                perfect_bit = 0;

                for (j = 0; j < ftr_in_theme; j++) {
                    perfect_bit |= (1 << j);
                }
#else
                perfect_bit = (1 << ftr_in_theme) - 1;
#endif

                if (complete_bit == perfect_bit) {
                    mMkRm_GetSeriesName(series_name, i);

                    if (wall_num == wall_floor_idx && floor_num == wall_floor_idx) {
                        points[0] += ftr_in_theme * mMkRm_THEME_SERIES_COMPLETE_FTR_BONUS +
                                     mMkRm_THEME_SERIES_COMPLETE_BONUS_WALL_AND_FLOOR;
                        complete_theme[0] = i;
                        mMkRm_letter_bit |= mMkRm_LETTER_BIT_THEME_SERIES_COMPLETE;

                        return TRUE;
                    }

                    if (wall_num == wall_floor_idx && floor_num != wall_floor_idx) {
                        mMkRm_letter_bit |= mMkRm_LETTER_BIT_SERIES_ALMOST_COMPLETE;
/* @BUG - devs used the wrong item category for the recommended item here */
#ifndef BUGFIXES
                        theme_recommendation_item[0] = ITM_CARPET_START + floor_num;
#else
                        theme_recommendation_item[0] = ITM_WALL_START + floor_num;
#endif
                    } else if (wall_num != wall_floor_idx && floor_num == wall_floor_idx) {
                        mMkRm_letter_bit |= mMkRm_LETTER_BIT_SERIES_ALMOST_COMPLETE;
/* @BUG - devs used the wrong item category for the recommended item here */
#ifndef BUGFIXES
                        theme_recommendation_item[0] = ITM_WALL_START + wall_num;
#else
                        theme_recommendation_item[0] = ITM_CARPET_START + wall_num;
#endif
                    }
                } else {
                    int have_ftr = 0;
                    int not_have_ftr_idx = 0;

                    for (j = 0; j < ftr_in_theme; j++) {
                        if (((complete_bit >> j) & 1) != 0) {
                            have_ftr++;
                        }

                        if (((complete_bit >> j) & 1) == 0) {
                            not_have_ftr_idx = j;
                        }
                    }

                    if (ftr_in_theme == have_ftr + 1) {
                        if (wall_num == wall_floor_idx && floor_num == wall_floor_idx) {
                            theme_recommendation_item[0] = mMkRm_GetRemainOneFtr(not_have_ftr_idx, i);
                            mMkRm_letter_bit |= mMkRm_LETTER_BIT_SERIES_ALMOST_COMPLETE;
                        }
                    } else if (have_ftr >= 6) {
                        mMkRm_letter_bit |= mMkRm_LETTER_BIT_SERIES_STARTED;
                    }
                }
            }
        }
    }

    for (i = 0; i < mMkRm_SERIES_NUM; i++) {
        int type = mMkRm_series_info[i].type;

        if (type == mMkRm_SERIES_TYPE_THEME && mMkRm_series_info[i].num_ftr != 0 &&
            wall_num == mMkRm_series_info[i].wall_floor_idx && floor_num == mMkRm_series_info[i].wall_floor_idx) {
            points[0] += mMkRm_THEME_SERIES_COMPLETE_BONUS_WALL_OR_FLOOR;
            mMkRm_letter_bit |= mMkRm_LETTER_BIT_THEME_SERIES_WALL_AND_FLOOR_MATCH;
            return FALSE;
        }
    }

    return FALSE;
}

static int mMkRm_EvaluateBaseSeriesComplete(int* points, mActor_name_t* base_recommendation, int wall_num,
                                            int floor_num) {
    int series;

    for (series = 0; series < mMkRm_SERIES_NUM; series++) {
        int type = mMkRm_series_info[series].type;
        if (type == mMkRm_SERIES_TYPE_BASE) {
            int ftr_in_base = mMkRm_series_info[series].num_ftr;

            if (mMkRm_series_info[series].num_ftr != 0) {
                if ((mMkRm_search_table[series] & 0x3FF) == 0x3FF) {
                    int wall_floor_idx = mMkRm_series_info[series].wall_floor_idx;

                    points[0] += mMkRm_BASE_SERIES_COMPLETE_FTR_BONUS;
                    mMkRm_letter_bit |= mMkRm_LETTER_BIT_BASE_SERIES_FTR_COMPLETE;

                    if (wall_num == wall_floor_idx && floor_num == wall_floor_idx) {
                        points[0] += mMkRm_BASE_SERIES_MATCHING_WALL_AND_FLOOR_BONUS;
                        mMkRm_letter_bit |= mMkRm_LETTER_BIT_BASE_SERIES_MATCHING_WALL_AND_FLOOR;
                    } else if (wall_num == wall_floor_idx) {
                        points[0] += mMkRm_BASE_SERIES_MATCHING_WALL_OR_FLOOR_BONUS;
                        base_recommendation[0] = ITM_CARPET_START + wall_floor_idx;
                        mMkRm_letter_bit |= mMkRm_LETTER_BIT_BASE_SERIES_WALL_OR_FLOOR_MATCH;
                    } else if (floor_num == wall_floor_idx) {
                        points[0] += mMkRm_BASE_SERIES_MATCHING_WALL_OR_FLOOR_BONUS;
                        base_recommendation[0] = ITM_WALL_START + wall_floor_idx;
                        mMkRm_letter_bit |= mMkRm_LETTER_BIT_BASE_SERIES_WALL_OR_FLOOR_MATCH;
                    }

                    return TRUE;
                } else {
                    u32 complete_bit = mMkRm_search_table[series];
                    int j;
                    int have_ftr = 0;
                    int not_have_ftr_idx = 0;

                    for (j = 0; j < ftr_in_base; j++) {
                        if (((complete_bit >> j) & 1) != 0) {
                            have_ftr++;
                        }

                        if (((complete_bit >> j) & 1) == 0) {
                            not_have_ftr_idx = j;
                        }
                    }

                    if (ftr_in_base == have_ftr + 1) {
                        base_recommendation[0] = mMkRm_GetRemainOneFtr(not_have_ftr_idx, series);
                        mMkRm_letter_bit |= mMkRm_LETTER_BIT_BASE_SERIES_FTR_ALMOST_COMPLETE;
                        return FALSE;
                    } else if (have_ftr >= 6) {
                        mMkRm_letter_bit |= mMkRm_LETTER_BIT_SERIES_STARTED;
                        return FALSE;
                    }
                }
            }
        }
    }

    return FALSE;
}

static void mMkRm_EvaluateNessBounos(int* points) {
    const int mMkRm_NECESSITIES_PERFECT_BIT = (1 << (mMkRm_NECESSITY_NUM - 1)) - 1;
    u32 total_necessities = 0;
    int series;

    for (series = 0; series < mMkRm_SERIES_NUM; series++) {
        int type = mMkRm_series_info[series].type;

        if (type == mMkRm_SERIES_TYPE_BASE) {
            u32 series_ftr = mMkRm_search_table[series];

            total_necessities |= series_ftr;
            if ((series_ftr & mMkRm_NECESSITIES_PERFECT_BIT) == mMkRm_NECESSITIES_PERFECT_BIT) {
                points[0] += mMkRm_NECESSITY_COMPLETE_SAME_SERIES_BONUS;
                mMkRm_letter_bit |= mMkRm_LETTER_BIT_NECESSITIES_COMPLETE_SAME_SERIES;

                return;
            }
        }
    }

    if ((total_necessities & mMkRm_NECESSITIES_PERFECT_BIT) == mMkRm_NECESSITIES_PERFECT_BIT) {
        points[0] += mMkRm_NECESSITY_COMPLETE_DIFF_SERIES_BONUS;
        mMkRm_letter_bit |= mMkRm_LETTER_BIT_NECESSITIES_COMPLETE;
    }
}

static void mMkRm_EvaluateBasePoint(int* points, mActor_name_t** layer_ut_info, int ut_max, int wall_num,
                                    int floor_num) {
    int birth_type_occur_tbl[mRmTp_BIRTH_TYPE_NUM];
    int birth_points_tbl[mRmTp_BIRTH_TYPE_NUM];
    int layer;
    int i;
    int ut_x;
    int ut_z;
    int base_points = 0;

    for (i = 0; i < mRmTp_BIRTH_TYPE_NUM; i++) {
        birth_type_occur_tbl[i] = 0;
        birth_points_tbl[i] = 0;
    }

    for (layer = mCoBG_LAYER0; layer < mCoBG_LAYER2; layer++) {
        mActor_name_t* ut_info = layer_ut_info[layer];

        if (ut_info != NULL) {
            for (ut_z = 1; ut_z < ut_max; ut_z++) {
                for (ut_x = 1; ut_x < ut_max; ut_x++) {
                    mActor_name_t item = ut_info[(ut_z * UT_Z_NUM) + ut_x];

                    if (ITEM_IS_FTR(item)) {
                        int ftr_idx = mNT_ftr_item_no_to_ftr_idx(item);

                        birth_type_occur_tbl[mMkRm_ftr_info[ftr_idx].birth_type]++;
                    }
                }
            }
        }
    }

    for (i = 0; i < mRmTp_BIRTH_TYPE_NUM; i++) {
        birth_points_tbl[i] = birth_type_occur_tbl[i] * mMkRm_birth_point_table[i];
        base_points += birth_points_tbl[i];
    }

    if (FLOOR_IS_MY_ORIG(floor_num)) {
        base_points += mMkRm_birth_point_table[mRmTp_BIRTH_TYPE_MY_ORIGINAL];
    } else {
        base_points += mMkRm_birth_point_table[mMkRm_floor_from[floor_num]];
    }

    if (WALL_IS_MY_ORIG(wall_num)) {
        base_points += mMkRm_birth_point_table[mRmTp_BIRTH_TYPE_MY_ORIGINAL];
    } else {
        base_points += mMkRm_birth_point_table[mMkRm_wall_from[wall_num]];
    }

    points[0] += base_points;
}

static void mMkRm_InitSearchTable() {
    u32* search_table_p = mMkRm_search_table;
    int series;

    for (series = 0; series < mMkRm_SERIES_NUM; series++, search_table_p++) {
        search_table_p[0] = 0;
    }
}

static void mMkRm_AssignIdxInGroup_BaseSeries(int series) {
    int i;
    int group_idx = mMkRm_NOT_NECESSITY;
    int num_ftr = 0;

    for (i = 0; i < FTR_NUM; i++) {
        if (series == mMkRm_ftr_info[i].series) {
            if (mMkRm_ftr_info[i].group_idx >= mMkRm_NOT_NECESSITY) {
                mMkRm_ftr_info[i].group_idx = group_idx;
                group_idx++;
            }

            num_ftr++;
        }
    }

    mMkRm_series_info[series].num_ftr = num_ftr;
}

static void mMkRm_AssignIdxInGroup_ThemeSeries(int series) {
    int i;
    int group_idx = 0;
    int num_ftr = 0;

    for (i = 0; i < FTR_NUM; i++) {
        if (series == mMkRm_ftr_info[i].series) {
            mMkRm_ftr_info[i].group_idx = group_idx;
            group_idx++;
            num_ftr++;
        }
    }

    mMkRm_series_info[series].num_ftr = num_ftr;
}

static void mMkRm_AssignIdxInGroup_SetSeries(int series) {
    int i;
    int group_idx = 0;
    int num_ftr = 0;

    for (i = 0; i < FTR_NUM; i++) {
        if (series == mMkRm_ftr_info[i].series) {
            mMkRm_ftr_info[i].group_idx = group_idx;
            group_idx++;
            num_ftr++;
        }
    }

    mMkRm_series_info[series].num_ftr = num_ftr;
}

static void mMkRm_AssignIdxInGroup_OneSeries(int series) {
    int i;
    int group_idx = 0;
    int num_ftr = 0;

    for (i = 0; i < FTR_NUM; i++) {
        if (series == mMkRm_ftr_info[i].series) {
            mMkRm_ftr_info[i].group_idx = group_idx;
            group_idx++;
            num_ftr++;
        }
    }

    mMkRm_series_info[series].num_ftr = num_ftr;
}

typedef void (*mMkRm_ASSIGN_FUNC_PROC)(int);

static void mMkRm_AssignIdxInGroup() {
    static mMkRm_ASSIGN_FUNC_PROC assign_func_table[mMkRm_SERIES_TYPE_NUM] = { &mMkRm_AssignIdxInGroup_OneSeries,
                                                                               &mMkRm_AssignIdxInGroup_BaseSeries,
                                                                               &mMkRm_AssignIdxInGroup_ThemeSeries,
                                                                               &mMkRm_AssignIdxInGroup_SetSeries };

    int series;

    for (series = 0; series < mMkRm_SERIES_NUM; series++) {
        int type = mMkRm_series_info[series].type;

        if (type >= 0 && type < mMkRm_SERIES_TYPE_NUM) {
            (*assign_func_table[type])(series);
        }
    }
}

static void mMkRm_MakeFtrTable(mActor_name_t** layer_ut_info, int ut_max) {
    int lucky = 0;
    int layer;
    int ut_x;
    int ut_z;

    for (layer = mCoBG_LAYER0; layer < mCoBG_LAYER2; layer++) {
        mActor_name_t* ut_info = layer_ut_info[layer];

        if (ut_info != NULL) {
            for (ut_z = 1; ut_z < ut_max; ut_z++) {
                for (ut_x = 1; ut_x < ut_max; ut_x++) {
                    mActor_name_t item = ut_info[(ut_z * UT_Z_NUM) + ut_x];

                    if (ITEM_IS_FTR(item)) {
                        int ftr_idx = mNT_ftr_item_no_to_ftr_idx(item);
                        int series = mMkRm_ftr_info[ftr_idx].series;

                        if (series != mMkRm_SERIES_OTHER) {
                            mMkRm_search_table[series] |= (1 << mMkRm_ftr_info[ftr_idx].group_idx);
                        }
                    }
                }
            }
        }
    }
}

static void mMkRm_InitData(mActor_name_t** layer_ut_info, int ut_max) {
    mMkRm_InitSearchTable();
    mMkRm_AssignIdxInGroup();
    mMkRm_MakeFtrTable(layer_ut_info, ut_max);
}

static int mMkRm_MarkRoomOneFloor(mActor_name_t** layer_ut_info, int room_size, int wall_num, int floor_num,
                                  mActor_name_t* base_item_recomendation, mActor_name_t* theme_item_recomendation,
                                  u8* series_name, int mode) {
    int ut_max = mMkRm_unit_max_table[room_size];
    int points = 0;
    int complete_theme_idx = -1;
    int completed_theme = FALSE;

    mRmTp_MakeFtrNoTable(ftr_fg_table1, layer_ut_info[0]); // floor
    mRmTp_MakeFtrNoTable(ftr_fg_table2, layer_ut_info[1]); // second layer
    mMkRm_InitData(layer_ut_info, ut_max);

    if ((mode & mMkRm_EVALUATE_BASE_POINT)) {
        mMkRm_EvaluateBasePoint(&points, layer_ut_info, ut_max, wall_num, floor_num);
    }

    if ((mode & mMkRm_EVALUATE_NECESSITY)) {
        mMkRm_EvaluateNessBounos(&points);
    }

    if ((mode & mMkRm_EVALUATE_BASE_SERIES)) {
        mMkRm_EvaluateBaseSeriesComplete(&points, base_item_recomendation, wall_num, floor_num);
    }

    if ((mode & mMkRm_EVALUATE_THEME_SERIES)) {
        completed_theme = mMkRm_EvaluateThemeSeriesComplete(&points, &complete_theme_idx, theme_item_recomendation,
                                                            series_name, wall_num, floor_num);
    }

    if ((mode & mMkRm_EVALUATE_SET_SERIES)) {
        mMkRm_EvaluateSetSeriesComplete(&points);
    }

    if ((mode & mMkRm_EVALUATE_LUCKY_FTR)) {
        mMkRm_EvaluateLuckyFurniture(&points, layer_ut_info, ut_max);
    }

    if ((mode & mMkRm_EVALUATE_DIRECTION)) {
        mMkRm_EvaluateDirect(&points, layer_ut_info, ut_max, room_size);
    }

    if ((mode & mMkRm_EVALUATE_THEME_SERIES)) {
        mMkRm_EvaluateCompleteObstacle(&points, layer_ut_info, ut_max, completed_theme, complete_theme_idx);
    }

    if ((mode & mMkRm_EVALUATE_LETS_CLEAN)) {
        mMkRm_EvaluateLetsClean(&points, layer_ut_info, ut_max);
    }

    mMkRm_ForbidMinusPoint(&points);

    return points;
}

extern int mMkRm_MarkRoomOvl(int player_no) {
    static u8 series_name[mIN_ITEM_NAME_LEN] = "          ";

    if (player_no < PLAYER_NUM) {
        mActor_name_t* layer_ut_info[2];
        int points;

        int house_no = mHS_get_arrange_idx(player_no) & 3;
        mHm_hs_c* house = Save_GetPointer(homes[house_no]);
        mActor_name_t base_recommendation = EMPTY_NO;
        mActor_name_t theme_recommendation = EMPTY_NO;

        mMkRm_letter_bit = 0;
        layer_ut_info[0] = house->floors[0].layer_main.items[0];
        layer_ut_info[1] = house->floors[0].layer_secondary.items[0];

        points = mMkRm_MarkRoomOneFloor(layer_ut_info, house->size_info.size,
                                        house->floors[mHm_ROOM_MAIN].wall_floor.wallpaper_idx,
                                        house->floors[mHm_ROOM_MAIN].wall_floor.flooring_idx, &base_recommendation,
                                        &theme_recommendation, series_name, mMkRm_FULL_EVALUATION);

        if (house->size_info.size == mHm_HOMESIZE_UPPER) {
            layer_ut_info[0] = house->floors[mHm_ROOM_UPPER].layer_main.items[0];
            layer_ut_info[1] = house->floors[mHm_ROOM_UPPER].layer_secondary.items[0];

            points += mMkRm_MarkRoomOneFloor(
                layer_ut_info, mHm_ROOMTYPE_MEDIUM, house->floors[mHm_ROOM_UPPER].wall_floor.wallpaper_idx,
                house->floors[mHm_ROOM_UPPER].wall_floor.flooring_idx, &base_recommendation, &theme_recommendation,
                series_name, mMkRm_UPPER_EVALUATION);
        }

        mMkRm_SendMarkLetter(house, points, house->size_info.size, series_name, base_recommendation,
                             theme_recommendation);

        return points;
    }

    return 0;
}
