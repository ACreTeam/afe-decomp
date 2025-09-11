#ifndef FSREAD_H
#define FSREAD_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Read(SDFileInfo* param1, const void* data, s32 length, int param4, UnknownStruct1* param5);
extern u16 FS_FatTable_PageChange(SDDriveInfo* pDriveInfo);
extern u16 FS_GetAccessClusterCount(SDFileInfo* pFileInfo, u32 param2);

#ifdef __cplusplus
};
#endif

#endif
