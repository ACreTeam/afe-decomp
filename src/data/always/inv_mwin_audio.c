#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 inv_mwin_audio_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mwin_audio/inv_mwin_audio_pal.inc"
};

u8 inv_mwin_audio_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mwin_audio/inv_mwin_audio_tex.inc"
};

Vtx mus_icon_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/inv_mwin_audio/mus_icon_v.inc"
};

Gfx mus_icon_model_before[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, inv_mwin_audio_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, inv_mwin_audio_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPEndDisplayList(),
};

Gfx mus_icon_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(mus_icon_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

u16 icon_music_live2_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mwin_audio/icon_music_live2_pal.inc"
};

u8 icon_music_live2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mwin_audio/icon_music_live2_tex.inc"
};

Vtx icon_music_live2_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/inv_mwin_audio/icon_music_live2_v.inc"
};

Gfx icon_music_live2T_model_before[] ATTRIBUTE_ALIGN(8) = {
gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_TEX_EDGE2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, icon_music_live2_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, icon_music_live2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPEndDisplayList(),
};

Gfx icon_music_live2T_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(icon_music_live2_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
