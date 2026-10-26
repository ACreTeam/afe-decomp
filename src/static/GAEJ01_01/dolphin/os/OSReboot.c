#include <dolphin/os.h>
#include <dolphin/dvd.h>
#include <dolphin/ai.h>
#include "../src/static/GAEJ01_01/dolphin/dvd/__dvd.h"
#include "../src/static/GAEJ01_01/dolphin/os/__os.h"

static void* SaveStart = NULL;
static void* SaveEnd   = NULL;
static BOOL Prepared;

extern u32 OS_RESET_CODE AT_ADDRESS(0x800030F0);
// unknown function, set to true by __OSReboot
extern u8 OS_REBOOT_BOOL AT_ADDRESS(0x800030E2);
extern BOOL __OSIsGcam;

#define OS_BOOTROM_ADDR ((void*)0x81300000)

typedef struct _ApploaderHeader {
	/* 0x00 */ char date[16];
	/* 0x10 */ u32 entry;
	/* 0x14 */ u32 size;
	/* 0x18 */ u32 rebootSize;
	/* 0x1C */ u32 reserved2;
} ApploaderHeader; // Size: 0x20

static ApploaderHeader Header __attribute__((aligned(32)));

static BOOL IsStreamEnabled(void)
{
	if (DVDGetCurrentDiskID()->streaming) {
		return TRUE;
	}
	return FALSE;
}

static asm void Run(register void* addr)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc

	sync
	isync
	mtlr addr
	blr
#endif // clang-format on
}

static void ReadApploader(OSTime time1)
{
	if (!DVDCheckDisk() || OSGetTime() - time1 > OS_TIMER_CLOCK) {
		__OSDoHotReset(0);
	}
}

static void Callback(s32 result, struct DVDCommandBlock* block)
{
	Prepared = TRUE;
}

void __OSReboot(u32 resetCode, u32 bootDol)
{
	OSContext exceptionContext;
	OSTime time1;
	DVDCommandBlock dvdCmd;
	DVDCommandBlock dvdCmd2;
	DVDCommandBlock dvdCmd3;
	u32 numBytes;
	u32 offset;

	OSDisableInterrupts();
	OS_RESET_CODE     = resetCode;
	OS_REBOOT_BOOL    = TRUE;
	BOOT_REGION_START = SaveStart;
	BOOT_REGION_END   = SaveEnd;
	OSClearContext(&exceptionContext);
	OSSetCurrentContext(&exceptionContext);
	DVDInit();
	DVDSetAutoInvalidation(TRUE);
	DVDResume();

	Prepared = FALSE;
	__DVDPrepareResetAsync(Callback);

	__OSMaskInterrupts(0xffffffe0);
	__OSUnmaskInterrupts(0x400);
	OSEnableInterrupts();

	time1 = OSGetTime();
	while (Prepared != TRUE) {
		ReadApploader(time1);
	}

	if (!__OSIsGcam) {
		if (IsStreamEnabled()) {
			AISetStreamVolLeft(0);
			AISetStreamVolRight(0);
			DVDCancelStreamAsync(&dvdCmd, NULL);
			time1 = OSGetTime();
			while (DVDGetCommandBlockStatus(&dvdCmd)) {
				ReadApploader(time1);
			}

			AISetStreamPlayState(0);
		}
	}

	DVDReadAbsAsyncPrio(&dvdCmd2, Header.date, 32, 0x2440, NULL, 0);

	time1 = OSGetTime();
	while (DVDGetCommandBlockStatus(&dvdCmd2)) {
		ReadApploader(time1);
	}

	offset   = Header.size + 0x20;
	numBytes = OSRoundUp32B(Header.rebootSize);
	DVDReadAbsAsyncPrio(&dvdCmd3, OS_BOOTROM_ADDR, numBytes, offset + 0x2440, NULL, 0);

	time1 = OSGetTime();
	while (DVDGetCommandBlockStatus(&dvdCmd3)) {
		ReadApploader(time1);
	}

	ICInvalidateRange(OS_BOOTROM_ADDR, numBytes);
	OSDisableInterrupts();
	ICFlashInvalidate();
	Run(OS_BOOTROM_ADDR);
}

void OSSetSaveRegion(void* start, void* end)
{
	SaveStart = start;
	SaveEnd   = end;
}

void OSGetSaveRegion(void** start, void** end)
{
	*start = SaveStart;
	*end   = SaveEnd;
}
