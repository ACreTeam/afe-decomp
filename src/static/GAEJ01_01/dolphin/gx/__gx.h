#ifndef _DOLPHIN_GX_INTERNAL_H_
#define _DOLPHIN_GX_INTERNAL_H_

#include <dolphin/gx.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Bitfield helpers */

#define GX_BITFIELD(field, pos, size, value)       (__rlwimi((field), (value), 31 - (pos) - (size) + 1, (pos), (pos) + (size) - 1))
#define GX_BITFIELD_SET(field, pos, size, value)   ((field) = GX_BITFIELD(field, pos, size, value))
#define GX_BITFIELD_TRUNC(field, pos, size, value) (__rlwimi((field), (value), 0, (pos), (pos) + (size) - 1))
#define GX_BITGET(field, pos, size)                ((field) >> (31 - (pos) - (size) + 1) & ((1 << (size)) - 1))

#define GX_REG_MASK(st, end)          (((1 << ((end) - (st) + 1)) - 1) << 31 - (end))
#define GX_GET_REG(reg, st, end)      GX_BITGET((reg), (st), ((end) - (st) + 1))
#define GX_SET_REG(reg, x, st, end)   GX_BITFIELD_SET((reg), (st), ((end) - (st) + 1), (x))
#define GX_SET_TRUNC(reg, x, st, end) GX_BITFIELD_TRUNC((reg), (st), ((end) - (st) + 1), (x))

#define GX_LARGE_NUMBER 1.0e+18f

#define GX_MAX_TLUT     16
#define GX_MAX_BIGTLUT  4
#define GX_MAX_TLUT_ALL (GX_MAX_TLUT + GX_MAX_BIGTLUT)

#define GXCOLOR_AS_U32(color) (*((u32*)&(color)))

/* Write-gather FIFO */

#define GX_WRITE_U8(val)  (GXWGFifo.u8 = val)
#define GX_WRITE_U16(val) (GXWGFifo.u16 = val)
#define GX_WRITE_U32(val) (GXWGFifo.u32 = (u32)val)
#define GX_WRITE_F32(val) (GXWGFifo.f32 = (f32)val)

/* Internal object layouts */

typedef struct _GXFifoObjPriv {
    void* base;        // _00
    void* end;         // _04
    u32 size;          // _08
    u32 highWatermark; // _0C
    u32 lowWatermark;  // _10
    void* readPtr;     // _14
    void* writePtr;    // _18
    s32 rwDistance;    // _1C
    u8 _20[0x60];      // _20
} GXFifoObjPriv;

typedef struct __GXFifoObj {
    u8* base;
    u8* top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void* rdPtr;
    void* wrPtr;
    s32 count;
    u8 bind_cpu;
    u8 bind_gp;
} __GXFifoObj;

typedef struct _GXTexObjPriv {
    u32 mode0;       // _00
    u32 mode1;       // _04
    u32 image0;      // _08
    u32 image3;      // _0C
    void* userData;  // _10
    GXTexFmt format; // _14
    u32 tlutName;    // _18
    u16 loadCount;   // _1C
    u8 loadFormat;   // _1E
    u8 flags;        // _1F
} GXTexObjPriv;

typedef struct _GXTexRegionPriv {
    u32 unk0;      // _00
    u32 unk4;      // _04
    u32 unk8;      // _08
    u8 unkC;       // _0C
    u8 unkD;       // _0D
    u8 padding[2]; // _0E
} GXTexRegionPriv;

typedef struct _GXTlutObjPriv {
    u32 unk0;        // _00
    u32 unk4;        // _04
    u16 numEntries;  // _08
    u8 padding[0x2]; // _0A
} GXTlutObjPriv;

typedef struct _GXTlutRegionPriv {
    u32 unk0;              // _00
    GXTlutObjPriv tlutObj; // _04
} GXTlutRegionPriv;

typedef struct __GXLightObjPriv {
    u32 reserved[3]; // _00
    GXColor color;   // _0C
    f32 a[3];        // _10
    f32 k[3];        // _1C
    f32 lpos[3];     // _28
    f32 ldir[3];     // _34
} GXLightObjPriv;

/* Hardware registers */

// Flags for setting GXData dirtyState.
typedef enum _GXDirtyFlag {
    GX_DIRTY_SU_TEX   = (1 << 0), // 0x1
    GX_DIRTY_BP_MASK  = (1 << 1), // 0x2
    GX_DIRTY_GEN_MODE = (1 << 2), // 0x4
    GX_DIRTY_VCD      = (1 << 3), // 0x8
    GX_DIRTY_VAT      = (1 << 4), // 0x10
    // . . .
    GX_DIRTY_AMB_COLOR0  = (1 << 8),  // 0x100
    GX_DIRTY_AMB_COLOR1  = (1 << 9),  // 0x200
    GX_DIRTY_MAT_COLOR0  = (1 << 10), // 0x400
    GX_DIRTY_MAT_COLOR1  = (1 << 11), // 0x800
    GX_DIRTY_CHAN_COLOR0 = (1 << 12), // 0x1000
    GX_DIRTY_CHAN_COLOR1 = (1 << 13), // 0x2000
    GX_DIRTY_CHAN_ALPHA0 = (1 << 14), // 0x4000
    GX_DIRTY_CHAN_ALPHA1 = (1 << 15), // 0x8000
    GX_DIRTY_TEX0        = (1 << 16), // 0x10000
    GX_DIRTY_TEX1        = (1 << 17), // 0x20000
    GX_DIRTY_TEX2        = (1 << 18), // 0x40000
    GX_DIRTY_TEX3        = (1 << 19), // 0x80000
    GX_DIRTY_TEX4        = (1 << 20), // 0x100000
    GX_DIRTY_TEX5        = (1 << 21), // 0x200000
    GX_DIRTY_TEX6        = (1 << 22), // 0x400000
    GX_DIRTY_TEX7        = (1 << 23), // 0x800000
    GX_DIRTY_NUM_COLORS  = (1 << 24), // 0x1000000
    GX_DIRTY_NUM_TEX     = (1 << 25), // 0x2000000
    GX_DIRTY_MTX_IDX     = (1 << 26), // 0x4000000
    GX_DIRTY_PROJECTION  = (1 << 27), // 0x8000000
    GX_DIRTY_VIEWPORT    = (1 << 28), // 0x10000000

    GX_AMB_MAT_MASK = GX_DIRTY_AMB_COLOR0 | GX_DIRTY_AMB_COLOR1 | GX_DIRTY_MAT_COLOR0 | GX_DIRTY_MAT_COLOR1, // 0xF00

    GX_LIGHT_CHAN_MASK = GX_DIRTY_CHAN_COLOR0 | GX_DIRTY_CHAN_COLOR1 | GX_DIRTY_CHAN_ALPHA0 | GX_DIRTY_CHAN_ALPHA1
        | GX_DIRTY_NUM_COLORS, // 0x100F000

    GX_TEX_GEN_MASK = 0x2FF0000, // all GX_DIRTY_TEXs | GX_DIRTY_NUM_TEX
} GXDirtyFlag;

// Commands for interacting with the GXFifo pipe.
typedef enum _GXFifoCmd {
    GX_FIFO_CMD_NOOP = 0x00, // no operation

    GX_FIFO_CMD_LOAD_BP_REG = 0x61, // load blitting processor reg
    GX_FIFO_CMD_LOAD_CP_REG = 0x08, // load command processor reg
    GX_FIFO_CMD_LOAD_XF_REG = 0x10, // load transform unit reg

    GX_FIFO_CMD_LOAD_INDX_A = 0x20, // load index A
    GX_FIFO_CMD_LOAD_INDX_B = 0x28, // load index B
    GX_FIFO_CMD_LOAD_INDX_C = 0x30, // load index C
    GX_FIFO_CMD_LOAD_INDX_D = 0x38, // load index D

    GX_FIFO_CMD_CALL_DL   = 0x40, // call displaylist
    GX_FIFO_CMD_INVAL_VTX = 0x48, // invalid vertex

} GXFifoCmd;

// Texture register fields for XF (transform) unit.
typedef enum _GXXfTexReg {
    GX_XF_TEX_PROJ_ST  = 0, // (s,t) (2x4)
    GX_XF_TEX_PROJ_STQ = 1, // (s,t,q) (3x4)

    GX_XF_TEX_FORM_AB11 = 0, // (A, B, 1.0f, 1.0f), used for regular tex src
    GX_XF_TEX_FORM_ABC1 = 1, // (A, B, C, 1.0f), used for geometry/normal src
} GXXfTexReg;

// General texture commands.
typedef enum _GXXfTexGen {
    GX_XF_TG_REGULAR = 0, // Regular; transform incoming data.
    GX_XF_TG_BUMP    = 1, // Texgen bump mapping.
    GX_XF_TG_CLR0    = 2, // Color texgen for color 0 (s,t) = (r, g:b)
    GX_XF_TG_CLR1    = 3, // Color texgen for color 1 (s,t) = (r, g:b)
} GXXfTexGen;

// Transform memory types.
typedef enum _GXXfMem {
    GX_XF_MEM_POSMTX     = 0x000, // position coord matrix
    GX_XF_MEM_NRMMTX     = 0x400, // normal coord matrix
    GX_XF_MEM_DUALTEXMTX = 0x500, // dual texture matrix
    GX_XF_MEM_LIGHTOBJ   = 0x600, // light object
} GXXfMem;

