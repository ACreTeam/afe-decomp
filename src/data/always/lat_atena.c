#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 lat_atena_win_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/lat_atena/lat_atena_win_tex.inc"
};

Gfx lat_atena_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_CLD_SURF | G_RM_CLD_SURF2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, lat_atena_win_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_atena_winT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsSPVertex(anime_1_txt, 8, 0),
gsSP2Triangles(0, 4, 1, 0, 4, 6, 1, 0),
gsSP2Triangles(2, 0, 3, 0, 0, 1, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};

Gfx lat_atena_kageT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
gsDPSetPrimColor(0, 255, 20, 40, 0, 185),
gsSPVertex(anime_1_txt + 0x80, 8, 0),
gsSP2Triangles(0, 4, 1, 0, 4, 6, 1, 0),
gsSP2Triangles(2, 0, 3, 0, 0, 1, 3, 0),
gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
gsSPEndDisplayList(),
};

Gfx lat_atena_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(lat_atena_mode),
gsSPDisplayList(lat_atena_kageT_model),
gsSPEndDisplayList(),
};
