#ifndef FSCLOSE_H
#define FSCLOSE_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Close(SDFileInfo* pFileInfo);
extern u16 FS_Close_sub(SDFileInfo* pFileInfo);

#ifdef __cplusplus
};
#endif

#endif
