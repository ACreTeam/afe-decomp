#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_koban_tel_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_tel_pal.inc"
};

u16 rom_koban_win_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_win_pal.inc"
};

u16 rom_koban_us_pos_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_us_pos_pal.inc"
};

u16 rom_koban_jim_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_jim_pal.inc"
};

u16 rom_koban_kabe_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_kabe_pal.inc"
};

u16 rom_koban_roc_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_roc_pal.inc"
};

u8 rom_koban_tel[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_tel.inc"
};

u8 rom_koban_win[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_win.inc"
};

u8 rom_koban_desk_front[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_desk_front.inc"
};

u8 rom_koban_desk_side[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_desk_side.inc"
};

u8 rom_koban_desk_top[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_desk_top.inc"
};

u8 rom_koban_yuka[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_yuka.inc"
};

u8 rom_koban_us_pos1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_us_pos1.inc"
};

u8 rom_koban_us_pos2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_us_pos2.inc"
};

u8 rom_koban_kage1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_kage1.inc"
};

u8 rom_koban_kage2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_kage2.inc"
};

u8 rom_koban_ent[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_ent.inc"
};

u8 rom_koban_jim_front[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_jim_front.inc"
};

u8 rom_koban_jim_side[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_jim_side.inc"
};

u8 rom_koban_jim_top[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_jim_top.inc"
};

u8 rom_koban_kabe1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_kabe1.inc"
};

u8 rom_koban_telcode[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_telcode.inc"
};

u8 rom_koban_book[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_book.inc"
};

u8 rom_koban_roc_s[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_roc_s.inc"
};

u8 rom_koban_roc_t[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_roc_t.inc"
};

u8 rom_koban_kabe3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_kabe3.inc"
};

u8 rom_koban_isu[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_isu.inc"
};

u8 rom_koban_roc_i[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_roc_i.inc"
};

u8 rom_koban_roc_f3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_koban_tel/rom_koban_roc_f3.inc"
};

Vtx police_indoor_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_koban_tel/police_indoor_v.inc"
};

Gfx police_indoor_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPEndDisplayList(),
};

