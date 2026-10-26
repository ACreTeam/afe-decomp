#ifndef TRK_DSTYPES_H
#define TRK_DSTYPES_H

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

typedef unsigned int uint;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

typedef unsigned char u128[16];

#define nullptr 0

#ifdef __MWERKS__
#define WEAKFUNC        __declspec(weak)
#define DECL_SECT(name) __declspec(section name)
#define ASM             asm
#else
#define WEAKFUNC
#define DECL_SECT(name)
#define ASM
#endif

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
