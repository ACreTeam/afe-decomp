#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

extern u8 lat_sousa_3d_tex[];
extern u8 lat_sousa_ei_tex[];
extern u8 lat_sousa_fuki_tex[];
extern u8 lat_sousa_han1_tex[];
extern u8 lat_sousa_han2_tex[];
extern u8 lat_sousa_henn_tex[];
extern u8 lat_sousa_hira_tex[];
extern u8 lat_sousa_kata_tex[];
extern u8 lat_sousa_keshi_tex[];
extern u8 lat_sousa_kigo_tex[];
extern u8 lat_sousa_list_tex[];
extern u8 lat_sousa_newka1_tex_rgb_ia8[];
extern u8 lat_sousa_newka2_tex_rgb_ia8[];
extern u8 lat_sousa_su_tex[];
extern u8 lat_sousa_tei_tex[];
extern u8 lat_sousa_yame_tex[];
extern u8 lat_tegami_kaso1_tex[];
extern u8 lat_yaji_shita_tex[];

Vtx lat_sousa_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_sousa/lat_sousa_v.inc"
};

Gfx lat_sousa_mode[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_DECAL_LEQUAL),
gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsSPEndDisplayList(),
};

Gfx lat_sousa_sousaT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 125, 205, 225, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 128, lat_sousa_han2_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(lat_sousa_v, 12, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 128, lat_sousa_han1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPNTrianglesInit_5b(4, 4, 5, 6, 5, 7, 6, 8, 9, 10),
gsSPNTriangles_5b(9, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_henT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 64, 32, lat_sousa_fuki_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_waku1T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, anime_2_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_waku2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, lat_sousa_newka1_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[20], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_waku3T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, lat_sousa_newka2_tex_rgb_ia8),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[24], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_3dsT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 215, 215, 215, 255),
gsDPSetEnvColor(10, 10, 10, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, lat_sousa_3d_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[28], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_stT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(0, 0, 0, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[32], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_kirikaeT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 125, 0, 255),
gsDPSetEnvColor(235, 235, 150, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, lat_sousa_list_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[36], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_kesuT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(110, 35, 30, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, lat_sousa_keshi_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[40], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_owariT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(145, 20, 115, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, lat_sousa_yame_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[44], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_teiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(30, 85, 95, 255),
gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, lat_sousa_tei_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[48], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_cursorT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(185, 70, 0, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, lat_tegami_kaso1_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[52], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_henkanT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetEnvColor(60, 30, 85, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, lat_sousa_henn_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[56], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_hiraT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_hira_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[60], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_kataT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_kata_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[64], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_eiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_ei_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[68], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_suT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_su_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[72], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_kigouT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_kigo_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[76], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_jyuT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 160, 160, 160, 255),
gsDPSetEnvColor(0, 0, 0, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[80], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_yT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 170, 170, 170, 255),
gsDPSetEnvColor(60, 60, 60, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 16, anime_2_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&lat_sousa_v[84], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_xT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 180, 180, 180, 255),
gsDPSetEnvColor(60, 60, 60, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, anime_1_txt),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
gsSPVertex(&lat_sousa_v[88], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_yajiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, lat_yaji_shita_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&lat_sousa_v[92], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

u8 lat_sousa_word_combine[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_sousa/lat_sousa_word_combine.inc"
};

u8 lat_sousa_other_combine[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_sousa/lat_sousa_other_combine.inc"
};

u8 lat_sousa_2cycle_combine[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_sousa/lat_sousa_2cycle_combine.inc"
};

Gfx lat_sousa_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(lat_sousa_xT_model),
gsSPDisplayList(lat_sousa_cursorT_model),
gsSPDisplayList(lat_sousa_3dsT_model),
gsSPDisplayList(lat_sousa_yT_model),
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
gsSPDisplayList(lat_sousa_kesuT_model),
gsSPDisplayList(lat_sousa_owariT_model),
gsSPEndDisplayList(),
};

u8 lat_sousa_sp_tex[] = {
#include "assets/forestd/lat_sousa/lat_sousa_sp_tex.inc"
};

Vtx lat_sp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_sousa/lat_sp_v.inc"
};

Gfx lat_sousa_spT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPDisplayList(lat_sousa_mode),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, lat_sousa_sp_tex),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
gsSPVertex(lat_sp_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};

u8 lat_tegami_end_tex[] = {
#include "assets/forestd/lat_sousa/lat_tegami_end_tex.inc"
};

Vtx lat_end_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_sousa/lat_end_v.inc"
};

Gfx lat_end_cordT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsSPDisplayList(lat_sousa_mode),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 0, 135, 0, 255),
gsDPSetEnvColor(255, 255, 255, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureLUT(G_TT_NONE),
gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, lat_tegami_end_tex),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 511, 512),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
gsSPVertex(lat_end_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};
