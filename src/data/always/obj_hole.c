#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u8 obj_hole_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/obj_hole/obj_hole_tex.inc"
};

Vtx obj_hole0_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole0_v.inc"
};

Vtx obj_hole1_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole1_v.inc"
};

Vtx obj_hole2_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole2_v.inc"
};

Vtx obj_hole3_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole3_v.inc"
};

Vtx obj_hole4_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole4_v.inc"
};

Vtx obj_hole5_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole5_v.inc"
};

Vtx obj_hole6_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole6_v.inc"
};

Vtx obj_hole7_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole7_v.inc"
};

Vtx obj_hole8_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole8_v.inc"
};

Vtx obj_hole9_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole9_v.inc"
};

Vtx obj_hole10_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole10_v.inc"
};

Vtx obj_hole11_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole11_v.inc"
};

Vtx obj_hole12_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole12_v.inc"
};

Vtx obj_hole13_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole13_v.inc"
};

Vtx obj_hole14_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole14_v.inc"
};

Vtx obj_hole15_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole15_v.inc"
};

Vtx obj_hole16_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole16_v.inc"
};

Vtx obj_hole17_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole17_v.inc"
};

Vtx obj_hole18_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole18_v.inc"
};

Vtx obj_hole19_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole19_v.inc"
};

Vtx obj_hole20_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole20_v.inc"
};

Vtx obj_hole21_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole21_v.inc"
};

Vtx obj_hole22_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole22_v.inc"
};

Vtx obj_hole23_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole23_v.inc"
};

Vtx obj_hole24_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_hole/obj_hole24_v.inc"
};

Gfx obj_hole0T_g_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_hole_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 4, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole0T_s_mat_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_hole_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 5, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole0T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole0_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole1T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole1_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole2T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole2_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole3T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole3_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole4T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole4_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole5T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole5_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole6T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole6_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole7T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole7_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole8T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole8_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole9T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole9_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole10T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole10_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole11T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole11_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole12T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole12_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole13T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole13_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole14T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole14_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole15T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole15_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole16T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole16_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole17T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole17_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole18T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole18_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole19T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole19_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole20T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole20_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole21T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole21_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole22T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole22_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole23T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole23_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx obj_hole24T_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_hole24_v, 5, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 2, 3, 4, 2, 1, 3),
gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
