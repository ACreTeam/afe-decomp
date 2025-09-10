#ifndef FSFORM_H
#define FSFORM_H

#include "types.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MODE_UNK_1 1
#define MODE_FAT12 2

#define PTR_BOOT_SECTOR_ENTRY(pDrvCtl, index) ((FSPartitionBootSector*)((u32)pDrvCtl->ctrl_p.unk_20BA4 + index))
#define PBS_COUNT 32

#define PTR_ROOT_DIR_ENTRY(pDrvCtl, index) ((FSDirEntry*)((u32)pDrvCtl->ctrl_p.unk_20BA4 + index))
#define FAT_FLAG_DELETED 0xE5
#define FAT_ATTR_READ_ONLY 0x01
#define FAT_ATTR_HIDDEN 0x02
#define FAT_ATTR_SYSTEM 0x04
#define FAT_ATTR_VOLUME_ID 0x08
#define FAT_ATTR_DIRECTORY 0x10
#define FAT_ATTR_ARCHIVE 0x20
#define FAT_ATTR_LFN 0x0F // Long File Name
#define CHECK_ATTR(pDirEntry, value) ((((pDirEntry)->DIR_Attr) & 0x3F) == value)

typedef union u8_u16 {
    u8 data_u8[2];
    u16 data_u16;
} u8_u16;

typedef union u8_u32 {
    u8 data_u8[4];
    u32 data_u32;
} u8_u32;

#pragma pack(push, 1)

typedef struct FSPartitionBootSector16 {
    // Common Boot Sector Fields
    /* 0x000 */ u8 BS_jmpBoot[3];   // Jump instruction to boot code
    /* 0x003 */ char BS_OEMName[8]; // OEM Name Identifier

    // BIOS Parameter Block (BPB) - DOS 2.0
    /* 0x00B */ u8_u16 BPB_BytsPerSec; // Bytes per sector (512, 1024, 2048, 4096)
    /* 0x00D */ u8 BPB_SecPerClus;     // Sectors per cluster (must be a power of 2)
    /* 0x00E */ u8_u16 BPB_RsvdSecCnt; // Number of reserved sectors
    /* 0x010 */ u8 BPB_NumFATs;        // Number of FATs (usually 2)
    /* 0x011 */ u8_u16 BPB_RootEntCnt; // Max number of root directory entries (FAT16)
    /* 0x013 */ u8_u16 BPB_TotSec16;   // Total sectors (16-bit) for small partitions
    /* 0x015 */ u8 BPB_Media;          // Media type (0xF8 for hard disk)
    /* 0x016 */ u8_u16 BPB_FATSz16;    // Sectors per FAT (16-bit)

    // BPB - DOS 3.31
    /* 0x018 */ u8_u16 BPB_SecPerTrk; // Sectors per track (for INT 13h)
    /* 0x01A */ u8_u16 BPB_NumHeads;  // Number of heads (for INT 13h)
    /* 0x01C */ u8_u32 BPB_HiddSec;   // Count of hidden sectors
    /* 0x020 */ u8_u32 BPB_TotSec32;  // Total sectors (32-bit) for large partitions

    // Extended BIOS Parameter Block (EBPB)
    /* 0x024 */ u8 BS_DrvNum;          // Drive number (0x80 for hard disk)
    /* 0x025 */ u8 BS_Reserved1;       // Reserved (used by Windows NT)
    /* 0x026 */ u8 BS_BootSig;         // Extended boot signature (0x29)
    /* 0x027 */ u8_u32 BS_VolID;       // Volume serial number
    /* 0x02B */ char BS_VolLab[11];    // Volume label
    /* 0x036 */ char BS_FilSysType[8]; // File system type ("FAT16   ")

    // Remainder of the sector
    /* 0x03E */ u8 BS_BootCode[448]; // Bootloader code
    /* 0x1FE */ u8_u16 BS_BootSign;  // Boot signature (0xAA55)
} FSPartitionBootSector16;           // size = 0x200

