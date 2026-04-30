#include "JSystem/JUtility/fs_open.h"

#include "JSystem/JUtility/fs_dele.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_form.h"
#include "JSystem/JUtility/fs_seek.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Open(SDDriveInfo* param1, SDFileInfo** ppFileInfo, char* param3, u16 param4) {
    SDFileInfo* temp_r28;
    DrvCtl* pDrvCtl;
    u16 status;

    status = 0;
    temp_r28 = *ppFileInfo;

    if ((param1 == NULL) || (param3 == NULL)) {
        return 0xA00C;
    }

    if (param1->unk_04 != 1) {
        return 0xA016;
    }

    if (param1->unk_06 != 2) {
        return 0xA003;
    }

    pDrvCtl = &FS_drv_ctl[param1->nChan];
    if (param1 != pDrvCtl->unk_08) {
        return 0xA00C;
    }

    status = FS_Open_sub(param1, ppFileInfo, param3, param4);
    if (status != 0) {
        *ppFileInfo = temp_r28;
    } else {
        (*ppFileInfo)->unk_32 = 0;
    }

    return status;
}

u16 FS_Open_sub(SDDriveInfo* param1, SDFileInfo** ppFileInfo, char* param3, u16 param4) {
    char sp84[64];
    char* sp64[8];
    u16 sp60;
    char sp20[64];
    u16 sp1C;
    DrvCtl* sp18;
    u16 status;

    sp60 = 0;
    sp18 = &FS_drv_ctl[param1->nChan];
    sp1C = param4;

    status = FS_open_flag_check(&sp1C);
    if (status != 0) {
        return status;
    }

    if (param1->unk_06 != 2) {
        return 0xA003;
    }

    if (FS_strlen(param3) > sizeof(sp84) - 1) {
        return 0xA017;
    }

    FS_strcpy(sp84, param3);
    status = FS_uchar_to_dchar(sp84);
    if (status != 0) {
        return status;
    }

    status = FS_check_same_FILE(param1, sp84, sp1C);
    if (status != 0) {
        return status;
    }

    FS_strcpy(sp20, sp84);

    status = FS_divide_fpathname(sp84, sp64, &sp60, param1->nChan);
    if (status != 0) {
        return status;
    }

    //! TODO: use array count?
    if (sp60 > (u16)(param1->unk_04 == 1 ? 8 : 5)) {
        return 0xA013;
    }

    if ((sp1C & 0x200) || (sp1C & 0x400)) {
        status = FS_open_check_parent(param1, sp20);
        if (status != 0) {
            return status;
        }

        status = FS_CreateFile_Open(param1, ppFileInfo, sp20, sp64, sp60, sp1C);
        if (status != 0) {
            return status;
        }
    } else {
        status = FS_ExistFile_Open(param1, ppFileInfo, sp20, sp64, sp60, sp1C);
        if (status != 0) {
            return status;
        }
    }

    if (sp1C & 0x100) {
        status = FS_Seek_sub(*ppFileInfo, 0, 4);
        if (status != 0) {
            FS_free_FILE_id(*ppFileInfo);
            return status;
        }
    }

    return 0;
}

