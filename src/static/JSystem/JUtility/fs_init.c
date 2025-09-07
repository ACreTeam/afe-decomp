#include "JSystem/JUtility/fs_init.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_drvsel.h"

const u16 kindDrv[] = {
    /* Memory Card Slot A */ 0x0100,
    /* Memory Card Slot B */ 0x0101,
};

u16 FS_Init(int param1, int param2, u16 param3) {
    u16 sp12;
    DrvCtl* temp_r31;
    u16 status;
    u16 zero = 0;

    temp_r31 = &FS_drv_ctl[param3];

    if (param3 > 1) {
        return 0xA00C;
    }

    FS_Init_set_drive_info(param3);
    status = FS_Init_check_config(param3, &sp12);

    if (status != 0) {
        return status;
    }

    temp_r31->unk_08[0].unk_06 = 1;
    temp_r31->unk_08[0].unk_F4 = 0;
    temp_r31->unk_08[0].unk_C0 = 0;
    temp_r31->unk_08[0].unk_FA = 0;

    temp_r31->unk_08[1].unk_06 = 1;
    temp_r31->unk_08[1].unk_F4 = 0;
    temp_r31->unk_08[1].unk_C0 = 0;
    temp_r31->unk_08[1].unk_FA = 0;

    temp_r31->unk_259D4 = 0;
    temp_r31->unk_259D8 = 1;
    temp_r31->unk_259DC = 0;

    if (sp12 == 1) {
        status = FS_DrvSel_Reset();
    }

    if (status == 0) {
        status = FS_DrvSel_Init(param1, param2, temp_r31->unk_00[1]);
    }

    if (status != 0) {
        return status;
    }

    return zero;
}

u16 FS_Init_check_config(u16 param1, u16* param2) {
    u16 unused;
    DrvCtl* sp10 = &FS_drv_ctl[param1];
    u32 value;

    (void)unused;
    (void)unused;

    value = 2;
    if ((value != 1) && (value != 2)) {
        return 0xA042;
    }

    value = 2;
    if ((value != 1) && (value != 2)) {
        return 0xA042;
    }

    value = 2;
    if ((value != 1) && (value != 2)) {
        return 0xA042;
    }

    value = 1;
    if ((value != 2) && (value != 1)) {
        return 0xA042;
    }

    value = 1;
    if ((value != 2) && (value != 1)) {
        return 0xA042;
    }

    value = 0x400000;
    if (value > 0x400000) {
        return 0xA042;
    }

    value = 5;
    if ((value < 1) || (value > 5)) {
        return 0xA042;
    }

    value = 3;
    if ((value < 1) || (value > 5)) {
        return 0xA042;
    }

    value = 3;
    if ((value < 1) || (value > 3)) {
        return 0xA042;
    }

    value = 2;
    if ((value < 1) || (value > 3)) {
        return 0xA042;
    }

    value = 8;
    if ((value < 1) || (value > 8)) {
        return 0xA042;
    }

    value = 5;
    if ((value < 1) || (value > 8)) {
        return 0xA042;
    }

    value = 2;
    if ((value != 1) && (value != 2)) {
        return 0xA042;
    }

    value = 0x20400;
    if (value < 0x800U) {
        return 0xA042;
    }

    value = 0x200;
    if (value < 0x200) {
        return 0xA042;
    }

    if (value > 0x8100) {
        return 0xA042;
    }

    if ((value & 0x1FF) != 0) {
        return 0xA042;
    }

    value = 0x200;
    if ((value < 2) || (value > 0x200)) {
        return 0xA042;
    }

    if (FS_Init_check_kind_of_drive(param2) != 0) {
        return 0xA042;
    }

    value = 0x4000;
    if ((value & 0x7FF) != 0) {
        return 0xA042;
    }

    return 0;
}

void FS_Init_set_drive_info(u16 param1) {
    DrvCtl* temp_r31 = &FS_drv_ctl[param1];

    temp_r31->unk_00[2] = 0;
    temp_r31->unk_00[0] = param1;
    temp_r31->unk_00[1] = kindDrv[param1];
}

u16 FS_Init_check_kind_of_drive(u16* param1) {
    u16 sVar2;
    u16 uVar3;
    u16 status;
    u16 uVar5;
    DrvCtl* ptr;

    sVar2 = 0;
    status = 0;

    for (uVar5 = 1; uVar5 < 2; uVar5++) {
        for (uVar3 = 0; uVar3 < (2 - uVar5); uVar3++) {
            if (kindDrv[uVar3] == kindDrv[uVar5 + uVar3] && kindDrv[uVar3] != 0) {
                return 0xA042;
            }
        }
    }

    for (uVar5 = 0; uVar5 <= 1; uVar5++) {
        if ((kindDrv[uVar5] & 0x200) == 0x200) {
            return 0xA042;
        }
    }

    for (uVar5 = 0; uVar5 <= 1; uVar5++) {
        switch (kindDrv[uVar5]) {
            case 0x0000:
                if (uVar5 == 0) {
                    status = 0xA042;
                }

                ptr = &FS_drv_ctl[uVar5];
                ptr->unk_00[0] = 0xFFFF;
                ptr->unk_00[1] = kindDrv[uVar5];
                sVar2++;
                break;
            case 0x0100:
            case 0x0101:
            case 0x0200:
                if (sVar2 != 0) {
                    status = 0xA042;
                }
                break;
            default:
                status = 0xA042;
                break;
        }

        if (status != 0) {
            return status;
        }
    }

    *param1 = 2 - sVar2;
    return status;
}
