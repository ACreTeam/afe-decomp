#include "types.h"
#include "evw_anime.h"

extern u8 clk_num_00_tex_rgb_ia8[];
extern u8 clk_num_01_tex_rgb_ia8[];
extern u8 clk_num_02_tex_rgb_ia8[];
extern u8 clk_num_03_tex_rgb_ia8[];
extern u8 clk_num_04_tex_rgb_ia8[];
extern u8 clk_num_05_tex_rgb_ia8[];
extern u8 clk_num_06_tex_rgb_ia8[];
extern u8 clk_num_07_tex_rgb_ia8[];
extern u8 clk_num_08_tex_rgb_ia8[];
extern u8 clk_num_09_tex_rgb_ia8[];

void* clk_min01_a_evw_anime_1_tex_table[] = {
clk_num_01_tex_rgb_ia8, clk_num_02_tex_rgb_ia8, clk_num_03_tex_rgb_ia8, clk_num_04_tex_rgb_ia8, clk_num_05_tex_rgb_ia8, clk_num_06_tex_rgb_ia8, clk_num_07_tex_rgb_ia8, clk_num_08_tex_rgb_ia8, clk_num_09_tex_rgb_ia8, clk_num_00_tex_rgb_ia8
};

u8 clk_min01_a_evw_anime_1_anime_ptn[] = {
0,
1,
2,
3,
4,
5,
6,
7,
8,
9
};

EVW_ANIME_TEXANIME clk_min01_a_evw_anime_1[] = {
	{ ARRAY_COUNT(clk_min01_a_evw_anime_1_anime_ptn), 0, clk_min01_a_evw_anime_1_tex_table, clk_min01_a_evw_anime_1_anime_ptn, NULL }
};

EVW_ANIME_SCROLL clk_min01_a_evw_anime_2[] = {
	{ 0, 10, 32, 64 },
	{ 0, 0, 0, 0 }
};

EVW_ANIME_DATA clk_min01_a_evw_anime[] = {
	{ 1, EVW_ANIME_TYPE_TEXANIME, clk_min01_a_evw_anime_1 },
	{ -2, EVW_ANIME_TYPE_SCROLL2, clk_min01_a_evw_anime_2 }
};
