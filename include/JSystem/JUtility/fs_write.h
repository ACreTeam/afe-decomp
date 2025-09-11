#ifndef FSWRITE_H
#define FSWRITE_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Write(SDFileInfo* param1, const void* data, u32 length, int param4, UnknownStruct1* param5);
extern u16 FS_Write_SubPrc(SDFileInfo* pFileInfo, const void* data, u32 length, u32 param4, UnknownStruct1* param5);
extern u16 FS_GetWriteDoingCluster2(SDFileInfo* pFileInfo, u16* param2, u16* param3, u16* param4, u32* param5,
                                    u16* param6);
extern u16 FS_GetWriteNextCluster(SDFileInfo* pFileInfo, u16 param2);
extern u16 FS_WriteIODoing(SDFileInfo* pFileInfo, void* param2, u16 param3, u16 param4, u16 param5,
                           UnknownStruct1* param6, u16 param7);
extern u16 FS_ChkWriteAccessSize(SDFileInfo* pFileInfo, u32 length);

#ifdef __cplusplus
};
#endif

#endif
