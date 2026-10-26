#include "JSystem/JUtility/JUTSDCard.h"
#include "os/OSTime.h"
#include "types.h"
#include "JSystem/JUtility/carddrv.h"
#include "JSystem/JUtility/exidrv.h"

#define CARD_SECTOR_SIZE 64

RES SD_RES[CARD_NUM_CHANS];
CMD SD_CMD[CARD_NUM_CHANS];
CID SD_CID[CARD_NUM_CHANS];
SDSTATUS SD_SDSTATUS[CARD_NUM_CHANS];
CSD SD_CSD[CARD_NUM_CHANS];
OSAlarm CARD_Alarm[CARD_NUM_CHANS];
OSSemaphore CARD_Sem[CARD_NUM_CHANS];

const u8 CARD_TBL_CLOCK_DIV[16][4] = {
    { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0x00, 0x03, 0x05 }, { 0xFF, 0x00, 0x03, 0x05 }, { 0xFF, 0x00, 0x03, 0x05 },
    { 0xFF, 0x00, 0x03, 0x05 }, { 0xFF, 0x01, 0x04, 0x05 }, { 0xFF, 0x01, 0x04, 0x05 }, { 0xFF, 0x01, 0x04, 0x05 },
    { 0xFF, 0x01, 0x05, 0x05 }, { 0xFF, 0x02, 0x05, 0x05 }, { 0xFF, 0x02, 0x05, 0x05 }, { 0xFF, 0x02, 0x05, 0x05 },
    { 0xFF, 0x02, 0x05, 0x05 }, { 0xFF, 0x02, 0x05, 0x05 }, { 0xFF, 0x02, 0x05, 0x05 }, { 0xFF, 0x03, 0x05, 0x05 },
};

int CARD_WP_Flag[CARD_NUM_CHANS]; // write protection flag
u16 CARD_ExiChannel;
u16 CARD_ExiFreq[CARD_NUM_CHANS];
ARG SD_ARG[CARD_NUM_CHANS];
int CARD_SectorSize[CARD_NUM_CHANS];
volatile u16 CARD_ErrStatus[CARD_NUM_CHANS];
int CARD_Status[CARD_NUM_CHANS];
int CARD_UnlockFlag[CARD_NUM_CHANS];
u32 CARD_Size[CARD_NUM_CHANS];
int func_CARD_In[CARD_NUM_CHANS];
int func_CARD_Out[CARD_NUM_CHANS];

u16 CARD_IF_Reset() {
    int i;

    EXIInit();
    CARD_ExiChannel = 0;

    for (i = 0; i < CARD_NUM_CHANS; i++) {
        OSInitSemaphore(&CARD_Sem[i], 0);
        OSCreateAlarm(&CARD_Alarm[i]);
        CARD_ErrStatus[i] = 0;
    }

    return 0;
}

u16 CARD_InitD(int param_1, int param_2) {
    u16 ret_code;
    int iVar1;

    func_CARD_In[CARD_ExiChannel] = param_1;
    func_CARD_Out[CARD_ExiChannel] = param_2;
    CARD_Size[CARD_ExiChannel] = 0;
    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;

    while ((iVar1 = EXIProbeEx(CARD_ExiChannel)) == 0) {}

    if (iVar1 == 1) {
        CARD_Reset();
    } else {
        return 0x90;
    }

    ret_code = CARD_ErrStatus[CARD_ExiChannel];
    return ret_code;
}

u16 CARD_SelectedNo() {
    return CARD_ExiChannel;
}

