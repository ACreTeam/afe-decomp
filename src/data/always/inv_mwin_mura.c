#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 inv_mwin_mura_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/forestd/inv_mwin_mura/inv_mwin_mura_tex.inc"
};

Vtx inv_mura_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/inv_mwin_mura/inv_mura_v.inc"
};

Gfx inv_mwin_muraT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, inv_mwin_mura_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(inv_mura_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};
