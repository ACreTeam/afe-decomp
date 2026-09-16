#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_ost_1;
extern unsigned short ost_2_pal[];
extern unsigned char ost_2_eye1_TA_tex_txt[];
extern unsigned char ost_2_eye2_TA_tex_txt[];
extern unsigned char ost_2_eye3_TA_tex_txt[];
extern unsigned char ost_2_eye4_TA_tex_txt[];
extern unsigned char ost_2_eye5_TA_tex_txt[];
extern unsigned char ost_2_eye6_TA_tex_txt[];
extern unsigned char ost_2_eye7_TA_tex_txt[];
extern unsigned char ost_2_eye8_TA_tex_txt[];
extern unsigned char ost_2_tmem_txt[];

static aNPC_draw_data_c ost_2_draw_data = {
#endif
    ACTOR_OBJ_BANK_286,
    ACTOR_OBJ_BANK_288,
    &cKF_bs_r_ost_1,
    {
        ost_2_tmem_txt,
        ost_2_pal,
        {
            ost_2_eye1_TA_tex_txt,
            ost_2_eye2_TA_tex_txt,
            ost_2_eye3_TA_tex_txt,
            ost_2_eye4_TA_tex_txt,
            ost_2_eye5_TA_tex_txt,
            ost_2_eye6_TA_tex_txt,
            ost_2_eye7_TA_tex_txt,
            ost_2_eye8_TA_tex_txt,
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
    1,
    31,
    44,
    0,
    0,
    198,
    20,
    50,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
