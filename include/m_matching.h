#ifndef M_MATCHING_H
#define M_MATCHING_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum matching_character_type {
    mMG_CHARACTER_LAZY = 0x00,
    mMG_CHARACTER_JOCK = 0x01,
    mMG_CHARACTER_CRANKY = 0x02,

    mMG_CHARACTER_NORMAL = 0x0A,
    mMG_CHARACTER_PEPPY = 0x0B,
    mMG_CHARACTER_SNOOTY = 0x0C,
} mMG_character_type;

typedef enum matching_constellation_type {
    mMG_CONSTELLATION_ARIES,
    mMG_CONSTELLATION_TAURUS,
    mMG_CONSTELLATION_GEMINI,
    mMG_CONSTELLATION_CANCER,
    mMG_CONSTELLATION_LEO,
    mMG_CONSTELLATION_VIRGO,
    mMG_CONSTELLATION_LIBRA,
    mMG_CONSTELLATION_SCORPIO,
    mMG_CONSTELLATION_SAGITTARIUS,
    mMG_CONSTELLATION_CAPRICORN,
    mMG_CONSTELLATION_AQUARIUS,
    mMG_CONSTELLATION_PISCES,

    mMG_CONSTELLATION_NUM
} mMG_constellation_type;

typedef enum matching_tribe_type {
    mMG_TRIBE_DUCK,
    mMG_TRIBE_ANTEATER,
    mMG_TRIBE_DOG,
    mMG_TRIBE_HORSE,
    mMG_TRIBE_RABBIT,
    mMG_TRIBE_BULL,
    mMG_TRIBE_COW,
    mMG_TRIBE_WOLF,
    mMG_TRIBE_FROG,
    mMG_TRIBE_HIPPO,
    mMG_TRIBE_KANGAROO,
    mMG_TRIBE_BEAR,
    mMG_TRIBE_CUB,
    mMG_TRIBE_KOALA,
    mMG_TRIBE_GORILLA,
    mMG_TRIBE_EAGLE,
    mMG_TRIBE_RHINO,
    mMG_TRIBE_ELEPHANT,
    mMG_TRIBE_OCTOPUS,
    mMG_TRIBE_OSTRICH,
    mMG_TRIBE_TIGER,
    mMG_TRIBE_BIRD,
    mMG_TRIBE_CHICKEN,
    mMG_TRIBE_CAT,
    mMG_TRIBE_MOUSE,
    mMG_TRIBE_SHEEP,
    mMG_TRIBE_PIG,
    mMG_TRIBE_PENGUIN,
    mMG_TRIBE_GOAT,
    mMG_TRIBE_LION,
    mMG_TRIBE_SQUIRREL,
    mMG_TRIBE_ALLIGATOR,

    mMG_TRIBE_NUM
} mMG_tribe_type;

extern int mMG_paramC_matching_point(u8* params0, u8* params1);

#ifdef __cplusplus
}
#endif

#endif
