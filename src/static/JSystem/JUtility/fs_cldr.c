#include "JSystem/JUtility/fs_cldr.h"

#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Closedir(FSDir* pDir) {
    u16 status;
    DrvCtl* ptr;
    s32 spC = 0;

    if (pDir == NULL) {
        return 0xA00C;
    } else {
        ptr = &FS_drv_ctl[pDir->pDriveInfo->nChan];

        if (pDir->pDriveInfo != &ptr->unk_08[0]) {
            return 0xA02E;
        } else if (pDir->pDriveInfo->unk_06 != 2) {
            return 0xA003;
        } else if (pDir->pDriveInfo->unk_04 != 1) {
            return 0xA016;
        }

        status = FS_Closedir_sub(pDir);
        if (status != 0) {
            return status;
        }
    }

    return 0;
}

u16 FS_Closedir_sub(FSDir* pDir) {
    pDir->pDriveInfo = NULL;
    pDir->unk_04 = 0;
    pDir->unk_08 = 0;
    pDir->unk_10 = 0;
    pDir->unk_0C = 0;
    pDir->unk_12 = 0;
    FS_memset(pDir->unk_14, 0, sizeof(pDir->unk_14));
    return 0;
}
