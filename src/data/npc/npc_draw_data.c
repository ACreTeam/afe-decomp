#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_cat_1;
extern unsigned short cat_1_pal[];
extern unsigned char cat_1_eye1_TA_tex_txt[];
extern unsigned char cat_1_eye2_TA_tex_txt[];
extern unsigned char cat_1_eye3_TA_tex_txt[];
extern unsigned char cat_1_eye4_TA_tex_txt[];
extern unsigned char cat_1_eye5_TA_tex_txt[];
extern unsigned char cat_1_eye6_TA_tex_txt[];
extern unsigned char cat_1_eye7_TA_tex_txt[];
extern unsigned char cat_1_eye8_TA_tex_txt[];
extern unsigned char cat_1_mouth1_TA_tex_txt[];
extern unsigned char cat_1_mouth2_TA_tex_txt[];
extern unsigned char cat_1_mouth3_TA_tex_txt[];
extern unsigned char cat_1_mouth4_TA_tex_txt[];
extern unsigned char cat_1_mouth5_TA_tex_txt[];
extern unsigned char cat_1_mouth6_TA_tex_txt[];
extern unsigned char cat_1_tmem_txt[];
extern unsigned short cat_2_pal[];
extern unsigned char cat_2_eye1_TA_tex_txt[];
extern unsigned char cat_2_eye2_TA_tex_txt[];
extern unsigned char cat_2_eye3_TA_tex_txt[];
extern unsigned char cat_2_eye4_TA_tex_txt[];
extern unsigned char cat_2_eye5_TA_tex_txt[];
extern unsigned char cat_2_eye6_TA_tex_txt[];
extern unsigned char cat_2_eye7_TA_tex_txt[];
extern unsigned char cat_2_eye8_TA_tex_txt[];
extern unsigned char cat_2_mouth1_TA_tex_txt[];
extern unsigned char cat_2_mouth2_TA_tex_txt[];
extern unsigned char cat_2_mouth3_TA_tex_txt[];
extern unsigned char cat_2_mouth4_TA_tex_txt[];
extern unsigned char cat_2_mouth5_TA_tex_txt[];
extern unsigned char cat_2_mouth6_TA_tex_txt[];
extern unsigned char cat_2_tmem_txt[];
extern unsigned short cat_3_pal[];
extern unsigned char cat_3_eye1_TA_tex_txt[];
extern unsigned char cat_3_eye2_TA_tex_txt[];
extern unsigned char cat_3_eye3_TA_tex_txt[];
extern unsigned char cat_3_eye4_TA_tex_txt[];
extern unsigned char cat_3_eye5_TA_tex_txt[];
extern unsigned char cat_3_eye6_TA_tex_txt[];
extern unsigned char cat_3_eye7_TA_tex_txt[];
extern unsigned char cat_3_eye8_TA_tex_txt[];
extern unsigned char cat_3_mouth1_TA_tex_txt[];
extern unsigned char cat_3_mouth2_TA_tex_txt[];
extern unsigned char cat_3_mouth3_TA_tex_txt[];
extern unsigned char cat_3_mouth4_TA_tex_txt[];
extern unsigned char cat_3_mouth5_TA_tex_txt[];
extern unsigned char cat_3_mouth6_TA_tex_txt[];
extern unsigned char cat_3_tmem_txt[];
extern unsigned short cat_4_pal[];
extern unsigned char cat_4_eye1_TA_tex_txt[];
extern unsigned char cat_4_eye2_TA_tex_txt[];
extern unsigned char cat_4_eye3_TA_tex_txt[];
extern unsigned char cat_4_eye4_TA_tex_txt[];
extern unsigned char cat_4_eye5_TA_tex_txt[];
extern unsigned char cat_4_eye6_TA_tex_txt[];
extern unsigned char cat_4_eye7_TA_tex_txt[];
extern unsigned char cat_4_eye8_TA_tex_txt[];
extern unsigned char cat_4_mouth1_TA_tex_txt[];
extern unsigned char cat_4_mouth2_TA_tex_txt[];
extern unsigned char cat_4_mouth3_TA_tex_txt[];
extern unsigned char cat_4_mouth4_TA_tex_txt[];
extern unsigned char cat_4_mouth5_TA_tex_txt[];
extern unsigned char cat_4_mouth6_TA_tex_txt[];
extern unsigned char cat_4_tmem_txt[];
extern unsigned short cat_5_pal[];
extern unsigned char cat_5_eye1_TA_tex_txt[];
extern unsigned char cat_5_eye2_TA_tex_txt[];
extern unsigned char cat_5_eye3_TA_tex_txt[];
extern unsigned char cat_5_eye4_TA_tex_txt[];
extern unsigned char cat_5_eye5_TA_tex_txt[];
extern unsigned char cat_5_eye6_TA_tex_txt[];
extern unsigned char cat_5_eye7_TA_tex_txt[];
extern unsigned char cat_5_eye8_TA_tex_txt[];
extern unsigned char cat_5_mouth1_TA_tex_txt[];
extern unsigned char cat_5_mouth2_TA_tex_txt[];
extern unsigned char cat_5_mouth3_TA_tex_txt[];
extern unsigned char cat_5_mouth4_TA_tex_txt[];
extern unsigned char cat_5_mouth5_TA_tex_txt[];
extern unsigned char cat_5_mouth6_TA_tex_txt[];
extern unsigned char cat_5_tmem_txt[];
extern unsigned short cat_6_pal[];
extern unsigned char cat_6_eye1_TA_tex_txt[];
extern unsigned char cat_6_eye2_TA_tex_txt[];
extern unsigned char cat_6_eye3_TA_tex_txt[];
extern unsigned char cat_6_eye4_TA_tex_txt[];
extern unsigned char cat_6_eye5_TA_tex_txt[];
extern unsigned char cat_6_eye6_TA_tex_txt[];
extern unsigned char cat_6_eye7_TA_tex_txt[];
extern unsigned char cat_6_eye8_TA_tex_txt[];
extern unsigned char cat_6_mouth1_TA_tex_txt[];
extern unsigned char cat_6_mouth2_TA_tex_txt[];
extern unsigned char cat_6_mouth3_TA_tex_txt[];
extern unsigned char cat_6_mouth4_TA_tex_txt[];
extern unsigned char cat_6_mouth5_TA_tex_txt[];
extern unsigned char cat_6_mouth6_TA_tex_txt[];
extern unsigned char cat_6_tmem_txt[];
extern unsigned short cat_7_pal[];
extern unsigned char cat_7_eye1_TA_tex_txt[];
extern unsigned char cat_7_eye2_TA_tex_txt[];
extern unsigned char cat_7_eye3_TA_tex_txt[];
extern unsigned char cat_7_eye4_TA_tex_txt[];
extern unsigned char cat_7_eye5_TA_tex_txt[];
extern unsigned char cat_7_eye6_TA_tex_txt[];
extern unsigned char cat_7_eye7_TA_tex_txt[];
extern unsigned char cat_7_eye8_TA_tex_txt[];
extern unsigned char cat_7_mouth1_TA_tex_txt[];
extern unsigned char cat_7_mouth2_TA_tex_txt[];
extern unsigned char cat_7_mouth3_TA_tex_txt[];
extern unsigned char cat_7_mouth4_TA_tex_txt[];
extern unsigned char cat_7_mouth5_TA_tex_txt[];
extern unsigned char cat_7_mouth6_TA_tex_txt[];
extern unsigned char cat_7_tmem_txt[];
extern unsigned short cat_8_pal[];
extern unsigned char cat_8_eye1_TA_tex_txt[];
extern unsigned char cat_8_eye2_TA_tex_txt[];
extern unsigned char cat_8_eye3_TA_tex_txt[];
extern unsigned char cat_8_eye4_TA_tex_txt[];
extern unsigned char cat_8_eye5_TA_tex_txt[];
extern unsigned char cat_8_eye6_TA_tex_txt[];
extern unsigned char cat_8_eye7_TA_tex_txt[];
extern unsigned char cat_8_eye8_TA_tex_txt[];
extern unsigned char cat_8_mouth1_TA_tex_txt[];
extern unsigned char cat_8_mouth2_TA_tex_txt[];
extern unsigned char cat_8_mouth3_TA_tex_txt[];
extern unsigned char cat_8_mouth4_TA_tex_txt[];
extern unsigned char cat_8_mouth5_TA_tex_txt[];
extern unsigned char cat_8_mouth6_TA_tex_txt[];
extern unsigned char cat_8_tmem_txt[];
extern unsigned short cat_9_pal[];
extern unsigned char cat_9_eye1_TA_tex_txt[];
extern unsigned char cat_9_eye2_TA_tex_txt[];
extern unsigned char cat_9_eye3_TA_tex_txt[];
extern unsigned char cat_9_eye4_TA_tex_txt[];
extern unsigned char cat_9_eye5_TA_tex_txt[];
extern unsigned char cat_9_eye6_TA_tex_txt[];
extern unsigned char cat_9_eye7_TA_tex_txt[];
extern unsigned char cat_9_eye8_TA_tex_txt[];
extern unsigned char cat_9_mouth1_TA_tex_txt[];
extern unsigned char cat_9_mouth2_TA_tex_txt[];
extern unsigned char cat_9_mouth3_TA_tex_txt[];
extern unsigned char cat_9_mouth4_TA_tex_txt[];
extern unsigned char cat_9_mouth5_TA_tex_txt[];
extern unsigned char cat_9_mouth6_TA_tex_txt[];
extern unsigned char cat_9_tmem_txt[];
extern unsigned short cat_10_pal[];
extern unsigned char cat_10_eye1_TA_tex_txt[];
extern unsigned char cat_10_eye2_TA_tex_txt[];
extern unsigned char cat_10_eye3_TA_tex_txt[];
extern unsigned char cat_10_eye4_TA_tex_txt[];
extern unsigned char cat_10_eye5_TA_tex_txt[];
extern unsigned char cat_10_eye6_TA_tex_txt[];
extern unsigned char cat_10_eye7_TA_tex_txt[];
extern unsigned char cat_10_eye8_TA_tex_txt[];
extern unsigned char cat_10_mouth1_TA_tex_txt[];
extern unsigned char cat_10_mouth2_TA_tex_txt[];
extern unsigned char cat_10_mouth3_TA_tex_txt[];
extern unsigned char cat_10_mouth4_TA_tex_txt[];
extern unsigned char cat_10_mouth5_TA_tex_txt[];
extern unsigned char cat_10_mouth6_TA_tex_txt[];
extern unsigned char cat_10_tmem_txt[];
extern unsigned short cat_11_pal[];
extern unsigned char cat_11_eye1_TA_tex_txt[];
extern unsigned char cat_11_eye2_TA_tex_txt[];
extern unsigned char cat_11_eye3_TA_tex_txt[];
extern unsigned char cat_11_eye4_TA_tex_txt[];
extern unsigned char cat_11_eye5_TA_tex_txt[];
extern unsigned char cat_11_eye6_TA_tex_txt[];
extern unsigned char cat_11_eye7_TA_tex_txt[];
extern unsigned char cat_11_eye8_TA_tex_txt[];
extern unsigned char cat_11_mouth1_TA_tex_txt[];
extern unsigned char cat_11_mouth2_TA_tex_txt[];
extern unsigned char cat_11_mouth3_TA_tex_txt[];
extern unsigned char cat_11_mouth4_TA_tex_txt[];
extern unsigned char cat_11_mouth5_TA_tex_txt[];
extern unsigned char cat_11_mouth6_TA_tex_txt[];
extern unsigned char cat_11_tmem_txt[];
extern unsigned short cat_12_pal[];
extern unsigned char cat_12_eye1_TA_tex_txt[];
extern unsigned char cat_12_eye2_TA_tex_txt[];
extern unsigned char cat_12_eye3_TA_tex_txt[];
extern unsigned char cat_12_eye4_TA_tex_txt[];
extern unsigned char cat_12_eye5_TA_tex_txt[];
extern unsigned char cat_12_eye6_TA_tex_txt[];
extern unsigned char cat_12_eye7_TA_tex_txt[];
extern unsigned char cat_12_eye8_TA_tex_txt[];
extern unsigned char cat_12_mouth1_TA_tex_txt[];
extern unsigned char cat_12_mouth2_TA_tex_txt[];
extern unsigned char cat_12_mouth3_TA_tex_txt[];
extern unsigned char cat_12_mouth4_TA_tex_txt[];
extern unsigned char cat_12_mouth5_TA_tex_txt[];
extern unsigned char cat_12_mouth6_TA_tex_txt[];
extern unsigned char cat_12_tmem_txt[];
extern unsigned short cat_13_pal[];
extern unsigned char cat_13_eye1_TA_tex_txt[];
extern unsigned char cat_13_eye2_TA_tex_txt[];
extern unsigned char cat_13_eye3_TA_tex_txt[];
extern unsigned char cat_13_eye4_TA_tex_txt[];
extern unsigned char cat_13_eye5_TA_tex_txt[];
extern unsigned char cat_13_eye6_TA_tex_txt[];
extern unsigned char cat_13_eye7_TA_tex_txt[];
extern unsigned char cat_13_eye8_TA_tex_txt[];
extern unsigned char cat_13_mouth1_TA_tex_txt[];
extern unsigned char cat_13_mouth2_TA_tex_txt[];
extern unsigned char cat_13_mouth3_TA_tex_txt[];
extern unsigned char cat_13_mouth4_TA_tex_txt[];
extern unsigned char cat_13_mouth5_TA_tex_txt[];
extern unsigned char cat_13_mouth6_TA_tex_txt[];
extern unsigned char cat_13_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_ant_1;
extern unsigned short ant_1_pal[];
extern unsigned char ant_1_eye1_TA_tex_txt[];
extern unsigned char ant_1_eye2_TA_tex_txt[];
extern unsigned char ant_1_eye3_TA_tex_txt[];
extern unsigned char ant_1_eye4_TA_tex_txt[];
extern unsigned char ant_1_eye5_TA_tex_txt[];
extern unsigned char ant_1_eye6_TA_tex_txt[];
extern unsigned char ant_1_eye7_TA_tex_txt[];
extern unsigned char ant_1_eye8_TA_tex_txt[];
extern unsigned char ant_1_tmem_txt[];
extern unsigned short ant_2_pal[];
extern unsigned char ant_2_eye1_TA_tex_txt[];
extern unsigned char ant_2_eye2_TA_tex_txt[];
extern unsigned char ant_2_eye3_TA_tex_txt[];
extern unsigned char ant_2_eye4_TA_tex_txt[];
extern unsigned char ant_2_eye5_TA_tex_txt[];
extern unsigned char ant_2_eye6_TA_tex_txt[];
extern unsigned char ant_2_eye7_TA_tex_txt[];
extern unsigned char ant_2_eye8_TA_tex_txt[];
extern unsigned char ant_2_tmem_txt[];
extern unsigned short ant_3_pal[];
extern unsigned char ant_3_eye1_TA_tex_txt[];
extern unsigned char ant_3_eye2_TA_tex_txt[];
extern unsigned char ant_3_eye3_TA_tex_txt[];
extern unsigned char ant_3_eye4_TA_tex_txt[];
extern unsigned char ant_3_eye5_TA_tex_txt[];
extern unsigned char ant_3_eye6_TA_tex_txt[];
extern unsigned char ant_3_eye7_TA_tex_txt[];
extern unsigned char ant_3_eye8_TA_tex_txt[];
extern unsigned char ant_3_tmem_txt[];
extern unsigned short ant_4_pal[];
extern unsigned char ant_4_eye1_TA_tex_txt[];
extern unsigned char ant_4_eye2_TA_tex_txt[];
extern unsigned char ant_4_eye3_TA_tex_txt[];
extern unsigned char ant_4_eye4_TA_tex_txt[];
extern unsigned char ant_4_eye5_TA_tex_txt[];
extern unsigned char ant_4_eye6_TA_tex_txt[];
extern unsigned char ant_4_eye7_TA_tex_txt[];
extern unsigned char ant_4_eye8_TA_tex_txt[];
extern unsigned char ant_4_tmem_txt[];
extern unsigned short ant_5_pal[];
extern unsigned char ant_5_eye1_TA_tex_txt[];
extern unsigned char ant_5_eye2_TA_tex_txt[];
extern unsigned char ant_5_eye3_TA_tex_txt[];
extern unsigned char ant_5_eye4_TA_tex_txt[];
extern unsigned char ant_5_eye5_TA_tex_txt[];
extern unsigned char ant_5_eye6_TA_tex_txt[];
extern unsigned char ant_5_eye7_TA_tex_txt[];
extern unsigned char ant_5_eye8_TA_tex_txt[];
extern unsigned char ant_5_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_bea_1;
extern unsigned short bea_1_pal[];
extern unsigned char bea_1_eye1_TA_tex_txt[];
extern unsigned char bea_1_eye2_TA_tex_txt[];
extern unsigned char bea_1_eye3_TA_tex_txt[];
extern unsigned char bea_1_eye4_TA_tex_txt[];
extern unsigned char bea_1_eye5_TA_tex_txt[];
extern unsigned char bea_1_eye6_TA_tex_txt[];
extern unsigned char bea_1_eye7_TA_tex_txt[];
extern unsigned char bea_1_eye8_TA_tex_txt[];
extern unsigned char bea_1_mouth1_TA_tex_txt[];
extern unsigned char bea_1_mouth2_TA_tex_txt[];
extern unsigned char bea_1_mouth3_TA_tex_txt[];
extern unsigned char bea_1_mouth4_TA_tex_txt[];
extern unsigned char bea_1_mouth5_TA_tex_txt[];
extern unsigned char bea_1_mouth6_TA_tex_txt[];
extern unsigned char bea_1_tmem_txt[];
extern unsigned short bea_2_pal[];
extern unsigned char bea_2_eye1_TA_tex_txt[];
extern unsigned char bea_2_eye2_TA_tex_txt[];
extern unsigned char bea_2_eye3_TA_tex_txt[];
extern unsigned char bea_2_eye4_TA_tex_txt[];
extern unsigned char bea_2_eye5_TA_tex_txt[];
extern unsigned char bea_2_eye6_TA_tex_txt[];
extern unsigned char bea_2_eye7_TA_tex_txt[];
extern unsigned char bea_2_eye8_TA_tex_txt[];
extern unsigned char bea_2_mouth1_TA_tex_txt[];
extern unsigned char bea_2_mouth2_TA_tex_txt[];
extern unsigned char bea_2_mouth3_TA_tex_txt[];
extern unsigned char bea_2_mouth4_TA_tex_txt[];
extern unsigned char bea_2_mouth5_TA_tex_txt[];
extern unsigned char bea_2_mouth6_TA_tex_txt[];
extern unsigned char bea_2_tmem_txt[];
extern unsigned short bea_3_pal[];
extern unsigned char bea_3_eye1_TA_tex_txt[];
extern unsigned char bea_3_eye2_TA_tex_txt[];
extern unsigned char bea_3_eye3_TA_tex_txt[];
extern unsigned char bea_3_eye4_TA_tex_txt[];
extern unsigned char bea_3_eye5_TA_tex_txt[];
extern unsigned char bea_3_eye6_TA_tex_txt[];
extern unsigned char bea_3_eye7_TA_tex_txt[];
extern unsigned char bea_3_eye8_TA_tex_txt[];
extern unsigned char bea_3_mouth1_TA_tex_txt[];
extern unsigned char bea_3_mouth2_TA_tex_txt[];
extern unsigned char bea_3_mouth3_TA_tex_txt[];
extern unsigned char bea_3_mouth4_TA_tex_txt[];
extern unsigned char bea_3_mouth5_TA_tex_txt[];
extern unsigned char bea_3_mouth6_TA_tex_txt[];
extern unsigned char bea_3_tmem_txt[];
extern unsigned short bea_5_pal[];
extern unsigned char bea_5_eye1_TA_tex_txt[];
extern unsigned char bea_5_eye2_TA_tex_txt[];
extern unsigned char bea_5_eye3_TA_tex_txt[];
extern unsigned char bea_5_eye4_TA_tex_txt[];
extern unsigned char bea_5_eye5_TA_tex_txt[];
extern unsigned char bea_5_eye6_TA_tex_txt[];
extern unsigned char bea_5_eye7_TA_tex_txt[];
extern unsigned char bea_5_eye8_TA_tex_txt[];
extern unsigned char bea_5_mouth1_TA_tex_txt[];
extern unsigned char bea_5_mouth2_TA_tex_txt[];
extern unsigned char bea_5_mouth3_TA_tex_txt[];
extern unsigned char bea_5_mouth4_TA_tex_txt[];
extern unsigned char bea_5_mouth5_TA_tex_txt[];
extern unsigned char bea_5_mouth6_TA_tex_txt[];
extern unsigned char bea_5_tmem_txt[];
extern unsigned short bea_6_pal[];
extern unsigned char bea_6_eye1_TA_tex_txt[];
extern unsigned char bea_6_eye2_TA_tex_txt[];
extern unsigned char bea_6_eye3_TA_tex_txt[];
extern unsigned char bea_6_eye4_TA_tex_txt[];
extern unsigned char bea_6_eye5_TA_tex_txt[];
extern unsigned char bea_6_eye6_TA_tex_txt[];
extern unsigned char bea_6_eye7_TA_tex_txt[];
extern unsigned char bea_6_eye8_TA_tex_txt[];
extern unsigned char bea_6_mouth1_TA_tex_txt[];
extern unsigned char bea_6_mouth2_TA_tex_txt[];
extern unsigned char bea_6_mouth3_TA_tex_txt[];
extern unsigned char bea_6_mouth4_TA_tex_txt[];
extern unsigned char bea_6_mouth5_TA_tex_txt[];
extern unsigned char bea_6_mouth6_TA_tex_txt[];
extern unsigned char bea_6_tmem_txt[];
extern unsigned short bea_7_pal[];
extern unsigned char bea_7_eye1_TA_tex_txt[];
extern unsigned char bea_7_eye2_TA_tex_txt[];
extern unsigned char bea_7_eye3_TA_tex_txt[];
extern unsigned char bea_7_eye4_TA_tex_txt[];
extern unsigned char bea_7_eye5_TA_tex_txt[];
extern unsigned char bea_7_eye6_TA_tex_txt[];
extern unsigned char bea_7_eye7_TA_tex_txt[];
extern unsigned char bea_7_eye8_TA_tex_txt[];
extern unsigned char bea_7_mouth1_TA_tex_txt[];
extern unsigned char bea_7_mouth2_TA_tex_txt[];
extern unsigned char bea_7_mouth3_TA_tex_txt[];
extern unsigned char bea_7_mouth4_TA_tex_txt[];
extern unsigned char bea_7_mouth5_TA_tex_txt[];
extern unsigned char bea_7_mouth6_TA_tex_txt[];
extern unsigned char bea_7_tmem_txt[];
extern unsigned short bea_8_pal[];
extern unsigned char bea_8_eye1_TA_tex_txt[];
extern unsigned char bea_8_eye2_TA_tex_txt[];
extern unsigned char bea_8_eye3_TA_tex_txt[];
extern unsigned char bea_8_eye4_TA_tex_txt[];
extern unsigned char bea_8_eye5_TA_tex_txt[];
extern unsigned char bea_8_eye6_TA_tex_txt[];
extern unsigned char bea_8_eye7_TA_tex_txt[];
extern unsigned char bea_8_eye8_TA_tex_txt[];
extern unsigned char bea_8_mouth1_TA_tex_txt[];
extern unsigned char bea_8_mouth2_TA_tex_txt[];
extern unsigned char bea_8_mouth3_TA_tex_txt[];
extern unsigned char bea_8_mouth4_TA_tex_txt[];
extern unsigned char bea_8_mouth5_TA_tex_txt[];
extern unsigned char bea_8_mouth6_TA_tex_txt[];
extern unsigned char bea_8_tmem_txt[];
extern unsigned short bea_9_pal[];
extern unsigned char bea_9_eye1_TA_tex_txt[];
extern unsigned char bea_9_eye2_TA_tex_txt[];
extern unsigned char bea_9_eye3_TA_tex_txt[];
extern unsigned char bea_9_eye4_TA_tex_txt[];
extern unsigned char bea_9_eye5_TA_tex_txt[];
extern unsigned char bea_9_eye6_TA_tex_txt[];
extern unsigned char bea_9_eye7_TA_tex_txt[];
extern unsigned char bea_9_eye8_TA_tex_txt[];
extern unsigned char bea_9_mouth1_TA_tex_txt[];
extern unsigned char bea_9_mouth2_TA_tex_txt[];
extern unsigned char bea_9_mouth3_TA_tex_txt[];
extern unsigned char bea_9_mouth4_TA_tex_txt[];
extern unsigned char bea_9_mouth5_TA_tex_txt[];
extern unsigned char bea_9_mouth6_TA_tex_txt[];
extern unsigned char bea_9_tmem_txt[];
extern unsigned short bea_10_pal[];
extern unsigned char bea_10_eye1_TA_tex_txt[];
extern unsigned char bea_10_eye2_TA_tex_txt[];
extern unsigned char bea_10_eye3_TA_tex_txt[];
extern unsigned char bea_10_eye4_TA_tex_txt[];
extern unsigned char bea_10_eye5_TA_tex_txt[];
extern unsigned char bea_10_eye6_TA_tex_txt[];
extern unsigned char bea_10_eye7_TA_tex_txt[];
extern unsigned char bea_10_eye8_TA_tex_txt[];
extern unsigned char bea_10_mouth1_TA_tex_txt[];
extern unsigned char bea_10_mouth2_TA_tex_txt[];
extern unsigned char bea_10_mouth3_TA_tex_txt[];
extern unsigned char bea_10_mouth4_TA_tex_txt[];
extern unsigned char bea_10_mouth5_TA_tex_txt[];
extern unsigned char bea_10_mouth6_TA_tex_txt[];
extern unsigned char bea_10_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_brd_1;
extern unsigned short brd_1_pal[];
extern unsigned char brd_1_eye1_TA_tex_txt[];
extern unsigned char brd_1_eye2_TA_tex_txt[];
extern unsigned char brd_1_eye3_TA_tex_txt[];
extern unsigned char brd_1_eye4_TA_tex_txt[];
extern unsigned char brd_1_eye5_TA_tex_txt[];
extern unsigned char brd_1_eye6_TA_tex_txt[];
extern unsigned char brd_1_eye7_TA_tex_txt[];
extern unsigned char brd_1_eye8_TA_tex_txt[];
extern unsigned char brd_1_tmem_txt[];
extern unsigned short brd_2_pal[];
extern unsigned char brd_2_eye1_TA_tex_txt[];
extern unsigned char brd_2_eye2_TA_tex_txt[];
extern unsigned char brd_2_eye3_TA_tex_txt[];
extern unsigned char brd_2_eye4_TA_tex_txt[];
extern unsigned char brd_2_eye5_TA_tex_txt[];
extern unsigned char brd_2_eye6_TA_tex_txt[];
extern unsigned char brd_2_eye7_TA_tex_txt[];
extern unsigned char brd_2_eye8_TA_tex_txt[];
extern unsigned char brd_2_tmem_txt[];
extern unsigned short brd_3_pal[];
extern unsigned char brd_3_eye1_TA_tex_txt[];
extern unsigned char brd_3_eye2_TA_tex_txt[];
extern unsigned char brd_3_eye3_TA_tex_txt[];
extern unsigned char brd_3_eye4_TA_tex_txt[];
extern unsigned char brd_3_eye5_TA_tex_txt[];
extern unsigned char brd_3_eye6_TA_tex_txt[];
extern unsigned char brd_3_eye7_TA_tex_txt[];
extern unsigned char brd_3_eye8_TA_tex_txt[];
extern unsigned char brd_3_tmem_txt[];
extern unsigned short brd_4_pal[];
extern unsigned char brd_4_eye1_TA_tex_txt[];
extern unsigned char brd_4_eye2_TA_tex_txt[];
extern unsigned char brd_4_eye3_TA_tex_txt[];
extern unsigned char brd_4_eye4_TA_tex_txt[];
extern unsigned char brd_4_eye5_TA_tex_txt[];
extern unsigned char brd_4_eye6_TA_tex_txt[];
extern unsigned char brd_4_eye7_TA_tex_txt[];
extern unsigned char brd_4_eye8_TA_tex_txt[];
extern unsigned char brd_4_tmem_txt[];
extern unsigned short brd_5_pal[];
extern unsigned char brd_5_eye1_TA_tex_txt[];
extern unsigned char brd_5_eye2_TA_tex_txt[];
extern unsigned char brd_5_eye3_TA_tex_txt[];
extern unsigned char brd_5_eye4_TA_tex_txt[];
extern unsigned char brd_5_eye5_TA_tex_txt[];
extern unsigned char brd_5_eye6_TA_tex_txt[];
extern unsigned char brd_5_eye7_TA_tex_txt[];
extern unsigned char brd_5_eye8_TA_tex_txt[];
extern unsigned char brd_5_tmem_txt[];
extern unsigned short brd_6_pal[];
extern unsigned char brd_6_eye1_TA_tex_txt[];
extern unsigned char brd_6_eye2_TA_tex_txt[];
extern unsigned char brd_6_eye3_TA_tex_txt[];
extern unsigned char brd_6_eye4_TA_tex_txt[];
extern unsigned char brd_6_eye5_TA_tex_txt[];
extern unsigned char brd_6_eye6_TA_tex_txt[];
extern unsigned char brd_6_eye7_TA_tex_txt[];
extern unsigned char brd_6_eye8_TA_tex_txt[];
extern unsigned char brd_6_tmem_txt[];
extern unsigned short brd_7_pal[];
extern unsigned char brd_7_eye1_TA_tex_txt[];
extern unsigned char brd_7_eye2_TA_tex_txt[];
extern unsigned char brd_7_eye3_TA_tex_txt[];
extern unsigned char brd_7_eye4_TA_tex_txt[];
extern unsigned char brd_7_eye5_TA_tex_txt[];
extern unsigned char brd_7_eye6_TA_tex_txt[];
extern unsigned char brd_7_eye7_TA_tex_txt[];
extern unsigned char brd_7_eye8_TA_tex_txt[];
extern unsigned char brd_7_tmem_txt[];
extern unsigned short brd_8_pal[];
extern unsigned char brd_8_eye1_TA_tex_txt[];
extern unsigned char brd_8_eye2_TA_tex_txt[];
extern unsigned char brd_8_eye3_TA_tex_txt[];
extern unsigned char brd_8_eye4_TA_tex_txt[];
extern unsigned char brd_8_eye5_TA_tex_txt[];
extern unsigned char brd_8_eye6_TA_tex_txt[];
extern unsigned char brd_8_eye7_TA_tex_txt[];
extern unsigned char brd_8_eye8_TA_tex_txt[];
extern unsigned char brd_8_tmem_txt[];
extern unsigned short brd_9_pal[];
extern unsigned char brd_9_eye1_TA_tex_txt[];
extern unsigned char brd_9_eye2_TA_tex_txt[];
extern unsigned char brd_9_eye3_TA_tex_txt[];
extern unsigned char brd_9_eye4_TA_tex_txt[];
extern unsigned char brd_9_eye5_TA_tex_txt[];
extern unsigned char brd_9_eye6_TA_tex_txt[];
extern unsigned char brd_9_eye7_TA_tex_txt[];
extern unsigned char brd_9_eye8_TA_tex_txt[];
extern unsigned char brd_9_tmem_txt[];
extern unsigned short brd_10_pal[];
extern unsigned char brd_10_eye1_TA_tex_txt[];
extern unsigned char brd_10_eye2_TA_tex_txt[];
extern unsigned char brd_10_eye3_TA_tex_txt[];
extern unsigned char brd_10_eye4_TA_tex_txt[];
extern unsigned char brd_10_eye5_TA_tex_txt[];
extern unsigned char brd_10_eye6_TA_tex_txt[];
extern unsigned char brd_10_eye7_TA_tex_txt[];
extern unsigned char brd_10_eye8_TA_tex_txt[];
extern unsigned char brd_10_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_bul_1;
extern unsigned short bul_1_pal[];
extern unsigned char bul_1_eye1_TA_tex_txt[];
extern unsigned char bul_1_eye2_TA_tex_txt[];
extern unsigned char bul_1_eye3_TA_tex_txt[];
extern unsigned char bul_1_eye4_TA_tex_txt[];
extern unsigned char bul_1_eye5_TA_tex_txt[];
extern unsigned char bul_1_eye6_TA_tex_txt[];
extern unsigned char bul_1_eye7_TA_tex_txt[];
extern unsigned char bul_1_eye8_TA_tex_txt[];
extern unsigned char bul_1_mouth1_TA_tex_txt[];
extern unsigned char bul_1_mouth2_TA_tex_txt[];
extern unsigned char bul_1_mouth3_TA_tex_txt[];
extern unsigned char bul_1_mouth4_TA_tex_txt[];
extern unsigned char bul_1_mouth5_TA_tex_txt[];
extern unsigned char bul_1_mouth6_TA_tex_txt[];
extern unsigned char bul_1_tmem_txt[];
extern unsigned short bul_2_pal[];
extern unsigned char bul_2_eye1_TA_tex_txt[];
extern unsigned char bul_2_eye2_TA_tex_txt[];
extern unsigned char bul_2_eye3_TA_tex_txt[];
extern unsigned char bul_2_eye4_TA_tex_txt[];
extern unsigned char bul_2_eye5_TA_tex_txt[];
extern unsigned char bul_2_eye6_TA_tex_txt[];
extern unsigned char bul_2_eye7_TA_tex_txt[];
extern unsigned char bul_2_eye8_TA_tex_txt[];
extern unsigned char bul_2_mouth1_TA_tex_txt[];
extern unsigned char bul_2_mouth2_TA_tex_txt[];
extern unsigned char bul_2_mouth3_TA_tex_txt[];
extern unsigned char bul_2_mouth4_TA_tex_txt[];
extern unsigned char bul_2_mouth5_TA_tex_txt[];
extern unsigned char bul_2_mouth6_TA_tex_txt[];
extern unsigned char bul_2_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_chn_1;
extern unsigned short chn_1_pal[];
extern unsigned char chn_1_eye1_TA_tex_txt[];
extern unsigned char chn_1_eye2_TA_tex_txt[];
extern unsigned char chn_1_eye3_TA_tex_txt[];
extern unsigned char chn_1_eye4_TA_tex_txt[];
extern unsigned char chn_1_eye5_TA_tex_txt[];
extern unsigned char chn_1_eye6_TA_tex_txt[];
extern unsigned char chn_1_eye7_TA_tex_txt[];
extern unsigned char chn_1_eye8_TA_tex_txt[];
extern unsigned char chn_1_tmem_txt[];
extern unsigned short chn_2_pal[];
extern unsigned char chn_2_eye1_TA_tex_txt[];
extern unsigned char chn_2_eye2_TA_tex_txt[];
extern unsigned char chn_2_eye3_TA_tex_txt[];
extern unsigned char chn_2_eye4_TA_tex_txt[];
extern unsigned char chn_2_eye5_TA_tex_txt[];
extern unsigned char chn_2_eye6_TA_tex_txt[];
extern unsigned char chn_2_eye7_TA_tex_txt[];
extern unsigned char chn_2_eye8_TA_tex_txt[];
extern unsigned char chn_2_tmem_txt[];
extern unsigned short chn_3_pal[];
extern unsigned char chn_3_eye1_TA_tex_txt[];
extern unsigned char chn_3_eye2_TA_tex_txt[];
extern unsigned char chn_3_eye3_TA_tex_txt[];
extern unsigned char chn_3_eye4_TA_tex_txt[];
extern unsigned char chn_3_eye5_TA_tex_txt[];
extern unsigned char chn_3_eye6_TA_tex_txt[];
extern unsigned char chn_3_eye7_TA_tex_txt[];
extern unsigned char chn_3_eye8_TA_tex_txt[];
extern unsigned char chn_3_tmem_txt[];
extern unsigned short chn_4_pal[];
extern unsigned char chn_4_eye1_TA_tex_txt[];
extern unsigned char chn_4_eye2_TA_tex_txt[];
extern unsigned char chn_4_eye3_TA_tex_txt[];
extern unsigned char chn_4_eye4_TA_tex_txt[];
extern unsigned char chn_4_eye5_TA_tex_txt[];
extern unsigned char chn_4_eye6_TA_tex_txt[];
extern unsigned char chn_4_eye7_TA_tex_txt[];
extern unsigned char chn_4_eye8_TA_tex_txt[];
extern unsigned char chn_4_tmem_txt[];
extern unsigned short chn_5_pal[];
extern unsigned char chn_5_eye1_TA_tex_txt[];
extern unsigned char chn_5_eye2_TA_tex_txt[];
extern unsigned char chn_5_eye3_TA_tex_txt[];
extern unsigned char chn_5_eye4_TA_tex_txt[];
extern unsigned char chn_5_eye5_TA_tex_txt[];
extern unsigned char chn_5_eye6_TA_tex_txt[];
extern unsigned char chn_5_eye7_TA_tex_txt[];
extern unsigned char chn_5_eye8_TA_tex_txt[];
extern unsigned char chn_5_tmem_txt[];
extern unsigned short chn_6_pal[];
extern unsigned char chn_6_eye1_TA_tex_txt[];
extern unsigned char chn_6_eye2_TA_tex_txt[];
extern unsigned char chn_6_eye3_TA_tex_txt[];
extern unsigned char chn_6_eye4_TA_tex_txt[];
extern unsigned char chn_6_eye5_TA_tex_txt[];
extern unsigned char chn_6_eye6_TA_tex_txt[];
extern unsigned char chn_6_eye7_TA_tex_txt[];
extern unsigned char chn_6_eye8_TA_tex_txt[];
extern unsigned char chn_6_tmem_txt[];
extern unsigned short chn_7_pal[];
extern unsigned char chn_7_eye1_TA_tex_txt[];
extern unsigned char chn_7_eye2_TA_tex_txt[];
extern unsigned char chn_7_eye3_TA_tex_txt[];
extern unsigned char chn_7_eye4_TA_tex_txt[];
extern unsigned char chn_7_eye5_TA_tex_txt[];
extern unsigned char chn_7_eye6_TA_tex_txt[];
extern unsigned char chn_7_eye7_TA_tex_txt[];
extern unsigned char chn_7_eye8_TA_tex_txt[];
extern unsigned char chn_7_tmem_txt[];
extern unsigned short chn_8_pal[];
extern unsigned char chn_8_eye1_TA_tex_txt[];
extern unsigned char chn_8_eye2_TA_tex_txt[];
extern unsigned char chn_8_eye3_TA_tex_txt[];
extern unsigned char chn_8_eye4_TA_tex_txt[];
extern unsigned char chn_8_eye5_TA_tex_txt[];
extern unsigned char chn_8_eye6_TA_tex_txt[];
extern unsigned char chn_8_eye7_TA_tex_txt[];
extern unsigned char chn_8_eye8_TA_tex_txt[];
extern unsigned char chn_8_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_cbr_1;
extern unsigned short cbr_1_pal[];
extern unsigned char cbr_1_eye1_TA_tex_txt[];
extern unsigned char cbr_1_eye2_TA_tex_txt[];
extern unsigned char cbr_1_eye3_TA_tex_txt[];
extern unsigned char cbr_1_eye4_TA_tex_txt[];
extern unsigned char cbr_1_eye5_TA_tex_txt[];
extern unsigned char cbr_1_eye6_TA_tex_txt[];
extern unsigned char cbr_1_eye7_TA_tex_txt[];
extern unsigned char cbr_1_eye8_TA_tex_txt[];
extern unsigned char cbr_1_mouth1_TA_tex_txt[];
extern unsigned char cbr_1_mouth2_TA_tex_txt[];
extern unsigned char cbr_1_mouth3_TA_tex_txt[];
extern unsigned char cbr_1_mouth4_TA_tex_txt[];
extern unsigned char cbr_1_mouth5_TA_tex_txt[];
extern unsigned char cbr_1_mouth6_TA_tex_txt[];
extern unsigned char cbr_1_tmem_txt[];
extern unsigned short cbr_2_pal[];
extern unsigned char cbr_2_eye1_TA_tex_txt[];
extern unsigned char cbr_2_eye2_TA_tex_txt[];
extern unsigned char cbr_2_eye3_TA_tex_txt[];
extern unsigned char cbr_2_eye4_TA_tex_txt[];
extern unsigned char cbr_2_eye5_TA_tex_txt[];
extern unsigned char cbr_2_eye6_TA_tex_txt[];
extern unsigned char cbr_2_eye7_TA_tex_txt[];
extern unsigned char cbr_2_eye8_TA_tex_txt[];
extern unsigned char cbr_2_mouth1_TA_tex_txt[];
extern unsigned char cbr_2_mouth2_TA_tex_txt[];
extern unsigned char cbr_2_mouth3_TA_tex_txt[];
extern unsigned char cbr_2_mouth4_TA_tex_txt[];
extern unsigned char cbr_2_mouth5_TA_tex_txt[];
extern unsigned char cbr_2_mouth6_TA_tex_txt[];
extern unsigned char cbr_2_tmem_txt[];
extern unsigned short cbr_3_pal[];
extern unsigned char cbr_3_eye1_TA_tex_txt[];
extern unsigned char cbr_3_eye2_TA_tex_txt[];
extern unsigned char cbr_3_eye3_TA_tex_txt[];
extern unsigned char cbr_3_eye4_TA_tex_txt[];
extern unsigned char cbr_3_eye5_TA_tex_txt[];
extern unsigned char cbr_3_eye6_TA_tex_txt[];
extern unsigned char cbr_3_eye7_TA_tex_txt[];
extern unsigned char cbr_3_eye8_TA_tex_txt[];
extern unsigned char cbr_3_mouth1_TA_tex_txt[];
extern unsigned char cbr_3_mouth2_TA_tex_txt[];
extern unsigned char cbr_3_mouth3_TA_tex_txt[];
extern unsigned char cbr_3_mouth4_TA_tex_txt[];
extern unsigned char cbr_3_mouth5_TA_tex_txt[];
extern unsigned char cbr_3_mouth6_TA_tex_txt[];
extern unsigned char cbr_3_tmem_txt[];
extern unsigned short cbr_4_pal[];
extern unsigned char cbr_4_eye1_TA_tex_txt[];
extern unsigned char cbr_4_eye2_TA_tex_txt[];
extern unsigned char cbr_4_eye3_TA_tex_txt[];
extern unsigned char cbr_4_eye4_TA_tex_txt[];
extern unsigned char cbr_4_eye5_TA_tex_txt[];
extern unsigned char cbr_4_eye6_TA_tex_txt[];
extern unsigned char cbr_4_eye7_TA_tex_txt[];
extern unsigned char cbr_4_eye8_TA_tex_txt[];
extern unsigned char cbr_4_mouth1_TA_tex_txt[];
extern unsigned char cbr_4_mouth2_TA_tex_txt[];
extern unsigned char cbr_4_mouth3_TA_tex_txt[];
extern unsigned char cbr_4_mouth4_TA_tex_txt[];
extern unsigned char cbr_4_mouth5_TA_tex_txt[];
extern unsigned char cbr_4_mouth6_TA_tex_txt[];
extern unsigned char cbr_4_tmem_txt[];
extern unsigned short cbr_5_pal[];
extern unsigned char cbr_5_eye1_TA_tex_txt[];
extern unsigned char cbr_5_eye2_TA_tex_txt[];
extern unsigned char cbr_5_eye3_TA_tex_txt[];
extern unsigned char cbr_5_eye4_TA_tex_txt[];
extern unsigned char cbr_5_eye5_TA_tex_txt[];
extern unsigned char cbr_5_eye6_TA_tex_txt[];
extern unsigned char cbr_5_eye7_TA_tex_txt[];
extern unsigned char cbr_5_eye8_TA_tex_txt[];
extern unsigned char cbr_5_mouth1_TA_tex_txt[];
extern unsigned char cbr_5_mouth2_TA_tex_txt[];
extern unsigned char cbr_5_mouth3_TA_tex_txt[];
extern unsigned char cbr_5_mouth4_TA_tex_txt[];
extern unsigned char cbr_5_mouth5_TA_tex_txt[];
extern unsigned char cbr_5_mouth6_TA_tex_txt[];
extern unsigned char cbr_5_tmem_txt[];
extern unsigned short cbr_6_pal[];
extern unsigned char cbr_6_eye1_TA_tex_txt[];
extern unsigned char cbr_6_eye2_TA_tex_txt[];
extern unsigned char cbr_6_eye3_TA_tex_txt[];
extern unsigned char cbr_6_eye4_TA_tex_txt[];
extern unsigned char cbr_6_eye5_TA_tex_txt[];
extern unsigned char cbr_6_eye6_TA_tex_txt[];
extern unsigned char cbr_6_eye7_TA_tex_txt[];
extern unsigned char cbr_6_eye8_TA_tex_txt[];
extern unsigned char cbr_6_mouth1_TA_tex_txt[];
extern unsigned char cbr_6_mouth2_TA_tex_txt[];
extern unsigned char cbr_6_mouth3_TA_tex_txt[];
extern unsigned char cbr_6_mouth4_TA_tex_txt[];
extern unsigned char cbr_6_mouth5_TA_tex_txt[];
extern unsigned char cbr_6_mouth6_TA_tex_txt[];
extern unsigned char cbr_6_tmem_txt[];
extern unsigned short cbr_7_pal[];
extern unsigned char cbr_7_eye1_TA_tex_txt[];
extern unsigned char cbr_7_eye2_TA_tex_txt[];
extern unsigned char cbr_7_eye3_TA_tex_txt[];
extern unsigned char cbr_7_eye4_TA_tex_txt[];
extern unsigned char cbr_7_eye5_TA_tex_txt[];
extern unsigned char cbr_7_eye6_TA_tex_txt[];
extern unsigned char cbr_7_eye7_TA_tex_txt[];
extern unsigned char cbr_7_eye8_TA_tex_txt[];
extern unsigned char cbr_7_mouth1_TA_tex_txt[];
extern unsigned char cbr_7_mouth2_TA_tex_txt[];
extern unsigned char cbr_7_mouth3_TA_tex_txt[];
extern unsigned char cbr_7_mouth4_TA_tex_txt[];
extern unsigned char cbr_7_mouth5_TA_tex_txt[];
extern unsigned char cbr_7_mouth6_TA_tex_txt[];
extern unsigned char cbr_7_tmem_txt[];
extern unsigned short cbr_8_pal[];
extern unsigned char cbr_8_eye1_TA_tex_txt[];
extern unsigned char cbr_8_eye2_TA_tex_txt[];
extern unsigned char cbr_8_eye3_TA_tex_txt[];
extern unsigned char cbr_8_eye4_TA_tex_txt[];
extern unsigned char cbr_8_eye5_TA_tex_txt[];
extern unsigned char cbr_8_eye6_TA_tex_txt[];
extern unsigned char cbr_8_eye7_TA_tex_txt[];
extern unsigned char cbr_8_eye8_TA_tex_txt[];
extern unsigned char cbr_8_mouth1_TA_tex_txt[];
extern unsigned char cbr_8_mouth2_TA_tex_txt[];
extern unsigned char cbr_8_mouth3_TA_tex_txt[];
extern unsigned char cbr_8_mouth4_TA_tex_txt[];
extern unsigned char cbr_8_mouth5_TA_tex_txt[];
extern unsigned char cbr_8_mouth6_TA_tex_txt[];
extern unsigned char cbr_8_tmem_txt[];
extern unsigned short cbr_9_pal[];
extern unsigned char cbr_9_eye1_TA_tex_txt[];
extern unsigned char cbr_9_eye2_TA_tex_txt[];
extern unsigned char cbr_9_eye3_TA_tex_txt[];
extern unsigned char cbr_9_eye4_TA_tex_txt[];
extern unsigned char cbr_9_eye5_TA_tex_txt[];
extern unsigned char cbr_9_eye6_TA_tex_txt[];
extern unsigned char cbr_9_eye7_TA_tex_txt[];
extern unsigned char cbr_9_eye8_TA_tex_txt[];
extern unsigned char cbr_9_mouth1_TA_tex_txt[];
extern unsigned char cbr_9_mouth2_TA_tex_txt[];
extern unsigned char cbr_9_mouth3_TA_tex_txt[];
extern unsigned char cbr_9_mouth4_TA_tex_txt[];
extern unsigned char cbr_9_mouth5_TA_tex_txt[];
extern unsigned char cbr_9_mouth6_TA_tex_txt[];
extern unsigned char cbr_9_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_cow_1;
extern unsigned short cow_1_pal[];
extern unsigned char cow_1_eye1_TA_tex_txt[];
extern unsigned char cow_1_eye2_TA_tex_txt[];
extern unsigned char cow_1_eye3_TA_tex_txt[];
extern unsigned char cow_1_eye4_TA_tex_txt[];
extern unsigned char cow_1_eye5_TA_tex_txt[];
extern unsigned char cow_1_eye6_TA_tex_txt[];
extern unsigned char cow_1_eye7_TA_tex_txt[];
extern unsigned char cow_1_eye8_TA_tex_txt[];
extern unsigned char cow_1_mouth1_TA_tex_txt[];
extern unsigned char cow_1_mouth2_TA_tex_txt[];
extern unsigned char cow_1_mouth3_TA_tex_txt[];
extern unsigned char cow_1_mouth4_TA_tex_txt[];
extern unsigned char cow_1_mouth5_TA_tex_txt[];
extern unsigned char cow_1_mouth6_TA_tex_txt[];
extern unsigned char cow_1_tmem_txt[];
extern unsigned short cow_2_pal[];
extern unsigned char cow_2_eye1_TA_tex_txt[];
extern unsigned char cow_2_eye2_TA_tex_txt[];
extern unsigned char cow_2_eye3_TA_tex_txt[];
extern unsigned char cow_2_eye4_TA_tex_txt[];
extern unsigned char cow_2_eye5_TA_tex_txt[];
extern unsigned char cow_2_eye6_TA_tex_txt[];
extern unsigned char cow_2_eye7_TA_tex_txt[];
extern unsigned char cow_2_eye8_TA_tex_txt[];
extern unsigned char cow_2_mouth1_TA_tex_txt[];
extern unsigned char cow_2_mouth2_TA_tex_txt[];
extern unsigned char cow_2_mouth3_TA_tex_txt[];
extern unsigned char cow_2_mouth4_TA_tex_txt[];
extern unsigned char cow_2_mouth5_TA_tex_txt[];
extern unsigned char cow_2_mouth6_TA_tex_txt[];
extern unsigned char cow_2_tmem_txt[];
extern unsigned short cow_3_pal[];
extern unsigned char cow_3_eye1_TA_tex_txt[];
extern unsigned char cow_3_eye2_TA_tex_txt[];
extern unsigned char cow_3_eye3_TA_tex_txt[];
extern unsigned char cow_3_eye4_TA_tex_txt[];
extern unsigned char cow_3_eye5_TA_tex_txt[];
extern unsigned char cow_3_eye6_TA_tex_txt[];
extern unsigned char cow_3_eye7_TA_tex_txt[];
extern unsigned char cow_3_eye8_TA_tex_txt[];
extern unsigned char cow_3_mouth1_TA_tex_txt[];
extern unsigned char cow_3_mouth2_TA_tex_txt[];
extern unsigned char cow_3_mouth3_TA_tex_txt[];
extern unsigned char cow_3_mouth4_TA_tex_txt[];
extern unsigned char cow_3_mouth5_TA_tex_txt[];
extern unsigned char cow_3_mouth6_TA_tex_txt[];
extern unsigned char cow_3_tmem_txt[];
extern unsigned short cow_4_pal[];
extern unsigned char cow_4_eye1_TA_tex_txt[];
extern unsigned char cow_4_eye2_TA_tex_txt[];
extern unsigned char cow_4_eye3_TA_tex_txt[];
extern unsigned char cow_4_eye4_TA_tex_txt[];
extern unsigned char cow_4_eye5_TA_tex_txt[];
extern unsigned char cow_4_eye6_TA_tex_txt[];
extern unsigned char cow_4_eye7_TA_tex_txt[];
extern unsigned char cow_4_eye8_TA_tex_txt[];
extern unsigned char cow_4_mouth1_TA_tex_txt[];
extern unsigned char cow_4_mouth2_TA_tex_txt[];
extern unsigned char cow_4_mouth3_TA_tex_txt[];
extern unsigned char cow_4_mouth4_TA_tex_txt[];
extern unsigned char cow_4_mouth5_TA_tex_txt[];
extern unsigned char cow_4_mouth6_TA_tex_txt[];
extern unsigned char cow_4_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_crd_1;
extern unsigned short crd_1_pal[];
extern unsigned char crd_1_eye1_TA_tex_txt[];
extern unsigned char crd_1_eye2_TA_tex_txt[];
extern unsigned char crd_1_eye3_TA_tex_txt[];
extern unsigned char crd_1_eye4_TA_tex_txt[];
extern unsigned char crd_1_eye5_TA_tex_txt[];
extern unsigned char crd_1_eye6_TA_tex_txt[];
extern unsigned char crd_1_eye7_TA_tex_txt[];
extern unsigned char crd_1_eye8_TA_tex_txt[];
extern unsigned char crd_1_tmem_txt[];
extern unsigned short crd_2_pal[];
extern unsigned char crd_2_eye1_TA_tex_txt[];
extern unsigned char crd_2_eye2_TA_tex_txt[];
extern unsigned char crd_2_eye3_TA_tex_txt[];
extern unsigned char crd_2_eye4_TA_tex_txt[];
extern unsigned char crd_2_eye5_TA_tex_txt[];
extern unsigned char crd_2_eye6_TA_tex_txt[];
extern unsigned char crd_2_eye7_TA_tex_txt[];
extern unsigned char crd_2_eye8_TA_tex_txt[];
extern unsigned char crd_2_tmem_txt[];
extern unsigned short crd_3_pal[];
extern unsigned char crd_3_eye1_TA_tex_txt[];
extern unsigned char crd_3_eye2_TA_tex_txt[];
extern unsigned char crd_3_eye3_TA_tex_txt[];
extern unsigned char crd_3_eye4_TA_tex_txt[];
extern unsigned char crd_3_eye5_TA_tex_txt[];
extern unsigned char crd_3_eye6_TA_tex_txt[];
extern unsigned char crd_3_eye7_TA_tex_txt[];
extern unsigned char crd_3_eye8_TA_tex_txt[];
extern unsigned char crd_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_dog_1;
extern unsigned short dog_1_pal[];
extern unsigned char dog_1_eye1_TA_tex_txt[];
extern unsigned char dog_1_eye2_TA_tex_txt[];
extern unsigned char dog_1_eye3_TA_tex_txt[];
extern unsigned char dog_1_eye4_TA_tex_txt[];
extern unsigned char dog_1_eye5_TA_tex_txt[];
extern unsigned char dog_1_eye6_TA_tex_txt[];
extern unsigned char dog_1_eye7_TA_tex_txt[];
extern unsigned char dog_1_eye8_TA_tex_txt[];
extern unsigned char dog_1_mouth1_TA_tex_txt[];
extern unsigned char dog_1_mouth2_TA_tex_txt[];
extern unsigned char dog_1_mouth3_TA_tex_txt[];
extern unsigned char dog_1_mouth4_TA_tex_txt[];
extern unsigned char dog_1_mouth5_TA_tex_txt[];
extern unsigned char dog_1_mouth6_TA_tex_txt[];
extern unsigned char dog_1_tmem_txt[];
extern unsigned short dog_2_pal[];
extern unsigned char dog_2_eye1_TA_tex_txt[];
extern unsigned char dog_2_eye2_TA_tex_txt[];
extern unsigned char dog_2_eye3_TA_tex_txt[];
extern unsigned char dog_2_eye4_TA_tex_txt[];
extern unsigned char dog_2_eye5_TA_tex_txt[];
extern unsigned char dog_2_eye6_TA_tex_txt[];
extern unsigned char dog_2_eye7_TA_tex_txt[];
extern unsigned char dog_2_eye8_TA_tex_txt[];
extern unsigned char dog_2_mouth1_TA_tex_txt[];
extern unsigned char dog_2_mouth2_TA_tex_txt[];
extern unsigned char dog_2_mouth3_TA_tex_txt[];
extern unsigned char dog_2_mouth4_TA_tex_txt[];
extern unsigned char dog_2_mouth5_TA_tex_txt[];
extern unsigned char dog_2_mouth6_TA_tex_txt[];
extern unsigned char dog_2_tmem_txt[];
extern unsigned short dog_3_pal[];
extern unsigned char dog_3_eye1_TA_tex_txt[];
extern unsigned char dog_3_eye2_TA_tex_txt[];
extern unsigned char dog_3_eye3_TA_tex_txt[];
extern unsigned char dog_3_eye4_TA_tex_txt[];
extern unsigned char dog_3_eye5_TA_tex_txt[];
extern unsigned char dog_3_eye6_TA_tex_txt[];
extern unsigned char dog_3_eye7_TA_tex_txt[];
extern unsigned char dog_3_eye8_TA_tex_txt[];
extern unsigned char dog_3_mouth1_TA_tex_txt[];
extern unsigned char dog_3_mouth2_TA_tex_txt[];
extern unsigned char dog_3_mouth3_TA_tex_txt[];
extern unsigned char dog_3_mouth4_TA_tex_txt[];
extern unsigned char dog_3_mouth5_TA_tex_txt[];
extern unsigned char dog_3_mouth6_TA_tex_txt[];
extern unsigned char dog_3_tmem_txt[];
extern unsigned short dog_4_pal[];
extern unsigned char dog_4_eye1_TA_tex_txt[];
extern unsigned char dog_4_eye2_TA_tex_txt[];
extern unsigned char dog_4_eye3_TA_tex_txt[];
extern unsigned char dog_4_eye4_TA_tex_txt[];
extern unsigned char dog_4_eye5_TA_tex_txt[];
extern unsigned char dog_4_eye6_TA_tex_txt[];
extern unsigned char dog_4_eye7_TA_tex_txt[];
extern unsigned char dog_4_eye8_TA_tex_txt[];
extern unsigned char dog_4_mouth1_TA_tex_txt[];
extern unsigned char dog_4_mouth2_TA_tex_txt[];
extern unsigned char dog_4_mouth3_TA_tex_txt[];
extern unsigned char dog_4_mouth4_TA_tex_txt[];
extern unsigned char dog_4_mouth5_TA_tex_txt[];
extern unsigned char dog_4_mouth6_TA_tex_txt[];
extern unsigned char dog_4_tmem_txt[];
extern unsigned short dog_5_pal[];
extern unsigned char dog_5_eye1_TA_tex_txt[];
extern unsigned char dog_5_eye2_TA_tex_txt[];
extern unsigned char dog_5_eye3_TA_tex_txt[];
extern unsigned char dog_5_eye4_TA_tex_txt[];
extern unsigned char dog_5_eye5_TA_tex_txt[];
extern unsigned char dog_5_eye6_TA_tex_txt[];
extern unsigned char dog_5_eye7_TA_tex_txt[];
extern unsigned char dog_5_eye8_TA_tex_txt[];
extern unsigned char dog_5_mouth1_TA_tex_txt[];
extern unsigned char dog_5_mouth2_TA_tex_txt[];
extern unsigned char dog_5_mouth3_TA_tex_txt[];
extern unsigned char dog_5_mouth4_TA_tex_txt[];
extern unsigned char dog_5_mouth5_TA_tex_txt[];
extern unsigned char dog_5_mouth6_TA_tex_txt[];
extern unsigned char dog_5_tmem_txt[];
extern unsigned short dog_6_pal[];
extern unsigned char dog_6_eye1_TA_tex_txt[];
extern unsigned char dog_6_eye2_TA_tex_txt[];
extern unsigned char dog_6_eye3_TA_tex_txt[];
extern unsigned char dog_6_eye4_TA_tex_txt[];
extern unsigned char dog_6_eye5_TA_tex_txt[];
extern unsigned char dog_6_eye6_TA_tex_txt[];
extern unsigned char dog_6_eye7_TA_tex_txt[];
extern unsigned char dog_6_eye8_TA_tex_txt[];
extern unsigned char dog_6_mouth1_TA_tex_txt[];
extern unsigned char dog_6_mouth2_TA_tex_txt[];
extern unsigned char dog_6_mouth3_TA_tex_txt[];
extern unsigned char dog_6_mouth4_TA_tex_txt[];
extern unsigned char dog_6_mouth5_TA_tex_txt[];
extern unsigned char dog_6_mouth6_TA_tex_txt[];
extern unsigned char dog_6_tmem_txt[];
extern unsigned short dog_8_pal[];
extern unsigned char dog_8_eye1_TA_tex_txt[];
extern unsigned char dog_8_eye2_TA_tex_txt[];
extern unsigned char dog_8_eye3_TA_tex_txt[];
extern unsigned char dog_8_eye4_TA_tex_txt[];
extern unsigned char dog_8_eye5_TA_tex_txt[];
extern unsigned char dog_8_eye6_TA_tex_txt[];
extern unsigned char dog_8_eye7_TA_tex_txt[];
extern unsigned char dog_8_eye8_TA_tex_txt[];
extern unsigned char dog_8_mouth1_TA_tex_txt[];
extern unsigned char dog_8_mouth2_TA_tex_txt[];
extern unsigned char dog_8_mouth3_TA_tex_txt[];
extern unsigned char dog_8_mouth4_TA_tex_txt[];
extern unsigned char dog_8_mouth5_TA_tex_txt[];
extern unsigned char dog_8_mouth6_TA_tex_txt[];
extern unsigned char dog_8_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_duk_1;
extern unsigned short duk_1_pal[];
extern unsigned char duk_1_eye1_TA_tex_txt[];
extern unsigned char duk_1_eye2_TA_tex_txt[];
extern unsigned char duk_1_eye3_TA_tex_txt[];
extern unsigned char duk_1_eye4_TA_tex_txt[];
extern unsigned char duk_1_eye5_TA_tex_txt[];
extern unsigned char duk_1_eye6_TA_tex_txt[];
extern unsigned char duk_1_eye7_TA_tex_txt[];
extern unsigned char duk_1_eye8_TA_tex_txt[];
extern unsigned char duk_1_mouth1_TA_tex_txt[];
extern unsigned char duk_1_mouth2_TA_tex_txt[];
extern unsigned char duk_1_mouth3_TA_tex_txt[];
extern unsigned char duk_1_mouth4_TA_tex_txt[];
extern unsigned char duk_1_mouth5_TA_tex_txt[];
extern unsigned char duk_1_mouth6_TA_tex_txt[];
extern unsigned char duk_1_tmem_txt[];
extern unsigned short duk_2_pal[];
extern unsigned char duk_2_eye1_TA_tex_txt[];
extern unsigned char duk_2_eye2_TA_tex_txt[];
extern unsigned char duk_2_eye3_TA_tex_txt[];
extern unsigned char duk_2_eye4_TA_tex_txt[];
extern unsigned char duk_2_eye5_TA_tex_txt[];
extern unsigned char duk_2_eye6_TA_tex_txt[];
extern unsigned char duk_2_eye7_TA_tex_txt[];
extern unsigned char duk_2_eye8_TA_tex_txt[];
extern unsigned char duk_2_mouth1_TA_tex_txt[];
extern unsigned char duk_2_mouth2_TA_tex_txt[];
extern unsigned char duk_2_mouth3_TA_tex_txt[];
extern unsigned char duk_2_mouth4_TA_tex_txt[];
extern unsigned char duk_2_mouth5_TA_tex_txt[];
extern unsigned char duk_2_mouth6_TA_tex_txt[];
extern unsigned char duk_2_tmem_txt[];
extern unsigned short duk_3_pal[];
extern unsigned char duk_3_eye1_TA_tex_txt[];
extern unsigned char duk_3_eye2_TA_tex_txt[];
extern unsigned char duk_3_eye3_TA_tex_txt[];
extern unsigned char duk_3_eye4_TA_tex_txt[];
extern unsigned char duk_3_eye5_TA_tex_txt[];
extern unsigned char duk_3_eye6_TA_tex_txt[];
extern unsigned char duk_3_eye7_TA_tex_txt[];
extern unsigned char duk_3_eye8_TA_tex_txt[];
extern unsigned char duk_3_mouth1_TA_tex_txt[];
extern unsigned char duk_3_mouth2_TA_tex_txt[];
extern unsigned char duk_3_mouth3_TA_tex_txt[];
extern unsigned char duk_3_mouth4_TA_tex_txt[];
extern unsigned char duk_3_mouth5_TA_tex_txt[];
extern unsigned char duk_3_mouth6_TA_tex_txt[];
extern unsigned char duk_3_tmem_txt[];
extern unsigned short duk_4_pal[];
extern unsigned char duk_4_eye1_TA_tex_txt[];
extern unsigned char duk_4_eye2_TA_tex_txt[];
extern unsigned char duk_4_eye3_TA_tex_txt[];
extern unsigned char duk_4_eye4_TA_tex_txt[];
extern unsigned char duk_4_eye5_TA_tex_txt[];
extern unsigned char duk_4_eye6_TA_tex_txt[];
extern unsigned char duk_4_eye7_TA_tex_txt[];
extern unsigned char duk_4_eye8_TA_tex_txt[];
extern unsigned char duk_4_mouth1_TA_tex_txt[];
extern unsigned char duk_4_mouth2_TA_tex_txt[];
extern unsigned char duk_4_mouth3_TA_tex_txt[];
extern unsigned char duk_4_mouth4_TA_tex_txt[];
extern unsigned char duk_4_mouth5_TA_tex_txt[];
extern unsigned char duk_4_mouth6_TA_tex_txt[];
extern unsigned char duk_4_tmem_txt[];
extern unsigned short duk_5_pal[];
extern unsigned char duk_5_eye1_TA_tex_txt[];
extern unsigned char duk_5_eye2_TA_tex_txt[];
extern unsigned char duk_5_eye3_TA_tex_txt[];
extern unsigned char duk_5_eye4_TA_tex_txt[];
extern unsigned char duk_5_eye5_TA_tex_txt[];
extern unsigned char duk_5_eye6_TA_tex_txt[];
extern unsigned char duk_5_eye7_TA_tex_txt[];
extern unsigned char duk_5_eye8_TA_tex_txt[];
extern unsigned char duk_5_mouth1_TA_tex_txt[];
extern unsigned char duk_5_mouth2_TA_tex_txt[];
extern unsigned char duk_5_mouth3_TA_tex_txt[];
extern unsigned char duk_5_mouth4_TA_tex_txt[];
extern unsigned char duk_5_mouth5_TA_tex_txt[];
extern unsigned char duk_5_mouth6_TA_tex_txt[];
extern unsigned char duk_5_tmem_txt[];
extern unsigned short duk_6_pal[];
extern unsigned char duk_6_eye1_TA_tex_txt[];
extern unsigned char duk_6_eye2_TA_tex_txt[];
extern unsigned char duk_6_eye3_TA_tex_txt[];
extern unsigned char duk_6_eye4_TA_tex_txt[];
extern unsigned char duk_6_eye5_TA_tex_txt[];
extern unsigned char duk_6_eye6_TA_tex_txt[];
extern unsigned char duk_6_eye7_TA_tex_txt[];
extern unsigned char duk_6_eye8_TA_tex_txt[];
extern unsigned char duk_6_mouth1_TA_tex_txt[];
extern unsigned char duk_6_mouth2_TA_tex_txt[];
extern unsigned char duk_6_mouth3_TA_tex_txt[];
extern unsigned char duk_6_mouth4_TA_tex_txt[];
extern unsigned char duk_6_mouth5_TA_tex_txt[];
extern unsigned char duk_6_mouth6_TA_tex_txt[];
extern unsigned char duk_6_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_elp_1;
extern unsigned short elp_1_pal[];
extern unsigned char elp_1_eye1_TA_tex_txt[];
extern unsigned char elp_1_eye2_TA_tex_txt[];
extern unsigned char elp_1_eye3_TA_tex_txt[];
extern unsigned char elp_1_eye4_TA_tex_txt[];
extern unsigned char elp_1_eye5_TA_tex_txt[];
extern unsigned char elp_1_eye6_TA_tex_txt[];
extern unsigned char elp_1_eye7_TA_tex_txt[];
extern unsigned char elp_1_eye8_TA_tex_txt[];
extern unsigned char elp_1_mouth1_TA_tex_txt[];
extern unsigned char elp_1_mouth2_TA_tex_txt[];
extern unsigned char elp_1_mouth3_TA_tex_txt[];
extern unsigned char elp_1_mouth4_TA_tex_txt[];
extern unsigned char elp_1_mouth5_TA_tex_txt[];
extern unsigned char elp_1_mouth6_TA_tex_txt[];
extern unsigned char elp_1_tmem_txt[];
extern unsigned short elp_2_pal[];
extern unsigned char elp_2_eye1_TA_tex_txt[];
extern unsigned char elp_2_eye2_TA_tex_txt[];
extern unsigned char elp_2_eye3_TA_tex_txt[];
extern unsigned char elp_2_eye4_TA_tex_txt[];
extern unsigned char elp_2_eye5_TA_tex_txt[];
extern unsigned char elp_2_eye6_TA_tex_txt[];
extern unsigned char elp_2_eye7_TA_tex_txt[];
extern unsigned char elp_2_eye8_TA_tex_txt[];
extern unsigned char elp_2_mouth1_TA_tex_txt[];
extern unsigned char elp_2_mouth2_TA_tex_txt[];
extern unsigned char elp_2_mouth3_TA_tex_txt[];
extern unsigned char elp_2_mouth4_TA_tex_txt[];
extern unsigned char elp_2_mouth5_TA_tex_txt[];
extern unsigned char elp_2_mouth6_TA_tex_txt[];
extern unsigned char elp_2_tmem_txt[];
extern unsigned short elp_3_pal[];
extern unsigned char elp_3_eye1_TA_tex_txt[];
extern unsigned char elp_3_eye2_TA_tex_txt[];
extern unsigned char elp_3_eye3_TA_tex_txt[];
extern unsigned char elp_3_eye4_TA_tex_txt[];
extern unsigned char elp_3_eye5_TA_tex_txt[];
extern unsigned char elp_3_eye6_TA_tex_txt[];
extern unsigned char elp_3_eye7_TA_tex_txt[];
extern unsigned char elp_3_eye8_TA_tex_txt[];
extern unsigned char elp_3_mouth1_TA_tex_txt[];
extern unsigned char elp_3_mouth2_TA_tex_txt[];
extern unsigned char elp_3_mouth3_TA_tex_txt[];
extern unsigned char elp_3_mouth4_TA_tex_txt[];
extern unsigned char elp_3_mouth5_TA_tex_txt[];
extern unsigned char elp_3_mouth6_TA_tex_txt[];
extern unsigned char elp_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_flg_1;
extern unsigned short flg_1_pal[];
extern unsigned char flg_1_eye1_TA_tex_txt[];
extern unsigned char flg_1_eye2_TA_tex_txt[];
extern unsigned char flg_1_eye3_TA_tex_txt[];
extern unsigned char flg_1_eye4_TA_tex_txt[];
extern unsigned char flg_1_eye5_TA_tex_txt[];
extern unsigned char flg_1_eye6_TA_tex_txt[];
extern unsigned char flg_1_eye7_TA_tex_txt[];
extern unsigned char flg_1_eye8_TA_tex_txt[];
extern unsigned char flg_1_mouth1_TA_tex_txt[];
extern unsigned char flg_1_mouth2_TA_tex_txt[];
extern unsigned char flg_1_mouth3_TA_tex_txt[];
extern unsigned char flg_1_mouth4_TA_tex_txt[];
extern unsigned char flg_1_mouth5_TA_tex_txt[];
extern unsigned char flg_1_mouth6_TA_tex_txt[];
extern unsigned char flg_1_tmem_txt[];
extern unsigned short flg_2_pal[];
extern unsigned char flg_2_eye1_TA_tex_txt[];
extern unsigned char flg_2_eye2_TA_tex_txt[];
extern unsigned char flg_2_eye3_TA_tex_txt[];
extern unsigned char flg_2_eye4_TA_tex_txt[];
extern unsigned char flg_2_eye5_TA_tex_txt[];
extern unsigned char flg_2_eye6_TA_tex_txt[];
extern unsigned char flg_2_eye7_TA_tex_txt[];
extern unsigned char flg_2_eye8_TA_tex_txt[];
extern unsigned char flg_2_mouth1_TA_tex_txt[];
extern unsigned char flg_2_mouth2_TA_tex_txt[];
extern unsigned char flg_2_mouth3_TA_tex_txt[];
extern unsigned char flg_2_mouth4_TA_tex_txt[];
extern unsigned char flg_2_mouth5_TA_tex_txt[];
extern unsigned char flg_2_mouth6_TA_tex_txt[];
extern unsigned char flg_2_tmem_txt[];
extern unsigned short flg_3_pal[];
extern unsigned char flg_3_eye1_TA_tex_txt[];
extern unsigned char flg_3_eye2_TA_tex_txt[];
extern unsigned char flg_3_eye3_TA_tex_txt[];
extern unsigned char flg_3_eye4_TA_tex_txt[];
extern unsigned char flg_3_eye5_TA_tex_txt[];
extern unsigned char flg_3_eye6_TA_tex_txt[];
extern unsigned char flg_3_eye7_TA_tex_txt[];
extern unsigned char flg_3_eye8_TA_tex_txt[];
extern unsigned char flg_3_mouth1_TA_tex_txt[];
extern unsigned char flg_3_mouth2_TA_tex_txt[];
extern unsigned char flg_3_mouth3_TA_tex_txt[];
extern unsigned char flg_3_mouth4_TA_tex_txt[];
extern unsigned char flg_3_mouth5_TA_tex_txt[];
extern unsigned char flg_3_mouth6_TA_tex_txt[];
extern unsigned char flg_3_tmem_txt[];
extern unsigned short flg_4_pal[];
extern unsigned char flg_4_eye1_TA_tex_txt[];
extern unsigned char flg_4_eye2_TA_tex_txt[];
extern unsigned char flg_4_eye3_TA_tex_txt[];
extern unsigned char flg_4_eye4_TA_tex_txt[];
extern unsigned char flg_4_eye5_TA_tex_txt[];
extern unsigned char flg_4_eye6_TA_tex_txt[];
extern unsigned char flg_4_eye7_TA_tex_txt[];
extern unsigned char flg_4_eye8_TA_tex_txt[];
extern unsigned char flg_4_mouth1_TA_tex_txt[];
extern unsigned char flg_4_mouth2_TA_tex_txt[];
extern unsigned char flg_4_mouth3_TA_tex_txt[];
extern unsigned char flg_4_mouth4_TA_tex_txt[];
extern unsigned char flg_4_mouth5_TA_tex_txt[];
extern unsigned char flg_4_mouth6_TA_tex_txt[];
extern unsigned char flg_4_tmem_txt[];
extern unsigned short flg_5_pal[];
extern unsigned char flg_5_eye1_TA_tex_txt[];
extern unsigned char flg_5_eye2_TA_tex_txt[];
extern unsigned char flg_5_eye3_TA_tex_txt[];
extern unsigned char flg_5_eye4_TA_tex_txt[];
extern unsigned char flg_5_eye5_TA_tex_txt[];
extern unsigned char flg_5_eye6_TA_tex_txt[];
extern unsigned char flg_5_eye7_TA_tex_txt[];
extern unsigned char flg_5_eye8_TA_tex_txt[];
extern unsigned char flg_5_mouth1_TA_tex_txt[];
extern unsigned char flg_5_mouth2_TA_tex_txt[];
extern unsigned char flg_5_mouth3_TA_tex_txt[];
extern unsigned char flg_5_mouth4_TA_tex_txt[];
extern unsigned char flg_5_mouth5_TA_tex_txt[];
extern unsigned char flg_5_mouth6_TA_tex_txt[];
extern unsigned char flg_5_tmem_txt[];
extern unsigned short flg_6_pal[];
extern unsigned char flg_6_eye1_TA_tex_txt[];
extern unsigned char flg_6_eye2_TA_tex_txt[];
extern unsigned char flg_6_eye3_TA_tex_txt[];
extern unsigned char flg_6_eye4_TA_tex_txt[];
extern unsigned char flg_6_eye5_TA_tex_txt[];
extern unsigned char flg_6_eye6_TA_tex_txt[];
extern unsigned char flg_6_eye7_TA_tex_txt[];
extern unsigned char flg_6_eye8_TA_tex_txt[];
extern unsigned char flg_6_mouth1_TA_tex_txt[];
extern unsigned char flg_6_mouth2_TA_tex_txt[];
extern unsigned char flg_6_mouth3_TA_tex_txt[];
extern unsigned char flg_6_mouth4_TA_tex_txt[];
extern unsigned char flg_6_mouth5_TA_tex_txt[];
extern unsigned char flg_6_mouth6_TA_tex_txt[];
extern unsigned char flg_6_tmem_txt[];
extern unsigned short flg_7_pal[];
extern unsigned char flg_7_eye1_TA_tex_txt[];
extern unsigned char flg_7_eye2_TA_tex_txt[];
extern unsigned char flg_7_eye3_TA_tex_txt[];
extern unsigned char flg_7_eye4_TA_tex_txt[];
extern unsigned char flg_7_eye5_TA_tex_txt[];
extern unsigned char flg_7_eye6_TA_tex_txt[];
extern unsigned char flg_7_eye7_TA_tex_txt[];
extern unsigned char flg_7_eye8_TA_tex_txt[];
extern unsigned char flg_7_mouth1_TA_tex_txt[];
extern unsigned char flg_7_mouth2_TA_tex_txt[];
extern unsigned char flg_7_mouth3_TA_tex_txt[];
extern unsigned char flg_7_mouth4_TA_tex_txt[];
extern unsigned char flg_7_mouth5_TA_tex_txt[];
extern unsigned char flg_7_mouth6_TA_tex_txt[];
extern unsigned char flg_7_tmem_txt[];
extern unsigned short flg_8_pal[];
extern unsigned char flg_8_eye1_TA_tex_txt[];
extern unsigned char flg_8_eye2_TA_tex_txt[];
extern unsigned char flg_8_eye3_TA_tex_txt[];
extern unsigned char flg_8_eye4_TA_tex_txt[];
extern unsigned char flg_8_eye5_TA_tex_txt[];
extern unsigned char flg_8_eye6_TA_tex_txt[];
extern unsigned char flg_8_eye7_TA_tex_txt[];
extern unsigned char flg_8_eye8_TA_tex_txt[];
extern unsigned char flg_8_mouth1_TA_tex_txt[];
extern unsigned char flg_8_mouth2_TA_tex_txt[];
extern unsigned char flg_8_mouth3_TA_tex_txt[];
extern unsigned char flg_8_mouth4_TA_tex_txt[];
extern unsigned char flg_8_mouth5_TA_tex_txt[];
extern unsigned char flg_8_mouth6_TA_tex_txt[];
extern unsigned char flg_8_tmem_txt[];
extern unsigned short flg_9_pal[];
extern unsigned char flg_9_eye1_TA_tex_txt[];
extern unsigned char flg_9_eye2_TA_tex_txt[];
extern unsigned char flg_9_eye3_TA_tex_txt[];
extern unsigned char flg_9_eye4_TA_tex_txt[];
extern unsigned char flg_9_eye5_TA_tex_txt[];
extern unsigned char flg_9_eye6_TA_tex_txt[];
extern unsigned char flg_9_eye7_TA_tex_txt[];
extern unsigned char flg_9_eye8_TA_tex_txt[];
extern unsigned char flg_9_mouth1_TA_tex_txt[];
extern unsigned char flg_9_mouth2_TA_tex_txt[];
extern unsigned char flg_9_mouth3_TA_tex_txt[];
extern unsigned char flg_9_mouth4_TA_tex_txt[];
extern unsigned char flg_9_mouth5_TA_tex_txt[];
extern unsigned char flg_9_mouth6_TA_tex_txt[];
extern unsigned char flg_9_tmem_txt[];
extern unsigned short flg_10_pal[];
extern unsigned char flg_10_eye1_TA_tex_txt[];
extern unsigned char flg_10_eye2_TA_tex_txt[];
extern unsigned char flg_10_eye3_TA_tex_txt[];
extern unsigned char flg_10_eye4_TA_tex_txt[];
extern unsigned char flg_10_eye5_TA_tex_txt[];
extern unsigned char flg_10_eye6_TA_tex_txt[];
extern unsigned char flg_10_eye7_TA_tex_txt[];
extern unsigned char flg_10_eye8_TA_tex_txt[];
extern unsigned char flg_10_mouth1_TA_tex_txt[];
extern unsigned char flg_10_mouth2_TA_tex_txt[];
extern unsigned char flg_10_mouth3_TA_tex_txt[];
extern unsigned char flg_10_mouth4_TA_tex_txt[];
extern unsigned char flg_10_mouth5_TA_tex_txt[];
extern unsigned char flg_10_mouth6_TA_tex_txt[];
extern unsigned char flg_10_tmem_txt[];
extern unsigned short flg_11_pal[];
extern unsigned char flg_11_eye1_TA_tex_txt[];
extern unsigned char flg_11_eye2_TA_tex_txt[];
extern unsigned char flg_11_eye3_TA_tex_txt[];
extern unsigned char flg_11_eye4_TA_tex_txt[];
extern unsigned char flg_11_eye5_TA_tex_txt[];
extern unsigned char flg_11_eye6_TA_tex_txt[];
extern unsigned char flg_11_eye7_TA_tex_txt[];
extern unsigned char flg_11_eye8_TA_tex_txt[];
extern unsigned char flg_11_mouth1_TA_tex_txt[];
extern unsigned char flg_11_mouth2_TA_tex_txt[];
extern unsigned char flg_11_mouth3_TA_tex_txt[];
extern unsigned char flg_11_mouth4_TA_tex_txt[];
extern unsigned char flg_11_mouth5_TA_tex_txt[];
extern unsigned char flg_11_mouth6_TA_tex_txt[];
extern unsigned char flg_11_tmem_txt[];
extern unsigned short flg_12_pal[];
extern unsigned char flg_12_eye1_TA_tex_txt[];
extern unsigned char flg_12_eye2_TA_tex_txt[];
extern unsigned char flg_12_eye3_TA_tex_txt[];
extern unsigned char flg_12_eye4_TA_tex_txt[];
extern unsigned char flg_12_eye5_TA_tex_txt[];
extern unsigned char flg_12_eye6_TA_tex_txt[];
extern unsigned char flg_12_eye7_TA_tex_txt[];
extern unsigned char flg_12_eye8_TA_tex_txt[];
extern unsigned char flg_12_mouth1_TA_tex_txt[];
extern unsigned char flg_12_mouth2_TA_tex_txt[];
extern unsigned char flg_12_mouth3_TA_tex_txt[];
extern unsigned char flg_12_mouth4_TA_tex_txt[];
extern unsigned char flg_12_mouth5_TA_tex_txt[];
extern unsigned char flg_12_mouth6_TA_tex_txt[];
extern unsigned char flg_12_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_goa_1;
extern unsigned short goa_1_pal[];
extern unsigned char goa_1_eye1_TA_tex_txt[];
extern unsigned char goa_1_eye2_TA_tex_txt[];
extern unsigned char goa_1_eye3_TA_tex_txt[];
extern unsigned char goa_1_eye4_TA_tex_txt[];
extern unsigned char goa_1_eye5_TA_tex_txt[];
extern unsigned char goa_1_eye6_TA_tex_txt[];
extern unsigned char goa_1_eye7_TA_tex_txt[];
extern unsigned char goa_1_eye8_TA_tex_txt[];
extern unsigned char goa_1_mouth1_TA_tex_txt[];
extern unsigned char goa_1_mouth2_TA_tex_txt[];
extern unsigned char goa_1_mouth3_TA_tex_txt[];
extern unsigned char goa_1_mouth4_TA_tex_txt[];
extern unsigned char goa_1_mouth5_TA_tex_txt[];
extern unsigned char goa_1_mouth6_TA_tex_txt[];
extern unsigned char goa_1_tmem_txt[];
extern unsigned short goa_2_pal[];
extern unsigned char goa_2_eye1_TA_tex_txt[];
extern unsigned char goa_2_eye2_TA_tex_txt[];
extern unsigned char goa_2_eye3_TA_tex_txt[];
extern unsigned char goa_2_eye4_TA_tex_txt[];
extern unsigned char goa_2_eye5_TA_tex_txt[];
extern unsigned char goa_2_eye6_TA_tex_txt[];
extern unsigned char goa_2_eye7_TA_tex_txt[];
extern unsigned char goa_2_eye8_TA_tex_txt[];
extern unsigned char goa_2_mouth1_TA_tex_txt[];
extern unsigned char goa_2_mouth2_TA_tex_txt[];
extern unsigned char goa_2_mouth3_TA_tex_txt[];
extern unsigned char goa_2_mouth4_TA_tex_txt[];
extern unsigned char goa_2_mouth5_TA_tex_txt[];
extern unsigned char goa_2_mouth6_TA_tex_txt[];
extern unsigned char goa_2_tmem_txt[];
extern unsigned short goa_3_pal[];
extern unsigned char goa_3_eye1_TA_tex_txt[];
extern unsigned char goa_3_eye2_TA_tex_txt[];
extern unsigned char goa_3_eye3_TA_tex_txt[];
extern unsigned char goa_3_eye4_TA_tex_txt[];
extern unsigned char goa_3_eye5_TA_tex_txt[];
extern unsigned char goa_3_eye6_TA_tex_txt[];
extern unsigned char goa_3_eye7_TA_tex_txt[];
extern unsigned char goa_3_eye8_TA_tex_txt[];
extern unsigned char goa_3_mouth1_TA_tex_txt[];
extern unsigned char goa_3_mouth2_TA_tex_txt[];
extern unsigned char goa_3_mouth3_TA_tex_txt[];
extern unsigned char goa_3_mouth4_TA_tex_txt[];
extern unsigned char goa_3_mouth5_TA_tex_txt[];
extern unsigned char goa_3_mouth6_TA_tex_txt[];
extern unsigned char goa_3_tmem_txt[];
extern unsigned short goa_4_pal[];
extern unsigned char goa_4_eye1_TA_tex_txt[];
extern unsigned char goa_4_eye2_TA_tex_txt[];
extern unsigned char goa_4_eye3_TA_tex_txt[];
extern unsigned char goa_4_eye4_TA_tex_txt[];
extern unsigned char goa_4_eye5_TA_tex_txt[];
extern unsigned char goa_4_eye6_TA_tex_txt[];
extern unsigned char goa_4_eye7_TA_tex_txt[];
extern unsigned char goa_4_eye8_TA_tex_txt[];
extern unsigned char goa_4_mouth1_TA_tex_txt[];
extern unsigned char goa_4_mouth2_TA_tex_txt[];
extern unsigned char goa_4_mouth3_TA_tex_txt[];
extern unsigned char goa_4_mouth4_TA_tex_txt[];
extern unsigned char goa_4_mouth5_TA_tex_txt[];
extern unsigned char goa_4_mouth6_TA_tex_txt[];
extern unsigned char goa_4_tmem_txt[];
extern unsigned short goa_5_pal[];
extern unsigned char goa_5_eye1_TA_tex_txt[];
extern unsigned char goa_5_eye2_TA_tex_txt[];
extern unsigned char goa_5_eye3_TA_tex_txt[];
extern unsigned char goa_5_eye4_TA_tex_txt[];
extern unsigned char goa_5_eye5_TA_tex_txt[];
extern unsigned char goa_5_eye6_TA_tex_txt[];
extern unsigned char goa_5_eye7_TA_tex_txt[];
extern unsigned char goa_5_eye8_TA_tex_txt[];
extern unsigned char goa_5_mouth1_TA_tex_txt[];
extern unsigned char goa_5_mouth2_TA_tex_txt[];
extern unsigned char goa_5_mouth3_TA_tex_txt[];
extern unsigned char goa_5_mouth4_TA_tex_txt[];
extern unsigned char goa_5_mouth5_TA_tex_txt[];
extern unsigned char goa_5_mouth6_TA_tex_txt[];
extern unsigned char goa_5_tmem_txt[];
extern unsigned short goa_6_pal[];
extern unsigned char goa_6_eye1_TA_tex_txt[];
extern unsigned char goa_6_eye2_TA_tex_txt[];
extern unsigned char goa_6_eye3_TA_tex_txt[];
extern unsigned char goa_6_eye4_TA_tex_txt[];
extern unsigned char goa_6_eye5_TA_tex_txt[];
extern unsigned char goa_6_eye6_TA_tex_txt[];
extern unsigned char goa_6_eye7_TA_tex_txt[];
extern unsigned char goa_6_eye8_TA_tex_txt[];
extern unsigned char goa_6_mouth1_TA_tex_txt[];
extern unsigned char goa_6_mouth2_TA_tex_txt[];
extern unsigned char goa_6_mouth3_TA_tex_txt[];
extern unsigned char goa_6_mouth4_TA_tex_txt[];
extern unsigned char goa_6_mouth5_TA_tex_txt[];
extern unsigned char goa_6_mouth6_TA_tex_txt[];
extern unsigned char goa_6_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_gor_1;
extern unsigned short gor_1_pal[];
extern unsigned char gor_1_eye1_TA_tex_txt[];
extern unsigned char gor_1_eye2_TA_tex_txt[];
extern unsigned char gor_1_eye3_TA_tex_txt[];
extern unsigned char gor_1_eye4_TA_tex_txt[];
extern unsigned char gor_1_eye5_TA_tex_txt[];
extern unsigned char gor_1_eye6_TA_tex_txt[];
extern unsigned char gor_1_eye7_TA_tex_txt[];
extern unsigned char gor_1_eye8_TA_tex_txt[];
extern unsigned char gor_1_mouth1_TA_tex_txt[];
extern unsigned char gor_1_mouth2_TA_tex_txt[];
extern unsigned char gor_1_mouth3_TA_tex_txt[];
extern unsigned char gor_1_mouth4_TA_tex_txt[];
extern unsigned char gor_1_mouth5_TA_tex_txt[];
extern unsigned char gor_1_mouth6_TA_tex_txt[];
extern unsigned char gor_1_tmem_txt[];
extern unsigned short gor_2_pal[];
extern unsigned char gor_2_eye1_TA_tex_txt[];
extern unsigned char gor_2_eye2_TA_tex_txt[];
extern unsigned char gor_2_eye3_TA_tex_txt[];
extern unsigned char gor_2_eye4_TA_tex_txt[];
extern unsigned char gor_2_eye5_TA_tex_txt[];
extern unsigned char gor_2_eye6_TA_tex_txt[];
extern unsigned char gor_2_eye7_TA_tex_txt[];
extern unsigned char gor_2_eye8_TA_tex_txt[];
extern unsigned char gor_2_mouth1_TA_tex_txt[];
extern unsigned char gor_2_mouth2_TA_tex_txt[];
extern unsigned char gor_2_mouth3_TA_tex_txt[];
extern unsigned char gor_2_mouth4_TA_tex_txt[];
extern unsigned char gor_2_mouth5_TA_tex_txt[];
extern unsigned char gor_2_mouth6_TA_tex_txt[];
extern unsigned char gor_2_tmem_txt[];
extern unsigned short gor_3_pal[];
extern unsigned char gor_3_eye1_TA_tex_txt[];
extern unsigned char gor_3_eye2_TA_tex_txt[];
extern unsigned char gor_3_eye3_TA_tex_txt[];
extern unsigned char gor_3_eye4_TA_tex_txt[];
extern unsigned char gor_3_eye5_TA_tex_txt[];
extern unsigned char gor_3_eye6_TA_tex_txt[];
extern unsigned char gor_3_eye7_TA_tex_txt[];
extern unsigned char gor_3_eye8_TA_tex_txt[];
extern unsigned char gor_3_mouth1_TA_tex_txt[];
extern unsigned char gor_3_mouth2_TA_tex_txt[];
extern unsigned char gor_3_mouth3_TA_tex_txt[];
extern unsigned char gor_3_mouth4_TA_tex_txt[];
extern unsigned char gor_3_mouth5_TA_tex_txt[];
extern unsigned char gor_3_mouth6_TA_tex_txt[];
extern unsigned char gor_3_tmem_txt[];
extern unsigned short gor_4_pal[];
extern unsigned char gor_4_eye1_TA_tex_txt[];
extern unsigned char gor_4_eye2_TA_tex_txt[];
extern unsigned char gor_4_eye3_TA_tex_txt[];
extern unsigned char gor_4_eye4_TA_tex_txt[];
extern unsigned char gor_4_eye5_TA_tex_txt[];
extern unsigned char gor_4_eye6_TA_tex_txt[];
extern unsigned char gor_4_eye7_TA_tex_txt[];
extern unsigned char gor_4_eye8_TA_tex_txt[];
extern unsigned char gor_4_mouth1_TA_tex_txt[];
extern unsigned char gor_4_mouth2_TA_tex_txt[];
extern unsigned char gor_4_mouth3_TA_tex_txt[];
extern unsigned char gor_4_mouth4_TA_tex_txt[];
extern unsigned char gor_4_mouth5_TA_tex_txt[];
extern unsigned char gor_4_mouth6_TA_tex_txt[];
extern unsigned char gor_4_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hip_1;
extern unsigned short hip_1_pal[];
extern unsigned char hip_1_eye1_TA_tex_txt[];
extern unsigned char hip_1_eye2_TA_tex_txt[];
extern unsigned char hip_1_eye3_TA_tex_txt[];
extern unsigned char hip_1_eye4_TA_tex_txt[];
extern unsigned char hip_1_eye5_TA_tex_txt[];
extern unsigned char hip_1_eye6_TA_tex_txt[];
extern unsigned char hip_1_eye7_TA_tex_txt[];
extern unsigned char hip_1_eye8_TA_tex_txt[];
extern unsigned char hip_1_tmem_txt[];
extern unsigned short hip_2_pal[];
extern unsigned char hip_2_eye1_TA_tex_txt[];
extern unsigned char hip_2_eye2_TA_tex_txt[];
extern unsigned char hip_2_eye3_TA_tex_txt[];
extern unsigned char hip_2_eye4_TA_tex_txt[];
extern unsigned char hip_2_eye5_TA_tex_txt[];
extern unsigned char hip_2_eye6_TA_tex_txt[];
extern unsigned char hip_2_eye7_TA_tex_txt[];
extern unsigned char hip_2_eye8_TA_tex_txt[];
extern unsigned char hip_2_tmem_txt[];
extern unsigned short hip_3_pal[];
extern unsigned char hip_3_eye1_TA_tex_txt[];
extern unsigned char hip_3_eye2_TA_tex_txt[];
extern unsigned char hip_3_eye3_TA_tex_txt[];
extern unsigned char hip_3_eye4_TA_tex_txt[];
extern unsigned char hip_3_eye5_TA_tex_txt[];
extern unsigned char hip_3_eye6_TA_tex_txt[];
extern unsigned char hip_3_eye7_TA_tex_txt[];
extern unsigned char hip_3_eye8_TA_tex_txt[];
extern unsigned char hip_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hrs_1;
extern unsigned short hrs_1_pal[];
extern unsigned char hrs_1_eye1_TA_tex_txt[];
extern unsigned char hrs_1_eye2_TA_tex_txt[];
extern unsigned char hrs_1_eye3_TA_tex_txt[];
extern unsigned char hrs_1_eye4_TA_tex_txt[];
extern unsigned char hrs_1_eye5_TA_tex_txt[];
extern unsigned char hrs_1_eye6_TA_tex_txt[];
extern unsigned char hrs_1_eye7_TA_tex_txt[];
extern unsigned char hrs_1_eye8_TA_tex_txt[];
extern unsigned char hrs_1_tmem_txt[];
extern unsigned short hrs_2_pal[];
extern unsigned char hrs_2_eye1_TA_tex_txt[];
extern unsigned char hrs_2_eye2_TA_tex_txt[];
extern unsigned char hrs_2_eye3_TA_tex_txt[];
extern unsigned char hrs_2_eye4_TA_tex_txt[];
extern unsigned char hrs_2_eye5_TA_tex_txt[];
extern unsigned char hrs_2_eye6_TA_tex_txt[];
extern unsigned char hrs_2_eye7_TA_tex_txt[];
extern unsigned char hrs_2_eye8_TA_tex_txt[];
extern unsigned char hrs_2_tmem_txt[];
extern unsigned short hrs_3_pal[];
extern unsigned char hrs_3_eye1_TA_tex_txt[];
extern unsigned char hrs_3_eye2_TA_tex_txt[];
extern unsigned char hrs_3_eye3_TA_tex_txt[];
extern unsigned char hrs_3_eye4_TA_tex_txt[];
extern unsigned char hrs_3_eye5_TA_tex_txt[];
extern unsigned char hrs_3_eye6_TA_tex_txt[];
extern unsigned char hrs_3_eye7_TA_tex_txt[];
extern unsigned char hrs_3_eye8_TA_tex_txt[];
extern unsigned char hrs_3_tmem_txt[];
extern unsigned short hrs_4_pal[];
extern unsigned char hrs_4_eye1_TA_tex_txt[];
extern unsigned char hrs_4_eye2_TA_tex_txt[];
extern unsigned char hrs_4_eye3_TA_tex_txt[];
extern unsigned char hrs_4_eye4_TA_tex_txt[];
extern unsigned char hrs_4_eye5_TA_tex_txt[];
extern unsigned char hrs_4_eye6_TA_tex_txt[];
extern unsigned char hrs_4_eye7_TA_tex_txt[];
extern unsigned char hrs_4_eye8_TA_tex_txt[];
extern unsigned char hrs_4_tmem_txt[];
extern unsigned short hrs_5_pal[];
extern unsigned char hrs_5_eye1_TA_tex_txt[];
extern unsigned char hrs_5_eye2_TA_tex_txt[];
extern unsigned char hrs_5_eye3_TA_tex_txt[];
extern unsigned char hrs_5_eye4_TA_tex_txt[];
extern unsigned char hrs_5_eye5_TA_tex_txt[];
extern unsigned char hrs_5_eye6_TA_tex_txt[];
extern unsigned char hrs_5_eye7_TA_tex_txt[];
extern unsigned char hrs_5_eye8_TA_tex_txt[];
extern unsigned char hrs_5_tmem_txt[];
extern unsigned short hrs_6_pal[];
extern unsigned char hrs_6_eye1_TA_tex_txt[];
extern unsigned char hrs_6_eye2_TA_tex_txt[];
extern unsigned char hrs_6_eye3_TA_tex_txt[];
extern unsigned char hrs_6_eye4_TA_tex_txt[];
extern unsigned char hrs_6_eye5_TA_tex_txt[];
extern unsigned char hrs_6_eye6_TA_tex_txt[];
extern unsigned char hrs_6_eye7_TA_tex_txt[];
extern unsigned char hrs_6_eye8_TA_tex_txt[];
extern unsigned char hrs_6_tmem_txt[];
extern unsigned short hrs_7_pal[];
extern unsigned char hrs_7_eye1_TA_tex_txt[];
extern unsigned char hrs_7_eye2_TA_tex_txt[];
extern unsigned char hrs_7_eye3_TA_tex_txt[];
extern unsigned char hrs_7_eye4_TA_tex_txt[];
extern unsigned char hrs_7_eye5_TA_tex_txt[];
extern unsigned char hrs_7_eye6_TA_tex_txt[];
extern unsigned char hrs_7_eye7_TA_tex_txt[];
extern unsigned char hrs_7_eye8_TA_tex_txt[];
extern unsigned char hrs_7_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_kgr_1;
extern unsigned short kgr_1_pal[];
extern unsigned char kgr_1_eye1_TA_tex_txt[];
extern unsigned char kgr_1_eye2_TA_tex_txt[];
extern unsigned char kgr_1_eye3_TA_tex_txt[];
extern unsigned char kgr_1_eye4_TA_tex_txt[];
extern unsigned char kgr_1_eye5_TA_tex_txt[];
extern unsigned char kgr_1_eye6_TA_tex_txt[];
extern unsigned char kgr_1_eye7_TA_tex_txt[];
extern unsigned char kgr_1_eye8_TA_tex_txt[];
extern unsigned char kgr_1_tmem_txt[];
extern unsigned short kgr_2_pal[];
extern unsigned char kgr_2_eye1_TA_tex_txt[];
extern unsigned char kgr_2_eye2_TA_tex_txt[];
extern unsigned char kgr_2_eye3_TA_tex_txt[];
extern unsigned char kgr_2_eye4_TA_tex_txt[];
extern unsigned char kgr_2_eye5_TA_tex_txt[];
extern unsigned char kgr_2_eye6_TA_tex_txt[];
extern unsigned char kgr_2_eye7_TA_tex_txt[];
extern unsigned char kgr_2_eye8_TA_tex_txt[];
extern unsigned char kgr_2_tmem_txt[];
extern unsigned short kgr_3_pal[];
extern unsigned char kgr_3_eye1_TA_tex_txt[];
extern unsigned char kgr_3_eye2_TA_tex_txt[];
extern unsigned char kgr_3_eye3_TA_tex_txt[];
extern unsigned char kgr_3_eye4_TA_tex_txt[];
extern unsigned char kgr_3_eye5_TA_tex_txt[];
extern unsigned char kgr_3_eye6_TA_tex_txt[];
extern unsigned char kgr_3_eye7_TA_tex_txt[];
extern unsigned char kgr_3_eye8_TA_tex_txt[];
extern unsigned char kgr_3_tmem_txt[];
extern unsigned short kgr_4_pal[];
extern unsigned char kgr_4_eye1_TA_tex_txt[];
extern unsigned char kgr_4_eye2_TA_tex_txt[];
extern unsigned char kgr_4_eye3_TA_tex_txt[];
extern unsigned char kgr_4_eye4_TA_tex_txt[];
extern unsigned char kgr_4_eye5_TA_tex_txt[];
extern unsigned char kgr_4_eye6_TA_tex_txt[];
extern unsigned char kgr_4_eye7_TA_tex_txt[];
extern unsigned char kgr_4_eye8_TA_tex_txt[];
extern unsigned char kgr_4_tmem_txt[];
extern unsigned short kgr_5_pal[];
extern unsigned char kgr_5_eye1_TA_tex_txt[];
extern unsigned char kgr_5_eye2_TA_tex_txt[];
extern unsigned char kgr_5_eye3_TA_tex_txt[];
extern unsigned char kgr_5_eye4_TA_tex_txt[];
extern unsigned char kgr_5_eye5_TA_tex_txt[];
extern unsigned char kgr_5_eye6_TA_tex_txt[];
extern unsigned char kgr_5_eye7_TA_tex_txt[];
extern unsigned char kgr_5_eye8_TA_tex_txt[];
extern unsigned char kgr_5_tmem_txt[];
extern unsigned short kgr_6_pal[];
extern unsigned char kgr_6_eye1_TA_tex_txt[];
extern unsigned char kgr_6_eye2_TA_tex_txt[];
extern unsigned char kgr_6_eye3_TA_tex_txt[];
extern unsigned char kgr_6_eye4_TA_tex_txt[];
extern unsigned char kgr_6_eye5_TA_tex_txt[];
extern unsigned char kgr_6_eye6_TA_tex_txt[];
extern unsigned char kgr_6_eye7_TA_tex_txt[];
extern unsigned char kgr_6_eye8_TA_tex_txt[];
extern unsigned char kgr_6_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_kal_1;
extern unsigned short kal_1_pal[];
extern unsigned char kal_1_eye1_TA_tex_txt[];
extern unsigned char kal_1_eye2_TA_tex_txt[];
extern unsigned char kal_1_eye3_TA_tex_txt[];
extern unsigned char kal_1_eye4_TA_tex_txt[];
extern unsigned char kal_1_eye5_TA_tex_txt[];
extern unsigned char kal_1_eye6_TA_tex_txt[];
extern unsigned char kal_1_eye7_TA_tex_txt[];
extern unsigned char kal_1_eye8_TA_tex_txt[];
extern unsigned char kal_1_mouth1_TA_tex_txt[];
extern unsigned char kal_1_mouth2_TA_tex_txt[];
extern unsigned char kal_1_mouth3_TA_tex_txt[];
extern unsigned char kal_1_mouth4_TA_tex_txt[];
extern unsigned char kal_1_mouth5_TA_tex_txt[];
extern unsigned char kal_1_mouth6_TA_tex_txt[];
extern unsigned char kal_1_tmem_txt[];
extern unsigned short kal_2_pal[];
extern unsigned char kal_2_eye1_TA_tex_txt[];
extern unsigned char kal_2_eye2_TA_tex_txt[];
extern unsigned char kal_2_eye3_TA_tex_txt[];
extern unsigned char kal_2_eye4_TA_tex_txt[];
extern unsigned char kal_2_eye5_TA_tex_txt[];
extern unsigned char kal_2_eye6_TA_tex_txt[];
extern unsigned char kal_2_eye7_TA_tex_txt[];
extern unsigned char kal_2_eye8_TA_tex_txt[];
extern unsigned char kal_2_mouth1_TA_tex_txt[];
extern unsigned char kal_2_mouth2_TA_tex_txt[];
extern unsigned char kal_2_mouth3_TA_tex_txt[];
extern unsigned char kal_2_mouth4_TA_tex_txt[];
extern unsigned char kal_2_mouth5_TA_tex_txt[];
extern unsigned char kal_2_mouth6_TA_tex_txt[];
extern unsigned char kal_2_tmem_txt[];
extern unsigned short kal_3_pal[];
extern unsigned char kal_3_eye1_TA_tex_txt[];
extern unsigned char kal_3_eye2_TA_tex_txt[];
extern unsigned char kal_3_eye3_TA_tex_txt[];
extern unsigned char kal_3_eye4_TA_tex_txt[];
extern unsigned char kal_3_eye5_TA_tex_txt[];
extern unsigned char kal_3_eye6_TA_tex_txt[];
extern unsigned char kal_3_eye7_TA_tex_txt[];
extern unsigned char kal_3_eye8_TA_tex_txt[];
extern unsigned char kal_3_mouth1_TA_tex_txt[];
extern unsigned char kal_3_mouth2_TA_tex_txt[];
extern unsigned char kal_3_mouth3_TA_tex_txt[];
extern unsigned char kal_3_mouth4_TA_tex_txt[];
extern unsigned char kal_3_mouth5_TA_tex_txt[];
extern unsigned char kal_3_mouth6_TA_tex_txt[];
extern unsigned char kal_3_tmem_txt[];
extern unsigned short kal_4_pal[];
extern unsigned char kal_4_eye1_TA_tex_txt[];
extern unsigned char kal_4_eye2_TA_tex_txt[];
extern unsigned char kal_4_eye3_TA_tex_txt[];
extern unsigned char kal_4_eye4_TA_tex_txt[];
extern unsigned char kal_4_eye5_TA_tex_txt[];
extern unsigned char kal_4_eye6_TA_tex_txt[];
extern unsigned char kal_4_eye7_TA_tex_txt[];
extern unsigned char kal_4_eye8_TA_tex_txt[];
extern unsigned char kal_4_mouth1_TA_tex_txt[];
extern unsigned char kal_4_mouth2_TA_tex_txt[];
extern unsigned char kal_4_mouth3_TA_tex_txt[];
extern unsigned char kal_4_mouth4_TA_tex_txt[];
extern unsigned char kal_4_mouth5_TA_tex_txt[];
extern unsigned char kal_4_mouth6_TA_tex_txt[];
extern unsigned char kal_4_tmem_txt[];
extern unsigned short kal_5_pal[];
extern unsigned char kal_5_eye1_TA_tex_txt[];
extern unsigned char kal_5_eye2_TA_tex_txt[];
extern unsigned char kal_5_eye3_TA_tex_txt[];
extern unsigned char kal_5_eye4_TA_tex_txt[];
extern unsigned char kal_5_eye5_TA_tex_txt[];
extern unsigned char kal_5_eye6_TA_tex_txt[];
extern unsigned char kal_5_eye7_TA_tex_txt[];
extern unsigned char kal_5_eye8_TA_tex_txt[];
extern unsigned char kal_5_mouth1_TA_tex_txt[];
extern unsigned char kal_5_mouth2_TA_tex_txt[];
extern unsigned char kal_5_mouth3_TA_tex_txt[];
extern unsigned char kal_5_mouth4_TA_tex_txt[];
extern unsigned char kal_5_mouth5_TA_tex_txt[];
extern unsigned char kal_5_mouth6_TA_tex_txt[];
extern unsigned char kal_5_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_lon_1;
extern unsigned short lon_1_pal[];
extern unsigned char lon_1_eye1_TA_tex_txt[];
extern unsigned char lon_1_eye2_TA_tex_txt[];
extern unsigned char lon_1_eye3_TA_tex_txt[];
extern unsigned char lon_1_eye4_TA_tex_txt[];
extern unsigned char lon_1_eye5_TA_tex_txt[];
extern unsigned char lon_1_eye6_TA_tex_txt[];
extern unsigned char lon_1_eye7_TA_tex_txt[];
extern unsigned char lon_1_eye8_TA_tex_txt[];
extern unsigned char lon_1_mouth1_TA_tex_txt[];
extern unsigned char lon_1_mouth2_TA_tex_txt[];
extern unsigned char lon_1_mouth3_TA_tex_txt[];
extern unsigned char lon_1_mouth4_TA_tex_txt[];
extern unsigned char lon_1_mouth5_TA_tex_txt[];
extern unsigned char lon_1_mouth6_TA_tex_txt[];
extern unsigned char lon_1_tmem_txt[];
extern unsigned short lon_2_pal[];
extern unsigned char lon_2_eye1_TA_tex_txt[];
extern unsigned char lon_2_eye2_TA_tex_txt[];
extern unsigned char lon_2_eye3_TA_tex_txt[];
extern unsigned char lon_2_eye4_TA_tex_txt[];
extern unsigned char lon_2_eye5_TA_tex_txt[];
extern unsigned char lon_2_eye6_TA_tex_txt[];
extern unsigned char lon_2_eye7_TA_tex_txt[];
extern unsigned char lon_2_eye8_TA_tex_txt[];
extern unsigned char lon_2_mouth1_TA_tex_txt[];
extern unsigned char lon_2_mouth2_TA_tex_txt[];
extern unsigned char lon_2_mouth3_TA_tex_txt[];
extern unsigned char lon_2_mouth4_TA_tex_txt[];
extern unsigned char lon_2_mouth5_TA_tex_txt[];
extern unsigned char lon_2_mouth6_TA_tex_txt[];
extern unsigned char lon_2_tmem_txt[];
extern unsigned short lon_3_pal[];
extern unsigned char lon_3_eye1_TA_tex_txt[];
extern unsigned char lon_3_eye2_TA_tex_txt[];
extern unsigned char lon_3_eye3_TA_tex_txt[];
extern unsigned char lon_3_eye4_TA_tex_txt[];
extern unsigned char lon_3_eye5_TA_tex_txt[];
extern unsigned char lon_3_eye6_TA_tex_txt[];
extern unsigned char lon_3_eye7_TA_tex_txt[];
extern unsigned char lon_3_eye8_TA_tex_txt[];
extern unsigned char lon_3_mouth1_TA_tex_txt[];
extern unsigned char lon_3_mouth2_TA_tex_txt[];
extern unsigned char lon_3_mouth3_TA_tex_txt[];
extern unsigned char lon_3_mouth4_TA_tex_txt[];
extern unsigned char lon_3_mouth5_TA_tex_txt[];
extern unsigned char lon_3_mouth6_TA_tex_txt[];
extern unsigned char lon_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mus_1;
extern unsigned short mus_1_pal[];
extern unsigned char mus_1_eye1_TA_tex_txt[];
extern unsigned char mus_1_eye2_TA_tex_txt[];
extern unsigned char mus_1_eye3_TA_tex_txt[];
extern unsigned char mus_1_eye4_TA_tex_txt[];
extern unsigned char mus_1_eye5_TA_tex_txt[];
extern unsigned char mus_1_eye6_TA_tex_txt[];
extern unsigned char mus_1_eye7_TA_tex_txt[];
extern unsigned char mus_1_eye8_TA_tex_txt[];
extern unsigned char mus_1_mouth1_TA_tex_txt[];
extern unsigned char mus_1_mouth2_TA_tex_txt[];
extern unsigned char mus_1_mouth3_TA_tex_txt[];
extern unsigned char mus_1_mouth4_TA_tex_txt[];
extern unsigned char mus_1_mouth5_TA_tex_txt[];
extern unsigned char mus_1_mouth6_TA_tex_txt[];
extern unsigned char mus_1_tmem_txt[];
extern unsigned short mus_2_pal[];
extern unsigned char mus_2_eye1_TA_tex_txt[];
extern unsigned char mus_2_eye2_TA_tex_txt[];
extern unsigned char mus_2_eye3_TA_tex_txt[];
extern unsigned char mus_2_eye4_TA_tex_txt[];
extern unsigned char mus_2_eye5_TA_tex_txt[];
extern unsigned char mus_2_eye6_TA_tex_txt[];
extern unsigned char mus_2_eye7_TA_tex_txt[];
extern unsigned char mus_2_eye8_TA_tex_txt[];
extern unsigned char mus_2_mouth1_TA_tex_txt[];
extern unsigned char mus_2_mouth2_TA_tex_txt[];
extern unsigned char mus_2_mouth3_TA_tex_txt[];
extern unsigned char mus_2_mouth4_TA_tex_txt[];
extern unsigned char mus_2_mouth5_TA_tex_txt[];
extern unsigned char mus_2_mouth6_TA_tex_txt[];
extern unsigned char mus_2_tmem_txt[];
extern unsigned short mus_3_pal[];
extern unsigned char mus_3_eye1_TA_tex_txt[];
extern unsigned char mus_3_eye2_TA_tex_txt[];
extern unsigned char mus_3_eye3_TA_tex_txt[];
extern unsigned char mus_3_eye4_TA_tex_txt[];
extern unsigned char mus_3_eye5_TA_tex_txt[];
extern unsigned char mus_3_eye6_TA_tex_txt[];
extern unsigned char mus_3_eye7_TA_tex_txt[];
extern unsigned char mus_3_eye8_TA_tex_txt[];
extern unsigned char mus_3_mouth1_TA_tex_txt[];
extern unsigned char mus_3_mouth2_TA_tex_txt[];
extern unsigned char mus_3_mouth3_TA_tex_txt[];
extern unsigned char mus_3_mouth4_TA_tex_txt[];
extern unsigned char mus_3_mouth5_TA_tex_txt[];
extern unsigned char mus_3_mouth6_TA_tex_txt[];
extern unsigned char mus_3_tmem_txt[];
extern unsigned short mus_4_pal[];
extern unsigned char mus_4_eye1_TA_tex_txt[];
extern unsigned char mus_4_eye2_TA_tex_txt[];
extern unsigned char mus_4_eye3_TA_tex_txt[];
extern unsigned char mus_4_eye4_TA_tex_txt[];
extern unsigned char mus_4_eye5_TA_tex_txt[];
extern unsigned char mus_4_eye6_TA_tex_txt[];
extern unsigned char mus_4_eye7_TA_tex_txt[];
extern unsigned char mus_4_eye8_TA_tex_txt[];
extern unsigned char mus_4_mouth1_TA_tex_txt[];
extern unsigned char mus_4_mouth2_TA_tex_txt[];
extern unsigned char mus_4_mouth3_TA_tex_txt[];
extern unsigned char mus_4_mouth4_TA_tex_txt[];
extern unsigned char mus_4_mouth5_TA_tex_txt[];
extern unsigned char mus_4_mouth6_TA_tex_txt[];
extern unsigned char mus_4_tmem_txt[];
extern unsigned short mus_5_pal[];
extern unsigned char mus_5_eye1_TA_tex_txt[];
extern unsigned char mus_5_eye2_TA_tex_txt[];
extern unsigned char mus_5_eye3_TA_tex_txt[];
extern unsigned char mus_5_eye4_TA_tex_txt[];
extern unsigned char mus_5_eye5_TA_tex_txt[];
extern unsigned char mus_5_eye6_TA_tex_txt[];
extern unsigned char mus_5_eye7_TA_tex_txt[];
extern unsigned char mus_5_eye8_TA_tex_txt[];
extern unsigned char mus_5_mouth1_TA_tex_txt[];
extern unsigned char mus_5_mouth2_TA_tex_txt[];
extern unsigned char mus_5_mouth3_TA_tex_txt[];
extern unsigned char mus_5_mouth4_TA_tex_txt[];
extern unsigned char mus_5_mouth5_TA_tex_txt[];
extern unsigned char mus_5_mouth6_TA_tex_txt[];
extern unsigned char mus_5_tmem_txt[];
extern unsigned short mus_6_pal[];
extern unsigned char mus_6_eye1_TA_tex_txt[];
extern unsigned char mus_6_eye2_TA_tex_txt[];
extern unsigned char mus_6_eye3_TA_tex_txt[];
extern unsigned char mus_6_eye4_TA_tex_txt[];
extern unsigned char mus_6_eye5_TA_tex_txt[];
extern unsigned char mus_6_eye6_TA_tex_txt[];
extern unsigned char mus_6_eye7_TA_tex_txt[];
extern unsigned char mus_6_eye8_TA_tex_txt[];
extern unsigned char mus_6_mouth1_TA_tex_txt[];
extern unsigned char mus_6_mouth2_TA_tex_txt[];
extern unsigned char mus_6_mouth3_TA_tex_txt[];
extern unsigned char mus_6_mouth4_TA_tex_txt[];
extern unsigned char mus_6_mouth5_TA_tex_txt[];
extern unsigned char mus_6_mouth6_TA_tex_txt[];
extern unsigned char mus_6_tmem_txt[];
extern unsigned short mus_7_pal[];
extern unsigned char mus_7_eye1_TA_tex_txt[];
extern unsigned char mus_7_eye2_TA_tex_txt[];
extern unsigned char mus_7_eye3_TA_tex_txt[];
extern unsigned char mus_7_eye4_TA_tex_txt[];
extern unsigned char mus_7_eye5_TA_tex_txt[];
extern unsigned char mus_7_eye6_TA_tex_txt[];
extern unsigned char mus_7_eye7_TA_tex_txt[];
extern unsigned char mus_7_eye8_TA_tex_txt[];
extern unsigned char mus_7_mouth1_TA_tex_txt[];
extern unsigned char mus_7_mouth2_TA_tex_txt[];
extern unsigned char mus_7_mouth3_TA_tex_txt[];
extern unsigned char mus_7_mouth4_TA_tex_txt[];
extern unsigned char mus_7_mouth5_TA_tex_txt[];
extern unsigned char mus_7_mouth6_TA_tex_txt[];
extern unsigned char mus_7_tmem_txt[];
extern unsigned short mus_8_pal[];
extern unsigned char mus_8_eye1_TA_tex_txt[];
extern unsigned char mus_8_eye2_TA_tex_txt[];
extern unsigned char mus_8_eye3_TA_tex_txt[];
extern unsigned char mus_8_eye4_TA_tex_txt[];
extern unsigned char mus_8_eye5_TA_tex_txt[];
extern unsigned char mus_8_eye6_TA_tex_txt[];
extern unsigned char mus_8_eye7_TA_tex_txt[];
extern unsigned char mus_8_eye8_TA_tex_txt[];
extern unsigned char mus_8_mouth1_TA_tex_txt[];
extern unsigned char mus_8_mouth2_TA_tex_txt[];
extern unsigned char mus_8_mouth3_TA_tex_txt[];
extern unsigned char mus_8_mouth4_TA_tex_txt[];
extern unsigned char mus_8_mouth5_TA_tex_txt[];
extern unsigned char mus_8_mouth6_TA_tex_txt[];
extern unsigned char mus_8_tmem_txt[];
extern unsigned short mus_9_pal[];
extern unsigned char mus_9_eye1_TA_tex_txt[];
extern unsigned char mus_9_eye2_TA_tex_txt[];
extern unsigned char mus_9_eye3_TA_tex_txt[];
extern unsigned char mus_9_eye4_TA_tex_txt[];
extern unsigned char mus_9_eye5_TA_tex_txt[];
extern unsigned char mus_9_eye6_TA_tex_txt[];
extern unsigned char mus_9_eye7_TA_tex_txt[];
extern unsigned char mus_9_eye8_TA_tex_txt[];
extern unsigned char mus_9_mouth1_TA_tex_txt[];
extern unsigned char mus_9_mouth2_TA_tex_txt[];
extern unsigned char mus_9_mouth3_TA_tex_txt[];
extern unsigned char mus_9_mouth4_TA_tex_txt[];
extern unsigned char mus_9_mouth5_TA_tex_txt[];
extern unsigned char mus_9_mouth6_TA_tex_txt[];
extern unsigned char mus_9_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_oct_1;
extern unsigned short oct_1_pal[];
extern unsigned char oct_1_eye1_TA_tex_txt[];
extern unsigned char oct_1_eye2_TA_tex_txt[];
extern unsigned char oct_1_eye3_TA_tex_txt[];
extern unsigned char oct_1_eye4_TA_tex_txt[];
extern unsigned char oct_1_eye5_TA_tex_txt[];
extern unsigned char oct_1_eye6_TA_tex_txt[];
extern unsigned char oct_1_eye7_TA_tex_txt[];
extern unsigned char oct_1_eye8_TA_tex_txt[];
extern unsigned char oct_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_ost_1;
extern unsigned short ost_1_pal[];
extern unsigned char ost_1_eye1_TA_tex_txt[];
extern unsigned char ost_1_eye2_TA_tex_txt[];
extern unsigned char ost_1_eye3_TA_tex_txt[];
extern unsigned char ost_1_eye4_TA_tex_txt[];
extern unsigned char ost_1_eye5_TA_tex_txt[];
extern unsigned char ost_1_eye6_TA_tex_txt[];
extern unsigned char ost_1_eye7_TA_tex_txt[];
extern unsigned char ost_1_eye8_TA_tex_txt[];
extern unsigned char ost_1_tmem_txt[];
extern unsigned short ost_2_pal[];
extern unsigned char ost_2_eye1_TA_tex_txt[];
extern unsigned char ost_2_eye2_TA_tex_txt[];
extern unsigned char ost_2_eye3_TA_tex_txt[];
extern unsigned char ost_2_eye4_TA_tex_txt[];
extern unsigned char ost_2_eye5_TA_tex_txt[];
extern unsigned char ost_2_eye6_TA_tex_txt[];
extern unsigned char ost_2_eye7_TA_tex_txt[];
extern unsigned char ost_2_eye8_TA_tex_txt[];
extern unsigned char ost_2_tmem_txt[];
extern unsigned short ost_3_pal[];
extern unsigned char ost_3_eye1_TA_tex_txt[];
extern unsigned char ost_3_eye2_TA_tex_txt[];
extern unsigned char ost_3_eye3_TA_tex_txt[];
extern unsigned char ost_3_eye4_TA_tex_txt[];
extern unsigned char ost_3_eye5_TA_tex_txt[];
extern unsigned char ost_3_eye6_TA_tex_txt[];
extern unsigned char ost_3_eye7_TA_tex_txt[];
extern unsigned char ost_3_eye8_TA_tex_txt[];
extern unsigned char ost_3_tmem_txt[];
extern unsigned short ost_4_pal[];
extern unsigned char ost_4_eye1_TA_tex_txt[];
extern unsigned char ost_4_eye2_TA_tex_txt[];
extern unsigned char ost_4_eye3_TA_tex_txt[];
extern unsigned char ost_4_eye4_TA_tex_txt[];
extern unsigned char ost_4_eye5_TA_tex_txt[];
extern unsigned char ost_4_eye6_TA_tex_txt[];
extern unsigned char ost_4_eye7_TA_tex_txt[];
extern unsigned char ost_4_eye8_TA_tex_txt[];
extern unsigned char ost_4_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pbr_1;
extern unsigned short pbr_1_pal[];
extern unsigned char pbr_1_eye1_TA_tex_txt[];
extern unsigned char pbr_1_eye2_TA_tex_txt[];
extern unsigned char pbr_1_eye3_TA_tex_txt[];
extern unsigned char pbr_1_eye4_TA_tex_txt[];
extern unsigned char pbr_1_eye5_TA_tex_txt[];
extern unsigned char pbr_1_eye6_TA_tex_txt[];
extern unsigned char pbr_1_eye7_TA_tex_txt[];
extern unsigned char pbr_1_eye8_TA_tex_txt[];
extern unsigned char pbr_1_tmem_txt[];
extern unsigned short pbr_2_pal[];
extern unsigned char pbr_2_eye1_TA_tex_txt[];
extern unsigned char pbr_2_eye2_TA_tex_txt[];
extern unsigned char pbr_2_eye3_TA_tex_txt[];
extern unsigned char pbr_2_eye4_TA_tex_txt[];
extern unsigned char pbr_2_eye5_TA_tex_txt[];
extern unsigned char pbr_2_eye6_TA_tex_txt[];
extern unsigned char pbr_2_eye7_TA_tex_txt[];
extern unsigned char pbr_2_eye8_TA_tex_txt[];
extern unsigned char pbr_2_tmem_txt[];
extern unsigned short pbr_3_pal[];
extern unsigned char pbr_3_eye1_TA_tex_txt[];
extern unsigned char pbr_3_eye2_TA_tex_txt[];
extern unsigned char pbr_3_eye3_TA_tex_txt[];
extern unsigned char pbr_3_eye4_TA_tex_txt[];
extern unsigned char pbr_3_eye5_TA_tex_txt[];
extern unsigned char pbr_3_eye6_TA_tex_txt[];
extern unsigned char pbr_3_eye7_TA_tex_txt[];
extern unsigned char pbr_3_eye8_TA_tex_txt[];
extern unsigned char pbr_3_tmem_txt[];
extern unsigned short pbr_4_pal[];
extern unsigned char pbr_4_eye1_TA_tex_txt[];
extern unsigned char pbr_4_eye2_TA_tex_txt[];
extern unsigned char pbr_4_eye3_TA_tex_txt[];
extern unsigned char pbr_4_eye4_TA_tex_txt[];
extern unsigned char pbr_4_eye5_TA_tex_txt[];
extern unsigned char pbr_4_eye6_TA_tex_txt[];
extern unsigned char pbr_4_eye7_TA_tex_txt[];
extern unsigned char pbr_4_eye8_TA_tex_txt[];
extern unsigned char pbr_4_tmem_txt[];
extern unsigned short pbr_5_pal[];
extern unsigned char pbr_5_eye1_TA_tex_txt[];
extern unsigned char pbr_5_eye2_TA_tex_txt[];
extern unsigned char pbr_5_eye3_TA_tex_txt[];
extern unsigned char pbr_5_eye4_TA_tex_txt[];
extern unsigned char pbr_5_eye5_TA_tex_txt[];
extern unsigned char pbr_5_eye6_TA_tex_txt[];
extern unsigned char pbr_5_eye7_TA_tex_txt[];
extern unsigned char pbr_5_eye8_TA_tex_txt[];
extern unsigned char pbr_5_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pgn_1;
extern unsigned short pgn_1_pal[];
extern unsigned char pgn_1_eye1_TA_tex_txt[];
extern unsigned char pgn_1_eye2_TA_tex_txt[];
extern unsigned char pgn_1_eye3_TA_tex_txt[];
extern unsigned char pgn_1_eye4_TA_tex_txt[];
extern unsigned char pgn_1_eye5_TA_tex_txt[];
extern unsigned char pgn_1_eye6_TA_tex_txt[];
extern unsigned char pgn_1_eye7_TA_tex_txt[];
extern unsigned char pgn_1_eye8_TA_tex_txt[];
extern unsigned char pgn_1_tmem_txt[];
extern unsigned short pgn_2_pal[];
extern unsigned char pgn_2_eye1_TA_tex_txt[];
extern unsigned char pgn_2_eye2_TA_tex_txt[];
extern unsigned char pgn_2_eye3_TA_tex_txt[];
extern unsigned char pgn_2_eye4_TA_tex_txt[];
extern unsigned char pgn_2_eye5_TA_tex_txt[];
extern unsigned char pgn_2_eye6_TA_tex_txt[];
extern unsigned char pgn_2_eye7_TA_tex_txt[];
extern unsigned char pgn_2_eye8_TA_tex_txt[];
extern unsigned char pgn_2_tmem_txt[];
extern unsigned short pgn_3_pal[];
extern unsigned char pgn_3_eye1_TA_tex_txt[];
extern unsigned char pgn_3_eye2_TA_tex_txt[];
extern unsigned char pgn_3_eye3_TA_tex_txt[];
extern unsigned char pgn_3_eye4_TA_tex_txt[];
extern unsigned char pgn_3_eye5_TA_tex_txt[];
extern unsigned char pgn_3_eye6_TA_tex_txt[];
extern unsigned char pgn_3_eye7_TA_tex_txt[];
extern unsigned char pgn_3_eye8_TA_tex_txt[];
extern unsigned char pgn_3_tmem_txt[];
extern unsigned short pgn_4_pal[];
extern unsigned char pgn_4_eye1_TA_tex_txt[];
extern unsigned char pgn_4_eye2_TA_tex_txt[];
extern unsigned char pgn_4_eye3_TA_tex_txt[];
extern unsigned char pgn_4_eye4_TA_tex_txt[];
extern unsigned char pgn_4_eye5_TA_tex_txt[];
extern unsigned char pgn_4_eye6_TA_tex_txt[];
extern unsigned char pgn_4_eye7_TA_tex_txt[];
extern unsigned char pgn_4_eye8_TA_tex_txt[];
extern unsigned char pgn_4_tmem_txt[];
extern unsigned short pgn_5_pal[];
extern unsigned char pgn_5_eye1_TA_tex_txt[];
extern unsigned char pgn_5_eye2_TA_tex_txt[];
extern unsigned char pgn_5_eye3_TA_tex_txt[];
extern unsigned char pgn_5_eye4_TA_tex_txt[];
extern unsigned char pgn_5_eye5_TA_tex_txt[];
extern unsigned char pgn_5_eye6_TA_tex_txt[];
extern unsigned char pgn_5_eye7_TA_tex_txt[];
extern unsigned char pgn_5_eye8_TA_tex_txt[];
extern unsigned char pgn_5_tmem_txt[];
extern unsigned short pgn_6_pal[];
extern unsigned char pgn_6_eye1_TA_tex_txt[];
extern unsigned char pgn_6_eye2_TA_tex_txt[];
extern unsigned char pgn_6_eye3_TA_tex_txt[];
extern unsigned char pgn_6_eye4_TA_tex_txt[];
extern unsigned char pgn_6_eye5_TA_tex_txt[];
extern unsigned char pgn_6_eye6_TA_tex_txt[];
extern unsigned char pgn_6_eye7_TA_tex_txt[];
extern unsigned char pgn_6_eye8_TA_tex_txt[];
extern unsigned char pgn_6_tmem_txt[];
extern unsigned short pgn_7_pal[];
extern unsigned char pgn_7_eye1_TA_tex_txt[];
extern unsigned char pgn_7_eye2_TA_tex_txt[];
extern unsigned char pgn_7_eye3_TA_tex_txt[];
extern unsigned char pgn_7_eye4_TA_tex_txt[];
extern unsigned char pgn_7_eye5_TA_tex_txt[];
extern unsigned char pgn_7_eye6_TA_tex_txt[];
extern unsigned char pgn_7_eye7_TA_tex_txt[];
extern unsigned char pgn_7_eye8_TA_tex_txt[];
extern unsigned char pgn_7_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pig_1;
extern unsigned short pig_1_pal[];
extern unsigned char pig_1_eye1_TA_tex_txt[];
extern unsigned char pig_1_eye2_TA_tex_txt[];
extern unsigned char pig_1_eye3_TA_tex_txt[];
extern unsigned char pig_1_eye4_TA_tex_txt[];
extern unsigned char pig_1_eye5_TA_tex_txt[];
extern unsigned char pig_1_eye6_TA_tex_txt[];
extern unsigned char pig_1_eye7_TA_tex_txt[];
extern unsigned char pig_1_eye8_TA_tex_txt[];
extern unsigned char pig_1_mouth1_TA_tex_txt[];
extern unsigned char pig_1_mouth2_TA_tex_txt[];
extern unsigned char pig_1_mouth3_TA_tex_txt[];
extern unsigned char pig_1_mouth4_TA_tex_txt[];
extern unsigned char pig_1_mouth5_TA_tex_txt[];
extern unsigned char pig_1_mouth6_TA_tex_txt[];
extern unsigned char pig_1_tmem_txt[];
extern unsigned short pig_2_pal[];
extern unsigned char pig_2_eye1_TA_tex_txt[];
extern unsigned char pig_2_eye2_TA_tex_txt[];
extern unsigned char pig_2_eye3_TA_tex_txt[];
extern unsigned char pig_2_eye4_TA_tex_txt[];
extern unsigned char pig_2_eye5_TA_tex_txt[];
extern unsigned char pig_2_eye6_TA_tex_txt[];
extern unsigned char pig_2_eye7_TA_tex_txt[];
extern unsigned char pig_2_eye8_TA_tex_txt[];
extern unsigned char pig_2_mouth1_TA_tex_txt[];
extern unsigned char pig_2_mouth2_TA_tex_txt[];
extern unsigned char pig_2_mouth3_TA_tex_txt[];
extern unsigned char pig_2_mouth4_TA_tex_txt[];
extern unsigned char pig_2_mouth5_TA_tex_txt[];
extern unsigned char pig_2_mouth6_TA_tex_txt[];
extern unsigned char pig_2_tmem_txt[];
extern unsigned short pig_3_pal[];
extern unsigned char pig_3_eye1_TA_tex_txt[];
extern unsigned char pig_3_eye2_TA_tex_txt[];
extern unsigned char pig_3_eye3_TA_tex_txt[];
extern unsigned char pig_3_eye4_TA_tex_txt[];
extern unsigned char pig_3_eye5_TA_tex_txt[];
extern unsigned char pig_3_eye6_TA_tex_txt[];
extern unsigned char pig_3_eye7_TA_tex_txt[];
extern unsigned char pig_3_eye8_TA_tex_txt[];
extern unsigned char pig_3_mouth1_TA_tex_txt[];
extern unsigned char pig_3_mouth2_TA_tex_txt[];
extern unsigned char pig_3_mouth3_TA_tex_txt[];
extern unsigned char pig_3_mouth4_TA_tex_txt[];
extern unsigned char pig_3_mouth5_TA_tex_txt[];
extern unsigned char pig_3_mouth6_TA_tex_txt[];
extern unsigned char pig_3_tmem_txt[];
extern unsigned short pig_4_pal[];
extern unsigned char pig_4_eye1_TA_tex_txt[];
extern unsigned char pig_4_eye2_TA_tex_txt[];
extern unsigned char pig_4_eye3_TA_tex_txt[];
extern unsigned char pig_4_eye4_TA_tex_txt[];
extern unsigned char pig_4_eye5_TA_tex_txt[];
extern unsigned char pig_4_eye6_TA_tex_txt[];
extern unsigned char pig_4_eye7_TA_tex_txt[];
extern unsigned char pig_4_eye8_TA_tex_txt[];
extern unsigned char pig_4_mouth1_TA_tex_txt[];
extern unsigned char pig_4_mouth2_TA_tex_txt[];
extern unsigned char pig_4_mouth3_TA_tex_txt[];
extern unsigned char pig_4_mouth4_TA_tex_txt[];
extern unsigned char pig_4_mouth5_TA_tex_txt[];
extern unsigned char pig_4_mouth6_TA_tex_txt[];
extern unsigned char pig_4_tmem_txt[];
extern unsigned short pig_5_pal[];
extern unsigned char pig_5_eye1_TA_tex_txt[];
extern unsigned char pig_5_eye2_TA_tex_txt[];
extern unsigned char pig_5_eye3_TA_tex_txt[];
extern unsigned char pig_5_eye4_TA_tex_txt[];
extern unsigned char pig_5_eye5_TA_tex_txt[];
extern unsigned char pig_5_eye6_TA_tex_txt[];
extern unsigned char pig_5_eye7_TA_tex_txt[];
extern unsigned char pig_5_eye8_TA_tex_txt[];
extern unsigned char pig_5_mouth1_TA_tex_txt[];
extern unsigned char pig_5_mouth2_TA_tex_txt[];
extern unsigned char pig_5_mouth3_TA_tex_txt[];
extern unsigned char pig_5_mouth4_TA_tex_txt[];
extern unsigned char pig_5_mouth5_TA_tex_txt[];
extern unsigned char pig_5_mouth6_TA_tex_txt[];
extern unsigned char pig_5_tmem_txt[];
extern unsigned short pig_6_pal[];
extern unsigned char pig_6_eye1_TA_tex_txt[];
extern unsigned char pig_6_eye2_TA_tex_txt[];
extern unsigned char pig_6_eye3_TA_tex_txt[];
extern unsigned char pig_6_eye4_TA_tex_txt[];
extern unsigned char pig_6_eye5_TA_tex_txt[];
extern unsigned char pig_6_eye6_TA_tex_txt[];
extern unsigned char pig_6_eye7_TA_tex_txt[];
extern unsigned char pig_6_eye8_TA_tex_txt[];
extern unsigned char pig_6_mouth1_TA_tex_txt[];
extern unsigned char pig_6_mouth2_TA_tex_txt[];
extern unsigned char pig_6_mouth3_TA_tex_txt[];
extern unsigned char pig_6_mouth4_TA_tex_txt[];
extern unsigned char pig_6_mouth5_TA_tex_txt[];
extern unsigned char pig_6_mouth6_TA_tex_txt[];
extern unsigned char pig_6_tmem_txt[];
extern unsigned short pig_7_pal[];
extern unsigned char pig_7_eye1_TA_tex_txt[];
extern unsigned char pig_7_eye2_TA_tex_txt[];
extern unsigned char pig_7_eye3_TA_tex_txt[];
extern unsigned char pig_7_eye4_TA_tex_txt[];
extern unsigned char pig_7_eye5_TA_tex_txt[];
extern unsigned char pig_7_eye6_TA_tex_txt[];
extern unsigned char pig_7_eye7_TA_tex_txt[];
extern unsigned char pig_7_eye8_TA_tex_txt[];
extern unsigned char pig_7_mouth1_TA_tex_txt[];
extern unsigned char pig_7_mouth2_TA_tex_txt[];
extern unsigned char pig_7_mouth3_TA_tex_txt[];
extern unsigned char pig_7_mouth4_TA_tex_txt[];
extern unsigned char pig_7_mouth5_TA_tex_txt[];
extern unsigned char pig_7_mouth6_TA_tex_txt[];
extern unsigned char pig_7_tmem_txt[];
extern unsigned short pig_8_pal[];
extern unsigned char pig_8_eye1_TA_tex_txt[];
extern unsigned char pig_8_eye2_TA_tex_txt[];
extern unsigned char pig_8_eye3_TA_tex_txt[];
extern unsigned char pig_8_eye4_TA_tex_txt[];
extern unsigned char pig_8_eye5_TA_tex_txt[];
extern unsigned char pig_8_eye6_TA_tex_txt[];
extern unsigned char pig_8_eye7_TA_tex_txt[];
extern unsigned char pig_8_eye8_TA_tex_txt[];
extern unsigned char pig_8_mouth1_TA_tex_txt[];
extern unsigned char pig_8_mouth2_TA_tex_txt[];
extern unsigned char pig_8_mouth3_TA_tex_txt[];
extern unsigned char pig_8_mouth4_TA_tex_txt[];
extern unsigned char pig_8_mouth5_TA_tex_txt[];
extern unsigned char pig_8_mouth6_TA_tex_txt[];
extern unsigned char pig_8_tmem_txt[];
extern unsigned short pig_9_pal[];
extern unsigned char pig_9_eye1_TA_tex_txt[];
extern unsigned char pig_9_eye2_TA_tex_txt[];
extern unsigned char pig_9_eye3_TA_tex_txt[];
extern unsigned char pig_9_eye4_TA_tex_txt[];
extern unsigned char pig_9_eye5_TA_tex_txt[];
extern unsigned char pig_9_eye6_TA_tex_txt[];
extern unsigned char pig_9_eye7_TA_tex_txt[];
extern unsigned char pig_9_eye8_TA_tex_txt[];
extern unsigned char pig_9_mouth1_TA_tex_txt[];
extern unsigned char pig_9_mouth2_TA_tex_txt[];
extern unsigned char pig_9_mouth3_TA_tex_txt[];
extern unsigned char pig_9_mouth4_TA_tex_txt[];
extern unsigned char pig_9_mouth5_TA_tex_txt[];
extern unsigned char pig_9_mouth6_TA_tex_txt[];
extern unsigned char pig_9_tmem_txt[];
extern unsigned short pig_10_pal[];
extern unsigned char pig_10_eye1_TA_tex_txt[];
extern unsigned char pig_10_eye2_TA_tex_txt[];
extern unsigned char pig_10_eye3_TA_tex_txt[];
extern unsigned char pig_10_eye4_TA_tex_txt[];
extern unsigned char pig_10_eye5_TA_tex_txt[];
extern unsigned char pig_10_eye6_TA_tex_txt[];
extern unsigned char pig_10_eye7_TA_tex_txt[];
extern unsigned char pig_10_eye8_TA_tex_txt[];
extern unsigned char pig_10_mouth1_TA_tex_txt[];
extern unsigned char pig_10_mouth2_TA_tex_txt[];
extern unsigned char pig_10_mouth3_TA_tex_txt[];
extern unsigned char pig_10_mouth4_TA_tex_txt[];
extern unsigned char pig_10_mouth5_TA_tex_txt[];
extern unsigned char pig_10_mouth6_TA_tex_txt[];
extern unsigned char pig_10_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rbt_1;
extern unsigned short rbt_1_pal[];
extern unsigned char rbt_1_eye1_TA_tex_txt[];
extern unsigned char rbt_1_eye2_TA_tex_txt[];
extern unsigned char rbt_1_eye3_TA_tex_txt[];
extern unsigned char rbt_1_eye4_TA_tex_txt[];
extern unsigned char rbt_1_eye5_TA_tex_txt[];
extern unsigned char rbt_1_eye6_TA_tex_txt[];
extern unsigned char rbt_1_eye7_TA_tex_txt[];
extern unsigned char rbt_1_eye8_TA_tex_txt[];
extern unsigned char rbt_1_mouth1_TA_tex_txt[];
extern unsigned char rbt_1_mouth2_TA_tex_txt[];
extern unsigned char rbt_1_mouth3_TA_tex_txt[];
extern unsigned char rbt_1_mouth4_TA_tex_txt[];
extern unsigned char rbt_1_mouth5_TA_tex_txt[];
extern unsigned char rbt_1_mouth6_TA_tex_txt[];
extern unsigned char rbt_1_tmem_txt[];
extern unsigned short rbt_2_pal[];
extern unsigned char rbt_2_eye1_TA_tex_txt[];
extern unsigned char rbt_2_eye2_TA_tex_txt[];
extern unsigned char rbt_2_eye3_TA_tex_txt[];
extern unsigned char rbt_2_eye4_TA_tex_txt[];
extern unsigned char rbt_2_eye5_TA_tex_txt[];
extern unsigned char rbt_2_eye6_TA_tex_txt[];
extern unsigned char rbt_2_eye7_TA_tex_txt[];
extern unsigned char rbt_2_eye8_TA_tex_txt[];
extern unsigned char rbt_2_mouth1_TA_tex_txt[];
extern unsigned char rbt_2_mouth2_TA_tex_txt[];
extern unsigned char rbt_2_mouth3_TA_tex_txt[];
extern unsigned char rbt_2_mouth4_TA_tex_txt[];
extern unsigned char rbt_2_mouth5_TA_tex_txt[];
extern unsigned char rbt_2_mouth6_TA_tex_txt[];
extern unsigned char rbt_2_tmem_txt[];
extern unsigned short rbt_3_pal[];
extern unsigned char rbt_3_eye1_TA_tex_txt[];
extern unsigned char rbt_3_eye2_TA_tex_txt[];
extern unsigned char rbt_3_eye3_TA_tex_txt[];
extern unsigned char rbt_3_eye4_TA_tex_txt[];
extern unsigned char rbt_3_eye5_TA_tex_txt[];
extern unsigned char rbt_3_eye6_TA_tex_txt[];
extern unsigned char rbt_3_eye7_TA_tex_txt[];
extern unsigned char rbt_3_eye8_TA_tex_txt[];
extern unsigned char rbt_3_mouth1_TA_tex_txt[];
extern unsigned char rbt_3_mouth2_TA_tex_txt[];
extern unsigned char rbt_3_mouth3_TA_tex_txt[];
extern unsigned char rbt_3_mouth4_TA_tex_txt[];
extern unsigned char rbt_3_mouth5_TA_tex_txt[];
extern unsigned char rbt_3_mouth6_TA_tex_txt[];
extern unsigned char rbt_3_tmem_txt[];
extern unsigned short rbt_4_pal[];
extern unsigned char rbt_4_eye1_TA_tex_txt[];
extern unsigned char rbt_4_eye2_TA_tex_txt[];
extern unsigned char rbt_4_eye3_TA_tex_txt[];
extern unsigned char rbt_4_eye4_TA_tex_txt[];
extern unsigned char rbt_4_eye5_TA_tex_txt[];
extern unsigned char rbt_4_eye6_TA_tex_txt[];
extern unsigned char rbt_4_eye7_TA_tex_txt[];
extern unsigned char rbt_4_eye8_TA_tex_txt[];
extern unsigned char rbt_4_mouth1_TA_tex_txt[];
extern unsigned char rbt_4_mouth2_TA_tex_txt[];
extern unsigned char rbt_4_mouth3_TA_tex_txt[];
extern unsigned char rbt_4_mouth4_TA_tex_txt[];
extern unsigned char rbt_4_mouth5_TA_tex_txt[];
extern unsigned char rbt_4_mouth6_TA_tex_txt[];
extern unsigned char rbt_4_tmem_txt[];
extern unsigned short rbt_5_pal[];
extern unsigned char rbt_5_eye1_TA_tex_txt[];
extern unsigned char rbt_5_eye2_TA_tex_txt[];
extern unsigned char rbt_5_eye3_TA_tex_txt[];
extern unsigned char rbt_5_eye4_TA_tex_txt[];
extern unsigned char rbt_5_eye5_TA_tex_txt[];
extern unsigned char rbt_5_eye6_TA_tex_txt[];
extern unsigned char rbt_5_eye7_TA_tex_txt[];
extern unsigned char rbt_5_eye8_TA_tex_txt[];
extern unsigned char rbt_5_mouth1_TA_tex_txt[];
extern unsigned char rbt_5_mouth2_TA_tex_txt[];
extern unsigned char rbt_5_mouth3_TA_tex_txt[];
extern unsigned char rbt_5_mouth4_TA_tex_txt[];
extern unsigned char rbt_5_mouth5_TA_tex_txt[];
extern unsigned char rbt_5_mouth6_TA_tex_txt[];
extern unsigned char rbt_5_tmem_txt[];
extern unsigned short rbt_6_pal[];
extern unsigned char rbt_6_eye1_TA_tex_txt[];
extern unsigned char rbt_6_eye2_TA_tex_txt[];
extern unsigned char rbt_6_eye3_TA_tex_txt[];
extern unsigned char rbt_6_eye4_TA_tex_txt[];
extern unsigned char rbt_6_eye5_TA_tex_txt[];
extern unsigned char rbt_6_eye6_TA_tex_txt[];
extern unsigned char rbt_6_eye7_TA_tex_txt[];
extern unsigned char rbt_6_eye8_TA_tex_txt[];
extern unsigned char rbt_6_mouth1_TA_tex_txt[];
extern unsigned char rbt_6_mouth2_TA_tex_txt[];
extern unsigned char rbt_6_mouth3_TA_tex_txt[];
extern unsigned char rbt_6_mouth4_TA_tex_txt[];
extern unsigned char rbt_6_mouth5_TA_tex_txt[];
extern unsigned char rbt_6_mouth6_TA_tex_txt[];
extern unsigned char rbt_6_tmem_txt[];
extern unsigned short rbt_7_pal[];
extern unsigned char rbt_7_eye1_TA_tex_txt[];
extern unsigned char rbt_7_eye2_TA_tex_txt[];
extern unsigned char rbt_7_eye3_TA_tex_txt[];
extern unsigned char rbt_7_eye4_TA_tex_txt[];
extern unsigned char rbt_7_eye5_TA_tex_txt[];
extern unsigned char rbt_7_eye6_TA_tex_txt[];
extern unsigned char rbt_7_eye7_TA_tex_txt[];
extern unsigned char rbt_7_eye8_TA_tex_txt[];
extern unsigned char rbt_7_mouth1_TA_tex_txt[];
extern unsigned char rbt_7_mouth2_TA_tex_txt[];
extern unsigned char rbt_7_mouth3_TA_tex_txt[];
extern unsigned char rbt_7_mouth4_TA_tex_txt[];
extern unsigned char rbt_7_mouth5_TA_tex_txt[];
extern unsigned char rbt_7_mouth6_TA_tex_txt[];
extern unsigned char rbt_7_tmem_txt[];
extern unsigned short rbt_8_pal[];
extern unsigned char rbt_8_eye1_TA_tex_txt[];
extern unsigned char rbt_8_eye2_TA_tex_txt[];
extern unsigned char rbt_8_eye3_TA_tex_txt[];
extern unsigned char rbt_8_eye4_TA_tex_txt[];
extern unsigned char rbt_8_eye5_TA_tex_txt[];
extern unsigned char rbt_8_eye6_TA_tex_txt[];
extern unsigned char rbt_8_eye7_TA_tex_txt[];
extern unsigned char rbt_8_eye8_TA_tex_txt[];
extern unsigned char rbt_8_mouth1_TA_tex_txt[];
extern unsigned char rbt_8_mouth2_TA_tex_txt[];
extern unsigned char rbt_8_mouth3_TA_tex_txt[];
extern unsigned char rbt_8_mouth4_TA_tex_txt[];
extern unsigned char rbt_8_mouth5_TA_tex_txt[];
extern unsigned char rbt_8_mouth6_TA_tex_txt[];
extern unsigned char rbt_8_tmem_txt[];
extern unsigned short rbt_9_pal[];
extern unsigned char rbt_9_eye1_TA_tex_txt[];
extern unsigned char rbt_9_eye2_TA_tex_txt[];
extern unsigned char rbt_9_eye3_TA_tex_txt[];
extern unsigned char rbt_9_eye4_TA_tex_txt[];
extern unsigned char rbt_9_eye5_TA_tex_txt[];
extern unsigned char rbt_9_eye6_TA_tex_txt[];
extern unsigned char rbt_9_eye7_TA_tex_txt[];
extern unsigned char rbt_9_eye8_TA_tex_txt[];
extern unsigned char rbt_9_mouth1_TA_tex_txt[];
extern unsigned char rbt_9_mouth2_TA_tex_txt[];
extern unsigned char rbt_9_mouth3_TA_tex_txt[];
extern unsigned char rbt_9_mouth4_TA_tex_txt[];
extern unsigned char rbt_9_mouth5_TA_tex_txt[];
extern unsigned char rbt_9_mouth6_TA_tex_txt[];
extern unsigned char rbt_9_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rhn_1;
extern unsigned short rhn_1_pal[];
extern unsigned char rhn_1_eye1_TA_tex_txt[];
extern unsigned char rhn_1_eye2_TA_tex_txt[];
extern unsigned char rhn_1_eye3_TA_tex_txt[];
extern unsigned char rhn_1_eye4_TA_tex_txt[];
extern unsigned char rhn_1_eye5_TA_tex_txt[];
extern unsigned char rhn_1_eye6_TA_tex_txt[];
extern unsigned char rhn_1_eye7_TA_tex_txt[];
extern unsigned char rhn_1_eye8_TA_tex_txt[];
extern unsigned char rhn_1_mouth1_TA_tex_txt[];
extern unsigned char rhn_1_mouth2_TA_tex_txt[];
extern unsigned char rhn_1_mouth3_TA_tex_txt[];
extern unsigned char rhn_1_mouth4_TA_tex_txt[];
extern unsigned char rhn_1_mouth5_TA_tex_txt[];
extern unsigned char rhn_1_mouth6_TA_tex_txt[];
extern unsigned char rhn_1_tmem_txt[];
extern unsigned short rhn_2_pal[];
extern unsigned char rhn_2_eye1_TA_tex_txt[];
extern unsigned char rhn_2_eye2_TA_tex_txt[];
extern unsigned char rhn_2_eye3_TA_tex_txt[];
extern unsigned char rhn_2_eye4_TA_tex_txt[];
extern unsigned char rhn_2_eye5_TA_tex_txt[];
extern unsigned char rhn_2_eye6_TA_tex_txt[];
extern unsigned char rhn_2_eye7_TA_tex_txt[];
extern unsigned char rhn_2_eye8_TA_tex_txt[];
extern unsigned char rhn_2_mouth1_TA_tex_txt[];
extern unsigned char rhn_2_mouth2_TA_tex_txt[];
extern unsigned char rhn_2_mouth3_TA_tex_txt[];
extern unsigned char rhn_2_mouth4_TA_tex_txt[];
extern unsigned char rhn_2_mouth5_TA_tex_txt[];
extern unsigned char rhn_2_mouth6_TA_tex_txt[];
extern unsigned char rhn_2_tmem_txt[];
extern unsigned short rhn_3_pal[];
extern unsigned char rhn_3_eye1_TA_tex_txt[];
extern unsigned char rhn_3_eye2_TA_tex_txt[];
extern unsigned char rhn_3_eye3_TA_tex_txt[];
extern unsigned char rhn_3_eye4_TA_tex_txt[];
extern unsigned char rhn_3_eye5_TA_tex_txt[];
extern unsigned char rhn_3_eye6_TA_tex_txt[];
extern unsigned char rhn_3_eye7_TA_tex_txt[];
extern unsigned char rhn_3_eye8_TA_tex_txt[];
extern unsigned char rhn_3_mouth1_TA_tex_txt[];
extern unsigned char rhn_3_mouth2_TA_tex_txt[];
extern unsigned char rhn_3_mouth3_TA_tex_txt[];
extern unsigned char rhn_3_mouth4_TA_tex_txt[];
extern unsigned char rhn_3_mouth5_TA_tex_txt[];
extern unsigned char rhn_3_mouth6_TA_tex_txt[];
extern unsigned char rhn_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_shp_1;
extern unsigned short shp_1_pal[];
extern unsigned char shp_1_eye1_TA_tex_txt[];
extern unsigned char shp_1_eye2_TA_tex_txt[];
extern unsigned char shp_1_eye3_TA_tex_txt[];
extern unsigned char shp_1_eye4_TA_tex_txt[];
extern unsigned char shp_1_eye5_TA_tex_txt[];
extern unsigned char shp_1_eye6_TA_tex_txt[];
extern unsigned char shp_1_eye7_TA_tex_txt[];
extern unsigned char shp_1_eye8_TA_tex_txt[];
extern unsigned char shp_1_mouth1_TA_tex_txt[];
extern unsigned char shp_1_mouth2_TA_tex_txt[];
extern unsigned char shp_1_mouth3_TA_tex_txt[];
extern unsigned char shp_1_mouth4_TA_tex_txt[];
extern unsigned char shp_1_mouth5_TA_tex_txt[];
extern unsigned char shp_1_mouth6_TA_tex_txt[];
extern unsigned char shp_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_squ_1;
extern unsigned short squ_1_pal[];
extern unsigned char squ_1_eye1_TA_tex_txt[];
extern unsigned char squ_1_eye2_TA_tex_txt[];
extern unsigned char squ_1_eye3_TA_tex_txt[];
extern unsigned char squ_1_eye4_TA_tex_txt[];
extern unsigned char squ_1_eye5_TA_tex_txt[];
extern unsigned char squ_1_eye6_TA_tex_txt[];
extern unsigned char squ_1_eye7_TA_tex_txt[];
extern unsigned char squ_1_eye8_TA_tex_txt[];
extern unsigned char squ_1_mouth1_TA_tex_txt[];
extern unsigned char squ_1_mouth2_TA_tex_txt[];
extern unsigned char squ_1_mouth3_TA_tex_txt[];
extern unsigned char squ_1_mouth4_TA_tex_txt[];
extern unsigned char squ_1_mouth5_TA_tex_txt[];
extern unsigned char squ_1_mouth6_TA_tex_txt[];
extern unsigned char squ_1_tmem_txt[];
extern unsigned short squ_2_pal[];
extern unsigned char squ_2_eye1_TA_tex_txt[];
extern unsigned char squ_2_eye2_TA_tex_txt[];
extern unsigned char squ_2_eye3_TA_tex_txt[];
extern unsigned char squ_2_eye4_TA_tex_txt[];
extern unsigned char squ_2_eye5_TA_tex_txt[];
extern unsigned char squ_2_eye6_TA_tex_txt[];
extern unsigned char squ_2_eye7_TA_tex_txt[];
extern unsigned char squ_2_eye8_TA_tex_txt[];
extern unsigned char squ_2_mouth1_TA_tex_txt[];
extern unsigned char squ_2_mouth2_TA_tex_txt[];
extern unsigned char squ_2_mouth3_TA_tex_txt[];
extern unsigned char squ_2_mouth4_TA_tex_txt[];
extern unsigned char squ_2_mouth5_TA_tex_txt[];
extern unsigned char squ_2_mouth6_TA_tex_txt[];
extern unsigned char squ_2_tmem_txt[];
extern unsigned short squ_3_pal[];
extern unsigned char squ_3_eye1_TA_tex_txt[];
extern unsigned char squ_3_eye2_TA_tex_txt[];
extern unsigned char squ_3_eye3_TA_tex_txt[];
extern unsigned char squ_3_eye4_TA_tex_txt[];
extern unsigned char squ_3_eye5_TA_tex_txt[];
extern unsigned char squ_3_eye6_TA_tex_txt[];
extern unsigned char squ_3_eye7_TA_tex_txt[];
extern unsigned char squ_3_eye8_TA_tex_txt[];
extern unsigned char squ_3_mouth1_TA_tex_txt[];
extern unsigned char squ_3_mouth2_TA_tex_txt[];
extern unsigned char squ_3_mouth3_TA_tex_txt[];
extern unsigned char squ_3_mouth4_TA_tex_txt[];
extern unsigned char squ_3_mouth5_TA_tex_txt[];
extern unsigned char squ_3_mouth6_TA_tex_txt[];
extern unsigned char squ_3_tmem_txt[];
extern unsigned short squ_4_pal[];
extern unsigned char squ_4_eye1_TA_tex_txt[];
extern unsigned char squ_4_eye2_TA_tex_txt[];
extern unsigned char squ_4_eye3_TA_tex_txt[];
extern unsigned char squ_4_eye4_TA_tex_txt[];
extern unsigned char squ_4_eye5_TA_tex_txt[];
extern unsigned char squ_4_eye6_TA_tex_txt[];
extern unsigned char squ_4_eye7_TA_tex_txt[];
extern unsigned char squ_4_eye8_TA_tex_txt[];
extern unsigned char squ_4_mouth1_TA_tex_txt[];
extern unsigned char squ_4_mouth2_TA_tex_txt[];
extern unsigned char squ_4_mouth3_TA_tex_txt[];
extern unsigned char squ_4_mouth4_TA_tex_txt[];
extern unsigned char squ_4_mouth5_TA_tex_txt[];
extern unsigned char squ_4_mouth6_TA_tex_txt[];
extern unsigned char squ_4_tmem_txt[];
extern unsigned short squ_5_pal[];
extern unsigned char squ_5_eye1_TA_tex_txt[];
extern unsigned char squ_5_eye2_TA_tex_txt[];
extern unsigned char squ_5_eye3_TA_tex_txt[];
extern unsigned char squ_5_eye4_TA_tex_txt[];
extern unsigned char squ_5_eye5_TA_tex_txt[];
extern unsigned char squ_5_eye6_TA_tex_txt[];
extern unsigned char squ_5_eye7_TA_tex_txt[];
extern unsigned char squ_5_eye8_TA_tex_txt[];
extern unsigned char squ_5_mouth1_TA_tex_txt[];
extern unsigned char squ_5_mouth2_TA_tex_txt[];
extern unsigned char squ_5_mouth3_TA_tex_txt[];
extern unsigned char squ_5_mouth4_TA_tex_txt[];
extern unsigned char squ_5_mouth5_TA_tex_txt[];
extern unsigned char squ_5_mouth6_TA_tex_txt[];
extern unsigned char squ_5_tmem_txt[];
extern unsigned short squ_6_pal[];
extern unsigned char squ_6_eye1_TA_tex_txt[];
extern unsigned char squ_6_eye2_TA_tex_txt[];
extern unsigned char squ_6_eye3_TA_tex_txt[];
extern unsigned char squ_6_eye4_TA_tex_txt[];
extern unsigned char squ_6_eye5_TA_tex_txt[];
extern unsigned char squ_6_eye6_TA_tex_txt[];
extern unsigned char squ_6_eye7_TA_tex_txt[];
extern unsigned char squ_6_eye8_TA_tex_txt[];
extern unsigned char squ_6_mouth1_TA_tex_txt[];
extern unsigned char squ_6_mouth2_TA_tex_txt[];
extern unsigned char squ_6_mouth3_TA_tex_txt[];
extern unsigned char squ_6_mouth4_TA_tex_txt[];
extern unsigned char squ_6_mouth5_TA_tex_txt[];
extern unsigned char squ_6_mouth6_TA_tex_txt[];
extern unsigned char squ_6_tmem_txt[];
extern unsigned short squ_7_pal[];
extern unsigned char squ_7_eye1_TA_tex_txt[];
extern unsigned char squ_7_eye2_TA_tex_txt[];
extern unsigned char squ_7_eye3_TA_tex_txt[];
extern unsigned char squ_7_eye4_TA_tex_txt[];
extern unsigned char squ_7_eye5_TA_tex_txt[];
extern unsigned char squ_7_eye6_TA_tex_txt[];
extern unsigned char squ_7_eye7_TA_tex_txt[];
extern unsigned char squ_7_eye8_TA_tex_txt[];
extern unsigned char squ_7_mouth1_TA_tex_txt[];
extern unsigned char squ_7_mouth2_TA_tex_txt[];
extern unsigned char squ_7_mouth3_TA_tex_txt[];
extern unsigned char squ_7_mouth4_TA_tex_txt[];
extern unsigned char squ_7_mouth5_TA_tex_txt[];
extern unsigned char squ_7_mouth6_TA_tex_txt[];
extern unsigned char squ_7_tmem_txt[];
extern unsigned short squ_8_pal[];
extern unsigned char squ_8_eye1_TA_tex_txt[];
extern unsigned char squ_8_eye2_TA_tex_txt[];
extern unsigned char squ_8_eye3_TA_tex_txt[];
extern unsigned char squ_8_eye4_TA_tex_txt[];
extern unsigned char squ_8_eye5_TA_tex_txt[];
extern unsigned char squ_8_eye6_TA_tex_txt[];
extern unsigned char squ_8_eye7_TA_tex_txt[];
extern unsigned char squ_8_eye8_TA_tex_txt[];
extern unsigned char squ_8_mouth1_TA_tex_txt[];
extern unsigned char squ_8_mouth2_TA_tex_txt[];
extern unsigned char squ_8_mouth3_TA_tex_txt[];
extern unsigned char squ_8_mouth4_TA_tex_txt[];
extern unsigned char squ_8_mouth5_TA_tex_txt[];
extern unsigned char squ_8_mouth6_TA_tex_txt[];
extern unsigned char squ_8_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_tig_1;
extern unsigned short tig_1_pal[];
extern unsigned char tig_1_eye1_TA_tex_txt[];
extern unsigned char tig_1_eye2_TA_tex_txt[];
extern unsigned char tig_1_eye3_TA_tex_txt[];
extern unsigned char tig_1_eye4_TA_tex_txt[];
extern unsigned char tig_1_eye5_TA_tex_txt[];
extern unsigned char tig_1_eye6_TA_tex_txt[];
extern unsigned char tig_1_eye7_TA_tex_txt[];
extern unsigned char tig_1_eye8_TA_tex_txt[];
extern unsigned char tig_1_tmem_txt[];
extern unsigned short tig_2_pal[];
extern unsigned char tig_2_eye1_TA_tex_txt[];
extern unsigned char tig_2_eye2_TA_tex_txt[];
extern unsigned char tig_2_eye3_TA_tex_txt[];
extern unsigned char tig_2_eye4_TA_tex_txt[];
extern unsigned char tig_2_eye5_TA_tex_txt[];
extern unsigned char tig_2_eye6_TA_tex_txt[];
extern unsigned char tig_2_eye7_TA_tex_txt[];
extern unsigned char tig_2_eye8_TA_tex_txt[];
extern unsigned char tig_2_tmem_txt[];
extern unsigned short tig_3_pal[];
extern unsigned char tig_3_eye1_TA_tex_txt[];
extern unsigned char tig_3_eye2_TA_tex_txt[];
extern unsigned char tig_3_eye3_TA_tex_txt[];
extern unsigned char tig_3_eye4_TA_tex_txt[];
extern unsigned char tig_3_eye5_TA_tex_txt[];
extern unsigned char tig_3_eye6_TA_tex_txt[];
extern unsigned char tig_3_eye7_TA_tex_txt[];
extern unsigned char tig_3_eye8_TA_tex_txt[];
extern unsigned char tig_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_wol_1;
extern unsigned short wol_1_pal[];
extern unsigned char wol_1_eye1_TA_tex_txt[];
extern unsigned char wol_1_eye2_TA_tex_txt[];
extern unsigned char wol_1_eye3_TA_tex_txt[];
extern unsigned char wol_1_eye4_TA_tex_txt[];
extern unsigned char wol_1_eye5_TA_tex_txt[];
extern unsigned char wol_1_eye6_TA_tex_txt[];
extern unsigned char wol_1_eye7_TA_tex_txt[];
extern unsigned char wol_1_eye8_TA_tex_txt[];
extern unsigned char wol_1_tmem_txt[];
extern unsigned short wol_2_pal[];
extern unsigned char wol_2_eye1_TA_tex_txt[];
extern unsigned char wol_2_eye2_TA_tex_txt[];
extern unsigned char wol_2_eye3_TA_tex_txt[];
extern unsigned char wol_2_eye4_TA_tex_txt[];
extern unsigned char wol_2_eye5_TA_tex_txt[];
extern unsigned char wol_2_eye6_TA_tex_txt[];
extern unsigned char wol_2_eye7_TA_tex_txt[];
extern unsigned char wol_2_eye8_TA_tex_txt[];
extern unsigned char wol_2_tmem_txt[];
extern unsigned short wol_3_pal[];
extern unsigned char wol_3_eye1_TA_tex_txt[];
extern unsigned char wol_3_eye2_TA_tex_txt[];
extern unsigned char wol_3_eye3_TA_tex_txt[];
extern unsigned char wol_3_eye4_TA_tex_txt[];
extern unsigned char wol_3_eye5_TA_tex_txt[];
extern unsigned char wol_3_eye6_TA_tex_txt[];
extern unsigned char wol_3_eye7_TA_tex_txt[];
extern unsigned char wol_3_eye8_TA_tex_txt[];
extern unsigned char wol_3_tmem_txt[];
extern unsigned short duk_7_pal[];
extern unsigned char duk_7_eye1_TA_tex_txt[];
extern unsigned char duk_7_eye2_TA_tex_txt[];
extern unsigned char duk_7_eye3_TA_tex_txt[];
extern unsigned char duk_7_eye4_TA_tex_txt[];
extern unsigned char duk_7_eye5_TA_tex_txt[];
extern unsigned char duk_7_eye6_TA_tex_txt[];
extern unsigned char duk_7_eye7_TA_tex_txt[];
extern unsigned char duk_7_eye8_TA_tex_txt[];
extern unsigned char duk_7_mouth1_TA_tex_txt[];
extern unsigned char duk_7_mouth2_TA_tex_txt[];
extern unsigned char duk_7_mouth3_TA_tex_txt[];
extern unsigned char duk_7_mouth4_TA_tex_txt[];
extern unsigned char duk_7_mouth5_TA_tex_txt[];
extern unsigned char duk_7_mouth6_TA_tex_txt[];
extern unsigned char duk_7_tmem_txt[];
extern unsigned short duk_8_pal[];
extern unsigned char duk_8_eye1_TA_tex_txt[];
extern unsigned char duk_8_eye2_TA_tex_txt[];
extern unsigned char duk_8_eye3_TA_tex_txt[];
extern unsigned char duk_8_eye4_TA_tex_txt[];
extern unsigned char duk_8_eye5_TA_tex_txt[];
extern unsigned char duk_8_eye6_TA_tex_txt[];
extern unsigned char duk_8_eye7_TA_tex_txt[];
extern unsigned char duk_8_eye8_TA_tex_txt[];
extern unsigned char duk_8_mouth1_TA_tex_txt[];
extern unsigned char duk_8_mouth2_TA_tex_txt[];
extern unsigned char duk_8_mouth3_TA_tex_txt[];
extern unsigned char duk_8_mouth4_TA_tex_txt[];
extern unsigned char duk_8_mouth5_TA_tex_txt[];
extern unsigned char duk_8_mouth6_TA_tex_txt[];
extern unsigned char duk_8_tmem_txt[];
extern unsigned short wol_4_pal[];
extern unsigned char wol_4_eye1_TA_tex_txt[];
extern unsigned char wol_4_eye2_TA_tex_txt[];
extern unsigned char wol_4_eye3_TA_tex_txt[];
extern unsigned char wol_4_eye4_TA_tex_txt[];
extern unsigned char wol_4_eye5_TA_tex_txt[];
extern unsigned char wol_4_eye6_TA_tex_txt[];
extern unsigned char wol_4_eye7_TA_tex_txt[];
extern unsigned char wol_4_eye8_TA_tex_txt[];
extern unsigned char wol_4_tmem_txt[];
extern unsigned short rhn_4_pal[];
extern unsigned char rhn_4_eye1_TA_tex_txt[];
extern unsigned char rhn_4_eye2_TA_tex_txt[];
extern unsigned char rhn_4_eye3_TA_tex_txt[];
extern unsigned char rhn_4_eye4_TA_tex_txt[];
extern unsigned char rhn_4_eye5_TA_tex_txt[];
extern unsigned char rhn_4_eye6_TA_tex_txt[];
extern unsigned char rhn_4_eye7_TA_tex_txt[];
extern unsigned char rhn_4_eye8_TA_tex_txt[];
extern unsigned char rhn_4_mouth1_TA_tex_txt[];
extern unsigned char rhn_4_mouth2_TA_tex_txt[];
extern unsigned char rhn_4_mouth3_TA_tex_txt[];
extern unsigned char rhn_4_mouth4_TA_tex_txt[];
extern unsigned char rhn_4_mouth5_TA_tex_txt[];
extern unsigned char rhn_4_mouth6_TA_tex_txt[];
extern unsigned char rhn_4_tmem_txt[];
extern unsigned short bul_3_pal[];
extern unsigned char bul_3_eye1_TA_tex_txt[];
extern unsigned char bul_3_eye2_TA_tex_txt[];
extern unsigned char bul_3_eye3_TA_tex_txt[];
extern unsigned char bul_3_eye4_TA_tex_txt[];
extern unsigned char bul_3_eye5_TA_tex_txt[];
extern unsigned char bul_3_eye6_TA_tex_txt[];
extern unsigned char bul_3_eye7_TA_tex_txt[];
extern unsigned char bul_3_eye8_TA_tex_txt[];
extern unsigned char bul_3_mouth1_TA_tex_txt[];
extern unsigned char bul_3_mouth2_TA_tex_txt[];
extern unsigned char bul_3_mouth3_TA_tex_txt[];
extern unsigned char bul_3_mouth4_TA_tex_txt[];
extern unsigned char bul_3_mouth5_TA_tex_txt[];
extern unsigned char bul_3_mouth6_TA_tex_txt[];
extern unsigned char bul_3_tmem_txt[];
extern unsigned short bul_4_pal[];
extern unsigned char bul_4_eye1_TA_tex_txt[];
extern unsigned char bul_4_eye2_TA_tex_txt[];
extern unsigned char bul_4_eye3_TA_tex_txt[];
extern unsigned char bul_4_eye4_TA_tex_txt[];
extern unsigned char bul_4_eye5_TA_tex_txt[];
extern unsigned char bul_4_eye6_TA_tex_txt[];
extern unsigned char bul_4_eye7_TA_tex_txt[];
extern unsigned char bul_4_eye8_TA_tex_txt[];
extern unsigned char bul_4_mouth1_TA_tex_txt[];
extern unsigned char bul_4_mouth2_TA_tex_txt[];
extern unsigned char bul_4_mouth3_TA_tex_txt[];
extern unsigned char bul_4_mouth4_TA_tex_txt[];
extern unsigned char bul_4_mouth5_TA_tex_txt[];
extern unsigned char bul_4_mouth6_TA_tex_txt[];
extern unsigned char bul_4_tmem_txt[];
extern unsigned short hip_4_pal[];
extern unsigned char hip_4_eye1_TA_tex_txt[];
extern unsigned char hip_4_eye2_TA_tex_txt[];
extern unsigned char hip_4_eye3_TA_tex_txt[];
extern unsigned char hip_4_eye4_TA_tex_txt[];
extern unsigned char hip_4_eye5_TA_tex_txt[];
extern unsigned char hip_4_eye6_TA_tex_txt[];
extern unsigned char hip_4_eye7_TA_tex_txt[];
extern unsigned char hip_4_eye8_TA_tex_txt[];
extern unsigned char hip_4_tmem_txt[];
extern unsigned short elp_4_pal[];
extern unsigned char elp_4_eye1_TA_tex_txt[];
extern unsigned char elp_4_eye2_TA_tex_txt[];
extern unsigned char elp_4_eye3_TA_tex_txt[];
extern unsigned char elp_4_eye4_TA_tex_txt[];
extern unsigned char elp_4_eye5_TA_tex_txt[];
extern unsigned char elp_4_eye6_TA_tex_txt[];
extern unsigned char elp_4_eye7_TA_tex_txt[];
extern unsigned char elp_4_eye8_TA_tex_txt[];
extern unsigned char elp_4_mouth1_TA_tex_txt[];
extern unsigned char elp_4_mouth2_TA_tex_txt[];
extern unsigned char elp_4_mouth3_TA_tex_txt[];
extern unsigned char elp_4_mouth4_TA_tex_txt[];
extern unsigned char elp_4_mouth5_TA_tex_txt[];
extern unsigned char elp_4_mouth6_TA_tex_txt[];
extern unsigned char elp_4_tmem_txt[];
extern unsigned short dog_9_pal[];
extern unsigned char dog_9_eye1_TA_tex_txt[];
extern unsigned char dog_9_eye2_TA_tex_txt[];
extern unsigned char dog_9_eye3_TA_tex_txt[];
extern unsigned char dog_9_eye4_TA_tex_txt[];
extern unsigned char dog_9_eye5_TA_tex_txt[];
extern unsigned char dog_9_eye6_TA_tex_txt[];
extern unsigned char dog_9_eye7_TA_tex_txt[];
extern unsigned char dog_9_eye8_TA_tex_txt[];
extern unsigned char dog_9_mouth1_TA_tex_txt[];
extern unsigned char dog_9_mouth2_TA_tex_txt[];
extern unsigned char dog_9_mouth3_TA_tex_txt[];
extern unsigned char dog_9_mouth4_TA_tex_txt[];
extern unsigned char dog_9_mouth5_TA_tex_txt[];
extern unsigned char dog_9_mouth6_TA_tex_txt[];
extern unsigned char dog_9_tmem_txt[];
extern unsigned short dog_10_pal[];
extern unsigned char dog_10_eye1_TA_tex_txt[];
extern unsigned char dog_10_eye2_TA_tex_txt[];
extern unsigned char dog_10_eye3_TA_tex_txt[];
extern unsigned char dog_10_eye4_TA_tex_txt[];
extern unsigned char dog_10_eye5_TA_tex_txt[];
extern unsigned char dog_10_eye6_TA_tex_txt[];
extern unsigned char dog_10_eye7_TA_tex_txt[];
extern unsigned char dog_10_eye8_TA_tex_txt[];
extern unsigned char dog_10_mouth1_TA_tex_txt[];
extern unsigned char dog_10_mouth2_TA_tex_txt[];
extern unsigned char dog_10_mouth3_TA_tex_txt[];
extern unsigned char dog_10_mouth4_TA_tex_txt[];
extern unsigned char dog_10_mouth5_TA_tex_txt[];
extern unsigned char dog_10_mouth6_TA_tex_txt[];
extern unsigned char dog_10_tmem_txt[];
extern unsigned short hip_5_pal[];
extern unsigned char hip_5_eye1_TA_tex_txt[];
extern unsigned char hip_5_eye2_TA_tex_txt[];
extern unsigned char hip_5_eye3_TA_tex_txt[];
extern unsigned char hip_5_eye4_TA_tex_txt[];
extern unsigned char hip_5_eye5_TA_tex_txt[];
extern unsigned char hip_5_eye6_TA_tex_txt[];
extern unsigned char hip_5_eye7_TA_tex_txt[];
extern unsigned char hip_5_eye8_TA_tex_txt[];
extern unsigned char hip_5_tmem_txt[];
extern unsigned short hip_6_pal[];
extern unsigned char hip_6_eye1_TA_tex_txt[];
extern unsigned char hip_6_eye2_TA_tex_txt[];
extern unsigned char hip_6_eye3_TA_tex_txt[];
extern unsigned char hip_6_eye4_TA_tex_txt[];
extern unsigned char hip_6_eye5_TA_tex_txt[];
extern unsigned char hip_6_eye6_TA_tex_txt[];
extern unsigned char hip_6_eye7_TA_tex_txt[];
extern unsigned char hip_6_eye8_TA_tex_txt[];
extern unsigned char hip_6_tmem_txt[];
extern unsigned short hip_7_pal[];
extern unsigned char hip_7_eye1_TA_tex_txt[];
extern unsigned char hip_7_eye2_TA_tex_txt[];
extern unsigned char hip_7_eye3_TA_tex_txt[];
extern unsigned char hip_7_eye4_TA_tex_txt[];
extern unsigned char hip_7_eye5_TA_tex_txt[];
extern unsigned char hip_7_eye6_TA_tex_txt[];
extern unsigned char hip_7_eye7_TA_tex_txt[];
extern unsigned char hip_7_eye8_TA_tex_txt[];
extern unsigned char hip_7_tmem_txt[];
extern unsigned short squ_9_pal[];
extern unsigned char squ_9_eye1_TA_tex_txt[];
extern unsigned char squ_9_eye2_TA_tex_txt[];
extern unsigned char squ_9_eye3_TA_tex_txt[];
extern unsigned char squ_9_eye4_TA_tex_txt[];
extern unsigned char squ_9_eye5_TA_tex_txt[];
extern unsigned char squ_9_eye6_TA_tex_txt[];
extern unsigned char squ_9_eye7_TA_tex_txt[];
extern unsigned char squ_9_eye8_TA_tex_txt[];
extern unsigned char squ_9_mouth1_TA_tex_txt[];
extern unsigned char squ_9_mouth2_TA_tex_txt[];
extern unsigned char squ_9_mouth3_TA_tex_txt[];
extern unsigned char squ_9_mouth4_TA_tex_txt[];
extern unsigned char squ_9_mouth5_TA_tex_txt[];
extern unsigned char squ_9_mouth6_TA_tex_txt[];
extern unsigned char squ_9_tmem_txt[];
extern unsigned short squ_10_pal[];
extern unsigned char squ_10_eye1_TA_tex_txt[];
extern unsigned char squ_10_eye2_TA_tex_txt[];
extern unsigned char squ_10_eye3_TA_tex_txt[];
extern unsigned char squ_10_eye4_TA_tex_txt[];
extern unsigned char squ_10_eye5_TA_tex_txt[];
extern unsigned char squ_10_eye6_TA_tex_txt[];
extern unsigned char squ_10_eye7_TA_tex_txt[];
extern unsigned char squ_10_eye8_TA_tex_txt[];
extern unsigned char squ_10_mouth1_TA_tex_txt[];
extern unsigned char squ_10_mouth2_TA_tex_txt[];
extern unsigned char squ_10_mouth3_TA_tex_txt[];
extern unsigned char squ_10_mouth4_TA_tex_txt[];
extern unsigned char squ_10_mouth5_TA_tex_txt[];
extern unsigned char squ_10_mouth6_TA_tex_txt[];
extern unsigned char squ_10_tmem_txt[];
extern unsigned short elp_5_pal[];
extern unsigned char elp_5_eye1_TA_tex_txt[];
extern unsigned char elp_5_eye2_TA_tex_txt[];
extern unsigned char elp_5_eye3_TA_tex_txt[];
extern unsigned char elp_5_eye4_TA_tex_txt[];
extern unsigned char elp_5_eye5_TA_tex_txt[];
extern unsigned char elp_5_eye6_TA_tex_txt[];
extern unsigned char elp_5_eye7_TA_tex_txt[];
extern unsigned char elp_5_eye8_TA_tex_txt[];
extern unsigned char elp_5_mouth1_TA_tex_txt[];
extern unsigned char elp_5_mouth2_TA_tex_txt[];
extern unsigned char elp_5_mouth3_TA_tex_txt[];
extern unsigned char elp_5_mouth4_TA_tex_txt[];
extern unsigned char elp_5_mouth5_TA_tex_txt[];
extern unsigned char elp_5_mouth6_TA_tex_txt[];
extern unsigned char elp_5_tmem_txt[];
extern unsigned short elp_6_pal[];
extern unsigned char elp_6_eye1_TA_tex_txt[];
extern unsigned char elp_6_eye2_TA_tex_txt[];
extern unsigned char elp_6_eye3_TA_tex_txt[];
extern unsigned char elp_6_eye4_TA_tex_txt[];
extern unsigned char elp_6_eye5_TA_tex_txt[];
extern unsigned char elp_6_eye6_TA_tex_txt[];
extern unsigned char elp_6_eye7_TA_tex_txt[];
extern unsigned char elp_6_eye8_TA_tex_txt[];
extern unsigned char elp_6_mouth1_TA_tex_txt[];
extern unsigned char elp_6_mouth2_TA_tex_txt[];
extern unsigned char elp_6_mouth3_TA_tex_txt[];
extern unsigned char elp_6_mouth4_TA_tex_txt[];
extern unsigned char elp_6_mouth5_TA_tex_txt[];
extern unsigned char elp_6_mouth6_TA_tex_txt[];
extern unsigned char elp_6_tmem_txt[];
extern unsigned short crd_4_pal[];
extern unsigned char crd_4_eye1_TA_tex_txt[];
extern unsigned char crd_4_eye2_TA_tex_txt[];
extern unsigned char crd_4_eye3_TA_tex_txt[];
extern unsigned char crd_4_eye4_TA_tex_txt[];
extern unsigned char crd_4_eye5_TA_tex_txt[];
extern unsigned char crd_4_eye6_TA_tex_txt[];
extern unsigned char crd_4_eye7_TA_tex_txt[];
extern unsigned char crd_4_eye8_TA_tex_txt[];
extern unsigned char crd_4_tmem_txt[];
extern unsigned short rbt_10_pal[];
extern unsigned char rbt_10_eye1_TA_tex_txt[];
extern unsigned char rbt_10_eye2_TA_tex_txt[];
extern unsigned char rbt_10_eye3_TA_tex_txt[];
extern unsigned char rbt_10_eye4_TA_tex_txt[];
extern unsigned char rbt_10_eye5_TA_tex_txt[];
extern unsigned char rbt_10_eye6_TA_tex_txt[];
extern unsigned char rbt_10_eye7_TA_tex_txt[];
extern unsigned char rbt_10_eye8_TA_tex_txt[];
extern unsigned char rbt_10_mouth1_TA_tex_txt[];
extern unsigned char rbt_10_mouth2_TA_tex_txt[];
extern unsigned char rbt_10_mouth3_TA_tex_txt[];
extern unsigned char rbt_10_mouth4_TA_tex_txt[];
extern unsigned char rbt_10_mouth5_TA_tex_txt[];
extern unsigned char rbt_10_mouth6_TA_tex_txt[];
extern unsigned char rbt_10_tmem_txt[];
extern unsigned short shp_2_pal[];
extern unsigned char shp_2_eye1_TA_tex_txt[];
extern unsigned char shp_2_eye2_TA_tex_txt[];
extern unsigned char shp_2_eye3_TA_tex_txt[];
extern unsigned char shp_2_eye4_TA_tex_txt[];
extern unsigned char shp_2_eye5_TA_tex_txt[];
extern unsigned char shp_2_eye6_TA_tex_txt[];
extern unsigned char shp_2_eye7_TA_tex_txt[];
extern unsigned char shp_2_eye8_TA_tex_txt[];
extern unsigned char shp_2_mouth1_TA_tex_txt[];
extern unsigned char shp_2_mouth2_TA_tex_txt[];
extern unsigned char shp_2_mouth3_TA_tex_txt[];
extern unsigned char shp_2_mouth4_TA_tex_txt[];
extern unsigned char shp_2_mouth5_TA_tex_txt[];
extern unsigned char shp_2_mouth6_TA_tex_txt[];
extern unsigned char shp_2_tmem_txt[];
extern unsigned short shp_3_pal[];
extern unsigned char shp_3_eye1_TA_tex_txt[];
extern unsigned char shp_3_eye2_TA_tex_txt[];
extern unsigned char shp_3_eye3_TA_tex_txt[];
extern unsigned char shp_3_eye4_TA_tex_txt[];
extern unsigned char shp_3_eye5_TA_tex_txt[];
extern unsigned char shp_3_eye6_TA_tex_txt[];
extern unsigned char shp_3_eye7_TA_tex_txt[];
extern unsigned char shp_3_eye8_TA_tex_txt[];
extern unsigned char shp_3_mouth1_TA_tex_txt[];
extern unsigned char shp_3_mouth2_TA_tex_txt[];
extern unsigned char shp_3_mouth3_TA_tex_txt[];
extern unsigned char shp_3_mouth4_TA_tex_txt[];
extern unsigned char shp_3_mouth5_TA_tex_txt[];
extern unsigned char shp_3_mouth6_TA_tex_txt[];
extern unsigned char shp_3_tmem_txt[];
extern unsigned short wol_5_pal[];
extern unsigned char wol_5_eye1_TA_tex_txt[];
extern unsigned char wol_5_eye2_TA_tex_txt[];
extern unsigned char wol_5_eye3_TA_tex_txt[];
extern unsigned char wol_5_eye4_TA_tex_txt[];
extern unsigned char wol_5_eye5_TA_tex_txt[];
extern unsigned char wol_5_eye6_TA_tex_txt[];
extern unsigned char wol_5_eye7_TA_tex_txt[];
extern unsigned char wol_5_eye8_TA_tex_txt[];
extern unsigned char wol_5_tmem_txt[];
extern unsigned short duk_9_pal[];
extern unsigned char duk_9_eye1_TA_tex_txt[];
extern unsigned char duk_9_eye2_TA_tex_txt[];
extern unsigned char duk_9_eye3_TA_tex_txt[];
extern unsigned char duk_9_eye4_TA_tex_txt[];
extern unsigned char duk_9_eye5_TA_tex_txt[];
extern unsigned char duk_9_eye6_TA_tex_txt[];
extern unsigned char duk_9_eye7_TA_tex_txt[];
extern unsigned char duk_9_eye8_TA_tex_txt[];
extern unsigned char duk_9_mouth1_TA_tex_txt[];
extern unsigned char duk_9_mouth2_TA_tex_txt[];
extern unsigned char duk_9_mouth3_TA_tex_txt[];
extern unsigned char duk_9_mouth4_TA_tex_txt[];
extern unsigned char duk_9_mouth5_TA_tex_txt[];
extern unsigned char duk_9_mouth6_TA_tex_txt[];
extern unsigned char duk_9_tmem_txt[];
extern unsigned short duk_10_pal[];
extern unsigned char duk_10_eye1_TA_tex_txt[];
extern unsigned char duk_10_eye2_TA_tex_txt[];
extern unsigned char duk_10_eye3_TA_tex_txt[];
extern unsigned char duk_10_eye4_TA_tex_txt[];
extern unsigned char duk_10_eye5_TA_tex_txt[];
extern unsigned char duk_10_eye6_TA_tex_txt[];
extern unsigned char duk_10_eye7_TA_tex_txt[];
extern unsigned char duk_10_eye8_TA_tex_txt[];
extern unsigned char duk_10_mouth1_TA_tex_txt[];
extern unsigned char duk_10_mouth2_TA_tex_txt[];
extern unsigned char duk_10_mouth3_TA_tex_txt[];
extern unsigned char duk_10_mouth4_TA_tex_txt[];
extern unsigned char duk_10_mouth5_TA_tex_txt[];
extern unsigned char duk_10_mouth6_TA_tex_txt[];
extern unsigned char duk_10_tmem_txt[];
extern unsigned short shp_4_pal[];
extern unsigned char shp_4_eye1_TA_tex_txt[];
extern unsigned char shp_4_eye2_TA_tex_txt[];
extern unsigned char shp_4_eye3_TA_tex_txt[];
extern unsigned char shp_4_eye4_TA_tex_txt[];
extern unsigned char shp_4_eye5_TA_tex_txt[];
extern unsigned char shp_4_eye6_TA_tex_txt[];
extern unsigned char shp_4_eye7_TA_tex_txt[];
extern unsigned char shp_4_eye8_TA_tex_txt[];
extern unsigned char shp_4_mouth1_TA_tex_txt[];
extern unsigned char shp_4_mouth2_TA_tex_txt[];
extern unsigned char shp_4_mouth3_TA_tex_txt[];
extern unsigned char shp_4_mouth4_TA_tex_txt[];
extern unsigned char shp_4_mouth5_TA_tex_txt[];
extern unsigned char shp_4_mouth6_TA_tex_txt[];
extern unsigned char shp_4_tmem_txt[];
extern unsigned short shp_5_pal[];
extern unsigned char shp_5_eye1_TA_tex_txt[];
extern unsigned char shp_5_eye2_TA_tex_txt[];
extern unsigned char shp_5_eye3_TA_tex_txt[];
extern unsigned char shp_5_eye4_TA_tex_txt[];
extern unsigned char shp_5_eye5_TA_tex_txt[];
extern unsigned char shp_5_eye6_TA_tex_txt[];
extern unsigned char shp_5_eye7_TA_tex_txt[];
extern unsigned char shp_5_eye8_TA_tex_txt[];
extern unsigned char shp_5_mouth1_TA_tex_txt[];
extern unsigned char shp_5_mouth2_TA_tex_txt[];
extern unsigned char shp_5_mouth3_TA_tex_txt[];
extern unsigned char shp_5_mouth4_TA_tex_txt[];
extern unsigned char shp_5_mouth5_TA_tex_txt[];
extern unsigned char shp_5_mouth6_TA_tex_txt[];
extern unsigned char shp_5_tmem_txt[];
extern unsigned short shp_6_pal[];
extern unsigned char shp_6_eye1_TA_tex_txt[];
extern unsigned char shp_6_eye2_TA_tex_txt[];
extern unsigned char shp_6_eye3_TA_tex_txt[];
extern unsigned char shp_6_eye4_TA_tex_txt[];
extern unsigned char shp_6_eye5_TA_tex_txt[];
extern unsigned char shp_6_eye6_TA_tex_txt[];
extern unsigned char shp_6_eye7_TA_tex_txt[];
extern unsigned char shp_6_eye8_TA_tex_txt[];
extern unsigned char shp_6_mouth1_TA_tex_txt[];
extern unsigned char shp_6_mouth2_TA_tex_txt[];
extern unsigned char shp_6_mouth3_TA_tex_txt[];
extern unsigned char shp_6_mouth4_TA_tex_txt[];
extern unsigned char shp_6_mouth5_TA_tex_txt[];
extern unsigned char shp_6_mouth6_TA_tex_txt[];
extern unsigned char shp_6_tmem_txt[];
extern unsigned short dog_7_pal[];
extern unsigned char dog_7_eye1_TA_tex_txt[];
extern unsigned char dog_7_eye2_TA_tex_txt[];
extern unsigned char dog_7_eye3_TA_tex_txt[];
extern unsigned char dog_7_eye4_TA_tex_txt[];
extern unsigned char dog_7_eye5_TA_tex_txt[];
extern unsigned char dog_7_eye6_TA_tex_txt[];
extern unsigned char dog_7_eye7_TA_tex_txt[];
extern unsigned char dog_7_eye8_TA_tex_txt[];
extern unsigned char dog_7_mouth1_TA_tex_txt[];
extern unsigned char dog_7_mouth2_TA_tex_txt[];
extern unsigned char dog_7_mouth3_TA_tex_txt[];
extern unsigned char dog_7_mouth4_TA_tex_txt[];
extern unsigned char dog_7_mouth5_TA_tex_txt[];
extern unsigned char dog_7_mouth6_TA_tex_txt[];
extern unsigned char dog_7_tmem_txt[];
extern unsigned short duk_11_pal[];
extern unsigned char duk_11_eye1_TA_tex_txt[];
extern unsigned char duk_11_eye2_TA_tex_txt[];
extern unsigned char duk_11_eye3_TA_tex_txt[];
extern unsigned char duk_11_eye4_TA_tex_txt[];
extern unsigned char duk_11_eye5_TA_tex_txt[];
extern unsigned char duk_11_eye6_TA_tex_txt[];
extern unsigned char duk_11_eye7_TA_tex_txt[];
extern unsigned char duk_11_eye8_TA_tex_txt[];
extern unsigned char duk_11_mouth1_TA_tex_txt[];
extern unsigned char duk_11_mouth2_TA_tex_txt[];
extern unsigned char duk_11_mouth3_TA_tex_txt[];
extern unsigned char duk_11_mouth4_TA_tex_txt[];
extern unsigned char duk_11_mouth5_TA_tex_txt[];
extern unsigned char duk_11_mouth6_TA_tex_txt[];
extern unsigned char duk_11_tmem_txt[];
extern unsigned short rbt_11_pal[];
extern unsigned char rbt_11_eye1_TA_tex_txt[];
extern unsigned char rbt_11_eye2_TA_tex_txt[];
extern unsigned char rbt_11_eye3_TA_tex_txt[];
extern unsigned char rbt_11_eye4_TA_tex_txt[];
extern unsigned char rbt_11_eye5_TA_tex_txt[];
extern unsigned char rbt_11_eye6_TA_tex_txt[];
extern unsigned char rbt_11_eye7_TA_tex_txt[];
extern unsigned char rbt_11_eye8_TA_tex_txt[];
extern unsigned char rbt_11_mouth1_TA_tex_txt[];
extern unsigned char rbt_11_mouth2_TA_tex_txt[];
extern unsigned char rbt_11_mouth3_TA_tex_txt[];
extern unsigned char rbt_11_mouth4_TA_tex_txt[];
extern unsigned char rbt_11_mouth5_TA_tex_txt[];
extern unsigned char rbt_11_mouth6_TA_tex_txt[];
extern unsigned char rbt_11_tmem_txt[];
extern unsigned short squ_11_pal[];
extern unsigned char squ_11_eye1_TA_tex_txt[];
extern unsigned char squ_11_eye2_TA_tex_txt[];
extern unsigned char squ_11_eye3_TA_tex_txt[];
extern unsigned char squ_11_eye4_TA_tex_txt[];
extern unsigned char squ_11_eye5_TA_tex_txt[];
extern unsigned char squ_11_eye6_TA_tex_txt[];
extern unsigned char squ_11_eye7_TA_tex_txt[];
extern unsigned char squ_11_eye8_TA_tex_txt[];
extern unsigned char squ_11_mouth1_TA_tex_txt[];
extern unsigned char squ_11_mouth2_TA_tex_txt[];
extern unsigned char squ_11_mouth3_TA_tex_txt[];
extern unsigned char squ_11_mouth4_TA_tex_txt[];
extern unsigned char squ_11_mouth5_TA_tex_txt[];
extern unsigned char squ_11_mouth6_TA_tex_txt[];
extern unsigned char squ_11_tmem_txt[];
extern unsigned short flg_13_pal[];
extern unsigned char flg_13_eye1_TA_tex_txt[];
extern unsigned char flg_13_eye2_TA_tex_txt[];
extern unsigned char flg_13_eye3_TA_tex_txt[];
extern unsigned char flg_13_eye4_TA_tex_txt[];
extern unsigned char flg_13_eye5_TA_tex_txt[];
extern unsigned char flg_13_eye6_TA_tex_txt[];
extern unsigned char flg_13_eye7_TA_tex_txt[];
extern unsigned char flg_13_eye8_TA_tex_txt[];
extern unsigned char flg_13_mouth1_TA_tex_txt[];
extern unsigned char flg_13_mouth2_TA_tex_txt[];
extern unsigned char flg_13_mouth3_TA_tex_txt[];
extern unsigned char flg_13_mouth4_TA_tex_txt[];
extern unsigned char flg_13_mouth5_TA_tex_txt[];
extern unsigned char flg_13_mouth6_TA_tex_txt[];
extern unsigned char flg_13_tmem_txt[];
extern unsigned short lon_4_pal[];
extern unsigned char lon_4_eye1_TA_tex_txt[];
extern unsigned char lon_4_eye2_TA_tex_txt[];
extern unsigned char lon_4_eye3_TA_tex_txt[];
extern unsigned char lon_4_eye4_TA_tex_txt[];
extern unsigned char lon_4_eye5_TA_tex_txt[];
extern unsigned char lon_4_eye6_TA_tex_txt[];
extern unsigned char lon_4_eye7_TA_tex_txt[];
extern unsigned char lon_4_eye8_TA_tex_txt[];
extern unsigned char lon_4_mouth1_TA_tex_txt[];
extern unsigned char lon_4_mouth2_TA_tex_txt[];
extern unsigned char lon_4_mouth3_TA_tex_txt[];
extern unsigned char lon_4_mouth4_TA_tex_txt[];
extern unsigned char lon_4_mouth5_TA_tex_txt[];
extern unsigned char lon_4_mouth6_TA_tex_txt[];
extern unsigned char lon_4_tmem_txt[];
extern unsigned short pgn_8_pal[];
extern unsigned char pgn_8_eye1_TA_tex_txt[];
extern unsigned char pgn_8_eye2_TA_tex_txt[];
extern unsigned char pgn_8_eye3_TA_tex_txt[];
extern unsigned char pgn_8_eye4_TA_tex_txt[];
extern unsigned char pgn_8_eye5_TA_tex_txt[];
extern unsigned char pgn_8_eye6_TA_tex_txt[];
extern unsigned char pgn_8_eye7_TA_tex_txt[];
extern unsigned char pgn_8_eye8_TA_tex_txt[];
extern unsigned char pgn_8_tmem_txt[];
extern unsigned short elp_7_pal[];
extern unsigned char elp_7_eye1_TA_tex_txt[];
extern unsigned char elp_7_eye2_TA_tex_txt[];
extern unsigned char elp_7_eye3_TA_tex_txt[];
extern unsigned char elp_7_eye4_TA_tex_txt[];
extern unsigned char elp_7_eye5_TA_tex_txt[];
extern unsigned char elp_7_eye6_TA_tex_txt[];
extern unsigned char elp_7_eye7_TA_tex_txt[];
extern unsigned char elp_7_eye8_TA_tex_txt[];
extern unsigned char elp_7_mouth1_TA_tex_txt[];
extern unsigned char elp_7_mouth2_TA_tex_txt[];
extern unsigned char elp_7_mouth3_TA_tex_txt[];
extern unsigned char elp_7_mouth4_TA_tex_txt[];
extern unsigned char elp_7_mouth5_TA_tex_txt[];
extern unsigned char elp_7_mouth6_TA_tex_txt[];
extern unsigned char elp_7_tmem_txt[];
extern unsigned short brd_11_pal[];
extern unsigned char brd_11_eye1_TA_tex_txt[];
extern unsigned char brd_11_eye2_TA_tex_txt[];
extern unsigned char brd_11_eye3_TA_tex_txt[];
extern unsigned char brd_11_eye4_TA_tex_txt[];
extern unsigned char brd_11_eye5_TA_tex_txt[];
extern unsigned char brd_11_eye6_TA_tex_txt[];
extern unsigned char brd_11_eye7_TA_tex_txt[];
extern unsigned char brd_11_eye8_TA_tex_txt[];
extern unsigned char brd_11_tmem_txt[];
extern unsigned short wol_6_pal[];
extern unsigned char wol_6_eye1_TA_tex_txt[];
extern unsigned char wol_6_eye2_TA_tex_txt[];
extern unsigned char wol_6_eye3_TA_tex_txt[];
extern unsigned char wol_6_eye4_TA_tex_txt[];
extern unsigned char wol_6_eye5_TA_tex_txt[];
extern unsigned char wol_6_eye6_TA_tex_txt[];
extern unsigned char wol_6_eye7_TA_tex_txt[];
extern unsigned char wol_6_eye8_TA_tex_txt[];
extern unsigned char wol_6_tmem_txt[];
extern unsigned short mus_10_pal[];
extern unsigned char mus_10_eye1_TA_tex_txt[];
extern unsigned char mus_10_eye2_TA_tex_txt[];
extern unsigned char mus_10_eye3_TA_tex_txt[];
extern unsigned char mus_10_eye4_TA_tex_txt[];
extern unsigned char mus_10_eye5_TA_tex_txt[];
extern unsigned char mus_10_eye6_TA_tex_txt[];
extern unsigned char mus_10_eye7_TA_tex_txt[];
extern unsigned char mus_10_eye8_TA_tex_txt[];
extern unsigned char mus_10_mouth1_TA_tex_txt[];
extern unsigned char mus_10_mouth2_TA_tex_txt[];
extern unsigned char mus_10_mouth3_TA_tex_txt[];
extern unsigned char mus_10_mouth4_TA_tex_txt[];
extern unsigned char mus_10_mouth5_TA_tex_txt[];
extern unsigned char mus_10_mouth6_TA_tex_txt[];
extern unsigned char mus_10_tmem_txt[];
extern unsigned short hrs_8_pal[];
extern unsigned char hrs_8_eye1_TA_tex_txt[];
extern unsigned char hrs_8_eye2_TA_tex_txt[];
extern unsigned char hrs_8_eye3_TA_tex_txt[];
extern unsigned char hrs_8_eye4_TA_tex_txt[];
extern unsigned char hrs_8_eye5_TA_tex_txt[];
extern unsigned char hrs_8_eye6_TA_tex_txt[];
extern unsigned char hrs_8_eye7_TA_tex_txt[];
extern unsigned char hrs_8_eye8_TA_tex_txt[];
extern unsigned char hrs_8_tmem_txt[];
extern unsigned short chn_9_pal[];
extern unsigned char chn_9_eye1_TA_tex_txt[];
extern unsigned char chn_9_eye2_TA_tex_txt[];
extern unsigned char chn_9_eye3_TA_tex_txt[];
extern unsigned char chn_9_eye4_TA_tex_txt[];
extern unsigned char chn_9_eye5_TA_tex_txt[];
extern unsigned char chn_9_eye6_TA_tex_txt[];
extern unsigned char chn_9_eye7_TA_tex_txt[];
extern unsigned char chn_9_eye8_TA_tex_txt[];
extern unsigned char chn_9_tmem_txt[];
extern unsigned short kal_6_pal[];
extern unsigned char kal_6_eye1_TA_tex_txt[];
extern unsigned char kal_6_eye2_TA_tex_txt[];
extern unsigned char kal_6_eye3_TA_tex_txt[];
extern unsigned char kal_6_eye4_TA_tex_txt[];
extern unsigned char kal_6_eye5_TA_tex_txt[];
extern unsigned char kal_6_eye6_TA_tex_txt[];
extern unsigned char kal_6_eye7_TA_tex_txt[];
extern unsigned char kal_6_eye8_TA_tex_txt[];
extern unsigned char kal_6_mouth1_TA_tex_txt[];
extern unsigned char kal_6_mouth2_TA_tex_txt[];
extern unsigned char kal_6_mouth3_TA_tex_txt[];
extern unsigned char kal_6_mouth4_TA_tex_txt[];
extern unsigned char kal_6_mouth5_TA_tex_txt[];
extern unsigned char kal_6_mouth6_TA_tex_txt[];
extern unsigned char kal_6_tmem_txt[];
extern unsigned short gor_5_pal[];
extern unsigned char gor_5_eye1_TA_tex_txt[];
extern unsigned char gor_5_eye2_TA_tex_txt[];
extern unsigned char gor_5_eye3_TA_tex_txt[];
extern unsigned char gor_5_eye4_TA_tex_txt[];
extern unsigned char gor_5_eye5_TA_tex_txt[];
extern unsigned char gor_5_eye6_TA_tex_txt[];
extern unsigned char gor_5_eye7_TA_tex_txt[];
extern unsigned char gor_5_eye8_TA_tex_txt[];
extern unsigned char gor_5_mouth1_TA_tex_txt[];
extern unsigned char gor_5_mouth2_TA_tex_txt[];
extern unsigned char gor_5_mouth3_TA_tex_txt[];
extern unsigned char gor_5_mouth4_TA_tex_txt[];
extern unsigned char gor_5_mouth5_TA_tex_txt[];
extern unsigned char gor_5_mouth6_TA_tex_txt[];
extern unsigned char gor_5_tmem_txt[];
extern unsigned short tig_4_pal[];
extern unsigned char tig_4_eye1_TA_tex_txt[];
extern unsigned char tig_4_eye2_TA_tex_txt[];
extern unsigned char tig_4_eye3_TA_tex_txt[];
extern unsigned char tig_4_eye4_TA_tex_txt[];
extern unsigned char tig_4_eye5_TA_tex_txt[];
extern unsigned char tig_4_eye6_TA_tex_txt[];
extern unsigned char tig_4_eye7_TA_tex_txt[];
extern unsigned char tig_4_eye8_TA_tex_txt[];
extern unsigned char tig_4_tmem_txt[];
extern unsigned short cbr_10_pal[];
extern unsigned char cbr_10_eye1_TA_tex_txt[];
extern unsigned char cbr_10_eye2_TA_tex_txt[];
extern unsigned char cbr_10_eye3_TA_tex_txt[];
extern unsigned char cbr_10_eye4_TA_tex_txt[];
extern unsigned char cbr_10_eye5_TA_tex_txt[];
extern unsigned char cbr_10_eye6_TA_tex_txt[];
extern unsigned char cbr_10_eye7_TA_tex_txt[];
extern unsigned char cbr_10_eye8_TA_tex_txt[];
extern unsigned char cbr_10_mouth1_TA_tex_txt[];
extern unsigned char cbr_10_mouth2_TA_tex_txt[];
extern unsigned char cbr_10_mouth3_TA_tex_txt[];
extern unsigned char cbr_10_mouth4_TA_tex_txt[];
extern unsigned char cbr_10_mouth5_TA_tex_txt[];
extern unsigned char cbr_10_mouth6_TA_tex_txt[];
extern unsigned char cbr_10_tmem_txt[];
extern unsigned short cbr_11_pal[];
extern unsigned char cbr_11_eye1_TA_tex_txt[];
extern unsigned char cbr_11_eye2_TA_tex_txt[];
extern unsigned char cbr_11_eye3_TA_tex_txt[];
extern unsigned char cbr_11_eye4_TA_tex_txt[];
extern unsigned char cbr_11_eye5_TA_tex_txt[];
extern unsigned char cbr_11_eye6_TA_tex_txt[];
extern unsigned char cbr_11_eye7_TA_tex_txt[];
extern unsigned char cbr_11_eye8_TA_tex_txt[];
extern unsigned char cbr_11_mouth1_TA_tex_txt[];
extern unsigned char cbr_11_mouth2_TA_tex_txt[];
extern unsigned char cbr_11_mouth3_TA_tex_txt[];
extern unsigned char cbr_11_mouth4_TA_tex_txt[];
extern unsigned char cbr_11_mouth5_TA_tex_txt[];
extern unsigned char cbr_11_mouth6_TA_tex_txt[];
extern unsigned char cbr_11_tmem_txt[];
extern unsigned short pig_11_pal[];
extern unsigned char pig_11_eye1_TA_tex_txt[];
extern unsigned char pig_11_eye2_TA_tex_txt[];
extern unsigned char pig_11_eye3_TA_tex_txt[];
extern unsigned char pig_11_eye4_TA_tex_txt[];
extern unsigned char pig_11_eye5_TA_tex_txt[];
extern unsigned char pig_11_eye6_TA_tex_txt[];
extern unsigned char pig_11_eye7_TA_tex_txt[];
extern unsigned char pig_11_eye8_TA_tex_txt[];
extern unsigned char pig_11_mouth1_TA_tex_txt[];
extern unsigned char pig_11_mouth2_TA_tex_txt[];
extern unsigned char pig_11_mouth3_TA_tex_txt[];
extern unsigned char pig_11_mouth4_TA_tex_txt[];
extern unsigned char pig_11_mouth5_TA_tex_txt[];
extern unsigned char pig_11_mouth6_TA_tex_txt[];
extern unsigned char pig_11_tmem_txt[];
extern unsigned short cat_14_pal[];
extern unsigned char cat_14_eye1_TA_tex_txt[];
extern unsigned char cat_14_eye2_TA_tex_txt[];
extern unsigned char cat_14_eye3_TA_tex_txt[];
extern unsigned char cat_14_eye4_TA_tex_txt[];
extern unsigned char cat_14_eye5_TA_tex_txt[];
extern unsigned char cat_14_eye6_TA_tex_txt[];
extern unsigned char cat_14_eye7_TA_tex_txt[];
extern unsigned char cat_14_eye8_TA_tex_txt[];
extern unsigned char cat_14_mouth1_TA_tex_txt[];
extern unsigned char cat_14_mouth2_TA_tex_txt[];
extern unsigned char cat_14_mouth3_TA_tex_txt[];
extern unsigned char cat_14_mouth4_TA_tex_txt[];
extern unsigned char cat_14_mouth5_TA_tex_txt[];
extern unsigned char cat_14_mouth6_TA_tex_txt[];
extern unsigned char cat_14_tmem_txt[];
extern unsigned short cat_15_pal[];
extern unsigned char cat_15_eye1_TA_tex_txt[];
extern unsigned char cat_15_eye2_TA_tex_txt[];
extern unsigned char cat_15_eye3_TA_tex_txt[];
extern unsigned char cat_15_eye4_TA_tex_txt[];
extern unsigned char cat_15_eye5_TA_tex_txt[];
extern unsigned char cat_15_eye6_TA_tex_txt[];
extern unsigned char cat_15_eye7_TA_tex_txt[];
extern unsigned char cat_15_eye8_TA_tex_txt[];
extern unsigned char cat_15_mouth1_TA_tex_txt[];
extern unsigned char cat_15_mouth2_TA_tex_txt[];
extern unsigned char cat_15_mouth3_TA_tex_txt[];
extern unsigned char cat_15_mouth4_TA_tex_txt[];
extern unsigned char cat_15_mouth5_TA_tex_txt[];
extern unsigned char cat_15_mouth6_TA_tex_txt[];
extern unsigned char cat_15_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_wls_1;
extern unsigned short wls_1_pal[];
extern unsigned char wls_1_eye1_TA_tex_txt[];
extern unsigned char wls_1_eye2_TA_tex_txt[];
extern unsigned char wls_1_eye3_TA_tex_txt[];
extern unsigned char wls_1_eye4_TA_tex_txt[];
extern unsigned char wls_1_eye5_TA_tex_txt[];
extern unsigned char wls_1_eye6_TA_tex_txt[];
extern unsigned char wls_1_eye7_TA_tex_txt[];
extern unsigned char wls_1_eye8_TA_tex_txt[];
extern unsigned char wls_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_fox_1;
extern unsigned short fox_1_pal[];
extern unsigned char fox_1_eye1_TA_tex_txt[];
extern unsigned char fox_1_eye2_TA_tex_txt[];
extern unsigned char fox_1_eye3_TA_tex_txt[];
extern unsigned char fox_1_eye4_TA_tex_txt[];
extern unsigned char fox_1_eye5_TA_tex_txt[];
extern unsigned char fox_1_eye6_TA_tex_txt[];
extern unsigned char fox_1_eye7_TA_tex_txt[];
extern unsigned char fox_1_eye8_TA_tex_txt[];
extern unsigned char fox_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_grf_1;
extern unsigned short grf_1_pal[];
extern unsigned char grf_1_eye1_TA_tex_txt[];
extern unsigned char grf_1_eye2_TA_tex_txt[];
extern unsigned char grf_1_eye3_TA_tex_txt[];
extern unsigned char grf_1_eye4_TA_tex_txt[];
extern unsigned char grf_1_eye5_TA_tex_txt[];
extern unsigned char grf_1_eye6_TA_tex_txt[];
extern unsigned char grf_1_eye7_TA_tex_txt[];
extern unsigned char grf_1_eye8_TA_tex_txt[];
extern unsigned char grf_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pga_1;
extern unsigned short pga_1_pal[];
extern unsigned char pga_1_eye1_TA_tex_txt[];
extern unsigned char pga_1_eye2_TA_tex_txt[];
extern unsigned char pga_1_eye3_TA_tex_txt[];
extern unsigned char pga_1_eye4_TA_tex_txt[];
extern unsigned char pga_1_eye5_TA_tex_txt[];
extern unsigned char pga_1_eye6_TA_tex_txt[];
extern unsigned char pga_1_eye7_TA_tex_txt[];
extern unsigned char pga_1_eye8_TA_tex_txt[];
extern unsigned char pga_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_xct_1;
extern unsigned short xct_1_pal[];
extern unsigned char xct_1_eye1_TA_tex_txt[];
extern unsigned char xct_1_eye2_TA_tex_txt[];
extern unsigned char xct_1_eye3_TA_tex_txt[];
extern unsigned char xct_1_eye4_TA_tex_txt[];
extern unsigned char xct_1_eye5_TA_tex_txt[];
extern unsigned char xct_1_eye6_TA_tex_txt[];
extern unsigned char xct_1_eye7_TA_tex_txt[];
extern unsigned char xct_1_eye8_TA_tex_txt[];
extern unsigned char xct_1_mouth1_TA_tex_txt[];
extern unsigned char xct_1_mouth2_TA_tex_txt[];
extern unsigned char xct_1_mouth3_TA_tex_txt[];
extern unsigned char xct_1_mouth4_TA_tex_txt[];
extern unsigned char xct_1_mouth5_TA_tex_txt[];
extern unsigned char xct_1_mouth6_TA_tex_txt[];
extern unsigned char xct_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_cml_1;
extern unsigned short cml_1_pal[];
extern unsigned char cml_1_eye1_TA_tex_txt[];
extern unsigned char cml_1_eye2_TA_tex_txt[];
extern unsigned char cml_1_eye3_TA_tex_txt[];
extern unsigned char cml_1_eye4_TA_tex_txt[];
extern unsigned char cml_1_eye5_TA_tex_txt[];
extern unsigned char cml_1_eye6_TA_tex_txt[];
extern unsigned char cml_1_eye7_TA_tex_txt[];
extern unsigned char cml_1_eye8_TA_tex_txt[];
extern unsigned char cml_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_boa_1;
extern unsigned short boa_1_pal[];
extern unsigned char boa_1_eye1_TA_tex_txt[];
extern unsigned char boa_1_eye2_TA_tex_txt[];
extern unsigned char boa_1_eye3_TA_tex_txt[];
extern unsigned char boa_1_eye4_TA_tex_txt[];
extern unsigned char boa_1_eye5_TA_tex_txt[];
extern unsigned char boa_1_eye6_TA_tex_txt[];
extern unsigned char boa_1_eye7_TA_tex_txt[];
extern unsigned char boa_1_eye8_TA_tex_txt[];
extern unsigned char boa_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcn_1;
extern unsigned short rcn_1_pal[];
extern unsigned char rcn_1_eye1_TA_tex_txt[];
extern unsigned char rcn_1_eye2_TA_tex_txt[];
extern unsigned char rcn_1_eye3_TA_tex_txt[];
extern unsigned char rcn_1_eye4_TA_tex_txt[];
extern unsigned char rcn_1_eye5_TA_tex_txt[];
extern unsigned char rcn_1_eye6_TA_tex_txt[];
extern unsigned char rcn_1_eye7_TA_tex_txt[];
extern unsigned char rcn_1_eye8_TA_tex_txt[];
extern unsigned char rcn_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcc_1;
extern unsigned short rcc_1_pal[];
extern unsigned char rcc_1_eye1_TA_tex_txt[];
extern unsigned char rcc_1_eye2_TA_tex_txt[];
extern unsigned char rcc_1_eye3_TA_tex_txt[];
extern unsigned char rcc_1_eye4_TA_tex_txt[];
extern unsigned char rcc_1_eye5_TA_tex_txt[];
extern unsigned char rcc_1_eye6_TA_tex_txt[];
extern unsigned char rcc_1_eye7_TA_tex_txt[];
extern unsigned char rcc_1_eye8_TA_tex_txt[];
extern unsigned char rcc_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcs_1;
extern unsigned short rcs_1_pal[];
extern unsigned char rcs_1_eye1_TA_tex_txt[];
extern unsigned char rcs_1_eye2_TA_tex_txt[];
extern unsigned char rcs_1_eye3_TA_tex_txt[];
extern unsigned char rcs_1_eye4_TA_tex_txt[];
extern unsigned char rcs_1_eye5_TA_tex_txt[];
extern unsigned char rcs_1_eye6_TA_tex_txt[];
extern unsigned char rcs_1_eye7_TA_tex_txt[];
extern unsigned char rcs_1_eye8_TA_tex_txt[];
extern unsigned char rcs_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcd_1;
extern unsigned short rcd_1_pal[];
extern unsigned char rcd_1_eye1_TA_tex_txt[];
extern unsigned char rcd_1_eye2_TA_tex_txt[];
extern unsigned char rcd_1_eye3_TA_tex_txt[];
extern unsigned char rcd_1_eye4_TA_tex_txt[];
extern unsigned char rcd_1_eye5_TA_tex_txt[];
extern unsigned char rcd_1_eye6_TA_tex_txt[];
extern unsigned char rcd_1_eye7_TA_tex_txt[];
extern unsigned char rcd_1_eye8_TA_tex_txt[];
extern unsigned char rcd_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_bpt_1;
extern unsigned short bpt_1_pal[];
extern unsigned char bpt_1_eye1_TA_tex_txt[];
extern unsigned char bpt_1_eye2_TA_tex_txt[];
extern unsigned char bpt_1_eye3_TA_tex_txt[];
extern unsigned char bpt_1_eye4_TA_tex_txt[];
extern unsigned char bpt_1_eye5_TA_tex_txt[];
extern unsigned char bpt_1_eye6_TA_tex_txt[];
extern unsigned char bpt_1_eye7_TA_tex_txt[];
extern unsigned char bpt_1_eye8_TA_tex_txt[];
extern unsigned char bpt_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_plc_1;
extern unsigned short plc_1_pal[];
extern unsigned char plc_1_eye1_TA_tex_txt[];
extern unsigned char plc_1_eye2_TA_tex_txt[];
extern unsigned char plc_1_eye3_TA_tex_txt[];
extern unsigned char plc_1_eye4_TA_tex_txt[];
extern unsigned char plc_1_eye5_TA_tex_txt[];
extern unsigned char plc_1_eye6_TA_tex_txt[];
extern unsigned char plc_1_eye7_TA_tex_txt[];
extern unsigned char plc_1_eye8_TA_tex_txt[];
extern unsigned char plc_1_mouth1_TA_tex_txt[];
extern unsigned char plc_1_mouth2_TA_tex_txt[];
extern unsigned char plc_1_mouth3_TA_tex_txt[];
extern unsigned char plc_1_mouth4_TA_tex_txt[];
extern unsigned char plc_1_mouth5_TA_tex_txt[];
extern unsigned char plc_1_mouth6_TA_tex_txt[];
extern unsigned char plc_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mnk_1;
extern unsigned short mnk_1_pal[];
extern unsigned char mnk_1_eye1_TA_tex_txt[];
extern unsigned char mnk_1_eye2_TA_tex_txt[];
extern unsigned char mnk_1_eye3_TA_tex_txt[];
extern unsigned char mnk_1_eye4_TA_tex_txt[];
extern unsigned char mnk_1_eye5_TA_tex_txt[];
extern unsigned char mnk_1_eye6_TA_tex_txt[];
extern unsigned char mnk_1_eye7_TA_tex_txt[];
extern unsigned char mnk_1_eye8_TA_tex_txt[];
extern unsigned char mnk_1_mouth1_TA_tex_txt[];
extern unsigned char mnk_1_mouth2_TA_tex_txt[];
extern unsigned char mnk_1_mouth3_TA_tex_txt[];
extern unsigned char mnk_1_mouth4_TA_tex_txt[];
extern unsigned char mnk_1_mouth5_TA_tex_txt[];
extern unsigned char mnk_1_mouth6_TA_tex_txt[];
extern unsigned char mnk_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_snt_1;
extern unsigned short snt_1_pal[];
extern unsigned char snt_1_eye1_TA_tex_txt[];
extern unsigned char snt_1_eye2_TA_tex_txt[];
extern unsigned char snt_1_eye3_TA_tex_txt[];
extern unsigned char snt_1_eye4_TA_tex_txt[];
extern unsigned char snt_1_eye5_TA_tex_txt[];
extern unsigned char snt_1_eye6_TA_tex_txt[];
extern unsigned char snt_1_eye7_TA_tex_txt[];
extern unsigned char snt_1_eye8_TA_tex_txt[];
extern unsigned char snt_1_mouth1_TA_tex_txt[];
extern unsigned char snt_1_mouth2_TA_tex_txt[];
extern unsigned char snt_1_mouth3_TA_tex_txt[];
extern unsigned char snt_1_mouth4_TA_tex_txt[];
extern unsigned char snt_1_mouth5_TA_tex_txt[];
extern unsigned char snt_1_mouth6_TA_tex_txt[];
extern unsigned char snt_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pla_1;
extern unsigned short pla_1_pal[];
extern unsigned char pla_1_eye1_TA_tex_txt[];
extern unsigned char pla_1_eye2_TA_tex_txt[];
extern unsigned char pla_1_eye3_TA_tex_txt[];
extern unsigned char pla_1_eye4_TA_tex_txt[];
extern unsigned char pla_1_eye5_TA_tex_txt[];
extern unsigned char pla_1_eye6_TA_tex_txt[];
extern unsigned char pla_1_eye7_TA_tex_txt[];
extern unsigned char pla_1_eye8_TA_tex_txt[];
extern unsigned char pla_1_mouth1_TA_tex_txt[];
extern unsigned char pla_1_mouth2_TA_tex_txt[];
extern unsigned char pla_1_mouth3_TA_tex_txt[];
extern unsigned char pla_1_mouth4_TA_tex_txt[];
extern unsigned char pla_1_mouth5_TA_tex_txt[];
extern unsigned char pla_1_mouth6_TA_tex_txt[];
extern unsigned char pla_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_plb_1;
extern unsigned short plb_1_pal[];
extern unsigned char plb_1_eye1_TA_tex_txt[];
extern unsigned char plb_1_eye2_TA_tex_txt[];
extern unsigned char plb_1_eye3_TA_tex_txt[];
extern unsigned char plb_1_eye4_TA_tex_txt[];
extern unsigned char plb_1_eye5_TA_tex_txt[];
extern unsigned char plb_1_eye6_TA_tex_txt[];
extern unsigned char plb_1_eye7_TA_tex_txt[];
extern unsigned char plb_1_eye8_TA_tex_txt[];
extern unsigned char plb_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pgb_1;
extern unsigned short pgb_1_pal[];
extern unsigned char pgb_1_eye1_TA_tex_txt[];
extern unsigned char pgb_1_eye2_TA_tex_txt[];
extern unsigned char pgb_1_eye3_TA_tex_txt[];
extern unsigned char pgb_1_eye4_TA_tex_txt[];
extern unsigned char pgb_1_eye5_TA_tex_txt[];
extern unsigned char pgb_1_eye6_TA_tex_txt[];
extern unsigned char pgb_1_eye7_TA_tex_txt[];
extern unsigned char pgb_1_eye8_TA_tex_txt[];
extern unsigned char pgb_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_end_1;
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_bev_1;
extern unsigned short bev_1_pal[];
extern unsigned char bev_1_eye1_TA_tex_txt[];
extern unsigned char bev_1_eye2_TA_tex_txt[];
extern unsigned char bev_1_eye3_TA_tex_txt[];
extern unsigned char bev_1_eye4_TA_tex_txt[];
extern unsigned char bev_1_eye5_TA_tex_txt[];
extern unsigned char bev_1_eye6_TA_tex_txt[];
extern unsigned char bev_1_eye7_TA_tex_txt[];
extern unsigned char bev_1_eye8_TA_tex_txt[];
extern unsigned char bev_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcf_1;
extern unsigned short rcf_1_pal[];
extern unsigned char rcf_1_eye1_TA_tex_txt[];
extern unsigned char rcf_1_eye2_TA_tex_txt[];
extern unsigned char rcf_1_eye3_TA_tex_txt[];
extern unsigned char rcf_1_eye4_TA_tex_txt[];
extern unsigned char rcf_1_eye5_TA_tex_txt[];
extern unsigned char rcf_1_eye6_TA_tex_txt[];
extern unsigned char rcf_1_eye7_TA_tex_txt[];
extern unsigned char rcf_1_eye8_TA_tex_txt[];
extern unsigned char rcf_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pkn_1;
extern unsigned short pkn_1_pal[];
extern unsigned char pkn_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_lrc_1;
extern unsigned short lrc_1_pal[];
extern unsigned char lrc_1_eye1_TA_tex_txt[];
extern unsigned char lrc_1_eye2_TA_tex_txt[];
extern unsigned char lrc_1_eye3_TA_tex_txt[];
extern unsigned char lrc_1_eye4_TA_tex_txt[];
extern unsigned char lrc_1_eye5_TA_tex_txt[];
extern unsigned char lrc_1_eye6_TA_tex_txt[];
extern unsigned char lrc_1_eye7_TA_tex_txt[];
extern unsigned char lrc_1_eye8_TA_tex_txt[];
extern unsigned char lrc_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_fob_1;
extern unsigned short fob_1_pal[];
extern unsigned char fob_1_eye1_TA_tex_txt[];
extern unsigned char fob_1_eye2_TA_tex_txt[];
extern unsigned char fob_1_eye3_TA_tex_txt[];
extern unsigned char fob_1_eye4_TA_tex_txt[];
extern unsigned char fob_1_eye5_TA_tex_txt[];
extern unsigned char fob_1_eye6_TA_tex_txt[];
extern unsigned char fob_1_eye7_TA_tex_txt[];
extern unsigned char fob_1_eye8_TA_tex_txt[];
extern unsigned char fob_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_kab_1;
extern unsigned short kab_1_pal[];
extern unsigned char kab_1_eye1_TA_tex_txt[];
extern unsigned char kab_1_eye2_TA_tex_txt[];
extern unsigned char kab_1_eye3_TA_tex_txt[];
extern unsigned char kab_1_eye4_TA_tex_txt[];
extern unsigned char kab_1_eye5_TA_tex_txt[];
extern unsigned char kab_1_eye6_TA_tex_txt[];
extern unsigned char kab_1_eye7_TA_tex_txt[];
extern unsigned char kab_1_eye8_TA_tex_txt[];
extern unsigned char kab_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mol_1;
extern unsigned short mol_1_pal[];
extern unsigned char mol_1_eye1_TA_tex_txt[];
extern unsigned char mol_1_eye2_TA_tex_txt[];
extern unsigned char mol_1_eye3_TA_tex_txt[];
extern unsigned char mol_1_eye4_TA_tex_txt[];
extern unsigned char mol_1_eye5_TA_tex_txt[];
extern unsigned char mol_1_eye6_TA_tex_txt[];
extern unsigned char mol_1_eye7_TA_tex_txt[];
extern unsigned char mol_1_eye8_TA_tex_txt[];
extern unsigned char mol_1_mouth1_TA_tex_txt[];
extern unsigned char mol_1_mouth2_TA_tex_txt[];
extern unsigned char mol_1_mouth3_TA_tex_txt[];
extern unsigned char mol_1_mouth4_TA_tex_txt[];
extern unsigned char mol_1_mouth5_TA_tex_txt[];
extern unsigned char mol_1_mouth6_TA_tex_txt[];
extern unsigned char mol_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_plj_1;
extern unsigned short plj_1_pal[];
extern unsigned char plj_1_eye1_TA_tex_txt[];
extern unsigned char plj_1_eye2_TA_tex_txt[];
extern unsigned char plj_1_eye3_TA_tex_txt[];
extern unsigned char plj_1_eye4_TA_tex_txt[];
extern unsigned char plj_1_eye5_TA_tex_txt[];
extern unsigned char plj_1_eye6_TA_tex_txt[];
extern unsigned char plj_1_eye7_TA_tex_txt[];
extern unsigned char plj_1_eye8_TA_tex_txt[];
extern unsigned char plj_1_mouth1_TA_tex_txt[];
extern unsigned char plj_1_mouth2_TA_tex_txt[];
extern unsigned char plj_1_mouth3_TA_tex_txt[];
extern unsigned char plj_1_mouth4_TA_tex_txt[];
extern unsigned char plj_1_mouth5_TA_tex_txt[];
extern unsigned char plj_1_mouth6_TA_tex_txt[];
extern unsigned char plj_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_seg_1;
extern unsigned short seg_1_pal[];
extern unsigned char seg_1_eye1_TA_tex_txt[];
extern unsigned char seg_1_eye2_TA_tex_txt[];
extern unsigned char seg_1_eye3_TA_tex_txt[];
extern unsigned char seg_1_eye4_TA_tex_txt[];
extern unsigned char seg_1_eye5_TA_tex_txt[];
extern unsigned char seg_1_eye6_TA_tex_txt[];
extern unsigned char seg_1_eye7_TA_tex_txt[];
extern unsigned char seg_1_eye8_TA_tex_txt[];
extern unsigned char seg_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_xsq_1;
extern unsigned short xsq_1_pal[];
extern unsigned char xsq_1_eye1_TA_tex_txt[];
extern unsigned char xsq_1_eye2_TA_tex_txt[];
extern unsigned char xsq_1_eye3_TA_tex_txt[];
extern unsigned char xsq_1_eye4_TA_tex_txt[];
extern unsigned char xsq_1_eye5_TA_tex_txt[];
extern unsigned char xsq_1_eye6_TA_tex_txt[];
extern unsigned char xsq_1_eye7_TA_tex_txt[];
extern unsigned char xsq_1_eye8_TA_tex_txt[];
extern unsigned char xsq_1_mouth1_TA_tex_txt[];
extern unsigned char xsq_1_mouth2_TA_tex_txt[];
extern unsigned char xsq_1_mouth3_TA_tex_txt[];
extern unsigned char xsq_1_mouth4_TA_tex_txt[];
extern unsigned char xsq_1_mouth5_TA_tex_txt[];
extern unsigned char xsq_1_mouth6_TA_tex_txt[];
extern unsigned char xsq_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_owl_1;
extern unsigned short owl_1_pal[];
extern unsigned char owl_1_eye1_TA_tex_txt[];
extern unsigned char owl_1_eye2_TA_tex_txt[];
extern unsigned char owl_1_eye3_TA_tex_txt[];
extern unsigned char owl_1_eye4_TA_tex_txt[];
extern unsigned char owl_1_eye5_TA_tex_txt[];
extern unsigned char owl_1_eye6_TA_tex_txt[];
extern unsigned char owl_1_eye7_TA_tex_txt[];
extern unsigned char owl_1_eye8_TA_tex_txt[];
extern unsigned char owl_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_ttl_1;
extern unsigned short ttl_1_pal[];
extern unsigned char ttl_1_eye1_TA_tex_txt[];
extern unsigned char ttl_1_eye2_TA_tex_txt[];
extern unsigned char ttl_1_eye3_TA_tex_txt[];
extern unsigned char ttl_1_eye4_TA_tex_txt[];
extern unsigned char ttl_1_eye5_TA_tex_txt[];
extern unsigned char ttl_1_eye6_TA_tex_txt[];
extern unsigned char ttl_1_eye7_TA_tex_txt[];
extern unsigned char ttl_1_eye8_TA_tex_txt[];
extern unsigned char ttl_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_gst_1;
extern unsigned short gst_1_pal[];
extern unsigned char gst_1_eye1_TA_tex_txt[];
extern unsigned char gst_1_eye2_TA_tex_txt[];
extern unsigned char gst_1_eye3_TA_tex_txt[];
extern unsigned char gst_1_eye4_TA_tex_txt[];
extern unsigned char gst_1_eye5_TA_tex_txt[];
extern unsigned char gst_1_eye6_TA_tex_txt[];
extern unsigned char gst_1_eye7_TA_tex_txt[];
extern unsigned char gst_1_eye8_TA_tex_txt[];
extern unsigned char gst_1_mouth1_TA_tex_txt[];
extern unsigned char gst_1_mouth2_TA_tex_txt[];
extern unsigned char gst_1_mouth3_TA_tex_txt[];
extern unsigned char gst_1_mouth4_TA_tex_txt[];
extern unsigned char gst_1_mouth5_TA_tex_txt[];
extern unsigned char gst_1_mouth6_TA_tex_txt[];
extern unsigned char gst_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hgh_1;
extern unsigned short hgh_1_pal[];
extern unsigned char hgh_1_eye1_TA_tex_txt[];
extern unsigned char hgh_1_eye2_TA_tex_txt[];
extern unsigned char hgh_1_eye3_TA_tex_txt[];
extern unsigned char hgh_1_eye4_TA_tex_txt[];
extern unsigned char hgh_1_eye5_TA_tex_txt[];
extern unsigned char hgh_1_eye6_TA_tex_txt[];
extern unsigned char hgh_1_eye7_TA_tex_txt[];
extern unsigned char hgh_1_eye8_TA_tex_txt[];
extern unsigned char hgh_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hgs_1;
extern unsigned short hgs_1_pal[];
extern unsigned char hgs_1_eye1_TA_tex_txt[];
extern unsigned char hgs_1_eye2_TA_tex_txt[];
extern unsigned char hgs_1_eye3_TA_tex_txt[];
extern unsigned char hgs_1_eye4_TA_tex_txt[];
extern unsigned char hgs_1_eye5_TA_tex_txt[];
extern unsigned char hgs_1_eye6_TA_tex_txt[];
extern unsigned char hgs_1_eye7_TA_tex_txt[];
extern unsigned char hgs_1_eye8_TA_tex_txt[];
extern unsigned char hgs_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_wip_1;
extern unsigned short wip_1_pal[];
extern unsigned char wip_1_eye1_TA_tex_txt[];
extern unsigned char wip_1_eye2_TA_tex_txt[];
extern unsigned char wip_1_eye3_TA_tex_txt[];
extern unsigned char wip_1_eye4_TA_tex_txt[];
extern unsigned char wip_1_eye5_TA_tex_txt[];
extern unsigned char wip_1_eye6_TA_tex_txt[];
extern unsigned char wip_1_eye7_TA_tex_txt[];
extern unsigned char wip_1_eye8_TA_tex_txt[];
extern unsigned char wip_1_mouth1_TA_tex_txt[];
extern unsigned char wip_1_mouth2_TA_tex_txt[];
extern unsigned char wip_1_mouth3_TA_tex_txt[];
extern unsigned char wip_1_mouth4_TA_tex_txt[];
extern unsigned char wip_1_mouth5_TA_tex_txt[];
extern unsigned char wip_1_mouth6_TA_tex_txt[];
extern unsigned char wip_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mka_1;
extern unsigned short mka_1_pal[];
extern unsigned char mka_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mob_1;
extern unsigned short mob_1_pal[];
extern unsigned char mob_1_eye1_TA_tex_txt[];
extern unsigned char mob_1_eye2_TA_tex_txt[];
extern unsigned char mob_1_eye3_TA_tex_txt[];
extern unsigned char mob_1_eye4_TA_tex_txt[];
extern unsigned char mob_1_eye5_TA_tex_txt[];
extern unsigned char mob_1_eye6_TA_tex_txt[];
extern unsigned char mob_1_eye7_TA_tex_txt[];
extern unsigned char mob_1_eye8_TA_tex_txt[];
extern unsigned char mob_1_mouth1_TA_tex_txt[];
extern unsigned char mob_1_mouth2_TA_tex_txt[];
extern unsigned char mob_1_mouth3_TA_tex_txt[];
extern unsigned char mob_1_mouth4_TA_tex_txt[];
extern unsigned char mob_1_mouth5_TA_tex_txt[];
extern unsigned char mob_1_mouth6_TA_tex_txt[];
extern unsigned char mob_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mos_1;
extern unsigned short mos_1_pal[];
extern unsigned char mos_1_eye1_TA_tex_txt[];
extern unsigned char mos_1_eye2_TA_tex_txt[];
extern unsigned char mos_1_eye3_TA_tex_txt[];
extern unsigned char mos_1_eye4_TA_tex_txt[];
extern unsigned char mos_1_eye5_TA_tex_txt[];
extern unsigned char mos_1_eye6_TA_tex_txt[];
extern unsigned char mos_1_eye7_TA_tex_txt[];
extern unsigned char mos_1_eye8_TA_tex_txt[];
extern unsigned char mos_1_mouth1_TA_tex_txt[];
extern unsigned char mos_1_mouth2_TA_tex_txt[];
extern unsigned char mos_1_mouth3_TA_tex_txt[];
extern unsigned char mos_1_mouth4_TA_tex_txt[];
extern unsigned char mos_1_mouth5_TA_tex_txt[];
extern unsigned char mos_1_mouth6_TA_tex_txt[];
extern unsigned char mos_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_tuk_1;
extern unsigned short tuk_1_pal[];
extern unsigned char tuk_1_eye1_TA_tex_txt[];
extern unsigned char tuk_1_eye2_TA_tex_txt[];
extern unsigned char tuk_1_eye3_TA_tex_txt[];
extern unsigned char tuk_1_eye4_TA_tex_txt[];
extern unsigned char tuk_1_eye5_TA_tex_txt[];
extern unsigned char tuk_1_eye6_TA_tex_txt[];
extern unsigned char tuk_1_eye7_TA_tex_txt[];
extern unsigned char tuk_1_eye8_TA_tex_txt[];
extern unsigned char tuk_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hem_1;
extern unsigned short hem_1_pal[];
extern unsigned char hem_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_cmo_1;
extern unsigned short cmo_1_pal[];
extern unsigned char cmo_1_eye1_TA_tex_txt[];
extern unsigned char cmo_1_eye2_TA_tex_txt[];
extern unsigned char cmo_1_eye3_TA_tex_txt[];
extern unsigned char cmo_1_eye4_TA_tex_txt[];
extern unsigned char cmo_1_eye5_TA_tex_txt[];
extern unsigned char cmo_1_eye6_TA_tex_txt[];
extern unsigned char cmo_1_eye7_TA_tex_txt[];
extern unsigned char cmo_1_eye8_TA_tex_txt[];
extern unsigned char cmo_1_mouth1_TA_tex_txt[];
extern unsigned char cmo_1_mouth2_TA_tex_txt[];
extern unsigned char cmo_1_mouth3_TA_tex_txt[];
extern unsigned char cmo_1_mouth4_TA_tex_txt[];
extern unsigned char cmo_1_mouth5_TA_tex_txt[];
extern unsigned char cmo_1_mouth6_TA_tex_txt[];
extern unsigned char cmo_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_cmb_1;
extern unsigned short cmb_1_pal[];
extern unsigned char cmb_1_eye1_TA_tex_txt[];
extern unsigned char cmb_1_eye2_TA_tex_txt[];
extern unsigned char cmb_1_eye3_TA_tex_txt[];
extern unsigned char cmb_1_eye4_TA_tex_txt[];
extern unsigned char cmb_1_eye5_TA_tex_txt[];
extern unsigned char cmb_1_eye6_TA_tex_txt[];
extern unsigned char cmb_1_eye7_TA_tex_txt[];
extern unsigned char cmb_1_eye8_TA_tex_txt[];
extern unsigned char cmb_1_mouth1_TA_tex_txt[];
extern unsigned char cmb_1_mouth2_TA_tex_txt[];
extern unsigned char cmb_1_mouth3_TA_tex_txt[];
extern unsigned char cmb_1_mouth4_TA_tex_txt[];
extern unsigned char cmb_1_mouth5_TA_tex_txt[];
extern unsigned char cmb_1_mouth6_TA_tex_txt[];
extern unsigned char cmb_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcp_1;
extern unsigned short rcp_1_pal[];
extern unsigned char rcp_1_eye1_TA_tex_txt[];
extern unsigned char rcp_1_eye2_TA_tex_txt[];
extern unsigned char rcp_1_eye3_TA_tex_txt[];
extern unsigned char rcp_1_eye4_TA_tex_txt[];
extern unsigned char rcp_1_eye5_TA_tex_txt[];
extern unsigned char rcp_1_eye6_TA_tex_txt[];
extern unsigned char rcp_1_eye7_TA_tex_txt[];
extern unsigned char rcp_1_eye8_TA_tex_txt[];
extern unsigned char rcp_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_lrp_1;
extern unsigned short lrp_1_pal[];
extern unsigned char lrp_1_eye1_TA_tex_txt[];
extern unsigned char lrp_1_eye2_TA_tex_txt[];
extern unsigned char lrp_1_eye3_TA_tex_txt[];
extern unsigned char lrp_1_eye4_TA_tex_txt[];
extern unsigned char lrp_1_eye5_TA_tex_txt[];
extern unsigned char lrp_1_eye6_TA_tex_txt[];
extern unsigned char lrp_1_eye7_TA_tex_txt[];
extern unsigned char lrp_1_eye8_TA_tex_txt[];
extern unsigned char lrp_1_tmem_txt[];
extern unsigned short lrp_2_pal[];

