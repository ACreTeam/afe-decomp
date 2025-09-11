#include "JSystem/JUtility/fs_write.h"

#include "JSystem/JUtility/fs_read.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Write(SDFileInfo* pFileInfo, const void* data, u32 length, int param4, UnknownStruct1* param5) {
    DrvCtl* pDrvCtl;
    u16 status;
    u16 status2;

    status2 = 0;
    status = 0;

    if (param5 == NULL) {
        return 0xA00C;
    }

    param5->unk_00 = 0x2000;
    param5->unk_04 = 0;
    param5->unk_02 = status2;

    if (pFileInfo == NULL || data == NULL) {
        return (param5->unk_02 = 0xA00C);
    } else if (pFileInfo->pDriveInfo->unk_04 != 1) {
        return (param5->unk_02 = 0xA016);
    } else {
        pDrvCtl = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];

        if (pFileInfo->pDriveInfo != pDrvCtl->unk_08) {
            return (param5->unk_02 = 0xA00C);
        }
    }

    if (length == 0) {
        return status2;
    }

    status2 = FS_Write_SubPrc(pFileInfo, data, length, param4, param5);
    pFileInfo->unk_02 = 1;

    if (param5->unk_02 == 0) {
        if (status2 != 0) {
            param5->unk_02 = status2;
        } else {
            param5->unk_02 = status;
        }
    }

    if (status2 != 0) {
        return status2;
    }

    return status;
}

u16 FS_Write_SubPrc(SDFileInfo* pFileInfo, const void* data, u32 length, u32 param4, UnknownStruct1* param5) {
    u32 sp30;
    u16 sp2E;
    u16 sp2C;
    u16 sp2A;
    u16 sp28;
    UnknownStruct1 sp20;
    DrvCtl* sp1C;
    u16 var_r26;
    u16 temp_r25;
    u16 temp_r3;
    void* var_r27;
    u16 status;
    UnknownStruct1* pSp20;

    pSp20 = &sp20;
    sp1C = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];
    var_r27 = (void*)data;

    if (param4 != 0) {
        return 0xA021;
    }

    if (pFileInfo->pDriveInfo == NULL) {
        return 0xA008;
    }

    if (pFileInfo->unk_00 >= GET_FILE_INFO_COUNT(sp1C, pFileInfo->pDriveInfo)) {
        return 0xA008;
    }

    status = FS_ChkWriteAccessSize(pFileInfo, length);
    if (status != 0) {
        return status;
    }

    if ((pFileInfo->unk_2C & 1) || (pFileInfo->unk_13 & 1)) {
        return 0xA027;
    }

    sp30 = length;
    temp_r25 = FS_GetAccessClusterCount(pFileInfo, sp30);
    var_r26 = 0;

    while (var_r26 < temp_r25) {
        status = FS_GetWriteDoingCluster2(pFileInfo, &sp2E, &sp2C, &sp2A, &sp30, &sp28);
        if (status != 0) {
            return status;
        }

        pSp20->unk_00 = 0x2000;
        pSp20->unk_04 = 0;
        pSp20->unk_02 = 0;

        status = FS_WriteIODoing(pFileInfo, var_r27, sp2E, sp2C, sp2A, pSp20, sp28);
        if (status != 0 && pFileInfo->unk_30 != 0) {
            FS_release_space(pFileInfo->pDriveInfo, pFileInfo->unk_22, pFileInfo->unk_30);
            pFileInfo->unk_30 = 0;
        }

        param5->unk_04 += pSp20->unk_04;
        var_r27 = (void*)((u8*)var_r27 + pSp20->unk_04);
        sp30 -= pSp20->unk_04;

        temp_r3 = FS_GetWriteNextCluster(pFileInfo, sp2A);
        if (temp_r3 != 0 && pFileInfo->unk_30 != 0) {
            FS_release_space(pFileInfo->pDriveInfo, pFileInfo->unk_22, pFileInfo->unk_30);
            pFileInfo->unk_30 = 0;
        }

        pFileInfo->unk_28 += pSp20->unk_04;
        if (pFileInfo->unk_24 < pFileInfo->unk_28) {
            pFileInfo->unk_24 = pFileInfo->unk_28;
        }

        if (status != 0) {
            return status;
        }

        if (temp_r3 != 0) {
            return temp_r3;
        }

        var_r26++;
    }

    return status;
}

