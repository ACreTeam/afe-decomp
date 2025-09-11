#include "JSystem/JUtility/fs_umount.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Umount(SDDriveInfo* pDriveInfo) {
    u16 status;
    DrvCtl* pDrvCtl;

    if (pDriveInfo == NULL) {
        return 0xA00C;
    }

    if (pDriveInfo->unk_04 != 1) {
        return 0xA016;
    }

    pDrvCtl = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo != pDrvCtl->unk_08) {
        return 0xA00C;
    }

    status = FS_Umount_sub(pDriveInfo);
    return status;
}

u16 FS_Umount_sub(SDDriveInfo* pDriveInfo) {
    DrvCtl* temp_r29;
    u16 status;
    u16 var_r27;
    u16 var_r26;
    u16 var_r25;
    u16 var_r30;
    int pad;
    u16 spC[0x102];

    temp_r29 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo->unk_06 == 1) {
        return 0xA003;
    }

    if (pDriveInfo->unk_F4 != 0) {
        return 0xA009;
    }

    status = FS_Flush(pDriveInfo);
    var_r30 = 0;
    var_r26 = 0;

    while (var_r30 < temp_r29->unk_5F0 / 512) {
        if (temp_r29->ctrl_p.unk_4BB8.unk_408[var_r30] == pDriveInfo->unk_04) {
            temp_r29->ctrl_p.unk_4BB8.unk_60C[var_r30] = 0;
            temp_r29->ctrl_p.unk_4BB8.unk_810[var_r30] = 0;
            temp_r29->ctrl_p.unk_4BB8.unk_A14[var_r30] = 0;
            temp_r29->ctrl_p.unk_4BB8.unk_C18[var_r30] = 0;
            temp_r29->ctrl_p.unk_4BB8.unk_408[var_r30] = 3;
            temp_r29->ctrl_p.unk_4BB8.unk_000[var_r30] = 0;
            var_r26++;
        }

        var_r30++;
    }

    if (var_r26 != 0) {
        var_r30 = 0;

        while (var_r30 < temp_r29->unk_5F0 / 512 + 1) {
            spC[var_r30] = 0xFFFF;
            var_r30++;
        }

        var_r30 = 0;
        var_r25 = 0;

        while (var_r30 < temp_r29->unk_5F0 / 512) {
            if (temp_r29->ctrl_p.unk_4BB8.unk_A14[var_r30] != 0) {
                spC[temp_r29->ctrl_p.unk_4BB8.unk_A14[var_r30]] = var_r30;
                var_r25++;
            }

            var_r30++;
        }

        var_r30 = 0;
        var_r27 = 1;

        while (var_r30 < temp_r29->unk_5F0 / 512 + 1) {
            if (spC[var_r30] != 0xFFFF) {
                temp_r29->ctrl_p.unk_4BB8.unk_A14[spC[var_r30]] = var_r27;
                var_r27++;
            }

            var_r30++;
        }

        if (var_r27 - 1 != var_r25 && status == 0) {
            status = 0xA02D;
        }
    }

    pDriveInfo->unk_06 = 1;
    pDriveInfo->unk_08 = 0;
    pDriveInfo->unk_0C = 0;
    pDriveInfo->unk_0D = 0;
    pDriveInfo->unk_0E = 0;
    pDriveInfo->unk_10 = 0;
    pDriveInfo->unk_11 = 0;
    pDriveInfo->unk_12 = 0;
    pDriveInfo->unk_14 = 0;
    pDriveInfo->unk_18 = 0;
    pDriveInfo->unk_1C = 0;
    pDriveInfo->unk_1E = 0;
    pDriveInfo->unk_20 = 0;
    pDriveInfo->unk_22 = 0;
    pDriveInfo->unk_24 = 0;
    pDriveInfo->unk_26 = 0;
    pDriveInfo->unk_28 = 0;
    pDriveInfo->unk_2A = 0;
    pDriveInfo->unk_2C = 0;
    pDriveInfo->unk_2E = 0;
    pDriveInfo->unk_30 = 0;
    pDriveInfo->unk_34 = 0;
    pDriveInfo->unk_38 = 0;
    pDriveInfo->unk_3C = 0;
    FS_memset(pDriveInfo->unk_3E, 0, sizeof(pDriveInfo->unk_3E));
    FS_memset(pDriveInfo->unk_4A, 0, sizeof(pDriveInfo->unk_4A));
    pDriveInfo->unk_53 = 0;
    pDriveInfo->unk_54 = 0;
    pDriveInfo->unk_58 = 0;
    pDriveInfo->unk_5C = 0;
    pDriveInfo->nSector = 0;
    pDriveInfo->unk_64 = 0;
    pDriveInfo->unk_68 = 0;
    pDriveInfo->unk_6C = 0;
    pDriveInfo->unk_70 = 0;
    pDriveInfo->unk_72 = 0;
    pDriveInfo->unk_74 = 0;
    FS_memset(pDriveInfo->unk_76, 0, sizeof(pDriveInfo->unk_76));
    FS_strncpy(pDriveInfo->unk_76, "\\", 1);
    pDriveInfo->unk_B8 = 0;
    pDriveInfo->unk_BA = 0;
    pDriveInfo->unk_BC = 0;
    pDriveInfo->unk_BE = 0;
    pDriveInfo->unk_C0 = 0;
    FS_memset(pDriveInfo->unk_C2, 0, sizeof(pDriveInfo->unk_C2));
    pDriveInfo->unk_E2 = 0;
    pDriveInfo->unk_E4 = 0;
    pDriveInfo->unk_E8 = NULL;
    pDriveInfo->unk_F0 = 0;
    pDriveInfo->unk_F4 = 0;
    pDriveInfo->unk_F6 = 0;
    pDriveInfo->unk_F8 = 0;
    pDriveInfo->unk_FA = 0;
    pDriveInfo->unk_FC = 0;
    pDriveInfo->unk_100 = 0;
    pDriveInfo->unk_102 = 0;

    return status;
}
