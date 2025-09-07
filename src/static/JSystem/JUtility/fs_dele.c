#include "JSystem/JUtility/fs_dele.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/fs_open.h"
#include "JSystem/JUtility/fs_subd.h"

u16 FS_Delete(FSFile* param1, const char* param2) {
    DrvCtl* ptr;
    u16 status = 0;

    if (param1 == NULL || param2 == NULL) {
        return 0xA00C;
    }

    if (param1->unk_04[0] != 1) {
        return 0xA016;
    }

    ptr = &FS_drv_ctl[param1->unk_00[0]];
    if (param1->unk_00 != ptr->unk_08) {
        return 0xA00C;
    }

    status = FS_Delete_sub(param1, param2);
    return status;
}

u16 FS_Delete_sub(FSFile* param1, const char* param2) {
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
    ptr = &FS_drv_ctl[param1->unk_00[0]];
    status = FS_Search_Entry(param1, (char*)param2, sp68, sp48, sp44, sp24, &sp20, &sp1E, &sp1C, 1);

    if (status != 0) {
        return status;
    }

    if ((sp24[11] & 1) || (sp24[11] & 8) || (sp24[11] & 0x10) || ((sp24[11] & 0xF) == 0xF)) {
        return 0xA006;
    }

    status = FS_Delete_Entry(param1, sp20, sp1E, sp1C);
    return status;
}

u16 FS_Delete_Entry(FSFile* param1, int param2, u16 param3, u16 param4) {
    DrvCtl* ptr;
    DrvCtl_unk_20000* ptr2;
    u16 temp_r29;
    u16 status;
    int pad;
    int idx;

    ptr = &FS_drv_ctl[param1->unk_00[0]];
    if(param1->unk_04[13] == 0x20){
        pad = 0;
        (void)pad;
        (void)pad;
        (void)idx;
    };
    // ptr2 = (DrvCtl_unk_20000*)((u32)&ptr->unk_20000 + param3);
    idx = (int)param3;
    ptr2 = (DrvCtl_unk_20000*)((u32)ptr->ctrl_p + idx);

    ptr2->unk_20BA4.unk_00[0] = 0xE5;
    temp_r29 = ((ptr2->unk_20BA4.unk_1B << 8) & 0xFF00) | (ptr2->unk_20BA4.unk_1A & 0x00FF);

    status = FS_delete_lfn_entry(param1, param4, param2, param3);

    if (status != 0) {
        return status;
    }

    if (temp_r29 > 1 && temp_r29 <= (param1->unk_BC - 1)) {
        status = FS_fat_clear(temp_r29, param1); // the declaration for this was changed

        if (status != 0) {
            return status;
        }

        status = FS_Flush(param1);
    } else {
        if (temp_r29 == 0) {
            status = 0;
        } else {
            status = 0xA032;
        }
    }

    return status;
}
