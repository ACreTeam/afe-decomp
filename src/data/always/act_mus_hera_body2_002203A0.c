#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 int_ike_hera_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_hera_body2_002203A0/int_ike_hera_pal.inc"
};

static u8 act_mus_hera_body2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_hera_body2_002203A0/act_mus_hera_body2.inc"
};

static u8 act_mus_hera_body1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_hera_body2_002203A0/act_mus_hera_body1.inc"
};

static u8 act_mus_hera_body3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_hera_body2_002203A0/act_mus_hera_body3.inc"
};

static Vtx act_m_hera_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/act_mus_hera_body2_002203A0/act_m_hera_v.inc"
};

Gfx act_m_hera1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_hera_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_hera_body1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_m_hera_v, 24, 0),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(0, 5, 1, 5, 5, 1, 5, 5, 5, 5, 4, 1),
gsSPNTriangles_5b(6, 0, 7, 6, 5, 0, 8, 5, 6, 8, 5, 5),
gsSPNTriangles_5b(9, 5, 8, 5, 5, 8, 10, 4, 9, 4, 5, 9),
gsSPNTriangles_5b(11, 3, 10, 3, 4, 10, 7, 2, 12, 7, 0, 2),
gsSPNTriangles_5b(12, 13, 14, 12, 2, 13, 13, 15, 14, 2, 3, 16),
gsSPNTriangles_5b(2, 16, 13, 16, 15, 13, 15, 16, 17, 16, 11, 17),
gsSPNTriangles_5b(16, 3, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_hera_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 18, 19, 20, 18, 20, 21, 22, 18, 21),
gsSPNTriangles_5b(22, 21, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_m_hera2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_hera_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_hera_body3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_hera_v[24], 28, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_hera_body1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(28, 4, 5, 6, 5, 7, 6, 5, 8, 7),
gsSPNTriangles_5b(4, 9, 5, 9, 9, 5, 9, 9, 9, 9, 8, 5),
gsSPNTriangles_5b(10, 11, 12, 13, 9, 4, 14, 9, 13, 14, 9, 9),
gsSPNTriangles_5b(15, 9, 14, 9, 9, 14, 16, 17, 18, 8, 9, 15),
gsSPNTriangles_5b(19, 7, 20, 7, 8, 20, 21, 6, 22, 21, 4, 6),
gsSPNTriangles_5b(22, 23, 24, 22, 6, 23, 23, 25, 24, 6, 7, 26),
gsSPNTriangles_5b(6, 26, 23, 26, 25, 23, 25, 26, 27, 26, 19, 27),
gsSPNTriangles_5b(26, 7, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_hera_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&act_m_hera_v[52], 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(4, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
