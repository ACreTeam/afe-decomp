#include "JSystem/JUtility/fs_chdr.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Chdir(SDDriveInfo* pDriveInfo, char* arg1) {
    u16 status;
    DrvCtl* ptr;

    if (pDriveInfo == NULL || arg1 == NULL) {
        return 0xA00C;
    } else if (pDriveInfo->unk_04 != 1) {
        return 0xA016;
    } else if (pDriveInfo->unk_06 != 2) {
        return 0xA003;
    }

    ptr = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo != &ptr->unk_08[0]) {
        return 0xA00C;
    }

    status = FS_Chdir_sub(pDriveInfo, arg1);
    return status;
}

u16 FS_Chdir_sub(SDDriveInfo* pDriveInfo, char* arg1) {
    u16 status;
    u16 sp9A;
    char sp80[25];
    s32 sp7C;
    u16 sp78[2];
    u16 sp76;
    u16 sp74;
    char* sp54[8];
    char sp14[64];
    DrvCtl *sp10;

    sp78[0] = 0;
    sp10 = &FS_drv_ctl[pDriveInfo->nChan];

    if (FS_strlen(arg1) > 63) {
        return 0xA017;
    } else if (pDriveInfo->unk_06 != 2) {
        return 0xA003;
    } else if (FS_strncmp(arg1, "\\\0", 2) == 0) {
        pDriveInfo->unk_6C = 0;
        pDriveInfo->unk_70 = 0;
        pDriveInfo->unk_72 = 0;
        pDriveInfo->unk_74 = 0;
        FS_memset(pDriveInfo->unk_76, 0, sizeof(pDriveInfo->unk_76));
        FS_strncpy(pDriveInfo->unk_76, "\\", 1);
        return 0;
    }

    FS_strcpy(sp14, arg1);
    status = FS_uchar_to_dchar(sp14);
    if (status != 0) {
        return status;
    }

    status = FS_divide_fpathname(sp14, sp54, sp78, pDriveInfo->nChan);
    if (status != 0) {
        return status;
    }

    status = FS_get_entry(pDriveInfo, sp80, sp54, sp78[0], &sp7C, &sp76, &sp74);
    if (status != 0) {
        return status;
    }

    if ((sp80[11] & 0x10) != 0x10 || (sp80[11] & 0x08) == 0x08 || (sp80[11] & 0x0F) == 0x0F) {
        return 0xA027;
    }

    pDriveInfo->unk_6C = sp7C;
    pDriveInfo->unk_70 = sp76;
    pDriveInfo->unk_72 = sp74;
    pDriveInfo->unk_74 = sp9A;
    FS_strcpy(sp14, arg1);
    FS_uchar_to_dchar(sp14);
    FS_strcpy(pDriveInfo->unk_76, sp14);
    return 0;
}
