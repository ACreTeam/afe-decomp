#include "JSystem/JUtility/fs_renm.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_open.h"
#include "JSystem/JUtility/fs_subd.h"
#include "types.h"

u16 FS_Rename(FSFile* pFile, char* arg1, char* arg2) {
    u16 status;
    DrvCtl* ptr;

    if (pFile == NULL || arg1 == NULL || arg2 == NULL) {
        return 0xA00C;
    } else if (pFile->unk_04[1] != 2) {
        return 0xA003;
    } else if (pFile->unk_04[0] != 1) {
        return 0xA016;
    }

    ptr = &FS_drv_ctl[pFile->unk_00[0]];

    if (pFile->unk_00 != ptr->unk_08) {
        return 0xA00C;
    }

    status = FS_Rename_sub(pFile, arg1, arg2);
    return status;
}

typedef struct TESTTESTTEST {
    char unk_00[11];
    u8 unk_0B;
} TESTTESTTEST;

typedef struct TESTTESTTEST2 {
    char pad[11];
    u8 unk_0B;
    char unk_0C[10];
    char unk_16[32];
    char unk_17;
    char unk_18;
    char unk_19;
    char unk_1A;
    char unk_1B;
    char unk_1C;
    char unk_1D;
    char unk_1E;
    char unk_1F;
} TESTTESTTEST2;

