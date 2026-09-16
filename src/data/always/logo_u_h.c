#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 logo_u_h_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_u_h/logo_u_h_tex.inc"
};

static u8 logo_back_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/logo_u_h/logo_back_tex.inc"
};

Vtx logo_u_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/logo_u_h/logo_u_v.inc"
};

Gfx logo_back_uT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, logo_back_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(logo_u_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx logo_type_uT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, logo_u_h_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&logo_u_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
