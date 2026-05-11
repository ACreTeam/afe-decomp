#include "m_mail_password_check.h"

#include "m_font.h"
#include "m_room_type.h"
#include "m_name_table.h"
#include "m_private.h"
#include "m_npc.h"
#include "m_shop.h"
#include "_mem.h"
#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_text.h"
#include "m_handbill.h"
#include "m_post_office.h"
#include "m_string.h"

#ifdef __INTELLISENSE__
#define __abs(x) ABS(x)
#endif

static u8 usable_to_fontnum[64] = {
    CHAR_PP_000, CHAR_PP_001, CHAR_PP_002, CHAR_PP_003, CHAR_PP_004, CHAR_PP_005, CHAR_PP_006, CHAR_PP_007,
    CHAR_PP_008, CHAR_PP_009, CHAR_PP_010, CHAR_PP_011, CHAR_PP_012, CHAR_PP_013, CHAR_PP_014, CHAR_PP_015,
    CHAR_PP_016, CHAR_PP_017, CHAR_PP_018, CHAR_PP_019, CHAR_PP_020, CHAR_PP_021, CHAR_PP_022, CHAR_PP_023,
    CHAR_PP_024, CHAR_PP_025, CHAR_PP_026, CHAR_PP_027, CHAR_PP_028, CHAR_PP_029, CHAR_PP_030, CHAR_PP_031,
    CHAR_PP_035, CHAR_PP_036, CHAR_PP_091, CHAR_PP_093, CHAR_PP_094, CHAR_PP_096, CHAR_PP_123, CHAR_PP_124,
    CHAR_PP_125, CHAR_PP_126, CHAR_PP_192, CHAR_PP_193, CHAR_PP_194, CHAR_PP_195, CHAR_PP_231, CHAR_PP_232,
    CHAR_PP_233, CHAR_PP_234, CHAR_PP_235, CHAR_PP_236, CHAR_PP_237, CHAR_PP_238, CHAR_PP_239, CHAR_PP_240,
    CHAR_PP_241, CHAR_PP_242, CHAR_PP_243, CHAR_PP_244, CHAR_PP_245, CHAR_PP_247, CHAR_PP_248, CHAR_PP_249,
};

static u8 usable_to_fontnum_new[64] = {
    CHAR_PP_010, CHAR_PP_031, CHAR_PP_029, CHAR_PP_240, CHAR_PP_241, CHAR_PP_245, CHAR_PP_013, CHAR_PP_005,
    CHAR_PP_242, CHAR_PP_030, CHAR_PP_231, CHAR_PP_096, CHAR_PP_235, CHAR_PP_017, CHAR_PP_023, CHAR_PP_004,
    CHAR_PP_237, CHAR_PP_021, CHAR_PP_035, CHAR_PP_233, CHAR_PP_232, CHAR_PP_239, CHAR_PP_022, CHAR_PP_016,
    CHAR_PP_009, CHAR_PP_244, CHAR_PP_194, CHAR_PP_018, CHAR_PP_248, CHAR_PP_192, CHAR_PP_015, CHAR_PP_195,
    CHAR_PP_247, CHAR_PP_091, CHAR_PP_123, CHAR_PP_094, CHAR_PP_008, CHAR_PP_000, CHAR_PP_025, CHAR_PP_002,
    CHAR_PP_249, CHAR_PP_036, CHAR_PP_026, CHAR_PP_012, CHAR_PP_236, CHAR_PP_124, CHAR_PP_014, CHAR_PP_234,
    CHAR_PP_001, CHAR_PP_019, CHAR_PP_007, CHAR_PP_126, CHAR_PP_024, CHAR_PP_243, CHAR_PP_020, CHAR_PP_028,
    CHAR_PP_093, CHAR_PP_003, CHAR_PP_238, CHAR_PP_027, CHAR_PP_011, CHAR_PP_125, CHAR_PP_193, CHAR_PP_006,
};

static int mMpswd_prime_number[256] = {
    17,   19,   23,   29,   31,   37,   41,   43,   47,   53,   59,   61,   67,   71,   73,   79,   83,   89,   97,
    101,  103,  107,  109,  113,  127,  131,  137,  139,  149,  151,  157,  163,  167,  173,  179,  181,  191,  193,
    197,  199,  211,  223,  227,  229,  233,  239,  241,  251,  257,  263,  269,  271,  277,  281,  283,  293,  307,
    311,  313,  317,  331,  337,  347,  349,  353,  359,  367,  373,  379,  383,  389,  397,  401,  409,  419,  421,
    431,  433,  439,  443,  449,  457,  461,  463,  467,  479,  487,  491,  499,  503,  509,  521,  523,  541,  547,
    557,  563,  569,  571,  577,  587,  593,  599,  601,  607,  613,  617,  619,  631,  641,  643,  647,  653,  659,
    661,  673,  677,  683,  691,  701,  709,  719,  727,  733,  739,  743,  751,  757,  761,  769,  773,  787,  797,
    809,  811,  821,  823,  827,  829,  839,  853,  857,  859,  863,  877,  881,  883,  887,  907,  911,  919,  929,
    937,  941,  947,  953,  967,  971,  977,  983,  991,  997,  1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051,
    1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193,
    1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319,
    1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481,
    1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607,
    1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667,
};

static u8 mMpswd_transposition_cipher_char0_0[9] = "NiiMasaru";
static u8 mMpswd_transposition_cipher_char0_1[15] = "KomatsuKunihiro";
static u8 mMpswd_transposition_cipher_char0_2[14] = "TakakiGentarou";
static u8 mMpswd_transposition_cipher_char0_3[15] = "MiyakeHiromichi";
static u8 mMpswd_transposition_cipher_char0_4[13] = "HayakawaKenzo";
static u8 mMpswd_transposition_cipher_char0_5[18] = "KasamatsuShigehiro";
static u8 mMpswd_transposition_cipher_char0_6[17] = "SumiyoshiNobuhiro";
static u8 mMpswd_transposition_cipher_char0_7[12] = "NomaTakafumi";
static u8 mMpswd_transposition_cipher_char0_8[13] = "EguchiKatsuya";
static u8 mMpswd_transposition_cipher_char0_9[13] = "NogamiHisashi";
static u8 mMpswd_transposition_cipher_char0_10[8] = "IidaToki";
static u8 mMpswd_transposition_cipher_char0_11[13] = "IkegawaNoriko";
static u8 mMpswd_transposition_cipher_char0_12[14] = "KawaseTomohiro";
static u8 mMpswd_transposition_cipher_char0_13[9] = "BandoTaro";
static u8 mMpswd_transposition_cipher_char0_14[11] = "TotakaKazuo";
static u8 mMpswd_transposition_cipher_char0_15[13] = "WatanabeKunio";

static u8 mMpswd_transposition_cipher_char1_0[11] = "RichAmtower";
static u8 mMpswd_transposition_cipher_char1_1[10] = "KyleHudson";
static u8 mMpswd_transposition_cipher_char1_2[15] = "MichaelKelbaugh";
static u8 mMpswd_transposition_cipher_char1_3[14] = "RaycholeLAneff";
static u8 mMpswd_transposition_cipher_char1_4[10] = "LeslieSwan";
static u8 mMpswd_transposition_cipher_char1_5[16] = "YoshinobuMantani";
static u8 mMpswd_transposition_cipher_char1_6[12] = "KirkBuchanan";
static u8 mMpswd_transposition_cipher_char1_7[9] = "TimOLeary";
static u8 mMpswd_transposition_cipher_char1_8[10] = "BillTrinen";
static u8 mMpswd_transposition_cipher_char1_9[20] = "nAkAyOsInoNyuuSankin";
static u8 mMpswd_transposition_cipher_char1_10[20] = "zendamaKINAKUDAMAkin";
static u8 mMpswd_transposition_cipher_char1_11[19] = "OishikutetUYOKUNARU";
static u8 mMpswd_transposition_cipher_char1_12[13] = "AsetoAminofen";
static u8 mMpswd_transposition_cipher_char1_13[20] = "fcSFCn64GCgbCGBagbVB";
static u8 mMpswd_transposition_cipher_char1_14[11] = "YossyIsland";
static u8 mMpswd_transposition_cipher_char1_15[14] = "KedamonoNoMori";

typedef struct {
    u8* str;
    int len;
} mMpswd_transposition_cipher_str_c;

static mMpswd_transposition_cipher_str_c mMpswd_transposition_cipher_char0_table[16] = {
    { mMpswd_transposition_cipher_char0_0, sizeof(mMpswd_transposition_cipher_char0_0) },
    { mMpswd_transposition_cipher_char0_1, sizeof(mMpswd_transposition_cipher_char0_1) },
    { mMpswd_transposition_cipher_char0_2, sizeof(mMpswd_transposition_cipher_char0_2) },
    { mMpswd_transposition_cipher_char0_3, sizeof(mMpswd_transposition_cipher_char0_3) },
    { mMpswd_transposition_cipher_char0_4, sizeof(mMpswd_transposition_cipher_char0_4) },
    { mMpswd_transposition_cipher_char0_5, sizeof(mMpswd_transposition_cipher_char0_5) },
    { mMpswd_transposition_cipher_char0_6, sizeof(mMpswd_transposition_cipher_char0_6) },
    { mMpswd_transposition_cipher_char0_7, sizeof(mMpswd_transposition_cipher_char0_7) },
    { mMpswd_transposition_cipher_char0_8, sizeof(mMpswd_transposition_cipher_char0_8) },
    { mMpswd_transposition_cipher_char0_9, sizeof(mMpswd_transposition_cipher_char0_9) },
    { mMpswd_transposition_cipher_char0_10, sizeof(mMpswd_transposition_cipher_char0_10) },
    { mMpswd_transposition_cipher_char0_11, sizeof(mMpswd_transposition_cipher_char0_11) },
    { mMpswd_transposition_cipher_char0_12, sizeof(mMpswd_transposition_cipher_char0_12) },
    { mMpswd_transposition_cipher_char0_13, sizeof(mMpswd_transposition_cipher_char0_13) },
    { mMpswd_transposition_cipher_char0_14, sizeof(mMpswd_transposition_cipher_char0_14) },
    { mMpswd_transposition_cipher_char0_15, sizeof(mMpswd_transposition_cipher_char0_15) }
};

static mMpswd_transposition_cipher_str_c mMpswd_transposition_cipher_char1_table[16] = {
    { mMpswd_transposition_cipher_char1_0, sizeof(mMpswd_transposition_cipher_char1_0) },
    { mMpswd_transposition_cipher_char1_1, sizeof(mMpswd_transposition_cipher_char1_1) },
    { mMpswd_transposition_cipher_char1_2, sizeof(mMpswd_transposition_cipher_char1_2) },
    { mMpswd_transposition_cipher_char1_3, sizeof(mMpswd_transposition_cipher_char1_3) },
    { mMpswd_transposition_cipher_char1_4, sizeof(mMpswd_transposition_cipher_char1_4) },
    { mMpswd_transposition_cipher_char1_5, sizeof(mMpswd_transposition_cipher_char1_5) },
    { mMpswd_transposition_cipher_char1_6, sizeof(mMpswd_transposition_cipher_char1_6) },
    { mMpswd_transposition_cipher_char1_7, sizeof(mMpswd_transposition_cipher_char1_7) },
    { mMpswd_transposition_cipher_char1_8, sizeof(mMpswd_transposition_cipher_char1_8) },
    { mMpswd_transposition_cipher_char1_9, sizeof(mMpswd_transposition_cipher_char1_9) },
    { mMpswd_transposition_cipher_char1_10, sizeof(mMpswd_transposition_cipher_char1_10) },
    { mMpswd_transposition_cipher_char1_11, sizeof(mMpswd_transposition_cipher_char1_11) },
    { mMpswd_transposition_cipher_char1_12, sizeof(mMpswd_transposition_cipher_char1_12) },
    { mMpswd_transposition_cipher_char1_13, sizeof(mMpswd_transposition_cipher_char1_13) },
    { mMpswd_transposition_cipher_char1_14, sizeof(mMpswd_transposition_cipher_char1_14) },
    { mMpswd_transposition_cipher_char1_15, sizeof(mMpswd_transposition_cipher_char1_15) }
};

static mMpswd_transposition_cipher_str_c* mMpswd_transposition_cipher_char_table[2] = {
    mMpswd_transposition_cipher_char0_table, mMpswd_transposition_cipher_char1_table
};

