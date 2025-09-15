#include "JSystem/JUtility/fs_form.h"

#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_drvsel.h"
#include "JSystem/JUtility/fs_subd.h"
#include "JSystem/JUtility/time.h"
#include "macros.h"

#include <stddef.h>

typedef struct DataCluTbl {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
} DataCluTbl;

u32 FS_LCS;
u16 FS_TRACK_PER_SECTOR;
u16 FS_HEAD_NUM;
u32 FS_gl_partition_size;
u16 FS_gl_card_size;
u16 FS_format_fat_mode;
u16 FS_gl_bu;
u8 FS_FAT_MODE;
u16 FS_FAT_SC;
u32 FS_FAT_MAX;
u16 FS_FAT_SF;
u16 FS_FAT_SSA;
u16 FS_FAT_RSC;
u16 FS_FAT_MBR;
u16 FS_BUF_POS_FDC;
u16 FS_BUF_POS_FAT1;
u16 FS_BUF_POS_FAT2;
u16 FS_BUF_POS_RDE;

static inline void FS_UnknownMathInline1(u32* param1, u16 param2, u32 param3) {
    if (param2 == 1) {
        *param1 += FS_gl_bu * ((FS_gl_bu + param3 + 1) / FS_gl_bu);

        if ((FS_gl_bu + param3 + 1) / FS_gl_bu == (FS_gl_bu + param3) / FS_gl_bu) {
            *param1 += FS_gl_bu;
        }
    } else {
        *param1 += param3 + 1;
    }
}

static inline u16 FS_UnknownMathInline2(u32 param1) {
    return ((FS_FAT_MAX + 1) * param1 + 0xFFF) >> 0xC;
}

u16 FS_Format(const char* param1, u16 param2, u16 param3) {
    int pad1;
    int pad2;
    s32 sp10;
    u16 status;

    sp10 = 0;
    (void)pad1;
    (void)pad1;

    if (param3 > 1) {
        return 0xA00C;
    }

    FS_format_fat_mode = 1;
    FS_gl_partition_size = 0x3D40;
    FS_gl_card_size = 8;

    status = FS_Format_sub(param1, param2, 0, 1, 1, param3);
    if (status != 0) {
        return status;
    }

    return 0;
}

