#include "m_birthday_msg.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "libultra/libultra.h"
#include "m_font.h"

static u16 mBm_cnv_date(u8 month, u8 day) {
    return (month << 8) | day;
}

static int mBm_check_date_range(u16 birthday, u16 tomorrow, u16 next_week) {
    if (tomorrow > next_week) {
        int ret = FALSE;
        if (tomorrow <= birthday || birthday <= next_week) {
            ret = TRUE;
        }

        return ret;
    } else {
        int ret = FALSE;
        if (tomorrow <= birthday && birthday <= next_week) {
            ret = TRUE;
        }

        return ret;
    }
}

static int mBm_check_out_term_local(lbRTC_time_c* time) {
    lbRTC_time_c next_week;
    lbRTC_time_c last_week;

    lbRTC_TimeCopy(&next_week, Common_GetPointer(time.rtc_time));
    lbRTC_Add_DD(&next_week, lbRTC_WEEK + 1);
    lbRTC_TimeCopy(&last_week, Common_GetPointer(time.rtc_time));
    lbRTC_Sub_DD(&last_week, lbRTC_WEEK + 1);

    if (lbRTC_IsOverTime(time, &last_week) == lbRTC_OVER || lbRTC_IsOverTime(&next_week, time) == lbRTC_OVER) {
        return TRUE;
    }

    return FALSE;
}

static void mBm_check_out_term(int player_no) {
    if (player_no != mPr_FOREIGNER) {
        int mask;
        int i;
        mPr_birthday_msg_info_c* info = &Save_Get(private_data[player_no]).birthday_msg_info;

        for (i = 0; i < PLAYER_NUM; i++) {
            mask = 1 << i;

            if (info->flags & mask) {
                if (mBm_check_out_term_local(&info->msgs[i].time)) {
                    info->flags &= ~mask;
                }
            }
        }
    }
}

static mPr_birthday_msg_c* mBm_get_receive_are_local_rewrite(mPr_birthday_msg_info_c* info, PersonalID_c* pid) {
    mPr_birthday_msg_c* msg;
    int mask;
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        mask = 1 << i;

        if (info->flags & mask) {
            msg = &info->msgs[i];
            if (mPr_CheckCmpPersonalID(pid, &msg->id)) {
                if (mBm_check_out_term_local(&msg->time)) {
                    info->flags &= ~mask;
                } else {
                    return msg;
                }
            }
        }
    }

    return NULL;
}

static int mBm_get_receive_are_local_null(mPr_birthday_msg_info_c* info) {
    int mask;
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        mask = 1 << i;

        if ((info->flags & mask) == 0) {
            return i;
        }
    }

    return -1;
}

static int mBm_get_receive_are_local_ancent(mPr_birthday_msg_info_c* info) {
    int i;
    int ret = 0;

    for (i = 1; i < PLAYER_NUM; i++) {
        if (lbRTC_IsOverTime(&info->msgs[i].time, &info->msgs[ret].time) == lbRTC_OVER) {
            // @BUG - this seems to be intended to pick the 'oldest' birthday message,
            // but the dev always assigns 0 to the result (first message).
#ifndef BUGFIXES
            ret = 0;
#else
            ret = i;
#endif
        }
    }

    return ret;
}

static void mBm_init_BDMsg_Mail(mPr_birthday_msg_c* msg, PersonalID_c* pid, int birthday_player_no, u8 clear_char) {
    static u8 header_str[] = { CHAR_PP_010, CHAR_PP_195, CHAR_PP_028 };
    static u8 footer_str[] = { CHAR_PP_096, CHAR_PP_124 };
    PersonalID_c* birthday_pid = &Save_Get(private_data[birthday_player_no]).player_ID;
    int name_len;

    bzero(msg, sizeof(mPr_birthday_msg_c));
    mPr_CopyPersonalID(&msg->id, pid);
    lbRTC_TimeCopy(&msg->time, Common_GetPointer(time.rtc_time));
    msg->header_back_start = 0;
    mem_clear(msg->header, sizeof(msg->header), clear_char);
    name_len = mMl_strlen(birthday_pid->player_name, sizeof(birthday_pid->player_name), CHAR_PP_032);
    mem_copy(msg->header, birthday_pid->player_name, name_len);
    mem_copy(msg->header + name_len, header_str, sizeof(header_str));

    mem_clear(msg->body, sizeof(msg->body), clear_char);
    mem_clear(msg->footer, sizeof(msg->footer), clear_char);

    name_len = mMl_strlen(pid->player_name, sizeof(pid->player_name), CHAR_PP_032);
    mem_copy(msg->footer, pid->player_name, name_len);
    mem_copy(msg->footer + name_len, footer_str, sizeof(footer_str));
}

