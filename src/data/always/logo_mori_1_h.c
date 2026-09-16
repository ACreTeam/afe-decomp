#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

static u8 logo_back_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_mori_1_h/logo_back_tex.inc"
};

static u8 logo_mori_1_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_mori_1_h/logo_mori_1_h_tex.inc"
};

static u8 logo_mori_2_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_mori_1_h/logo_mori_2_h_tex.inc"
};

Vtx logo_mori_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/logo_mori_1_h/logo_mori_v.inc"
};

Gfx logo_back_moriT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, logo_back_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(logo_mori_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx logo_type_moriT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 80, 48, logo_mori_2_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&logo_mori_v[4], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 80, 48, logo_mori_1_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
gsSPEndDisplayList(),
};
