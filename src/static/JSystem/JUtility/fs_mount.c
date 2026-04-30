#include "JSystem/JUtility/fs_mount.h"

#include "JSystem/JUtility/fs_drvsel.h"
#include "JSystem/JUtility/fs_form.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Mount(SDDriveInfo** ppDriveInfo, u16 nChan) {
    DrvCtl* temp_r29;
    SDDriveInfo* temp_r27;
    u16 status;

    if (ppDriveInfo == NULL) {
        return 0xA00C;
    }

    if (nChan > 1) {
        return 0xA00C;
    }

    temp_r29 = &FS_drv_ctl[nChan];

    if (nChan != temp_r29->unk_00[0]) {
        return 0xA00C;
    }

    temp_r27 = *ppDriveInfo;
    *ppDriveInfo = temp_r29->unk_08;
    (*ppDriveInfo)->unk_04 = 1;
    (*ppDriveInfo)->nChan = nChan;
    (*ppDriveInfo)->unk_02 = temp_r29->unk_00[1];

    if ((*ppDriveInfo)->unk_F4 != 0) {
        *ppDriveInfo = temp_r27;
        return 0xA009;
    }

    status = FS_Mount_sub(*ppDriveInfo);
    if (status != 0 && (status == 0xA01A || (status & 0xFF00) != 0xA000)) {
        *ppDriveInfo = temp_r27;
    }

    return status;
}

u16 FS_Mount_sub(SDDriveInfo* pDriveInfo) {
    DrvCtl* spC;
    u16 status;

    spC = &FS_drv_ctl[pDriveInfo->nChan];
    pDriveInfo->unk_06 = 1;
    status = FS_GetCardInfo(pDriveInfo);

    if (status != 0 && (status == 0xA01A || (status & 0xFF00) != 0xA000)) {
        return status;
    }

    FS_InitGlobalData(pDriveInfo);

    status = FS_ReadMBR(pDriveInfo);
    if (status != 0 && (status == 0xA01A || (status & 0xFF00) != 0xA000)) {
        return status;
    }

    status = FS_ReadFDC(pDriveInfo);
    if (status != 0 && (status == 0xA01A || (status & 0xFF00) != 0xA000)) {
        return status;
    }

    status = FS_ReadFAT(pDriveInfo);
    if (status != 0 && (status == 0xA01A || (status & 0xFF00) != 0xA000)) {
        return status;
    }

    status = FS_ChkMnt(pDriveInfo);
    if (status != 0 && (status == 0xA01A || (status & 0xFF00) != 0xA000)) {
        return status;
    }

    if (pDriveInfo->unk_102 & 1) {
        pDriveInfo->unk_06 = 1;
        return status;
    }

    if (pDriveInfo->unk_102 & 8) {
        status = 0xA046;
    } else {
        status = 0;
    }

    pDriveInfo->unk_06 = 2;
    return status;
}

u16 FS_GetCardInfo(SDDriveInfo* pDriveInfo) {
    u16 sp14;
    u32 sp10;
    s32 spC;
    u16 status;

    sp14 = 0xFFFF;
    status = FS_DrvSel_Getstatus(&sp14, pDriveInfo->unk_02);
    if (status != 0) {
        pDriveInfo->unk_102 |= 1;
        return status;
    }

    if (sp14 & 0x400) {
        pDriveInfo->unk_102 |= 1;
        return 0xA037;
    }

    if ((sp14 & 0xE000) == 0xE000 || (sp14 & 0xE000) == 0xC000 || (sp14 & 0xE000) == 0xA000 ||
        (sp14 & 0xE000) == 0x6000 || !(sp14 & 0xE000)) {
        pDriveInfo->unk_102 |= 1;
        return 0xA037;
    }

    if (sp14 & 0x8000) {
        pDriveInfo->unk_100 = 1;
    } else if (sp14 & 0x4000) {
        pDriveInfo->unk_100 = 2;
    } else if (sp14 & 0x2000) {
        pDriveInfo->unk_100 = 4;
    } else {
        pDriveInfo->unk_102 |= 1;
        return 0xA037;
    }

    status = FS_csd_to_size(&sp10, &spC, pDriveInfo->unk_04, pDriveInfo->unk_100, pDriveInfo->nChan);
    if (status != 0) {
        pDriveInfo->unk_FC ^= pDriveInfo->unk_FC;
        pDriveInfo->unk_102 |= 1;
        return status;
    }

    pDriveInfo->unk_FC = sp10;
    return 0;
}