u16 FS_Format_sub(const char* param1, u16 param2, u16 param3, u16 param4, u16 param5, u16 nChan) {
    UnknownStruct1 sp38;
    s32 sp34;
    u32 sp30;
    u32 sp2C;
    u32 sp28;
    u16 sp24;
    char sp18[12];
    DrvCtl* temp_r25;
    u16 var_r21;
    u16 status;
    u32 var_r31;
    u32 var_r27;
    u32 var_r23;
    u32 var_r22;

    static const DataCluTbl data_clu_tbl[] = {
        { 0x00004000, 0x0010, 0x0010 }, { 0x00020000, 0x0020, 0x0020 }, { 0x00080000, 0x0020, 0x0040 },
        { 0x00200000, 0x0020, 0x0080 }, { 0x00400000, 0x0040, 0x0080 }, { 0x0000FFFF, 0xFFFF, 0xFFFF },
    };

    static const DataCluTbl prot_clu_tbl[] = {
        { 0x00000200, 0x0001, 0x0001 }, { 0x00000800, 0x0002, 0x0002 }, { 0x00002000, 0x0008, 0x0008 },
        { 0x00200000, 0x0020, 0x0020 }, { 0x00400000, 0x0040, 0x0040 }, { 0x0000FFFF, 0xFFFF, 0xFFFF },
    };

    sp34 = 0;
    temp_r25 = &FS_drv_ctl[nChan];

    status = FS_DrvSel_Getstatus(&sp24, temp_r25->unk_00[1]);
    if (status != 0) {
        return status;
    }

    if (sp24 & 0x400) {
        return 0xA037;
    } else if (sp24 & 0x4000) {
        var_r21 = 2;
    } else if (sp24 & 0x8000) {
        var_r21 = 1;
    } else if (sp24 & 0x2000) {
        var_r21 = 4;
    } else {
        return 0xA037;
    }

    FS_memset(temp_r25->unk_20BA4, 0, sizeof(temp_r25->unk_20BA4));
    FS_memset(sp18, 0, sizeof(sp18));

    if (param1 != NULL) {
        for (var_r31 = 0; var_r31 < ARRAY_COUNT(sp18); var_r31++) {
            if (param1[var_r31] == '\0') {
                break;
            }

            if (var_r31 == 11) {
                return 0xA00C;
            }

            sp18[var_r31] = param1[var_r31];
        }
    }

    var_r27 = 0;

    if (param1 != NULL) {
        for (var_r31 = 0; var_r31 < 0xC; var_r31++) {
            if (sp18[var_r31] != 0x20) {
                break;
            }

            var_r27++;
        }

        if (var_r27 != 0) {
            for (var_r31 = 0; var_r31 < (0xC - var_r27); var_r31++) {
                sp18[var_r31] = sp18[var_r31 + var_r27];
            }
        }
    }

    FS_toupper(sp18);

    if (param2 != 1 && param2 != 2) {
        return 0xA00C;
    }

    if (param4 != 2 && param4 != 1) {
        return 0xA00C;
    }

    if ((param4 == 1 && temp_r25->unk_08[0].unk_06 == 2) || (param4 == 2 && temp_r25->unk_08[1].unk_06 == 2)) {
        return 0xA002;
    }

    status = FS_get_area_information(param4, &sp30, &sp2C, var_r21, nChan);
    if (status != 0) {
        return status;
    }

    sp28 = sp30;

    if (param4 == 1) {
        for (var_r31 = 0; var_r31 <= ARRAY_COUNT(data_clu_tbl) - 1; var_r31++) {
            if (data_clu_tbl[var_r31].unk_00 == 0xFFFF) {
                return 0xA00E;
            }

            if (data_clu_tbl[var_r31].unk_00 >= sp2C) {
                FS_FAT_SC = data_clu_tbl[var_r31].unk_04;
                FS_gl_bu = data_clu_tbl[var_r31].unk_06;
                break;
            }
        }
    } else {
        for (var_r31 = 0; var_r31 <= ARRAY_COUNT(prot_clu_tbl) - 1; var_r31++) {
            if (prot_clu_tbl[var_r31].unk_00 == 0xFFFF) {
                return 0xA00E;
            }

            if (prot_clu_tbl[var_r31].unk_00 >= sp30) {
                FS_FAT_SC = prot_clu_tbl[var_r31].unk_04;
                FS_gl_bu = prot_clu_tbl[var_r31].unk_06;
                break;
            }
        }
    }

    if (param3 == 1 || param3 == 2 || param3 == 4 || param3 == 8 || param3 == 0x10 || param3 == 0x20 ||
        param3 == 0x40) {
        FS_FAT_SC = param3;
    } else if (param3 != 0) {
        return 0xA00C;
    }

    FS_LCS = FS_FAT_SC << 9;

    if (param4 == 1) {
        var_r23 = FS_FAT_SC * 0xFEF;
        var_r22 = FS_FAT_SC * 0xFF7;

        if (param5 == 1) {
            var_r23 += (FS_gl_bu * ((u32)(FS_gl_bu + 0x39) / FS_gl_bu));
            var_r22 += (FS_gl_bu * ((u32)(FS_gl_bu + 0x41) / FS_gl_bu));

            if (((u32)(FS_gl_bu + 0x39) / FS_gl_bu) == ((u32)(FS_gl_bu + 0x38) / FS_gl_bu)) {
                var_r23 += FS_gl_bu;
            }

            if (((u32)(FS_gl_bu + 0x41) / FS_gl_bu) == ((u32)(FS_gl_bu + 0x40) / FS_gl_bu)) {
                var_r22 += FS_gl_bu;
            }
        } else {
            var_r23 += 0x39;
            var_r22 += 0x41;
        }

        if (sp28 >= var_r23 && sp28 < var_r22) {
            sp28 = var_r23 - FS_FAT_SC;
        }
    }

    status = FS_calc_parameter(&sp28, param5);
    if (status != 0) {
        return status;
    }

    FS_BUF_POS_FDC = FS_FAT_MBR / 32;
    FS_BUF_POS_FAT1 = (FS_FAT_MBR + FS_FAT_RSC) / 32;
    FS_BUF_POS_FAT2 = (FS_FAT_MBR + FS_FAT_RSC + FS_FAT_SF) / 32;
    FS_BUF_POS_RDE = (FS_FAT_MBR + FS_FAT_RSC + FS_FAT_SF * 2) / 32;

    if (param5 == 1) {
        status = FS_init_mbr(sp28, &sp34, param4, nChan);
        if (status != 0) {
            return status;
        }
    }

    status = FS_init_pbs(sp18, sp28, &sp34, param4, param5, nChan);
    if (status != 0) {
        return status;
    }

    status = FS_init_fat(&sp34, param4, nChan);
    if (status != 0) {
        return status;
    }

    status = FS_init_rde(sp18, &sp34, param4, nChan);
    if (status != 0) {
        return status;
    }

    if (param2 == 1) {
        FS_memset(temp_r25->unk_20BA4, 0xFF, sizeof(temp_r25->unk_20BA4));
        sp34 = FS_FAT_SSA + FS_FAT_MBR;

        for (var_r31 = 0; var_r31 < ((u32)((FS_FAT_MAX - 1) * FS_FAT_SC) >> 5); var_r31++) {
            status = FS_format_write_sub(&sp34, param4, nChan);
            if (status != 0) {
                return status;
            }
        }

        sp38.unk_00 = 0x2000;
        sp38.unk_02 = 0;
        sp38.unk_04 = 0;
        var_r27 = ((FS_FAT_MAX - 1) * FS_FAT_SC) & 0x1F;

        if (var_r27 != 0) {
            if (param4 == 1) {
                status = FS_DrvSel_Write(temp_r25->unk_20BA4, var_r27, sp34, 0, &sp38, temp_r25->unk_00[1]);
            } else {
                status = 0xA047;
            }

            if (status != 0) {
                return status;
            }

            sp34 += var_r27;
        }
    }

    return status;
}

