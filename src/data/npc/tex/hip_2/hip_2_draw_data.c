#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_hip_1;
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

static aNPC_draw_data_c hip_2_draw_data = {
#endif
    ACTOR_OBJ_BANK_238,
    ACTOR_OBJ_BANK_240,
    &cKF_bs_r_hip_1,
    {
        hip_2_tmem_txt,
        hip_2_pal,
        {
            hip_2_eye1_TA_tex_txt,
            hip_2_eye2_TA_tex_txt,
            hip_2_eye3_TA_tex_txt,
            hip_2_eye4_TA_tex_txt,
            hip_2_eye5_TA_tex_txt,
            hip_2_eye6_TA_tex_txt,
            hip_2_eye7_TA_tex_txt,
            hip_2_eye8_TA_tex_txt,
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
    1,
    8,
    43,
    0,
    0,
    78,
    25,
    50,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
