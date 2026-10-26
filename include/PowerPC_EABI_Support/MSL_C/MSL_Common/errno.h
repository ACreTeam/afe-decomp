#ifndef _MSL_COMMON_ERRNO_H
#define _MSL_COMMON_ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

#define ENOERR 0
#define EDOM   33
#define ERANGE 34
#define EFPOS  40
#define EILSEQ 88

extern int errno;

#ifdef __cplusplus
}
#endif

#endif
