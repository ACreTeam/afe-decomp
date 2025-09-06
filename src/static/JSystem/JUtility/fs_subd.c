#include "JSystem/JUtility/fs_subd.h"

u16 FS_fat_clear(FSFile* param1, u16 param2) {}
u16 FS_Flush(FSFile* pFile) {}
u16 FS_get_entry(void* param1, void* param2, char* param3, u16 param4, void* param5, void* param6, void* param7) {}
u16 FS_allocate_entry(FSFile* pFile, int param1, int* param2, u16* param3) {}
u16 FS_delete_lfn_entry(FSFile* pFile, u16 param1, int param2, u16 param3) {}
u16 FS_cluster_to_sector(FSFile* pFile, u16 param1) {}
u16 FS_read_sub(void* param1, int param2, int param3, int param4, u16* param5, u16* param6) {}
u16 FS_write_sub(void* param1, int param2, int param3, int param4, u16* param5, int param6, u16* param7) {}
u16 FS_divide_fpathname(void* param1, void* param2, void* param3, u16 param4) {}
u16 FS_entry_name_set(void* param1, int param2) {}

u16 FS_uchar_to_dchar(char* param1) {}

void FS_toupper(char *arg0) {
    char* pChar = arg0;
    int i;

    for (i = 0; i < FS_strlen(arg0); i++) {
        // >= 'a' && <= 'z'
        if (pChar[i] > 0x60 && pChar[i] < 0x7B) {
            pChar[i] -= 0x20;
        }
    }
}

void *FS_memset(void *dest, u16 ch, size_t count) {
    size_t var_r31;
    u32 var_r30;
    u8 *var_r29;
    u32 *var_r27;
    u8 *var_r28;
    s32 var_r26;

    var_r29 = dest;
    var_r31 = count;


    while (((u32) var_r29 & 3) && var_r31 != 0) {
        *var_r29++ = ch;
        var_r31--;
    }

    if (var_r31 > 4) {
        var_r26 = (ch + (ch << 8));
        var_r26 += var_r26 << 0x10;

        for (var_r27 = (u32*)var_r29, var_r30 = 0; var_r30 < (var_r31 >> 2); var_r30++, var_r27++) {
            *var_r27 = var_r26;
        }
    
        var_r29 = (u8*)var_r27;
        var_r31 -= var_r30 * 4;
    }

    if (var_r31 != 0) {
        var_r28 = var_r29;

        (void)var_r28;
        (void)var_r28;

        for (var_r30 = 0; var_r30 < var_r31; var_r30++, var_r28++) {
            *var_r28 = ch;
        }
    }

    return dest;
}

char *FS_strcpy(char *dest, const char *src) {
    size_t var_r31 = 0;

    while (var_r31 < -1) {
        dest[var_r31] = src[var_r31];

        if (src[var_r31] != '\0') {
            var_r31++;
            continue;
        }

        break;
    }

    return dest;
}

char *FS_strncpy(char *dest, const char *src, size_t num) {
    char *var_r26;
    char *var_r27;
    char *var_r30;
    char *var_r31;
    u32 var_r28;
    u32 var_r29;

    (void)var_r31;
    (void)var_r31;
    (void)var_r27;
    (void)var_r27;

    if (num != 0) {
        var_r31 = dest;
        var_r30 = (char*)src;
        var_r28 = num;

        if (((s32) dest & 1) && ((s32) var_r30 & 1)) {
            *var_r31 = *var_r30;
            var_r31++;
            var_r30++;
            var_r28--;
        } else if (((s32) var_r31 & 1) || ((s32) var_r30 & 1)) {
            var_r29 = 0;

            while (var_r29 < var_r28) {
                *var_r31 = *var_r30;
                var_r29++;
                var_r31++;
                var_r30++;
            }

            return dest;
        }

        if (var_r28 > 4) {
            var_r27 = var_r31;
            var_r26 = var_r30;
            var_r29 = 0;

            while (var_r29 < (u32) (var_r28 >> 2)) {
                *((s32*)var_r27) = *((s32*)var_r26);
                var_r29++;
                var_r27 += 4;
                var_r26 += 4;
            }

            var_r31 = var_r27;
            var_r30 = var_r26;
            var_r28 -= var_r29 * 4;
        }

        if (var_r28 != 0) {
            var_r29 = 0;

            while (var_r29 < var_r28) {
                *var_r31 = *var_r30;
                var_r29++;
                var_r31++;
                var_r30++;
            }
        }
    }

    return dest;
}

size_t FS_strlen(const char *s) {
    const char* pChar = s;
    size_t length;

    for (length = 0; length < -1; length++) {
        if (pChar[length] == '\0') {
            return length;
        }
    }

    return -1;
}

u16 FS_strncmp(const char *s1, const char *s2, size_t n) {
    int i;

    for (i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return -1;
        }
    }

    return 0;
}

void FS_srand(u16 arg0, u16 arg1) {
    DrvCtl *temp_r31;

    temp_r31 = &FS_drv_ctl[arg1];
    temp_r31->unk_259D8 = arg0;
    temp_r31->unk_259DC = 1;
}

u16 FS_rand(u16 arg0, u16 arg1) {
    DrvCtl *temp_r31;

    temp_r31 = &FS_drv_ctl[arg1];
    temp_r31->unk_259DC = 1;
    temp_r31->unk_259D8 = (temp_r31->unk_259D8 * 0x60C98293) + 0x3039;
    return (temp_r31->unk_259D8 % (arg0 + 1));
}
