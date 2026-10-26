#include <dolphin.h>
#include <dolphin/dvd.h>
#include <string.h>

#include "../src/static/GAEJ01_01/dolphin/dvd/__dvd.h"

static u32 strnlen(const char* str, u32 maxlen) {
    u32 i;

    for (i = 0; i < maxlen; i++) {
        if (*str++ == 0) {
            return i;
        }
    }

    return maxlen;
}

BOOL DVDCompareDiskID(DVDDiskID* id1, DVDDiskID* id2) {
    if (id1->gameName[0] != 0 && id2->gameName[0] != 0 && strncmp(id1->gameName, id2->gameName, 4) != 0) {
        return FALSE;
    }

    if (id1->company[0] == 0 || id2->company[0] == 0 || strncmp(id1->company, id2->company, 2) != 0) {
        return FALSE;
    }

    if (id1->diskNumber != 0xFF && id2->diskNumber != 0xFF && id1->diskNumber != id2->diskNumber) {
        return FALSE;
    }

    if (id1->gameVersion != 0xFF && id2->gameVersion != 0xFF && id1->gameVersion != id2->gameVersion) {
        return FALSE;
    }

    return TRUE;
}

DVDDiskID* DVDGenerateDiskID(DVDDiskID* id, const char* game, const char* company, u8 diskNum, u8 version) {
    memset(id, 0, sizeof(DVDDiskID));

    if (game != NULL) {
        strncpy(id->gameName, game, 4);
    }

    if (company != NULL) {
        strncpy(id->company, company, 2);
    }

    id->diskNumber = diskNum;
    id->gameVersion = version;
    return id;
}
