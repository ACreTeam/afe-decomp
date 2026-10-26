#include "jaudio_NES/emusound.hpp"
#include "dolphin/os.h"
#include "jaudio_NES/aictrl.h"
#include "jaudio_NES/sample.h"

#define NES_CLOCK_SPEED 1789773

#define artificial_padding(lastOffset, currentOffset, typeOfLastMember) \
    u8 __##currentOffset##padding[currentOffset - lastOffset - sizeof(typeOfLastMember)]

typedef struct _NESSoundStruct2 {
    u8 _00;
    // bad padding
    union {
        u32 _04;
        struct {
            u16 _04_hi;
            u16 _04_lo;
        } _04p;
    };
    u32 _08;
    u32 _0C;
    u32 _10;
    u32 _14;
    u16 _18;
    u16 _1A;
    u8 _1C;
    u8 _1D;
    s16 _1E;
    u8 _20;
    u8 _21;
    u8 _22;
    u8 _23;
} NESSoundStruct2;

typedef struct _NESSoundStruct3 {
    u8 _00;
    u32 _04;
    artificial_padding(0x4, 0xd, u32);
    u8 _0D;
    u16 _0E;
    artificial_padding(0xe, 0x18, u16);
} NESSoundStruct3;

typedef struct _NESSoundStruct {
    u8 _00;
    // bad padding
    union {
        u32 _04;
        struct {
            u16 _04_hi;
            u16 _04_lo;
        } _04p;
    };
    u32 _08;
    u16 _0C;
    u16 _0E;
    u32 _10;
    u32 _14;
    u32 _18;
    u8 _1C;
    u8 _1D;
    // bad padding
    u32 _20;
    u32 _24;
    u8 _28;
    // bad padding
    u16 _2A;
    u16 _2C;
    // bad padding
    u32 _30;
    u32 _34;
    u8 _38;
    u8 _39;
    u8 _3A;
    u8 _3B;
    u8 _3C;
    // bad padding
    u16 _3E;
    u16 _40;
    u16 _42;
    u8 _44;
    artificial_padding(0x44, 0x47, u8);
    u8 _47;
    u16 _48;
    u8 _4A;
    // bad padding
} NESSoundStruct; // size 0x48

typedef struct _NESSoundStructF {
    u8 _00;
    // bad padding
    union {
        u32 _04;
        struct {
            u16 _04_hi;
            u16 _04_lo;
        } _04p;
    };
    u32 _08;
    u32 _0C;
    u32 _10;
    u16 _14;
    u16 _16;
    u32 _18;
    u16 _1C;
    // bad padding
    u32 _20;
    u32 _24;
    u32 _28;
    u8 _2C;
    u8 _2D;
    u8 _2E;
    u8 _2F;
    // bad padding
    u32 _30;
    u32 _34;
    u8 _38;
    u8 _39;
    u8 _3A;
    u8 _3B;
    u16 _3C;
    // bad padding
    u16 _3E;
    u16 _40;
    u8 _42;
    u8 _43;
    s8 _44;
    u8 _45;
    u8 _46;
    u8 _47;
    u8 _48;
    u8 _49;
    u8 _4A;
    // bad padding
} NESSoundStructF; // size 0x48

// bss
u8 PCMH2[16];
NESSoundStruct SoundA, SoundB, SoundC, SoundD;
NESSoundStruct2 SoundE;
NESSoundStruct SoundX, SoundY, SoundZ;
NESSoundStruct SoundM, SoundN;
NESSoundStructF SoundF;
NESSoundStruct3 SoundP;

u8 DUMMY_ACTIVE[9];

// sbss
u8 beforemode;
u8 move_to_50;
u8 MMC_MODE;
u8* NOISE_DTABLE;
u32 PHASE_SYNC_FLAG;
u32 FRAME_SYNC_FLAG;
u32 PHASE_SYNC_COUNTER;
u32 FRAME_SYNC_COUNTER;
s8 NOISE_PULSE;

