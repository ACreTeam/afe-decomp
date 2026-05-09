#include "m_name_table.h"

#include "m_actor.h"
#include "m_npc_personal_id.h"
#include "m_common_data.h"

s16 move_obj_profile_table[] = {
    mAc_PROFILE_AIRPLANE,        mAc_PROFILE_BALL,         mAc_PROFILE_MY_ROOM,      mAc_PROFILE_MBG,
    mAc_PROFILE_BOXMANAGER,      mAc_PROFILE_BOXTRICK01,   mAc_PROFILE_ARRANGE_ROOM, mAc_PROFILE_ARRANGE_FURNITURE,
    mAc_PROFILE_EFFECT_CONTROL,  mAc_PROFILE_SHOP_DESIGN,  mAc_PROFILE_SHOP_MANEKIN, mAc_PROFILE_SHOP_INDOOR,
    mAc_PROFILE_SHOP_GOODS,      mAc_PROFILE_SNOWMAN,      mAc_PROFILE_SNOWMAN,      mAc_PROFILE_BROKER_DESIGN,
    mAc_PROFILE_MY_INDOOR,       mAc_PROFILE_TRAIN_WINDOW, mAc_PROFILE_UKI,          mAc_PROFILE_SHOP_UMBRELLA,
    mAc_PROFILE_KAMAKURA_INDOOR, mAc_PROFILE_HOUSE_CLOCK
};

s16 actor_profile_table[] = { mAc_PROFILE_SAMPLE };

s16 props_profile_table[] = {
    mAc_PROFILE_MAILBOX,  mAc_PROFILE_MAILBOX,  mAc_PROFILE_MAILBOX,   mAc_PROFILE_MAILBOX,   mAc_PROFILE_HANIWA,
    mAc_PROFILE_HANIWA,   mAc_PROFILE_HANIWA,   mAc_PROFILE_HANIWA,    mAc_PROFILE_PSNOWMAN,  mAc_PROFILE_PSNOWMAN,
    mAc_PROFILE_PSNOWMAN, mAc_PROFILE_PSNOWMAN, mAc_PROFILE_PSNOWMAN,  mAc_PROFILE_PSNOWMAN,  mAc_PROFILE_PSNOWMAN,
    mAc_PROFILE_PSNOWMAN, mAc_PROFILE_PSNOWMAN, mAc_PROFILE_TRAINDOOR, mAc_PROFILE_NAMEPLATE,
};

u8 npc_looks_table[NPC_NUM + 1] = {
    mNpc_LOOKS_BOY,         mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GIRL,        mNpc_LOOKS_GIRL,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_NANIWA_LADY,
    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GIRL,        mNpc_LOOKS_GIRL,        mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_BOY,         mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_BOY,         mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GIRL,        mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_BOY,         mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_GIRL,        mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_BOY,         mNpc_LOOKS_GIRL,
    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GIRL,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_GIRL,        mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GIRL,        mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GIRL,        mNpc_LOOKS_BOY,
    mNpc_LOOKS_GIRL,        mNpc_LOOKS_GIRL,        mNpc_LOOKS_BOY,         mNpc_LOOKS_NANIWA_LADY,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_BOY,         mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_BOY,         mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GIRL,
    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_GIRL,        mNpc_LOOKS_BOY,         mNpc_LOOKS_BOY,         mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_BOY,         mNpc_LOOKS_GIRL,        mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_GIRL,        mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_BOY,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_BOY,         mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GIRL,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GIRL,        mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GIRL,        mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GIRL,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GIRL,        mNpc_LOOKS_NANIWA_LADY,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GIRL,        mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_BOY,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_BOY,         mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GIRL,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_GIRL,
    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GIRL,        mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_BOY,         mNpc_LOOKS_BOY,         mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GIRL,        mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_BOY,         mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_GIRL,        mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_BOY,         mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GIRL,        mNpc_LOOKS_BOY,         mNpc_LOOKS_GIRL,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_BOY,
    mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_BOY,         mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_NANIWA_LADY,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_GIRL,        mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GIRL,        mNpc_LOOKS_GIRL,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GIRL,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_GIRL,        mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_GIRL,        mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_GIRL,        mNpc_LOOKS_SPORT_MAN,
    mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_BOY,         mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_GRIM_MAN,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_KO_GIRL,
    mNpc_LOOKS_GIRL,        mNpc_LOOKS_BOY,         mNpc_LOOKS_GRIM_MAN,    mNpc_LOOKS_GIRL,
    mNpc_LOOKS_KO_GIRL,     mNpc_LOOKS_SPORT_MAN,   mNpc_LOOKS_NANIWA_LADY, mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,
    mNpc_LOOKS_BOY,         mNpc_LOOKS_KO_GIRL
};

