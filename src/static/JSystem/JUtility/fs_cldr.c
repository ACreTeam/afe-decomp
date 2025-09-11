#include "JSystem/JUtility/fs_cldr.h"

#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Closedir(SDDirInfo* pDirInfo) {
    u16 status;
    DrvCtl* ptr;
    s32 spC = 0;

    if (pDirInfo == NULL) {
        return 0xA00C;
    } else {
        ptr = &FS_drv_ctl[pDirInfo->pDriveInfo->nChan];

        if (pDirInfo->pDriveInfo != &ptr->unk_08[0]) {
            return 0xA02E;
        } else if (pDirInfo->pDriveInfo->unk_06 != 2) {
            return 0xA003;
        } else if (pDirInfo->pDriveInfo->unk_04 != 1) {
            return 0xA016;
        }

        status = FS_Closedir_sub(pDirInfo);
        if (status != 0) {
            return status;
        }
    }

    return 0;
}

u16 FS_Closedir_sub(SDDirInfo* pDirInfo) {
    pDirInfo->pDriveInfo = NULL;
    pDirInfo->unk_04 = 0;
    pDirInfo->unk_08 = 0;
    pDirInfo->unk_10 = 0;
    pDirInfo->unk_0C = 0;
    pDirInfo->unk_12 = 0;
    FS_memset(pDirInfo->unk_14, 0, sizeof(pDirInfo->unk_14));
    return 0;
}