static u8 mMpswd_chg_code_table[256] = {
    0xf0, 0x83, 0xfd, 0x62, 0x93, 0x49, 0x0d, 0x3e, 0xe1, 0xa4, 0x2b, 0xaf, 0x3a, 0x25, 0xd0, 0x82, 0x7f, 0x97, 0xd2,
    0x03, 0xb2, 0x32, 0xb4, 0xe6, 0x09, 0x42, 0x57, 0x27, 0x60, 0xea, 0x76, 0xab, 0x2d, 0x65, 0xa8, 0x4d, 0x8b, 0x95,
    0x01, 0x37, 0x59, 0x79, 0x33, 0xac, 0x2f, 0xae, 0x9f, 0xfe, 0x56, 0xd9, 0x04, 0xc6, 0xb9, 0x28, 0x06, 0x5c, 0x54,
    0x8d, 0xe5, 0x00, 0xb3, 0x7b, 0x5e, 0xa7, 0x3c, 0x78, 0xcb, 0x2e, 0x6d, 0xe4, 0xe8, 0xdc, 0x40, 0xa0, 0xde, 0x2c,
    0xf5, 0x1f, 0xcc, 0x85, 0x71, 0x3d, 0x26, 0x74, 0x9c, 0x13, 0x7d, 0x7e, 0x66, 0xf2, 0x9e, 0x02, 0xa1, 0x53, 0x15,
    0x4f, 0x51, 0x20, 0xd5, 0x39, 0x1a, 0x67, 0x99, 0x41, 0xc7, 0xc3, 0xa6, 0xc4, 0xbc, 0x38, 0x8c, 0xaa, 0x81, 0x12,
    0xdd, 0x17, 0xb7, 0xef, 0x2a, 0x80, 0x9d, 0x50, 0xdf, 0xcf, 0x89, 0xc8, 0x91, 0x1b, 0xbb, 0x73, 0xf8, 0x14, 0x61,
    0xc2, 0x45, 0xc5, 0x55, 0xfc, 0x8e, 0xe9, 0x8a, 0x46, 0xdb, 0x4e, 0x05, 0xc1, 0x64, 0xd1, 0xe0, 0x70, 0x16, 0xf9,
    0xb6, 0x36, 0x44, 0x8f, 0x0c, 0x29, 0xd3, 0x0e, 0x6f, 0x7c, 0xd7, 0x4a, 0xff, 0x75, 0x6c, 0x11, 0x10, 0x77, 0x3b,
    0x98, 0xba, 0x69, 0x5b, 0xa3, 0x6a, 0x72, 0x94, 0xd6, 0xd4, 0x22, 0x08, 0x86, 0x31, 0x47, 0xbe, 0x87, 0x63, 0x34,
    0x52, 0x3f, 0x68, 0xf6, 0x0f, 0xbf, 0xeb, 0xc0, 0xce, 0x24, 0xa5, 0x9a, 0x90, 0xed, 0x19, 0xb8, 0xb5, 0x96, 0xfa,
    0x88, 0x6e, 0xfb, 0x84, 0x23, 0x5d, 0xcd, 0xee, 0x92, 0x58, 0x4c, 0x0b, 0xf7, 0x0a, 0xb1, 0xda, 0x35, 0x5f, 0x9b,
    0xc9, 0xa9, 0xe7, 0x07, 0x1d, 0x18, 0xf3, 0xe3, 0xf1, 0xf4, 0xca, 0xb0, 0x6b, 0x30, 0xec, 0x4b, 0x48, 0x1c, 0xad,
    0xe2, 0x21, 0x1e, 0xa2, 0xbd, 0x5a, 0xd8, 0x43, 0x7a,
};

static int mMpswd_select_idx0[8] = { 17, 11, 0, 20, 14, 6, 8, 4 };
static int mMpswd_select_idx1[8] = { 5, 8, 11, 16, 4, 6, 9, 19 };
static int mMpswd_select_idx2[8] = { 9, 14, 17, 21, 11, 10, 19, 2 };
static int mMpswd_select_idx3[8] = { 0, 2, 1, 4, 18, 10, 11, 8 };
static int mMpswd_select_idx4[8] = { 17, 19, 16, 20, 14, 8, 2, 9 };
static int mMpswd_select_idx5[8] = { 16, 2, 1, 8, 18, 4, 7, 6 };
static int mMpswd_select_idx6[8] = { 19, 6, 10, 17, 1, 16, 8, 9 };
static int mMpswd_select_idx7[8] = { 17, 7, 18, 16, 15, 2, 11, 0 };
static int mMpswd_select_idx8[8] = { 6, 2, 11, 1, 8, 14, 0, 16 };
static int mMpswd_select_idx9[8] = { 19, 16, 11, 8, 17, 2, 6, 14 };
static int mMpswd_select_idx10[8] = { 18, 15, 2, 7, 10, 11, 1, 14 };
static int mMpswd_select_idx11[8] = { 8, 0, 14, 2, 20, 11, 15, 17 };
static int mMpswd_select_idx12[8] = { 9, 1, 2, 0, 19, 8, 14, 10 };
static int mMpswd_select_idx13[8] = { 10, 11, 14, 16, 19, 7, 17, 8 };
static int mMpswd_select_idx14[8] = { 19, 8, 6, 1, 17, 9, 14, 10 };
static int mMpswd_select_idx15[8] = { 9, 7, 17, 14, 19, 10, 1, 11 };

static int* mMpswd_select_idx_table[16] = {
    mMpswd_select_idx0,  mMpswd_select_idx1,  mMpswd_select_idx2,  mMpswd_select_idx3,
    mMpswd_select_idx4,  mMpswd_select_idx5,  mMpswd_select_idx6,  mMpswd_select_idx7,
    mMpswd_select_idx8,  mMpswd_select_idx9,  mMpswd_select_idx10, mMpswd_select_idx11,
    mMpswd_select_idx12, mMpswd_select_idx13, mMpswd_select_idx14, mMpswd_select_idx15,
};

static void mMpswd_shift(u8* bits, int count, int amount) {
    u8 shift_bits[mMpswd_OLD_PASSWORD_BITS_LEN];
    u8* shift_p;
    int shift;
    int i;

    shift = -amount;
    shift_p = shift_bits;
    for (i = 0; i < count; i++) {
        if (shift >= count) {
            shift = 0;
        }

        if (shift < 0) {
            shift += count;
        }

        *shift_p++ = bits[shift++];
    }

    memcpy(bits, shift_bits, sizeof(shift_bits));
}

static void mMpswd_hanten(u8* bits, int count) {
    u8 hanten_bits[mMpswd_OLD_PASSWORD_BITS_LEN];
    int i;

    for (i = 0; i < count; i++) {
        hanten_bits[i] = ~bits[i] & 1;
    }

    memcpy(bits, hanten_bits, sizeof(hanten_bits));
}

static void mMpswd_reverse(u8* bits, int count) {
    u8 reverse_bits[mMpswd_OLD_PASSWORD_BITS_LEN];
    u8* src_p;
    u8* dst_p;
    int max;
    int i;

    max = count - 1;
    src_p = bits + max;
    dst_p = reverse_bits;
    for (i = 0; i <= max; i++) {
        *dst_p++ = *src_p--;
    }

    memcpy(bits, reverse_bits, sizeof(reverse_bits));
}

static void mMpswd_bit_shift(u8* pswd, int shift) {
    u8 buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 shifted_buf[mMpswd_PASSWORD_DATA_LEN - 1];
    int bytes_shifted;
    int bits_shifted;

    /* copy password data into work buffer while skipping key index byte */
    memcpy(buf, pswd, 1);
    memcpy(buf + 1, pswd + 2, (mMpswd_PASSWORD_DATA_LEN - 2));

    // this has to be a fakematch
    bytes_shifted = __abs(shift);
    bytes_shifted /= 8; // degenerate code
    bits_shifted = ABS(shift) % 8;

    while (bytes_shifted > mMpswd_PASSWORD_DATA_LEN - 1) {
        bytes_shifted -= (mMpswd_PASSWORD_DATA_LEN - 1);
    }

    if (shift > 0) {
        /* positive shift */
        int dst;
        int byte;
        int shift_mask = 0;
        int i;
        for (i = 0; i < bits_shifted; i++) {
            shift_mask = shift_mask * 2 + 1;
        }

        byte = (buf[bits_shifted == 0 ? 0 : mMpswd_PASSWORD_DATA_LEN - 2] >> (8 - bits_shifted)) & shift_mask;
        dst = bytes_shifted;
        for (i = 0; i < mMpswd_PASSWORD_DATA_LEN - 1; i++) {
            u8 now_byte = buf[i];

            shifted_buf[dst] = byte | (now_byte << bits_shifted);
            byte = (now_byte >> (8 - bits_shifted)) & shift_mask;
            dst = (dst + 1) % (mMpswd_PASSWORD_DATA_LEN - 1);
        }
    } else if (shift < 0) {
        /* negative shift */
        int shift_idx;
        int shift;
        int shift_mask = 0;
        int byte;
        int i;

        for (i = 0; i < bits_shifted; i++) {
            shift_mask = shift_mask * 2 + 1;
        }

        // fakematch?
        byte = 0;
        byte += (buf[bits_shifted == 0 ? mMpswd_PASSWORD_DATA_LEN - 2 : 0]); // start byte

        shift = 8 - bits_shifted;                                                                    // invert shift
        shift_idx = (mMpswd_PASSWORD_DATA_LEN - 2 - bytes_shifted) % (mMpswd_PASSWORD_DATA_LEN - 1); // dst index
        byte &= shift_mask;
        byte <<= shift; // move bits into position

        for (i = mMpswd_PASSWORD_DATA_LEN - 2; i >= 0; i--) {
            int now_byte = buf[i];

            shifted_buf[shift_idx] = byte | (now_byte >> bits_shifted); // save shifted byte
            byte = (now_byte & shift_mask) << shift;                    // update initial bits

            shift_idx--;
            if (shift_idx < 0) {
                shift_idx = mMpswd_PASSWORD_DATA_LEN - 2;
            }
        }
    } else {
        /* no shift (shift == 0) */
        memcpy(shifted_buf, buf, mMpswd_PASSWORD_DATA_LEN - 1);
    }

    /* copy shifted buffer back into main password buffer */
    memcpy(pswd, shifted_buf, 1);
    memcpy(pswd + 2, shifted_buf + 1, mMpswd_PASSWORD_DATA_LEN - 2);
}

static void mMpswd_bit_reverse(u8* pswd) {
    int i;

    for (i = 0; i < mMpswd_PASSWORD_DATA_LEN; i++) {
        if (i != mMpswd_PASSWORD_KEY_IDX) {
            pswd[i] ^= 0xFF;
        }
    }
}

static void mMpswd_bit_arrange_reverse(u8* pswd) {
    u8 buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 reversed_buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 reversed;
    int i;
    int j;
    int b;

    /* copy password data into work buffer while skipping key index byte */
    memcpy(buf, pswd, 1);
    memcpy(buf + 1, pswd + 2, (mMpswd_PASSWORD_DATA_LEN - 2));

    for (i = mMpswd_PASSWORD_DATA_LEN - 2, j = 0; i >= 0; i--) {

        reversed = 0;

        for (b = 7; b >= 0; b--) {
            reversed |= ((buf[i] >> b) & 1) << (7 - b);
        }

        reversed_buf[j] = reversed;
        j++;
    }

    memcpy(pswd, reversed_buf, 1);
    memcpy(pswd + 2, reversed_buf + 1, mMpswd_PASSWORD_DATA_LEN - 2);
}

static int mMpswd_check_opening_sentence(const u16* sentence) {
    int res = FALSE;

    // あいことば
    if (sentence[0] == CHAR_PP_000 && sentence[1] == CHAR_PP_001 && sentence[2] == CHAR_PP_009 &&
        sentence[3] == CHAR_PP_019 && sentence[4] == CHAR_PP_246) {
        res = TRUE;
    } else if (sentence[0] == (0x100 + CHAR_PP_KANJI0_005)) { // key
        res = TRUE;
    }

    return res;
}

static int mMpswd_check_version(u16** text_pp) {
    u16* next_p;
    int ret = mMpswd_VERSION_BAD;
    int i;

    for (i = 0; i < 16; i++) {
        if ((*text_pp)[0] == CHAR_NEW_LINE) {
            next_p = (*text_pp) + 1;

            if (next_p[11] == CHAR_NEW_LINE) {
                *text_pp = next_p;
                ret = mMpswd_VERSION_OLD;
                break;
            }

            if (next_p[0x1B] == CHAR_NEW_LINE) {
                if (next_p[11] == CHAR_SPACE && next_p[0xC] == CHAR_SPACE && next_p[0xD] == CHAR_SPACE &&
                    next_p[0xE] == CHAR_SPACE && next_p[0xF] == CHAR_SPACE) {
                    *text_pp = next_p;
                    ret = mMpswd_VERSION_OLD;
                    break;
                }
            } else if (next_p[0x20] == CHAR_SPACE || next_p[0x20] == CHAR_NEW_LINE) {
                if (next_p[11] == CHAR_SPACE && next_p[0xC] == CHAR_SPACE && next_p[0xD] == CHAR_SPACE &&
                    next_p[0xE] == CHAR_SPACE && next_p[0xF] == CHAR_SPACE && next_p[0x1B] == CHAR_SPACE &&
                    next_p[0x1C] == CHAR_SPACE && next_p[0x1D] == CHAR_SPACE && next_p[0x1E] == CHAR_SPACE &&
                    next_p[0x1F] == CHAR_SPACE) {
                    *text_pp = next_p;
                    ret = mMpswd_VERSION_OLD;
                    break;
                }

                *text_pp = next_p;
                ret = mMpswd_VERSION_NEW;
                break;
            }
        }

        (*text_pp)++;
    }

    return ret;
}