void FS_InitGlobalData(SDDriveInfo* pDriveInfo) {
    DrvCtl* temp_r30;
    SDDriveInfo* var_r28;
    u16 var_r31;
    void* temp_r3;

    temp_r30 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo->unk_04 == 1) {
        for (var_r31 = 0; var_r31 < ARRAY_COUNT(temp_r30->unk_210); var_r31++) {
            temp_r30->unk_210[var_r31].unk_00 = 0xFFFF;
            temp_r30->unk_210[var_r31].pDriveInfo = NULL;
        }

        for (var_r31 = 0; var_r31 < ARRAY_COUNT(temp_r30->unk_20A00); var_r31++) {
            temp_r30->unk_20A00[var_r31].pDriveInfo = NULL;
            temp_r30->unk_20A00[var_r31].unk_04 = 0;
            temp_r30->unk_20A00[var_r31].unk_08 = 0;
            temp_r30->unk_20A00[var_r31].unk_10 = 0;
            FS_memset(temp_r30->unk_20A00[var_r31].unk_14, 0, sizeof(temp_r30->unk_20A00[var_r31].unk_14));
        }
    } else if (pDriveInfo->unk_04 == 2) {
        for (var_r31 = 0; var_r31 < ARRAY_COUNT(temp_r30->unk_47C); var_r31++) {
            temp_r30->unk_47C[var_r31].unk_00 = 0xFFFF;
            temp_r30->unk_47C[var_r31].pDriveInfo = NULL;
        }

        for (var_r31 = 0; var_r31 < ARRAY_COUNT(temp_r30->unk_20AFC); var_r31++) {
            temp_r30->unk_20AFC[var_r31].pDriveInfo = NULL;
            temp_r30->unk_20AFC[var_r31].unk_04 = 0;
            temp_r30->unk_20AFC[var_r31].unk_08 = 0;
            temp_r30->unk_20AFC[var_r31].unk_10 = 0;
            FS_memset(temp_r30->unk_20AFC[var_r31].unk_14, 0, sizeof(temp_r30->unk_20AFC[var_r31].unk_14));
        }
    }

    pDriveInfo->unk_EC = &temp_r30->unk_24BB8;

    if (pDriveInfo->unk_04 == 1) {
        var_r28 = &temp_r30->unk_08[1];
    } else {
        var_r28 = &temp_r30->unk_08[0];
    }

    if (pDriveInfo->unk_06 == 1 && var_r28->unk_06 == 1) {
        FS_memset(&temp_r30->unk_24BB8, 0, sizeof(UnknownStruct2));

        for (var_r31 = 0; var_r31 < 0x102; var_r31++) {
            temp_r30->unk_24BB8.unk_408[var_r31] = 3;
            temp_r30->unk_24BB8.unk_C18[var_r31] = 0;
        }
    }

    pDriveInfo->unk_F8 ^= pDriveInfo->unk_F8;
    pDriveInfo->unk_102 ^= pDriveInfo->unk_102;
    pDriveInfo->unk_F6 ^= pDriveInfo->unk_F6;
    pDriveInfo->unk_6C = 0;
    pDriveInfo->unk_70 = 0;
    pDriveInfo->unk_72 = 0;
    pDriveInfo->unk_74 = 0;
    FS_memset(pDriveInfo->unk_76, 0, sizeof(pDriveInfo->unk_76));
    FS_strncpy(pDriveInfo->unk_76, "\\", 1);
    pDriveInfo->unk_E2 = 0;
    FS_memset(pDriveInfo->unk_C2, 0, sizeof(pDriveInfo->unk_C2));
    pDriveInfo->unk_E4 = 0x200;
}