// data

// UNUSED
u8 LEN_TABLE[] = { 0x05, 0x7e, 0x0a, 0x01, 0x13, 0x02, 0x28, 0x03, 0x50,  0x04, 0x1e, 0x05, 0x07, 0x06, 0x0d, 0x07,
                   0x06, 0x08, 0x0c, 0x09, 0x18, 0x0a, 0x30, 0x0b, 0x060, 0x0c, 0x24, 0x0d, 0x08, 0x0e, 0x10, 0x0f };

// UNUSED
f32 NOISE_FREQ_TABLE[] = { 4.f,  2.f,   1.f,   0.5f,  0.25f, 0.2f,  0.15f, 0.12f,
                           0.1f, 0.08f, 0.07f, 0.06f, 0.05f, 0.04f, 0.03f, 0.03f };

// https://www.nesdev.org/wiki/APU_registers

typedef struct _PulseChannel {
    // https://www.nesdev.org/wiki/APU_Pulse
    // $4000/$4004
    u8 Duty : 2;
    u8 EnvelopeLoopCounter : 1;
    u8 ConstantVolume : 1;
    u8 EnvelopePeriod_Volume : 4;
    // $4001/$4005
    u8 SweepUnitEnabled : 1;
    u8 SweepUnitPeriod : 3;
    u8 SweepUnitNegative : 1;
    u8 SweepUnitShiftCount : 3;
    // $4002/$4006
    u8 TimerLow : 8;
    // $4003/$4007
    u8 LengthCounterLow : 5;
    u8 TimerHigh : 3;
} PulseChannel;

typedef struct _TriangleChannel {
    // https://www.nesdev.org/wiki/APU_Triangle
    // $4008
    u8 LengthCounter : 1;
    u8 LinearCounterReloadVaue : 7;
    // $4009
    u8 _unused_4009 : 8;
    // $400A
    u8 TimerLow : 8;
    // $400B
    u8 LengthCounterLoad : 5;
    u8 TimerHigh : 3;
} TriangleChannel;

typedef struct _NoiseChannel {
    // https://www.nesdev.org/wiki/APU_Noise
    // $400C
    u8 _unused_400C_high2 : 2;
    u8 LoopEnvelope : 1;
    u8 ConstantVolume : 1;
    u8 EnvelopePeriod_Volume : 4;
    // $400D
    u8 _unused_400D : 8;
    // $400E
    u8 LoopNoise : 1;
    u8 _unused_400E_3bits : 3;
    u8 Period : 4;
    // $400F
    u8 LengthCounterLoad : 5;
    u8 _unused_400F_low3 : 3;
} NoiseChannel;

typedef struct _DMCChannel {
    // https://www.nesdev.org/wiki/APU_DMC
    // $4010
    u8 IRQEnable : 1;
    u8 LoopSample : 1;
    u8 _unused_4010_middle2 : 2;
    u8 FrequencyIndex : 4;
    // $4011
    u8 _unused_4011_heigh : 1;
    u8 DirectLoad : 7;
    // $4012
    u8 SampleAddress : 8;
    // $4013
    u8 SampleLength : 8;
} DMCChannel;

typedef struct _WaveTableEntry {
    u8 Read : 2;
    u8 Sample : 6;
} WaveTableEntry;

typedef struct _unknown_C0 {
    u8 _0_7 : 1; // 10000000
    u8 _0_6 : 3; // 01100000
    u8 _0_3 : 4; // 00001111
    u8 _1;
    u8 _2;
    u8 _3_7 : 1; // 10000000
    u8 _3_6 : 3; // 01110000
    u8 _3_3 : 4; // 00001111
} Unknown_VRC;

