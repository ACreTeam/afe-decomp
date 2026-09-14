// Keep unrelated sqrtf constants out of this translation unit's constant pool.
#define FIX_SQRT_LINKAGE
#include "JSystem/JUtility/JUTTiff.h"
#include "JSystem/JUtility/JUTException.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "libc/string.h"
#include "_mem.h"
#include <dolphin/gx.h>

static inline u32 makeCopyright(const char* photoStr, const char* editorStr, void*& result) {
    u32 photoLen = photoStr != nullptr ? strlen(photoStr) : 0;
    u32 editorLen = editorStr != nullptr ? strlen(editorStr) : 0;

    // Allocate memory for the concatenated copyright string
    void* copyrightStr = JKRAllocFromSysHeap(photoLen + editorLen + 8, 0);
    result = copyrightStr;

    strcpy((char*)copyrightStr, photoLen != 0 ? photoStr : " ");

    u32 copyrightTotalLen = photoLen != 0 ? photoLen + 1 : 2;
    if (editorStr != nullptr) {
        strcpy((char*)copyrightStr + copyrightTotalLen, editorStr);
        copyrightTotalLen = editorLen + copyrightTotalLen;
        copyrightTotalLen++;
    }
    return copyrightTotalLen;
}

// needed for data ordering so that " " loads first
static void __fake() {
    void* tmp;
    makeCopyright(nullptr, nullptr, tmp);
}

void JUTTiff::storeEntry_1data(u16 tag, EType type, u32 value) {
    writeShort(m_IFDEntryAddr, tag); // tag
    writeShort(m_IFDEntryAddr + 2, static_cast<u16>(type)); // type
    writeLong(m_IFDEntryAddr + 4, 1); // count

    if (type == ETYPE_LONG || type == ETYPE_SLONG) {
        writeLong(m_IFDEntryAddr + 8, value); // value
    } else {
        writeShort(m_IFDEntryAddr + 8, value); // value
        writeShort(m_IFDEntryAddr + 10, 0); // nothing
    }

    m_IFDEntryAddr += JUTTiff_IFDEntrySize;
    mNumIFDEntries++;
}

void JUTTiff::storeEntry_multidata(u8* buffer, u16 tag, void* value) {
    // Find the tag
    // @BUG - no check for nullptr
    u8* entryPtr = findTag(buffer, tag);

    // Read the existing tag's metadata
    u16 dataType = readShort(entryPtr + 2);
    u32 dataCount = readLong(entryPtr + 4);

    // Update the tag's offset pointer
    // We are appending this array to the very end of our active buffer.
    // Calculate the absolute byte offset and write it into bytes 8-11 of the tag.
    u32 dataOffset = (u32)(m_IFDEntryAddr - mBuffer);
    writeLong(entryPtr + 8, dataOffset);

    // Copy the array data to the end of the buffer
    for (int i = 0; i < dataCount; i++) {
        if (dataType == ETYPE_SHORT) {
            u16 src = *(u16*)value;
            value = (void*)((u32)value + sizeof(u16));
            writeShort(m_IFDEntryAddr, src);
            m_IFDEntryAddr += sizeof(u16);
        }
        
        if (dataType == ETYPE_LONG || dataType == ETYPE_SLONG) {
            u32 src = *(u32*)value;
            value = (void*)((u32)value + sizeof(u32));
            writeLong(m_IFDEntryAddr, src);
            m_IFDEntryAddr += sizeof(u32);
        }
    }
}

void JUTTiff::storeEntry_rational(u8* buffer, u16 tag, u32 numerator, u32 denominator) {
    // Find the tag
    // @BUG - no check for nullptr
    u8* entryPtr = findTag(buffer, tag);

    // Read the existing tag's metadata
    u16 dataType = readShort(entryPtr + 2);
    u32 dataCount = readLong(entryPtr + 4);

    // Update the tag's offset pointer
    // We are appending this array to the very end of our active buffer.
    // Calculate the absolute byte offset and write it into bytes 8-11 of the tag.
    u32 dataOffset = (u32)(m_IFDEntryAddr - mBuffer);
    writeLong(entryPtr + 8, dataOffset);

    // Copy the array data to the end of the buffer
    writeLong(m_IFDEntryAddr, numerator);
    writeLong(m_IFDEntryAddr + sizeof(u32), denominator);
    m_IFDEntryAddr += sizeof(u32) * 2;
}

inline void JUTTiff::storeEntry_n_ascii(u8* buffer, u16 tag, u8* ascii, int len) {
    if (len <= 4 || ascii == nullptr) {
        return;
    }

    u8* entryPtr = findTag(buffer, tag);
    writeLong(entryPtr + 8, (u32)(m_IFDEntryAddr - mBuffer));
    int count = len;
    for (; count != 0; count--) {
        *m_IFDEntryAddr++ = *ascii++;
    }
    while (((uintptr_t)m_IFDEntryAddr - (uintptr_t)mBuffer) & 1) {
        *m_IFDEntryAddr = 0;
        m_IFDEntryAddr++;
    }
}