u16 FS_calc_parameter(u32* param1, u16 param2) {
    u32 var_r31;
    u32 var_r30;
    u32 var_r29;
    u32 var_r28;

    var_r29 = FS_FAT_SC * 0xFFF6;
    FS_UnknownMathInline1(&var_r29, param2, 0x220);

    if (*param1 >= var_r29) {
        return 0xA034;
    }

    var_r30 = FS_FAT_SC * 0xFF4;
    FS_UnknownMathInline1(&var_r30, param2, 0x38);

    var_r28 = FS_FAT_SC * 0xFF5;
    FS_UnknownMathInline1(&var_r28, param2, 0x40);

    if (FS_format_fat_mode == 2) {
        // most likely a debug left-over
        (void)0;
    }

    if (*param1 >= var_r28) {
        FS_FAT_MODE = MODE_UNK_1;
        var_r31 = 0x10;
    } else if (*param1 > var_r30) {
        FS_FAT_MODE = MODE_FAT12;
        var_r31 = 0xC;
        *param1 = var_r30;
    } else {
        FS_FAT_MODE = MODE_FAT12;
        var_r31 = 0xC;
    }

    FS_FAT_MAX = *param1 / FS_FAT_SC + 1;
    FS_FAT_SF = FS_UnknownMathInline2(var_r31);
    FS_FAT_RSC = 1;

    do {
        FS_FAT_SSA = FS_FAT_SF * 2 + 0x20;

        if (param2 == 1) {
            FS_FAT_MBR = FS_gl_bu - (FS_FAT_SSA % FS_gl_bu);

            if (FS_FAT_MBR == 1) {
                FS_FAT_MBR = FS_gl_bu;
            } else {
                FS_FAT_MBR -= FS_FAT_RSC;
                FS_FAT_MBR += FS_gl_bu;
            }
        } else {
            FS_FAT_MBR = 0;
        }

        FS_FAT_SSA += FS_FAT_RSC;

        if (*param1 < FS_FAT_MBR + FS_FAT_SSA) {
            return 0xA01E;
        }

        FS_FAT_MAX = (*param1 - FS_FAT_MBR - FS_FAT_SSA) / FS_FAT_SC + 1;

        if (FS_FAT_MAX < 1) {
            return 0xA01E;
        }

        if (FS_FAT_SF == FS_UnknownMathInline2(var_r31)) {
            return 0;
        }

        if (FS_FAT_SF < FS_UnknownMathInline2(var_r31)) {
            if (param2 == 1) {
                FS_FAT_MBR += FS_gl_bu;
                FS_FAT_MAX = (*param1 - FS_FAT_MBR - FS_FAT_SSA) / FS_FAT_SC + 1;

                if (FS_FAT_SF == FS_UnknownMathInline2(var_r31)) {
                    return 0;
                }

                if (FS_FAT_SC == 1) {
                    FS_FAT_MBR += FS_gl_bu;
                    FS_FAT_MAX = (*param1 - FS_FAT_MBR - FS_FAT_SSA) / FS_FAT_SC + 1;

                    if (FS_FAT_SF == FS_UnknownMathInline2(var_r31)) {
                        return 0;
                    }
                }

                return 0xA01E;
            }

            FS_FAT_MAX = (*param1 - FS_FAT_MBR - FS_FAT_SSA) / FS_FAT_SC;
            *param1 -= FS_gl_bu;

            if (FS_FAT_SF == FS_UnknownMathInline2(var_r31)) {
                return 0;
            }

            if (FS_FAT_SC == 1) {
                FS_FAT_MAX = ((*param1 - FS_FAT_MBR) - FS_FAT_SSA) / FS_FAT_SC;
                *param1 -= FS_gl_bu;

                if (FS_FAT_SF == FS_UnknownMathInline2(var_r31)) {
                    return 0;
                }
            }

            return 0xA01E;
        }

        FS_FAT_SF--;
    } while (FS_FAT_SF != 0);

    return 0xA01E;
}

