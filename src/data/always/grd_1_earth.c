#include "types.h"
#include "PR/mbi.h"

u16 grd_1_earth_pal[] = {
#include "assets/forestd/grd_1_earth/grd_1_earth_pal.inc"
};

static u8 grd_s_river_tex[] = {
#include "assets/forestd/grd_1_earth/grd_s_river_tex.inc"
};

u8 grd_water1_tex[] = {
#include "assets/forestd/grd_1_earth/grd_water1_tex.inc"
};

static u8 grd_s_grass_tex[] = {
#include "assets/forestd/grd_1_earth/grd_s_grass_tex.inc"
};

Vtx tmpr2_v[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/grd_1_earth/tmpr2_v.inc"
};

u8 tmpr2_grp_grd_s_r1_1_river[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/grd_1_earth/tmpr2_grp_grd_s_r1_1_river.inc"
};

u8 tmpr2_grp_grd_s_r1_1_grass[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/grd_1_earth/tmpr2_grp_grd_s_r1_1_grass.inc"
};

u8 tmpr2_grp_grd_s_r1_1_waterT[] ATTRIBUTE_ALIGN(8) = {
#include "assets/forestd/grd_1_earth/tmpr2_grp_grd_s_r1_1_waterT.inc"
};

Gfx tmpr2_modelT[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(tmpr2_grp_grd_s_r1_1_waterT),
gsSPEndDisplayList(),
};

Gfx tmpr2_model[] ATTRIBUTE_ALIGN(8) = {
gsSPDisplayList(tmpr2_grp_grd_s_r1_1_grass),
gsSPDisplayList(tmpr2_grp_grd_s_r1_1_river),
gsSPEndDisplayList(),
};
