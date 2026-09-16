#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/mbi.h"

Vtx win_syasin_error_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/win_syasin_error/win_syasin_error_v.inc"
};

Gfx win_syasin_error1_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 150, 50, 50, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsSPVertex(win_syasin_error_v, 12, 0),
gsSPNTrianglesInit_5b(10, 0, 1, 2, 1, 3, 2, 4, 1, 5),
gsSPNTriangles_5b(4, 6, 1, 7, 8, 9, 8, 6, 9, 10, 8, 11),
gsSPNTriangles_5b(10, 3, 8, 3, 1, 8, 1, 6, 8, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx win_syasin_error2_model[] ATTRIBUTE_ALIGN(8) = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
gsDPSetPrimColor(0, 255, 65, 65, 65, 255),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
gsSPVertex(&win_syasin_error_v[12], 16, 0),
gsSPNTrianglesInit_5b(16, 0, 1, 2, 1, 3, 2, 4, 5, 6),
gsSPNTriangles_5b(5, 7, 6, 0, 2, 8, 6, 9, 4, 10, 3, 1),
gsSPNTriangles_5b(5, 11, 7, 8, 9, 0, 9, 6, 0, 7, 10, 1),
gsSPNTriangles_5b(7, 11, 10, 11, 12, 10, 4, 13, 5, 9, 8, 14),
gsSPNTriangles_5b(15, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

Gfx win_syasin_base_error_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(win_syasin_error1_model),
gsSPDisplayList(win_syasin_error2_model),
gsSPEndDisplayList(),
};