static u8 item1_1_tableNo[] = { 9, 9, 9, 9 };

static u8 item1_5_tableNo[] = {
    0x16, 0x1E, 0x23, 0x22, 0x24, 0x21, 0x2A, 0x2B,
    0x10, 0x0D, 0x0D, 0x0D, 0x0D, 0x09, 0x15, 0x15,
    0x15, 0x14, 0x17, 0x1D, 0x19, 0x18, 0x18, 0x18,
    0x19, 0x19, 0x18, 0x1A, 0x0E, 0x0B, 0x13, 0x0E,
    0x0E, 0x0E, 0x0E, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F,
    0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F,
    0x34
};

static u8 item1_C_tableNo[] = {
    49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
    49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
    49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
    49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
};

static u8 item1_E_tableNo[] = { 46, 46 };

static u8 item1_F_tableNo[] = { 7, 7, 7, 7 };

static u8 item1_0_tableNo[] = {
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
};

static u8 item1_2_tableNo[] = {
    0x22, 0x21, 0x24, 0x23, 0x29, 0x29, 0x29, 0x29,
    0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29,
    0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29,
    0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29,
    0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29,
    0x29, 0x29, 0x29, 0x29, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x26, 0x25, 0x28, 0x27, 0x21, 0x21, 0x21,
    0x21, 0x21, 0x21, 0x21, 0x13, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x2A, 0x2A, 0x2A, 0x2A,
    0x2A, 0x2A, 0x2A, 0x2A, 0x2B, 0x2B, 0x2B, 0x2B,
    0x2B, 0x2B, 0x2B, 0x2B, 0x36, 0x13, 0x13, 0x13,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x38,
};

static u8 item1_3_tableNo[48] = {
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
};

static u8 item1_4_tableNo[] = {
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
};

static u8 item1_6_tableNo[] = {
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
};

static u8 item1_7_tableNo[] = {
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
    32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
};

static u8 item1_8_tableNo[] = { 1, 5, 4, 3, 2, 6, 27, 28 };

static u8 item1_9_tableNo[] = { 17, 17, 45, 45, 45, 45, 45, 45, 45, 45, 45 };

static u8 item1_A_tableNo[] = {
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
    0x35, 0x35, 0x35, 0x35,
};

// ?? Shouldn't these be different from saplings?
static u8 item1_B_tableNo[] = { 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51 };

static u8 item1_D_tableNo[] = {
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
    18, 18, 18, 18, 18, 18, 18,
};

extern int mNT_get_itemTableNo(mActor_name_t item) {
    static u8* item1_tableNo[ITEM1_CAT_NUM] = { item1_0_tableNo, item1_1_tableNo, item1_2_tableNo, item1_3_tableNo,
                                                item1_4_tableNo, item1_5_tableNo, item1_6_tableNo, item1_7_tableNo,
                                                item1_8_tableNo, item1_9_tableNo, item1_A_tableNo, item1_B_tableNo,
                                                item1_C_tableNo, item1_D_tableNo, item1_E_tableNo, item1_F_tableNo, };

    switch (ITEM_NAME_GET_TYPE(item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            if (item >= FTR_DINO_START && item <= FTR_DINO_END) {
                return mNT_ITEM_TYPE_BONE;
            } else if (item >= HANIWA_START && item <= HANIWA_END) {
                return mNT_ITEM_TYPE_HANIWA;
            } else if (item >= ITM_DIARY_START && item <= ITM_DIARY15) {
                return mNT_ITEM_TYPE_DIARY;
            }

            return mNT_ITEM_TYPE_LEAF;
        }

        case NAME_TYPE_ITEM1: {
            int category = ITEM_NAME_GET_CAT((mActor_name_t)item);
            int idx = ITEM_NAME_GET_INDEX((mActor_name_t)item);

            return item1_tableNo[category][idx];
        }

        default:
            return mNT_ITEM_TYPE_NONE;
    }
}

