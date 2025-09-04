#include "os.h"
#include "types.h"
#include "macros.h"
#include "JSystem/JUtility/exidrv.h"
#include "JSystem/JUtility/carddrv.h"

#include <dolphin.h>

u8 SD_DUMMY[0x80];
u8 EXI_ClrData[CARD_NUM_CHANS];

#define EXI_Lock()                                                         \
    {                                                                      \
        CARD_UnlockFlag[CARD_ExiChannel] = 0;                              \
        if (EXILock(CARD_ExiChannel, 0, (EXICallback)EXI_Unlock) == 0) {   \
            while (CARD_UnlockFlag[CARD_ExiChannel] == 0) {}               \
                                                                           \
            if (EXILock(CARD_ExiChannel, 0, (EXICallback)EXI_Null) == 0) { \
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00A0;        \
                return CARD_ErrStatus[CARD_ExiChannel];                    \
            }                                                              \
        }                                                                  \
    }

#define EXI_Select(nFreq)                                           \
    {                                                               \
        if (EXISelect(CARD_ExiChannel, 0, nFreq) == 0) {            \
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00B0;     \
                                                                    \
            if (EXIUnlock(CARD_ExiChannel) == 0) {                  \
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00D0; \
            }                                                       \
                                                                    \
            return CARD_ErrStatus[CARD_ExiChannel];                 \
        }                                                           \
    }

#define EXI_SelectSD(nFreq)                                         \
    {                                                               \
        if (EXISelectSD(CARD_ExiChannel, 0, nFreq) == FALSE) {      \
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00B0;     \
                                                                    \
            if (EXIUnlock(CARD_ExiChannel) == 0) {                  \
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00D0; \
            }                                                       \
                                                                    \
            return CARD_ErrStatus[CARD_ExiChannel];                 \
        }                                                           \
    }

static inline u16 EXI_LockAndSelect(u32 nFreq) {
    (void)nFreq;

    EXI_Lock();
    EXI_Select(nFreq);

    return 0;
}

static inline u16 EXI_DeselectAndUnlock() {
    if (EXIDeselect(CARD_ExiChannel) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00E0;
    }

    if (EXIUnlock(CARD_ExiChannel) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00D0;
        CARD_ErrStatus[CARD_ExiChannel];
    }

    return CARD_ErrStatus[CARD_ExiChannel];
}

static inline void EXI_UnknownInline3(u8* pRES, OSTick tick, int time) {
    while (((pRES[0] & 0x80) != 0)) {
        pRES[0] = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, pRES, sizeof(u8), 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
            break;
        }

        if ((pRES[0] & 0x80) == 0) {
            break;
        }

        if (EXI_CheckTimeOut(tick, time) == 0) {
            continue;
        }

        pRES[0] = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, pRES, sizeof(u8), 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        } else if ((pRES[0] & 0x80) != 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_4000;
        }

        break;
    }
}

static inline void EXI_UnknownInline4(u8* pRES, OSTick tick, int time) {
    while (pRES[0] != 0xFF) {
        pRES[1] = pRES[0];
        pRES[0] = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, pRES, sizeof(u8), 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
            break;
        }

        if (pRES[0] == 0xFF) {
            break;
        }

        if (EXI_CheckTimeOut(tick, 0x5DCU) == 0) {
            continue;
        }

        pRES[1] = pRES[0];
        pRES[0] = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, pRES, sizeof(u8), 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        } else if (pRES[0] != 0xFF) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_4000;
        }

        break;
    }
}

ASM void EXI_Null(s32 chan /*, OSContext* context*/) {
}

ASM void EXI_Unlock(s32 chan /*, OSContext* context*/) {
#ifdef __MWERKS__ // clang-format off
    li r4, 1
    lhz r0, CARD_ExiChannel
    slwi r0, r0, 2
    li r3, CARD_UnlockFlag
    stwx r4, r3, r0
#endif // clang-format on
}

#pragma peephole on

void EXI_AlarmFunc(OSAlarm* alarm, OSContext* context) {
    OSSignalSemaphore(&CARD_Sem[CARD_ExiChannel]);
}

u16 EXI_ResRead(u8* arg0, u16 arg1) {
    u8* sp8;
    u16 spE;
    u16 bruh = arg1;
    OSTick tick;

    if (EXI_LockAndSelect(CARD_ExiFreq[CARD_ExiChannel])) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    spE = 0;
    sp8 = arg0;
    (void)sp8;
    (void)bruh;
    (void)bruh;
    (void)bruh;

    sp8[0] = EXI_ClrData[CARD_ExiChannel];

    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    tick = OSGetTick();
    (void)tick;
    EXI_UnknownInline3(sp8, tick, 500);

    if (arg1 > sizeof(u8)) {
        *++sp8 = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, sp8, arg1 - 1, 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        }
    }

    return EXI_DeselectAndUnlock();
}

