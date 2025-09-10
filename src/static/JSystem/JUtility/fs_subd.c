#include "JSystem/JUtility/fs_subd.h"
#include "JSystem/JUtility/fs_drvsel.h"
#include "JSystem/JUtility/JUTSDCard.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_form.h"
#include "JSystem/JUtility/fs_sync.h"
#include "JSystem/JUtility/time.h"
#include "types.h"

u16 FS_get_space(SDDriveInfo* pDriveInfo, u16 nCluster, u16* param3) {
    u16 nCurCluster;
    u16 nNextCluster;
    u16 status;
    u16 sp16;
    u16 sp14;

    *param3 = 0xFFFF;

    if (nCluster == 1 || nCluster >= pDriveInfo->unk_BC) {
        return 0xA00C;
    }

    status = FS_FAT_onmemory_check(pDriveInfo);
    if (status != 0) {
        for (sp14 = pDriveInfo->unk_BE; sp14 < pDriveInfo->unk_BC; sp14++) {
            FS_get_fat_entry(pDriveInfo, sp14, &sp16);

            if (sp16 == 0) {
                goto block_20;
            }
        }

        for (sp14 = 2; sp14 < pDriveInfo->unk_BE; sp14++) {
            FS_get_fat_entry(pDriveInfo, sp14, &sp16);

            if (sp16 == 0) {
                goto block_20;
            }
        }
    } else {
        sp16 = pDriveInfo->unk_BE;
        status = FS_get_space_cache(pDriveInfo, sp16, pDriveInfo->unk_BC - 1, &sp14);

        if (status == 0) {
            goto block_20;
        } 

        if (status != 0xA012) {
            return status;
        }

        status = FS_get_space_cache(pDriveInfo, 2, sp16, &sp14);
        if (status == 0) {
            goto block_20;
        }

        if (status != 0xA012) {
            return status;
        }
    }

    return 0xA012;

block_20:
    *param3 = sp14;
    pDriveInfo->unk_BE = sp14;
    nCurCluster = nCluster;

    if (nCluster == 0) {
        status = FS_set_fat_entry(pDriveInfo, sp14, 0xFFFF);
        return status;
    }

    for (sp14 = 0; sp14 < pDriveInfo->unk_BC; sp14++) {
        nNextCluster = FS_get_next_cluster(pDriveInfo, nCurCluster);

        if (nNextCluster >= 0xFFF7 && nNextCluster < 0xFFFF) {
            return 0xA029;
        }

        if (nNextCluster == 0xFFFF) {
            status = FS_set_fat_entry(pDriveInfo, *param3, 0xFFFF);
            if (status != 0) {
                return status;
            }

            return FS_set_fat_entry(pDriveInfo, nCurCluster, *param3);
        }

        nCurCluster = nNextCluster;
    }

    return 0xA029;
}

extern u16 FS_find_fat_memory(SDDriveInfo* pDriveInfo, u16 param2, u16* param3, u16* param4);

// u16 FS_get_space_cache(SDDriveInfo* arg0, u16 arg1, u16 arg2, u16* arg3) {
//     u16 sp1A;
//     u16 sp18;
//     DrvCtl* sp14;
//     s32 temp_r28_2;
//     u16 temp_r24;
//     u16 temp_r3;
//     u16 temp_r3_2;
//     u16 temp_r3_3;
//     u16 var_r0;
//     u16 var_r0_2;
//     u16 var_r25;
//     u16 var_r29;
//     u16 var_r30;
//     u16 var_r30_2;
//     u32 temp_r21;
//     u32 temp_r28;
//     void* temp_r27;

//     sp14 = &FS_drv_ctl[arg0->nChan];

//     if (arg1 < 2) {
//         var_r25 = 2;
//     } else {
//         var_r25 = arg1;
//     }

//     if (var_r25 > arg2) {
//         return 0xA00C;
//     }

//     for (; var_r25 < arg2; var_r25 = var_r29) {
//         temp_r3_3 = FS_find_fat_memory(arg0, var_r25, &sp1A, &sp18);
//         if (temp_r3_3 != 0) {
//             return temp_r3_3;
//         }

//         temp_r21 = arg0->unk_1C * (*(arg0->unk_EC + ((sp1A * 2) + 0x60C)) + *(arg0->unk_EC + ((sp1A * 2) + 0x810)));
//         if ((u16) arg0->unk_3C == 1) {
//             var_r29 = (u16) (temp_r21 >> 1);
//         } else {
//             var_r29 = (u16) ((u32) ((temp_r21 * 2) + 2) / 3);
//         }

//         if ((s32) var_r29 > (s32) (arg2 + 1)) {
//             var_r29 = arg2 + 1;
//         }

//         if ((u16) arg0->unk_3C == 1) {
//             temp_r24 = (u16) ((u32) (*(arg0->unk_EC + ((sp1A * 2) + 0x60C)) * arg0->unk_1C) >> 1);
//             var_r30 = var_r25 - temp_r24;

//             while (var_r30 < (u16) (var_r29 - temp_r24)) {
//                 if ((u16) *(*(arg0->unk_EC + (sp1A * 4)) + ((var_r30 * 2) & 0x1FFFE)) == 0) {
//                     *arg3 = var_r30 + temp_r24;
//                     return 0;
//                 }

