#ifndef AC_T_HATATHLETIC2_H
#define AC_T_HATATHLETIC2_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*HATATHLETIC2_PROC)(ACTOR*);

typedef struct tool_hat_athletic2_s {
    TOOLS_ACTOR tools_class;
    HATATHLETIC2_PROC act_proc; 
    int action;
} TOOL_HAT_ATHLETIC2_ACTOR;

#ifdef __cplusplus
}
#endif
#endif // AC_T_HATATHLETIC2_H