inline void JUTTiff::storeEntry_n_ascii_nochk(u8* buffer, u16 tag, u8* ascii, int len) {
    if (len <= 4) {
        return;
    }

    u8* entryPtr = findTag(buffer, tag);
    writeLong(entryPtr + 8, (u32)(m_IFDEntryAddr - mBuffer));
    for (; len != 0; len--) {
        *m_IFDEntryAddr++ = *ascii++;
    }
    while (((uintptr_t)m_IFDEntryAddr - (uintptr_t)mBuffer) & 1) {
        *m_IFDEntryAddr = 0;
        m_IFDEntryAddr++;
    }
}

inline void JUTTiff::storeEntry_ascii(u8* buffer, u16 tag, u8* ascii) {
    if (ascii == nullptr || ascii == nullptr) {
        return;
    }

    storeEntry_n_ascii(buffer, tag, ascii, strlen((const char*)ascii) + 1);
}

inline void JUTTiff::prepEntry_multidata(u16 tag, EType type, int count) {
    writeShort(m_IFDEntryAddr, tag); // tag
    writeShort(m_IFDEntryAddr + 2, static_cast<u16>(type)); // type
    writeLong(m_IFDEntryAddr + 4, count); // count
    writeLong(m_IFDEntryAddr + 8, 0); // offset
    m_IFDEntryAddr += JUTTiff_IFDEntrySize;
    mNumIFDEntries++;
}

void JUTTiff::prepEntry_n_ascii(u16 tag, int length, u8* ascii) {
    if (length == 0 || ascii == nullptr) {
        return;
    }

    writeShort(m_IFDEntryAddr, tag); // tag
    writeShort(m_IFDEntryAddr + 2, ETYPE_ASCII); // type
    writeLong(m_IFDEntryAddr + 4, length); // count
    m_IFDEntryAddr += 8;

    // Copy the ASCII string to the end of the buffer
    if (length <= 4) {
        int i;

        for (i = 0; i < length; i++) {
            *m_IFDEntryAddr++ = *ascii++;
        }

        for (; i < 4; i++) {
            *m_IFDEntryAddr++ = 0;
        }
    } else {
        writeLong(m_IFDEntryAddr, 0);
        m_IFDEntryAddr += sizeof(u32);
    }

    mNumIFDEntries++;
}

// TODO: figure out why prepEntry_ascii is being inlined
// Perhaps the double nullptr implies a smaller inline?
#pragma dont_inline on
void JUTTiff::prepEntry_ascii(u16 tag, u8* ascii) {
    if (ascii == nullptr || ascii == nullptr) {
        return;
    }

    int length = strlen((const char*)ascii) + 1;
    prepEntry_n_ascii(tag, length, ascii);
}
#pragma dont_inline off

void JUTTiff::prepEntry_undefined(u16 tag, int length, u8* undefined) {
    // @BUG - no check for nullptr
    if (length == 0) {
        return;
    }

    writeShort(m_IFDEntryAddr, tag); // tag
    writeShort(m_IFDEntryAddr + 2, ETYPE_UNDEFINED); // type
    writeLong(m_IFDEntryAddr + 4, length); // count
    m_IFDEntryAddr += 8;

    // Copy the ASCII string to the end of the buffer
    if (length <= 4) {
        int i;

        for (i = 0; i < length; i++) {
            *m_IFDEntryAddr++ = *undefined++;
        }

        for (; i < 4; i++) {
            *m_IFDEntryAddr++ = 0;
        }
    } else {
        writeLong(m_IFDEntryAddr, 0);
        m_IFDEntryAddr += sizeof(u32);
    }

    mNumIFDEntries++;
}

const char* title = "TIFF_Sample";
const char* maker = "Nintendo";
const char* model = "Gamecube";
const char* copyright_p = "(C)2003 Nintendo. All rights reserved.";
const char* copyright_e = "";
const char* date = "2003:04:01 12:00:00";
const char* date_original = "2003:04:01 12:00:00";
const char* date_digitalized = "2003:04:01 12:00:00";

inline JUTTiff_IFD0::JUTTiff_IFD0() {
    _00 = 0;
    _04 = 0;
    mImageWidth = 640;
    mImageHeight = 480;
    mCompression = JUTTiff_COMPRESSION_UNCOMPRESSED;
    mTitle = title;
    mMaker = maker;
    mModel = model;
    mSoftware = nullptr;
    mArtist = nullptr;
    mCopyrightPhotographer = copyright_p;
    mCopyrightEditor = copyright_e;
    mDateModified = date;
    mRowsPerStrip = 5;
}

// TODO: dunno if IFD0 actually has a ctor, seems to match with or without it.
JUTTiff::JUTTiff() : mIFD0() {
    // mIFD0._00 = 0;
    // mIFD0._04 = 0;
    // mIFD0.mImageWidth = 640;
    // mIFD0.mImageHeight = 480;
    // mIFD0.mCompression = JUTTiff_COMPRESSION_UNCOMPRESSED;
    // mIFD0.mTitle = title;
    // mIFD0.mMaker = maker;
    // mIFD0.mModel = model;
    // mIFD0.mSoftware = nullptr;
    // mIFD0.mArtist = nullptr;
    // mIFD0.mCopyrightPhotographer = copyright_p;
    // mIFD0.mCopyrightEditor = copyright_e;
    // mIFD0.mDateModified = date;
    // mIFD0.mRowsPerStrip = 5;

#if VERSION == GAEJ01_00
    mDates.mDateOriginal = date_original;
    mDates.mDateDigitalized = date_digitalized;
    mCommentInfo.mComment = nullptr;
    mCommentInfo.mCommentLength = 0;
    mThumbnailSize.mThumbnailWidth = 160;
    mThumbnailSize.mThumbnailHeight = 120;
#else
    mDateOriginal = date_original;
    mDateDigitalized = date_digitalized;
    mComment = nullptr;
    mCommentLength = 0;
    mThumbnailWidth = 160;
    mThumbnailHeight = 120;
#endif
    mImageArea = nullptr;
    mImageAreaSize = 0;
    _AC = 0;
    _B0 = 0xE100;
    mThumbnailIncluding = true;
    mXluImageArea = nullptr;
    mXluImageX = 0;
    mXluImageY = 0;
    _B5 = false;
    mByteOrder = JUTTiff_BYTE_ORDER_LITTLE;
}