static void mMpswd_except_return_code(u8* dst, u16* src, int version) {
    u16 password_str[mMpswd_PASSWORD_STR_LEN];
    int len = mMpswd_PASSWORD_STR_LEN;

    if (version == mMpswd_VERSION_OLD) {
        int i;
        int count;

        mem_clear((u8*)password_str, sizeof(password_str), CHAR_NEW_LINE);

        count = 0;
        for (i = 0; i < mMpswd_PASSWORD_STR_LEN + 1; i++) {
            switch (src[i]) {
                case CHAR_NEW_LINE:
                case CHAR_SPACE:
                    break;
                default:
                    password_str[count] = src[i];
                    count++;
                    if (count >= mMpswd_OLD_PASSWORD_STR_LEN) {
                        i = mMpswd_PASSWORD_STR_LEN;
                    }
                    break;
            }
        }

        len = mMpswd_OLD_PASSWORD_STR_LEN;
    } else {
        mem_copy((u8*)password_str, (u8*)src, mMpswd_PASSWORD_STR_LEN * sizeof(u16));
    }

    mTxt_conv_9or8bit(password_str, dst, len);
}

static void mMpswd_make_passcode(u8* passcode, int type, int hit_rate, u8* str0, u8* str1, u8* str2, mActor_name_t item,
                                 int npc_type, int npc_code) {
    int checksum;

    switch (type) {
        case mMpswd_CODETYPE_FAMICOM:
        case mMpswd_CODETYPE_USER:
        case mMpswd_CODETYPE_CARD_E_MINI: {
            hit_rate = 4;
            npc_type = 0;
            npc_code = 0xFF;
            break;
        }

        case mMpswd_CODETYPE_MONUMENT: {
            npc_type &= 0xFF;
            hit_rate = 4;
            npc_code = 0xFF;
            break;
        }

        case mMpswd_CODETYPE_NPC:
        case mMpswd_CODETYPE_NPC_NEW: {
            npc_type &= 3;
            hit_rate = 4;
            break;
        }

        case mMpswd_CODETYPE_CARD_E: {
            hit_rate &= 3;
            npc_type &= 3;
            break;
        }

        case mMpswd_CODETYPE_MAGAZINE: {
            npc_type = 0;
            hit_rate &= 7;
            npc_code = 0xFF;
            break;
        }

        default: {
            hit_rate = 4;
            type = mMpswd_CODETYPE_USER;
            break;
        }
    }

    passcode[0] = type << 5;
    passcode[0] |= hit_rate << 2;
    passcode[1] = npc_type;
    passcode[2] = npc_code;

    memcpy(passcode + 3, str0, PLAYER_NAME_LEN);
    memcpy(passcode + 9, str1, PLAYER_NAME_LEN);
    memcpy(passcode + 15, str2, PLAYER_NAME_LEN);

    checksum = 0;
    passcode[21] = (item >> 8);
    passcode[22] = item;

    {
        int i;

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += str0[i];
        }

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += str1[i];
        }

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += str2[i];
        }
    }

    checksum += item;
    checksum += npc_code;
    passcode[0] |= (checksum & 0xC) >> 2;
    passcode[1] |= (checksum & 0x3) << 6;
}

static void mMpswd_chg_6bits_code(u8* sixbits, u8* eightbits) {
    u8 six_byte;
    int six_idx;
    int eight_bit;
    int six_bit;

    six_idx = 0;
    eight_bit = 0;
    six_bit = 0;
    six_byte = 0;

    do {
        u8 bit = ((eightbits[0] >> eight_bit) & 1) << six_bit;
        eight_bit++;
        six_bit++;
        six_byte |= bit;

        if (six_bit >= 6) {
            six_idx++;
            sixbits[0] = six_byte;
            six_bit = 0;
            sixbits++;

            if (six_idx >= mMpswd_PASSWORD_STR_LEN) {
                return;
            }

            six_byte = 0;
        }

        if (eight_bit >= 8) {
            eight_bit = 0;
            eightbits++;
        }
    } while (TRUE);
}

static void mMpswd_chg_8bits_code(u8* eightbits, u8* sixbits) {
    u8 eight_byte;
    int eight_idx;
    int six_bit;
    int eight_bit;

    eight_idx = 0;
    six_bit = 0;
    eight_bit = 0;
    eight_byte = 0;

    do {
        u8 bit = ((sixbits[0] >> six_bit) & 1) << eight_bit;
        six_bit++;
        eight_bit++;
        eight_byte |= bit;

        if (eight_bit >= 8) {
            eight_idx++;
            eightbits[0] = eight_byte;
            eight_bit = 0;
            eightbits++;

            if (eight_idx >= mMpswd_PASSWORD_DATA_LEN) {
                return;
            }

            eight_byte = 0;
        }

        if (six_bit >= 6) {
            six_bit = 0;
            sixbits++;
        }
    } while (TRUE);
}

static void mMpswd_get_RSA_key_code(int* p, int* q, int* r, int** select_table, u8* pswd) {
    u32 rsa_info = pswd[mMpswd_RSA_INFO_IDX];
    int p_idx = rsa_info & 3;
    int q_idx = (rsa_info >> 2) & 3;

    if (p_idx == 3) {
        p_idx = (p_idx ^ q_idx) & 3;
        if (p_idx == 3) {
            p_idx = 0;
        }
    }

    if (q_idx == 3) {
        q_idx = (p_idx + 1) & 3;
        if (q_idx == 3) {
            q_idx = 1;
        }
    }

    if (p_idx == q_idx) {
        q_idx = (p_idx + 1) & 3;
        if (q_idx == 3) {
            q_idx = 1;
        }
    }

    *p = mMpswd_prime_number[p_idx];
    *q = mMpswd_prime_number[q_idx];
    *select_table = mMpswd_select_idx_table[(rsa_info >> 4) & 0xF];
    *r = mMpswd_prime_number[pswd[mMpswd_RSA_R_PRIME_IDX]];
}

static void mMpswd_chg_RSA_cipher(u8* pswd) {
    int r;
    int p;
    int q;
    int* select_idx_table;
    int b;
    int pq;
    int rsa_keysave;
    int i;
    int idx;
    int pow;
    int chg;

    mMpswd_get_RSA_key_code(&p, &q, &r, &select_idx_table, pswd);

    rsa_keysave = 0;
    pq = p * q;

    for (i = 0; i < 8; i++) {
        idx = select_idx_table[0];
        b = pswd[idx];
        chg = b;

        for (pow = r - 1; pow > 0; pow--) {
            chg = (chg * b) % pq;
        }

        pswd[idx] = chg;
        // save the 9th bit state
        rsa_keysave |= ((chg >> 8) & 1) << i;
        select_idx_table++;
    }

    pswd[mMpswd_RSA_KEYSAVE_IDX] = rsa_keysave;
}

static void mMpswd_decode_RSA_cipher(u8* pswd) {
    int n;
    int r;
    int p;
    int q;
    int pq_1;
    int* select_idx_table;
    int decrypted;
    int i;
    int b;
    int pq;
    int pow;
    int rsa_keysave;
    int d;

    mMpswd_get_RSA_key_code(&p, &q, &r, &select_idx_table, pswd);
    pq = p * q;
    pq_1 = (p - 1) * (q - 1);
    pow = 1;

    /* Calculate exponent d for decryption */
    for (pow = 1;; pow++) {
        n = pow * pq_1 + 1;
        if (n % r == 0) {
            r = n / r;
            break;
        }
    }
    // do {
    //     n = pow * pq_1 + 1;
    //     if (n % r == 0) {
    //         r = n / r;
    //         break;
    //     }

    //     pow++;
    // } while (TRUE);

    rsa_keysave = pswd[mMpswd_RSA_KEYSAVE_IDX];
    for (i = 0; i < 8; i++) {
        b = pswd[select_idx_table[0]] | (((rsa_keysave >> i) & 1) << 8);
        decrypted = b;

        /* Do decryption c^d = (m^e)^d = m (% n) */
        for (d = r - 1; d > 0; d--) {
            decrypted = (decrypted * b) % pq;
        }

        pswd[select_idx_table[0]] = decrypted;
        select_idx_table++;
    }
}

static void mMpswd_bit_mix_code(u8* pswd) {
    int bit_mix_code = pswd[mMpswd_BITMIX_CODE_IDX] & 0xF;

    if (bit_mix_code > 12) { // [13, 15] (3 or 18.75%)
        mMpswd_bit_arrange_reverse(pswd);
        mMpswd_bit_reverse(pswd);
        mMpswd_bit_shift(pswd, bit_mix_code * 3);
    } else if (bit_mix_code > 8) { // [9, 12] (4 or 25%)
        mMpswd_bit_arrange_reverse(pswd);
        mMpswd_bit_shift(pswd, -bit_mix_code * 5);
    } else if (bit_mix_code > 4) { // [5, 8] (4 or 25%)
        mMpswd_bit_shift(pswd, -bit_mix_code * 5);
        mMpswd_bit_reverse(pswd);
    } else { // [0, 4] (5 or 31.25%)
        mMpswd_bit_shift(pswd, bit_mix_code * 3);
        mMpswd_bit_arrange_reverse(pswd);
    }
}

static void mMpswd_decode_bit_code(u8* pswd) {
    int bit_mix_code = pswd[mMpswd_BITMIX_CODE_IDX] & 0xF;

    if (bit_mix_code > 12) { // [13, 15] (3 or 18.75%)
        mMpswd_bit_shift(pswd, -bit_mix_code * 3);
        mMpswd_bit_reverse(pswd);
        mMpswd_bit_arrange_reverse(pswd);
    } else if (bit_mix_code > 8) { // [9, 12] (4 or 25%)
        mMpswd_bit_shift(pswd, bit_mix_code * 5);
        mMpswd_bit_arrange_reverse(pswd);
    } else if (bit_mix_code > 4) { // [5, 8] (4 or 25%)
        mMpswd_bit_reverse(pswd);
        mMpswd_bit_shift(pswd, bit_mix_code * 5);
    } else { // [0, 4] (5 or 31.25%)
        mMpswd_bit_arrange_reverse(pswd);
        mMpswd_bit_shift(pswd, -bit_mix_code * 3);
    }
}

static void mMpswd_substitution_cipher(u8* pswd) {
    int i;

    for (i = 0; i < mMpswd_PASSWORD_DATA_LEN; i++) {
        pswd[i] = mMpswd_chg_code_table[pswd[i]];
    }
}

static void mMpswd_decode_substitution_cipher(u8* pswd) {
    int i;
    int idx;

    for (i = 0, idx = 0; i < mMpswd_PASSWORD_DATA_LEN; i++) {
        int j;

        for (j = 0; j < 256; j++) {
            if (mMpswd_chg_code_table[j] == pswd[idx]) {
                pswd[idx] = j;
                idx++;
                break;
            }
        }
    }
}

static void mMpswd_transposition_cipher(u8* pswd, int dir, int char_idx) {
    static int key_idx[2] = { 22, 6 };
    mMpswd_transposition_cipher_str_c* cipher;
    u8* trans_str;
    int len;

    int m;
    int i;
    int str_idx;

    cipher = &mMpswd_transposition_cipher_char_table[char_idx][pswd[key_idx[char_idx]] & 0xF];
    trans_str = cipher->str;
    len = cipher->len;

    m = 1;
    if (dir == 1) {
        m = -1;
    }
    str_idx = 0;
    for (i = 0; i < mMpswd_PASSWORD_DATA_LEN; i++) {
        if (i != key_idx[char_idx]) {
            *pswd += trans_str[str_idx++] * m;

            if (str_idx >= len) {
                str_idx = 0;
            }
        }

        pswd++;
    }
}

// @fakematch
static void mMpswd_bit_shuffle(u8* pswd, int stage) {
    u8 buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 work_buf[mMpswd_PASSWORD_DATA_LEN - 1];

    int key_idx;
    int test2;
    u8* test;
    int count;

    count = mMpswd_PASSWORD_DATA_LEN - 1;
    key_idx = 9;

    if (stage == 0) {
        key_idx = 13;
        count = mMpswd_PASSWORD_DATA_LEN - 2;
    }

    memcpy(buf, pswd, key_idx);
    test = pswd + key_idx + 1;
    memcpy(buf + key_idx, test, test2 = (mMpswd_PASSWORD_DATA_LEN - 1) - key_idx); // TODO: fakematch here
    bzero(work_buf, count);

    {
        int* select_idx_table = mMpswd_select_idx_table[pswd[key_idx] & 3];
        int dst_idx;
        int i;

        for (i = 0; i < count; i++) {
            u8 b = buf[i];
            int bit;

            for (bit = 0; bit < 8; bit++) {
                dst_idx = i + select_idx_table[bit];

                if (dst_idx >= count) {
                    dst_idx -= count;
                }

                work_buf[dst_idx] |= (u8)(((b >> bit) & 1) << bit);
            }
        }
    }

    memcpy(pswd, work_buf, key_idx);
    memcpy(test, work_buf + key_idx, test2); // (mMpswd_PASSWORD_DATA_LEN - 1) - key_idx adding this screws it up
}