inline void test(DrvCtl* temp_r31, u32 arg1, u16 index) {

}

u32 GET_FS_LCS() { return FS_LCS; };
u16 GET_FS_TRACK_PER_SECTOR() { return FS_TRACK_PER_SECTOR; };
u16 GET_FS_HEAD_NUM() { return FS_HEAD_NUM; };
u32 GET_FS_gl_partition_size() { return FS_gl_partition_size; };
u16 GET_FS_gl_card_size() { return FS_gl_card_size; };
u16 GET_FS_format_fat_mode() { return FS_format_fat_mode; };
u16 GET_FS_gl_bu() { return FS_gl_bu; };
u8 GET_FS_FAT_MODE() { return FS_FAT_MODE; };
u16 GET_FS_FAT_SC() { return FS_FAT_SC; };
u32 GET_FS_FAT_MAX() { return FS_FAT_MAX; };
u16 GET_FS_FAT_SF() { return FS_FAT_SF; };
u16 GET_FS_FAT_SSA() { return FS_FAT_SSA; };
u16 GET_FS_FAT_RSC() { return FS_FAT_RSC; };
u16 GET_FS_FAT_MBR() { return FS_FAT_MBR; };
u16 GET_FS_BUF_POS_FDC() { return FS_BUF_POS_FDC; };
u16 GET_FS_BUF_POS_FAT1() { return FS_BUF_POS_FAT1; };
u16 GET_FS_BUF_POS_FAT2() { return FS_BUF_POS_FAT2; };
u16 GET_FS_BUF_POS_RDE() { return FS_BUF_POS_RDE; };