u16 FS_Rename_sub(FSFile *pFile, char *arg1, char *arg2) {
    char spF8[64];
    char spB8[64];
    char sp98[32];
    char sp78[32];
    u16 sp76;
    u16 sp74;
    char sp60[20];
    /* char */ TESTTESTTEST sp54/* [12] */;
    char sp34[32];
    int sp30;
    int sp2C;
    u16 sp28;
    u16 sp26;
    u16 sp24;
    u16 sp22;
    u16 sp20;
    int sp1C;
    char *sp18;
    char *sp14;
    int spC;
    u16 *sp8;
    DrvCtl *temp_r27;
    int var_r28;
    u16 temp_r3;
    u16 temp_r3_10;
    u16 temp_r3_2;
    u16 temp_r3_3;
    u16 temp_r3_4;
    u16 temp_r3_5;
    u16 temp_r3_6;
    u16 temp_r3_7;
    u16 temp_r3_8;
    u16 temp_r3_9;
    u16 var_r31;
    TESTTESTTEST2 *temp_r29;

    sp14 = arg1;
    sp18 = arg2;
    sp76 = 1;
    sp74 = 1;
    sp24 = 1;
    sp22 = 1;
    sp20 = 0;
    sp1C = 0;
    temp_r27 = &FS_drv_ctl[pFile->unk_00[0]];
    sp8 = &sp22;
    spC = 2;
    temp_r3_4 = FS_Search_Entry(pFile, sp18, spB8, &sp78[0], &sp74, sp34, &sp2C, &sp26);
    if (temp_r3_4 == 0) {
        return 0xA011;
    }
    if ((sp22 == 0) && (sp74 != 1)) {
        return 0xA00F;
    }
    if (temp_r3_4 != 0xA007) {
        return temp_r3_4;
    }
    sp8 = &sp24;
    spC = 2;
    temp_r3_3 = FS_Search_Entry(pFile, sp14, spF8, &sp98[0], &sp76, sp54.unk_00, &sp30, &sp28);
    if (temp_r3_3 != 0) {
        return temp_r3_3;
    }
    if (sp24 == sp22) {
        temp_r3_2 = FS_entry_name_set(temp_r27 + 0x20000 + sp28 + 0xBA4, (&sp78[0])[sp74 - 1]);
        if (temp_r3_2 != 0) {
            return temp_r3_2;
        }
        temp_r3_5 = FS_write_sub(0, 1, sp30, 0, &pFile->unk_04[0], 0, &pFile->unk_00[0]);
        var_r31 = temp_r3_5;
        if (temp_r3_5 == 0) {
            var_r31 = FS_delete_lfn_entry(pFile, sp24, sp30, sp28);
        }
        if (sp54.unk_0B & 0x10) {
            pFile->unk_6C = 0;
            pFile->unk_70 = 0;
            pFile->unk_72 = 0;
            pFile->unk_74 = 0;
            FS_memset(pFile->unk_76, 0, 0x40U);
            FS_strncpy(pFile->unk_76, "\\", 1U);
        }
    } else {
        if (sp54.unk_0B & 0x10) {
            return 0xA006;
        }
        if (sp74 == 1) {
            var_r28 = pFile->unk_60;
        } else {
            var_r28 = FS_cluster_to_sector(pFile, sp22);
            if ((u32) (var_r28 + 0x10000) == -1U) {
                return 0xA032;
            }
        }

        temp_r3 = FS_allocate_entry(pFile, var_r28, &sp1C, &sp20);
        if (temp_r3 != 0) {
            return temp_r3;
        }
        temp_r29 = (TESTTESTTEST2*)(&temp_r27->unk_20BA4[sp20]);
        FS_memset(temp_r29, 0, 0x20U);
        temp_r3_6 = FS_entry_name_set(temp_r29, (&sp78[0])[sp74 - 1]);
        var_r31 = temp_r3_6;
        if (temp_r3_6 == 0) {
            temp_r29->unk_0B = sp54.unk_0B;
            FS_strncpy(temp_r29->unk_0C, sp60, 0xAU);
            temp_r29->unk_16[0] = sp60[0]; // sp6A;
            temp_r29->unk_16[1]/*7*/ = sp60[1]; // ((s32) sp6A >> 8);
            temp_r29->unk_16[2]/*8*/ = sp60[2]; // sp6C;
            temp_r29->unk_16[3]/*9*/ = sp60[3]; // ((s32) sp6C >> 8);
            temp_r29->unk_16[4]/*A*/ = sp60[4]; // sp6E;
            temp_r29->unk_16[5]/*B*/ = sp60[5]; // ((s32) sp6E >> 8);
            temp_r29->unk_16[6]/*C*/ = sp60[6]; // (sp70 >> 0);
            temp_r29->unk_16[7]/*D*/ = sp60[7]; // (sp70 >> 8);
            temp_r29->unk_16[8]/*E*/ = sp60[8]; // (sp70 >> 16);
            temp_r29->unk_16[9]/*F*/ = sp60[9]; // (sp70 >> 24);
            temp_r3_7 = FS_write_sub(0, 1, sp1C, 0, &pFile->unk_04[0], 0, &pFile->unk_00[0]);
            var_r31 = temp_r3_7;
            if (temp_r3_7 == 0) {
                temp_r3_8 = FS_read_sub(0, 1, sp30, 0, &pFile->unk_04[0], &pFile->unk_00[0]);
                var_r31 = temp_r3_8;
                if (temp_r3_8 == 0) {
                    // (temp_r27 + 0x20000 + sp28)->unkBA4 = 0xE5;
                    temp_r3_9 = FS_write_sub(0, 1, sp30, 0, &pFile->unk_04[0], 0, &pFile->unk_00[0]);
                    var_r31 = temp_r3_9;
                    if (temp_r3_9 == 0) {
                        temp_r3_10 = FS_delete_lfn_entry(pFile, sp24, sp30, sp28);
                        var_r31 = temp_r3_10;
                        if (temp_r3_10 != 0) {
                            return var_r31;
                        }
                    }
                }
            }
        }
        if (sp20 == 0) {
            var_r31 = FS_Flush(pFile);
        }
    }

    return var_r31;
}


// u16 FS_Rename_sub(FSFile* pFile, int* arg1, int* arg2) {
//     DrvCtl* volatile var_r27; // volatile real?
//     u16* uVar1;
//     int iVar3;
//     u16 status; // uVar2
//     char* iVar4;

//     char acStack_58[64]; // spF8
//     char acStack_98[64]; // spB8
//     char auStack_b8[32]; // sp98
//     char local_d8[32]; // sp78
//     u16 local_dc[2]; // sp74, sp76
//     char auStack_f0[20]; // sp60
//     char auStack_fc[12]; // sp54
//     char auStack_11c[32]; // sp34
//     int local_120; // sp30
//     int auStack_124; // sp2c
//     u16 local_128[2]; // sp28
//     u16 auStack_12a[1]; // sp26
//     u16 local_12c[2]; // sp22, sp24
//     u16 local_130; // sp20
//     int local_134; // sp1C

