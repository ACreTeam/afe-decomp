#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 int_ike_yado_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_yado_body_00228E60/int_ike_yado_pal.inc"
};

static u8 act_mus_yado_body[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_yado_body_00228E60/act_mus_yado_body.inc"
};

static u8 act_mus_yado_body2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_yado_body_00228E60/act_mus_yado_body2.inc"
};

static u8 act_mus_yado_body3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_yado_body_00228E60/act_mus_yado_body3.inc"
};

static Vtx act_m_yado_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/act_mus_yado_body_00228E60/act_m_yado_v.inc"
};

Gfx act_m_yado1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_yado_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_yado_body3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_m_yado_v, 22, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 0, 2, 4, 1, 0),
gsSPNTriangles_5b(3, 5, 0, 5, 6, 4, 5, 4, 0, 7, 1, 4),
gsSPNTriangles_5b(6, 7, 4, 7, 8, 1, 8, 9, 1, 9, 10, 1),
gsSPNTriangles_5b(10, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_yado_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(12, 11, 12, 13, 11, 13, 14, 11, 15, 16),
gsSPNTriangles_5b(11, 14, 15, 17, 16, 18, 17, 11, 16, 19, 20, 21),
gsSPNTriangles_5b(19, 17, 18, 19, 18, 20, 19, 11, 17, 12, 19, 21),
gsSPNTriangles_5b(12, 11, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_m_yado2_1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_yado_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_yado_body),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_yado_v[22], 8, 0),
gsSPNTrianglesInit_5b(9, 0, 1, 2, 1, 3, 4, 1, 4, 2),
gsSPNTriangles_5b(3, 5, 4, 1, 6, 3, 3, 6, 5, 6, 7, 5),
gsSPNTriangles_5b(0, 6, 1, 0, 7, 6, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_m_yado2_2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_yado_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_yado_body),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_yado_v[30], 8, 0),
gsSPNTrianglesInit_5b(9, 0, 1, 2, 1, 3, 4, 1, 4, 2),
gsSPNTriangles_5b(3, 5, 4, 1, 6, 3, 3, 6, 5, 6, 7, 5),
gsSPNTriangles_5b(0, 6, 1, 0, 7, 6, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
