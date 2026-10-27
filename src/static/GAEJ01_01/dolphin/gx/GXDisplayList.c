#include <libc/string.h>

#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "../src/static/GAEJ01_01/dolphin/gx/__gx.h"

static __GXFifoObj DisplayListFifo;
static volatile __GXFifoObj* OldCPUFifo;
static GXData __savedGXdata;

void GXBeginDisplayList(void* list, u32 size)
{
    __GXFifoObj* CPUFifo = (__GXFifoObj*)GXGetCPUFifo();

    if (gx->dirtyState != 0) {
        __GXSetDirtyState();
    }

    if (gx->dlSaveContext != 0) {
        memcpy(&__savedGXdata, gx, sizeof(__savedGXdata));
    }

    DisplayListFifo.base  = (u8*)list;
    DisplayListFifo.top   = (u8*)list + size - 4;
    DisplayListFifo.size  = size;
    DisplayListFifo.count = 0;
    DisplayListFifo.rdPtr = list;
    DisplayListFifo.wrPtr = list;
    gx->inDispList        = 1;
    GXSaveCPUFifo((GXFifoObj*)CPUFifo);
    OldCPUFifo = CPUFifo;
    GXSetCPUFifo((GXFifoObj*)&DisplayListFifo);
    GXResetWriteGatherPipe();
}

u32 GXEndDisplayList(void)
{
    u32 ov;
    BOOL enabled;
    u32 cpenable;

    GXFlush();
    ov = (GX_GET_PI_REG(5) >> 26) & 1;
    __GXSaveCPUFifoAux((GXFifoObj*)&DisplayListFifo);
    GXSetCPUFifo((GXFifoObj*)OldCPUFifo);

    if (gx->dlSaveContext != 0) {
        enabled  = OSDisableInterrupts();
        cpenable = gx->cpEnable;
        memcpy(gx, &__savedGXdata, sizeof(*gx));
        gx->cpEnable = cpenable;
        OSRestoreInterrupts(enabled);
    }

    gx->inDispList = 0;
    if (!ov) {
        return DisplayListFifo.count;
    }

    return 0;
}

void GXCallDisplayList(void* list, u32 nbytes)
{
    if (gx->dirtyState) {
        __GXSetDirtyState();
    }

    if (GX_CHECK_FLUSH()) {
        __GXSendFlushPrim();
    }

    GX_WRITE_U8(GX_FIFO_CMD_CALL_DL);
    GX_WRITE_U32((u32)list);
    GX_WRITE_U32(nbytes);
}
