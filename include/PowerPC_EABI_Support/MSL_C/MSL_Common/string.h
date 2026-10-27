#ifndef _MSL_COMMON_STRING_H
#define _MSL_COMMON_STRING_H

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/mem.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char*);
char* strcpy(char*, const char*);
char* strncpy(char*, const char*, size_t);
char* strcat(char*, const char*);
char* strncat(char*, const char*, size_t);
int strcmp(const char*, const char*);
int strncmp(const char*, const char*, size_t);
char* strchr(const char*, int);
char* strrchr(const char*, int);
char* strstr(const char*, const char*);

#ifdef __cplusplus
}
#endif

#endif
