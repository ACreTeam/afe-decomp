#ifndef CARDDRV_H
#define CARDDRV_H

#include "types.h"
#include "JSystem/JUtility/JUTSDCard.h"

#include <dolphin.h>

#ifdef __cplusplus
extern "C" {
#endif

enum CardErrorStatus {
    CARD_ERROR_0000 = (0 << 0),
    CARD_ERROR_0001 = (1 << 0),
    CARD_ERROR_0002 = (1 << 1),
    CARD_ERROR_0008 = (1 << 3),
    CARD_ERROR_0010 = (1 << 4),
    CARD_ERROR_0020 = (1 << 5),
    CARD_ERROR_0040 = (1 << 6),
    CARD_ERROR_0080 = (1 << 7),
    CARD_ERROR_0100 = (1 << 8),
    CARD_ERROR_0200 = (1 << 9),
    CARD_ERROR_1000 = (1 << 12),
    CARD_ERROR_4000 = (1 << 14),
    CARD_ERROR_8000 = (1 << 15),

    CARD_ERROR_0090 = (CARD_ERROR_0080 | CARD_ERROR_0010),
    CARD_ERROR_00A0 = (CARD_ERROR_0080 | CARD_ERROR_0020),
    CARD_ERROR_00B0 = (CARD_ERROR_0080 | CARD_ERROR_0020 | CARD_ERROR_0010),
    CARD_ERROR_00C0 = (CARD_ERROR_0080 | CARD_ERROR_0040),
    CARD_ERROR_00D0 = (CARD_ERROR_0080 | CARD_ERROR_0040 | CARD_ERROR_0010),
    CARD_ERROR_00E0 = (CARD_ERROR_0080 | CARD_ERROR_0040 | CARD_ERROR_0020),
    CARD_ERROR_00F0 = (CARD_ERROR_0080 | CARD_ERROR_0040 | CARD_ERROR_0020 | CARD_ERROR_0010),
};

typedef struct UnkARG {
    ARG arg;
    u8 _00;
} UnkARG;

typedef struct ReadWriteDParam5 {
    u16 unk_00;
    u16 unk_02;
    u32 unk_04;
} ReadWriteDParam5;

extern int CARD_IF_Reset();
extern u16 CARD_InitD(int param_1, int param_2);
extern u16 CARD_SelectedNo();
extern u16 CARD_Select(u16 param_1);
extern u16 CARD_Reset();
extern int CARD_Getstatus(u16* param1);
extern int CARD_Getinfo(u8* param1);
extern u16 CARD_ReadD(SDSTATUS* param1, u32 param2, int param3, int param4, ReadWriteDParam5* param5);
extern u16 CARD_WriteD(SDSTATUS* param1, u32 param2, int param3, int param4, ReadWriteDParam5* param5);
extern u16 CARD_SD_Status();
extern u16 CARD_Command(u8 param1, int cmd);
extern u16 CARD_Response1(void);
extern u16 CARD_Response2();
extern u16 CARD_StopResponse();
extern u16 CARD_DataResponse();
extern u16 CARD_SoftReset();
extern u16 CARD_AppCommand();
extern u16 CARD_SendOpCond();
extern u16 CARD_SendCSD();
extern u16 CARD_SendCID();
extern u16 CARD_SetBlockLength(int param_1);
extern u16 CARD_Term();

extern RES SD_RES[CARD_NUM_CHANS];
extern CMD SD_CMD[CARD_NUM_CHANS];
extern CID SD_CID[CARD_NUM_CHANS];
extern SDSTATUS SD_SDSTATUS[CARD_NUM_CHANS];
extern CSD SD_CSD[CARD_NUM_CHANS];
extern OSAlarm CARD_Alarm[CARD_NUM_CHANS];
extern OSSemaphore CARD_Sem[CARD_NUM_CHANS];
extern int CARD_WP_Flag[CARD_NUM_CHANS];
extern u16 CARD_ExiChannel;
extern u16 CARD_ExiFreq[CARD_NUM_CHANS];
extern ARG SD_ARG[CARD_NUM_CHANS];
extern int CARD_SectorSize[CARD_NUM_CHANS];
extern volatile u16 CARD_ErrStatus[CARD_NUM_CHANS];
extern int CARD_Status[CARD_NUM_CHANS];
extern int CARD_UnlockFlag[CARD_NUM_CHANS];
extern int CARD_Size[CARD_NUM_CHANS];
extern int func_CARD_In[CARD_NUM_CHANS];
extern int func_CARD_Out[CARD_NUM_CHANS];

#ifdef __cplusplus
};
#endif

#endif
