#ifndef M_BOARD_OVL_H
#define M_BOARD_OVL_H

#include "types.h"
#include "m_board_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_mail.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mBD_MAX_WIDTH 192
#define mBD_BODY_LINE_NUM 6

enum {
    mBD_FIELD_HEADER,
    mBD_FIELD_BODY,
    mBD_FIELD_FOOTER,

    mBD_FIELD_NUM
};

enum {
    mBD_LINE_CHECK_OK,
    mBD_LINE_CHECK_NEWLINE,
    mBD_LINE_CHECK_OVERLINE,
    mBD_LINE_CHECK_OVERSTRING,

    mBD_LINE_CHECK_NUM
};

enum {
    mBD_HEADER_POS_PRE_NAME,
    mBD_HEADER_POS_ON_NAME,
    mBD_HEADER_POS_POST_NAME,

    mBD_HEADER_POS_NUM
};

typedef struct {
    u16 header[MAIL_HEADER_LEN];
    u16 body[MAIL_BODY_LEN];
    u16 footer[MAIL_FOOTER_LEN];
} MailW_text_content_c;

typedef union {
    MailW_text_content_c split;
    u16 all[MAIL_HEADER_LEN + MAIL_BODY_LEN + MAIL_FOOTER_LEN];
} MailW_text_u;

typedef struct {
    u8 font;
    u8 header_back_start;
    u8 mail_type;
    u8 paper_type;
    MailW_text_u text;
} MailW_ct_c;

typedef struct {
    Mail_hdr_c header;
    mActor_name_t present;
    MailW_ct_c content;
} MailW_c;

struct board_ovl_s {
    u8 field;
    u8 center_line;
    u8 header_pos;
    u8 header_name_len;
    u8 first;
    u8 lengths[mBD_FIELD_NUM];
    Mail_c* dst_p;
    MailW_c mail;
    f32 ofs_x;
    f32 ofs_y;
    int _134;
    int _138;
};

extern void mBD_board_ovl_set_proc(Submenu* submenu);
extern void mBD_board_ovl_construct(Submenu* submenu);
extern void mBD_board_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