// Blitting processor registers.
typedef enum _GXBPRegs {
    // gen mode
    GX_BP_REG_GENMODE = 0x0, // gen mode

    // display copy filters
    GX_BP_REG_DISPCOPYFILTER0 = 0x1, // display copy filter 0
    GX_BP_REG_DISPCOPYFILTER1 = 0x2, // display copy filter 1
    GX_BP_REG_DISPCOPYFILTER2 = 0x3, // display copy filter 2
    GX_BP_REG_DISPCOPYFILTER3 = 0x4, // display copy filter 3

    // indirect matrices
    GX_BP_REG_INDMTX0A = 0x6, // indirect matrix 0A
    GX_BP_REG_INDMTX0B = 0x7, // indirect matrix 0B
    GX_BP_REG_INDMTX0C = 0x8, // indirect matrix 0C
    GX_BP_REG_INDMTX1A = 0x9, // indirect matrix 1A
    GX_BP_REG_INDMTX1B = 0xA, // indirect matrix 1B
    GX_BP_REG_INDMTX1C = 0xB, // indirect matrix 1C
    GX_BP_REG_INDMTX2A = 0xC, // indirect matrix 2A
    GX_BP_REG_INDMTX2B = 0xD, // indirect matrix 2B
    GX_BP_REG_INDMTX2C = 0xE, // indirect matrix 2C
    GX_BP_REG_INDIMASK = 0xF, // indirect mask

    // indirect TEV stages
    GX_BP_REG_INDTEVSTAGE0  = 0x10, // indirect TEV stage 0
    GX_BP_REG_INDTEVSTAGE1  = 0x11, // indirect TEV stage 1
    GX_BP_REG_INDTEVSTAGE2  = 0x12, // indirect TEV stage 2
    GX_BP_REG_INDTEVSTAGE3  = 0x13, // indirect TEV stage 3
    GX_BP_REG_INDTEVSTAGE4  = 0x14, // indirect TEV stage 4
    GX_BP_REG_INDTEVSTAGE5  = 0x15, // indirect TEV stage 5
    GX_BP_REG_INDTEVSTAGE6  = 0x16, // indirect TEV stage 6
    GX_BP_REG_INDTEVSTAGE7  = 0x17, // indirect TEV stage 7
    GX_BP_REG_INDTEVSTAGE8  = 0x18, // indirect TEV stage 8
    GX_BP_REG_INDTEVSTAGE9  = 0x19, // indirect TEV stage 9
    GX_BP_REG_INDTEVSTAGE10 = 0x1A, // indirect TEV stage 10
    GX_BP_REG_INDTEVSTAGE11 = 0x1B, // indirect TEV stage 11
    GX_BP_REG_INDTEVSTAGE12 = 0x1C, // indirect TEV stage 12
    GX_BP_REG_INDTEVSTAGE13 = 0x1D, // indirect TEV stage 13
    GX_BP_REG_INDTEVSTAGE14 = 0x1E, // indirect TEV stage 14
    GX_BP_REG_INDTEVSTAGE15 = 0x1F, // indirect TEV stage 15

    // performance manips
    GX_BP_REG_SCISSORTL   = 0x20, // scissor top left
    GX_BP_REG_SCISSORBR   = 0x21, // scissor bottom right
    GX_BP_REG_LINEPTWIDTH = 0x22, // line point width
    GX_BP_REG_PERF0TRI    = 0x23, // performance 0 (triangle)
    GX_BP_REG_PERF0QUAD   = 0x24, // performance 0 (quad)

    // rasters
    GX_BP_REG_RAS1_SS0   = 0x25,
    GX_BP_REG_RAS1_SS1   = 0x26,
    GX_BP_REG_RAS1_IREF  = 0x27,
    GX_BP_REG_RAS1_TREF0 = 0x28,
    GX_BP_REG_RAS1_TREF1 = 0x29,
    GX_BP_REG_RAS1_TREF2 = 0x2A,
    GX_BP_REG_RAS1_TREF3 = 0x2B,
    GX_BP_REG_RAS1_TREF4 = 0x2C,
    GX_BP_REG_RAS1_TREF5 = 0x2D,
    GX_BP_REG_RAS1_TREF6 = 0x2E,
    GX_BP_REG_RAS1_TREF7 = 0x2F,

    // setup sizes
    GX_BP_REG_SU_SSIZE0 = 0x30,
    GX_BP_REG_SU_TSIZE0 = 0x31,
    GX_BP_REG_SU_SSIZE1 = 0x32,
    GX_BP_REG_SU_TSIZE1 = 0x33,
    GX_BP_REG_SU_SSIZE2 = 0x34,
    GX_BP_REG_SU_TSIZE2 = 0x35,
    GX_BP_REG_SU_SSIZE3 = 0x36,
    GX_BP_REG_SU_TSIZE3 = 0x37,
    GX_BP_REG_SU_SSIZE4 = 0x38,
    GX_BP_REG_SU_TSIZE4 = 0x39,
    GX_BP_REG_SU_SSIZE5 = 0x3A,
    GX_BP_REG_SU_TSIZE5 = 0x3B,
    GX_BP_REG_SU_SSIZE6 = 0x3C,
    GX_BP_REG_SU_TSIZE6 = 0x3D,
    GX_BP_REG_SU_SSIZE7 = 0x3E,
    GX_BP_REG_SU_TSIZE7 = 0x3F,

    // Z and blend controls
    GX_BP_REG_ZMODE      = 0x40,
    GX_BP_REG_BLENDMODE  = 0x41,
    GX_BP_REG_DSTALPHA   = 0x42,
    GX_BP_REG_ZCONTROL   = 0x43,
    GX_BP_REG_FIELDMASK  = 0x44,
    GX_BP_REG_DRAWDONE   = 0x45,
    GX_BP_REG_PETOKEN    = 0x47,
    GX_BP_REG_PETOKENINT = 0x48,

    // copying
    GX_BP_REG_TEXCOPYSRCXY   = 0x49,
    GX_BP_REG_TEXCOPYSRCWH   = 0x4A,
    GX_BP_REG_TEXCOPYDST     = 0x4B,
    GX_BP_REG_DISPCOPYSTRIDE = 0x4D,
    GX_BP_REG_DISPCOPYSCALEY = 0x4E,
    GX_BP_REG_COPYCLEARAR    = 0x4F,
    GX_BP_REG_COPYCLEARGB    = 0x50,
    GX_BP_REG_COPYCLEARZ     = 0x51,
    GX_BP_REG_COPYFILTER0    = 0x53,
    GX_BP_REG_COPYFILTER1    = 0x54,

    //
    GX_BP_REG_BOUNDINGBOX0 = 0x55,
    GX_BP_REG_BOUNDINGBOX1 = 0x56,

    GX_BP_REG_SCISSOROFFSET = 0x59,

    // texture memory
    GX_BP_REG_TMEMPRELOADADDR   = 0x60,
    GX_BP_REG_TMEMPRELOADEVEN   = 0x61,
    GX_BP_REG_TMEMPRELOADODD    = 0x62,
    GX_BP_REG_TMEMPRELOADMODE   = 0x63,
    GX_BP_REG_TMEMTLUTSRC       = 0x64,
    GX_BP_REG_TMEMTLUTDST       = 0x65,
    GX_BP_REG_TMEMTEXINVALIDATE = 0x66,

    // performance 1
    GX_BP_REG_PERF1     = 0x67,
    GX_BP_REG_FIELDMODE = 0x68,

    // set modes
    GX_BP_REG_SETMODE0_TEX0 = 0x80,
    GX_BP_REG_SETMODE0_TEX1 = 0x81,
    GX_BP_REG_SETMODE0_TEX2 = 0x82,
    GX_BP_REG_SETMODE0_TEX3 = 0x83,
    GX_BP_REG_SETMODE1_TEX0 = 0x84,
    GX_BP_REG_SETMODE1_TEX1 = 0x85,
    GX_BP_REG_SETMODE1_TEX2 = 0x86,
    GX_BP_REG_SETMODE1_TEX3 = 0x87,

    // set images
    GX_BP_REG_SETIMAGE0_TEX0 = 0x88,
    GX_BP_REG_SETIMAGE0_TEX1 = 0x89,
    GX_BP_REG_SETIMAGE0_TEX2 = 0x8A,
    GX_BP_REG_SETIMAGE0_TEX3 = 0x8B,
    GX_BP_REG_SETIMAGE1_TEX0 = 0x8C,
    GX_BP_REG_SETIMAGE1_TEX1 = 0x8D,
    GX_BP_REG_SETIMAGE1_TEX2 = 0x8E,
    GX_BP_REG_SETIMAGE1_TEX3 = 0x8F,
    GX_BP_REG_SETIMAGE2_TEX0 = 0x90,
    GX_BP_REG_SETIMAGE2_TEX1 = 0x91,
    GX_BP_REG_SETIMAGE2_TEX2 = 0x92,
    GX_BP_REG_SETIMAGE2_TEX3 = 0x93,
    GX_BP_REG_SETIMAGE3_TEX0 = 0x94,
    GX_BP_REG_SETIMAGE3_TEX1 = 0x95,
    GX_BP_REG_SETIMAGE3_TEX2 = 0x96,
    GX_BP_REG_SETIMAGE3_TEX3 = 0x97,

    // set texture lookups
    GX_BP_REG_SETTLUT_TEX0 = 0x98,
    GX_BP_REG_SETTLUT_TEX1 = 0x99,
    GX_BP_REG_SETTLUT_TEX2 = 0x9A,
    GX_BP_REG_SETTLUT_TEX3 = 0x9B,

    // set modes continued
    GX_BP_REG_SETMODE0_TEX4 = 0xA0,
    GX_BP_REG_SETMODE0_TEX5 = 0xA1,
    GX_BP_REG_SETMODE0_TEX6 = 0xA2,
    GX_BP_REG_SETMODE0_TEX7 = 0xA3,
    GX_BP_REG_SETMODE1_TEX4 = 0xA4,
    GX_BP_REG_SETMODE1_TEX5 = 0xA5,
    GX_BP_REG_SETMODE1_TEX6 = 0xA6,
    GX_BP_REG_SETMODE1_TEX7 = 0xA7,

    // set images continued
    GX_BP_REG_SETIMAGE0_TEX4 = 0xA8,
    GX_BP_REG_SETIMAGE0_TEX5 = 0xA9,
    GX_BP_REG_SETIMAGE0_TEX6 = 0xAA,
    GX_BP_REG_SETIMAGE0_TEX7 = 0xAB,
    GX_BP_REG_SETIMAGE1_TEX4 = 0xAC,
    GX_BP_REG_SETIMAGE1_TEX5 = 0xAD,
    GX_BP_REG_SETIMAGE1_TEX6 = 0xAE,
    GX_BP_REG_SETIMAGE1_TEX7 = 0xAF,
    GX_BP_REG_SETIMAGE2_TEX4 = 0xB0,
    GX_BP_REG_SETIMAGE2_TEX5 = 0xB1,
    GX_BP_REG_SETIMAGE2_TEX6 = 0xB2,
    GX_BP_REG_SETIMAGE2_TEX7 = 0xB3,
    GX_BP_REG_SETIMAGE3_TEX4 = 0xB4,
    GX_BP_REG_SETIMAGE3_TEX5 = 0xB5,
    GX_BP_REG_SETIMAGE3_TEX6 = 0xB6,
    GX_BP_REG_SETIMAGE3_TEX7 = 0xB7,

    // set texture lookups continued
    GX_BP_REG_SETTLUT_TEX4 = 0xB8,
    GX_BP_REG_SETTLUT_TEX5 = 0xB9,
    GX_BP_REG_SETTLUT_TEX6 = 0xBA,
    GX_BP_REG_SETTLUT_TEX7 = 0xBB,

    // TEV color manips
    GX_BP_REG_TEVCOLORCOMBINER0  = 0xC0,
    GX_BP_REG_TEVALPHACOMBINER0  = 0xC1,
    GX_BP_REG_TEVCOLORCOMBINER1  = 0xC2,
    GX_BP_REG_TEVALPHACOMBINER1  = 0xC3,
    GX_BP_REG_TEVCOLORCOMBINER2  = 0xC4,
    GX_BP_REG_TEVALPHACOMBINER2  = 0xC5,
    GX_BP_REG_TEVCOLORCOMBINER3  = 0xC6,
    GX_BP_REG_TEVALPHACOMBINER3  = 0xC7,
    GX_BP_REG_TEVCOLORCOMBINER4  = 0xC8,
    GX_BP_REG_TEVALPHACOMBINER4  = 0xC9,
    GX_BP_REG_TEVCOLORCOMBINER5  = 0xCA,
    GX_BP_REG_TEVALPHACOMBINER5  = 0xCB,
    GX_BP_REG_TEVCOLORCOMBINER6  = 0xCC,
    GX_BP_REG_TEVALPHACOMBINER6  = 0xCD,
    GX_BP_REG_TEVCOLORCOMBINER7  = 0xCE,
    GX_BP_REG_TEVALPHACOMBINER7  = 0xCF,
    GX_BP_REG_TEVCOLORCOMBINER8  = 0xD0,
    GX_BP_REG_TEVALPHACOMBINER8  = 0xD1,
    GX_BP_REG_TEVCOLORCOMBINER9  = 0xD2,
    GX_BP_REG_TEVALPHACOMBINER9  = 0xD3,
    GX_BP_REG_TEVCOLORCOMBINER10 = 0xD4,
    GX_BP_REG_TEVALPHACOMBINER10 = 0xD5,
    GX_BP_REG_TEVCOLORCOMBINER11 = 0xD6,
    GX_BP_REG_TEVALPHACOMBINER11 = 0xD7,
    GX_BP_REG_TEVCOLORCOMBINER12 = 0xD8,
    GX_BP_REG_TEVALPHACOMBINER12 = 0xD9,
    GX_BP_REG_TEVCOLORCOMBINER13 = 0xDA,
    GX_BP_REG_TEVALPHACOMBINER13 = 0xDB,
    GX_BP_REG_TEVCOLORCOMBINER14 = 0xDC,
    GX_BP_REG_TEVALPHACOMBINER14 = 0xDD,
    GX_BP_REG_TEVCOLORCOMBINER15 = 0xDE,
    GX_BP_REG_TEVALPHACOMBINER15 = 0xDF,

    // TEV registers
    GX_BP_REG_TEVREG0LO = 0xE0,
    GX_BP_REG_TEVREG0HI = 0xE1,
    GX_BP_REG_TEVREG1LO = 0xE2,
    GX_BP_REG_TEVREG1HI = 0xE3,
    GX_BP_REG_TEVREG2LO = 0xE4,
    GX_BP_REG_TEVREG2HI = 0xE5,
    GX_BP_REG_TEVREG3LO = 0xE6,
    GX_BP_REG_TEVREG3HI = 0xE7,

    // fog registers
    GX_BP_REG_FOGRANGE   = 0xE8,
    GX_BP_REG_FOGRANGEK0 = 0xE9,
    GX_BP_REG_FOGRANGEK1 = 0xEA,
    GX_BP_REG_FOGRANGEK2 = 0xEB,
    GX_BP_REG_FOGRANGEK3 = 0xEC,
    GX_BP_REG_FOGRANGEK4 = 0xED,
    GX_BP_REG_FOGPARAM0  = 0xEE,
    GX_BP_REG_FOGPARAM1  = 0xEF,
    GX_BP_REG_FOGPARAM2  = 0xF0,
    GX_BP_REG_FOGPARAM3  = 0xF1,
    GX_BP_REG_FOGCOLOR   = 0xF2,

    // performance manip registers
    GX_BP_REG_ALPHACOMPARE = 0xF3,
    GX_BP_REG_ZTEXTURE0    = 0xF4,
    GX_BP_REG_ZTEXTURE1    = 0xF5,

    // TEV K selectors
    GX_BP_REG_TEVKSEL0 = 0xF6,
    GX_BP_REG_TEVKSEL1 = 0xF7,
    GX_BP_REG_TEVKSEL2 = 0xF8,
    GX_BP_REG_TEVKSEL3 = 0xF9,
    GX_BP_REG_TEVKSEL4 = 0xFA,
    GX_BP_REG_TEVKSEL5 = 0xFB,
    GX_BP_REG_TEVKSEL6 = 0xFC,
    GX_BP_REG_TEVKSEL7 = 0xFD,

    // SS mask
    GX_BP_REG_SSMASK = 0xFE,
} GXBPRegs;

