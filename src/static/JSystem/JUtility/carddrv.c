#include "JSystem/JUtility/JUTSDCard.h"
#include "os/OSTime.h"
#include "types.h"
#include "JSystem/JUtility/carddrv.h"
#include "JSystem/JUtility/exidrv.h"

RES SD_RES[CARD_NUM_CHANS];
CMD SD_CMD[CARD_NUM_CHANS];
CID SD_CID[CARD_NUM_CHANS];
SDSTATUS SD_SDSTATUS[CARD_NUM_CHANS];
CSD SD_CSD[CARD_NUM_CHANS];
OSAlarm CARD_Alarm[CARD_NUM_CHANS];
OSSemaphore CARD_Sem[CARD_NUM_CHANS];

const u8 CARD_TBL_CLOCK_DIV[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x03, 0x05, 0xFF, 0x00, 0x03, 0x05, 0xFF, 0x00, 0x03, 0x05,
    0xFF, 0x00, 0x03, 0x05, 0xFF, 0x01, 0x04, 0x05, 0xFF, 0x01, 0x04, 0x05, 0xFF, 0x01, 0x04, 0x05,
    0xFF, 0x01, 0x05, 0x05, 0xFF, 0x02, 0x05, 0x05, 0xFF, 0x02, 0x05, 0x05, 0xFF, 0x02, 0x05, 0x05,
    0xFF, 0x02, 0x05, 0x05, 0xFF, 0x02, 0x05, 0x05, 0xFF, 0x02, 0x05, 0x05, 0xFF, 0x03, 0x05, 0x05,
};

int CARD_WP_Flag[CARD_NUM_CHANS]; // write protection flag
u16 CARD_ExiChannel;
u16 CARD_ExiFreq[CARD_NUM_CHANS];
ARG SD_ARG[CARD_NUM_CHANS];
int CARD_SectorSize[CARD_NUM_CHANS];
volatile u16 CARD_ErrStatus[CARD_NUM_CHANS];
int CARD_Status[CARD_NUM_CHANS];
int CARD_UnlockFlag[CARD_NUM_CHANS];
int CARD_Size[CARD_NUM_CHANS];
int func_CARD_In[CARD_NUM_CHANS];
int func_CARD_Out[CARD_NUM_CHANS];

