#include "JSystem/JUtility/fs_opdr.h"

#include "JSystem/JUtility/fs_form.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Opendir(SDDriveInfo* pDriveInfo, SDDirInfo** ppDirInfo, const char* param3) {
    u16 status;
    DrvCtl* pDrvCtl;

    if (pDriveInfo == NULL || ppDirInfo == NULL || param3 == NULL) {
        return 0xA00C;
    }

    if (pDriveInfo->unk_04 != 1) {
        return 0xA016;
    }

    if (pDriveInfo->unk_06 != 2) {
        return 0xA003;
    }

    pDrvCtl = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo != pDrvCtl->unk_08) {
        return 0xA00C;
    }

    status = FS_Opendir_sub(pDriveInfo, ppDirInfo, param3);
    return status;
}

u16 FS_Opendir_sub(SDDriveInfo* pDriveInfo, SDDirInfo** ppDirInfo, const char* param3) {
    SDDirInfo* var_r28;
    SDDirInfo* var_r31;
    u16 status;
    u16 var_r26;
    u16 var_r29;
    DrvCtl* temp_r25;
    FSDirEntry sp80;
    u32 sp7C;
    u16 sp78;
    u16 sp76;
    u16 sp74;
    char* sp54[8];
    char sp14[64];

    sp78 = 0;
    temp_r25 = &FS_drv_ctl[pDriveInfo->nChan];

    if (FS_strlen(param3) > sizeof(sp14) - 1) {
        return 0xA017;
    }

    FS_strcpy(sp14, param3);

    if (pDriveInfo->unk_06 != 2) {
        return 0xA003;
    }

    status = FS_uchar_to_dchar(sp14);
    if (status != 0) {
        return status;
    }

    var_r31 = NULL;

    if (pDriveInfo->unk_04 == 1) {
        var_r28 = temp_r25->unk_20A00;
    } else {
        var_r28 = temp_r25->unk_20AFC;
    }

    for (var_r26 = 0; var_r26 < GET_DIR_INFO_COUNT2(temp_r25, pDriveInfo); var_r26++, var_r28++) {
        if (var_r28->pDriveInfo != NULL) {
            for (var_r29 = 0; var_r29 < 64; var_r29++) {
                if (var_r29 == 0x3F) {
                    if (sp14[var_r29] != '\0') {
                        return 0xA017;
                    }

                    if (var_r28->unk_14[var_r29] != '\0') {
                        return 0xA02D;
                    }

                    return 0xA02F;
                }

                if (var_r28->unk_14[var_r29] == '\0') {
                    if (sp14[var_r29] == '\0') {
                        return 0xA02F;
                    }
                } else if (var_r28->unk_14[var_r29] == sp14[var_r29]) {
                    continue;
                }

                break;
            }
        } else if (var_r31 == NULL) {
            if (pDriveInfo->unk_04 == 1) {
                var_r31 = &temp_r25->unk_20A00[var_r26];
            } else {
                var_r31 = &temp_r25->unk_20AFC[var_r26];
            }
            var_r31->pDriveInfo = pDriveInfo;
        }
    }

    if (var_r31 == NULL) {
        return 0xA004;
    }

    if (sp14[0] == '\\' && sp14[1] == '\0') {
        var_r31->unk_04 = pDriveInfo->nSector;
        var_r31->unk_08 = 0;
        var_r31->unk_10 = 0;
        var_r31->unk_0C = pDriveInfo->nSector;
        FS_memset(var_r31->unk_14, 0, sizeof(var_r31->unk_14));
        FS_strcpy(var_r31->unk_14, sp14);
        var_r31->unk_12 = pDriveInfo->unk_FA;
        *ppDirInfo = var_r31;
        return 0;
    }

    FS_memset(var_r31->unk_14, 0, sizeof(var_r31->unk_14));
    FS_strcpy(var_r31->unk_14, sp14);

    status = FS_divide_fpathname(sp14, sp54, &sp78, pDriveInfo->nChan);
    if (status != 0) {
        var_r31->pDriveInfo = NULL;
        return status;
    }

    if (FS_get_entry(pDriveInfo, &sp80, sp54, sp78, &sp7C, &sp76, &sp74) != 0) {
        var_r31->pDriveInfo = NULL;
        return 0xA00F;
    }

    if (!DIRECTORY(&sp80) || CHECK_ATTR(&sp80, 0x3F, FAT_ATTR_LFN)) {
        var_r31->pDriveInfo = NULL;
        return 0xA027;
    }

    var_r31->unk_04 = FS_cluster_to_sector(pDriveInfo, sp80.DIR_FstClusLO.data_u16);
    if (var_r31->unk_04 == -1) {
        return 0xA032;
    }

    var_r31->unk_08 = 0;
    var_r31->unk_10 = 0;
    var_r31->unk_0C = var_r31->unk_04;
    var_r31->unk_12 = pDriveInfo->unk_FA;
    *ppDirInfo = var_r31;
    return 0;
}
