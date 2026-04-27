#ifndef M_MONUMENT_H
#define M_MONUMENT_H

#include "types.h"
#include "m_name_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMM_MONUMENT_MAX 5

typedef struct monument_order_s {
    u8 bx;
    u8 bz;
    u8 ux;
    u8 uz;
    mActor_name_t name;
    u16 pad;
} mMM_order_c;

#ifdef __cplusplus
}
#endif

#endif