u16 FS_init_pbs(char* arg0, u32 arg1, s32* arg2, u16 arg3, u16 arg4, u16 arg5) {
    DrvCtl* temp_r31;
    u16 index;
    u16 status;
    u16 var_r24;
    u16 temp_r29=0;
    u16 tmp;

    (void)arg4;
    (void)temp_r29; // this is actually r25
    (void)temp_r29; // this is actually r25
    (void)status;
    (void)status;

    temp_r31 = &FS_drv_ctl[arg5];
    index = ((FS_FAT_MBR % 32) * sizeof(FSPartitionBootSector));

    // test(temp_r31, arg1, index);

    temp_r31->unk_20BA4[(OFFSET_BS_JMP_BOOT_INDEX_0 + index)] = 0xEB;
    temp_r31->unk_20BA4[(OFFSET_BS_JMP_BOOT_INDEX_1 + index)] = 0x00;
    temp_r31->unk_20BA4[(OFFSET_BS_JMP_BOOT_INDEX_2 + index)] = 0x90;


    FS_memset(&temp_r31->unk_20BA4[OFFSET_BS_OEM_NAME + index], 0x20,
              membersize(FSPartitionBootSector16, BS_OEMName));
    FS_strncpy((char*)&temp_r31->unk_20BA4[OFFSET_BS_OEM_NAME + index], "        ",
               membersize(FSPartitionBootSector16, BS_OEMName));

    temp_r31->unk_20BA4[OFFSET_BPB_BYTES_PER_SEC_INDEX_0 + index] = 0;
    temp_r31->unk_20BA4[OFFSET_BPB_BYTES_PER_SEC_INDEX_1 + index] = 2;

    temp_r31->unk_20BA4[OFFSET_BPB_SEC_PER_CLUS + index] = FS_LCS / sizeof(FSPartitionBootSector);
    temp_r31->unk_20BA4[OFFSET_BPB_RSVD_SEC_CNT_INDEX_0 + index] = FS_FAT_RSC;
    temp_r31->unk_20BA4[OFFSET_BPB_RSVD_SEC_CNT_INDEX_1 + index] = (FS_FAT_RSC >> 8);

    temp_r31->unk_20BA4[OFFSET_BPB_NUM_FATS + index] = 2;
    temp_r31->unk_20BA4[OFFSET_BPB_ROOT_ENT_CNT_INDEX_0 + index] = 0;
    temp_r31->unk_20BA4[OFFSET_BPB_ROOT_ENT_CNT_INDEX_1 + index] = 2;

    if ((arg1 - FS_FAT_MBR) < 0x10000) {
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_16_INDEX_0 + index] = arg1 - FS_FAT_MBR;
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_16_INDEX_1 + index] = (arg1 - FS_FAT_MBR) >> 8;
    } else {
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_16_INDEX_0 + index] = 0;
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_16_INDEX_1 + index] = 0;
    }

    temp_r31->unk_20BA4[OFFSET_BPB_MEDIA + index] = 0xF8;
    temp_r31->unk_20BA4[OFFSET_BPB_FAT_SZ_16_INDEX_0 + index] = FS_FAT_SF;
    temp_r31->unk_20BA4[OFFSET_BPB_FAT_SZ_16_INDEX_1 + index] = FS_FAT_SF >> 8;

    temp_r31->unk_20BA4[OFFSET_BPB_SEC_PER_TRK_INDEX_0 + index] = FS_TRACK_PER_SECTOR;
    temp_r31->unk_20BA4[OFFSET_BPB_SEC_PER_TRK_INDEX_1 + index] = FS_TRACK_PER_SECTOR >> 8;

    temp_r31->unk_20BA4[OFFSET_BPB_NUM_HEADS_INDEX_0 + index] = FS_HEAD_NUM;
    temp_r31->unk_20BA4[OFFSET_BPB_NUM_HEADS_INDEX_1 + index] = FS_HEAD_NUM >> 8;

    temp_r31->unk_20BA4[OFFSET_BPB_HIDD_SEC_INDEX_0 + index] = FS_FAT_MBR & 0xFF;
    temp_r31->unk_20BA4[OFFSET_BPB_HIDD_SEC_INDEX_1 + index] = EXTRACT_BITS(FS_FAT_MBR, 8, 8);
    temp_r31->unk_20BA4[OFFSET_BPB_HIDD_SEC_INDEX_2 + index] = EXTRACT_BITS(FS_FAT_MBR, 8, 16);
    temp_r31->unk_20BA4[OFFSET_BPB_HIDD_SEC_INDEX_3 + index] = (FS_FAT_MBR >> 24) & 0xFF;

    if ((arg1 - FS_FAT_MBR) > 0xFFFF) {
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_32_INDEX_0 + index] = (arg1 - FS_FAT_MBR) >> 0;
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_32_INDEX_1 + index] = EXTRACT_BITS(arg1 - FS_FAT_MBR, 8, 8);
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_32_INDEX_2 + index] = EXTRACT_BITS(arg1 - FS_FAT_MBR, 8, 16);
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_32_INDEX_3 + index] = (arg1 - FS_FAT_MBR) >> 24;
    } else {
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_32_INDEX_0 + index] = 0;
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_32_INDEX_1 + index] = 0;
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_32_INDEX_2 + index] = 0;
        temp_r31->unk_20BA4[OFFSET_BPB_TOT_SEC_32_INDEX_3 + index] = 0;
    }

    temp_r31->unk_20BA4[OFFSET_BS_DRV_NUM + index] = 0x80;
    temp_r31->unk_20BA4[OFFSET_BS_RESERVED_1 + index] = 0;
    temp_r31->unk_20BA4[OFFSET_BS_BOOT_SIG + index] = 0x29;

    if (temp_r31->unk_259DC == 0) {
        FS_srand(GetRandomSeed(), arg5);
    }

    status = FS_rand(0xFF, arg5) * 256;
    // tmp = FS_rand(0xFF, arg5);
    status *= (temp_r29 = FS_rand(0xFF, arg5));
    temp_r31->unk_20BA4[OFFSET_BS_VOL_ID_INDEX_0 + index] = status;
    temp_r31->unk_20BA4[OFFSET_BS_VOL_ID_INDEX_1 + index] = EXTRACT_BITS(status, 8, 8);

    status = FS_rand(0xFF, arg5) * 256;
    // tmp = FS_rand(0xFF, arg5);
    status *= (temp_r29 = FS_rand(0xFF, arg5));
    temp_r31->unk_20BA4[OFFSET_BS_VOL_ID_INDEX_2 + index] = status;
    // temp_r31->unk_20BA4[OFFSET_BS_VOL_ID_INDEX_3 + index] = EXTRACT_BITS(status, 8, 8);
    temp_r31->unk_20BA4[OFFSET_BS_VOL_ID_INDEX_3 + index] = (status >> 8) & 0xFF;

    if (arg0[0] != '\0') {
        FS_memset(&temp_r31->unk_20BA4[OFFSET_BS_VOL_LAB + index], 0x20,
                  membersize(FSPartitionBootSector16, BS_VolLab));
        FS_strncpy((char*)&temp_r31->unk_20BA4[OFFSET_BS_VOL_LAB + index], arg0, FS_strlen(arg0));
    } else {
        FS_strcpy((char*)&temp_r31->unk_20BA4[OFFSET_BS_VOL_LAB + index], "NO NAME    ");
    }

    if (FS_FAT_MODE == MODE_FAT12) {
        FS_strcpy((char*)&temp_r31->unk_20BA4[OFFSET_BS_FIL_SYS_TYPE + index], "FAT12   ");
    } else {
        FS_strcpy((char*)&temp_r31->unk_20BA4[OFFSET_BS_FIL_SYS_TYPE + index], "FAT16   ");
    }

    FS_memset(&temp_r31->unk_20BA4[OFFSET_BS_BOOT_CODE + index], 0,
              membersize(FSPartitionBootSector16, BS_BootCode));
    temp_r31->unk_20BA4[OFFSET_BS_BOOT_SIGN_INDEX_0 + index] = 0x55;
    temp_r31->unk_20BA4[OFFSET_BS_BOOT_SIGN_INDEX_1 + index] = 0xAA;

    if (FS_BUF_POS_FDC != FS_BUF_POS_FAT1) {
        status = FS_format_write_sub(arg2, arg3, arg5);
        if (status != 0) {
            return status;
        }

        FS_memset(temp_r31->unk_20BA4, 0, sizeof(temp_r31->unk_20BA4));

        for (var_r24 = FS_BUF_POS_FDC; var_r24 < (FS_BUF_POS_FAT1 - 1); var_r24++) {
            status = FS_format_write_sub(arg2, arg3, arg5);
            if (status != 0) {
                return status;
            }
        }
    }

    return 0;
}

