#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 ef_situren01_0[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_situren01/ef_situren01_0.inc"
};

Vtx ef_situren01_00_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_situren01/ef_situren01_00_v.inc"
};

Gfx ef_situren01_00_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetEnvColor(255, 0, 100, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, ef_situren01_0),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(ef_situren01_00_v, 4, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 1, 3, 2),
gsSPEndDisplayList(),
};

u8 ef_situren01_1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_situren01/ef_situren01_1.inc"
};

Vtx ef_situren01_01_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_situren01/ef_situren01_01_v.inc"
};

Gfx ef_situren01_01_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetEnvColor(255, 0, 100, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ef_situren01_1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(ef_situren01_01_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Vtx ef_situren01_02_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_situren01/ef_situren01_02_v.inc"
};

Gfx ef_situren01_02_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetEnvColor(255, 0, 100, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, ef_situren01_1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(ef_situren01_02_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 0, 2, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