u16 FS_GetWriteDoingCluster2(SDFileInfo* pFileInfo, u16* param2, u16* param3, u16* param4, u32* param5, u16* param6) {
    DrvCtl* sp20;
    u16 status;
    u32 temp_r28;
    u16 temp2;
    u16 temp;

    status = 0;

    temp_r28 = pFileInfo->pDriveInfo->unk_F6 * pFileInfo->pDriveInfo->unk_1C;

    sp20 = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];
    pFileInfo->unk_30 = 0;

    *param3 = pFileInfo->unk_28 % temp_r28;
    *param4 = temp_r28 - *param3;

    if (*param5 < *param4) {
        *param4 = *param5;
    }

    *param2 = pFileInfo->unk_2E;

    if (*param2 == 1) {
        return 0xA029;
    } else if (*param2 == 0xFFFF) {
        status = FS_get_space(pFileInfo->pDriveInfo, pFileInfo->unk_22, param2);
        if (status != 0) {
            return status;
        }

        pFileInfo->unk_2E = pFileInfo->unk_30 = *param2;
    } else if (*param2 == 0) {
        if (pFileInfo->unk_22 == 0) {
            status = FS_get_space(pFileInfo->pDriveInfo, 0U, param2);
            if (status != 0) {
                return status;
            }

            pFileInfo->unk_22 = pFileInfo->unk_2E = pFileInfo->unk_30 = *param2;
        } else {
            return 0xA02D;
        }
    } else if (*param2 > (pFileInfo->pDriveInfo->unk_BC - 1) || *param2 >= 0xFFF7) {
        return 0xA029;
    }

    if ((pFileInfo->pDriveInfo->unk_1E % pFileInfo->pDriveInfo->unk_F6) != 0) {
        return 0xA02D;
    }

    temp = (pFileInfo->pDriveInfo->unk_1E / pFileInfo->pDriveInfo->unk_F6);
    temp2 = (pFileInfo->unk_28 / temp_r28);
    *param6 = temp2 % temp;
    return status;
}

u16 FS_GetWriteNextCluster(SDFileInfo* pFileInfo, u16 param2) {
    u16 status;
    u16 var_r29;
    u16 var_r28;
    u32 temp_r27;
    u16 var_r26;
    SDDriveInfo* temp_r25;

    status = 0;
    var_r29 = 0;
    var_r28 = TRUE;
    var_r26 = TRUE;
    temp_r25 = pFileInfo->pDriveInfo;
    temp_r27 = pFileInfo->pDriveInfo->unk_1E * pFileInfo->pDriveInfo->unk_1C;

    if ((pFileInfo->unk_28 + param2) / temp_r27 == pFileInfo->unk_28 / temp_r27) {
        return status;
    }

    while (var_r26) {
        var_r29 = FS_get_next_cluster(pFileInfo->pDriveInfo, pFileInfo->unk_2E);

        if (var_r29 == 0xFFF7 || var_r29 == 0xFFFD || var_r29 == 0xFFFE) {
            if (var_r28 == TRUE && temp_r25->unk_F0 == 2) {
                status = FS_FatTable_PageChange(pFileInfo->pDriveInfo);
                if (status != 0) {
                    return status;
                }

                var_r28 = FALSE;
                continue;
            }

            status = 0xA029;
            var_r29 = 1;
        } else if (var_r28 == FALSE) {
            status = FS_Flush(pFileInfo->pDriveInfo);
            if (status != 0) {
                return status;
            }

            pFileInfo->pDriveInfo->unk_B8 = 1;
        }

        break;
    }

    pFileInfo->unk_2E = var_r29;
    return status;
}

