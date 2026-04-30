#include "JSystem/JUtility/JUTTiff.h"
#include "JSystem/JUtility/JUTException.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "libc/string.h"
#include <dolphin/gx.h>

static const char* title = "TIFF_Sample";
static const char* maker = "Nintendo";
static const char* model = "Gamecube";
static const char* copyright_p = "(C)2003 Nintendo. All rights reserved.";
static const char* copyright_e = "";
static const char* date = "2003:04:01 12:00:00";
static const char* date_original = "2003:04:01 12:00:00";
static const char* date_digitalized = "2003:04:01 12:00:00";

JUTTiff_IFD0::JUTTiff_IFD0() {
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

void JUTTiff::storeEntry_n_ascii(u8* buffer, u16 tag, u8* ascii, int len) {
    if (len <= 4 || ascii == nullptr) {
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

void JUTTiff::storeEntry_n_ascii_nochk(u8* buffer, u16 tag, u8* ascii, int len) {
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

void JUTTiff::storeEntry_ascii(u8* buffer, u16 tag, u8* ascii) {
    if (ascii == nullptr || ascii == nullptr) {
        return;
    }

    storeEntry_n_ascii(buffer, tag, ascii, strlen((const char*)ascii) + 1);
}

void JUTTiff::prepEntry_multidata(u16 tag, EType type, int count) {
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

    mDateOriginal = date_original;
    mDateDigitalized = date_digitalized;
    mComment = nullptr;
    mCommentLength = 0;
    mThumbnailWidth = 160;
    mThumbnailHeight = 120;
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
    const char* photoStr;
    const char* editorStr;
    u32 photoLen;
    u32 editorLen;
    u32 copyrightTotalLen;
    void* copyrightStr;

    // 1. Initialize Header Pointers
    mIFDAddr = m_IFDEntryAddr;
    _58 = m_IFDEntryAddr;
    mNumIFDEntries = 0;
    _64 = m_IFDEntryAddr;
    m_IFDEntryAddr += 2; // Leave 2 bytes of space for the Entry Count

    // 2. Prepare the Copyright String
    photoStr = mIFD0.mCopyrightPhotographer;
    editorStr = mIFD0.mCopyrightEditor;

    photoLen = photoStr != nullptr ? strlen(photoStr) : 0;
    editorLen = editorStr != nullptr ? strlen(editorStr) : 0;

    // Allocate memory for the concatenated copyright string
    copyrightStr = JKRAllocFromSysHeap(photoLen + editorLen + 8, 0);

    strcpy((char*)copyrightStr, photoLen != 0 ? photoStr : " ");

    copyrightTotalLen = photoLen != 0 ? photoLen + 1 : 2;
    if (editorStr != nullptr) {
        strcpy((char*)copyrightStr + copyrightTotalLen, editorStr);
        copyrightTotalLen += editorLen;
        copyrightTotalLen++;
    }

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
    prepEntry_ascii(0x9003, (u8*)mDateOriginal);                  // DateTimeOriginal
    prepEntry_ascii(0x9004, (u8*)mDateDigitalized);               // DateTimeDigitized
    prepEntry_undefined(0x9286, mCommentLength, (u8*)mComment);   // UserComment
    
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
    
    if (mDateOriginal != nullptr) {
        storeEntry_ascii(data, 0x9003, (u8*)mDateOriginal);
    }

    if (mDateDigitalized != nullptr) {
        storeEntry_ascii(data, 0x9004, (u8*)mDateDigitalized);
    }
    
    // ETYPE_UNDEFINED copies bytes exactly like ASCII, so we can reuse the n_ascii method
    // Dunno why this one is missing a check for nullptr
    storeEntry_n_ascii_nochk(data, 0x9286, (u8*)mComment, mCommentLength);

    // Initialize the NextIFD Offset field to 0
    writeLong(_60, 0);
}

void JUTTiff::createIFD1() {
    // 1. Link IFD0's NextIFD offset to the start of this new thumbnail IFD
    mNextIFDAddr = m_IFDEntryAddr;
    u16 numEntriesIFD0 = readShort(mIFDAddr);
    u8* nextIfdOffsetPtr = mIFDAddr + (numEntriesIFD0 * JUTTiff_IFDEntrySize);
    writeLong(nextIfdOffsetPtr + 2, (u32)(m_IFDEntryAddr - mBuffer));

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
    // 1. Update IFD1's StripOffsets (Tag 0x111) to point to our current buffer location
    // This connects the thumbnail directory to the pixel data we are about to write.
    u8* stripOffsetsTag = findTag(mNextIFDAddr, 0x111);
    if (stripOffsetsTag != nullptr) {
        writeLong(stripOffsetsTag + 8, (u32)(m_IFDEntryAddr - mBuffer));
    }

    // 2. Write the Thumbnail Pixel Data
    u8* customThumb = (u8*)_AC;

    if (customThumb != nullptr) {
        // --- Custom Buffer Branch ---
        // If a custom thumbnail was provided, simply copy it byte-by-byte into the file buffer.
        // Assuming thumbnail is RGB8 (3 bytes per pixel) based on the image bounds.
        int totalBytes = mThumbnailWidth * mThumbnailHeight * 3;
        
        for (int i = 0; i < 0x4B00; i++) {
            *m_IFDEntryAddr++ = *customThumb++;
        }
    } else {
        // --- Dynamic Downsampling Branch ---
        float scaleX = (float)mIFD0.mImageWidth / mThumbnailWidth;
        float scaleY = (float)mIFD0.mImageHeight / mThumbnailHeight;

        for (int y = 0; y < mThumbnailHeight; y++) {
            for (int x = 0; x < mThumbnailWidth; x++) {
                
                // Calculate the bounding box in the source image for this single thumbnail pixel
                int startY = mIFD0._04 + (int)(y * scaleY);
                int endY   = mIFD0._04 + (int)((y + 1) * scaleY);
                
                u32 r = 0, g = 0, b = 0;
                u32 count = 0;
                
                // Average all the source pixels inside that bounding box
                for (int sy = startY; sy < endY; sy++) {
                    int startX = mIFD0._00 + (x * scaleX);
                    int endX   = mIFD0._00 + (int)((x + 1) * scaleX);
                    for (int sx = startX; sx < endX; sx++) {
                        if (mImageArea != nullptr) {
                            // Read from the provided main image buffer (Assuming RGB8 / 3 bytes per pixel)
                            u8* pixel = mImageArea + (sx + sy * mIFD0.mImageWidth) * 3;
                            r += pixel[0];
                            g += pixel[1];
                            b += pixel[2];
                        } else {
                            // If no memory buffer exists, read directly from the GX Framebuffer (EFB)
                            u32 color;
                            GXPeekARGB((u16)sx, (u16)sy, &color);
                            r += (color >> 16) & 0xFF;
                            g += (color >> 8) & 0xFF;
                            b += color & 0xFF;
                        }
                        count++;
                    }
                }

                if (count == 0) count = 1; // Failsafe to prevent division by zero

                *m_IFDEntryAddr++ = (u8)(r / count);
                *m_IFDEntryAddr++ = (u8)(g / count);
                *m_IFDEntryAddr++ = (u8)(b / count);
            }
        }
    }
}