u16 CARD_Select(u16 nDrive) {
    if (CARD_ExiChannel != nDrive) {
        CARD_ExiChannel = nDrive;
    }

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;
    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_Reset() {
    volatile u32 sp8;
    u8 tran;
    u8 value;
    u16 div;
    u8 unit;

    (void)tran;
    (void)tran;
    (void)tran;

    CARD_ExiFreq[CARD_ExiChannel] = 0;

    if (EXIAttach(CARD_ExiChannel, (EXICallback)EXI_Null) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0090;
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_Status[CARD_ExiChannel] = 0;
    CARD_Size[CARD_ExiChannel] = 0;
    CARD_WP_Flag[CARD_ExiChannel] = 0;
    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;

    CARD_SoftReset();

    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        CARD_WP_Flag[CARD_ExiChannel] = 1;

        CARD_SoftReset();
        if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
            return CARD_ErrStatus[CARD_ExiChannel];
        }
    }

    CARD_SendOpCond();
    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_SendCSD();
    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_SendCID();
    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_SectorSize[CARD_ExiChannel] = CARD_SECTOR_SIZE * 8;
    CARD_SetBlockLength(CARD_SectorSize[CARD_ExiChannel]);
    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    unit = SD_CSD[CARD_ExiChannel].data[3];
    value = (unit >> 3) & 0xF;
    unit &= 7;

    if (unit > 3) {
        CARD_ExiFreq[CARD_ExiChannel] = 0;
    } else {
        div = CARD_TBL_CLOCK_DIV[value][unit];

        if (div == 0xFF) {
            CARD_ExiFreq[CARD_ExiChannel] = 0;
        } else {
            CARD_ExiFreq[CARD_ExiChannel] = div;
        }
    }

    CARD_ErrStatus[CARD_ExiChannel];
    CARD_SD_Status();
    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    ((u16*)&CARD_Size[CARD_ExiChannel])[1] =
        ((u16)SD_SDSTATUS[CARD_ExiChannel].data[6] << 8) + SD_SDSTATUS[CARD_ExiChannel].data[7];
    ((u16*)&CARD_Size[CARD_ExiChannel])[0] =
        ((u16)SD_SDSTATUS[CARD_ExiChannel].data[4] << 8) + SD_SDSTATUS[CARD_ExiChannel].data[5];

    CARD_Size[CARD_ExiChannel] *= 4 << (((SD_CSD[CARD_ExiChannel].data[9] & 3) << 1) |
                                        ((SD_CSD[CARD_ExiChannel].data[10] & 0x80) >> 7));

    if ((SD_CSD[CARD_ExiChannel].data[5] & 0xF) != 0) {
        CARD_Size[CARD_ExiChannel] = CARD_Size[CARD_ExiChannel] << (((SD_CSD[CARD_ExiChannel].data[12] & 3) << 2) |
                                                                    ((SD_CSD[CARD_ExiChannel].data[13] & 0xC0) >> 6));
    }

    CARD_Size[CARD_ExiChannel] /= CARD_SectorSize[CARD_ExiChannel];

    sp8 = ((SD_CSD[CARD_ExiChannel].data[8] & 0xC0) >> 6) + (SD_CSD[CARD_ExiChannel].data[7] << 2) +
          ((SD_CSD[CARD_ExiChannel].data[6] & 3) << 10) + 1;
    sp8 *= 4 << (((SD_CSD[CARD_ExiChannel].data[9] & 3) << 1) | ((SD_CSD[CARD_ExiChannel].data[10] & 0x80) >> 7));
    sp8 <<= ((SD_CSD[CARD_ExiChannel].data[12] & 3) << 2) | ((SD_CSD[CARD_ExiChannel].data[13] & 0xC0) >> 6);
    sp8 /= CARD_SectorSize[CARD_ExiChannel];
    !tran;
    CARD_Size[CARD_ExiChannel] += sp8;
    !tran;

    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_Getstatus(u16* param1) {
    int iVar1;

    *param1 = 0x831F;

    while ((iVar1 = EXIProbeEx(CARD_ExiChannel)) == 0) {}

    if (iVar1 != 1) {
        *param1 |= 0x420;
    }

    if (CARD_WP_Flag[CARD_ExiChannel] != 0) {
        *param1 |= 0x80;
    }

    return 0;
}

u16 CARD_Getinfo(SDInfos* param1) {
    s32 iVar1;
    u8* ptr = param1->data;

    for (iVar1 = 0; iVar1 < ARRAY_COUNT(param1->cid); iVar1++) {
        *ptr++ = SD_CID[CARD_ExiChannel].data[0x0F - iVar1];
    }

    for (iVar1 = 0; iVar1 < ARRAY_COUNT(param1->csd); iVar1++) {
        *ptr++ = SD_CSD[CARD_ExiChannel].data[0x0F - iVar1];
    }

    return 0;
}

u16 CARD_ReadD(u8* param1, u32 param2, int param3, int param4, UnknownStruct1* param5) {
    u8* pData;
    int i;

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;
    pData = (u8*)param1;

    if (!CARD_Command(READ_MULTIPLE_BLOCK, param3 * CARD_SectorSize[CARD_ExiChannel]) && !CARD_Response1()) {
        for (i = 0; i < param2 - 1; i++) {
            if (EXI_DataRead(pData, CARD_SectorSize[CARD_ExiChannel]) != 0) {
                break;
            }

            pData += CARD_SectorSize[CARD_ExiChannel];
        }

        if (EXI_DataReadFinal(pData, CARD_SectorSize[CARD_ExiChannel]) == 0) {
            CARD_StopResponse();
        }
    }

    param5->unk_02 = CARD_ErrStatus[CARD_ExiChannel];
    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_WriteD(u8* param1, u32 param2, int param3, int param4, UnknownStruct1* param5) {
    u8* volatile pData;
    int i;

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;

    if (CARD_WP_Flag[CARD_ExiChannel] != 0) {
        return LOCK_UNLOCK_FAILED;
    }

    pData = param1;

    if (!CARD_Command(WRITE_MULTIPLE_BLOCK, param3 * CARD_SectorSize[CARD_ExiChannel]) && !CARD_Response1()) {
        for (i = 0; i < param2; i++) {
            if (EXI_MultiDataWrite(pData, CARD_SectorSize[CARD_ExiChannel])) {
                break;
            }

            pData += CARD_SectorSize[CARD_ExiChannel];
        }
    }

    EXI_MultiWriteStop();
    SD_ARG[CARD_ExiChannel].data_u32 = 0;

    if (CARD_ErrStatus[CARD_ExiChannel] == 0 && !CARD_Command(SEND_STATUS, SD_ARG[CARD_ExiChannel].data_u32)) {
        CARD_Response2();
    }

    param5->unk_02 = CARD_ErrStatus[CARD_ExiChannel];
    param5->unk_04 = i * CARD_SectorSize[CARD_ExiChannel];
    return CARD_ErrStatus[CARD_ExiChannel];
}

static inline u16 CARD_Inline1(void) {
    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_SD_Status() {
    int iVar3;
    int pad;

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;
    iVar3 = CARD_SectorSize[CARD_ExiChannel];
    CARD_SectorSize[CARD_ExiChannel] = CARD_SECTOR_SIZE;
    CARD_SetBlockLength(CARD_SectorSize[CARD_ExiChannel]);

    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_AppCommand();

    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_Inline1(); // not necessary but likely exists unless it's leftover from a debug assert

    SD_ARG[CARD_ExiChannel].data_u32 = 0;

    if (!CARD_Command(CMD_4D, SD_ARG[CARD_ExiChannel].data_u32) && !CARD_Response2()) {
        EXI_DataRead(SD_SDSTATUS[CARD_ExiChannel].data, CARD_SectorSize[CARD_ExiChannel]);
    }

    CARD_SectorSize[CARD_ExiChannel] = iVar3;
    CARD_SetBlockLength(CARD_SectorSize[CARD_ExiChannel]);

    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_Command(u8 param1, int cmd) {
    SD_CMD[CARD_ExiChannel].data[0] = param1;
    SD_CMD[CARD_ExiChannel].data[1] = ((ARG*)&cmd)->data[0];
    SD_CMD[CARD_ExiChannel].data[2] = ((ARG*)&cmd)->data[1];
    SD_CMD[CARD_ExiChannel].data[3] = ((ARG*)&cmd)->data[2];
    SD_CMD[CARD_ExiChannel].data[4] = ((ARG*)&cmd)->data[3];

    EXI_CmdWrite(SD_CMD[CARD_ExiChannel].data, 5);
    return CARD_ErrStatus[CARD_ExiChannel];
}

static inline u16 CARD_Command2(UnkARG* param1) {
    SD_CMD[CARD_ExiChannel].data[0] = param1->_00;
    SD_CMD[CARD_ExiChannel].data[1] = param1->arg.data[0];
    SD_CMD[CARD_ExiChannel].data[2] = param1->arg.data[1];
    SD_CMD[CARD_ExiChannel].data[3] = param1->arg.data[2];
    SD_CMD[CARD_ExiChannel].data[4] = param1->arg.data[3];

    EXI_CmdWrite(SD_CMD[CARD_ExiChannel].data, 5);
    return CARD_ErrStatus[CARD_ExiChannel];
}

static inline u16 CARD_GetResponse0() {
    return SD_RES[CARD_ExiChannel].data[0];
}

u16 CARD_Response1(void) {
    EXI_ResRead(SD_RES[CARD_ExiChannel].data, 1);

    if ((SD_RES[CARD_ExiChannel].data[0] & 0x40)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_1000;
    }

    if ((SD_RES[CARD_ExiChannel].data[0] & 0x20)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0100;
    }

    if ((SD_RES[CARD_ExiChannel].data[0] & 0x08)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0002;
    }

    if ((SD_RES[CARD_ExiChannel].data[0] & 0x04)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0001;
    }

    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_Response2() {
    EXI_ResRead(SD_RES[CARD_ExiChannel].data, 2);

    if ((SD_RES[CARD_ExiChannel].data[0] & 0x7C) || (SD_RES[CARD_ExiChannel].data[1] & 0x9E)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0008;
        CARD_Status[CARD_ExiChannel] = SD_RES[CARD_ExiChannel].data[0] << 8;
        CARD_Status[CARD_ExiChannel] += SD_RES[CARD_ExiChannel].data[1];
    }

    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_StopResponse() {
    EXI_StopResRead(SD_RES[CARD_ExiChannel].data, 1);

    if ((SD_RES[CARD_ExiChannel].data[0] & 0x40)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_1000;
    }

    if ((SD_RES[CARD_ExiChannel].data[0] & 0x20)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0100;
    }

    if ((SD_RES[CARD_ExiChannel].data[0] & 0x08)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0002;
    }

    if ((SD_RES[CARD_ExiChannel].data[0] & 0x04)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0001;
    }

    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_SoftReset() {
    u16 ret;
    UnkARG iVar0;
    UnkARG iVar1;
    UnkARG iVar2;
    UnkARG iVar3;

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;
    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar1.arg = SD_ARG[CARD_ExiChannel];
    iVar1._00 = GO_IDLE_STATE;
    SD_CMD[CARD_ExiChannel].data[0] = iVar1._00;
    SD_CMD[CARD_ExiChannel].data[1] = iVar1.arg.data[0];
    SD_CMD[CARD_ExiChannel].data[2] = iVar1.arg.data[1];
    SD_CMD[CARD_ExiChannel].data[3] = iVar1.arg.data[2];
    SD_CMD[CARD_ExiChannel].data[4] = iVar1.arg.data[3];

    EXI_CmdWrite0(SD_CMD[CARD_ExiChannel].data, 5);

    CARD_ErrStatus[CARD_ExiChannel];
    !ret;
    !ret;
    CARD_ErrStatus[CARD_ExiChannel];
    CARD_Response1();

    CARD_ErrStatus[CARD_ExiChannel];
    iVar2.arg.data_u32 = 0;
    iVar2._00 = STOP_TRANSMISSION;
    SD_CMD[CARD_ExiChannel].data[0] = iVar2._00;
    SD_CMD[CARD_ExiChannel].data[1] = iVar2.arg.data[0];
    SD_CMD[CARD_ExiChannel].data[2] = iVar2.arg.data[1];
    SD_CMD[CARD_ExiChannel].data[3] = iVar2.arg.data[2];
    SD_CMD[CARD_ExiChannel].data[4] = iVar2.arg.data[3];

    EXI_CmdWrite(SD_CMD[CARD_ExiChannel].data, 5);

    if (CARD_ErrStatus[CARD_ExiChannel] == 0) {
        CARD_StopResponse();
    }

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;

    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar3.arg = SD_ARG[CARD_ExiChannel];
    iVar3._00 = GO_IDLE_STATE;
    SD_CMD[CARD_ExiChannel].data[0] = iVar3._00;
    SD_CMD[CARD_ExiChannel].data[1] = iVar3.arg.data[0];
    SD_CMD[CARD_ExiChannel].data[2] = iVar3.arg.data[1];
    SD_CMD[CARD_ExiChannel].data[3] = iVar3.arg.data[2];
    SD_CMD[CARD_ExiChannel].data[4] = iVar3.arg.data[3];
    EXI_CmdWrite(SD_CMD[CARD_ExiChannel].data, 5);

    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_ErrStatus[CARD_ExiChannel];
    !ret;
    CARD_Response1();
    !ret;

    CARD_ErrStatus[CARD_ExiChannel];
    ret = CARD_ErrStatus[CARD_ExiChannel];
    return ret;
}

u16 CARD_AppCommand() {
    UnkARG iVar2;
    u16 ret;

    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar2.arg = SD_ARG[CARD_ExiChannel];
    iVar2._00 = APP_CMD;

    if (CARD_Command2(&iVar2)) {
        ret = CARD_ErrStatus[CARD_ExiChannel];
        return ret;
    }

    CARD_Response1();
    ret = CARD_ErrStatus[CARD_ExiChannel];
    return ret;
}

static inline u16 CARD_AppCommandI() {
    UnkARG iVar2;

    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar2.arg = SD_ARG[CARD_ExiChannel];
    iVar2._00 = APP_CMD;

    if (CARD_Command2(&iVar2)) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_Response1();
    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_SendOpCond() {
    u16 ret;
    UnkARG iVar1;
    UnkARG iVar2;
    OSTick tick;

    tick = OSGetTick();

    do {
        CARD_AppCommandI();
        if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
            return CARD_ErrStatus[CARD_ExiChannel];
        }

        CARD_ErrStatus[CARD_ExiChannel];
        SD_ARG[CARD_ExiChannel].data_u32 = 0;
        iVar1.arg = SD_ARG[CARD_ExiChannel];
        iVar1._00 = CMD_69;
        if (CARD_Command2(&iVar1)) {
            return CARD_ErrStatus[CARD_ExiChannel];
        }

        CARD_Response1();
        ret = SD_RES[CARD_ExiChannel].data[0];
        !tick;

        if (CARD_ErrStatus[CARD_ExiChannel] != 0 || !(SD_RES[CARD_ExiChannel].data[0] & 1)) {
            goto end;
        }
    } while (EXI_CheckTimeOut(tick, 1500) == 0);

    CARD_AppCommandI();
    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_ErrStatus[CARD_ExiChannel];
    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar2.arg = SD_ARG[CARD_ExiChannel];
    iVar2._00 = CMD_69;
    if (CARD_Command2(&iVar2)) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_Response1();
    ret = SD_RES[CARD_ExiChannel].data[0];

    if (CARD_ErrStatus[CARD_ExiChannel] == 0 && (SD_RES[CARD_ExiChannel].data[0] & 1)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_8000;
    }

end:
    ret = CARD_ErrStatus[CARD_ExiChannel];
    return ret;
}

u16 CARD_SendCSD() {
    UnkARG iVar2;
    u16 ret;
    int i;

    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar2.arg = SD_ARG[CARD_ExiChannel];
    iVar2._00 = SEND_CSD;

    if (CARD_Command2(&iVar2)) {
        ret = CARD_ErrStatus[CARD_ExiChannel];
        return ret;
    }

    if (!CARD_Response1()) {
        EXI_DataRead(SD_CSD[CARD_ExiChannel].data, 0x10);
    }

    for (i = 0; i < 0x10; i++) {}

    ret = CARD_ErrStatus[CARD_ExiChannel];
    return ret;
}

u16 CARD_SendCID() {
    UnkARG iVar2;
    u16 ret;
    int i;

    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar2.arg = SD_ARG[CARD_ExiChannel];
    iVar2._00 = SEND_CID;

    if (CARD_Command2(&iVar2)) {
        ret = CARD_ErrStatus[CARD_ExiChannel];
        return ret;
    }

    if (!CARD_Response1()) {
        EXI_DataRead(SD_CID[CARD_ExiChannel].data, 0x10);
    }

    for (i = 0; i < 0x10; i++) {}

    ret = CARD_ErrStatus[CARD_ExiChannel];
    return ret;
}

u16 CARD_SetBlockLength(int param_1) {
    UnkARG iVar2;
    u16 ret;

    SD_ARG[CARD_ExiChannel].data_u32 = param_1;
    iVar2.arg = SD_ARG[CARD_ExiChannel];
    iVar2._00 = SET_BLOCKLEN;

    if (CARD_Command2(&iVar2)) {
        ret = CARD_ErrStatus[CARD_ExiChannel];
        return ret;
    }

    CARD_Response1();

    ret = CARD_ErrStatus[CARD_ExiChannel];
    return ret;
}

u16 CARD_SecureGetinfo(SDInfos* param1) {
    u8* ptr;
    int i;

    CARD_SD_Status();

    if (CARD_ErrStatus[CARD_ExiChannel] == 0) {
        ptr = param1->data;

        for (i = 0; i < ARRAY_COUNT(SD_SDSTATUS[CARD_ExiChannel].data); i++) {
            *ptr++ = SD_SDSTATUS[CARD_ExiChannel].data[i];
        }
    }

    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_Term() {
    u16 uVar2;

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;

    if (EXIDetach(CARD_ExiChannel) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00C0;
        uVar2 = CARD_ErrStatus[CARD_ExiChannel];
        return uVar2;
    }

    return 0;
}
