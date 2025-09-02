#include "JSystem/JUtility/JUTSDDrive.h"
#include "JSystem/JUtility/JUTFileSystem.h"

#include <string.h>

extern "C" int SDTerm(u16);

bool JUTSDDrive::sInitialized;
int JUTSDDrive::sCurrentDrive;
void* JUTSDDrive::sDriveInfoPtr[MAX_DRIVES];
char JUTSDDrive::sCurrentPath[MAX_DRIVES][MAX_PATH_LEN - 1];

bool JUTSDDrive::sAvailable[MAX_DRIVES] = {
    /* Memory Card Slot A */ false,
    /* Memory Card Slot B */ false,
};

bool JUTSDDrive::sMounted[MAX_DRIVES] = {
    /* Memory Card Slot A */ false,
    /* Memory Card Slot B */ false,
};

u16 driveTable[MAX_DRIVES] = {
    /* Memory Card Slot A */ DRIVE_SLOT_A,
    /* Memory Card Slot B */ DRIVE_SLOT_B,
};

bool JUTSDDrive::init() {
    if (!IsAvailable(FS_CardIFReset())) {
        return false;
    }

    sInitialized = true;
    sAvailable[DRIVE_SLOT_A] = false;
    sAvailable[DRIVE_SLOT_B] = false;
    sMounted[DRIVE_SLOT_A] = false;
    sMounted[DRIVE_SLOT_B] = false;
    sCurrentDrive = DRIVE_SLOT_A;
    return true;
}

int JUTSDDrive::setup(int nDrive) {
    unsigned int uVar1 = FS_Init(0, 0, driveTable[nDrive]);
    unsigned int uVar2;
    unsigned int ret;

    if (!IsAvailable(uVar1)) {
        sAvailable[nDrive] = false;
        sMounted[nDrive] = false;

        uVar2 = JUTSDDrive::terminate(nDrive);
        ret = uVar1;

        if (!IsAvailable(uVar2)) {
            ret = uVar2;
        }

        return ret;
    }

    sAvailable[nDrive] = true;
    sMounted[nDrive] = false;
    strcpy(sCurrentPath[nDrive], "\\");
    return 0;
}

int JUTSDDrive::mount(int nDrive) {
    unsigned int uVar1 = FS_Mount(&sDriveInfoPtr[nDrive], driveTable[nDrive]);

    if (!IsAvailable(uVar1)) {
        return uVar1;
    }

    sMounted[nDrive] = true;
    return 0;
}

int JUTSDDrive::unmount(int nDrive) {
    unsigned int uVar1 = FS_Umount(sDriveInfoPtr[nDrive]);

    if (!IsAvailable(uVar1)) {
        return uVar1;
    }

    sMounted[nDrive] = false;
    return 0;
}

int JUTSDDrive::format(int nDrive, u16 param2, const char* param3) {
    return Format(param3, param2, driveTable[nDrive]);
}

int JUTSDDrive::terminate(int nDrive) {
    unsigned int uVar1 = SDTerm(driveTable[nDrive]);

    if (!IsAvailable(uVar1)) {
        return uVar1;
    }

    sAvailable[nDrive] = false;
    sMounted[nDrive] = false;
    return 0;
}

int JUTSDDrive::removeFile(int nDrive, const char* fileName) {
    char filePath[MAX_PATH_LEN];

    JUTSDDrive::expandPath(nDrive, fileName, filePath);
    return Delete(sDriveInfoPtr[nDrive], filePath);
}

int JUTSDDrive::renameFile(int nDrive, const char* curFileName, const char* newFileName) {
    char curFilePath[MAX_PATH_LEN];
    char newFilePath[MAX_PATH_LEN];

    JUTSDDrive::expandPath(nDrive, curFileName, curFilePath);
    JUTSDDrive::expandPath(nDrive, newFileName, newFilePath);
    return Rename(sDriveInfoPtr[nDrive], curFilePath, newFilePath);
}

int JUTSDDrive::setCurrentDirectory(int nDrive, const char* path) {
    char* curPath;
    char newPath[MAX_PATH_LEN];
    unsigned int uVar1;

    curPath = sCurrentPath[nDrive];
    strcpy(newPath, curPath);
    JUTAppendDirectory(curPath, path);

    uVar1 = FS_Chdir(sDriveInfoPtr[nDrive], curPath);

    if (!IsAvailable(uVar1)) {
        strcpy(curPath, newPath);
        return uVar1;
    }

    return 0;
}

