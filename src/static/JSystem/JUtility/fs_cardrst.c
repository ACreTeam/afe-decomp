#include "JSystem/JUtility/fs_drvsel.h"

u16 FS_CardIFReset(void) {
    u16 status = FS_DrvSel_Reset();
    return status;
}
