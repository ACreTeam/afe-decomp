#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

u16 rom_yami_wall_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_wall_pal.inc"
};

u16 rom_yami_floor_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_floor_pal.inc"
};

u16 rom_yami_box_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_box_pal.inc"
};

u16 rom_yami_mono01_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_mono01_pal.inc"
};

u16 rom_yami_mono02_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_mono02_pal.inc"
};

u16 rom_yami_mono03_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_mono03_pal.inc"
};

u16 rom_yami_qup_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_qup_pal.inc"
};

u16 rom_yami_hyou_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_hyou_pal.inc"
};

u16 rom_yami_step_tex_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_step_tex_pal.inc"
};

u16 rom_yami_hugu_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_hugu_pal.inc"
};

u16 rom_yami_tama_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_tama_pal.inc"
};

u8 rom_yami_wall_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_wall_tex.inc"
};

u8 rom_yami_floor_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_floor_tex.inc"
};

u8 rom_yami_poll_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_poll_tex.inc"
};

u8 rom_yami_box01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_box01_tex.inc"
};

u8 rom_yami_box02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_box02_tex.inc"
};

u8 rom_yami_mono01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_mono01_tex.inc"
};

u8 rom_yami_mono02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_mono02_tex.inc"
};

u8 rom_yami_mono03_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_mono03_tex.inc"
};

u8 rom_yami_qup_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_qup_tex.inc"
};

u8 rom_yami_hyou_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_hyou_tex.inc"
};

u8 rom_yami_hyou02_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_hyou02_tex.inc"
};

u8 rom_yami_step_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_step_tex.inc"
};

u8 rom_yami_hugu_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_hugu_tex.inc"
};

u8 rom_yami_tama_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_tama_tex.inc"
};

u8 rom_yami_shadow01_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/rom_yami_wall/rom_yami_shadow01_tex.inc"
};

Vtx grd_yamishop_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/rom_yami_wall/grd_yamishop_v.inc"
};

Gfx grd_yamishop_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPEndDisplayList(),
};