//! TODO: hidden inline?
u16 FS_ReadMBR(SDDriveInfo* pDriveInfo) {
    u8* temp_r28;
    u8* ptr2;
    DrvCtl* temp_r27;
    u16 status;
    int pad1;
    int pad2;
    int pad3;

    pad1 = 0;
    pad2 = 0;
    pad3 = 0;

    (void)pad1;
    (void)pad1;
    (void)pad1;
    (void)pad2;
    (void)pad2;
    (void)pad2;
    (void)pad3;
    (void)pad3;
    (void)pad3;
    (void)pad3;
    (void)pad3;
    (void)pad3;
    (void)pad3;

    (void)pDriveInfo;
    (void)pDriveInfo;
    (void)temp_r27;

    temp_r27 = &FS_drv_ctl[pDriveInfo->nChan];
    temp_r28 = &temp_r27->unk_20BA4[0];
    ptr2 = &temp_r27->unk_20BA4[sizeof(FSMasterBootRecord)];
    pDriveInfo->unk_08 = 0;

    status = FS_read_sub(temp_r28, 1, 0, NULL, pDriveInfo->unk_04, pDriveInfo->nChan);
    if (status != 0) {
        pDriveInfo->unk_102 |= 1;
        return status;
    }

    status = FS_ChkMBR(pDriveInfo, (FSMasterBootRecord*)temp_r28, (FSDescriptor*)ptr2);
    if (status != 0) {
        if (status == 0xA01A || (status & 0xFF00) != 0xA000) {
            return status;
        }
    } else {
        pDriveInfo->unk_08 = LOAD_LE_u32(((FSMasterBootRecord*)temp_r28)->partition_table[0].lba_start_sector.data_u32);
    }

    return status;
}

u16 FS_ChkMBR(SDDriveInfo* pDriveInfo, FSMasterBootRecord* pMBR, FSDescriptor* pFDC) {
    u16 status2;
    u16 status;
    DrvCtl* temp_r25;
    u32 r27;
    u32 temp_r24;

    (void)pDriveInfo;
    (void)pDriveInfo;
    (void)pDriveInfo;

    r27 = 1;
    temp_r25 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pMBR == NULL) {
        pMBR = (FSMasterBootRecord*)&temp_r25->unk_20BA4[0];
    }

    if (pFDC == NULL) {
        pFDC = (FSDescriptor*)&temp_r25->unk_20BA4[sizeof(FSMasterBootRecord)];
    }

    temp_r24 = LOAD_LE_u32(pMBR->partition_table[0].lba_start_sector.data_u32);
    if ((r27 > pDriveInfo->unk_FC) || ((r27 + temp_r24) > pDriveInfo->unk_FC)) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    status = FS_read_sub((u8*)pFDC, r27, temp_r24, NULL, pDriveInfo->unk_04, pDriveInfo->nChan);
    if (status != 0) {
        pDriveInfo->unk_102 |= 2;
        return 0xA01D;
    }

    status2 = FS_ChkFDC(pDriveInfo, pFDC, 1);
    status = status2;
    if (status != 0) {
        pDriveInfo->unk_102 &= ~5;
        pDriveInfo->unk_102 |= 2;
        status2 = 0xA01D;
    } else if ((pMBR->partition_table[0].chs_start_sector.data_u8[0] == 0x80) ||
               (pMBR->partition_table[0].chs_start_sector.data_u8[0] == 0)) {
        if (*(u32*)&pMBR->partition_table[0].total_sectors.data_u8[2] < 0x7FA8) {
            if (pMBR->partition_table[0].chs_end_sector.data_u8[0] != 1) {
                goto exit;
            }
        } else if (*(u32*)&pMBR->partition_table[0].total_sectors.data_u8[2] < 0x10000) {
            if (pMBR->partition_table[0].chs_end_sector.data_u8[0] != 4) {
                goto exit;
            }
        } else {
            if (pMBR->partition_table[0].chs_end_sector.data_u8[0] != 6) {
                goto exit;
            }
        }

        pDriveInfo->unk_F8 |= 1;
    }

