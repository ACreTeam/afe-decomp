#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 ut_mike[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ut_mike/ut_mike.inc"
};

u8 utPal_mike[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ut_mike/utPal_mike.inc"
};

u8 ut_mouth[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ut_mike/ut_mouth.inc"
};

u8 utPal_mouth[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ut_mike/utPal_mouth.inc"
};

Vtx ef_ongen_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ut_mike/ef_ongen_v.inc"
};

Gfx ef_ongen_mic_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, utPal_mike),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ut_mike),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(ef_ongen_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};

Gfx ef_ongen_mouth_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, utPal_mouth),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ut_mouth),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(ef_ongen_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
gsSPEndDisplayList(),
};
