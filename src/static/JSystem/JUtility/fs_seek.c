#include "JSystem/JUtility/fs_seek.h"

#include "JSystem/JUtility/fs_read.h"
#include "JSystem/JUtility/fs_subd.h"

extern u16 FS_Seek_sub(SDFileInfo* pFileInfo, u32 param2, u16 param3);

u16 FS_Seek(SDFileInfo* pFileInfo, u32 param2, u16 param3) {
    u16 status;
    DrvCtl* ptr;

    if (pFileInfo == NULL) {
        return 0xA00C;
    }

    if (pFileInfo->pDriveInfo->unk_04 != 1) {
        return 0xA016;
    }

    ptr = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];

    if (pFileInfo->pDriveInfo != &ptr->unk_08[0]) {
        return 0xA00C;
    }

    status = FS_Seek_sub(pFileInfo, param2, param3);
    return status;
}

u16 FS_Seek_sub(SDFileInfo* pFileInfo, u32 param2, u16 param3) {
    u16 var_r30;
    s32 var_r29;
    u16 status;
    u32 temp_r27;
    u32 var_r26;
    u32 var_r25;
    s32 var_r24;
    SDDriveInfo* temp_r21;

    status = 0;
    temp_r27 = pFileInfo->pDriveInfo->unk_1E * pFileInfo->pDriveInfo->unk_1C;
    temp_r21 = pFileInfo->pDriveInfo;

    if (pFileInfo == NULL) {
        return 0xA00C;
    }

    if (pFileInfo->pDriveInfo->unk_06 == 1) {
        return 0xA003;
    }

    if (pFileInfo->unk_00 == 0xFFFF) {
        return 0xA008;
    }

    switch (param3) {
        case 1:
            var_r29 = param2;
            break;
        case 2:
            var_r29 = pFileInfo->unk_28 + param2;
            break;
        case 4:
            var_r29 = pFileInfo->unk_24 + param2;
            break;
        case 3:
        default:
            return 0xA00C;
    }

    if (var_r29 < 0) {
        return 0xA00C;
    }

    var_r24 = var_r29;
    if (var_r24 > pFileInfo->unk_24) {
        return 0xA00C;
    }

    if (param3 == 2 && (var_r24 > pFileInfo->unk_28)) {
        var_r30 = pFileInfo->unk_2E;
        var_r26 = (param2 + (pFileInfo->unk_28 % temp_r27)) / temp_r27;
    } else if (param3 == 4 && var_r24 > pFileInfo->unk_28) {
        var_r30 = pFileInfo->unk_2E;
        var_r26 = (var_r24 / temp_r27) - (pFileInfo->unk_28 / temp_r27);
    } else {
        var_r30 = pFileInfo->unk_22;
        var_r26 = var_r24 / temp_r27;
    }

    var_r25 = 0;

    while (var_r25 < var_r26) {
        var_r30 = FS_get_next_cluster(pFileInfo->pDriveInfo, var_r30);

        if (var_r30 == 0xFFF7 || var_r30 == 0xFFFD || var_r30 == 0xFFFE) {
            status = 0xA029;
            var_r30 = 1;
        } else {
            var_r25++;
            continue;
        }

        break;
    }

    if ((var_r30 == 1) && (temp_r21->unk_F0 == 2)) {
        status = FS_FatTable_PageChange(pFileInfo->pDriveInfo);
        if (status != 0) {
            return status;
        }

        var_r30 = pFileInfo->unk_22;
        var_r26 = (var_r24 / temp_r27);
        var_r25 = 0;

        while (var_r25 < var_r26) {
            var_r30 = FS_get_next_cluster(pFileInfo->pDriveInfo, var_r30);

            if (var_r30 == 0xFFF7 || var_r30 == 0xFFFD || var_r30 == 0xFFFE) {
                status = 0xA029;
                var_r30 = 1;
            } else {
                var_r25++;
                continue;
            }

            break;
        }
    }

    pFileInfo->unk_2E = var_r30;
    pFileInfo->unk_28 = var_r24;
    return status;
}
