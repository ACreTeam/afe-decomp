#ifndef _MSL_COMMON_STRTOLD_H
#define _MSL_COMMON_STRTOLD_H

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/msl_types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

f128 __strtold(int max_width, int (*ReadProc)(void*, int, int), void* ReadProcArg, int* chars_scanned, int* overflow);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