extern mActor_name_t mNT_FishIdx2FishItemNo(int idx) {
    if (idx >= 0 && idx <= (FISH_NUM + 1)) {
        return ITM_FISH_START + idx;
    }

    return EMPTY_NO;
}

extern mActor_name_t bg_item_fg_sub(mActor_name_t item, s16 flag) {
    static mActor_name_t cnvfg[mNT_TREE_SIZE_NUM][mNT_TREE_TYPE_NUM] = {
        { TREE_STUMP004, TREE_PALM_STUMP004, CEDAR_TREE_STUMP004, GOLD_TREE_STUMP004 },
        { TREE_STUMP003, TREE_PALM_STUMP003, CEDAR_TREE_STUMP003, GOLD_TREE_STUMP003 },
        { TREE_STUMP002, TREE_PALM_STUMP002, CEDAR_TREE_STUMP002, GOLD_TREE_STUMP002 },
        { TREE_STUMP001, TREE_PALM_STUMP001, CEDAR_TREE_STUMP001, GOLD_TREE_STUMP001 }
    };

    u32 what = item;
    int tree_type = FGTreeType_check(what);
    mActor_name_t stump = what;

    if (flag != 0) {
        stump = what;
    } else if (item == TREE || item == TREE_1000BELLS || item == TREE_10000BELLS || item == TREE_30000BELLS ||
               item == TREE_100BELLS || item == CEDAR_TREE || item == GOLD_TREE_SHOVEL || item == GOLD_TREE ||
               item == TREE_APPLE_NOFRUIT_0 || item == TREE_APPLE_NOFRUIT_1 || item == TREE_APPLE_NOFRUIT_2 ||
               item == TREE_APPLE_FRUIT || item == TREE_ORANGE_NOFRUIT_0 || item == TREE_ORANGE_NOFRUIT_1 ||
               item == TREE_ORANGE_NOFRUIT_2 || item == TREE_ORANGE_FRUIT || item == TREE_PEACH_NOFRUIT_0 ||
               item == TREE_PEACH_NOFRUIT_1 || item == TREE_PEACH_NOFRUIT_2 || item == TREE_PEACH_FRUIT ||
               item == TREE_PEAR_NOFRUIT_0 || item == TREE_PEAR_NOFRUIT_1 || item == TREE_PEAR_NOFRUIT_2 ||
               item == TREE_PEAR_FRUIT || item == TREE_CHERRY_NOFRUIT_0 || item == TREE_CHERRY_NOFRUIT_1 ||
               item == TREE_CHERRY_NOFRUIT_2 || item == TREE_CHERRY_FRUIT || item == TREE_PALM_NOFRUIT_0 ||
               item == TREE_PALM_NOFRUIT_1 || item == TREE_PALM_NOFRUIT_2 || item == TREE_PALM_FRUIT ||
               item == TREE_BEES || item == TREE_FTR || item == TREE_LIGHTS || item == TREE_PRESENT ||
               item == TREE_BELLS || item == CEDAR_TREE_BELLS || item == CEDAR_TREE_FTR || item == CEDAR_TREE_BEES ||
               item == CEDAR_TREE_LIGHTS || item == GOLD_TREE_BELLS || item == GOLD_TREE_FTR ||
               item == GOLD_TREE_BEES) {
        stump = cnvfg[mNT_TREE_SIZE_FULL][tree_type];
    } else if (item == TREE_S2 || item == TREE_APPLE_S2 || item == TREE_ORANGE_S2 || item == TREE_PEACH_S2 ||
               item == TREE_PEAR_S2 || item == TREE_CHERRY_S2 || item == TREE_1000BELLS_S2 ||
               item == TREE_10000BELLS_S2 || item == TREE_30000BELLS_S2 || item == TREE_100BELLS_S2 ||
               item == TREE_PALM_S2 || item == CEDAR_TREE_S2 || item == GOLD_TREE_S2) {
        stump = cnvfg[mNT_TREE_SIZE_S2][tree_type];
    } else if (item == TREE_S1 || item == TREE_APPLE_S1 || item == TREE_ORANGE_S1 || item == TREE_PEACH_S1 ||
               item == TREE_PEAR_S1 || item == TREE_CHERRY_S1 || item == TREE_1000BELLS_S1 ||
               item == TREE_10000BELLS_S1 || item == TREE_30000BELLS_S1 || item == TREE_100BELLS_S1 ||
               item == TREE_PALM_S1 || item == CEDAR_TREE_S1 || item == GOLD_TREE_S1) {
        stump = cnvfg[mNT_TREE_SIZE_S1][tree_type];
    } else if (item == TREE_S0 || item == TREE_APPLE_S0 || item == TREE_ORANGE_S0 || item == TREE_PEACH_S0 ||
               item == TREE_PEAR_S0 || item == TREE_CHERRY_S0 || item == TREE_1000BELLS_S0 ||
               item == TREE_10000BELLS_S0 || item == TREE_30000BELLS_S0 || item == TREE_100BELLS_S0 ||
               item == TREE_PALM_S0 || item == CEDAR_TREE_S0 || item == GOLD_TREE_S0) {
        stump = cnvfg[mNT_TREE_SIZE_S0][tree_type];
    }

    return stump;
}