extern aNPC_draw_data_c npc_draw_data_tbl[] = {
    {
#include "../src/data/npc/tex/cat_1/cat_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_2/cat_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_3/cat_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_4/cat_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_5/cat_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_6/cat_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_7/cat_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_8/cat_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_9/cat_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_10/cat_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_11/cat_11_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_12/cat_12_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_13/cat_13_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ant_1/ant_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ant_2/ant_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ant_3/ant_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ant_4/ant_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ant_5/ant_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bea_1/bea_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bea_2/bea_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bea_3/bea_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bea_5/bea_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bea_6/bea_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bea_7/bea_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bea_8/bea_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bea_9/bea_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bea_10/bea_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_1/brd_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_2/brd_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_3/brd_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_4/brd_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_5/brd_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_6/brd_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_7/brd_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_8/brd_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_9/brd_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_10/brd_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bul_1/bul_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bul_2/bul_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_2/chn_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_3/chn_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_4/chn_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_5/chn_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_6/chn_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_7/chn_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_8/chn_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_1/cbr_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_2/cbr_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_3/cbr_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_4/cbr_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_5/cbr_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_6/cbr_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_7/cbr_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_8/cbr_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_9/cbr_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cow_1/cow_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cow_2/cow_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cow_3/cow_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cow_4/cow_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/crd_1/crd_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/crd_2/crd_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/crd_3/crd_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_1/dog_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_2/dog_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_3/dog_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_4/dog_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_5/dog_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_6/dog_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_8/dog_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_1/duk_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_2/duk_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_3/duk_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_4/duk_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_5/duk_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_6/duk_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/elp_1/elp_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/elp_2/elp_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/elp_3/elp_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_1/flg_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_2/flg_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_3/flg_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_4/flg_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_5/flg_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_6/flg_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_7/flg_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_8/flg_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_9/flg_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_10/flg_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_11/flg_11_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_12/flg_12_draw_data.c"
    },
    {
#include "../src/data/npc/tex/goa_1/goa_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/goa_2/goa_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/goa_3/goa_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/goa_4/goa_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/goa_5/goa_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/goa_6/goa_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/gor_1/gor_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/gor_2/gor_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/gor_3/gor_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/gor_4/gor_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hip_1/hip_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hip_2/hip_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hip_3/hip_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hrs_1/hrs_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hrs_2/hrs_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hrs_3/hrs_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hrs_4/hrs_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hrs_5/hrs_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hrs_6/hrs_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hrs_7/hrs_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kgr_1/kgr_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kgr_2/kgr_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kgr_3/kgr_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kgr_4/kgr_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kgr_5/kgr_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kgr_6/kgr_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kal_1/kal_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kal_2/kal_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kal_3/kal_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kal_4/kal_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kal_5/kal_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/lon_1/lon_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/lon_2/lon_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/lon_3/lon_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_1/mus_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_2/mus_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_3/mus_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_4/mus_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_5/mus_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_6/mus_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_7/mus_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_8/mus_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_9/mus_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/oct_1/oct_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ost_1/ost_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ost_2/ost_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ost_3/ost_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ost_4/ost_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pbr_1/pbr_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pbr_2/pbr_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pbr_3/pbr_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pbr_4/pbr_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pbr_5/pbr_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pgn_1/pgn_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pgn_2/pgn_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pgn_3/pgn_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pgn_4/pgn_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pgn_5/pgn_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pgn_6/pgn_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pgn_7/pgn_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_1/pig_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_2/pig_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_3/pig_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_4/pig_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_5/pig_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_6/pig_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_7/pig_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_8/pig_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_9/pig_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_10/pig_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_1/rbt_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_2/rbt_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_3/rbt_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_4/rbt_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_5/rbt_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_6/rbt_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_7/rbt_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_8/rbt_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_9/rbt_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rhn_1/rhn_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rhn_2/rhn_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rhn_3/rhn_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/shp_1/shp_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_1/squ_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_2/squ_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_3/squ_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_4/squ_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_5/squ_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_6/squ_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_7/squ_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_8/squ_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/tig_1/tig_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/tig_2/tig_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/tig_3/tig_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/wol_1/wol_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/wol_2/wol_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/wol_3/wol_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_7/duk_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_8/duk_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/wol_4/wol_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rhn_4/rhn_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bul_3/bul_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bul_4/bul_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hip_4/hip_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/elp_4/elp_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_9/dog_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_10/dog_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hip_5/hip_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hip_6/hip_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hip_7/hip_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_9/squ_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_10/squ_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/elp_5/elp_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/elp_6/elp_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/crd_4/crd_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_10/rbt_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/shp_2/shp_2_draw_data.c"
    },
    {
#include "../src/data/npc/tex/shp_3/shp_3_draw_data.c"
    },
    {
#include "../src/data/npc/tex/wol_5/wol_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_9/duk_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_10/duk_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/shp_4/shp_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/shp_5/shp_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/shp_6/shp_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/dog_7/dog_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/duk_11/duk_11_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rbt_11/rbt_11_draw_data.c"
    },
    {
#include "../src/data/npc/tex/squ_11/squ_11_draw_data.c"
    },
    {
#include "../src/data/npc/tex/flg_13/flg_13_draw_data.c"
    },
    {
#include "../src/data/npc/tex/lon_4/lon_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pgn_8/pgn_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/elp_7/elp_7_draw_data.c"
    },
    {
#include "../src/data/npc/tex/brd_11/brd_11_draw_data.c"
    },
    {
#include "../src/data/npc/tex/wol_6/wol_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mus_10/mus_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hrs_8/hrs_8_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_9/chn_9_draw_data.c"
    },
    {
#include "../src/data/npc/tex/kal_6/kal_6_draw_data.c"
    },
    {
#include "../src/data/npc/tex/gor_5/gor_5_draw_data.c"
    },
    {
#include "../src/data/npc/tex/tig_4/tig_4_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_10/cbr_10_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cbr_11/cbr_11_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pig_11/pig_11_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_14/cat_14_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cat_15/cat_15_draw_data.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_4.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_5.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_6.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_7.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_8.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_9.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_10.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_11.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_12.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_13.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_14.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_15.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_16.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_17.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_18.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_19.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_20.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_21.c"
    },
    {
#include "../src/data/npc/tex/chn_1/chn_1_draw_data_22.c"
    },
    {
#include "../src/data/npc/tex/wls_1/wls_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/fox_1/fox_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/grf_1/grf_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pga_1/pga_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/xct_1/xct_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/xct_1/xct_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/cml_1/cml_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/boa_1/boa_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rcn_1/rcn_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rcc_1/rcc_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rcs_1/rcs_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rcd_1/rcd_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/bpt_1/bpt_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/plc_1/plc_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mnk_1/mnk_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/snt_1/snt_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pla_1/pla_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/plb_1/plb_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pgb_1/pgb_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/fox_1/fox_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/rcn_1/rcn_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/rcc_1/rcc_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/rcs_1/rcs_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/rcd_1/rcd_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rcn_1/rcn_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/rcc_1/rcc_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/rcs_1/rcs_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/rcd_1/rcd_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/bev_1/bev_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rcf_1/rcf_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/pkn_1/pkn_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/pkn_1/pkn_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/pkn_1/pkn_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/pkn_1/pkn_1_draw_data_4.c"
    },
    {
#include "../src/data/npc/tex/pkn_1/pkn_1_draw_data_5.c"
    },
    {
#include "../src/data/npc/tex/pkn_1/pkn_1_draw_data_6.c"
    },
    {
#include "../src/data/npc/tex/lrc_1/lrc_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_4.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_5.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_6.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_7.c"
    },
    {
#include "../src/data/npc/tex/fob_1/fob_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_8.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_9.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_10.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_11.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_12.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_13.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_14.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_15.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_16.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_17.c"
    },
    {
#include "../src/data/npc/tex/lrc_1/lrc_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/kab_1/kab_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/fob_1/fob_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/rcf_1/rcf_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/rcf_1/rcf_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/rcf_1/rcf_1_draw_data_4.c"
    },
    {
#include "../src/data/npc/tex/bpt_1/bpt_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/mol_1/mol_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_18.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_19.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_20.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_21.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_22.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_23.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_24.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_25.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_26.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_27.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_28.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_29.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_30.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_31.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_32.c"
    },
    {
#include "../src/data/npc/tex/plj_1/plj_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_33.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_34.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_35.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_36.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_37.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_38.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_39.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_40.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_41.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_42.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_43.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_44.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_45.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_46.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_47.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_48.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_49.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_50.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_51.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_52.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_53.c"
    },
    {
#include "../src/data/npc/tex/seg_1/seg_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mol_1/mol_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_54.c"
    },
    {
#include "../src/data/npc/tex/mnk_1/mnk_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/mol_1/mol_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/mol_1/mol_1_draw_data_4.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_55.c"
    },
    {
#include "../src/data/npc/tex/mol_1/mol_1_draw_data_5.c"
    },
    {
#include "../src/data/npc/tex/xsq_1/xsq_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/owl_1/owl_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ttl_1/ttl_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/gst_1/gst_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hgh_1/hgh_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hgs_1/hgs_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/wip_1/wip_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_56.c"
    },
    {
#include "../src/data/npc/tex/ttl_1/ttl_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/mka_1/mka_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/mka_1/mka_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_57.c"
    },
    {
#include "../src/data/npc/tex/ttl_1/ttl_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/pkn_1/pkn_1_draw_data_7.c"
    },
    {
#include "../src/data/npc/tex/mnk_1/mnk_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/seg_1/seg_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/mol_1/mol_1_draw_data_6.c"
    },
    {
#include "../src/data/npc/tex/mol_1/mol_1_draw_data_7.c"
    },
    {
#include "../src/data/npc/tex/mob_1/mob_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/ttl_1/ttl_1_draw_data_4.c"
    },
    {
#include "../src/data/npc/tex/mol_1/mol_1_draw_data_8.c"
    },
    {
#include "../src/data/npc/tex/mos_1/mos_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_58.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_59.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_60.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_61.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_62.c"
    },
    {
#include "../src/data/npc/tex/ttl_1/ttl_1_draw_data_5.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_63.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_64.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_65.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_66.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_67.c"
    },
    {
#include "../src/data/npc/tex/tuk_1/tuk_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/hem_1/hem_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_68.c"
    },
    {
#include "../src/data/npc/tex/cmo_1/cmo_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/cmb_1/cmb_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rcp_1/rcp_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/rcp_1/rcp_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/rcp_1/rcp_1_draw_data_3.c"
    },
    {
#include "../src/data/npc/tex/rcp_1/rcp_1_draw_data_4.c"
    },
    {
#include "../src/data/npc/tex/lrp_1/lrp_1_draw_data.c"
    },
    {
#include "../src/data/npc/tex/lrp_1/lrp_1_draw_data_2.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_69.c"
    },
    {
#include "../src/data/npc/tex/end_1/end_1_draw_data_70.c"
    },
};

