#ifndef EXIDRV_H
#define EXIDRV_H

#include "types.h"
#include "JSystem/JUtility/JUTSDCard.h"

#include <dolphin.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void EXI_Null(s32 chan /*, OSContext* context*/);
extern void EXI_Unlock(s32 chan /*, OSContext* context*/);
extern void EXI_AlarmFunc(OSAlarm* alarm, OSContext* context);
extern u16 EXI_ResRead(u8* arg0, u16 arg1);
extern u16 EXI_StopResRead(u8* arg0, u16 arg1);
extern u16 EXI_DataRes(u8* arg0);
extern u16 EXI_MultiWriteStop(void);
extern u16 EXI_DataRead(u8* arg0, u16 arg1);
extern u16 EXI_DataReadFinal(u8* arg0, u16 arg1);
extern u16 EXI_CmdWrite0(u8* arg0, u16 arg1);
extern u16 EXI_CmdWrite(u8* arg0, u16 arg1);
extern u16 EXI_MultiDataWrite(u8* arg0, u16 arg1);
extern u8 EXI_MakeCRC7(u8* arg0, u16 arg1);
extern u16 EXI_MakeCRC16(u8* arg0, u16 arg1);
extern s32 EXI_CheckTimeOut(u32 arg0, u32 arg1);

extern u8 SD_DUMMY[0x80];
extern u8 EXI_ClrData[CARD_NUM_CHANS];

#ifdef __cplusplus
};
#endif

#endif
