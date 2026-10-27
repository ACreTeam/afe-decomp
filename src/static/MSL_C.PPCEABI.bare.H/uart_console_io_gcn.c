#include "PowerPC_EABI_Support/MSL_C/MSL_Common/ansi_files.h"

typedef int UARTError;

UARTError InitializeUART(u32 baudRate);
UARTError WriteUARTN(const void* buf, u32 len);
u32 OSGetConsoleType(void);
int __TRK_write_console(__file_handle handle, char* buffer, size_t* count, __ref_con ref_con);

int __write_console(__file_handle handle, char* buffer, size_t* count, __ref_con ref_con)
{
	static int initialized;

	if ((OSGetConsoleType() & 0x20000000) == 0) {
		UARTError err = 0;

		if (initialized == 0) {
			err = InitializeUART(0xE100);

			if (err == 0) {
				initialized = 1;
			}
		}

		if (err != 0) {
			return 1;
		}

		if (WriteUARTN(buffer, *count) != 0) {
			*count = 0;
			return 1;
		}
	}

	__TRK_write_console(handle, buffer, count, ref_con);
	return 0;
}

int __close_console(__file_handle handle)
{
	return 0;
}
