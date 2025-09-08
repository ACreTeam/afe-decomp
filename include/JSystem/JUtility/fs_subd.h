#ifndef FSSUBD_H
#define FSSUBD_H

#include "JSystem/JUtility/fs_file.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FS_SD_CARD_MODE_RAW (1 << 0)
#define FS_SD_CARD_MODE_FORMATTED_MODE (1 << 1)

extern u16 FS_get_fat_entry(SDDriveInfo* pDriveInfo, u16 param2, u16* param3);
extern u16 FS_fat_clear(u16 param2, SDDriveInfo* param1);
extern u16 FS_Flush(SDDriveInfo* pFile);
extern u16 FS_get_entry(SDDriveInfo* param1, char* param2, char* param3, u16 param4, void* param5, void* param6, void* param7);
extern u16 FS_allocate_entry(SDDriveInfo* pFile, int param1, int* param2, u16* param3);
extern u16 FS_delete_lfn_entry(SDDriveInfo* pFile, u32 param1, int param2, u16 param3);

extern u16 FS_set_fat_entry(SDDriveInfo* pDriveInfo, u16 param2, int param3);
extern u16 FS_fat_clear(u16 param2, SDDriveInfo* pDriveInfo);
extern u16 FS_fat_sync(SDDriveInfo* pDriveInfo);
extern u32 FS_set_now_date(UnkStruct_20BA4 *param1, void *param2);
extern u16 FS_open_check_parent(SDDriveInfo *pDriveInfo, char* param2);
extern u16 FS_open_check_all(SDDriveInfo *pDriveInfo, char* param2);
extern u16 FS_get_next_cluster(SDDriveInfo *pDriveInfo, u16 param2);
extern u16 FS_get_previous_cluster(SDDriveInfo *pDriveInfo, u16 param2, u16 param3);
extern u16 FS_sector_to_cluster(SDDriveInfo *pDriveInfo, u32 param2);
extern u32 FS_cluster_to_sector(SDDriveInfo* pDriveInfo, u32 param2);
extern u16 FS_read_sub(UnkStruct_20BA4_2* param1, int param2, u32 param3, UnkStruct_24BA4* param4, u16 param5, u16 param6);
extern u16 FS_write_sub(UnkStruct_20BA4_2* param1, int param2, u32 param3, UnkStruct_24BA4* param4, u16 param5, int param6, u16 nChan);
extern s32 FS_csd_to_size(u32 *outSectorsPerCluster, s32 *outCsdBlockMultiplier, u16 modeFlags, u16 arg3, u16 chan);
extern u16 FS_divide_fpathname(char* param1, char** param2, u16* param3, u16 param4);
extern u16 FS_fat_strcmp(UnkStruct_20BA4 *arg0, UnkStruct_20BA4 *arg1); // matched but param types not 100% confirmed
extern u16 FS_entry_name_set(char* param1, char* param2);
extern void FS_entname_to_stdname(char* param1);
extern u16 FS_uchar_to_dchar(char* param1);
extern void FS_toupper(char *arg0);
extern void *FS_memset(void *dest, u16 ch, size_t count);
extern char *FS_strcpy(char *dest, const char *src);
extern char *FS_strncpy(char *dest, const char *src, size_t num);
extern size_t FS_strlen(const char *s);
extern u16 FS_strncmp(const char *s1, const char *s2, size_t n);
extern void FS_srand(u16 arg0, u16 arg1);
extern u16 FS_rand(u16 arg0, u16 arg1);

#ifdef __cplusplus
};
#endif

#endif
