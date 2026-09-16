#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

static u16 rom_museum4_step_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/rom_museum4_step_pal.inc"
};

u16 obj_01_zassou_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_01_zassou_pal.inc"
};

u16 obj_c_01_flower_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_c_01_flower_pal.inc"
};

u16 obj_b_01_flower_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_b_01_flower_pal.inc"
};

u16 obj_a_01_flower_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_a_01_flower_pal.inc"
};

u16 obj_s_stone_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_s_stone_pal.inc"
};

static u16 obj_tree_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_tree_pal.inc"
};

static u16 grd_bush_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/grd_bush_pal.inc"
};

u16 obj_palm_coco_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_palm_coco_pal.inc"
};

u8 rom_museum4_plate_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/rom_museum4_plate_tex.inc"
};

u8 obj_zassou_01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_zassou_01_tex.inc"
};

u8 obj_c_01_flower_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_c_01_flower_tex.inc"
};

u8 obj_b_01_flower_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_b_01_flower_tex.inc"
};

u8 obj_a_01_flower_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_a_01_flower_tex.inc"
};

u8 obj_s_stone_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_s_stone_tex.inc"
};

static u8 obj_s_tree_trunk_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_s_tree_trunk_tex.inc"
};

static u8 obj_s_tree_leaf_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_s_tree_leaf_tex.inc"
};

u8 grd_s_bushA_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/grd_s_bushA_tex.inc"
};

u8 obj_s_palm_coco_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_s_palm_coco_tex.inc"
};

static u8 obj_s_palm_leaf_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_s_palm_leaf_tex.inc"
};

static u8 obj_s_palm_trunk_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_museum4_step_0033F320/obj_s_palm_trunk_tex.inc"
};

Vtx rom_museum4_pp_ue_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_museum4_step_0033F320/rom_museum4_pp_ue_v.inc"
};

Gfx rom_museum4_pp_ue_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, grd_bush_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, grd_s_bushA_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_museum4_pp_ue_v[27], 11, 0),
gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 0, 4, 5, 3, 6),
gsSPNTriangles_5b(7, 5, 8, 9, 7, 10, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_tree_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_palm_trunk_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[38], 7, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsSPNTriangles_5b(1, 5, 4, 0, 6, 1, 6, 5, 1, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_palm_leaf_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[45], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
gsSPNTriangles_5b(21, 23, 22, 24, 25, 26, 25, 27, 26, 28, 29, 30),
gsSPNTriangles_5b(28, 31, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[77], 24, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_palm_coco_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_palm_coco_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 19, 17, 20, 21, 22),
gsSPNTriangles_5b(21, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_tree_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_leaf_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[101], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(4, 2, 1, 5, 6, 7, 8, 5, 7, 9, 8, 7),
gsSPNTriangles_5b(9, 7, 6, 10, 11, 12, 13, 10, 12, 11, 14, 12),
gsSPNTriangles_5b(13, 12, 14, 15, 16, 17, 15, 18, 16, 18, 19, 16),
gsSPNTriangles_5b(19, 17, 16, 20, 21, 22, 23, 20, 22, 24, 23, 22),
gsSPNTriangles_5b(24, 22, 21, 25, 26, 27, 28, 25, 27, 26, 29, 27),
gsSPNTriangles_5b(28, 27, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[131], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(4, 2, 1, 5, 6, 7, 8, 5, 7, 9, 8, 7),
gsSPNTriangles_5b(9, 7, 6, 10, 11, 12, 13, 10, 12, 11, 14, 12),
gsSPNTriangles_5b(13, 12, 14, 15, 16, 17, 15, 18, 16, 18, 19, 16),
gsSPNTriangles_5b(19, 17, 16, 20, 21, 22, 23, 20, 22, 24, 23, 22),
gsSPNTriangles_5b(24, 22, 21, 25, 26, 27, 28, 25, 27, 26, 29, 27),
gsSPNTriangles_5b(28, 27, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[161], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(4, 2, 1, 5, 6, 7, 8, 5, 7, 9, 8, 7),
gsSPNTriangles_5b(9, 7, 6, 10, 11, 12, 13, 10, 12, 11, 14, 12),
gsSPNTriangles_5b(13, 12, 14, 15, 16, 17, 15, 18, 16, 18, 19, 16),
gsSPNTriangles_5b(19, 17, 16, 20, 21, 22, 23, 20, 22, 24, 23, 22),
gsSPNTriangles_5b(24, 22, 21, 25, 26, 27, 28, 25, 27, 26, 29, 27),
gsSPNTriangles_5b(28, 27, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[191], 15, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 3, 2),
gsSPNTriangles_5b(1, 4, 2, 5, 6, 7, 8, 5, 7, 6, 9, 7),
gsSPNTriangles_5b(8, 7, 9, 10, 11, 12, 13, 12, 11, 14, 10, 12),
gsSPNTriangles_5b(13, 14, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_trunk_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[206], 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 1, 3, 2, 4, 2, 5),
gsSPNTriangles_5b(4, 0, 2, 5, 2, 6, 2, 3, 6, 7, 8, 9),
gsSPNTriangles_5b(8, 10, 9, 11, 9, 12, 11, 7, 9, 12, 9, 13),
gsSPNTriangles_5b(9, 10, 13, 14, 15, 16, 15, 17, 16, 18, 16, 19),
gsSPNTriangles_5b(18, 14, 16, 19, 16, 20, 16, 17, 20, 21, 22, 23),
gsSPNTriangles_5b(22, 24, 23, 25, 23, 26, 25, 21, 23, 26, 23, 27),
gsSPNTriangles_5b(23, 24, 27, 28, 29, 30, 31, 29, 28, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[238], 20, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 2, 3, 4, 1, 5, 2),
gsSPNTriangles_5b(5, 3, 2, 6, 7, 8, 7, 9, 8, 10, 8, 11),
gsSPNTriangles_5b(10, 6, 8, 11, 8, 12, 8, 9, 12, 13, 14, 15),
gsSPNTriangles_5b(14, 16, 15, 17, 15, 18, 17, 13, 15, 18, 15, 19),
gsSPNTriangles_5b(15, 16, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_a_01_flower_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_a_01_flower_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[258], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[290], 16, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_b_01_flower_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_b_01_flower_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[306], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[338], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_c_01_flower_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_c_01_flower_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[346], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[378], 20, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_01_zassou_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_zassou_01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_museum4_step_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_museum4_plate_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_museum4_pp_ue_v[398], 24, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_s_stone_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_stone_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(rom_museum4_pp_ue_v, 27, 0),
gsSPNTrianglesInit_5b(29, 0, 1, 2, 0, 3, 1, 4, 3, 5),
gsSPNTriangles_5b(4, 1, 3, 3, 6, 5, 3, 0, 6, 4, 7, 1),
gsSPNTriangles_5b(7, 2, 1, 8, 6, 9, 6, 0, 9, 10, 11, 12),
gsSPNTriangles_5b(10, 13, 11, 9, 14, 10, 9, 0, 14, 14, 13, 10),
gsSPNTriangles_5b(8, 9, 12, 9, 10, 12, 15, 16, 17, 16, 18, 17),
gsSPNTriangles_5b(18, 19, 17, 16, 20, 18, 20, 21, 18, 16, 22, 20),
gsSPNTriangles_5b(18, 23, 19, 23, 24, 19, 18, 21, 23, 15, 25, 16),
gsSPNTriangles_5b(25, 22, 16, 15, 26, 25, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
