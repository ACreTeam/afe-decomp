#include "m_font.h"

#include "audio.h"
#include "m_lib.h"
#include "libforest/gbi_extensions.h"
#include "dataobject.h"
#include "game.h"
#include "graph.h"
#include "types.h"
#include "libultra/gu.h"
#include "sys_matrix.h"
#include "MSL_C/w_math.h"
#include "m_rcp.h"
#include "libc64/math64.h"
#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "padmgr.h"

#define mFont_CC_FONT 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0
#define mFont_CC_NOFONT 0, 0, 0, PRIMITIVE, 0, PRIMITIVE, TEXEL0, PRIMITIVE

#include "../src/game/m_font_offset.c_inc"
#include "../src/game/m_font_main.c_inc"
#include "../src/game/m_font_wide.c_inc"
#include "../src/game/m_font_mark.c_inc"
#include "../src/game/m_font_rect.c_inc"

/* @unused static u8* mFont_Get_end_load_texture() */

extern void mFont_ct() {
    mFont_CurrentScale_init();
    mFont_CurrentColor_init();
}

static int mFont_CutLeftSpace(u8* str, int str_len) {
    u8* dst;
    u8* src;
    int i, j;

    for (i = 0; i < str_len; i++) {
        if (str[i] != CHAR_SPACE) {
            break;
        }
    }

    if (i == str_len) {
        return 0;
    } else if (i == 0) {
        return str_len;
    }

    dst = str;
    src = str + i;
    for (j = i; j < str_len; j++) {
        *dst++ = *src++;
    }

    for (j = 0; j < i; j++) {
        *dst++ = CHAR_SPACE;
    }

    return str_len - i;
}

static u8 mFont_suji_data[10] = "0123456789";

