#ifndef M_MAIL_H
#define M_MAIL_H

#include "types.h"
#include "m_personal_id.h"
#include "m_npc_personal_id.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAIL_HEADER_BASE_LEN 16
#define MAIL_HEADER_LEN (MAIL_HEADER_BASE_LEN - PLAYER_NAME_LEN)
#define MAIL_FOOTER_LEN 16
#define MAIL_BODY_LEN 96

#define MAIL_FOOTER2_LEN 48
#define MAIL_HEADER2_LEN (MAIL_FOOTER2_LEN - PLAYER_NAME_LEN)

#define mMl_POSTOFFICE_GIFT_NUM 4

#define mMl_MUSEUM_INFO_MAIL_NO 189 // TODO: enum?

enum {
    mMl_NAME_TYPE_PLAYER,
    mMl_NAME_TYPE_NPC,
    mMl_NAME_TYPE_MUSEUM,

    mMl_NAME_TYPE_NUM,
    mMl_NAME_TYPE_CLEAR = 0xFF
};

enum {
    mMl_FONT_RECV,                     /* Received letter (with or without a present attached), unread */
    mMl_FONT_SEND,                     /* Player-written letter */
    mMl_FONT_RECV_READ,                /* Recieved letter, with/without present, and then read it */
    mMl_FONT_RECV_PLAYER_PRESENT,      /* Recieved letter where present was attached, unread */
    mMl_FONT_RECV_PLAYER_PRESENT_READ, /* Recieved letter where present was attached, read */

    mMl_FONT_NUM
};

enum {
    mMl_DATA,
    mMl_DATA2,

    mMl_DATA_NUM
};

enum {
    mMl_TYPE_MAIL,
    mMl_TYPE_XMAS,
    mMl_TYPE_SHOP_SALE_LEAFLET,
    mMl_TYPE_BROKER_SALE_LEAFLET,
    mMl_TYPE_MOTHER,
    mMl_TYPE_OMIKUJI,
    mMl_TYPE_HRA,
    mMl_TYPE_SHOP,
    mMl_TYPE_SNOWMAN,
    mMl_TYPE_FISHING_CONTENST,
    mMl_TYPE_POSTOFFICE,
    mMl_TYPE_SPNPC_PASSWORD,

    mMl_TYPE_NUM
};

/* sizeof(Mail_nm_c) == 0x12 */
typedef struct mail_nm_s {
    /* 0x00 */ PersonalID_c personalID;
    /* 0x10 */ u8 type;
} Mail_nm_c;

/* sizeof(mail_header_save_s) == 0x36 */
typedef struct mail_header_save_s {
    /* 0x00 */ s8 header_back_start;
    /* 0x01 */ u8 unknown;
    /* 0x02 */ u16 header[MAIL_HEADER_LEN];
    /* 0x16 */ u16 footer[MAIL_FOOTER_LEN];
} Mail_hs_c;

/* sizeof(Mail_hdr_c) == 0x24 */
typedef struct mail_header_s {
    /* 0x00 */ Mail_nm_c recipient;
    /* 0x12 */ Mail_nm_c sender;
} Mail_hdr_c;

typedef struct mail_text_content_s {
    /* 0x00 */ u8 header[MAIL_HEADER_LEN];
    /* 0x0A */ u8 _0A[4];
    /* 0x0E */ u8 body[MAIL_BODY_LEN];
    /* 0x6E */ u8 _56[14];
    /* 0x7C */ u8 footer[MAIL_FOOTER_LEN];
} Mail_text_content_c;

typedef union {
    Mail_text_content_c split;
    u8 all[0x90];
} Mail_text_u;

/* sizeof(Mail_ct_c) == 0x94 */
typedef struct mail_content_s {
    /* 0x00 */ u8 font;
    /* 0x01 */ u8 header_back_start;
    /* 0x02 */ u8 mail_type;
    /* 0x03 */ u8 paper_type;
    /* 0x04 */ Mail_text_u text;
} Mail_ct_c;

/* sizeof(Mail_c) == 0xBA */
typedef struct mail_s {
    /* 0x000 */ Mail_hdr_c header;
    /* 0x02C */ mActor_name_t present;
    /* 0x026 */ Mail_ct_c content;
} Mail_c;



extern int mMl_strlen(u8* str, int size, u8 end_char);
extern int mMl_strlen2(int* found, u8* str, int size, u8 end_char);
extern void mMl_clear_mail_header(Mail_hdr_c* header);
extern void mMl_clear_mail(Mail_c* mail);
extern void mMl_clear_mail_box(Mail_c* mail, int num);
extern int mMl_check_not_used_mail(Mail_c* mail);
extern void mMl_copy_header_name(Mail_nm_c* dst, Mail_nm_c* src);
extern void mMl_set_to_plname(Mail_c* mail, PersonalID_c* pid);
extern void mMl_set_playername(Mail_c* mail, PersonalID_c* pid);
extern void mMl_init_mail(Mail_c* mail, PersonalID_c* pid);
extern int mMl_chk_mail_free_space(Mail_c* mail, int num);
extern int mMl_count_use_mail_space(Mail_c* mail, int num);
extern void mMl_copy_mail(Mail_c* dst, Mail_c* src);
extern void mMl_clear_mail_header_common(Mail_hs_c* header);
extern void mMl_set_mail_name_npcinfo(Mail_nm_c* name, AnmPersonalID_c* anm_pid);
extern int mMl_get_npcinfo_from_mail_name(AnmPersonalID_c* anm_pid, Mail_nm_c* name);
extern int mMl_hunt_for_send_address(Mail_c* mail);
extern int mMl_check_send_mail(Mail_c* mail);
extern int mMl_check_set_present_myself(Mail_c* mail);
extern int mMl_send_mail_box(PersonalID_c* recipient_pid, int player_no, Mail_c* mail, mActor_name_t present,
                             mActor_name_t paper, int mail_no, u8* sender_name, u32 proc_type);
extern int mMl_send_mail_postoffice(PersonalID_c* recipient_pid, int player_no, mActor_name_t present,
                                    mActor_name_t paper, int mail_no, u8* sender_name, u32 proc_type, u8 mail_type);
extern int mMl_send_mail(PersonalID_c* recipient_pid, int player_no, mActor_name_t present, mActor_name_t paper,
                         int mail_no, u8* sender_name, u32 proc_type);
extern void mMl_start_send_mail();

#ifdef __cplusplus
}
#endif

#endif
