#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_wol_1;
extern unsigned short wol_4_pal[];
extern unsigned char wol_4_eye1_TA_tex_txt[];
extern unsigned char wol_4_eye2_TA_tex_txt[];
extern unsigned char wol_4_eye3_TA_tex_txt[];
extern unsigned char wol_4_eye4_TA_tex_txt[];
extern unsigned char wol_4_eye5_TA_tex_txt[];
extern unsigned char wol_4_eye6_TA_tex_txt[];
extern unsigned char wol_4_eye7_TA_tex_txt[];
extern unsigned char wol_4_eye8_TA_tex_txt[];
extern unsigned char wol_4_tmem_txt[];

static aNPC_draw_data_c wol_4_draw_data = {
#endif
    ACTOR_OBJ_BANK_362,
    ACTOR_OBJ_BANK_366,
    &cKF_bs_r_wol_1,
    {
        wol_4_tmem_txt,
        wol_4_pal,
        {
            wol_4_eye1_TA_tex_txt,
            wol_4_eye2_TA_tex_txt,
            wol_4_eye3_TA_tex_txt,
            wol_4_eye4_TA_tex_txt,
            wol_4_eye5_TA_tex_txt,
            wol_4_eye6_TA_tex_txt,
            wol_4_eye7_TA_tex_txt,
            wol_4_eye8_TA_tex_txt,
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
    3,
    16,
    37,
    0,
    0,
    87,
    20,
    45,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
