#include "JSystem/JUtility/JUTSDFile.h"
#include "JSystem/JUtility/JUTSDDrive.h"
#include "JSystem/JUtility/JUTException.h"
#include "JSystem/JUtility/fs.h"

JUTSDFile::JUTSDFile() {
    mUnk_26 = 0;
}

JUTSDFile::~JUTSDFile() {
}

bool JUTSDFile::open(int nDrive, const char* path, u16 param3) {
    char filePath[MAX_PATH_LEN];

    if (!JUTSDDrive::GetAvailable(nDrive) || !JUTSDDrive::GetMounted(nDrive)) {
        JUTException::panic(__FILE__, 49, "Drive not mounted");
        return false;
    }

    JUTSDDrive::expandPath(nDrive, path, filePath);
    mUnk_26 = FS_Open(JUTSDDrive::GetDriveInfoPtr(nDrive), &mUnk_20, filePath, param3);

    if (mUnk_26 != 0) {
        return false;
    }

    mUnk_1C = nDrive;
    mUnk_24 = true;
    return true;
}

bool JUTSDFile::close() {
    mUnk_26 = FS_Close(mUnk_20);
    mUnk_24 = false;
    //! @bug: missing return
}

int JUTSDFile::readData(void* data, s32 length, s32 ofs) {
    UnkStruct_ReadWrite sp8;
    u16 status;

    status = FS_Seek(mUnk_20, ofs, 1);

    if (status != 0) {
        mUnk_26 = status;
        return -1;
    }

    status = FS_Read(mUnk_20, data, length, 0, &sp8);

    if (status != 0) {
        mUnk_26 = status;
        return -1;
    }

    switch (sp8.unk_02) {
        case 0x0:
            mUnk_26 = 0;
            return sp8.unk_04;
        case 0xA014:
            mUnk_26 = 0;
            return sp8.unk_04;
        case 0xA015:
            mUnk_26 = 0xA015;
            return 0;
        default:
            break;
    }

    mUnk_26 = sp8.unk_02;
    return -1;
}

int JUTSDFile::writeData(const void* data, s32 length, s32 ofs) {
    UnkStruct_ReadWrite sp8;
    u16 status;

    status = FS_Seek(mUnk_20, ofs, 1);

    if (status != 0) {
        mUnk_26 = status;
        return -1;
    }

    status = FS_Write(mUnk_20, data, length, 0, &sp8);

    if (status != 0) {
        mUnk_26 = status;
        return -1;
    }

    switch (sp8.unk_02) {
        case 0:
            mUnk_26 = 0;
            return sp8.unk_04;
        default:
            break;
    }

    mUnk_26 = sp8.unk_02;
    return -1;
}

u32 JUTSDFile::getFileSize() const {
    u16 status;
    u32 fileSize;

    status = FS_Seek(mUnk_20, 0, 4);

    if (status != 0) {
        mUnk_26 = status;
        return 0;
    }

    status = FS_Getpos(mUnk_20, &fileSize);

    if (status != 0) {
        mUnk_26 = status;
        return 0;
    }

    mUnk_26 = 0;
    return fileSize;
}

bool JUTSDFile::open(const char* path) {
    return this->open(JUTSDDrive::GetCurrentDrive(), path, 0x204);
}
