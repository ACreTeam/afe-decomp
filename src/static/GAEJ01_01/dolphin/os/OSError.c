// The shared headers still declare the pre-FPE (16 entry) error table.
#define __OSErrorTable __OSErrorTable16
#include "dolphin/os.h"
#include "dolphin/os/OSError.h"
#include "dolphin/os/OSException.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/base/PPCArch.h"
#include "dolphin/hw_regs.h"

#include "../src/static/GAEJ01_01/dolphin/os/__os.h"
#undef __OSErrorTable

// All enable
#define FPSCR_ENABLE 0xF8

#define FPSCR_FX     0x80000000 // Exception summary
#define FPSCR_OX     0x10000000 // Overflow exception
#define FPSCR_UX     0x08000000 // Underflow exception
#define FPSCR_ZX     0x04000000 // Zero divide exception
#define FPSCR_XX     0x02000000 // Inexact exception
#define FPSCR_VXSNAN 0x01000000 // SNaN
#define FPSCR_VXISI  0x00800000 // Infinity - Infinity
#define FPSCR_VXIDI  0x00400000 // Infinity / Infinity
#define FPSCR_VXZDZ  0x00200000 // 0 / 0
#define FPSCR_VXIMZ  0x00100000 // Infinity * 0
#define FPSCR_VXVC   0x00080000 // Invalid compare
#define FPSCR_FI     0x00020000 // Fraction inexact
#define FPSCR_VXSOFT 0x00000400 // Software request
#define FPSCR_VXSQRT 0x00000200 // Invalid square root
#define FPSCR_VXCVI  0x00000100 // Invalid integer convert
#define FPSCR_NI     0x00000004 // Non-IEEE mode

u32 PPCMffpscr(void);
void PPCMtfpscr(u32 newFPSCR);

OSErrorHandler __OSErrorTable[OS_ERROR_FPE + 1];
u32 __OSFpscrEnableBits = FPSCR_ENABLE;

__declspec(weak) void OSReport(const char* msg, ...) {
    va_list marker;
    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
}

__declspec(weak) void OSPanic(const char* file, int line, const char* msg, ...) {
    va_list marker;
    u32 i;
    u32* p;

    OSDisableInterrupts();
    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
    OSReport(" in \"%s\" on line %d.\n", file, line);

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (u32*)OSGetStackPointer(); p && (u32)p != 0xffffffff && i++ < 16; p = (u32*)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }

    PPCHalt();
}

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler) {
    OSErrorHandler oldHandler;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    oldHandler = __OSErrorTable[error];
    __OSErrorTable[error] = handler;

    if (error == OS_ERROR_FPE) {
        u32 msr;
        u32 fpscr;
        OSThread* thread;

        msr = PPCMfmsr();
        PPCMtmsr(msr | MSR_FP);
        fpscr = PPCMffpscr();
        if (handler) {
            for (thread = __OSActiveThreadQueue.head; thread; thread = thread->linkActive.next) {
                thread->context.srr1 |= MSR_FE0 | MSR_FE1;
                if ((thread->context.state & OS_CONTEXT_STATE_FPSAVED) == 0) {
                    int i;

                    thread->context.state |= OS_CONTEXT_STATE_FPSAVED;
                    for (i = 0; i < 32; ++i) {
                        *(u64*)&thread->context.fpr[i] = (u64)0xffffffffffffffffLL;
                        *(u64*)&thread->context.psf[i] = (u64)0xffffffffffffffffLL;
                    }
                    thread->context.fpscr = FPSCR_NI;
                }
                thread->context.fpscr |= __OSFpscrEnableBits & FPSCR_ENABLE;
                thread->context.fpscr &= 0x6005F8FF;
            }
            fpscr |= __OSFpscrEnableBits & FPSCR_ENABLE;
            msr |= MSR_FE0 | MSR_FE1;
        } else {
            for (thread = __OSActiveThreadQueue.head; thread; thread = thread->linkActive.next) {
                thread->context.srr1 &= ~(MSR_FE0 | MSR_FE1);
                thread->context.fpscr &= ~FPSCR_ENABLE;
                thread->context.fpscr &= 0x6005F8FF;
            }
            fpscr &= ~FPSCR_ENABLE;
            msr &= ~(MSR_FE0 | MSR_FE1);
        }

        fpscr &= 0x6005F8FF;

        PPCMtfpscr(fpscr);
        PPCMtmsr(msr);
    }

    OSRestoreInterrupts(enabled);
    return oldHandler;
}

