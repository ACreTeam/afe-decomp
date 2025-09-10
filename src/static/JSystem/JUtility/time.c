#include "JSystem/JUtility/time.h"

#include <dolphin.h>

u16 GetNowData(NowData* pNowData) {
    OSCalendarTime td;
    OSTime time = OSGetTime();

    OSTicksToCalendarTime(time, &td);

    pNowData->year = td.year;
    pNowData->mon = td.mon + 1;
    pNowData->mday = td.mday;
    pNowData->hour = td.hour;
    pNowData->min = td.min;
    pNowData->sec = td.sec;

    return 0;
}

u16 GetRandomSeed(void) {
    u16 seed = 0x67CD;
    return seed;
}
