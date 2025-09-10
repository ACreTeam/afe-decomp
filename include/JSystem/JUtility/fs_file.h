#ifndef FSFILE_H
#define FSFILE_H

#include "JSystem/JUtility/fs_form.h"
#include "types.h"

// #include <dolphin.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SDDriveInfo {
    /* 0x000 */ u16 nChan;
    /* 0x002 */ u16 unk_02;
    /* 0x004 */ u16 unk_04;
    /* 0x006 */ u16 unk_06;
    /* 0x008 */ char pad_unk_08[0x1C - 0x08];
    /* 0x01C */ u16 unk_1C;
    /* 0x01E */ u16 unk_1E[1];
    /* 0x020 */ char pad_unk_20[0x3C - 0x20];
    /* 0x03C */ u16 unk_3C;
    /* 0x03E */ char pad_unk_3E[0x60 - 0x3E];
    /* 0x060 */ s32 nSector;
    /* 0x064 */ u32 unk_64;
    /* 0x068 */ u32 unk_68;
    /* 0x06C */ s32 unk_6C;
    /* 0x070 */ u16 unk_70;
    /* 0x072 */ u16 unk_72;
    /* 0x074 */ u16 unk_74;
    /* 0x076 */ char unk_76[64];
    /* 0x0B6 */ char pad_unk_B6[0xBC - 0xB6];
    /* 0x0BC */ u16 unk_BC;
    /* 0x0BE */ u16 unk_BE;
    /* 0x0C0 */ u16 unk_C0;
    /* 0x0C2 */ char unk_C2[0x20];
    /* 0x0E2 */ u16 unk_E2;
    /* 0x0E4 */ char unk_E4;
    /* 0x0E5 */ char unk_E5;
    /* 0x0E6 */ char unk_E6;
    /* 0x0E7 */ char unk_E7;
    /* 0x0E8 */ void* unk_E8;
    /* 0x0EC */ void* unk_EC;
    /* 0x0F0 */ u32 pad_unk_F0;
    /* 0x0F4 */ u16 unk_F4;
    /* 0x0F6 */ char pad_unk_F6[0xFA - 0xF6];
    /* 0x0FA */ u16 unk_FA;
    /* 0x0FC */ u32 unk_FC;
    /* 0x100 */ u32 pad_unk_100;
} SDDriveInfo; // size = 0x104

// SDDirInfo ?
typedef struct UnkStruct_20A00 {
    /* 0x00 */ SDDriveInfo* pDriveInfo;
    /* 0x04 */ int unk_04;
    /* 0x08 */ int unk_08;
    /* 0x0C */ int unk_0C;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ char unk_14[64];
} UnkStruct_20A00; // size = 0x54

typedef struct SDFileInfo {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 pad_unk_02;
    /* 0x04 */ SDDriveInfo* pDriveInfo;
    /* 0x08 */ u8 unk_08[11];
    /* 0x13 */ u8 pad_unk_13;
    /* 0x14 */ char unk_14[10];
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ u32 unk_28;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ u32 unk_34;
    /* 0x38 */ u16 unk_38;
    /* 0x3A */ char path[64];
    /* 0x7A */ u8 pad_unk_7A;
    /* 0x7B */ u8 pad_unk_7B;
} SDFileInfo; // size = 0x7C

typedef struct UnkStruct_20BA4_2 {
    /* 0x00 */ u16 unk_00;
    /* 0x00 */ u16 unk_02;
    /* 0x00 */ u16 unk_04;
} UnkStruct_20BA4_2;

typedef struct UnkStruct_24BA4 {
    /* 0x00 */ u16 unk_00;
    /* 0x00 */ u16 unk_02;
    /* 0x00 */ u16 unk_04;
} UnkStruct_24BA4;

// size = 0x200? (see 80254D0C)
typedef struct UnkStruct_20BA4 {
    /* 0x00 */ u8 unk_00[2]; //! TODO: accessed either as u8 or u16??
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u16 pad_unk_08;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ char unk_0C[10];
    /* 0x16 */ u8 unk_16[2];
    /* 0x18 */ u8 unk_18[2];
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ u8 unk_1C;
    /* 0x1D */ u8 unk_1D;
    /* 0x1E */ u8 unk_1E;
    /* 0x1F */ u8 unk_1F;
} UnkStruct_20BA4; // size = 0x20

typedef struct UnknownStruct1 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u32 unk_04;
} UnknownStruct1; // size = 0x08

typedef struct DrvCtl_unk_20000 {
    /* 0x0000 */ char pad_unk_000[0x9F8];
    /* 0x09F8 */ void* unk_09F8;
    /* 0x0000 */ char pad_unk_9FC[0x0A00 - 0x9FC];
    /* 0x0A00 */ UnkStruct_20A00 unk_20A00[3];
    /* 0x0AFC */ UnkStruct_20A00 unk_20AFC[2];
    /* 0x0BA4 */ u8 unk_20BA4[sizeof(FSPartitionBootSector) * PBS_COUNT];
    /* 0x4BA4 */ UnknownStruct1 unk_24BA4;
    /* 0x4BAC */ char pad_unk_4BAC[0x4DA4 - 0x4BAC];
} DrvCtl_unk_20000; // size = 0x4DA4

typedef struct DrvCtl {
    /* 0x00000 */ u16 unk_00[4]; // note sure if it's the same array
    /* 0x00008 */ SDDriveInfo unk_08[2];
    /* 0x00210 */ SDFileInfo unk_210[5];
    /* 0x0047C */ SDFileInfo unk_47C[3];
    /* 0x005F0 */ char pad_unk_6E8[0x20000 - 0x5F0];
    /* 0x20000 */ DrvCtl_unk_20000 ctrl_p;
    /* 0x24DA4 */ char pad_unk_24DA4[0x259D4 - 0x24DA4];
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

#define GET_PBS_PTR(pDrvCtl, index) ((FSPartitionBootSector*)((pDrvCtl)->ctrl_p.unk_20BA4 + (index)))

extern DrvCtl FS_drv_ctl[2];

#ifdef __cplusplus
};
#endif

#endif
