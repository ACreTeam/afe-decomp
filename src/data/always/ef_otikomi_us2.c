#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 ef_otikomi_us1_int_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_otikomi_us2/ef_otikomi_us1_int_i4.inc"
};

u8 ef_otikomi_us2_int_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_otikomi_us2/ef_otikomi_us2_int_i4.inc"
};

Vtx ef_otikomi_us2_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_otikomi_us2/ef_otikomi_us2_v.inc"
};

Gfx ef_otikomi_us2_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, ef_otikomi_us2_int_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, ef_otikomi_us1_int_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 15, 0),
gsSPDisplayList(anime_2_txt),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(ef_otikomi_us2_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};
