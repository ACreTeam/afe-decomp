#ifndef FSOPDR_H
#define FSOPDR_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Opendir(SDDriveInfo* pDriveInfo, SDDirInfo** ppDirInfo, const char* param3);
extern u16 FS_Opendir_sub(SDDriveInfo* pDriveInfo, SDDirInfo** ppDirInfo, const char* param3);

#ifdef __cplusplus
};
#endif

#endif
