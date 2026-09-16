#include "types.h"
#include "evw_anime.h"

EVW_ANIME_SCROLL grd_player_select_evw_anime_1[] ATTRIBUTE_ALIGN(32) = {
	{ 1, 1, 32, 32 },
	{ 0, 0, 32, 64 }
};

EVW_ANIME_DATA grd_player_select_evw_anime[] = {
	{ -1, EVW_ANIME_TYPE_SCROLL2, grd_player_select_evw_anime_1 }
};
