#ifdef __INTELLISENSE__
#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_pga_1;
extern unsigned short pga_1_pal[];
extern unsigned char pga_1_eye1_TA_tex_txt[];
extern unsigned char pga_1_eye2_TA_tex_txt[];
extern unsigned char pga_1_eye3_TA_tex_txt[];
extern unsigned char pga_1_eye4_TA_tex_txt[];
extern unsigned char pga_1_eye5_TA_tex_txt[];
extern unsigned char pga_1_eye6_TA_tex_txt[];
extern unsigned char pga_1_eye7_TA_tex_txt[];
extern unsigned char pga_1_eye8_TA_tex_txt[];
extern unsigned char pga_1_tmem_txt[];

static aNPC_draw_data_c pga_1_draw_data = {
#endif
    ACTOR_OBJ_BANK_314,
    ACTOR_OBJ_BANK_315,
    &cKF_bs_r_pga_1,
    {
        pga_1_tmem_txt,
        pga_1_pal,
        {
            pga_1_eye1_TA_tex_txt,
            pga_1_eye2_TA_tex_txt,
            pga_1_eye3_TA_tex_txt,
            pga_1_eye4_TA_tex_txt,
            pga_1_eye5_TA_tex_txt,
            pga_1_eye6_TA_tex_txt,
            pga_1_eye7_TA_tex_txt,
            pga_1_eye8_TA_tex_txt,
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
        0,
    },
    0.00800000037997961,
    1,
    0,
    0,
    36,
    0,
    0,
    234,
    20,
    30,
    -1,
    -1,
#ifdef __INTELLISENSE__
};
#endif
