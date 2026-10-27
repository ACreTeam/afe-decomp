#ifndef _MSL_COMMON_CTYPE_API_H
#define _MSL_COMMON_CTYPE_API_H

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/msl_types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

extern u8 __ctype_map[256];
extern u8 __lower_map[256];
extern u8 __upper_map[256];

#define __control_char 0x01
#define __motion_char  0x02
#define __space_char   0x04
#define __punctuation  0x08
#define __digit        0x10
#define __hex_digit    0x20
#define __lower_case   0x40
#define __upper_case   0x80

#define __letter       (__lower_case | __upper_case)
#define __alphanumeric (__letter | __digit)
#define __graphic      (__alphanumeric | __punctuation)
#define __printable    (__graphic | __space_char)
#define __whitespace   (__motion_char | __space_char)
#define __control      (__motion_char | __control_char)

int tolower(int __c);

inline int isalpha(int c)
{
	return (int)(__ctype_map[(u8)c] & __letter);
}
inline int isdigit(int c)
{
	return (int)(__ctype_map[(u8)c] & __digit);
}
inline int isspace(int c)
{
	return (int)(__ctype_map[(u8)c] & __whitespace);
}
inline int isupper(int c)
{
	return (int)(__ctype_map[(u8)c] & __upper_case);
}
inline int isxdigit(int c)
{
	return (int)(__ctype_map[(u8)c] & __hex_digit);
}
inline int isprintable(int c)
{
	return (int)(__ctype_map[(u8)c] & __printable);
}
// added underscore to avoid naming conflicts
inline int _tolower(int c)
{
	return (c == -1 ? -1 : (int)__lower_map[(u8)c]);
}
inline int toupper(int c)
{
	return (c == -1 ? -1 : (int)__upper_map[(u8)c]);
}

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
