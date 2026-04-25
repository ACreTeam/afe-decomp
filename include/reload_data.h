#ifndef RELOAD_DATA_H
#define RELOAD_DATA_H

#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reload_data_s {
    GAME game;
    u8 _E4[0xCC18 - 0xE4];
} GAME_RELOAD_DATA;

extern void reload_data_init(GAME* game);
extern void reload_data_cleanup(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