// @fakematch
static void mMpswd_decode_bit_shuffle(u8* pswd, int stage) {
    u8 work_buf[mMpswd_PASSWORD_DATA_LEN - 1];
    u8 buf[mMpswd_PASSWORD_DATA_LEN - 1];
    int key_idx;
    int test2;
    u8* test;
    int count;
    int* select_idx_table;
    int i;

    count = mMpswd_PASSWORD_DATA_LEN - 1;
    key_idx = 9;

    if (stage == 0) {
        key_idx = 13;
        count = mMpswd_PASSWORD_DATA_LEN - 2;
    }

    memcpy(work_buf, pswd, key_idx);
    test = pswd + key_idx + 1;
    memcpy(work_buf + key_idx, test, test2 = (mMpswd_PASSWORD_DATA_LEN - 1) - key_idx); // TODO: fakematch
    bzero(buf, count);

    select_idx_table = mMpswd_select_idx_table[pswd[key_idx] & 3];

    for (i = 0; i < count; i++) {
        int bit;

        for (bit = 0; bit < 8; bit++) {
            int dst_idx = i + select_idx_table[bit];

            if (dst_idx >= count) {
                dst_idx -= count;
            }

            buf[i] |= (u8)(((work_buf[dst_idx] >> bit) & 1) << bit);
        }
    }

    memcpy(pswd, buf, key_idx);
    memcpy(test, buf + key_idx, test2);
}

static void mMpswd_chg_common_font_code(u8* pswd) {
    u8 changed_pswd[mMpswd_PASSWORD_STR_LEN];
    int i;

    for (i = 0; i < mMpswd_PASSWORD_STR_LEN; i++) {
        changed_pswd[i] = usable_to_fontnum_new[pswd[i]];
    }

    memcpy(pswd, changed_pswd, mMpswd_PASSWORD_STR_LEN);
}

static u8 mMpswd_chg_password_font_code_sub(u8 c, int version) {
    static u8* fontnum_table_p[] = { usable_to_fontnum, usable_to_fontnum_new };
    u8* fontnum_table;
    int i;
    int res = 0xFF;

    fontnum_table = fontnum_table_p[version];
    for (i = 0; i < 64; i++) {
        u8 chk = *fontnum_table;

        if (chk == c) {
            res = i; // probably should've used a break; here
        }

        fontnum_table++;
    }

    return res;
}

static int mMpswd_chg_password_font_code(u8* pswd, int version) {
    static u32 pword_length_table[] = { mMpswd_OLD_PASSWORD_STR_LEN, mMpswd_PASSWORD_STR_LEN };
    u8 changed_pswd[mMpswd_PASSWORD_STR_LEN];
    u8* changed_pswd_p;
    u8* src_p;
    u32 len;
    int i;
    int res = TRUE;

    len = pword_length_table[version];
    src_p = pswd;
    changed_pswd_p = changed_pswd;
    for (i = 0; i < len; i++) {
        u8 new_code = mMpswd_chg_password_font_code_sub(*src_p, version);

        if (new_code == 0xFF) {
            res = FALSE;
            break;
        }

        src_p++;
        *changed_pswd_p++ = new_code;
    }

    if (res == TRUE) {
        memcpy(pswd, changed_pswd, len);
    }

    return res;
}

extern void mMpswd_make_password(u8* password_buf, int type, int hit_rate, u8* str0, u8* str1, u8* str2,
                                 mActor_name_t item, int npc_type, int npc_code) {
    u8 work_buf[mMpswd_PASSWORD_STR_LEN];
    u8* work_buf_p = work_buf + 1;

    bzero(work_buf, mMpswd_PASSWORD_STR_LEN);
    mMpswd_make_passcode(work_buf_p, type, hit_rate, str0, str1, str2, item, npc_type, npc_code);
    mMpswd_substitution_cipher(work_buf_p);
    mMpswd_transposition_cipher(work_buf_p, 1, 0);
    mMpswd_bit_shuffle(work_buf_p, 0);
    mMpswd_chg_RSA_cipher(work_buf_p);
    mMpswd_bit_mix_code(work_buf_p);
    mMpswd_bit_shuffle(work_buf_p, 1);
    mMpswd_transposition_cipher(work_buf_p, 0, 1);
    mMpswd_chg_6bits_code(password_buf, work_buf_p);
    mMpswd_chg_common_font_code(password_buf);
}

static int mMpswd_old_decode_code(u8* password_data, u8* password_str) {
    u8 work_buf[mMpswd_OLD_PASSWORD_BITS_LEN];
    u8 decoded_data[mMpswd_OLD_PASSWORD_DATA_LEN];
    u8 mix_code;
    int i;
    int ret = FALSE;

    if (mMpswd_chg_password_font_code(password_str, mMpswd_VERSION_OLD) == TRUE) {
        int idx = 0;
        int i;
        int bit;

        for (i = 0; i < mMpswd_OLD_PASSWORD_STR_LEN; i++) {
            for (bit = 5; bit >= 0; bit--) {
                work_buf[idx++] = (password_str[i] >> bit) & 1;
            }
        }

        mMpswd_shift(work_buf, mMpswd_OLD_PASSWORD_BITS_LEN, -15);
        mix_code = (work_buf[0x80] << 3) | (work_buf[0x81] << 2) | (work_buf[0x82] << 1) | (work_buf[0x83] << 0);
        if (mix_code > 12) {
            mMpswd_shift(work_buf, 0x80, -mix_code * 3);
            mMpswd_hanten(work_buf, 0x80);
            mMpswd_reverse(work_buf, 0x80);
        } else if (mix_code > 8) {
            mMpswd_shift(work_buf, 0x80, mix_code * 5);
            mMpswd_reverse(work_buf, 0x80);
        } else if (mix_code > 4) {
            mMpswd_hanten(work_buf, 0x80);
            mMpswd_shift(work_buf, 0x80, mix_code * 5);
        } else {
            mMpswd_reverse(work_buf, 0x80);
            mMpswd_shift(work_buf, 0x80, -mix_code * 3);
        }

        bzero(decoded_data, mMpswd_OLD_PASSWORD_DATA_LEN);
        {
            int idx = 0;
            u8 decoded_byte;
            int i;
            int bit;
            for (i = 0; i < 16; i++) {
                decoded_byte = decoded_data[i];

                for (bit = 7; bit >= 0; bit--) {
                    decoded_byte |= work_buf[idx++] << bit;
                }

                decoded_data[i] = decoded_byte;
            }
        }

        decoded_data[0x10] = mix_code;
        for (i = 0; i < mMpswd_OLD_PASSWORD_DATA_LEN; i++) {
            password_data[i] = decoded_data[i];
        }
        ret = TRUE;
    }

    return ret;
}

extern int mMpswd_new_decode_code(u8* password_data, u8* password_str) {
    u8 work_buf[mMpswd_PASSWORD_STR_LEN];
    int res = FALSE;

    memcpy(work_buf, password_str, mMpswd_PASSWORD_STR_LEN);
    if (mMpswd_chg_password_font_code(work_buf, mMpswd_VERSION_NEW) == TRUE) {
        mMpswd_chg_8bits_code(password_data, work_buf);
        mMpswd_transposition_cipher(password_data, 1, 1);
        mMpswd_decode_bit_shuffle(password_data, 1);
        mMpswd_decode_bit_code(password_data);
        mMpswd_decode_RSA_cipher(password_data);
        mMpswd_decode_bit_shuffle(password_data, 0);
        mMpswd_transposition_cipher(password_data, 0, 0);
        mMpswd_decode_substitution_cipher(password_data);

        res = TRUE;
    }

    return res;
}

extern int mMpswd_restore_code(u8* password, u8* body) {
    u16 conv_buf[MAIL_BODY_LEN];
    u8 password_str[mMpswd_PASSWORD_STR_LEN];
    int res = FALSE;

    mTxt_conv_16bit(body, conv_buf, MAIL_BODY_LEN);
    if (mMpswd_check_opening_sentence(conv_buf) == TRUE) {
        u16* conv_buf_p = conv_buf;
        int version = mMpswd_check_version(&conv_buf_p);
        if (version != mMpswd_VERSION_BAD) {
            mMpswd_except_return_code(password_str, conv_buf_p, version);

            switch (version) {
                case mMpswd_VERSION_OLD:
                    res = mMpswd_old_decode_code(password + 1, password_str);
                    break;
                case mMpswd_VERSION_NEW:
                    res = mMpswd_new_decode_code(password + 1, password_str);
                    break;
            }

            password[0] = version;
        }
    }

    return res;
}

static void mMpswd_old_password(mMpswd_password_c* password, u8* data) {
    int i;

    password->checksum = data[16];
    for (i = 0; i < PLAYER_NAME_LEN; i++) {
        password->str0[i] = data[8 + i];
    }

    for (i = 0; i < PLAYER_NAME_LEN; i++) {
        password->str1[i] = data[2 + i];
    }

    password->item = (data[14] << 8) + data[15];
    password->type = (data[0] >> 6) & 3;

    switch (password->type) {
        case mMpswd_CODETYPE_NPC:
            password->hit_rate_index = 1;
            password->npc_type = data[0] & 1;
            password->npc_code = data[1];
            break;
        case mMpswd_CODETYPE_CARD_E:
            password->hit_rate_index = (data[0] >> 1) & 3;
            password->npc_type = data[0] & 1;
            password->npc_code = data[1];
            break;
        default:
            password->hit_rate_index = data[0] & 0x3F;
            password->npc_type = -1;
            password->npc_code = -1;
            break;
    }
}

static void mMpswd_new_password(mMpswd_password_c* password, u8* data) {
    int b0 = data[0];
    int b1 = data[1];
    int b2 = data[2];
    u32 price;
    u8* str_p;
    u8* str_end;
    int len;
    int digit;
    int i;

    bzero(password, sizeof(mMpswd_password_c));
    password->type = (b0 >> 5) & 7;
    password->checksum = ((b1 >> 6) & 3) | ((b0 & 3) << 2);
    memcpy(password->str0, data + 3, PLAYER_NAME_LEN);
    memcpy(password->str1, data + 9, PLAYER_NAME_LEN);
    memcpy(password->str2, data + 15, PLAYER_NAME_LEN);
    password->item = (data[21] << 8) + data[22];
    password->npc_type = b1 & 3;
    password->npc_code = b2;
    password->_0B = (b1 >> 2) == 0 ? 0 : 1;

    switch (password->type) {
        case mMpswd_CODETYPE_CARD_E:
            password->hit_rate_index = (b0 >> 2) & 3;
            break;

        case mMpswd_CODETYPE_MAGAZINE:
            password->hit_rate_index = (b0 >> 2) & 7;
            break;

        case mMpswd_CODETYPE_MONUMENT:
            password->hit_rate_index = (b0 >> 2) & 7;
            password->bx = b1 & 7;
            password->bz = (b1 >> 3) & 7;

            price = 0;
            digit = 1;
            str_p = password->str2;
            len = mMl_strlen(password->str2, PLAYER_NAME_LEN, CHAR_SPACE);
            str_p += len - 1;
            for (; len != 0; len--) {
                if (!(*str_p >= CHAR_ZERO && *str_p <= CHAR_NINE)) {
#ifndef BUGFIXES
                    *str_p = 0; // @BUG - this should be set to CHAR_ZERO.
#else
                    *str_p = CHAR_ZERO;
#endif
                }

                price += (*str_p - CHAR_ZERO) * digit;
                digit *= 10;
                str_p--;
            }
            password->price = price;
            break;

        default:
            password->hit_rate_index = (b0 >> 2) & 7;
            break;
    }
}

extern void mMpswd_password(mMpswd_password_c* password, u8* data) {
    switch (data[0]) {
        case mMpswd_VERSION_OLD:
            mMpswd_old_password(password, data + 1);
            break;
        case mMpswd_VERSION_NEW:
            mMpswd_new_password(password, data + 1);
            break;
    }

    password->version = data[0];
}

static int mMpswd_check_default_hit_rate(mMpswd_password_c* password) {
    int ret = FALSE;

    switch (password->type) {
        case mMpswd_CODETYPE_MAGAZINE:
            if (password->hit_rate_index <= 4) {
                ret = TRUE;
            }
            break;
        default:
            if (password->hit_rate_index == 4) {
                ret = TRUE;
            }
            break;
    }

    return ret;
}

static int mMpswd_check_default_npc_code(mMpswd_password_c* password) {
    int ret = FALSE;

    switch (password->type) {
        case mMpswd_CODETYPE_FAMICOM:
        case mMpswd_CODETYPE_CARD_E:
        case mMpswd_CODETYPE_MAGAZINE:
        case mMpswd_CODETYPE_USER:
            if (password->npc_type == 0 && password->npc_code == 0xFF) {
                ret = TRUE;
            }
            break;
        case mMpswd_CODETYPE_MONUMENT:
            if (password->npc_code == 0xFF) {
                ret = TRUE;
            }
            break;

        default:
            ret = TRUE;
            break;
    }
    return ret;
}

#if VERSION == VER_GAEJ01_01
static int mMpswd_check_strings(u8* str, int len) {
    int ret = TRUE;
    int i;

    for (i = 0; i < len; i++) {
        // Don't allow control codes or msg tags
        if (*str == CHAR_PP_127 || *str == CHAR_PP_128) {
            ret = FALSE;
            break;
        }
        str++;
    }

    return ret;
}
#endif

