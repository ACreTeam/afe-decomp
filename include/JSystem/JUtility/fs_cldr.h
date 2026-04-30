#ifndef FSCLDR_H
#define FSCLDR_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Closedir(SDDirInfo* pDirInfo);
extern u16 FS_Closedir_sub(SDDirInfo* pDirInfo);

#ifdef __cplusplus
};
#endif

#endif
