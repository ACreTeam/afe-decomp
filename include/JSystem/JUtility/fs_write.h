#ifndef FSWRITE_H
#define FSWRITE_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Write(SDDriveInfo* param1, const void* data, s32 length, int param4, UnkStruct_ReadWrite* param5);

#ifdef __cplusplus
};
#endif

#endif