static int mMpswd_old_password_zuru_check(mMpswd_password_c* password) {
    u16 checksum = 0;
    int ret = FALSE;
    int i;

    for (i = 0; i < PLAYER_NAME_LEN; i++) {
        checksum += password->str0[i];
    }
    for (i = 0; i < PLAYER_NAME_LEN; i++) {
        checksum += password->str1[i];
    }

    checksum += password->item;

    if (password->type == mMpswd_CODETYPE_NPC || password->type == mMpswd_CODETYPE_CARD_E) {
        checksum += (u16)(password->npc_code + ((u16)password->npc_type << 8));
    }

    if (password->type == mMpswd_CODETYPE_CARD_E) {
        checksum += password->hit_rate_index;
    }

#if VERSION == VER_GAEJ01_01
    if ((checksum % 16) != password->checksum) {
        ret = TRUE;
    } else if (!mMpswd_check_strings(password->str0, PLAYER_NAME_LEN) ||
               !mMpswd_check_strings(password->str1, PLAYER_NAME_LEN)) {
        ret = TRUE;
    }
#else
    if ((checksum % 16) != password->checksum) {
        ret = TRUE;
    }
#endif

    return ret;
}

static int mMpswd_new_password_zuru_check(mMpswd_password_c* password) {
    int cheated = TRUE;

    if (password->type < mMpswd_CODETYPE_NUM && password->type != mMpswd_CODETYPE_CARD_E) {
        u8* str_p;
        int checksum = 0;
        int i;

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += password->str0[i];
        }

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += password->str1[i];
        }

        for (i = 0; i < PLAYER_NAME_LEN; i++) {
            checksum += password->str2[i];
        }

        checksum += password->item;
        checksum += password->npc_code;

#if VERSION == VER_GAEJ01_01
        if ((checksum & 0xF) == password->checksum && mMpswd_check_default_hit_rate(password) == TRUE &&
            mMpswd_check_default_npc_code(password) == TRUE &&
            mMpswd_check_strings(password->str0, PLAYER_NAME_LEN) == TRUE &&
            mMpswd_check_strings(password->str1, PLAYER_NAME_LEN) == TRUE &&
            mMpswd_check_strings(password->str2, PLAYER_NAME_LEN) == TRUE) {
            cheated = FALSE;
        }
#else
        if ((checksum & 0xF) == password->checksum && mMpswd_check_default_hit_rate(password) == TRUE &&
            mMpswd_check_default_npc_code(password) == TRUE) {
            cheated = FALSE;
        }
#endif
    }

    return cheated;
}

extern int mMpswd_password_zuru_check(mMpswd_password_c* password) {
    int ret = TRUE;
    switch (password->version) {
        case mMpswd_VERSION_OLD:
            ret = mMpswd_old_password_zuru_check(password);
            break;
        case mMpswd_VERSION_NEW:
            ret = mMpswd_new_password_zuru_check(password);
            break;
    }
    return ret;
}

extern u32 pswd_present_list_max;
extern u16 pswd_present_list[];

static int mMpswd_old_check_present_other(mActor_name_t item) {
    int ret = FALSE;
    int i;

    if (item == RSV_NO) {
        ret = TRUE;
    }

    // ftr
    for (i = 0; i < pswd_present_list_max; i++) {
        if (item == pswd_present_list[i]) {
            ret = TRUE;
            break;
        }
    }

    // carpet
    for (i = 0; i < 64; i++) {
        if (0x5DC + i == item) {
            ret = TRUE;
            break;
        }
    }

    // wallpaper
    for (i = 0; i < 64; i++) {
        if (0x7D0 + i == item) {
            ret = TRUE;
            break;
        }
    }

    // clothing
    for (i = 0; i < 255; i++) {
        if (i >= 18 && i <= 25) {
            continue;
        }

        if (0x9C4 + i == item) {
            ret = TRUE;
            break;
        }
    }

    return ret;
}

extern u32 pswd_old_famicom_list_max;
extern u16 pswd_old_famicom_list[];

static int mMpswd_old_check_present_famicom(mActor_name_t item) {
    int ret = FALSE;
    int i;

    for (i = 0; i < pswd_old_famicom_list_max; i++) {
        if (item == pswd_old_famicom_list[i]) {
            ret = TRUE;
            break;
        }
    }

    return ret;
}

static int mMpswd_new_check_present_famicom(mActor_name_t item) {
    int i;
    int res = FALSE;

    for (i = 0; i < pswd_famicom_list_max; i++) {
        if (item == mNT_ftr_idx_to_ftr_item_no(pswd_famicom_list[i], 0)) {
            res = TRUE;
            break;
        }
    }

    return res;
}

extern int mMpswd_new_check_present_user(mActor_name_t item) {
    mActor_name_t full_stack_item;
    u32 price = 0;
    int res = FALSE;

    switch (ITEM_NAME_GET_TYPE(item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            if (item >= FTR_CLOTH_START && item <= FTR_CLOTH_END) {
                item = mRmTp_FtrItemNo2Item1ItemNo(item, FALSE);
                if (mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_COMMON, NULL) ||
                    mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_UNCOMMON, NULL) ||
                    mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_RARE, NULL)) {
                    price = mSP_ItemNo2ItemPrice(item);
                }
            } else if (item >= FTR_UMBRELLA_START && item <= FTR_UMBRELLA_END) {
                price = mSP_ItemNo2ItemPrice(mRmTp_FtrItemNo2Item1ItemNo(item, FALSE));
            } else if ( // TODO: furniture index values need to be declared in some header file as defines
                (mNT_ftr_item_no_to_ftr_idx(item) >= FTR_NOG_BALLOON_COMMON0 &&
                 mNT_ftr_item_no_to_ftr_idx(item) <= FTR_NOG_BALLOON_COMMON7) ||                    // balloons
                (item >= FTR_START(FTR_NOG_COLLEGENOTE) && item <= FTR_END(FTR_IKE_NIKKI_WAFU1)) || // diaries
                (mNT_ftr_item_no_to_ftr_idx(item) >= FTR_UTIWA0 &&
                 mNT_ftr_item_no_to_ftr_idx(item) <= FTR_UTIWA7) || // fans
                (mNT_ftr_item_no_to_ftr_idx(item) >= FTR_KAZAGURUMA0 &&
                 mNT_ftr_item_no_to_ftr_idx(item) <= FTR_KAZAGURUMA7) || // pinwheels
                (mNT_ftr_item_no_to_ftr_idx(item) >= FTR_GOLD_ITEM0 &&
                 mNT_ftr_item_no_to_ftr_idx(item) <= FTR_GOLD_ITEM3) || // golden tools
                (mNT_ftr_item_no_to_ftr_idx(item) >= FTR_TOOL0 &&
                 mNT_ftr_item_no_to_ftr_idx(item) <= FTR_TOOL3) ||   // regular tools
                mNT_ftr_item_no_to_ftr_idx(item) == FTR_TOOL_CRACKER // cracker
            ) {
                /* Convert furniture to their item1 variants */
                price = mSP_ItemNo2ItemPrice(mRmTp_FtrItemNo2Item1ItemNo(item, FALSE));
            } else if (mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_COMMON, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_UNCOMMON, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_TRAIN, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_EVENT, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY, NULL) ||
                       mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_EVENTPRESENTCHUMON,
                                                      NULL)) {
                price = mSP_ItemNo2ItemPrice(item);
            }

            break;
        }

        case NAME_TYPE_ITEM1: {
            if (item >= ITM_CLOTH_START && item < ITM_CLOTH_END) {
                if (mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_COMMON, NULL) ||
                    mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_UNCOMMON, NULL) ||
                    mSP_SearchItemCategoryPriority(item, mSP_KIND_CLOTH, mSP_LISTTYPE_RARE, NULL)) {
                    price = mSP_ItemNo2ItemPrice(item);
                }
            } else if (item >= ITM_UMBRELLA00 && item <= ITM_MY_ORG_UMBRELLA7) {
                price = mSP_ItemNo2ItemPrice(item);
            } else if ((item >= ITM_RED_BALLOON && item <= ITM_BUNNY_O_BALLOON) ||
                       (item >= ITM_DIARY00 && item <= ITM_DIARY15) ||
                       (item >= ITM_BLUEBELL_FAN && item <= ITM_LEAF_FAN) ||
                       (item >= ITM_YELLOW_PINWHEEL && item <= ITM_FANCY_PINWHEEL) ||
                       (item >= ITM_GOLDEN_NET && item <= ITM_GOLDEN_ROD) || (item >= ITM_NET && item <= ITM_ROD) ||
                       item == ITM_CRACKER) {
                price = mSP_ItemNo2ItemPrice(item);
            } else {
                switch (ITEM_NAME_GET_CAT(item)) {
                    case ITEM1_CAT_FRUIT: {
                        price = mSP_ItemNo2ItemPrice(item);
                        break;
                    }

                    case ITEM1_CAT_PAPER: {
                        full_stack_item = ITM_PAPER_STACK_FOUR_START + (item & 0x3F);
                        if (mSP_SearchItemCategoryPriority(full_stack_item, mSP_KIND_PAPER, mSP_LISTTYPE_COMMON,
                                                           NULL) ||
                            mSP_SearchItemCategoryPriority(full_stack_item, mSP_KIND_PAPER, mSP_LISTTYPE_UNCOMMON,
                                                           NULL) ||
                            mSP_SearchItemCategoryPriority(full_stack_item, mSP_KIND_PAPER, mSP_LISTTYPE_RARE, NULL)) {
                            price = mSP_ItemNo2ItemPrice(full_stack_item);
                        }

                        break;
                    }

                    case ITEM1_CAT_WALL: {
                        if (mSP_SearchItemCategoryPriority(item, mSP_KIND_WALLPAPER, mSP_LISTTYPE_COMMON, NULL) ||
                            mSP_SearchItemCategoryPriority(item, mSP_KIND_WALLPAPER, mSP_LISTTYPE_UNCOMMON, NULL) ||
                            mSP_SearchItemCategoryPriority(item, mSP_KIND_WALLPAPER, mSP_LISTTYPE_RARE, NULL)) {
                            price = mSP_ItemNo2ItemPrice(item);
                        }

                        break;
                    }

                    case ITEM1_CAT_CARPET: {
                        if (mSP_SearchItemCategoryPriority(item, mSP_KIND_CARPET, mSP_LISTTYPE_COMMON, NULL) ||
                            mSP_SearchItemCategoryPriority(item, mSP_KIND_CARPET, mSP_LISTTYPE_UNCOMMON, NULL) ||
                            mSP_SearchItemCategoryPriority(item, mSP_KIND_CARPET, mSP_LISTTYPE_RARE, NULL)) {
                            price = mSP_ItemNo2ItemPrice(item);
                        }

                        break;
                    }
                }
            }

            break;
        }
    }

    if (price != 0) {
        res = TRUE;
    }

    return res;
}

static int mMpswd_new_check_present_monument(mMpswd_password_c* password) {
    int ret = FALSE;

    if (IS_ITEM_MONUMENT(password->item)) {
        ret = TRUE;
    } else {
        mActor_name_t monument = password->item + MONUMENT_PARK_CLOCK;

        if (IS_ITEM_MONUMENT(monument)) {
            password->item = monument;
            ret = TRUE;
        }
    }

    return ret;
}

static int mMpswd_new_check_present_other(mActor_name_t item) {
    int res = FALSE;

    switch (ITEM_NAME_GET_TYPE(item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            switch (mRmTp_FurnitureIdx2FurnitureKind(mNT_ftr_item_no_to_ftr_idx(item))) {
                case mRmTp_BIRTH_TYPE_FTR_CLOTH:
                case mRmTp_BIRTH_TYPE_FTR_UMBRELLA:
                case mRmTp_BIRTH_TYPE_FTR_INSECT:
                case mRmTp_BIRTH_TYPE_FTR_FISH:
                case mRmTp_BIRTH_TYPE_UNOBTAINABLE:
                case mRmTp_BIRTH_TYPE_FAMICOM_EREADER:
                case mRmTp_BIRTH_TYPE_MY_ORIGINAL:
                case mRmTp_BIRTH_TYPE_FAMICOM_CODE:
                case mRmTp_BIRTH_TYPE_FTR_DIARY: {
                    break;
                }

                default: {
                    res = TRUE;
                    break;
                }
            }

            break;
        }

        case NAME_TYPE_ITEM1: {
            switch (ITEM_NAME_GET_CAT(item)) {
                case ITEM1_CAT_TOOL: {
                    /* allow umbrellas */
                    if (item >= ITM_UMBRELLA00 && item <= ITM_UMBRELLA31) {
                        res = TRUE;
                        break;
                    }

                    /* allow balloons */
                    if ((item >= ITM_RED_BALLOON && item <= ITM_BUNNY_O_BALLOON) == TRUE) {
                        res = TRUE;
                        break;
                    }

                    /* allow fans */
                    if ((item >= ITM_BLUEBELL_FAN && item <= ITM_LEAF_FAN) == TRUE) {
                        res = TRUE;
                        break;
                    }

                    /* allow pinwheels */
                    if ((item >= ITM_YELLOW_PINWHEEL && item <= ITM_FANCY_PINWHEEL) == TRUE) {
                        res = TRUE;
                        break;
                    }

                    /* allow crackers */
                    if (item == ITM_CRACKER) {
                        res = TRUE;
                        break;
                    }

                    break;
                }

                case ITEM1_CAT_PAPER: {
                    int amount = item - ITM_PAPER_START;
                    if (amount / 64 + 1 >= 4) {
                        res = TRUE; // Paper in stacks of 4
                    }

                    break;
                }

                case ITEM1_CAT_FISH: {
                    /* fish are not allowed */
                    break;
                }

                case ITEM1_CAT_INSECT: {
                    /* insects are not allowed */
                    break;
                }

                default: {
                    /* allow everything else in the 2XXX range through */
                    res = TRUE;
                    break;
                }
            }
            break;
        }
    }

    return res;
}

