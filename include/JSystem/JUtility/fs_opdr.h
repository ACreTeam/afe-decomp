#ifndef FSOPDR_H
#define FSOPDR_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Opendir(FSFile* param1, FSDir** param2, const char* param3);

#ifdef __cplusplus
};
#endif

#endif
