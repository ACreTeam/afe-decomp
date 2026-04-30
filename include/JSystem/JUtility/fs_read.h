#ifndef FSREAD_H
#define FSREAD_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Read(SDFileInfo* param1, const void* data, s32 length, int param4, UnknownStruct1* param5);
extern u16 FS_Read_SubPrc(SDFileInfo* param1, const void* data, u32 length, u32 param4, UnknownStruct1* param5);
extern u16 FS_GetChkAccessSize(SDFileInfo* pFileInfo, u32 param2, u32* param3);
extern u16 FS_GetAccessClusterCount(SDFileInfo* pFileInfo, u32 param2);
extern u16 FS_GetDoingCluster2(SDFileInfo* pFileInfo, u16* param2, u16* param3, u16* param4, u32* param5, u16* param6);
extern u16 FS_GetNextCluster(SDFileInfo* pFileInfo, u16 param2);
extern u16 FS_ReadIODoing(SDFileInfo* pFileInfo, void* param2, u16 param3, u16 param4, u16 param5, UnknownStruct1* param6, u16 param7);
extern u16 FS_FatTable_PageChange(SDDriveInfo* pDriveInfo);

#ifdef __cplusplus
};
#endif

#endif
