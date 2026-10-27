#include "JSystem/JSystem.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTFader.h"
#include "JSystem/J2D/J2DGrafContext.h"
#include "JSystem/JFramework/JFWDisplay.h"
#include "JSystem/JFramework/JFWSystem.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JUtility/JUTFont.h"

#include "MSL_C/printf.h"

extern "C" {
#include "../src/static/libjsys/jsyswrapper_main.cpp"
}

extern "C" void JC_JUTConsole_print_f_va(void* console, const char* fmt, va_list arg) {
    reinterpret_cast<JUTConsole*>(console)->print_f_va(fmt, arg);
}

extern "C" void JC_JUTConsole_print_f(void* console, const char* fmt, ...) {
    va_list arg;

    va_start(arg, fmt);
    JC_JUTConsole_print_f_va(console, fmt, arg);
    va_end(arg);
}

void enter_(int x, int y, int show_count, const char* fmt, va_list arg);

extern "C" void JW_JUTReport(int x, int y, int show_count, const char* fmt, ...) {
    va_list arg;

    va_start(arg, fmt);
    enter_(x, y, show_count, fmt, arg);
    va_end(arg);
}

void enter_(int x, int y, int show_count, const char* fmt, va_list arg) {
    JUTDbPrint* dbprint = JUTDbPrint::getManager();

    if (dbprint == nullptr || !dbprint->isVisible()) {
        return;
    }

    char buf[256];
    int len = vsnprintf(buf, sizeof(buf), fmt, arg);

    if (len >= 0) {
        dbprint->enter(x, y, show_count, buf, len >= (int)sizeof(buf) ? sizeof(buf) - 1 : len);
    }
}

extern "C" void* JW_Alloc(size_t size, int align) {
    return JC_JKRHeap_alloc(JC_JFWSystem_getSystemHeap(), size, align);
}

extern "C" s32 JW_Resize(void* ptr, size_t new_size) {
    return JC_JKRHeap_resize(JC_JFWSystem_getSystemHeap(), ptr, new_size);
}

extern "C" void JW_Free(void* ptr) {
    JC_JKRHeap_free(JC_JFWSystem_getSystemHeap(), ptr);
}

extern "C" size_t JW_GetMemBlockSize(void* ptr) {
    return JC_JKRHeap_getSize(JC_JFWSystem_getSystemHeap(), ptr);
}

extern "C" void JW_JUTXfb_clearIndex(void) {
    JC_JUTXfb_clearIndex(JC_JUTXfb_getManager());
}
