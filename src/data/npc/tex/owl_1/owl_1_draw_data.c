#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_owl_1;
extern unsigned short owl_1_pal[];
extern unsigned char owl_1_eye1_TA_tex_txt[];
extern unsigned char owl_1_eye2_TA_tex_txt[];
extern unsigned char owl_1_eye3_TA_tex_txt[];
extern unsigned char owl_1_eye4_TA_tex_txt[];
extern unsigned char owl_1_eye5_TA_tex_txt[];
extern unsigned char owl_1_eye6_TA_tex_txt[];
extern unsigned char owl_1_eye7_TA_tex_txt[];
extern unsigned char owl_1_eye8_TA_tex_txt[];
extern unsigned char owl_1_tmem_txt[];

static aNPC_draw_data_c owl_1_draw_data = {
#endif
    ACTOR_OBJ_BANK_401,
    ACTOR_OBJ_BANK_402,
    &cKF_bs_r_owl_1,
    {
        owl_1_tmem_txt,
        owl_1_pal,
        {
            owl_1_eye1_TA_tex_txt,
            owl_1_eye2_TA_tex_txt,
            owl_1_eye3_TA_tex_txt,
            owl_1_eye4_TA_tex_txt,
            owl_1_eye5_TA_tex_txt,
            owl_1_eye6_TA_tex_txt,
            owl_1_eye7_TA_tex_txt,
            owl_1_eye8_TA_tex_txt,
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
    0.009499999694526196,
    2,
    0,
    0,
    40,
    0,
    0,
    280,
    20,
    50,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
