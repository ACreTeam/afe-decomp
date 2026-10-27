#ifndef FAMICOM_CSTRING_H
#define FAMICOM_CSTRING_H

#include "libc/string.h"

#ifdef __cplusplus
namespace std {
inline char* strstr(char* str, const char* pat) {
    return ::strstr(str, pat);
}
} // namespace std
#endif

#endif
