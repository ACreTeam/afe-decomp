#ifndef AC_T_HATCHRISTMAS1_H
#define AC_T_HATCHRISTMAS1_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*HATCHRISTMAS1_PROC)(ACTOR*);

typedef struct tool_hat_christmas1_s {
    TOOLS_ACTOR tools_class;
    HATCHRISTMAS1_PROC act_proc; 
    int action;
} TOOL_HAT_CHRISTMAS1_ACTOR;

#ifdef __cplusplus
}
#endif
#endif // AC_T_HATCHRISTMAS1_H
