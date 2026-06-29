#ifndef M_ISLAND_H
#define M_ISLAND_H

#include "types.h"
#include "m_island_h.h"
#include "m_personal_id.h"
#include "m_npc.h"
#include "m_land.h"
#include "m_field_make.h"
#include "m_home.h"
#include "m_needlework.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: verify these names
enum {
    mISL_NPC_DAY_TYPE_NOT_EXIST, // islander doesn't exist
    mISL_NPC_DAY_TYPE_APPEARED_TODAY, // islander appeared today (player spoke to them)
    mISL_NPC_DAY_TYPE_NORMAL, // normal
    mISL_NPC_DAY_TYPE_LEAVING_TOMORROW, // islander is leaving tomorrow

    mISL_NPC_DAY_TYPE_NUM
};

#define mISL_PLAYER_ACTION_NUM 32

#define mISL_PLAYER_ACTION_DIG_SCOOP (1 << 0)
#define mISL_PLAYER_ACTION_PLANT_FLOWER (1 << 1)
#define mISL_PLAYER_ACTION_CHANGE_FLAG (1 << 2)
#define mISL_PLAYER_ACTION_SHAKE_TREE (1 << 3)
#define mISL_PLAYER_ACTION_TRAMPLE_FLOWER (1 << 4)
#define mISL_PLAYER_ACTION_TRAMPLE_ALL_FLOWERS (1 << 5) // seems to be incorrectly? set when only a single flower was trampled
#define mISL_PLAYER_ACTION_CHOP_PALM_TREE (1 << 6)
#define mISL_PLAYER_ACTION_CHOP_TREE (1 << 7)
#define mISL_PLAYER_ACTION_PLANT_TREE (1 << 8)
#define mISL_PLAYER_ACTION_UZAI_PUSHED (1 << 9)
#define mISL_PLAYER_ACTION_UZAI_HIT (1 << 10)
#define mISL_PLAYER_ACTION_BEST_FRIEND (1 << 11) // seemingly unused but based on intention from dialogue
#define mISL_PLAYER_ACTION_UZAI_HIT_NET (1 << 12) // set at the same time as "UZAI_HIT"
#define mISL_PLAYER_ACTION_FALL_PITFALL (1 << 13)
#define mISL_PLAYER_ACTION_PLANT_APPLE_TREE (1 << 14)
#define mISL_PLAYER_ACTION_PLANT_PEACH_TREE (1 << 15)
#define mISL_PLAYER_ACTION_PLANT_CHERRY_TREE (1 << 16)
#define mISL_PLAYER_ACTION_PLANT_PEAR_TREE (1 << 17)
#define mISL_PLAYER_ACTION_PLANT_ORANGE_TREE (1 << 18)
#define mISL_PLAYER_ACTION_PLANT_COCONUT_TREE (1 << 19)
#define mISL_PLAYER_ACTION_PICKUP_COCONUT (1 << 20)
#define mISL_PLAYER_ACTION_EAT_COCONUT (1 << 21)
#define mISL_PLAYER_ACTION_TUMBLE (1 << 22)
#define mISL_PLAYER_ACTION_DESTINY_POPULAR (1 << 23)
#define mISL_PLAYER_ACTION_DESTINY_UNPOPULAR (1 << 24)
#define mISL_PLAYER_ACTION_DESTINY_BAD_LUCK (1 << 25)
#define mISL_PLAYER_ACTION_DESTINY_MONEY_LUCK (1 << 26)
#define mISL_PLAYER_ACTION_DESTINY_GOODS_LUCK (1 << 27)
#define mISL_PLAYER_ACTION_SEX_MALE (1 << 28)
#define mISL_PLAYER_ACTION_SEX_FEMALE (1 << 29)
#define mISL_PLAYER_ACTION_TRADE_CLOTH (1 << 30)
#define mISL_PLAYER_ACTION_NOTICE_FISHING_ROD (1 << 31)

// Around-town actions
#define mISL_VILLAGE_PLAYER_ACTION_NUM 28

#define mISL_VILLAGE_PLAYER_ACTION_PLANT_MONEY_TREE (1 << 2)
#define mISL_VILLAGE_PLAYER_ACTION_HIT_ROCK (1 << 6)
#define mISL_VILLAGE_PLAYER_ACTION_PUT_ITEM (1 << 9)
#define mISL_VILLAGE_PLAYER_ACTION_PICKUP_ITEM (1 << 10)
#define mISL_VILLAGE_PLAYER_ACTION_PICKUP_PRESENT (1 << 11)
#define mISL_VILLAGE_PLAYER_ACTION_PUT_DUST (1 << 19)
#define mISL_VILLAGE_PLAYER_ACTION_BURY_DUST (1 << 20)
#define mISL_VILLAGE_PLAYER_ACTION_PICKUP_DUST (1 << 21)
#define mISL_VILLAGE_PLAYER_ACTION_SHAKE_BEES (1 << 23)
#define mISL_VILLAGE_PLAYER_ACTION_REMOVE_GRASS (1 << 24)

extern void mISL_ClearKeepIsland(void);
extern void mISL_ChangeBG(void);
extern void mISL_RestoreIsland(void);
extern void mISL_init(Island_c* island);
extern void mISL_SetHouseIdx(int player_no);
extern int mISL_GetNpcDayType(Island_c* island);
extern int mISL_CheckAppearIslandNpc_com(mHm_hs_c* home, PersonalID_c* pid);
extern int mISL_CheckAppearIslandNpc(void);
extern void mISL_ClearNowPlayerAction_island(void);
extern void mISL_ClearNowPlayerAction_land(void);
extern void mISL_SetPlayerAction(PersonalID_c* pid, u32 action);
extern void mISL_SetNowPlayerAction(u32 action);
extern void mISL_UnsetPlayerAction(PersonalID_c* pid, u32 action);
extern void mISL_UnsetNowPlayerAction(u32 action);
extern int mISL_CheckPlayerAction(PersonalID_c* pid, u32 action);
extern int mISL_CheckNowPlayerAction(u32 action);
extern void mISL_MoveNowPlayerAction(void);
extern int mISL_GetNowPlayerActionNum_land(void);

#ifdef __cplusplus
}
#endif

#endif