int JUTSDDrive::makeDirectory(int nDrive, const char* newDirName) {
    char newDirPath[MAX_PATH_LEN];

    JUTSDDrive::expandPath(nDrive, newDirName, newDirPath);
    return Mkdir(sDriveInfoPtr[nDrive], newDirPath);
}

JUTSDCardFinder::JUTSDCardFinder(const char* path) {
    unsigned int uVar1;
    char finalPath[MAX_PATH_LEN];
    int currentDrive = JUTSDDrive::GetCurrentDrive();

    strcpy(finalPath, JUTSDDrive::GetCurrentPath(currentDrive));
    JUTAppendDirectory(finalPath, path);

    uVar1 = Opendir(JUTSDDrive::GetDriveInfoPtr(currentDrive), &mUnk_14, finalPath);
    mUnk_6C = uVar1;
    mIsAvailable = IsAvailable(uVar1);
}

JUTSDCardFinder::~JUTSDCardFinder() {
    u32 uVar1 = 0;

    if (mIsAvailable) {
        uVar1 = Closedir(mUnk_14);
    }

    mUnk_6C = uVar1;
}

bool JUTSDCardFinder::findNextFile() {
    unsigned int uVar1;
    unsigned int uVar2;
    bool uVar3;

    uVar2 = Readdir(this->mUnk_14, &this->mUnk_18);
    uVar1 = uVar2 & 0xFFFF;
    this->mUnk_6C = uVar2;

    if (uVar1 == 0xA030) {
        return false;
    }

    if (!IsAvailable(uVar1)) {
        return false;
    }

    //! TODO: fake match?
    this->mIsDir = (this->mUnk_5C >> 4) & 1;
    return true;
}

JUTSeekPathResult JUTSeekPathString(const char* param1, char** param2, char** param3, int* param4) {
    char* param;
    int iVar2;

    if (param1 == NULL || *param1 == '\0') {
        return JUT_PATH_NONE;
    }

    param = (char*)param1;
    *param3 = (char*)param1;

    for (iVar2 = 0; *param != '\0'; param++, iVar2++) {
        if (*param == '\\' || *param == '/') {
            break;
        }
    }

    if (iVar2 == 0) {
        iVar2 = 1;
        param++;
    }

    while (*param == '\\' || *param == '/') {
        param++;
    }

    *param2 = *param != '\0' ? param : NULL;
    *param4 = iVar2;

    if ((*param3)[0] == '.') {
        if (iVar2 == 1) {
            return JUT_PATH_CUR_DIR;
        }

        if ((*param3)[1] == '.') {
            return JUT_PATH_PARENT_DIR;
        }
    }

    return JUT_PATH_SUCCESS;
}

void JUTCutTailPath(char* path) {
    char* pcVar1;
    char* pcVar2 = NULL;

    for (pcVar1 = path; *pcVar1 != '\0'; pcVar1++) {
        if (*pcVar1 == '\\') {
            pcVar2 = pcVar1;
        }
    }

    if (pcVar2 == NULL) {
        path[0] = '\\';
        path[1] = '\0';
        return;
    }

    if (pcVar2 == path) {
        path[1] = '\0';
        return;
    }

    *pcVar2 = '\0';
}

char* JUTAppendDirectory(char* dest, const char* src) {
    char* sp8;
    char* spC;
    int sp10;
    JUTSeekPathResult eResult = JUTSeekPathString(src, &sp8, &spC, &sp10);

    if (eResult == JUT_PATH_NONE) {
        return dest;
    }

    if (eResult != JUT_PATH_CUR_DIR) {
        if (eResult == JUT_PATH_PARENT_DIR) {
            JUTCutTailPath(dest);
        } else {
            if (*spC == '\\' || *spC == '/') {
                *dest = '\0';
                strncat(dest, spC, sp10);

                if (*dest == '/') {
                    *dest = '\\';
                }
            } else {
                if (dest[0] != '\\' || dest[1] != '\0') {
                    strcat(dest, "\\");
                }

                strncat(dest, spC, sp10);
            }
        }
    }

    JUTAppendDirectory(dest, sp8);
    return dest;
}

int JUTSDDrive::expandPath(int nDrive, const char* src, char* dest) {
    strcpy(dest, JUTSDDrive::GetCurrentPath(nDrive));
    JUTAppendDirectory(dest, src);
    return 0;
}