exit:
    return status2;
}

u16 FS_ReadFDC(SDDriveInfo* pDriveInfo) {
    u16 status;
    int pad;

    (void)pad;
    (void)pad;

    status = FS_read_sub(NULL, 1U, pDriveInfo->unk_08, 0, pDriveInfo->unk_04, pDriveInfo->nChan);
    if (status != 0) {
        pDriveInfo->unk_102 |= 1;
        return status;
    }

    status = FS_ChkFDC(pDriveInfo, NULL, 7);
    if (pDriveInfo->unk_102 & 1) {
        return status;
    }

    FS_SetFDC(pDriveInfo);

    status = FS_SetFATsecN(pDriveInfo);
    if (pDriveInfo->unk_102 & 1) {
        return status;
    }

    status = FS_SetFATkind(pDriveInfo);
    if (pDriveInfo->unk_102 & 1) {
        return status;
    }

    if (pDriveInfo->unk_1E <= 0x20U) {
        pDriveInfo->unk_F6 = pDriveInfo->unk_1E;
    } else {
        pDriveInfo->unk_F6 = 0x20;
    }

    return status;
}

void FS_SetFDC(SDDriveInfo* pDriveInfo) {
    DrvCtl* temp_r28;
    u8 temp_r29;
    FSDescriptor* temp_r31;

    temp_r28 = &FS_drv_ctl[pDriveInfo->nChan];
    temp_r31 = (FSDescriptor*)&temp_r28->unk_20BA4[0];

    FS_strncpy(pDriveInfo->unk_4A, temp_r31->oem_name, sizeof(pDriveInfo->unk_4A) - 1);
    pDriveInfo->unk_4A[8] = '\0';

    pDriveInfo->unk_1C = LOAD_LE_u16(temp_r31->bytes_per_sector.data_u16);
    pDriveInfo->unk_1E = temp_r31->sectors_per_cluster;
    pDriveInfo->unk_24 = LOAD_LE_u16(temp_r31->reserved_sectors.data_u16);
    pDriveInfo->unk_26 = temp_r31->fat_count;
    pDriveInfo->unk_28 = LOAD_LE_u16(temp_r31->root_dir_entries.data_u16);
    pDriveInfo->unk_2A = LOAD_LE_u16(temp_r31->total_sectors.data_u16);
    pDriveInfo->unk_2C = temp_r31->media_type;
    pDriveInfo->unk_2E = LOAD_LE_u16(temp_r31->sectors_per_fat.data_u16);
    pDriveInfo->unk_20 = LOAD_LE_u16(temp_r31->sectors_per_track.data_u16);
    pDriveInfo->unk_22 = LOAD_LE_u16(temp_r31->num_heads.data_u16);
    temp_r29 = temp_r31->extended_boot_sig;
    pDriveInfo->unk_53 = temp_r29;

    if (temp_r29 == FDC_ATTR_EXTENDED_BOOT) {
        pDriveInfo->unk_F8 |= 4;
        pDriveInfo->unk_30 = LOAD_LE_u32(temp_r31->hidden_sectors);
        pDriveInfo->unk_34 = LOAD_LE_u32(temp_r31->total_sectors_32);
        pDriveInfo->unk_38 = LOAD_LE_u32(temp_r31->volume_id);
        FS_strncpy(pDriveInfo->unk_3E, temp_r31->volume_label, sizeof(pDriveInfo->unk_3E) - 1);
        pDriveInfo->unk_3E[11] = '\0';

        if (FS_strncmp(temp_r31->fs_type, "FAT12   ", sizeof(temp_r31->fs_type)) == 0) {
            pDriveInfo->unk_3C = 2;
            return;
        }

        if (FS_strncmp(temp_r31->fs_type, "FAT16   ", sizeof(temp_r31->fs_type)) == 0) {
            pDriveInfo->unk_3C = 1;
            return;
        }

        pDriveInfo->unk_3C = 8;
        return;
    }

    pDriveInfo->unk_F8 |= 2;
    pDriveInfo->unk_30 = 0;
    pDriveInfo->unk_34 = 0;
    pDriveInfo->unk_53 = 0;
    pDriveInfo->unk_38 = 0;
    FS_memset(pDriveInfo->unk_3E, 0, sizeof(pDriveInfo->unk_3E) - 1);
    pDriveInfo->unk_3E[11] = '\0';
    pDriveInfo->unk_3C = 8;
}

