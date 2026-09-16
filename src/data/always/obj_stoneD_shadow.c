#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

Vtx obj_stoneD_shadow_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_stoneD_shadow/obj_stoneD_shadow_v.inc"
};

Gfx obj_stoneD_shadowT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 3, 2, 5, 3, 5, 4, 0, 0, 0),
gsSPEndDisplayList(),
};
