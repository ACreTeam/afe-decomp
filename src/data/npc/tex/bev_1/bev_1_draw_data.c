#ifdef __INTELLISENSE__
#include "ac_npc.h"

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

static aNPC_draw_data_c bev_1_draw_data = {
#endif
    ACTOR_OBJ_BANK_86,
    ACTOR_OBJ_BANK_87,
    &cKF_bs_r_bev_1,
    {
        bev_1_tmem_txt,
        bev_1_pal,
        {
            bev_1_eye1_TA_tex_txt,
            bev_1_eye2_TA_tex_txt,
            bev_1_eye3_TA_tex_txt,
            bev_1_eye4_TA_tex_txt,
            bev_1_eye5_TA_tex_txt,
            bev_1_eye6_TA_tex_txt,
            bev_1_eye7_TA_tex_txt,
            bev_1_eye8_TA_tex_txt,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        40,
        0,
        0,
    },
    0.008999999612569809,
    1,
    0,
    0,
    39,
    0,
    0,
    238,
    20,
    45,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
