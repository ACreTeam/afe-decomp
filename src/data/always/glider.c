#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

Vtx glider_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/glider/glider_v.inc"
};

Gfx glider_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_OFF),
gsDPPipeSync(),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPVertex(glider_v, 11, 0),
gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
gsSP2Triangles(6, 7, 8, 0, 4, 9, 10, 0),
gsSPEndDisplayList(),
};
