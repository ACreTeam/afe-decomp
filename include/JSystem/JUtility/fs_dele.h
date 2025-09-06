#ifndef FSDELE_H
#define FSDELE_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Delete(FSFile* param1, const char* param2);
extern u16 FS_Delete_sub(FSFile* param1, const char* param2);
extern u16 FS_Delete_Entry(FSFile* param1, int param2, u16 param3, u16 param4);

#ifdef __cplusplus
};
#endif

#endif
