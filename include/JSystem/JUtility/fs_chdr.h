#ifndef FSCHDR_H
#define FSCHDR_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Chdir(SDDriveInfo* pDriveInfo, char* arg1);
extern u16 FS_Chdir_sub(SDDriveInfo* pDriveInfo, char* arg1);

#ifdef __cplusplus
};
#endif

#endif
