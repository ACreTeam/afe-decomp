#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 lat_letter01_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/lat_tegami_fusen_003D6280/lat_letter01_pal.inc"
};

static u8 lat_letter01_04_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/lat_tegami_fusen_003D6280/lat_letter01_04_tex.inc"
};

static u8 lat_tegami_fusen_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/lat_tegami_fusen_003D6280/lat_tegami_fusen_tex.inc"
};

Vtx dia_win2_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_tegami_fusen_003D6280/dia_win2_v.inc"
};

Gfx dia_win2_wT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter01_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter01_04_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(dia_win2_v, 10, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 3, 8, 1, 3, 9, 8, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx dia_win2_fusenT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 100, 100, 135, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, lat_tegami_fusen_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&dia_win2_v[10], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};
