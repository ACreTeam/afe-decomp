#include "m_field_make.h"
#include "m_field_info.h"

extern Gfx room01_model[];
extern Gfx myr_etc_model[];
extern Gfx tmp_model[];
extern Gfx tmp_modelT[];
extern Gfx tmp2_model[];
extern Gfx tmp2_modelT[];
extern Gfx tmpr_model[];
extern Gfx tmpr_modelT[];
extern EVW_ANIME_DATA tmpr_evw_anime[];
extern Gfx tmpr2_model[];
extern Gfx tmpr2_modelT[];
extern EVW_ANIME_DATA tmpr2_evw_anime[];
extern Gfx tmp3_model[];
extern Gfx tmp3_modelT[];
extern Gfx tmpr3_model[];
extern Gfx tmpr3_modelT[];
extern EVW_ANIME_DATA tmpr3_evw_anime[];
extern Gfx tmp4_model[];
extern Gfx tmp4_modelT[];
extern Gfx tmpr4_model[];
extern Gfx tmpr4_modelT[];
extern EVW_ANIME_DATA tmpr4_evw_anime[];
extern Gfx grd_s_c1_r1_1_model[];
extern Gfx grd_s_c1_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_c1_r1_1_evw_anime[];
extern Gfx grd_s_c1_s_1_model[];
extern Gfx grd_s_c1_s_1_modelT[];
extern Gfx grd_s_c2_r1_1_model[];
extern Gfx grd_s_c2_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_c2_r1_1_evw_anime[];
extern Gfx grd_s_c2_r2_1_model[];
extern Gfx grd_s_c2_r2_1_modelT[];
extern EVW_ANIME_DATA grd_s_c2_r2_1_evw_anime[];
extern Gfx grd_s_c5_r1_1_model[];
extern Gfx grd_s_c5_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_c5_r1_1_evw_anime[];
extern Gfx grd_s_t_r1_1_model[];
extern Gfx grd_s_t_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_t_r1_1_evw_anime[];
extern Gfx grd_s_f_1_model[];
extern Gfx grd_s_f_1_modelT[];
extern Gfx grd_s_f_2_model[];
extern Gfx grd_s_f_2_modelT[];
extern Gfx grd_s_c1_1_model[];
extern Gfx grd_s_c1_1_modelT[];
extern Gfx grd_s_c1_r2_1_model[];
extern Gfx grd_s_c1_r2_1_modelT[];
extern EVW_ANIME_DATA grd_s_c1_r2_1_evw_anime[];
extern Gfx grd_s_c1_r3_1_model[];
extern Gfx grd_s_c1_r3_1_modelT[];
extern EVW_ANIME_DATA grd_s_c1_r3_1_evw_anime[];
extern Gfx grd_s_c2_1_model[];
extern Gfx grd_s_c2_1_modelT[];
extern Gfx grd_s_c3_1_model[];
extern Gfx grd_s_c3_1_modelT[];
extern Gfx grd_s_c3_r1_1_model[];
extern Gfx grd_s_c3_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_c3_r1_1_evw_anime[];
extern Gfx grd_s_c4_1_model[];
extern Gfx grd_s_c4_1_modelT[];
extern Gfx grd_s_c4_r1_1_model[];
extern Gfx grd_s_c4_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_c4_r1_1_evw_anime[];
extern Gfx grd_s_c4_r2_1_model[];
extern Gfx grd_s_c4_r2_1_modelT[];
extern EVW_ANIME_DATA grd_s_c4_r2_1_evw_anime[];
extern Gfx grd_s_c5_1_model[];
extern Gfx grd_s_c5_1_modelT[];
extern Gfx grd_s_c5_r2_1_model[];
extern Gfx grd_s_c5_r2_1_modelT[];
extern EVW_ANIME_DATA grd_s_c5_r2_1_evw_anime[];
extern Gfx grd_s_c5_r3_1_model[];
extern Gfx grd_s_c5_r3_1_modelT[];
extern EVW_ANIME_DATA grd_s_c5_r3_1_evw_anime[];
extern Gfx grd_s_c6_1_model[];
extern Gfx grd_s_c6_1_modelT[];
extern Gfx grd_s_c6_r1_1_model[];
extern Gfx grd_s_c6_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_c6_r1_1_evw_anime[];
extern Gfx grd_s_c7_1_model[];
extern Gfx grd_s_c7_1_modelT[];
extern Gfx grd_s_r1_1_model[];
extern Gfx grd_s_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_r1_1_evw_anime[];
extern Gfx grd_s_r2_1_model[];
extern Gfx grd_s_r2_1_modelT[];
extern EVW_ANIME_DATA grd_s_r2_1_evw_anime[];
extern Gfx grd_s_r3_1_model[];
extern Gfx grd_s_r3_1_modelT[];
extern EVW_ANIME_DATA grd_s_r3_1_evw_anime[];
extern Gfx grd_s_r4_1_model[];
extern Gfx grd_s_r4_1_modelT[];
extern EVW_ANIME_DATA grd_s_r4_1_evw_anime[];
extern Gfx grd_s_r5_1_model[];
extern Gfx grd_s_r5_1_modelT[];
extern EVW_ANIME_DATA grd_s_r5_1_evw_anime[];
extern Gfx grd_s_r6_1_model[];
extern Gfx grd_s_r6_1_modelT[];
extern EVW_ANIME_DATA grd_s_r6_1_evw_anime[];
extern Gfx grd_s_r7_1_model[];
extern Gfx grd_s_r7_1_modelT[];
extern EVW_ANIME_DATA grd_s_r7_1_evw_anime[];
extern Gfx grd_s_c3_r2_1_model[];
extern Gfx grd_s_c3_r2_1_modelT[];
extern EVW_ANIME_DATA grd_s_c3_r2_1_evw_anime[];
extern Gfx grd_s_c7_r3_1_model[];
extern Gfx grd_s_c7_r3_1_modelT[];
extern EVW_ANIME_DATA grd_s_c7_r3_1_evw_anime[];
extern Gfx grd_s_c6_r3_1_model[];
extern Gfx grd_s_c6_r3_1_modelT[];
extern EVW_ANIME_DATA grd_s_c6_r3_1_evw_anime[];
extern Gfx grd_s_r1_b_1_model[];
extern Gfx grd_s_r1_b_1_modelT[];
extern EVW_ANIME_DATA grd_s_r1_b_1_evw_anime[];
extern Gfx grd_s_r2_b_1_model[];
extern Gfx grd_s_r2_b_1_modelT[];
extern EVW_ANIME_DATA grd_s_r2_b_1_evw_anime[];
extern Gfx grd_s_r3_b_1_model[];
extern Gfx grd_s_r3_b_1_modelT[];
extern EVW_ANIME_DATA grd_s_r3_b_1_evw_anime[];
extern Gfx grd_s_r4_b_1_model[];
extern Gfx grd_s_r4_b_1_modelT[];
extern EVW_ANIME_DATA grd_s_r4_b_1_evw_anime[];
extern Gfx grd_s_r5_b_1_model[];
extern Gfx grd_s_r5_b_1_modelT[];
extern EVW_ANIME_DATA grd_s_r5_b_1_evw_anime[];
extern Gfx grd_s_r6_b_1_model[];
extern Gfx grd_s_r6_b_1_modelT[];
extern EVW_ANIME_DATA grd_s_r6_b_1_evw_anime[];
extern Gfx grd_s_r7_b_1_model[];
extern Gfx grd_s_r7_b_1_modelT[];
extern EVW_ANIME_DATA grd_s_r7_b_1_evw_anime[];
extern Gfx grd_s_t_1_model[];
extern Gfx grd_s_t_1_modelT[];
extern EVW_ANIME_DATA grd_s_t_1_evw_anime[];
extern Gfx grd_s_c1_s_2_model[];
extern Gfx grd_s_c1_s_2_modelT[];
extern Gfx grd_s_c2_s_1_model[];
extern Gfx grd_s_c2_s_1_modelT[];
extern Gfx grd_s_c3_s_1_model[];
extern Gfx grd_s_c3_s_1_modelT[];
extern EVW_ANIME_DATA grd_s_c3_s_1_evw_anime[];
extern Gfx grd_s_c4_s_1_model[];
extern Gfx grd_s_c4_s_1_modelT[];
extern Gfx grd_s_c5_s_1_model[];
extern Gfx grd_s_c5_s_1_modelT[];
extern Gfx grd_s_c6_s_1_model[];
extern Gfx grd_s_c6_s_1_modelT[];
extern Gfx grd_s_c7_s_1_model[];
extern Gfx grd_s_c4_r3_1_model[];
extern Gfx grd_s_c4_r3_1_modelT[];
extern EVW_ANIME_DATA grd_s_c4_r3_1_evw_anime[];
extern Gfx grd_s_c7_r1_1_model[];
extern Gfx grd_s_c7_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_c7_r1_1_evw_anime[];
extern Gfx grd_s_t_st1_1_model[];
extern Gfx grd_s_t_st1_1_modelT[];
extern Gfx grd_s_c1_2_model[];
extern Gfx grd_s_c1_2_modelT[];
extern Gfx grd_s_c1_3_model[];
extern Gfx grd_s_c1_3_modelT[];
extern Gfx grd_s_c1_4_model[];
extern Gfx grd_s_c1_4_modelT[];
extern Gfx grd_s_c1_5_model[];
extern Gfx grd_s_c1_5_modelT[];
extern Gfx grd_s_c2_2_model[];
extern Gfx grd_s_c2_2_modelT[];
extern Gfx grd_s_r1_2_model[];
extern Gfx grd_s_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_r1_2_evw_anime[];
extern Gfx grd_s_r1_3_model[];
extern Gfx grd_s_r1_3_modelT[];
extern EVW_ANIME_DATA grd_s_r1_3_evw_anime[];
extern Gfx grd_s_r4_2_model[];
extern Gfx grd_s_r4_2_modelT[];
extern EVW_ANIME_DATA grd_s_r4_2_evw_anime[];
extern Gfx grd_s_r5_2_model[];
extern Gfx grd_s_r5_2_modelT[];
extern EVW_ANIME_DATA grd_s_r5_2_evw_anime[];
extern Gfx grd_s_r7_2_model[];
extern Gfx grd_s_r7_2_modelT[];
extern EVW_ANIME_DATA grd_s_r7_2_evw_anime[];
extern Gfx grd_s_r7_3_model[];
extern Gfx grd_s_r7_3_modelT[];
extern EVW_ANIME_DATA grd_s_r7_3_evw_anime[];
extern Gfx grd_s_c2_s_2_model[];
extern Gfx grd_s_c2_s_2_modelT[];
extern Gfx grd_s_c1_s_3_model[];
extern Gfx grd_s_c4_s_2_model[];
extern Gfx grd_s_c4_s_2_modelT[];
extern Gfx grd_s_c5_s_2_model[];
extern Gfx grd_s_c6_r1_2_model[];
extern Gfx grd_s_c6_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_c6_r1_2_evw_anime[];
extern Gfx grd_s_c3_r1_2_model[];
extern Gfx grd_s_c3_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_c3_r1_2_evw_anime[];
extern Gfx grd_s_c3_2_model[];
extern Gfx grd_s_c3_2_modelT[];
extern EVW_ANIME_DATA grd_s_c3_2_evw_anime[];
extern Gfx grd_s_c7_3_model[];
extern Gfx grd_s_c7_3_modelT[];
extern EVW_ANIME_DATA grd_s_c7_3_evw_anime[];
extern Gfx grd_s_c1_r2_2_model[];
extern Gfx grd_s_c1_r2_2_modelT[];
extern EVW_ANIME_DATA grd_s_c1_r2_2_evw_anime[];
extern Gfx grd_s_c1_r3_2_model[];
extern Gfx grd_s_c1_r3_2_modelT[];
extern EVW_ANIME_DATA grd_s_c1_r3_2_evw_anime[];
extern Gfx grd_s_c4_2_model[];
extern Gfx grd_s_c4_2_modelT[];
extern Gfx grd_s_c5_2_model[];
extern Gfx grd_s_c5_2_modelT[];
extern Gfx grd_s_c6_2_model[];
extern Gfx grd_s_c6_2_modelT[];
extern Gfx grd_s_r2_2_model[];
extern Gfx grd_s_r2_2_modelT[];
extern EVW_ANIME_DATA grd_s_r2_2_evw_anime[];
extern Gfx grd_s_r3_2_model[];
extern Gfx grd_s_r3_2_modelT[];
extern EVW_ANIME_DATA grd_s_r3_2_evw_anime[];
extern Gfx grd_s_c4_r1_2_model[];
extern Gfx grd_s_c4_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_c4_r1_2_evw_anime[];
extern Gfx grd_s_c4_r2_2_model[];
extern Gfx grd_s_c4_r2_2_modelT[];
extern EVW_ANIME_DATA grd_s_c4_r2_2_evw_anime[];
extern Gfx grd_s_c7_r1_2_model[];
extern Gfx grd_s_c7_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_c7_r1_2_evw_anime[];
extern Gfx grd_s_c6_2_model[];
extern Gfx grd_s_c6_2_modelT[];
extern Gfx grd_s_c5_r2_2_model[];
extern Gfx grd_s_c5_r2_2_modelT[];
extern EVW_ANIME_DATA grd_s_c5_r2_2_evw_anime[];
extern Gfx grd_s_c4_r3_2_model[];
extern Gfx grd_s_c4_r3_2_modelT[];
extern EVW_ANIME_DATA grd_s_c4_r3_2_evw_anime[];
extern Gfx grd_s_r2_3_model[];
extern Gfx grd_s_r2_3_modelT[];
extern EVW_ANIME_DATA grd_s_r2_3_evw_anime[];
extern Gfx grd_s_r3_3_model[];
extern Gfx grd_s_r3_3_modelT[];
extern EVW_ANIME_DATA grd_s_r3_3_evw_anime[];
extern Gfx grd_s_c5_r3_2_model[];
extern Gfx grd_s_c5_r3_2_modelT[];
extern EVW_ANIME_DATA grd_s_c5_r3_2_evw_anime[];
extern Gfx grd_s_c5_3_model[];
extern Gfx grd_s_c5_3_modelT[];
extern Gfx grd_s_c4_3_model[];
extern Gfx grd_s_c4_3_modelT[];
extern Gfx grd_s_c3_3_model[];
extern Gfx grd_s_c3_3_modelT[];
extern Gfx grd_s_c2_3_model[];
extern Gfx grd_s_c2_3_modelT[];
extern EVW_ANIME_DATA grd_s_c2_3_evw_anime[];
extern Gfx grd_s_r1_p_1_model[];
extern Gfx grd_s_r1_p_1_modelT[];
extern EVW_ANIME_DATA grd_s_r1_p_1_evw_anime[];
extern Gfx grd_s_r6_2_model[];
extern Gfx grd_s_r6_2_modelT[];
extern EVW_ANIME_DATA grd_s_r6_2_evw_anime[];
extern Gfx police_indoor_model[];
extern Gfx police_indoor_modelT[];
extern Gfx grd_s_c1_r1_2_model[];
extern Gfx grd_s_c1_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_c1_r1_2_evw_anime[];
extern Gfx grd_s_c1_r1_3_model[];
extern Gfx grd_s_c1_r1_3_modelT[];
extern EVW_ANIME_DATA grd_s_c1_r1_3_evw_anime[];
extern Gfx grd_s_c1_r2_3_model[];
extern Gfx grd_s_c1_r2_3_modelT[];
extern EVW_ANIME_DATA grd_s_c1_r2_3_evw_anime[];
extern Gfx grd_s_c1_r3_3_model[];
extern Gfx grd_s_c1_r3_3_modelT[];
extern EVW_ANIME_DATA grd_s_c1_r3_3_evw_anime[];
extern Gfx grd_s_c2_r1_2_model[];
extern Gfx grd_s_c2_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_c2_r1_2_evw_anime[];
extern Gfx grd_s_c5_r1_2_model[];
extern Gfx grd_s_c5_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_c5_r1_2_evw_anime[];
extern Gfx grd_s_c6_3_model[];
extern Gfx grd_s_c6_3_modelT[];
extern Gfx grd_s_c7_2_model[];
extern Gfx grd_s_c7_2_modelT[];
extern Gfx grd_s_r1_4_model[];
extern Gfx grd_s_r1_4_modelT[];
extern EVW_ANIME_DATA grd_s_r1_4_evw_anime[];
extern Gfx grd_s_r2_4_model[];
extern Gfx grd_s_r2_4_modelT[];
extern EVW_ANIME_DATA grd_s_r2_4_evw_anime[];
extern Gfx grd_s_r3_4_model[];
extern Gfx grd_s_r3_4_modelT[];
extern EVW_ANIME_DATA grd_s_r3_4_evw_anime[];
extern Gfx grd_s_r4_3_model[];
extern Gfx grd_s_r4_3_modelT[];
extern EVW_ANIME_DATA grd_s_r4_3_evw_anime[];
extern Gfx grd_s_r5_3_model[];
extern Gfx grd_s_r5_3_modelT[];
extern EVW_ANIME_DATA grd_s_r5_3_evw_anime[];
extern Gfx grd_s_r6_3_model[];
extern Gfx grd_s_r6_3_modelT[];
extern EVW_ANIME_DATA grd_s_r6_3_evw_anime[];
extern Gfx grd_s_c2_r2_2_model[];
extern Gfx grd_s_c2_r2_2_modelT[];
extern EVW_ANIME_DATA grd_s_c2_r2_2_evw_anime[];
extern Gfx grd_s_c3_r2_2_model[];
extern Gfx grd_s_c3_r2_2_modelT[];
extern EVW_ANIME_DATA grd_s_c3_r2_2_evw_anime[];
extern Gfx grd_s_r1_b_2_model[];
extern Gfx grd_s_r1_b_2_modelT[];
extern EVW_ANIME_DATA grd_s_r1_b_2_evw_anime[];
extern Gfx grd_s_r2_b_2_model[];
extern Gfx grd_s_r2_b_2_modelT[];
extern EVW_ANIME_DATA grd_s_r2_b_2_evw_anime[];
extern Gfx grd_s_r4_b_2_model[];
extern Gfx grd_s_r4_b_2_modelT[];
extern EVW_ANIME_DATA grd_s_r4_b_2_evw_anime[];
extern Gfx grd_s_r3_b_2_model[];
extern Gfx grd_s_r3_b_2_modelT[];
extern EVW_ANIME_DATA grd_s_r3_b_2_evw_anime[];
extern Gfx grd_s_r5_b_2_model[];
extern Gfx grd_s_r5_b_2_modelT[];
extern EVW_ANIME_DATA grd_s_r5_b_2_evw_anime[];
extern Gfx grd_s_r6_b_2_model[];
extern Gfx grd_s_r6_b_2_modelT[];
extern EVW_ANIME_DATA grd_s_r6_b_2_evw_anime[];
extern Gfx grd_s_r7_b_2_model[];
extern Gfx grd_s_r7_b_2_modelT[];
extern EVW_ANIME_DATA grd_s_r7_b_2_evw_anime[];
extern Gfx grd_s_r1_b_3_model[];
extern Gfx grd_s_r1_b_3_modelT[];
extern EVW_ANIME_DATA grd_s_r1_b_3_evw_anime[];
extern Gfx grd_s_r2_b_3_model[];
extern Gfx grd_s_r2_b_3_modelT[];
extern EVW_ANIME_DATA grd_s_r2_b_3_evw_anime[];
extern Gfx grd_s_r3_b_3_model[];
extern Gfx grd_s_r3_b_3_modelT[];
extern EVW_ANIME_DATA grd_s_r3_b_3_evw_anime[];
extern Gfx grd_s_f_3_model[];
extern Gfx grd_s_f_3_modelT[];
extern Gfx grd_s_f_4_model[];
extern Gfx grd_s_f_4_modelT[];
extern EVW_ANIME_DATA grd_s_f_4_evw_anime[];
extern Gfx grd_s_f_5_model[];
extern Gfx grd_s_f_5_modelT[];
extern EVW_ANIME_DATA grd_s_f_5_evw_anime[];
extern Gfx grd_s_f_6_model[];
extern Gfx grd_s_f_6_modelT[];
extern EVW_ANIME_DATA grd_s_f_6_evw_anime[];
extern Gfx grd_s_f_7_model[];
extern Gfx grd_s_f_7_modelT[];
extern Gfx grd_s_f_8_model[];
extern Gfx grd_s_f_8_modelT[];
extern Gfx grd_s_f_9_model[];
extern Gfx grd_s_f_9_modelT[];
extern Gfx grd_s_f_10_model[];
extern Gfx grd_s_f_10_modelT[];
extern Gfx grd_s_t_2_model[];
extern Gfx grd_s_t_2_modelT[];
extern Gfx grd_s_t_3_model[];
extern Gfx grd_s_t_3_modelT[];
extern Gfx grd_s_t_4_model[];
extern Gfx grd_s_t_4_modelT[];
extern EVW_ANIME_DATA grd_s_t_4_evw_anime[];
extern Gfx grd_s_t_5_model[];
extern Gfx grd_s_t_5_modelT[];
extern EVW_ANIME_DATA grd_s_t_5_evw_anime[];
extern Gfx grd_s_t_6_model[];
extern Gfx grd_s_t_6_modelT[];
extern Gfx grd_s_t_7_model[];
extern Gfx grd_s_t_7_modelT[];
extern Gfx grd_s_t_8_model[];
extern Gfx grd_s_t_8_modelT[];
extern Gfx grd_s_t_9_model[];
extern Gfx grd_s_t_9_modelT[];
extern Gfx grd_s_t_10_model[];
extern Gfx grd_s_t_10_modelT[];
extern Gfx grd_s_t_r1_2_model[];
extern Gfx grd_s_t_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_t_r1_2_evw_anime[];
extern Gfx grd_s_t_r1_3_model[];
extern Gfx grd_s_t_r1_3_modelT[];
extern EVW_ANIME_DATA grd_s_t_r1_3_evw_anime[];
extern Gfx grd_s_t_r1_4_model[];
extern Gfx grd_s_t_r1_4_modelT[];
extern EVW_ANIME_DATA grd_s_t_r1_4_evw_anime[];
extern Gfx grd_s_t_r1_5_model[];
extern Gfx grd_s_t_r1_5_modelT[];
extern EVW_ANIME_DATA grd_s_t_r1_5_evw_anime[];
extern Gfx grd_s_r2_p_1_model[];
extern Gfx grd_s_r2_p_1_modelT[];
extern EVW_ANIME_DATA grd_s_r2_p_1_evw_anime[];
extern Gfx grd_s_r3_p_1_model[];
extern Gfx grd_s_r3_p_1_modelT[];
extern EVW_ANIME_DATA grd_s_r3_p_1_evw_anime[];
extern Gfx grd_s_r6_p_1_model[];
extern Gfx grd_s_r6_p_1_modelT[];
extern EVW_ANIME_DATA grd_s_r6_p_1_evw_anime[];
extern Gfx grd_s_r7_p_1_model[];
extern Gfx grd_s_r7_p_1_modelT[];
extern EVW_ANIME_DATA grd_s_r7_p_1_evw_anime[];
extern Gfx grd_s_t_st1_2_model[];
extern Gfx grd_s_t_st1_2_modelT[];
extern Gfx grd_s_t_st1_3_model[];
extern Gfx grd_s_t_st1_3_modelT[];
extern Gfx rom_yubin_pp_model[];
extern Gfx rom_yubin_pp_modelT[];
extern Gfx grd_s_r4_p_1_model[];
extern Gfx grd_s_r4_p_1_modelT[];
extern EVW_ANIME_DATA grd_s_r4_p_1_evw_anime[];
extern Gfx grd_s_r5_p_1_model[];
extern Gfx grd_s_r5_p_1_modelT[];
extern EVW_ANIME_DATA grd_s_r5_p_1_evw_anime[];
extern Gfx rom_train_in_model[];
extern Gfx rom_train_in_modelT[];
extern Gfx grd_s_f_9_model[];
extern Gfx grd_s_f_9_modelT[];
extern Gfx grd_s_r1_3_model[];
extern Gfx grd_s_r1_3_modelT[];
extern EVW_ANIME_DATA grd_s_r1_3_evw_anime[];
extern Gfx grd_s_c1_3_model[];
extern Gfx grd_s_c1_3_modelT[];
extern Gfx grd_s_f_9_model[];
extern Gfx grd_s_f_9_modelT[];
extern Gfx grd_yamishop_model[];
extern Gfx grd_yamishop_modelT[];
extern Gfx grd_player_select_model[];
extern Gfx grd_player_select_modelT[];
extern EVW_ANIME_DATA grd_player_select_evw_anime[];
extern Gfx grd_s_c1_s_4_model[];
extern Gfx grd_s_c1_s_4_modelT[];
extern Gfx grd_s_e1_1_model[];
extern Gfx grd_s_e1_1_modelT[];
extern Gfx grd_s_e1_r1_1_model[];
extern Gfx grd_s_e1_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_e1_r1_1_evw_anime[];
extern Gfx grd_s_e2_1_model[];
extern Gfx grd_s_e2_1_modelT[];
extern Gfx grd_s_e2_c1_1_model[];
extern Gfx grd_s_e2_c1_1_modelT[];
extern Gfx grd_s_e2_t_1_model[];
extern Gfx grd_s_e2_t_1_modelT[];
extern Gfx grd_s_e3_1_model[];
extern Gfx grd_s_e3_1_modelT[];
extern Gfx grd_s_e3_c1_1_model[];
extern Gfx grd_s_e3_c1_1_modelT[];
extern Gfx grd_s_e3_t_1_model[];
extern Gfx grd_s_e3_t_1_modelT[];
extern Gfx grd_s_e4_1_model[];
extern Gfx grd_s_e4_1_modelT[];
extern Gfx grd_s_e5_1_model[];
extern Gfx grd_s_e5_1_modelT[];
extern Gfx grd_s_f_ko_1_model[];
extern Gfx grd_s_f_ko_1_modelT[];
extern Gfx grd_s_f_ko_2_model[];
extern Gfx grd_s_f_ko_2_modelT[];
extern Gfx grd_s_f_ko_3_model[];
extern Gfx grd_s_f_ko_3_modelT[];
extern EVW_ANIME_DATA grd_s_f_ko_3_evw_anime[];
extern Gfx grd_s_f_mh_1_model[];
extern Gfx grd_s_f_mh_1_modelT[];
extern Gfx grd_s_f_mh_2_model[];
extern Gfx grd_s_f_mh_2_modelT[];
extern Gfx grd_s_f_mh_3_model[];
extern Gfx grd_s_f_mh_3_modelT[];
extern Gfx grd_s_f_pk_1_model[];
extern Gfx grd_s_f_pk_1_modelT[];
extern Gfx grd_s_f_pk_2_model[];
extern Gfx grd_s_f_pk_2_modelT[];
extern Gfx grd_s_f_pk_3_model[];
extern Gfx grd_s_f_pk_3_modelT[];
extern Gfx grd_s_t_po_1_model[];
extern Gfx grd_s_t_po_1_modelT[];
extern Gfx grd_s_t_po_2_model[];
extern Gfx grd_s_t_po_2_modelT[];
extern Gfx grd_s_t_po_3_model[];
extern Gfx grd_s_t_po_3_modelT[];
extern EVW_ANIME_DATA grd_s_t_po_3_evw_anime[];
extern Gfx grd_s_t_sh_1_model[];
extern Gfx grd_s_t_sh_1_modelT[];
extern Gfx grd_s_t_sh_2_model[];
extern Gfx grd_s_t_sh_2_modelT[];
extern EVW_ANIME_DATA grd_s_t_sh_2_evw_anime[];
extern Gfx grd_s_t_sh_3_model[];
extern Gfx grd_s_t_sh_3_modelT[];
extern Gfx rom_uranai_model[];
extern Gfx rom_uranai_modelT[];
extern EVW_ANIME_DATA rom_uranai_evw_anime[];
extern Gfx rom_shop4_1_model[];
extern Gfx rom_shop4_1_modelT[];
extern Gfx grd_s_hole_test_model[];
extern Gfx grd_s_hole_test_modelT[];
extern Gfx grd_s_m_1_model[];
extern Gfx grd_s_m_1_modelT[];
extern Gfx grd_s_m_r1_1_model[];
extern Gfx grd_s_m_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_m_r1_1_evw_anime[];
extern Gfx grd_s_e2_m_1_model[];
extern Gfx grd_s_e2_m_1_modelT[];
extern Gfx grd_s_e3_m_1_model[];
extern Gfx grd_s_e3_m_1_modelT[];
extern Gfx rom_shop4_fuku_model[];
extern Gfx rom_shop4_fuku_modelT[];
extern Gfx grd_s_m_r1_2_model[];
extern Gfx grd_s_m_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_m_r1_2_evw_anime[];
extern Gfx grd_s_m_r1_3_model[];
extern Gfx grd_s_m_r1_3_modelT[];
extern EVW_ANIME_DATA grd_s_m_r1_3_evw_anime[];
extern Gfx grd_s_m_r1_4_model[];
extern Gfx grd_s_m_r1_4_modelT[];
extern EVW_ANIME_DATA grd_s_m_r1_4_evw_anime[];
extern Gfx grd_s_m_r1_5_model[];
extern Gfx grd_s_m_r1_5_modelT[];
extern EVW_ANIME_DATA grd_s_m_r1_5_evw_anime[];
extern Gfx grd_s_m_r1_b_1_model[];
extern Gfx grd_s_m_r1_b_1_modelT[];
extern EVW_ANIME_DATA grd_s_m_r1_b_1_evw_anime[];
extern Gfx grd_s_m_r1_b_2_model[];
extern Gfx grd_s_m_r1_b_2_modelT[];
extern EVW_ANIME_DATA grd_s_m_r1_b_2_evw_anime[];
extern Gfx grd_s_m_r1_b_3_model[];
extern Gfx grd_s_m_r1_b_3_modelT[];
extern EVW_ANIME_DATA grd_s_m_r1_b_3_evw_anime[];
extern Gfx grd_s_m_2_model[];
extern Gfx grd_s_m_2_modelT[];
extern Gfx grd_s_m_3_model[];
extern Gfx grd_s_m_3_modelT[];
extern Gfx grd_s_m_4_model[];
extern Gfx grd_s_m_4_modelT[];
extern Gfx grd_s_m_5_model[];
extern Gfx grd_s_m_5_modelT[];
extern Gfx grd_s_m_6_model[];
extern Gfx grd_s_m_6_modelT[];
extern Gfx grd_s_m_7_model[];
extern Gfx grd_s_m_7_modelT[];
extern Gfx grd_s_m_8_model[];
extern Gfx grd_s_m_8_modelT[];
extern Gfx grd_s_m_9_model[];
extern Gfx grd_s_m_9_modelT[];
extern Gfx grd_s_m_10_model[];
extern Gfx grd_s_m_10_modelT[];
extern Gfx grd_s_c2_s_3_model[];
extern Gfx grd_s_c2_s_3_modelT[];
extern Gfx grd_s_c7_s_2_model[];
extern Gfx grd_s_c7_s_3_model[];
extern Gfx grd_s_c7_r3_2_model[];
extern Gfx grd_s_c7_r3_2_modelT[];
extern EVW_ANIME_DATA grd_s_c7_r3_2_evw_anime[];
extern Gfx rom_museum1_model[];
extern Gfx rom_museum1_modelT[];
extern Gfx rom_museum2_model[];
extern Gfx rom_museum2_modelT[];
extern Gfx rom_museum3_model[];
extern Gfx rom_museum3_modelT[];
extern Gfx rom_museum5_pp_model[];
extern Gfx rom_museum5_pp_modelT[];
extern Gfx rom_tailor_model[];
extern Gfx rom_tailor_modelT[];
extern Gfx rom_toudai_model[];
extern Gfx rom_toudai_modelT[];
extern Gfx grd_s_f_mu_1_model[];
extern Gfx grd_s_f_mu_1_modelT[];
extern Gfx grd_s_f_mu_2_model[];
extern Gfx grd_s_f_mu_2_modelT[];
extern Gfx grd_s_f_mu_3_model[];
extern Gfx grd_s_f_mu_3_modelT[];
extern EVW_ANIME_DATA grd_s_f_mu_3_evw_anime[];
extern Gfx grd_s_m_ta_1_model[];
extern Gfx grd_s_m_ta_1_modelT[];
extern EVW_ANIME_DATA grd_s_m_ta_1_evw_anime[];
extern Gfx grd_s_m_ta_2_model[];
extern Gfx grd_s_m_ta_2_modelT[];
extern EVW_ANIME_DATA grd_s_m_ta_2_evw_anime[];
extern Gfx grd_s_m_ta_3_model[];
extern Gfx grd_s_m_ta_3_modelT[];
extern EVW_ANIME_DATA grd_s_m_ta_3_evw_anime[];
extern Gfx grd_s_m_wf_1_model[];
extern Gfx grd_s_m_wf_1_modelT[];
extern EVW_ANIME_DATA grd_s_m_wf_1_evw_anime[];
extern Gfx grd_s_m_wf_2_model[];
extern Gfx grd_s_m_wf_2_modelT[];
extern EVW_ANIME_DATA grd_s_m_wf_2_evw_anime[];
extern Gfx grd_s_m_wf_3_model[];
extern Gfx grd_s_m_wf_3_modelT[];
extern EVW_ANIME_DATA grd_s_m_wf_3_evw_anime[];
extern Gfx grd_s_ir_1_model[];
extern Gfx grd_s_ir_1_modelT[];
extern Gfx grd_s_il_1_model[];
extern Gfx grd_s_il_1_modelT[];
extern Gfx grd_s_o_1_model[];
extern Gfx grd_s_o_1_modelT[];
extern EVW_ANIME_DATA grd_s_o_1_evw_anime[];
extern Gfx grd_s_o_2_model[];
extern Gfx grd_s_o_2_modelT[];
extern EVW_ANIME_DATA grd_s_o_2_evw_anime[];
extern Gfx grd_s_o_3_model[];
extern Gfx grd_s_o_3_modelT[];
extern EVW_ANIME_DATA grd_s_o_3_evw_anime[];
extern Gfx grd_s_o_4_model[];
extern Gfx grd_s_o_4_modelT[];
extern EVW_ANIME_DATA grd_s_o_4_evw_anime[];
extern Gfx grd_s_e2_o_1_model[];
extern Gfx grd_s_e2_o_1_modelT[];
extern Gfx grd_s_e3_o_1_model[];
extern Gfx grd_s_e3_o_1_modelT[];
extern Gfx grd_s_o_5_model[];
extern Gfx grd_s_o_5_modelT[];
extern EVW_ANIME_DATA grd_s_o_5_evw_anime[];
extern Gfx grd_s_o_6_model[];
extern Gfx grd_s_o_6_modelT[];
extern EVW_ANIME_DATA grd_s_o_6_evw_anime[];
extern Gfx grd_s_o_7_model[];
extern Gfx grd_s_o_7_modelT[];
extern EVW_ANIME_DATA grd_s_o_7_evw_anime[];
extern Gfx grd_s_o_8_model[];
extern Gfx grd_s_o_8_modelT[];
extern EVW_ANIME_DATA grd_s_o_8_evw_anime[];
extern Gfx grd_s_o_9_model[];
extern Gfx grd_s_o_9_modelT[];
extern EVW_ANIME_DATA grd_s_o_9_evw_anime[];
extern Gfx grd_s_o_10_model[];
extern Gfx grd_s_o_10_modelT[];
extern EVW_ANIME_DATA grd_s_o_10_evw_anime[];
extern Gfx grd_s_o_i_1_model[];
extern Gfx grd_s_o_i_1_modelT[];
extern Gfx grd_s_o_i_2_model[];
extern Gfx grd_s_o_i_2_modelT[];
extern EVW_ANIME_DATA grd_s_o_i_2_evw_anime[];
extern Gfx grd_s_o_r1_1_model[];
extern Gfx grd_s_o_r1_1_modelT[];
extern EVW_ANIME_DATA grd_s_o_r1_1_evw_anime[];
extern Gfx grd_s_o_r1_2_model[];
extern Gfx grd_s_o_r1_2_modelT[];
extern EVW_ANIME_DATA grd_s_o_r1_2_evw_anime[];
extern Gfx grd_s_o_r1_3_model[];
extern Gfx grd_s_o_r1_3_modelT[];
extern EVW_ANIME_DATA grd_s_o_r1_3_evw_anime[];
extern Gfx grd_s_o_r1_4_model[];
extern Gfx grd_s_o_r1_4_modelT[];
extern EVW_ANIME_DATA grd_s_o_r1_4_evw_anime[];
extern Gfx grd_s_o_r1_5_model[];
extern Gfx grd_s_o_r1_5_modelT[];
extern EVW_ANIME_DATA grd_s_o_r1_5_evw_anime[];
extern Gfx grd_s_o_r1_b_1_model[];
extern Gfx grd_s_o_r1_b_1_modelT[];
extern EVW_ANIME_DATA grd_s_o_r1_b_1_evw_anime[];
extern Gfx grd_s_o_r1_b_2_model[];
extern Gfx grd_s_o_r1_b_2_modelT[];
extern EVW_ANIME_DATA grd_s_o_r1_b_2_evw_anime[];
extern Gfx grd_s_o_r1_b_3_model[];
extern Gfx grd_s_o_r1_b_3_modelT[];
extern EVW_ANIME_DATA grd_s_o_r1_b_3_evw_anime[];
extern Gfx grd_s_o_ta_1_model[];
extern Gfx grd_s_o_ta_1_modelT[];
extern EVW_ANIME_DATA grd_s_o_ta_1_evw_anime[];
extern Gfx grd_s_o_ta_2_model[];
extern Gfx grd_s_o_ta_2_modelT[];
extern EVW_ANIME_DATA grd_s_o_ta_2_evw_anime[];
extern Gfx grd_s_o_ta_3_model[];
extern Gfx grd_s_o_ta_3_modelT[];
extern EVW_ANIME_DATA grd_s_o_ta_3_evw_anime[];
extern Gfx grd_s_o_wf_1_model[];
extern Gfx grd_s_o_wf_1_modelT[];
extern EVW_ANIME_DATA grd_s_o_wf_1_evw_anime[];
extern Gfx grd_s_o_wf_2_model[];
extern Gfx grd_s_o_wf_2_modelT[];
extern EVW_ANIME_DATA grd_s_o_wf_2_evw_anime[];
extern Gfx grd_s_o_wf_3_model[];
extern Gfx grd_s_o_wf_3_modelT[];
extern EVW_ANIME_DATA grd_s_o_wf_3_evw_anime[];
extern Gfx grd_s_ir_2_model[];
extern Gfx grd_s_ir_2_modelT[];
extern Gfx grd_s_il_2_model[];
extern Gfx grd_s_il_2_modelT[];
extern Gfx grd_s_ir_3_model[];
extern Gfx grd_s_ir_3_modelT[];
extern Gfx grd_s_il_3_model[];
extern Gfx grd_s_il_3_modelT[];
extern Gfx grd_s_ir_4_model[];
extern Gfx grd_s_ir_4_modelT[];
extern Gfx grd_s_il_4_model[];
extern Gfx grd_s_il_4_modelT[];
extern Gfx rom_tent_model[];
extern Gfx rom_tent_modelT[];

