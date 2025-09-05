#ifndef FSFILE_H
#define FSFILE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FSFile {
    u16 unk_00[2];

    // ?
    union {
        u16* unk_04_ptr;
        u16 unk_04[18];
    };

    s32 unk_28;
    char unk_2C[0x1C];
    s32 unk_6C;
    u16 unk_70; 
    u16 unk_72; 
    u16 unk_74;
    char unk_76[64];
} FSFile;

extern unsigned char FS_drv_ctl[0x4BC90];

#ifdef __cplusplus
};
#endif

#endif
