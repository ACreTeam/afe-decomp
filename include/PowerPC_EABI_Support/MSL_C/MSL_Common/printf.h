#ifndef _MSL_COMMON_PRINTF_H
#define _MSL_COMMON_PRINTF_H

#include "stdarg.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/file_struc.h"

int printf(const char*, ...);
int fprintf(FILE*, const char* format, ...);
int vprintf(const char*, va_list);
int vsnprintf(char*, size_t, const char*, va_list);
int vsprintf(char*, const char*, va_list);
int snprintf(char*, size_t, const char*, ...);
int sprintf(char*, const char*, ...);

#endif
