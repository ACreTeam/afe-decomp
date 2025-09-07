#include "JSystem/JUtility/fs_subd.h"
#include "JSystem/JUtility/fs_drvsel.h"
#include "JSystem/JUtility/JUTSDCard.h"
#include "JSystem/JUtility/fs_file.h"
#include "types.h"

u16 FS_fat_clear(u16 param2, SDDriveInfo* param1) {}
u16 FS_Flush(SDDriveInfo* pFile) {}
u16 FS_get_entry(SDDriveInfo* param1, char* param2, char* param3, u16 param4, void* param5, void* param6, void* param7) {}
u16 FS_allocate_entry(FSFile* pFile, int param1, int* param2, u16* param3) {}
u16 FS_delete_lfn_entry(SDDriveInfo* pFile, u16 param1, int param2, u16 param3) {}
u16 FS_cluster_to_sector(FSFile* pFile, u16 param1) {}
u16 FS_read_sub(void* param1, int param2, int param3, int param4, u16* param5, u16* param6) {}

u16 FS_write_sub(UnkStruct_20BA4* param1, int param2, int param3, UnkStruct_20BA4* param4, u16 param5, u16 param6, u16 param7) {
    DrvCtl* pDrvCtl;
    u16 status;
    u16 sp1E;

    pDrvCtl = &FS_drv_ctl[param7];

    if (param5 != 1 && param5 != 2) {
        return 0xA016;
    }

    if (param4 == NULL) {
        param4 = &pDrvCtl->ctrl_p[1]->unk_20BA4; // 24ba4
    }

    if (param1 == NULL) {
        param1 = &pDrvCtl->ctrl_p[0]->unk_20BA4;
    }

    ((u16*)param4->unk_00)[0] = 0x2000;
    ((u16*)param4->unk_00)[1] = 0;
    param4->unk_04 = 0;

    if (param5 == 1) {
        if (pDrvCtl->unk_08[0].unk_06 == 2 && pDrvCtl->unk_08[0].unk_FC < (param3 + param2)) {
            return 0xA023;
        }
    } else {
        if (pDrvCtl->unk_08[1].unk_06 == 2 && pDrvCtl->unk_08[1].unk_FC < (param3 + param2)) {
            return 0xA023;
        }
    }

    if (param5 == 1) {
        status = FS_DrvSel_Write(param1, param2, param3, 0, (DrvCtl_unk_20000*)param4, pDrvCtl->unk_00[1]);
    } else {
        sp1E = param6;
        status = 0xA047;
    }

    return status;
}

