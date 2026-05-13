#ifndef M_PRIVATE_H
#define M_PRIVATE_H

#include "types.h"
#include "m_private_h.h"
#include "libu64/gfxprint.h"
#include "m_personal_id.h"
#include "m_npc.h"
#include "m_museum.h"
#include "m_mail.h"
#include "m_needlework.h"
#include "m_calendar.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mPr_WALLET_MAX 99999
#define mPr_DEPOSIT_MAX 999999999

#define mPr_FLAG_MASK_CAT_SCHEDULED (1 << 0)             // Blanca appears when travelling
#define mPr_FLAG_1 (1 << 1)                              // unused?
#define mPr_FLAG_POSTOFFICE_GIFT0 (1 << 2)               // 1,000,000 Bells
#define mPr_FLAG_POSTOFFICE_GIFT1 (1 << 3)               // 10,000,000 Bells
#define mPr_FLAG_POSTOFFICE_GIFT2 (1 << 4)               // 100,000,000 Bells
#define mPr_FLAG_POSTOFFICE_GIFT3 (1 << 5)               // 999,999,999 Bells
#define mPr_FLAG_MUSEUM_COMP_HANDBILL_SCHEDULED (1 << 6) // player is scheduled to receive completion letter & reward
#define mPr_FLAG_MUSEUM_COMP_HANDBILL_RECEIVED (1 << 7)  // player has received the completion letter & reward
#define mPr_FLAG_8 (1 << 8)                              // unused?
#define mPr_FLAG_UPDATE_OUTLOOK_PENDING (1 << 9)         // player bought a new coat of roof paint to be repainted
#define mPr_FLAG_BIRTHDAY_ACTIVE (1 << 10)       // player's birthday is active and a villager can give them a gift
#define mPr_FLAG_TOTAKEKE_INTRODUCTION (1 << 11) // player has spoken to K.K. Slider before
#define mPr_FLAG_ANGLER_PRESENT_GIVEN (1 << 20) // Chip gave the player a fishing rod

#define mPr_MONEY_POWER_MIN -80

#define mPr_GOODS_POWER_MIN -30
#define mPr_GOODS_POWER_MAX 50

enum {
    mPr_PLAYER_0,
    mPr_PLAYER_1,
    mPr_PLAYER_2,
    mPr_PLAYER_3,
    mPr_FOREIGNER,

    mPr_PLAYER_NUM
};

enum {
    mPr_ITEM_COND_NORMAL,
    mPr_ITEM_COND_PRESENT,
    mPr_ITEM_COND_QUEST,
    mPr_ITEM_COND_4 = 4,
    mPr_ITEM_COND_LOST_ITEM = 8,

    mPr_ITEM_COND_NUM
};

enum {
    mPr_SEX_MALE,
    mPr_SEX_FEMALE,
    mPr_SEX_OTHER,

    mPr_SEX_NUM = mPr_SEX_OTHER
};

enum {
    mPr_FACE_TYPE0,
    mPr_FACE_TYPE1,
    mPr_FACE_TYPE2,
    mPr_FACE_TYPE3,
    mPr_FACE_TYPE4,
    mPr_FACE_TYPE5,
    mPr_FACE_TYPE6,
    mPr_FACE_TYPE7,

    mPr_FACE_TYPE_NUM
};

#define mPr_ECARD_NUM 367
#define mPr_ECARD_LETTER_NUM ((mPr_ECARD_NUM + 7) / 8) // 46

#define mPr_POCKETS_SLOT_COUNT 15
#define mPr_INVENTORY_MAIL_COUNT 10
#define mPr_DELIVERY_QUEST_NUM mPr_POCKETS_SLOT_COUNT
#define mPr_ERRAND_QUEST_NUM 5
#define mPr_CATALOG_ORDER_NUM 5
#define mPr_FOREIGN_MAP_COUNT 8
#define mPr_ORIGINAL_DESIGN_COUNT 8
#define mPr_RADIOCARD_MAX_DAYS 13

#define mPr_ORIGINAL_DESIGN_IDX_VALID(idx) ((idx) >= 0 && (idx) < mPr_ORIGINAL_DESIGN_COUNT)

#if 0
#define mPr_GET_ITEM_COND(all_cond, slot_no) (((all_cond) >> (((u32)(slot_no)) << 1)) & mPr_ITEM_COND_NUM)
#define mPr_SET_ITEM_COND(all_cond, slot_no, cond) \
    (((all_cond) & ~((u32)mPr_ITEM_COND_NUM << ((u32)(slot_no) << 1))) | ((u32)(cond) << ((u32)(slot_no) << 1)))
