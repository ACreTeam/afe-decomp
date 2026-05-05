#ifndef M_FONT_H
#define M_FONT_H

#include "types.h"
#include "m_lib.h"
#include "graph.h"
#include "game.h"
#include "libforest/gbi_extensions.h"
#include "charmap.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mFont_MARKTYPE_VERT_ARROW 0
#define mFont_MARKTYPE_HORI_ARROW 1
#define mFont_MARKTYPE_CURSOR 2
#define mFont_MARKTYPE_NEXT 3
#define mFont_MARKTYPE_CHOICE 4
#define mFont_MARKTYPE_TOTAL 5

#define mFont_MODE_POLY 0
#define mFont_MODE_FONT 1

enum {
  mFont_CONT_CODE_BEGIN = 0,
  mFont_CONT_CODE_LAST = mFont_CONT_CODE_BEGIN,
  mFont_CONT_CODE_CONTINUE,
  mFont_CONT_CODE_CLEAR,
  mFont_CONT_CODE_CURSOR_SET_TIME,
  mFont_CONT_CODE_BUTTON,
  mFont_CONT_CODE_COLOR,
  mFont_CONT_CODE_ABLE_CANCEL,
  mFont_CONT_CODE_UNABLE_CANCEL,
  mFont_CONT_CODE_SET_DEMO_ORDER_PLAYER,
  mFont_CONT_CODE_SET_DEMO_ORDER_NPC0,
  mFont_CONT_CODE_SET_DEMO_ORDER_NPC1,
  mFont_CONT_CODE_SET_DEMO_ORDER_NPC2,
  mFont_CONT_CODE_SET_DEMO_ORDER_QUEST,
  mFont_CONT_CODE_SET_SELECT_WINDOW,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_F,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_0,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_1,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_2,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_3,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_2,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_3,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_4,
  mFont_CONT_CODE_SET_SELECT_STRING_2,
  mFont_CONT_CODE_SET_SELECT_STRING_3,
  mFont_CONT_CODE_SET_SELECT_STRING_4,
  mFont_CONT_CODE_SET_FORCE_NEXT,
  mFont_CONT_CODE_PUT_STRING_PLAYER_NAME,
  mFont_CONT_CODE_PUT_STRING_TALK_NAME,
  mFont_CONT_CODE_PUT_STRING_TAIL,
  mFont_CONT_CODE_PUT_STRING_YEAR,
  mFont_CONT_CODE_PUT_STRING_MONTH,
  mFont_CONT_CODE_PUT_STRING_WEEK,
  mFont_CONT_CODE_PUT_STRING_DAY,
  mFont_CONT_CODE_PUT_STRING_HOUR,
  mFont_CONT_CODE_PUT_STRING_MIN,
  mFont_CONT_CODE_PUT_STRING_SEC,
  mFont_CONT_CODE_PUT_STRING_FREE0,
  mFont_CONT_CODE_PUT_STRING_FREE1,
  mFont_CONT_CODE_PUT_STRING_FREE2,
  mFont_CONT_CODE_PUT_STRING_FREE3,
  mFont_CONT_CODE_PUT_STRING_FREE4,
  mFont_CONT_CODE_PUT_STRING_FREE5,
  mFont_CONT_CODE_PUT_STRING_FREE6,
  mFont_CONT_CODE_PUT_STRING_FREE7,
  mFont_CONT_CODE_PUT_STRING_FREE8,
  mFont_CONT_CODE_PUT_STRING_FREE9,
  mFont_CONT_CODE_PUT_STRING_DETERMINATION,
  mFont_CONT_CODE_PUT_STRING_COUNTRY_NAME,
  mFont_CONT_CODE_PUT_STRING_RANDOM_NUMBER_2,
  mFont_CONT_CODE_PUT_STRING_ITEM0,
  mFont_CONT_CODE_PUT_STRING_ITEM1,
  mFont_CONT_CODE_PUT_STRING_ITEM2,
  mFont_CONT_CODE_PUT_STRING_ITEM3,
  mFont_CONT_CODE_PUT_STRING_ITEM4,
  mFont_CONT_CODE_PUT_STRING_FREE10,
  mFont_CONT_CODE_PUT_STRING_FREE11,
  mFont_CONT_CODE_PUT_STRING_FREE12,
  mFont_CONT_CODE_PUT_STRING_FREE13,
  mFont_CONT_CODE_PUT_STRING_FREE14,
  mFont_CONT_CODE_PUT_STRING_FREE15,
  mFont_CONT_CODE_PUT_STRING_FREE16,
  mFont_CONT_CODE_PUT_STRING_FREE17,
  mFont_CONT_CODE_PUT_STRING_FREE18,
  mFont_CONT_CODE_PUT_STRING_FREE19,
  mFont_CONT_CODE_PUT_STRING_MAIL,
  mFont_CONT_CODE_SET_PLAYER_DESTINY0,
  mFont_CONT_CODE_SET_PLAYER_DESTINY1,
  mFont_CONT_CODE_SET_PLAYER_DESTINY2,
  mFont_CONT_CODE_SET_PLAYER_DESTINY3,
  mFont_CONT_CODE_SET_PLAYER_DESTINY4,
  mFont_CONT_CODE_SET_PLAYER_DESTINY5,
  mFont_CONT_CODE_SET_PLAYER_DESTINY6,
  mFont_CONT_CODE_SET_PLAYER_DESTINY7,
  mFont_CONT_CODE_SET_PLAYER_DESTINY8,
  mFont_CONT_CODE_SET_PLAYER_DESTINY9,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_NORMAL,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_ANGRY,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_SAD,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_FUN,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_SLEEPY,
  mFont_CONT_CODE_SET_COLOR_CHAR,
  mFont_CONT_CODE_SOUND_CUT,
  mFont_CONT_CODE_SET_LINE_OFFSET,
  mFont_CONT_CODE_SET_LINE_TYPE,
  mFont_CONT_CODE_SET_CHAR_SCALE,
  mFont_CONT_CODE_BUTTON2,
  mFont_CONT_CODE_BGM_MAKE,
  mFont_CONT_CODE_BGM_DELETE,
  mFont_CONT_CODE_MSG_TIME_END,
  mFont_CONT_CODE_SOUND_TRG_SYS,
  mFont_CONT_CODE_SET_LINE_SCALE,
  mFont_CONT_CODE_SOUND_NO_PAGE,
  mFont_CONT_CODE_VOICE_TRUE,
  mFont_CONT_CODE_VOICE_FALSE,
  mFont_CONT_CODE_SELECT_NO_B,
  mFont_CONT_CODE_GIVE_OPEN,
  mFont_CONT_CODE_GIVE_CLOSE,
  mFont_CONT_CODE_SET_MESSAGE_CONTENTS_GLOOMY,
  mFont_CONT_CODE_SELECT_NO_B_CLOSE,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_SECTION,
  mFont_CONT_CODE_AGB_DUMMY0,
  mFont_CONT_CODE_AGB_DUMMY1,
  mFont_CONT_CODE_AGB_DUMMY2,
  mFont_CONT_CODE_SPACE,
  mFont_CONT_CODE_AGB_DUMMY3,
  mFont_CONT_CODE_AGB_DUMMY4,
  mFont_CONT_CODE_AGB_MALE_FEMALE_CHECK,
  mFont_CONT_CODE_AGB_DUMMY5,
  mFont_CONT_CODE_AGB_DUMMY6,
  mFont_CONT_CODE_AGB_DUMMY7,
  mFont_CONT_CODE_AGB_DUMMY8,
  mFont_CONT_CODE_AGB_DUMMY9,
  mFont_CONT_CODE_AGB_DUMMY10,
  mFont_CONT_CODE_PUT_STRING_ISLAND_NAME,
  mFont_CONT_CODE_SET_CURSOR_JUST,
  mFont_CONT_CODE_CLR_CURSOR_JUST,
  mFont_CONT_CODE_CUT_ARTICLE,
  mFont_CONT_CODE_CAPITAL_LETTER,
  mFont_CONT_CODE_PUT_STRING_AM_PM,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_4,
  mFont_CONT_CODE_SET_NEXT_MESSAGE_5,
  mFont_CONT_CODE_SET_SELECT_STRING_5,
  mFont_CONT_CODE_SET_SELECT_STRING_6,
  mFont_CONT_CODE_9BIT,
  mFont_CONT_CODE_FONT_KIGOU,