typedef struct FSPartitionBootSector32 {
    // Common Boot Sector Fields
    /* 0x000 */ u8 BS_jmpBoot[3];   // Jump instruction to boot code
    /* 0x003 */ char BS_OEMName[8]; // OEM Name Identifier

    // BIOS Parameter Block (BPB)
    /* 0x00B */ u8_u16 BPB_BytsPerSec; // Bytes per sector
    /* 0x00D */ u8 BPB_SecPerClus;     // Sectors per cluster
    /* 0x00E */ u8_u16 BPB_RsvdSecCnt; // Number of reserved sectors
    /* 0x010 */ u8 BPB_NumFATs;        // Number of FATs
    /* 0x011 */ u8_u16 BPB_RootEntCnt; // (Must be 0 for FAT32)
    /* 0x013 */ u8_u16 BPB_TotSec16;   // (Must be 0 for FAT32)
    /* 0x015 */ u8 BPB_Media;          // Media type
    /* 0x016 */ u8_u16 BPB_FATSz16;    // (Must be 0 for FAT32)
    /* 0x018 */ u8_u16 BPB_SecPerTrk;  // Sectors per track
    /* 0x01A */ u8_u16 BPB_NumHeads;   // Number of heads
    /* 0x01C */ u8_u32 BPB_HiddSec;    // Count of hidden sectors
    /* 0x020 */ u8_u32 BPB_TotSec32;   // Total sectors (32-bit)

    // Extended BIOS Parameter Block (EBPB) for FAT32
    /* 0x024 */ u8_u32 BPB_FATSz32;    // Sectors per FAT (32-bit)
    /* 0x028 */ u8_u16 BPB_ExtFlags;   // Extended flags
    /* 0x02A */ u8_u16 BPB_FSVer;      // Filesystem version
    /* 0x02C */ u8_u32 BPB_RootClus;   // First cluster of root directory
    /* 0x030 */ u8_u16 BPB_FSInfo;     // Sector number of FSINFO structure
    /* 0x032 */ u8_u16 BPB_BkBootSec;  // Sector number of backup boot sector
    /* 0x034 */ u8 BPB_Reserved[12];   // Reserved
    /* 0x040 */ u8 BS_DrvNum;          // Drive number
    /* 0x041 */ u8 BS_Reserved1;       // Reserved
    /* 0x042 */ u8 BS_BootSig;         // Extended boot signature (0x29)
    /* 0x043 */ u8_u32 BS_VolID;       // Volume serial number
    /* 0x047 */ char BS_VolLab[11];    // Volume label
    /* 0x052 */ char BS_FilSysType[8]; // File system type ("FAT32   ")

    // Remainder of the sector
    /* 0x05A */ u8 BS_BootCode[420]; // Bootloader code
    /* 0x1FE */ u8_u16 BS_BootSign;  // Boot signature (0xAA55)
} FSPartitionBootSector32;           // size = 0x200

typedef struct FSDirEntry {
    /* 0x00 */ u8 DIR_Name[8 + 3];    // File name (8) and extension (3)
    /* 0x0B */ u8 DIR_Attr;           // File attributes (read-only, hidden, etc.)
    /* 0x0C */ u8 DIR_NTRes;          // Reserved for Windows NT
    /* 0x0D */ u8 DIR_CrtTimeTenth;   // Creation time in tenths of a second
    /* 0x0E */ u8_u16 DIR_CrtTime;    // Creation time
    /* 0x10 */ u8_u16 DIR_CrtDate;    // Creation date
    /* 0x12 */ u8_u16 DIR_LstAccDate; // Last access date
    /* 0x14 */ u8_u16 DIR_FstClusHI;  // High 16 bits of first cluster (FAT32)
    /* 0x16 */ u8_u16 DIR_WrtTime;    // Last modification time
    /* 0x18 */ u8_u16 DIR_WrtDate;    // Last modification date
    /* 0x1A */ u8_u16 DIR_FstClusLO;  // Low 16 bits of first cluster
    /* 0x1C */ u8_u32 DIR_FileSize;   // File size in bytes
} FSDirEntry;                         // size = 0x20

#pragma pack(pop)

typedef union FSPartitionBootSector {
    FSPartitionBootSector16 FAT16; // also FAT12
    FSPartitionBootSector32 FAT32;
} FSPartitionBootSector;

extern u16 FS_Format(const char* param1, u16 param2, u16 param3);
extern u16 FS_Format_sub(const char* param1, u16 param2, u16 param3, u16 param4, u16 param5, u16 nChan);
extern u16 FS_get_area_information(u16 param1, u32* param2, u32* param3, u16 param4, u16 param6);
extern u16 FS_calc_parameter(u32* param1, u16 param2);
extern u16 FS_init_mbr(u32 param1, s32* param2, u16 param3, u16 nChan);
extern u16 FS_init_pbs(char* param1, u32 param2, s32* param3, u16 param4, u16 param5, u16 nChan);
extern u16 FS_init_fat(s32* param1, u16 param2, u16 nChan);
extern u16 FS_init_rde(char* param1, s32* param2, u16 param3, u16 nChan);
extern u16 FS_format_write_sub(s32* param1, u16 param2, u16 nChan);

