#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u16 obj_cata_live_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_cata_live/obj_cata_live_pal.inc"
};

u8 obj_cata_live_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_cata_live/obj_cata_live_tex.inc"
};

Vtx obj_cata_live_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_cata_live/obj_cata_live_v.inc"
};

Gfx obj_cata_liveT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
gsDPSetTextureLUT(G_TT_RGBA16),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_cata_live_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_cata_live_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(obj_cata_live_v, 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 0, 4, 5),
gsSPNTriangles_5b(4, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
