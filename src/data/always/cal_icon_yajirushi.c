#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 cal_win_mark2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/cal_icon_yajirushi/cal_win_mark2_tex.inc"
};

Vtx cal_icon3_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/cal_icon_yajirushi/cal_icon3_v.inc"
};

Gfx cal_icon_sakana_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 185, 50, 50, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, cal_win_mark2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(cal_icon3_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_icon_yajirushi_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsSPEndDisplayList(),
};

Gfx cal_icon_yajirushi_gfx[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&cal_icon3_v[4], 3, 0),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx cal_icon_yajirushi_gfx2[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(&cal_icon3_v[7], 3, 0),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