typedef struct _APURegisters {
    // $4000
    PulseChannel Pulse1;
    // $4004
    PulseChannel Pulse2;
    // $4008
    TriangleChannel Triangle;
    // $400C
    NoiseChannel Noise;
    // $4010
    DMCChannel DMC;
    // $4014
    u8 _unused_4014;
    // https://www.nesdev.org/wiki/APU#Status_($4015)
    // $4015
    u8 DMCInterrupt : 1;
    u8 FrameInterrupt : 1;
    u8 _unused_4015_1bit : 1;
    u8 LengthCounterStatus : 1;
    u8 NoiseStatus : 1;
    u8 TriangleStatus : 1;
    u8 Pulse2Status : 1;
    u8 Pulse1Status : 1;
    // $4016
    u8 _unused_4016;
    // https://www.nesdev.org/wiki/APU#Frame_Counter_($4017)
    // $4017
    u8 FrameCounter_5FrameSequence : 1;
    u8 FrameCounter_DisableFrameInterrupt : 1;
    u8 _unused_4017_low : 6;

    artificial_padding(0x17, 0x40, u8);
    // $4040 - $4079 https://www.nesdev.org/wiki/FDS_audio#Wavetable_RAM_($4040-$407F)
    WaveTableEntry WaveTable[0x40];
    // $4080 https://www.nesdev.org/wiki/FDS_audio#Volume_envelope_($4080)
    u8 VolumeEnvelopeEnabled : 1;
    u8 VolumeEnvelopeIncreasing : 1;
    u8 VolumeEnvelopeGainAndSpeed : 6;
    // $4081
    u8 _unused_4081;
    // $4082 https://www.nesdev.org/wiki/FDS_audio#Frequency_low_($4082)
    u8 FrequencyLow;
    // $4083 https://www.nesdev.org/wiki/FDS_audio#Frequency_high_($4083)
    u8 HighSpeedFrequency : 1;
    u8 DisableSweepAndEnvelope : 1;
    u8 _unused_4083_midbits : 2;
    u8 FrequencyHigh : 4;
    // $4084 https://www.nesdev.org/wiki/FDS_audio#Mod_envelope_($4084)
    u8 ModEnvelopeEnabled : 1;
    u8 ModEnvelopeIncreasing : 1;
    u8 ModEnvelopeGainAndSpeed : 6;
    // $4085 https://www.nesdev.org/wiki/FDS_audio#Mod_counter_($4085)
    u8 _unused_4085_high : 1;
    u8 ModCounter : 7;
    // $4086 https://www.nesdev.org/wiki/FDS_audio#Mod_frequency_low_($4086)
    u8 ModFrequencyLow;
    // $4087 https://www.nesdev.org/wiki/FDS_audio#Mod_frequency_high_($4087)
    u8 HaltModTableCounter : 1;
    u8 ForceAccumulatorStepOut : 1;
    u8 _unused_4087_mid : 2;
    u8 ModFrequencyHigh : 4;
    // $4088 https://www.nesdev.org/wiki/FDS_audio#Mod_table_write_($4088)
    // unused in the following code
    u8 _unused_4088_high : 5;
    u8 ModulationTableWrite : 3;
    // $4089 https://www.nesdev.org/wiki/FDS_audio#Wave_write_/_master_volume_($4089)
    u8 WaveTableWriteEnable : 1;
    u8 _unused_4089_midbits : 5;
    u8 WaveTableMasterVolume : 2;
    // $408A https://www.nesdev.org/wiki/FDS_audio#Envelope_speed_($408A)
    u8 EnvelopeSpeed;

    artificial_padding(0x8a, 0xc0, u8);

    Unknown_VRC _C0;
    Unknown_VRC _C4;
    Unknown_VRC _C8;
    artificial_padding(0xc8, 0xd5, Unknown_VRC);
    u8 _unused_D5_high : 5;
    u8 _D5_2 : 1;
    u8 _D5_1 : 1;
    u8 _D5_0 : 1;

} APURegisters;

typedef union _sbufferStruct {
    APURegisters apu;
    u8 buff[0x4100 - 0x4000];
} sbufferStruct;

sbufferStruct sbuffer = { 0 };

