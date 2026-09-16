#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 ef_ame02_0[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_ame02/ef_ame02_0.inc"
};

Vtx ef_ame02_00_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_ame02/ef_ame02_00_v.inc"
};

Gfx ef_ame02_setmode[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 50, 50, 80),
gsDPSetEnvColor(100, 225, 225, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, ef_ame02_0),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx ef_ame02_00_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(ef_ame02_00_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Vtx ef_ame02_01_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_ame02/ef_ame02_01_v.inc"
};

Gfx ef_ame02_01_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(ef_ame02_01_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Vtx ef_ame02_02_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_ame02/ef_ame02_02_v.inc"
};

Gfx ef_ame02_02_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(ef_ame02_02_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Vtx ef_ame02_03_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_ame02/ef_ame02_03_v.inc"
};

Gfx ef_ame02_03_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(ef_ame02_03_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Vtx ef_ame02_04_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_ame02/ef_ame02_04_v.inc"
};

Gfx ef_ame02_04_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(ef_ame02_04_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};
