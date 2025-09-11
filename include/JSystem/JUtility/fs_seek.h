#ifndef FSSEEK_H
#define FSSEEK_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Seek(SDFileInfo* param1, u32 param2, u16 param3);
extern u16 FS_Seek_sub(SDFileInfo* pFileInfo, u32 param2, u16 param3);

#ifdef __cplusplus
};
#endif

#endif