//     local_dc[1] = 1;
//     local_dc[0] = 1;
//     local_12c[1] = 1;
//     local_12c[0] = 1;
//     local_130 = 0;
//     local_134 = 0;
//     var_r27 = &FS_drv_ctl[pFile->unk_00[0]];

//     uVar1 = pFile->unk_00;
//     status = FS_Search_entry(pFile, arg2, acStack_98, local_d8, &local_dc[0], auStack_11c, auStack_124, auStack_12a,
//                              &local_12c[1], 2);

//     if (status == 0) {
//         return 0xA011;
//     }

//     if (local_12c[1] == 0 && local_dc[0] != 1) {
//         return 0xA00F;
//     }

//     if (status != 0xA007) {
//         return status;
//     }

//     status = FS_Search_entry(pFile, arg1, acStack_58, auStack_b8, &local_dc[1], auStack_fc, local_120, local_128,
//                              &local_12c[0], 2);
//     if (status != 0) {
//         return status;
//     }

//     if (local_12c[0] == local_12c[1]) {
//         status = FS_entry_name_set(var_r27[local_128[0]].unk_20BA4 + local_128[0], local_d8[local_dc[0] - 1]);

//         if (status == 0) {
//             status = FS_write_sub(NULL, 1, local_120, 0, pFile->unk_04, 0, pFile->unk_00);

//             if (status == 0) {
//                 status = FS_delete_lfn_entry(pFile, local_12c[0], local_120, local_128[0]);
//             }

//             if (auStack_fc[11] & 0x10) {
//                 pFile->unk_6C = 0;
//                 pFile->unk_70 = 0;
//                 pFile->unk_72 = 0;
//                 pFile->unk_74 = 0;
//                 FS_memset(pFile->unk_76, 0, sizeof(pFile->unk_76));
//                 FS_strncpy(pFile->unk_76, "\\", 1);
//             }
//         }
//     } else if (auStack_fc[11] & 0x10) {
//         status = 0xA006;
//     } else {
//         if (local_dc[0] == 1) {
//             iVar3 = pFile->unk_60;
//         } else {
//             iVar3 = FS_cluster_to_sector(pFile, local_12c[1]);

//             if (iVar3 == 0xFFFF) {
//                 return 0xA032;
//             }
//         }

//         status = FS_allocate_entry(pFile, iVar3, &local_134, &local_130);

//         if (status == 0) {
//             iVar3 = uVar1[0];
//             iVar4 = FS_drv_ctl[iVar3].unk_20BA4;
//             FS_memset(iVar4, 0, 0x20);
//             status = FS_entry_name_set(iVar4, local_d8[local_dc[0] - 1]);

//             if (status == 0) {
//                 // FS_drv_ctl[iVar3].unk_20BAF = auStack_fc[11];
//                 // FS_strncpy(FS_drv_ctl[iVar3].unk_20BB0, auStack_f0, 0x0A);
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[0];
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[1];
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[2];
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[3];
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[4];
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[5];
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[6];
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[7];
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[8];
//                 // FS_drv_ctl[iVar3].unk_20BBA[local_130] = auStack_f0[9];

//                 status = FS_write_sub(NULL, 1, local_134, 0, pFile->unk_04, 0, pFile->unk_00);

//                 if (status == 0) {
//                     status = FS_read_sub(NULL, 1, local_120, 0, pFile->unk_04, pFile->unk_00);
                    
//                     if (status == 0) {
//                         FS_drv_ctl[uVar1[0]].unk_20BA4[local_128[0]] = 0xE5;

//                         status = FS_write_sub(NULL, 1, local_120, 0, pFile->unk_04, 0, pFile->unk_00);

//                         if (status == 0) {
//                             status = FS_delete_lfn_entry(pFile, local_12c[0], local_120, local_128[0]);

//                             if (status != 0) {
//                                 return status;
//                             }
//                         }
//                     }
//                 }
//             }

//             if (local_130 == 0) {
//                 status = FS_Flush(pFile);
//             }
//         }
//     }

//     return status;
// }