//                 var_r30++;
//             }

//             continue;
//         }

//         temp_r27 = *(arg0->unk_EC + (sp1A * 4));

//         var_r30_2 = var_r25;
//         while ((s32) var_r30_2 < (s32) (var_r29 - 1)) {
//             temp_r28_2 = ((u32) (var_r30_2 * 3) >> 1) - (*(arg0->unk_EC + ((sp1A * 2) + 0x60C)) * arg0->unk_1C);
//             if ((var_r30_2 % 2) != 0) {
//                 var_r0_2 = (((u8) *(temp_r27 + temp_r28_2) >> 4) & 0xF & ~0xFF0) | ((*(temp_r27 + (temp_r28_2 + 1)) << 4) & 0xFF0);
//             } else {
//                 var_r0_2 = ((u8) *(temp_r27 + temp_r28_2) & ~0xF00) | ((*(temp_r27 + (temp_r28_2 + 1)) << 8) & 0xF00);
//             }

//             if (var_r0_2 == 0) {
//                 *arg3 = var_r30_2;
//                 return 0;
//             }

//             var_r30_2++;
//         }

//         temp_r28 = ((u32) (var_r30_2 * 3) >> 1) - (*(arg0->unk_EC + ((sp1A * 2) + 0x60C)) * arg0->unk_1C);
//         if (temp_r28 != (u32) ((*(arg0->unk_EC + ((sp1A * 2) + 0x810)) * arg0->unk_1C) - 1)) {
//             if ((var_r30_2 % 2) != 0) {
//                 var_r0 = (((u8) *(temp_r27 + temp_r28) >> 4) & 0xF & ~0xFF0) | ((*(temp_r27 + (temp_r28 + 1)) << 4) & 0xFF0);
//             } else {
//                 var_r0 = ((u8) *(temp_r27 + temp_r28) & ~0xF00) | ((*(temp_r27 + (temp_r28 + 1)) << 8) & 0xF00);
//             }

//             if (var_r0 == 0) {
//                 *arg3 = var_r30_2;
//                 return 0;
//             }
//         } else if (((var_r29 - 1) % 2) != 0) {
//             if (!(temp_r27->unk1FF & 0xF0)) {
//                 temp_r3_2 = FS_find_fat_memory(arg0, var_r29 - 1, &sp1A, &sp18);
//                 if (temp_r3_2 != 0) {
//                     return temp_r3_2;
//                 }

//                 if (sp18 == -1) {
//                     return 0xA02D;
//                 }

//                 if ((u8) **(arg0->unk_EC + (sp18 * 4)) == 0) {
//                     *arg3 = var_r29 - 1;
//                     return 0;
//                 }
//             }
//         } else if ((u8) temp_r27->unk1FF == 0) {
//             temp_r3 = FS_find_fat_memory(arg0, var_r29 - 1, &sp1A, &sp18);
//             if (temp_r3 != 0) {
//                 return temp_r3;
//             }

//             if (sp18 == -1) {
//                 return 0xA02D;
//             }

//             if (!(**(arg0->unk_EC + (sp18 * 4)) & 0xF)) {
//                 *arg3 = var_r29 - 1;
//                 return 0;
//             }
//         }
//     }

//     return 0xA012;
// }

u16 FS_fat_clear(u16 param2, SDDriveInfo* pDriveInfo) {
    DrvCtl* sp10;
    u16 temp_r3_2;
    u16 var_r28;
    u16 var_r29;
    u16 status;

    sp10 = &FS_drv_ctl[pDriveInfo->nChan];

    if (param2 < 2 || param2 >= pDriveInfo->unk_BC) {
        return 0xA00C;
    }

    var_r29 = param2;

    for (var_r28 = 0; var_r28 < 0xFFFF; var_r28++) {
        temp_r3_2 = FS_get_next_cluster(pDriveInfo, var_r29);

        if (temp_r3_2 >= 0xFFF7 && temp_r3_2 < 0xFFFF) {
            break;
        }

        status = FS_set_fat_entry(pDriveInfo, var_r29, 0);

        if (status != 0) {
            return status;
        }

        if (temp_r3_2 == 0xFFFF) {
            return FS_fat_sync(pDriveInfo);
        }

        var_r29 = temp_r3_2;
    }

    return 0xA029;
}

u16 FS_Flush(SDDriveInfo* pDriveInfo) {
    return FS_Sync_sub(pDriveInfo);
}

u16 FS_get_entry(SDDriveInfo* pDriveInfo, char* param2, char* param3, u16 param4, void* param5, void* param6, void* param7) {}
u16 FS_allocate_entry(SDDriveInfo* pDriveInfo, int param1, int* param2, u16* param3) {}

