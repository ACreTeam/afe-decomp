#ifndef JUTSDCARD_H
#define JUTSDCARD_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SECTOR_SIZE 64

enum SDCommands {
    // Block Read
    /* 0x11 */ READ_SINGLE_BLOCK = 17,
    /* 0x12 */ READ_MULTIPLE_BLOCK = 18,
    /* 0x1E */ SEND_WRITE_PROT = 30,
    /* 0x33 */ SEND_SCR = 51,

    // Block Write
    /* 0x18 */ WRITE_BLOCK = 24,
    /* 0x19 */ WRITE_MULTIPLE_BLOCK = 25,
    /* 0x1A */ PROGRAM_CID = 26,
    /* 0x1B */ PROGRAM_CSD = 27,
    /* 0x2A */ LOCK_UNLOCK = 42,

    /* 0x00 */ GO_IDLE_STATE = 0,
    /* 0x09 */ SEND_CSD = 9,
    /* 0x0A */ SEND_CID = 10,
    /* 0x0C */ STOP_TRANSMISSION = 12,
    /* 0x0D */ SEND_STATUS = 13,
    /* 0x10 */ SET_BLOCKLEN = 16,
    /* 0x37 */ APP_CMD = 55,
    /* 0x38 */ GEN_CMD = 56,
    /* 0x4D */ CMD_4D = 77,
    /* 0x69 */ CMD_69 = 105,
};

enum SDErrorStatus {
    /* 0x400 */ LOCK_UNLOCK_FAILED = 1024,
};

typedef struct CID {
    u8 data[0x10];
} CID;

typedef struct CSD {
    u8 data[0x12];
} CSD;

typedef struct SDSTATUS {
    u8 data[0x40];
} SDSTATUS;

typedef struct CMD {
    u8 data[0x05];
} CMD;

typedef struct RES {
    u8 data[0x80];
} RES;

typedef struct ARG {
    union {
        u8 data[0x04];
        u32 data_u32;
    };
} ARG;

#ifdef __cplusplus
};
#endif

#endif
