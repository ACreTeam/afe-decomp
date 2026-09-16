#ifdef __INTELLISENSE__
#include "ac_npc.h"

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

static aNPC_draw_data_c ant_1_draw_data = {
#endif
    ACTOR_OBJ_BANK_88,
    ACTOR_OBJ_BANK_89,
    &cKF_bs_r_ant_1,
    {
        ant_1_tmem_txt,
        ant_1_pal,
        {
            ant_1_eye1_TA_tex_txt,
            ant_1_eye2_TA_tex_txt,
            ant_1_eye3_TA_tex_txt,
            ant_1_eye4_TA_tex_txt,
            ant_1_eye5_TA_tex_txt,
            ant_1_eye6_TA_tex_txt,
            ant_1_eye7_TA_tex_txt,
            ant_1_eye8_TA_tex_txt,
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
    0,
    27,
    41,
    0,
    0,
    159,
    25,
    45,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
