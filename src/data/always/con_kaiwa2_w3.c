#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 con_kaiwa2_w3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/con_kaiwa2_w3/con_kaiwa2_w3_tex.inc"
};

u8 con_kaiwa2_w1_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/con_kaiwa2_w3/con_kaiwa2_w1_tex.inc"
};

u8 con_kaiwa2_w2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/con_kaiwa2_w3/con_kaiwa2_w2_tex.inc"
};

Vtx win_syasin_02_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/con_kaiwa2_w3/win_syasin_02_v.inc"
};

Gfx win_syasin_kumoT_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 30, 140, 255, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 64, con_kaiwa2_w2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(win_syasin_02_v, 24, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 0, 4, 5, 6),
gsSPNTriangles_5b(6, 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 64, con_kaiwa2_w1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
gsSPNTriangles_5b(14, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 64, con_kaiwa2_w3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 16, 17, 18, 18, 19, 16, 20, 21, 22),
gsSPNTriangles_5b(22, 23, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
