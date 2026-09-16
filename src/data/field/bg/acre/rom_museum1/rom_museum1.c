#include "libforest/gbi_extensions.h"


static u16 rom_museum1_mado_pal[] = {
#include "assets/field/bg/rom_museum1_mado_pal.inc"
};

static u16 rom_museum1_step_pal[] = {
#include "assets/field/bg/rom_museum1_step_pal.inc"
};

static u16 rom_museum1_floor_pal[] = {
#include "assets/field/bg/rom_museum1_floor_pal.inc"
};

static u16 rom_museum1_wall_pal[] = {
#include "assets/field/bg/rom_museum1_wall_pal.inc"
};

static u8 rom_museum1_mado1_tex[] = {
#include "assets/field/bg/rom_museum1_mado1_tex.inc"
};

static u8 rom_museum1_step1_tex[] = {
#include "assets/field/bg/rom_museum1_step1_tex.inc"
};

static u8 rom_museum1_step2_tex[] = {
#include "assets/field/bg/rom_museum1_step2_tex.inc"
};

static u8 rom_museum1_floorA_tex[] = {
#include "assets/field/bg/rom_museum1_floorA_tex.inc"
};

static u8 rom_museum1_floorB_tex[] = {
#include "assets/field/bg/rom_museum1_floorB_tex.inc"
};

static u8 rom_museum1_mado2_tex[] = {
#include "assets/field/bg/rom_museum1_mado2_tex.inc"
};

static u8 rom_museum1_sign1_tex[] = {
#include "assets/field/bg/rom_museum1_sign1_tex.inc"
};

static u8 rom_museum1_wallA_tex[] = {
#include "assets/field/bg/rom_museum1_wallA_tex.inc"
};

static u8 rom_museum1_wallB_tex[] = {
#include "assets/field/bg/rom_museum1_wallB_tex.inc"
};

static u8 rom_museum1_sign2_tex[] = {
#include "assets/field/bg/rom_museum1_sign2_tex.inc"
};

static u8 rom_museum1_sign3_tex[] = {
#include "assets/field/bg/rom_museum1_sign3_tex.inc"
};

static u8 rom_museum1_sign4_tex[] = {
#include "assets/field/bg/rom_museum1_sign4_tex.inc"
};

static Vtx rom_museum1_v[] = {
#include "assets/field/bg/rom_museum1_v.inc"
};

extern Gfx rom_museum1_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 1, 0, PRIM_LOD_FRAC, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_mado_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_mado2_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_museum1_v[268], 16, 0),
    gsDPNoOpTag(0x0003DAB0),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_mado1_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[284], 16, 0),
    gsDPNoOpTag(0x00031EB0),
    gsSPEndDisplayList(),
};

extern Gfx rom_museum1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_museum1_v[0], 16, 0),
    gsDPNoOpTag(0x0003DCC0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_step_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_sign4_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[16], 20, 0),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_sign3_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_sign2_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_sign1_tex, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_step2_tex, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&rom_museum1_v[36], 27, 0),
    gsDPNoOpTag(0x349CE510),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_step1_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_wall_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_wallA_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[63], 32, 0),
    gsDPNoOpTag(0x0007BBC0),
    gsSPVertex(&rom_museum1_v[94], 18, 0),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_wallB_tex, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[112], 32, 0),
    gsDPLoadSync(),
    gsDPNoOpTag(0xDCEF35D0),
    gsSPVertex(&rom_museum1_v[143], 32, 0),
    gsDPNoOpTag(0x0007FDD0),
    gsSPVertex(&rom_museum1_v[175], 8, 0),
    gsDPNoOpTag(0xA4314640),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum1_floor_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_floorB_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[183], 32, 0),
    gsSPDmaRead(0x1C50, 0xD5A4A700, 0x0C57),
    gsDPNoOpTag(0x00033EE0),
    gsSPVertex(&rom_museum1_v[215], 10, 0),
    gsDPNoOpTag(0x00021270),
    gsDPLoadTextureBlock_4b_Dolphin(rom_museum1_floorA_tex, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_museum1_v[225], 27, 0),
    gsDPNoOpTag(0x0003DB10),
    gsSPVertex(&rom_museum1_v[252], 16, 0),
    gsDPNoOpTag(0x0003DCD0),
    gsSPEndDisplayList(),
};
