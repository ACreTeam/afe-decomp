#ifndef JUTSDDRIVE_H
#define JUTSDDRIVE_H

#include "types.h"
#include "JSystem/JKernel/JKRFileFinder.h"

#define DRIVE_SLOT_A 0
#define DRIVE_SLOT_B 1
#define MAX_DRIVES 2
#define MAX_PATH_LEN 64

#define IsAvailable(n) ((n & 0xFFFF) == 0)

enum JUTSeekPathResult {
    JUT_PATH_NONE,
    JUT_PATH_SUCCESS,
    JUT_PATH_PARENT_DIR,
    JUT_PATH_CUR_DIR,
};

class JUTSDCardFinder : public JKRFileFinder {
    JUTSDCardFinder(const char* path);

    virtual ~JUTSDCardFinder();
    virtual bool findNextFile(); // _0C

    // _00     = VTBL
    // _00-_14 = JKRFileFinder
    void* mUnk_14; // _14
    void* mUnk_18; // _18
    char mUnk_1C[0x5C - 0x1C]; // _1C
    u16 mUnk_5C;
    char mUnk_5E[0x6C - 0x5E]; // _5E
    u16 mUnk_6C; // _6C
};

struct JUTSDDrive {
  public:
    static bool init();
    static int setup(int nDrive);
    static int mount(int nDrive);
    static int unmount(int nDrive);
    static int format(int nDrive, u16 param2, const char* param3);
    static int terminate(int nDrive);
    static int removeFile(int nDrive, const char* fileName);
    static int renameFile(int nDrive, const char* curFileName, const char* newFileName);
    static int setCurrentDirectory(int nDrive, const char* path);
    static int makeDirectory(int nDrive, const char* newDirName);
    static int expandPath(int nDrive, const char* src, char* dest);

    static bool IsInitialized() {
        return sInitialized;
    }

    static int GetCurrentDrive() {
        return sCurrentDrive;
    }

    static void* GetDriveInfoPtr(int nDrive) {
        return sDriveInfoPtr[nDrive];
    }

    static char* GetCurrentPath(int nDrive) {
        return sCurrentPath[nDrive];
    }

    static bool GetAvailable(int nDrive) {
        return sAvailable[nDrive];
    }

    static bool GetMounted(int nDrive) {
        return sMounted[nDrive];
    }

  private:
    static bool sInitialized;
    static int sCurrentDrive;
    static void* sDriveInfoPtr[MAX_DRIVES];
    static char sCurrentPath[MAX_DRIVES][MAX_PATH_LEN - 1];
    static bool sAvailable[MAX_DRIVES];
    static bool sMounted[MAX_DRIVES];
};

JUTSeekPathResult JUTSeekPathString(const char* param1, char** param2, char** param3, int* param4);
void JUTCutTailPath(char* path);
char* JUTAppendDirectory(char* dest, const char* src);

#endif