extern int mMpswd_check_present(mMpswd_password_c* password) {
    int valid = FALSE;

    switch (password->version) {
        case mMpswd_VERSION_OLD: {
            switch (password->type) {
                case mMpswd_CODETYPE_FAMICOM: {
                    valid = mMpswd_old_check_present_famicom(password->item);
                    break;
                }

                default: {
                    valid = mMpswd_old_check_present_other(password->item);
                    break;
                }
            }
            break;
        }
        case mMpswd_VERSION_NEW: {
            if (password->item == RSV_NO) {
                valid = TRUE;
            } else {
                switch (password->type) {
                    case mMpswd_CODETYPE_FAMICOM: {
                        valid = mMpswd_new_check_present_famicom(password->item);
                        break;
                    }

                    case mMpswd_CODETYPE_USER: {
                        valid = mMpswd_new_check_present_user(password->item);
                        break;
                    }

                    case mMpswd_CODETYPE_MONUMENT: {
                        valid = mMpswd_new_check_present_monument(password);
                        break;
                    }

                    default: {
                        valid = mMpswd_new_check_present_other(password->item);
                        break;
                    }
                }
            }
        }
    }

    return valid;
}

extern mActor_name_t mMpswd_get_sp_npc_num(int sp_npc) {
    static mActor_name_t sp_npc_code_table[mMpswd_SPECIAL_NPC_NUM] = {
        SP_NPC_SHOP_MASTER,    // Tom Nook
        SP_NPC_ARTIST,         // Wendell
        SP_NPC_CARPETPEDDLER,  // Saharah
        SP_NPC_DESIGNER,       // Gracie
        SP_NPC_KABUPEDDLER,    // Joan
        SP_NPC_GYPSY,          // Katrina
        SP_NPC_POLICE,         // Copper
        SP_NPC_HALLOWEEN,      // Jack
        SP_NPC_SANTA,          // Jingle
        SP_NPC_POST_MAN,       // Pete
        SP_NPC_POST_GIRL,      // Pelly
        SP_NPC_POST_GIRL2,     // Phyllis
        SP_NPC_GUIDE,          // Rover
        SP_NPC_TOTAKEKE,       // K.K. Slider
        SP_NPC_ANGLER,         // Chip
        SP_NPC_POLICE2,        // Booker
        SP_NPC_MAMEDANUKI0,    // Timmy
        SP_NPC_MAMEDANUKI1,    // Tommy
        SP_NPC_BROKER,         // Redd
        SP_NPC_MAJIN,          // Resetti
        SP_NPC_EV_DOZAEMON,    // Gulliver
        SP_NPC_STATION_MASTER, // Porter
        SP_NPC_CURATOR,        // Blathers
        SP_NPC_SENDO,          // Kapp'n
        SP_NPC_NEEDLEWORK0,    // Mable
        SP_NPC_NEEDLEWORK1,    // Sable
        SP_NPC_EV_SONCHO,      // Tortimer
        SP_NPC_EV_GHOST,       // Wisp
        SP_NPC_MAJIN_BROTHER,  // Don
        SP_NPC_MASK_CAT,       // Blanca
        SP_NPC_TURKEY,         // Franklin
        SP_NPC_HEM,            // Farley
    };

    if (sp_npc < 0 || sp_npc >= mMpswd_SPECIAL_NPC_NUM) {
        sp_npc = 0;
    }

    return sp_npc_code_table[sp_npc];
}

extern int mMpswd_check_npc_code(mMpswd_password_c* password) {
    int res = FALSE;

    if ((password->npc_type == mMpswd_NPCTYPE_NORMAL && password->npc_code < NPC_ROM_NUM) ||
        (password->npc_type == mMpswd_NPCTYPE_SPECIAL && password->npc_code < mMpswd_SPECIAL_NPC_NUM) ||
        (password->npc_type == mMpswd_NPCTYPE_ADD_NPC)) {
        res = TRUE;
    }

    return res;
}

extern int mMpswd_check_name(mMpswd_password_c* password) {
    int res = FALSE;

    if (mLd_CheckCmpLandName(password->str0, Now_Private->player_ID.land_name) == TRUE) {
        if (mPr_CheckCmpPlayerName(password->str1, Now_Private->player_ID.player_name) == TRUE) {
            res = TRUE;
        }
    }

    return res;
}

extern void mMpswd_ClearHPMail(AnmHPMail_c* hp_mail, int count) {
    bzero(hp_mail, count * sizeof(AnmHPMail_c));
}

extern void mMpswd_AllClearHPMailPlayerIdx(int idx) {
    Animal_c* animal = Save_Get(animals);
    int i;

    if (idx >= 0 && idx < PLAYER_NUM) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            mMpswd_ClearHPMail(&animal->hp_mail[idx], 1);
            animal++;
        }
    }
}

extern int mMpswd_ReceiveHPMail(Mail_c* mail) {
    static u8 password[mMpswd_PASSWORD_DATA_LEN + 1];
    Animal_c* animal = Save_Get(animals);
    AnmPersonalID_c anm_id;
    int ret = FALSE;
    int private_idx = mPr_GetPrivateIdx(&mail->header.sender.personalID);

    if (mail->header.sender.type == mMl_NAME_TYPE_PLAYER && private_idx >= 0 && private_idx < PLAYER_NUM) {
        if (mMpswd_restore_code(password, mail->content.text.split.body) == TRUE &&
            mMl_get_npcinfo_from_mail_name(&anm_id, &mail->header.recipient) == TRUE) {
            int npc_idx = mNpc_SearchAnimalinfo(animal, anm_id.npc_id, ANIMAL_NUM_MAX);

            if (npc_idx != -1) {
                animal = &animal[npc_idx];

                if (animal != NULL) {
                    bcopy(password, animal->hp_mail[private_idx].password, mMpswd_PASSWORD_DATA_LEN + 1);
                    lbRTC_TimeCopy(&animal->hp_mail[private_idx].receive_time, Common_GetPointer(time.rtc_time));
                    ret = TRUE;
                }
            }
        }
    }

    return ret;
}

static int mMpswd_CheckHit_Rate(u8 hitrate, int n) {
    u8 perfect_bit = 0xFF;
    int res = FALSE;
    int i;

    for (i = 0; i < n; i++) {
        perfect_bit &= ~(1 << i);
    }

    if ((hitrate & perfect_bit) == 0) {
        res = TRUE;
    }

    return res;
}

static int mMpswd_GetHit_magazine(u8 hitrate) {
    static float chk_rate[] = { 0.8f, 0.6f, 0.3f };
    int res = FALSE;

    switch (hitrate) {
        case 4: // always win
            res = TRUE;
            break;
        default:
            if (hitrate < ARRAY_COUNT(chk_rate)) {
                if (RANDOM_F(1.0f) <= chk_rate[hitrate]) {
                    res = TRUE;
                }
            }
            break;
        case 3: // always fail
            break;
    }

    return res;
}

static int mMpswd_GetHit_cardE(u8 hitrate) {
    static float chk_rate[] = { 0.8f, 0.6f, 0.4f, 0.2f };

    int res = FALSE;

    if (hitrate < ARRAY_COUNT(chk_rate)) {
        float hit = RANDOM_F(1.0f);

        if (hit <= chk_rate[hitrate]) {
            res = TRUE;
        }
    }

    return res;
}