u16 FS_delete_lfn_entry(SDDriveInfo* pDriveInfo, u32 param1, int param2, u16 param3) {
    FSPartitionBootSector* var_r26;
    DrvCtl* temp_r24;
    u32 var_r30;
    u16 var_r22;
    u16 var_r23;
    u32 var_r27;
    u16 var_r29;
    u16 status;
    u32 temp_r3;
    u32 temp_r3_2;

    var_r29 = 1;
    temp_r24 = &FS_drv_ctl[pDriveInfo->nChan];

    var_r26 = PTR_BOOT_SECTOR_ENTRY(temp_r24, param3);
    var_r30 = param2;
    var_r22 = 0;

    while (var_r22 < 0x15) {
        if (var_r22 != 0) {
            if (var_r26->FAT16.BS_jmpBoot[0] == 0xE5 || (var_r26->FAT16.BPB_BytsPerSec.data_u8[0] & 0x3F) != 0x0F) {
                break;
            }

            var_r26->FAT16.BS_jmpBoot[0] = 0xE5;
        }

        if (var_r26 == (FSPartitionBootSector*)temp_r24->ctrl_p.unk_20BA4) {
            if (var_r30 < pDriveInfo->unk_64) {
                if (var_r30 == pDriveInfo->nSector) {
                    break;
                }

                var_r30--;
            } else {
                temp_r3_2 = FS_sector_to_cluster(pDriveInfo, var_r30);
                temp_r3 = FS_cluster_to_sector(pDriveInfo, temp_r3_2);

                if (temp_r3_2 == 0xFFFFFFFF) {
                    break;
                }

                if (temp_r3_2 != var_r30) {
                    var_r30--;
                } else {
                    temp_r3_2 = FS_get_previous_cluster(pDriveInfo, param1, temp_r3_2);

                    if (temp_r3_2 >= 0xFFF7) {
                        break;
                    }
                    
                    temp_r3 = FS_cluster_to_sector(pDriveInfo, temp_r3);

                    if (temp_r3 >= 0xFFF7) {
                        break;
                    }

                    var_r30 = pDriveInfo->unk_1E[temp_r3 - 1];
                }

                if ((var_r27 == (u32) (var_r30 - 1)) && (var_r29 < 0x20)) {
                    for (var_r23 = 0; var_r23 < var_r29; var_r23++) {
                        // FS_strncpy(temp_r24 + (((var_r29 - var_r23) << 9) + 0x20BA4), temp_r24 + ((((var_r29 - var_r23) - 1) << 9) + 0x20BA4), 0x200);
                        FS_strncpy((char*)&temp_r24->ctrl_p.unk_20BA4[((var_r29 - var_r23) * sizeof(FSPartitionBootSector))], (char*)&temp_r24->ctrl_p.unk_20BA4[((var_r29 - var_r23 - 1) * sizeof(FSPartitionBootSector))], sizeof(FSPartitionBootSector));
                    }
                } else {
                    status = FS_write_sub(NULL, var_r29, var_r30, NULL, pDriveInfo->unk_04, 0, pDriveInfo->nChan);
                    if (status != 0) {
                        return status;
                    }

                    var_r29 = 0;
                }

                status = FS_read_sub(NULL, 1, temp_r3, NULL, pDriveInfo->unk_04, pDriveInfo->nChan);
                if (status != 0) {
                    return status;
                }

                var_r30 = var_r27;
                var_r26 = (FSPartitionBootSector*)&temp_r24->ctrl_p.unk_20BA4[sizeof(FSPartitionBootSector) * 1];
                var_r29++;
            }
        }

    block_27:
        var_r22++;
        var_r26--;
    }

    status = FS_write_sub(NULL, var_r29, var_r30, NULL, pDriveInfo->unk_04, 0, pDriveInfo->nChan);
    return status;
}

u32 FS_set_now_date(FSDirEntry *param1, void *param2) {
    NowData sp10;
    u16 temp_r30;
    u16 status;

    FS_memset(&sp10, 0, sizeof(NowData));

    if (param2 == NULL) {
        status = GetNowData(&sp10);

        if (status != 0) {
            param1->DIR_WrtTime.data_u16 = 0;
            param1->DIR_WrtDate.data_u16 = 0;
            return 0xA041;
        }
    } else {
        // ?
        FS_strncpy((char*)&sp10, param2, sizeof(NowData));
    }

    if (sp10.year < 1980 || sp10.year > 2107 || sp10.mon < 1 || sp10.mon > 12 || sp10.mday < 1 || sp10.mday > 31 || sp10.hour > 23 || sp10.min > 59 || sp10.sec > 59) {
        param1->DIR_WrtTime.data_u16 = 0;
        param1->DIR_WrtDate.data_u16 = 0;
        return 0xA041;
    }

    temp_r30 = (sp10.hour << 11) + (sp10.min << 5) + (sp10.sec / 2);
    param1->DIR_WrtTime.data_u8[0] = temp_r30;
    param1->DIR_WrtTime.data_u8[1] = temp_r30 >> 8;

    temp_r30 = ((sp10.year - 1980) << 9) + (sp10.mon << 5) + sp10.mday;
    param1->DIR_WrtDate.data_u8[0] = temp_r30;
    param1->DIR_WrtDate.data_u8[1] = temp_r30 >> 8;
    return 0;
}

