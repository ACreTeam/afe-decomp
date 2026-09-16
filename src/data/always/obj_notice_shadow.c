#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 obj_notice_shadow_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_notice_shadow/obj_notice_shadow_tex.inc"
};

Vtx obj_notice_shadow_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_notice_shadow/obj_notice_shadow_v.inc"
};

Gfx obj_notice_shadowT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, obj_notice_shadow_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_notice_shadowT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
