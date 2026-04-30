#ifndef AC_T_HATPARY4_H
#define AC_T_HATPARY4_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*HATPARY4_PROC)(ACTOR*);

typedef struct tool_hat_party4_s {
    TOOLS_ACTOR tools_class;
    HATPARY4_PROC act_proc; 
    int action;
} TOOL_HAT_PARTY4_ACTOR;

#ifdef __cplusplus
}
#endif
#endif // AC_T_HATPARY4_H