u16 FS_open_check_parent(SDDriveInfo *pDriveInfo, char* param2) {
    UnkStruct_20A00 *var_r28;
    SDFileInfo *var_r27;
    DrvCtl *pDrvCtl;
    u16 nArrayCount;
    u16 var_r31;
    u16 var_r30;
    u16 var_r29;

    pDrvCtl = &FS_drv_ctl[pDriveInfo->nChan];

    nArrayCount = pDriveInfo->unk_04 == 1 ? ARRAY_COUNT(pDrvCtl->unk_210) : ARRAY_COUNT(pDrvCtl->unk_47C);
    for (var_r30 = 0; var_r30 < nArrayCount; var_r30++) {
        if (pDriveInfo->unk_04 == 1) {
            var_r27 = &pDrvCtl->unk_210[var_r30];
        } else {
            var_r27 = &pDrvCtl->unk_47C[var_r30];
        }

        if (var_r27->pDriveInfo != NULL) {
            for (var_r31 = 0; var_r31 < ARRAY_COUNT(var_r27->path); var_r31++) {
                if (param2[var_r31] == '\0') {
                    if (var_r27->path[var_r31] == '\0') {
                        return 0xA018;
                    }

                    break;
                }

                if (var_r27->path[var_r31] != param2[var_r31]) {
                    break;
                }
            }
        }
    }

    nArrayCount = pDriveInfo->unk_04 == 1 ? ARRAY_COUNT(pDrvCtl->ctrl_p.unk_20A00) : ARRAY_COUNT(pDrvCtl->ctrl_p.unk_20AFC);
    for (var_r30 = 0; var_r30 < nArrayCount; var_r30++) {
        if (pDriveInfo->unk_04 == 1) {
            var_r28 = &pDrvCtl->ctrl_p.unk_20A00[var_r30];
        } else {
            var_r28 = &pDrvCtl->ctrl_p.unk_20AFC[var_r30];
        }

        if (var_r28->pDriveInfo != NULL) {
            for (var_r31 = 0; var_r31 < ARRAY_COUNT(var_r28->unk_14); var_r31++) {
                if (param2[var_r31] == '\0') {
                    if (var_r28->unk_14[var_r31] == '\0') {
                        return 0xA018;
                    }

                    break;
                } 

                if (var_r28->unk_14[var_r31] == '\0') {
                    if (param2[var_r31] == '\\') {
                        for (var_r29 = var_r31 + 1; var_r29 < 64; var_r29++) {
                            if (param2[var_r29] == '\\') {
                                break;
                            }

                            if (param2[var_r29] == '\0') {
                                return 0xA02F;
                            }
                        }

                        break;
                    }
                    
                    if (var_r31 == 1 && var_r28->unk_14[0] == '\\') {
                        for (var_r29 = 1; var_r29 < 64; var_r29++) {
                            if (param2[var_r29] == '\\') {
                                break;
                            }

                            if (param2[var_r29] == '\0') {
                                return 0xA02F;
                            }

                        }
                    }

                    break;
                }

                if (var_r28->unk_14[var_r31] != param2[var_r31]) {
                    break;
                }
            }
        }
    }

    return 0;
}

u16 FS_open_check_all(SDDriveInfo *pDriveInfo, char* param2) {
    DrvCtl *pDrvCtl;
    SDFileInfo *var_r28;
    UnkStruct_20A00 *var_r29;
    u16 nArrayCount;
    u16 var_r30;
    u16 var_r31;

    pDrvCtl = &FS_drv_ctl[pDriveInfo->nChan];

    nArrayCount = pDriveInfo->unk_04 == 1 ? ARRAY_COUNT(pDrvCtl->unk_210) : ARRAY_COUNT(pDrvCtl->unk_47C);
    for (var_r30 = 0; var_r30 < nArrayCount; var_r30++) {
        if (pDriveInfo->unk_04 == 1) {
            var_r28 = &pDrvCtl->unk_210[var_r30];
        } else {
            var_r28 = &pDrvCtl->unk_47C[var_r30];
        }

        if (var_r28->pDriveInfo != NULL) {
            for (var_r31 = 0; var_r31 < ARRAY_COUNT(var_r28->path); var_r31++) {
                if (param2[var_r31] == '\0') {
                    if (var_r28->path[var_r31] == '\0') {
                        return 0xA009;
                    }

                    if (var_r28->path[var_r31] == '\\') {
                        return 0xA009;
                    }

                    break;
                }

                if (var_r28->path[var_r31] != param2[var_r31]) {
                    break;
                }
            }
        }
    }

    nArrayCount = pDriveInfo->unk_04 == 1 ? ARRAY_COUNT(pDrvCtl->ctrl_p.unk_20A00) : ARRAY_COUNT(pDrvCtl->ctrl_p.unk_20AFC);
    for (var_r30 = 0; var_r30 < nArrayCount; var_r30++) {
        if (pDriveInfo->unk_04 == 1) {
            var_r29 = &pDrvCtl->ctrl_p.unk_20A00[var_r30];
        } else {
            var_r29 = &pDrvCtl->ctrl_p.unk_20AFC[var_r30];
        }

        if (var_r29->pDriveInfo != NULL) {
            for (var_r31 = 0; var_r31 < ARRAY_COUNT(var_r29->unk_14); var_r31++) {
                if (param2[var_r31] == '\0') {
                    if (var_r29->unk_14[var_r31] == '\0') {
                        return 0xA02F;
                    }

                    if (var_r29->unk_14[var_r31] == '\\') {
                        return 0xA02F;
                    }

                    break;
                }

                if (var_r29->unk_14[var_r31] == '\0') {
                    if (param2[var_r31] == '\\') {
                        return 0xA02F;
                    }

                    if (var_r31 == 1 && var_r29->unk_14[0] == '\\') {
                        return 0xA02F;
                    }
                }

                if (var_r29->unk_14[var_r31] != param2[var_r31]) {
                    break;
                }
            }
        }
    }

    return 0;
}

