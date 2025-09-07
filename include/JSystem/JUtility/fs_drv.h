#ifndef FSDRV_H
#define FSDRV_H

#include "JSystem/JUtility/JUTSDCard.h"
#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 CARD_Write(UnkStruct_20BA4* param1, u32 param2, int param3, u32 param4, UnkStruct_20BA4* param5);
extern u16 CARD_Read(UnkStruct_20BA4* param1, u32 param2, int param3, u32 param4, UnkStruct_20BA4* param5);
extern u16 CARD_Init(int param1, int param2);
extern u16 SDTerm(u16 param1);

#ifdef __cplusplus
};
#endif

#endif
