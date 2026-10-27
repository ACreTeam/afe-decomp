#ifndef _MSL_TYPES_H
#define _MSL_TYPES_H

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;
typedef long double f128;

typedef unsigned int uint;

#ifndef _SIZE_T_DEF
#define _SIZE_T_DEF
typedef unsigned long size_t;
#endif

#ifndef __cplusplus
#ifndef _WCHAR_T_DEF
#define _WCHAR_T_DEF
typedef unsigned short wchar_t;
#endif
#endif

typedef int BOOL;

#define TRUE  1
#define FALSE 0

#ifndef NULL
#define NULL ((void*)0)
#endif
#define nullptr 0

#define WEAKFUNC __declspec(weak)

#endif