// Command processor registers.
typedef enum _GXCPRegs {
    GX_CP_REG_MTXIDXA     = 0x30, // Matrix index A
    GX_CP_REG_MTXIDXB     = 0x40, // Matrix index B
    GX_CP_REG_VCD_LO      = 0x50, // Vertex descriptor (lo)
    GX_CP_REG_VCD_HI      = 0x60, // Vertex descriptor (hi)
    GX_CP_REG_VAT_GRP0    = 0x70, // Vertex attribute table (group 0)
    GX_CP_REG_VAT_GRP1    = 0x80, // Vertex attribute table (group 1)
    GX_CP_REG_VAT_GRP2    = 0x90, // Vertex attribute table (group 2)
    GX_CP_REG_ARRAYBASE   = 0xA0, // Vertex array start/base
    GX_CP_REG_ARRAYSTRIDE = 0xB0, // Vertex array stride
} GXCPRegs;

// Transform unit registers.
typedef enum _GXXFRegs {
    GX_XF_REG_ERROR        = 0x1000,
    GX_XF_REG_DIAGNOSTICS  = 0x1001,
    GX_XF_REG_STATE0       = 0x1002,
    GX_XF_REG_STATE1       = 0x1003,
    GX_XF_REG_CLOCK        = 0x1004,
    GX_XF_REG_CLIPDISABLE  = 0x1005,
    GX_XF_REG_PERF0        = 0x1006,
    GX_XF_REG_PERF1        = 0x1007,
    GX_XF_REG_INVERTEXSPEC = 0x1008,
    GX_XF_REG_NUMCOLORS    = 0x1009,
    GX_XF_REG_AMBIENT0     = 0x100A,
    GX_XF_REG_AMBIENT1     = 0x100B,
    GX_XF_REG_MATERIAL0    = 0x100C,
    GX_XF_REG_MATERIAL1    = 0x100D,
    GX_XF_REG_COLOR0CNTRL  = 0x100E,
    GX_XF_REG_COLOR1CNTRL  = 0x100F,
    GX_XF_REG_ALPHA0CNTRL  = 0x1010,
    GX_XF_REG_ALPHA1CNTRL  = 0x1011,
    GX_XF_REG_DUALTEXTRAN  = 0x1012,
    GX_XF_REG_MATRIXINDEX0 = 0x1018,
    GX_XF_REG_MATRIXINDEX1 = 0x1019,
    GX_XF_REG_SCALEX       = 0x101A,
    GX_XF_REG_SCALEY       = 0x101B,
    GX_XF_REG_SCALEZ       = 0x101C,
    GX_XF_REG_OFFSETX      = 0x101D,
    GX_XF_REG_OFFSETY      = 0x101E,
    GX_XF_REG_OFFSETZ      = 0x101F,
    GX_XF_REG_PROJECTIONA  = 0x1020,
    GX_XF_REG_PROJECTIONB  = 0x1021,
    GX_XF_REG_PROJECTIONC  = 0x1022,
    GX_XF_REG_PROJECTIOND  = 0x1023,
    GX_XF_REG_PROJECTIONE  = 0x1024,
    GX_XF_REG_PROJECTIONF  = 0x1025,
    GX_XF_REG_PROJECTORTHO = 0x1026,
    GX_XF_REG_NUMTEX       = 0x103F,
    GX_XF_REG_TEX0         = 0x1040,
    GX_XF_REG_TEX1         = 0x1041,
    GX_XF_REG_TEX2         = 0x1042,
    GX_XF_REG_TEX3         = 0x1043,
    GX_XF_REG_TEX4         = 0x1044,
    GX_XF_REG_TEX5         = 0x1045,
    GX_XF_REG_TEX6         = 0x1046,
    GX_XF_REG_TEX7         = 0x1047,
    GX_XF_REG_DUALTEX0     = 0x1050,
    GX_XF_REG_DUALTEX1     = 0x1051,
    GX_XF_REG_DUALTEX2     = 0x1052,
    GX_XF_REG_DUALTEX3     = 0x1053,
    GX_XF_REG_DUALTEX4     = 0x1054,
    GX_XF_REG_DUALTEX5     = 0x1055,
    GX_XF_REG_DUALTEX6     = 0x1056,
    GX_XF_REG_DUALTEX7     = 0x1057,
} GXXFRegs;

