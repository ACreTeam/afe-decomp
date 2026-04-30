#ifndef FSMKDR_H
#define FSMKDR_H

#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/time.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Mkdir(SDDriveInfo* pDriveInfo, const char* param2);
extern u16 FS_Mkdir_sub(SDDriveInfo* pDriveInfo, const char* param2);
extern u16 FS_initialize_directory_data(SDDriveInfo* pDriveInfo, u16 param2, u16 param3, NowData* pNowData);

#ifdef __cplusplus
};
#endif

#endif
