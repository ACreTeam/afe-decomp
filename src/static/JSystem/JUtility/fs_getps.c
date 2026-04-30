#include "JSystem/JUtility/fs_getps.h"

#include "JSystem/JUtility/fs_file.h"

u16 FS_Getpos(SDFileInfo* pFileInfo, u32* arg1) {
    u16 status = 0;
    DrvCtl* ptr;

    if (pFileInfo == NULL) {
        return 0xA00C;
    } else if (pFileInfo->pDriveInfo->unk_04 != 1) {
        return 0xA016;
    } else if (pFileInfo->pDriveInfo->unk_06 != 2) {
        return 0xA003;
    }

    ptr = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];

    if (pFileInfo->pDriveInfo != &ptr->unk_08[0]) {
        return 0xA00C;
    } else if (pFileInfo->unk_00 >= 5) {
        return 0xA008;
    } else {
        *arg1 = pFileInfo->unk_28;
    }

    return status;
}