u16 FS_init_fat(s32* arg0, u16 arg1, u16 nChan) {
    u32 index;
    u16 status;
    u16 var_r25;
    u16 var_r28;
    DrvCtl* temp_r29;
    u16 var_r27;
    u16 var_r26;

    temp_r29 = &FS_drv_ctl[nChan];

    for (var_r26 = 1; var_r26 < 3; var_r26++) {
        if (var_r26 == 1) {
            index = ((FS_FAT_MBR + FS_FAT_RSC) & 0x1F) * (sizeof(FSPartitionBootSector));
            var_r28 = FS_BUF_POS_FAT1;
            var_r27 = FS_BUF_POS_FAT2;
        } else {
            index = ((FS_FAT_MBR + FS_FAT_RSC + FS_FAT_SF) & 0x1F) * (sizeof(FSPartitionBootSector));
            var_r28 = FS_BUF_POS_FAT2;
            var_r27 = FS_BUF_POS_RDE;
        }

        temp_r29->unk_20BA4[OFFSET_BS_JMP_BOOT_INDEX_0 + index] = 0xF8;
        temp_r29->unk_20BA4[OFFSET_BS_JMP_BOOT_INDEX_1 + index] = 0xFF;
        temp_r29->unk_20BA4[OFFSET_BS_JMP_BOOT_INDEX_2 + index] = 0xFF;

        if (FS_FAT_MODE == MODE_UNK_1) {
            temp_r29->unk_20BA4[OFFSET_BS_OEM_NAME + index] = 0xFF;
        }

        if (var_r28 != var_r27) {
            status = FS_format_write_sub(arg0, arg1, nChan);
            if (status != 0) {
                return status;
            }

            FS_memset(temp_r29->unk_20BA4, 0, sizeof(temp_r29->unk_20BA4));

            for (var_r25 = var_r28; var_r25 < (var_r27 - 1); var_r25++) {
                status = FS_format_write_sub(arg0, arg1, nChan);
                if (status != 0) {
                    return status;
                }
            }
        }
    }

    return 0;
}

