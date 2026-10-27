#ifndef _DOLPHIN_DVD_INTERNAL_H_
#define _DOLPHIN_DVD_INTERNAL_H_

#include <dolphin/dvd.h>

// dvd.c
BOOL DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback, s32 prio);
BOOL DVDSeekAbsAsyncPrio(DVDCommandBlock* block, s32 offset, DVDCBCallback callback, s32 prio);
BOOL DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback);
BOOL DVDReadDiskID(DVDCommandBlock* block, DVDDiskID* diskID, DVDCBCallback callback);
BOOL DVDPrepareStreamAbsAsync(DVDCommandBlock* block, u32 length, u32 offset, DVDCBCallback callback);
BOOL DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback);
BOOL DVDInquiryAsync(DVDCommandBlock* block, DVDDriveInfo* info, DVDCBCallback callback);
BOOL __DVDTestAlarm(OSAlarm* alarm);
void __DVDAudioBufferConfig(struct DVDCommandBlock * block, unsigned long enable, unsigned long size, void (* callback)(long, struct DVDCommandBlock *));
void __DVDPrepareResetAsync(DVDCBCallback callback);

// dvdFatal.c
void __DVDPrintFatalMessage(void);

// dvderror.c
void __DVDStoreErrorCode(u32 error);

// dvdfs.c
extern struct OSThreadQueue __DVDThreadQueue;
extern unsigned long __DVDLongFileNameFlag;

void __DVDFSInit();

// dvdlow.c
void __DVDInitWA(void);
void __DVDInterruptHandler(short unused, struct OSContext * context);
void __DVDLowSetWAType(u32 type, u32 location);
BOOL DVDLowRead(void* addr, u32 length, u32 offset, DVDLowCallback callback);
BOOL DVDLowSeek(u32 offset, DVDLowCallback callback);
BOOL DVDLowWaitCoverClose(DVDLowCallback callback);
BOOL DVDLowReadDiskID(DVDDiskID* diskID, DVDLowCallback callback);
BOOL DVDLowStopMotor(DVDLowCallback callback);
BOOL DVDLowRequestError(DVDLowCallback callback);
BOOL DVDLowInquiry(DVDDriveInfo* info, DVDLowCallback callback);
BOOL DVDLowAudioStream(u32 subcmd, u32 length, u32 offset, DVDLowCallback callback);
BOOL DVDLowRequestAudioStatus(u32 subcmd, DVDLowCallback callback);
BOOL DVDLowAudioBufferConfig(BOOL enable, u32 size, DVDLowCallback callback);
void DVDLowReset(void);
BOOL DVDLowBreak(void);
BOOL __DVDLowTestAlarm(OSAlarm* alarm);

// dvdqueue.c
void __DVDClearWaitingQueue();
int __DVDPushWaitingQueue(long prio, struct DVDCommandBlock * block);
struct DVDCommandBlock * __DVDPopWaitingQueue();
int __DVDCheckWaitingQueue();
int __DVDDequeueWaitingQueue(struct DVDCommandBlock * block);
int __DVDIsBlockInWaitingQueue(struct DVDCommandBlock * block);

// fstload.c
void __fstLoad();

#endif // _DOLPHIN_DVD_INTERNAL_H_
