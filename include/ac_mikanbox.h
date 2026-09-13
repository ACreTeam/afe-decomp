#ifndef AC_MIKANBOX_H
#define AC_MIKANBOX_H

#include "types.h"
#include "m_actor.h"
#include "ac_mikanbox_clip.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mikanbox_actor_s {
    STRUCTURE_ACTOR s_actor;
} MIKANBOX_ACTOR;

extern ACTOR_PROFILE Mikanbox_Profile;

extern void aMKBC_header_draw(GAME_PLAY* play, int timer);
extern void aMKBC_body_draw(GAME_PLAY* play, int timer);
extern void aMKBC_footer_draw(GAME_PLAY* play, int timer);
extern void aNTT_bdmsg_h_start(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play);
extern void aNTT_bdmsg_b_start(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play);
extern void aNTT_bdmsg_f_start(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