static int mBm_check_near_birthday(int player_no) {
    lbRTC_time_c* time = Common_GetPointer(time.rtc_time);
    Private_c* priv;
    lbRTC_time_c tomorrow;
    lbRTC_time_c next_week;
    u16 tomrrow_md;
    u16 next_week_md;
    u16 birthday_md;

    if (player_no >= mPr_FOREIGNER) {
        return FALSE;
    }

    priv = Save_GetPointer(private_data[player_no]);
    if (mPr_NullCheckPersonalID(&priv->player_ID)) {
        return FALSE;
    }

    if (priv->birthday.month == 0xFF) {
        return FALSE;
    }

    lbRTC_TimeCopy(&tomorrow, time);
    lbRTC_TimeCopy(&next_week, time);
    lbRTC_Add_DD(&tomorrow, 1);
    lbRTC_Add_DD(&next_week, lbRTC_WEEK);

    tomrrow_md = mBm_cnv_date(tomorrow.month, tomorrow.day);
    next_week_md = mBm_cnv_date(next_week.month, next_week.day);
    birthday_md = mBm_cnv_date(priv->birthday.month, priv->birthday.day);
    return mBm_check_date_range(birthday_md, tomrrow_md, next_week_md);
}

extern int mBm_receive_msg(int previous_player_no) {
    int i;
    int current_player_no = Common_Get(player_no);
    int candidate_player_no = previous_player_no + 1;

    for (i = 0; i < PLAYER_NUM; i++) {
        candidate_player_no &= PLAYER_NUM - 1;

        if (candidate_player_no != current_player_no && mBm_check_near_birthday(candidate_player_no) &&
            !mBm_chk_send_birthday_msg(candidate_player_no)) {
            return candidate_player_no;
        }

        candidate_player_no++;
    }
        
    candidate_player_no = previous_player_no + 1;
    for (i = 0; i < PLAYER_NUM; i++) {
        candidate_player_no &= PLAYER_NUM - 1;

        if (candidate_player_no != current_player_no && mBm_check_near_birthday(candidate_player_no)) {
            return candidate_player_no;
        }

        candidate_player_no++;
    }
    return -1;
}

extern int mBm_chk_send_birthday_msg(int birthday_player_no) {
    mPr_birthday_msg_info_c* info = &Save_Get(private_data[birthday_player_no]).birthday_msg_info;
    PersonalID_c* pid = &Now_Private->player_ID;

    return mBm_get_receive_are_local_rewrite(info, pid) != NULL;
}

extern mPr_birthday_msg_c* mBm_get_receive_are(int player_no) {
    PersonalID_c* pid = &Now_Private->player_ID;
    mPr_birthday_msg_info_c* info = &Save_Get(private_data[player_no]).birthday_msg_info;
    mPr_birthday_msg_c* msg = mBm_get_receive_are_local_rewrite(info, pid);
    int idx;

    if (msg != NULL) {
        return msg;
    }

    idx = mBm_get_receive_are_local_null(info);
    if (idx == -1) {
        idx = mBm_get_receive_are_local_ancent(info);

        // NOTE: this cannot pass because mBm_get_receive_are_local_ancent never returns -1
        if (idx == -1) {
            return &Now_Private->birthday_msg_info.msgs[0];
        }
    }

    msg = &info->msgs[idx];
    info->flags |= 1 << idx;
    mBm_init_BDMsg_Mail(msg, pid, player_no, CHAR_PP_032);
    return msg;
}

