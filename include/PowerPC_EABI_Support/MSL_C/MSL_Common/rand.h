#ifndef _MSL_COMMON_RAND_H
#define _MSL_COMMON_RAND_H

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/msl_types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

int rand(void);
void srand(u32 seed);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
