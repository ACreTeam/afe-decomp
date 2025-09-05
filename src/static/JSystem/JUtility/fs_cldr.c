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
        ptr = &FS_drv_ctl[pDir->pFile->unk_00[0]];

        if (pDir->pFile->unk_00 != ptr->unk_08) {
            return 0xA02E;
        } else if (pDir->pFile->unk_04[1] != 2) {
            return 0xA003;
        } else if (pDir->pFile->unk_04[0] != 1) {
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
    pDir->pFile = NULL;
    pDir->unk_04 = 0;
    pDir->unk_08 = 0;
    pDir->unk_10 = 0;
    pDir->unk_0C = 0;
    pDir->unk_12 = 0;
    FS_memset(pDir->unk_14, 0, sizeof(pDir->unk_14));
    return 0;
}
