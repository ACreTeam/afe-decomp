#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 ef_nagare01_inta_ia8[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_nagare01_inta_ia8/ef_nagare01_inta_ia8.inc"
};

u8 ef_nagare02_int_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_nagare01_inta_ia8/ef_nagare02_int_i4.inc"
};

Vtx ef_nagare01_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_nagare01_inta_ia8/ef_nagare01_v.inc"
};

Gfx ef_nagare01_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, COMBINED, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 255, 255, 180, 150),
gsDPSetEnvColor(255, 200, 20, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 8, 256, ef_nagare01_inta_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_REPEAT, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 8, 32, ef_nagare02_int_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPDisplayList(anime_2_txt),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(ef_nagare01_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
