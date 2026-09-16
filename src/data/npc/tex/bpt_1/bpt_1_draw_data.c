#ifdef __INTELLISENSE__
#include "ac_npc.h"

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

static aNPC_draw_data_c bpt_1_draw_data = {
#endif
    ACTOR_OBJ_BANK_234,
    ACTOR_OBJ_BANK_235,
    &cKF_bs_r_bpt_1,
    {
        bpt_1_tmem_txt,
        bpt_1_pal,
        {
            bpt_1_eye1_TA_tex_txt,
            bpt_1_eye2_TA_tex_txt,
            bpt_1_eye3_TA_tex_txt,
            bpt_1_eye4_TA_tex_txt,
            bpt_1_eye5_TA_tex_txt,
            bpt_1_eye6_TA_tex_txt,
            bpt_1_eye7_TA_tex_txt,
            bpt_1_eye8_TA_tex_txt,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        12,
        0,
        0,
    },
    0.009499999694526196,
    1,
    0,
    0,
    40,
    0,
    0,
    228,
    20,
    50,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
