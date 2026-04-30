#ifndef FSSYNC_H
#define FSSYNC_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Sync_sub(SDDriveInfo* pDriveInfo);
extern u16 FS_Sync_DirEntry(SDFileInfo* pFileInfo);

#ifdef __cplusplus
};
#endif

#endif
