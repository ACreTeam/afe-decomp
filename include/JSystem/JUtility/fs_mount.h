#ifndef FSMOUNT_H
#define FSMOUNT_H

#include "JSystem/JUtility/fs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Mount(SDDriveInfo** ppDriveInfo, u16 nChan);
extern u16 FS_Mount_sub(SDDriveInfo* pDriveInfo);
extern u16 FS_GetCardInfo(SDDriveInfo* pDriveInfo);
extern void FS_InitGlobalData(SDDriveInfo* pDriveInfo);
extern u16 FS_ReadMBR(SDDriveInfo* pDriveInfo);
extern u16 FS_ChkMBR(SDDriveInfo* pDriveInfo, FSMasterBootRecord* pStart, u8* pEnd);
extern u16 FS_ReadFDC(SDDriveInfo* pDriveInfo);
extern void FS_SetFDC(SDDriveInfo* pDriveInfo);
extern u16 FS_SetFATkind(SDDriveInfo* pDriveInfo);
extern u16 FS_SetFATsecN(SDDriveInfo* pDriveInfo);
extern u16 FS_ReadFAT(SDDriveInfo* pDriveInfo);
extern u16 FS_ReadFATSetCacheInfo(SDDriveInfo* pDriveInfo, SDDriveInfo* param2);
extern u16 FS_ReadFATSetFATinfo(SDDriveInfo* pDriveInfo);
extern void FS_ReadFATSetMemSize(SDDriveInfo* pDriveInfo, SDDriveInfo* param2);
extern u16 FS_ChkFDC(SDDriveInfo* pDriveInfo, u8* param2, u16 param3);
extern u16 FS_ChkMnt(SDDriveInfo* pDriveInfo);
extern u16 FS_ChkMntOther(SDDriveInfo* pDriveInfo);

#ifdef __cplusplus
};
#endif

#endif
