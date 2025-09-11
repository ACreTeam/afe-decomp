#include "JSystem/JUtility/fs_sync.h"

#include "JSystem/JUtility/fs_subd.h"

u16 FS_Sync_sub(SDDriveInfo* pDriveInfo) {
    SDFileInfo* pFileInfo;
    DrvCtl* temp_r29;
    u16 status;
    u16 var_r31;

    temp_r29 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo->unk_04 == 1) {
        for (var_r31 = 0; var_r31 < 5; var_r31++) {
            if (temp_r29->unk_210[var_r31].unk_00 == var_r31) {
                pFileInfo = &temp_r29->unk_210[var_r31];

                status = FS_Sync_DirEntry(pFileInfo);
                if (status != 0) {
                    return status;
                }
            }
        }
    } else if (pDriveInfo->unk_04 == 2) {
        for (var_r31 = 0; var_r31 < 3; var_r31++) {
            if (temp_r29->unk_47C[var_r31].unk_00 == var_r31) {
                pFileInfo = &temp_r29->unk_47C[var_r31];

                status = FS_Sync_DirEntry(pFileInfo);
                if (status != 0) {
                    return status;
                }
            }
        }
    }

    status = FS_fat_sync(pDriveInfo);
    if (status != 0) {
        return status;
    }

    return status;
}

u16 FS_Sync_DirEntry(SDFileInfo* pFileInfo) {
    FSDirEntry* temp_r29;
    DrvCtl* temp_r28;
    u16 status;

    (void)status;
    (void)status;

    status = 0;
    temp_r28 = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];

    if (pFileInfo->unk_00 >= 5 || pFileInfo->pDriveInfo == NULL) {
        return 0xA02D;
    }

    if ((pFileInfo->unk_13 & 1) || (pFileInfo->unk_2C & 1)) {
        return status;
    }

    if (pFileInfo->unk_02 != 1) {
        return status;
    }

    status = FS_read_sub(0, 1, pFileInfo->unk_34, 0, pFileInfo->pDriveInfo->unk_04, pFileInfo->pDriveInfo->nChan);
    if (status != 0) {
        return status;
    }

    temp_r29 = PTR_ROOT_DIR_ENTRY(temp_r28, pFileInfo->unk_38);
    FS_strncpy(temp_r29->DIR_Name, pFileInfo->unk_08, sizeof(temp_r29->DIR_Name));
    temp_r29->DIR_Attr = pFileInfo->unk_13;
    temp_r29->DIR_FileSize.data_u8[0] = (pFileInfo->unk_24 >> 0);
    temp_r29->DIR_FileSize.data_u8[1] = (pFileInfo->unk_24 >> 8);
    temp_r29->DIR_FileSize.data_u8[2] = (pFileInfo->unk_24 >> 16);
    temp_r29->DIR_FileSize.data_u8[3] = (pFileInfo->unk_24 >> 24);
    temp_r29->DIR_FstClusLO.data_u8[0] = pFileInfo->unk_22;
    temp_r29->DIR_FstClusLO.data_u8[1] = (pFileInfo->unk_22 >> 8);

    // sets DIR_NTRes, DIR_CrtTimeTenth, DIR_CrtTime, DIR_CrtDate, DIR_LstAccDate and DIR_FstClusHI
    FS_strncpy((char*)&temp_r29->DIR_NTRes, pFileInfo->unk_14,
                offsetof(FSDirEntry, DIR_WrtTime) - offsetof(FSDirEntry, DIR_NTRes));

    FS_set_now_date(temp_r29, NULL);

    status = FS_write_sub(0, 1, pFileInfo->unk_34, 0, pFileInfo->pDriveInfo->unk_04, 0, pFileInfo->pDriveInfo->nChan);
    if (status != 0) {
        return status;
    }

    pFileInfo->unk_02 = 0;
    return status;
}
