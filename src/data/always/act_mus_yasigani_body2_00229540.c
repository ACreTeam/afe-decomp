#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 int_ike_yasigani_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_yasigani_body2_00229540/int_ike_yasigani_pal.inc"
};

static u8 act_mus_yasigani_body2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_yasigani_body2_00229540/act_mus_yasigani_body2.inc"
};

static u8 act_mus_yasigani_body1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_yasigani_body2_00229540/act_mus_yasigani_body1.inc"
};

static Vtx act_m_yasigani_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/act_mus_yasigani_body2_00229540/act_m_yasigani_v.inc"
};

Gfx act_m_yasigani1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_yasigani_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_mus_yasigani_body1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_m_yasigani_v, 32, 0),
gsSPNTrianglesInit_5b(33, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(0, 4, 5, 6, 7, 8, 9, 10, 11, 9, 11, 12),
gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 14, 17, 16, 13, 18, 14),
gsSPNTriangles_5b(18, 19, 14, 19, 17, 14, 20, 18, 13, 20, 13, 21),
gsSPNTriangles_5b(22, 19, 18, 22, 18, 20, 23, 17, 19, 23, 19, 22),
gsSPNTriangles_5b(24, 16, 17, 24, 17, 23, 25, 26, 26, 25, 26, 27),
gsSPNTriangles_5b(21, 13, 15, 21, 15, 28, 15, 25, 28, 15, 26, 25),
gsSPNTriangles_5b(16, 26, 26, 16, 26, 15, 24, 27, 16, 27, 26, 16),
gsSPNTriangles_5b(11, 30, 12, 31, 10, 9, 0, 0, 0, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 11, 10, 29, 11, 29, 29, 0, 0, 0),
gsSPVertex(&act_m_yasigani_v[32], 27, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 0, 3, 1, 4, 3, 3),
gsSPNTriangles_5b(4, 3, 5, 6, 7, 8, 7, 3, 8, 9, 10, 11),
gsSPNTriangles_5b(12, 13, 11, 14, 15, 16, 14, 16, 17, 18, 19, 20),
gsSPNTriangles_5b(18, 20, 21, 18, 21, 22, 18, 22, 23, 24, 25, 13),
gsSPNTriangles_5b(24, 13, 26, 25, 11, 13, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_mus_yasigani_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_yasigani_v[59], 32, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 4, 8, 7, 4, 6, 8, 9, 10, 11),
gsSPNTriangles_5b(9, 12, 10, 9, 13, 12, 9, 11, 13, 14, 15, 16),
gsSPNTriangles_5b(15, 17, 16, 17, 18, 16, 18, 14, 16, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(10, 19, 20, 21, 19, 21, 22, 21, 23, 24),
gsSPNTriangles_5b(21, 24, 22, 25, 26, 27, 25, 27, 28, 26, 29, 30),
gsSPNTriangles_5b(26, 30, 27, 25, 31, 26, 31, 29, 26, 0, 0, 0),
gsSPVertex(&act_m_yasigani_v[91], 32, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(2, 12, 13, 14, 13, 15, 14, 0, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 0, 6, 5, 7, 0, 5, 8, 7, 9, 0, 10),
gsSPNTriangles_5b(0, 7, 10, 11, 1, 9, 1, 0, 9, 16, 17, 18),
gsSPNTriangles_5b(16, 18, 19, 20, 17, 21, 17, 16, 21, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 21, 16, 19, 21, 19, 22, 20, 24, 25),
gsSPNTriangles_5b(17, 20, 25, 26, 17, 25, 26, 25, 27, 28, 29, 18),
gsSPNTriangles_5b(28, 18, 17, 28, 17, 30, 17, 26, 30, 29, 28, 30),
gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_m_yasigani_v[123], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_m_yasigani2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_yasigani_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_mus_yasigani_body1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_yasigani_v[127], 32, 0),
gsSPNTrianglesInit_5b(35, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(0, 4, 5, 6, 7, 8, 9, 10, 11, 9, 11, 12),
gsSPNTriangles_5b(13, 14, 15, 14, 16, 15, 14, 17, 16, 13, 18, 14),
gsSPNTriangles_5b(18, 19, 14, 19, 17, 14, 20, 18, 13, 20, 13, 21),
gsSPNTriangles_5b(22, 19, 18, 22, 18, 20, 23, 17, 19, 23, 19, 22),
gsSPNTriangles_5b(24, 16, 17, 24, 17, 23, 25, 26, 26, 25, 26, 27),
gsSPNTriangles_5b(21, 13, 15, 21, 15, 28, 15, 25, 28, 15, 26, 25),
gsSPNTriangles_5b(16, 26, 26, 16, 26, 15, 24, 27, 16, 27, 26, 16),
gsSPNTriangles_5b(11, 10, 29, 11, 29, 29, 11, 30, 12, 31, 10, 9),
gsSPVertex(&act_m_yasigani_v[159], 27, 0),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 0, 3, 1, 4, 3, 3),
gsSPNTriangles_5b(4, 3, 5, 6, 7, 8, 7, 3, 8, 9, 10, 11),
gsSPNTriangles_5b(12, 13, 11, 14, 15, 16, 14, 16, 17, 18, 19, 20),
gsSPNTriangles_5b(18, 20, 21, 18, 21, 22, 18, 22, 23, 24, 25, 13),
gsSPNTriangles_5b(24, 13, 26, 25, 11, 13, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, act_mus_yasigani_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&act_m_yasigani_v[186], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 7, 8, 6, 8, 4, 6, 9, 10, 11),
gsSPNTriangles_5b(10, 12, 11, 12, 13, 11, 13, 9, 11, 14, 15, 16),
gsSPNTriangles_5b(14, 17, 15, 14, 18, 17, 14, 16, 18, 19, 20, 21),
gsSPNTriangles_5b(19, 21, 22, 21, 23, 24, 21, 24, 22, 25, 26, 27),
gsSPNTriangles_5b(25, 27, 28, 26, 29, 30, 26, 30, 27, 25, 31, 26),
gsSPNTriangles_5b(31, 29, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&act_m_yasigani_v[218], 32, 0),
gsSPNTrianglesInit_5b(30, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 0, 6, 5, 7, 0, 5, 8, 7, 9, 0, 10),
gsSPNTriangles_5b(0, 7, 10, 11, 1, 9, 1, 0, 9, 12, 13, 14),
gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 18, 19, 20, 17, 21),
gsSPNTriangles_5b(17, 16, 21, 20, 21, 22, 20, 22, 23, 21, 16, 19),
gsSPNTriangles_5b(21, 19, 22, 20, 24, 25, 17, 20, 25, 26, 17, 25),
gsSPNTriangles_5b(26, 25, 27, 28, 29, 18, 28, 18, 17, 28, 17, 30),
gsSPNTriangles_5b(17, 26, 30, 29, 28, 30, 29, 30, 31, 0, 0, 0),
gsSPVertex(&act_m_yasigani_v[250], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
