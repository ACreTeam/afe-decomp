#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

Vtx obj_s_stoneB_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/obj_s_stoneB/obj_s_stoneB_v.inc"
};

Gfx obj_s_stoneB_gfx_model[] ATTRIBUTE_ALIGN(8) = {
gsSPVertex(obj_s_stoneB_v, 12, 0),
gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(1, 5, 3, 5, 6, 3, 1, 7, 5, 3, 8, 4),
gsSPNTriangles_5b(8, 9, 4, 3, 6, 8, 0, 10, 1, 10, 7, 1),
gsSPNTriangles_5b(0, 11, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};
