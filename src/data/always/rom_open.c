#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_open_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_open/rom_open_pal.inc"
};

u8 rom_open_floor_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_open/rom_open_floor_tex.inc"
};

u8 rom_open_shade_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_open/rom_open_shade_tex.inc"
};

u8 rom_open_spot2_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_open/rom_open_spot2_tex_rgb_i4.inc"
};

u8 rom_open_spot_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_open/rom_open_spot_tex.inc"
};

Vtx grd_player_select_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_open/grd_player_select_v.inc"
};

Gfx grd_player_select_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, TEXEL1, TEXEL1, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
gsDPSetPrimColor(0, 150, 255, 255, 255, 255),
gsDPSetEnvColor(255, 255, 130, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, rom_open_spot2_tex_rgb_i4),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 15, 15),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 32, 64, rom_open_spot_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPDisplayList(anime_1_txt),
gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&grd_player_select_v[12], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 0, 0, 0, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, rom_open_shade_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&grd_player_select_v[16], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx grd_player_select_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_open_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_open_floor_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(grd_player_select_v, 12, 0),
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
gsSPEndDisplayList(),
};
