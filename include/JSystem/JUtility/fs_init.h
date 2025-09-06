#ifndef FSINIT_H
#define FSINIT_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u16 FS_Init(int param1, int param2, u16 param3);
extern u16 FS_Init_check_config(u16 param1, u16* param2);
extern void FS_Init_set_drive_info(u16 param1);
extern u16 FS_Init_check_kind_of_drive(u16* param1);

extern const u16 kindDrv[];

#ifdef __cplusplus
};
#endif

#endif
