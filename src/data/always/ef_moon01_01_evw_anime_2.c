#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"
#include "evw_anime.h"

EVW_ANIME_SCROLL ef_moon01_01_evw_anime_2[] = {
	{ 0, 0, 64, 64 },
	{ 1, -1, 32, 32 }
};

EVW_ANIME_DATA ef_moon01_01_evw_anime[] = {
	{ -1, EVW_ANIME_TYPE_SCROLL2, ef_moon01_01_evw_anime_2 }
};

static u8 ef_moon01_1_int_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_moon01_01_evw_anime_2/ef_moon01_1_int_i4.inc"
};

u8 ef_moon01_2_int_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_moon01_01_evw_anime_2/ef_moon01_2_int_i4.inc"
};

Vtx ef_moon01_01_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_moon01_01_evw_anime_2/ef_moon01_01_v.inc"
};

Gfx ef_moon01_01_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, TEXEL1, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetEnvColor(0, 255, 200, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 64, ef_moon01_2_int_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, ef_moon01_1_int_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 4, 3),
gsSPDisplayList(anime_1_txt),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(ef_moon01_01_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
