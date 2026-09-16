#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 int_ike_gengoro_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_gengoro_body_0021EE00/int_ike_gengoro_pal.inc"
};

static u8 act_mus_gengoro_body[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_gengoro_body_0021EE00/act_mus_gengoro_body.inc"
};

static u8 act_mus_gengoro_body2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_gengoro_body_0021EE00/act_mus_gengoro_body2.inc"
};

static u8 act_mus_gengoro_body3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_gengoro_body_0021EE00/act_mus_gengoro_body3.inc"
};

u8 act_mus_gengoro_body4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_gengoro_body_0021EE00/act_mus_gengoro_body4.inc"
};

static Vtx act_m_gengoro_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/act_mus_gengoro_body_0021EE00/act_m_gengoro_v.inc"
};

Gfx act_m_gengoro1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_gengoro_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_mus_gengoro_body3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_m_gengoro_v, 22, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(4, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_gengoro_body),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(20, 6, 7, 8, 6, 8, 9, 8, 10, 11),
gsSPNTriangles_5b(9, 8, 11, 11, 10, 10, 11, 10, 12, 12, 10, 10),
gsSPNTriangles_5b(12, 10, 13, 13, 10, 14, 13, 14, 15, 16, 17, 17),
gsSPNTriangles_5b(16, 17, 17, 16, 17, 18, 14, 8, 7, 14, 7, 19),
gsSPNTriangles_5b(20, 7, 6, 19, 7, 20, 21, 19, 20, 15, 14, 19),
gsSPNTriangles_5b(15, 19, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_m_gengoro2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_gengoro_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_gengoro_body4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_gengoro_v[22], 26, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_mus_gengoro_body3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 4, 5, 6, 7, 4, 6, 7, 6, 8),
gsSPNTriangles_5b(5, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_gengoro_body),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(20, 10, 11, 11, 10, 11, 12, 13, 14, 10),
gsSPNTriangles_5b(14, 11, 10, 15, 16, 14, 15, 14, 13, 17, 18, 19),
gsSPNTriangles_5b(17, 19, 20, 20, 19, 21, 19, 16, 21, 21, 16, 15),
gsSPNTriangles_5b(18, 14, 16, 18, 16, 19, 22, 23, 23, 22, 23, 23),
gsSPNTriangles_5b(22, 23, 24, 25, 18, 17, 25, 11, 18, 12, 11, 11),
gsSPNTriangles_5b(12, 11, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_m_gengoro3T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_gengoro_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_mus_gengoro_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_gengoro_v[48], 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 0, 3),
gsSPNTriangles_5b(4, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