void JUTTiff::setImageArea(u8* buffer, int width, int height, GXCompType compType) {
    int bytesPerPixel;
    
    switch (compType) {
        case GX_RGB8:
            bytesPerPixel = 3;
            break;
        case GX_RGB565:
            bytesPerPixel = 2;
            break;
        default:
            JUTException::panic_f(__FILE__, 638, "%s", "bad format");
            break;
    }

    mIFD0._00 = 0;
    mIFD0._04 = 0;
    mIFD0.mImageWidth = width;
    mIFD0.mImageHeight = height;
    mImageArea = buffer;
    mImageAreaSize = width * height * bytesPerPixel;
    mImageAreaCompType = compType;
}

void JUTTiff::setXluImageArea(u8* buffer, GXCompType compType, int width, int height, float transparency, u32 param_6) {
    mXluImageArea = buffer;
    mXluImageWidth = width;
    mXluImageHeight = height;
    mXluImageCompType = compType;
    mXluImageTransparency = transparency;
    _A8 = param_6;
}

void JUTTiff::setXluImagePos(int x, int y) {
    mXluImageX = x;
    mXluImageY = y;
}

void JUTTiff::createIFD0() {
    // 1. Initialize Header Pointers
    mIFDAddr = m_IFDEntryAddr;
    _58 = m_IFDEntryAddr;
    mNumIFDEntries = 0;
    _64 = m_IFDEntryAddr;
    m_IFDEntryAddr += 2;

    void* copyrightStr;
    int copyrightTotalLen = makeCopyright(mIFD0.mCopyrightPhotographer, mIFD0.mCopyrightEditor, copyrightStr);

    // --- Write Directory Entries (Tags) ---

    storeEntry_1data(0x100, ETYPE_LONG, mIFD0.mImageWidth);
    storeEntry_1data(0x101, ETYPE_LONG, mIFD0.mImageHeight);


    prepEntry_multidata(0x102, ETYPE_SHORT, 3); // BitsPerSample
    storeEntry_1data(0x103, ETYPE_SHORT, 1);    // Compression
    storeEntry_1data(0x106, ETYPE_SHORT, 2);    // PhotometricInterpretation

    prepEntry_ascii(0x10E, (u8*)mIFD0.mTitle);
    prepEntry_ascii(0x10F, (u8*)mIFD0.mMaker);
    prepEntry_ascii(0x110, (u8*)mIFD0.mModel);

    prepEntry_multidata(0x111, ETYPE_LONG, mStripCount); // StripOffsets

    storeEntry_1data(0x112, ETYPE_SHORT, 1);             // Orientation
    storeEntry_1data(0x115, ETYPE_SHORT, 3);             // SamplesPerPixel
    storeEntry_1data(0x116, ETYPE_LONG, mIFD0.mRowsPerStrip);

    prepEntry_multidata(0x117, ETYPE_LONG, mStripCount); // StripByteCounts
    prepEntry_multidata(0x11A, ETYPE_RATIONAL, 1);       // XResolution
    prepEntry_multidata(0x11B, ETYPE_RATIONAL, 1);       // YResolution

    storeEntry_1data(0x11C, ETYPE_SHORT, 1);             // PlanarConfiguration
    storeEntry_1data(0x128, ETYPE_SHORT, 2);             // ResolutionUnit

    prepEntry_ascii(0x131, (u8*)mIFD0.mSoftware);
    prepEntry_ascii(0x132, (u8*)mIFD0.mDateModified);
    prepEntry_ascii(0x13B, (u8*)mIFD0.mArtist);

    prepEntry_n_ascii(0x8298, copyrightTotalLen, (u8*)copyrightStr);
    storeEntry_1data(0x8769, ETYPE_LONG, 0);             // ExifOffset

    _60 = m_IFDEntryAddr;
    m_IFDEntryAddr += 4; // Skip the NextIFD Offset pointer

    // Write the finalized entry count at the very start of the IFD
    writeShort(_58, mNumIFDEntries);


    // --- Resolve Out-of-Line Data for Multidata Tags ---

    u16 bitsPerSample[3] = {8, 8, 8}; // Replaces local_24/local_20 magic numbers
    u16 dummyStripData[1] = {0}; // Replaces local_28
    u8* data = _64;

    storeEntry_multidata(data, 0x102, bitsPerSample);
    if (mIFD0.mTitle != nullptr) {
        storeEntry_ascii(data, 0x10E, (u8*)mIFD0.mTitle);
    }

    if (mIFD0.mMaker != nullptr) {
        storeEntry_ascii(data, 0x10F, (u8*)mIFD0.mMaker);
    }

    if (mIFD0.mModel != nullptr) {
        storeEntry_ascii(data, 0x110, (u8*)mIFD0.mModel);
    }

    storeEntry_multidata(data, 0x111, dummyStripData);
    storeEntry_multidata(data, 0x117, dummyStripData);

    storeEntry_rational(data, 0x11A, 0x48, 1); // 72 DPI (0x48 = 72)
    storeEntry_rational(data, 0x11B, 0x48, 1); // 72 DPI

    if (mIFD0.mSoftware != nullptr) {
        storeEntry_ascii(data, 0x131, (u8*)mIFD0.mSoftware);
    }

    if (mIFD0.mDateModified != nullptr) {
        storeEntry_ascii(data, 0x132, (u8*)mIFD0.mDateModified);
    }

    if (mIFD0.mArtist != nullptr) {
        storeEntry_ascii(data, 0x13B, (u8*)mIFD0.mArtist);
    }

    storeEntry_n_ascii(data, 0x8298, (u8*)copyrightStr, copyrightTotalLen);

    // EXIF Offset logic (Does not append data, just links the pointer)
    u8* exifEntry = findTag(data, 0x8769);
    writeLong(exifEntry + 8, (u32)(m_IFDEntryAddr - mBuffer));

    JKRHeap::free(copyrightStr, nullptr);

    // Initialize the NextIFD Offset field to 0
    writeLong(_60, 0);
}