u16 FS_init_rde(char* arg0, s32* arg1, u16 arg2, u16 nChan) {
    char* pArg0;
    DrvCtl* temp_r31;
    u16 temp_r30;
    s32 var_r29;
    u16 status = 0;

    (void)arg0;
    (void)arg0;
    (void)pArg0;
    (void)pArg0;

    pArg0 = arg0;
    temp_r31 = &FS_drv_ctl[nChan];
    temp_r30 = ((FS_FAT_MBR + FS_FAT_RSC + FS_FAT_SF * 2) * sizeof(FSPartitionBootSector)) & 0x3E00;

    if (pArg0[0] != '\0') {
        FS_memset(&temp_r31->unk_20BA4[OFFSET_DIR_NAME + temp_r30], 0x20, membersize(FSDirEntry, DIR_Name));
        FS_strncpy((char*)&temp_r31->unk_20BA4[OFFSET_DIR_NAME + temp_r30], arg0, FS_strlen(arg0));
        temp_r31->unk_20BA4[OFFSET_DIR_ATTR + temp_r30] = 0x28;
        FS_set_now_date((FSDirEntry*)&temp_r31->unk_20BA4[temp_r30], NULL);
    }

    var_r29 = sizeof(FSDirEntry);
    var_r29 += ((FS_FAT_MBR + FS_FAT_RSC + FS_FAT_SF * 2) & 0x1F) & 0xFFFF;
    var_r29 &= 0xFFFF;

    while (var_r29 > 0) {
        status = FS_format_write_sub(arg1, arg2, nChan);
        if (status != 0) {
            return status;
        }

        FS_memset(temp_r31->unk_20BA4, 0, sizeof(temp_r31->unk_20BA4));
        var_r29 -= sizeof(FSDirEntry);
    }

    return 0;
}

u16 FS_init_mbr(u32 param1, s32* param2, u16 param3, u16 nChan) {
    u8* temp_r31;
    u8* pMBR;
    u16 temp_r5;
    u16 status;
    u16 var_r26;
    DrvCtl* temp_r29;

    (void)temp_r5;
    (void)temp_r5;
    (void)temp_r5;
    (void)temp_r5;

    temp_r29 = &FS_drv_ctl[nChan];
    pMBR = PTR_MBR_BASE(temp_r29, 0);
    temp_r31 = PTR_MBR_BASE(temp_r29, 0);
    PTR_MBR(temp_r31)->partition_table[0].status = 0;
    PTR_MBR(temp_r31)->partition_table[0].chs_start_head = (FS_FAT_MBR % (FS_TRACK_PER_SECTOR * FS_HEAD_NUM)) / FS_TRACK_PER_SECTOR;

    temp_r5 = (FS_FAT_MBR % (FS_TRACK_PER_SECTOR * FS_HEAD_NUM)) % FS_TRACK_PER_SECTOR + 1;
    PTR_MBR(temp_r31)->partition_table[0].chs_start_sector.data_u8[0] &= 0xC0;
    PTR_MBR(temp_r31)->partition_table[0].chs_start_sector.data_u8[0] |= temp_r5 & 0x3F;

    temp_r5 = (FS_FAT_MBR / (FS_TRACK_PER_SECTOR * FS_HEAD_NUM)) & 0xFFFF;
    PTR_MBR(temp_r31)->partition_table[0].chs_start_sector.data_u8[0] &= 0x3F;
    PTR_MBR(temp_r31)->partition_table[0].chs_start_sector.data_u8[0] |= (((u32)(temp_r5 >> 8) & 3) << 6);
    PTR_MBR(temp_r31)->partition_table[0].chs_start_sector.data_u8[1] = temp_r5;

    temp_r31 = (u8*)&PTR_MBR(temp_r31)->partition_table[0];
    if ((param1 - FS_FAT_MBR) < 0x7FA8) {
        PTR_MBR_ENTRY(temp_r31)->partition_type = 1;
    } else if ((param1 - FS_FAT_MBR) < 0x10000) {
        PTR_MBR_ENTRY(temp_r31)->partition_type = 4;
    } else {
        PTR_MBR_ENTRY(temp_r31)->partition_type = 6;
    }

    PTR_MBR_ENTRY(temp_r31)->chs_end_head = ((param1 - 1) % (FS_TRACK_PER_SECTOR * FS_HEAD_NUM)) / FS_TRACK_PER_SECTOR;
    temp_r5 = (((param1 - 1) % (FS_TRACK_PER_SECTOR * FS_HEAD_NUM)) % FS_TRACK_PER_SECTOR + 1);
    PTR_MBR_ENTRY(temp_r31)->chs_end_sector.data_u8[0] &= 0xC0;
    PTR_MBR_ENTRY(temp_r31)->chs_end_sector.data_u8[0] |= temp_r5 & 0x3F;

    temp_r5 = (param1 - 1) / (FS_TRACK_PER_SECTOR * FS_HEAD_NUM);
    PTR_MBR_ENTRY(temp_r31)->chs_end_sector.data_u8[0] &= 0x3F;
    PTR_MBR_ENTRY(temp_r31)->chs_end_sector.data_u8[0] |= (((u32)(temp_r5 >> 8) & 3) << 6);
    PTR_MBR_ENTRY(temp_r31)->chs_end_sector.data_u8[1] = temp_r5;

    temp_r29->unk_20BA4[0x1C6] = (FS_FAT_MBR >> 0);
    temp_r29->unk_20BA4[0x1C7] = (FS_FAT_MBR >> 8);
    temp_r29->unk_20BA4[0x1C8] = (FS_FAT_MBR >> 16);
    temp_r29->unk_20BA4[0x1C9] = (FS_FAT_MBR >> 24);

    temp_r29->unk_20BA4[0x1CA] = ((param1 - FS_FAT_MBR) >> 0);
    temp_r29->unk_20BA4[0x1CB] = ((param1 - FS_FAT_MBR) >> 8);
    temp_r29->unk_20BA4[0x1CC] = ((param1 - FS_FAT_MBR) >> 16);
    temp_r29->unk_20BA4[0x1CD] = ((param1 - FS_FAT_MBR) >> 24);

    temp_r29->unk_20BA4[0x1FE] = 0x55;
    temp_r29->unk_20BA4[0x1FF] = 0xAA;

    if (FS_BUF_POS_FDC != 0) {
        status = FS_format_write_sub(param2, param3, nChan);
        if (status != 0) {
            return status;
        }

        FS_memset(temp_r29->unk_20BA4, 0, sizeof(temp_r29->unk_20BA4));

        for (var_r26 = 0; var_r26 < (FS_BUF_POS_FDC - 1); var_r26++) {
            status = FS_format_write_sub(param2, param3, nChan);
            if (status != 0) {
                return status;
            }
        }
    }

    return 0;
}

