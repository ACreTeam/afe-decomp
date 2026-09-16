#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 kai_sousa_button3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/kai_sousa_button3/kai_sousa_button3_tex.inc"
};

Vtx pas_start_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/kai_sousa_button3/pas_start_v.inc"
};

Gfx pas_start_yaji_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
gsDPSetPrimColor(0, 255, 205, 0, 0, 255),
gsSPVertex(pas_start_v, 7, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPEndDisplayList(),
};

Gfx pas_start_buttonT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 235, 235, 235, 255),
gsDPSetEnvColor(70, 70, 70, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, kai_sousa_button3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&pas_start_v[7], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx pas_start_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(pas_start_yaji_model),
gsSPDisplayList(pas_start_buttonT_model),
gsSPEndDisplayList(),
};