#define XF_REG_TEX(proj, form, tgType, row, embossRow, embossLit) \
    ((proj) << 1 | (form) << 2 | (tgType) << 4 | (row) << 7 | (embossRow) << 12 | (embossLit) << 15)

// BP GenMode locators.
typedef enum _GXBPGenMode {
    // Active texture counts [28-31]
    GX_BP_GENMODE_NUMTEX_ST  = 28,
    GX_BP_GENMODE_NUMTEX_END = 31,

    // Color/channel counts [25-27]
    GX_BP_GENMODE_NUMCOLORS_ST  = 25,
    GX_BP_GENMODE_NUMCOLORS_END = 27,

    // Multisample mode [22-22]
    GX_BP_GENMODE_MULTISAMPLE_ST  = 22,
    GX_BP_GENMODE_MULTISAMPLE_END = 22,

    // Cull mode [16-17]
    GX_BP_GENMODE_CULLMODE_ST  = 16,
    GX_BP_GENMODE_CULLMODE_END = 17,

    // Indirect stage counts [13-15]
    GX_BP_GENMODE_NUMINDSTAGES_ST  = 13,
    GX_BP_GENMODE_NUMINDSTAGES_END = 15,

    // Toggle co-planar/Z-freeze [12-12]
    GX_BP_GENMODE_COPLANAR_ST  = 12,
    GX_BP_GENMODE_COPLANAR_END = 12,
} GXBPGenMode;

// BP locators for indirect texture matrices (same for A, B, and C).
typedef enum _GXBPIndMtx {
    // Texture offset matrix [0][0] [21-31]
    GX_BP_INDMTX_M00_ST  = 21,
    GX_BP_INDMTX_M00_END = 31,

    // Texture offset matrix [1][0] [10-20]
    GX_BP_INDMTX_M10_ST  = 10,
    GX_BP_INDMTX_M10_END = 20,

    // Texture scaling exponent (2^x) [8-9]
    GX_BP_INDMTX_EXP_ST  = 8,
    GX_BP_INDMTX_EXP_END = 9,
} GXBPIndMtx;

// BP locators for indirect texture masks.
typedef enum _GXBPIndIMask {
    // Indirect mask [24-31]
    GX_BP_INDIMASK_ST  = 24,
    GX_BP_INDIMASK_END = 31,
} GXBPIndIMask;

// BP locators for indirect texture environment details.
typedef enum _GXBPIndTevStage {
    // Indirect texture stage ID [30-31]
    GX_BP_INDTEV_STAGE_ST  = 30,
    GX_BP_INDTEV_STAGE_END = 31,

    // Indirect texture format [28-29]
    GX_BP_INDTEV_FMT_ST  = 28,
    GX_BP_INDTEV_FMT_END = 29,

    // Indirect texture bias [25-27]
    GX_BP_INDTEV_BIAS_ST  = 25,
    GX_BP_INDTEV_BIAS_END = 27,

    // Indirect texture alpha [23-24]
    GX_BP_INDTEV_ALPHA_ST  = 23,
    GX_BP_INDTEV_ALPHA_END = 24,

    // Indirect texture matrices [19-22]
    GX_BP_INDTEV_MTX_ST  = 19,
    GX_BP_INDTEV_MTX_END = 22,

    // Indirect texture S component wrap factor [16-18]
    GX_BP_INDTEV_WRAPS_ST  = 16,
    GX_BP_INDTEV_WRAPS_END = 18,

    // Indirect texture T component wrap factor [13-15]
    GX_BP_INDTEV_WRAPT_ST  = 13,
    GX_BP_INDTEV_WRAPT_END = 15,

    // Indirect texture unmodified texcoord setting (for mipmaps) [12-12]
    GX_BP_INDTEV_UNMODTEXCOORD_ST  = 12,
    GX_BP_INDTEV_UNMODTEXCOORD_END = 12,

    // Indirect texture add previous results setting [11-11]
    GX_BP_INDTEV_ADDPREV_ST  = 11,
    GX_BP_INDTEV_ADDPREV_END = 11,
} GXBPIndTevStage;

// BP locators for top-left scissor.
typedef enum _GXBPScissorTL {
    // Top component [21-31]
    GX_BP_SCISSORTL_TOP_ST  = 21,
    GX_BP_SCISSORTL_TOP_END = 31,

    // Left component [9-19]
    GX_BP_SCISSORTL_LEFT_ST  = 9,
    GX_BP_SCISSORTL_LEFT_END = 19,
} GXBPScissorTL;

// BP locators for bottom-right scissor.
typedef enum _GXBPScissorBR {
    // Bottom component [21-31]
    GX_BP_SCISSORBR_BOT_ST  = 21,
    GX_BP_SCISSORBR_BOT_END = 31,

    // Right component [9-19]
    GX_BP_SCISSORBR_RIGHT_ST  = 9,
    GX_BP_SCISSORBR_RIGHT_END = 19,
} GXBPScissorBR;

// BP locators for line and point settings.
typedef enum _GXBPLinePtWidth {
    // Line size/width [24-31]
    GX_BP_LINEPTWIDTH_LINESZ_ST  = 24,
    GX_BP_LINEPTWIDTH_LINESZ_END = 31,

    // Point size [16-23]
    GX_BP_LINEPTWIDTH_POINTSZ_ST  = 16,
    GX_BP_LINEPTWIDTH_POINTSZ_END = 23,

    // Line offset [13-15]
    GX_BP_LINEPTWIDTH_LINEOFS_ST  = 13,
    GX_BP_LINEPTWIDTH_LINEOFS_END = 15,

    // Point offset [10-12]
    GX_BP_LINEPTWIDTH_POINTOFS_ST  = 10,
    GX_BP_LINEPTWIDTH_POINTOFS_END = 12,

    // Interlacing adjustment for aspect ratio [9-9]
    GX_BP_LINEPTWIDTH_ADJUST_ST  = 9,
    GX_BP_LINEPTWIDTH_ADJUST_END = 9,
} GXBPLinePtWidth;

// BP locators for raster 1 SS0.
typedef enum _GXBPRas1SS0 {
    // S-component scale (stage 0) [28-31]
    GX_BP_RAS1_SS0_S0_ST  = 28,
    GX_BP_RAS1_SS0_S0_END = 31,

    // T-component scale (stage 0) [24-27]
    GX_BP_RAS1_SS0_T0_ST  = 24,
    GX_BP_RAS1_SS0_T0_END = 27,

    // S-component scale (stage 1) [20-23]
    GX_BP_RAS1_SS0_S1_ST  = 20,
    GX_BP_RAS1_SS0_S1_END = 23,

    // T-component scale (stage 1) [16-19]
    GX_BP_RAS1_SS0_T1_ST  = 16,
    GX_BP_RAS1_SS0_T1_END = 19,
} GXBPRas1SS0;

// BP locators for raster 1 SS1.
typedef enum _GXBPRas1SS1 {
    // S-component scale (stage 2) [28-31]
    GX_BP_RAS1_SS1_S2_ST  = 28,
    GX_BP_RAS1_SS1_S2_END = 31,

    // T-component scale (stage 2) [24-27]
    GX_BP_RAS1_SS1_T2_ST  = 24,
    GX_BP_RAS1_SS1_T2_END = 27,

    // S-component scale (stage 3) [20-23]
    GX_BP_RAS1_SS1_S3_ST  = 20,
    GX_BP_RAS1_SS1_S3_END = 23,

    // T-component scale (stage 3) [16-19]
    GX_BP_RAS1_SS1_T3_ST  = 16,
    GX_BP_RAS1_SS1_T3_END = 19,
} GXBPRas1SS1;

// BP locators for raster 1 ID-reference.
typedef enum _GXBPRasIRef {
    // Texmap ID (stage 0) [29-31]
    GX_BP_RAS1_IREF_MAP0_ST  = 29,
    GX_BP_RAS1_IREF_MAP0_END = 31,

    // Texcoord ID (stage 0) [26-28]
    GX_BP_RAS1_IREF_TXC0_ST  = 26,
    GX_BP_RAS1_IREF_TXC0_END = 28,

    // Texmap ID (stage 1) [23-25]
    GX_BP_RAS1_IREF_MAP1_ST  = 23,
    GX_BP_RAS1_IREF_MAP1_END = 25,

    // Texcoord ID (stage 1) [20-22]
    GX_BP_RAS1_IREF_TXC1_ST  = 20,
    GX_BP_RAS1_IREF_TXC1_END = 22,

    // Texmap ID (stage 2) [17-19]
    GX_BP_RAS1_IREF_MAP2_ST  = 17,
    GX_BP_RAS1_IREF_MAP2_END = 19,

    // Texcoord ID (stage 2) [14-16]
    GX_BP_RAS1_IREF_TXC2_ST  = 14,
    GX_BP_RAS1_IREF_TXC2_END = 16,

    // Texmap ID (stage 3) [11-13]
    GX_BP_RAS1_IREF_MAP3_ST  = 11,
    GX_BP_RAS1_IREF_MAP3_END = 13,

    // Texcoord ID (stage 3) [8-10]
    GX_BP_RAS1_IREF_TXC3_ST  = 8,
    GX_BP_RAS1_IREF_TXC3_END = 10,
} GXBPRasIRef;

// BP locators for setup size.
typedef enum _GXBPSUSSize {
    // Use line offsets [13-13]
    GX_BP_SU_SSIZE_USELINEOFS_ST  = 13,
    GX_BP_SU_SSIZE_USELINEOFS_END = 13,

    // Use point offsets [12-12]
    GX_BP_SU_SSIZE_USEPTOFS_ST  = 12,
    GX_BP_SU_SSIZE_USEPTOFS_END = 12,
} GXBPSUSSize;

