#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 int_ike_kani_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_kani_body2_00222A60/int_ike_kani_pal.inc"
};

static u8 act_mus_kani_body2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_kani_body2_00222A60/act_mus_kani_body2.inc"
};

static u8 act_mus_kani_body1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_kani_body2_00222A60/act_mus_kani_body1.inc"
};

static Vtx act_m_kani_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/act_mus_kani_body2_00222A60/act_m_kani_v.inc"
};

Gfx act_m_kani1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_kani_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_kani_body1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_m_kani_v, 21, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 0, 4, 5),
gsSPNTriangles_5b(0, 5, 1, 6, 0, 7, 6, 4, 0, 8, 5, 4),
gsSPNTriangles_5b(8, 4, 6, 9, 1, 8, 10, 2, 1, 10, 1, 9),
gsSPNTriangles_5b(11, 3, 2, 11, 2, 10, 7, 0, 3, 7, 3, 11),
gsSPNTriangles_5b(1, 5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_kani_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(8, 12, 13, 14, 13, 15, 14, 16, 13, 17),
gsSPNTriangles_5b(13, 12, 17, 13, 18, 19, 13, 19, 15, 16, 20, 18),
gsSPNTriangles_5b(16, 18, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_m_kani2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_kani_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_kani_body1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_kani_v[21], 21, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 3, 2, 4),
gsSPNTriangles_5b(3, 4, 5, 5, 4, 6, 5, 6, 7, 7, 6, 8),
gsSPNTriangles_5b(6, 9, 8, 8, 9, 10, 8, 10, 11, 11, 1, 0),
gsSPNTriangles_5b(11, 10, 1, 1, 6, 4, 1, 4, 2, 1, 10, 9),
gsSPNTriangles_5b(1, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_mus_kani_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(8, 12, 13, 14, 12, 14, 15, 15, 14, 16),
gsSPNTriangles_5b(15, 16, 17, 15, 18, 19, 12, 15, 19, 15, 17, 20),
gsSPNTriangles_5b(18, 15, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
