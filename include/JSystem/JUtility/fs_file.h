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

    /* 0x60 */ s32 unk_60;
    /* 0x64 */ char pad_unk_64[8];
    /* 0x6C */ s32 unk_6C;
    /* 0x70 */ u16 unk_70; 
    /* 0x72 */ u16 unk_72; 
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ char unk_76[64];
    /* 0xB6 */ char pad_unk_96[0xBC - 0xB6];
    /* 0xBC */ u16 unk_BC;
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

typedef struct UnkStruct_20BA4 {
    /* 0x00 */ u8 unk_00[2];
    /* 0x02 */ char pad_unk_04[0x0A - 0x02];
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ char pad_unk_0C[0x1A - 0x0C];
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ int pad_unk_1C;
} UnkStruct_20BA4; // size = 0x20

typedef struct DrvCtl_unk_20000 {
    char pad[0xBA4];
    /* 0xBA4 */ UnkStruct_20BA4 unk_20BA4;
} DrvCtl_unk_20000;

typedef struct DrvCtl {
    /* 0x00000 */ u16 unk_00[2];
    /* 0x00004 */ u16 unk_04;
    /* 0x00006 */ u16 unk_06;
    /* 0x00008 */ u16 unk_08[2];
    /* 0x0000C */ u16 unk_0C;
    /* 0x0000E */ u16 unk_0E;
    /* 0x00010 */ char pad_unk_10[0xB8];
    /* 0x000C8 */ u16 unk_C8;
    /* 0x000CA */ char pad_unk_CA[0x32];
    /* 0x000FC */ u16 unk_FC;
    /* 0x000FE */ char pad_unk_FE[4];
    /* 0x00102 */ u16 unk_102;
    /* 0x00104 */ char pad_unk_104[0xE];
    /* 0x00112 */ u16 unk_112;
    /* 0x00114 */ char pad_unk_114[0xB8];
    /* 0x001CC */ u16 unk_1CC;
    /* 0x001CE */ char pad_unk_1CE[0x32];
    /* 0x00200 */ u16 unk_200;
    /* 0x00202 */ char pad_unk_202[4];
    /* 0x00206 */ u16 unk_206;
    /* 0x00208 */ char pad_unk_208[0x20000 - 0x00208];
    /* 0x20000 */ DrvCtl_unk_20000* ctrl_p[2];
    /* 0x20008 */ u8 pad[(0x20BC4 - 0x20008)];

    //! TODO: part of DrvCtl_unk_20000?
    /* 0x20BC4 */ char pad_unk_20BC4[0x4E10];
    /* 0x259D4 */ s32 unk_259D4;
    /* 0x259D8 */ u32 unk_259D8;
    /* 0x259DC */ u16 unk_259DC;
    /* 0x259DE */ char pad_unk_259DE[0x46A];
} DrvCtl; // size = 0x25E48

extern DrvCtl FS_drv_ctl[CARD_NUM_CHANS];

#ifdef __cplusplus
};
#endif

#endif
