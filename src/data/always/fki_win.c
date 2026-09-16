#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 fki_win_w2_tex[] = {
#include "assets/forestd/fki_win/fki_win_w2_tex.inc"
};

u8 fki_win_de3_tex[] = {
#include "assets/forestd/fki_win/fki_win_de3_tex.inc"
};

u8 fki_win_de4_tex[] = {
#include "assets/forestd/fki_win/fki_win_de4_tex.inc"
};

u8 fki_win_wa_tex[] = {
#include "assets/forestd/fki_win/fki_win_wa_tex.inc"
};

Vtx fki_win_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/fki_win/fki_win_v.inc"
};

Gfx fki_win_w4_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, fki_win_wa_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 60),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(fki_win_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx fki_win_w3T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 215, 255),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, fki_win_w2_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&fki_win_v[4], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx fki_win_w1T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 215, 255),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, fki_win_de4_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
gsSPVertex(&fki_win_v[8], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx fki_win_w2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 215, 255),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, fki_win_de3_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
gsSPVertex(&fki_win_v[12], 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

Gfx fki_win_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_DECAL_LEQUAL),
gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_TEX_EDGE | G_RM_TEX_EDGE2),
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsSPEndDisplayList(),
};
