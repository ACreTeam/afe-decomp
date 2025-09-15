#ifndef FSDRV_H
#define FSDRV_H

#include "JSystem/JUtility/JUTSDCard.h"
#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 CARD_Write(u8* param1, u32 param2, int param3, u32 param4, UnknownStruct1* param5);
extern u16 CARD_Read(u8* param1, u32 param2, int param3, u32 param4, UnknownStruct1* param5);
extern u16 CARD_Init(int param1, int param2);
extern u16 SDTerm(u16 nDrive);

#ifdef __cplusplus
};
#endif

#endif