Gfx grd_yamishop_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_hugu_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, rom_yami_hugu_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(&grd_yamishop_v[226], 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_tama_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, rom_yami_tama_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[232], 6, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_hyou_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_yami_hyou02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[238], 12, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_yami_hyou_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPNTrianglesInit_5b(4, 6, 7, 8, 6, 8, 9, 7, 10, 11),
gsSPNTriangles_5b(7, 11, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_qup_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, rom_yami_qup_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[250], 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_mono01_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_yami_mono01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[255], 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_mono02_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, rom_yami_mono02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[260], 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 1, 3, 2, 1, 4, 3),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_mono03_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, rom_yami_mono03_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[265], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_step_tex_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, rom_yami_step_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(grd_yamishop_v, 5, 0),
gsSPNTrianglesInit_5b(3, 0, 1, 2, 2, 3, 0, 0, 4, 1),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, rom_yami_wall_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[5], 32, 0),
gsSPNTrianglesInit_5b(35, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 6, 8, 2, 0, 2, 8, 6, 7, 8),
gsSPNTriangles_5b(9, 6, 2, 10, 11, 3, 10, 9, 11, 9, 2, 11),
gsSPNTriangles_5b(2, 3, 11, 9, 12, 6, 12, 4, 6, 9, 13, 12),
gsSPNTriangles_5b(13, 4, 12, 14, 15, 16, 17, 14, 16, 16, 15, 18),
gsSPNTriangles_5b(17, 16, 18, 19, 4, 20, 17, 19, 20, 13, 17, 20),
gsSPNTriangles_5b(13, 20, 4, 17, 18, 19, 18, 21, 22, 23, 19, 22),
gsSPNTriangles_5b(18, 22, 19, 24, 21, 18, 15, 24, 18, 5, 4, 19),
gsSPNTriangles_5b(23, 5, 19, 25, 26, 27, 26, 28, 27, 29, 30, 31),
gsSPVertex(&grd_yamishop_v[37], 13, 0),
gsSPNTrianglesInit_5b(13, 0, 1, 2, 2, 3, 4, 5, 4, 3),
gsSPNTriangles_5b(2, 1, 3, 6, 2, 4, 7, 8, 9, 7, 6, 8),
gsSPNTriangles_5b(6, 4, 8, 4, 9, 8, 6, 10, 2, 10, 11, 2),
gsSPNTriangles_5b(6, 12, 10, 12, 11, 10, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_floor_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, rom_yami_floor_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&grd_yamishop_v[50], 32, 0),
gsSPNTrianglesInit_5b(23, 0, 1, 2, 0, 3, 1, 3, 0, 4),
gsSPNTriangles_5b(0, 5, 4, 6, 7, 1, 8, 9, 6, 10, 11, 12),
gsSPNTriangles_5b(10, 13, 11, 14, 15, 16, 14, 17, 15, 17, 18, 19),
gsSPNTriangles_5b(20, 21, 13, 13, 17, 14, 22, 23, 2, 22, 24, 23),
gsSPNTriangles_5b(24, 25, 23, 25, 12, 23, 26, 24, 22, 25, 24, 27),
gsSPNTriangles_5b(28, 29, 5, 28, 30, 29, 28, 31, 30, 28, 16, 31),
gsSPVertex(&grd_yamishop_v[82], 32, 0),
gsSPNTrianglesInit_5b(22, 0, 1, 2, 3, 1, 4, 5, 6, 7),
gsSPNTriangles_5b(6, 8, 7, 5, 9, 6, 10, 6, 11, 5, 7, 12),
gsSPNTriangles_5b(7, 8, 13, 14, 15, 9, 16, 14, 17, 16, 15, 14),
gsSPNTriangles_5b(16, 18, 15, 19, 20, 12, 0, 2, 21, 22, 0, 21),
gsSPNTriangles_5b(23, 22, 21, 24, 25, 11, 26, 27, 28, 24, 29, 28),
gsSPNTriangles_5b(27, 24, 28, 13, 30, 4, 31, 3, 4, 0, 0, 0),
gsSPVertex(&grd_yamishop_v[114], 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 3, 1, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_wall_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_yami_poll_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[118], 32, 0),
gsSPNTrianglesInit_5b(26, 0, 1, 2, 0, 2, 3, 1, 4, 5),
gsSPNTriangles_5b(1, 5, 2, 4, 6, 7, 4, 7, 5, 8, 9, 1),
gsSPNTriangles_5b(8, 1, 0, 9, 10, 4, 9, 4, 1, 10, 11, 6),
gsSPNTriangles_5b(10, 6, 4, 12, 13, 14, 12, 14, 15, 13, 16, 17),
gsSPNTriangles_5b(13, 17, 14, 16, 18, 19, 16, 19, 17, 20, 21, 22),
gsSPNTriangles_5b(20, 22, 23, 21, 24, 25, 21, 25, 22, 26, 20, 23),
gsSPNTriangles_5b(26, 23, 27, 28, 29, 30, 28, 30, 31, 0, 0, 0),
gsSPVertex(&grd_yamishop_v[150], 24, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 9, 12, 13),
gsSPNTriangles_5b(9, 13, 10, 14, 8, 11, 14, 11, 15, 16, 17, 18),
gsSPNTriangles_5b(16, 18, 19, 17, 20, 21, 17, 21, 18, 22, 16, 19),
gsSPNTriangles_5b(22, 19, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadTLUT_Dolphin(15, 16, 1, rom_yami_box_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, rom_yami_box02_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(&grd_yamishop_v[174], 8, 0),
gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, rom_yami_box01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[182], 28, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 1),
gsSPNTriangles_5b(4, 1, 0, 6, 7, 8, 6, 8, 9, 10, 11, 12),
gsSPNTriangles_5b(10, 12, 13, 14, 15, 16, 14, 16, 17, 18, 19, 20),
gsSPNTriangles_5b(18, 20, 21, 22, 23, 19, 22, 19, 18, 24, 25, 26),
gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 150, 10, 10, 30, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 32, rom_yami_shadow01_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
gsSPVertex(&grd_yamishop_v[210], 16, 0),
gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