#endif

#define mPr_GET_ITEM_COND(all_cond, slot_no) ((all_cond)[slot_no])
// #define mPr_SET_ITEM_COND(all_cond, slot_no, cond) ((all_cond)[slot_no] = (cond))
#define mPr_SET_ITEM_COND(all_cond, slot_no, cond) ((all_cond)[slot_no] = (all_cond)[slot_no] & ~0xF | (cond))
#define mPr_CHK_ITEM_COND(cond, slot_no) ((cond)[slot_no] & (0xF))

enum {
    mPr_SUNBURN_RANK_MIN,

    mPr_SUNBURN_RANK0 = mPr_SUNBURN_RANK_MIN,
    mPr_SUNBURN_RANK1,
    mPr_SUNBURN_RANK2,
    mPr_SUNBURN_RANK3,
    mPr_SUNBURN_RANK4,
    mPr_SUNBURN_RANK5,
    mPr_SUNBURN_RANK6,
    mPr_SUNBURN_RANK7,
    mPr_SUNBURN_RANK8,

    mPr_SUNBURN_RANK_MAX = mPr_SUNBURN_RANK8,

    mPr_SUNBURN_RANK_NUM
};

enum {
    mPr_DESTINY_NORMAL,     /* standard fortune state */
    mPr_DESTINY_POPULAR,    /* good luck with villagers */
    mPr_DESTINY_UNPOPULAR,  /* bad luck with villagers */
    mPr_DESTINY_BAD_LUCK,   /* bad luck in general */
    mPr_DESTINY_MONEY_LUCK, /* good money luck */
    mPr_DESTINY_GOODS_LUCK, /* good goods/item luck */

    mPr_DESTINY_NUM
};

/* sizeof(mPr_destiny_c) == 0xA */
typedef struct player_destiny_s {
    /* 0x00 */ lbRTC_time_c received_time; /* time fortune was received */
    /* 0x08 */ u8 type;                    /* fortune type */
} mPr_destiny_c;

/* sizeof(mPr_birthday_c) == 4 */
typedef struct player_birthday_s {
    /* 0x00 */ u16 year; /* assumed, set in mPr_ClearPrivateBirthday but goes unused elsewhere */
    /* 0x02 */ u8 month;
    /* 0x03 */ u8 day;
} mPr_birthday_c;

/* sizeof(mPr_catalog_order_c) == 4 */
typedef struct player_catalog_order_s {
    /* 0x00 */ mActor_name_t item; /* ordered item */
    /* 0x02 */ u8 shop_level;      /* shop 'level' at time of order */
} mPr_catalog_order_c;

/* sizeof(mPr_animal_memory_c) == 0x1A */
typedef struct player_animal_memory_s {
    /* 0x00 */ AnmPersonalID_c npc_id;
    /* 0x14 */ u8 land_name[LAND_NAME_SIZE];
} mPr_animal_memory_c;

/* sizeof(mPr_map_info_c) == 0x8 */
typedef struct player_map_s {
    /* 0x00 */ u8 land_name[LAND_NAME_SIZE];
    /* 0x08 */ u16 land_id;
} mPr_map_info_c;

/* sizeof(mPr_day_day_c) == 6 */
typedef struct player_day_day_s {
    /* 0x00 */ lbRTC_ymd_c last_date; /* last date modified */
    /* 0x04 */ u8 days;               /* number of unique days */
} mPr_day_day_c;

/* sizeof(mPr_sunburn_c) == 6 */
typedef struct player_sunburn_s {
    /* 0x00 */ lbRTC_ymd_c last_changed_date; /* last date that the sunburn rank changed */
    /* 0x04 */ s8 rank;                       /* level of sunburn, 0-8 */
    /* 0x05 */ s8 rankdown_days;              /* days until sunburn rank decreases */
} mPr_sunburn_c;

/* sizeof(mPr_carde_data_c) == 0x32 */
typedef struct player_ecard_data_s {
    /* 0x00 */ lbRTC_ymd_c letter_send_date;               /* date the latest eCard letter was sent */
    /* 0x04 */ u8 card_letters_sent[mPr_ECARD_LETTER_NUM]; /* bitfield keeping track of which eCard letters have been
                                                              sent to the player [0, 366] */
} mPr_carde_data_c;

#define mPr_MOTHER_MAIL_NORMAL_NUM 7
#define mPr_MOTHER_MAIL_MONTHLY_NUM 2

