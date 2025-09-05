#ifndef CARDDRV_H
#define CARDDRV_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NowData {
    u16 year;
    u8 mon;
    u8 mday;
    u8 hour;
    u8 min;
    u8 sec;
} NowData;

extern int GetNowData(NowData* pNowData);
extern int GetRandomSeed(void);

#ifdef __cplusplus
};
#endif

#endif
