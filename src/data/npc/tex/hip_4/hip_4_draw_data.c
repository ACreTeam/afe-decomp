#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_hip_1;
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

static aNPC_draw_data_c hip_4_draw_data = {
#endif
    ACTOR_OBJ_BANK_238,
    ACTOR_OBJ_BANK_242,
    &cKF_bs_r_hip_1,
    {
        hip_4_tmem_txt,
        hip_4_pal,
        {
            hip_4_eye1_TA_tex_txt,
            hip_4_eye2_TA_tex_txt,
            hip_4_eye3_TA_tex_txt,
            hip_4_eye4_TA_tex_txt,
            hip_4_eye5_TA_tex_txt,
            hip_4_eye6_TA_tex_txt,
            hip_4_eye7_TA_tex_txt,
            hip_4_eye8_TA_tex_txt,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        136,
        0,
        32,
    },
    0.007300000172108412,
    2,
    3,
    4,
    43,
    0,
    0,
    80,
    25,
    50,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
