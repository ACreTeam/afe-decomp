#ifndef FSFILE_H
#define FSFILE_H

#include "JSystem/JUtility/fs_form.h"
#include "types.h"

// #include <dolphin.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct UnknownStruct3 {
    /* 0x00 */ char unk_00[64];
    /* 0x40 */ u32 unk_40;
    /* 0x44 */ u16 unk_44; 
    /* 0x46 */ u16 unk_46; 
    /* 0x48 */ u16 unk_48; 
    /* 0x4A */ u16 unk_4A; 
    /* 0x4C */ u16 unk_4C; 
    /* 0x4E */ u16 unk_4E; 
    /* 0x50 */ u16 unk_50; 
    /* 0x52 */ u16 unk_52; 
} UnknownStruct3; // size = 0x54

typedef struct UnknownStruct2 {
    /* 0x000 */ u32 unk_000[0x102];
    /* 0x408 */ u16 unk_408[0x102];
    /* 0x60C */ u16 unk_60C[0x102];
    /* 0x810 */ u16 unk_810[0x102];
    /* 0xA14 */ u16 unk_A14[0x102];
    /* 0xC18 */ u16 unk_C18[0x102];
} UnknownStruct2; // size = 0xE1C

typedef struct SDDriveInfo {
    /* 0x000 */ u16 nChan;
    /* 0x002 */ u16 unk_02;
    /* 0x004 */ u16 unk_04;
    /* 0x006 */ u16 unk_06;
    /* 0x008 */ u32 unk_08;
    /* 0x00C */ u8 unk_0C;
    /* 0x00D */ u8 unk_0D;
    /* 0x00E */ u16 unk_0E;
    /* 0x010 */ u8 unk_10;
    /* 0x011 */ u8 unk_11;
    /* 0x012 */ u16 unk_12;
    /* 0x014 */ u32 unk_14;
    /* 0x018 */ u32 unk_18;
    /* 0x01C */ u16 unk_1C;
    /* 0x01E */ u16 unk_1E;
    /* 0x020 */ u16 unk_20;
    /* 0x022 */ u16 unk_22;
    /* 0x024 */ u16 unk_24;
    /* 0x026 */ u16 unk_26;
    /* 0x028 */ u16 unk_28;
    /* 0x02A */ u16 unk_2A;
    /* 0x02C */ u16 unk_2C;
    /* 0x02E */ u16 unk_2E;
    /* 0x030 */ u32 unk_30;
    /* 0x034 */ u32 unk_34;
    /* 0x038 */ u32 unk_38;
    /* 0x03C */ u16 unk_3C;
    /* 0x03E */ char unk_3E[12];
    /* 0x04A */ char unk_4A[9];
    /* 0x058 */ u8 unk_53;
    /* 0x058 */ u32 unk_54;
    /* 0x058 */ u32 unk_58;
    /* 0x05C */ u32 unk_5C;
    /* 0x060 */ s32 nSector;
    /* 0x064 */ u32 unk_64;
    /* 0x068 */ u32 unk_68;
    /* 0x06C */ s32 unk_6C;
    /* 0x070 */ u16 unk_70;
    /* 0x072 */ u16 unk_72;
    /* 0x074 */ u16 unk_74;
    /* 0x076 */ char unk_76[64];
    /* 0x0B6 */ u16 unk_B6;
    /* 0x0B8 */ u16 unk_B8;
    /* 0x0BA */ u16 unk_BA;
    /* 0x0BC */ u16 unk_BC;
    /* 0x0BE */ u16 unk_BE;
    /* 0x0C0 */ u16 unk_C0;
    /* 0x0C2 */ char unk_C2[32];
    /* 0x0E2 */ u16 unk_E2;
    /* 0x0E4 */ u16 unk_E4;
    /* 0x0E6 */ char unk_E6;
    /* 0x0E7 */ char unk_E7;
    /* 0x0E8 */ u8* unk_E8;
    /* 0x0EC */ UnknownStruct2* unk_EC;    
    /* 0x0F0 */ u16 unk_F0;
    /* 0x0F0 */ u16 unk_F2;
    /* 0x0F4 */ u16 unk_F4;
    /* 0x0F6 */ u16 unk_F6;
    /* 0x0F8 */ u16 unk_F8;
    /* 0x0FA */ u16 unk_FA;
    /* 0x0FC */ u32 unk_FC;
    /* 0x100 */ u16 unk_100;
    /* 0x100 */ u16 unk_102;
} SDDriveInfo; // size = 0x104

typedef struct SDDirInfo {
    /* 0x00 */ SDDriveInfo* pDriveInfo;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ char unk_14[64];
} SDDirInfo; // size = 0x54

typedef struct SDFileInfo {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ SDDriveInfo* pDriveInfo;
    /* 0x08 */ char unk_08[8 + 3]; // filename + extension
    /* 0x13 */ u8 unk_13;
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

typedef struct UnknownStruct1 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u32 unk_04;
} UnknownStruct1; // size = 0x08

typedef struct DrvCtl {
    /* 0x00000 */ u16 unk_00[4]; // note sure if it's the same array
    /* 0x00008 */ SDDriveInfo unk_08[2];
    /* 0x00210 */ SDFileInfo unk_210[5];
    /* 0x0047C */ SDFileInfo unk_47C[3];
    /* 0x005F0 */ u32 unk_5F0;
    /* 0x005F4 */ char unk_5F2[0x209F8 - 0x5F4];
    /* 0x209F8 */ void* unk_209F8;
    /* 0x20000 */ char pad_unk_209FC[4];
    /* 0x20A00 */ SDDirInfo unk_20A00[3];
    /* 0x20AFC */ SDDirInfo unk_20AFC[2];
    /* 0x20BA4 */ u8 unk_20BA4[sizeof(FSPartitionBootSector) * PBS_COUNT];
    /* 0x24BA4 */ UnknownStruct1 unk_24BA4;
    /* 0x24BAC */ u32 unk_24BAC;
    /* 0x24BB0 */ u32 unk_24BB0;
    /* 0x24BB4 */ u16 unk_24BB4;
    /* 0x24BB6 */ u16 unk_24BB6;
    /* 0x24BB8 */ UnknownStruct2 unk_24BB8;
    /* 0x259D4 */ s32 unk_259D4;
    /* 0x259D8 */ u32 unk_259D8;
    /* 0x259DC */ u16 unk_259DC;
    /* 0x259DE */ char pad_unk_259DE[0x25E48 - 0x259DE];
} DrvCtl; // size = 0x25E48

#define GET_FILE_INFO_COUNT(pDrvCtl, pDriveInfo) ((u16)((pDriveInfo)->unk_04 == 1 ? ARRAY_COUNT((pDrvCtl)->unk_210) : ARRAY_COUNT((pDrvCtl)->unk_47C)))
#define GET_DIR_INFO_COUNT(pDrvCtl, pDriveInfo) ((u16)((pDriveInfo)->unk_04 == 1 ? ARRAY_COUNT((pDrvCtl)->unk_20A00) : ARRAY_COUNT((pDrvCtl)->unk_20AFC)))
#define GET_DIR_INFO_COUNT2(pDrvCtl, pDriveInfo) (((pDriveInfo)->unk_04 == 1 ? ARRAY_COUNT((pDrvCtl)->unk_20A00) : ARRAY_COUNT((pDrvCtl)->unk_20AFC)))

extern DrvCtl FS_drv_ctl[2];

#ifdef __cplusplus
};
#endif

#endif