u16 FS_SetFATkind(SDDriveInfo* pDriveInfo) {
    u32 uVar2;

    if (pDriveInfo->unk_1E == 0) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    uVar2 = (pDriveInfo->unk_68 - pDriveInfo->unk_64) / pDriveInfo->unk_1E;

    if (uVar2 < 0xFF5) {
        if (pDriveInfo->unk_3C != 2) {
            if (pDriveInfo->unk_3C == 1) {
                pDriveInfo->unk_3C = 2;
                pDriveInfo->unk_102 |= 2;
                return 0xA01D;
            }

            if (pDriveInfo->unk_3C == 8) {
                pDriveInfo->unk_3C = 2;
            }
        }
    } else if (uVar2 == 0xFF5) {
        if (pDriveInfo->unk_3C == 2) {
            pDriveInfo->unk_3C = 1;
            pDriveInfo->unk_102 |= 2;
            return 0xA01D;
        }

        if (pDriveInfo->unk_3C != 1 && pDriveInfo->unk_3C == 8) {
            if (pDriveInfo->unk_2E == 0xC) {
                pDriveInfo->unk_3C = 2;
            } else {
                if (pDriveInfo->unk_2E == 0x10) {
                    pDriveInfo->unk_3C = 1;
                } else {
                    pDriveInfo->unk_102 |= 1;
                    return 0xA01A;
                }
            }
        }
    } else if (uVar2 > 0xFF5) {
        if (pDriveInfo->unk_3C == 2) {
            pDriveInfo->unk_3C = 1;
            pDriveInfo->unk_102 |= 2;
            return 0xA01D;
        }

        if (pDriveInfo->unk_3C != 1 && pDriveInfo->unk_3C == 8) {
            pDriveInfo->unk_3C = 1;
        }
    }

    return 0;
}

u16 FS_SetFATsecN(SDDriveInfo* pDriveInfo) {
    u16 status;

    status = 0;
    pDriveInfo->unk_54 = pDriveInfo->unk_08;
    pDriveInfo->unk_58 = pDriveInfo->unk_54 + pDriveInfo->unk_24;
    pDriveInfo->unk_5C = pDriveInfo->unk_58 + pDriveInfo->unk_2E;
    pDriveInfo->nSector = pDriveInfo->unk_5C + pDriveInfo->unk_2E;

    if (pDriveInfo->unk_1C != 0) {
        pDriveInfo->unk_64 = pDriveInfo->nSector;
        pDriveInfo->unk_64 += (pDriveInfo->unk_1C + pDriveInfo->unk_28 * 32u - 1) / pDriveInfo->unk_1C;
    } else {
        pDriveInfo->unk_64 = 0;
        pDriveInfo->unk_102 |= 1;
        status = 0xA01A;
    }

    if (pDriveInfo->unk_2A != 0) {
        pDriveInfo->unk_68 = pDriveInfo->unk_2A + pDriveInfo->unk_54;
    } else {
        pDriveInfo->unk_68 = pDriveInfo->unk_34 + pDriveInfo->unk_54;
    }

    if (pDriveInfo->unk_64 > pDriveInfo->unk_68) {
        pDriveInfo->unk_102 |= 1;
        status = 0xA01A;
    }

    return status;
}