extern mActor_name_t bg_item_fg_sub_tree_grow(mActor_name_t item, int past_days, int check_plant) {
    static s16 grow_check[84][2] = {
        { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 }, { -1, mCoBG_PLANT3 }, { 0, mCoBG_PLANT4 },
        { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 }, { -4, mCoBG_PLANT3 }, { -1, mCoBG_PLANT4 },
        { -1, mCoBG_PLANT4 }, { -1, mCoBG_PLANT4 }, { 0, mCoBG_PLANT4 },  { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 },
        { -1, mCoBG_PLANT2 }, { -4, mCoBG_PLANT3 }, { -1, mCoBG_PLANT4 }, { -1, mCoBG_PLANT4 }, { -1, mCoBG_PLANT4 },
        { 0, mCoBG_PLANT4 },  { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 }, { -4, mCoBG_PLANT3 },
        { -1, mCoBG_PLANT4 }, { -1, mCoBG_PLANT4 }, { -1, mCoBG_PLANT4 }, { 0, mCoBG_PLANT4 },  { -1, mCoBG_PLANT0 },
        { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 }, { -4, mCoBG_PLANT3 }, { -1, mCoBG_PLANT4 }, { -1, mCoBG_PLANT4 },
        { -1, mCoBG_PLANT4 }, { 0, mCoBG_PLANT4 },  { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 },
        { -4, mCoBG_PLANT3 }, { -1, mCoBG_PLANT4 }, { -1, mCoBG_PLANT4 }, { -1, mCoBG_PLANT4 }, { 0, mCoBG_PLANT4 },
        { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 }, { -1, mCoBG_PLANT3 }, { 0, mCoBG_PLANT4 },
        { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 }, { -1, mCoBG_PLANT3 }, { 0, mCoBG_PLANT4 },
        { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 }, { -1, mCoBG_PLANT3 }, { 0, mCoBG_PLANT4 },
        { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 }, { -1, mCoBG_PLANT3 }, { 0, mCoBG_PLANT4 },
        { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 }, { -1, mCoBG_PLANT2 }, { -4, mCoBG_PLANT3 }, { -1, mCoBG_PLANT4 },
        { -1, mCoBG_PLANT4 }, { -1, mCoBG_PLANT4 }, { 0, mCoBG_PLANT4 },  { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 },
        { -1, mCoBG_PLANT2 }, { -1, mCoBG_PLANT3 }, { 0, mCoBG_PLANT4 },  { -1, mCoBG_PLANT0 }, { -1, mCoBG_PLANT1 },
        { -1, mCoBG_PLANT2 }, { -1, mCoBG_PLANT3 }, { 0, mCoBG_PLANT4 },  { 0, mCoBG_PLANT4 }
    };

    int idx;
    int i;

    if ((item >= TREE_SAPLING && item <= TREE_30000BELLS) ||
        (item >= TREE_100BELLS_SAPLING && item <= TREE_PALM_FRUIT) ||
        (item >= CEDAR_TREE_SAPLING && item <= CEDAR_TREE) || (item >= GOLD_TREE_SAPLING && item <= GOLD_TREE)) {
        if (item >= TREE_PALM_SAPLING && item <= TREE_PALM_FRUIT) {
            idx = item - 0x0813;
        } else if (item >= CEDAR_TREE_SAPLING && item <= CEDAR_TREE) {
            idx = item - 0x0814;
        } else if (item == GOLD_TREE || (item >= GOLD_TREE_SAPLING && item <= GOLD_TREE_SHOVEL)) {
            idx = item - 0x0815;
        } else if (item >= TREE_100BELLS_SAPLING) {
            idx = item - 0x0813;
        } else {
            idx = item - 0x0800;
        }

        for (i = 0; i <= past_days; i++) {
            int diff = -grow_check[idx][0];

            if (grow_check[idx + diff][1] > check_plant) {
                break;
            }

            idx += diff;
            item += diff;
        }
    }

    return item;
}

