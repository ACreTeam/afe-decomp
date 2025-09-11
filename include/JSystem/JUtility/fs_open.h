#ifndef FSOPEN_H
#define FSOPEN_H

#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_form.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Open(SDDriveInfo* param1, SDFileInfo** param2, char* param3, u16 param4);
extern u16 FS_Search_Entry(SDDriveInfo* pFile, char* param_2, char* param_3, char** param_4, u16* param_5, FSDirEntry* param_6,
                           int* param_7, u16* param_8, u16* param_9, u16 param_10);

#ifdef __cplusplus
};
#endif

#endif
