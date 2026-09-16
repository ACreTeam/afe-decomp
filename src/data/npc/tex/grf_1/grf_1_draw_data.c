#ifdef __INTELLISENSE__
#include "ac_npc.h"

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

static aNPC_draw_data_c grf_1_draw_data = {
#endif
    ACTOR_OBJ_BANK_180,
    ACTOR_OBJ_BANK_181,
    &cKF_bs_r_grf_1,
    {
        grf_1_tmem_txt,
        grf_1_pal,
        {
            grf_1_eye1_TA_tex_txt,
            grf_1_eye2_TA_tex_txt,
            grf_1_eye3_TA_tex_txt,
            grf_1_eye4_TA_tex_txt,
            grf_1_eye5_TA_tex_txt,
            grf_1_eye6_TA_tex_txt,
            grf_1_eye7_TA_tex_txt,
            grf_1_eye8_TA_tex_txt,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        68,
        0,
        0,
    },
    0.010999999940395355,
    1,
    0,
    0,
    35,
    0,
    0,
    226,
    20,
    65,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