static void mMpswd_get_gobi_str_from_name(u8* str, mActor_name_t npc_id) {
    if (str != NULL && ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        int idx = npc_id & 0xFFF;

/* @BUG - devs used && instead of || */
#ifndef BUGFIXES
        if (idx < 0 && idx >= NPC_ROM_NUM) {
#else
        if (idx < 0 || idx >= NPC_ROM_NUM) {
#endif
            idx = 0;
        }

        mString_Load_StringFromRom(str, ANIMAL_CATCHPHRASE_LEN, npc_def_list[idx].catchphrase_str_idx);
    }
}

static mActor_name_t mMpswd_get_pw_npc_name(mMpswd_password_c* password) {
    mActor_name_t ret = EMPTY_NO;

    switch (password->npc_type) {
        case mMpswd_NPCTYPE_NORMAL:
            ret = NPC_START | password->npc_code;
            break;
        case mMpswd_NPCTYPE_SPECIAL:
            ret = mMpswd_get_sp_npc_num(password->npc_code);
            break;
        case mMpswd_NPCTYPE_ADD_NPC:
            ret = NPC_ADD_START | password->npc_code; // Probably should be + not |
            break;
    }

    return ret;
}

static int mMpswd_get_pw_npc_looks(mMpswd_password_c* password) {
    int ret = mNpc_LOOKS_GIRL;

    switch (password->npc_type) {
        case mMpswd_NPCTYPE_NORMAL:
        case mMpswd_NPCTYPE_SPECIAL: // @BUG - special NPCs are not handled correctly
            ret = mNpc_GetLooks(NPC_START + password->npc_code);
            break;
        case mMpswd_NPCTYPE_ADD_NPC:
            ret = password->_0B;
            break;
    }

    return ret;
}

static int mMpswd_get_receive_npc_num(mActor_name_t npc_name) {
    int ret = -1;

    if (ITEM_NAME_GET_TYPE(npc_name) == NAME_TYPE_NPC) {
        if (IS_NPC_ADD_NPC(npc_name)) {
            ret = npc_name - NPC_ADD_START;
        } else {
            ret = npc_name & 0xFFF;
        }
    }

    return ret;
}

static void mMpswd_set_npc_name_str(u8* name_str, mActor_name_t npc_name, mMpswd_password_c* password) {
    if (name_str != NULL) {
        switch (ITEM_NAME_GET_TYPE(npc_name)) {
            case NAME_TYPE_NPC:
                if (IS_NPC_ADD_NPC(npc_name)) {
                    mem_copy(name_str, password->str2, ANIMAL_NAME_LEN);
                } else {
                    mNpc_GetNpcWorldNameTableNo(name_str, npc_name);
                }
                break;

            case NAME_TYPE_SPNPC:
                mNpc_GetActorWorldName(name_str, npc_name);
                break;
        }
    }
}

static int mMpswd_check_memory_village(mActor_name_t npc_name) {
    int idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_name, ANIMAL_NUM_MAX);

    // @BUG - whoopsies (devs checked == -1 instead of != -1, leads to invalid animal access)
#ifndef BUGFIXES
    if (idx == -1) {
#else
    if (idx != -1) {
#endif
        idx = mNpc_GetAnimalMemoryIdx(&Now_Private->player_ID, Save_Get(animals[idx]).memories, ANIMAL_MEMORY_NUM);
    }

    return idx;
}

static int mMpswd_check_memory_island(mActor_name_t npc_name) {
    int idx = mNpc_SearchIslandAnimalinfo(npc_name, 0xFF);

    // They managed to get the check right here
    if (idx != -1) {
        idx = mNpc_GetAnimalMemoryIdx(&Now_Private->player_ID, Save_Get(homes[idx]).island.animal.memories,
                                      ANIMAL_MEMORY_NUM);
    }

    return idx;
}

static void mMpswd_check_memory(int* village_mem_idx, int* island_mem_idx, mActor_name_t npc_name) {
    *village_mem_idx = -1;
    *island_mem_idx = -1;

    // Not sure why they gate against searching for DLC NPCs,
    // they could've included the card ID to check for.
    if (!IS_NPC_ADD_NPC(npc_name)) {
        *village_mem_idx = mMpswd_check_memory_village(npc_name);

        if (*village_mem_idx == -1) {
            *island_mem_idx = mMpswd_check_memory_island(npc_name);
        }
    }
}

static int mMpswd_get_send_type_famicom(mMpswd_password_c* password, Animal_c* animal) {
    int hit_rate = 1;
    int ret = mMpswd_SEND_TYPE_NG;

    if (password->version == mMpswd_VERSION_NEW) {
        hit_rate = 4;
    }

    if (password->hit_rate_index == hit_rate && mMpswd_password_zuru_check(password) == FALSE &&
        mMpswd_check_present(password) == TRUE && mMpswd_check_name(password) == TRUE) {
        if (password->version == mMpswd_VERSION_OLD) {
            ret = mMpswd_SEND_TYPE_OLD_CORRECT;
        } else {
            ret = mMpswd_SEND_TYPE_CORRECT;
        }
    }

    return ret;
}

static int mMpswd_get_send_type_npc(mMpswd_password_c* password, Animal_c* animal) {
    int ret = mMpswd_SEND_TYPE_NG;

    if (mMpswd_password_zuru_check(password) == FALSE && mMpswd_check_npc_code(password) == TRUE &&
        mMpswd_check_present(password) == TRUE && mMpswd_check_name(password) == TRUE) {
        if (password->version == mMpswd_VERSION_OLD) {
            ret = mMpswd_SEND_TYPE_OLD_CORRECT;
        } else {
            ret = mMpswd_SEND_TYPE_CORRECT;
        }
    }

    return ret;
}

static int mMpswd_get_send_type_cardE(mMpswd_password_c* password, Animal_c* animal) {
    int ret = mMpswd_SEND_TYPE_NG;

    if (password->npc_type != mMpswd_NPCTYPE_ADD_NPC && mMpswd_password_zuru_check(password) == FALSE &&
        mMpswd_check_present(password) == TRUE && mMpswd_check_npc_code(password) == TRUE) {
        if (password->version == mMpswd_VERSION_OLD) {
            ret = mMpswd_SEND_TYPE_OLD_CORRECT;
        } else {
            ret = mMpswd_SEND_TYPE_CORRECT;
        }
    }

    return ret;
}

static int mMpswd_get_send_type_magazine(mMpswd_password_c* password, Animal_c* animal) {
    int ret = mMpswd_SEND_TYPE_NG;

    if (mMpswd_CheckHit_Rate(password->hit_rate_index, 3) == TRUE && mMpswd_password_zuru_check(password) == FALSE &&
        mMpswd_check_present(password) == TRUE) {
        if (password->version == mMpswd_VERSION_OLD) {
            ret = mMpswd_SEND_TYPE_OLD_CORRECT;
        } else {
            ret = mMpswd_SEND_TYPE_CORRECT;
        }
    }

    return ret;
}

static int mMpswd_get_send_type_user(mMpswd_password_c* password, Animal_c* animal) {
    int ret = mMpswd_SEND_TYPE_NG;

    if (mMpswd_password_zuru_check(password) == FALSE && mMpswd_check_present(password) == TRUE &&
        mMpswd_check_name(password) == TRUE && (int)animal->id.looks < mNpc_LOOKS_NUM) {
        if (password->version == mMpswd_VERSION_OLD) {
            ret = mMpswd_SEND_TYPE_OLD_CORRECT;
        } else {
            ret = mMpswd_SEND_TYPE_CORRECT;
        }
    }

    return ret;
}

static int mMpswd_get_send_type_cardE_mini(mMpswd_password_c* password, Animal_c* animal) {
    int ret = mMpswd_SEND_TYPE_NG;

    if (mMpswd_password_zuru_check(password) == FALSE && (int)animal->id.looks < mNpc_LOOKS_NUM) {
        if (password->version == mMpswd_VERSION_OLD) {
            ret = mMpswd_SEND_TYPE_OLD_CORRECT;
        } else {
            ret = mMpswd_SEND_TYPE_CORRECT;
        }
    }

    return ret;
}

static int mMpswd_get_send_type_new_npc(mMpswd_password_c* password, Animal_c* animal) {
    int ret = mMpswd_SEND_TYPE_NG;

    if (mMpswd_password_zuru_check(password) == FALSE && mMpswd_check_present(password) == TRUE &&
        mMpswd_check_name(password) == TRUE && (int)password->_0B < mNpc_LOOKS_NUM) {
        if (password->version == mMpswd_VERSION_OLD) {
            ret = mMpswd_SEND_TYPE_OLD_CORRECT;
        } else {
            ret = mMpswd_SEND_TYPE_CORRECT;
        }
    }

    return ret;
}

typedef int (*mMpswd_GET_SEND_TYPE_PROC)(mMpswd_password_c* password, Animal_c* animal);

static int mMpswd_get_send_type(mMpswd_password_c* password, Animal_c* animal) {
    static mMpswd_GET_SEND_TYPE_PROC get_send_type_proc[] = {
        &mMpswd_get_send_type_famicom,  &mMpswd_get_send_type_npc,        &mMpswd_get_send_type_cardE,
        &mMpswd_get_send_type_magazine, &mMpswd_get_send_type_user,       &mMpswd_get_send_type_cardE_mini,
        &mMpswd_get_send_type_new_npc,  &mMpswd_get_send_type_cardE_mini,
    };
    int ret = mMpswd_SEND_TYPE_NG;

    if (password->type < mMpswd_CODETYPE_NUM) {
        ret = (*get_send_type_proc[password->type])(password, animal);
    }

    return ret;
}

// Rev1 adds an optional flag to set the free strings
#if VERSION == VER_GAEJ01_01
static void mMpswd_make_send_mail_common(Mail_c* mail, mMpswd_password_c* password, PersonalID_c* pid,
                                         Animal_c* animal, int mail_no, u8* name_str, u8* submenu_name_str,
                                         mActor_name_t present, int set_exchange_name, int set_strings) {
    static int exchange_name_str_flg[] = { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE };
    u8 item_name_str[mIN_ITEM_NAME_LEN];
    u8 animal_name_str[ANIMAL_NAME_LEN];

    mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
    if (name_str != NULL) {
        mHandbill_Set_free_str(mHandbill_FREE_STR1, name_str, ANIMAL_NAME_LEN);
    }

    if (set_strings == TRUE) {
        mHandbill_Set_free_str(mHandbill_FREE_STR2, password->str0, PLAYER_NAME_LEN);
        mHandbill_Set_free_str(mHandbill_FREE_STR3, password->str1, PLAYER_NAME_LEN);
    }

    if (present != EMPTY_NO) {
        mem_clear(item_name_str, mIN_ITEM_NAME_LEN, CHAR_SPACE);
        mIN_copy_name_str(item_name_str, present);
        mHandbill_Set_free_str(mHandbill_FREE_STR4, item_name_str, mIN_ITEM_NAME_LEN);
    }
    //
    mem_clear(animal_name_str, ANIMAL_NAME_LEN, CHAR_SPACE);
    mNpc_GetNpcWorldNameAnm(animal_name_str, &animal->id);
    mHandbill_Set_free_str(mHandbill_FREE_STR6, animal_name_str, ANIMAL_NAME_LEN);

    mNpc_LoadMailDataCommon2(mail, pid, &animal->id, present, mNpc_GetPaperType(), mail_no);

    if (set_exchange_name == TRUE && exchange_name_str_flg[password->type] == TRUE) {
        if (submenu_name_str != NULL) {
            bcopy(submenu_name_str, mail->header.sender.personalID.player_name, PLAYER_NAME_LEN);
        }

        bcopy(pid->player_name, mail->header.recipient.personalID.player_name, PLAYER_NAME_LEN);

        if (password->npc_type == mMpswd_NPCTYPE_SPECIAL) {
            mail->content.mail_type = mMl_TYPE_SPNPC_PASSWORD;
        }
    }
}
#else
static void mMpswd_make_send_mail_common(Mail_c* mail, mMpswd_password_c* password, PersonalID_c* pid,
                                         Animal_c* animal, int mail_no, u8* name_str, u8* submenu_name_str,
                                         mActor_name_t present, int set_exchange_name) {
    static int exchange_name_str_flg[] = { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE };
    u8 item_name_str[mIN_ITEM_NAME_LEN];
    u8 animal_name_str[ANIMAL_NAME_LEN];

    mHandbill_Set_free_str(mHandbill_FREE_STR0, pid->player_name, PLAYER_NAME_LEN);
    if (name_str != NULL) {
        mHandbill_Set_free_str(mHandbill_FREE_STR1, name_str, ANIMAL_NAME_LEN);
    }

    mHandbill_Set_free_str(mHandbill_FREE_STR2, password->str0, PLAYER_NAME_LEN);
    mHandbill_Set_free_str(mHandbill_FREE_STR3, password->str1, PLAYER_NAME_LEN);

    if (present != EMPTY_NO) {
        mem_clear(item_name_str, mIN_ITEM_NAME_LEN, CHAR_SPACE);
        mIN_copy_name_str(item_name_str, present);
        mHandbill_Set_free_str(mHandbill_FREE_STR4, item_name_str, mIN_ITEM_NAME_LEN);
    }

    mem_clear(animal_name_str, ANIMAL_NAME_LEN, CHAR_SPACE);
    mNpc_GetNpcWorldNameAnm(animal_name_str, &animal->id);
    mHandbill_Set_free_str(mHandbill_FREE_STR6, animal_name_str, ANIMAL_NAME_LEN);

    mNpc_LoadMailDataCommon2(mail, pid, &animal->id, present, mNpc_GetPaperType(), mail_no);

    if (set_exchange_name == TRUE && exchange_name_str_flg[password->type] == TRUE) {
        if (submenu_name_str != NULL) {
            bcopy(submenu_name_str, mail->header.sender.personalID.player_name, PLAYER_NAME_LEN);
        }

        bcopy(pid->player_name, mail->header.recipient.personalID.player_name, PLAYER_NAME_LEN);

        if (password->npc_type == mMpswd_NPCTYPE_SPECIAL) {
            mail->content.mail_type = mMl_TYPE_SPNPC_PASSWORD;
        }
    }
}
#endif

static void mMpswd_make_send_mail_famicom(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
                                          mMpswd_password_c* password, Animal_c* animal) {
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);
    *mail_no = 0x24A + animal->id.looks;
    *present = password->item;
}

static void mMpswd_make_send_mail_npc(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
                                      mMpswd_password_c* password, Animal_c* animal) {
    mActor_name_t npc_name;
    int receive_npc_num;
    int looks;
    int npc_type;
    int idx;

    npc_name = mMpswd_get_pw_npc_name(password);
    mMpswd_set_npc_name_str(name_str, npc_name, password);
    mem_copy(submenu_name_str, name_str, 6);

    if (password->npc_type == mMpswd_NPCTYPE_NORMAL) {
        npc_type = mMpswd_NPCTYPE_NORMAL;
        if (IS_NPC_ADD_NPC(animal->id.npc_id)) {
            npc_type = mMpswd_NPCTYPE_ADD_NPC;
        }

        receive_npc_num = mMpswd_get_receive_npc_num(animal->id.npc_id);
        looks = mMpswd_get_pw_npc_looks(password);

        if (npc_type == mMpswd_NPCTYPE_NORMAL && receive_npc_num == password->npc_code) {
            *mail_no = looks + 0x256;
        } else if (mNpc_CheckIslandAnimalTableNo(npc_name) == TRUE) {
            *mail_no = looks + 0x262;
        } else {
            *mail_no = looks + 0x25C;
        }
    } else if (password->npc_type == mMpswd_NPCTYPE_SPECIAL) {
        *mail_no = password->npc_code + 0x268;
        // replace さん (-san) with spaces
        if (submenu_name_str[4] == CHAR_PP_010 && submenu_name_str[5] == CHAR_PP_195) {
            submenu_name_str[4] = CHAR_SPACE;
            submenu_name_str[5] = CHAR_SPACE;
        }
    } else if (password->npc_type == mMpswd_NPCTYPE_ADD_NPC) {
        mActor_name_t actor_id = animal->id.npc_id;

        npc_type = mMpswd_NPCTYPE_NORMAL;
        if (IS_NPC_ADD_NPC(actor_id)) {
            npc_type = mMpswd_NPCTYPE_ADD_NPC;
        }

        idx = actor_id & 0xFFF;
#if VERSION == VER_GAEJ01_01
        looks = mMpswd_get_pw_npc_looks(password);
#else
        looks = mNpc_GetLooks(npc_name);
#endif
        if (npc_type == mMpswd_NPCTYPE_ADD_NPC && idx == (u16)password->npc_code) {
            *mail_no = looks + 0x256;
        } else if (mNpc_CheckIslandAnimalTableNo(npc_name) == TRUE) {
            *mail_no = looks + 0x262;
        } else {
            *mail_no = looks + 0x25C;
        }
    }

    if (password->item != RSV_NO) {
        *present = password->item;
    }
}


