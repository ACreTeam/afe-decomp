#ifndef _NEW_H
#define _NEW_H

#include <stddef.h>

#ifdef __cplusplus
inline void* operator new(size_t, void* buf) {
    return buf;
}
#endif

#endif
