#include "JSystem/JUtility/fs_dele.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_open.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Delete(SDDriveInfo* pDriveInfo, const char* param2) {
    DrvCtl* ptr;
    u16 status = 0;

    if (pDriveInfo == NULL || param2 == NULL) {
        return 0xA00C;
    }

    if (pDriveInfo->unk_04 != 1) {
        return 0xA016;
    }

    ptr = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo != &ptr->unk_08[0]) {
        return 0xA00C;
    }

    status = FS_Delete_sub(pDriveInfo, param2);
    return status;
}

u16 FS_Delete_sub(SDDriveInfo* pDriveInfo, const char* param2) {
    char sp68[64];
    char sp48[32];
    u16 sp44[2];
    char sp24[32];
    int sp20;
    u16 sp1E;
    u16 sp1C;
    DrvCtl* ptr;
    u16 status;

    sp44[0] = 0;
    ptr = &FS_drv_ctl[pDriveInfo->nChan];
    status = FS_Search_Entry(pDriveInfo, (char*)param2, sp68, sp48, sp44, sp24, &sp20, &sp1E, &sp1C, 1);

    if (status != 0) {
        return status;
    }

    if ((sp24[11] & 1) || (sp24[11] & 8) || (sp24[11] & 0x10) || ((sp24[11] & 0xF) == 0xF)) {
        return 0xA006;
    }

    status = FS_Delete_Entry(pDriveInfo, sp20, sp1E, sp1C);
    return status;
}

u16 FS_Delete_Entry(SDDriveInfo* pDriveInfo, int param2, u16 param3, u16 param4) {
    DrvCtl* ptr;
    FSDirEntry* ptr2;
    u16 clusterLO;
    u16 status;
    int pad;
    int idx;

    ptr = &FS_drv_ctl[pDriveInfo->nChan];

    if(pDriveInfo->unk_1E[0] == 0x20) {
        pad = 0;
        (void)pad;
        (void)pad;
        (void)idx;
    }

    idx = (int)param3;
    ptr2 = PTR_ROOT_DIR_ENTRY(ptr, idx);

    ptr2->DIR_Name[0] = FLAG_DELETED;
    clusterLO = ((ptr2->DIR_FstClusLO.data_u8[1] << 8) & 0xFF00) | (ptr2->DIR_FstClusLO.data_u8[0] & 0x00FF);

    status = FS_delete_lfn_entry(pDriveInfo, param4, param2, param3);

    if (status != 0) {
        return status;
    }

    if (clusterLO > 1 && clusterLO <= (pDriveInfo->unk_BC - 1)) {
        status = FS_fat_clear(clusterLO, pDriveInfo);

        if (status != 0) {
            return status;
        }

        status = FS_Flush(pDriveInfo);
    } else {
        if (clusterLO == 0) {
            status = 0;
        } else {
            status = 0xA032;
        }
    }

    return status;
}