void JUTTiff::createIFDExif() {
    // 1. Initialize Header Pointers
    mExifIFDAddr = m_IFDEntryAddr;
    _58 = m_IFDEntryAddr;
    mNumIFDEntries = 0;
    _64 = m_IFDEntryAddr;
    m_IFDEntryAddr += 2; // Leave 2 bytes of space for the Entry Count

    // Replicate Ghidra's builtin_memcpy for the 4-byte version strings
    u8 exifVersion[4] = {'0', '2', '2', '0'};
    u8 flashPixVersion[4] = {'0', '1', '0', '0'};

    // --- Write Directory Entries (Tags) ---

    prepEntry_undefined(0x9000, 4, exifVersion);                  // ExifVersion
#if VERSION == VER_GAEJ01_00
    prepEntry_ascii(0x9003, (u8*)mDates.mDateOriginal);                  // DateTimeOriginal
    prepEntry_ascii(0x9004, (u8*)mDates.mDateDigitalized);               // DateTimeDigitized
    prepEntry_undefined(0x9286, mCommentInfo.mCommentLength, (u8*)mCommentInfo.mComment);   // UserComment
#else
    prepEntry_ascii(0x9003, (u8*)mDateOriginal);                  // DateTimeOriginal
    prepEntry_ascii(0x9004, (u8*)mDateDigitalized);               // DateTimeDigitized
    prepEntry_undefined(0x9286, mCommentLength, (u8*)mComment);   // UserComment
#endif
    
    // SubSec strings are 4 bytes with null-terminator, so they fit inline
    prepEntry_ascii(0x9290, (u8*)"000");                          // SubSecTime
    prepEntry_ascii(0x9291, (u8*)"000");                          // SubSecTimeOriginal
    prepEntry_ascii(0x9292, (u8*)"000");                          // SubSecTimeDigitized
    
    prepEntry_undefined(0xA000, 4, flashPixVersion);              // FlashpixVersion
    storeEntry_1data(0xA001, ETYPE_SHORT, 1);                     // ColorSpace
    storeEntry_1data(0xA401, ETYPE_SHORT, 1);                     // CustomRendered

    _60 = m_IFDEntryAddr;
    m_IFDEntryAddr += 4; // Skip the NextIFD Offset pointer

    // Write the finalized entry count at the very start of the EXIF IFD
    writeShort(_58, mNumIFDEntries);


    // --- Resolve Out-of-Line Data ---

    u8* data = _64;
    
#if VERSION == VER_GAEJ01_00
    if (mDates.mDateOriginal != nullptr) {
        storeEntry_ascii(data, 0x9003, (u8*)mDates.mDateOriginal);
#else
    if (mDateOriginal != nullptr) {
        storeEntry_ascii(data, 0x9003, (u8*)mDateOriginal);
#endif
    }

#if VERSION == VER_GAEJ01_00
    if (mDates.mDateDigitalized != nullptr) {
        storeEntry_ascii(data, 0x9004, (u8*)mDates.mDateDigitalized);
#else
    if (mDateDigitalized != nullptr) {
        storeEntry_ascii(data, 0x9004, (u8*)mDateDigitalized);
#endif
    }
    
    // ETYPE_UNDEFINED copies bytes exactly like ASCII, so we can reuse the n_ascii method
    // Dunno why this one is missing a check for nullptr
#if VERSION == VER_GAEJ01_00
    storeEntry_n_ascii_nochk(data, 0x9286, (u8*)mCommentInfo.mComment, mCommentInfo.mCommentLength);
#else
    storeEntry_n_ascii_nochk(data, 0x9286, (u8*)mComment, mCommentLength);
#endif

    // Initialize the NextIFD Offset field to 0
    writeLong(_60, 0);
}

void JUTTiff::createIFD1() {
    // 1. Link IFD0's NextIFD offset to the start of this new thumbnail IFD
    mNextIFDAddr = m_IFDEntryAddr;
    u8* nextIfdOffsetPtr = mIFDAddr;
    u16 numEntriesIFD0 = readShort(nextIfdOffsetPtr);
    nextIfdOffsetPtr += numEntriesIFD0 * JUTTiff_IFDEntrySize + 2;
    writeLong(nextIfdOffsetPtr, (u32)(m_IFDEntryAddr - mBuffer));

    // 2. Initialize IFD1 Pointers
    _58 = m_IFDEntryAddr;
    mNumIFDEntries = 0;
    _64 = m_IFDEntryAddr;
    m_IFDEntryAddr += 2; // Leave 2 bytes of space for the Entry Count

    // --- Write Directory Entries (Tags) ---
    
    storeEntry_1data(0x100, ETYPE_LONG, 160);  // ImageWidth (160)
    storeEntry_1data(0x101, ETYPE_LONG, 120); // ImageLength (120)
    
    prepEntry_multidata(0x102, ETYPE_SHORT, 3);            // BitsPerSample
    storeEntry_1data(0x103, ETYPE_SHORT, 1);               // Compression (1 = Uncompressed)
    storeEntry_1data(0x106, ETYPE_SHORT, 2);               // PhotometricInterpretation (2 = RGB)
    
    storeEntry_1data(0x111, ETYPE_LONG, 0);                // StripOffsets (0 for now)
    storeEntry_1data(0x115, ETYPE_SHORT, 3);               // SamplesPerPixel (3 for RGB)
    storeEntry_1data(0x116, ETYPE_LONG, 120); // RowsPerStrip (120 - One continuous strip)
    storeEntry_1data(0x117, ETYPE_LONG, 0xE100);              // StripByteCounts (57600 bytes)
    
    prepEntry_multidata(0x11A, ETYPE_RATIONAL, 1);         // XResolution
    prepEntry_multidata(0x11B, ETYPE_RATIONAL, 1);         // YResolution
    
    storeEntry_1data(0x11C, ETYPE_SHORT, 1);               // PlanarConfiguration (1 = Chunky)
    storeEntry_1data(0x128, ETYPE_SHORT, 2);               // ResolutionUnit (2 = Inch)

    _60 = m_IFDEntryAddr;
    m_IFDEntryAddr += 4; // Skip the NextIFD Offset pointer

    // Write the finalized entry count at the very start of IFD1
    writeShort(_58, mNumIFDEntries);


    // --- Resolve Out-of-Line Data ---
    
    u16 bitsPerSample[3] = {8, 8, 8};
    u8* data = _64;
    
    storeEntry_multidata(data, 0x102, bitsPerSample);
    storeEntry_rational(data, 0x11A, 0x48, 1); // 72 DPI (0x48 = 72)
    storeEntry_rational(data, 0x11B, 0x48, 1); // 72 DPI

    // Initialize the NextIFD Offset field to 0 (This is the final IFD in the file)
    writeLong(_60, 0);
}

void JUTTiff::createThumbnail() {
    u8* entry = findTag(mNextIFDAddr, 0x111);
    writeLong(entry + 8, m_IFDEntryAddr - mBuffer);
    if ((u8*)_AC != NULL) {
        u8* custom = (u8*)_AC;
        for (int i = 0; i < 160 * 120; i++) *m_IFDEntryAddr++ = *custom++;
    } else {
        float scaleX = (float)mIFD0.mImageWidth / 160.0f;
        float scaleY = (float)mIFD0.mImageHeight / 120.0f;
        for (int y = 0; y < 120; y++) {
            for (int x = 0; x < 160; x++) {
                u32 r = 0, g = 0, b = 0, count = 0;
                int sy = (float)(u32)mIFD0._04 + scaleY * y;
                int endY = (float)(u32)mIFD0._04 + scaleY * (y + 1);
                int sx;
                int endX = (float)(u32)mIFD0._00 + scaleX * (x + 1);
                do {
                    sx = (float)(u32)mIFD0._00 + scaleX * x;
                    do {
                        if (mImageArea) {
                            u8* pixel = mImageArea + (sx + sy * mIFD0.mImageWidth) * 3;
                            r += pixel[0]; g += pixel[1]; b += pixel[2];
                        } else {
                            u32 color;
                            GXPeekARGB(sx, sy, &color);
                            r += (color >> 16) & 255; g += (color >> 8) & 255; b += color & 255;
                        }
                        count++;
                        sx++;
                    } while (sx < endX);
                    sy++;
                } while (sy < endY);
                *m_IFDEntryAddr++ = r / count;
                *m_IFDEntryAddr++ = g / count;
                *m_IFDEntryAddr++ = b / count;
            }
        }
    }
}

static inline u16 tiffReadShort(u8* buffer, int byteOrder) {
    if (byteOrder == 0) return (buffer[0] << 8) | buffer[1];
    return (buffer[1] << 8) | buffer[0];
}

static inline u32 tiffReadLong(u8* buffer, int byteOrder) {
    if (byteOrder == 0) return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
    return (buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0];
}

struct TiffRGB { u8 r, g, b; };

static inline void tiffRgb565Read(u8* src, u8* dst) {
    dst[0] = (src[0] & 0xF8) | (src[0] >> 5);
    dst[1] = ((src[0] >> 1) & 3) | ((src[0] << 5) | (src[1] >> 3));
    dst[2] = (src[1] << 3) | ((src[1] >> 2) & 3);
}

void JUTTiff::createMainImage() {
    u8* offsets = findTag(mIFDAddr, 0x111);
    u8* counts = findTag(mIFDAddr, 0x117);
    u32 first = readLong(offsets + 8);
    offsets = mBuffer;
    offsets += first;
    u32 second = readLong(counts + 8);
    counts = mBuffer;
    counts += second;
    u32 stripSize = mIFD0.mRowsPerStrip * (mIFD0.mImageWidth * 3);
    u32 offset = m_IFDEntryAddr - mBuffer;
    for (int i = 0; i < mStripCount; i++) {
        writeLong(offsets, offset);
        offsets += 4;
        offset += stripSize;
        writeLong(counts, stripSize);
        counts += 4;
    }
    if (!_B5) {
        u32 x = mIFD0._00;
        u32 y = mIFD0._04;
        u8* src = mImageArea;
        if (!mXluImageArea) {
            for (int i = 0; i < mStripCount; i++) {
                for (u32 j = 0; j < stripSize; j += 3) {
                    if (mImageArea) {
                        if (mImageAreaCompType == GX_S8) {
                            *m_IFDEntryAddr++ = *src++;
                            *m_IFDEntryAddr++ = *src++;
                            *m_IFDEntryAddr++ = *src++;
                        } else {
                            src = mImageArea + mIFD0.mImageWidth * ((y & 0xFFFC) * 8) / 4 +
                                  ((u16)x & 0xFFFC) * 8 + ((u16)x & 3) * 2 + (y & 3) * 8;
                            tiffRgb565Read(src, m_IFDEntryAddr);
                            m_IFDEntryAddr += 3;
                        }
                    } else {
                        u32 color;
                        GXPeekARGB(x, y, &color);
                        *m_IFDEntryAddr++ = color >> 16;
                        *m_IFDEntryAddr++ = color >> 8;
                        *m_IFDEntryAddr++ = color;
                    }
                    x++;
                    if (x >= mIFD0._00 + mIFD0.mImageWidth) { y++; x = mIFD0._00; }
                }
            }
        }
        if (mXluImageArea) {
            u32 useKey;
            int pixelSize = mXluImageCompType == GX_S8 ? 3 : 2;
            useKey = _A8;
            useKey = ((0xFFFFFFFF - useKey) | (useKey + 1)) >> 31;
            u8 keyR, keyG, keyB;
            if (pixelSize == 3) {
                u32 red = (_A8 >> 16) & 255;
                u32 green = (_A8 >> 8) & 255;
                u32 blue = _A8 & 255;
                keyR = red; keyG = green; keyB = blue;
            } else {
                u32 red = (_A8 >> 8) & 255;
                u32 green = _A8 & 255;
                keyR = red; keyG = green;
            }
            for (int i = 0; i < mStripCount; i++) {
                for (u32 j = 0; j < stripSize; j += 3) {
                    u8 r, b, g;
                    if (mImageArea) {
                        if (mImageAreaCompType == GX_S8) {
                            r = *src++; g = *src++; b = *src++;
                        } else {
                            src = mImageArea + mIFD0.mImageWidth * ((y & 0xFFFC) * 8) / 4 +
                                  ((u16)x & 0xFFFC) * 8 + ((u16)x & 3) * 2 + (y & 3) * 8;
                            u8 hi = *src++; u8 lo = *src & 0xFF;
                            r = (hi & 0xF8) | (hi >> 5);
                            g = ((hi >> 1) & 3) | ((hi << 5) | (lo >> 3));
                            b = (lo << 3) | ((lo >> 2) & 3);
                        }
                    } else {
                        u32 color;
                        GXPeekARGB(x, y, &color);
                        r = (color >> 16) & 255; g = (color >> 8) & 255; b = color & 255;
                    }
                    if (mXluImageX <= x && x < mXluImageX + mXluImageWidth &&
                        mXluImageY <= y && y < mXluImageY + mXluImageHeight) {
                        bool transparent;
                        u8* decal;
                        if (pixelSize == 2) {
                            decal = mXluImageArea + mXluImageWidth * (((y - mXluImageY) & 0xFFFC) * 8) / 4 +
                                    ((u16)(x - mXluImageX) & 0xFFFC) * 8 + ((u16)(x - mXluImageX) & 3) * 2 +
                                    ((y - mXluImageY) & 3) * 8;
                        }
                        else decal = mXluImageArea + ((x - mXluImageX) + mXluImageWidth * (y - mXluImageY)) * 3;
                        transparent = false;
                        if (useKey && decal[0] == keyR && decal[1] == keyG && (pixelSize == 2 || decal[2] == keyB)) transparent = true;
                        if (!transparent) {
                            u8 color[3];
                            if (pixelSize == 2) tiffRgb565Read(decal, color);
                            else { *(TiffRGB*)color = *(TiffRGB*)decal; }
                            if (mXluImageTransparency >= 1.0f) { r = color[0]; g = color[1]; b = color[2]; }
                            else {
                                r = r * (1.0f - mXluImageTransparency) + color[0] * mXluImageTransparency;
                                g = g * (1.0f - mXluImageTransparency) + color[1] * mXluImageTransparency;
                                b = b * (1.0f - mXluImageTransparency) + color[2] * mXluImageTransparency;
                            }
                        }
                    }
                    *m_IFDEntryAddr++ = r; *m_IFDEntryAddr++ = g; *m_IFDEntryAddr++ = b;
                    x++;
                    if (x >= mIFD0._00 + mIFD0.mImageWidth) { y++; x = mIFD0._00; }
                }
            }
        }
    }
}

static inline u32 tiffStripCount(u32 height, u32 rows) {
    return (height + rows - 1) / rows;
}

void JUTTiff::create(u8* buffer) {
    if (!mImageArea) _B5 = false;
    if (mImageArea && mImageAreaCompType == GX_U8) _B5 = false;
    mBuffer = buffer;
    m_IFDEntryAddr = mBuffer;
    mStripCount = tiffStripCount(mIFD0.mImageHeight, mIFD0.mRowsPerStrip);
    if (mByteOrder == JUTTiff_BYTE_ORDER_BIG) writeShort(m_IFDEntryAddr, JUTTiff_BYTE_ORDER_MAGIC_BIG);
    else writeShort(m_IFDEntryAddr, JUTTiff_BYTE_ORDER_MAGIC_LITTLE);
    writeShort(m_IFDEntryAddr + 2, JUTTiff_MAGIC_NUMBER);
    writeLong(m_IFDEntryAddr + 4, 8);
    m_IFDEntryAddr += 8;
    createIFD0();
    createIFDExif();
    if (mThumbnailIncluding) { createIFD1(); createThumbnail(); }
    createMainImage();
    _74 = m_IFDEntryAddr - mBuffer;
    int imageSize = _B5 ? mImageAreaSize : 0;
    mFileSize = imageSize + (m_IFDEntryAddr - mBuffer);
}

u8 defaultTimgData[32] = {
    6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0x20
};

static inline u8* tiffTileAddress(u8* buffer, u32 width, u32 x, u32 y, int blockSize) {
    u32 row = width * (((int)(y & 0xFFFC) / 4) * blockSize) / 4;
    return buffer + row + ((int)(x & 0xFFFC) / 4) * blockSize + (x & 3) * 2 + (y & 3) * 8;
}

int JUTTiff::convertTiffToTimg(u8* src, u8* dst, GXTexFmt format) {
    JUTTiff tiff;
    u32 endY;
    u16* outRGBA;
    u16* outRGB;
    u32 y;
    u32 height;
    u32 width;
    u8* offsets;
    u8* counts;
    u32 startY;
    int strip;
    u8* pixel;
    u32 x;
    u32 size;
    tiff.getInfo(src);
    memcpy(dst, defaultTimgData, 32);
    switch (format) { case GX_TF_RGBA8: dst[0] = GX_TF_RGBA8; break; case GX_TF_RGB565: dst[0] = GX_TF_RGB565; break; default: return 0; }
    width = tiff.getImageWidth();
    height = tiff.mIFD0.mImageHeight;
    dst[2] = width >> 8; dst[3] = width;
    dst[4] = height >> 8; dst[5] = height;
    if (width & 31) { OSReport("Err: sizeX=%d", width); return 0; }
    offsets = tiff.getStripOffsets();
    counts = tiff.getStripByteCounts();
    startY = 0;
    for (strip = 0; strip < tiff.mStripCount; strip++) {
        pixel = tiff.mBuffer + tiff.readLong(offsets);
        size = tiff.readLong(counts);
        const u32 rows = size / width;
        if (size % width) { OSReport("Err: sizeX=%d size=%d", width, size); return 0; }
        endY = startY + rows;
        for (y = startY; y < endY; y++) {
            if (y >= height) break;
            for (x = 0; x < width; x += 4) {
                switch (format) {
                case GX_TF_RGBA8: {
                    outRGBA = (u16*)tiffTileAddress(dst + 32, width, x, y, 64);
                    for (int i = 0; i < 4; i++) { outRGBA[0] = 0xFF00 | pixel[0]; outRGBA[16] = (pixel[1] << 8) | pixel[2]; outRGBA++; pixel += 3; }
                    break;
                }
                case GX_TF_RGB565: {
                    outRGB = (u16*)tiffTileAddress(dst + 32, width, x, y, 32);
                    for (int i = 0; i < 4; i++) { *outRGB++ = ((pixel[0] & 0xF8) << 8) | ((pixel[1] & 0xFC) << 3) | (pixel[2] >> 3); pixel += 3; }
                    break;
                }
                }
            }
        }
        offsets += 4; counts += 4;
        startY += rows / 3;
    }
    int result;
    switch (format) {
    case GX_TF_RGBA8: result = ((width + 3) & ~3) * height * 4 + 32; break;
    case GX_TF_RGB565: result = ((width + 3) & ~3) * height * 2 + 32; break;
    }
    return result;
}

bool JUTTiff::getInfo(u8* buffer) { return getInfo_subroutine(buffer, true); }

inline void JUTTiff::readEntry_string(u8* entry, const char** value) {
    u16 type = readShort(entry + 2);
    if (type != ETYPE_UNDEFINED && type != ETYPE_ASCII) {
        OSReport("illegal data\n");
        return;
    }
    if (readLong(entry + 4) <= 4) {
        if (value) *value = (const char*)(entry + 8);
    } else {
        if (value) *value = (const char*)(mBuffer + readLong(entry + 8));
    }
}

bool JUTTiff::getInfo_subroutine(u8* buffer, bool full) {
    mBuffer = buffer;
    int byteOrder;
    switch ((u16)((buffer[1] << 8) | buffer[0])) {
    case JUTTiff_BYTE_ORDER_MAGIC_LITTLE: byteOrder = JUTTiff_BYTE_ORDER_LITTLE; break;
    case JUTTiff_BYTE_ORDER_MAGIC_BIG: byteOrder = JUTTiff_BYTE_ORDER_BIG; break;
    default: return false;
    }
    mByteOrder = byteOrder;
    if (tiffReadShort(buffer + 2, byteOrder) != JUTTiff_MAGIC_NUMBER) return false;
    mIFDAddr = mBuffer + tiffReadLong(buffer + 4, byteOrder);
    mExifIFDAddr = NULL; mNextIFDAddr = NULL;
    mIFD0.mImageWidth = 0; mIFD0.mImageHeight = 0; mIFD0.mCompression = 0;
    mIFD0.mTitle = NULL; mIFD0.mMaker = NULL; mIFD0.mModel = NULL; mIFD0.mSoftware = NULL; mIFD0.mDateModified = NULL;
#if VERSION == VER_GAEJ01_00
    mDates.mDateOriginal = NULL; mDates.mDateDigitalized = NULL; mCommentInfo.mComment = NULL;
#else
    mDateOriginal = NULL; mDateDigitalized = NULL; mComment = NULL;
#endif
    u32 found = 0;
    m_IFDEntryAddr = mIFDAddr + 2;
    for (int i = 0; i < tiffReadShort(mIFDAddr, byteOrder); i++) {
        switch (tiffReadShort(m_IFDEntryAddr, byteOrder)) {
        case 0x100: mIFD0.mImageWidth = readEntry_1data(m_IFDEntryAddr); found |= 1; break;
        case 0x101: mIFD0.mImageHeight = readEntry_1data(m_IFDEntryAddr); found |= 2; break;
        case 0x103: mIFD0.mCompression = readEntry_1data(m_IFDEntryAddr); break;
        case 0x10E: readEntry_string(m_IFDEntryAddr, &mIFD0.mTitle); break;
        case 0x10F: readEntry_string(m_IFDEntryAddr, &mIFD0.mMaker); break;
        case 0x110: readEntry_string(m_IFDEntryAddr, &mIFD0.mModel); break;
        case 0x131: readEntry_string(m_IFDEntryAddr, &mIFD0.mSoftware); break;
        case 0x132: readEntry_string(m_IFDEntryAddr, &mIFD0.mDateModified); break;
        case 0x13B: readEntry_string(m_IFDEntryAddr, &mIFD0.mArtist); break;
        case 0x111: readEntry_array(m_IFDEntryAddr, &mStripOffsetsArr, &mStripCount); break;
        case 0x117: readEntry_array(m_IFDEntryAddr, &mStripByteCountsArr, &mStripCount); break;
        case 0x116: mIFD0.mRowsPerStrip = readEntry_1data(m_IFDEntryAddr); break;
        case 0x8769: mExifIFDAddr = mBuffer + readEntry_1data(m_IFDEntryAddr); break;
        }
        m_IFDEntryAddr += 12;
        if (!full && m_IFDEntryAddr - mBuffer >= 64) return found == 3;
    }
    if (!full) return false;
    u32 next = readLong(m_IFDEntryAddr);
    mNextIFDAddr = next ? mBuffer + next : NULL;
    m_IFDEntryAddr = mExifIFDAddr + 2;
    if (mExifIFDAddr) {
        for (int i = 0; i < tiffReadShort(mExifIFDAddr, byteOrder); i++) {
            switch (tiffReadShort(m_IFDEntryAddr, byteOrder)) {
#if VERSION == VER_GAEJ01_00
            case 0x9003: readEntry_string(m_IFDEntryAddr, &mDates.mDateOriginal); break;
            case 0x9004: readEntry_string(m_IFDEntryAddr, &mDates.mDateDigitalized); break;
            case 0x9286: readEntry_string(m_IFDEntryAddr, &mCommentInfo.mComment); break;
#else
            case 0x9003: readEntry_string(m_IFDEntryAddr, &mDateOriginal); break;
            case 0x9004: readEntry_string(m_IFDEntryAddr, &mDateDigitalized); break;
            case 0x9286: readEntry_string(m_IFDEntryAddr, &mComment); break;
#endif
            }
            m_IFDEntryAddr += 12;
        }
    }
    m_IFDEntryAddr = mNextIFDAddr + 2;
    if (mNextIFDAddr) {
        for (int i = 0; i < tiffReadShort(mNextIFDAddr, byteOrder); i++) {
            switch (tiffReadShort(m_IFDEntryAddr, byteOrder)) {
#if VERSION == VER_GAEJ01_00
            case 0x100: mThumbnailSize.mThumbnailWidth = readEntry_1data(m_IFDEntryAddr); break;
            case 0x101: mThumbnailSize.mThumbnailHeight = readEntry_1data(m_IFDEntryAddr); break;
#else
            case 0x100: mThumbnailWidth = readEntry_1data(m_IFDEntryAddr); break;
            case 0x101: mThumbnailHeight = readEntry_1data(m_IFDEntryAddr); break;
#endif
            }
            m_IFDEntryAddr += 12;
        }
    }
    return true;
}
