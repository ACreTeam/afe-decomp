#ifndef FSFILE_H
#define FSFILE_H

#include "types.h"

#include <dolphin.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SDDriveInfo {
    /* 0x000 */ u16 nChan;
    /* 0x002 */ u16 unk_02;
    /* 0x004 */ u16 unk_04;
    /* 0x006 */ u16 unk_06;
    /* 0x008 */ char pad_unk_08[0x1E - 0x08];
    /* 0x01E */ u16 unk_1E;
    /* 0x020 */ char pad_unk_20[0x60 - 0x20];
    /* 0x060 */ s32 nSector;
    /* 0x064 */ s32 pad_unk_64;
    /* 0x068 */ s32 pad_unk_68;
    /* 0x06C */ s32 unk_6C;
    /* 0x070 */ u16 unk_70;
    /* 0x072 */ u16 unk_72;
    /* 0x074 */ u16 unk_74;
    /* 0x076 */ char unk_76[64];
    /* 0x0B6 */ char pad_unk_B6[0xBC - 0xB6];
    /* 0x0BC */ u16 unk_BC;
    /* 0x0BE */ u16 pad_unk_BE;
    /* 0x0C0 */ u16 unk_C0;
    /* 0x0C2 */ char pad_unk_C2[0xF4 - 0xC2];
    /* 0x0F4 */ u16 unk_F4;
    /* 0x0F6 */ char pad_unk_F6[0xFA - 0xF6];
    /* 0x0FA */ u16 unk_FA;
    /* 0x0FC */ u32 unk_FC;
    /* 0x100 */ u32 pad_unk_100;
} SDDriveInfo; // size = 0x104 (?)

typedef struct SDFileInfo {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 pad_unk_02;
    /* 0x04 */ SDDriveInfo* pDriveInfo;
    /* 0x08 */ u8 unk_08[11];
    /* 0x13 */ u8 pad_unk_13;
    /* 0x14 */ u8 unk_14[10];
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ u32 unk_2C;
    /* 0x2E */ u32 unk_2E;
    /* 0x30 */ u32 unk_30;
    /* 0x32 */ u32 unk_32;
    /* 0x34 */ u32 unk_34;
    /* 0x38 */ u16 unk_38;
    /* 0x3A */ char path[64];
    /* 0x7A */ u8 pad_unk_7A;
    /* 0x7B */ u8 pad_unk_7B;
} SDFileInfo; // size = 0x7C (?)

typedef struct UnkStruct_20BA4 {
    /* 0x00 */ u8 unk_00[2]; //! TODO: accessed either as u8 or u16??
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u16 pad_unk_08;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ char pad_unk_0C[0x1A - 0x0C];
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ int pad_unk_1C;
} UnkStruct_20BA4; // size = 0x20

typedef struct DrvCtl_unk_20000 {
    /* 0x0000 */ char pad_unk_000[0x9F8];
    /* 0x09F8 */ void* unk_09F8; // OK
    /* 0x0000 */ char pad_unk_9FC[0xBA4 - 0x9FC];
    /* 0x0BA4 */ UnkStruct_20BA4 unk_20BA4;
    /* 0x0BC4 */ char pad_unk_BC4[0x4000 - 0xBC4];
} DrvCtl_unk_20000; // size = 0x4000 (?)

typedef struct DrvCtl {
    /* 0x00000 */ u16 unk_00[4]; // note sure if it's the same array
    /* 0x00008 */ SDDriveInfo unk_08[2];
    /* 0x00210 */ SDFileInfo unk_210[5];
    /* 0x0047C */ SDFileInfo unk_47C[5];
    /* 0x00738 */ char pad_unk_738[0x20000 - 0x738];
    /* 0x20000 */ DrvCtl_unk_20000* ctrl_p[2]; //! TODO: confirm
    /* 0x20008 */ char pad_unk_20008[0x259D4 - 0x20008];
    /* 0x259D4 */ s32 unk_259D4;
    /* 0x259D8 */ u32 unk_259D8;
    /* 0x259DC */ u16 unk_259DC;
    /* 0x259DE */ char pad_unk_259DE[0x25E48 - 0x259DE];
} DrvCtl; // size = 0x25E48

// --- OLD

typedef struct UnkStruct_ReadWrite {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */ int unk_04;
} UnkStruct_ReadWrite; // size = 0x08

typedef struct FSFile {
    u16 unk_00[2];
    u16 unk_04[18];
    s32 unk_28;

    /* 0x2C */ char pad_unk_2C[0x3E - 0x2C];
    /* 0x3E */ char unk_3E[12]; // OK
    /* 0x4A */ char unk_4A[8]; // OK
    /* 0x53 */ char pad_unk_53[0x60 - 0x52];

    /* 0x60 */ s32 unk_60;
    /* 0x64 */ char pad_unk_64[8];
    /* 0x6C */ s32 unk_6C;
    /* 0x70 */ u16 unk_70; 
    /* 0x72 */ u16 unk_72; 
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ char unk_76[64]; // OK

    /* 0xB6 */ char pad_unk_96[0xBC - 0xB6];
    /* 0xBC */ u16 unk_BC;
    /* 0xBE */ char pad_unk_BE[0x104 - 0xBE];
} FSFile; // size = 0x104 (?)

typedef struct FSDir {
    /* 0x00 */ SDDriveInfo* pDriveInfo;
    /* 0x04 */ int unk_04;
    /* 0x08 */ int unk_08;
    /* 0x0C */ int unk_0C;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ char unk_14[64];
} FSDir; // size = 0x44

// ---

extern DrvCtl FS_drv_ctl[CARD_NUM_CHANS];

#ifdef __cplusplus
};
#endif

#endif