u16 FS_get_next_cluster(SDDriveInfo *pDriveInfo, u16 param2) {
    u16 status;
    u16 spE;

    if (param2 < 2 || param2 >= pDriveInfo->unk_BC) {
        return 0xFFFD;
    }

    status = FS_get_fat_entry(pDriveInfo, param2, &spE);

    if (status != 0) {
        return 0xFFFE;
    }

    if (spE >= 2 && spE < pDriveInfo->unk_BC) {
        return spE;
    }

    if (pDriveInfo->unk_3C == 1) {
        if (spE == 0xFFF7) {
            return 0xFFF7;
        }
        if (spE >= 0xFFF8 && spE <= 0xFFFF) {
            return 0xFFFF;
        }
        return 0xFFFE;
    }

    if (spE == 0xFF7) {
        return 0xFFF7;
    }

    if (spE >= 0xFF8 && spE <= 0xFFF) {
        return 0xFFFF;
    }

    return 0xFFFE;
}

u32 FS_get_previous_cluster(SDDriveInfo *pDriveInfo, u16 param2, u16 param3) {
    u16 var_r29;
    u16 var_r31;
    u16 status;
    u16 sp10;

    if (param2 < 2 || param2 >= pDriveInfo->unk_BC) {
        return 0xFFFD;
    }

    if (param3 < 2 || param3 >= pDriveInfo->unk_BC) {
        return 0xFFFD;
    }

    if (param2 == param3) {
        return 0xFFFD;
    }

    var_r31 = param2;

    if (pDriveInfo->unk_3C == 1) {
        for (var_r29 = 0; var_r29 < 0xFFFF; var_r29++) {
            status = FS_get_fat_entry(pDriveInfo, var_r31, &sp10);
            if (status != 0) {
                return 0xFFFE;
            }

            if (sp10 == param3) {
                return var_r31;
            }

            if (sp10 == 0xFFF7) {
                return 0xFFF7;
            }

            if (sp10 >= 0xFFF8 && sp10 <= 0xFFFF) {
                return 0xFFFF;
            }

            if (sp10 < 2 || sp10 >= pDriveInfo->unk_BC) {
                return 0xFFFE;
            }

            var_r31 = sp10;
        }

        return 0xFFFE;
    }

    for (var_r29 = 0; var_r29 < 0xFFFF; var_r29++) {
        status = FS_get_fat_entry(pDriveInfo, var_r31, &sp10);
        if (status != 0) {
            return 0xFFFE;
        }

        if (sp10 == param3) {
            return var_r31;
        }

        if (sp10 == 0xFF7) {
            return 0xFFF7;
        }

        if (sp10 >= 0xFF8 && sp10 <= 0xFFF) {
            return 0xFFFF;
        }

        if (sp10 < 2 || sp10 >= pDriveInfo->unk_BC) {
            return 0xFFFE;
        }

        var_r31 = sp10;
    }

    return 0xFFFE;
}

u32 FS_sector_to_cluster(SDDriveInfo *pDriveInfo, u32 param2) {
    u32 nCluster;

    if (param2 < pDriveInfo->unk_64) {
        return 0xFFFF;
    }

    if (param2 >= pDriveInfo->unk_68) {
        return 0xFFFF;
    }

    nCluster = ((param2 - pDriveInfo->unk_64) / pDriveInfo->unk_1E[0]) + 2;
    return nCluster & 0xFFFF;
}

u32 FS_cluster_to_sector(SDDriveInfo* pDriveInfo, u32 param2) {
    u32 nSector;

    if ((param2 & 0xFFFF) < 2) {
        return -1;
    }

    nSector = pDriveInfo->unk_64 + (((param2 & 0xFFFF) - 2) * pDriveInfo->unk_1E[0]);

    if (nSector >= pDriveInfo->unk_68) {
        return -1;
    }

    return nSector;
}

u16 FS_read_sub(u8* param1, int param2, u32 param3, UnknownStruct1* param4, u16 param5, u16 param6) {}

