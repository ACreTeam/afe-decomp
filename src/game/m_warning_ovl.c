#include "m_warning_ovl.h"

#include "audio.h"
#include "sys_matrix.h"
#include "m_font.h"

typedef struct warning_ovl_line_s {
  f32 pos_x;
  f32 pos_y;
  u8* str;
  int str_len;
} mWR_line_c;

typedef struct warning_ovl_data_s {
  mWR_line_c* lines;
  int num_lines;
  f32 scale_x;
  f32 scale_y;
} mWR_data_c;

static u8 wr_yes_mes[] = { CHAR_PP_146, CHAR_PP_146, CHAR_PP_096 };

static u8 wr_no_mes[] = { CHAR_PP_216, CHAR_PP_178 };

static u8 wr_mailbox_mes0[] = { CHAR_PP_091, CHAR_PP_198, CHAR_PP_163, CHAR_PP_206, CHAR_PP_176, CHAR_PP_194,
                                CHAR_PP_091, CHAR_PP_018, CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_mailbox_mes1[] = { CHAR_PP_001, CHAR_PP_123, CHAR_PP_020, CHAR_PP_001, CHAR_PP_163,
                                CHAR_PP_206, CHAR_PP_176, CHAR_PP_132, CHAR_PP_012, CHAR_PP_018,
                                CHAR_PP_018, CHAR_PP_091, CHAR_PP_146, CHAR_PP_146, CHAR_PP_063 };

static u8 wr_pr_leave_mes0[] = { CHAR_PP_179, CHAR_PP_161, CHAR_PP_179, CHAR_PP_169, CHAR_PP_231, CHAR_PP_001,
                                 CHAR_PP_204, CHAR_PP_251, CHAR_PP_001, CHAR_PP_241, CHAR_PP_019, CHAR_PP_132 };

static u8 wr_pr_leave_mes1[] = { CHAR_PP_228, CHAR_PP_186, CHAR_PP_214, CHAR_PP_189, CHAR_PP_164,
                                 CHAR_PP_025, CHAR_PP_170, CHAR_PP_213, CHAR_PP_013, CHAR_PP_020,
                                 CHAR_PP_001, CHAR_PP_096, CHAR_PP_033 };

static u8 wr_money_mes0[] = { CHAR_PP_057, CHAR_PP_057, CHAR_PP_057, CHAR_PP_057, CHAR_PP_057, CHAR_PP_224,
                              CHAR_PP_185, CHAR_PP_030, CHAR_PP_244, CHAR_PP_011, CHAR_PP_005, CHAR_PP_132 };

static u8 wr_money_mes1[] = { CHAR_PP_091, CHAR_PP_017, CHAR_PP_154, CHAR_PP_164, CHAR_PP_231, CHAR_PP_244,
                              CHAR_PP_006, CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_food_mes[] = { CHAR_PP_007, CHAR_PP_010, CHAR_PP_204, CHAR_PP_016, CHAR_PP_201,
                            CHAR_PP_002, CHAR_PP_179, CHAR_PP_169, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_send_mes[] = { CHAR_PP_150, CHAR_PP_223, CHAR_PP_093, CHAR_PP_146, CHAR_PP_151,
                            CHAR_PP_179, CHAR_PP_169, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_quest_mes[] = { CHAR_PP_015, CHAR_PP_021, CHAR_PP_195, CHAR_PP_024,
                             CHAR_PP_179, CHAR_PP_169, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_furniture_mes[] = { CHAR_PP_014, CHAR_PP_195, CHAR_PP_020, CHAR_PP_179,
                                 CHAR_PP_169, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_present_mes[] = { CHAR_PP_228, CHAR_PP_186, CHAR_PP_214, CHAR_PP_189, CHAR_PP_164, CHAR_PP_244,
                               CHAR_PP_006, CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_putin_mes[] = {
    CHAR_PP_011, CHAR_PP_030, CHAR_PP_003, CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033
};

static u8 wr_sell_mes[] = { CHAR_PP_002, CHAR_PP_126, CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_put_max_furniture_mes0[] = { CHAR_PP_154, CHAR_PP_186, CHAR_PP_001, CHAR_PP_237, CHAR_PP_203,
                                          CHAR_PP_002, CHAR_PP_132, CHAR_PP_004, CHAR_PP_007, CHAR_PP_019 };

static u8 wr_put_max_furniture_mes1[] = { CHAR_PP_181, CHAR_PP_150, CHAR_PP_231, CHAR_PP_022, CHAR_PP_008,
                                          CHAR_PP_016, CHAR_PP_201, CHAR_PP_002, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_put_furniture_mes0[] = { CHAR_PP_091, CHAR_PP_198, CHAR_PP_009, CHAR_PP_024, CHAR_PP_029, CHAR_PP_002,
                                      CHAR_PP_009, CHAR_PP_002, CHAR_PP_021, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_put_furniture_mes1[] = { CHAR_PP_004, CHAR_PP_007, CHAR_PP_009, CHAR_PP_019, CHAR_PP_231, CHAR_PP_244,
                                      CHAR_PP_006, CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_put_item_mes0[] = { CHAR_PP_091, CHAR_PP_198, CHAR_PP_009, CHAR_PP_024, CHAR_PP_000,
                                 CHAR_PP_015, CHAR_PP_124, CHAR_PP_021, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_put_item_mes1[] = { CHAR_PP_179, CHAR_PP_169, CHAR_PP_231, CHAR_PP_004, CHAR_PP_008,
                                 CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_put_plant_mes0[] = { CHAR_PP_009, CHAR_PP_024, CHAR_PP_246, CHAR_PP_011,
                                  CHAR_PP_203, CHAR_PP_021, CHAR_PP_025 };

static u8 wr_put_plant_mes1[] = { CHAR_PP_002, CHAR_PP_003, CHAR_PP_123, CHAR_PP_126,
                                  CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_hukubukuro_open_mes0[] = { CHAR_PP_051, CHAR_PP_017, CHAR_PP_001, CHAR_PP_237, CHAR_PP_203,
                                        CHAR_PP_002, CHAR_PP_145, CHAR_PP_151, CHAR_PP_231, CHAR_PP_020,
                                        CHAR_PP_001, CHAR_PP_019, CHAR_PP_132 };

static u8 wr_hukubukuro_open_mes1[] = { CHAR_PP_027, CHAR_PP_007, CHAR_PP_248, CHAR_PP_007, CHAR_PP_192,
                                        CHAR_PP_025, CHAR_PP_145, CHAR_PP_153, CHAR_PP_126, CHAR_PP_020,
                                        CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_present_mail_mes0[] = { CHAR_PP_228, CHAR_PP_186, CHAR_PP_214, CHAR_PP_189, CHAR_PP_164, CHAR_PP_225,
                                     CHAR_PP_143, CHAR_PP_152, CHAR_PP_157, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_present_mail_mes1[] = { CHAR_PP_163, CHAR_PP_206, CHAR_PP_176, CHAR_PP_021, CHAR_PP_017, CHAR_PP_008,
                                     CHAR_PP_123, CHAR_PP_126, CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_write_mes0[] = { CHAR_PP_163, CHAR_PP_206, CHAR_PP_176, CHAR_PP_231, CHAR_PP_001, CHAR_PP_204,
                              CHAR_PP_251, CHAR_PP_001, CHAR_PP_241, CHAR_PP_019, CHAR_PP_132 };

static u8 wr_write_mes1[] = { CHAR_PP_005, CHAR_PP_007, CHAR_PP_154, CHAR_PP_164, CHAR_PP_231, CHAR_PP_244,
                              CHAR_PP_006, CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_lock_diary_mes0[] = { CHAR_PP_009, CHAR_PP_024, CHAR_PP_021, CHAR_PP_204,
                                   CHAR_PP_006, CHAR_PP_021, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_lock_diary_mes1[] = { CHAR_PP_150, CHAR_PP_207, CHAR_PP_231, CHAR_PP_005, CHAR_PP_005, CHAR_PP_204,
                                   CHAR_PP_018, CHAR_PP_001, CHAR_PP_125, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_music_mes0[] = { CHAR_PP_179, CHAR_PP_161, CHAR_PP_179, CHAR_PP_169, CHAR_PP_231, CHAR_PP_001,
                              CHAR_PP_204, CHAR_PP_251, CHAR_PP_001, CHAR_PP_241, CHAR_PP_019, CHAR_PP_132 };

static u8 wr_music_mes1[] = { CHAR_PP_019, CHAR_PP_124, CHAR_PP_241, CHAR_PP_013,
                              CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_music2_mes0[] = { CHAR_PP_009, CHAR_PP_024, CHAR_PP_176, CHAR_PP_141, CHAR_PP_144,
                               CHAR_PP_212, CHAR_PP_143, CHAR_PP_152, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_music2_mes1[] = { CHAR_PP_091, CHAR_PP_198, CHAR_PP_025, CHAR_PP_001, CHAR_PP_204,
                               CHAR_PP_018, CHAR_PP_125, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_original_mes0[] = { CHAR_PP_179, CHAR_PP_161, CHAR_PP_179, CHAR_PP_169, CHAR_PP_231, CHAR_PP_001,
                                 CHAR_PP_204, CHAR_PP_251, CHAR_PP_001, CHAR_PP_241, CHAR_PP_019, CHAR_PP_132 };

static u8 wr_original_mes1[] = { CHAR_PP_175, CHAR_PP_146, CHAR_PP_219, CHAR_PP_211,
                                 CHAR_PP_146, CHAR_PP_189, CHAR_PP_019 };

static u8 wr_original_mes2[] = { CHAR_PP_001, CHAR_PP_126, CHAR_PP_005, CHAR_PP_003, CHAR_PP_125,
                                 CHAR_PP_009, CHAR_PP_019, CHAR_PP_231, CHAR_PP_244, CHAR_PP_006,
                                 CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_put_sign_mes1[] = { CHAR_PP_015, CHAR_PP_018, CHAR_PP_123, CHAR_PP_126,
                                 CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_put_sign_other_mes0[] = { CHAR_PP_029, CHAR_PP_005, CHAR_PP_024, CHAR_PP_035,
                                       CHAR_PP_123, CHAR_PP_021, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_put_sign_island_mes0[] = { CHAR_PP_011, CHAR_PP_030, CHAR_PP_021, CHAR_PP_025, CHAR_PP_132,
                                        CHAR_PP_015, CHAR_PP_018, CHAR_PP_123, CHAR_PP_126, CHAR_PP_020,
                                        CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_card_mes0[] = { CHAR_PP_015, CHAR_PP_001, CHAR_PP_014, CHAR_PP_002, CHAR_PP_150,
                             CHAR_PP_144, CHAR_PP_220, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_put_fami_mes0[] = { CHAR_PP_011, CHAR_PP_030, CHAR_PP_021, CHAR_PP_025, CHAR_PP_009,
                                 CHAR_PP_024, CHAR_PP_172, CHAR_PP_135, CHAR_PP_176, CHAR_PP_154,
                                 CHAR_PP_189, CHAR_PP_025, CHAR_PP_132 };

static u8 wr_put_fami_mes1[] = { CHAR_PP_004, CHAR_PP_007, CHAR_PP_009, CHAR_PP_019, CHAR_PP_231, CHAR_PP_244,
                                 CHAR_PP_006, CHAR_PP_020, CHAR_PP_001, CHAR_PP_142, CHAR_PP_033 };

static u8 wr_You_dont_have_room[] = { CHAR_PP_089, CHAR_PP_111, CHAR_PP_117, CHAR_PP_032, CHAR_PP_100,
                                      CHAR_PP_111, CHAR_PP_110, CHAR_PP_039, CHAR_PP_116, CHAR_PP_032,
                                      CHAR_PP_104, CHAR_PP_097, CHAR_PP_118, CHAR_PP_101, CHAR_PP_032,
                                      CHAR_PP_114, CHAR_PP_111, CHAR_PP_111, CHAR_PP_109 };

static u8 wr_to_write_any_more[] = { CHAR_PP_116, CHAR_PP_111, CHAR_PP_032, CHAR_PP_119, CHAR_PP_114, CHAR_PP_105,
                                     CHAR_PP_116, CHAR_PP_101, CHAR_PP_032, CHAR_PP_097, CHAR_PP_110, CHAR_PP_121,
                                     CHAR_PP_032, CHAR_PP_109, CHAR_PP_111, CHAR_PP_114, CHAR_PP_101, CHAR_PP_046 };

static u8 wr_You_entered_letters[] = { CHAR_PP_089, CHAR_PP_111, CHAR_PP_117, CHAR_PP_032, CHAR_PP_101,
                                       CHAR_PP_110, CHAR_PP_116, CHAR_PP_101, CHAR_PP_114, CHAR_PP_101,
                                       CHAR_PP_100, CHAR_PP_032, CHAR_PP_108, CHAR_PP_101, CHAR_PP_116,
                                       CHAR_PP_116, CHAR_PP_101, CHAR_PP_114, CHAR_PP_115 };

static u8 wr_that_have_nothing_to_do[] = { CHAR_PP_116, CHAR_PP_104, CHAR_PP_097, CHAR_PP_116, CHAR_PP_032, CHAR_PP_104,
                                           CHAR_PP_097, CHAR_PP_118, CHAR_PP_101, CHAR_PP_032, CHAR_PP_110, CHAR_PP_111,
                                           CHAR_PP_116, CHAR_PP_104, CHAR_PP_105, CHAR_PP_110, CHAR_PP_103, CHAR_PP_032,
                                           CHAR_PP_116, CHAR_PP_111, CHAR_PP_032, CHAR_PP_100, CHAR_PP_111 };

static u8 wr_with_secret_codes[] = { CHAR_PP_119, CHAR_PP_105, CHAR_PP_116, CHAR_PP_104, CHAR_PP_032, CHAR_PP_115,
                                     CHAR_PP_101, CHAR_PP_099, CHAR_PP_114, CHAR_PP_101, CHAR_PP_116, CHAR_PP_032,
                                     CHAR_PP_099, CHAR_PP_111, CHAR_PP_100, CHAR_PP_101, CHAR_PP_115, CHAR_PP_033 };

static u8 wr_pr_fork_mes[] = { CHAR_PP_009, CHAR_PP_024, CHAR_PP_145, CHAR_PP_146,
                               CHAR_PP_163, CHAR_PP_177, CHAR_PP_025, CHAR_PP_132 };

static mWR_line_c wr_mailbox_line[] = {
    { 44.0f, 27.0f, wr_mailbox_mes0, sizeof(wr_mailbox_mes0) },
    { 29.0f, 7.0f, wr_mailbox_mes1, sizeof(wr_mailbox_mes1) },
    { 63.0f, 7.0f, wr_yes_mes, sizeof(wr_yes_mes) },
    { 150.0f, -16.0f, wr_no_mes, sizeof(wr_no_mes) },
};

static mWR_line_c wr_pre_leave_line[] = {
    { 36.0f, 32.0f, wr_pr_leave_mes0, sizeof(wr_pr_leave_mes0) },
    { 30.0f, 8.0f, wr_pr_leave_mes1, sizeof(wr_pr_leave_mes1) },
};

static mWR_line_c wr_money_line[] = {
    { 32.0f, 30.0f, wr_money_mes0, sizeof(wr_money_mes0) },
    { 36.0f, 8.0f, wr_money_mes1, sizeof(wr_money_mes1) },
};

static mWR_line_c wr_pr_food_line[] = {
    { 48.0f, 27.0f, wr_send_mes, sizeof(wr_send_mes) },
    { 33.0f, 8.0f, wr_present_mes, sizeof(wr_present_mes) },
};

static mWR_line_c wr_pr_quest_line[] = {
    { 49.0f, 26.0f, wr_quest_mes, sizeof(wr_quest_mes) },
    { 34.0f, 8.0f, wr_present_mes, sizeof(wr_present_mes) },
};

static mWR_line_c wr_put_max_furniture_line[] = {
    { 37.0f, 27.0f, wr_put_max_furniture_mes0, sizeof(wr_put_max_furniture_mes0) },
    { 37.0f, 8.0f, wr_put_max_furniture_mes1, sizeof(wr_put_max_furniture_mes1) },
};

static mWR_line_c wr_put_furniture_line[] = {
    { 36.0f, 30.0f, wr_put_furniture_mes0, sizeof(wr_put_furniture_mes0) },
    { 36.0f, 8.0f, wr_put_furniture_mes1, sizeof(wr_put_furniture_mes1) },
};

static mWR_line_c wr_put_item_line[] = {
    { 35.0f, 25.0f, wr_put_item_mes0, sizeof(wr_put_item_mes0) },
    { 35.0f, 8.0f, wr_put_item_mes1, sizeof(wr_put_item_mes1) },
};

static mWR_line_c wr_put_plant_line[] = {
    { 44.0f, 25.0f, wr_put_plant_mes0, sizeof(wr_put_plant_mes0) },
    { 44.0f, 8.0f, wr_put_plant_mes1, sizeof(wr_put_plant_mes1) },
};

static mWR_line_c wr_hukubukuro_open_line[] = {
    { 27.0f, 32.0f, wr_hukubukuro_open_mes0, sizeof(wr_hukubukuro_open_mes0) },
    { 27.0f, 8.0f, wr_hukubukuro_open_mes1, sizeof(wr_hukubukuro_open_mes1) },
};

static mWR_line_c wr_present_mail_line[] = {
    { 36.0f, 29.0f, wr_present_mail_mes0, sizeof(wr_present_mail_mes0) },
    { 28.0f, 8.0f, wr_present_mail_mes1, sizeof(wr_present_mail_mes1) },
};

static mWR_line_c wr_write_line[] = {
    { 38.0f, 30.0f, wr_write_mes0, sizeof(wr_write_mes0) },
    { 38.0f, 8.0f, wr_write_mes1, sizeof(wr_write_mes1) },
};

static mWR_line_c wr_music_line[] = {
    { 28.0f, 30.0f, wr_music_mes0, sizeof(wr_music_mes0) },
    { 51.0f, 8.0f, wr_music_mes1, sizeof(wr_music_mes1) },
};

static mWR_line_c wr_music2_line[] = {
    { 39.0f, 30.0f, wr_music2_mes0, sizeof(wr_music2_mes0) },
    { 45.0f, 8.0f, wr_music2_mes1, sizeof(wr_music2_mes1) },
};

static mWR_line_c wr_original_line[] = {
    { 43.0f, 36.0f, wr_original_mes0, sizeof(wr_original_mes0) },
    { 73.0f, 8.0f, wr_original_mes1, sizeof(wr_original_mes1) },
    { 33.0f, 8.0f, wr_original_mes2, sizeof(wr_original_mes2) },
};

static mWR_line_c wr_put_sign_line[] = {
    { 44.0f, 25.0f, wr_put_plant_mes0, sizeof(wr_put_plant_mes0) },
    { 44.0f, 8.0f, wr_put_sign_mes1, sizeof(wr_put_sign_mes1) },
};

static mWR_line_c wr_put_sign_other_line[] = {
    { 44.0f, 25.0f, wr_put_sign_other_mes0, sizeof(wr_put_sign_other_mes0) },
    { 44.0f, 8.0f, wr_put_sign_mes1, sizeof(wr_put_sign_mes1) },
};

static mWR_line_c wr_put_sign_island_line[] = {
    { 43.0f, 42.0f, wr_put_sign_island_mes0, sizeof(wr_put_sign_island_mes0) },
};

static mWR_line_c wr_pr_card_line[] = {
    { 48.0f, 27.0f, wr_card_mes0, sizeof(wr_card_mes0) },
    { 32.0f, 8.0f, wr_present_mes, sizeof(wr_present_mes) },
};

static mWR_line_c wr_lock_diary_line[] = {
    { 48.0f, 27.0f, wr_lock_diary_mes0, sizeof(wr_lock_diary_mes0) },
    { 36.0f, 8.0f, wr_lock_diary_mes1, sizeof(wr_lock_diary_mes1) },
};

static mWR_line_c wr_put_fami_line[] = {
    { 32.0f, 34.0f, wr_put_fami_mes0, sizeof(wr_put_fami_mes0) },
    { 40.0f, 8.0f, wr_put_fami_mes1, sizeof(wr_put_fami_mes1) },
};

static mWR_line_c wr_word_over_line[] = {
    { 54.0f, 40.0f, wr_You_dont_have_room, sizeof(wr_You_dont_have_room) },
    { 63.0f, 24.0f, wr_to_write_any_more, sizeof(wr_to_write_any_more) },
};

static mWR_line_c wr_pw_chk_line[] = {
    { 59.0f, 40.0f, wr_You_entered_letters, sizeof(wr_You_entered_letters) },
    { 45.0f, 24.0f, wr_that_have_nothing_to_do, sizeof(wr_that_have_nothing_to_do) },
    { 63.0f, 24.0f, wr_with_secret_codes, sizeof(wr_with_secret_codes) },
};

static mWR_line_c wr_pr_fork_line[] = {
    { 49.0f, 26.0f, wr_pr_fork_mes, sizeof(wr_pr_fork_mes) },
    { 34.0f, 8.0f, wr_present_mes, sizeof(wr_present_mes) },
};

static mWR_data_c wr_win_data[] = {
    { wr_mailbox_line, ARRAY_COUNT(wr_mailbox_line), 1.0f, 1.0f },
    { wr_pre_leave_line, ARRAY_COUNT(wr_pre_leave_line), 0.8700000047683716f, 0.8700000047683716f },
    { wr_money_line, ARRAY_COUNT(wr_money_line), 0.8500000238418579f, 0.8399999737739563f },
    { wr_pr_food_line, ARRAY_COUNT(wr_pr_food_line), 0.800000011920929f, 0.7799999713897705f },
    { wr_pr_quest_line, ARRAY_COUNT(wr_pr_quest_line), 0.7900000214576721f, 0.7599999904632568f },
    { wr_put_max_furniture_line, ARRAY_COUNT(wr_put_max_furniture_line), 0.800000011920929f, 0.7799999713897705f },
    { wr_put_furniture_line, ARRAY_COUNT(wr_put_furniture_line), 0.8500000238418579f, 0.8399999737739563f },
    { wr_put_item_line, ARRAY_COUNT(wr_put_item_line), 0.7699999809265137f, 0.75f },
    { wr_put_plant_line, ARRAY_COUNT(wr_put_plant_line), 0.7699999809265137f, 0.75f },
    { wr_hukubukuro_open_line, ARRAY_COUNT(wr_hukubukuro_open_line), 0.8700000047683716f, 0.8999999761581421f },
    { wr_present_mail_line, ARRAY_COUNT(wr_present_mail_line), 0.8199999928474426f, 0.8199999928474426f },
    { wr_write_line, ARRAY_COUNT(wr_write_line), 0.8500000238418579f, 0.8399999737739563f },
    { wr_music_line, ARRAY_COUNT(wr_music_line), 0.8500000238418579f, 0.8399999737739563f },
    { wr_music2_line, ARRAY_COUNT(wr_music2_line), 0.8500000238418579f, 0.8399999737739563f },
    { wr_original_line, ARRAY_COUNT(wr_original_line), 0.9599999785423279f, 1.149999976158142f },
    { wr_put_sign_line, ARRAY_COUNT(wr_put_sign_line), 0.7699999809265137f, 0.75f },
    { wr_put_sign_other_line, ARRAY_COUNT(wr_put_sign_other_line), 0.7699999809265137f, 0.75f },
    { wr_put_sign_island_line, ARRAY_COUNT(wr_put_sign_island_line), 1.0f, 0.8500000238418579f },
    { wr_pr_card_line, ARRAY_COUNT(wr_pr_card_line), 0.800000011920929f, 0.7799999713897705f },
    { wr_lock_diary_line, ARRAY_COUNT(wr_lock_diary_line), 0.800000011920929f, 0.7799999713897705f },
    { wr_put_fami_line, ARRAY_COUNT(wr_put_fami_line), 0.8999999761581421f, 0.8999999761581421f },
    { wr_word_over_line, ARRAY_COUNT(wr_word_over_line), 1.0f, 1.0f },
    { wr_pw_chk_line, ARRAY_COUNT(wr_pw_chk_line), 1.0f, 1.2000000476837158f },
    { wr_pr_fork_line, ARRAY_COUNT(wr_pr_fork_line), 0.800000011920929f, 0.7799999713897705f },
};

static void mWR_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  static f32 add[mWR_STATE_NUM] = { -0.2f, 0.2f };

  mWR_Ovl_c* ovl = submenu->overlay->warning_ovl;
  f32 new_scale = ovl->scale;

  new_scale += add[ovl->state];
  if (new_scale > 1.0f) {
    menu_info->proc_status = menu_info->next_proc_status;
    new_scale = 1.0f;
  }
  else if (new_scale < 0.0f) {
    menu_info->proc_status = menu_info->next_proc_status;
    new_scale = 0.0f;
  }

  ovl->scale = new_scale;
}

static void mWR_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  u32 trigger = submenu->overlay->menu_control.trigger;
  mWR_Ovl_c* warning_ovl = submenu->overlay->warning_ovl;

  if ((trigger & (BUTTON_A | BUTTON_B | BUTTON_START)) != 0) {
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_END;
    warning_ovl->state = mWR_STATE_OUT;

    if ((trigger & BUTTON_B) != 0) {
      warning_ovl->selected = 1;
    }
    else if (warning_ovl->selected == 0) {
      sAdo_SysTrgStart(0x435);
    }

    if (menu_info->data0 == 0) {
      menu_info->data1 = warning_ovl->selected;
    }
  }
  else if (menu_info->data0 == 0) {
    if ((trigger & BUTTON_CLEFT) != 0) {
      if (warning_ovl->selected == 1) {
        warning_ovl->selected = 0;
        sAdo_SysTrgStart(NA_SE_CURSOL);
      }
    }
    else if ((trigger & BUTTON_CRIGHT) != 0) {
      if (warning_ovl->selected == 0) {
        warning_ovl->selected = 1;
        sAdo_SysTrgStart(NA_SE_CURSOL);
      }
    }
  }
}

static void mWR_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

typedef void (*mWR_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mWR_warning_ovl_move(Submenu* submenu) {
  static mWR_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = {
    &mWR_move_Move,
    &mWR_move_Play,
    (mWR_MOVE_PROC)&none_proc1,
    (mWR_MOVE_PROC)&none_proc1,
    &mWR_move_End
  };

  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_WARNING];

  (*menu_info->pre_move_func)(submenu);
  (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);

  switch (menu_info->proc_status) {
    case mSM_OVL_PROC_PLAY:
      submenu->overlay->menu_control.animation_flag = TRUE;
      break;

    case mSM_OVL_PROC_MOVE:
      submenu->overlay->menu_control.animation_flag = FALSE;
      break;
  }
}

extern Gfx att_win_model[];
extern Gfx att_win_cursor_model[];

static void mWR_set_frame_dl(Submenu* submenu, GRAPH* graph, mSM_MenuInfo_c* menu_info, mWR_data_c* data) {
  Gfx* gfx;
  f32 scale = submenu->overlay->warning_ovl->scale * 16.0f;

  Matrix_scale(scale * data->scale_x, scale * data->scale_y, 1.0f, MTX_LOAD);
  Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);

  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  /* Draw background */
  gDPPipeSync(gfx++);
  gDPSetBlendColor(gfx++, 255, 255, 255, 40);
  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gSPDisplayList(gfx++, att_win_model);
  gDPPipeSync(gfx++);
  gDPSetAlphaCompare(gfx++, G_AC_NONE);
  gDPSetBlendColor(gfx++, 255, 255, 255, 8);

  /* Draw cursor */
  if (menu_info->data0 == 0) {
    f32 x;
    f32 y;

    f32 line_y = data->lines[2].pos_y + (data->lines[0].pos_y + data->lines[1].pos_y);
    x = (menu_info->position[0] - 120.0f) - 5.0f;
    y = ((60.0f + menu_info->position[1]) - (32.0f + line_y)) - 8.0f;
    if (submenu->overlay->warning_ovl->selected == 0) {
        x += data->lines[2].pos_x;
    } else {
        x += data->lines[3].pos_x;
    }

    Matrix_scale(scale, scale, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, -32.0f, MTX_MULT);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, att_win_cursor_model);
  }

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);
}

static void mWR_set_strings(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info, mWR_data_c* data) {
  static int col_type0[3] = { 255, 255,   0 }; // base color
  static int col_type1[3] = { 255, 175, 175 }; // selected choice color
  static int col_type2[3] = { 255, 255, 255 }; // unselected choice color

  mWR_Ovl_c* warning_ovl = submenu->overlay->warning_ovl;
  int selected_idx = 2 + warning_ovl->selected;
  f32 scale = warning_ovl->scale;
  f32 x;
  f32 y;
  f32 line_x;
  int i;
  mWR_line_c* line;
  int* color;
  
  (*submenu->overlay->set_char_matrix_proc)(game->graph);

  line = data->lines;
  x = (160.0f + menu_info->position[0]) - scale * 120.0f * data->scale_x;
  y = (120.0f - menu_info->position[1]) - scale * 60.0f * data->scale_y;

  for (i = 0; i < data->num_lines; i++, line++) {
      if (i == selected_idx) {
          color = col_type1;
      } else if (i >= 2 && menu_info->data0 == 0) {
          color = col_type2;
      } else {
          color = col_type0;
      }

      line_x = line->pos_x * scale;
      y += line->pos_y * scale;

      mFont_SetLineStrings(game, line->str, line->str_len, x + line_x, y, color[0], color[1], color[2], 255, FALSE,
                           FALSE, scale, scale, mFont_MODE_POLY);

      y += scale * 16.0f;
  }
}

static void mWR_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
  int str_no = menu_info->data0;

  mWR_set_frame_dl(submenu, game->graph, menu_info, &wr_win_data[str_no]);
  mWR_set_strings(submenu, game, menu_info, &wr_win_data[str_no]);
}

static void mWR_warning_ovl_draw(Submenu* submenu, GAME* game) {
  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_WARNING];

  (*menu_info->pre_draw_func)(submenu, game);
  mWR_set_dl(submenu, game, menu_info);
}

extern void mWR_warning_ovl_set_proc(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  overlay->menu_control.menu_move_func = &mWR_warning_ovl_move;
  overlay->menu_control.menu_draw_func = &mWR_warning_ovl_draw;
}

extern void mWR_warning_ovl_init(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;
  mWR_Ovl_c* warning_ovl = overlay->warning_ovl;

  overlay->menu_control.animation_flag = FALSE;
  overlay->menu_info[mSM_OVL_WARNING].proc_status = mSM_OVL_PROC_MOVE;
  overlay->menu_info[mSM_OVL_WARNING].next_proc_status = mSM_OVL_PROC_PLAY;
  warning_ovl->selected = 1;
  warning_ovl->scale = 0.0f;
  warning_ovl->state = mWR_STATE_IN;
}

static mWR_Ovl_c wr_ovl_data;

extern void mWR_warning_ovl_construct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  if (overlay->warning_ovl == NULL) {
    mem_clear((u8*)&wr_ovl_data, sizeof(mWR_Ovl_c), 0);
    overlay->warning_ovl = &wr_ovl_data;
  }

  mWR_warning_ovl_init(submenu);
  mWR_warning_ovl_set_proc(submenu);
}

extern void mWR_warning_ovl_destruct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  overlay->warning_ovl = NULL;
}