u16 FS_CreateFile_Open(SDDriveInfo* pDriveInfo, SDFileInfo** ppFileInfo, char* param3, char** param4, u16 param5,
                       u16 param6) {
    u16 sp44;
    FSDirEntry sp24;
    u32 sp20;
    u16 sp1E;
    u16 sp1C;
    SDFileInfo* var_r29;
    u32 var_r27;
    u16 var_r25;
    u16 var_r24;
    DrvCtl* temp_r23;
    u16 status;

    temp_r23 = &FS_drv_ctl[pDriveInfo->nChan];

    sp44 = FS_get_FILE_id(pDriveInfo, 1);
    if (sp44 >= GET_FILE_INFO_COUNT(temp_r23, pDriveInfo)) {
        return 0xA004;
    }

    status = FS_get_entry(pDriveInfo, &sp24, param4, param5, &sp20, &sp1E, &sp1C);
    if (status != 0) {
        if (sp1C == 0 && param5 > 1) {
            return 0xA00F;
        }

        if (param6 & 1) {
            return 0xA00B;
        }

        var_r24 = 0;
    } else {
        if (param6 & 0x400) {
            return 0xA011;
        }

        var_r24 = 1;
    }

    var_r25 = 0;

    if (param5 == 1) {
        var_r27 = pDriveInfo->nSector;
    } else {
        var_r27 = FS_cluster_to_sector(pDriveInfo, sp1C);
        if (var_r27 == -1) {
            return 0xA032;
        }
    }

    if (var_r24 == 0) {
        status = FS_allocate_entry(pDriveInfo, var_r27, &sp20, &sp1E);
        if (status != 0) {
            return status;
        }

        status = FS_SetDirEntry(pDriveInfo, sp20, sp1E, param4, param5, var_r25);
        if (status != 0) {
            return status;
        }

        status = FS_Flush(pDriveInfo);
        if (status != 0) {
            return status;
        }

        sp44 = FS_get_FILE_id(pDriveInfo, 0);
        if (sp44 >= GET_FILE_INFO_COUNT(temp_r23, pDriveInfo)) {
            return 0xA004;
        }

        if (pDriveInfo->unk_04 == 1) {
            var_r29 = &temp_r23->unk_210[sp44];
        } else {
            var_r29 = &temp_r23->unk_47C[sp44];
        }

        status = FS_entry_name_set(var_r29->unk_08, param4[param5 - 1]);
        if (status != 0) {
            return status;
        }

        var_r29->unk_13 = 0x20;
        FS_memset(var_r29->unk_14, 0, sizeof(var_r29->unk_14));
        var_r29->unk_1E = 0;
        var_r29->unk_20 = 0;
        var_r29->unk_22 = var_r25;
        var_r29->unk_24 = 0;
        *ppFileInfo = var_r29;
    } else {
        status = FS_ExistFile_InfoPrc(pDriveInfo, ppFileInfo, &sp24, &sp44, param6);
        if (status != 0) {
            return status;
        }
    }

    status = FS_EntryInfo_Set(pDriveInfo, *ppFileInfo, sp44, sp20, sp1E, param3, param6);
    return status;
}

u16 FS_ExistFile_Open(SDDriveInfo* pDriveInfo, SDFileInfo** ppFileInfo, char* param3, char** param4, u16 param5,
                      u16 param6) {
    u16 sp48;
    FSDirEntry sp28;
    u32 sp24;
    u16 sp22;
    u16 sp20;
    DrvCtl* sp1C;
    u32 var_r29;
    u16 status;

    sp1C = &FS_drv_ctl[pDriveInfo->nChan];
    sp48 = FS_get_FILE_id(pDriveInfo, 1);

    if (sp48 >= GET_FILE_INFO_COUNT(sp1C, pDriveInfo)) {
        return 0xA004;
    }

    status = FS_get_entry(pDriveInfo, &sp28, param4, param5, &sp24, &sp22, &sp20);
    if (status != 0) {
        return 0xA007;
    }

    if (param6 & 0x800) {
        status = FS_file_atr_check(&sp28, param6);
        if (status != 0) {
            return status;
        }

        status = FS_Delete_Entry(pDriveInfo, sp24, sp22, sp20);
        if (status != 0) {
            return status;
        }

        if (param5 == 1) {
            var_r29 = pDriveInfo->nSector;
        } else {
            var_r29 = FS_cluster_to_sector(pDriveInfo, sp20);
            if (var_r29 + 0x10000 == 0xFFFF) {
                return 0xA032;
            }
        }

        status = FS_allocate_entry(pDriveInfo, var_r29, &sp24, &sp22);
        if (status != 0) {
            return status;
        }

        status = FS_SetDirEntry(pDriveInfo, sp24, sp22, param4, param5, 0);
        if (status != 0) {
            return status;
        }

        status = FS_Flush(pDriveInfo);
        if (status != 0) {
            return status;
        }

        status = FS_get_entry(pDriveInfo, &sp28, param4, param5, &sp24, &sp22, &sp20);
        if (status != 0) {
            return 0xA007;
        }
    }

    status = FS_ExistFile_InfoPrc(pDriveInfo, ppFileInfo, &sp28, &sp48, param6);
    if (status != 0) {
        return status;
    }

    status = FS_EntryInfo_Set(pDriveInfo, *ppFileInfo, sp48, sp24, sp22, param3, param6);
    return status;
}

