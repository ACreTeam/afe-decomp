#ifndef AC_T_HATPARY1_H
#define AC_T_HATPARY1_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*HATPARY1_PROC)(ACTOR*);

typedef struct tool_hat_party1_s {
    TOOLS_ACTOR tools_class;
    HATPARY1_PROC act_proc; 
    int action;
} TOOL_HAT_PARTY1_ACTOR;

#ifdef __cplusplus
}
#endif
#endif // AC_T_HATPARY1_H
