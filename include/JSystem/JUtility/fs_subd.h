#ifndef FSSUBD_H
#define FSSUBD_H

#include "JSystem/JUtility/fs_file.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_fat_clear(FSFile* param1, u16 param2);
extern u16 FS_Flush(FSFile* pFile);
extern u16 FS_get_entry(void* param1, void* param2, char* param3, u16 param4, void* param5, void* param6, void* param7);
extern u16 FS_allocate_entry(FSFile* pFile, int param1, int* param2, u16* param3);
extern u16 FS_delete_lfn_entry(FSFile* pFile, u16 param1, int param2, u16 param3);
extern u16 FS_cluster_to_sector(FSFile* pFile, u16 param1);
extern u16 FS_read_sub(void* param1, int param2, int param3, int param4, u16* param5, u16* param6);
extern u16 FS_write_sub(void* param1, int param2, int param3, int param4, u16* param5, int param6, u16* param7);
extern u16 FS_divide_fpathname(void* param1, void* param2, void* param3, u16 param4);
extern u16 FS_entry_name_set(void* param1, int param2);
extern u16 FS_uchar_to_dchar(char* param1);
extern void *FS_memset(void *dest, int ch, size_t count);
extern char *FS_strcpy(char *dest, const char *src);
extern char *FS_strncpy(char *dest, const char *src, size_t num);
extern size_t FS_strlen(const char *s);
extern u16 FS_strncmp(const char *s1, const char *s2, size_t n);

#ifdef __cplusplus
};
#endif

#endif
