#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

Vtx des_sen_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/des_sen/des_sen_v.inc"
};

Gfx des_sen_waku_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 90, 90, 90, 255),
gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),
gsSPVertex(des_sen_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