// BP locators for Z mode.
typedef enum _GXBPZMode {
    // Test enable [31-31]
    GX_BP_ZMODE_TEST_ENABLE_ST  = 31,
    GX_BP_ZMODE_TEST_ENABLE_END = 31,

    // Compare [28-30]
    GX_BP_ZMODE_COMPARE_ST  = 28,
    GX_BP_ZMODE_COMPARE_END = 30,

    // Update enable [27-27]
    GX_BP_ZMODE_UPDATE_ENABLE_ST  = 27,
    GX_BP_ZMODE_UPDATE_ENABLE_END = 27,
} GXBPZMode;

// BP locators for blend mode.
typedef enum _GXBPBlendMode {
    // Blend enable [31-31]
    GX_BP_BLENDMODE_ENABLE_ST  = 31,
    GX_BP_BLENDMODE_ENABLE_END = 31,

    // Logic operation enable [30-30]
    GX_BP_BLENDMODE_LOGIC_OP_ST  = 30,
    GX_BP_BLENDMODE_LOGIC_OP_END = 30,

    // Dither [29-29]
    GX_BP_BLENDMODE_DITHER_ST  = 29,
    GX_BP_BLENDMODE_DITHER_END = 29,

    // Color update [28-28]
    GX_BP_BLENDMODE_COLOR_UPDATE_ST  = 28,
    GX_BP_BLENDMODE_COLOR_UPDATE_END = 28,

    // Alpha update [27-27]
    GX_BP_BLENDMODE_ALPHA_UPDATE_ST  = 27,
    GX_BP_BLENDMODE_ALPHA_UPDATE_END = 27,

    // Destination factor [24-26]
    GX_BP_BLENDMODE_DSTFACTOR_ST  = 24,
    GX_BP_BLENDMODE_DSTFACTOR_END = 26,

    // Source factor [21-23]
    GX_BP_BLENDMODE_SRCFACTOR_ST  = 21,
    GX_BP_BLENDMODE_SRCFACTOR_END = 23,

    // Subtract [20-20]
    GX_BP_BLENDMODE_SUBTRACT_ST  = 20,
    GX_BP_BLENDMODE_SUBTRACT_END = 20,

    // Logic mode [16-19]
    GX_BP_BLENDMODE_LOGICMODE_ST  = 16,
    GX_BP_BLENDMODE_LOGICMODE_END = 19,
} GXBPBlendMode;

// BP locators for destination alpha.
typedef enum _GXBPDstAlpha {
    // Alpha [24-31]
    GX_BP_DSTALPHA_ALPHA_ST  = 24,
    GX_BP_DSTALPHA_ALPHA_END = 31,

    // Enable [23-23]
    GX_BP_DSTALPHA_ENABLE_ST  = 23,
    GX_BP_DSTALPHA_ENABLE_END = 23,

    // YUV format [21-22]
    GX_BP_DSTALPHA_YUV_FMT_ST  = 21,
    GX_BP_DSTALPHA_YUV_FMT_END = 22,
} GXBPDstAlpha;

// BP locators for Z control.
typedef enum _GXBPZControl {
    // Pixel format [29-31]
    GX_BP_ZCONTROL_PIXEL_FMT_ST  = 29,
    GX_BP_ZCONTROL_PIXEL_FMT_END = 31,

    // Z format [26-28]
    GX_BP_ZCONTROL_Z_FMT_ST  = 26,
    GX_BP_ZCONTROL_Z_FMT_END = 28,

    // Whether to do Z-buffering before or after texturing [25-25]
    GX_BP_ZCONTROL_BEFORE_TEX_ST  = 25,
    GX_BP_ZCONTROL_BEFORE_TEX_END = 25,
} GXBPZControl;

// BP locators for field mask.
typedef enum _GXBPFieldMask {
    // Whether to write odd fields to the EFB [31-31]
    GX_BP_FIELDMASK_ODD_ST  = 31,
    GX_BP_FIELDMASK_ODD_END = 31,

    // Whether to write even fields to the EFB [30-30]
    GX_BP_FIELDMASK_EVEN_ST  = 30,
    GX_BP_FIELDMASK_EVEN_END = 30,
} GXBPFieldMask;

// BP locators for scissor offset.
typedef enum _GXBPScissorOffset {
    // X offset [22-31]
    GX_BP_SCISSOROFS_OX_ST  = 22,
    GX_BP_SCISSOROFS_OX_END = 31,

    // Y offset [12-21]
    GX_BP_SCISSOROFS_OY_ST  = 12,
    GX_BP_SCISSOROFS_OY_END = 21,
} GXBPScissorOffset;

// BP locators for field mode.
typedef enum _GXBPFieldMode {
    // Adjust vertex tex LOD computation to account for interlacing
    GX_BP_FIELDMODE_TEX_LOD_ST  = 31,
    GX_BP_FIELDMODE_TEX_LOD_END = 31,
} GXBPFieldMode;

// BP locators for fog range.
typedef enum _GXBPFogRange {
    // Center [22-31]
    GX_BP_FOGRANGE_CENTER_ST  = 22,
    GX_BP_FOGRANGE_CENTER_END = 31,

    // Enabled [21-21]
    GX_BP_FOGRANGE_ENABLED_ST  = 21,
    GX_BP_FOGRANGE_ENABLED_END = 21,
} GXBPFogRange;

// BP locators for fog range K.
typedef enum _GXBPFogRangeK {
    // Hi [20-31]
    GX_BP_FOGRANGEK_HI_ST  = 20,
    GX_BP_FOGRANGEK_HI_END = 31,

    // Lo [8-19]
    GX_BP_FOGRANGEK_LO_ST  = 8,
    GX_BP_FOGRANGEK_LO_END = 19,
} GXBPFogRangeK;

// BP locators for fog parameter 0.
typedef enum _GXBPFogParam0 {
    // A mantissa [21-31]
    GX_BP_FOGPARAM0_A_MANT_ST  = 21,
    GX_BP_FOGPARAM0_A_MANT_END = 31,

    // A exponent [13-20]
    GX_BP_FOGPARAM0_A_EXP_ST  = 13,
    GX_BP_FOGPARAM0_A_EXP_END = 20,

    // A sign [12-12]
    GX_BP_FOGPARAM0_A_SIGN_ST  = 12,
    GX_BP_FOGPARAM0_A_SIGN_END = 12,
} GXBPFogParam0;

// BP locators for fog parameter 1.
typedef enum _GXBPFogParam1 {
    // B magnitude [8-31]
    GX_BP_FOGPARAM1_B_MAG_ST  = 8,
    GX_BP_FOGPARAM1_B_MAG_END = 31,
} GXBPFogParam1;

// BP locators for fog parameter 2.
typedef enum _GXBPFogParam2 {
    // B shift [27-31]
    GX_BP_FOGPARAM2_B_SHIFT_ST  = 27,
    GX_BP_FOGPARAM2_B_SHIFT_END = 31,
} GXBPFogParam2;

// BP locators for fog parameter 3.
typedef enum _GXBPFogParam3 {
    // C mantissa [21-31]
    GX_BP_FOGPARAM3_C_MANT_ST  = 21,
    GX_BP_FOGPARAM3_C_MANT_END = 31,

    // C exponent [13-20]
    GX_BP_FOGPARAM3_C_EXP_ST  = 13,
    GX_BP_FOGPARAM3_C_EXP_END = 20,

    // C sign [12-12]
    GX_BP_FOGPARAM3_C_SIGN_ST  = 12,
    GX_BP_FOGPARAM3_C_SIGN_END = 12,

    // Projection [11]
    GX_BP_FOGPARAM3_PROJ_ST  = 11,
    GX_BP_FOGPARAM3_PROJ_END = 11,

    // F select [8-10]
    GX_BP_FOGPARAM3_FSEL_ST  = 8,
    GX_BP_FOGPARAM3_FSEL_END = 10,
} GXBPFogParam3;

// BP locators for fog color.
typedef enum _GXBPFogColor {
    // RGB components of color [8-31]
    GX_BP_FOGCOLOR_RGB_ST  = 8,
    GX_BP_FOGCOLOR_RGB_END = 31,
} GXBPFogColor;

// CP locator for matrix index A.
typedef enum _GXCPMtxIdxA {
    // Geometry [26-31]
    GX_CP_MTXIDXA_GEOM_ST  = 26,
    GX_CP_MTXIDXA_GEOM_END = 31,

    // Tex0 [20-25]
    GX_CP_MTXIDXA_TEX0_ST  = 20,
    GX_CP_MTXIDXA_TEX0_END = 25,

    // Tex1 [14-19]
    GX_CP_MTXIDXA_TEX1_ST  = 14,
    GX_CP_MTXIDXA_TEX1_END = 19,

    // Tex2 [8-13]
    GX_CP_MTXIDXA_TEX2_ST  = 8,
    GX_CP_MTXIDXA_TEX2_END = 13,

    // Tex3 [2-7]
    GX_CP_MTXIDXA_TEX3_ST  = 2,
    GX_CP_MTXIDXA_TEX3_END = 7,
} GXCPMtxIdxA;

// CP locator for matrix index B.
typedef enum _GXCPMtxIdxB {
    // Tex4 [26-31]
    GX_CP_MTXIDXB_TEX4_ST  = 26,
    GX_CP_MTXIDXB_TEX4_END = 31,

    // Tex5 [20-25]
    GX_CP_MTXIDXB_TEX5_ST  = 20,
    GX_CP_MTXIDXB_TEX5_END = 25,

    // Tex6 [14-19]
    GX_CP_MTXIDXB_TEX6_ST  = 14,
    GX_CP_MTXIDXB_TEX6_END = 19,

    // Tex7 [8-13]
    GX_CP_MTXIDXB_TEX7_ST  = 8,
    GX_CP_MTXIDXB_TEX7_END = 13,
} GXCPMtxIdxB;

