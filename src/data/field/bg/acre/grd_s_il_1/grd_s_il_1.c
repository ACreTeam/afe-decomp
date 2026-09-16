#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave2_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 sand_tex_dummy[];
extern u8 beach_pal_dummy2[];
extern u8 beach2_tex_dummy2[];
extern u8 beach1_tex_dummy2[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_il_1_v[] = {
#include "assets/field/bg/grd_s_il_1_v.inc"
};

extern Gfx grd_s_il_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_il_1_v[145], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        3, 4, 2, // tri1
        1, 3, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 3, 1, // tri0
        6, 5, 1, // tri1
        7, 6, 1, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 9, // tri0
        11, 12, 9, // tri1
        11, 13, 12, // tri2
        11, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        14, 16, 15, // tri1
        16, 17, 15, // tri2
        17, 18, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        19, 20, 18, // tri1
        20, 21, 18, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 21, // tri0
        22, 24, 23, // tri1
        24, 25, 23, // tri2
        25, 26, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 27, 26, // tri0
        25, 28, 27, // tri1
        28, 29, 27, // tri2
        28, 30, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_il_1_v[177], 3, 0),
    gsSPNTrianglesInit_5b(
        1, // tri count
        0, 1, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_il_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        30, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        5, 6, 4, // tri1
        5, 7, 6, // tri2
        0, 8, 1 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 6, // tri0
        7, 10, 9, // tri1
        10, 11, 9, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        12, 14, 13, // tri1
        14, 15, 13, // tri2
        15, 16, 13 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        17, 18, 16, // tri1
        18, 19, 16, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 19, // tri0
        21, 22, 19, // tri1
        21, 23, 22, // tri2
        23, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 22, // tri0
        24, 26, 25, // tri1
        26, 27, 25, // tri2
        26, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 27, // tri0
        29, 30, 27, // tri1
        29, 31, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_il_1_v[32], 5, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_il_1_v[37], 8, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        2, 1, 4 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        4, 5, 6, // tri1
        5, 7, 6, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_il_1_v[45], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 8, 9, // tri1
        8, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        10, 14, 11, // tri0
        15, 16, 17, // tri1
        12, 15, 13, // tri2
        16, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 21, // tri0
        20, 22, 21, // tri1
        23, 24, 25, // tri2
        26, 23, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        28, 30, 22, // tri1
        29, 26, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_il_1_v[77], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        0, 3, 4, // tri1
        5, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        6, 5, 3, // tri0
        7, 8, 6, // tri1
        9, 10, 7, // tri2
        11, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        11, 14, 13, // tri1
        14, 15, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_il_1_v[94], 32, 0),
    gsSPNTrianglesInit_5b(
        32, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 2, 6, // tri0
        2, 4, 6, // tri1
        5, 7, 2, // tri2
        7, 8, 2 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 0, // tri0
        9, 10, 0, // tri1
        11, 4, 12, // tri2
        11, 6, 4 // tri3
    ),
    gsSPNTriangles_5b(
        8, 0, 2, // tri0
        13, 14, 15, // tri1
        14, 16, 15, // tri2
        14, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        14, 18, 17, // tri0
        15, 19, 20, // tri1
        15, 16, 19, // tri2
        16, 10, 19 // tri3
    ),
    gsSPNTriangles_5b(
        10, 9, 19, // tri0
        3, 21, 4, // tri1
        21, 22, 4, // tri2
        22, 12, 4 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 12, // tri0
        22, 24, 23, // tri1
        22, 25, 24, // tri2
        3, 26, 21 // tri3
    ),
    gsSPNTriangles_5b(
        3, 27, 26, // tri0
        27, 28, 26, // tri1
        27, 29, 28, // tri2
        27, 30, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_il_1_v[126], 11, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        1, 7, 2, // tri0
        7, 8, 2, // tri1
        7, 9, 8, // tri2
        9, 10, 8 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_il_1_v[137], 8, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        2, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        2, 3, 4, // tri0
        5, 4, 6, // tri1
        4, 7, 6, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_il_1_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, wave2_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(DAT_0b000000),
    gsSPVertex(&grd_s_il_1_v[180], 12, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        2, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        2, 3, 4, // tri0
        5, 4, 6, // tri1
        4, 7, 6, // tri2
        1, 8, 3 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 3, // tri0
        3, 10, 4, // tri1
        3, 9, 10, // tri2
        4, 11, 7 // tri3
    ),
    gsSPNTriangles_5b(
        4, 10, 11, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_il_1_v[192], 25, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        5, 8, 6, // tri1
        8, 9, 6, // tri2
        9, 10, 6 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        11, 12, 10, // tri1
        12, 13, 10, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 15, 14, // tri0
        15, 16, 14, // tri1
        15, 17, 16, // tri2
        17, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        19, 20, 18, // tri1
        20, 21, 18, // tri2
        19, 22, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 23, 22, // tri0
        23, 2, 22, // tri1
        23, 0, 2, // tri2
        14, 24, 13 // tri3
    ),
    gsSPEndDisplayList(),
};