void __OSUnhandledException(__OSException exception, OSContext* context, u32 dsisr, u32 dar) {
    OSTime now;

    now = OSGetTime();

    if (!(context->srr1 & MSR_RI)) {
        OSReport("Non-recoverable Exception %d", exception);
    } else {
        if (exception == __OS_EXCEPTION_PROGRAM && (context->srr1 & (0x80000000 >> 11)) && __OSErrorTable[OS_ERROR_FPE] != NULL) {
            u32 fpscr;
            u32 msr;

            exception = OS_ERROR_FPE;

            msr = PPCMfmsr();
            PPCMtmsr(msr | MSR_FP);

            if (__OSFPUContext) {
                OSSaveFPUContext((OSContext*)__OSFPUContext);
            }

            fpscr = PPCMffpscr();
            fpscr &= ~(FPSCR_VXVC | FPSCR_VXIMZ | FPSCR_VXZDZ | FPSCR_VXIDI | FPSCR_VXISI | FPSCR_VXSNAN | FPSCR_VXSOFT | FPSCR_VXSQRT
                       | FPSCR_VXCVI | FPSCR_XX | FPSCR_ZX | FPSCR_UX | FPSCR_OX | FPSCR_FX | FPSCR_FI);
            PPCMtfpscr(fpscr);

            PPCMtmsr(msr);

            if (__OSFPUContext == context) {
                OSDisableScheduler();
                __OSErrorTable[exception](exception, context, dsisr, dar);
                context->srr1 &= ~MSR_FP;
                __OSFPUContext = NULL;

                context->fpscr &= ~(FPSCR_VXVC | FPSCR_VXIMZ | FPSCR_VXZDZ | FPSCR_VXIDI | FPSCR_VXISI | FPSCR_VXSNAN | FPSCR_VXSOFT
                                    | FPSCR_VXSQRT | FPSCR_VXCVI | FPSCR_XX | FPSCR_ZX | FPSCR_UX | FPSCR_OX | FPSCR_FX | FPSCR_FI);
                OSEnableScheduler();
                __OSReschedule();
            } else {
                context->srr1 &= ~MSR_FP;
                __OSFPUContext = NULL;
            }

            OSLoadContext(context);
        }

        if (__OSErrorTable[exception]) {
            OSDisableScheduler();
            __OSErrorTable[exception](exception, context, dsisr, dar);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }

        if (exception == __OS_EXCEPTION_DECREMENTER) {
            OSLoadContext(context);
        }

        OSReport("Unhandled Exception %d", exception);
    }

    OSReport("\n");
    OSDumpContext(context);
    OSReport("\nDSISR = 0x%08x                   DAR  = 0x%08x\n", dsisr, dar);
    OSReport("TB = 0x%016llx\n", now);

    switch (exception) {
        case __OS_EXCEPTION_DSI:
            OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                     "invalid address 0x%x (read from DAR)\n",
                     context->srr0, dar);
            break;
        case __OS_EXCEPTION_ISI:
            OSReport("\nAttempted to fetch instruction from invalid address 0x%x "
                     "(read from SRR0)\n",
                     context->srr0);
            break;
        case __OS_EXCEPTION_ALIGNMENT:
            OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                     "unaligned address 0x%x (read from DAR)\n",
                     context->srr0, dar);
            break;
        case __OS_EXCEPTION_PROGRAM:
            OSReport("\nProgram exception : Possible illegal instruction/operation "
                     "at or around 0x%x (read from SRR0)\n",
                     context->srr0, dar);
            break;
        case OS_ERROR_PROTECTION:
            OSReport("\n");
            OSReport("AI DMA Address =   0x%04x%04x\n", __DSPRegs[24], __DSPRegs[25]);
            OSReport("ARAM DMA Address = 0x%04x%04x\n", __DSPRegs[16], __DSPRegs[17]);
            OSReport("DI DMA Address =   0x%08x\n", __DIRegs[5]);
            break;
    }

    OSReport("\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n", __OSLastInterrupt, __OSLastInterruptSrr0,
             __OSLastInterruptTime);
    PPCHalt();
}
