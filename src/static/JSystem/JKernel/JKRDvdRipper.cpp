#include "_mem.h"
#include "types.h"
#include "dolphin/vi.h"
#include "JSystem/JSystem.h"
#include "JSystem/JKernel/JKRMacro.h"
#include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JKernel/JKRDecomp.h"

#include "JSystem/JKernel/JKRDvdRipper.h"

static u8* firstSrcData();
static u8* nextSrcData(u8* src);
static int decompSZS_subroutine(u8* src, u8* dest);

JSUList<JKRDMCommand> JKRDvdRipper::sDvdAsyncList;
static OSMutex decompMutex;
bool JKRDvdRipper::errorRetry = true;
int JKRDvdRipper::sSZSBufferSize = 0x400;

static u8* szpBuf;
static u8* szpEnd;
static u8* refBuf;
static u8* refEnd;
static u8* refCurrent;
static u32 srcOffset;
static u32 transLeft;
static u8* srcLimit;
static JKRDvdFile* srcFile;
static u32 fileOffset;
static u32 readCount;
static u32 maxDest;
static bool isInitMutex;
static u32* tsPtr;
static u32 tsArea;

void* JKRDvdRipper::loadToMainRAM(const char* fileName, u8* buf, JKRExpandSwitch expandSwitch, u32 maxSize,
                                  JKRHeap* heap, EAllocDirection allocDir, u32 offset, int* pCompression,
                                  u32* pSize) {
    JKRDvdFile dvdFile;
    if (!dvdFile.open(fileName)) {
        return nullptr;
    } else {
        return loadToMainRAM(&dvdFile, buf, expandSwitch, maxSize, heap, allocDir, offset, pCompression, pSize);
    }
}

void* JKRDvdRipper::loadToMainRAM(s32 entryNum, u8* buf, JKRExpandSwitch expandSwitch, u32 maxSize, JKRHeap* heap,
                                  EAllocDirection allocDir, u32 offset, int* pCompression, u32* pSize) {
    JKRDvdFile dvdFile;
    if (!dvdFile.open(entryNum)) {
        return nullptr;
    } else {
        return loadToMainRAM(&dvdFile, buf, expandSwitch, maxSize, heap, allocDir, offset, pCompression, pSize);
    }
}