extern u32 FS_LCS;
extern u16 FS_TRACK_PER_SECTOR;
extern u16 FS_HEAD_NUM;
extern u32 FS_gl_partition_size;
extern u16 FS_gl_card_size;
extern u16 FS_format_fat_mode;
extern u16 FS_gl_bu;
extern u8 FS_FAT_MODE;
extern u16 FS_FAT_SC;
extern u32 FS_FAT_MAX;
extern u16 FS_FAT_SF;
extern u16 FS_FAT_SSA;
extern u16 FS_FAT_RSC;
extern u16 FS_FAT_MBR;
extern u16 FS_BUF_POS_FDC;
extern u16 FS_BUF_POS_FAT1;
extern u16 FS_BUF_POS_FAT2;
extern u16 FS_BUF_POS_RDE;

// indices to use when accessing the data without casting (unfortunately required...)

// PBS
#define OFFSET_BS_JMP_BOOT_INDEX_0 (offsetof(FSPartitionBootSector16, BS_jmpBoot) + 0)
#define OFFSET_BS_JMP_BOOT_INDEX_1 (offsetof(FSPartitionBootSector16, BS_jmpBoot) + 1)
#define OFFSET_BS_JMP_BOOT_INDEX_2 (offsetof(FSPartitionBootSector16, BS_jmpBoot) + 2)
#define OFFSET_BS_OEM_NAME (offsetof(FSPartitionBootSector16, BS_OEMName))
#define OFFSET_BPB_BYTES_PER_SEC_INDEX_0 (offsetof(FSPartitionBootSector16, BPB_BytsPerSec) + 0)
#define OFFSET_BPB_BYTES_PER_SEC_INDEX_1 (offsetof(FSPartitionBootSector16, BPB_BytsPerSec) + 1)
#define OFFSET_BPB_SEC_PER_CLUS (offsetof(FSPartitionBootSector16, BPB_SecPerClus))
#define OFFSET_BPB_RSVD_SEC_CNT_INDEX_0 (offsetof(FSPartitionBootSector16, BPB_RsvdSecCnt) + 0)
#define OFFSET_BPB_RSVD_SEC_CNT_INDEX_1 (offsetof(FSPartitionBootSector16, BPB_RsvdSecCnt) + 1)
#define OFFSET_BPB_NUM_FATS (offsetof(FSPartitionBootSector16, BPB_NumFATs))
#define OFFSET_BPB_ROOT_ENT_CNT_INDEX_0 (offsetof(FSPartitionBootSector16, BPB_RootEntCnt) + 0)
#define OFFSET_BPB_ROOT_ENT_CNT_INDEX_1 (offsetof(FSPartitionBootSector16, BPB_RootEntCnt) + 1)
#define OFFSET_BPB_TOT_SEC_16_INDEX_0 (offsetof(FSPartitionBootSector16, BPB_TotSec16) + 0)
#define OFFSET_BPB_TOT_SEC_16_INDEX_1 (offsetof(FSPartitionBootSector16, BPB_TotSec16) + 1)
#define OFFSET_BPB_MEDIA (offsetof(FSPartitionBootSector16, BPB_Media))
#define OFFSET_BPB_FAT_SZ_16_INDEX_0 (offsetof(FSPartitionBootSector16, BPB_FATSz16) + 0)
#define OFFSET_BPB_FAT_SZ_16_INDEX_1 (offsetof(FSPartitionBootSector16, BPB_FATSz16) + 1)
#define OFFSET_BPB_SEC_PER_TRK_INDEX_0 (offsetof(FSPartitionBootSector16, BPB_SecPerTrk) + 0)
#define OFFSET_BPB_SEC_PER_TRK_INDEX_1 (offsetof(FSPartitionBootSector16, BPB_SecPerTrk) + 1)
#define OFFSET_BPB_NUM_HEADS_INDEX_0 (offsetof(FSPartitionBootSector16, BPB_NumHeads) + 0)
#define OFFSET_BPB_NUM_HEADS_INDEX_1 (offsetof(FSPartitionBootSector16, BPB_NumHeads) + 1)
#define OFFSET_BPB_HIDD_SEC_INDEX_0 (offsetof(FSPartitionBootSector16, BPB_HiddSec) + 0)
#define OFFSET_BPB_HIDD_SEC_INDEX_1 (offsetof(FSPartitionBootSector16, BPB_HiddSec) + 1)
#define OFFSET_BPB_HIDD_SEC_INDEX_2 (offsetof(FSPartitionBootSector16, BPB_HiddSec) + 2)
#define OFFSET_BPB_HIDD_SEC_INDEX_3 (offsetof(FSPartitionBootSector16, BPB_HiddSec) + 3)
#define OFFSET_BPB_TOT_SEC_32_INDEX_0 (offsetof(FSPartitionBootSector16, BPB_TotSec32) + 0)
#define OFFSET_BPB_TOT_SEC_32_INDEX_1 (offsetof(FSPartitionBootSector16, BPB_TotSec32) + 1)
#define OFFSET_BPB_TOT_SEC_32_INDEX_2 (offsetof(FSPartitionBootSector16, BPB_TotSec32) + 2)
#define OFFSET_BPB_TOT_SEC_32_INDEX_3 (offsetof(FSPartitionBootSector16, BPB_TotSec32) + 3)
#define OFFSET_BS_DRV_NUM (offsetof(FSPartitionBootSector16, BS_DrvNum))
#define OFFSET_BS_RESERVED_1 (offsetof(FSPartitionBootSector16, BS_Reserved1))
#define OFFSET_BS_BOOT_SIG (offsetof(FSPartitionBootSector16, BS_BootSig))
#define OFFSET_BS_VOL_ID_INDEX_0 (offsetof(FSPartitionBootSector16, BS_VolID) + 0)
#define OFFSET_BS_VOL_ID_INDEX_1 (offsetof(FSPartitionBootSector16, BS_VolID) + 1)
#define OFFSET_BS_VOL_ID_INDEX_2 (offsetof(FSPartitionBootSector16, BS_VolID) + 2)
#define OFFSET_BS_VOL_ID_INDEX_3 (offsetof(FSPartitionBootSector16, BS_VolID) + 3)
#define OFFSET_BS_VOL_LAB (offsetof(FSPartitionBootSector16, BS_VolLab))
#define OFFSET_BS_FIL_SYS_TYPE (offsetof(FSPartitionBootSector16, BS_FilSysType))
#define OFFSET_BS_BOOT_CODE (offsetof(FSPartitionBootSector16, BS_BootCode))
#define OFFSET_BS_BOOT_SIGN_INDEX_0 (offsetof(FSPartitionBootSector16, BS_BootSign) + 0)
#define OFFSET_BS_BOOT_SIGN_INDEX_1 (offsetof(FSPartitionBootSector16, BS_BootSign) + 1)