extern void mBm_bdmsg_to_mailc(mPr_birthday_msg_c* msg, Mail_c* mail, int player_no) {
    mMl_clear_mail(mail);
    mail->header.sender.type = mMl_NAME_TYPE_PLAYER;
    mPr_CopyPersonalID(&mail->header.sender.personalID, &msg->id);
    mail->header.recipient.type = mMl_NAME_TYPE_PLAYER;
    mPr_CopyPersonalID(&mail->header.recipient.personalID, &Save_Get(private_data[player_no]).player_ID);
    mail->content.font = mMl_FONT_SEND;
    mail->content.paper_type = (u8)(ITM_PAPER15 - ITM_PAPER_START);
    mail->content.mail_type = mMl_TYPE_MAIL;
    mail->content.header_back_start = msg->header_back_start;
    mem_copy(mail->content.text.split.header, msg->header, sizeof(msg->header));
    mem_copy(mail->content.text.split.body, msg->body, sizeof(msg->body));
    mem_copy(mail->content.text.split.footer, msg->footer, sizeof(msg->footer));
}

extern void mBm_mailc_to_bdmsg(Mail_c* mail, mPr_birthday_msg_c* msg) {
    mPr_CopyPersonalID(&msg->id, &mail->header.sender.personalID);
    lbRTC_TimeCopy(&msg->time, Common_GetPointer(time.rtc_time));
    msg->header_back_start = mail->content.header_back_start;
    mem_copy(msg->header, mail->content.text.split.header, sizeof(msg->header));
    mem_copy(msg->body, mail->content.text.split.body, sizeof(msg->body));
    mem_copy(msg->footer, mail->content.text.split.footer, sizeof(msg->footer));
}

static void mBm_clear_birthday_msg(int player_no) {
    mPr_birthday_msg_info_c* info = &Save_Get(private_data[player_no]).birthday_msg_info;

    info->flags = 0;
}

extern int mBm_chk_sing_birthday(void) {
    if (Common_Get(player_no) == mPr_FOREIGNER) {
        return FALSE;
    }

    if (mEv_ArbeitPlayer(Common_Get(player_no))) {
        return FALSE;
    }

    if (mBm_check_birthday(-1) == FALSE) {
        return FALSE;
    }

    mBm_check_out_term(Common_Get(player_no));
    
    if ((Now_Private->birthday_msg_info.flags & 0xF) == 0) {
        return FALSE;
    }

    return TRUE;
}

extern void mBm_check_birthday_msg(void) {
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        Private_c* priv = Save_GetPointer(private_data[i]);
        if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE) {
            if ((priv->birthday_msg_info.flags & 0x8000) != 0) {
                mBm_clear_birthday_msg(i);
            }
        }
    }
}

extern int mBm_get_validity_birthday_msg_num(void) {
    int num = 0;
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if ((Now_Private->birthday_msg_info.flags & (1 << i)) != 0) {
            num++;
        }
    }

    return num;
}

extern mPr_birthday_msg_c* mBm_get_validity_birthday_msg(int index) {
    mPr_birthday_msg_info_c* info = &Now_Private->birthday_msg_info;
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if ((info->flags & (1 << i)) != 0) {
            if (index == 0) {
                return &info->msgs[i];
            }
            index--;
        }
    }
    return NULL;
}

extern Mail_c* mBm_work_area_Mail(void) {
    static Mail_c static_mail;

    return &static_mail;
}

extern int mBm_check_birthday(int player_no) {
    mPr_birthday_c birthday;
    
    if (player_no < 0) {
        player_no = Common_Get(player_no);
    }

    if (player_no >= mPr_FOREIGNER) {
        birthday = Now_Private->birthday;
    } else {
        birthday = Save_Get(private_data[player_no]).birthday;
    }

    if (birthday.month == 0xFF) {
        return FALSE;
    }

    if (birthday.month == lbRTC_FEBRUARY && birthday.day == 29) {
        if (lbRTC_GetDaysByMonth(Common_Get(time.rtc_time.year), lbRTC_FEBRUARY) == 28) {
            birthday.month = lbRTC_MARCH;
            birthday.day = 1;
        }
    }

    if (Common_Get(time.rtc_time.month) != birthday.month || Common_Get(time.rtc_time.day) != birthday.day) {
        return FALSE;
    }

    return TRUE;
}
