#include "JSystem/JUtility/JUTSDDrive.h"
#include "JSystem/JUtility/fs.h"

#include <string.h>

bool JUTSDDrive::sInitialized;
int JUTSDDrive::sCurrentDrive;
SDDriveInfo* JUTSDDrive::sDriveInfoPtr[MAX_DRIVES];
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
    if (FS_CardIFReset() != 0) {
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

u16 JUTSDDrive::setup(int nDrive) {
    u16 initStatus = FS_Init(0, 0, driveTable[nDrive]);
    u16 terminateStatus;
    u16 status;

    if (initStatus != 0) {
        sAvailable[nDrive] = false;
        sMounted[nDrive] = false;

        terminateStatus = JUTSDDrive::terminate(nDrive);

        if (terminateStatus != 0) {
            status = terminateStatus;
        } else {
            status = initStatus;
        }

        return status;
    }

    sAvailable[nDrive] = true;
    sMounted[nDrive] = false;
    strcpy(sCurrentPath[nDrive], "\\");
    return 0;
}

u16 JUTSDDrive::mount(int nDrive) {
    u16 status = FS_Mount(&sDriveInfoPtr[nDrive], driveTable[nDrive]);

    if (status != 0) {
        return status;
    }

    sMounted[nDrive] = true;
    return 0;
}

u16 JUTSDDrive::unmount(int nDrive) {
    u16 status = FS_Umount(sDriveInfoPtr[nDrive]);

    if (status != 0) {
        return status;
    }

    sMounted[nDrive] = false;
    return 0;
}

u16 JUTSDDrive::format(int nDrive, u16 param2, const char* param3) {
    return CheckStatus(FS_Format(param3, param2, driveTable[nDrive]));
}

u16 JUTSDDrive::terminate(int nDrive) {
    u16 status = SDTerm(driveTable[nDrive]);

    if (status != 0) {
        return status;
    }

    sAvailable[nDrive] = false;
    sMounted[nDrive] = false;
    return 0;
}

u16 JUTSDDrive::removeFile(int nDrive, const char* fileName) {
    char filePath[MAX_PATH_LEN];

    JUTSDDrive::expandPath(nDrive, fileName, filePath);
    return CheckStatus(FS_Delete(sDriveInfoPtr[nDrive], filePath));
}

u16 JUTSDDrive::renameFile(int nDrive, const char* curFileName, const char* newFileName) {
    char curFilePath[MAX_PATH_LEN];
    char newFilePath[MAX_PATH_LEN];

    JUTSDDrive::expandPath(nDrive, curFileName, curFilePath);
    JUTSDDrive::expandPath(nDrive, newFileName, newFilePath);
    return CheckStatus(FS_Rename(sDriveInfoPtr[nDrive], curFilePath, newFilePath));
}

u16 JUTSDDrive::setCurrentDirectory(int nDrive, const char* path) {
    char* curPath;
    char newPath[MAX_PATH_LEN];
    u16 status;

    curPath = sCurrentPath[nDrive];
    strcpy(newPath, curPath);
    JUTAppendDirectory(curPath, path);

    status = FS_Chdir(sDriveInfoPtr[nDrive], curPath);

    if (status != 0) {
        strcpy(curPath, newPath);
        return status;
    }

    return 0;
}

u16 JUTSDDrive::makeDirectory(int nDrive, const char* newDirName) {
    char newDirPath[MAX_PATH_LEN];

    JUTSDDrive::expandPath(nDrive, newDirName, newDirPath);
    return CheckStatus(FS_Mkdir(sDriveInfoPtr[nDrive], newDirPath));
}

JUTSDCardFinder::JUTSDCardFinder(const char* path) {
    u16 status;
    char finalPath[MAX_PATH_LEN];
    int currentDrive = JUTSDDrive::GetCurrentDrive();

    strcpy(finalPath, JUTSDDrive::GetCurrentPath(currentDrive));
    JUTAppendDirectory(finalPath, path);

    status = mUnk_6C = CheckStatus(FS_Opendir(JUTSDDrive::GetDriveInfoPtr(currentDrive), &mUnk_14, finalPath));
    mIsAvailable = status == 0;
}

JUTSDCardFinder::~JUTSDCardFinder() {
    u16 status = 0;

    if (mIsAvailable) {
        status = CheckStatus(FS_Closedir(mUnk_14));
    }

    mUnk_6C = status;
}

bool JUTSDCardFinder::findNextFile() {
    u16 status = CheckStatus(FS_Readdir(this->mUnk_14, &this->mUnk_18));

    this->mUnk_6C = status;

    if (status == 0xA030) {
        return false;
    }

    if (status != 0) {
        return false;
    }

    this->mIsDir = this->mUnk_18.unk_44 & FAT_ATTR_DIRECTORY;
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

u16 JUTSDDrive::expandPath(int nDrive, const char* src, char* dest) {
    strcpy(dest, JUTSDDrive::GetCurrentPath(nDrive));
    JUTAppendDirectory(dest, src);
    return 0;
}
