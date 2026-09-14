#define FIX_SQRT_LINKAGE
#include "m_sdcard.h"

#include "JSystem/JUtility/JUTSDDrive.h"
#include "JSystem/JUtility/JUTSDFile.h"
#include "JSystem/JUtility/JUTTiff.h"
#include "JSystem/ResTIMG.h"
#include "dolphin/os.h"
#include "dolphin/card.h"
#include "dolphin/exi.h"
#include "dolphin/string.h"
#include "_mem.h"

extern "C" s32 zurumode_flag;
extern "C" ResTIMG* JW_Get_picture_copy_data_p(void);

// Unreferenced header statics occupy 0x40 bytes before the file registration record.
#pragma force_active on
static u8 unused_header_statics[0x40];
#pragma force_active reset

JUTSDFile S_sdfile00;
int S_driveno_now;
int testtesttest;
int S_tiffBufferSize;
char S_eng_name[13];
int S_CRV32;
u8 S_renban_chk[1250];

extern "C" void* mSD_Get_tex_p_inResTIMG(void* image);

extern "C" void S_CRV32SET(int v) { S_CRV32 = v; }

extern "C" int mCsd_tiffBufferSize_get(void) { return S_tiffBufferSize; }

extern "C" int mCsd_nowdrive_get(void) { return S_driveno_now; }

extern "C" void mCsd_nowdrive_set(int drive) { S_driveno_now = drive; }

extern "C" void mCsd_set_mura_filename(const u8* name) {
    int i = 8;
    memset(S_eng_name, 0, sizeof(S_eng_name));
    memcpy(S_eng_name, name, 8);
    while (true) {
        if (S_eng_name[i - 1] != ' ') break;
        S_eng_name[i - 1] = 0;
        i--;
    }
    S_eng_name[i] = '.';
    S_eng_name[i + 1] = 'D';
    S_eng_name[i + 2] = 'B';
    S_eng_name[i + 3] = 'M';
}

extern "C" void mCsd_set_mura_filename_tmp_set(void) {
    for (int i = 0; i < 10; i++) {
        if (S_eng_name[i] == '.') {
            S_eng_name[i + 1] = 'T';
            S_eng_name[i + 2] = 'M';
            S_eng_name[i + 3] = 'P';
            S_eng_name[i + 4] = 0;
            break;
        }
    }
}

