#include "JSystem/JUtility/fs_renm.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_form.h"
#include "JSystem/JUtility/fs_open.h"
#include "JSystem/JUtility/fs_subd.h"
#include "types.h"

u16 FS_Rename(SDDriveInfo* pDriveInfo, char* arg1, char* arg2) {
    u16 status;
    DrvCtl* ptr;

    if (pDriveInfo == NULL || arg1 == NULL || arg2 == NULL) {
        return 0xA00C;
    } else if (pDriveInfo->unk_06 != 2) {
        return 0xA003;
    } else if (pDriveInfo->unk_04 != 1) {
        return 0xA016;
    }

    ptr = &FS_drv_ctl[pDriveInfo->nChan];

    if (pDriveInfo != &ptr->unk_08[0]) {
        return 0xA00C;
    }

    status = FS_Rename_sub(pDriveInfo, arg1, arg2);
    return status;
}

u16 FS_Rename_sub(SDDriveInfo *pDriveInfo, char *arg1, char *arg2) {
    char spF8[64];
    char spB8[64];
    char* sp98[8];
    char* sp78[8];
    u16 sp76;
    u16 sp74;
    FSDirEntry sp54;
    FSDirEntry sp34;
    int sp30;
    int sp2C;
    u16 sp28;
    u16 sp26;
    u16 sp24;
    u16 sp22;
    u16 sp20;
    u32 sp1C;
    FSDirEntry *temp_r29;
    u32 var_r28;
    DrvCtl *temp_r27;
    u16 status;

    sp76 = 1;
    sp74 = 1;
    sp24 = 1;
    sp22 = 1;
    sp20 = 0;
    sp1C = 0;

    temp_r27 = &FS_drv_ctl[pDriveInfo->nChan];

    status = FS_Search_Entry(pDriveInfo, arg2, spB8, sp78, &sp74, &sp34, &sp2C, &sp26, &sp22, 2);
    if (status == 0) {
        return 0xA011;
    }

    if ((sp22 == 0) && (sp74 != 1)) {
        return 0xA00F;
    }

    if (status != 0xA007) {
        return status;
    }

    status = FS_Search_Entry(pDriveInfo, arg1, spF8, &sp98[0], &sp76, &sp54, &sp30, &sp28, &sp24, 2);
    if (status != 0) {
        return status;
    }

    if (sp24 == sp22) {
        var_r28 = sp28;
        temp_r29 = PTR_ROOT_DIR_ENTRY(temp_r27, var_r28);
        status = FS_entry_name_set(temp_r29->DIR_Name, sp78[sp74 - 1]);
        if (status != 0) {
            return status;
        }

        status = FS_write_sub(0, 1, sp30, 0, pDriveInfo->unk_04, 0, pDriveInfo->nChan);
        if (status == 0) {
            status = FS_delete_lfn_entry(pDriveInfo, sp24, sp30, sp28);
        }

        if (sp54.DIR_Attr & FAT_ATTR_DIRECTORY) {
            pDriveInfo->unk_6C = 0;
            pDriveInfo->unk_70 = 0;
            pDriveInfo->unk_72 = 0;
            pDriveInfo->unk_74 = 0;
            FS_memset(pDriveInfo->unk_76, 0, sizeof(pDriveInfo->unk_76));
            FS_strncpy(pDriveInfo->unk_76, "\\", 1);
        }
    } else {
        if (sp54.DIR_Attr & FAT_ATTR_DIRECTORY) {
            return 0xA006;
        }

        if (sp74 == 1) {
            var_r28 = pDriveInfo->nSector;
        } else {
            var_r28 = FS_cluster_to_sector(pDriveInfo, sp22);
            if ((var_r28 + 0x10000) == 0xFFFF) {
                return 0xA032;
            }
        }

        status = FS_allocate_entry(pDriveInfo, var_r28, &sp1C, &sp20);
        if (status != 0) {
            return status;
        }

        var_r28 = sp20;
        temp_r29 = PTR_ROOT_DIR_ENTRY(temp_r27, var_r28);
        FS_memset(temp_r29, 0, sizeof(FSDirEntry));

        status = FS_entry_name_set(temp_r29->DIR_Name, sp78[sp74 - 1]);
        if (status == 0) {
            temp_r29->DIR_Attr = sp54.DIR_Attr;

            // sets DIR_NTRes, DIR_CrtTimeTenth, DIR_CrtTime, DIR_CrtDate, DIR_LstAccDate and DIR_FstClusHI
            FS_strncpy((char*)&temp_r29->DIR_NTRes, (char*)&sp54.DIR_NTRes, offsetof(FSDirEntry, DIR_WrtTime) - offsetof(FSDirEntry, DIR_NTRes));
            
            temp_r29->DIR_WrtTime.data_u8[0] = sp54.DIR_WrtTime.data_u16 >> 0;
            temp_r29->DIR_WrtTime.data_u8[1] = sp54.DIR_WrtTime.data_u16 >> 8;

            temp_r29->DIR_WrtDate.data_u8[0] = sp54.DIR_WrtDate.data_u16 >> 0;
            temp_r29->DIR_WrtDate.data_u8[1] = sp54.DIR_WrtDate.data_u16 >> 8;

            temp_r29->DIR_FstClusLO.data_u8[0] = sp54.DIR_FstClusLO.data_u16 >> 0;
            temp_r29->DIR_FstClusLO.data_u8[1] = sp54.DIR_FstClusLO.data_u16 >> 8;

            temp_r29->DIR_FileSize.data_u8[0] = sp54.DIR_FileSize.data_u32 >> 0;
            temp_r29->DIR_FileSize.data_u8[1] = sp54.DIR_FileSize.data_u32 >> 8;
            temp_r29->DIR_FileSize.data_u8[2] = sp54.DIR_FileSize.data_u32 >> 16;
            temp_r29->DIR_FileSize.data_u8[3] = sp54.DIR_FileSize.data_u32 >> 24;

            status = FS_write_sub(0, 1, sp1C, 0, pDriveInfo->unk_04, 0, pDriveInfo->nChan);
            if (status == 0) {
                status = FS_read_sub(0, 1, sp30, 0, pDriveInfo->unk_04, pDriveInfo->nChan);
                if (status == 0) {
                    var_r28 = sp28;
                    temp_r29 = PTR_ROOT_DIR_ENTRY(temp_r27, var_r28);
                    temp_r29->DIR_Name[0] = FAT_FLAG_DELETED;

                    status = FS_write_sub(0, 1, sp30, 0, pDriveInfo->unk_04, 0, pDriveInfo->nChan);
                    if (status == 0) {
                        status = FS_delete_lfn_entry(pDriveInfo, sp24, sp30, sp28);
                        if (status != 0) {
                            return status;
                        }
                    }
                }
            }
        }

        if (sp20 == 0) {
            status = FS_Flush(pDriveInfo);
        }
    }

    return status;
}
