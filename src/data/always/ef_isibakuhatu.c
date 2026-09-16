#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 ef_isibakuhatu_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_isibakuhatu/ef_isibakuhatu_pal.inc"
};

u8 ef_isibakuhatu1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_isibakuhatu/ef_isibakuhatu1.inc"
};

Vtx ef_isibakuhatu_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_isibakuhatu/ef_isibakuhatu_v.inc"
};

Gfx ef_isibakuhatu_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, ef_isibakuhatu_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_isibakuhatu1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(ef_isibakuhatu_v, 10, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(1, 0, 4, 5, 6, 7, 6, 8, 7, 6, 9, 8),
gsSPNTriangles_5b(6, 5, 9, 9, 3, 4, 8, 9, 4, 8, 4, 0),
gsSPNTriangles_5b(0, 7, 8, 2, 7, 0, 5, 7, 2, 5, 2, 3),
gsSPNTriangles_5b(9, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