extern "C" int mCsd_mura_filename_equal_cgeck(const u8* name) {
    int result = 1;
    for (int i = 0; i < 12; i++) {
        if (S_eng_name[i] == '.') break;
        if (S_eng_name[i] != name[i]) {
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" void mCsd_set_mura_filename_dbm_set(void) {
    for (int i = 0; i < 10; i++) {
        if (S_eng_name[i] == '.') {
            S_eng_name[i + 1] = 'D';
            S_eng_name[i + 2] = 'B';
            S_eng_name[i + 3] = 'M';
            S_eng_name[i + 4] = 0;
            break;
        }
    }
}

int mCsd_set_mura_filename_tmp_check(void) {
    int result = 0;
    for (int i = 0; i < 10; i++) {
        if (S_eng_name[i] == '.' && S_eng_name[i + 1] == 'T' &&
            S_eng_name[i + 2] == 'M' && S_eng_name[i + 3] == 'P') {
            result = 1;
            break;
        }
    }
    return result;
}

void mCsd_set_mura_filename_dbm_get(char* name) {
    int i = 9;
    memcpy(name, S_eng_name, sizeof(S_eng_name));
    while (true) {
        if (name[i] == '.') break;
        if (--i <= 0) return;
    }
    name[i + 1] = 'D';
    name[i + 2] = 'B';
    name[i + 3] = 'M';
    name[i + 4] = 0;
}

void mCsd_set_mura_filename_tmp_get(char* name) {
    int i = 9;
    memcpy(name, S_eng_name, sizeof(S_eng_name));
    while (true) {
        if (name[i] == '.') break;
        if (--i <= 0) return;
    }
    name[i + 1] = 'T';
    name[i + 2] = 'M';
    name[i + 3] = 'P';
    name[i + 4] = 0;
}

int mSD_fileentry_next(JUTSDCardFinder* finder, int directories) {
    int result = 0;
    if (!finder->isAvailable()) return 0;
    while (true) {
        if (!finder->findNextFile()) break;
        if (directories == 0 && finder->isDirectory()) continue;
        result = 1;
        break;
    }
    return result;
}

int mSD_DCIM_dirno_get(void) {
    int number = -1;
    u8 used[125];
    JUTSDCardFinder object("\\\\DCIM");
    JUTSDCardFinder* finder = &object;
    char path[40];

    memset(used, 0, sizeof(used));
    while (true) {
        if (mSD_fileentry_next(finder, 1) != 1) break;
        memcpy(path, finder->getPathName(), sizeof(path));
        if (path[6] >= '1' && path[6] <= '9' && path[7] >= '0' && path[7] <= '9' &&
            path[8] >= '0' && path[8] <= '9' && path[14] == 0) {
            int n = (path[6] - '0') * 100;
            n += (path[7] - '0') * 10;
            n += path[8] - '0';
            if (memcmp(path + 9, "NINTD", 6) == 0 && finder->isDirectory()) {
                number = n;
                break;
            }
            used[n / 8] |= (u8)(1 << (n % 8));
        }
    }
    if (number == -1) {
        for (int i = 12; i < 125; i++) {
            for (int bit = 0; bit < 8; bit++) {
                if (!(used[i] & (1 << bit))) {
                    number = i * 8 + bit;
                    if (number >= 100) {
                        i = 999;
                        break;
                    }
                    number = -1;
                }
            }
        }
    }
    return number;
}

extern "C" int mCsd_sdcard_selectslot_chk(s32 chan) {
    int result = -1;
    s32 mem_size = 0;
    s32 sector_size = 0;
    s32 probe;
    do { probe = EXIProbeEx(chan); } while (probe == 0);
    if (probe == 1 && (CARDProbeEx(chan, &mem_size, &sector_size) != 0 || sector_size != 0x2000)) {
        result = chan;
    }
    return result;
}

extern "C" int mCsd_sdcard_slot_chk(void) {
    int result = -1;
    s32 mem_size = 0;
    s32 sector_size = 0;
    for (s32 chan = 0; chan < 2; chan++) {
        s32 probe;
        do { probe = EXIProbeEx(chan); } while (probe == 0);
        if (probe == 1 && (CARDProbeEx(chan, &mem_size, &sector_size) != 0 || sector_size != 0x2000)) {
            result = chan;
            break;
        }
    }
    return result;
}

extern "C" int mCsd_sdcard_selectslot_sweet_chk(s32 chan) {
    int result = 1;
    if (mCsd_sdcard_selectslot_chk(chan) == -1) result = 0;
    return result;
}

extern "C" int mCsd_sdcard_sweet_chk(void) {
    int result = 1;
    if (mCsd_sdcard_slot_chk() == -1) result = 0;
    return result;
}

int mSD_sdcard_unmount(int drive) {
    int result = 0;
    if (JUTSDDrive::unmount(drive) != 0) result = 0x29;
    return result;
}

int mSD_sdcard_terminate(int drive) {
    int result = 0;
    if (JUTSDDrive::terminate(drive) != 0) result = 0x29;
    return result;
}

void mSD_unmout_and_terminate(int drive) {
    mSD_sdcard_unmount(drive);
    mSD_sdcard_terminate(drive);
}

void mSD_close_unmout_and_terminate(int drive) {
    S_sdfile00.close();
    mSD_unmout_and_terminate(drive);
}

int mSD_sdcard_init(void) {
    int result = 0;
    if (testtesttest == 0) {
        if (!JUTSDDrive::init()) result = 0x29;
        else testtesttest = 1;
    }
    return result;
}

int mSD_sdcard_setup(int drive) {
    int status = JUTSDDrive::setup(drive);
    if (status != 0) {
        if (status & 1) return 0x32;
        if ((status & 0x90) == 0x90) return 0x22;
        return 0x22;
    }
    return 0;
}

int mSD_sdcard_mount(int drive) {
    int result = 0;
    int status = JUTSDDrive::mount(drive);
    if (status != 0) {
        JUTSDDrive::terminate(drive);
        if (status == 0xA01A) return 0x23;
        else if (status == 0xA00E) return 0x24;
        else if (status & 0x4000) return 0x2E;
        else return 0x29;
    } else if (zurumode_flag >= 2 && S_CRV32 != 0) {
        JUTSDDrive::unmount(drive);
        JUTSDDrive::terminate(drive);
        result = 0x23;
    }
    return result;
}

int mSD_sdcard_makeDirectory(int drive, char* path) {
    int result = 0;
    u16 status = JUTSDDrive::makeDirectory(path);
    if (status != 0 && status != 0xA011) {
        mSD_unmout_and_terminate(drive);
        if (status & 0x400) return 0x25;
        else if (status == 0xA012) return 0x24;
        else if (status == 0xA01A) return 0x23;
        else if (status & 0x4000) return 0x2E;
        else if (mCsd_sdcard_selectslot_sweet_chk(drive) == 1) return 0x29;
        else return 0x22;
    } else if (zurumode_flag >= 2 && S_CRV32 != 0) {
        mSD_unmout_and_terminate(drive);
        result = 0x23;
    }
    return result;
}

int mSD_sdcard_fileopen(int drive, char* path, u16 mode) {
    int result = 0;
    if (!S_sdfile00.open(path, mode)) {
        int status = S_sdfile00.getErrorStatus();
        mSD_unmout_and_terminate(drive);
        if (status == 0xA007) return 0x2A;
        else if (status == 0xA006) return 0x2A;
        else if (status == 0xA012) return 0x24;
        else if (status == 0xA01A) return 0x23;
        else if (status & 0x400) return 0x25;
        else if (status & 0x4000) return 0x2E;
        else return 0x29;
    } else if (zurumode_flag >= 2 && S_CRV32 != 0) {
        mSD_close_unmout_and_terminate(drive);
        result = 0x23;
    }
    return result;
}

int mSD_sdcard_create_fileopen(int drive, char* path, int overwrite) {
    int result = 0;
    int failed = 0;
    if (!S_sdfile00.open(path, 2)) {
        if (!S_sdfile00.open(path, 0x204)) failed = 1;
    } else {
        S_sdfile00.close();
        if (overwrite == 0) {
            mSD_unmout_and_terminate(drive);
            return 0x2D;
        }
        if (!S_sdfile00.open(path, 0x802)) failed = 1;
    }
    if (failed == 1) {
        result = S_sdfile00.getErrorStatus();
        mSD_unmout_and_terminate(drive);
        if (result == 0xA007) return 0x2A;
        else if (result == 0xA006) return 0x33;
        else if (result == 0xA012) return 0x24;
        else if (result == 0xA01A) return 0x23;
        else if (result & 0x400) return 0x25;
        else if (result & 0x4000) return 0x2E;
        else return 0x29;
    } else if (zurumode_flag >= 2 && S_CRV32 != 0) {
        S_sdfile00.close();
        mSD_unmout_and_terminate(drive);
        result = 0x23;
    }
    return result;
}

int mSD_sdcard_filewrite(int drive, u8* data, int size, char* path) {
    int result = 0;
    if (S_sdfile00.writeData(data, size, 0) < 0) {
        int status = S_sdfile00.getErrorStatus();
        S_sdfile00.close();
        JUTSDDrive::removeFile(drive, path);
        mSD_unmout_and_terminate(drive);
        if (status == 0xA012) return 0x24;
        else if (status == 0xA01A) return 0x23;
        else if (status & 0x400) return 0x25;
        else if (status & 0x4000) return 0x2E;
        else if ((status & 0xB0) == 0xB0) return 0x22;
        else return 0x29;
    } else if (zurumode_flag >= 2 && S_CRV32 != 0) {
        S_sdfile00.close();
        mSD_unmout_and_terminate(drive);
        result = 0x23;
    }
    return result;
}

int mSD_sdcard_filerename(int drive, char* from, char* to) {
    JUTSDDrive::renameFile(drive, from, to);
    return 0;
}

int mSD_sdcard_fileread(int drive, char* data, int size) {
    int result = 0;
    if (S_sdfile00.readData(data, size, 0) < 0) {
        int status = S_sdfile00.getErrorStatus();
        mSD_close_unmout_and_terminate(drive);
        if (status == 0xA01A) return 0x23;
        else if (status & 0x4000) return 0x2E;
        else if ((status & 0xB0) == 0xB0) return 0x22;
        else return 0x29;
    } else if (zurumode_flag >= 2 && S_CRV32 != 0) {
        mSD_close_unmout_and_terminate(drive);
        result = 0x23;
    }
    return result;
}

int mSD_sdcard_tiff_fileread(int drive, char* data, int size) {
    int result = 0;
    int read = S_sdfile00.readData(data, size, 0);
    if (read < 0) {
        int status = S_sdfile00.getErrorStatus();
        mSD_close_unmout_and_terminate(drive);
        if (status == 0xA01A) return 0x23;
        else if (status & 0x4000) return 0x2E;
        else return 0x29;
    } else if (read > 0xE15D0) {
        mSD_close_unmout_and_terminate(drive);
        return 0x2B;
    } else if (zurumode_flag >= 2 && S_CRV32 != 0) {
        mSD_close_unmout_and_terminate(drive);
        result = 0x23;
    }
    return result;
}

int mSD_sdcard_format_common(int drive) {
    int result = 0x21;
    u16 status = JUTSDDrive::format(drive, 2, NULL);
    if (status != 0) {
        if (status & 0x400) result = 0x25;
        else if (status & 1) result = 0x32;
        else if (status & 0x4000) result = 0x2E;
        else {
            switch (status) {
                case 0xA037: result = 0x22; break;
                default: result = 0x29; break;
            }
        }
    }
    return result;
}

int mSD_sdcard_removeFile_common(int drive, char* path) {
    int result = 0;
    u16 status = JUTSDDrive::removeFile(drive, path);
    if (status != 0) {
        if (status & 0x400) result = 0x25;
        else result = 0x29;
    }
    return result;
}

int mSD_set_tiffname(char* path, int number) {
    int result = 1;
    memset(path, 0, 40);
    memcpy(path, "\\DCIM\\100NINTD\\MORI", 19);
    int dir = mSD_DCIM_dirno_get();
    if (dir != -1) {
        path[6] = dir / 100 + '0';
        dir -= dir / 100 * 100;
        path[7] = dir / 10 + '0';
        dir -= dir / 10 * 10;
        path[8] = dir + '0';
        path[19] = number / 1000 + '0';
        number -= number / 1000 * 1000;
        path[20] = number / 100 + '0';
        number -= number / 100 * 100;
        path[21] = number / 10 + '0';
        number -= number / 10 * 10;
        path[22] = number + '0';
        path[23] = '.';
        path[24] = 'T';
        path[25] = 'I';
        path[26] = 'F';
    } else {
        result = 0;
    }
    return result;
}

void mSD_tiff_nextnumber_get_common(int* number, int* count) {
    char path[40];
    char directory[40];
    char digits[40];
    *number = -1;
    int end = 0;
    int dir = mSD_DCIM_dirno_get();
    if (dir != -1) {
        memcpy(directory, "\\\\DCIM\\100NINTD", 16);
        directory[7] = dir / 100 + '0';
        dir -= dir / 100 * 100;
        directory[8] = dir / 10 + '0';
        dir -= dir / 10 * 10;
        directory[9] = dir + '0';
    } else {
        return;
    }
    JUTSDCardFinder object(directory);
    JUTSDCardFinder* finder = &object;
    for (int i = 0; i < *count; i++) {
        if (mSD_fileentry_next(finder, 0) != 1) {
            end = 1;
            break;
        }
    }
    while (!end) {
        (*count)++;
        if (mSD_fileentry_next(finder, 0) != 1) break;
        memcpy(path, finder->getPathName(), 40);
        if (memcmp(path + 1, directory + 2, 13) == 0 && memcmp(path + 14, "\\MORI", 5) == 0 &&
            memcmp(path + 23, ".TIF", 4) == 0) {
            memset(digits, 0, 40);
            memcpy(digits, path + 19, 4);
            if (digits[0] >= '0' && digits[0] <= '9' && digits[1] >= '0' && digits[1] <= '9' &&
                digits[2] >= '0' && digits[2] <= '9' && digits[3] >= '0' && digits[3] <= '9') {
                int n = (digits[0] - '0') * 1000;
                n += (digits[1] - '0') * 100;
                n += (digits[2] - '0') * 10;
                n += digits[3] - '0';
                if (n != 0) {
                    *number = n;
                    break;
                }
            }
        }
    }
}

int mSD_tiff_get_spacenumber_get(void) {
    int number = -1;
    char path[40];
    char directory[40];
    char digits[40];
    u8* used = S_renban_chk;
    if (used == NULL) return -1;
    memset(used, 0, sizeof(S_renban_chk));
    int dir = mSD_DCIM_dirno_get();
    if (dir != -1) {
        memcpy(directory, "\\\\DCIM\\100NINTD", 16);
        directory[7] = dir / 100 + '0';
        dir -= dir / 100 * 100;
        directory[8] = dir / 10 + '0';
        dir -= dir / 10 * 10;
        directory[9] = dir + '0';
    } else {
        return -1;
    }
    JUTSDCardFinder object(directory);
    JUTSDCardFinder* finder = &object;
    while (true) {
        if (mSD_fileentry_next(finder, 1) != 1) break;
        memcpy(path, finder->getPathName(), 40);
        if (memcmp(path + 1, directory + 2, 13) == 0) {
            memset(digits, 0, 40);
            memcpy(digits, path + 19, 4);
            if (digits[0] >= '0' && digits[0] <= '9' && digits[1] >= '0' && digits[1] <= '9' &&
                digits[2] >= '0' && digits[2] <= '9' && digits[3] >= '0' && digits[3] <= '9') {
                int n = (digits[0] - '0') * 1000;
                n += (digits[1] - '0') * 100;
                n += (digits[2] - '0') * 10;
                n += digits[3] - '0';
                used[n / 8] |= (u8)(1 << (n % 8));
            }
        }
    }
    for (int i = 0; i < 1250; i++) {
        for (int bit = 0; bit < 8; bit++) {
            if (!((1 << bit) & used[i])) {
                number = bit + i * 8;
                if (number > 0) {
                    i = 9999;
                    break;
                }
                number = -1;
            }
        }
    }
    return number;
}

int mSD_tiff_get_startnumber_common(void) {
    int number = -1;
    char path[40];
    char directory[40];
    char digits[40];
    int dir = mSD_DCIM_dirno_get();
    if (dir != -1) {
        memcpy(directory, "\\\\DCIM\\100NINTD", 16);
        directory[7] = dir / 100 + '0';
        dir -= dir / 100 * 100;
        directory[8] = dir / 10 + '0';
        dir -= dir / 10 * 10;
        directory[9] = dir + '0';
    } else {
        return 0;
    }
    JUTSDCardFinder object(directory);
    JUTSDCardFinder* finder = &object;
    while (true) {
        if (mSD_fileentry_next(finder, 0) != 1) break;
        memcpy(path, finder->getPathName(), 40);
        if (memcmp(path + 1, directory + 2, 13) == 0 && memcmp(path + 14, "\\MORI", 5) == 0 &&
            memcmp(path + 23, ".TIF", 4) == 0) {
            memset(digits, 0, 40);
            memcpy(digits, path + 19, 4);
            if (digits[0] >= '0' && digits[0] <= '9' && digits[1] >= '0' && digits[1] <= '9' &&
                digits[2] >= '0' && digits[2] <= '9' && digits[3] >= '0' && digits[3] <= '9') {
                int n = (digits[0] - '0') * 1000;
                n += (digits[1] - '0') * 100;
                n += (digits[2] - '0') * 10;
                n += digits[3] - '0';
                if (n != 0) {
                    if (number < 0) number = n;
                    if (n < number) number = n;
                }
            }
        }
    }
    return number;
}

u8 tiff_commentStr[91] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x96, 0x7B, 0x89, 0xE6,
    0x91, 0x9C, 0x82, 0xCC, 0x8E, 0x67, 0x97, 0x70, 0x94, 0xCD, 0x88, 0xCD,
    0x82, 0xC9, 0x82, 0xC2, 0x82, 0xA2, 0x82, 0xC4, 0x82, 0xCD, 0x81, 0x41,
    0x81, 0x77, 0x82, 0xC7, 0x82, 0xA4, 0x82, 0xD4, 0x82, 0xC2, 0x82, 0xCC,
    0x90, 0x58, 0x65, 0x81, 0x7B, 0x81, 0x78, 0x82, 0xCC, 0x83, 0x51, 0x81,
    0x5B, 0x83, 0x80, 0x8E, 0xE6, 0x88, 0xB5, 0x90, 0xE0, 0x96, 0xBE, 0x8F,
    0x91, 0x82, 0xF0, 0x82, 0xA8, 0x93, 0xC7, 0x82, 0xDD, 0x82, 0xAD, 0x82,
    0xBE, 0x82, 0xB3, 0x82, 0xA2, 0x81, 0x42,
};

// @fabricated -- necessary for weak function ordering
extern "C" int mSD_tiff_get_compression(void* image) {
    JUTTiff object;
    JUTTiff* tiff = &object;
    int width = tiff->getImageWidth();
    int height = tiff->getImageHeight();
    int compression = tiff->getCompression();

    return compression;
}

extern "C" int mSD_tiff_make(void* image, void* buffer) {
    JUTTiff object;
    JUTTiff* tiff = &object;
    OSCalendarTime time;
    u8 date[20];
    tiff->setImageArea((u8*)image, 640, 480, GX_U8);
    if (JW_Get_picture_copy_data_p() != NULL) {
        ResTIMG* picture = JW_Get_picture_copy_data_p();
        tiff->setDecalImageArea((u8*)mSD_Get_tex_p_inResTIMG(picture), GX_U8,
                              picture->mSizeX, picture->mSizeY, 0xF81F);
        tiff->setDecalImagePos(608 - picture->mSizeX, 456 - picture->mSizeY);
    }
    tiff->setThumbnailIncluding(false);
    tiff->setTitle((u8*)"DOUBUTSUNOMORIe+ photo");
    tiff->setMaker((u8*)"Nintendo Co.,Ltd.");
    tiff->setModel((u8*)"NINTENDO GAMECUBE");
    tiff->setCopyright((u8*)"Copyright Nintendo, 2001-2003. All reserved.", NULL);
    tiff->setSoftware((u8*)"DOUBUTSUNOMORIe+");
    tiff->setArtist((u8*)"Nintendo Co.,Ltd.");
    tiff->setComment(tiff_commentStr, sizeof(tiff_commentStr));
    OSTicksToCalendarTime(OSGetTime(), &time);
    memset(date, 0, sizeof(date));
    int value = time.year;
    date[0] = value / 1000 + '0';
    value -= value / 1000 * 1000;
    date[1] = value / 100 + '0';
    value -= value / 100 * 100;
    date[2] = value / 10 + '0';
    value -= value / 10 * 10;
    date[3] = value + '0';
    date[4] = ':';
    value = time.mon;
    date[5] = value / 10 + '0';
    value -= value / 10 * 10;
    date[6] = value + '0';
    date[7] = ':';
    value = time.mday;
    date[8] = value / 10 + '0';
    value -= value / 10 * 10;
    date[9] = value + '0';
    date[10] = ' ';
    value = time.hour;
    date[11] = value / 10 + '0';
    value -= value / 10 * 10;
    date[12] = value + '0';
    date[13] = ':';
    value = time.min;
    date[14] = value / 10 + '0';
    value -= value / 10 * 10;
    date[15] = value + '0';
    date[16] = ':';
    value = time.sec;
    date[17] = value / 10 + '0';
    value -= value / 10 * 10;
    date[18] = value + '0';
    tiff->setDate_modified(date);
    tiff->setDate_original(date);
    tiff->setDate_digitized(date);
    tiff->create((u8*)buffer);
    S_tiffBufferSize = tiff->getFileSize();
    return 1;
}

extern "C" int mSD_sdcard_test(int drive) {
    int result = mSD_sdcard_init();
    if (result != 0) return result;
    result = mSD_sdcard_setup(drive);
    if (result != 0) return result;
    result = mSD_sdcard_mount(drive);
    if (result != 0) return result;
    result = mSD_sdcard_unmount(drive);
    if (result != 0) return result;
    result = mSD_sdcard_terminate(drive);
    if (result != 0) return result;
    return result;
}

extern "C" int mSD_sdcard_mura_write(void* data, u32 size, int overwrite) {
    int drive = mCsd_nowdrive_get();
    int result = mSD_sdcard_init();
    if (result != 0) return result;
    result = mSD_sdcard_setup(drive);
    if (result != 0) return result;
    result = mSD_sdcard_mount(drive);
    if (result != 0) return result;
    JUTSDDrive::setCurrentDrive(drive);
    JUTSDDrive::setCurrentDirectory("//");
    if (JUTSDDrive::setCurrentDirectory("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU") != 0) {
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE");
        if (result != 0) return result;
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE/GAMECUBE");
        if (result != 0) {
            if (result == 0x29) result = 0x33;
            return result;
        }
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE/GAMECUBE/NINTENDO");
        if (result != 0) {
            if (result == 0x29) result = 0x33;
            return result;
        }
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE/GAMECUBE/NINTENDO/DOUBUTU");
        if (result != 0) {
            if (result == 0x29) result = 0x33;
            return result;
        }
    }
    if (JUTSDDrive::setCurrentDirectory("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU") != 0) {
        mSD_unmout_and_terminate(drive);
        return 0x33;
    }
    result = (u16)mSD_sdcard_create_fileopen(drive, S_eng_name, overwrite);
    if (result != 0) return result;
    result = (u16)mSD_sdcard_filewrite(drive, (u8*)data, size, S_eng_name);
    if (result != 0) return result;
    S_sdfile00.close();
    if (mCsd_set_mura_filename_tmp_check() == 1) {
        char tmp[16];
        char dbm[16];
        mCsd_set_mura_filename_tmp_get(tmp);
        mCsd_set_mura_filename_dbm_get(dbm);
        JUTSDDrive::removeFile(drive, dbm);
        mCsd_set_mura_filename_dbm_set();
        mSD_sdcard_filerename(drive, tmp, dbm);
        JUTSDDrive::removeFile(drive, tmp);
    }
    result = mSD_sdcard_unmount(drive);
    if (result != 0) return result;
    result = mSD_sdcard_terminate(drive);
    if (result != 0) return result;
    return 0;
}

extern "C" int mSD_sdcard_tiff_write(void* data, u32 size) {
    int drive = mCsd_nowdrive_get();
    int result = mSD_sdcard_init();
    if (result != 0) return result;
    result = mSD_sdcard_setup(drive);
    if (result != 0) return result;
    result = mSD_sdcard_mount(drive);
    if (result != 0) return result;
    JUTSDDrive::setCurrentDrive(drive);
    JUTSDDrive::setCurrentDirectory("//");
    int dir = mSD_DCIM_dirno_get();
    if (dir == -1) {
        mSD_unmout_and_terminate(drive);
        return 0x30;
    }
    char filename[40];
    char directory[40];
    memcpy(directory, "\\\\DCIM\\100NINTD", 16);
    directory[7] = dir / 100 + '0';
    dir -= dir / 100 * 100;
    directory[8] = dir / 10 + '0';
    dir -= dir / 10 * 10;
    directory[9] = dir + '0';
    if (JUTSDDrive::setCurrentDirectory(directory) != 0) {
        result = mSD_sdcard_makeDirectory(drive, "DCIM");
        if (result != 0) return result;
        result = mSD_sdcard_makeDirectory(drive, directory);
        if (result != 0) {
            if (result == 0x29) result = 0x33;
            return result;
        }
    }
    if (JUTSDDrive::setCurrentDirectory(directory) != 0) {
        mSD_unmout_and_terminate(drive);
        return 0x33;
    }
    int number = mSD_tiff_get_spacenumber_get();
    if (number == -1) {
        mSD_unmout_and_terminate(drive);
        return 0x28;
    }
    memset(filename, 0, 40);
    memcpy(filename, "MORI", 4);
    filename[4] = number / 1000 + '0';
    number -= number / 1000 * 1000;
    filename[5] = number / 100 + '0';
    number -= number / 100 * 100;
    filename[6] = number / 10 + '0';
    number -= number / 10 * 10;
    filename[7] = number + '0';
    filename[8] = '.';
    filename[9] = 'T';
    filename[10] = 'I';
    filename[11] = 'F';
    result = (u16)mSD_sdcard_create_fileopen(drive, filename, 1);
    if (result != 0) return result;
    result = (u16)mSD_sdcard_filewrite(drive, (u8*)data, size, filename);
    if (result != 0) return result;
    S_sdfile00.close();
    result = mSD_sdcard_unmount(drive);
    if (result != 0) return result;
    result = mSD_sdcard_terminate(drive);
    if (result != 0) return result;
    return 0;
}

extern "C" int mSD_sdcard_mura_read(void* data, u32 size) {
    int drive = mCsd_nowdrive_get();
    int result = mSD_sdcard_init();
    if (result != 0) return result;
    result = mSD_sdcard_setup(drive);
    if (result != 0) return result;
    result = mSD_sdcard_mount(drive);
    if (result != 0) return result;
    JUTSDDrive::setCurrentDrive(drive);
    if (JUTSDDrive::setCurrentDirectory("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU") != 0) {
        mSD_unmout_and_terminate(drive);
        return 0x2A;
    }
    result = mSD_sdcard_fileopen(drive, S_eng_name, 4);
    if (result != 0) return result;
    result = mSD_sdcard_fileread(drive, (char*)data, size);
    if (result != 0) return result;
    S_sdfile00.close();
    result = mSD_sdcard_unmount(drive);
    if (result != 0) return result;
    result = mSD_sdcard_terminate(drive);
    if (result != 0) return result;
    return 0;
}

extern "C" int mSD_sdcard_tiff_read_common(void* data, s32 size, s32 number) {
    int drive = mCsd_nowdrive_get();
    int result = mSD_sdcard_init();
    if (result != 0) return result;
    result = mSD_sdcard_setup(drive);
    if (result != 0) return result;
    result = mSD_sdcard_mount(drive);
    if (result != 0) return result;
    JUTSDDrive::setCurrentDrive(drive);
    if (JUTSDDrive::setCurrentDirectory("//") != 0) {
        mSD_unmout_and_terminate(drive);
        return 0x29;
    }
    char path[40];
    if (mSD_set_tiffname(path, number) == 0) return 0x29;
    result = mSD_sdcard_fileopen(drive, path, 4);
    if (result != 0) return result;
    result = mSD_sdcard_tiff_fileread(drive, (char*)data, size);
    if (result != 0) return result;
    JUTTiff tiff;
    JUTTiff* info = &tiff;
    if (!info->getInfo((u8*)data)) result = 0x2B;
    else if (info->getImageWidth() != 640 || info->getImageHeight() != 480 ||
             info->getCompression() != JUTTiff_COMPRESSION_UNCOMPRESSED) result = 0x2B;
    // The original calls operator delete on this stack-allocated object.
    delete info;
    if (result != 0) {
        mSD_close_unmout_and_terminate(drive);
        return result;
    }
    S_sdfile00.close();
    result = mSD_sdcard_unmount(drive);
    if (result != 0) return result;
    result = mSD_sdcard_terminate(drive);
    if (result != 0) return result;
    return 0;
}

extern "C" int mSD_tiff_nextnumber_get(int* number, int* count) {
    int result;
    int dir;
    char directory[40];
    int slot = mCsd_sdcard_slot_chk();
    if (slot < 0) return 0x22;
    mCsd_nowdrive_set(slot);
    int drive = mCsd_nowdrive_get();
    result = mSD_sdcard_init();
    if (result != 0) goto exit;
    result = mSD_sdcard_setup(drive);
    if (result != 0) goto exit;
    result = mSD_sdcard_mount(drive);
    if (result != 0) goto exit;
    JUTSDDrive::setCurrentDrive(drive);
    dir = mSD_DCIM_dirno_get();
    if (dir != -1) {
        memcpy(directory, "\\\\DCIM\\100NINTD", 16);
        directory[7] = dir / 100 + '0';
        dir -= dir / 100 * 100;
        directory[8] = dir / 10 + '0';
        dir -= dir / 10 * 10;
        directory[9] = dir + '0';
    } else {
        *number = -1;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    if (JUTSDDrive::setCurrentDirectory(directory) != 0) {
        *number = -1;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    mSD_tiff_nextnumber_get_common(number, count);
    mSD_unmout_and_terminate(drive);
exit:
    return result;
}

extern "C" int mSD_tiff_picno_remove(int number) {
    char path[40];
    int result;
    int drive = mCsd_nowdrive_get();
    result = mSD_sdcard_init();
    if (result != 0) goto exit;
    result = mSD_sdcard_setup(drive);
    if (result != 0) goto exit;
    result = mSD_sdcard_mount(drive);
    if (result != 0) goto exit;
    JUTSDDrive::setCurrentDrive(drive);
    if (JUTSDDrive::setCurrentDirectory("//") != 0) {
        result = 0x29;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    if (mSD_set_tiffname(path, number) == 0) {
        result = 0x29;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    result = mSD_sdcard_removeFile_common(drive, path);
    mSD_unmout_and_terminate(drive);
exit:
    return result;
}

int mSD_tiff_remove_min(void) {
    int number;
    char path[40];
    int result;
    int drive = mCsd_nowdrive_get();
    result = mSD_sdcard_init();
    if (result != 0) goto exit;
    result = mSD_sdcard_setup(drive);
    if (result != 0) goto exit;
    result = mSD_sdcard_mount(drive);
    if (result != 0) goto exit;
    JUTSDDrive::setCurrentDrive(drive);
    if (JUTSDDrive::setCurrentDirectory("//") != 0) {
        result = 0x29;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    number = mSD_tiff_get_startnumber_common();
    if (number < 0) {
        result = -1;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    if (mSD_set_tiffname(path, number) == 0) {
        result = -1;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    result = mSD_sdcard_removeFile_common(drive, path);
    mSD_unmout_and_terminate(drive);
exit:
    return result;
}

extern "C" int mSD_tiff_remove_all(void) {
    int result = 0;
    int removed = 0;
    int drive = mCsd_sdcard_slot_chk();
    if (drive < 0) return 0x22;
    mCsd_nowdrive_set(drive);
    while (true) {
        int status = mSD_tiff_remove_min();
        if (status == -1) break;
        if (status != 0) {
            result = status;
            break;
        }
        removed = 1;
    }
    if (result == 0 && !removed) result = 0x2A;
    return result;
}

extern "C" int mSD_sdcard_format(void) {
    int result;
    int drive = mCsd_nowdrive_get();
    result = mSD_sdcard_init();
    if (result == 0) {
        result = mSD_sdcard_setup(drive);
        if (result != 0) {
            if (result == 0x29) result = 0x32;
        } else {
            for (int i = 0; i < 5; i++) {
                result = mSD_sdcard_format_common(drive);
                if (result != 0x2E) break;
            }
            mSD_sdcard_terminate(drive);
        }
    }
    return result;
}

extern "C" bool mSD_TiffToRGB565(void* src, void* dst) {
    JUTTiff tiff = JUTTiff();
    if (!tiff.getInfo((u8*)src)) return 0;
    u32 width = tiff.getImageWidth();
    u32 height = tiff.getImageHeight();
    u32 compression = tiff.getCompression();
    if (width != 640 || height != 480 || compression != JUTTiff_COMPRESSION_UNCOMPRESSED) return false;
    return JUTTiff::convertTiffToTimg((u8*)src, (u8*)dst, GX_TF_RGB565) != 0;
}

static int mSD_mura_nextname_get_common_common(char* name, int* count);

extern "C" void* mSD_Get_tex_p_inResTIMG(void* image) { return (u8*)image + 0x20; }

int mSD_mura_nextname_get_common_common(char* name, int* count) {
    int result = 0;
    int end = 0;
    int i;
    int invalid;
    char path[80];
    JUTSDCardFinder object("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU");
    JUTSDCardFinder* finder = &object;
    for (i = 0; i < *count; i++) {
        if (mSD_fileentry_next(finder, 0) != 1) {
            end = 1;
            break;
        }
    }
    while (!end) {
        invalid = 0;
        size_t length = 0;
        (*count)++;
        if (mSD_fileentry_next(finder, 0) != 1) break;
        memcpy(path, finder->getPathName(), sizeof(path));
        while (true) {
            if (memcmp(&path[length + 35], ".DBM", 4) == 0) break;
            u32 c = path[length + 35];
            if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                length++;
                if (length <= 8) continue;
                invalid = 1;
                break;
            } else {
                invalid = 1;
                break;
            }
        }
        if (invalid) continue;
        memset(name, ' ', 8);
        memcpy(name, path + 35, length);
        memset(S_eng_name, 0, sizeof(S_eng_name));
        memcpy(S_eng_name, name, length);
        S_eng_name[length] = '.';
        S_eng_name[length + 1] = 'D';
        S_eng_name[length + 2] = 'B';
        S_eng_name[length + 3] = 'M';
        result = 1;
        break;
    }
    return result;
}

extern "C" int mSD_mura_nextname_get_common(u8* name, int* count) {
    int result;
    int slot = mCsd_sdcard_slot_chk();
    if (slot < 0) return 0x22;
    mCsd_nowdrive_set(slot);
    int drive = mCsd_nowdrive_get();
    result = mSD_sdcard_init();
    if (result != 0) goto exit;
    result = mSD_sdcard_setup(drive);
    if (result != 0) goto exit;
    result = mSD_sdcard_mount(drive);
    if (result != 0) goto exit;
    JUTSDDrive::setCurrentDrive(drive);
    if (JUTSDDrive::setCurrentDirectory("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU") != 0) {
        result = 0x2C;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    if (mSD_mura_nextname_get_common_common((char*)name, count) == 0) result = 0x2C;
    mSD_unmout_and_terminate(drive);
exit:
    return result;
}

extern "C" int mSD_mura_allcount_get_common(s32* count) {
    static int next_cnt;
    u8 name[24];
    int result;
    int n = 0;
    next_cnt = 0;
    while (true) {
        result = mSD_mura_nextname_get_common(name, &next_cnt);
        if (result != 0) break;
        n++;
        if (n > 1) goto exit;
    }
    if (result == 0x2C) result = 0;
exit:
    *count = n;
    return result;
}

extern "C" int mSD_mura_specification_remove(const u8* name) {
    int drive;
    int length = 8;
    char filename[12];
    char path[80];
    int result;
    drive = mCsd_nowdrive_get();
    result = mSD_sdcard_init();
    if (result != 0) goto exit;
    result = mSD_sdcard_setup(drive);
    if (result != 0) goto exit;
    result = mSD_sdcard_mount(drive);
    if (result != 0) goto exit;
    JUTSDDrive::setCurrentDrive(drive);
    if (JUTSDDrive::setCurrentDirectory("//") != 0) {
        result = 0x29;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    memset(filename, 0, 12);
    memset(path, 0, 80);
    memcpy(path, "//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU/", 36);
    memcpy(filename, name, 8);
    while (true) {
        if (filename[length - 1] != ' ') break;
        length--;
    }
    filename[length] = '.';
    filename[length + 1] = 'D';
    filename[length + 2] = 'B';
    filename[length + 3] = 'M';
    memcpy(path + 36, filename, length + 4);
    result = mSD_sdcard_removeFile_common(drive, path);
    mSD_unmout_and_terminate(drive);
exit:
    return result;
}

extern "C" int mSD_mura_remove_all(void) {
    int result = 0;
    static int next_cnt = 0;
    u8 name[8];
    int removed = 0;
    int status;
    while (true) {
        next_cnt = 0;
        status = mSD_mura_nextname_get_common(name, &next_cnt);
        if (status != 0) break;
        status = mSD_mura_specification_remove(name);
        if (status != 0) {
            result = status;
            goto exit;
        }
        removed = 1;
    }
    if (status != 0x2C) result = status;
exit:
    if (result == 0 && removed == 0) result = 0x2A;
    return result;
}

extern "C" int mSD_mura_repayment_remove(void) {
    int result;
    int drive = mCsd_nowdrive_get();
    result = mSD_sdcard_init();
    if (result != 0) goto exit;
    result = mSD_sdcard_setup(drive);
    if (result != 0) goto exit;
    result = mSD_sdcard_mount(drive);
    if (result != 0) goto exit;
    JUTSDDrive::setCurrentDrive(drive);
    if (JUTSDDrive::setCurrentDirectory("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU/") != 0) {
        result = 0x22;
        mSD_unmout_and_terminate(drive);
        goto exit;
    }
    result = mSD_sdcard_removeFile_common(drive, S_eng_name);
    mSD_unmout_and_terminate(drive);
exit:
    return result;
}

extern "C" int mSD_mura_make_directory(void) {
    int slot = mCsd_sdcard_slot_chk();
    if (slot < 0) return 0x22;
    mCsd_nowdrive_set(slot);
    int drive = mCsd_nowdrive_get();
    int result = mSD_sdcard_init();
    if (result != 0) return result;
    result = mSD_sdcard_setup(drive);
    if (result != 0) return result;
    result = mSD_sdcard_mount(drive);
    if (result != 0) return result;
    JUTSDDrive::setCurrentDrive(drive);
    JUTSDDrive::setCurrentDirectory("//");
    if (JUTSDDrive::setCurrentDirectory("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU") != 0) {
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE");
        if (result != 0) return result;
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE/GAMECUBE");
        if (result != 0) {
            if (result == 0x29) result = 0x33;
            return result;
        }
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE/GAMECUBE/NINTENDO");
        if (result != 0) {
            if (result == 0x29) result = 0x33;
            return result;
        }
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE/GAMECUBE/NINTENDO/DOUBUTU");
        if (result != 0) {
            if (result == 0x29) result = 0x33;
            return result;
        }
    }
    if (JUTSDDrive::setCurrentDirectory("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU") != 0) {
        mSD_unmout_and_terminate(drive);
        return 0x33;
    }
    result = mSD_sdcard_unmount(drive);
    if (result != 0) return result;
    result = mSD_sdcard_terminate(drive);
    if (result != 0) return result;
    return 0;
}

extern "C" int mSD_sdcard_write_protect_check(void) {
    int drive = mCsd_nowdrive_get();
    int result = mSD_sdcard_init();
    if (result != 0) return result;
    result = mSD_sdcard_setup(drive);
    if (result != 0) return result;
    result = mSD_sdcard_mount(drive);
    if (result != 0) return result;
    JUTSDDrive::setCurrentDrive(drive);
    if (JUTSDDrive::setCurrentDirectory("//") != 0) return 0x29;
    if (JUTSDDrive::setCurrentDirectory("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU") != 0) {
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE");
        if (result != 0) return result;
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE/GAMECUBE");
        if (result != 0) {
            return result;
        }
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE/GAMECUBE/NINTENDO");
        if (result != 0) {
            return result;
        }
        result = mSD_sdcard_makeDirectory(drive, "PRIVATE/GAMECUBE/NINTENDO/DOUBUTU");
        if (result != 0) {
            return result;
        }
    }
    if (JUTSDDrive::setCurrentDirectory("//PRIVATE/GAMECUBE/NINTENDO/DOUBUTU") != 0) {
        mSD_unmout_and_terminate(drive);
        return 0x29;
    }
    result = (u16)mSD_sdcard_create_fileopen(drive, "dammy.tmp", 1);
    if (result != 0) {
        if (result == 0x33) result = 0x2A;
        return result;
    }
    S_sdfile00.close();
    result = mSD_sdcard_removeFile_common(drive, "dammy.tmp");
    if (result != 0) return result;
    result = mSD_sdcard_unmount(drive);
    if (result != 0) return result;
    result = mSD_sdcard_terminate(drive);
    if (result != 0) return result;
    return 0;
}

extern "C" void mSD_static_clear(void) {
    S_driveno_now = 0;
    S_tiffBufferSize = 0;
    S_CRV32 = 0;
}
