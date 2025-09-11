#ifndef FSRDDR_H
#define FSRDDR_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Readdir(SDDirInfo* pDirInfo, UnknownStruct3* param2);
extern u16 FS_Readdir_sub(SDDirInfo* pDirInfo, UnknownStruct3* param2);

#ifdef __cplusplus
};
#endif

#endif
