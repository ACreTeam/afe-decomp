#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 obj_ike_takotubo_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_ike_takotubo/obj_ike_takotubo_pal.inc"
};

u8 act_mus_takotubo1_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_ike_takotubo/act_mus_takotubo1_body_tex_txt.inc"
};

u8 act_mus_takotubo2_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_ike_takotubo/act_mus_takotubo2_body_tex_txt.inc"
};

u8 act_mus_takotubo3_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_ike_takotubo/act_mus_takotubo3_body_tex_txt.inc"
};

u8 act_mus_takotubo4_body_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_ike_takotubo/act_mus_takotubo4_body_tex_txt.inc"
};

Vtx obj_takotubo_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_ike_takotubo/obj_takotubo_v.inc"
};

Gfx obj_takotubo_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_ike_takotubo_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_takotubo1_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(obj_takotubo_v, 32, 0),
gsSPNTrianglesInit_5b(27, 0, 1, 2, 1, 0, 3, 3, 4, 5),
gsSPNTriangles_5b(5, 4, 6, 6, 7, 8, 9, 0, 2, 0, 9, 10),
gsSPNTriangles_5b(10, 11, 4, 4, 11, 12, 12, 13, 7, 14, 9, 2),
gsSPNTriangles_5b(9, 14, 15, 15, 16, 11, 11, 16, 17, 17, 18, 13),
gsSPNTriangles_5b(19, 14, 2, 14, 19, 20, 20, 21, 16, 16, 21, 22),
gsSPNTriangles_5b(22, 23, 18, 24, 19, 2, 19, 24, 25, 25, 26, 21),
gsSPNTriangles_5b(21, 26, 27, 27, 28, 23, 26, 29, 30, 30, 31, 28),
gsSPVertex(&obj_takotubo_v[32], 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 2, 3, 4, 5, 6, 1),
gsSPNTriangles_5b(1, 6, 7, 7, 8, 3, 9, 10, 11, 2, 9, 0),
gsSPNTriangles_5b(7, 2, 1, 6, 5, 12, 12, 5, 13, 14, 7, 6),
gsSPNTriangles_5b(8, 7, 14, 15, 14, 16, 16, 14, 17, 17, 12, 18),
gsSPNTriangles_5b(18, 12, 19, 20, 18, 21, 22, 16, 23, 23, 18, 20),
gsSPNTriangles_5b(24, 22, 25, 25, 20, 26, 26, 20, 27, 28, 26, 29),
gsSPNTriangles_5b(30, 26, 28, 10, 24, 30, 31, 24, 10, 0, 0, 0),
gsSPVertex(&obj_takotubo_v[64], 25, 0),
gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 1, 5, 6, 7),
gsSPNTriangles_5b(8, 9, 10, 10, 9, 11, 12, 7, 13, 14, 13, 15),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_takotubo2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPNTrianglesInit_5b(8, 16, 17, 18, 19, 20, 18, 21, 19, 18),
gsSPNTriangles_5b(22, 21, 18, 17, 23, 18, 24, 16, 18, 20, 24, 18),
gsSPNTriangles_5b(23, 22, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, act_mus_takotubo3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 444, 28),
gsSPVertex(&obj_takotubo_v[89], 27, 0),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 0, 2, 3, 4, 5, 1),
gsSPNTriangles_5b(4, 1, 0, 1, 6, 7, 1, 7, 2, 5, 8, 6),
gsSPNTriangles_5b(5, 6, 1, 6, 9, 10, 6, 10, 7, 8, 11, 9),
gsSPNTriangles_5b(8, 9, 6, 9, 12, 13, 9, 13, 10, 11, 14, 12),
gsSPNTriangles_5b(11, 12, 9, 15, 16, 17, 15, 17, 18, 19, 20, 16),
gsSPNTriangles_5b(19, 16, 15, 16, 21, 22, 16, 22, 17, 20, 23, 21),
gsSPNTriangles_5b(20, 21, 16, 24, 0, 3, 24, 3, 25, 26, 4, 0),
gsSPNTriangles_5b(26, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, act_mus_takotubo3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 28),
gsSPVertex(&obj_takotubo_v[116], 21, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 4, 5, 3, 5, 6),
gsSPNTriangles_5b(6, 5, 7, 6, 7, 1, 8, 9, 10, 11, 12, 1),
gsSPNTriangles_5b(11, 1, 0, 4, 13, 14, 4, 14, 5, 5, 14, 15),
gsSPNTriangles_5b(5, 15, 7, 9, 16, 10, 17, 18, 12, 17, 12, 11),
gsSPNTriangles_5b(19, 17, 11, 19, 11, 20, 20, 11, 0, 20, 0, 15),
gsSPNTriangles_5b(15, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, act_mus_takotubo3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 28),
gsSPVertex(&obj_takotubo_v[137], 31, 0),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 5, 3, 5, 6),
gsSPNTriangles_5b(6, 5, 7, 6, 7, 8, 8, 9, 10, 11, 6, 1),
gsSPNTriangles_5b(11, 1, 0, 4, 12, 13, 4, 13, 14, 15, 3, 6),
gsSPNTriangles_5b(15, 6, 11, 12, 15, 11, 12, 11, 16, 16, 11, 0),
gsSPNTriangles_5b(16, 0, 17, 17, 0, 10, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, act_mus_takotubo4_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(11, 18, 19, 20, 18, 20, 21, 19, 22, 23),
gsSPNTriangles_5b(19, 23, 20, 24, 25, 26, 24, 26, 27, 19, 18, 28),
gsSPNTriangles_5b(20, 23, 29, 28, 22, 19, 29, 21, 20, 30, 27, 26),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_takotubo1_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&obj_takotubo_v[168], 32, 0),
gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 7, 1),
gsSPNTriangles_5b(8, 9, 10, 4, 11, 12, 13, 10, 7, 14, 3, 15),
gsSPNTriangles_5b(16, 14, 17, 18, 19, 20, 21, 4, 3, 22, 23, 24),
gsSPNTriangles_5b(25, 9, 26, 26, 11, 4, 11, 27, 28, 29, 27, 11),
gsSPNTriangles_5b(9, 18, 29, 20, 30, 27, 31, 3, 14, 0, 0, 0),
gsSPVertex(&obj_takotubo_v[200], 32, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 3, 4, 5, 5, 6, 3),
gsSPNTriangles_5b(3, 7, 8, 9, 3, 6, 10, 11, 6, 6, 11, 9),
gsSPNTriangles_5b(12, 13, 7, 14, 15, 16, 17, 18, 11, 11, 18, 19),
gsSPNTriangles_5b(1, 0, 13, 7, 3, 12, 20, 21, 22, 22, 23, 18),
gsSPNTriangles_5b(18, 23, 2, 2, 24, 0, 21, 25, 26, 26, 27, 23),
gsSPNTriangles_5b(23, 27, 28, 29, 30, 24, 0, 0, 0, 0, 0, 0),
gsSPVertex(&obj_takotubo_v[231], 30, 0),
gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 5, 6, 7),
gsSPNTriangles_5b(7, 6, 8, 8, 9, 10, 11, 12, 13, 4, 14, 1),
gsSPNTriangles_5b(1, 0, 6, 6, 0, 15, 16, 17, 9, 18, 15, 0),
gsSPNTriangles_5b(8, 19, 7, 2, 20, 0, 0, 20, 18, 12, 11, 17),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, act_mus_takotubo2_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPNTrianglesInit_5b(8, 21, 22, 23, 24, 25, 23, 22, 24, 23),
gsSPNTriangles_5b(26, 27, 23, 28, 29, 23, 29, 26, 23, 27, 21, 23),
gsSPNTriangles_5b(25, 28, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 8, act_mus_takotubo3_body_tex_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 444, 28),
gsSPVertex(&obj_takotubo_v[261], 27, 0),
gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 4, 5, 3, 5, 6),
gsSPNTriangles_5b(7, 8, 9, 7, 9, 10, 11, 12, 3, 11, 3, 8),
gsSPNTriangles_5b(0, 2, 13, 2, 14, 15, 13, 2, 15, 13, 15, 16),
gsSPNTriangles_5b(1, 17, 2, 8, 3, 6, 8, 6, 9, 1, 18, 17),
gsSPNTriangles_5b(19, 13, 16, 20, 19, 21, 20, 21, 22, 23, 11, 8),
gsSPNTriangles_5b(23, 8, 7, 12, 24, 4, 12, 4, 3, 19, 16, 21),
gsSPNTriangles_5b(2, 17, 14, 25, 26, 19, 25, 19, 20, 26, 0, 13),
gsSPNTriangles_5b(26, 13, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
