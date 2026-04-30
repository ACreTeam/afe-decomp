#ifndef AC_T_HATPARY2_H
#define AC_T_HATPARY2_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*HATPARY2_PROC)(ACTOR*);

typedef struct tool_hat_party2_s {
    TOOLS_ACTOR tools_class;
    HATPARY2_PROC act_proc; 
    int action;
} TOOL_HAT_PARTY2_ACTOR;

#ifdef __cplusplus
}
#endif
#endif // AC_T_HATPARY2_H
