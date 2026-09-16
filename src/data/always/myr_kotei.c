#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 myr_kotei_pal[] = {
#include "assets/forestd/myr_kotei/myr_kotei_pal.inc"
};

u8 myr_enter[] = {
#include "assets/forestd/myr_kotei/myr_enter.inc"
};

u8 myr_window[] = {
#include "assets/forestd/myr_kotei/myr_window.inc"
};

Vtx myr_kotei_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/myr_kotei/myr_kotei_v.inc"
};

Gfx myr_kotei_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_RGBA16),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, myr_kotei_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, myr_enter),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
gsSPClearGeometryMode(G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_DECAL_LEQUAL),
gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(myr_kotei_v, 6, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 2, 0, 5, 0, 2, 0),
gsSPEndDisplayList(),
};

Gfx myr_out_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2),
gsSPClearGeometryMode(G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_DECAL_LEQUAL),
gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&myr_kotei_v[6], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
gsSPEndDisplayList(),
};

Gfx myr_koteiT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2),
gsDPPipeSync(),
gsDPSetTextureLUT(G_TT_RGBA16),
gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, myr_kotei_pal),
gsDPTileSync(),
gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
gsDPPipeSync(),
gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, myr_window),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_MIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
gsSPClearGeometryMode(G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_DECAL_LEQUAL),
gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&myr_kotei_v[14], 8, 0),
gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
gsSPEndDisplayList(),
};

Gfx myr_etc_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPDisplayList(myr_kotei_model),
gsSPDisplayList(myr_koteiT_model),
gsSPDisplayList(myr_out_model),
gsSPEndDisplayList(),
};
