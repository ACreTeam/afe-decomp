#ifndef M_AGB_PP_H
#define M_AGB_PP_H

#include "types.h"
#include "m_actor_type.h"
#include "m_personal_id.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mAP_GAME_DARUMASANGAKORONDA, // red-light green-light
    mAP_GAME_DONJANKEN,          // balance
    mAP_GAME_NAKADOJJI,          // dodgeball

    mAP_GAME_NUM
};

extern u8* mAP_set_world_info4(u8* buf);
extern int mAP_agb_game_type_to_npc_num(int game_type);
extern void mAP_decide_today_agb_game(void);
extern int mAP_select_agb_game_npc(mActor_name_t* npc_name_tbl, int count);
extern u32 mAP_make_send_data(u8* buf, mActor_name_t npc0_name, mActor_name_t npc1_name, mActor_name_t npc2_name,
                              mActor_name_t npc3_name, mActor_name_t npc4_name, int sex, int face, PersonalID_c* pid);
extern int mAP_receive_data_to_agb_game_type(u8* data);
extern int mAP_receive_data_to_agb_game_result(u8* data);
extern void mAP_receive_data_to_agb_friendship(s8* npc0_friendship, s8* npc1_friendship, s8* npc2_friendship,
                                               s8* npc3_friendship, s8* npc4_friendship, u8* data);
extern void mAP_receive_data_to_agb_npc_name(u8* dst, u8* data, int idx);
extern void mAP_receive_data_to_agb_distinguish(u16* npc0_distinguish, u16* npc1_distinguish, u16* npc2_distinguish,
                                                u16* npc3_distinguish, u16* npc4_distinguish, u8* data);
extern void mAP_receive_data_to_agb_personalID(PersonalID_c* pid, u8* data);
extern int mAP_receive_data_to_update_already(u8* data);
extern int mAP_receive_data_to_topic_npc_receive_index(u8* data);

#ifdef __cplusplus
}
#endif
#endif // M_AGB_PP_H
