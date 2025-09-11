#include "JSystem/JUtility/fs_close.h"

#include "JSystem/JUtility/fs_form.h"
#include "JSystem/JUtility/fs_open.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Close(SDFileInfo* pFileInfo) {
    u16 status;
    DrvCtl* pDrvCtl;

    if (pFileInfo == NULL || pFileInfo->pDriveInfo == NULL) {
        return 0xA00C;
    }

    if (pFileInfo->pDriveInfo->unk_04 != 1) {
        return 0xA016;
    }

    pDrvCtl = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];

    if (pFileInfo->pDriveInfo != pDrvCtl->unk_08) {
        return 0xA00C;
    }

    status = FS_Close_sub(pFileInfo);
    return status;
}

u16 FS_Close_sub(SDFileInfo* pFileInfo) {
    DrvCtl* temp_r28;
    u16 status;
    FSDirEntry* temp_r29;

    status = 0;

    if (pFileInfo->pDriveInfo == NULL) {
        return 0xA008;
    }

    if (pFileInfo->pDriveInfo->unk_06 != 2) {
        return 0xA003;
    }

    if (pFileInfo->unk_00 >= GET_FILE_INFO_COUNT(temp_r28, pFileInfo->pDriveInfo)) {
        return 0xA008;
    }

    if (pFileInfo->pDriveInfo->nChan > 1) {
        return 0xA008;
    }

    temp_r28 = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];

    if (pFileInfo->unk_02 == 1) {
        if (pFileInfo->unk_24 == 0) {
            FS_fat_clear(pFileInfo->unk_22, pFileInfo->pDriveInfo);
        }

        status =
            FS_read_sub(NULL, 1, pFileInfo->unk_34, NULL, pFileInfo->pDriveInfo->unk_04, pFileInfo->pDriveInfo->nChan);
        if (status != 0) {
            return status;
        }

        temp_r29 = PTR_ROOT_DIR_ENTRY(temp_r28, pFileInfo->unk_38);
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

        status = FS_write_sub(NULL, 1, pFileInfo->unk_34, NULL, pFileInfo->pDriveInfo->unk_04, 0,
                              pFileInfo->pDriveInfo->nChan);
        if (status != 0) {
            return status;
        }

        pFileInfo->unk_02 = 0;
        status = FS_Flush(pFileInfo->pDriveInfo);
        if (status != 0) {
            return status;
        }
    }

    FS_free_FILE_id(pFileInfo);
    return status;
}