// CP locator for vertex descriptor (lo).
typedef enum _GXCPVCDLo {
    // Position matrix idx [31]
    GX_CP_VCD_LO_POSMTXIDX_ST  = 31,
    GX_CP_VCD_LO_POSMTXIDX_END = 31,

    // Tex 0 matrix idx [30]
    GX_CP_VCD_LO_TEX0MTXIDX_ST  = 30,
    GX_CP_VCD_LO_TEX0MTXIDX_END = 30,

    // Tex 1 matrix idx [29]
    GX_CP_VCD_LO_TEX1MTXIDX_ST  = 29,
    GX_CP_VCD_LO_TEX1MTXIDX_END = 29,

    // Tex 2 matrix idx [28]
    GX_CP_VCD_LO_TEX2MTXIDX_ST  = 28,
    GX_CP_VCD_LO_TEX2MTXIDX_END = 28,

    // Tex 3 matrix idx [27]
    GX_CP_VCD_LO_TEX3MTXIDX_ST  = 27,
    GX_CP_VCD_LO_TEX3MTXIDX_END = 27,

    // Tex 4 matrix idx [26]
    GX_CP_VCD_LO_TEX4MTXIDX_ST  = 26,
    GX_CP_VCD_LO_TEX4MTXIDX_END = 26,

    // Tex 5 matrix idx [25]
    GX_CP_VCD_LO_TEX5MTXIDX_ST  = 25,
    GX_CP_VCD_LO_TEX5MTXIDX_END = 25,

    // Tex 6 matrix idx [24]
    GX_CP_VCD_LO_TEX6MTXIDX_ST  = 24,
    GX_CP_VCD_LO_TEX6MTXIDX_END = 24,

    // Tex 7 matrix idx [23]
    GX_CP_VCD_LO_TEX7MTXIDX_ST  = 23,
    GX_CP_VCD_LO_TEX7MTXIDX_END = 23,

    // Position [21-22]
    GX_CP_VCD_LO_POS_ST  = 21,
    GX_CP_VCD_LO_POS_END = 22,

    // Normal [19-20]
    GX_CP_VCD_LO_NRM_ST  = 19,
    GX_CP_VCD_LO_NRM_END = 20,

    // Color diffused [17-18]
    GX_CP_VCD_LO_CLRDIF_ST  = 17,
    GX_CP_VCD_LO_CLRDIF_END = 18,

    // Color specular [15-16]
    GX_CP_VCD_LO_CLRSPEC_ST  = 15,
    GX_CP_VCD_LO_CLRSPEC_END = 16,
} GXCPVCDLo;

// CP locators for vertex descriptor (hi).
typedef enum _GXCPVCDHi {
    // Tex0 coordinates [30-31]
    GX_CP_VCD_HI_TEX0COORD_ST  = 30,
    GX_CP_VCD_HI_TEX0COORD_END = 31,

    // Tex1 coordinates [28-29]
    GX_CP_VCD_HI_TEX1COORD_ST  = 28,
    GX_CP_VCD_HI_TEX1COORD_END = 29,

    // Tex2 coordinates [26-27]
    GX_CP_VCD_HI_TEX2COORD_ST  = 26,
    GX_CP_VCD_HI_TEX2COORD_END = 27,

    // Tex3 coordinates [24-25]
    GX_CP_VCD_HI_TEX3COORD_ST  = 24,
    GX_CP_VCD_HI_TEX3COORD_END = 25,

    // Tex4 coordinates [22-23]
    GX_CP_VCD_HI_TEX4COORD_ST  = 22,
    GX_CP_VCD_HI_TEX4COORD_END = 23,

    // Tex5 coordinates [20-21]
    GX_CP_VCD_HI_TEX5COORD_ST  = 20,
    GX_CP_VCD_HI_TEX5COORD_END = 21,

    // Tex6 coordinates [18-19]
    GX_CP_VCD_HI_TEX6COORD_ST  = 18,
    GX_CP_VCD_HI_TEX6COORD_END = 19,

    // Tex7 coordinates [16-17]
    GX_CP_VCD_HI_TEX7COORD_ST  = 16,
    GX_CP_VCD_HI_TEX7COORD_END = 17,
} GXCPVCDHi;

// CP locator for vertex attribute table (group 0).
typedef enum _GXCPVATGrp0 {
    // Position count [31-31]
    GX_CP_VAT_GRP0_POS_CNT_ST  = 31,
    GX_CP_VAT_GRP0_POS_CNT_END = 31,

    // Position type [28-30]
    GX_CP_VAT_GRP0_POS_TYPE_ST  = 28,
    GX_CP_VAT_GRP0_POS_TYPE_END = 30,

    // Position shift [23-27]
    GX_CP_VAT_GRP0_POS_SHIFT_ST  = 23,
    GX_CP_VAT_GRP0_POS_SHIFT_END = 27,

    // Normal count [22-22]
    GX_CP_VAT_GRP0_NRM_CNT_ST  = 22,
    GX_CP_VAT_GRP0_NRM_CNT_END = 22,

    // Normal type [19-21]
    GX_CP_VAT_GRP0_NRM_TYPE_ST  = 19,
    GX_CP_VAT_GRP0_NRM_TYPE_END = 21,

    // Color diffused count [18-18]
    GX_CP_VAT_GRP0_CLRDIFF_CNT_ST  = 18,
    GX_CP_VAT_GRP0_CLRDIFF_CNT_END = 18,

    // Color diffused type [15-17]
    GX_CP_VAT_GRP0_CLRDIFF_TYPE_ST  = 15,
    GX_CP_VAT_GRP0_CLRDIFF_TYPE_END = 17,

    // Color specular count [14-14]
    GX_CP_VAT_GRP0_CLRSPEC_CNT_ST  = 14,
    GX_CP_VAT_GRP0_CLRSPEC_CNT_END = 14,

    // Color specular type [11-13]
    GX_CP_VAT_GRP0_CLRSPEC_TYPE_ST  = 11,
    GX_CP_VAT_GRP0_CLRSPEC_TYPE_END = 13,

    // Tex0 coord count [10-10]
    GX_CP_VAT_GRP0_TXC0_CNT_ST  = 10,
    GX_CP_VAT_GRP0_TXC0_CNT_END = 10,

    // Tex0 coord type [7-9]
    GX_CP_VAT_GRP0_TXC0_TYPE_ST  = 7,
    GX_CP_VAT_GRP0_TXC0_TYPE_END = 9,

    // Tex0 coord shift [2-6]
    GX_CP_VAT_GRP0_TXC0_SHIFT_ST  = 2,
    GX_CP_VAT_GRP0_TXC0_SHIFT_END = 6,

    // Byte dequantised [1-1]
    GX_CP_VAT_GRP0_BYTEDEQ_ST  = 1,
    GX_CP_VAT_GRP0_BYTEDEQ_END = 1,

    // Normal index 3 [0-0] (Input will be treated as three staggered indices (one per triple biased by component size) into normal table))
    GX_CP_VAT_GRP0_NRMIDX3_ST  = 0,
    GX_CP_VAT_GRP0_NRMIDX3_END = 0,
} GXCPVATGrp0;

// CP locators for vertex attribute table (group 1).
typedef enum _GXCPVATGrp1 {
    // Tex1 coord count [31-31]
    GX_CP_VAT_GRP1_TXC1_CNT_ST  = 31,
    GX_CP_VAT_GRP1_TXC1_CNT_END = 31,

    // Tex1 coord type [28-30]
    GX_CP_VAT_GRP1_TXC1_TYPE_ST  = 28,
    GX_CP_VAT_GRP1_TXC1_TYPE_END = 30,

    // Tex1 coord shift [23-27]
    GX_CP_VAT_GRP1_TXC1_SHIFT_ST  = 23,
    GX_CP_VAT_GRP1_TXC1_SHIFT_END = 27,

    // Tex2 coord count [22-22]
    GX_CP_VAT_GRP1_TXC2_CNT_ST  = 22,
    GX_CP_VAT_GRP1_TXC2_CNT_END = 22,

    // Tex2 coord type [19-21]
    GX_CP_VAT_GRP1_TXC2_TYPE_ST  = 19,
    GX_CP_VAT_GRP1_TXC2_TYPE_END = 21,

    // Tex2 coord shift [14-18]
    GX_CP_VAT_GRP1_TXC2_SHIFT_ST  = 14,
    GX_CP_VAT_GRP1_TXC2_SHIFT_END = 18,

    // Tex3 coord count [13-13]
    GX_CP_VAT_GRP1_TXC3_CNT_ST  = 13,
    GX_CP_VAT_GRP1_TXC3_CNT_END = 13,

    // Tex3 coord type [10-12]
    GX_CP_VAT_GRP1_TXC3_TYPE_ST  = 10,
    GX_CP_VAT_GRP1_TXC3_TYPE_END = 12,

    // Tex3 coord shift [5-9]
    GX_CP_VAT_GRP1_TXC3_SHIFT_ST  = 5,
    GX_CP_VAT_GRP1_TXC3_SHIFT_END = 9,

    // Tex4 coord count [4-4]
    GX_CP_VAT_GRP1_TXC4_CNT_ST  = 4,
    GX_CP_VAT_GRP1_TXC4_CNT_END = 4,

    // Tex4 coord type [1-3]
    GX_CP_VAT_GRP1_TXC4_TYPE_ST  = 1,
    GX_CP_VAT_GRP1_TXC4_TYPE_END = 3,

} GXCPVATGrp1;

