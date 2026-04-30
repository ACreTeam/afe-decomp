#ifndef FSUMOUNT_H
#define FSUMOUNT_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Umount(SDDriveInfo* pDriveInfo);
extern u16 FS_Umount_sub(SDDriveInfo* pDriveInfo);

#ifdef __cplusplus
};
#endif

#endif
