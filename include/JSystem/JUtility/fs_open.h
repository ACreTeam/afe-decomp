#ifndef FSOPEN_H
#define FSOPEN_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Search_Entry(FSFile* pFile, int* param_2, char* param_3, char* param_4, u16* param_5, char* param_6,
                           int* param_7, u16* param_8/* , u16* param_9, u16 param_10 */);

#ifdef __cplusplus
};
#endif

#endif