mNpc_RaceData_c npc_race_data_tbl[] = {
    {&cKF_bs_r_cat_1, 0x00, 0x20, 0x80, 0.009f, 0x21, 0x00, 0x00, 0x00, 0x0014, 0x0028},
    {&cKF_bs_r_elp_1, 0x30, 0xB0, 0x50, 0.01f, 0x28, 0x02, 0x00, 0x00, 0x0019, 0x0037},
    {&cKF_bs_r_shp_1, 0x60, 0x80, 0xC0, 0.01f, 0x28, 0x00, 0x00, 0x00, 0x0014, 0x0023},
    {&cKF_bs_r_bea_1, 0x40, 0x60, 0xB0, 0.009f, 0x2F, 0x00, 0x00, 0x00, 0x0014, 0x0037},
    {&cKF_bs_r_dog_1, 0x30, 0x00, 0x50, 0.0095f, 0x25, 0x00, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_squ_1, 0x48, 0x68, 0xA0, 0.0068f, 0x1A, 0x00, 0x00, 0x00, 0x0014, 0x0023},
    {&cKF_bs_r_rbt_1, 0x50, 0x70, 0xB0, 0.01f, 0x22, 0x00, 0x00, 0x00, 0x0014, 0x0028},
    {&cKF_bs_r_duk_1, 0x70, 0x48, 0xA0, 0.01f, 0x1F, 0x02, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_hip_1, 0x88,   -1, 0x20, 0.0073f, 0x2B, 0x02, 0x00, 0x00, 0x0019, 0x0032},
    {&cKF_bs_r_wol_1, 0x50,   -1, 0xA0, 0.01f, 0x25, 0x02, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_mus_1, 0x60, 0x80, 0xB8, 0.0055f, 0x1E, 0x02, 0x00, 0x00, 0x0014, 0x0028},
    {&cKF_bs_r_pig_1, 0x40, 0x70, 0xA0, 0.01f, 0x24, 0x00, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_chn_1, 0x10,   -1, 0x98, 0.01f, 0x23, 0x02, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_bul_1, 0x80, 0x20, 0xB0, 0.0125f, 0x2D, 0x00, 0x00, 0x00, 0x0019, 0x0032},
    {&cKF_bs_r_cow_1, 0x38, 0x68, 0xB0, 0.0113f, 0x2A, 0x00, 0x00, 0x00, 0x0019, 0x0032},
    {&cKF_bs_r_brd_1, 0x08,   -1, 0x90, 0.0095f, 0x23, 0x02, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_flg_1, 0x00, 0x20, 0xB0, 0.008f, 0x26, 0x00, 0x00, 0x00, 0x0014, 0x0023},
    {&cKF_bs_r_crd_1, 0x60,   -1, 0xA8, 0.0105f, 0x30, 0x02, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_goa_1, 0x88, 0x58, 0xC0, 0.0105f, 0x23, 0x00, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_tig_1, 0x08,   -1, 0xB0, 0.0113f, 0x29, 0x02, 0x00, 0x00, 0x0014, 0x0032},
    {&cKF_bs_r_ant_1, 0x20,   -1, 0x98, 0.0107f, 0x29, 0x02, 0x00, 0x00, 0x0019, 0x002D},
    {&cKF_bs_r_kal_1, 0x00, 0x20, 0xC0, 0.0085f, 0x22, 0x00, 0x00, 0x00, 0x0014, 0x0028},
    {&cKF_bs_r_hrs_1, 0x28,   -1, 0xB8, 0.0115f, 0x2B, 0x02, 0x00, 0x00, 0x0017, 0x0032},
    {&cKF_bs_r_oct_1, 0x00,   -1, 0x50, 0.0093f, 0x23, 0x02, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_lon_1, 0x80, 0x60, 0xB8, 0.0114f, 0x2B, 0x00, 0x00, 0x00, 0x0014, 0x0032},
    {&cKF_bs_r_cbr_1, 0x80, 0x08, 0xB0, 0.0065f, 0x21, 0x00, 0x00, 0x00, 0x0014, 0x002D},
    {&cKF_bs_r_rhn_1, 0x48, 0x78, 0xA8, 0.011f, 0x25, 0x02, 0x00, 0x00, 0x0017, 0x0037},
    {&cKF_bs_r_gor_1, 0x50, 0x70, 0x98, 0.01f, 0x2A, 0x02, 0x00, 0x00, 0x0014, 0x0037},
    {&cKF_bs_r_ost_1, 0x38,   -1, 0xA0, 0.0115f, 0x2C, 0x02, 0x00, 0x00, 0x0014, 0x0032},
    {&cKF_bs_r_kgr_1, 0x58,   -1, 0x80, 0.0105f, 0x29, 0x02, 0x00, 0x00, 0x0017, 0x002D},
    {&cKF_bs_r_pbr_1, 0x28,   -1, 0x90, 0.013f, 0x2E, 0x02, 0x00, 0x00, 0x0017, 0x0037},
    {&cKF_bs_r_pgn_1, 0x30,   -1, 0x90, 0.0075f, 0x1F, 0x02, 0x00, 0x00, 0x0014, 0x0028},
};
