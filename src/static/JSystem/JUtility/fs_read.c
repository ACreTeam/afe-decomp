#include "JSystem/JUtility/fs_read.h"

#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Read(SDFileInfo* pFileInfo, const void* data, s32 length, int param4, UnknownStruct1* param5) {
    DrvCtl* pDrvCtl;
    u16 status;
    u16 status2;

    status2 = 0;
    status = 0;

    if (param5 == NULL) {
        return 0xA00C;
    }

    param5->unk_00 = 0x1000;
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

    status2 = FS_Read_SubPrc(pFileInfo, data, length, param4, param5);

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

u16 FS_Read_SubPrc(SDFileInfo* pFileInfo, const void* data, u32 length, u32 param4, UnknownStruct1* param5) {
    u32 sp2C;
    u16 sp2A;
    u16 sp28;
    u16 sp26;
    u16 sp24;
    UnknownStruct1 sp1C;
    u16 temp_r3;
    void* var_r27;
    u16 var_r26;
    u16 temp_r25;
    u16 status;
    UnknownStruct1* pSp1C;

    (void)temp_r3;

    pSp1C = &sp1C;
    var_r27 = (void*)data;

    if (param4 != 0) {
        return 0xA021;
    }

    if (pFileInfo->pDriveInfo == NULL) {
        return 0xA008;
    }

    if (pFileInfo->unk_00 >= GET_FILE_INFO_COUNT(&FS_drv_ctl[pFileInfo->pDriveInfo->nChan], pFileInfo->pDriveInfo)) {
        return 0xA008;
    }

    if (pFileInfo->unk_2C & 2) {
        return 0xA027;
    }

    status = FS_GetChkAccessSize(pFileInfo, length, &sp2C);

    if (status == 0xA015 || status == 0xA028) {
        return status;
    } else if (status == 0xA014) {
        param5->unk_02 = status;
    }

    temp_r25 = FS_GetAccessClusterCount(pFileInfo, sp2C);
    var_r26 = 0;

    while (var_r26 < temp_r25) {
        status = FS_GetDoingCluster2(pFileInfo, &sp2A, &sp28, &sp26, &sp2C, &sp24);
        if (status != 0) {
            return status;
        }

        pSp1C->unk_00 = 0x1000;
        pSp1C->unk_04 = 0;
        pSp1C->unk_02 = 0;

        status = FS_ReadIODoing(pFileInfo, var_r27, sp2A, sp28, sp26, pSp1C, sp24);
        param5->unk_04 += pSp1C->unk_04;
        var_r27 = (void*)((u8*)var_r27 + pSp1C->unk_04);
        sp2C -= pSp1C->unk_04;
        temp_r3 = FS_GetNextCluster(pFileInfo, sp26);
        pFileInfo->unk_28 += pSp1C->unk_04;

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

u16 FS_GetChkAccessSize(SDFileInfo* pFileInfo, u32 param2, u32* param3) {
    if (pFileInfo->unk_24 < pFileInfo->unk_28) {
        *param3 = 0;
        return 0xA028;
    }

    if (pFileInfo->unk_24 > pFileInfo->unk_28 + param2) {
        *param3 = param2;
        return 0;
    }

    if (pFileInfo->unk_24 == pFileInfo->unk_28 + param2) {
        *param3 = param2;
        return 0xA014;
    }

    if (pFileInfo->unk_24 == pFileInfo->unk_28) {
        *param3 = 0;
        return 0xA015;
    }

    *param3 = pFileInfo->unk_24 - pFileInfo->unk_28;
    return 0xA014;
}

static inline u16 UnknownInline1(u32 param1, u32 param2, u32 param3) {
    u16 var_r30 = param1 / param3;

    if (param1 % param3) {
        var_r30++;
    }

    return var_r30;
}

u16 FS_GetAccessClusterCount(SDFileInfo* pFileInfo, u32 param2) {
    u32 temp_r31 = pFileInfo->pDriveInfo->unk_F6 * pFileInfo->pDriveInfo->unk_1C;
    return UnknownInline1(param2 + pFileInfo->unk_28 % temp_r31, param2, temp_r31);
}

u16 FS_GetDoingCluster2(SDFileInfo* pFileInfo, u16* param2, u16* param3, u16* param4, u32* param5, u16* param6) {
    u32 temp_r28;
    u16 temp2;
    u16 temp;
    SDDriveInfo* pDriveInfo;

    temp_r28 = pFileInfo->pDriveInfo->unk_F6 * pFileInfo->pDriveInfo->unk_1C;

    pDriveInfo = pFileInfo->pDriveInfo;

    *param3 = pFileInfo->unk_28 % temp_r28;
    *param4 = temp_r28 - *param3;

    if (*param5 < *param4) {
        *param4 = *param5;
    }

    *param2 = pFileInfo->unk_2E;

    if (*param2 == 1 || *param2 == 0xFFFF || *param2 == 0 || *param2 >= 0xFFF7 ||
        (*param2 > (pDriveInfo->unk_BC - 1))) {
        return 0xA029;
    }

    if ((pDriveInfo->unk_1E % pDriveInfo->unk_F6) != 0) {
        return 0xA02D;
    }

    temp = (pDriveInfo->unk_1E / pDriveInfo->unk_F6);
    temp2 = (pFileInfo->unk_28 / temp_r28);
    *param6 = temp2 % temp;
    return 0;
}

u16 FS_GetNextCluster(SDFileInfo* pFileInfo, u16 param2) {
    u16 status;
    u16 var_r29;
    u16 var_r28;
    u32 temp_r27;
    u16 var_r26;
    SDDriveInfo* temp_r25;

    status = 0;
    var_r29 = pFileInfo->unk_2E;
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

u16 FS_ReadIODoing(SDFileInfo* pFileInfo, void* param2, u16 param3, u16 param4, u16 param5, UnknownStruct1* param6,
                   u16 param7) {
    DrvCtl* temp_r24;
    SDDriveInfo* temp_r31;
    u32 temp_r26;
    u16 var_r22;
    u16 status;
    u32 var_r20;
    u32 temp_r19;
    u32 someValue;

    status = 0;
    temp_r19 = pFileInfo->pDriveInfo->unk_F6 * pFileInfo->pDriveInfo->unk_1C;
    temp_r24 = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];
    someValue = (u32)param2;
    temp_r31 = pFileInfo->pDriveInfo;

    if (param5 == 0) {
        return status;
    }

    if (param5 > (temp_r31->unk_F6 << 9)) {
        return 0xA00C;
    }

    var_r20 = FS_cluster_to_sector(temp_r31, param3);
    temp_r26 = var_r20 + (temp_r31->unk_F6 * param7);

    if (param4 == 0 && temp_r19 == (param4 + param5)) {
        if (someValue & 1) {
            status = FS_read_sub(NULL, temp_r31->unk_F6, temp_r26, param6, temp_r31->unk_04, temp_r31->nChan);
            FS_strncpy(param2, (char*)temp_r24->ctrl_p.unk_20BA4, param5);
        } else {
            status = FS_read_sub(param2, temp_r31->unk_F6, temp_r26, param6, temp_r31->unk_04, temp_r31->nChan);
        }
    } else if (param4 % 512 == 0 && param5 % 512 == 0) {
        if (someValue & 1) {
            status = FS_read_sub(NULL, (param5 / 512) & 0xFFFF, temp_r26 + (param4 / 512), param6, temp_r31->unk_04,
                                 temp_r31->nChan);
            FS_strncpy(param2, (char*)temp_r24->ctrl_p.unk_20BA4, param5);
        } else {
            status = FS_read_sub(param2, (param5 / 512) & 0xFFFF, temp_r26 + (param4 / 512), param6, temp_r31->unk_04,
                                 temp_r31->nChan);
        }
    } else {
        var_r22 = (param4 % 512 + param5) / 512;

        if ((param4 % 512 + param5) % 512 != 0) {
            var_r22++;
        }

        status = FS_read_sub(0, var_r22, temp_r26 + (param4 / 512), param6, temp_r31->unk_04, temp_r31->nChan);
        if (status != 0) {
            param6->unk_04 = 0;
        } else {
            FS_strncpy(param2, (char*)&temp_r24->ctrl_p.unk_20BA4[param4 % 512], param5);
            param6->unk_04 = param5;
        }
    }

    return status;
}

u16 FS_FatTable_PageChange(SDDriveInfo* pDriveInfo) {
    s32 var_r29;
    s32 var_r28;
    u16 status;

    status = 0;

    if (pDriveInfo->unk_F0 == 1) {
        return status;
    }

    if (pDriveInfo->unk_B8 == 1) {
        var_r28 = pDriveInfo->unk_58;
        var_r29 = pDriveInfo->unk_5C;
    } else {
        var_r28 = pDriveInfo->unk_5C;
        var_r29 = pDriveInfo->unk_58;
    }

    status = FS_read_sub(pDriveInfo->unk_E8, pDriveInfo->unk_2E, var_r29, NULL, pDriveInfo->unk_04, pDriveInfo->nChan);
    if (status != 0) {
        return FS_read_sub(pDriveInfo->unk_E8, pDriveInfo->unk_2E, var_r28, NULL, pDriveInfo->unk_04,
                           pDriveInfo->nChan);
    }

    if (pDriveInfo->unk_B8 == 1) {
        pDriveInfo->unk_B8 = 2;
    } else {
        pDriveInfo->unk_B8 = 1;
    }

    return status;
}
