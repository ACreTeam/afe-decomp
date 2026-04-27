#ifndef M_ADD_NPC_H
#define M_ADD_NPC_H

#include "types.h"
#include "m_npc_personal_id.h"
#include "m_npc.h"

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
    /* 0x1A */ s16 voice_melody; // voice sound
    /* 0x1C */ u8 love_cloth_type;
    /* 0x1D */ u8 hate_cloth_type;
    /* 0x1E */ u8 _1E;
    /* 0x1F */ u8 _1F;
    /* 0x20 */ u8 agb_param[8];
    /* 0x40 */ u8 texture[0x1A80] ATTRIBUTE_ALIGN(32);
} AddNpcData_c;

/* sizeof(AddNpcInfo_c) == 0x1FC60 */
typedef struct add_npc_info_s {
    /* 0x00000 */ AddNpcData_c data[mAN_ANIMAL_NUM]; // aligned to 32 bytes
    /* 0x1FC40 */ int set_bitfield;
} AddNpcInfo_c;

#ifdef __cplusplus
}
#endif

#endif
