#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 obj_notice_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_w_notice/obj_notice_pal.inc"
};

u8 obj_w_notice_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_w_notice/obj_w_notice_tex.inc"
};

Vtx obj_w_notice_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_w_notice/obj_w_notice_v.inc"
};

Gfx obj_w_noticeT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_notice_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_w_notice_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_w_noticeT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_w_notice_v, 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