void* JKRDvdRipper::loadToMainRAM(JKRDvdFile* dvdFile, u8* buf, JKRExpandSwitch expandSwitch, u32 maxSize,
                                  JKRHeap* heap, EAllocDirection allocDir, u32 offset, int* pCompression,
                                  u32* pSize) {
    s32 fileSizeAligned;
    bool hasAllocated = false;
    int compression = JKRCOMPRESSION_NONE;
    u32 expandSize;
    u8* mem = nullptr;

    fileSizeAligned = ALIGN_NEXT(dvdFile->getFileSize(), 32);
    if (expandSwitch == EXPAND_SWITCH_DECOMPRESS) {
        u8 buffer[0x40];
        u8* bufPtr = (u8*)ALIGN_NEXT((u32)buffer, 32);
        while (true) {
            int readBytes = DVDReadPrio(dvdFile->getFileInfo(), bufPtr, 0x20, 0, 2);
            if (readBytes >= 0) {
                break;
            }

            if (readBytes == -3 || errorRetry == false) {
                return nullptr;
            }

            VIWaitForRetrace();
        }
        DCInvalidateRange(bufPtr, 0x20);

        compression = JKRCheckCompressed_noASR(bufPtr);
        expandSize = JKRDecompExpandSize(bufPtr);
    }

    if (pCompression) {
        *pCompression = compression;
    }

    if (expandSwitch == EXPAND_SWITCH_DECOMPRESS && compression != JKRCOMPRESSION_NONE) {
        if (maxSize != 0 && expandSize > maxSize) {
            expandSize = maxSize;
        }
        if (buf == nullptr) {
            buf = (u8*)JKRAllocFromHeap(heap, expandSize, allocDir == ALLOC_DIR_TOP ? 32 : -32);
            hasAllocated = true;
        }
        if (buf == nullptr) {
            return nullptr;
        }
        if (compression == JKRCOMPRESSION_YAY0) {
            mem = (u8*)JKRAllocFromHeap(heap, fileSizeAligned, 32);
            if (mem == nullptr) {
                if (hasAllocated == true) {
                    JKRFree(buf);
                    return nullptr;
                }
            }
        }
    } else {
        if (buf == nullptr) {
            u32 size = fileSizeAligned - offset;
            if (maxSize != 0 && size > maxSize) {
                size = maxSize;
            }

            buf = (u8*)JKRAllocFromHeap(heap, size, allocDir == ALLOC_DIR_TOP ? 32 : -32);
            hasAllocated = true;
        }
        if (buf == nullptr) {
            return nullptr;
        }
    }

    if (compression == JKRCOMPRESSION_NONE) {
        int compression2 = JKRCOMPRESSION_NONE;

        if (offset != 0) {
            u8 buffer[0x40];
            u8* bufPtr = (u8*)ALIGN_NEXT((u32)buffer, 32);
            while (true) {
                int readBytes = DVDReadPrio(dvdFile->getFileInfo(), bufPtr, 32, (s32)offset, 2);
                if (readBytes >= 0) {
                    break;
                }

                if (readBytes == -3 || !errorRetry) {
                    if (hasAllocated == true) {
                        JKRFree(buf);
                    }
                    return nullptr;
                }
                VIWaitForRetrace();
            }
            DCInvalidateRange(bufPtr, 32);

            compression2 = JKRCheckCompressed_noASR(bufPtr);
        }

        if ((compression2 == JKRCOMPRESSION_NONE || expandSwitch == EXPAND_SWITCH_NONE) ||
            expandSwitch == EXPAND_SWITCH_DEFAULT) {
            s32 size = fileSizeAligned - offset;
            if (maxSize != 0 && maxSize < size) {
                size = maxSize;
            }

            while (true) {
                int readBytes = DVDReadPrio(dvdFile->getFileInfo(), buf, size, (s32)offset, 2);
                if (readBytes >= 0) {
                    break;
                }

                if (readBytes == -3 || !errorRetry) {
                    if (hasAllocated == true) {
                        JKRFree(buf);
                    }
                    return nullptr;
                }
                VIWaitForRetrace();
            }

            if (pSize) {
                *pSize = size;
            }
            return buf;
        } else if (compression2 == JKRCOMPRESSION_YAZ0) {
            JKRDecompressFromDVD(dvdFile, buf, fileSizeAligned, maxSize, 0, offset, pSize);
        } else {
            JPANIC(323, "Sorry, not applied for SZP archive.");
        }
        return buf;
    } else if (compression == JKRCOMPRESSION_YAY0) {
        if (offset != 0) {
            JPANIC(333, "Not support SZP with offset read");
        }

        while (true) {
            int readBytes = DVDReadPrio(dvdFile->getFileInfo(), mem, fileSizeAligned, 0, 2);
            if (readBytes >= 0) {
                break;
            }

            if (readBytes == -3 || !errorRetry) {
                if (hasAllocated == true) {
                    JKRFree(buf);
                }

                JKRFree(mem);
                return nullptr;
            }
            VIWaitForRetrace();
        }
        DCInvalidateRange(mem, fileSizeAligned);
        JKRDecompress(mem, buf, expandSize, offset);
        JKRFree(mem);
        if (pSize) {
            *pSize = expandSize;
        }
        return buf;
    } else if (compression == JKRCOMPRESSION_YAZ0) {
        if (JKRDecompressFromDVD(dvdFile, buf, fileSizeAligned, expandSize, offset, 0, pSize) != 0u) {
            if (hasAllocated) {
                JKRFree(buf);
            }
            buf = nullptr;
        }
        return buf;
    } else if (hasAllocated) {
        JKRFree(buf);
        buf = nullptr;
    }
    return nullptr;
}

int JKRDecompressFromDVD(JKRDvdFile* file, void* dst, u32 size, u32 inMaxDest, u32 inFileOffset, u32 inSrcOffset,
                         u32* inTsPtr) {
    BOOL interrupts = OSDisableInterrupts();
    if (isInitMutex == false) {
        OSInitMutex(&decompMutex);
        isInitMutex = true;
    }
    OSRestoreInterrupts(interrupts);
    OSLockMutex(&decompMutex);

    int bufSize = JKRDvdRipper::getSZSBufferSize();
    szpBuf = (u8*)JKRAllocFromSysHeap(bufSize, -0x20);
    JUT_ASSERT(szpBuf != 0);
    szpEnd = szpBuf + bufSize;

    if (inFileOffset != 0) {
        refBuf = (u8*)JKRAllocFromSysHeap(REF_BUFFERSIZE, -4);
        JUT_ASSERT(refBuf != 0);
        refEnd = refBuf + REF_BUFFERSIZE;
        refCurrent = refBuf;
    } else {
        refBuf = nullptr;
    }

    srcFile = file;
    srcOffset = inSrcOffset;
    transLeft = size - inSrcOffset;
    fileOffset = inFileOffset;
    readCount = 0;
    maxDest = inMaxDest;
    if (!inTsPtr) {
        tsPtr = &tsArea;
    } else {
        tsPtr = inTsPtr;
    }
    *tsPtr = 0;

    u8* data = firstSrcData();
    u32 result = (data != nullptr) ? decompSZS_subroutine(data, (u8*)dst) : -1;
    JKRFree(szpBuf);
    if (refBuf) {
        JKRFree(refBuf);
    }
    DCStoreRangeNoSync(dst, *tsPtr);
    OSUnlockMutex(&decompMutex);
    return result;
}