u16 FS_write_sub(u8* param1, int param2, u32 param3, UnknownStruct1* param4, u16 param5, u16 param6, u16 nChan) {
    DrvCtl* pDrvCtl;
    u16 status;
    u16 sp1E;

    pDrvCtl = &FS_drv_ctl[nChan];

    if (param5 != 1 && param5 != 2) {
        return 0xA016;
    }

    if (param4 == NULL) {
        param4 = &pDrvCtl->ctrl_p.unk_24BA4;
    }

    if (param1 == NULL) {
        param1 = pDrvCtl->ctrl_p.unk_20BA4;
    }

    param4->unk_00 = 0x2000;
    param4->unk_02 = 0;
    param4->unk_04 = 0;

    if (param5 == 1) {
        if (pDrvCtl->unk_08[0].unk_06 == 2 && pDrvCtl->unk_08[0].unk_FC < (param3 + param2)) {
            return 0xA023;
        }
    } else {
        if (pDrvCtl->unk_08[1].unk_06 == 2 && pDrvCtl->unk_08[1].unk_FC < (param3 + param2)) {
            return 0xA023;
        }
    }

    if (param5 == 1) {
        status = FS_DrvSel_Write(param1, param2, param3, 0, param4, pDrvCtl->unk_00[1]);
    } else {
        sp1E = param6;
        status = 0xA047;
    }

    return status;
}

u16 FS_csd_to_size(u32 *outSectorsPerCluster, s32 *outCsdBlockMultiplier, u16 modeFlags, u16 arg3, u16 chan) {
    s32 blockMultiplier;
    u32 i;
    DrvCtl* pDrvCtl;
    SDInfos rawCsdInfo;
    SDInfos csdInfo;
    u16 status;
    u16 sp16;
    u32 read_bl_len;
    u32 c_size;
    u32 c_size_mult;
    u32 max;
    u32 size;
    s32 t0;

    pDrvCtl = &FS_drv_ctl[chan];
    sp16 = arg3;

    // these are probably used somewhere in assert calls or something
    (void)read_bl_len;
    (void)c_size;
    (void)c_size_mult;
    (void)t0;

    if (modeFlags & FS_SD_CARD_MODE_RAW) {
        *outSectorsPerCluster = 0xF28 * 0x20; // 0x1E500
        *outCsdBlockMultiplier = 0x20;
    } else {
        *outSectorsPerCluster = 0xA0 * 0x08; // 0x500
        *outCsdBlockMultiplier = 0x20;
    }

    status = FS_DrvSel_Getinfo(&rawCsdInfo, pDrvCtl->unk_00[1]);

    // byte swap CSD register data I guess?
    i = 0;
    while (i < ARRAY_COUNT(csdInfo.data)) {
        csdInfo.data[i] = rawCsdInfo.data[0x1F - i];
        i++;
    }

    read_bl_len = ((u16)(csdInfo.data[12] & 3) << 2) | ((u16)(csdInfo.data[13] & (3 << 6)) >> 6);
    c_size = ((u16)(csdInfo.data[6] & (3 << 0)) << 10) | ((u16)(csdInfo.data[7] << 2)) | ((u16)(csdInfo.data[8] & (3 << 6)) >> 6);
    c_size_mult = ((u16)(csdInfo.data[9] & (3 << 0)) << 1) | ((u16)(csdInfo.data[10] & (1 << 7)) >> 7); // r23
    size = 1 + (c_size & 0xFFFF); // these are actually the 'total blocks' until the later multiplication step
    
    max = c_size_mult & 0xFFFF;
    blockMultiplier = 2;
    i = 0;
    while (i < (max + 1)) {
        blockMultiplier <<= 1;
        i++;
    }

    max = read_bl_len & 0xFFFF;
    t0 = 2;
    i = 0;
    while (i < max - 1) {
        t0 <<= 1;
        i++;
    }

    max = blockMultiplier;
    size *= max;

    if (modeFlags & FS_SD_CARD_MODE_RAW) {
        // Get the raw card size
        *outSectorsPerCluster = size;
        *outCsdBlockMultiplier = blockMultiplier;
    } else {
        // Chose an optimal cluster size for a given card size.
        // Larger capacity cards perform better with a larger minimum cluster size for files.
        if (size <= 0x1F60) {
            *outSectorsPerCluster = 0xA0; // 4MB card
        } else if (size <= 0x3F60) {
            *outSectorsPerCluster = 0xA0; // 8MB card
        } else if (size <= 0x7EC0) {
            *outSectorsPerCluster = 0xA0 * 0x02; // 16MB card
        } else if (size <= 0xFD80) {
            *outSectorsPerCluster = 0xA0 * 0x04; // 32MB card
        } else if (size <= 0x1F3E4) {
            *outSectorsPerCluster = 0xA0 * 0x08; // 64MB card
        } else if (size <= 0x3F600) {
            *outSectorsPerCluster = 0xA0 * 0x10; // 128MB card
        } else if (size <= 0x7EC0A) {
            *outSectorsPerCluster = 0xA0 * 0x20; // 256MB card
        } else if (size <= 0xFD800) {
            *outSectorsPerCluster = 0xA0 * 0x40; // 512MB card
        } else if (size <= 0x1FB000) {
            *outSectorsPerCluster = 0xA0 * 0x80; // 1GB card
        } else if (size <= 0x3F6000) {
            *outSectorsPerCluster = 0xA0 * 0x100; // 2GB card
        }

        *outCsdBlockMultiplier = blockMultiplier;
    }

    return 0;
}

