#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 yubin_k_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_k_pal.inc"
};

u16 yubin_k2_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_k2_pal.inc"
};

u16 yubin_floor_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_floor_pal.inc"
};

u16 yubin_hakari_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_hakari_pal.inc"
};

u16 yubin_wall_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_wall_pal.inc"
};

u16 yubin_letter_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_letter_pal.inc"
};

u16 yubin_us_bag_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_us_bag_pal.inc"
};

u16 zzzyubin_tree_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/zzzyubin_tree_pal.inc"
};

u16 yubin_t_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_t_pal.inc"
};

u16 yubin_us_card_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_us_card_pal.inc"
};

u16 yubin_pp_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_pp_pal.inc"
};

u8 yuibn_kaunta01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yuibn_kaunta01_tex.inc"
};

u8 yuibn_kaunta02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yuibn_kaunta02_tex.inc"
};

u8 yuibn_desk01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yuibn_desk01_tex.inc"
};

u8 yubin_ark01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_ark01_tex.inc"
};

u8 yuibn_kaunta03_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yuibn_kaunta03_tex.inc"
};

u8 yuibn_kaunta04_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yuibn_kaunta04_tex.inc"
};

u8 yubin_floor01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_floor01_tex.inc"
};

u8 yubin_floor02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_floor02_tex.inc"
};

u8 yubin_floor03_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_floor03_tex.inc"
};

u8 yubin_hakari01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_hakari01_tex.inc"
};

u8 yubin_hakari02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_hakari02_tex.inc"
};

u8 yubin_hakari03_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_hakari03_tex.inc"
};

u8 yubin_wall04_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_wall04_tex.inc"
};

u8 yubin_letter01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_letter01_tex.inc"
};

u8 yubin_window_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_window_tex.inc"
};

u8 yubin_us_bag_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_us_bag_tex.inc"
};

u8 yubin_tree2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_tree2_tex.inc"
};

u8 yubin_tree_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_tree_tex.inc"
};

u8 yubin_tree3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_tree3_tex.inc"
};

u8 yubin_tree4_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_tree4_tex.inc"
};

u8 yubin_step_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_step_tex.inc"
};

u8 rom_yubinkyoku_akril_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/rom_yubinkyoku_akril_tex.inc"
};

u8 rom_yubinkyoku_shede_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/rom_yubinkyoku_shede_tex.inc"
};

u8 yubin_us_card_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_us_card_tex.inc"
};

u8 yubin_pp_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_pp_tex.inc"
};

u8 rom_yubinkyoku_shadow_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/rom_yubinkyoku_shadow_tex.inc"
};

u8 yubin_us_card2_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/yubin_k/yubin_us_card2_tex.inc"
};

Vtx rom_yubin_pp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/yubin_k/rom_yubin_pp_v.inc"
};

