#ifndef FSFILE_H
#define FSFILE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FSFile {
    u16 unk_00;
    u16 unk_02;
    u16* unk_04;
    char unk_08[0x28 - 0x08];
    s32 unk_28;
} FSFile;

extern unsigned char FS_drv_ctl[0x4BC90];

#ifdef __cplusplus
};
#endif

#endif
