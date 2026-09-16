#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_brd_1;
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

static aNPC_draw_data_c brd_2_draw_data = {
#endif
    ACTOR_OBJ_BANK_113,
    ACTOR_OBJ_BANK_115,
    &cKF_bs_r_brd_1,
    {
        brd_2_tmem_txt,
        brd_2_pal,
        {
            brd_2_eye1_TA_tex_txt,
            brd_2_eye2_TA_tex_txt,
            brd_2_eye3_TA_tex_txt,
            brd_2_eye4_TA_tex_txt,
            brd_2_eye5_TA_tex_txt,
            brd_2_eye6_TA_tex_txt,
            brd_2_eye7_TA_tex_txt,
            brd_2_eye8_TA_tex_txt,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        8,
        0,
        144,
    },
    0.009499999694526196,
    2,
    1,
    0,
    35,
    0,
    0,
    125,
    20,
    45,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
