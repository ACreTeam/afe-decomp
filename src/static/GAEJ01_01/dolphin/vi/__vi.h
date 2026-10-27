#ifndef _DOLPHIN_VI_INTERNAL_H_
#define _DOLPHIN_VI_INTERNAL_H_

#include <dolphin/vi.h>

#define VI_3D  3
#define VI_GCA 6

#define VI_TVMODE_NTSC_3D  VI_TVMODE(VI_NTSC, VI_3D)
#define VI_TVMODE_GCA_INT  VI_TVMODE(VI_GCA, VI_INTERLACE)
#define VI_TVMODE_GCA_DS   VI_TVMODE(VI_GCA, VI_NON_INTERLACE)
#define VI_TVMODE_GCA_PROG VI_TVMODE(VI_GCA, VI_PROGRESSIVE)

typedef void (*VIPositionCallback)(s16 x, s16 y);

typedef struct VITimingInfo {
    u8 equ;           // _00
    u16 acv;          // _02
    u16 prbOdd;       // _04
    u16 prbEven;      // _06
    u16 psbOdd;       // _08
    u16 psbEven;      // _0A
    u8 bs1;           // _0C
    u8 bs2;           // _0D
    u8 bs3;           // _0E
    u8 bs4;           // _0F
    u16 be1;          // _10
    u16 be2;          // _12
    u16 be3;          // _14
    u16 be4;          // _16
    u16 numHalfLines; // _18
    u16 hlw;          // _1A
    u8 hsy;           // _1C
    u8 hcs;           // _1D
    u8 hce;           // _1E
    u8 hbe640;        // _1F
    u16 hbs640;       // _20
    u8 hbeCCIR656;    // _24
    u16 hbsCCIR656;   // _26
} VITimingInfo;

typedef struct VIPositionInfo {
    u16 dispPosX;         // _00
    u16 dispPosY;         // _02
    u16 dispSizeX;        // _04
    u16 dispSizeY;        // _06
    u16 adjDispPosX;      // _08
    u16 adjDispPosY;      // _0A
    u16 adjDispSizeY;     // _0C
    u16 adjPanPosY;       // _0E
    u16 adjPanSizeY;      // _10
    u16 fbSizeX;          // _12
    u16 fbSizeY;          // _14
    u16 panPosX;          // _16
    u16 panPosY;          // _18
    u16 panSizeX;         // _1A
    u16 panSizeY;         // _1C
    VIXFBMode xfbMode;    // _20
    u32 nonInter;         // _24
    u32 tv;               // _28
    u8 wordPerLine;       // _2C
    u8 std;               // _2D
    u8 wpl;               // _2E
    u32 bufAddr;          // _30
    u32 tfbb;             // _34
    u32 bfbb;             // _38
    u8 xof;               // _3C
    BOOL isBlack;         // _40
    BOOL is3D;            // _44
    u32 rbufAddr;         // _48
    u32 rtfbb;            // _4C
    u32 rbfbb;            // _50
    VITimingInfo* timing; // _54
} VIPositionInfo;

/* gpioexi.c */

void __VIInitI2C(void);
void __VISetSCL(int value);
int __VIGetSCL(void);
void __VISetSDA(int value);
int __VIGetSDA(void);

/* i2c.c */

int __VISendI2CData(u8 slaveAddr, u8* pData, int nBytes);

/* initphilips.c */

void __VIInitPhilips(void);

/* vi.c */

void __VIInit(VITVMode mode);
void __VISetAdjustingValues(s16 x, s16 y);
void __VIGetAdjustingValues(s16* x, s16* y);
void __VIGetCurrentPosition(s16* x, s16* y);
void __VIDisplayPositionToXY(u32 hcount, u32 vcount, s16* x, s16* y);

#endif