extern mActor_name_t bg_item_fg_sub_dig2take_conv(mActor_name_t item) {
    mActor_name_t dig_item;

    dig_item = item;
    if ((item >= BURIED_PITFALL_HOLE_START) && (item <= BURIED_PITFALL_HOLE_END)) {
        dig_item = ITM_PITFALL;
    }

    if (item == SHINE_SPOT) {
        f32 rng_val = RANDOM_F(100.0f);
        f32 money_power = mPr_GetMoneyPower();
        f32 max_bells_roll = 2.0f * (money_power / 40.0f);    // 30k
        f32 large_bells_roll = 10.0f * (money_power / 40.0f); // 10k

        if ((rng_val <= max_bells_roll) || ((int)Common_Get(now_private)->destiny.type == mPr_DESTINY_MONEY_LUCK)) {
            dig_item = ITM_MONEY_30000;
        } else if (rng_val <= (large_bells_roll + max_bells_roll)) {
            dig_item = ITM_MONEY_10000;
        } else {
            dig_item = ITM_MONEY_1000;
        }
    }
    return dig_item;
}

static mNT_offset_table_c height_table[3] = {
    { 0, { mCoBG_ATTRIBUTE_NONE, 0, 0, 0, 0, 0, 0 } },
    { 0, { mCoBG_ATTRIBUTE_WOOD, 4, 4, 4, 4, 4, 0 } },
    { 0, { mCoBG_ATTRIBUTE_WOOD, 7, 7, 7, 7, 7, 0 } },
};

extern mNT_offset_table_c* obj_hight_table_item0_nogrow(mActor_name_t item) {
    mNT_offset_table_c* table = &height_table[0];

    if (item == FENCE0 || item == FENCE1 || item == MESSAGE_BOARD0 || item == MESSAGE_BOARD1 || item == WOOD_FENCE) {
        table = &height_table[1];
    } else if (item == MAP_BOARD0 || item == MAP_BOARD1 || item == MUSIC_BOARD0 || item == MUSIC_BOARD1) {
        table = &height_table[2];
    }

    return table;
}

extern int FGTreeType_check(mActor_name_t tree) {
    if ((tree >= TREE_PALM_SAPLING && tree <= TREE_PALM_FRUIT) || (tree == DEAD_PALM_SAPLING) ||
        (tree >= TREE_PALM_STUMP001 && tree <= TREE_PALM_STUMP004)) {
        return mNT_TREE_TYPE_PALM;
    }

    if ((tree >= CEDAR_TREE_SAPLING && tree <= CEDAR_TREE) || (tree == DEAD_CEDAR_SAPLING) ||
        (tree == CEDAR_TREE_BELLS) || (tree == CEDAR_TREE_FTR) || (tree == CEDAR_TREE_BEES) ||
        (tree == CEDAR_TREE_LIGHTS) || (tree >= CEDAR_TREE_STUMP001 && tree <= CEDAR_TREE_STUMP004)) {
        return mNT_TREE_TYPE_CEDAR;
    }

    if ((tree == GOLD_TREE) || (tree >= GOLD_TREE_SAPLING && tree <= GOLD_TREE_SHOVEL) || (tree == DEAD_GOLD_SAPLING) ||
        (tree == GOLD_TREE_BELLS) || (tree == GOLD_TREE_FTR) || (tree == GOLD_TREE_BEES) ||
        (tree >= GOLD_TREE_STUMP001 && tree <= GOLD_TREE_STUMP004)) {
        return mNT_TREE_TYPE_GOLD;
    }

    return mNT_TREE_TYPE_NORMAL;
}

