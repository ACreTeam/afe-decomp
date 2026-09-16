#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 int_ike_fun_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_fun_body_005B73E0/int_ike_fun_pal.inc"
};

static u8 act_mus_fun_body[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_fun_body_005B73E0/act_mus_fun_body.inc"
};

static u8 act_mus_fun_body2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_fun_body_005B73E0/act_mus_fun_body2.inc"
};

static u8 act_mus_fun_body3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_fun_body_005B73E0/act_mus_fun_body3.inc"
};

static Vtx act_m_fun_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/act_mus_fun_body_005B73E0/act_m_fun_v.inc"
};

Gfx act_m_mu_fun1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_fun_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_fun_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_m_fun_v, 19, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_fun_body),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(20, 6, 7, 8, 6, 8, 9, 6, 10, 10),
gsSPNTriangles_5b(6, 10, 10, 6, 10, 7, 11, 6, 12, 11, 10, 6),
gsSPNTriangles_5b(13, 10, 10, 13, 10, 11, 14, 10, 10, 14, 10, 13),
gsSPNTriangles_5b(15, 7, 14, 7, 10, 14, 16, 8, 7, 16, 7, 15),
gsSPNTriangles_5b(12, 6, 9, 12, 9, 17, 17, 9, 18, 9, 8, 18),
gsSPNTriangles_5b(18, 8, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_m_mu_fun2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_fun_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_fun_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_fun_v[19], 19, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_fun_body),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(20, 6, 7, 8, 6, 8, 9, 6, 10, 10),
gsSPNTriangles_5b(6, 10, 10, 6, 10, 7, 11, 6, 12, 11, 10, 6),
gsSPNTriangles_5b(13, 10, 10, 13, 10, 11, 14, 10, 10, 14, 10, 13),
gsSPNTriangles_5b(15, 7, 14, 7, 10, 14, 16, 8, 7, 16, 7, 15),
gsSPNTriangles_5b(12, 6, 9, 12, 9, 17, 17, 9, 18, 9, 8, 18),
gsSPNTriangles_5b(18, 8, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx act_m_mu_fun3T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_fun_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_fun_body3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_fun_v[38], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_fun_body2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&act_m_fun_v[42], 19, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, act_mus_fun_body),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(20, 6, 7, 8, 6, 8, 9, 6, 10, 10),
gsSPNTriangles_5b(6, 10, 10, 6, 10, 7, 11, 6, 12, 11, 10, 6),
gsSPNTriangles_5b(13, 10, 10, 13, 10, 11, 14, 10, 10, 14, 10, 13),
gsSPNTriangles_5b(15, 7, 14, 7, 10, 14, 16, 8, 7, 16, 7, 15),
gsSPNTriangles_5b(12, 6, 9, 12, 9, 17, 17, 9, 18, 9, 8, 18),
gsSPNTriangles_5b(18, 8, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