u16 FS_ExistFile_InfoPrc(SDDriveInfo* pDriveInfo, SDFileInfo** ppFileInfo, FSDirEntry* pDirEntry, u16* param4,
                         u16 param6) {
    DrvCtl* temp_r26;
    SDFileInfo* var_r30;
    u16 status;

    temp_r26 = &FS_drv_ctl[pDriveInfo->nChan];

    status = FS_file_atr_check(pDirEntry, param6);
    if (status != 0) {
        return status;
    }

    if (pDirEntry->DIR_FileSize.data_u32 != 0 && pDirEntry->DIR_FstClusLO.data_u16 == 0) {
        return 0xA032;
    }

    if (pDirEntry->DIR_FstClusLO.data_u16 == 1 || pDirEntry->DIR_FstClusLO.data_u16 > pDriveInfo->unk_BC - 1) {
        return 0xA032;
    }

    if (pDriveInfo->unk_3C == 2) {
        if (pDirEntry->DIR_FstClusLO.data_u16 >= 0xFF7) {
            return 0xA032;
        }
    } else if (pDriveInfo->unk_3C == 1 && pDirEntry->DIR_FstClusLO.data_u16 >= 0xFFF7) {
        return 0xA032;
    }

    *param4 = FS_get_FILE_id(pDriveInfo, 0);

    if (*param4 >= GET_FILE_INFO_COUNT(temp_r26, pDriveInfo)) {
        return 0xA004;
    }

    if (pDriveInfo->unk_04 == 1) {
        var_r30 = &temp_r26->unk_210[*param4];
    } else {
        var_r30 = &temp_r26->unk_47C[*param4];
    }

    FS_strncpy(var_r30->unk_08, pDirEntry->DIR_Name, sizeof(var_r30->unk_08));
    var_r30->unk_13 = pDirEntry->DIR_Attr;

    // copies DIR_NTRes, DIR_CrtTimeTenth, DIR_CrtTime, DIR_CrtDate, DIR_LstAccDate and DIR_FstClusHI
    FS_strncpy(var_r30->unk_14, (char*)&pDirEntry->DIR_NTRes, OFFSET_DIR_WRT_TIME - OFFSET_DIR_NT_RES);

    var_r30->unk_1E = pDirEntry->DIR_WrtTime.data_u16;
    var_r30->unk_20 = pDirEntry->DIR_WrtDate.data_u16;
    var_r30->unk_22 = pDirEntry->DIR_FstClusLO.data_u16;
    var_r30->unk_24 = pDirEntry->DIR_FileSize.data_u32;
    *ppFileInfo = var_r30;
    return status;
}

u16 FS_EntryInfo_Set(SDDriveInfo* pDriveInfo, SDFileInfo* pFileInfo, u16 param3, u32 param4, u16 param5, char* param6,
                     u16 param7) {
    DrvCtl* sp24;

    sp24 = &FS_drv_ctl[pDriveInfo->nChan];

    pFileInfo->unk_00 = param3;
    pFileInfo->pDriveInfo = pDriveInfo;
    pFileInfo->unk_28 = 0;
    pFileInfo->unk_2C = param7;
    pFileInfo->unk_2E = pFileInfo->unk_22;
    pFileInfo->unk_30 = 0;
    pFileInfo->unk_34 = param4;
    pFileInfo->unk_38 = param5;
    FS_strcpy(pFileInfo->path, param6);
    return 0;
}

