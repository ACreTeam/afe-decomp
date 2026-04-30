#ifndef FSRENM_H
#define FSRENM_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Rename(SDDriveInfo* pDriveInfo, char* arg1, char* arg2);
extern u16 FS_Rename_sub(SDDriveInfo* pDriveInfo, char* arg1, char* arg2);

#ifdef __cplusplus
};
#endif

#endif
