#include "JSystem/JUtility/fs_drv.h"

#include "JSystem/JUtility/carddrv.h"
#include "JSystem/JUtility/fs_file.h"

#include <dolphin.h>

u16 CARD_Write(u8* param1, u32 param2, int param3, u32 param4, UnknownStruct1* param5) {
    OSTick start;
    OSTick end;
    u16 ret;

    if (param4 != 0) {
        return 0xA00C;
    }

    start = OSGetTick();
    ret = CARD_WriteD(param1, param2, param3, 0, param5);
    end = OSGetTick();
    return ret;
}

u16 CARD_Read(u8* param1, u32 param2, int param3, u32 param4, UnknownStruct1* param5) {
    OSTick start;
    OSTick end;
    u16 ret;

    if (param4 != 0) {
        return 0xA00C;
    }

    start = OSGetTick();
    ret = CARD_ReadD(param1, param2, param3, 0, param5);
    end = OSGetTick();
    param5->unk_04 = param2 << 9;
    return ret;
}

u16 CARD_Init(int param1, int param2) {
    return CARD_InitD(0, 0);
}

u16 SDTerm(u16 nDrive) {
    u16 status;

    if (nDrive > 1) {
        return 0xA00C;
    }

    status = CARD_Select(nDrive);

    if (status != 0) {
        return status;
    }

    return CARD_Term();
}
