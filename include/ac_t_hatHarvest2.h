#ifndef AC_T_HATHARVEST2_H
#define AC_T_HATHARVEST2_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*HATHARVEST2_PROC)(ACTOR*);

typedef struct tool_hat_harvest2_s {
    TOOLS_ACTOR tools_class;
    HATHARVEST2_PROC act_proc; 
    int action;
} TOOL_HAT_HARVEST2_ACTOR;

#ifdef __cplusplus
}
#endif
#endif // AC_T_HATHARVEST2_H