static int mFont_suji_check(u8 c) {
    int i;

    for (i = 0; i < 10; i++) {
        if (c == mFont_suji_data[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mFont_UnintToString(u8* str, int figure, u32 num, int figure_start, int left_cut, int fill_zero,
                               int separator) {
    int i;
    int j;
    u32 cur_num;
    int next;

    int temp2;
    int last_figure;

    int l = figure - figure_start;
    u8 fill_char = fill_zero ? CHAR_ZERO : CHAR_SPACE;
    u8 left_fill_char = fill_zero && !left_cut ? CHAR_ZERO : CHAR_SPACE;

    cur_num = num;
    for (last_figure = figure - 1; last_figure >= l; last_figure--) {
        next = cur_num / 10;
        temp2 = cur_num - next * 10;
        if (cur_num == 0) {
            if (num == 0 && last_figure == figure - 1) {
                str[last_figure] = CHAR_ZERO;
            } else {
                str[last_figure] = fill_char;
            }
        } else {
            str[last_figure] = mFont_suji_data[temp2];
        }
        cur_num = next;
    }

    for (i = last_figure; i >= 0; i--) {
        str[i] = left_fill_char;
    }

    if (separator) {
        int count = 0;
        for (i = figure - 1; i >= 0; i--) {
            if (mFont_suji_check(str[i])) {
                count++;
                if (count > 3) {
                    for (j = 0; j < i; j++) {
                        str[j] = str[j + 1];
                    }

                    str[i] = CHAR_COMMA;
                    count = 0;
                }
            }
        }
    }

    if (left_cut) {
        return mFont_CutLeftSpace(str, figure);
    }

    return figure;
}

extern int mFont_char_save_data_check_unshort(u16 c) {
    return c == CHAR_CONTROL_CODE || c == CHAR_MESSAGE_TAG;
}

extern u8 mFont_small_to_capital(u8 small) {
    static const u8 tbl[][2] = {
        { CHAR_a, CHAR_A },
        { CHAR_b, CHAR_B },
        { CHAR_c, CHAR_C },
        { CHAR_d, CHAR_D },
        { CHAR_e, CHAR_E },
        { CHAR_f, CHAR_F },
        { CHAR_g, CHAR_G },
        { CHAR_h, CHAR_H },
        { CHAR_i, CHAR_I },
        { CHAR_j, CHAR_J },
        { CHAR_k, CHAR_K },
        { CHAR_l, CHAR_L },
        { CHAR_m, CHAR_M },
        { CHAR_n, CHAR_N },
        { CHAR_o, CHAR_O },
        { CHAR_p, CHAR_P },
        { CHAR_q, CHAR_Q },
        { CHAR_r, CHAR_R },
        { CHAR_s, CHAR_S },
        { CHAR_t, CHAR_T },
        { CHAR_u, CHAR_U },
        { CHAR_v, CHAR_V },
        { CHAR_w, CHAR_W },
        { CHAR_x, CHAR_X },
        { CHAR_y, CHAR_Y },
        { CHAR_z, CHAR_Z },
    };

    u8 res = small;
    u8* t = (u8*)tbl;
    int i;

    for (i = 0; i < ARRAY_COUNT(tbl); i++, t += 2) {
        if (t[0] == small) {
            res = t[1];
            break;
        }
    }

    return res;
}

extern int mFont_Check_Cont(u8 c) {
    return c == CHAR_CONTROL_CODE;
}

extern int mFont_Check_ContId(const u8* str, int cont_id) {
    int ret = FALSE;

    if (mFont_Check_Cont(str[0]) && str[1] == cont_id) {
        ret = TRUE;
    }

    return ret;
}

extern u8 mFont_Get_ContPrmU8(const u8* str) {
    return str[2];
}

extern int mFont_Check_Tag(u8 c) {
    return c == CHAR_MESSAGE_TAG;
}

extern u8 mFont_Get_TagSize(const u8* str) {
    return str[1];
}

extern int mFont_Get_TagGroup(const u8* str) {
    return str[2];
}

extern int mFont_Get_TagId(const u8* str) {
    return (str[3] << 8) | str[4];
}

extern int mFont_Check_TagId(const u8* str, int args, int group, int id) {
    int ret = FALSE;

    if (mFont_Check_Tag(str[0])) {
        int chk_grp = str[2];
        int chk_id = mFont_Get_TagId(str);

        if (chk_grp == group && chk_id == id) {
            ret = TRUE;
        }
    }

    return ret;
}
extern u8 mFont_Get_TagPrmU8(const u8* str) {
    return str[5];
}

extern u16 mFont_Get_TagPrmU16(const u8* str) {
    return (str[5] << 8) | str[6];
}

extern void mFont_Get_TagPrmU16U16(const u8* str, u16* prm0, u16* prm1) {
    *prm0 = (str[5] << 8) | str[6];
    *prm1 = (str[7] << 8) | str[8];
}

extern void mFont_Get_TagPrmU16U16U16(const u8* str, u16* prm0, u16* prm1, u16* prm2) {
    *prm0 = (str[5] << 8) | str[6];
    *prm1 = (str[7] << 8) | str[8];
    *prm2 = (str[9] << 8) | str[10];
}

extern void mFont_Get_TagPrmU16U16U16U16(const u8* str, u16* prm0, u16* prm1, u16* prm2, u16* prm3) {
    *prm0 = (str[5] << 8) | str[6];
    *prm1 = (str[7] << 8) | str[8];
    *prm2 = (str[9] << 8) | str[10];
    *prm3 = (str[11] << 8) | str[12];
}

extern void mFont_Get_TagPrmU8U16(const u8* str, u8* prm0, u16* prm1) {
    *prm0 = str[5];
    *prm1 = (str[6] << 8) | str[7];
}

extern void mFont_Get_TagPrmU8U16U16(const u8* str, u8* prm0, u16* prm1, u16* prm2) {
    *prm0 = str[5];
    *prm1 = (str[6] << 8) | str[7];
    *prm2 = (str[8] << 8) | str[9];
}

extern void mFontTag_get_KanjiCom(const u8* str, int* lvl, int* bank) {
    u8 prm = mFont_Get_TagPrmU8(str);

    if (prm < 10) {
        *bank = 0;
    } else {
        *bank = 10;
        prm -= 10;
    }

    *lvl = prm;
}

extern void mFontTag_Get_Ruby(const u8* str, mFontRuby_c* ruby_info) {
    u8 group = mFont_Get_TagGroup(str); // @unused
    u16 id = mFont_Get_TagId(str); // @unused
    u8 size = mFont_Get_TagSize(str);

    ruby_info->cmd_size = (u8)size;
    ruby_info->kana_count = mFont_Get_TagPrmU8(str);
    ruby_info->ruby_start = 6;
    ruby_info->ruby_count = size - ruby_info->ruby_start;
}

extern int mFont_GetPlayerKanjiLv(void) {
    if (Common_Get(kanji_level_unset)) {
        return Common_Get(cur_kanji_lv);
    } else {
        int lv = Now_Private->kanji_pl_lv;

        if (mFont_GetKanjiLevel_debug() > 0 && mFont_GetKanjiLevel_debug() <= 6) {
            lv = mFont_GetKanjiLevel_debug() - 1;
        }

        return lv;
    }
}

extern void mFont_Change_RubyToKana(u8* str, int len) {
    int i;
    mFontRuby_c ruby;

    i = 0;
    do {
        u8* pb = str + i;

        if (mFont_Check_Tag(*pb)) {
            int tag_group = mFont_Get_TagGroup(pb);
            int tag_id = mFont_Get_TagId(pb);

            if (tag_group == mFont_TAG_GROUP_SYS && tag_id == mFont_TAG_SYS_RUBY) {
                mFontTag_Get_Ruby(pb, &ruby);
                mMsg_MoveDataCut(str, i + ruby.cmd_size, i + ruby.cmd_size + ruby.kana_count, len, TRUE);
                mMsg_MoveDataCut(str, i, i + ruby.ruby_start, len, TRUE);
                i += ruby.ruby_count;
            } else if (tag_group == mFont_TAG_GROUP_BASE && tag_id == mFont_TAG_BASE_KANJI_COM) {
                mMsg_MoveDataCut(str, i, i + mFont_Get_TagSize(pb), len, TRUE);
            } else {
                i += mFont_CodeSize_get(pb);
            }
        } else {
            i += mFont_CodeSize_get(pb);
        }
    } while (i < len);
}

static int l_mfont_kanji_level = 0;

extern int mFont_GetKanjiLevel_debug(void) {
    return l_mfont_kanji_level;
}

extern void mFont_KanjiLevel_debug(gfxprint_t* gfxprint) {
    if ((gamePT->pads[PAD2].on.button & BUTTON_Y) == BUTTON_Y) {
        l_mfont_kanji_level++;

        if (l_mfont_kanji_level > 6) {
            l_mfont_kanji_level = 0;
        }
    }

    if (l_mfont_kanji_level > 0) {
        gfxprint_color(gfxprint, 235, 255, 235, 255);
        gfxprint_locate8x8(gfxprint, 26, 4);
        gfxprint_printf(gfxprint, "kanji : %d", l_mfont_kanji_level - 1);
    }
}
