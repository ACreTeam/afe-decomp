#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_wol_1;
extern unsigned short wol_3_pal[];
extern unsigned char wol_3_eye1_TA_tex_txt[];
extern unsigned char wol_3_eye2_TA_tex_txt[];
extern unsigned char wol_3_eye3_TA_tex_txt[];
extern unsigned char wol_3_eye4_TA_tex_txt[];
extern unsigned char wol_3_eye5_TA_tex_txt[];
extern unsigned char wol_3_eye6_TA_tex_txt[];
extern unsigned char wol_3_eye7_TA_tex_txt[];
extern unsigned char wol_3_eye8_TA_tex_txt[];
extern unsigned char wol_3_tmem_txt[];

static aNPC_draw_data_c wol_3_draw_data = {
#endif
    ACTOR_OBJ_BANK_362,
    ACTOR_OBJ_BANK_365,
    &cKF_bs_r_wol_1,
    {
        wol_3_tmem_txt,
        wol_3_pal,
        {
            wol_3_eye1_TA_tex_txt,
            wol_3_eye2_TA_tex_txt,
            wol_3_eye3_TA_tex_txt,
            wol_3_eye4_TA_tex_txt,
            wol_3_eye5_TA_tex_txt,
            wol_3_eye6_TA_tex_txt,
            wol_3_eye7_TA_tex_txt,
            wol_3_eye8_TA_tex_txt,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        80,
        0,
        160,
    },
    0.009999999776482582,
    2,
    2,
    17,
    37,
    0,
    0,
    86,
    20,
    45,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
