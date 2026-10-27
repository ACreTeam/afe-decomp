#ifndef _MSL_COMMON_STRTOUL_H
#define _MSL_COMMON_STRTOUL_H

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/msl_types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

u32 __strtoul(int base, int max_width, int (*ReadProc)(void*, int, int), void* ReadProcArg, int* chars_scanned, int* negative,
              int* overflow);
u64 __strtoull(int base, int max_width, int (*ReadProc)(void*, int, int), void* ReadProcArg, int* chars_scanned, int* negative,
               int* overflow);
int atoi(const char* str);
u32 strtoul(const char* str, char** end, int base);
s32 strtol(const char* str, char** end, int base);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
