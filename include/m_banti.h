#ifndef M_BANTI_H
#define M_BANTI_H

#include "types.h"
#include "m_play_h.h"
#include "c_keyframe.h"
#include "m_time.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    banti_ANIM_STATE_STOPPED,
    banti_ANIM_STATE_PLAYING,

    banti_ANIM_STATE_NUM
};

extern void banti_ct();
extern void banti_dt();
extern void banti_move(GAME_PLAY* play);
extern void banti_draw(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
