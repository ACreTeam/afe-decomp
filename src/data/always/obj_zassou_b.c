#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

Vtx obj_zassou_b_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_zassou_b/obj_zassou_b_v.inc"
};

Gfx obj_zassou_bT_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_zassou_b_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList(),
};