typedef struct private_mother_mail_data_s {
    u8 normal[mPr_MOTHER_MAIL_NORMAL_NUM];
    u8 monthly[mPr_MOTHER_MAIL_MONTHLY_NUM];
    u8 _pad;
    u8 special;
} mPr_mother_mail_data_c;

typedef struct private_mother_mail_info_s {
    lbRTC_ymd_c date;
    mPr_mother_mail_data_c data;
} mPr_mother_mail_info_c;

/* sizeof(mPr_birthday_msg_c) == 0xAA */
typedef struct private_birthday_msg_s {
    /* 0x00 */ PersonalID_c id; // player who sent
    /* 0x10 */ lbRTC_time_c time; // date-time of message
    /* 0x18 */ u8 header_back_start;
    /* 0x19 */ u8 header[MAIL_HEADER_LEN + 4];
    /* 0x27 */ u8 body[MAIL_BODY_LEN + 14];
    /* 0x95 */ u8 footer[MAIL_FOOTER_LEN + 4];
} mPr_birthday_msg_c;

/* sizeof(mPr_birthday_msg_info_c) == 0x2AA */
typedef struct private_birthday_msg_info_s {
    /* 0x000 */ mPr_birthday_msg_c msgs[PLAYER_NUM];
    /* 0x2A8 */ u16 flags;
} mPr_birthday_msg_info_c;

/* sizeof(mPr_pwdInfo_c) == 0x4 */
typedef struct private_pwdinfo_s {
    /* 0x00 */ u8 used;
    /* 0x01 */ u8 card_id; // e-Card ID
    /* 0x02 */ u8 _02[2];
} mPr_pwdInfo_c;

/* sizeof(Private_c) == 0x26A0 */
struct private_s {
    /* 0x0000 */ PersonalID_c player_ID;      /* player's id info */
    /* 0x0010 */ s8 gender;                   /* gender/sex of player */
    /* 0x0011 */ s8 face;                     /* face type of player */
    /* 0x0012 */ u8 moved_from_plus; // existing character from DnM+
    /* 0x0013 */ u8 reset_count;              /* times player has reset */
    /* 0x0014 */ mMsm_record_c museum_record; /* museum items & remail info */

    /* must be a struct due to alignment of first member */
    /* 0x0064 */ struct {
        /* 0x0064 */ mActor_name_t pockets[mPr_POCKETS_SLOT_COUNT]; /* items in inventory */
        /* 0x0082 */ u8 lotto_ticket_expiry_month;
        /* 0x0083 */ u8 lotto_ticket_mail_storage;
        /* 0x0084 */ u8 item_conditions[mPr_POCKETS_SLOT_COUNT];
        /* 0x0094 */ u32 wallet;
        /* 0x0098 */ u32 loan;
    } inventory;

    /* 0x009C */ mQst_delivery_c deliveries[mPr_DELIVERY_QUEST_NUM]; /* delivery quests */
    /* 0x05C4 */ mQst_errand_c errands[mPr_ERRAND_QUEST_NUM];        /* errand quests */
    /* 0x081C */ mQst_delivery_c lost_item_quest;
    /* 0x0874 */ mActor_name_t equipment; /* equipped item */
    /* 0x0876 */ Mail_hs_c saved_mail_header; /* saved mail header/footer which is inserted when writing new letters */
    /* 0x08AC */ Mail_c mail[mPr_INVENTORY_MAIL_COUNT]; /* letters in inventory */
    /* 0x0FF0 */ mActor_name_t backgound_texture;       /* inventory background shirt item id */
    /* 0x0FF2 */ u8 exists;                             /* 0/1 if player exists or not */
    /* 0x0FF3 */ u8 hint_count;                         /* total hints heard from villagers (initial dialog) */
    /* 0x0FF4 */ mPr_cloth_c cloth;
    /* 0x0FF8 */ AnmPersonalID_c stored_anm_id; /* foriegn animal personal ID leftover from N64? */
    /* 0x100C */ mPr_destiny_c destiny;   /* player fortune, seemingly called destiny */
    /* 0x1016 */ mPr_birthday_c birthday; /* player birthday */
    /* 0x101A */ mPr_catalog_order_c catalog_orders[mPr_CATALOG_ORDER_NUM];      /* items ordered from catalog to be mailed */
    /* 0x102E */ u8 unk_10A8[22];                   /* seemingly unused? */
    /* 0x1044 */ u32 aircheck_collect_bitfield[3];  /* TODO: this should be a define like #define
                                                       mPr_AIRCHECK_BITFIELD_NUM ((MD_COUNT / 32) + 1) */
    /* 0x1050 */ Anmremail_c remail;                /* scheduled mail received from a foreign villager? */
    /* 0x1064 */ u32 reset_code;                    /* 0 when not reset, random value after reset */
    /* 0x1068 */ mPr_animal_memory_c animal_memory; /* id and town of last animal to move to another town */
    /* 0x1082 */ u8 complete_fish_insect_flags; /* bit0 = completed fish, bit1 = villager acknowledged completed fish, bit2 =
                                       completed insect, bit3 = villager acknowledged complete insect */
    /* 0x1084 */ lbRTC_year_t celebrated_birthday_year; /* last year a birthday was celebrated by card or visitor */

