#ifndef FSDRV_H
#define FSDRV_H

#include "JSystem/JUtility/JUTSDCard.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 CARD_Write(SDSTATUS* param1, u32 param2, int param3, u32 param4, ReadWriteDParam5* param5);
extern u16 CARD_Read(SDSTATUS* param1, u32 param2, int param3, u32 param4, ReadWriteDParam5* param5);
extern u16 CARD_Init(int param1, int param2);
extern u16 SDTerm(u16 param1);

#ifdef __cplusplus
};
#endif

#endif