static int decompSZS_subroutine(u8* src, u8* dest) {
    u8* endPtr;
    s32 validBitCount = 0;
    s32 currCodeByte = 0;
    u32 ts = 0;

    if (src[0] != 'Y' || src[1] != 'a' || src[2] != 'z' || src[3] != '0') {
        return -1;
    }

    SYaz0Header* header = (SYaz0Header*)src;
    endPtr = dest + (header->length - fileOffset);
    if (endPtr > dest + maxDest) {
        endPtr = dest + maxDest;
    }

    src += 0x10;
    do {
        if (validBitCount == 0) {
            if ((src > srcLimit) && transLeft) {
                src = nextSrcData(src);
                if (!src) {
                    return -1;
                }
            }
            currCodeByte = *src;
            validBitCount = 8;
            src++;
        }
        if (currCodeByte & 0x80) {
            if (fileOffset != 0) {
                if (readCount >= fileOffset) {
                    *dest = *src;
                    dest++;
                    ts++;
                    if (dest == endPtr) {
                        break;
                    }
                }
                *(refCurrent++) = *src;
                if (refCurrent == refEnd) {
                    refCurrent = refBuf;
                }
                src++;
            } else {
                *dest = *src;
                dest++;
                src++;
                ts++;
                if (dest == endPtr) {
                    break;
                }
            }
            readCount++;
        } else {
            u32 dist = src[1] | (src[0] & 0x0f) << 8;
            s32 numBytes = src[0] >> 4;
            src += 2;
            u8* copySource;
            if (fileOffset != 0) {
                copySource = refCurrent - dist - 1;
                if (copySource < refBuf) {
                    copySource += refEnd - refBuf;
                }
            } else {
                copySource = dest - dist - 1;
            }
            if (numBytes == 0) {
                numBytes = *src + 0x12;
                src += 1;
            } else {
                numBytes += 2;
            }
            if (fileOffset != 0) {
                do {
                    if (readCount >= fileOffset) {
                        *dest = *copySource;
                        dest++;
                        ts++;
                        if (dest == endPtr) {
                            break;
                        }
                    }
                    *(refCurrent++) = *copySource;
                    if (refCurrent == refEnd) {
                        refCurrent = refBuf;
                    }
                    copySource++;
                    if (copySource == refEnd) {
                        copySource = refBuf;
                    }
                    readCount++;
                    numBytes--;
                } while (numBytes != 0);
            } else {
                do {
                    *dest = *copySource;
                    dest++;
                    ts++;
                    if (dest == endPtr) {
                        break;
                    }
                    readCount++;
                    numBytes--;
                    copySource++;
                } while (numBytes != 0);
            }
        }
        currCodeByte <<= 1;
        validBitCount--;
    } while (dest < endPtr);
    *tsPtr = ts;
    return 0;
}

static u8* firstSrcData() {
    srcLimit = szpEnd - 0x19;
    u8* buf = szpBuf;
    u32 max = (szpEnd - szpBuf);
    u32 transSize = MIN(transLeft, max);

    while (true) {
        int result = DVDReadPrio(srcFile->getFileInfo(), buf, transSize, srcOffset, 2);
        if (0 <= result) {
            break;
        }
        if (result == -3 || !JKRDvdRipper::isErrorRetry()) {
            return nullptr;
        }
        VIWaitForRetrace();
    }
    DCInvalidateRange(buf, transSize);
    srcOffset += transSize;
    transLeft -= transSize;
    return buf;
}

static u8* nextSrcData(u8* src) {
    u32 limit = szpEnd - src;
    u8* buf;
    if (IS_NOT_ALIGNED(limit, 0x20)) {
        buf = szpBuf + 0x20 - (limit & (0x20 - 1));
    } else {
        buf = szpBuf;
    }

    memcpy(buf, src, limit);
    u32 transSize = (u32)(szpEnd - (buf + limit));
    if (transSize > transLeft) {
        transSize = transLeft;
    }
    JUT_ASSERT(transSize > 0);

    while (true) {
        s32 result = DVDReadPrio(srcFile->getFileInfo(), (buf + limit), transSize, srcOffset, 2);
        if (result >= 0) {
            break;
        }
        if (result == -3 || !JKRDvdRipper::isErrorRetry) {
            return nullptr;
        }

        VIWaitForRetrace();
    }
    DCInvalidateRange((buf + limit), transSize);
    srcOffset += transSize;
    transLeft -= transSize;
    if (transLeft == 0) {
        srcLimit = transSize + (buf + limit);
    }

    return buf;
}