// RDE
#define OFFSET_DIR_NAME (offsetof(FSDirEntry, DIR_Name))
#define OFFSET_DIR_ATTR (offsetof(FSDirEntry, DIR_Attr))
#define OFFSET_DIR_NT_RES (offsetof(FSDirEntry, DIR_NTRes))
#define OFFSET_DIR_CRT_TIME_TENTH (offsetof(FSDirEntry, DIR_CrtTimeTenth))
#define OFFSET_DIR_CRT_TIME (offsetof(FSDirEntry, DIR_CrtTime))
#define OFFSET_DIR_CRT_DATE (offsetof(FSDirEntry, DIR_CrtDate))
#define OFFSET_DIR_LST_ACC_DATE (offsetof(FSDirEntry, DIR_LstAccDate))
#define OFFSET_DIR_FST_CLUS_HI (offsetof(FSDirEntry, DIR_FstClusHI))
#define OFFSET_DIR_WRT_TIME (offsetof(FSDirEntry, DIR_WrtTime))
#define OFFSET_DIR_WRT_DATE (offsetof(FSDirEntry, DIR_WrtDate))
#define OFFSET_DIR_FST_CLUS_LO (offsetof(FSDirEntry, DIR_FstClusLO))
#define OFFSET_DIR_FILE_SIZE (offsetof(FSDirEntry, DIR_FileSize))

#ifdef __cplusplus
};
#endif

#endif
