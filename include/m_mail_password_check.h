#ifndef M_MAIL_PASSWORD_CHECK_H
#define M_MAIL_PASSWORD_CHECK_H

#include "types.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMpswd_OLD_PASSWORD_DATA_LEN 17
#define mMpswd_OLD_PASSWORD_STR_LEN 22
#define mMpswd_OLD_PASSWORD_BITS_LEN 132

#define mMpswd_PASSWORD_KEY_IDX 1
#define mMpswd_PASSWORD_DATA_LEN 24
#define mMpswd_PASSWORD_STR_LEN 32

#define mMpswd_BITMIX_CODE_IDX 1
#define mMpswd_RSA_R_PRIME_IDX 12
#define mMpswd_RSA_INFO_IDX 3
#define mMpswd_RSA_KEYSAVE_IDX 23

#define mMpswd_SPECIAL_NPC_NUM 32

enum {
    mMpswd_CODETYPE_FAMICOM,
    mMpswd_CODETYPE_NPC,
    mMpswd_CODETYPE_CARD_E,
    mMpswd_CODETYPE_MAGAZINE,
    mMpswd_CODETYPE_USER,
    mMpswd_CODETYPE_CARD_E_MINI,
    mMpswd_CODETYPE_NPC_NEW,
    mMpswd_CODETYPE_MONUMENT,

    mMpswd_CODETYPE_NUM
};

enum {
    mMpswd_NPCTYPE_NORMAL,
    mMpswd_NPCTYPE_SPECIAL,
    mMpswd_NPCTYPE_ADD_NPC,

    mMpswd_NPCTYPE_NUM
};

enum {
    mMpswd_VERSION_OLD,
    mMpswd_VERSION_NEW,
    mMpswd_VERSION_BAD,

    mMpswd_VERSION_NUM = mMpswd_VERSION_BAD
};

enum {
    mMpswd_SEND_TYPE_CORRECT,
    mMpswd_SEND_TYPE_NG,
    mMpswd_SEND_TYPE_2,
    mMpswd_SEND_TYPE_3,
    mMpswd_SEND_TYPE_OLD_CORRECT,

    mMpswd_SEND_TYPE_NUM
};

typedef struct mail_check_password_s {
    int version;
    u8 type;
    u8 hit_rate_index;
    mActor_name_t item;
    u8 checksum;
    u8 npc_type;
    u8 npc_code;
    u8 _0B;
    u8 bx;
    u8 bz;
    u32 price;
    u8 str0[PLAYER_NAME_LEN];
    u8 str1[PLAYER_NAME_LEN];
    u8 str2[PLAYER_NAME_LEN];
} mMpswd_password_c;

extern u32 pswd_famicom_list_max;
extern u16 pswd_famicom_list[];
extern u32 pswd_present_list_max;
extern u16 pswd_present_list[];
extern u32 pswd_old_famicom_list_max;
extern u16 pswd_old_famicom_list[];

extern void mMpswd_make_password(u8* password_buf, int type, int hit_rate, u8* str0, u8* str1, u8* str2, mActor_name_t item,
                                 int npc_type, int npc_code);

extern int mMpswd_new_decode_code(u8* password_data, u8* password_str);
extern int mMpswd_restore_code(u8* password, u8* body);
extern void mMpswd_password(mMpswd_password_c* password, u8* data);
extern int mMpswd_password_zuru_check(mMpswd_password_c* password);
extern int mMpswd_new_check_present_user(mActor_name_t item);
extern int mMpswd_check_present(mMpswd_password_c* password);
extern mActor_name_t mMpswd_get_sp_npc_num(int sp_npc);
extern int mMpswd_check_npc_code(mMpswd_password_c* password);
extern int mMpswd_check_name(mMpswd_password_c* password);

extern void mMpswd_ClearHPMail(AnmHPMail_c* hp_mail, int count);
extern void mMpswd_AllClearHPMailPlayerIdx(int idx);
extern int mMpswd_ReceiveHPMail(Mail_c* mail);
extern void mMpswd_SendHPMail(void);

#ifdef __cplusplus
}
#endif

#endif