u16 FS_divide_fpathname(char* param1, char** param2, u16* param3, u16 param4) {
    DrvCtl *sp18;
    u16 var_r30;
    u16 var_r31;

    var_r30 = 0;
    var_r31 = 0;
    sp18 = &FS_drv_ctl[param4];
    *param3 = 0;

    if (param1[0] != '\\') {
        return 0xA02C;
    }

    while (param1[0] != '\0') {
        if (var_r30 > 8 && var_r31 == 0) {
            return 0xA02C;
        }

        if (var_r31 > 4) {
            return 0xA02C;
        }

        if (param1[0] == '\\') {
            var_r30 = 0;
            var_r31 = 0;
            param1[0] = '\0';

            if ((param1++)[1] != '\0' && param1[0] != '\\') {
                (*param3)++;

                if (*param3 > 8) {
                    return 0xA013;
                }

                *param2 = param1;
                param2++;
            }
        } else {
            if (param1[0] == '.') {
                if (var_r31 != 0) {
                    return 0xA02C;
                }

                if (var_r30 == 0) {
                    return 0xA02C;
                }

                var_r31 = 1;
            } else {
                if (var_r31 != 0) {
                    var_r31++;
                } else {
                    var_r30++;
                }
            }

            param1++;
        }
    }

    if (var_r30 > 8 || var_r31 > 4) {
        return 0xA02C;
    }

    return 0;
}

// params not sure
u16 FS_fat_strcmp(UnkStruct_20BA4 *arg0, UnkStruct_20BA4 *arg1) {
    u16 var_r31 = 0;

    while (var_r31 < 5) {
        //! TODO: u16 vs u8 oddity, see `FS_Delete_Entry`
        if (((u16*)arg0->unk_00)[var_r31] != ((u16*)arg1->unk_00)[var_r31]) {
            return 0xA02B;
        }

        var_r31++;
    }

    if (arg0->unk_0A != arg1->unk_0A) {
        return 0xA02B;
    }

    return 0;
}

u16 FS_entry_name_set(char* param1, char* param2) {
    u16 var_r31;
    u16 var_r30;

    var_r31 = 0;
    while (var_r31 < 9) {
        if (param2[var_r31] == '\0' || param2[var_r31] == '.') {
            if (var_r31 == 0) {
                return 0xA02C;
            }

            var_r30 = var_r31;

            while (var_r30 < 8) {
                param1[var_r30] = ' ';
                var_r30++;
            }

            if (param2[var_r31] == '\0') {
                while (var_r30 < 0xB) {
                    param1[var_r30] = ' ';
                    var_r30++;
                }

                return 0;
            }

            var_r31++;
            break;
        }

        if (var_r31 == 8) {
            return 0xA02C;
        }

        param1[var_r31] = param2[var_r31];
        var_r31++;
    }

    var_r30 = 8;
    while (var_r30 < 0xC) {
        if (param2[var_r31] == '.') {
            return 0xA02C;
        }

        if (param2[var_r31] == '\0') {
            if (var_r30 == 8) {
                return 0xA02C;
            }

            while (var_r30 < 0xB) {
                param1[var_r30] = ' ';
                var_r30++;
            }

            return 0;
        }

        if (var_r30 == 0xB) {
            return 0xA02C;
        }

        param1[var_r30] = param2[var_r31];
        var_r30++;
        var_r31++;
    }

    return 0xA02C;
}

void FS_entname_to_stdname(char* param1) {
    char spC[12];
    u16 var_r29;
    u16 var_r30;
    u16 var_r31;

    FS_memset(spC, 0, sizeof(spC));
    var_r30 = 0;
    var_r31 = 11;

    while (var_r31 > 8) {
        if (param1[var_r31 - 1] != ' ') {
            var_r29 = var_r31;
            while (var_r29 > 8) {
                spC[var_r30] = param1[var_r29 - 1];
                var_r29--;
                var_r30++;
            }

            spC[var_r30] = '.';
            var_r30++;
            break;
        }

        var_r31--;
    }

    var_r31 = 8;
    while (var_r31 != 0) {
        if (param1[var_r31 - 1] != ' ') {
            var_r29 = var_r31;
            while (var_r29 != 0) {
                spC[var_r30] = param1[var_r29 - 1];
                var_r29--;
                var_r30++;
            }

            break;
        }

        var_r31--;
    }

    if (var_r30 == 0) {
        var_r29 = 0;
        while (var_r29 < 8) {
            spC[var_r30] = ' ';
            var_r29++;
            var_r30++;
        }
    }

    var_r31 = 0;
    while (var_r31 < var_r30) {
        param1[var_r31] = spC[var_r30 - var_r31 - 1];
        var_r31++;
    }

    param1[var_r31] ='\0';
}