s32 FS_csd_to_size(u32 *outSectorsPerCluster, s32 *outCsdBlockMultiplier, u16 modeFlags, u16 arg3, u16 chan) {
    s32 blockMultiplier;
    u32 i;
    DrvCtl* pDrvCtl;
    SDInfos rawCsdInfo;
    SDInfos csdInfo;
    u16 status;
    u16 sp16;
    u32 read_bl_len;
    u32 c_size;
    u32 c_size_mult;
    u32 max;
    u32 size;
    s32 t0;

    pDrvCtl = &FS_drv_ctl[chan];
    sp16 = arg3;

    // these are probably used somewhere in assert calls or something
    (void)read_bl_len;
    (void)c_size;
    (void)c_size_mult;
    (void)t0;


    if (modeFlags & FS_SD_CARD_MODE_RAW) {
        *outSectorsPerCluster = 0xF28 * 0x20; // 0x1E500
        *outCsdBlockMultiplier = 0x20;
    } else {
        *outSectorsPerCluster = 0xA0 * 0x08; // 0x500
        *outCsdBlockMultiplier = 0x20;
    }

    status = FS_DrvSel_Getinfo(&rawCsdInfo, pDrvCtl->unk_00[1]);

    // byte swap CSD register data I guess?
    i = 0;
    while (i < ARRAY_COUNT(csdInfo.data)) {
        csdInfo.data[i] = rawCsdInfo.data[0x1F - i];
        i++;
    }

    read_bl_len = ((u16)(csdInfo.data[12] & 3) << 2) | ((u16)(csdInfo.data[13] & (3 << 6)) >> 6);
    c_size = ((u16)(csdInfo.data[6] & (3 << 0)) << 10) | ((u16)(csdInfo.data[7] << 2)) | ((u16)(csdInfo.data[8] & (3 << 6)) >> 6);
    c_size_mult = ((u16)(csdInfo.data[9] & (3 << 0)) << 1) | ((u16)(csdInfo.data[10] & (1 << 7)) >> 7); // r23
    size = 1 + (c_size & 0xFFFF); // these are actually the 'total blocks' until the later multiplication step
    
    max = c_size_mult & 0xFFFF;
    blockMultiplier = 2;
    i = 0;
    while (i < (max + 1)) {
        blockMultiplier <<= 1;
        i++;
    }

    max = read_bl_len & 0xFFFF;
    t0 = 2;
    i = 0;
    while (i < max - 1) {
        t0 <<= 1;
        i++;
    }

    max = blockMultiplier;
    size *= max;

    if (modeFlags & FS_SD_CARD_MODE_RAW) {
        // Get the raw card size
        *outSectorsPerCluster = size;
        *outCsdBlockMultiplier = blockMultiplier;
    } else {
        // Chose an optimal cluster size for a given card size.
        // Larger capacity cards perform better with a larger minimum cluster size for files.
        if (size <= 0x1F60) {
            *outSectorsPerCluster = 0xA0; // 4MB card
        } else if (size <= 0x3F60) {
            *outSectorsPerCluster = 0xA0; // 8MB card
        } else if (size <= 0x7EC0) {
            *outSectorsPerCluster = 0xA0 * 0x02; // 16MB card
        } else if (size <= 0xFD80) {
            *outSectorsPerCluster = 0xA0 * 0x04; // 32MB card
        } else if (size <= 0x1F3E4) {
            *outSectorsPerCluster = 0xA0 * 0x08; // 64MB card
        } else if (size <= 0x3F600) {
            *outSectorsPerCluster = 0xA0 * 0x10; // 128MB card
        } else if (size <= 0x7EC0A) {
            *outSectorsPerCluster = 0xA0 * 0x20; // 256MB card
        } else if (size <= 0xFD800) {
            *outSectorsPerCluster = 0xA0 * 0x40; // 512MB card
        } else if (size <= 0x1FB000) {
            *outSectorsPerCluster = 0xA0 * 0x80; // 1GB card
        } else if (size <= 0x3F6000) {
            *outSectorsPerCluster = 0xA0 * 0x100; // 2GB card
        }

        *outCsdBlockMultiplier = blockMultiplier;
    }

    return 0;
}

u16 FS_divide_fpathname(char* param1, char** param2, u16* param3, u16 param4) {
    DrvCtl *sp18;
    u16 var_r30;
    u16 var_r31;

    var_r30 = 0;
    var_r31 = 0;
    sp18 = &FS_drv_ctl[param4];
    *param3 = 0;

    if (param1[0] != '\\') {
        return 0xA02C;
    }

    while (param1[0] != '\0') {
        if (var_r30 > 8 && var_r31 == 0) {
            return 0xA02C;
        }

        if (var_r31 > 4) {
            return 0xA02C;
        }

        if (param1[0] == '\\') {
            var_r30 = 0;
            var_r31 = 0;
            param1[0] = '\0';

            if ((param1++)[1] != '\0' && param1[0] != '\\') {
                (*param3)++;

                if (*param3 > 8) {
                    return 0xA013;
                }

                *param2 = param1;
                param2++;
            }
        } else {
            if (param1[0] == '.') {
                if (var_r31 != 0) {
                    return 0xA02C;
                }

                if (var_r30 == 0) {
                    return 0xA02C;
                }

                var_r31 = 1;
            } else {
                if (var_r31 != 0) {
                    var_r31++;
                } else {
                    var_r30++;
                }
            }

            param1++;
        }
    }

    if (var_r30 > 8 || var_r31 > 4) {
        return 0xA02C;
    }

    return 0;
}

// params not sure
u16 FS_fat_strcmp(UnkStruct_20BA4 *arg0, UnkStruct_20BA4 *arg1) {
    u16 var_r31 = 0;

    while (var_r31 < 5) {
        //! TODO: u16 vs u8 oddity, see `FS_Delete_Entry`
        if (((u16*)arg0->unk_00)[var_r31] != ((u16*)arg1->unk_00)[var_r31]) {
            return 0xA02B;
        }

        var_r31++;
    }

    if (arg0->unk_0A != arg1->unk_0A) {
        return 0xA02B;
    }

    return 0;
}