static void mMpswd_make_send_mail_cardE(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
                                      mMpswd_password_c* password, Animal_c* animal) {
    static u8 gobi_str[ANIMAL_CATCHPHRASE_LEN];
    mActor_name_t npc_name;
    int village_mem_idx;
    int island_mem_idx;
    int hit_card_e;
    int looks;
    int hit_famicom;
    int famicom_idx;
    int check_present;

    (void)animal;

    hit_famicom = FALSE;
    mem_clear(gobi_str, 4, CHAR_SPACE);

    npc_name = mMpswd_get_pw_npc_name(password);
    mMpswd_set_npc_name_str(name_str, npc_name, password);
    mem_copy(submenu_name_str, name_str, 6);

    if (password->npc_type == mMpswd_NPCTYPE_NORMAL) {
        mMpswd_check_memory(&village_mem_idx, &island_mem_idx, npc_name);
        if (village_mem_idx != -1 || island_mem_idx != -1) {
            hit_card_e = mMpswd_GetHit_cardE(password->hit_rate_index);
            if (hit_card_e != FALSE) {
                looks = mMpswd_get_pw_npc_looks(password);
                hit_famicom = TRUE;
                if (island_mem_idx != -1) {
                    *mail_no = looks + 0x3CA;
                } else {
                    *mail_no = looks + 0x3C4;
                }
            }
        }

        if (hit_famicom == FALSE) {
            *mail_no = password->npc_code + 0x2B2;
        }

        mMpswd_get_gobi_str_from_name(gobi_str, npc_name);
        mHandbill_Set_free_str(mHandbill_FREE_STR5, gobi_str, 4);
    } else {
        *mail_no = password->npc_code + 0x39E;
        if (submenu_name_str[4] == 0x0A && submenu_name_str[5] == 0xC3) {
            submenu_name_str[4] = CHAR_SPACE;
            submenu_name_str[5] = CHAR_SPACE;
        }
    }

    if (hit_famicom == TRUE) {
        famicom_idx = (int)RANDOM_F(8.0f);
        *present = mNT_ftr_idx_to_ftr_item_no(pswd_famicom_list[famicom_idx], 0);
    } else {
        check_present = mMpswd_check_present(password);
        if (check_present == TRUE && password->item != RSV_NO) {
            *present = password->item;
        }
    }
}

static void mMpswd_make_send_mail_magazine(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);

    if (mMpswd_GetHit_magazine(password->hit_rate_index) == TRUE) {
        *mail_no = 0x2A0 + animal->id.looks;

        if (password->item != RSV_NO) {
            *present = password->item;
        }
    } else {
        *mail_no = 0x2A6 + animal->id.looks;
    }
}

static void mMpswd_make_send_mail_user(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    *mail_no = 0x3D0 + animal->id.looks;
}

static void mMpswd_make_send_mail_new_npc(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);
    mem_copy(submenu_name_str, name_str, ANIMAL_NAME_LEN);
    *mail_no = 0x3D0 + animal->id.looks;
}

typedef void (*mMpswd_MAKE_SEND_MAIL_PROC)(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str, 
    mMpswd_password_c* password, Animal_c* animal);

static void mMpswd_make_send_mail_correct(Mail_c* mail, mMpswd_password_c* password, PersonalID_c* pid, Animal_c* animal) {
    static mMpswd_MAKE_SEND_MAIL_PROC make_send_mail_proc[mMpswd_CODETYPE_NUM] = {
        &mMpswd_make_send_mail_famicom,
        &mMpswd_make_send_mail_npc,
        &mMpswd_make_send_mail_cardE,
        &mMpswd_make_send_mail_magazine,
        &mMpswd_make_send_mail_user,
        &mMpswd_make_send_mail_user,
        &mMpswd_make_send_mail_new_npc,
        &mMpswd_make_send_mail_user,
    };

    static u8 name_str[ANIMAL_NAME_LEN];
    static u8 submenu_name_str[ANIMAL_NAME_LEN];
    int mail_no;
    mActor_name_t present = EMPTY_NO;

    mem_clear(name_str, ANIMAL_NAME_LEN, CHAR_SPACE);
    mem_clear(submenu_name_str, ANIMAL_NAME_LEN, CHAR_SPACE);
    (*make_send_mail_proc[password->type])(&mail_no, &present, name_str, submenu_name_str, password, animal);
#if VERSION == VER_GAEJ01_01
    mMpswd_make_send_mail_common(mail, password, pid, animal, mail_no, name_str, submenu_name_str, present, TRUE, TRUE);
#else
    mMpswd_make_send_mail_common(mail, password, pid, animal, mail_no, name_str, submenu_name_str, present, TRUE);
#endif
}

static void mMpswd_make_send_mail_NG_famicom(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);
    *mail_no = 0x250 + animal->id.looks;
}

static void mMpswd_make_send_mail_NG_npc(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);
    *mail_no = 0x288 + animal->id.looks;
}

static void mMpswd_make_send_mail_NG_cardE(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);
    *mail_no = 0x3BE + animal->id.looks;
}

static void mMpswd_make_send_mail_NG_magazine(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);
    *mail_no = 0x2AC + animal->id.looks;
}

static void mMpswd_make_send_mail_NG_common(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);
    *mail_no = 0x3BE + animal->id.looks;
}

static void mMpswd_make_send_mail_NG(Mail_c* mail, mMpswd_password_c* password, PersonalID_c* pid, Animal_c* animal) {
    static mMpswd_MAKE_SEND_MAIL_PROC make_send_mail_proc[mMpswd_CODETYPE_NUM] = {
        &mMpswd_make_send_mail_NG_famicom,
        &mMpswd_make_send_mail_NG_npc,
        &mMpswd_make_send_mail_NG_cardE,
        &mMpswd_make_send_mail_NG_magazine,
        &mMpswd_make_send_mail_NG_common,
        &mMpswd_make_send_mail_NG_common,
        &mMpswd_make_send_mail_NG_common,
        &mMpswd_make_send_mail_NG_common,
    };

    static u8 name_str[ANIMAL_NAME_LEN];
    static u8 submenu_name_str[ANIMAL_NAME_LEN];
    int mail_no;

    mem_clear(name_str, ANIMAL_NAME_LEN, CHAR_SPACE);
    mem_clear(submenu_name_str, ANIMAL_NAME_LEN, CHAR_SPACE);

    if (password->type >= mMpswd_CODETYPE_NUM) {
        mMpswd_make_send_mail_NG_common(&mail_no, NULL, name_str, submenu_name_str, password, animal);
    } else {
        (*make_send_mail_proc[password->type])(&mail_no, NULL, name_str, submenu_name_str, password, animal);
    }
#if VERSION == VER_GAEJ01_01
    mMpswd_make_send_mail_common(mail, password, pid, animal, mail_no, name_str, submenu_name_str, EMPTY_NO, FALSE, FALSE);
#else
    mMpswd_make_send_mail_common(mail, password, pid, animal, mail_no, name_str, submenu_name_str, EMPTY_NO, FALSE);
#endif
}

static void mMpswd_make_send_mail_old_correct_famicom(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    static u8 gobi_str[ANIMAL_CATCHPHRASE_LEN];
    
    mem_clear(gobi_str, ANIMAL_CATCHPHRASE_LEN, CHAR_SPACE);
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);
    mem_copy(submenu_name_str, name_str, ANIMAL_NAME_LEN);
    *mail_no = 0x250 + animal->id.looks;
    mem_copy(gobi_str, animal->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    mHandbill_Set_free_str(mHandbill_FREE_STR5, gobi_str, ANIMAL_CATCHPHRASE_LEN);
}

static void mMpswd_make_send_mail_old_correct_magazine(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
    mMpswd_password_c* password, Animal_c* animal) {
    static u8 gobi_str[ANIMAL_CATCHPHRASE_LEN];
    
    mem_clear(gobi_str, ANIMAL_CATCHPHRASE_LEN, CHAR_SPACE);
    mNpc_GetNpcWorldNameAnm(name_str, &animal->id);
    mem_copy(submenu_name_str, name_str, ANIMAL_NAME_LEN);
    *mail_no = 0x2AC + animal->id.looks;
    mem_copy(gobi_str, animal->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    mHandbill_Set_free_str(mHandbill_FREE_STR5, gobi_str, ANIMAL_CATCHPHRASE_LEN);
}

static void mMpswd_make_send_mail_old_correct_npc(int* mail_no, mActor_name_t* present, u8* name_str, u8* submenu_name_str,
                                                 mMpswd_password_c* password, Animal_c* animal) {
    static u8 gobi_str[ANIMAL_CATCHPHRASE_LEN];
    mActor_name_t npc_name;

    (void)animal;
    (void)present;

    mem_clear(gobi_str, 4, CHAR_SPACE);

    npc_name = mMpswd_get_pw_npc_name(password);
    mMpswd_set_npc_name_str(name_str, npc_name, password);
    mem_copy(submenu_name_str, name_str, 6);

    if (password->npc_type == mMpswd_NPCTYPE_NORMAL) {
        *mail_no = password->npc_code + 0x3D6;
        mMpswd_get_gobi_str_from_name(gobi_str, npc_name);
        mHandbill_Set_free_str(mHandbill_FREE_STR5, gobi_str, 4);
    } else {
        *mail_no = password->npc_code + 0x4C2;
        // replace さん (-san) with spaces
        if (submenu_name_str[4] == CHAR_PP_010 && submenu_name_str[5] == CHAR_PP_195) {
            submenu_name_str[4] = CHAR_SPACE;
            submenu_name_str[5] = CHAR_SPACE;
        }
    }
}

static void mMpswd_make_send_mail_old_correct(Mail_c* mail, mMpswd_password_c* password, PersonalID_c* pid, Animal_c* animal) {
    static mMpswd_MAKE_SEND_MAIL_PROC make_send_mail_proc[mMpswd_CODETYPE_NUM] = {
        &mMpswd_make_send_mail_old_correct_famicom,
        &mMpswd_make_send_mail_old_correct_npc,
        &mMpswd_make_send_mail_old_correct_npc,
        &mMpswd_make_send_mail_old_correct_magazine,
        &mMpswd_make_send_mail_old_correct_npc,
        &mMpswd_make_send_mail_old_correct_npc,
        &mMpswd_make_send_mail_old_correct_npc,
        &mMpswd_make_send_mail_old_correct_npc,
    };

    static u8 name_str[ANIMAL_NAME_LEN];
    static u8 submenu_name_str[ANIMAL_NAME_LEN];
    mActor_name_t unused_present = EMPTY_NO;
    int mail_no;

    mem_clear(name_str, ANIMAL_NAME_LEN, CHAR_SPACE);
    mem_clear(submenu_name_str, ANIMAL_NAME_LEN, CHAR_SPACE);
    (*make_send_mail_proc[password->type])(&mail_no, &unused_present, name_str, submenu_name_str, password, animal);
#if VERSION == VER_GAEJ01_01
    mMpswd_make_send_mail_common(mail, password, pid, animal, mail_no, name_str, submenu_name_str, mSP_get_old_password_furniture(), TRUE, TRUE);
#else
    mMpswd_make_send_mail_common(mail, password, pid, animal, mail_no, name_str, submenu_name_str, mSP_get_old_password_furniture(), TRUE);
#endif
}

static int mMpswd_make_send_mail(Mail_c* mail, mMpswd_password_c* password, PersonalID_c* pid, Animal_c* animal, int send_type) {
    int ret = FALSE;

    switch (send_type) {
        case mMpswd_SEND_TYPE_CORRECT:
            mMpswd_make_send_mail_correct(mail, password, pid, animal);
            ret = TRUE;
            break;
        case mMpswd_SEND_TYPE_NG:
            mMpswd_make_send_mail_NG(mail, password, pid, animal);
            ret = TRUE;
            break;
        case mMpswd_SEND_TYPE_OLD_CORRECT:
            mMpswd_make_send_mail_old_correct(mail, password, pid, animal);
            ret = TRUE;
            break;
    }

    return ret;
}

static int mMpswd_SendHPMail_analysis(PersonalID_c* pid, Animal_c* animal, AnmHPMail_c* hp_mail) {
    int res = FALSE;
    int keep_mail_sum;
    mMpswd_password_c password;
    Mail_c mail;
    int send_type;

    keep_mail_sum = mPO_get_keep_mail_sum();
    if (keep_mail_sum < mPO_MAIL_STORAGE_SIZE) {
        mMpswd_password(&password, hp_mail->password);
        send_type = mMpswd_get_send_type(&password, animal);
        res = mMpswd_make_send_mail(&mail, &password, pid, animal, send_type);
        if (res == TRUE) {
            if (mNpc_CheckCmpSickAnimalName(mail.header.sender.personalID.player_name) == 0) {
                res = mPO_receipt_proc(&mail, mPO_SENDTYPE_MAIL);
            }
        }
    }

    return res;
}

extern void mMpswd_SendHPMail() {
    Private_c* priv = Save_Get(private_data);
    Private_c* priv_p;
    Animal_c* animal = Save_Get(animals);
    AnmHPMail_c* hp_mail;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int i;
    int j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            hp_mail = animal->hp_mail;
            priv_p = priv;

            for (j = 0; j < ANIMAL_HP_MAIL_NUM; j++) {
                if (hp_mail->receive_time.year != 0 && hp_mail->receive_time.day != 0 &&
                    mPr_NullCheckPersonalID(&priv_p->player_ID) == FALSE) {
                    int days;

                    if (lbRTC_IsOverTime(&hp_mail->receive_time, rtc_time) == lbRTC_OVER) {
                        days = lbRTC_GetIntervalDays(&hp_mail->receive_time, rtc_time);
                    } else {
                        days = lbRTC_GetIntervalDays(rtc_time, &hp_mail->receive_time);
                    }

                    if (days >= 1 && mMpswd_SendHPMail_analysis(&priv_p->player_ID, animal, hp_mail) == TRUE) {
                        mMpswd_ClearHPMail(hp_mail, 1);
                    }
                }

                priv_p++;
                hp_mail++;
            }
        }

        animal++;
    }
}
