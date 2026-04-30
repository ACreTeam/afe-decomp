#ifndef _JSYSTEM_JUTILITY_JUTTIFF_H
#define _JSYSTEM_JUTILITY_JUTTIFF_H

#include "types.h"
#include <dolphin/gx.h>

#define JUTTiff_BYTE_ORDER_BIG 0
#define JUTTiff_BYTE_ORDER_LITTLE 1

#define JUTTiff_BYTE_ORDER_MAGIC_BIG 0x4D4D // 'MM'
#define JUTTiff_BYTE_ORDER_MAGIC_LITTLE 0x4949 // 'DD'

#define JUTTiff_MAGIC_NUMBER 0x002A // 42

#define JUTTiff_IFDEntrySize 12

enum JUTTiff_Compression {
    JUTTiff_COMPRESSION_INVALID,
    JUTTiff_COMPRESSION_UNCOMPRESSED,
    JUTTiff_COMPRESSION_CCITT1D,
    JUTTiff_COMPRESSION_GROUP3FAX,
    JUTTiff_COMPRESSION_GROUP4FAX,
    JUTTiff_COMPRESSION_LZW,
    JUTTiff_COMPRESSION_JPEG_OLD,
    JUTTiff_COMPRESSION_JPEG_NEW,
    JUTTiff_COMPRESSION_DEFLATE_ADOBE,

    JUTTiff_COMPRESSION_PACKBITS = 0x8005,
    JUTTiff_COMPRESSION_DEFLATE_STD = 0x80B2,
};

class JUTTiff_IFD0 {
public:
    JUTTiff_IFD0();

    void create();

// private:
    /* 0x00 */ int _00;
    /* 0x04 */ int _04;
    /* 0x08 */ u32 mImageWidth;
    /* 0x0C */ u32 mImageHeight;
    /* 0x10 */ u32 mCompression;
    /* 0x14 */ const char* mTitle;
    /* 0x18 */ const char* mMaker;
    /* 0x1C */ const char* mModel;
    /* 0x20 */ const char* mSoftware;
    /* 0x24 */ const char* mArtist;
    /* 0x28 */ const char* mCopyrightPhotographer;
    /* 0x2C */ const char* mCopyrightEditor;
    /* 0x30 */ const char* mDateModified;
    /* 0x34 */ int mRowsPerStrip;
};

class JUTTiff {
public:
    enum EType {
        ETYPE_NONE,
        ETYPE_BYTE, // 8-bit unsigned integer
        ETYPE_ASCII, // ASCII string (null-terminated)
        ETYPE_SHORT, // 16-bit unsigned integer
        ETYPE_LONG, // 32-bit unsigned integer
        ETYPE_RATIONAL, // (32-bit numerator, 32-bit denominator)
        ETYPE_SBYTE, // 8-bit signed integer
        ETYPE_UNDEFINED, // undefined
        ETYPE_SSHORT, // 16-bit signed integer
        ETYPE_SLONG, // 32-bit signed integer
        ETYPE_SRATIONAL, // (32-bit signed numerator, 32-bit signed denominator)
        ETYPE_FLOAT, // 32-bit IEEE floating point
        ETYPE_DOUBLE, // 64-bit IEEE floating point

        EType_NUM
    };

    JUTTiff();
    ~JUTTiff() {}

    void setImageArea(u8* buffer, int width, int height, GXCompType compType);
    void setXluImageArea(u8* buffer, GXCompType compType, int width, int height, float transparency, u32 param_6);
    void setXluImagePos(int x, int y);
    void createIFD0();
    void createIFDExif();
    void createIFD1();
    void createThumbnail();
    
    u32 getImageWidth() const { return mIFD0.mImageWidth; }
    u32 getImageHeight() const { return mIFD0.mImageHeight; }
    u32 getCompression() const { return mIFD0.mCompression; }
    
private:
    void storeEntry_1data(u16 tag, EType type, u32 value);
    void storeEntry_multidata(u8* buffer, u16 tag, void* value);
    void storeEntry_rational(u8* buffer, u16 tag, u32 numerator, u32 denominator);
    void storeEntry_n_ascii(u8* buffer, u16 tag, u8* ascii, int len);
    void storeEntry_n_ascii_nochk(u8* buffer, u16 tag, u8* ascii, int len);
    void storeEntry_ascii(u8* buffer, u16 tag, u8* ascii);
    void prepEntry_multidata(u16 tag, EType type, int count);
    void prepEntry_n_ascii(u16 tag, int length, u8* ascii);
    void prepEntry_ascii(u16 tag, u8* ascii);
    void prepEntry_undefined(u16 tag, int length, u8* undefined);

