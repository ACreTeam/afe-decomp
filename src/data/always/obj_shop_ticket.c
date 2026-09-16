#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 obj_shop_ticket_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_shop_ticket/obj_shop_ticket_pal.inc"
};

u8 obj_shop_ticket_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_shop_ticket/obj_shop_ticket_tex.inc"
};

Vtx obj_shop_ticket_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_shop_ticket/obj_shop_ticket_v.inc"
};

Gfx obj_ticketT_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_ticket_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_shop_ticket_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_ticketT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_shop_ticket_v, 20, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
gsSPEndDisplayList(),
};