u16 EXI_StopResRead(u8* arg0, u16 arg1) {
    u8* sp8;
    s16 spE;
    u16 bruh = arg1;
    OSTick tick;

    if (EXI_LockAndSelect(CARD_ExiFreq[CARD_ExiChannel])) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    spE = 0;
    sp8 = arg0;
    (void)sp8;
    (void)bruh;
    (void)bruh;
    (void)bruh;

    sp8[0] = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    sp8[0] = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    tick = OSGetTick();
    EXI_UnknownInline3(sp8, tick, 1500);
    EXI_UnknownInline4(sp8, tick, 1500);

    sp8[0] = sp8[1];

    if (arg1 > sizeof(u8)) {
        *++sp8 = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, (u8*)sp8, arg1 - 1, 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        }
    }

    return EXI_DeselectAndUnlock();
}

u16 EXI_DataRes(u8* arg0) {
    u8* sp8;
    OSTick tick;
    int pad2;
    s16 spE;

    if (EXI_LockAndSelect(CARD_ExiFreq[CARD_ExiChannel])) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    spE = 0;
    pad2 = 0;
    (void)pad2;
    (void)pad2;
    (void)pad2;
    (void)pad2;
    (void)pad2;
    (void)pad2;
    (void)pad2;
    (void)pad2;
    (void)sp8;
    sp8 = arg0;

    sp8[0] = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    tick = OSGetTick();
    (void)tick;
    (void)tick;
    while (sp8[0] & 0x10) {
        sp8[0] = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
            return EXI_DeselectAndUnlock();
        }

        if (sp8[0] & 0x10) {
            if (EXI_CheckTimeOut(tick, 1500) == 0) {
                continue;
            }

            sp8[0] = EXI_ClrData[CARD_ExiChannel];

            if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
                return EXI_DeselectAndUnlock();
            }

            if (sp8[0] & 0x10) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_4000;
            }
        }

        break;
    }

    *++sp8 = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    tick = OSGetTick();
    (void)tick;
    (void)tick;

    while (sp8[0] == 0) {
        sp8[0] = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
            return EXI_DeselectAndUnlock();
        }

        if (sp8[0] == 0) {
            if (EXI_CheckTimeOut(tick, 1500) == 0) {
                continue;
            }

            sp8[0] = EXI_ClrData[CARD_ExiChannel];

            if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
                return EXI_DeselectAndUnlock();
            }

            if (sp8[0] == 0) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_4000;
            }
        }

        break;
    }

    return EXI_DeselectAndUnlock();
}

u16 EXI_MultiWriteStop(void) {
    OSTick tick;
    OSTick tick2;
    int i;
    u8 sp8[32];

    for (i = 0; i < 0x20; i++) {
        sp8[i] = EXI_ClrData[CARD_ExiChannel];
    }

    if (EXI_LockAndSelect(CARD_ExiFreq[CARD_ExiChannel])) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    sp8[0] = 0xFD;
    if ((s32)CARD_WP_Flag[CARD_ExiChannel] != 0) {
        sp8[0] = 2;
    }

    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 1) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    sp8[0] = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    sp8[0] = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    sp8[0] = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    sp8[0] = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    tick2 = OSGetTick();
    (void)tick2;
    (void)tick2;
    (void)tick2;
    (void)tick2;
    tick = OSGetTick();
    !tick;

    while (sp8[0] == 0) {
        sp8[0] = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
            return EXI_DeselectAndUnlock();
        }

        if (sp8[0] == 0) {
            if (EXI_CheckTimeOut(tick, 1500) == 0) {
                continue;
            }

            sp8[0] = EXI_ClrData[CARD_ExiChannel];

            if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 2) == 0) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
                return EXI_DeselectAndUnlock();
            }

            if (sp8[0] == 0) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_4000;
            }
        }

        break;
    }

    return EXI_DeselectAndUnlock();
}

