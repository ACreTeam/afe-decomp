#ifndef _MSL_COMMON_MATH_API_H
#define _MSL_COMMON_MATH_API_H

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/msl_types.h"
#include "MSL_C/MSL_Common_Embedded/Math/fdlibm.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

inline int __fpclassifyf(f32 x)
{
	switch ((*(s32*)&x) & 0x7f800000) {
	case 0x7f800000: {
		if ((*(s32*)&x) & 0x007fffff)
			return 1;
		else
			return 2;
		break;
	}
	case 0: {
		if ((*(s32*)&x) & 0x007fffff)
			return 5;
		else
			return 3;
		break;
	}
	}
	return 4;
}

inline int __fpclassifyd(f64 x)
{
	switch (__HI(x) & 0x7ff00000) {
	case 0x7ff00000: {
		if ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff))
			return 1;
		else
			return 2;
		break;
	}
	case 0: {
		if ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff))
			return 5;
		else
			return 3;
		break;
	}
	}
	return 4;
}

#define fpclassify(x) ((sizeof(x) == sizeof(f32)) ? __fpclassifyf((f32)(x)) : __fpclassifyd((f64)(x)))

#define SIGNBIT(x) ((int)(__HI(x) & 0x80000000))

#define isnan(x)    ((fpclassify(x) == 1))
#define isinf(x)    ((fpclassify(x) == 2))
#define isfinite(x) ((fpclassify(x) > 2))

extern int __double_max[];
extern int __extended_min[];
extern int __extended_max[];

#define DBL_MAX  (*(f64*)__double_max)
#define LDBL_MAX (*(f128*)__extended_max)
#define LDBL_MIN (*(f128*)__extended_min)

#define DBL_MANT_DIG   53
#define DBL_DIG        15
#define DBL_MIN_EXP    (-1021)
#define DBL_MIN_10_EXP (-308)
#define DBL_MAX_EXP    1024
#define DBL_MAX_10_EXP 308

#define LDBL_MANT_DIG   53
#define LDBL_DIG        15
#define LDBL_MIN_EXP    (-1021)
#define LDBL_MIN_10_EXP (-308)
#define LDBL_MAX_EXP    1024
#define LDBL_MAX_10_EXP 308

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