// CP locators for vertex attribute table (group 2).
typedef enum _GXCPVATGrp2 {
    // Tex4 coord shift [27-31]
    GX_CP_VAT_GRP2_TXC4_SHIFT_ST  = 27,
    GX_CP_VAT_GRP2_TXC4_SHIFT_END = 31,

    // Tex5 coord count [26-26]
    GX_CP_VAT_GRP2_TXC5_CNT_ST  = 26,
    GX_CP_VAT_GRP2_TXC5_CNT_END = 26,

    // Tex5 coord type [23-25]
    GX_CP_VAT_GRP2_TXC5_TYPE_ST  = 23,
    GX_CP_VAT_GRP2_TXC5_TYPE_END = 25,

    // Tex5 coord shift [18-22]
    GX_CP_VAT_GRP2_TXC5_SHIFT_ST  = 18,
    GX_CP_VAT_GRP2_TXC5_SHIFT_END = 22,

    // Tex6 coord count [17-17]
    GX_CP_VAT_GRP2_TXC6_CNT_ST  = 17,
    GX_CP_VAT_GRP2_TXC6_CNT_END = 17,

    // Tex6 coord type [14-16]
    GX_CP_VAT_GRP2_TXC6_TYPE_ST  = 14,
    GX_CP_VAT_GRP2_TXC6_TYPE_END = 16,

    // Tex6 coord shift [9-13]
    GX_CP_VAT_GRP2_TXC6_SHIFT_ST  = 9,
    GX_CP_VAT_GRP2_TXC6_SHIFT_END = 13,

    // Tex7 coord count [8-8]
    GX_CP_VAT_GRP2_TXC7_CNT_ST  = 8,
    GX_CP_VAT_GRP2_TXC7_CNT_END = 8,

    // Tex7 coord type [5-7]
    GX_CP_VAT_GRP2_TXC7_TYPE_ST  = 5,
    GX_CP_VAT_GRP2_TXC7_TYPE_END = 7,

    // Tex7 coord shift [0-4]
    GX_CP_VAT_GRP2_TXC7_SHIFT_ST  = 0,
    GX_CP_VAT_GRP2_TXC7_SHIFT_END = 4,
} GXCPVATGrp2;

// CP locators for array base.
typedef enum _GXCPArrayBase {
    // Base [6-31]
    GX_CP_ARRAYBASE_BASE_ST  = 6,
    GX_CP_ARRAYBASE_BASE_END = 31,
} GXCPArrayBase;

// CP locators for array stride.
typedef enum _GXCPArrayStride {
    // Stride [24-31]
    GX_CP_ARRAYSTRIDE_STRIDE_ST  = 24,
    GX_CP_ARRAYSTRIDE_STRIDE_END = 31,
} GXCPArrayStride;

// XF locators for clip disabling.
typedef enum _GXXFClipDisable {
    // Disable detection [31-31]
    GX_XF_CLIPDISABLE_DETECT_ST  = 31,
    GX_XF_CLIPDISABLE_DETECT_END = 31,

    // Disable trivial rejection [30-30]
    GX_XF_CLIPDISABLE_REJECT_ST  = 30,
    GX_XF_CLIPDISABLE_REJECT_END = 30,

    // Disable cpoly clipping acceleration [29-29]
    GX_XF_CLIPDISABLE_ACCEL_ST  = 29,
    GX_XF_CLIPDISABLE_ACCEL_END = 29,
} GXXFClipDisable;

// XF locators for InVertexSpec.
typedef enum _GXXFInVertexSpec {
    // Color [30-31]
    GX_XF_INVERTEXSPEC_CLR_ST  = 30,
    GX_XF_INVERTEXSPEC_CLR_END = 31,

    // Normal [28-29]
    GX_XF_INVERTEXSPEC_NRM_ST  = 28,
    GX_XF_INVERTEXSPEC_NRM_END = 29,

    // Tex coords [24-27]
    GX_XF_INVERTEXSPEC_TEX_ST  = 24,
    GX_XF_INVERTEXSPEC_TEX_END = 27,
} GXXFInVertexSpec;

// XF locators for Color 0 control.
typedef enum _GXXFClr0Ctrl {
    // Matrix source [31-31]
    GX_XF_CLR0CTRL_MTXSRC_ST  = 31,
    GX_XF_CLR0CTRL_MTXSRC_END = 31,

    // Light [30-30]
    GX_XF_CLR0CTRL_LIGHT_ST  = 30,
    GX_XF_CLR0CTRL_LIGHT_END = 30,

    // Light mask (hi) [26-29]
    GX_XF_CLR0CTRL_LMASKHI_ST  = 26,
    GX_XF_CLR0CTRL_LMASKHI_END = 29,

    // Ambient source [25-25]
    GX_XF_CLR0CTRL_AMBSRC_ST  = 25,
    GX_XF_CLR0CTRL_AMBSRC_END = 25,

    // Diffuse attenuation [23-24]
    GX_XF_CLR0CTRL_DIFATTN_ST  = 23,
    GX_XF_CLR0CTRL_DIFATTN_END = 24,

    // Enable attenuation [22-22]
    GX_XF_CLR0CTRL_ATTNENABLE_ST  = 22,
    GX_XF_CLR0CTRL_ATTNENABLE_END = 22,

    // Select attenuation [21-21]
    GX_XF_CLR0CTRL_ATTNSEL_ST  = 21,
    GX_XF_CLR0CTRL_ATTNSEL_END = 21,

    // Light mask (lo) [17-20]
    GX_XF_CLR0CTRL_LMASKLO_ST  = 17,
    GX_XF_CLR0CTRL_LMASKLO_END = 20,
} GXXFClr0Ctrl;

// XF locators for matrix index 0.
typedef enum _GXXFMtxIdx0 {
    // Geometry [26-31]
    GX_XF_MTXIDX0_GEOM_ST  = 26,
    GX_XF_MTXIDX0_GEOM_END = 31,

    // Tex 0 [20-25]
    GX_XF_MTXIDX0_TEX0_ST  = 20,
    GX_XF_MTXIDX0_TEX0_END = 25,

    // Tex 1 [14-19]
    GX_XF_MTXIDX0_TEX1_ST  = 14,
    GX_XF_MTXIDX0_TEX1_END = 19,

    // Tex 2 [8-13]
    GX_XF_MTXIDX0_TEX2_ST  = 8,
    GX_XF_MTXIDX0_TEX2_END = 13,

    // Tex 3 [2-7]
    GX_XF_MTXIDX0_TEX3_ST  = 2,
    GX_XF_MTXIDX0_TEX3_END = 7,
} GXXFMtxIdx0;

// XF locators for matrix index 1.
typedef enum _GXXFMtxIdx1 {
    // Tex 4 [26-31]
    GX_XF_MTXIDX1_TEX4_ST  = 26,
    GX_XF_MTXIDX1_TEX4_END = 31,

    // Tex 5 [20-25]
    GX_XF_MTXIDX1_TEX5_ST  = 20,
    GX_XF_MTXIDX1_TEX5_END = 25,

    // Tex 6 [14-19]
    GX_XF_MTXIDX1_TEX6_ST  = 14,
    GX_XF_MTXIDX1_TEX6_END = 19,

    // Tex 7 [8-13]
    GX_XF_MTXIDX1_TEX7_ST  = 8,
    GX_XF_MTXIDX1_TEX7_END = 13,
} GXXFMtxIdx1;

// XF locators for textures.
typedef enum _GXXFTex {
    // Projection type [30-30]
    GX_XF_TEX_PROJTYPE_ST  = 30,
    GX_XF_TEX_PROJTYPE_END = 30,

    // Input format [29-29]
    GX_XF_TEX_INPUTFORM_ST  = 29,
    GX_XF_TEX_INPUTFORM_END = 29,

    // Texture gen type [25-27]
    GX_XF_TEX_TEXGENTYPE_ST  = 25,
    GX_XF_TEX_TEXGENTYPE_END = 27,

    // Source row [20-24]
    GX_XF_TEX_SRCROW_ST  = 20,
    GX_XF_TEX_SRCROW_END = 24,

    // Bump source texture [17-19]
    GX_XF_TEX_BUMPSRCTEX_ST  = 17,
    GX_XF_TEX_BUMPSRCTEX_END = 19,

    // Bump source light [14-16]
    GX_XF_TEX_BUMPSRCLIGHT_ST  = 14,
    GX_XF_TEX_BUMPSRCLIGHT_END = 16,
} GXXFTex;

// XF locators for dual textures.
typedef enum _GXXFDualTex {
    // Base row of the transform matrix [26-31]
    GX_XF_DUALTEX_BASEROW_ST  = 26,
    GX_XF_DUALTEX_BASEROW_END = 31,

    // Normalise texcoord before sending transform [23-23]
    GX_XF_DUALTEX_NORMALISE_ST  = 23,
    GX_XF_DUALTEX_NORMALISE_END = 23,
} GXXFDualTex;


/* Command FIFO register loads */

#define __GX_FIFO_SET_LOAD_INDX_DST(reg, x)   ((reg) = GX_BITFIELD_SET(reg, 20, 12, x))
#define __GX_FIFO_SET_LOAD_INDX_NELEM(reg, x) ((reg) = GX_BITFIELD_SET(reg, 16, 4, x))
#define __GX_FIFO_SET_LOAD_INDX_INDEX(reg, x) ((reg) = GX_BITFIELD_SET(reg, 0, 16, x))

#define __GX_FIFO_LOAD_INDX(reg, dst, nelem, index) \
    {                                               \
        u32 cmd = 0;                                \
        __GX_FIFO_SET_LOAD_INDX_DST(cmd, dst);      \
        __GX_FIFO_SET_LOAD_INDX_NELEM(cmd, nelem);  \
        __GX_FIFO_SET_LOAD_INDX_INDEX(cmd, index);  \
        GXWGFifo.s8  = reg;                         \
        GXWGFifo.s32 = cmd;                         \
    }

#define GX_FIFO_LOAD_INDX_A(dst, nelem, index) __GX_FIFO_LOAD_INDX(GX_FIFO_CMD_LOAD_INDX_A, dst, nelem, index)
#define GX_FIFO_LOAD_INDX_B(dst, nelem, index) __GX_FIFO_LOAD_INDX(GX_FIFO_CMD_LOAD_INDX_B, dst, nelem, index)
#define GX_FIFO_LOAD_INDX_C(dst, nelem, index) __GX_FIFO_LOAD_INDX(GX_FIFO_CMD_LOAD_INDX_C, dst, nelem, index)
#define GX_FIFO_LOAD_INDX_D(dst, nelem, index) __GX_FIFO_LOAD_INDX(GX_FIFO_CMD_LOAD_INDX_D, dst, nelem, index)

#define GX_BP_LOAD_REG(data)                \
    GXWGFifo.s8  = GX_FIFO_CMD_LOAD_BP_REG; \
    GXWGFifo.s32 = (data);

#define GX_BP_SET_OPCODE(cmd, opcode) (cmd) = GX_BITFIELD_SET(cmd, 0, 8, (opcode))

