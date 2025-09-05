#ifndef FSCLDR_H
#define FSCLDR_H

#include "JSystem/JUtility/fs_file.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FSDir {
    /* 0x00 */ FSFile* pFile;
    /* 0x04 */ int unk_04;
    /* 0x08 */ int unk_08;
    /* 0x0C */ int unk_0C;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ char unk_14[64];
} FSDir; // size = 0x44

extern u16 FS_Closedir(FSDir* pDir);
extern u16 FS_Closedir_sub(FSDir* pDir);

static inline u16 Closedir(FSDir* param1) {
    u16 status = FS_Closedir(param1);
    return status != 0 ? status : 0;
}

#ifdef __cplusplus
};
#endif

#endif
