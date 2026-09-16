#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 int_ike_nomi_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_nomi_body_002265C0/int_ike_nomi_pal.inc"
};

static u8 act_mus_nomi_body[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/act_mus_nomi_body_002265C0/act_mus_nomi_body.inc"
};

static Vtx act_m_nomi_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/act_mus_nomi_body_002265C0/act_m_nomi_v.inc"
};

Gfx act_m_nomi1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, int_ike_nomi_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_mus_nomi_body),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(act_m_nomi_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