#define GX_CP_LOAD_REG(addr, data)          \
    GXWGFifo.s8  = GX_FIFO_CMD_LOAD_CP_REG; \
    GXWGFifo.s8  = (addr);                  \
    GXWGFifo.s32 = (data);

#define GX_XF_LOAD_REG_HDR(addr)            \
    GXWGFifo.s8  = GX_FIFO_CMD_LOAD_XF_REG; \
    GXWGFifo.s32 = (addr);

#define GX_XF_LOAD_REG(addr, data) \
    GX_XF_LOAD_REG_HDR(addr);      \
    GXWGFifo.s32 = (data);

#define GX_XF_LOAD_REGS(size, addr)    \
    {                                  \
        u32 cmd = (size) << 16 | addr; \
        GX_XF_LOAD_REG_HDR(cmd);       \
    }

/* GX state */

typedef struct _GXData {
    // Bypass and vertex info
    u16 vNumNot;   // _000
    u16 bpSentNot; // _002
    u16 vNum;      // _004
    u16 vLim;      // _006

    // Command processor (CP) regs
    u32 cpEnable; // _008
    u32 cpStatus; // _00C
    u32 cpClr;    // _010
    u32 vcdLo;    // _014
    u32 vcdHi;    // _018
    u32 vatA[8];  // _01C
    u32 vatB[8];  // _03C
    u32 vatC[8];  // _05C
    u32 lpSize;   // _07C
    u32 matIdxA;  // _080
    u32 matIdxB;  // _084

    // Index loading base/stride regs (pos, nrm, tex, light)
    u32 indexBase[4];   // _088
    u32 indexStride[4]; // _098

    // Transform and lighting regs
    u32 ambColor[2]; // _0A8
    u32 matColor[2]; // _0B0

    // Setup regs
    u32 suTs0[8]; // _0B8
    u32 suTs1[8]; // _0D8
    u32 suScis0;  // _0F8
    u32 suScis1;  // _0FC

    // Raster regs
    u32 tref[8]; // _100
    u32 iref;    // _120

    // Bump/Indirect texture regs
    u32 bpMask;       // _124
    u32 IndTexScale0; // _128
    u32 IndTexScale1; // _12C

    // Tev regs
    u32 tevc[16];   // _130
    u32 teva[16];   // _170
    u32 tevKsel[8]; // _1B0

    // Pixel engine regs
    u32 cmode0; // _1D0
    u32 cmode1; // _1D4
    u32 zmode;  // _1D8
    u32 peCtrl; // _1DC

    // Display copy regs
    u32 cpDispSrc;    // _1E0
    u32 cpDispSize;   // _1E4
    u32 cpDispStride; // _1E8
    u32 cpDisp;       // _1EC

    // Texture copy regs
    u32 cpTexSrc;    // _1F0
    u32 cpTexSize;   // _1F4
    u32 cpTexStride; // _1F8
    u32 cpTex;       // _1FC
    GXBool cpTexZ;   // _200

    // General raster mode
    u32 genMode; // _204

    // Texture regions
    GXTexRegion TexRegions0[GX_MAX_TEXMAP]; // _208
    GXTexRegion TexRegions1[GX_MAX_TEXMAP]; // _288
    GXTexRegion TexRegions2[GX_MAX_TEXMAP]; // _308

    // Texture lookup table regions
    GXTlutRegion TlutRegions[GX_MAX_TLUT_ALL]; // _388
    GXTexRegionCallback texRegionCallback;   // _4C8
    GXTlutRegionCallback tlutRegionCallback; // _4CC

    // Command processor vars
    GXAttrType nrmType; // _4D0
    GXBool hasNrms;     // _4D4
    GXBool hasBiNrms;   // _4D5
    u32 projType;       // _4D8
    f32 projMtx[6];     // _4DC

    // Viewport parms
    f32 vpLeft;  // _4F4
    f32 vpTop;   // _4F8
    f32 vpWd;    // _4FC
    f32 vpHt;    // _500
    f32 vpNearz; // _504
    f32 vpFarz;  // _508
    f32 zOffset; // _50C
    f32 zScale;  // _510

    // Texture regs
    u32 tImage0[8];   // _514
    u32 tMode0[8];    // _534
    u32 texmapId[16]; // _554
    u32 tcsManEnab;   // _594
    u32 tevTcEnab;    // _598

    // Performance metrics
    GXPerf0 perf0; // _59C
    GXPerf1 perf1; // _5A0
    u32 perfSel;   // _5A4

    // Flags
    GXBool inDispList;    // _5A8
    GXBool dlSaveContext; // _5A9
    GXBool abtWaitPECopy; // _5AA
    u8 dirtyVAT;          // _5AB
    u32 dirtyState;       // _5AC
} GXData; // size 0x5B0

extern GXData* const __GXData;

#define gx __GXData

/* Memory-mapped register access */

#define GX_CP_ADDR  (0x0C000000)
#define GX_PE_ADDR  (0x0C001000)
#define GX_PI_ADDR  (0x0C003000)
#define GX_MEM_ADDR (0x0C004000)

#undef GX_GET_CP_REG
#undef GX_SET_CP_REG

#define GX_GET_MEM_REG(offset) (*(volatile u16*)((volatile u16*)(__memReg) + (offset)))
#define GX_GET_CP_REG(offset)  (*(volatile u16*)((volatile u16*)(__cpReg) + (offset)))
#define GX_GET_PE_REG(offset)  (*(volatile u16*)((volatile u16*)(__peReg) + (offset)))
#define GX_GET_PI_REG(offset)  (*(volatile u32*)((volatile u32*)(__piReg) + (offset)))

#define GX_SET_MEM_REG(offset, val) (*(volatile u16*)((volatile u16*)(__memReg) + (offset)) = val)
#define GX_SET_CP_REG(offset, val)  (*(volatile u16*)((volatile u16*)(__cpReg) + (offset)) = val)
#define GX_SET_PE_REG(offset, val)  (*(volatile u16*)((volatile u16*)(__peReg) + (offset)) = val)
#define GX_SET_PI_REG(offset, val)  (*(volatile u32*)((volatile u32*)(__piReg) + (offset)) = val)

static inline u32 GXReadMEMReg(u32 addrLo, u32 addrHi)
{
    u32 hiStart, hiNew, lo;
    hiStart = GX_GET_MEM_REG(addrHi);
    do {
        hiNew   = hiStart;
        lo      = GX_GET_MEM_REG(addrLo);
        hiStart = GX_GET_MEM_REG(addrHi);
    } while (hiStart != hiNew);

    return ((hiStart << 16) | lo);
}

static inline u32 GXReadCPReg(u32 addrLo, u32 addrHi)
{
    u32 hiStart, hiNew, lo;
    hiStart = GX_GET_CP_REG(addrHi);
    do {
        hiNew   = hiStart;
        lo      = GX_GET_CP_REG(addrLo);
        hiStart = GX_GET_CP_REG(addrHi);
    } while (hiStart != hiNew);

    return ((hiStart << 16) | lo);
}

static inline u32 GXReadPEReg(u32 addrLo, u32 addrHi)
{
    u32 hiStart, hiNew, lo;
    hiStart = GX_GET_PE_REG(addrHi);
    do {
        hiNew   = hiStart;
        lo      = GX_GET_PE_REG(addrLo);
        hiStart = GX_GET_PE_REG(addrHi);
    } while (hiStart != hiNew);

    return ((hiStart << 16) | lo);
}

static inline u32 GXReadPIReg(u32 addrLo, u32 addrHi)
{
    u32 hiStart, hiNew, lo;
    hiStart = GX_GET_PI_REG(addrHi);
    do {
        hiNew   = hiStart;
        lo      = GX_GET_PI_REG(addrLo);
        hiStart = GX_GET_PI_REG(addrHi);
    } while (hiStart != hiNew);

    return ((hiStart << 16) | lo);
}

#define GX_CHECK_FLUSH() (!(*(u32*)(&gx->vNumNot)))

/* Public functions missing from the shared headers */

void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, const GXVtxAttrFmtList* list);
void GXSetDispCopyFrame2Field(GXCopyMode mode);
void GXClearBoundingBox(void);
void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1);
void GXClearGPMetric(void);
void GXLoadTexObjPreLoaded(GXTexObj* obj, GXTexRegion* region, GXTexMapID id);
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback f);
void GXSetProjectionv(const f32* ptr);

/* GXAttr.c */

void __GXSetVCD(void);
void __GXCalculateVLim(void);
void __GXSetVAT(void);

/* GXBump.c */

void __GXUpdateBPMask(void);
void __GXFlushTextureState(void);
void __GXSetIndirectMask(u32 mask);

/* GXFifo.c */

void __GXSaveCPUFifoAux(GXFifoObj* fifo);
void __GXFifoInit(void);
void __GXFifoReadEnable(void);
void __GXFifoReadDisable(void);
void __GXFifoLink(u8 link);
void __GXWriteFifoIntEnable(u32 p1, u32 p2);
void __GXWriteFifoIntReset(u32 p1, u32 p2);
void __GXCleanGPFifo(void);

/* GXGeometry.c */

void __GXSetDirtyState(void);
void __GXSendFlushPrim(void);
void __GXSetGenMode(void);

/* GXInit.c */

void __GXInitGX(void);

/* GXMisc.c */

void __GXAbort(void);
void __GXPEInit(void);

/* GXTexture.c */

void __GetImageTileCount(GXTexFmt fmt, u16 wd, u16 ht, u32* rowTiles, u32* colTiles, u32* cmpTiles);
void __SetSURegs(u32 texImgIndex, u32 setUpRegIndex);
void __GXSetSUTexRegs(void);
void __GXSetTmemConfig(u32 config);

/* GXTransform.c */

void __GXSetMatrixIndex(GXAttr matIdxAttr);
void __GXSetProjection(void);
void __GXSetViewport(void);

/* vi.c */

u32 VIGetTvFormat(void);

/* GXStubs.c */

void __GXSetRange(f32 nearz, f32 fgSideX);

#ifdef __cplusplus
}
#endif

#endif
