#ifndef FSOPEN_H
#define FSOPEN_H

#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_form.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Open(SDDriveInfo* pDriveInfo, SDFileInfo** ppFileInfo, char* param3, u16 param4);
extern u16 FS_Open_sub(SDDriveInfo* pDriveInfo, SDFileInfo** ppFileInfo, char* param3, u16 param4);
extern u16 FS_CreateFile_Open(SDDriveInfo* pDriveInfo, SDFileInfo** ppFileInfo, char* param3, char** param4, u16 param5, u16 param6);
extern u16 FS_ExistFile_Open(SDDriveInfo* pDriveInfo, SDFileInfo** ppFileInfo, char* param3, char** param4, u16 param5, u16 param6);
extern u16 FS_ExistFile_InfoPrc(SDDriveInfo* pDriveInfo, SDFileInfo** ppFileInfo, FSDirEntry* pDirEntry, u16* param4, u16 param6);
extern u16 FS_EntryInfo_Set(SDDriveInfo* pDriveInfo, SDFileInfo* pFileInfo, u16 param3, u32 param4, u16 param5, char* param6, u16 param7);
extern u16 FS_SetDirEntry(SDDriveInfo* pDriveInfo, u32 param2, u16 param3, char** param4, u16 param5, u16 param6);
extern u16 FS_get_FILE_id(SDDriveInfo* pDriveInfo, u16 param2);
extern void FS_free_FILE_id(SDFileInfo* pFileInfo);
extern u16 FS_open_flag_check(u16* param1);
extern u16 FS_file_atr_check(FSDirEntry* pDirEntry, u16 param2);
extern u16 FS_check_same_FILE(SDDriveInfo* pDriveInfo, char* param2, u16 param3);
extern u16 FS_Search_Entry(SDDriveInfo* pDriveInfo, char* param_2, char* param3, char** param4, u16* param5, FSDirEntry* param6, u32* param7, u16* param8, u16* param9, u16 param10);

#ifdef __cplusplus
};
#endif

#endif
