#ifndef FSDRVSEL_H
#define FSDRVSEL_H

#include "JSystem/JUtility/JUTSDCard.h"
#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_DrvSel_Reset(void);
extern u16 FS_DrvSel_Init(int param1, int param2, u16 param3);
extern u16 FS_DrvSel_Select(int arg5);
extern u16 FS_DrvSel_Read(UnkStruct_20BA4* arg0, s32 arg1, s32 arg2, s32 arg3, UnkStruct_20BA4* arg4, int arg5);
extern u16 FS_DrvSel_Write(UnkStruct_20BA4* arg0, s32 arg1, s32 arg2, s32 arg3, DrvCtl_unk_20000* arg4, int arg5);
extern u16 FS_DrvSel_Getstatus(u16* arg0, int arg5);
extern u16 FS_DrvSel_Getinfo(SDInfos* arg0, int arg5);

#ifdef __cplusplus
};
#endif

#endif
