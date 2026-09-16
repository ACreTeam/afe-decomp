#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_ost_1;
extern unsigned short ost_4_pal[];
extern unsigned char ost_4_eye1_TA_tex_txt[];
extern unsigned char ost_4_eye2_TA_tex_txt[];
extern unsigned char ost_4_eye3_TA_tex_txt[];
extern unsigned char ost_4_eye4_TA_tex_txt[];
extern unsigned char ost_4_eye5_TA_tex_txt[];
extern unsigned char ost_4_eye6_TA_tex_txt[];
extern unsigned char ost_4_eye7_TA_tex_txt[];
extern unsigned char ost_4_eye8_TA_tex_txt[];
extern unsigned char ost_4_tmem_txt[];

static aNPC_draw_data_c ost_4_draw_data = {
#endif
    ACTOR_OBJ_BANK_286,
    ACTOR_OBJ_BANK_290,
    &cKF_bs_r_ost_1,
    {
        ost_4_tmem_txt,
        ost_4_pal,
        {
            ost_4_eye1_TA_tex_txt,
            ost_4_eye2_TA_tex_txt,
            ost_4_eye3_TA_tex_txt,
            ost_4_eye4_TA_tex_txt,
            ost_4_eye5_TA_tex_txt,
            ost_4_eye6_TA_tex_txt,
            ost_4_eye7_TA_tex_txt,
            ost_4_eye8_TA_tex_txt,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        56,
        0,
        160,
    },
    0.011500000022351742,
    2,
    3,
    9,
    44,
    0,
    0,
    200,
    20,
    50,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
