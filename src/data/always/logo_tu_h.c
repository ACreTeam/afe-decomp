#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

static u8 logo_back_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_tu_h/logo_back_tex.inc"
};

u8 logo_tu_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_tu_h/logo_tu_h_tex.inc"
};

Vtx logo_tu_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/logo_tu_h/logo_tu_v.inc"
};

Gfx logo_back_tuT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, logo_back_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(logo_tu_v, 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPEndDisplayList(),
};

Gfx logo_type_tuT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, logo_tu_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&logo_tu_v[5], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
