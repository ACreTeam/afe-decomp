#ifndef _MSL_COMMON_SCANF_H
#define _MSL_COMMON_SCANF_H

#include "stdarg.h"

int vsscanf(const char*, const char*, va_list);
int sscanf(const char*, const char*, ...);

#endif