u16 FS_ReadFAT(SDDriveInfo* pDriveInfo) {
    DrvCtl* temp_r31;
    SDDriveInfo* var_r29;
    u16 status;
    u16 temp_r28_2;

    temp_r31 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo->unk_04 == 1) {
        var_r29 = &temp_r31->unk_08[1];
    } else {
        var_r29 = &temp_r31->unk_08[0];
    }

    if (pDriveInfo->unk_04 == 2 || (var_r29->unk_04 == 2 && var_r29->unk_06 == 2)) {
        temp_r31->unk_5F4 = temp_r31->unk_08[1].unk_2E * temp_r31->unk_08[1].unk_1C;
        temp_r31->unk_5F0 = 0x20400 - temp_r31->unk_5F4;
    } else {
        temp_r31->unk_5F4 = 0;
        temp_r31->unk_5F0 = 0x20400;
    }

    status = FS_ReadFATSetCacheInfo(pDriveInfo, var_r29);
    if (pDriveInfo->unk_102 & 1) {
        return status;
    }

    if (pDriveInfo->unk_F0 == 1 || var_r29->unk_F0 == 1) {
        pDriveInfo->unk_102 |= 8;
    }

    status = FS_ReadFATSetFATinfo(pDriveInfo);
    FS_ReadFATSetMemSize(pDriveInfo, var_r29);
    return status;
}

u16 FS_ReadFATSetCacheInfo(SDDriveInfo* pDriveInfo, SDDriveInfo* param2) {
    DrvCtl* temp_r28;
    u16 status;

    (void)param2;

    status = 0;
    temp_r28 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo->unk_06 == 2 || (pDriveInfo->unk_06 == 2 && param2->unk_06 == 2)) {
        status = FS_Flush(pDriveInfo);

        if (status != 0) {
            pDriveInfo->unk_102 |= 1;
            return status;
        }
    } else if (pDriveInfo->unk_06 == 1 && param2->unk_06 == 1) {
        if (pDriveInfo->unk_2E * pDriveInfo->unk_1C > temp_r28->unk_5F0) {
            pDriveInfo->unk_BA = 0;
            pDriveInfo->unk_F0 = 1;
        } else {
            pDriveInfo->unk_BA = 0;
            pDriveInfo->unk_F0 = 0x102;
        }
    } else if (param2->unk_06 == 2) {
        if (pDriveInfo->unk_1C * (pDriveInfo->unk_2E + param2->unk_2E) > temp_r28->unk_5F0) {
            status = FS_Flush(param2);

            if (status != 0) {
                pDriveInfo->unk_102 |= 1;
                return status;
            }

            pDriveInfo->unk_BA = param2->unk_BA = 0;
            pDriveInfo->unk_F0 = param2->unk_F0 = 1;
        } else {
            if (param2->unk_BA != 0) {
                pDriveInfo->unk_BA = 0;
            } else {
                pDriveInfo->unk_BA = temp_r28->unk_5F0 / pDriveInfo->unk_1C - pDriveInfo->unk_2E;
            }

            pDriveInfo->unk_F0 = 0x102;
        }
    }

    return status;
}

u16 FS_ReadFATSetFATinfo(SDDriveInfo* pDriveInfo) {
    u16 status = 0;

    if ((pDriveInfo->unk_F0 & 0xF00) == 0x100) {
        status = FS_ReadFATSetFAT(pDriveInfo);
        pDriveInfo->unk_F0 &= ~0x100;

        if (pDriveInfo->unk_102 & 1) {
            return status;
        }
    } else {
        pDriveInfo->unk_B8 = 1;
        pDriveInfo->unk_BE = 2;

        if (pDriveInfo->unk_1E != 0) {
            pDriveInfo->unk_BC = ((pDriveInfo->unk_68 - pDriveInfo->unk_64) / pDriveInfo->unk_1E) + 2;
        } else {
            pDriveInfo->unk_102 |= 1;
            status = 0xA01A;
        }
    }

    if ((pDriveInfo->unk_F0 & 0xF00) == 0x100) {
        status = 0xA02D;
        pDriveInfo->unk_102 |= 1;
    }

    return status;
}