    /* catalog */
    /* 0x1088 */ u32 furniture_collected_bitfield[45];
    /* 0x113C */ u32 wall_collected_bitfield[3];
    /* 0x1148 */ u32 carpet_collected_bitfield[3];
    /* 0x1154 */ u32 paper_collected_bitfield[2];
    /* 0x115C */ u32 music_collected_bitfield[6];

    /* 0x1174 */ mPr_map_info_c maps[mPr_FOREIGN_MAP_COUNT]; /* maps 'collected' for foreign towns */

    /* 0x11B4 */ u32 bank_account;                                        /* probably 'deposit' interally */
    /* 0x11C0 */ mNW_original_design_c my_org[mPr_ORIGINAL_DESIGN_COUNT]; /* Able Sisters' designs */
    /* 0x22C0 */ u8 my_org_no_table[mPr_ORIGINAL_DESIGN_COUNT];           /* order of designs */
    /* 0x22C8 */ u32 state_flags;                    /* TODO: this might be a bitfield/struct, also document bits */
    /* 0x222C */ mCD_player_calendar_c calendar;     /* player calendar data */
    /* 0x2334 */ u32 soncho_trophy_field0;           /* first 28 tortimer event flags */
    /* 0x2338 */ mPr_day_day_c nw_visitor;           /* info for how many unique days the player has talked to Sable */
    /* 0x233E */ mPr_day_day_c radiocard;            /* radio stamp days */
    /* 0x2344 */ mPr_sunburn_c sunburn;              /* sunburn state */
    /* 0x234A */ u8 _234A[14];                 /* seemingly unused data */
    /* 0x2358 */ mActor_name_t birthday_present_npc; /* npc id of the 'best friend' villger who will gift the player a
                                                        present on their birthday (at the door) */
    /* 0x235A */ u8 golden_items_collected;          /* bitfield tracking which golden items the player has received */
    /* 0x235B */ u8 kanji_pl_lv;
    /* 0x235C */ u8 reset_center_flags;
    /* 0x2360 */ u32 soncho_trophy_field1;           /* remaining tortimer event flags */
    /* 0x2364 */ mPr_carde_data_c ecard_letter_data; /* info relating to scanned e-Card letters */
    /* 0x2396 */ u8 _2396[10];
    /* 0x23A0 */ mPr_birthday_msg_info_c birthday_msg_info;
    /* 0x264A */ u8 _264A[2];
    /* 0x264C */ mPr_pwdInfo_c pwdInfo[ANIMAL_NUM_MAX];
    /* 0x2688 */ u16 new_music_card_scanned; // bitfield tracking which music cards have been scanned
};

extern void mPr_ClearPlayerName(u8* buf);
extern void mPr_CopyPlayerName(u8* dst, u8* src);
extern int mPr_NullCheckPlayerName(u8* name_p);
extern int mPr_CheckCmpPlayerName(u8* name0, u8* name1);
extern int mPr_GetPlayerName(u8* buf, int player_no);
extern int mPr_NullCheckPersonalID(PersonalID_c* pid);
extern void mPr_ClearPersonalID(PersonalID_c* pid);
extern void mPr_ClearAnyPersonalID(PersonalID_c* pid, int count);
extern void mPr_CopyPersonalID(PersonalID_c* dst, PersonalID_c* src);
extern int mPr_CheckCmpPersonalID(PersonalID_c* pid0, PersonalID_c* pid1);
extern void mPr_ClearPrivateBirthday(mPr_birthday_c* birthday);
extern void mPr_ClearAnimalMemory(mPr_animal_memory_c* memory);
extern void mPr_ClearPrivateInfo(Private_c* private_info);
extern void mPr_SetNowPrivateCloth();
extern void mPr_InitPrivateInfo(Private_c* priv);
extern void mPr_CopyPrivateInfo(Private_c* dst, Private_c* src);
extern int mPr_CheckPrivate(Private_c* priv);
extern int mPr_CheckCmpPrivate(Private_c* priv0, Private_c* priv1);
extern int mPr_GetPrivateIdx(PersonalID_c* pid);
extern int mPr_GetPossessionItemIdx(Private_c* priv, mActor_name_t item);
extern int mPr_GetPossessionItemIdxWithCond(Private_c* priv, mActor_name_t item, u32 cond);
extern int mPr_GetPossessionItemIdxFGTypeWithCond_cancel(Private_c* priv, mActor_name_t fg_type, u32 cond,
                                                         mActor_name_t cancel_item);