mFM_bg_data_c data_bgd[] = {
    {
#include "../src/data/field/bg/acre/room01/room01_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_259/rom_my_room_s_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_260/rom_my_room_m_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_242/rom_my_room_l_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/myr_etc/myr_etc_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_246/npc_room01_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_248/rom_shop1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/tmp/tmp_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/tmp2/tmp2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/tmpr/tmpr_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/tmpr2/tmpr2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/tmp3/tmp3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/tmpr3/tmpr3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/tmp4/tmp4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/tmpr4/tmpr4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_r1_1/grd_s_c1_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_s_1/grd_s_c1_s_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_r1_1/grd_s_c2_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_r2_1/grd_s_c2_r2_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_r1_1/grd_s_c5_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_r1_1/grd_s_t_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_1/grd_s_f_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_2/grd_s_f_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_1/grd_s_c1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_r2_1/grd_s_c1_r2_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_r3_1/grd_s_c1_r3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_1/grd_s_c2_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c3_1/grd_s_c3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c3_r1_1/grd_s_c3_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_1/grd_s_c4_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_r1_1/grd_s_c4_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_r2_1/grd_s_c4_r2_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_1/grd_s_c5_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_r2_1/grd_s_c5_r2_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_r3_1/grd_s_c5_r3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c6_1/grd_s_c6_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c6_r1_1/grd_s_c6_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_1/grd_s_c7_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r1_1/grd_s_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r2_1/grd_s_r2_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r3_1/grd_s_r3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r4_1/grd_s_r4_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r5_1/grd_s_r5_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r6_1/grd_s_r6_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r7_1/grd_s_r7_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c3_r2_1/grd_s_c3_r2_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_r3_1/grd_s_c7_r3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c6_r3_1/grd_s_c6_r3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r1_b_1/grd_s_r1_b_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r2_b_1/grd_s_r2_b_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r3_b_1/grd_s_r3_b_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r4_b_1/grd_s_r4_b_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r5_b_1/grd_s_r5_b_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r6_b_1/grd_s_r6_b_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r7_b_1/grd_s_r7_b_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_1/grd_s_t_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_s_2/grd_s_c1_s_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_s_1/grd_s_c2_s_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c3_s_1/grd_s_c3_s_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_s_1/grd_s_c4_s_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_s_1/grd_s_c5_s_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c6_s_1/grd_s_c6_s_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_s_1/grd_s_c7_s_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_r3_1/grd_s_c4_r3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_r1_1/grd_s_c7_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_st1_1/grd_s_t_st1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_2/grd_s_c1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_3/grd_s_c1_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_4/grd_s_c1_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_5/grd_s_c1_5_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_2/grd_s_c2_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r1_2/grd_s_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r1_3/grd_s_r1_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r4_2/grd_s_r4_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r5_2/grd_s_r5_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r7_2/grd_s_r7_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r7_3/grd_s_r7_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_s_2/grd_s_c2_s_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_s_3/grd_s_c1_s_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_s_2/grd_s_c4_s_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_s_2/grd_s_c5_s_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c6_r1_2/grd_s_c6_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c3_r1_2/grd_s_c3_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c3_2/grd_s_c3_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_3/grd_s_c7_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_r2_2/grd_s_c1_r2_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_r3_2/grd_s_c1_r3_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_2/grd_s_c4_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_2/grd_s_c5_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c6_2/grd_s_c6_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r2_2/grd_s_r2_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r3_2/grd_s_r3_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_r1_2/grd_s_c4_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_r2_2/grd_s_c4_r2_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_r1_2/grd_s_c7_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c6_2/grd_s_c6_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_r2_2/grd_s_c5_r2_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_r3_2/grd_s_c4_r3_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r2_3/grd_s_r2_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r3_3/grd_s_r3_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_r3_2/grd_s_c5_r3_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_3/grd_s_c5_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c4_3/grd_s_c4_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c3_3/grd_s_c3_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_3/grd_s_c2_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r1_p_1/grd_s_r1_p_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r6_2/grd_s_r6_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/police_indoor/police_indoor_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_r1_2/grd_s_c1_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_r1_3/grd_s_c1_r1_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_r2_3/grd_s_c1_r2_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_r3_3/grd_s_c1_r3_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_r1_2/grd_s_c2_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c5_r1_2/grd_s_c5_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c6_3/grd_s_c6_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_2/grd_s_c7_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r1_4/grd_s_r1_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r2_4/grd_s_r2_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r3_4/grd_s_r3_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r4_3/grd_s_r4_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r5_3/grd_s_r5_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r6_3/grd_s_r6_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_r2_2/grd_s_c2_r2_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c3_r2_2/grd_s_c3_r2_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r1_b_2/grd_s_r1_b_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r2_b_2/grd_s_r2_b_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r4_b_2/grd_s_r4_b_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r3_b_2/grd_s_r3_b_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r5_b_2/grd_s_r5_b_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r6_b_2/grd_s_r6_b_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r7_b_2/grd_s_r7_b_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r1_b_3/grd_s_r1_b_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r2_b_3/grd_s_r2_b_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r3_b_3/grd_s_r3_b_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_3/grd_s_f_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_4/grd_s_f_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_5/grd_s_f_5_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_6/grd_s_f_6_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_7/grd_s_f_7_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_8/grd_s_f_8_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_9/grd_s_f_9_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_10/grd_s_f_10_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_2/grd_s_t_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_3/grd_s_t_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_4/grd_s_t_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_5/grd_s_t_5_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_6/grd_s_t_6_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_7/grd_s_t_7_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_8/grd_s_t_8_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_9/grd_s_t_9_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_10/grd_s_t_10_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_r1_2/grd_s_t_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_r1_3/grd_s_t_r1_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_r1_4/grd_s_t_r1_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_r1_5/grd_s_t_r1_5_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r2_p_1/grd_s_r2_p_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r3_p_1/grd_s_r3_p_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r6_p_1/grd_s_r6_p_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r7_p_1/grd_s_r7_p_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_st1_2/grd_s_t_st1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_st1_3/grd_s_t_st1_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_yubin_pp/grd_post_office_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r4_p_1/grd_s_r4_p_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r5_p_1/grd_s_r5_p_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_train_in/rom_train_in_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_9/grd_s_f_9_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_r1_3/grd_s_r1_3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_3/grd_s_c1_3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_9/grd_s_f_9_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_yamishop/grd_yamishop_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_player_select/grd_player_select_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c1_s_4/grd_s_c1_s_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e1_1/grd_s_e1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e1_r1_1/grd_s_e1_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e2_1/grd_s_e2_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e2_c1_1/grd_s_e2_c1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e2_t_1/grd_s_e2_t_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e3_1/grd_s_e3_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e3_c1_1/grd_s_e3_c1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e3_t_1/grd_s_e3_t_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e4_1/grd_s_e4_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e5_1/grd_s_e5_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_ko_1/grd_s_f_ko_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_ko_2/grd_s_f_ko_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_ko_3/grd_s_f_ko_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_mh_1/grd_s_f_mh_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_mh_2/grd_s_f_mh_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_mh_3/grd_s_f_mh_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_pk_1/grd_s_f_pk_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_pk_2/grd_s_f_pk_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_pk_3/grd_s_f_pk_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_po_1/grd_s_t_po_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_po_2/grd_s_t_po_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_po_3/grd_s_t_po_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_sh_1/grd_s_t_sh_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_sh_2/grd_s_t_sh_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_t_sh_3/grd_s_t_sh_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_uranai/rom_uranai_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_254/rom_shop2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_258/rom_shop3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_shop4_1/rom_shop4_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_257/rom_shop4_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_hole_test/grd_s_hole_test_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_1/grd_s_m_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_r1_1/grd_s_m_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e2_m_1/grd_s_e2_m_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e3_m_1/grd_s_e3_m_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_249/249_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_293/293_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_250/rom_shop1_fuku_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_251/rom_shop2_fuku_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_252/rom_shop3_fuku_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_shop4_fuku/rom_shop4_fuku_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_r1_2/grd_s_m_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_r1_3/grd_s_m_r1_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_r1_4/grd_s_m_r1_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_r1_5/grd_s_m_r1_5_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_r1_b_1/grd_s_m_r1_b_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_r1_b_2/grd_s_m_r1_b_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_r1_b_3/grd_s_m_r1_b_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_2/grd_s_m_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_3/grd_s_m_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_4/grd_s_m_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_5/grd_s_m_5_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_6/grd_s_m_6_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_7/grd_s_m_7_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_8/grd_s_m_8_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_9/grd_s_m_9_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_10/grd_s_m_10_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c2_s_3/grd_s_c2_s_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_s_2/grd_s_c7_s_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_s_3/grd_s_c7_s_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_c7_r3_2/grd_s_c7_r3_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_museum1/rom_museum1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_museum2/rom_museum2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_museum3/rom_museum3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_museum5_pp/rom_museum5_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_282/rom_museum4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_283/rom_my_room_ll1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_284/rom_my_room_ll2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_285/285_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_286/rom_my_room_m_basement_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_287/rom_my_room_l_basement_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_288/rom_my_room_ll1_basement_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_289/rom_my_room_basement_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_tailor/rom_tailor_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_toudai/rom_toudai_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_mu_1/grd_s_f_mu_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_mu_2/grd_s_f_mu_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_f_mu_3/grd_s_f_mu_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_ta_1/grd_s_m_ta_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_ta_2/grd_s_m_ta_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_ta_3/grd_s_m_ta_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_wf_1/grd_s_m_wf_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_wf_2/grd_s_m_wf_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_m_wf_3/grd_s_m_wf_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_ir_1/grd_s_ir_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_il_1/grd_s_il_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_1/grd_s_o_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_2/grd_s_o_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_3/grd_s_o_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_4/grd_s_o_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e2_o_1/grd_s_e2_o_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_e3_o_1/grd_s_e3_o_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_5/grd_s_o_5_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_6/grd_s_o_6_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_7/grd_s_o_7_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_8/grd_s_o_8_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_9/grd_s_o_9_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_10/grd_s_o_10_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_i_1/grd_s_o_i_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_i_2/grd_s_o_i_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_r1_1/grd_s_o_r1_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_r1_2/grd_s_o_r1_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_r1_3/grd_s_o_r1_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_r1_4/grd_s_o_r1_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_r1_5/grd_s_o_r1_5_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_r1_b_1/grd_s_o_r1_b_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_r1_b_2/grd_s_o_r1_b_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_r1_b_3/grd_s_o_r1_b_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_ta_1/grd_s_o_ta_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_ta_2/grd_s_o_ta_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_ta_3/grd_s_o_ta_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_wf_1/grd_s_o_wf_1_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_wf_2/grd_s_o_wf_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_o_wf_3/grd_s_o_wf_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_ir_2/grd_s_ir_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_il_2/grd_s_il_2_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_ir_3/grd_s_ir_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_il_3/grd_s_il_3_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_ir_4/grd_s_ir_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/grd_s_il_4/grd_s_il_4_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/rom_tent/rom_tent_bg_data.c"
    },
    {
#include "../src/data/field/bg/acre/bg_292/rom_reset_house_bg_data.c"
    },
};

int data_bgd_number = ARRAY_COUNT(data_bgd);