u16 FS_uchar_to_dchar(char* param1) {
    char spC[64];
    u16 var_r29;
    u16 var_r28;
    u16 var_r31;
    size_t var_r30;

    var_r28 = 0;
    var_r30 = FS_strlen(param1);

    if (var_r30 > sizeof(spC) - 1) {
        return 0xA017;
    }

    if (var_r30 > (u16)-1) {
        return 0xA017;
    }

    FS_strcpy(spC, param1);
    FS_toupper(spC);

    var_r31 = 0;

    while (var_r31 < (u16)var_r30) {
        switch (spC[var_r31]) {
            case ' ':
            case '\\':
                if (var_r28 != 0) {
                    var_r29 = var_r31;

                    while (var_r29 < (u16)var_r30) {
                        spC[var_r29] = spC[var_r29 + 1];
                        var_r29++;
                    }

                    var_r31--;
                    var_r30--;
                }

                if (spC[var_r31] == '\\') {
                    var_r28 = 1;
                }
                break;
            default:
                var_r28 = 0;
                break;
        }

        var_r31++;
    }

    if (var_r31 > 1 && var_r28 != 0) {
        spC[var_r30 - 1] = '\0';
    }

    FS_strcpy(param1, spC);
    return 0;
}

void FS_toupper(char *param1) {
    char* pChar = param1;
    int i;

    for (i = 0; i < FS_strlen(param1); i++) {
        // pChar[i] >= 'a' && pChar[i] <= 'z'
        if (pChar[i] > 0x60 && pChar[i] < 0x7B) {
            pChar[i] -= 0x20;
        }
    }
}

void *FS_memset(void *dest, u16 ch, size_t count) {
    size_t var_r31;
    u32 var_r30;
    u8 *var_r29;
    u32 *var_r27;
    u8 *var_r28;
    s32 var_r26;

    var_r29 = dest;
    var_r31 = count;


    while (((u32) var_r29 & 3) && var_r31 != 0) {
        *var_r29++ = ch;
        var_r31--;
    }

    if (var_r31 > 4) {
        var_r26 = (ch + (ch << 8));
        var_r26 += var_r26 << 0x10;

        for (var_r27 = (u32*)var_r29, var_r30 = 0; var_r30 < (var_r31 >> 2); var_r30++, var_r27++) {
            *var_r27 = var_r26;
        }
    
        var_r29 = (u8*)var_r27;
        var_r31 -= var_r30 * 4;
    }

    if (var_r31 != 0) {
        var_r28 = var_r29;

        (void)var_r28;
        (void)var_r28;

        for (var_r30 = 0; var_r30 < var_r31; var_r30++, var_r28++) {
            *var_r28 = ch;
        }
    }

    return dest;
}

char *FS_strcpy(char *dest, const char *src) {
    size_t var_r31 = 0;

    while (var_r31 < -1) {
        dest[var_r31] = src[var_r31];

        if (src[var_r31] != '\0') {
            var_r31++;
            continue;
        }

        break;
    }

    return dest;
}

char *FS_strncpy(char *dest, const char *src, size_t num) {
    char *var_r26;
    char *var_r27;
    char *var_r30;
    char *var_r31;
    u32 var_r28;
    u32 var_r29;

    (void)var_r31;
    (void)var_r31;
    (void)var_r27;
    (void)var_r27;

    if (num != 0) {
        var_r31 = dest;
        var_r30 = (char*)src;
        var_r28 = num;

        if (((s32) dest & 1) && ((s32) var_r30 & 1)) {
            *var_r31 = *var_r30;
            var_r31++;
            var_r30++;
            var_r28--;
        } else if (((s32) var_r31 & 1) || ((s32) var_r30 & 1)) {
            var_r29 = 0;

            while (var_r29 < var_r28) {
                *var_r31 = *var_r30;
                var_r29++;
                var_r31++;
                var_r30++;
            }

            return dest;
        }

        if (var_r28 > 4) {
            var_r27 = var_r31;
            var_r26 = var_r30;
            var_r29 = 0;

            while (var_r29 < (u32) (var_r28 >> 2)) {
                *((s32*)var_r27) = *((s32*)var_r26);
                var_r29++;
                var_r27 += 4;
                var_r26 += 4;
            }

            var_r31 = var_r27;
            var_r30 = var_r26;
            var_r28 -= var_r29 * 4;
        }

        if (var_r28 != 0) {
            var_r29 = 0;

            while (var_r29 < var_r28) {
                *var_r31 = *var_r30;
                var_r29++;
                var_r31++;
                var_r30++;
            }
        }
    }

    return dest;
}

size_t FS_strlen(const char *s) {
    const char* pChar = s;
    size_t length;

    for (length = 0; length < -1; length++) {
        if (pChar[length] == '\0') {
            return length;
        }
    }

    return -1;
}

u16 FS_strncmp(const char *s1, const char *s2, size_t n) {
    int i;

    for (i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return -1;
        }
    }

    return 0;
}

void FS_srand(u16 param1, u16 param2) {
    DrvCtl *temp_r31;

    temp_r31 = &FS_drv_ctl[param2];
    temp_r31->unk_259D8 = param1;
    temp_r31->unk_259DC = 1;
}

u16 FS_rand(u16 param1, u16 param2) {
    DrvCtl *temp_r31;

    temp_r31 = &FS_drv_ctl[param2];
    temp_r31->unk_259DC = 1;
    temp_r31->unk_259D8 = (temp_r31->unk_259D8 * 0x60C98293) + 0x3039;
    return (temp_r31->unk_259D8 % (param1 + 1));
}