extern int mPr_GetPossessionItemIdxItem1Category(Private_c* priv, u8 item1_type);
extern int mPr_GetPossessionItemIdxItem1CategoryWithCond_cancel(Private_c* priv, u8 item1_type, u32 cond,
                                                                mActor_name_t cancel_item);
extern int mPr_GetPossessionItemIdxKindWithCond(Private_c* priv, mActor_name_t kind_start, mActor_name_t kind_end,
                                                u32 cond);
extern u32 mPr_GetPossessionItemSum(Private_c* priv, mActor_name_t item);
extern u32 mPr_GetPossessionItemSumWithCond(Private_c* priv, mActor_name_t item, u32 cond);
#define mPr_GetFreePossessionItemSum(priv) mPr_GetPossessionItemSumWithCond(priv, EMPTY_NO, mPr_ITEM_COND_NORMAL)
extern u32 mPr_GetPossessionItemSumFGTypeWithCond_cancel(Private_c* priv, mActor_name_t fg_type, u32 cond,
                                                         mActor_name_t cancel_item);
extern u32 mPr_GetPossessionItemSumItemCategoryWithCond_cancel(Private_c* priv, u8 item1_type, u32 cond,
                                                               mActor_name_t cancel_item);
extern u32 mPr_GetPossessionItemSumItemCategoryWithCond(Private_c* priv, u8 item1_type, u32 cond);
extern u32 mPr_GetPossessionItemSumKindWithCond(Private_c* priv, mActor_name_t kind_start, mActor_name_t kind_end,
                                                u32 cond);
extern void mPr_SetItemCollectBit(mActor_name_t item);
extern mActor_name_t mPr_DummyPresentToTruePresent();
extern void mPr_SetPossessionItem(Private_c* priv, int idx, mActor_name_t item, u32 cond);
extern int mPr_SetFreePossessionItem(Private_c* priv, mActor_name_t item, u32 cond);
extern void mPr_AddFirstJobHint(Private_c* priv);
extern int mPr_GetFirstJobHintTime(Private_c* priv);
extern int mPr_CheckFirstJobHint(Private_c* priv);
extern s16 mPr_GetMoneyPower();
extern s16 mPr_GetGoodsPower();
extern int mPr_CheckMuseumAddress(Private_c* priv);
extern int mPr_CheckMuseumInfoMail(Private_c* priv);
extern Private_c* mPr_GetForeignerP();
extern int mPr_LoadPak_and_SetPrivateInfo2(Private_c* unused_private, u8 player_no);
extern void mPr_ClearMotherMailInfo(mPr_mother_mail_info_c* mother_mail);
extern void mPr_SendMailFromMother();
extern void mPr_SendForeingerAnimalMail(Private_c* priv);
extern void mPr_StartSetCompleteTalkInfo();
extern void mPr_SetFishCompleteTalk();
extern int mPr_CheckFishCompleteTalk(u8 player_no);
extern void mPr_SetInsectCompleteTalk();
extern int mPr_CheckInsectCompleteTalk(u8 player_no);
extern int mPr_GetFishCompTalkPermission();
extern int mPr_GetInsectCompTalkPermission();
extern void mPr_ClearMapInfo(mPr_map_info_c* map_info, int max);
extern int mPr_GetThisLandMapIdx(mPr_map_info_c* map_info, int max);
extern void mPr_SetNewMap(mPr_map_info_c* map_info, int max);
extern void mPr_RenewalMapInfo(mPr_map_info_c* map_info, int max, mLd_land_info_c* land_info);
extern void mPr_RandomSetPlayerData_title_demo();
extern void mPr_PrintMapInfo_debug(gfxprint_t* gfxprint);

extern Private_c g_foreigner_private;

#ifdef __cplusplus
}
#endif

#endif