u8 LEN_TABLE_HVC[] = { 0x05, 0x7e, 0x0a, 0x01, 0x13, 0x02, 0x28, 0x03, 0x50, 0x04, 0x1e, 0x05, 0x07, 0x06, 0x0d, 0x07,
                       0x06, 0x08, 0x0c, 0x09, 0x18, 0x0a, 0x30, 0x0b, 0x60, 0x0c, 0x24, 0x0d, 0x08, 0x0e, 0x10, 0x0f };

s8 TRIANGLE_TABLE[] = {
    0x00, 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x78, 0x69, 0x5a, 0x4b, 0x3c, 0x2d, 0x1e,
    0x0f, 0x00, 0xef, 0xde, 0xcd, 0xbb, 0xaa, 0x99, 0x88, 0x88, 0x99, 0xaa, 0xbb, 0xcd, 0xde, 0xef
};

static int NOISE_TABLE[] = { 0x000df86a, 0x0006fc35, 0x00037e1a, 0x0001bf0d, 0x0000df86, 0x00009504,
                             0x00006fc3, 0x00005969, 0x000046d1, 0x00003852, 0x000025a5, 0x00001c29,
                             0x000012c6, 0x00000e14, 0x00000708, 0x000006fd };

u8 NOISE_PULSE_TABLE[] = { 0x30, 0x32, 0x34, 0x38, 0x3c, 0x3d, 0x3e, 0x3f,
                           0x40, 0x42, 0x44, 0x46, 0x48, 0x50, 0x60, 0x60 };

u32 DMOD_TABLE[] = { 0x000010bd, 0x000012db, 0x00001513, 0x00001663, 0x0000190d, 0x00001c36, 0x00001fb4, 0x00002115,
                     0x000025b6, 0x00002cbf, 0x000032a4, 0x000037fb, 0x00004399, 0x00005475, 0x00006385, 0x000084b1 };

// UNUSED
u8 VOLTABLE_DELTAMOD[] = {
    0x00, 0x00, 0x00, 0xff, 0x01, 0xfc, 0x02, 0xf7, 0x03, 0xf0, 0x04, 0xe7, 0x05, 0xdc, 0x06, 0xcf, 0x07, 0xc0, 0x08,
    0xaf, 0x09, 0x9c, 0x0a, 0x87, 0x0b, 0x70, 0x0c, 0x57, 0x0d, 0x3c, 0x0e, 0x1f, 0x0f, 0x00, 0x0f, 0xdf, 0x10, 0xbc,
    0x11, 0x97, 0x12, 0x70, 0x13, 0x47, 0x14, 0x1c, 0x14, 0xef, 0x15, 0xc0, 0x16, 0x8f, 0x17, 0x5c, 0x18, 0x27, 0x18,
    0xf0, 0x19, 0xb7, 0x1a, 0x7c, 0x1b, 0x3f, 0x1c, 0x00, 0x1c, 0xbf, 0x1d, 0x7c, 0x1e, 0x37, 0x1e, 0xf0, 0x1f, 0xa7,
    0x20, 0x5c, 0x21, 0x0f, 0x21, 0xc0, 0x22, 0x6f, 0x23, 0x1c, 0x23, 0xc7, 0x24, 0x70, 0x25, 0x17, 0x25, 0xbc, 0x26,
    0x5f, 0x27, 0x00, 0x27, 0x9f, 0x28, 0x3c, 0x28, 0xd7, 0x29, 0x70, 0x2a, 0x07, 0x2a, 0x9c, 0x2b, 0x2f, 0x2b, 0xc0,
    0x2c, 0x4f, 0x2c, 0xdc, 0x2d, 0x67, 0x2d, 0xf0, 0x2e, 0x77, 0x2e, 0xfc, 0x2f, 0x7f, 0x30, 0x00, 0x30, 0x7f, 0x30,
    0xfc, 0x31, 0x77, 0x31, 0xf0, 0x32, 0x67, 0x32, 0xdc, 0x33, 0x4f, 0x33, 0xc0, 0x34, 0x2f, 0x34, 0x9c, 0x35, 0x07,
    0x35, 0x70, 0x35, 0xd7, 0x36, 0x3c, 0x36, 0x9f, 0x37, 0x00, 0x37, 0x5f, 0x37, 0xbc, 0x38, 0x17, 0x38, 0x70, 0x38,
    0xc7, 0x39, 0x1c, 0x39, 0x6f, 0x39, 0xc0, 0x3a, 0x0f, 0x3a, 0x5c, 0x3a, 0xa7, 0x3a, 0xf0, 0x3b, 0x37, 0x3b, 0x7c,
    0x3b, 0xbf, 0x3c, 0x00, 0x3c, 0x3f, 0x3c, 0x7c, 0x3c, 0xb7, 0x3c, 0xf0, 0x3d, 0x27, 0x3d, 0x5c, 0x3d, 0x8f, 0x3d,
    0xc0, 0x3d, 0xef, 0x3e, 0x1c, 0x3e, 0x47, 0x3e, 0x70, 0x3e, 0x97, 0x3e, 0xbc, 0x3e, 0xdf, 0x3f, 0x00, 0x3f, 0x1f,
    0x3f, 0x3c, 0x3f, 0x57, 0x3f, 0x70, 0x3f, 0x87, 0x3f, 0x9c, 0x3f, 0xaf, 0x3f, 0xc0, 0x3f, 0xcf, 0x3f, 0xdc, 0x3f,
    0xe7, 0x3f, 0xf0, 0x3f, 0xf7, 0x3f, 0xfc, 0x3f, 0xff
};

