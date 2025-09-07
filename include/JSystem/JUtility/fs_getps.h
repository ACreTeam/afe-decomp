#ifndef FSGETPS_H
#define FSGETPS_H

#include "types.h"
#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Getpos(SDDriveInfo* pFileInfo, u32* arg1);

#ifdef __cplusplus
};
#endif

#endif
