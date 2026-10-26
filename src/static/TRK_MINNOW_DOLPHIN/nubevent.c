#include "TRK/trk.h"

TRKEventQueue gTRKEventQueue;

DSError TRKInitializeEventQueue()
{
	TRKInitializeMutex(&gTRKEventQueue);
	TRKAcquireMutex(&gTRKEventQueue);
	gTRKEventQueue.count   = 0;
	gTRKEventQueue.next    = 0;
	gTRKEventQueue.eventID = 0x100;
	TRKReleaseMutex(&gTRKEventQueue);
	return DS_NoError;
}

void TRKCopyEvent(void)
{
	// UNUSED FUNCTION
}

BOOL TRKGetNextEvent(TRKEvent* ev)
{
	BOOL ret = FALSE;

	TRKAcquireMutex(&gTRKEventQueue);

	if (gTRKEventQueue.count > 0) {
		TRK_memcpy(ev, &gTRKEventQueue.events[gTRKEventQueue.next], sizeof(TRKEvent));
		gTRKEventQueue.count--;

		if (++gTRKEventQueue.next == 2) {
			gTRKEventQueue.next = 0;
		}

		ret = TRUE;
	}

	TRKReleaseMutex(&gTRKEventQueue);
	return ret;
}

DSError TRKPostEvent(TRKEvent* event)
{
	DSError ret = DS_NoError;
	int nextEventID;

	TRKAcquireMutex(&gTRKEventQueue);

	if (gTRKEventQueue.count == 2) {
		ret = DS_EventQueueFull;

	} else {
		nextEventID = (gTRKEventQueue.next + gTRKEventQueue.count) % 2;
		TRK_memcpy(&gTRKEventQueue.events[nextEventID], event, sizeof(TRKEvent));
		gTRKEventQueue.events[nextEventID].eventID = gTRKEventQueue.eventID;

		if (++gTRKEventQueue.eventID < 0x100) {
			gTRKEventQueue.eventID = 0x100;
		}

		gTRKEventQueue.count++;
	}

	TRKReleaseMutex(&gTRKEventQueue);
	return ret;
}

void TRKConstructEvent(TRKEvent* event, int eventType)
{
	event->eventType = eventType;
	event->eventID   = 0;
	event->msgBufID  = -1;
}

void TRKDestructEvent(TRKEvent* event)
{
	TRKReleaseBuffer(event->msgBufID);
}
