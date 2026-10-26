#ifndef JSYSWRAP_JKRARAMSTREAM_H
#define JSYSWRAP_JKRARAMSTREAM_H

#include "JSystem/JKernel/JKRAram.h"

inline void JKRSetAramTransferBuffer(u8* buf, u32 size, JKRHeap* heap) {
    JKRAramStream::setTransBuffer(buf, size, heap);
}

#endif