// UNUSED
u8 VOLTABLE_DISKFM[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10,
                         0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26,
                         0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c };

// UNUSED
u8 VOLTABLE_DISKFM_SUB[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
                             0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                             0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20 };

// UNUSED
u32 DISKFM_GAINTABLE[] = { 30, 20, 15, 12 };
u8 DISKFM_TABLE[0x40];

// UNUSED

u8 DEB1[16] = { 0 };
// sdata
s8 DISK_SUB_GAIN[] = { 0, 1, 2, 4, 0, -4, -2, -1 };
u8* ROM_TOP_C000 = DEB1;
u8* ROM_TOP_E000 = DEB1;
u32 DISK_FRAME_SAMPLE = 0x215;
u32 FRAME_SAMPLE = 0x215;
u32 PHASE_SAMPLE = 0x85;
u32 NOISE_MASTER = 1;
u32 NOISE_SHIFT = 0x800;
int write_pointer = 0x690;
int buffer_remain = 0x690;
u32 _STOP[2] = { 0 };

f32 VOLTABLE_HVCPULSE[] = { 0.0f,      0.080128,  0.157051f, 0.224359f, 0.294872f, 0.365385f,
                            0.435897f, 0.50641f,  0.592949f, 0.657051f, 0.730769f, 0.801282f,
                            0.865385f, 0.929487f, 0.99359f,  1.064103f, 1.064103f };

u8 VOLTABLE_VRCPULSE[] = { 0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14,
                           0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                           0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f };

#include "../src/static/jaudio_PP/game/emusound_vrc.c_inc"
#include "../src/static/jaudio_PP/game/emusound_a.c_inc"
#include "../src/static/jaudio_PP/game/emusound_b.c_inc"
#include "../src/static/jaudio_PP/game/emusound_d.c_inc"
#include "../src/static/jaudio_PP/game/emusound_e.c_inc"
#include "../src/static/jaudio_PP/game/emusound_c.c_inc"
#include "../src/static/jaudio_PP/game/emusound_disk.c_inc"
#include "../src/static/jaudio_PP/game/emusound_event.c_inc"
#include "../src/static/jaudio_PP/game/emusound_hvc.c_inc"
#include "../src/static/jaudio_PP/game/emusound_pcm.c_inc"
