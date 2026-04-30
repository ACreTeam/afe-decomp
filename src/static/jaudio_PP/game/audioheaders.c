#include "jaudio_NES/audioheaders.h"

ArcHeader AudioseqHeaderStart ATTRIBUTE_ALIGN(1) = {
    353,                     /* entries */
    0,                       /* unk param */
    nullptr,                 /* data start pointer */
    0,                       /* copy */
    { 0, 0, 0, 0, 0, 0, 0 }, /* pad */
    /* entries */
    {
        {
            /* entry 0 */
            0x00000000, /* rom addr */
            0x00000420, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 1 */
            0x00000420, /* rom addr */
            0x00000400, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 2 */
            0x00000820, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 3 */
            0x00000E20, /* rom addr */
            0x00001720, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 4 */
            0x00002540, /* rom addr */
            0x00000900, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 5 */
            0x00002E40, /* rom addr */
            0x00000A80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 6 */
            0x000038C0, /* rom addr */
            0x00000480, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 7 */
            0x00003D40, /* rom addr */
            0x00000800, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 8 */
            0x00004540, /* rom addr */
            0x000007C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 9 */
            0x00004D00, /* rom addr */
            0x00000A00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 10 */
            0x00005700, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 11 */
            0x00005CC0, /* rom addr */
            0x00000460, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 12 */
            0x00006120, /* rom addr */
            0x00000820, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 13 */
            0x00006940, /* rom addr */
            0x00000860, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 14 */
            0x000071A0, /* rom addr */
            0x000007E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 15 */
            0x00007980, /* rom addr */
            0x00000660, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 16 */
            0x00007FE0, /* rom addr */
            0x00000680, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 17 */
            0x00008660, /* rom addr */
            0x00000A20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 18 */
            0x00009080, /* rom addr */
            0x00000A60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 19 */
            0x00009AE0, /* rom addr */
            0x00000C80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 20 */
            0x0000A760, /* rom addr */
            0x00000C80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 21 */
            0x0000B3E0, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 22 */
            0x0000BEE0, /* rom addr */
            0x00000760, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 23 */
            0x0000C640, /* rom addr */
            0x00000880, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 24 */
            0x0000CEC0, /* rom addr */
            0x000007A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 25 */
            0x0000D660, /* rom addr */
            0x00000740, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 26 */
            0x0000DDA0, /* rom addr */
            0x00000640, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 27 */
            0x0000E3E0, /* rom addr */
            0x00000AE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 28 */
            0x0000EEC0, /* rom addr */
            0x00000500, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 29 */
            0x0000F3C0, /* rom addr */
            0x00000EE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 30 */
            0x000102A0, /* rom addr */
            0x00000620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 31 */
            0x000108C0, /* rom addr */
            0x000005A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 32 */
            0x00010E60, /* rom addr */
            0x00000EE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 33 */
            0x00011D40, /* rom addr */
            0x00000660, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 34 */
            0x000123A0, /* rom addr */
            0x00000760, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 35 */
            0x00012B00, /* rom addr */
            0x00000A60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 36 */
            0x00013560, /* rom addr */
            0x00000880, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 37 */
            0x00013DE0, /* rom addr */
            0x000009E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 38 */
            0x000147C0, /* rom addr */
            0x00000780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 39 */
            0x00014F40, /* rom addr */
            0x00000300, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 40 */
            0x00015240, /* rom addr */
            0x00000860, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 41 */
            0x00015AA0, /* rom addr */
            0x00000EC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 42 */
            0x00016960, /* rom addr */
            0x00000500, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 43 */
            0x00016E60, /* rom addr */
            0x00000560, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 44 */
            0x000173C0, /* rom addr */
            0x00000900, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 45 */
            0x00017CC0, /* rom addr */
            0x00000D40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 46 */
            0x00018A00, /* rom addr */
            0x000007C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 47 */
            0x000191C0, /* rom addr */
            0x00000C60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 48 */
            0x00019E20, /* rom addr */
            0x00000620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 49 */
            0x0001A440, /* rom addr */
            0x000013C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 50 */
            0x0001B800, /* rom addr */
            0x000007A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 51 */
            0x0001BFA0, /* rom addr */
            0x00000B40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 52 */
            0x0001CAE0, /* rom addr */
            0x00000360, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 53 */
            0x0001CE40, /* rom addr */
            0x000002A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 54 */
            0x0001D0E0, /* rom addr */
            0x00000580, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 55 */
            0x0001D660, /* rom addr */
            0x00000100, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 56 */
            0x0001D760, /* rom addr */
            0x00000420, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 57 */
            0x0001DB80, /* rom addr */
            0x00001100, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 58 */
            0x0001EC80, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 59 */
            0x0001F280, /* rom addr */
            0x00000360, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 60 */
            0x0001F5E0, /* rom addr */
            0x00000AE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 61 */
            0x000200C0, /* rom addr */
            0x00000640, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 62 */
            0x00020700, /* rom addr */
            0x00000840, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 63 */
            0x00020F40, /* rom addr */
            0x00000CA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 64 */
            0x00021BE0, /* rom addr */
            0x00000DA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 65 */
            0x00022980, /* rom addr */
            0x00000F60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 66 */
            0x000238E0, /* rom addr */
            0x00002860, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 67 */
            0x00026140, /* rom addr */
            0x00000B20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 68 */
            0x00026C60, /* rom addr */
            0x00000740, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 69 */
            0x000273A0, /* rom addr */
            0x00000820, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 70 */
            0x00027BC0, /* rom addr */
            0x000004C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 71 */
            0x00028080, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 72 */
            0x00028640, /* rom addr */
            0x00000340, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 73 */
            0x00028980, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 74 */
            0x00028D60, /* rom addr */
            0x00000660, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 75 */
            0x000293C0, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 76 */
            0x00029980, /* rom addr */
            0x00000940, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 77 */
            0x0002A2C0, /* rom addr */
            0x00000740, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 78 */
            0x0000004D, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 79 */
            0x0000004D, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 80 */
            0x0000004D, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 81 */
            0x0002AA00, /* rom addr */
            0x000002C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 82 */
            0x0002ACC0, /* rom addr */
            0x00000160, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 83 */
            0x0002AE20, /* rom addr */
            0x00000300, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 84 */
            0x0002B120, /* rom addr */
            0x00000140, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 85 */
            0x0002B260, /* rom addr */
            0x00000780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 86 */
            0x0002B9E0, /* rom addr */
            0x00000520, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 87 */
            0x0002BF00, /* rom addr */
            0x00000040, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 88 */
            0x0002BF40, /* rom addr */
            0x00000500, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 89 */
            0x0002C440, /* rom addr */
            0x00000720, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 90 */
            0x0002CB60, /* rom addr */
            0x00000720, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 91 */
            0x0002D280, /* rom addr */
            0x00000500, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 92 */
            0x0002D780, /* rom addr */
            0x00000580, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 93 */
            0x0002DD00, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 94 */
            0x0002E240, /* rom addr */
            0x000005A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 95 */
            0x0002E7E0, /* rom addr */
            0x00000520, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 96 */
            0x0002ED00, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 97 */
            0x0002F300, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 98 */
            0x0002F840, /* rom addr */
            0x00000520, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 99 */
            0x0002FD60, /* rom addr */
            0x000005A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 100 */
            0x00030300, /* rom addr */
            0x00000560, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 101 */
            0x00030860, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 102 */
            0x00030E20, /* rom addr */
            0x00000500, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 103 */
            0x00031320, /* rom addr */
            0x00000520, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 104 */
            0x00031840, /* rom addr */
            0x00000580, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 105 */
            0x00031DC0, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 106 */
            0x00032300, /* rom addr */
            0x000004C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 107 */
            0x000327C0, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 108 */
            0x00032D00, /* rom addr */
            0x00000580, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 109 */
            0x00033280, /* rom addr */
            0x00000520, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 110 */
            0x000337A0, /* rom addr */
            0x00000520, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 111 */
            0x00033CC0, /* rom addr */
            0x000003A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 112 */
            0x00034060, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 113 */
            0x00034440, /* rom addr */
            0x000003C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 114 */
            0x00034800, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 115 */
            0x00034BE0, /* rom addr */
            0x000003A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 116 */
            0x00034F80, /* rom addr */
            0x000003A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 117 */
            0x00035320, /* rom addr */
            0x000003A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 118 */
            0x000356C0, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 119 */
            0x00035AA0, /* rom addr */
            0x000003C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 120 */
            0x00035E60, /* rom addr */
            0x000003C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 121 */
            0x00036220, /* rom addr */
            0x000012A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 122 */
            0x000374C0, /* rom addr */
            0x00001620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 123 */
            0x00038AE0, /* rom addr */
            0x00000560, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 124 */
            0x00039040, /* rom addr */
            0x00000580, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 125 */
            0x000395C0, /* rom addr */
            0x00000660, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 126 */
            0x00039C20, /* rom addr */
            0x000003A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 127 */
            0x00039FC0, /* rom addr */
            0x00000560, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 128 */
            0x0000007F, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 129 */
            0x0003A520, /* rom addr */
            0x00000740, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 130 */
            0x0003AC60, /* rom addr */
            0x00000E20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 131 */
            0x0003BA80, /* rom addr */
            0x00000420, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 132 */
            0x0003BEA0, /* rom addr */
            0x000004E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 133 */
            0x0000007D, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 134 */
            0x0003C380, /* rom addr */
            0x00000460, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 135 */
            0x0003C7E0, /* rom addr */
            0x00000200, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 136 */
            0x0003C9E0, /* rom addr */
            0x000001A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 137 */
            0x0003CB80, /* rom addr */
            0x00000680, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 138 */
            0x0003D200, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 139 */
            0x0003D5E0, /* rom addr */
            0x000003C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 140 */
            0x0003D9A0, /* rom addr */
            0x00000640, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 141 */
            0x0003DFE0, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 142 */
            0x0003E5E0, /* rom addr */
            0x00000B40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 143 */
            0x0003F120, /* rom addr */
            0x00000360, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 144 */
            0x0003F480, /* rom addr */
            0x00001C40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 145 */
            0x000410C0, /* rom addr */
            0x00000720, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 146 */
            0x000417E0, /* rom addr */
            0x00000F20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 147 */
            0x00042700, /* rom addr */
            0x00001140, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 148 */
            0x00043840, /* rom addr */
            0x000008A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 149 */
            0x000440E0, /* rom addr */
            0x000011E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 150 */
            0x000452C0, /* rom addr */
            0x00000C80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 151 */
            0x00045F40, /* rom addr */
            0x00001160, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 152 */
            0x000470A0, /* rom addr */
            0x00001A20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 153 */
            0x00048AC0, /* rom addr */
            0x00000C20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 154 */
            0x000496E0, /* rom addr */
            0x00000B80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 155 */
            0x0004A260, /* rom addr */
            0x00000D80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 156 */
            0x0004AFE0, /* rom addr */
            0x00000CA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 157 */
            0x0004BC80, /* rom addr */
            0x000012A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 158 */
            0x0004CF20, /* rom addr */
            0x00000D40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 159 */
            0x0004DC60, /* rom addr */
            0x000008C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 160 */
            0x0004E520, /* rom addr */
            0x00000CA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 161 */
            0x0004F1C0, /* rom addr */
            0x000013A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 162 */
            0x00050560, /* rom addr */
            0x000012C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 163 */
            0x00051820, /* rom addr */
            0x00000D80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 164 */
            0x000525A0, /* rom addr */
            0x000014E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 165 */
            0x00053A80, /* rom addr */
            0x000009E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 166 */
            0x00054460, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 167 */
            0x00054F60, /* rom addr */
            0x00000780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 168 */
            0x000556E0, /* rom addr */
            0x00000580, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 169 */
            0x00055C60, /* rom addr */
            0x00000080, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 170 */
            0x00055CE0, /* rom addr */
            0x00000080, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 171 */
            0x00055D60, /* rom addr */
            0x00000060, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 172 */
            0x00055DC0, /* rom addr */
            0x00000080, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 173 */
            0x00055E40, /* rom addr */
            0x00000060, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 174 */
            0x00055EA0, /* rom addr */
            0x000009A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 175 */
            0x00056840, /* rom addr */
            0x00000FC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 176 */
            0x00057800, /* rom addr */
            0x000009E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 177 */
            0x000581E0, /* rom addr */
            0x00000B80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 178 */
            0x00058D60, /* rom addr */
            0x000012C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 179 */
            0x0005A020, /* rom addr */
            0x00001420, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 180 */
            0x0005B440, /* rom addr */
            0x000007E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 181 */
            0x0005BC20, /* rom addr */
            0x000007C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 182 */
            0x0005C3E0, /* rom addr */
            0x00000880, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 183 */
            0x0005CC60, /* rom addr */
            0x000014A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 184 */
            0x0005E100, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 185 */
            0x0005EC00, /* rom addr */
            0x00001200, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 186 */
            0x0005FE00, /* rom addr */
            0x00000B40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 187 */
            0x00060940, /* rom addr */
            0x000007A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 188 */
            0x000610E0, /* rom addr */
            0x00000820, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 189 */
            0x00061900, /* rom addr */
            0x00000C80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 190 */
            0x00062580, /* rom addr */
            0x00000BE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 191 */
            0x00063160, /* rom addr */
            0x00000C80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 192 */
            0x00063DE0, /* rom addr */
            0x00000840, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 193 */
            0x00064620, /* rom addr */
            0x00000CA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 194 */
            0x000652C0, /* rom addr */
            0x000016E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 195 */
            0x000669A0, /* rom addr */
            0x00000D80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 196 */
            0x00067720, /* rom addr */
            0x000009C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 197 */
            0x000680E0, /* rom addr */
            0x00000980, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 198 */
            0x00068A60, /* rom addr */
            0x00000E60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 199 */
            0x000698C0, /* rom addr */
            0x00000BE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 200 */
            0x0006A4A0, /* rom addr */
            0x00000D40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 201 */
            0x0006B1E0, /* rom addr */
            0x000010E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 202 */
            0x0006C2C0, /* rom addr */
            0x00000E20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 203 */
            0x0006D0E0, /* rom addr */
            0x00001100, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 204 */
            0x0006E1E0, /* rom addr */
            0x00001700, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 205 */
            0x0006F8E0, /* rom addr */
            0x000009C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 206 */
            0x000702A0, /* rom addr */
            0x00000C60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 207 */
            0x00070F00, /* rom addr */
            0x00000BC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 208 */
            0x00071AC0, /* rom addr */
            0x00001260, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 209 */
            0x00072D20, /* rom addr */
            0x00000880, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 210 */
            0x000735A0, /* rom addr */
            0x00001020, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 211 */
            0x000745C0, /* rom addr */
            0x00000640, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 212 */
            0x00074C00, /* rom addr */
            0x00000E20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 213 */
            0x00075A20, /* rom addr */
            0x00000760, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 214 */
            0x00076180, /* rom addr */
            0x00000A40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 215 */
            0x00076BC0, /* rom addr */
            0x000011E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 216 */
            0x00077DA0, /* rom addr */
            0x00000C20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 217 */
            0x000789C0, /* rom addr */
            0x00000AA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 218 */
            0x00079460, /* rom addr */
            0x00000BE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 219 */
            0x0007A040, /* rom addr */
            0x00002380, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 220 */
            0x0007C3C0, /* rom addr */
            0x00000680, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 221 */
            0x0007CA40, /* rom addr */
            0x00002180, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 222 */
            0x0007EBC0, /* rom addr */
            0x00000AE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 223 */
            0x0007F6A0, /* rom addr */
            0x00000FE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 224 */
            0x00080680, /* rom addr */
            0x000010C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 225 */
            0x00081740, /* rom addr */
            0x00001640, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 226 */
            0x00082D80, /* rom addr */
            0x000009E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 227 */
            0x00083760, /* rom addr */
            0x00000AC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 228 */
            0x00084220, /* rom addr */
            0x00000A40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 229 */
            0x00084C60, /* rom addr */
            0x000006E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 230 */
            0x00085340, /* rom addr */
            0x00000960, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 231 */
            0x00085CA0, /* rom addr */
            0x00000BA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 232 */
            0x00086840, /* rom addr */
            0x000018C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 233 */
            0x00088100, /* rom addr */
            0x000016C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 234 */
            0x000897C0, /* rom addr */
            0x00000E00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 235 */
            0x0008A5C0, /* rom addr */
            0x00000560, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 236 */
            0x0008AB20, /* rom addr */
            0x00001360, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 237 */
            0x0008BE80, /* rom addr */
            0x00000E80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 238 */
            0x0008CD00, /* rom addr */
            0x000010E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 239 */
            0x0008DDE0, /* rom addr */
            0x000016C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 240 */
            0x0008F4A0, /* rom addr */
            0x000008E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 241 */
            0x0008FD80, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 242 */
            0x00090380, /* rom addr */
            0x00000840, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 243 */
            0x00090BC0, /* rom addr */
            0x00000AA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 244 */
            0x00091660, /* rom addr */
            0x000004A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 245 */
            0x00091B00, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 246 */
            0x00092040, /* rom addr */
            0x00000460, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 247 */
            0x000924A0, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 248 */
            0x00092AA0, /* rom addr */
            0x00000C60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 249 */
            0x00093700, /* rom addr */
            0x00000BE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 250 */
            0x000942E0, /* rom addr */
            0x000006C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 251 */
            0x000949A0, /* rom addr */
            0x000004E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 252 */
            0x00094E80, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 253 */
            0x000953C0, /* rom addr */
            0x00000E60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 254 */
            0x00096220, /* rom addr */
            0x000007A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 255 */
            0x000969C0, /* rom addr */
            0x000008A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 256 */
            0x00097260, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 257 */
            0x00097820, /* rom addr */
            0x00000420, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 258 */
            0x00097C40, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 259 */
            0x00098240, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 260 */
            0x00098780, /* rom addr */
            0x00000760, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 261 */
            0x00098EE0, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 262 */
            0x000994A0, /* rom addr */
            0x00000620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 263 */
            0x00099AC0, /* rom addr */
            0x000008E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 264 */
            0x0009A3A0, /* rom addr */
            0x00000C00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 265 */
            0x0009AFA0, /* rom addr */
            0x00000980, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 266 */
            0x0009B920, /* rom addr */
            0x000004C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 267 */
            0x0009BDE0, /* rom addr */
            0x00000580, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 268 */
            0x0009C360, /* rom addr */
            0x000006C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 269 */
            0x0009CA20, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 270 */
            0x0009D020, /* rom addr */
            0x000005E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 271 */
            0x0009D600, /* rom addr */
            0x00000780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 272 */
            0x0009DD80, /* rom addr */
            0x00000780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 273 */
            0x0009E500, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 274 */
            0x0009EB00, /* rom addr */
            0x00000760, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 275 */
            0x0009F260, /* rom addr */
            0x00000720, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 276 */
            0x0009F980, /* rom addr */
            0x000010A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 277 */
            0x000A0A20, /* rom addr */
            0x000007E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 278 */
            0x000A1200, /* rom addr */
            0x00000A40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 279 */
            0x000A1C40, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 280 */
            0x000A2180, /* rom addr */
            0x00000CC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 281 */
            0x000A2E40, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 282 */
            0x000A3380, /* rom addr */
            0x00000720, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 283 */
            0x000A3AA0, /* rom addr */
            0x000003A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 284 */
            0x000A3E40, /* rom addr */
            0x00000640, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 285 */
            0x000A4480, /* rom addr */
            0x00000740, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 286 */
            0x000A4BC0, /* rom addr */
            0x00000700, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 287 */
            0x000A52C0, /* rom addr */
            0x00000500, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 288 */
            0x000A57C0, /* rom addr */
            0x00000660, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 289 */
            0x000A5E20, /* rom addr */
            0x00000DE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 290 */
            0x000A6C00, /* rom addr */
            0x000003C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 291 */
            0x000A6FC0, /* rom addr */
            0x000011E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 292 */
            0x000A81A0, /* rom addr */
            0x000006A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 293 */
            0x000A8840, /* rom addr */
            0x00000940, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 294 */
            0x000A9180, /* rom addr */
            0x000007C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 295 */
            0x000A9940, /* rom addr */
            0x00000CC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 296 */
            0x000AA600, /* rom addr */
            0x000007E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 297 */
            0x000AADE0, /* rom addr */
            0x00000640, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 298 */
            0x000AB420, /* rom addr */
            0x00000400, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 299 */
            0x000AB820, /* rom addr */
            0x000002A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 300 */
            0x000ABAC0, /* rom addr */
            0x000004E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 301 */
            0x000ABFA0, /* rom addr */
            0x00000900, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 302 */
            0x000AC8A0, /* rom addr */
            0x00000BE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 303 */
            0x000AD480, /* rom addr */
            0x00000E20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 304 */
            0x000AE2A0, /* rom addr */
            0x000005E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 305 */
            0x000AE880, /* rom addr */
            0x000004A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 306 */
            0x000AED20, /* rom addr */
            0x00000A60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 307 */
            0x000AF780, /* rom addr */
            0x00000620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 308 */
            0x000AFDA0, /* rom addr */
            0x00000C00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 309 */
            0x000B09A0, /* rom addr */
            0x00000D20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 310 */
            0x000B16C0, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 311 */
            0x000B1CC0, /* rom addr */
            0x00000380, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 312 */
            0x000B2040, /* rom addr */
            0x00000A20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 313 */
            0x000B2A60, /* rom addr */
            0x000005E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 314 */
            0x000B3040, /* rom addr */
            0x00000620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 315 */
            0x000B3660, /* rom addr */
            0x00000820, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 316 */
            0x000B3E80, /* rom addr */
            0x00001B20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 317 */
            0x000B59A0, /* rom addr */
            0x00000D00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 318 */
            0x000B66A0, /* rom addr */
            0x00001220, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 319 */
            0x000B78C0, /* rom addr */
            0x00002940, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 320 */
            0x000BA200, /* rom addr */
            0x000022E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 321 */
            0x000BC4E0, /* rom addr */
            0x000008E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 322 */
            0x000BCDC0, /* rom addr */
            0x00001280, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 323 */
            0x000BE040, /* rom addr */
            0x00001B40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 324 */
            0x000BFB80, /* rom addr */
            0x000028A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 325 */
            0x000C2420, /* rom addr */
            0x00001D20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 326 */
            0x000C4140, /* rom addr */
            0x00000660, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 327 */
            0x000C47A0, /* rom addr */
            0x00001480, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 328 */
            0x000C5C20, /* rom addr */
            0x00001120, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 329 */
            0x000C6D40, /* rom addr */
            0x000024E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 330 */
            0x000C9220, /* rom addr */
            0x00005180, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 331 */
            0x000CE3A0, /* rom addr */
            0x00004220, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 332 */
            0x000D25C0, /* rom addr */
            0x00003780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 333 */
            0x000D5D40, /* rom addr */
            0x00002C40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 334 */
            0x000D8980, /* rom addr */
            0x00002040, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 335 */
            0x000DA9C0, /* rom addr */
            0x00000A40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 336 */
            0x000DB400, /* rom addr */
            0x00000860, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 337 */
            0x000DBC60, /* rom addr */
            0x00000A40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 338 */
            0x000DC6A0, /* rom addr */
            0x00000860, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 339 */
            0x000DCF00, /* rom addr */
            0x00000B60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 340 */
            0x000DDA60, /* rom addr */
            0x000013C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 341 */
            0x000DEE20, /* rom addr */
            0x00001D20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 342 */
            0x000E0B40, /* rom addr */
            0x00001640, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 343 */
            0x000E2180, /* rom addr */
            0x00000EA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 344 */
            0x000E3020, /* rom addr */
            0x00000CE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 345 */
            0x000E3D00, /* rom addr */
            0x00000720, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 346 */
            0x000E4420, /* rom addr */
            0x000061A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 347 */
            0x000EA5C0, /* rom addr */
            0x00000620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 348 */
            0x000EABE0, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 349 */
            0x000EAFC0, /* rom addr */
            0x00000620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 350 */
            0x000EB5E0, /* rom addr */
            0x00005720, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 351 */
            0x000F0D00, /* rom addr */
            0x00000020, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 352 */
            0x000F0D20, /* rom addr */
            0x0001D580, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
    },
};

ArcHeader AudiobankHeaderStart = {
    176,                     /* entries */
    0,                       /* unk param */
    nullptr,                 /* data start pointer */
    0,                       /* copy */
    { 0, 0, 0, 0, 0, 0, 0 }, /* pad */
    /* entries */
    {
        {
            /* entry 0 */
            0x00000000, /* rom addr */
            0x00000180, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0100, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 1 */
            0x00000180, /* rom addr */
            0x000004C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0700, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 2 */
            0x00000640, /* rom addr */
            0x000004C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0700, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 3 */
            0x00000B00, /* rom addr */
            0x00000A60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 4 */
            0x00001560, /* rom addr */
            0x00000600, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 5 */
            0x00001B60, /* rom addr */
            0x00000CA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 6 */
            0x00002800, /* rom addr */
            0x00000100, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0200, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 7 */
            0x00002900, /* rom addr */
            0x00000220, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0400, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 8 */
            0x00002B20, /* rom addr */
            0x00000260, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0300, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 9 */
            0x00002D80, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0700, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 10 */
            0x00003340, /* rom addr */
            0x00000280, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 11 */
            0x000035C0, /* rom addr */
            0x00000840, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 12 */
            0x00003E00, /* rom addr */
            0x00000B40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A45, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 13 */
            0x00004940, /* rom addr */
            0x00000D00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 14 */
            0x00005640, /* rom addr */
            0x00000980, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 15 */
            0x00005FC0, /* rom addr */
            0x00000560, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0700, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 16 */
            0x00006520, /* rom addr */
            0x000004E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 17 */
            0x00006A00, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 18 */
            0x00006DE0, /* rom addr */
            0x00000A60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 19 */
            0x00007840, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0400, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 20 */
            0x00007C20, /* rom addr */
            0x00000300, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0300, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 21 */
            0x00007F20, /* rom addr */
            0x00000460, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0600, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 22 */
            0x00008380, /* rom addr */
            0x00000D80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 23 */
            0x00009100, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 24 */
            0x00009640, /* rom addr */
            0x00000760, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 25 */
            0x00009DA0, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 26 */
            0x0000A360, /* rom addr */
            0x00000940, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 27 */
            0x0000ACA0, /* rom addr */
            0x00000C00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A48, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 28 */
            0x0000B8A0, /* rom addr */
            0x000000E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0100, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 29 */
            0x0000B980, /* rom addr */
            0x00000440, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0600, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 30 */
            0x0000BDC0, /* rom addr */
            0x000009C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A48, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 31 */
            0x0000C780, /* rom addr */
            0x000007C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 32 */
            0x0000CF40, /* rom addr */
            0x00000440, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0400, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 33 */
            0x0000D380, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 34 */
            0x0000DE80, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 35 */
            0x0000E3C0, /* rom addr */
            0x00000B60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 36 */
            0x0000EF20, /* rom addr */
            0x00000760, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0B00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 37 */
            0x0000F680, /* rom addr */
            0x00000AC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 38 */
            0x00010140, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 39 */
            0x00010C40, /* rom addr */
            0x00000300, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0300, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 40 */
            0x00010F40, /* rom addr */
            0x000003C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0400, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 41 */
            0x00011300, /* rom addr */
            0x00000440, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 42 */
            0x00011740, /* rom addr */
            0x00000260, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0300, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 43 */
            0x000119A0, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 44 */
            0x00011D80, /* rom addr */
            0x000006A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0600, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 45 */
            0x00012420, /* rom addr */
            0x00000CA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0B43, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 46 */
            0x000130C0, /* rom addr */
            0x000007C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 47 */
            0x00013880, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0600, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 48 */
            0x00013E40, /* rom addr */
            0x00000240, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0200, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 49 */
            0x00014080, /* rom addr */
            0x000006C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0900, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 50 */
            0x00014740, /* rom addr */
            0x00000400, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 51 */
            0x00014B40, /* rom addr */
            0x00000A60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 52 */
            0x000155A0, /* rom addr */
            0x000007E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A48, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 53 */
            0x00015D80, /* rom addr */
            0x000009E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 54 */
            0x00016760, /* rom addr */
            0x00000480, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0900, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 55 */
            0x00016BE0, /* rom addr */
            0x00000280, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0200, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 56 */
            0x00016E60, /* rom addr */
            0x00000180, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0300, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 57 */
            0x00016FE0, /* rom addr */
            0x00000AE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0C41, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 58 */
            0x00017AC0, /* rom addr */
            0x00000AA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A3C, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 59 */
            0x00018560, /* rom addr */
            0x000004E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 60 */
            0x00018A40, /* rom addr */
            0x000004C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0C00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 61 */
            0x00018F00, /* rom addr */
            0x000003C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 62 */
            0x000192C0, /* rom addr */
            0x000003A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 63 */
            0x00019660, /* rom addr */
            0x00000AC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A3B, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 64 */
            0x0001A120, /* rom addr */
            0x00000780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0E00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 65 */
            0x0001A8A0, /* rom addr */
            0x00000680, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 66 */
            0x0001AF20, /* rom addr */
            0x00000AE0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A37, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 67 */
            0x0001BA00, /* rom addr */
            0x00000A20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0F3B, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 68 */
            0x0001C420, /* rom addr */
            0x000012E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1040, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 69 */
            0x0001D700, /* rom addr */
            0x00000B40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A3B, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 70 */
            0x0001E240, /* rom addr */
            0x00000A20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 71 */
            0x0001EC60, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 72 */
            0x0001F760, /* rom addr */
            0x000009A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 73 */
            0x00020100, /* rom addr */
            0x00000420, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 74 */
            0x00020520, /* rom addr */
            0x00000BA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 75 */
            0x000210C0, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 76 */
            0x00021BC0, /* rom addr */
            0x00000F80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 77 */
            0x00022B40, /* rom addr */
            0x00000620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 78 */
            0x0000004D, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 79 */
            0x0000004D, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 80 */
            0x0000004D, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 81 */
            0x00023160, /* rom addr */
            0x00000840, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 82 */
            0x000239A0, /* rom addr */
            0x00000820, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A48, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 83 */
            0x000241C0, /* rom addr */
            0x000003A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 84 */
            0x00024560, /* rom addr */
            0x000001C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0300, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 85 */
            0x00024720, /* rom addr */
            0x00000E00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1048, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 86 */
            0x00025520, /* rom addr */
            0x00000460, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 87 */
            0x00000054, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0300, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 88 */
            0x00025980, /* rom addr */
            0x000006C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 89 */
            0x00026040, /* rom addr */
            0x00000DC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0D00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 90 */
            0x00026E00, /* rom addr */
            0x00000BC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 91 */
            0x000279C0, /* rom addr */
            0x00000820, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0C00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 92 */
            0x000281E0, /* rom addr */
            0x00000DC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0B40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 93 */
            0x00028FA0, /* rom addr */
            0x000007C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0C00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 94 */
            0x00029760, /* rom addr */
            0x00000DA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0B40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 95 */
            0x0002A500, /* rom addr */
            0x00000840, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0C00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 96 */
            0x0002AD40, /* rom addr */
            0x00000AA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0E00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 97 */
            0x0002B7E0, /* rom addr */
            0x000008E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0C00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 98 */
            0x0002C0C0, /* rom addr */
            0x00000A60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0F00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 99 */
            0x0002CB20, /* rom addr */
            0x000008A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0D00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 100 */
            0x0002D3C0, /* rom addr */
            0x00000960, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0C00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 101 */
            0x0002DD20, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0D00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 102 */
            0x0002E820, /* rom addr */
            0x00000E00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 103 */
            0x0002F620, /* rom addr */
            0x000009A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0B00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 104 */
            0x0002FFC0, /* rom addr */
            0x000009E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0E00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 105 */
            0x000309A0, /* rom addr */
            0x00000C00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0D00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 106 */
            0x000315A0, /* rom addr */
            0x00000740, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 107 */
            0x00031CE0, /* rom addr */
            0x00000B40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0D00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 108 */
            0x00032820, /* rom addr */
            0x00000800, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0B00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 109 */
            0x00033020, /* rom addr */
            0x00000980, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0C00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 110 */
            0x000339A0, /* rom addr */
            0x00000A00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0900, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 111 */
            0x000343A0, /* rom addr */
            0x00000A20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0B00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 112 */
            0x00034DC0, /* rom addr */
            0x00000A80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0D00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 113 */
            0x00035840, /* rom addr */
            0x00000980, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0D00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 114 */
            0x000361C0, /* rom addr */
            0x000010C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1038, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 115 */
            0x00037280, /* rom addr */
            0x000005E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0600, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 116 */
            0x00037860, /* rom addr */
            0x000012E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x103E, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 117 */
            0x00038B40, /* rom addr */
            0x00000B20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A42, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 118 */
            0x00039660, /* rom addr */
            0x00000680, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 119 */
            0x00039CE0, /* rom addr */
            0x00000480, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0600, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 120 */
            0x0003A160, /* rom addr */
            0x000006E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0700, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 121 */
            0x0003A840, /* rom addr */
            0x000003C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 122 */
            0x0003AC00, /* rom addr */
            0x00000500, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 123 */
            0x0003B100, /* rom addr */
            0x00000520, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0600, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 124 */
            0x0003B620, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 125 */
            0x0003BBE0, /* rom addr */
            0x00000700, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 126 */
            0x0003C2E0, /* rom addr */
            0x000005E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0600, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 127 */
            0x0003C8C0, /* rom addr */
            0x00000340, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0500, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 128 */
            0x0003CC00, /* rom addr */
            0x000000C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0100, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 129 */
            0x0003CCC0, /* rom addr */
            0x00000280, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0400, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 130 */
            0x0003CF40, /* rom addr */
            0x00000280, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0300, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 131 */
            0x0003D1C0, /* rom addr */
            0x000009C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A42, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 132 */
            0x0003DB80, /* rom addr */
            0x000009E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A42, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 133 */
            0x0003E560, /* rom addr */
            0x00000BA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A42, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 134 */
            0x0003F100, /* rom addr */
            0x00000960, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A42, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 135 */
            0x0003FA60, /* rom addr */
            0x00000940, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0A42, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 136 */
            0x000403A0, /* rom addr */
            0x00000360, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x001A, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 137 */
            0x00040700, /* rom addr */
            0x00000360, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0019, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 138 */
            0x00040A60, /* rom addr */
            0x00000360, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x001A, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 139 */
            0x00040DC0, /* rom addr */
            0x00003620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x00FF, /* param0 */
            0x5000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 140 */
            0x000443E0, /* rom addr */
            0x00000B60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x01FF, /* param0 */
            0x0E00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 141 */
            0x00044F40, /* rom addr */
            0x00004500, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x02FF, /* param0 */
            0x6000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 142 */
            0x00049440, /* rom addr */
            0x000005E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0B00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 143 */
            0x00049A20, /* rom addr */
            0x00000860, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0E00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 144 */
            0x0004A280, /* rom addr */
            0x000005C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0E00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 145 */
            0x0004A840, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0F00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 146 */
            0x0004B340, /* rom addr */
            0x00000320, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0400, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 147 */
            0x0004B660, /* rom addr */
            0x00000A40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0F00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 148 */
            0x0004C0A0, /* rom addr */
            0x00000B40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0B40, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 149 */
            0x0004CBE0, /* rom addr */
            0x00000C60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0F48, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 150 */
            0x0004D840, /* rom addr */
            0x00000540, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0900, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 151 */
            0x0004DD80, /* rom addr */
            0x00000A60, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 152 */
            0x0004E7E0, /* rom addr */
            0x000006C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0D00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 153 */
            0x0004EEA0, /* rom addr */
            0x00000900, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0F00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 154 */
            0x0004F7A0, /* rom addr */
            0x000010C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1041, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 155 */
            0x00050860, /* rom addr */
            0x00001180, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1040, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 156 */
            0x0000009B, /* rom addr */
            0x00000000, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1040, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 157 */
            0x000519E0, /* rom addr */
            0x00001040, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1044, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 158 */
            0x00052A20, /* rom addr */
            0x00000B40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0E00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 159 */
            0x00053560, /* rom addr */
            0x000004C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0900, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 160 */
            0x00053A20, /* rom addr */
            0x00000EC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0E41, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 161 */
            0x000548E0, /* rom addr */
            0x000008E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0C00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 162 */
            0x000551C0, /* rom addr */
            0x00000A00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0F00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 163 */
            0x00055BC0, /* rom addr */
            0x00000920, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0F00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 164 */
            0x000564E0, /* rom addr */
            0x000010C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1040, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 165 */
            0x000575A0, /* rom addr */
            0x00000BC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 166 */
            0x00058160, /* rom addr */
            0x000010C0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x1040, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 167 */
            0x00059220, /* rom addr */
            0x00000B00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0F00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 168 */
            0x00059D20, /* rom addr */
            0x000003E0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0600, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 169 */
            0x0005A100, /* rom addr */
            0x00000620, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF, /* param0 */
            0x0800, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 170 */
            0x0005A720, /* rom addr */
            0x00005160, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x03FF, /* param0 */
            0x7E00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 171 */
            0x0005F880, /* rom addr */
            0x00004B80, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x03FF, /* param0 */
            0x7E00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 172 */
            0x00064400, /* rom addr */
            0x00002240, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x03FF, /* param0 */
            0x3B00, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 173 */
            0x00066640, /* rom addr */
            0x00002780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x03FF, /* param0 */
            0x4400, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 174 */
            0x00068DC0, /* rom addr */
            0x00002780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x03FF, /* param0 */
            0x4400, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 175 */
            0x0006B540, /* rom addr */
            0x00002780, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x03FF, /* param0 */
            0x4400, /* param1 */
            0x0000, /* param2 */
        },
    },
};

ArcHeader AudiowaveHeaderStart ATTRIBUTE_ALIGN(1) = {
    4,                       /* entries */
    0,                       /* unk param */
    nullptr,                 /* data start pointer */
    0,                       /* copy */
    { 0, 0, 0, 0, 0, 0, 0 }, /* pad */
    /* entries */
    {
        {
            /* entry 0 */
            0x00000000, /* rom addr */
            0x0003FD20, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 1 */
            0x0003FD20, /* rom addr */
            0x0000DF00, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 2 */
            0x0004DC20, /* rom addr */
            0x0006A080, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        {
            /* entry 3 */
            0x000B7CA0, /* rom addr */
            0x005D0FA0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
    },
};

ArcHeader AudiodataHeaderStart ATTRIBUTE_ALIGN(1) = {
    3,                       /* entries */
    0,                       /* unk param */
    nullptr,                 /* data start pointer */
    0,                       /* copy */
    { 0, 0, 0, 0, 0, 0, 0 }, /* pad */
    /* entries */
    {
        /* Audioseq */
        {
            /* entry 0 */
            0x00000000, /* rom addr */
            0x0010E2A0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        /* Audiobank */
        {
            /* entry 1 */
            0x0010E2A0, /* rom addr */
            0x0006DCC0, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
        /* Audiowave */
        {
            /* entry 2 */
            0x0017BF60, /* rom addr */
            0x00688C40, /* size */
            MEDIUM_CART, /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000, /* param0 */
            0x0000, /* param1 */
            0x0000, /* param2 */
        },
    },
};

// clang-format off
u8 AudiomapHeaderStart[] ATTRIBUTE_ALIGN(1) = {
    0x02, 0xC2, 0x02, 0xC4, 0x02, 0xC6, 0x02, 0xC8,
    0x02, 0xCA, 0x02, 0xCC, 0x02, 0xCE, 0x02, 0xD0,
    0x02, 0xD2, 0x02, 0xD4, 0x02, 0xD6, 0x02, 0xD8,
    0x02, 0xDA, 0x02, 0xDC, 0x02, 0xDE, 0x02, 0xE0,
    0x02, 0xE2, 0x02, 0xE4, 0x02, 0xE6, 0x02, 0xE8,
    0x02, 0xEA, 0x02, 0xEC, 0x02, 0xEE, 0x02, 0xF0,
    0x02, 0xF2, 0x02, 0xF4, 0x02, 0xF6, 0x02, 0xF8,
    0x02, 0xFA, 0x02, 0xFC, 0x02, 0xFE, 0x03, 0x00,
    0x03, 0x02, 0x03, 0x04, 0x03, 0x06, 0x03, 0x08,
    0x03, 0x0A, 0x03, 0x0C, 0x03, 0x0E, 0x03, 0x10,
    0x03, 0x12, 0x03, 0x14, 0x03, 0x16, 0x03, 0x18,
    0x03, 0x1A, 0x03, 0x1C, 0x03, 0x1E, 0x03, 0x20,
    0x03, 0x22, 0x03, 0x24, 0x03, 0x26, 0x03, 0x28,
    0x03, 0x2A, 0x03, 0x2C, 0x03, 0x2E, 0x03, 0x30,
    0x03, 0x32, 0x03, 0x34, 0x03, 0x36, 0x03, 0x38,
    0x03, 0x3A, 0x03, 0x3C, 0x03, 0x3E, 0x03, 0x40,
    0x03, 0x42, 0x03, 0x44, 0x03, 0x46, 0x03, 0x48,
    0x03, 0x4A, 0x03, 0x4C, 0x03, 0x4E, 0x03, 0x50,
    0x03, 0x52, 0x03, 0x54, 0x03, 0x56, 0x03, 0x58,
    0x03, 0x5A, 0x03, 0x5C, 0x03, 0x5E, 0x03, 0x60,
    0x03, 0x62, 0x03, 0x64, 0x03, 0x66, 0x03, 0x68,
    0x03, 0x6A, 0x03, 0x6C, 0x03, 0x6E, 0x03, 0x70,
    0x03, 0x72, 0x03, 0x74, 0x03, 0x76, 0x03, 0x78,
    0x03, 0x7A, 0x03, 0x7C, 0x03, 0x7E, 0x03, 0x80,
    0x03, 0x82, 0x03, 0x84, 0x03, 0x86, 0x03, 0x88,
    0x03, 0x8A, 0x03, 0x8C, 0x03, 0x8E, 0x03, 0x90,
    0x03, 0x92, 0x03, 0x94, 0x03, 0x96, 0x03, 0x98,
    0x03, 0x9A, 0x03, 0x9C, 0x03, 0x9E, 0x03, 0xA0,
    0x03, 0xA2, 0x03, 0xA4, 0x03, 0xA6, 0x03, 0xA8,
    0x03, 0xAA, 0x03, 0xAC, 0x03, 0xAE, 0x03, 0xB0,
    0x03, 0xB2, 0x03, 0xB4, 0x03, 0xB6, 0x03, 0xB8,
    0x03, 0xBA, 0x03, 0xBC, 0x03, 0xBE, 0x03, 0xC0,
    0x03, 0xC2, 0x03, 0xC4, 0x03, 0xC6, 0x03, 0xC8,
    0x03, 0xCA, 0x03, 0xCC, 0x03, 0xCE, 0x03, 0xD0,
    0x03, 0xD2, 0x03, 0xD4, 0x03, 0xD6, 0x03, 0xD8,
    0x03, 0xDA, 0x03, 0xDC, 0x03, 0xDE, 0x03, 0xE0,
    0x03, 0xE2, 0x03, 0xE4, 0x03, 0xE6, 0x03, 0xE8,
    0x03, 0xEA, 0x03, 0xEC, 0x03, 0xEE, 0x03, 0xF0,
    0x03, 0xF2, 0x03, 0xF4, 0x03, 0xF6, 0x03, 0xF8,
    0x03, 0xFA, 0x03, 0xFC, 0x03, 0xFE, 0x04, 0x00,
    0x04, 0x02, 0x04, 0x04, 0x04, 0x06, 0x04, 0x08,
    0x04, 0x0A, 0x04, 0x0C, 0x04, 0x0E, 0x04, 0x10,
    0x04, 0x12, 0x04, 0x14, 0x04, 0x16, 0x04, 0x18,
    0x04, 0x1A, 0x04, 0x1C, 0x04, 0x1E, 0x04, 0x20,
    0x04, 0x22, 0x04, 0x24, 0x04, 0x26, 0x04, 0x28,
    0x04, 0x2A, 0x04, 0x2C, 0x04, 0x2E, 0x04, 0x30,
    0x04, 0x32, 0x04, 0x34, 0x04, 0x36, 0x04, 0x38,
    0x04, 0x3A, 0x04, 0x3C, 0x04, 0x3E, 0x04, 0x40,
    0x04, 0x42, 0x04, 0x44, 0x04, 0x46, 0x04, 0x48,
    0x04, 0x4A, 0x04, 0x4C, 0x04, 0x4E, 0x04, 0x50,
    0x04, 0x52, 0x04, 0x54, 0x04, 0x56, 0x04, 0x58,
    0x04, 0x5A, 0x04, 0x5C, 0x04, 0x5E, 0x04, 0x60,
    0x04, 0x62, 0x04, 0x64, 0x04, 0x66, 0x04, 0x68,
    0x04, 0x6A, 0x04, 0x6C, 0x04, 0x6E, 0x04, 0x70,
    0x04, 0x72, 0x04, 0x74, 0x04, 0x76, 0x04, 0x78,
    0x04, 0x7A, 0x04, 0x7C, 0x04, 0x7E, 0x04, 0x80,
    0x04, 0x82, 0x04, 0x84, 0x04, 0x86, 0x04, 0x88,
    0x04, 0x8A, 0x04, 0x8C, 0x04, 0x8E, 0x04, 0x90,
    0x04, 0x92, 0x04, 0x94, 0x04, 0x96, 0x04, 0x98,
    0x04, 0x9A, 0x04, 0x9C, 0x04, 0x9E, 0x04, 0xA0,
    0x04, 0xA2, 0x04, 0xA4, 0x04, 0xA6, 0x04, 0xA8,
    0x04, 0xAA, 0x04, 0xAC, 0x04, 0xAE, 0x04, 0xB0,
    0x04, 0xB2, 0x04, 0xB4, 0x04, 0xB6, 0x04, 0xB8,
    0x04, 0xBA, 0x04, 0xBC, 0x04, 0xBE, 0x04, 0xC0,
    0x04, 0xC2, 0x04, 0xC4, 0x04, 0xC6, 0x04, 0xC8,
    0x04, 0xCA, 0x04, 0xCC, 0x04, 0xCE, 0x04, 0xD0,
    0x04, 0xD2, 0x04, 0xD4, 0x04, 0xD6, 0x04, 0xD8,
    0x04, 0xDA, 0x04, 0xDC, 0x04, 0xDE, 0x04, 0xE0,
    0x04, 0xE2, 0x04, 0xE4, 0x04, 0xE6, 0x04, 0xE8,
    0x04, 0xEA, 0x04, 0xEC, 0x04, 0xEE, 0x04, 0xF0,
    0x04, 0xF2, 0x04, 0xF4, 0x04, 0xF6, 0x04, 0xF8,
    0x04, 0xFA, 0x04, 0xFC, 0x04, 0xFE, 0x05, 0x00,
    0x05, 0x02, 0x05, 0x04, 0x05, 0x06, 0x05, 0x08,
    0x05, 0x0A, 0x05, 0x0C, 0x05, 0x0E, 0x05, 0x10,
    0x05, 0x12, 0x05, 0x14, 0x05, 0x16, 0x05, 0x18,
    0x05, 0x1A, 0x05, 0x1C, 0x05, 0x1E, 0x05, 0x20,
    0x05, 0x22, 0x05, 0x24, 0x05, 0x26, 0x05, 0x28,
    0x05, 0x2A, 0x05, 0x2C, 0x05, 0x2E, 0x05, 0x30,
    0x05, 0x32, 0x05, 0x34, 0x05, 0x36, 0x05, 0x38,
    0x05, 0x3A, 0x05, 0x3C, 0x05, 0x3E, 0x05, 0x40,
    0x05, 0x42, 0x05, 0x44, 0x05, 0x46, 0x05, 0x48,
    0x05, 0x4A, 0x05, 0x4C, 0x05, 0x4E, 0x05, 0x50,
    0x05, 0x52, 0x05, 0x54, 0x05, 0x56, 0x05, 0x58,
    0x05, 0x5A, 0x05, 0x5C, 0x05, 0x5E, 0x05, 0x60,
    0x05, 0x62, 0x05, 0x64, 0x05, 0x66, 0x05, 0x68,
    0x05, 0x6A, 0x05, 0x6C, 0x05, 0x6E, 0x05, 0x70,
    0x05, 0x72, 0x05, 0x74, 0x05, 0x76, 0x05, 0x7B,
    0x05, 0x7D, 0x05, 0x7F, 0x05, 0x81, 0x05, 0x84,
    0x05, 0x86, 0x01, 0x00, 0x01, 0x01, 0x01, 0x02,
    0x01, 0x03, 0x01, 0x04, 0x01, 0x05, 0x01, 0x06,
    0x01, 0x07, 0x01, 0x08, 0x01, 0x09, 0x01, 0x0A,
    0x01, 0x0B, 0x01, 0x0C, 0x01, 0x0D, 0x01, 0x0E,
    0x01, 0x0F, 0x01, 0x10, 0x01, 0x11, 0x01, 0x12,
    0x01, 0x13, 0x01, 0x14, 0x01, 0x15, 0x01, 0x16,
    0x01, 0x17, 0x01, 0x18, 0x01, 0x19, 0x01, 0x1A,
    0x01, 0x1B, 0x01, 0x1C, 0x01, 0x1D, 0x01, 0x1E,
    0x01, 0x1F, 0x01, 0x20, 0x01, 0x21, 0x01, 0x22,
    0x01, 0x23, 0x01, 0x24, 0x01, 0x25, 0x01, 0x26,
    0x01, 0x27, 0x01, 0x28, 0x01, 0x29, 0x01, 0x2A,
    0x01, 0x2B, 0x01, 0x2C, 0x01, 0x2D, 0x01, 0x2E,
    0x01, 0x2F, 0x01, 0x30, 0x01, 0x31, 0x01, 0x32,
    0x01, 0x33, 0x01, 0x34, 0x01, 0x35, 0x01, 0x36,
    0x01, 0x37, 0x01, 0x38, 0x01, 0x39, 0x01, 0x3D,
    0x01, 0x43, 0x01, 0x3B, 0x01, 0x3C, 0x01, 0x3A,
    0x01, 0x45, 0x01, 0x3F, 0x01, 0x41, 0x01, 0x44,
    0x01, 0x40, 0x01, 0x3E, 0x01, 0x42, 0x01, 0x46,
    0x01, 0x47, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4A,
    0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4D, 0x01, 0x4D,
    0x01, 0x4D, 0x01, 0x4D, 0x01, 0x51, 0x01, 0x52,
    0x01, 0x53, 0x01, 0x54, 0x01, 0x55, 0x01, 0x56,
    0x01, 0x57, 0x01, 0x58, 0x01, 0x59, 0x01, 0x59,
    0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A,
    0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A,
    0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A,
    0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A,
    0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A,
    0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A,
    0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A, 0x01, 0x5A,
    0x01, 0x5A, 0x01, 0x5A, 0x01, 0x74, 0x01, 0x76,
    0x01, 0x77, 0x01, 0x78, 0x01, 0x79, 0x01, 0x7A,
    0x01, 0x7B, 0x01, 0x7B, 0x01, 0x7C, 0x01, 0x7D,
    0x01, 0x75, 0x01, 0x7E, 0x01, 0x79, 0x01, 0x7F,
    0x01, 0x80, 0x01, 0x81, 0x01, 0x82, 0x01, 0x83,
    0x01, 0x83, 0x01, 0x84, 0x01, 0x85, 0x01, 0x86,
    0x01, 0x87, 0x01, 0x66, 0x01, 0x5F, 0x01, 0x68,
    0x01, 0x6C, 0x01, 0x6A, 0x01, 0x6E, 0x01, 0x6F,
    0x01, 0x60, 0x01, 0x6D, 0x01, 0x5D, 0x01, 0x71,
    0x01, 0x65, 0x01, 0x70, 0x01, 0x6B, 0x01, 0x5C,
    0x01, 0x5E, 0x01, 0x64, 0x01, 0x62, 0x01, 0x72,
    0x01, 0x69, 0x01, 0x63, 0x01, 0x67, 0x01, 0x61,
    0x01, 0x5B, 0x01, 0x73, 0x01, 0x88, 0x01, 0x88,
    0x01, 0x89, 0x01, 0x89, 0x01, 0x8A, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C,
    0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8C, 0x01, 0x8E,
    0x01, 0x8F, 0x01, 0x90, 0x01, 0x91, 0x01, 0x92,
    0x01, 0x93, 0x01, 0x94, 0x01, 0x95, 0x01, 0x96,
    0x01, 0x97, 0x01, 0x98, 0x01, 0x99, 0x01, 0x9A,
    0x01, 0x9B, 0x01, 0x9C, 0x01, 0x9D, 0x01, 0x9E,
    0x01, 0x9F, 0x01, 0xA0, 0x01, 0xA1, 0x01, 0xA2,
    0x01, 0xA3, 0x01, 0xA4, 0x01, 0xA5, 0x01, 0xA6,
    0x01, 0xA7, 0x01, 0xA8, 0x01, 0xA9, 0x04, 0x8D,
    0xAC, 0xAB, 0xAA, 0x01, 0xAD, 0x01, 0xAE, 0x01,
    0xAF, 0x02, 0x8D, 0x8B, 0x01, 0xAA, 0x01, 0x8D,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// clang-format on
