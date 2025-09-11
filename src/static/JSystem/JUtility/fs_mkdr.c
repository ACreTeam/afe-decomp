#include "JSystem/JUtility/fs_mkdr.h"

#include "JSystem/JUtility/fs_form.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Mkdir(SDDriveInfo* pDriveInfo, const char* param2) {
    u16 status;
    DrvCtl* pDrvCtl;

    if (pDriveInfo == NULL || param2 == NULL) {
        return 0xA00C;
    }

    if (pDriveInfo->unk_06 != 2) {
        return 0xA003;
    }

    if (pDriveInfo->unk_04 != 1) {
        return 0xA016;
    }

    pDrvCtl = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo != pDrvCtl->unk_08) {
        return 0xA00C;
    }

    status = FS_Mkdir_sub(pDriveInfo, param2);
    return status;
}

u16 FS_Mkdir_sub(SDDriveInfo* pDriveInfo, const char* param2) {
    FSDirEntry sp88;
    NowData sp80;
    u32 sp7C;
    u16 sp78;
    u16 sp76;
    u16 sp74;
    u16 sp72;
    u16 sp70;
    char* sp50[8];
    char sp10[64];
    FSDirEntry* temp_r29;
    DrvCtl* temp_r27;
    u32 var_r28;
    u16 status;

    sp76 = 0;
    temp_r27 = &FS_drv_ctl[pDriveInfo->nChan];

    if (FS_strlen(param2) > 64 - 1) {
        return 0xA017;
    }

    FS_strcpy(sp10, param2);

    if (sp10[0] == '\\' && sp10[1] == '\0') {
        return 0xA02C;
    }

    if (pDriveInfo->unk_06 != 2) {
        return 0xA003;
    }

    status = FS_uchar_to_dchar(sp10);
    if (status != 0) {
        return status;
    }

    status = FS_open_check_parent(pDriveInfo, sp10);
    if (status == 0xA02F) {
        return status;
    }

    if (status != 0) {
        return 0xA011;
    }

    status = FS_divide_fpathname(sp10, sp50, &sp76, pDriveInfo->nChan);
    if (status != 0) {
        return status;
    }

    status = FS_get_entry(pDriveInfo, &sp88, sp50, sp76, &sp7C, &sp72, &sp70);
    if (status == 0) {
        return 0xA011;
    }

    status = FS_get_space(pDriveInfo, 0, &sp74);
    if (status != 0) {
        return status;
    }

    GetNowData(&sp80);

    if (sp76 == 1) {
        status = FS_initialize_directory_data(pDriveInfo, sp74, 0, &sp80);
    } else {
        status = FS_initialize_directory_data(pDriveInfo, sp74, sp70, &sp80);
    }

    if (status != 0) {
        FS_release_space(pDriveInfo, sp74, sp74);
        return status;
    }

    if (sp76 == 1) {
        var_r28 = pDriveInfo->nSector;
    } else {
        var_r28 = FS_cluster_to_sector(pDriveInfo, sp70);
        if ((var_r28 + 0x10000) == 0xFFFF) {
            FS_release_space(pDriveInfo, sp74, sp74);
            return 0xA02A;
        }
    }

    status = FS_allocate_entry(pDriveInfo, (u32)var_r28, &sp7C, &sp72);
    if (status != 0) {
        FS_release_space(pDriveInfo, sp74, sp74);
        return status;
    }

    temp_r29 = (FSDirEntry*)&temp_r27->ctrl_p.unk_20BA4[(sp72 / (u16)sizeof(FSDirEntry)) * sizeof(FSDirEntry)];
    FS_memset(temp_r29, 0, sizeof(FSDirEntry));

    status = FS_entry_name_set(temp_r29->DIR_Name, sp50[sp76 - 1]);
    if (status != 0) {
        FS_release_space(pDriveInfo, sp74, sp74);
        return status;
    }

    sp78 = FS_set_now_date(temp_r29, &sp80);
    temp_r29->DIR_Attr = FAT_ATTR_DIRECTORY;
    temp_r29->DIR_FstClusLO.data_u8[0] = sp74;
    temp_r29->DIR_FstClusLO.data_u8[1] = (sp74 >> 8);

    status = FS_write_sub(NULL, 1, sp7C, NULL, pDriveInfo->unk_04, 0, pDriveInfo->nChan);
    if (status != 0) {
        FS_release_space(pDriveInfo, sp74, sp74);
        return status;
    }

    return FS_Flush(pDriveInfo);
}

u16 FS_initialize_directory_data(SDDriveInfo* pDriveInfo, u16 param2, u16 param3, NowData* pNowData) {
    FSDirEntry* temp_r31;
    u32 var_r29;
    u32 var_r28;
    DrvCtl* temp_r26;
    u16 var_r25;
    u16 status;
    int pad1;
    int pad2;

    (void)pad1;
    (void)pad1;

    temp_r26 = &FS_drv_ctl[pDriveInfo->nChan];
    FS_memset(temp_r26->ctrl_p.unk_20BA4, 0, sizeof(temp_r26->ctrl_p.unk_20BA4));

    temp_r31 = (FSDirEntry*)temp_r26->ctrl_p.unk_20BA4;
    FS_strncpy(temp_r31->DIR_Name, ".          ", sizeof(temp_r31->DIR_Name));
    temp_r31->DIR_Attr = FAT_ATTR_DIRECTORY;
    FS_set_now_date(temp_r31, pNowData);
    temp_r31->DIR_FstClusLO.data_u8[0] = param2;
    temp_r31->DIR_FstClusLO.data_u8[1] = (param2 >> 8);

    temp_r31++;
    FS_strncpy(temp_r31->DIR_Name, "..         ", sizeof(temp_r31->DIR_Name));
    temp_r31->DIR_Attr = FAT_ATTR_DIRECTORY;
    FS_set_now_date(temp_r31, pNowData);
    temp_r31->DIR_FstClusLO.data_u8[0] = param3;
    temp_r31->DIR_FstClusLO.data_u8[1] = (param3 >> 8);

    var_r29 = FS_cluster_to_sector(pDriveInfo, param2);
    if ((var_r29 + 0x10000) == 0xFFFF) {
        return 0xA029;
    }

    if (pDriveInfo->unk_1E > 0x20) {
        var_r28 = 0x20;
    } else {
        var_r28 = pDriveInfo->unk_1E;
    }

    status = FS_write_sub(NULL, var_r28, var_r29, NULL, pDriveInfo->unk_04, 0, pDriveInfo->nChan);
    if (status != 0) {
        return status;
    }

    var_r29 = var_r29 + var_r28;
    FS_memset(temp_r26->ctrl_p.unk_20BA4, 0, 0x40);

    for (var_r25 = 0; var_r25 < (pDriveInfo->unk_1E / (u16)var_r28) - 1; var_r25++) {
        status = FS_write_sub(NULL, var_r28, var_r29, NULL, pDriveInfo->unk_04, 0, pDriveInfo->nChan);
        if (status != 0) {
            return status;
        }

        var_r29 += var_r28;
    }

    return 0;
}