u16 FS_SetDirEntry(SDDriveInfo* pDriveInfo, u32 param2, u16 param3, char** param4, u16 param5, u16 param6) {
    FSDirEntry* temp_r30;
    DrvCtl* temp_r28;
    u16 status;

    (void)status;
    (void)status;
    (void)status;
    (void)status;

    temp_r28 = &FS_drv_ctl[pDriveInfo->nChan];

    status = FS_read_sub(NULL, 1, param2, NULL, pDriveInfo->unk_04, pDriveInfo->nChan);
    if (status != 0) {
        return status;
    }

    temp_r30 = PTR_ROOT_DIR_ENTRY(temp_r28, param3);
    FS_memset(temp_r30, 0, sizeof(FSDirEntry));
    temp_r30->DIR_Attr = FAT_ATTR_ARCHIVE;

    // sets DIR_NTRes, DIR_CrtTimeTenth, DIR_CrtTime, DIR_CrtDate, DIR_LstAccDate and DIR_FstClusHI
    FS_memset((char*)&temp_r30->DIR_NTRes, 0, OFFSET_DIR_WRT_TIME - OFFSET_DIR_NT_RES);

    temp_r30->DIR_FstClusLO.data_u8[0] = param6;
    temp_r30->DIR_FstClusLO.data_u8[1] = (param6 >> 8);
    temp_r30->DIR_FileSize.data_u32 = 0;
    FS_set_now_date(temp_r30, NULL);

    !pDriveInfo;

    status = FS_entry_name_set(temp_r30->DIR_Name, param4[param5 - 1]);
    if (status != 0) {
        return status;
    }

    return FS_write_sub(NULL, 1, param2, NULL, pDriveInfo->unk_04, 0, pDriveInfo->nChan);
}

u16 FS_get_FILE_id(SDDriveInfo* pDriveInfo, u16 param2) {
    DrvCtl* temp_r30;
    u16 var_r31;

    temp_r30 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo->unk_F4 > 5) {
        return 0xFFFF;
    }

    if (pDriveInfo->unk_04 == 2) {
        for (var_r31 = 0; var_r31 < ARRAY_COUNT(temp_r30->unk_47C); var_r31++) {
            if (temp_r30->unk_47C[var_r31].unk_00 == 0xFFFF) {
                if (param2 != 0) {
                    return 0;
                }

                temp_r30->unk_47C[var_r31].unk_00 = var_r31;
                temp_r30->unk_47C[var_r31].unk_02 = 0;
                temp_r30->unk_47C[var_r31].pDriveInfo = &temp_r30->unk_08[1];
                temp_r30->unk_47C[var_r31].pDriveInfo->unk_F4++;
                return var_r31;
            }
        }
    } else {
        for (var_r31 = 0; var_r31 < ARRAY_COUNT(temp_r30->unk_210); var_r31++) {
            if (temp_r30->unk_210[var_r31].unk_00 == 0xFFFF) {
                if (param2 != 0) {
                    return 0;
                }

                temp_r30->unk_210[var_r31].unk_00 = var_r31;
                temp_r30->unk_210[var_r31].unk_02 = 0;
                temp_r30->unk_210[var_r31].pDriveInfo = temp_r30->unk_08;
                temp_r30->unk_210[var_r31].pDriveInfo->unk_F4++;
                return var_r31;
            }
        }
    }

    return 0xFFFF;
}

void FS_free_FILE_id(SDFileInfo* pFileInfo) {
    DrvCtl* temp_r31;

    temp_r31 = &FS_drv_ctl[pFileInfo->pDriveInfo->nChan];

    if (pFileInfo->pDriveInfo->unk_04 == 2) {
        temp_r31->unk_47C[pFileInfo->unk_00].pDriveInfo->unk_F4--;
        temp_r31->unk_47C[pFileInfo->unk_00].pDriveInfo = NULL;
        temp_r31->unk_47C[pFileInfo->unk_00].unk_00 = 0xFFFF;
    } else {
        temp_r31->unk_210[pFileInfo->unk_00].pDriveInfo->unk_F4--;
        temp_r31->unk_210[pFileInfo->unk_00].pDriveInfo = NULL;
        temp_r31->unk_210[pFileInfo->unk_00].unk_00 = 0xFFFF;
    }
}

