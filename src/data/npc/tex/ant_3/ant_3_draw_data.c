#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_ant_1;
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

static aNPC_draw_data_c ant_3_draw_data = {
#endif
    ACTOR_OBJ_BANK_88,
    ACTOR_OBJ_BANK_91,
    &cKF_bs_r_ant_1,
    {
        ant_3_tmem_txt,
        ant_3_pal,
        {
            ant_3_eye1_TA_tex_txt,
            ant_3_eye2_TA_tex_txt,
            ant_3_eye3_TA_tex_txt,
            ant_3_eye4_TA_tex_txt,
            ant_3_eye5_TA_tex_txt,
            ant_3_eye6_TA_tex_txt,
            ant_3_eye7_TA_tex_txt,
            ant_3_eye8_TA_tex_txt,
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
    2,
    17,
    41,
    0,
    0,
    161,
    25,
    45,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
