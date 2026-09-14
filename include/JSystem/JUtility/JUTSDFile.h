#ifndef JUTSDFILE_H
#define JUTSDFILE_H

#include "types.h"
#include "JSystem/JKernel/JKRFile.h"
#include "JSystem/JUtility/fs_file.h"
#include "JSystem/JUtility/JUTSDDrive.h"

class JUTSDFile : public JKRFile {
  public:
    JUTSDFile();

    virtual ~JUTSDFile();
    virtual bool open(const char* path);
    virtual bool close();
    virtual int readData(void* data, s32 length, s32 ofs);
    virtual int writeData(const void* data, s32 length, s32 ofs);
    virtual u32 getFileSize() const;

    bool open(int nDrive, const char* param2, u16 param3);
    bool open(const char* path, u16 mode) { return open(JUTSDDrive::getCurrentDrive(), path, mode); }
    u16 getErrorStatus() const { return mUnk_26; }

  private:
    u16 mUnk_1C;   // _1C
    u16 mUnk_1E;   // _1E
    SDFileInfo* mUnk_20; // _20
    bool mUnk_24;  // _24
    bool mUnk_25;  // _25
    mutable u16 mUnk_26;   // _26
};

#endif
