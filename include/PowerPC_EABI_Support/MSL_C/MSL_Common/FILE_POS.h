#ifndef _MSL_COMMON_FILE_POS_H
#define _MSL_COMMON_FILE_POS_H

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/ansi_files.h"

#define SEEK_SET (0)
#define SEEK_CUR (1)
#define SEEK_END (2)

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

int fseek(FILE* stream, u32 offset, int whence);
int _fseek(FILE* stream, u32 offset, int whence);
int ftell(FILE* stream);
int _ftell(FILE* stream);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
