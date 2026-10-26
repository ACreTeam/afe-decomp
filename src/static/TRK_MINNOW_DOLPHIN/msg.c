#include "TRK/trk.h"

DSError TRKMessageSend(MessageBuffer* msg)
{
	DSError writeErr = TRKWriteUARTN(&msg->data, msg->length);
	MWTRACE(1, "MessageSend : cc_write returned %ld\n", writeErr);
	return DS_NoError;
}
