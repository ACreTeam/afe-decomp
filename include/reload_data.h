#ifndef RELOAD_DATA_H
#define RELOAD_DATA_H

#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void reload_data_init(GAME* game);
extern void reload_data_cleanup(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
