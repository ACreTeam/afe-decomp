#include "jaudio_NES/driver.h"

#include "PR/abi.h"
#include "jaudio_NES/audiocommon.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/astest.h"
#include "jaudio_NES/audiowork.h"
#include "jaudio_NES/track.h"
#include "jaudio_NES/system.h"
#include "os/OSCache.h"
#include "types.h"

#define DMEM_TEMP 0x380
#define DMEM_WET_TEMP 0x3A0
#define DMEM_COMB_TEMP 0x720
#define DMEM_LEFT_CH 0x900
#define DMEM_RIGHT_CH 0xAA0
#define DMEM_WET_LEFT_CH 0xC40
#define DMEM_WET_RIGHT_CH 0xDE0
#define DMEM_UNCOMPRESSED_NOTE 0x540
#define DMEM_COMPRESSED_ADPCM_DATA 0x900
#define DMEM_HAAS_TEMP 0x580
#define DMEM_SURROUND_TEMP 0x480

typedef enum {
    /* 0 */ HAAS_EFFECT_DELAY_NONE,
    /* 1 */ HAAS_EFFECT_DELAY_LEFT, // Delay left channel so that right channel is heard first
    /* 2 */ HAAS_EFFECT_DELAY_RIGHT // Delay right channel so that left channel is heard first
} HaasEffectDelaySide;

static u16 NOISE_TABLE[] = { 0, 1, 2, 4, 8, 12, 16, 20, 24, 32, 36, 40, 46, 52, 56, 64 };
static dspch_ DSPCH[64];
static s32 STOP_VELOCONV = 0;

static u32 Env_DataH = (A_CMD_ENVMIXER << 24) | (0x00 << 16) | (0x00 << 8) | (0x00);
static u32 Env_Data_L1 = 0x58AAC4DE;
static u32 Env_Data_L2 = 0x9058C4DE;
static u32 Env_Data_L3 = 0x90AAC4DE;

static Acmd* __LoadAuxBuf(Acmd* cmd, u16 ofs, u16 startPos, s32 size, delay* del_p);
static Acmd* __SaveAuxBuf(Acmd* cmd, u16 ofs, u16 startPos, s32 size, delay* del_p);
static Acmd* Nas_SaveBufferAuto(Acmd* cmd, u16 ofs, u16 size, s32 startAddr);

#include "../src/static/jaudio_PP/internal/driver_cpufx.c_inc"
#include "../src/static/jaudio_PP/internal/driver_synth.c_inc"
