#ifndef JUTFILESYSTEM_H
#define JUTFILESYSTEM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct UnkStruct_ReadWrite {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */ int unk_04;
} UnkStruct_ReadWrite; // size = 0x08

u16 FS_Open(void* param1, void** param2, char* param3, u16 param4);
u16 FS_Read(void* param1, const void* data, s32 length, int param4, UnkStruct_ReadWrite* param5);
u16 FS_Write(void* param1, const void* data, s32 length, int param4, UnkStruct_ReadWrite* param5);
u16 FS_Close(void* param1);
u16 FS_Seek(void* param1, int param2, int param3);
u16 FS_Getpos(void* param1, u32* param2);

//! TODO: return u16 instead of int?
int FS_CardIFReset();
int FS_Init(int param1, int param2, u16 param3);
int FS_Opendir(void* param1, void* param2, const char* param3);
int FS_Closedir(void* param1);
int FS_Mkdir(void* param1, const char* param2);
int FS_Chdir(void* param1, const char* param2);
int FS_Rename(void* param1, const char* param2, char* param3);
int FS_Delete(void* param1, const char* param2);
int FS_Format(const char* param1, u16 param2, u16 param3);
int FS_Mount(void** param1, u16 param2);
int FS_Umount(void* param1);
int FS_Readdir(void* param1, void* param2);

static inline int Init(int param1, int param2, u16 param3) {
    int r = FS_Init(param1, param2, param3);
    return r & 0xFFFF ? r : 0;
}

static inline int Opendir(void* param1, void* param2, const char* param3) {
    int r = FS_Opendir(param1, param2, param3);
    return r & 0xFFFF ? r : 0;
}

static inline int Closedir(void* param1) {
    int r = FS_Closedir(param1);
    return r & 0xFFFF ? r : 0;
}

static inline int Mkdir(void* param1, const char* param2) {
    int r = FS_Mkdir(param1, param2);
    return r & 0xFFFF ? r : 0;
}

static inline int Chdir(void* param1, const char* param2) {
    int r = FS_Chdir(param1, param2);
    return r & 0xFFFF ? r : 0;
}

static inline int Rename(void* param1, const char* param2, char* param3) {
    int r = FS_Rename(param1, param2, param3);
    return r & 0xFFFF ? r : 0;
}

static inline int Delete(void* param1, const char* param2) {
    int r = FS_Delete(param1, param2);
    return r & 0xFFFF ? r : 0;
}

static inline int Format(const char* param1, u16 param2, u16 param3) {
    int r = FS_Format(param1, param2, param3);
    return r & 0xFFFF ? r : 0;
}

static inline int Mount(void** param1, u16 param2) {
    int r = FS_Mount(param1, param2);
    return r & 0xFFFF ? r : 0;
}

static inline int Umount(void* param1) {
    int r = FS_Umount(param1);
    return r & 0xFFFF ? r : 0;
}

static inline int Readdir(void* param1, void* param2) {
    int r = FS_Readdir(param1, param2);
    return r & 0xFFFF ? r : 0;
}

#ifdef __cplusplus
};
#endif

#endif