u16 FS_get_area_information(u16 param1, u32* param2, u32* param3, u16 param4, u16 param6) {
    s32 sp20;
    u32 sp1C;
    u32 sp18;
    u16 var_r31;
    u16 status;

    static const DataCluTbl chs_tbl[] = {
        { 0x00001000, 0x0002, 0x0010 }, { 0x00008000, 0x0002, 0x0020 }, { 0x00010000, 0x0004, 0x0020 },
        { 0x00040000, 0x0008, 0x0020 }, { 0x00080000, 0x0010, 0x0020 }, { 0x000FC000, 0x0010, 0x003F },
        { 0x001F8000, 0x0020, 0x003F }, { 0x003F0000, 0x0040, 0x003F }, { 0x00400000, 0x0080, 0x003F },
        { 0x0000FFFF, 0xFFFF, 0xFFFF },
    };

    status = FS_csd_to_size(&sp1C, &sp20, FS_SD_CARD_MODE_RAW, param4, param6);
    if (status != 0) {
        return 0xA00E;
    }

    status = FS_csd_to_size(&sp18, &sp20, FS_SD_CARD_MODE_FORMATTED_MODE, param4, param6);
    if (status != 0) {
        return 0xA00E;
    }

    if (param1 == 1) {
        *param2 = sp1C;
    } else {
        *param2 = sp18;
    }

    *param3 = sp1C + sp18;
    sp20 = *param3;

    for (var_r31 = 0; var_r31 < 9; var_r31++) {
        if (chs_tbl[var_r31].unk_00 == 0xFFFF) {
            return 0xA00E;
        }

        if (chs_tbl[var_r31].unk_00 >= sp20) {
            FS_HEAD_NUM = chs_tbl[var_r31].unk_04;
            FS_TRACK_PER_SECTOR = chs_tbl[var_r31].unk_06;

            break;
        }
    }

    return 0;
}

u16 FS_format_write_sub(s32* param1, u16 param2, u16 nChan) {
    UnknownStruct1 sp10;
    DrvCtl* temp_r31;
    u16 status;

    temp_r31 = &FS_drv_ctl[nChan];
    sp10.unk_00 = 0x2000;
    sp10.unk_02 = 0;
    sp10.unk_04 = 0;

    if (param2 == 1) {
        status = FS_DrvSel_Write(temp_r31->unk_20BA4, 0x20, *param1, 0, &sp10, temp_r31->unk_00[1]);

        if (status != 0) {
            return status;
        }
    } else {
        return 0xA047;
    }

    *param1 += 0x20;
    return 0;
}