extern int mNT_ItIsStump(mActor_name_t actor) {
    if ((actor >= TREE_STUMP001 && actor <= TREE_STUMP004) ||
        (actor >= TREE_PALM_STUMP001 && actor <= TREE_PALM_STUMP004) ||
        (actor >= CEDAR_TREE_STUMP001 && actor <= CEDAR_TREE_STUMP004) ||
        (actor >= GOLD_TREE_STUMP001 && actor <= GOLD_TREE_STUMP004)) {
        return TRUE;
    }

    return FALSE;
}

extern int mNT_ItIsStoneCoin10(mActor_name_t actor) {
    int res = FALSE;

    if ((actor >= MONEY_ROCK_A) && (actor <= MONEY_FLOWER_SEED)) {
        res = TRUE;
    }

    return res != FALSE;
}

extern int mNT_ItIsRstStone(mActor_name_t item) {
    return (item >= RST_ROCK_A && item <= C_ROCK_E) !=  FALSE;
}

extern int mNT_ItIsReserveDummy(mActor_name_t actor) {
    return actor == DUMMY_RESERVE;
}

extern int mNT_check_unknown(mActor_name_t item_no) {
    static s16 item1_kinds[ITEM1_CAT_NUM] = {
        PAPER_NUM, // ITEM1_CAT_PAPER
        MONEY_NUM, // ITEM1_CAT_MONEY
        TOOL_NUM, // ITEM1_CAT_TOOL
        FISH_NUM, // ITEM1_CAT_FISH
        CLOTH_NUM, // ITEM1_CAT_CLOTH
        ETC_NUM, // ITEM1_CAT_ETC
        CARPET_NUM, // ITEM1_CAT_CARPET
        WALL_NUM, // ITEM1_CAT_WALL
        FRUIT_NUM, // ITEM1_CAT_FRUIT
        PLANT_NUM, // ITEM1_CAT_PLANT
        MINIDISK_NUM, // ITEM1_CAT_MINIDISK
        DIARY_NUM, // ITEM1_CAT_DUMMY
        TICKET_NUM, // ITEM1_CAT_TICKET
        INSECT_NUM, // ITEM1_CAT_INSECT
        HUKUBUKURO_NUM, // ITEM1_CAT_HUKUBUKURO
        KABU_NUM, // ITEM1_CAT_KABU
    };

    int index = ITEM_NAME_GET_INDEX(item_no);
    int res = FALSE;

    switch (ITEM_NAME_GET_TYPE(item_no)) {
        case NAME_TYPE_ITEM1: {
            int category = ITEM_NAME_GET_CAT(item_no);

            if (index < 0 || index >= item1_kinds[category]) {
                res = TRUE;
            }
            break;
        }

        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            int FtrIdx = mNT_ftr_item_no_to_ftr_idx(item_no);

            if (FtrIdx < 0 || FtrIdx >= FTR_NUM) {
                res = TRUE;
            }

            break;
        }
    }

    return res;
}

extern int mNT_get_org_umb_type(mActor_name_t umb) {
    if (ITEM_IS_MYUMBRELLA_TOOL(umb)) {
        return Save_Get(needlework).original_design[(umb - ITM_MY_ORG_UMBRELLA0) & 7].attr;
    }

    return 0xFF;
}