  mFont_CONT_CODE_NUM,
  mFont_CONT_CODE_END = 256
};

// TODO: figure out the other values for this
enum {
  mFont_CONT_ATTRIBUTE_0,
  mFont_CONT_ATTRIBUTE_DEMO,
  mFont_CONT_ATTRIBUTE_STRING,
  mFont_CONT_ATTRIBUTE_3,
  mFont_CONT_ATTRIBUTE_SENTENCE,
  mFont_CONT_ATTRIBUTE_CHARACTER,
  mFont_CONT_ATTRIBUTE_BGM,
  mFont_CONT_ATTRIBUTE_SE,
  mFont_CONT_ATTRIBUTE_AGB_DUMMY,

  mFont_CONT_ATTRIBUTE_END
};

enum {
  mFont_LineType_Top,
  mFont_LineType_Center,
  mFont_LineType_Bottom,

  mFont_LineType_End
};

enum {
  mFont_BGM_QUIET,

  // TODO

  mFont_BGM_NUM = 9
};

enum {
  mFont_BGM_STOP_TYPE_NORMAL,
  mFont_BGM_STOP_TYPE_QUICK,
  mFont_BGM_STOP_TYPE_RESETTI,

  mFont_BGM_STOP_TYPE_NUM
};

enum {
  mFont_SE_0,

  // TODO

  mFont_SE_NUM = 7
};

#define mFont_CHAR_FLAG_CUT 1
#define mFont_CHAR_FLAG_USE_POLY 2
#define mFont_CHAR_FLAG_SCALE 4
#define mFont_CHAR_FLAG_SCALE_RESET 8

