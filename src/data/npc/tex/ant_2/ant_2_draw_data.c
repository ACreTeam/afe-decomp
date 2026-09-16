#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_ant_1;
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

static aNPC_draw_data_c ant_2_draw_data = {
#endif
    ACTOR_OBJ_BANK_88,
    ACTOR_OBJ_BANK_90,
    &cKF_bs_r_ant_1,
    {
        ant_2_tmem_txt,
        ant_2_pal,
        {
            ant_2_eye1_TA_tex_txt,
            ant_2_eye2_TA_tex_txt,
            ant_2_eye3_TA_tex_txt,
            ant_2_eye4_TA_tex_txt,
            ant_2_eye5_TA_tex_txt,
            ant_2_eye6_TA_tex_txt,
            ant_2_eye7_TA_tex_txt,
            ant_2_eye8_TA_tex_txt,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        32,
        0,
        152,
    },
    0.010700000450015068,
    2,
    1,
    8,
    41,
    0,
    0,
    160,
    25,
    45,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
