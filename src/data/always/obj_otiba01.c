#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 obj_otiba01_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_otiba01/obj_otiba01_pal.inc"
};

u8 ef_otiba_0_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_otiba01/ef_otiba_0_tex.inc"
};

Gfx ef_otiba01_setmode[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 255, 200),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPPipeSync(),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_otiba01_pal),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Vtx ef_otiba01_00_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_otiba01/ef_otiba01_00_v.inc"
};

Gfx ef_otiba01_00_modelT[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_otiba_0_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(ef_otiba01_00_v, 5, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(0, 4, 1, 0, 4, 3, 1, 0),
gsSPEndDisplayList(),
};

u8 ef_otiba_1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_otiba01/ef_otiba_1_tex.inc"
};

Vtx ef_otiba01_01_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_otiba01/ef_otiba01_01_v.inc"
};

Gfx ef_otiba01_01_modelT[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_otiba_1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(ef_otiba01_01_v, 5, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(0, 4, 1, 0, 4, 3, 1, 0),
gsSPEndDisplayList(),
};

u8 ef_otiba_2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_otiba01/ef_otiba_2_tex.inc"
};

Vtx ef_otiba01_02_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_otiba01/ef_otiba01_02_v.inc"
};

Gfx ef_otiba01_02_modelT[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, ef_otiba_2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(ef_otiba01_02_v, 5, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(0, 4, 1, 0, 4, 3, 1, 0),
gsSPEndDisplayList(),
};
