#include "JSystem/JUtility/fs_rddr.h"

#include "JSystem/JUtility/fs_form.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Readdir(SDDirInfo* pDirInfo, UnknownStruct3* param2) {
    u16 status;
    DrvCtl* pDrvCtl;

    if (pDirInfo == NULL) {
        return 0xA00C;
    }

    if (pDirInfo->pDriveInfo->unk_04 != 1) {
        return 0xA016;
    }

    pDrvCtl = &FS_drv_ctl[pDirInfo->pDriveInfo->nChan];

    if (pDirInfo->pDriveInfo != pDrvCtl->unk_08) {
        return 0xA02E;
    }

    status = FS_Readdir_sub(pDirInfo, param2);
    return status;
}

u16 FS_Readdir_sub(SDDirInfo* pDirInfo, UnknownStruct3* param2) {
    FSDirEntry* var_r31;
    u16 temp_r30;
    DrvCtl* temp_r20;
    u32 temp_r27;
    u16 status;
    u16 var_r25;
    u32 var_r24;
    u32 var_r23;
    u16 temp_r22;
    u16 var_r21;
    u16 var_r19;
    char sp34[64];
    u16 sp32;
    volatile u16 sp30;
    volatile u32 sp2C;
    volatile u32 sp28;
    volatile u32 sp24;
    SDDriveInfo* volatile sp20;
    char sp10[16];

    (void)var_r24;
    (void)temp_r22;
    (void)var_r21;

    temp_r20 = &FS_drv_ctl[pDirInfo->pDriveInfo->nChan];

    if (param2 == NULL) {
        return 0xA00C;
    }

    if (pDirInfo->pDriveInfo->unk_06 != 2) {
        return 0xA003;
    }

    if ((pDirInfo->unk_0C + 0x10000) == 0xFFFF) {
        return 0xA030;
    }

    sp20 = pDirInfo->pDriveInfo;
    sp24 = pDirInfo->unk_04;
    sp28 = pDirInfo->unk_08;
    sp2C = pDirInfo->unk_0C;
    sp30 = pDirInfo->unk_10;
    sp32 = pDirInfo->unk_12;

    FS_strncpy(sp34, pDirInfo->unk_14, sizeof(sp34));
    temp_r22 = sp20->unk_1C * sp20->unk_1E[0];

    if (sp20->unk_1E[0] > 0x20) {
        var_r23 = 0x20;
    } else {
        var_r23 = sp20->unk_1E[0];
    }

    var_r31 = PTR_ROOT_DIR_ENTRY(temp_r20, sp28 % (var_r23 * sp20->unk_1C));
    // var_r25 = sp28 % temp_r22;
    var_r25 = (temp_r22 - (u16)(sp28 % temp_r22)) / 32;

    if (sp34[0] == '\\' && sp34[1] == '\0') {
        temp_r27 = ((sp28 % temp_r22) + (sp20->unk_1C * (sp2C - sp24)));
        temp_r27 /= 32;
        temp_r27 = sp20->unk_28 - temp_r27;

        if (temp_r27 < var_r25) {
            var_r25 = temp_r27;
        }
    }

    var_r24 = sp2C;
    var_r24 += (var_r23 * ((sp28 % temp_r22) / (var_r23 * sp20->unk_1C)));

    for (var_r19 = 0; var_r19 < 0xFFFF; var_r19++) {
        status = FS_read_sub(NULL, var_r23, var_r24, NULL, sp20->unk_04, pDirInfo->pDriveInfo->nChan);
        if (status != 0) {
            return status;
        }

        for (var_r21 = 0; var_r21 < var_r25; var_r21++) {
            if (var_r31->DIR_Name[0] == '\0') {
                return 0xA030;
            }

            if (var_r31->DIR_Name[0] == FAT_FLAG_DELETED || VOLUME_ID(var_r31) ||
                CHECK_ATTR(var_r31, 0x0F, FAT_ATTR_LFN)) {
                if ((u8*)var_r31 == (u8*)&temp_r20->ctrl_p.unk_20BA4 - 0x20 + (u16)(var_r23 * sp20->unk_1C) &&
                    var_r21 != var_r25 - 1) {
                    var_r24 += var_r23;

                    status = FS_read_sub(NULL, var_r23, var_r24, NULL, sp20->unk_04, pDirInfo->pDriveInfo->nChan);
                    if (status != 0) {
                        return status;
                    }

                    // ?
                    var_r31 = (FSDirEntry*)&temp_r20->ctrl_p.unk_20BA4;
                    var_r31--;
                }
            } else {
                FS_strncpy(sp10, var_r31->DIR_Name, sizeof(var_r31->DIR_Name));
                FS_entname_to_stdname(sp10);

                if (FS_strlen(pDirInfo->unk_14) + 1 + FS_strlen(sp10) > sizeof(param2->unk_00) - 1) {
                    FS_memset(param2->unk_00, 0, sizeof(param2->unk_00));
                    status = 0xA017;
                } else {
                    FS_memset(param2->unk_00, 0, sizeof(param2->unk_00));
                    FS_strncpy(param2->unk_00, pDirInfo->unk_14, FS_strlen(pDirInfo->unk_14));
                    FS_strncpy((char*)&param2->unk_00[FS_strlen(pDirInfo->unk_14)], "\\", 1);
                    FS_strncpy(param2->unk_00 + FS_strlen(pDirInfo->unk_14) + 1, sp10, FS_strlen(sp10));
                    status = 0;
                }

                FS_uchar_to_dchar(param2->unk_00);
                param2->unk_52 = LOAD_LE_u16(var_r31->DIR_FstClusLO);
                param2->unk_40 = LOAD_LE_u32(var_r31->DIR_FileSize);
                param2->unk_44 = LOAD_LE_u16(var_r31->DIR_Attr);

                temp_r30 = LOAD_LE_u16(var_r31->DIR_WrtDate.data_u16);
                param2->unk_46 = (((temp_r30 >> 9) & 0x7F) + 1980);
                param2->unk_48 = ((temp_r30 >> 5) & 0x0F);
                param2->unk_4A = (temp_r30 & 0x1F);

                temp_r30 = LOAD_LE_u16(var_r31->DIR_WrtTime.data_u16);
                param2->unk_4C = ((temp_r30 >> 11) & 0x1F);
                param2->unk_4E = ((temp_r30 >> 5) & 0x3F);
                param2->unk_50 = ((temp_r30 << 1) & 0x3E);
                sp28 += 0x20;
                sp30++;

                if (var_r21 == (var_r25 - 1)) {
                    if (sp34[0] == '\\' && sp34[1] == '\0') {
                        if ((sp2C + sp20->unk_1E[0]) < sp20->unk_64) {
                            sp2C += sp20->unk_1E[0];
                        } else {
                            sp2C = -1;
                        }
                    } else {
                        // right var? (var_r30)
                        temp_r30 = FS_sector_to_cluster(sp20, sp2C);
                        temp_r30 = FS_get_next_cluster(sp20, temp_r30);
                        if (temp_r30 > 0xFFF6 && temp_r30 < 0xFFFF) {
                            return 0xA029;
                        }

                        sp2C = FS_cluster_to_sector(sp20, temp_r30);
                    }
                }

                pDirInfo->unk_08 = sp28;
                pDirInfo->unk_0C = sp2C;
                pDirInfo->unk_10 = sp30;
                return status;
            }

            var_r31++;
            sp28 += 0x20;
        }

        if (sp34[0] == '\\' && sp34[1] == '\0') {
            if ((sp2C + sp20->unk_1E[0]) >= sp20->unk_64) {
                return 0xA030;
            }

            sp2C += sp20->unk_1E[0];
            var_r24 = sp2C;
        } else {
            // right var? (temp_r3_3)
            temp_r30 = FS_sector_to_cluster(sp20, sp2C);
            temp_r30 = FS_get_next_cluster(sp20, temp_r30);
            if (temp_r30 > 0xFFF6 && temp_r30 < 0xFFFF) {
                return 0xA029;
            }

            sp2C = FS_cluster_to_sector(sp20, temp_r30);
            var_r24 = sp2C;

            if ((var_r24 + 0x10000) == 0xFFFF) {
                return 0xA030;
            }
        }

        var_r31 = (FSDirEntry*)temp_r20->ctrl_p.unk_20BA4;
        var_r25 = ((sp20->unk_1E[0] * sp20->unk_1C) / 32);

        if (sp34[0] == '\\' && sp34[1] == '\0') {
            temp_r27 = (u32)((sp20->unk_1C * (sp2C - sp24)) + sp28);
            temp_r27 >>= 5;
            temp_r27 = sp20->unk_28 - temp_r27;
            if (temp_r27 < var_r25) {
                var_r25 = temp_r27;
            }
        }
    }

    return 0xA029;
}
