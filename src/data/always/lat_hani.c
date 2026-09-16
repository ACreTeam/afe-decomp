#include "types.h"
#include "PR/mbi.h"

static u8 lat_fusen_TXT[] = {
#include "assets/forestd/lat_hani/lat_fusen_TXT.inc"
};

Vtx lat_hani_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/lat_hani/lat_hani_v.inc"
};

Gfx lat_hani_senT_model[] ATTRIBUTE_ALIGN(8) = {
gsDPPipeSync(),
gsDPSetPrimColor(0, 255, 0, 0, 255, 255),
gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, lat_fusen_TXT),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPLoadSync(),
gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
gsDPPipeSync(),
gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
gsSPVertex(lat_hani_v, 4, 0),
gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
gsSPEndDisplayList(),
};