u16 FS_entry_name_set(char* param1, char* param2) {
    u16 var_r31;
    u16 var_r30;

    var_r31 = 0;
    while (var_r31 < 9) {
        if (param2[var_r31] == '\0' || param2[var_r31] == '.') {
            if (var_r31 == 0) {
                return 0xA02C;
            }

            var_r30 = var_r31;

            while (var_r30 < 8) {
                param1[var_r30] = ' ';
                var_r30++;
            }

            if (param2[var_r31] == '\0') {
                while (var_r30 < 0xB) {
                    param1[var_r30] = ' ';
                    var_r30++;
                }

                return 0;
            }

            var_r31++;
            break;
        }

        if (var_r31 == 8) {
            return 0xA02C;
        }

        param1[var_r31] = param2[var_r31];
        var_r31++;
    }

    var_r30 = 8;
    while (var_r30 < 0xC) {
        if (param2[var_r31] == '.') {
            return 0xA02C;
        }

        if (param2[var_r31] == '\0') {
            if (var_r30 == 8) {
                return 0xA02C;
            }

            while (var_r30 < 0xB) {
                param1[var_r30] = ' ';
                var_r30++;
            }

            return 0;
        }

        if (var_r30 == 0xB) {
            return 0xA02C;
        }

        param1[var_r30] = param2[var_r31];
        var_r30++;
        var_r31++;
    }

    return 0xA02C;
}

void FS_entname_to_stdname(char* param1) {
    char spC[12];
    u16 var_r29;
    u16 var_r30;
    u16 var_r31;

    FS_memset(spC, 0, sizeof(spC));
    var_r30 = 0;
    var_r31 = 11;

    while (var_r31 > 8) {
        if (param1[var_r31 - 1] != ' ') {
            var_r29 = var_r31;
            while (var_r29 > 8) {
                spC[var_r30] = param1[var_r29 - 1];
                var_r29--;
                var_r30++;
            }

            spC[var_r30] = '.';
            var_r30++;
            break;
        }

        var_r31--;
    }

    var_r31 = 8;
    while (var_r31 != 0) {
        if (param1[var_r31 - 1] != ' ') {
            var_r29 = var_r31;
            while (var_r29 != 0) {
                spC[var_r30] = param1[var_r29 - 1];
                var_r29--;
                var_r30++;
            }

            break;
        }

        var_r31--;
    }

    if (var_r30 == 0) {
        var_r29 = 0;
        while (var_r29 < 8) {
            spC[var_r30] = ' ';
            var_r29++;
            var_r30++;
        }
    }

    var_r31 = 0;
    while (var_r31 < var_r30) {
        param1[var_r31] = spC[var_r30 - var_r31 - 1];
        var_r31++;
    }

    param1[var_r31] ='\0';
}

u16 FS_uchar_to_dchar(char* param1) {
    char spC[64];
    u16 var_r29;
    u16 var_r28;
    u16 var_r31;
    size_t var_r30;

    var_r28 = 0;
    var_r30 = FS_strlen(param1);

    if (var_r30 > sizeof(spC) - 1) {
        return 0xA017;
    }

    if (var_r30 > (u16)-1) {
        return 0xA017;
    }

    FS_strcpy(spC, param1);
    FS_toupper(spC);

    var_r31 = 0;

    while (var_r31 < (u16)var_r30) {
        switch (spC[var_r31]) {
            case ' ':
            case '\\':
                if (var_r28 != 0) {
                    var_r29 = var_r31;

                    while (var_r29 < (u16)var_r30) {
                        spC[var_r29] = spC[var_r29 + 1];
                        var_r29++;
                    }

                    var_r31--;
                    var_r30--;
                }

                if (spC[var_r31] == '\\') {
                    var_r28 = 1;
                }
                break;
            default:
                var_r28 = 0;
                break;
        }

        var_r31++;
    }

    if (var_r31 > 1 && var_r28 != 0) {
        spC[var_r30 - 1] = '\0';
    }

    FS_strcpy(param1, spC);
    return 0;
}

void FS_toupper(char *param1) {
    char* pChar = param1;
    int i;

    for (i = 0; i < FS_strlen(param1); i++) {
        // pChar[i] >= 'a' && pChar[i] <= 'z'
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

void FS_srand(u16 param1, u16 param2) {
    DrvCtl *temp_r31;

    temp_r31 = &FS_drv_ctl[param2];
    temp_r31->unk_259D8 = param1;
    temp_r31->unk_259DC = 1;
}

u16 FS_rand(u16 param1, u16 param2) {
    DrvCtl *temp_r31;

    temp_r31 = &FS_drv_ctl[param2];
    temp_r31->unk_259DC = 1;
    temp_r31->unk_259D8 = (temp_r31->unk_259D8 * 0x60C98293) + 0x3039;
    return (temp_r31->unk_259D8 % (param1 + 1));
}