/* sizeof(struct font_char_s) == 0x40 */
typedef struct font_char_s {
  /* 0x00 */ u8* char_p;
  /* 0x04 */ s8 len;
  /* 0x05 */ u8 flags;
  /* 0x06 */ u8 pad0[2];
  /* 0x08 */ xy_t position;
  /* 0x10 */ xy_t scale;
  /* 0x18 */ xy_t inv_scale;
  /* 0x20 */ xy_t scaled_size;
  /* 0x28 */ xy_t inv_scaled_size;
  /* 0x30 */ f32 ofs_y;
  /* 0x34 */ rgba_t color;
  /* 0x38 */ u8 color_ctr;
  /* 0x39 */ u8 pad1[3];
  /* 0x3C */ f32 width;
} mFontChar;

#define mFont_SENTENCE_FLAG_CUT 1
#define mFont_SENTENCE_FLAG_REVERT 2
#define mFont_SENTENCE_FLAG_USE_POLY 4
#define mFont_SENTENCE_FLAG_3 8
#define mFont_SENTENCE_FLAG_NO_COMBINE 16
#define mFont_SENTENCE_FLAG_NO_COLOR 32
#define mFont_SENTENCE_SKIP_DRAW_NEW_LINE 64
#define mFont_SENTENCE_FLAG_VOICE_SE 128
#define mFont_SENTENCE_FLAG_8 256

typedef struct font_sentence_s {
  u8* sentence_p;
  int len;
  u32 flags;
  xy_t position;
  int line_type;
  rgba_t color;
  xy_t scale;
  xy_t inv_scale;
  int now_idx;
  f32 offset;
  f32 width;
  f32 line_scale;
  f32 inv_line_scale;
  int se_pos;
  s16 se_character_id;
  u8 voice_idx;
  u8 voice2_idx;
  u8 voice3_idx;
  u8 pad[3];
  mFontChar character;
} mFontSentence;

#define mFont_TEX_CHAR_WIDTH 12
#define mFont_TEX_CHAR_HEIGHT 16

#define mFont_TEX_CHAR_WIDTH_F32 12.0f
#define mFont_TEX_CHAR_HEIGHT_F32 16.0f

#define mFont_SCALE_F 16.0f

typedef void (*mFont_ControlCodeCharFunc)(mFontChar*, Gfx**);
typedef void (*mFont_ControlCodeSentenceFunc)(mFontSentence*, Gfx**);

extern void mFont_ct();
extern int mFont_UnintToString(u8* str, int figure, u32 num, int figure_start, int left_cut, int fill_zero, int separator);
extern int mFont_char_save_data_check(u8 c);
extern u8 mFont_small_to_capital(u8 small);
extern int mFont_GetCodeWidth(u8 c, int cut);
extern int mFont_GetStringWidth(u8* str, int len, int cut);
extern int mFont_GetStringWidth2(u8* str, int len, int cut);
extern int mFont_CodeSize_get(u8* str);
extern int mFont_CodeSize_idx_get(u8* str, int idx);
extern int mFont_cont_attr_get(int cont_code);
extern void mFont_gppSetMode(Gfx** gfx_pp);
extern void mFont_SetMode(GRAPH* graph, int mode);
extern void mFont_SetPrimColor(GRAPH* graph, int r, int g, int b, int a, int mode);
extern void mFont_SetCombineMode(GRAPH* graph, int revert_flag, int mode);
extern f32 mFont_SetVertexRectangle(GAME* game, f32 x, f32 y, int s, int t, f32 scale_x, f32 scale_y, int mode);
extern f32 mFont_SetLineStrings_AndSpace(GAME* game, u8* str, int len, f32 x, f32 y, int r, int g, int b, int a, int flag_revert, int flag_cut, int unused, f32 scale_x, f32 scale_y, int mode);
extern f32 mFont_SetLineStrings(GAME* game, u8* str, int len, f32 x, f32 y, int r, int g, int b, int a, int flag_revert, int flag_cut, f32 scale_x, f32 scale_y, int mode);
extern void mFont_CulcOrthoMatrix(Mtx* m);
extern void mFont_SetMatrix(GRAPH* graph, int mode);
extern void mFont_UnSetMatrix(GRAPH* graph, int mode);
extern void mFont_Main_start(GRAPH* graph);
extern void mFontSentence_set(mFontSentence* this, u8* sentence_p, int len, u32 flags, xy_t* pos, int line_type, xy_t* scale, rgba_t* color, int se_voice_pos, u8 voice_idx, u8 voice2_idx, u8 voice3_idx, s16 voice_se_character_idx);
extern void mFontSentence_gppDraw(mFontSentence* this, GAME* game, Gfx** gfx_pp);
extern f32 mFont_SetMarkChar(GAME* game, u8 mark_type, f32 x, f32 y, int r, int g, int b, int a, int revert_flag, f32 scale_x, f32 scale_y, int mode);
extern void mFont_gppSetRectMode(Gfx** gfx_pp);
extern void mFont_Change_RubyToKana(u8* str, int len);

extern void mFont_KanjiLevel_debug(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