Gfx police_indoor_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_win_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_koban_win),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&police_indoor_v[268], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_us_pos_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, rom_koban_us_pos2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&police_indoor_v[276], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, rom_koban_us_pos1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_win_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_koban_desk_side),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&police_indoor_v[336], 16, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_koban_desk_front),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&police_indoor_v[352], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 8, 11, 9, 12, 13, 14),
gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 19, 17, 20, 21, 22),
gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 24, 27, 25, 28, 29, 30),
gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&police_indoor_v[384], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_roc_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rom_koban_roc_f3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&police_indoor_v[392], 7, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_jim_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_koban_isu),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&police_indoor_v[399], 14, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(3, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_koban_jim_side),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 6, 7, 8, 6, 9, 7, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_koban_jim_front),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 10, 11, 12, 10, 12, 13, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_tel_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_koban_book),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&police_indoor_v[413], 12, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_koban_telcode),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(1, 4, 5, 6, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_koban_tel),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(3, 7, 8, 9, 7, 9, 10, 8, 7, 11),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_win_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_koban_ent),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(police_indoor_v, 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_kabe_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_koban_kabe1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
gsSPVertex(&police_indoor_v[5], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 2, 1, 2, 3, 4),
gsSPNTriangles_5b(0, 5, 6, 5, 7, 6, 8, 9, 10, 9, 11, 10),
gsSPNTriangles_5b(4, 12, 13, 12, 14, 13, 15, 16, 17, 16, 18, 17),
gsSPNTriangles_5b(17, 19, 10, 20, 1, 6, 1, 0, 6, 8, 10, 19),
gsSPNTriangles_5b(21, 12, 3, 12, 4, 3, 17, 18, 19, 22, 23, 24),
gsSPNTriangles_5b(25, 22, 24, 26, 27, 28, 29, 26, 28, 22, 30, 31),
gsSPNTriangles_5b(23, 22, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&police_indoor_v[37], 32, 0),
gsSPNTrianglesInit_5b(27, 0, 1, 2, 3, 4, 5, 4, 3, 6),
gsSPNTriangles_5b(7, 6, 3, 7, 0, 2, 8, 9, 10, 11, 12, 13),
gsSPNTriangles_5b(11, 14, 12, 14, 15, 12, 15, 13, 12, 14, 16, 15),
gsSPNTriangles_5b(17, 18, 19, 17, 8, 18, 8, 10, 18, 10, 19, 18),
gsSPNTriangles_5b(20, 21, 14, 20, 22, 21, 22, 23, 21, 23, 14, 21),
gsSPNTriangles_5b(23, 24, 14, 8, 25, 9, 25, 26, 9, 8, 27, 25),
gsSPNTriangles_5b(27, 26, 25, 16, 14, 24, 28, 29, 30, 31, 30, 29),
gsSPVertex(&police_indoor_v[69], 10, 0),
gsSPNTrianglesInit_5b(9, 0, 1, 2, 1, 3, 2, 4, 2, 3),
gsSPNTriangles_5b(4, 0, 2, 3, 5, 6, 3, 6, 7, 6, 8, 7),
gsSPNTriangles_5b(9, 7, 8, 9, 3, 7, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_tel_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_koban_yuka),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&police_indoor_v[79], 32, 0),
gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 3, 1, 3, 0, 4),
gsSPNTriangles_5b(0, 5, 4, 6, 7, 1, 8, 9, 6, 10, 11, 12),
gsSPNTriangles_5b(10, 13, 11, 14, 15, 16, 14, 17, 15, 17, 18, 19),
gsSPNTriangles_5b(20, 21, 22, 23, 17, 14, 24, 25, 2, 24, 26, 25),
gsSPNTriangles_5b(26, 27, 25, 27, 12, 25, 28, 26, 24, 27, 26, 29),
gsSPNTriangles_5b(30, 31, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&police_indoor_v[111], 32, 0),
gsSPNTrianglesInit_5b(25, 0, 1, 2, 0, 3, 1, 0, 4, 3),
gsSPNTriangles_5b(5, 1, 6, 7, 1, 3, 8, 9, 0, 9, 10, 0),
gsSPNTriangles_5b(8, 11, 9, 12, 9, 13, 8, 0, 14, 0, 10, 4),
gsSPNTriangles_5b(15, 16, 11, 17, 15, 18, 17, 16, 15, 17, 19, 16),
gsSPNTriangles_5b(2, 20, 14, 5, 6, 21, 22, 5, 21, 23, 22, 21),
gsSPNTriangles_5b(24, 25, 13, 26, 27, 28, 24, 29, 28, 27, 24, 28),
gsSPNTriangles_5b(4, 30, 3, 31, 7, 3, 0, 0, 0, 0, 0, 0),
gsSPVertex(&police_indoor_v[143], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsSPVertex(&police_indoor_v[147], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_win_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_koban_desk_top),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&police_indoor_v[155], 32, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 11, 9, 12, 13, 14),
gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 17, 19, 18, 20, 21, 22),
gsSPNTriangles_5b(20, 23, 21, 24, 25, 26, 24, 27, 25, 28, 29, 30),
gsSPNTriangles_5b(29, 31, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&police_indoor_v[187], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_roc_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_koban_roc_i),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&police_indoor_v[195], 12, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_koban_roc_t),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 7, 5, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_koban_roc_s),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(2, 8, 9, 10, 9, 11, 10, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_jim_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, rom_koban_jim_top),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&police_indoor_v[207], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_kabe_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, rom_koban_kabe3),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
gsSPVertex(&police_indoor_v[211], 32, 0),
gsSPNTrianglesInit_5b(27, 0, 1, 2, 1, 3, 2, 4, 5, 1),
gsSPNTriangles_5b(5, 3, 1, 5, 6, 3, 6, 7, 3, 3, 7, 2),
gsSPNTriangles_5b(7, 8, 2, 9, 10, 11, 9, 11, 12, 12, 11, 13),
gsSPNTriangles_5b(12, 13, 14, 15, 12, 14, 15, 14, 16, 9, 12, 15),
gsSPNTriangles_5b(9, 15, 17, 18, 19, 20, 19, 21, 20, 21, 22, 20),
gsSPNTriangles_5b(22, 23, 20, 24, 21, 25, 24, 22, 21, 21, 26, 25),
gsSPNTriangles_5b(21, 19, 26, 27, 28, 29, 27, 30, 28, 28, 31, 29),
gsSPVertex(&police_indoor_v[243], 25, 0),
gsSPNTrianglesInit_5b(17, 0, 1, 2, 3, 4, 5, 3, 6, 4),
gsSPNTriangles_5b(4, 7, 5, 4, 2, 7, 8, 9, 10, 11, 8, 10),
gsSPNTriangles_5b(10, 12, 13, 11, 10, 13, 14, 15, 12, 14, 12, 10),
gsSPNTriangles_5b(14, 10, 9, 14, 9, 16, 17, 18, 19, 18, 20, 19),
gsSPNTriangles_5b(21, 22, 23, 21, 24, 22, 0, 0, 0, 0, 0, 0),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 0, 0, 0, 115),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_koban_kage2),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&police_indoor_v[284], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, rom_koban_kage1),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&police_indoor_v[288], 32, 0),
gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 4, 5, 6, 7, 8),
gsSPNTriangles_5b(7, 9, 8, 10, 11, 12, 11, 13, 12, 14, 15, 16),
gsSPNTriangles_5b(15, 17, 16, 18, 19, 20, 18, 21, 19, 22, 23, 24),
gsSPNTriangles_5b(23, 25, 24, 26, 27, 28, 26, 29, 27, 0, 0, 0),
gsSPVertex(&police_indoor_v[318], 18, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(4, 7, 5, 8, 9, 10, 9, 11, 10, 12, 13, 14),
gsSPNTriangles_5b(15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
