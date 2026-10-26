#include "TRK/trk.h"

static DSError TRK_mainError;

DSError TRK_main(void)
{
	MWTRACE(1, "TRK_Main \n");
	TRK_mainError = TRKInitializeNub();

	if (TRK_mainError == DS_NoError) {
		TRKNubWelcome();
		TRKNubMainLoop();
	}

	TRK_mainError = TRKTerminateNub();

	return TRK_mainError;
}
