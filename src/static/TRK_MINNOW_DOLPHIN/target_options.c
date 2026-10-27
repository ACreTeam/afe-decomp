#include "TRK/trk.h"

static u8 bUseSerialIO;

void SetUseSerialIO(u8 sio)
{
	bUseSerialIO = sio;
	return;
}

u8 GetUseSerialIO(void)
{
	return bUseSerialIO;
}
