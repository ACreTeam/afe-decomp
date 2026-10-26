#ifndef _MSL_COMMON_ARITH_H
#define _MSL_COMMON_ARITH_H

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/msl_types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

typedef struct {
	int quot; /* quotient */
	int rem;  /* remainder */
} div_t;

typedef struct {
	long quot; /* quotient */
	long rem;  /* remainder */
} ldiv_t;

typedef struct {
	long long quot; /* quotient */
	long long rem;  /* remainder */
} lldiv_t;

int abs(int __x);
long labs(long __x);
div_t div(int __numer, int __denom);
ldiv_t ldiv(long __numer, long __denom);
lldiv_t lldiv(long long __numer, long long __denom);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
