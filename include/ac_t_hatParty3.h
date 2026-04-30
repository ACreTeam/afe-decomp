#ifndef AC_T_HATPARY3_H
#define AC_T_HATPARY3_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*HATPARY3_PROC)(ACTOR*);

typedef struct tool_hat_party3_s {
    TOOLS_ACTOR tools_class;
    HATPARY3_PROC act_proc; 
    int action;
} TOOL_HAT_PARTY3_ACTOR;

#ifdef __cplusplus
}
#endif
#endif // AC_T_HATPARY3_H
