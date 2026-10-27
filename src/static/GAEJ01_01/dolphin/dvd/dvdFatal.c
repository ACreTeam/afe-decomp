#include <dolphin.h>
#include <dolphin/dvd.h>

#include "../src/static/GAEJ01_01/dolphin/dvd/__dvd.h"

static void (*FatalFunc)();

void __DVDPrintFatalMessage(void) {
    if (FatalFunc) {
        (*FatalFunc)();
    }
}
