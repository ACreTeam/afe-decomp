#ifndef FSTIME_H
#define FSTIME_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NowData {
    /* 0x00 */ u16 year;
    /* 0x02 */ u8 mon;
    /* 0x03 */ u8 mday;
    /* 0x04 */ u8 hour;
    /* 0x05 */ u8 min;
    /* 0x06 */ u8 sec;
    /* 0x07 */ u8 pad_unk_07;
} NowData; // size = 0x08

extern u16 GetNowData(NowData* pNowData);
extern u16 GetRandomSeed(void);

#ifdef __cplusplus
};
#endif

#endif