    u16 readShort(u8* buffer) const {
        if (mByteOrder == JUTTiff_BYTE_ORDER_BIG) {
            return (buffer[0] << 8) | buffer[1];
        } else {
            return (buffer[1] << 8) | buffer[0];
        }
    }

    u32 readLong(u8* buffer) const {
        if (mByteOrder == JUTTiff_BYTE_ORDER_BIG) {
            return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
        } else {
            return (buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0];
        }
    }

    void writeShort(u8* buffer, u16 value) const {
        if (mByteOrder == JUTTiff_BYTE_ORDER_BIG) {
            buffer[0] = value >> 8;
            buffer[1] = value & 0xFF;
        } else {
            buffer[0] = value & 0xFF;
            buffer[1] = value >> 8;
        }
    }

    void writeLong(u8* buffer, u32 value) const {
        if (mByteOrder == JUTTiff_BYTE_ORDER_BIG) {
            buffer[0] = value >> 24;
            buffer[1] = value >> 16;
            buffer[2] = value >> 8;
            buffer[3] = value & 0xFF;
        } else {
            buffer[0] = value & 0xFF;
            buffer[1] = value >> 8;
            buffer[2] = value >> 16;
            buffer[3] = value >> 24;
        }
    }

    u8* findTag(u8* buffer, u16 tag) const {
        // Read the number of entries in this IFD block
        u16 numEntries = readShort(buffer);
        u8* entryPtr = buffer + sizeof(u16);

        // This loop is the issue
        for (int i = 0; i < numEntries; i++, entryPtr += JUTTiff_IFDEntrySize) {
            u16 tagValue = readShort(entryPtr);
            
            if (tagValue == tag) {
                return entryPtr;
            }
        }

        return nullptr;
    }

    /* 0x00 */ JUTTiff_IFD0 mIFD0;
    /* 0x38 */ const char* mDateOriginal;
    /* 0x3C */ const char* mDateDigitalized;
    /* 0x40 */ const char* mComment;
    /* 0x44 */ int mCommentLength;
    /* 0x48 */ int mThumbnailWidth;
    /* 0x4C */ int mThumbnailHeight;
    /* 0x50 */ u8* mBuffer;
    /* 0x54 */ u8* m_IFDEntryAddr; // current entry
    /* 0x58 */ u8* _58;
    /* 0x5C */ int mNumIFDEntries;
    /* 0x60 */ u8* _60;
    /* 0x64 */ u8* _64;
    /* 0x68 */ u8* mIFDAddr; // base
    /* 0x6C */ u8* mExifIFDAddr;
    /* 0x70 */ u8* mNextIFDAddr;
    /* 0x74 */ int _74;
    /* 0x78 */ u32 mFileSize;
    /* 0x7C */ int mStripCount;
    /* 0x80 */ u8* mImageArea;
    /* 0x84 */ int mImageAreaSize;
    /* 0x88 */ GXCompType mImageAreaCompType;
    /* 0x8C */ u8* mXluImageArea;
    /* 0x90 */ int mXluImageWidth;
    /* 0x94 */ int mXluImageHeight;
    /* 0x98 */ int mXluImageX;
    /* 0x9C */ int mXluImageY;
    /* 0xA0 */ GXCompType mXluImageCompType;
    /* 0xA4 */ float mXluImageTransparency;
    /* 0xA8 */ u32 _A8;
    /* 0xAC */ int _AC;
    /* 0xB0 */ int _B0;
    /* 0xB4 */ bool mThumbnailIncluding;
    /* 0xB5 */ bool _B5;
    /* 0xB8 */ int mByteOrder;
    /* 0xBC */ u8* mStripOffsetsArr;
    /* 0xC0 */ u8* mStripByteCountsArr;
};

#endif
