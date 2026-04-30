#ifndef _STDARG_H_
#define _STDARG_H_

#ifdef __MWERKS__
#ifdef __cplusplus
namespace std {
struct __tag_va_List {
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
};
}

typedef std::__tag_va_List __va_list[1];
#else
typedef struct {
  char gpr;
  char fpr;
  char reserved[2];
  char* input_arg_area;
  char* reg_save_area;
} __va_list[1];
#endif
typedef __va_list va_list;

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __MWERKS__
extern void __builtin_va_info(va_list*);
#endif

void* __va_arg(va_list v_list, int type);

#ifdef __cplusplus
}
#endif

#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))
#define va_arg(ap, t) (*((t*)__va_arg(ap, _var_arg_typeof(t))))
#define va_end(ap) (void)0

#else
typedef __builtin_va_list va_list;
#define va_start(v, l) __builtin_va_start(v, l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, l) __builtin_va_arg(v, l)
#endif

#endif