static inline u16 UnknownInline1(SDFileInfo* pFileInfo, u32 param2, u16 param4, u16 param5) {
    if (pFileInfo->unk_28 / param2 == pFileInfo->unk_24 / param2) {
        u16 param1 = pFileInfo->unk_24 % param2;

        (void)param1;

        if (param1 == 0) {
            return FALSE;
        } else if (((param4 + param5) / 512) <= (param1 / 512)) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else if (pFileInfo->unk_28 / param2 < pFileInfo->unk_24 / param2) {
        return TRUE;
    }

    return FALSE;
}

u16 FS_WriteIODoing(SDFileInfo* pFileInfo, void* param2, u16 param3, u16 param4, u16 param5, UnknownStruct1* param6,
                    u16 param7) {
    SDDriveInfo* temp_r30;
    u16 var_r28;
    s32 temp_r26;
    u16 var_r25;
    u32 temp_r24;
    u16 r20;
    DrvCtl* temp_r19;
    u32 someValue;
    u16 var_r18;
    u32 sp20;

    (void)r20;
    (void)r20;
    (void)r20;
    (void)var_r25;
    (void)var_r18;

    var_r28 = 0;
    temp_r24 = pFileInfo->pDriveInfo->unk_F6 * pFileInfo->pDriveInfo->unk_1C;
    someValue = (u32)param2;
    temp_r19 = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];
    temp_r30 = pFileInfo->pDriveInfo;

    if (param5 == 0) {
        return var_r28;
    }

    if (param5 > (temp_r30->unk_F6 * 0x200)) {
        return 0xA00C;
    }

    sp20 = FS_cluster_to_sector(temp_r30, param3);
    temp_r26 = sp20 + (temp_r30->unk_F6 * param7);

    if (param4 == 0 && temp_r24 == (param4 + param5)) {
        if (someValue & 1) {
            FS_strncpy((char*)temp_r19->ctrl_p.unk_20BA4, (char*)param2, param5);
            var_r28 = FS_write_sub(NULL, temp_r30->unk_F6, temp_r26, param6, temp_r30->unk_04, 1,
                                   pFileInfo->pDriveInfo->nChan);
        } else {
            var_r28 = FS_write_sub(param2, temp_r30->unk_F6, temp_r26, param6, temp_r30->unk_04, 1,
                                   pFileInfo->pDriveInfo->nChan);
        }
    } else if (param4 % 512 == 0 && param5 % 512 == 0) {
        if (someValue & 1) {
            FS_strncpy((char*)temp_r19->ctrl_p.unk_20BA4, (char*)param2, param5);
            var_r28 = FS_write_sub(NULL, (param5 >> 9U) & 0x7F, temp_r26 + ((param4 >> 9U) & 0x7F), param6,
                                   temp_r30->unk_04, 1, pFileInfo->pDriveInfo->nChan);
        } else {
            var_r28 = FS_write_sub(param2, (param5 >> 9U) & 0x7F, temp_r26 + ((param4 >> 9U) & 0x7F), param6,
                                   temp_r30->unk_04, 1, pFileInfo->pDriveInfo->nChan);
        }
    } else {
        if (UnknownInline1(pFileInfo, temp_r24, param4, param5) == FALSE) {
            if (param4 != 0) {
                var_r25 = ((param4 % 512) / 512);

                if ((param4 % 512) % 512 != 0) {
                    var_r25++;
                }

                var_r28 = FS_read_sub(0, var_r25, temp_r26 + (param4 / 512), 0, temp_r30->unk_04, temp_r30->nChan);
                if (var_r28 != 0) {
                    return var_r28;
                }
            } else {
                FS_memset(&temp_r19->ctrl_p.unk_20BA4[(((param4 + param5) / 512) << 9) & 0xFE00], 0, 0x200);
            }
        } else {
            var_r25 = ((param4 % 512) + param5) / 512;

            if (((param4 % 512) + param5) % 512 != 0) {
                var_r25++;
            }

            var_r28 = FS_read_sub(0, var_r25, temp_r26 + ((s32)param4 / 512), 0, temp_r30->unk_04, temp_r30->nChan);
            if (var_r28 != 0) {
                return var_r28;
            }
        }

        r20 = (param4 % 512);
        FS_strncpy((char*)&temp_r19->ctrl_p.unk_20BA4[r20], (char*)param2, param5);
        var_r18 = ((param4 % 512) + param5) / 512;

        if (((param4 % 512) + param5) % 512 != 0) {
            var_r18++;
        }

        var_r28 = FS_write_sub(NULL, var_r18, temp_r26 + (param4 / 512), param6, temp_r30->unk_04, 1, temp_r30->nChan);
        if (var_r28 != 0) {
            param6->unk_04 = 0;
        } else {
            param6->unk_04 = param5;
        }
    }

    pFileInfo->unk_13 |= 0x20;
    return var_r28;
}

u16 FS_ChkWriteAccessSize(SDFileInfo* pFileInfo, u32 length) {
    if (pFileInfo->unk_28 > pFileInfo->unk_24) {
        return 0xA00C;
    }

    if (pFileInfo->pDriveInfo->unk_2A != 0) {
        if (pFileInfo->pDriveInfo->unk_2A < (length / pFileInfo->pDriveInfo->unk_1C)) {
            return 0xA00C;
        }
    } else if (pFileInfo->pDriveInfo->unk_34 < (length / pFileInfo->pDriveInfo->unk_1C)) {
        return 0xA00C;
    }

    return 0;
}
