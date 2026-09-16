#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 ef_shutter_tex_i4c_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/ef_shutter/ef_shutter_tex_i4c_txt.inc"
};

Vtx ef_shutter_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/ef_shutter/ef_shutter_v.inc"
};

Gfx ef_shutter_mode[] ATTRIBUTE_ALIGN(8) = {
gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_OPA_SURF2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 45, 40, 40, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, ef_shutter_tex_i4c_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList(),
};

Gfx ef_shutter_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(ef_shutter_v, 3, 0),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
