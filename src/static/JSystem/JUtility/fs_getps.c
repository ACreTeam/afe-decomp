#include "JSystem/JUtility/fs_getps.h"
#include "JSystem/JUtility/fs.h"

u16 FS_Getpos(FSFile* pFile, int* arg1) {
    u16 status = 0;
    u16* ptr;

    if (pFile == NULL) {
        return 0xA00C;
    } else if (pFile->unk_04[2] != 1) {
        return 0xA016;
    } else if (pFile->unk_04[3] != 2) {
        return 0xA003;
    }

    ptr = (u16*)&FS_drv_ctl[pFile->unk_04[0] * 0x25E48];

    //! TODO: is FS_drv_ctl type FSFile struct?
    if (pFile->unk_04 != ptr + 4) {
        return 0xA00C;
    } else if (pFile->unk_00 >= 5) {
        return 0xA008;
    } else {
        *arg1 = pFile->unk_28;
    }

    return status;
}