void FS_ReadFATSetMemSize(SDDriveInfo* pDriveInfo, SDDriveInfo* param2) {
    DrvCtl* temp_r31 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo->unk_F0 == 2 && param2->unk_F0 == 2) {
        temp_r31->unk_259D4 = 0;
        return;
    }

    if (pDriveInfo->unk_F0 == 2) {
        temp_r31->unk_259D4 = temp_r31->unk_5F0 - pDriveInfo->unk_2E * pDriveInfo->unk_1C;
        return;
    }

    if (param2->unk_F0 == 2) {
        temp_r31->unk_259D4 = temp_r31->unk_5F0 - param2->unk_2E * param2->unk_1C;
        return;
    }

    temp_r31->unk_259D4 = temp_r31->unk_5F0;
}

u16 FS_ReadFATSetFAT(SDDriveInfo* pDriveInfo) {
    DrvCtl* temp_r30;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 status;
    void* var_r28;

    temp_r30 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo->unk_04 == 1) {
        temp_r30->unk_209F8 = PTR_UNK(temp_r30, pDriveInfo->unk_BA * pDriveInfo->unk_1C);
        pDriveInfo->unk_E8 = temp_r30->unk_209F8;
        var_r28 = temp_r30->unk_209F8;
    } else {
        temp_r30->unk_209FC = PTR_UNK(temp_r30, pDriveInfo->unk_BA * pDriveInfo->unk_1C);
        pDriveInfo->unk_E8 = temp_r30->unk_209FC;
        var_r28 = temp_r30->unk_209FC;
    }

    pDriveInfo->unk_B8 = 1;
    status = FS_read_sub(var_r28, pDriveInfo->unk_2E, pDriveInfo->unk_58, 0, pDriveInfo->unk_04, pDriveInfo->nChan);

    if (status != 0) {
        pDriveInfo->unk_B8 = 2;
        status = FS_read_sub(var_r28, pDriveInfo->unk_2E, pDriveInfo->unk_5C, 0, pDriveInfo->unk_04, pDriveInfo->nChan);

        if (status != 0) {
            pDriveInfo->unk_102 |= 1;
            return status;
        }
    }

    pDriveInfo->unk_BE = 2;

    if (pDriveInfo->unk_1E != 0) {
        pDriveInfo->unk_BC = ((pDriveInfo->unk_68 - pDriveInfo->unk_64) / pDriveInfo->unk_1E) + 2;
    } else {
        pDriveInfo->unk_102 |= 1;
        status = 0xA01A;
    }

    return status;
}

u16 FS_ChkFDC(SDDriveInfo* pDriveInfo, FSDescriptor* pFDC, u16 param3) {
    u16 status;

    if (param3 & 1) {
        status = FS_ChkFDCfatal(pDriveInfo, pFDC);
        if (status != 0) {
            return status;
        }
    }

    return 0;
}