u16 EXI_DataRead(u8* arg0, u16 arg1) {
    OSTick temp_r25;
    int var_r28;
    u8* var_r31;
    u16 sp12[CARD_NUM_CHANS];
    u8 sp10[CARD_NUM_CHANS];

    if (EXI_LockAndSelect(CARD_ExiFreq[CARD_ExiChannel])) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    var_r31 = arg0;
    for (var_r28 = 0; var_r28 < arg1; var_r28++) {
        *var_r31++ = EXI_ClrData[CARD_ExiChannel];
    }

    sp12[0] = sp12[1] = 0;

    if (EXIImmEx(CARD_ExiChannel, arg0, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    temp_r25 = OSGetTick();
    while (arg0[0] != 0xFE) {
        arg0[0] = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, arg0, sizeof(u8), 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
            return EXI_DeselectAndUnlock();
        }

        if (arg0[0] != 0xFE) {
            if (EXI_CheckTimeOut(temp_r25, 1500) == 0) {
                continue;
            }

            arg0[0] = EXI_ClrData[CARD_ExiChannel];

            if (EXIImmEx(CARD_ExiChannel, arg0, sizeof(u8), 2) == 0) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
                return EXI_DeselectAndUnlock();
            }

            if (arg0[0] != 0xFE) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_4000;
            }
        }

        break;
    }

    arg0[0] = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, arg0, arg1, 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    OSSetAlarm(&CARD_Alarm[CARD_ExiChannel], OSMicrosecondsToTicks(1), EXI_AlarmFunc);
    OSWaitSemaphore(&CARD_Sem[CARD_ExiChannel]);

    sp10[0] = EXI_ClrData[CARD_ExiChannel];
    sp10[1] = EXI_ClrData[CARD_ExiChannel];

    if (EXIImmEx(CARD_ExiChannel, &sp10, sizeof(u8) * 2, 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    sp12[0] = (sp10[0] << 8) & 0xFF00;
    sp12[0] += sp10[1];

    if (EXIDeselect(CARD_ExiChannel) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00E0;
    }

    if (EXIUnlock(CARD_ExiChannel) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00D0;
        CARD_ErrStatus[CARD_ExiChannel];
    }

    if (sp12[0] != EXI_MakeCRC16(arg0, arg1)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0002;
    }

    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 EXI_DataReadFinal(u8* arg0, u16 arg1) {
    int var_r28;
    u8* sp8;
    u8* var_r31;
    OSTick tick;
    u16 sp12[CARD_NUM_CHANS];
    u8 sp10[CARD_NUM_CHANS];
    u8 crc[6];
    int i;

    if (EXI_LockAndSelect(CARD_ExiFreq[CARD_ExiChannel])) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    var_r31 = arg0;
    for (var_r28 = 0; var_r28 < arg1; var_r28++) {
        *var_r31++ = EXI_ClrData[CARD_ExiChannel];
    }

    sp12[0] = sp12[1] = 0;

    arg0 = (u8*)var_r31;
    if (EXIImmEx(CARD_ExiChannel, arg0, sizeof(u8), 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    tick = OSGetTick();
    (void)tick;
    (void)tick;
    while (arg0[0] != 0xFE) {
        arg0[0] = EXI_ClrData[CARD_ExiChannel];

        if (EXIImmEx(CARD_ExiChannel, arg0, sizeof(u8), 2) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
            return EXI_DeselectAndUnlock();
        }

        if (arg0[0] != 0xFE) {
            if (EXI_CheckTimeOut(tick, 1500) == 0) {
                continue;
            }

            arg0[0] = EXI_ClrData[CARD_ExiChannel];

            if (EXIImmEx(CARD_ExiChannel, arg0, sizeof(u8), 2) == 0) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
                return EXI_DeselectAndUnlock();
            }

            if (arg0[0] != 0xFE) {
                CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_4000;
            }
        }

        break;
    }

    arg0[0] = EXI_ClrData[CARD_ExiChannel];
    if (EXIImmEx(CARD_ExiChannel, arg0, arg1 - 4, 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    crc[0] = 0x0C;
    crc[1] = 0x00;
    crc[2] = 0x00;
    crc[3] = 0x00;
    crc[4] = 0x00;
    crc[0] |= 0x40;
    crc[5] = EXI_MakeCRC7(crc, 5) | 1;

    if (CARD_WP_Flag[CARD_ExiChannel] != 0) {
        for (i = 0; i < 6; i++) {
            crc[i] = ~crc[i];
        }
    }

    if (EXIImmEx(CARD_ExiChannel, &sp10, 6, 2) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    arg0[arg1 - 4] = crc[0];
    arg0[arg1 - 3] = crc[1];
    arg0[arg1 - 2] = crc[2];
    arg0[arg1 - 1] = crc[3];
    sp10[0] = crc[4];
    sp10[1] = crc[5];

    OSSetAlarm(&CARD_Alarm[CARD_ExiChannel], OSMicrosecondsToTicks(1), EXI_AlarmFunc);
    OSWaitSemaphore(&CARD_Sem[CARD_ExiChannel]);

    sp12[0] = (sp10[0] << 8) & 0xFF00;
    sp12[0] += sp10[1];

    if (EXIDeselect(CARD_ExiChannel) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00E0;
    }

    if (EXIUnlock(CARD_ExiChannel) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00D0;
        CARD_ErrStatus[CARD_ExiChannel];
    }

    if (sp12[0] != EXI_MakeCRC16(arg0, arg1)) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_0002;
    }

    return CARD_ErrStatus[CARD_ExiChannel];
}

u16 EXI_CmdWrite0(u8* arg0, u16 arg1) {
    u8 sp18;
    s32 var_r30;
    u8* var_r29;
    u8* var_r27;
    u16 var_r26;
    int pad0;
    int pad1;

    pad0 = 0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)arg1;
    (void)arg1;

    EXI_ClrData[CARD_ExiChannel] = 0xFF;
    var_r29 = arg0;
    arg0[0] |= 0x40;

    sp18 = EXI_MakeCRC7(arg0, arg1);
    if (CARD_WP_Flag[CARD_ExiChannel] != 0) {
        EXI_ClrData[CARD_ExiChannel] = 0;

        for (var_r30 = 0; var_r30 < arg1; var_r30++) {
            *var_r29++ = ~(*var_r29);
        }

        var_r29 = arg0;
    }

    for (var_r26 = 0; var_r26 < arg1; var_r26++) {
        var_r29++;
    }

    var_r29 = arg0;
    for (var_r30 = 0; var_r30 < (s32)sizeof(SD_DUMMY); var_r30++) {
        !var_r29;
        SD_DUMMY[var_r30] = EXI_ClrData[CARD_ExiChannel];
    }

    EXI_Lock();
    EXI_SelectSD(CARD_ExiFreq[CARD_ExiChannel]);

    for (var_r30 = 0; var_r30 < 0x14; var_r30++) {
        if (EXIImmEx(CARD_ExiChannel, SD_DUMMY, sizeof(SD_DUMMY), 1) == 0) {
            CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
            return EXI_DeselectAndUnlock();
        }
    }

    EXIDeselect(CARD_ExiChannel);
    CARD_ErrStatus[CARD_ExiChannel] = CARD_ERROR_0000;
    EXI_Select(CARD_ExiFreq[CARD_ExiChannel]);

    if (EXIImmEx(CARD_ExiChannel, var_r29, arg1, 1) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    sp18 |= 1;
    if (CARD_WP_Flag[CARD_ExiChannel] != 0) {
        sp18 = ~sp18;
    }

    if (EXIImmEx(CARD_ExiChannel, &sp18, 1U, 1) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
    }

    return EXI_DeselectAndUnlock();
}

u16 EXI_CmdWrite(u8* arg0, u16 arg1) {
    s32 var_r30;
    u8* var_r29;
    u8* var_r27;
    u16 var_r26;
    int pad0;
    u8 sp18;
    u8 sp10[0x20];

    pad0 = 0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;

    (void)arg0;
    (void)arg1;
    (void)arg1;

    var_r29 = arg0;
    var_r29[0] |= 0x40;

    sp18 = EXI_MakeCRC7(var_r29, arg1);
    if (CARD_WP_Flag[CARD_ExiChannel] != 0) {
        for (var_r30 = 0; var_r30 < arg1; var_r30++) {
            *var_r29++ = ~(*var_r29);
        }

        var_r29 = arg0;
    }

    for (var_r26 = 0; var_r26 < arg1; var_r26++) {
        var_r29++;
    }

    var_r29 = arg0;

    if (EXI_LockAndSelect(CARD_ExiFreq[CARD_ExiChannel])) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    !var_r29;

    for (var_r30 = 0; var_r30 < 0x20; var_r30++) {
        sp10[var_r30] = EXI_ClrData[CARD_ExiChannel];
    }

    if (EXIImmEx(CARD_ExiChannel, &sp10, 0xA, 1) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    (void)arg0;
    (void)arg0;

    if (EXIImmEx(CARD_ExiChannel, arg0, arg1, 1) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    sp18 |= 1;
    if (CARD_WP_Flag[CARD_ExiChannel] != 0) {
        sp18 = ~sp18;
    }

    if (EXIImmEx(CARD_ExiChannel, &sp18, sizeof(u8), 1) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
    }

    return EXI_DeselectAndUnlock();
}

u16 EXI_MultiDataWrite(u8* arg0, u16 arg1) {
    int pad0;
    int pad1;
    int i;
    u8* volatile sp30;
    u8 sp8[32];
    u16 crc;

    (void)pad0;
    (void)pad0;
    (void)pad0;
    (void)pad0;

    for (i = 0; i < 0x20; i++) {
        sp8[i] = EXI_ClrData[CARD_ExiChannel];
    }

    crc = EXI_MakeCRC16(arg0, arg1);

    if (EXI_LockAndSelect(CARD_ExiFreq[CARD_ExiChannel])) {
        return CARD_ErrStatus[CARD_ExiChannel];
    }

    sp30 = arg0;
    sp8[0] = 0xFC;
    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8), 1) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    if (EXIImmEx(CARD_ExiChannel, sp30, arg1, 1) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
        return EXI_DeselectAndUnlock();
    }

    OSSetAlarm(&CARD_Alarm[CARD_ExiChannel], OSMicrosecondsToTicks(1), EXI_AlarmFunc);
    OSWaitSemaphore(&CARD_Sem[CARD_ExiChannel]);

    sp8[0] = crc >> 8;
    sp8[1] = crc;

    if (EXIImmEx(CARD_ExiChannel, sp8, sizeof(u8) * 2, 1) == 0) {
        CARD_ErrStatus[CARD_ExiChannel] |= CARD_ERROR_00F0;
    }

    return EXI_DeselectAndUnlock();
}

u8 EXI_MakeCRC7(u8* arg0, u16 arg1) {
    u16 i;
    u16 CRC;
    s32 j;
    u8* pData;
    u8 nMask;

    nMask = 0;
    CRC = 0;
    i = 0;
    pData = arg0;

    while (i < arg1) {
        nMask = 0x80;

        for (j = 0; j < 8; j++) {
            CRC <<= 1;

            if ((*pData ^ ((CRC & 0xFF) >> j)) & nMask) {
                CRC |= 1;

                if ((CRC ^ 8) & 8) {
                    CRC |= 8;
                } else {
                    CRC &= 0xFFF7;
                }
            } else {
                CRC &= 0xFFFE;

                if (CRC & 8) {
                    CRC |= 8;
                } else {
                    CRC &= 0xFFF7;
                }
            }

            nMask >>= 1;
        }

        CRC &= 0xFF;
        pData++;
        i++;
    }

    return CRC <<= 1;
}

u16 EXI_MakeCRC16(u8* arg0, u16 arg1) {
    u16 i;
    s32 j;
    u8* pData;
    u8 nMask;
    u8 nData;
    u8 pad0;
    volatile s32 CRC;
    volatile u16 spC;

    spC = arg1;
    nMask = 0;
    CRC = 0;
    i = 0;
    pData = arg0;

    (void)pad0;
    (void)pad0;
    (void)pad0;

    while (i < spC) {
        nData = *pData;
        nMask = 0x80;

        for (j = 0; j < 8; j++) {
            if ((nData ^ (((CRC & 0xFFFF) >> (j + 8)) & 0xFF)) & nMask) {
                CRC <<= 1;
                CRC |= 1;

                if ((CRC ^ 0x20) & 0x20) {
                    CRC |= 0x20;
                } else {
                    CRC &= ~0x20;
                }

                if ((CRC ^ 0x1000) & 0x1000) {
                    CRC |= 0x1000;
                } else {
                    CRC &= ~0x1000;
                }
            } else {
                CRC <<= 1;
                CRC &= ~1;

                if (CRC & 0x20) {
                    CRC |= 0x20;
                } else {
                    CRC &= ~0x20;
                }

                if (CRC & 0x1000) {
                    CRC |= 0x1000;
                } else {
                    CRC &= ~0x1000;
                }
            }

            nMask >>= 1;
        }

        CRC &= 0xFFFF;
        pData = pData + 1;
        i++;
    }

    return CRC;
}

s32 EXI_CheckTimeOut(u32 arg0, u32 arg1) {
    OSTick var_r31;
    OSTick temp_r3;

    if ((temp_r3 = OSGetTick()) < arg0) {
        var_r31 = 0xFFFFFFFF - arg0;
        var_r31 += 1 + temp_r3;
    } else {
        var_r31 = temp_r3 - arg0;
    }

    if (OSTicksToMilliseconds(var_r31) > arg1) {
        return 1;
    }

    return 0;
}
