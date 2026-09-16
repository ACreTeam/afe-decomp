#include "types.h"
#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

extern u8 lat_sousa_henyaji_tex[];

Vtx lat_henyaji_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/henyaji/lat_henyaji_v.inc"
};

Gfx lat_sousa_henyajiT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPSetPrimColor(0, 255, 225, 205, 40, 255),
gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_sousa_henyaji_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
gsSPVertex(lat_henyaji_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
gsSPEndDisplayList(),
};
