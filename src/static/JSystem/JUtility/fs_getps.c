#include "JSystem/JUtility/fs_file.h"

u16 FS_Getpos(FSFile* pFile, int* arg1) {
    u16 status = 0;
    DrvCtl* ptr;

    if (pFile == NULL) {
        return 0xA00C;
    } else if (pFile->unk_04_ptr[2] != 1) {
        return 0xA016;
    } else if (pFile->unk_04_ptr[3] != 2) {
        return 0xA003;
    }

    ptr = &FS_drv_ctl[pFile->unk_04_ptr[0]];

    if (pFile->unk_04_ptr != ptr->unk_08) {
        return 0xA00C;
    } else if (pFile->unk_00[0] >= 5) {
        return 0xA008;
    } else {
        *arg1 = pFile->unk_28;
    }

    return status;
}
