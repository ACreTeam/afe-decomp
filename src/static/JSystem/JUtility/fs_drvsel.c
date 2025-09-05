#include "JSystem/JUtility/JUTSDCard.h"
#include "JSystem/JUtility/carddrv.h"
#include "JSystem/JUtility/fs_drv.h"

u16 FS_DrvSel_Reset(void) {
    return CARD_IF_Reset();
}

u16 FS_DrvSel_Init(int param1, int param2, int param3) {
    u16 chan;
    u16 status;
    u16 value = param3 & 0xF00;

    switch (value) {
        case 0x100:
            chan = param3 & 0xFF;

            if (chan < CARD_NUM_CHANS) {
                status = CARD_Select(chan);

                if (status == 0) {
                    status = CARD_Init(param1, param2);
                }
            } else {
                status = 0xA00C;
            }
            break;
        default:
            status = 0xA00C;
            break;
    }

    return status;
}

u16 FS_DrvSel_Select(int arg5) {
    u16 status;
    u16 selected;
    u16 chan;

    status = 0;
    chan = arg5 & 0xFF;
    selected = CARD_SelectedNo();

    if (chan < CARD_NUM_CHANS) {
        if (chan != selected) {
            status = CARD_Select(chan);
        }
    } else {
        status = 0xA00C;
    }

    return status;
}

u16 FS_DrvSel_Read(SDSTATUS* arg0, s32 arg1, s32 arg2, s32 arg3, ReadWriteDParam5* arg4, int arg5) {
    u16 status;
    u16 value = arg5 & 0xF00;

    switch (value) {
        case 0x100:
            status = FS_DrvSel_Select(arg5);

            if (status == 0) {
                status = CARD_Read(arg0, arg1, arg2, arg3, arg4);
            }
            break;
        default:
            status = 0xA00C;
            break;
    }

    return status;
}

u16 FS_DrvSel_Write(SDSTATUS* arg0, s32 arg1, s32 arg2, s32 arg3, ReadWriteDParam5* arg4, int arg5) {
    u16 status;
    u16 value = arg5 & 0xF00;

    switch (value) {
        case 0x100:
            status = FS_DrvSel_Select(arg5);

            if (status == 0) {
                status = CARD_Write(arg0, arg1, arg2, arg3, arg4);
            }
            break;
        default:
            status = 0xA00C;
            break;
    }

    return status;
}

u16 FS_DrvSel_Getstatus(SDSTATUS* arg0, int arg5) {
    u16 status;
    u16 value = arg5 & 0xF00;

    switch (value) {
        case 0x100:
            status = FS_DrvSel_Select(arg5);

            if (status == 0) {
                status = CARD_Getstatus((u16*)arg0);
            }
            break;
        default:
            status = 0xA00C;
            break;
    }

    return status;
}

u16 FS_DrvSel_Getinfo(SDSTATUS* arg0, int arg5) {
    u16 status;
    u16 value = arg5 & 0xF00;

    if (value == 0x100) {
        status = FS_DrvSel_Select(arg5);

        if (status == 0) {
            status = CARD_Getinfo((u8*)arg0);
        }
    } else {
        status = 0xA00C;
    }

    return status;
}
