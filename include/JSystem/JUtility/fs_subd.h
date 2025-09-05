#ifndef FSSUBD_H
#define FSSUBD_H

#include "types.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_get_entry(void* param1, void* param2, char* param3, u16 param4, void* param5, void* param6, void* param7);
extern u16 FS_divide_fpathname(void* param1, void* param2, void* param3, u16 param4);
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