int CARD_IF_Reset() {
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

u16 CARD_Select(u16 param_1) {
    if (CARD_ExiChannel != param_1) {
        CARD_ExiChannel = param_1;
    }

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;
    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_Reset() {
    u32 sp8;
    u32 temp_r0;
    u8 temp_r28;
    u8 temp_r29;
    u8 temp_r29_2;

    CARD_ExiFreq[CARD_ExiChannel] = 4;

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

    CARD_SectorSize[CARD_ExiChannel] = SECTOR_SIZE * 8;
    CARD_SetBlockLength(CARD_SectorSize[CARD_ExiChannel]);
    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    temp_r29 = SD_CSD[CARD_ExiChannel].data[3];
    temp_r29_2 = temp_r29 & 7;

    if (temp_r29_2 > 3) {
        CARD_ExiFreq[CARD_ExiChannel] = 0;
    } else {
        temp_r28 = CARD_TBL_CLOCK_DIV[((((temp_r29 >> 3U) & 0xF) * 4) & 0x3FC) + temp_r29_2];

        if (temp_r28 == 0xFF) {
            CARD_ExiFreq[CARD_ExiChannel] = 0;
        } else {
            CARD_ExiFreq[CARD_ExiChannel] = temp_r28;
        }
    }

    CARD_SD_Status();
    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    CARD_Size[CARD_ExiChannel] = SD_SDSTATUS[CARD_ExiChannel].data[6] * 0x100 + SD_SDSTATUS[CARD_ExiChannel].data[7];
    CARD_Size[CARD_ExiChannel] = SD_SDSTATUS[CARD_ExiChannel].data[4] * 0x100 + SD_SDSTATUS[CARD_ExiChannel].data[5];

    CARD_Size[CARD_ExiChannel] *=
        (4 << ((SD_CSD[CARD_ExiChannel].data[9] & 3) << 1 | (SD_CSD[CARD_ExiChannel].data[10] >> 7)));

    if ((SD_CSD[CARD_ExiChannel].data[5] & 0xf) != 0) {
        CARD_Size[CARD_ExiChannel] <<=
            ((SD_CSD[CARD_ExiChannel].data[12] & 3) << 2 | (SD_CSD[CARD_ExiChannel].data[0xd] >> 6));
    }

    CARD_Size[CARD_ExiChannel] /= CARD_SectorSize[CARD_ExiChannel];

    CARD_Size[CARD_ExiChannel] +=
        (((SD_CSD[CARD_ExiChannel].data[8] >> 6) + SD_CSD[CARD_ExiChannel].data[7] * 4 +
          (SD_CSD[CARD_ExiChannel].data[6] & 3) * 0x400 + 1) *
             (4 << ((SD_CSD[CARD_ExiChannel].data[9] & 3) << 1 | (SD_CSD[CARD_ExiChannel].data[10] >> 7)))
         << ((SD_CSD[CARD_ExiChannel].data[12] & 3) << 2 | (SD_CSD[CARD_ExiChannel].data[13] >> 6))) /
        CARD_SectorSize[CARD_ExiChannel];

    return CARD_ErrStatus[CARD_ExiChannel];
}

int CARD_Getstatus(u16* param1) {
    int iVar1;

    param1[0] = 0x831F;

    while ((iVar1 = EXIProbeEx(CARD_ExiChannel)) == 0) {}

    if (iVar1 != 1) {
        param1[0] |= 0x420;
    }

    if (CARD_WP_Flag[CARD_ExiChannel] != 0) {
        param1[0] |= 0x80;
    }

    return 0;
}

int CARD_Getinfo(u8* param1) {
    s32 iVar1;
    u8* ptr = param1;

    for (iVar1 = 0; iVar1 < 0x10; iVar1++) {
        *ptr++ = SD_CID[CARD_ExiChannel].data[0x0F - iVar1];
    }

    // not sizeof(CSD)?
    for (iVar1 = 0; iVar1 < 0x10; iVar1++) {
        *ptr++ = SD_CSD[CARD_ExiChannel].data[0x0F - iVar1];
    }

    return 0;
}

u16 CARD_ReadD(SDSTATUS* param1, u32 param2, int param3, int param4, ReadWriteDParam5* param5) {
    u8* pData;
    int i;

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;
    pData = param1->data;

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

u16 CARD_WriteD(SDSTATUS* param1, u32 param2, int param3, int param4, ReadWriteDParam5* param5) {
    u8* volatile pData;
    int i;

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;

    if (CARD_WP_Flag[CARD_ExiChannel] != 0) {
        return LOCK_UNLOCK_FAILED;
    }

    pData = param1->data;

    if (!CARD_Command(WRITE_MULTIPLE_BLOCK, param3 * CARD_SectorSize[CARD_ExiChannel]) && !CARD_Response1()) {
        for (i = 0; i < param2; i++) {
            if (EXI_MultiDataWrite(pData, CARD_SectorSize[CARD_ExiChannel]) || CARD_DataResponse()) {
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
    CARD_SectorSize[CARD_ExiChannel] = SECTOR_SIZE;
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

u16 CARD_DataResponse() {
    EXI_DataRes(SD_RES[CARD_ExiChannel].data);

    if (((CARD_GetResponse0() >> 1) & 7) == 5) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0002;
    }

    if (((CARD_GetResponse0() >> 1) & 7) == 6) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0200;
    }

    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 CARD_SoftReset() {
    u16 ret;
    int tmp;
    UnkARG iVar2;
    UnkARG iVar2_2;
    int pad1;
    int pad2;

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;
    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar2.arg = SD_ARG[CARD_ExiChannel];
    iVar2._00 = GO_IDLE_STATE;
    SD_CMD[CARD_ExiChannel].data[0] = iVar2._00;
    SD_CMD[CARD_ExiChannel].data[1] = iVar2.arg.data[0];
    SD_CMD[CARD_ExiChannel].data[2] = iVar2.arg.data[1];
    SD_CMD[CARD_ExiChannel].data[3] = iVar2.arg.data[2];
    SD_CMD[CARD_ExiChannel].data[4] = iVar2.arg.data[3];

    EXI_CmdWrite0(SD_CMD[CARD_ExiChannel].data, 5);

    CARD_ErrStatus[CARD_ExiChannel];
    CARD_ErrStatus[CARD_ExiChannel];
    CARD_Response1();

    CARD_ErrStatus[CARD_ExiChannel];
    iVar2_2.arg = iVar2.arg;
    iVar2_2._00 = STOP_TRANSMISSION;
    SD_CMD[CARD_ExiChannel].data[0] = iVar2_2._00;
    SD_CMD[CARD_ExiChannel].data[1] = iVar2_2.arg.data[0];
    SD_CMD[CARD_ExiChannel].data[2] = iVar2_2.arg.data[1];
    SD_CMD[CARD_ExiChannel].data[3] = iVar2_2.arg.data[2];
    SD_CMD[CARD_ExiChannel].data[4] = iVar2_2.arg.data[3];

    EXI_CmdWrite(SD_CMD[CARD_ExiChannel].data, 5);

    if (CARD_ErrStatus[CARD_ExiChannel] == 0) {
        CARD_StopResponse();
    }

    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;

    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar2.arg = SD_ARG[CARD_ExiChannel];
    iVar2._00 = GO_IDLE_STATE;
    SD_CMD[CARD_ExiChannel].data[0] = iVar2._00;
    SD_CMD[CARD_ExiChannel].data[1] = iVar2.arg.data[0];
    SD_CMD[CARD_ExiChannel].data[2] = iVar2.arg.data[1];
    SD_CMD[CARD_ExiChannel].data[3] = iVar2.arg.data[2];
    SD_CMD[CARD_ExiChannel].data[4] = iVar2.arg.data[3];
    EXI_CmdWrite(SD_CMD[CARD_ExiChannel].data, 5);

    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        // ?
        CARD_ErrStatus[CARD_ExiChannel];
    } else {
        // ?
        CARD_ErrStatus[CARD_ExiChannel];
        CARD_Response1();
    }

    // ?
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

inline u16 CARD_SendOpCond_UnknownInline1() {
    u16 ret;

    if (CARD_ErrStatus[CARD_ExiChannel] != 0) {
        ret = CARD_ErrStatus[CARD_ExiChannel];
    } else {
        // CARD_Response1();
        ret = CARD_ErrStatus[CARD_ExiChannel];
    }

    return ret;
}

u16 CARD_SendOpCond() {
    UnkARG iVar2;
    u16 ret;
    OSTick tick;

    tick = OSGetTick();

    do {
        CARD_AppCommand();
        CARD_SendOpCond_UnknownInline1();

        SD_ARG[CARD_ExiChannel].data_u32 = 0;
        iVar2.arg = SD_ARG[CARD_ExiChannel];
        iVar2._00 = CMD_69;
        if (CARD_Command2(&iVar2)) {
            ret = CARD_ErrStatus[CARD_ExiChannel];
            return ret;
        }

        CARD_Response1();

        if (CARD_ErrStatus[CARD_ExiChannel] != 0 || !(SD_RES[CARD_ExiChannel].data[0] & 1)) {
            goto end;
        }
    } while (EXI_CheckTimeOut(tick, 1500) == 0);

    CARD_AppCommand();
    CARD_SendOpCond_UnknownInline1();

    SD_ARG[CARD_ExiChannel].data_u32 = 0;
    iVar2.arg = SD_ARG[CARD_ExiChannel];
    iVar2._00 = SEND_CSD;
    if (CARD_Command2(&iVar2)) {
        ret = CARD_ErrStatus[CARD_ExiChannel];
        return ret;
    }

    CARD_Response1();

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
