#ifndef M_BIRTHDAY_MSG_H
#define M_BIRTHDAY_MSG_H

#include "types.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int mBm_check_birthday(int player_no);
extern int mBm_receive_msg(int previous_player_no);
extern int mBm_chk_send_birthday_msg(int birthday_player_no);
extern mPr_birthday_msg_c* mBm_get_receive_are(int player_no);
extern void mBm_bdmsg_to_mailc(mPr_birthday_msg_c* msg, Mail_c* mail, int player_no);
extern void mBm_mailc_to_bdmsg(Mail_c* mail, mPr_birthday_msg_c* msg);
extern int mBm_chk_sing_birthday(void);
extern void mBm_check_birthday_msg(void);
extern int mBm_get_validity_birthday_msg_num(void);
extern mPr_birthday_msg_c* mBm_get_validity_birthday_msg(int index);
extern Mail_c* mBm_work_area_Mail(void);

#ifdef __cplusplus
}
#endif
#endif // M_BIRTHDAY_MSG_H
