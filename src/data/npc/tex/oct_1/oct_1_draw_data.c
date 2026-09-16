#ifdef __INTELLISENSE__
#include "ac_npc.h"

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

static aNPC_draw_data_c oct_1_draw_data = {
#endif
    ACTOR_OBJ_BANK_284,
    ACTOR_OBJ_BANK_285,
    &cKF_bs_r_oct_1,
    {
        oct_1_tmem_txt,
        oct_1_pal,
        {
            oct_1_eye1_TA_tex_txt,
            oct_1_eye2_TA_tex_txt,
            oct_1_eye3_TA_tex_txt,
            oct_1_eye4_TA_tex_txt,
            oct_1_eye5_TA_tex_txt,
            oct_1_eye6_TA_tex_txt,
            oct_1_eye7_TA_tex_txt,
            oct_1_eye8_TA_tex_txt,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        0,
        0,
        80,
    },
    0.00930000003427267,
    2,
    0,
    26,
    35,
    0,
    0,
    176,
    20,
    45,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
