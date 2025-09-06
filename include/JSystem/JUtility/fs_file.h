#ifndef FSFILE_H
#define FSFILE_H

#include "types.h"

#include <dolphin.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct UnkStruct_ReadWrite {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */ int unk_04;
} UnkStruct_ReadWrite; // size = 0x08

typedef struct FSFile {
    // ?
    u16 unk_00[2];
    union {
        u16* unk_04_ptr;
        u16 unk_04[18];
    };
    s32 unk_28;
    char pad_unk_2C[0x34];

    s32 unk_60;
    char pad_unk_64[8];
    s32 unk_6C;
    u16 unk_70; 
    u16 unk_72; 
    u16 unk_74;
    char unk_76[64];
} FSFile;

typedef struct FSDir {
    /* 0x00 */ FSFile* pFile;
    /* 0x04 */ int unk_04;
    /* 0x08 */ int unk_08;
    /* 0x0C */ int unk_0C;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ char unk_14[64];
} FSDir; // size = 0x44

typedef struct DrvCtl {
    /* 0x00 */ u16 unk_00[2];
    /* 0x04 */ int pad_unk_04;
    /* 0x08 */ u16 unk_08[2];
    /* 0x0C */ char pad_unk_0C[0x20BA4 - 0x0C];
    /* 0x20BA4 */ char unk_20BA4[32];
    /* 0x20BA8 */ char pad_unk_20BA8[7];
    /* 0x20BAF */ char unk_20BAF;
    /* 0x20BB0 */ char unk_20BB0[10];
    /* 0x20BBA */ char unk_20BBA[10];
    /* 0x20BC4 */ char pad_unk_20BC4[0x25E48 - 0x20BE0];
} DrvCtl; // size = 0x25E48

extern DrvCtl FS_drv_ctl[CARD_NUM_CHANS];

#ifdef __cplusplus
};
#endif

#endif