u16 FS_ChkFDCfatal(SDDriveInfo* pDriveInfo, FSDescriptor* pFDC) {
    FSDescriptor* var_r28;
    DrvCtl* pDrvCtl;
    u8* var_r30;
    u16 temp_r27;

    (void)var_r30;

    var_r28 = pFDC;
    pDrvCtl = &FS_drv_ctl[pDriveInfo->nChan];

    if (var_r28 == NULL) {
        pFDC = (FSDescriptor*)pDrvCtl->unk_20BA4;
        var_r28 = (FSDescriptor*)pFDC;
    }

    if (LOAD_LE_u16(var_r28->bytes_per_sector.data_u16) != 0x200) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    if (LOAD_LE_u16(pFDC->bytes_per_sector.data_u16) != LOAD_LE_u16(var_r28->bytes_per_sector.data_u16)) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    var_r30 = (u8*)((u32)var_r28 + offsetof(FSDescriptor, sectors_per_cluster));
    if ((*var_r30 != 1) && (*var_r30 != 2) && (*var_r30 != 4) && (*var_r30 != 8) && (*var_r30 != 0x10) &&
        (*var_r30 != 0x20) && (*var_r30 != 0x40)) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    if (var_r28->fat_count != 2) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    if (LOAD_LE_u16(var_r28->root_dir_entries.data_u16) != 0x200) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    temp_r27 = LOAD_LE_u16(var_r28->total_sectors.data_u16);

    if (var_r28->extended_boot_sig != FDC_ATTR_EXTENDED_BOOT) {
        if (temp_r27 == 0) {
            pDriveInfo->unk_102 |= 1;
            return 0xA01A;
        }
    } else {
        if (LOAD_LE_u32(var_r28->total_sectors_32.data_u32) == 0 && temp_r27 == 0) {
            pDriveInfo->unk_102 |= 1;
            return 0xA01A;
        }
    }

    if (LOAD_LE_u16(var_r28->sectors_per_fat.data_u16) == 0) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    if (FS_strncmp(var_r28->fs_type, "FAT32   ", sizeof(var_r28->fs_type)) == 0) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    var_r30 = (u8*)((u32)pFDC + offsetof(FSDescriptor, fs_type));
    if (FS_strncmp((char*)var_r30, "FAT32   ", sizeof(var_r28->fs_type)) == 0) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    return 0;
}

u16 FS_ChkMnt(SDDriveInfo* pDriveInfo) {
    int pad;
    u32 sp14;
    u32 sp10;
    s32 spC;
    u16 status;

    (void)status;
    (void)pad;
    (void)pad;

    sp14 = 0;
    sp10 = 0;
    spC = 0;

    if (pDriveInfo->unk_100 != 1) {
        return FS_ChkMntOther(pDriveInfo);
    }

    status = FS_csd_to_size(&sp14, &spC, 1, pDriveInfo->unk_100, pDriveInfo->nChan);
    if (status != 0) {
        pDriveInfo->unk_102 |= 1;
        return status;
    }

    status = FS_csd_to_size(&sp10, &spC, 2, pDriveInfo->unk_100, pDriveInfo->nChan);
    if (status != 0) {
        pDriveInfo->unk_102 |= 1;
        return status;
    }

    !pad;
    status = FS_ChkMntOther(pDriveInfo);
    return status;
}

u16 FS_ChkMntOther(SDDriveInfo* pDriveInfo) {
    u32 var_r31;

    if ((pDriveInfo->unk_2A != 0 && pDriveInfo->unk_2A > 0x400000u) ||
        (pDriveInfo->unk_34 != 0 && pDriveInfo->unk_34 > 0x400000u)) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    } else if ((pDriveInfo->unk_3C != 2) && (pDriveInfo->unk_3C != 1)) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    } else if (pDriveInfo->unk_2E == 0) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    if (pDriveInfo->unk_3C == 1) {
        var_r31 = (u32)((pDriveInfo->unk_BC << 1) + 0x1FF) / 0x200;
    } else {
        var_r31 = (u32)(((u32)(pDriveInfo->unk_BC * 3 + 1) >> 1) + 0x1FF) / 0x200;
    }

    if (var_r31 > (pDriveInfo->unk_2E)) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    if (pDriveInfo->unk_18 < pDriveInfo->unk_1C) {}

    if (pDriveInfo->unk_FC < pDriveInfo->unk_68) {
        pDriveInfo->unk_102 |= 1;
        return 0xA01A;
    }

    return 0;
}