Gfx rom_yubin_pp_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 255, 120),
gsDPSetEnvColor(0, 100, 255, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, rom_yubinkyoku_akril_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[197], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx rom_yubin_pp_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, yubin_window_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&rom_yubin_pp_v[217], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_k_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, yuibn_kaunta04_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[225], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, zzzyubin_tree_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, yubin_tree_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[229], 20, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, yubin_tree2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 16, 17, 18, 16, 18, 19, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_k2_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, yubin_ark01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[249], 32, 0),
gsSPNTrianglesInit_5b(25, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 6, 8, 9),
gsSPNTriangles_5b(6, 9, 7, 8, 10, 11, 8, 11, 9, 10, 12, 13),
gsSPNTriangles_5b(10, 13, 11, 12, 14, 15, 12, 15, 13, 16, 17, 18),
gsSPNTriangles_5b(16, 18, 19, 20, 0, 3, 20, 3, 21, 22, 23, 20),
gsSPNTriangles_5b(22, 20, 21, 24, 25, 3, 24, 3, 26, 27, 28, 29),
gsSPNTriangles_5b(27, 29, 30, 27, 30, 31, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_yubin_pp_v[281], 32, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8),
gsSPNTriangles_5b(9, 10, 11, 9, 11, 12, 11, 13, 14, 11, 14, 15),
gsSPNTriangles_5b(16, 17, 18, 16, 18, 19, 17, 20, 1, 17, 1, 21),
gsSPNTriangles_5b(22, 23, 24, 22, 24, 25, 26, 27, 28, 26, 28, 29),
gsSPNTriangles_5b(27, 30, 3, 27, 3, 31, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_yubin_pp_v[313], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_us_bag_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 48, yubin_us_bag_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[317], 10, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 0, 4, 1),
gsSPNTriangles_5b(5, 6, 7, 7, 8, 9, 5, 7, 9, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_floor_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, yubin_floor03_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_yubin_pp_v[327], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_hakari_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, yubin_hakari03_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[331], 8, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, yubin_hakari02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_letter_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, yubin_letter01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[339], 7, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 2, 4, 5),
gsSPNTriangles_5b(2, 5, 3, 2, 1, 6, 2, 6, 4, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_pp_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, yubin_pp_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[346], 22, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_us_card_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, yubin_us_card_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(10, 4, 5, 6, 5, 7, 6, 8, 9, 10),
gsSPNTriangles_5b(8, 10, 11, 12, 13, 14, 15, 16, 13, 17, 15, 13),
gsSPNTriangles_5b(12, 17, 13, 18, 19, 20, 18, 21, 19, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_t_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, yubin_step_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(rom_yubin_pp_v, 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 2, 4, 0),
gsSPNTriangles_5b(0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, yubin_wall04_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[6], 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 3, 2, 1, 1, 0, 4),
gsSPNTriangles_5b(3, 5, 2, 3, 6, 5, 7, 4, 8, 4, 0, 8),
gsSPNTriangles_5b(9, 10, 11, 10, 12, 11, 13, 14, 15, 14, 16, 15),
gsSPNTriangles_5b(15, 17, 11, 9, 11, 17, 15, 16, 17, 18, 4, 7),
gsSPNTriangles_5b(19, 18, 7, 14, 13, 6, 3, 14, 6, 20, 21, 22),
gsSPNTriangles_5b(21, 23, 22, 20, 22, 24, 20, 24, 25, 20, 25, 26),
gsSPNTriangles_5b(27, 26, 25, 28, 29, 30, 29, 31, 30, 0, 0, 0),
gsSPVertex(&rom_yubin_pp_v[38], 32, 0),
gsSPNTrianglesInit_5b(34, 0, 1, 2, 3, 0, 2, 4, 1, 0),
gsSPNTriangles_5b(5, 6, 7, 8, 9, 10, 8, 5, 9, 5, 7, 9),
gsSPNTriangles_5b(7, 10, 9, 5, 11, 6, 11, 12, 6, 5, 13, 11),
gsSPNTriangles_5b(13, 12, 11, 14, 15, 16, 17, 14, 16, 16, 15, 18),
gsSPNTriangles_5b(17, 16, 18, 19, 12, 20, 17, 19, 20, 13, 17, 20),
gsSPNTriangles_5b(13, 20, 12, 17, 21, 19, 17, 22, 21, 17, 18, 22),
gsSPNTriangles_5b(23, 3, 2, 23, 2, 24, 23, 24, 25, 26, 27, 28),
gsSPNTriangles_5b(26, 23, 27, 23, 25, 27, 25, 28, 27, 23, 29, 3),
gsSPNTriangles_5b(29, 30, 3, 23, 31, 29, 31, 30, 29, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_floor_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, yubin_floor01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
gsSPVertex(&rom_yubin_pp_v[70], 32, 0),
gsSPNTrianglesInit_5b(25, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 2, 6, 5, 7, 2, 4, 6, 8, 9, 4, 10),
gsSPNTriangles_5b(4, 8, 10, 11, 12, 13, 3, 14, 15, 16, 3, 0),
gsSPNTriangles_5b(17, 18, 19, 17, 20, 18, 20, 21, 18, 21, 22, 18),
gsSPNTriangles_5b(23, 20, 17, 21, 20, 24, 25, 17, 19, 26, 25, 27),
gsSPNTriangles_5b(26, 17, 25, 26, 23, 17, 21, 28, 22, 29, 30, 31),
gsSPNTriangles_5b(21, 24, 31, 30, 21, 31, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, yubin_floor02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
gsSPVertex(&rom_yubin_pp_v[102], 32, 0),
gsSPNTrianglesInit_5b(24, 0, 1, 2, 3, 4, 5, 6, 3, 5),
gsSPNTriangles_5b(4, 7, 5, 4, 8, 7, 9, 0, 2, 9, 8, 0),
gsSPNTriangles_5b(9, 10, 8, 9, 11, 10, 12, 8, 10, 13, 12, 10),
gsSPNTriangles_5b(13, 10, 14, 11, 15, 10, 13, 14, 16, 17, 18, 19),
gsSPNTriangles_5b(17, 20, 18, 21, 22, 23, 22, 19, 23, 19, 18, 23),
gsSPNTriangles_5b(21, 24, 22, 21, 25, 24, 21, 26, 25, 27, 28, 25),
gsSPNTriangles_5b(29, 30, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPVertex(&rom_yubin_pp_v[133], 3, 0),
gsSPNTrianglesInit_5b(1, 0, 1, 2, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_k_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, yuibn_kaunta03_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_yubin_pp_v[136], 28, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, yuibn_desk01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, yuibn_kaunta02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, yuibn_kaunta01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(6, 16, 17, 18, 16, 18, 19, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, zzzyubin_tree_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, yubin_tree4_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&rom_yubin_pp_v[164], 14, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 0, 3, 4),
gsSPNTriangles_5b(0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, yubin_tree3_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(6, 6, 7, 8, 6, 8, 9, 7, 10, 11),
gsSPNTriangles_5b(7, 11, 8, 10, 12, 13, 10, 13, 11, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_hakari_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, yubin_hakari01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[178], 7, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 2, 1),
gsSPNTriangles_5b(4, 1, 5, 6, 3, 2, 6, 2, 4, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, yubin_us_card_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, yubin_us_card2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[185], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsSPVertex(&rom_yubin_pp_v[189], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 120, 10, 0, 30, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, rom_yubinkyoku_shadow_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[201], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, rom_yubinkyoku_shede_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&rom_yubin_pp_v[209], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