extern int mNT_get_cloth_type(mActor_name_t cloth, u8 org_idx) {
    // clang-format off
    static u8 cloth_type_table[CLOTH_NUM] = {
        mNT_STYLE_COOL,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FANCY,
        mNT_STYLE_STRANGE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_FANCY,
        mNT_STYLE_FANCY,
        mNT_STYLE_FRESH,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_CUTE,
        mNT_STYLE_FANCY,
        mNT_STYLE_STRANGE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_FANCY,
        mNT_STYLE_CUTE,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_STRIKING,
        mNT_STYLE_REFINED,
        mNT_STYLE_FRESH,
        mNT_STYLE_FRESH,
        mNT_STYLE_STRIKING,
        mNT_STYLE_STRIKING,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_FANCY,
        mNT_STYLE_FANCY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_CUTE,
        mNT_STYLE_STRANGE,
        mNT_STYLE_STRANGE,
        mNT_STYLE_STRANGE,
        mNT_STYLE_STRANGE,
        mNT_STYLE_STRANGE,
        mNT_STYLE_STRANGE,
        mNT_STYLE_FANCY,
        mNT_STYLE_CUTE,
        mNT_STYLE_FRESH,
        mNT_STYLE_FANCY,
        mNT_STYLE_FANCY,
        mNT_STYLE_CUTE,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_COOL,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_STRANGE,
        mNT_STYLE_FANCY,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_FRESH,
        mNT_STYLE_STRANGE,
        mNT_STYLE_FANCY,
        mNT_STYLE_FANCY,
        mNT_STYLE_FRESH,
        mNT_STYLE_FRESH,
        mNT_STYLE_FRESH,
        mNT_STYLE_FRESH,
        mNT_STYLE_FRESH,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_COOL,
        mNT_STYLE_COOL,
        mNT_STYLE_COOL,
        mNT_STYLE_COOL,
        mNT_STYLE_COOL,
        mNT_STYLE_COOL,
        mNT_STYLE_FUNKY,
        mNT_STYLE_COOL,
        mNT_STYLE_COOL,
        mNT_STYLE_FRESH,
        mNT_STYLE_CUTE,
        mNT_STYLE_STRANGE,
        mNT_STYLE_FRESH,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_CUTE,
        mNT_STYLE_FUNKY,
        mNT_STYLE_REFINED,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_CUTE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_CUTE,
        mNT_STYLE_STRIKING,
        mNT_STYLE_COOL,
        mNT_STYLE_CUTE,
        mNT_STYLE_STRIKING,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_REFINED,
        mNT_STYLE_STRIKING,
        mNT_STYLE_STRIKING,
        mNT_STYLE_GAUDY,
        mNT_STYLE_CUTE,
        mNT_STYLE_COOL,
        mNT_STYLE_FRESH,
        mNT_STYLE_STRIKING,
        mNT_STYLE_COOL,
        mNT_STYLE_CUTE,
        mNT_STYLE_FRESH,
        mNT_STYLE_CUTE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_FANCY,
        mNT_STYLE_FANCY,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_FANCY,
        mNT_STYLE_FANCY,
        mNT_STYLE_FRESH,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_CUTE,
        mNT_STYLE_CUTE,
        mNT_STYLE_COOL,
        mNT_STYLE_FRESH,
        mNT_STYLE_FANCY,
        mNT_STYLE_FANCY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FRESH,
        mNT_STYLE_FRESH,
        mNT_STYLE_STRIKING,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_COOL,
        mNT_STYLE_REFINED,
        mNT_STYLE_FRESH,
        mNT_STYLE_REFINED,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_CUTE,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_FRESH,
        mNT_STYLE_REFINED,
        mNT_STYLE_CUTE,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_FANCY,
        mNT_STYLE_FRESH,
        mNT_STYLE_REFINED,
        mNT_STYLE_COOL,
        mNT_STYLE_REFINED,
        mNT_STYLE_COOL,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FANCY,
        mNT_STYLE_CUTE,
        mNT_STYLE_FRESH,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_CUTE,
        mNT_STYLE_REFINED,
        mNT_STYLE_FUNKY,
        mNT_STYLE_COOL,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_STRIKING,
        mNT_STYLE_COOL,
        mNT_STYLE_GAUDY,
        mNT_STYLE_COOL,
        mNT_STYLE_COOL,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_COOL,
        mNT_STYLE_FUNKY,
        mNT_STYLE_STRIKING,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_FUNKY,
        mNT_STYLE_STRANGE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_CUTE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_STRIKING,
        mNT_STYLE_GAUDY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_CUTE,
        mNT_STYLE_FUNKY,
        mNT_STYLE_STRIKING,
        mNT_STYLE_STRIKING,
        mNT_STYLE_FRESH,
        mNT_STYLE_CUTE,
        mNT_STYLE_FRESH,
        mNT_STYLE_STRIKING,
        mNT_STYLE_FANCY,
        mNT_STYLE_CUTE,
        mNT_STYLE_FANCY,
        mNT_STYLE_COOL,
        mNT_STYLE_STRIKING,
        mNT_STYLE_STRIKING,
        mNT_STYLE_STRIKING,
        mNT_STYLE_CUTE,
        mNT_STYLE_FANCY,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_REFINED,
        mNT_STYLE_COOL,
        mNT_STYLE_REFINED,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_STRIKING,
        mNT_STYLE_FUNKY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_REFINED,
        mNT_STYLE_STRANGE,
        mNT_STYLE_CUTE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_GAUDY,
        mNT_STYLE_FANCY,
        mNT_STYLE_FANCY,
        mNT_STYLE_CUTE,
        mNT_STYLE_STRIKING,
        mNT_STYLE_CUTE,
        mNT_STYLE_FANCY,
        mNT_STYLE_STRIKING,
        mNT_STYLE_CUTE,
        mNT_STYLE_FANCY,
        mNT_STYLE_STRANGE,
        mNT_STYLE_CUTE,
        mNT_STYLE_SUBTLE,
        mNT_STYLE_REFINED,
        mNT_STYLE_GAUDY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_FUNKY,
        mNT_STYLE_STRANGE,
        mNT_STYLE_GAUDY,
        mNT_STYLE_FANCY,
        mNT_STYLE_FRESH,
        mNT_STYLE_FANCY,
    };
    // clang-format on

    if (ITEM_IS_CLOTH(cloth)) {
        return cloth_type_table[ITEM1_CLOTH2IDX(cloth)];
    } else if (cloth == RSV_CLOTH) {
        return Now_Private->my_org[(org_idx - (CLOTH_NUM + 1)) & 7].attr;
    } else if (cloth == RSV_CLOTH1) {
        return Save_Get(needlework).original_design[org_idx & 7].attr;
    } else {
        return 0xFF;
    }
}

