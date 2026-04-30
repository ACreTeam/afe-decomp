#ifndef AC_T_HATHARVEST1_H
#define AC_T_HATHARVEST1_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*HATHARVEST1_PROC)(ACTOR*);

typedef struct tool_hat_harvest1_s {
    TOOLS_ACTOR tools_class;
    HATHARVEST1_PROC act_proc; 
    int action;
} TOOL_HAT_HARVEST1_ACTOR;

#ifdef __cplusplus
}
#endif
#endif // AC_T_HATHARVEST1_H
