#ifndef FSCLDR_H
#define FSCLDR_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Closedir(FSDir* pDir);
extern u16 FS_Closedir_sub(FSDir* pDir);

#ifdef __cplusplus
};
#endif

#endif