u16 FS_open_flag_check(u16* param1) {
    if (*param1 == 0) {
        return 0xA00B;
    }

    if (*param1 & 0xF0F8) {
        return 0xA00B;
    }

    if ((*param1 & 1) && (*param1 & 0xD00)) {
        return 0xA00B;
    }

    if (!(*param1 & 7)) {
        *param1 |= 4;
    }

    return 0;
}

u16 FS_file_atr_check(FSDirEntry* pDirEntry, u16 arg1) {
    if (CHECK_ATTR(pDirEntry, 0x10, FAT_ATTR_DIRECTORY) || CHECK_ATTR(pDirEntry, 0x08, FAT_ATTR_VOLUME_ID) ||
        CHECK_ATTR(pDirEntry, 0x0F, FAT_ATTR_LFN)) {
        return 0xA006;
    }

    if (pDirEntry->DIR_Attr & 1) {
        if (arg1 & 2) {
            return 0xA006;
        }

        if (arg1 & 4) {
            return 0xA006;
        }
    }

    return 0;
}

u16 FS_check_same_FILE(SDDriveInfo* pDriveInfo, char* param2, u16 param3) {
    DrvCtl* temp_r30;
    u16 var_r31;

    temp_r30 = &FS_drv_ctl[pDriveInfo->nChan];

    if (param3 == 1) {
        return 0;
    }

    if (pDriveInfo->unk_04 == 2) {
        //! @bug: should be `ARRAY_COUNT(temp_r30->unk_47C)`?
        for (var_r31 = 0; var_r31 < ARRAY_COUNT(temp_r30->unk_210); var_r31++) {
            if (temp_r30->unk_47C[var_r31].unk_00 != 0xFFFF &&
                FS_strncmp(temp_r30->unk_47C[var_r31].path, param2, (u16)FS_strlen(param2)) == 0) {
                return 0xA018;
            }
        }
    } else {
        for (var_r31 = 0; var_r31 < ARRAY_COUNT(temp_r30->unk_210); var_r31++) {
            if (temp_r30->unk_210[var_r31].unk_00 != 0xFFFF &&
                FS_strncmp(temp_r30->unk_210[var_r31].path, param2, (u16)FS_strlen(param2)) == 0) {
                return 0xA018;
            }
        }
    }

    return 0;
}

u16 FS_Search_Entry(SDDriveInfo* pDriveInfo, char* param_2, char* param3, char** param4, u16* param5,
                    FSDirEntry* param6, u32* param7, u16* param8, u16* param9, u16 param10) {
    DrvCtl* sp28;
    u16 status;

    sp28 = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo->unk_06 != 2) {
        return 0xA003;
    }

    if (FS_strlen(param_2) > 0x3F) {
        return 0xA017;
    }

    FS_strcpy(param3, param_2);
    if (param3[0] == '\\' && param3[1] == '\0') {
        return 0xA02C;
    }

    status = FS_uchar_to_dchar(param3);
    if (status != 0) {
        return status;
    }

    switch (param10) {
        case 1:
            status = FS_open_check_parent(pDriveInfo, param3);
            if (status == 0xA02F) {
                return status;
            }

            if (status != 0) {
                return 0xA009;
            }

            break;
        case 2:
            status = FS_open_check_all(pDriveInfo, param3);
            if (status != 0) {
                return status;
            }
            break;
        case 4:
            status = FS_open_check_parent(pDriveInfo, param3);
            if (status != 0xA02F && status != 0) {
                return 0xA009;
            }
            break;
        default:
            break;
    }

    status = FS_divide_fpathname(param3, param4, param5, pDriveInfo->nChan);
    if (status != 0) {
        return status;
    }

    if (*param5 > 8) {
        return 0xA013;
    }

    status = FS_get_entry(pDriveInfo, param6, param4, *param5, param7, param8, param9);
    if (status != 0) {
        return 0xA007;
    }

    return status;
}
