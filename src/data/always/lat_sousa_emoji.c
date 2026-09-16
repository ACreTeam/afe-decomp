#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_sousa_ei_tex[];
extern u8 lat_sousa_hira_tex[];
extern u8 lat_sousa_kata_tex[];
extern u8 lat_sousa_kigo_tex[];
extern u8 lat_sousa_list_tex[];
extern u8 lat_sousa_su_tex[];

u8 lat_sousa_emoji_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/lat_sousa_emoji/lat_sousa_emoji_tex.inc"
};

Vtx lat_sousa_pp_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_sousa_emoji/lat_sousa_pp_v.inc"
};

Gfx lat_sousa_kirikae2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 255, 125, 0, 255),
gsDPSetEnvColor(235, 235, 150, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, lat_sousa_list_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(lat_sousa_pp_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_hira2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_hira_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_sousa_pp_v[4], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_kigou2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_kigo_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_sousa_pp_v[8], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_kata2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_kata_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_sousa_pp_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_ei2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_ei_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_sousa_pp_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_su2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_su_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_sousa_pp_v[20], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx lat_sousa_emoji2T_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 48, 16, lat_sousa_emoji_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&lat_sousa_pp_v[24], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