extern mActor_name_t mNT_get_new_music_live_version(int idx) {
    Private_c* priv = Now_Private;
    int free_slots = mPr_GetFreePossessionItemSum(priv);

    if (mLd_PlayerManKindCheck() == NATIVE && priv != NULL && BITCHK(Save_Get(song_cards_scanned), idx & 0xF) && BITCHK(priv->new_music_card_scanned, idx & 0xF) && free_slots > 0) {
        return ITM_MINIDISK_LIVE58 + idx;
    }
    
    return EMPTY_NO;
}

extern void mNT_present_new_music_live_version(int idx) {
    Private_c* priv = Now_Private;

    if (mLd_PlayerManKindCheck() == NATIVE && priv != NULL) {
        u16 bit = ~(1 << (idx & 0xF));
        priv->new_music_card_scanned &= bit;
    }
}

extern int mNT_ftr_item_no_to_ftr_idx(mActor_name_t item_no) {
    if (ITEM_IS_FTR(item_no)) {
        switch (ITEM_NAME_GET_TYPE(item_no)) {
            case NAME_TYPE_FTR0:
                return (item_no - FTR0_START) >> 2;
            case NAME_TYPE_FTR1:
                return 0x400 + ((item_no - FTR1_START) >> 2);
        }
    }
    return 0;
}

extern mActor_name_t mNT_ftr_idx_to_ftr_item_no(int ftr_idx, int rotation) {
    mActor_name_t ftr_item_no;
    int real_direct = rotation & 3;

    if (ftr_idx < 0) {
        return FTR0_START;
    }

    ftr_item_no = FTR1_START + ((ftr_idx - 0x400) << 2) + real_direct;
    if (ftr_idx < 0x400) {
        ftr_item_no = FTR0_START + (ftr_idx << 2) + real_direct;
    }

    return ftr_item_no;
}
