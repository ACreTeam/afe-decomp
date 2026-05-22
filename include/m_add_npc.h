#ifndef M_ADD_NPC_H
#define M_ADD_NPC_H

#include "types.h"
#include "m_add_npc_h.h"
#include "m_npc_personal_id.h"
#include "m_npc.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mAN_ANIMAL_NUM (ANIMAL_NUM_MAX + ANIMAL_ISLAND_NUM)

typedef struct add_npc_data_s {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 name[ANIMAL_NAME_LEN];
    /* 0x07 */ u8 catchphrase[ANIMAL_CATCHPHRASE_LEN];
    /* 0x0B */ u8 race; // species/model
    /* 0x0C */ u8 is_islander;
    /* 0x0D */ u8 looks;
    /* 0x0E */ u8 shirt_no; // lower byte
    /* 0x0F */ u8 house_type;
    /* 0x10 */ u8 house_variant;
    /* 0x11 */ u8 wall_no; // lower byte
    /* 0x12 */ u8 floor_no; // lower byte
    /* 0x13 */ u8 _13;
    /* 0x14 */ u16 room_base_idx; // base layer
    /* 0x16 */ u16 room_second_idx; // second layer
    /* 0x18 */ u8 umbrella_no;
    /* 0x19 */ u8 song_no;
    /* 0x1A */ u16 voice_melody; // voice sound
    /* 0x1C */ u8 love_cloth_type;
    /* 0x1D */ u8 hate_cloth_type;
    /* 0x1E */ u8 _1E;
    /* 0x1F */ u8 _1F;
    /* 0x20 */ u8 agb_param[8];
    /* 0x40 */ u8 texture[0x1A80] ATTRIBUTE_ALIGN(32);
} AnimalInfo_c;

/* sizeof(AddNpcInfo_c) == 0x1FC60 */
typedef struct add_npc_info_s {
    /* 0x00000 */ AnimalInfo_c info[mAN_ANIMAL_NUM]; // aligned to 32 bytes
    /* 0x1FC40 */ int compress_info_table;
} AddNpcInfo_c;

/* sizeof(AddNpcNewComer_c) == 0x764 */
typedef struct add_npc_new_comer_s {
    /* 0x000 */ int new_comer_set;
    /* 0x004 */ PersonalID_c new_comer_inviter_pid; // player who invited the animal
    /* 0x014 */ lbRTC_ymd_c new_comer_invite_date; // date the animal was invited
    /* 0x018 */ mActor_name_t new_comer_npc_id; // npc id of the animal that was invited
    /* 0x01A */ u8 new_comer_data[mAN_COMPRESS_INFO_TABLE_MAX_SIZE]; // compressed data for new comer
} AddNpcNewComer_c;

/* sizeof(AddNpcSave_c) == 0x8A70 */
typedef struct add_npc_save_s {
    /* 0x000 */ int regist_add_npc;
    /* 0x004 */ u8 add_npc_compress_info_table[mAN_ANIMAL_NUM][mAN_COMPRESS_INFO_TABLE_MAX_SIZE];
} AddNpcSave_c;

typedef struct add_npc_s {
    AddNpcSave_c save;
    AddNpcNewComer_c new_comer;
} AddNpc_c;

extern void mAN_clear_compress_info_table(mActor_name_t npc_id, int* compress_info_table, AddNpcInfo_c* add_npc_info);
extern AnimalInfo_c* mAN_getP_animalInfo(mActor_name_t npc_id);
extern void mAN_set_def_animalInfo(Animal_c* animal, mActor_name_t npc_id);
extern void mAN_set_new_comer_compress_data(u8* compress_data, PersonalID_c* pid, mActor_name_t npc_id);
extern void mAN_clear_new_comer_compress_data(AddNpcNewComer_c* new_comer);
extern int mAN_get_free_compress_data_idx(int* compress_info_table);
extern void mAN_regist_add_npc_info(void);
extern void mAN_set_cd(AddNpcSave_c* add_npc_p, u8* compress_data, int add_npc_idx);
extern void mAN_regist_add_npc(void);
extern void mAN_load_add_npc_name_string(u8* name_buf, int id);
extern void mAN_set_draw_data(aNPC_draw_data_c* draw_data, mActor_name_t npc_id);
extern u8* mAN_getP_AnmAgbParam(mActor_name_t npc_id);
extern void mAN_regist_pwdInfoTable(u8 id);
extern int mAN_check_pwdInfoTable(mActor_name_t npc_id);
extern int mAN_unregist_pwdInfoTable(mActor_name_t npc_id);

#ifdef __cplusplus
}
#endif

#endif
