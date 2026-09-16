#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 clg_win_hajime_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clg_win_hajime/clg_win_hajime_tex.inc"
};

u8 clg_win_saigo_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clg_win_hajime/clg_win_saigo_tex.inc"
};

u8 cat_c_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clg_win_hajime/cat_c_tex.inc"
};

static u8 yaji[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/clg_win_hajime/yaji.inc"
};

Vtx clg_hyouji_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/clg_win_hajime/clg_hyouji_v.inc"
};

Gfx clg_win_cbT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 40, 225, 0, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, yaji),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(clg_hyouji_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 245, 245, 30, 255),
gsDPSetEnvColor(85, 75, 105, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, cat_c_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_hyouji_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(185, 70, 0, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, clg_win_saigo_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&clg_hyouji_v[12], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, clg_win_hajime_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
gsSPEndDisplayList(),
};
