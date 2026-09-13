#include "m_board_ovl.h"

#include "m_common_data.h"
#include "m_editor_ovl.h"
#include "m_editEndChk_ovl.h"
#include "m_font.h"
#include "m_tag_ovl.h"
#include "m_text.h"
#include "libultra/libultra.h"
#include "_mem.h"
#include "sys_matrix.h"

static mBD_Ovl_c board_ovl_data;

extern Gfx lat_letter01_model[];
extern Gfx lat_letter02_model[];
extern Gfx lat_letter03_model[];
extern Gfx lat_letter04_model[];
extern Gfx lat_letter05_model[];
extern Gfx lat_letter06_model[];
extern Gfx lat_letter07_model[];
extern Gfx lat_letter08_model[];
extern Gfx lat_letter09_model[];
extern Gfx lat_letter10_model[];
extern Gfx lat_letter11_model[];
extern Gfx lat_letter12_model[];
extern Gfx lat_letter13_model[];
extern Gfx lat_letter14_model[];
extern Gfx lat_letter15_model[];
extern Gfx lat_letter16_model[];
extern Gfx lat_letter17_model[];
extern Gfx lat_letter18_model[];
extern Gfx lat_letter19_model[];
extern Gfx lat_letter20_model[];
extern Gfx lat_letter21_model[];
extern Gfx lat_letter22_model[];
extern Gfx lat_letter23_model[];
extern Gfx lat_letter24_model[];
extern Gfx lat_letter25_model[];
extern Gfx lat_letter26_model[];
extern Gfx lat_letter27_model[];
extern Gfx lat_letter28_model[];
extern Gfx lat_letter29_model[];
extern Gfx lat_letter30_model[];
extern Gfx lat_letter31_model[];
extern Gfx lat_letter32_model[];
extern Gfx lat_letter33_model[];
extern Gfx lat_letter34_model[];
extern Gfx lat_letter35_model[];
extern Gfx lat_letter36_model[];
extern Gfx lat_letter37_model[];
extern Gfx lat_letter38_model[];
extern Gfx lat_letter39_model[];
extern Gfx lat_letter40_model[];
extern Gfx lat_letter41_model[];
extern Gfx lat_letter42_model[];
extern Gfx lat_letter43_model[];
extern Gfx lat_letter44_model[];
extern Gfx lat_letter45_model[];
extern Gfx lat_letter46_model[];
extern Gfx lat_letter47_model[];
extern Gfx lat_letter48_model[];
extern Gfx lat_letter49_model[];
extern Gfx lat_letter50_model[];
extern Gfx lat_letter51_model[];
extern Gfx lat_letter52_model[];
extern Gfx lat_letter53_model[];
extern Gfx lat_letter54_model[];
extern Gfx lat_letter55_model[];
extern Gfx lat_letter56_model[];
extern Gfx lat_letter57_model[];
extern Gfx lat_letter58_model[];
extern Gfx lat_letter59_model[];
extern Gfx lat_letter60_model[];
extern Gfx lat_letter61_model[];
extern Gfx lat_letter62_model[];
extern Gfx lat_letter63_win_model[];
extern Gfx lat_letter64_model[];

static Gfx* paper_disp_model[PAPER_NUM] = { lat_letter01_model,
                                            lat_letter02_model,
                                            lat_letter03_model,
                                            lat_letter04_model,
                                            lat_letter05_model,
                                            lat_letter06_model,
                                            lat_letter07_model,
                                            lat_letter08_model,
                                            lat_letter09_model,
                                            lat_letter10_model,
                                            lat_letter11_model,
                                            lat_letter12_model,
                                            lat_letter13_model,
                                            lat_letter14_model,
                                            lat_letter15_model,
                                            lat_letter16_model,
                                            lat_letter17_model,
                                            lat_letter18_model,
                                            lat_letter19_model,
                                            lat_letter20_model,
                                            lat_letter21_model,
                                            lat_letter22_model,
                                            lat_letter23_model,
                                            lat_letter24_model,
                                            lat_letter25_model,
                                            lat_letter26_model,
                                            lat_letter27_model,
                                            lat_letter28_model,
                                            lat_letter29_model,
                                            lat_letter30_model,
                                            lat_letter31_model,
                                            lat_letter32_model,
                                            lat_letter33_model,
                                            lat_letter34_model,
                                            lat_letter35_model,
                                            lat_letter36_model,
                                            lat_letter37_model,
                                            lat_letter38_model,
                                            lat_letter39_model,
                                            lat_letter40_model,
                                            lat_letter41_model,
                                            lat_letter42_model,
                                            lat_letter43_model,
                                            lat_letter44_model,
                                            lat_letter45_model,
                                            lat_letter46_model,
                                            lat_letter47_model,
                                            lat_letter48_model,
                                            lat_letter49_model,
                                            lat_letter50_model,
                                            lat_letter51_model,
                                            lat_letter52_model,
                                            lat_letter53_model,
                                            lat_letter54_model,
                                            lat_letter55_model,
                                            lat_letter56_model,
                                            lat_letter57_model,
                                            lat_letter58_model,
                                            lat_letter59_model,
                                            lat_letter60_model,
                                            lat_letter61_model,
                                            lat_letter62_model,
                                            lat_letter63_win_model,
                                            lat_letter64_model,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL,
                                            NULL };

extern Gfx lat_letter01_sen_model[];
extern Gfx lat_letter02_sen_model[];
extern Gfx lat_letter03_sen_model[];
extern Gfx lat_letter04_senT_model[];
extern Gfx lat_letter06_sen_model[];
extern Gfx lat_letter07_sen_model[];
extern Gfx lat_letter08_sen_model[];
extern Gfx lat_letter10_sen_model[];
extern Gfx lat_letter12_sen_model[];
extern Gfx lat_letter16_sen_model[];
extern Gfx lat_letter17_sen_model[];
extern Gfx lat_letter18_sen_model[];
extern Gfx lat_letter20_sen_model[];
extern Gfx lat_letter21_sen_model[];
extern Gfx lat_letter22_sen_model[];
extern Gfx lat_letter29_sen_model[];
extern Gfx lat_letter30_sen_model[];
extern Gfx lat_letter31_sen_model[];
extern Gfx lat_letter32_sen_model[];
extern Gfx lat_letter33_sen_model[];
extern Gfx lat_letter34_sen_model[];
extern Gfx lat_letter35_sen_model[];
extern Gfx lat_letter36_sen_model[];
extern Gfx lat_letter37_sen_model[];
extern Gfx lat_letter38_sen_model[];
extern Gfx lat_letter39_sen_model[];
extern Gfx lat_letter40_sen_model[];
extern Gfx lat_letter41_sen_model[];
extern Gfx lat_letter42_sen_model[];
extern Gfx lat_letter43_sen_model[];
extern Gfx lat_letter44_sen_model[];
extern Gfx lat_letter45_sen_model[];
extern Gfx lat_letter46_sen_model[];
extern Gfx lat_letter47_sen_model[];
extern Gfx lat_letter48_sen_model[];
extern Gfx lat_letter49_sen_model[];
extern Gfx lat_letter50_sen_model[];
extern Gfx lat_letter51_sen_model[];
extern Gfx lat_letter52_sen_model[];
extern Gfx lat_letter53_sen_model[];
extern Gfx lat_letter54_sen_model[];
extern Gfx lat_letter55_sen_model[];
extern Gfx lat_letter56_sen_model[];
extern Gfx lat_letter57_sen_model[];
extern Gfx lat_letter58_sen_model[];
extern Gfx lat_letter59_sen_model[];
extern Gfx lat_letter60_sen_model[];
extern Gfx lat_letter61_sen_model[];
extern Gfx lat_letter62_sen_model[];
extern Gfx lat_letter63_senT_model[];
extern Gfx lat_letter64_sen_model[];

static Gfx* paper_disp_sen_model[PAPER_NUM] = { lat_letter01_sen_model,
                                                lat_letter02_sen_model,
                                                lat_letter03_sen_model,
                                                lat_letter04_senT_model,
                                                NULL,
                                                lat_letter06_sen_model,
                                                lat_letter07_sen_model,
                                                lat_letter08_sen_model,
                                                NULL,
                                                lat_letter10_sen_model,
                                                NULL,
                                                lat_letter12_sen_model,
                                                NULL,
                                                NULL,
                                                NULL,
                                                lat_letter16_sen_model,
                                                lat_letter17_sen_model,
                                                lat_letter18_sen_model,
                                                NULL,
                                                lat_letter20_sen_model,
                                                lat_letter21_sen_model,
                                                lat_letter22_sen_model,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                lat_letter29_sen_model,
                                                lat_letter30_sen_model,
                                                lat_letter31_sen_model,
                                                lat_letter32_sen_model,
                                                lat_letter33_sen_model,
                                                lat_letter34_sen_model,
                                                lat_letter35_sen_model,
                                                lat_letter36_sen_model,
                                                lat_letter37_sen_model,
                                                lat_letter38_sen_model,
                                                lat_letter39_sen_model,
                                                lat_letter40_sen_model,
                                                lat_letter41_sen_model,
                                                lat_letter42_sen_model,
                                                lat_letter43_sen_model,
                                                lat_letter44_sen_model,
                                                lat_letter45_sen_model,
                                                lat_letter46_sen_model,
                                                lat_letter47_sen_model,
                                                lat_letter48_sen_model,
                                                lat_letter49_sen_model,
                                                lat_letter50_sen_model,
                                                lat_letter51_sen_model,
                                                lat_letter52_sen_model,
                                                lat_letter53_sen_model,
                                                lat_letter54_sen_model,
                                                lat_letter55_sen_model,
                                                lat_letter56_sen_model,
                                                lat_letter57_sen_model,
                                                lat_letter58_sen_model,
                                                lat_letter59_sen_model,
                                                lat_letter60_sen_model,
                                                lat_letter61_sen_model,
                                                lat_letter62_sen_model,
                                                lat_letter63_senT_model,
                                                lat_letter64_sen_model,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL };

static rgba_t letter_color[PAPER_NUM] = {
    { 70, 40, 50, 255 },    { 40, 40, 130, 255 },   { 90, 30, 30, 255 },    { 75, 115, 215, 255 },
    { 90, 70, 20, 255 },    { 110, 60, 0, 255 },    { 95, 25, 0, 255 },     { 255, 255, 255, 255 },
    { 0, 100, 120, 255 },   { 40, 85, 0, 255 },     { 0, 40, 135, 255 },    { 155, 50, 60, 255 },
    { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 90, 90, 90, 255 },    { 0, 10, 130, 255 },
    { 200, 255, 235, 255 }, { 70, 45, 30, 255 },    { 105, 65, 160, 255 },  { 65, 60, 0, 255 },
    { 60, 0, 90, 255 },     { 85, 85, 85, 255 },    { 255, 180, 0, 255 },   { 85, 55, 0, 255 },
    { 95, 75, 10, 255 },    { 120, 120, 120, 255 }, { 255, 255, 105, 255 }, { 109, 83, 21, 255 },
    { 0, 155, 0, 255 },     { 100, 130, 185, 255 }, { 0, 100, 0, 255 },     { 90, 100, 0, 255 },
    { 160, 0, 0, 255 },     { 115, 60, 0, 255 },    { 255, 185, 0, 255 },   { 255, 255, 205, 255 },
    { 0, 0, 100, 255 },     { 0, 100, 155, 255 },   { 0, 100, 205, 255 },   { 165, 20, 0, 255 },
    { 155, 40, 40, 255 },   { 0, 80, 135, 255 },    { 0, 20, 90, 255 },     { 100, 100, 155, 255 },
    { 0, 80, 5, 255 },      { 95, 70, 0, 255 },     { 100, 140, 100, 255 }, { 255, 255, 255, 255 },
    { 100, 110, 100, 255 }, { 80, 70, 0, 255 },     { 50, 155, 0, 255 },    { 0, 95, 175, 255 },
    { 0, 50, 90, 255 },     { 0, 60, 205, 255 },    { 0, 100, 0, 255 },     { 0, 80, 80, 255 },
    { 0, 115, 60, 255 },    { 100, 80, 100, 255 },  { 255, 255, 200, 255 }, { 90, 60, 0, 255 },
    { 55, 125, 0, 255 },    { 0, 155, 0, 255 },     { 70, 50, 235, 255 },   { 255, 255, 255, 255 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 },         { 0, 0, 0, 0 }
};

static void mMlW_clear_buf(u16* buf, int size, u16 clear_char) {
    while (--size >= 0) {
        *buf++ = clear_char;
    }
}

static void mMlW_clear_mail(MailW_c* mail) {
    bzero(mail, sizeof(MailW_c));
    mMl_clear_mail_header(&mail->header);
    mMlW_clear_buf(mail->content.text.all, MAIL_HEADER_LEN + MAIL_BODY_LEN + MAIL_FOOTER_LEN, CHAR_SPACE);
    mail->content.font = 0xFF;
}

static void mMlW_set_playername_edit(MailW_c* mail, PersonalID_c* pid) {
    mPr_CopyPersonalID(&mail->header.sender.personalID, pid);
    mail->header.sender.type = mMl_NAME_TYPE_PLAYER;
}

static void mMlW_init_mail(MailW_c* mail, PersonalID_c* pid) {
    mMlW_clear_mail(mail);
    mMlW_set_playername_edit(mail, pid);
    mail->content.font = mMl_FONT_SEND;
    mail->content.mail_type = mMl_TYPE_MAIL;
    mail->content.paper_type = 0;
}

static int mMlW_strlen(u16* str, int size, u16 end_char) {
    u16* p = str + (size - 1);
    int i = size;
    while (i != 0) {
        if (*p != end_char)
            return size;
        p--;
        size--;
        i--;
    }
    return 0;
}

static void mMl_conv_MlP2MlW(Mail_c* src, MailW_c* dst) {
    memcpy(&dst->header, &src->header, sizeof(Mail_hdr_c));
    dst->present = src->present;
    dst->content.font = src->content.font;
    dst->content.header_back_start = src->content.header_back_start;
    dst->content.mail_type = src->content.mail_type;
    dst->content.paper_type = src->content.paper_type;
    mTxt_conv_16bit(src->content.text.split.header, dst->content.text.split.header, MAIL_HEADER_LEN);
    mTxt_conv_16bit(src->content.text.split.body, dst->content.text.split.body, MAIL_BODY_LEN);
    mTxt_conv_16bit(src->content.text.split.footer, dst->content.text.split.footer, MAIL_FOOTER_LEN);
}

static void mMl_conv_MlW2MlP(MailW_c* src, Mail_c* dst) {
    memcpy(&dst->header, &src->header, sizeof(Mail_hdr_c));
    dst->present = src->present;
    dst->content.font = src->content.font;
    dst->content.header_back_start = src->content.header_back_start;
    dst->content.mail_type = src->content.mail_type;
    dst->content.paper_type = src->content.paper_type;
    mTxt_conv_9or8bit(src->content.text.split.header, dst->content.text.split.header, MAIL_HEADER_LEN);
    mTxt_conv_9or8bit(src->content.text.split.body, dst->content.text.split.body, MAIL_BODY_LEN);
    mTxt_conv_9or8bit(src->content.text.split.footer, dst->content.text.split.footer, MAIL_FOOTER_LEN);
}

static void mBD_chrCopyOneByteTwoByte(u16* dst, u8* src, int len) {
    for (; len > 0; len--)
        *dst++ = *src++;
}

static int mBD_strLineCheck(u16** str_pp, u16* str_end_p, int* width, int* line) {
    u16* str_p = *str_pp;
    int res = mBD_LINE_CHECK_OK;
    if (str_p >= str_end_p) {
        res = mBD_LINE_CHECK_OVERSTRING;
    } else {
        *width += mFont_GetCodeWidthWF(**str_pp, TRUE);
        if (*width > mBD_MAX_WIDTH) {
            res = mBD_LINE_CHECK_OVERLINE;
        } else {
            if (**str_pp == CHAR_NEW_LINE)
                res = mBD_LINE_CHECK_NEWLINE;
            (*str_pp)++;
            (*line)++;
        }
    }
    return res;
}

static void mBD_roll_control(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;

    if (editor_ovl != NULL) {
        int line;
        int dist;
        f32 pos;
        f32 pos_dist;
        f32 abs_pos_dist;

        if (board_ovl->field == mBD_FIELD_BODY) {
            line = editor_ovl->cursor_row + 2;
        } else if (board_ovl->field == mBD_FIELD_HEADER) {
            line = 0;
        } else {
            line = 9;
        }

        /* Calculate if we need to move the center of the display to the selected line */
        dist = line - board_ovl->center_line;
        if (dist < -2) {
            board_ovl->center_line = line + 2;
            menu_info->speed[1] = 1.0f;
        } else if (dist > 2) {
            board_ovl->center_line = line - 2;
            menu_info->speed[1] = 1.0f;
        }

        pos = (f32)((board_ovl->center_line - 2) * 16);
        pos_dist = pos - menu_info->position[1];
        abs_pos_dist = fabsf(pos_dist);

        if (abs_pos_dist > 0.1f) {
            /* Interpolate to final position */
            if (abs_pos_dist > 9.0f) {
                menu_info->speed[1] *= 2.0f;

                if (menu_info->speed[1] > 4.0f) {
                    menu_info->speed[1] = 4.0f;
                }
            } else if (abs_pos_dist < 7.0f) {
                menu_info->speed[1] *= 0.5f;

                if (menu_info->speed[1] < 1.0f) {
                    menu_info->speed[1] = 1.0f;
                }
            }

            chase_f(&menu_info->position[1], pos, menu_info->speed[1]);
        } else {
            /* Close enough so immediately move to final position */
            menu_info->position[1] = pos;
        }
    }
}

static void mBD_roll_control2(mSM_MenuInfo_c* menu_info) {
    f32 next_pos = menu_info->position[1] - menu_info->speed[1];

    if (menu_info->speed[1] < 1.0f) {
        menu_info->speed[1] = 1.0f;
    }

    if (next_pos > 0.0f) {
        menu_info->position[1] = next_pos;

        if (next_pos > -15.0f) {
            /* Speed up if the position is greater than -15 */

            /* -15 is a weird choice because we're supposed to slow down
                after passing 31... */
            menu_info->speed[1] *= 2.0f;

            if (menu_info->speed[1] > 16.0f) {
                menu_info->speed[1] = 16.0f;
            }
        } else if (next_pos < 31.0f) {
            /* Slow down speed exponentially as we approach the top */
            menu_info->speed[1] *= 0.5f;

            if (menu_info->speed[1] < 1.0f) {
                menu_info->speed[1] = 1.0f;
            }
        }
    } else {
        /* Clamp Y position to 0.0f */
        menu_info->position[1] = 0.0f;
        menu_info->speed[1] = 0.0f;
    }
}

static void mBD_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mBD_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if ((getTrigger() & (BUTTON_A | BUTTON_B | BUTTON_START))) {
        (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
        sAdo_SysTrgStart(0x5F);
    }
}

static void mBD_end_board(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* address_menu = &submenu->overlay->menu_info[mSM_OVL_ADDRESS];

    (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
    (*submenu->overlay->return_func_proc)(submenu, address_menu);
}

static void mBD_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* editor_menu = &submenu->overlay->menu_info[mSM_OVL_EDITOR];

    if (editor_menu->next_proc_status == mSM_OVL_PROC_END) {
        menu_info->proc_status = mSM_OVL_PROC_OBEY;
        submenu->overlay->board_ovl->center_line = 2;
        mSM_open_submenu(submenu, mSM_OVL_EDITENDCHK, mEE_TYPE_BOARD, 0);
    } else {
        mBD_roll_control(submenu, menu_info);
    }
}

static void mBD_move_Obey(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* editEndChk_menu = &submenu->overlay->menu_info[mSM_OVL_EDITENDCHK];
    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;
    mED_Ovl_c* editor_ovl;
    int footer_len;
    Mail_hs_c* mail_header;
    int footer_len_diff;
    int t_footer_len;
    u16 t_footer[MAIL_FOOTER_LEN];
    u16* footer_p;
    u16* t_footer_p;
    int i;

    mBD_roll_control2(menu_info);

    if (editEndChk_menu->proc_status == mSM_OVL_PROC_MOVE && editEndChk_menu->next_proc_status == mSM_OVL_PROC_END) {
        editor_ovl = submenu->overlay->editor_ovl;

        /* Did they select the 'yes' option? */
        if (editEndChk_menu->data1 == 0) {
            mail_header = &Common_Get(now_private)->saved_mail_header;
            footer_p = board_ovl->mail.content.text.split.footer;
            t_footer_p = footer_p;
            footer_len = mMlW_strlen(footer_p, MAIL_FOOTER_LEN, CHAR_SPACE);
            footer_len_diff = board_ovl->lengths[mBD_FIELD_FOOTER] - footer_len;
            t_footer_len = 0;

            for (i = 0; i < footer_len; i++) {
                if (*t_footer_p != CHAR_SPACE) {
                    break;
                }

                t_footer_len++;
                t_footer_p++;
            }

            mFont_ClearStringsW(t_footer, MAIL_FOOTER_LEN, CHAR_SPACE);

            /* Check if we should copy part of the old footer back */
            if (footer_len_diff < MAIL_FOOTER_LEN) {
                mFont_CopyStringsW(t_footer + footer_len_diff, t_footer_p, footer_len - t_footer_len);
            }

            mFont_CopyStringsW(footer_p, t_footer, MAIL_FOOTER_LEN);
            mMl_conv_MlW2MlP(&board_ovl->mail, board_ovl->dst_p);

            if (menu_info->data0 != mSM_BD_OPEN_WRITE_ISLAND && menu_info->data0 != mSM_BD_OPEN_WRITE_BIRTHDAY) {
                mail_header->header_back_start = board_ovl->mail.content.header_back_start;
                mFont_CopyStringsW(mail_header->header, board_ovl->mail.content.text.split.header, MAIL_HEADER_LEN);
                mFont_CopyStringsW(mail_header->footer, board_ovl->mail.content.text.split.footer, MAIL_FOOTER_LEN);
            }

            /* Decrement stationery count */
            if (menu_info->data1 != -1) {
                int paper_tmp = Common_Get(now_private)->inventory.pockets[menu_info->data1] - ITM_PAPER_START;
                int paper_num = (paper_tmp / PAPER_UNIQUE_NUM) + 1;
                int paper_no = paper_tmp % PAPER_UNIQUE_NUM;

                if (paper_num > 1) {
                    mPr_SetPossessionItem(Common_Get(now_private), menu_info->data1,
                                          ITM_PAPER_START + paper_no + (paper_num - 2) * PAPER_UNIQUE_NUM,
                                          mPr_ITEM_COND_NORMAL);
                } else {
                    mPr_SetPossessionItem(Common_Get(now_private), menu_info->data1, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                }

                (*submenu->overlay->tag_ovl->init_tag_data_item_win_proc)(submenu);
            }

            mBD_end_board(submenu, menu_info);
        } else if (editEndChk_menu->data1 == 1) {
            /* 'No' option was selected */
            mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_BOARD, 0, board_ovl->mail.content.text.split.body,
                                  sizeof(board_ovl->mail.content.text.split.body));
            board_ovl->field = mBD_FIELD_BODY;
            board_ovl->header_pos = mBD_HEADER_POS_PRE_NAME;
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
        } else {
            /* 'Cancel' option was selected */
            mBD_end_board(submenu, menu_info);
        }

        if (editor_ovl != NULL) {
            editor_ovl->cursor_idx = 0;
            editor_ovl->cursor_col = 0;
            editor_ovl->cursor_row = 0;
        }
    }
}

static void mBD_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

typedef void (*mBD_OVL_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mBD_board_ovl_move(Submenu* submenu) {
    static mBD_OVL_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = { &mBD_move_Move, &mBD_move_Play, &mBD_move_Wait,
                                                                 &mBD_move_Obey, &mBD_move_End };

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_BOARD];

    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx lat_letter_mode[];
extern Gfx lat_letter_sen_mode[];

static void mBD_set_frame_dl(GRAPH* graph, mSM_MenuInfo_c* menu_info, f32 x, f32 y, mBD_Ovl_c* board_ovl) {
    int paper_type = board_ovl->mail.content.paper_type;
    Gfx* gfx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 140.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    /* Draw paper background */
    gSPDisplayList(gfx++, lat_letter_mode);
    gSPDisplayList(gfx++, paper_disp_model[paper_type]);

    /* Draw extra Gfx if necessary */
    if (paper_disp_sen_model[paper_type] != NULL) {
        gSPDisplayList(gfx++, lat_letter_sen_mode);
        gSPDisplayList(gfx++, paper_disp_sen_model[paper_type]);
    }

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Gfx win_b_mes_model[];

static void mBD_set_frame_dl_Bday_mes(GRAPH* graph, mSM_MenuInfo_c* menu_info, f32 x, f32 y, mBD_Ovl_c* board_ovl) {
    Gfx* gfx;
    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(x, y, 140.0f, MTX_MULT);
    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, win_b_mes_model);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

extern Gfx lat_point_mT_model[];
extern Gfx lat_hani_senT_model[];

static void mBD_set_point(Submenu* submenu, GAME* game, f32 x, f32 y) {
    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;
    GRAPH* graph = game->graph;
    Gfx* gfx;

    board_ovl->ofs_x = x + (board_ovl->mail.content.header_back_start + 3) * 12.0f + -96.0f;
    board_ovl->ofs_y = y - -76.0f;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(board_ovl->ofs_x, board_ovl->ofs_y, 140.0f, MTX_MULT);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, lat_letter_mode);
    gSPDisplayList(gfx++, lat_point_mT_model);
    gSPDisplayList(gfx++, lat_hani_senT_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}

static void mBD_set_cursol(Submenu* submenu, GAME* game, f32 x, f32 y) {
    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;

    if (board_ovl->header_pos == mBD_HEADER_POS_ON_NAME) {
        mBD_set_point(submenu, game, x, y);
    } else {
        mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
        f32 ofs_x;
        f32 line;
        f32 ofs_y;

        switch (board_ovl->field) {
            case mBD_FIELD_HEADER: {
                int ox = 0;

                if (board_ovl->header_pos == mBD_HEADER_POS_POST_NAME) {
                    ox = PLAYER_NAME_LEN * 12;
                }

                ofs_x = (f32)editor_ovl->cursor_line_width + (f32)ox + -7.0f;
                line = 0.0f;
                ofs_y = 0.0f;
                break;
            }

            case mBD_FIELD_BODY: {
                ofs_x = (f32)editor_ovl->cursor_line_width + -7.0f;
                ofs_y = 12.0f;
                line = editor_ovl->cursor_row + 1;
                break;
            }

            default: {
                int width = mFont_GetStringWidthW(board_ovl->mail.content.text.split.footer,
                                                  board_ovl->lengths[mBD_FIELD_FOOTER], TRUE);

                ofs_x = 192.0f;
                ofs_x -= width;
                ofs_x += editor_ovl->cursor_line_width + -7.0f;
                line = 7.0f;
                ofs_y = 24.0f;
                break;
            }
        }

        (*submenu->overlay->editor_ovl->cursol_draw)(submenu, game, 64.0f + x + ofs_x,
                                                     36.0f - ((y - line * 16.0f) - ofs_y));
    }
}

static void mBD_set_writing_footer(Submenu* submenu, GAME* game, f32 x, f32 y, rgba_t* color) {
    int footer_len = submenu->overlay->board_ovl->lengths[mBD_FIELD_FOOTER];
    x += (MAIL_FOOTER_LEN - footer_len) * 12.0f;
    mFont_SetLineStringsW(game, submenu->overlay->board_ovl->mail.content.text.split.footer, footer_len, x, y, color->r,
                          color->g, color->b, 255, FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
}

static void mBD_set_writing_body(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game, f32 x, f32* y, f32* end_x,
                                 f32* end_y, rgba_t* color) {
    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;
    u16* str = board_ovl->mail.content.text.split.body;
    u16* str_p;
    u16* str_end_p = str + board_ovl->lengths[mBD_FIELD_BODY];
    int body_len;
    int i;
    int width = 0;
    int line = 0;
    int line_ret;

    for (i = 0; i < mBD_BODY_LINE_NUM; i++) {
        width = 0;
        line = 0;

        str_p = str;
        do {
            line_ret = mBD_strLineCheck(&str, str_end_p, &width, &line);

            if (line_ret == mBD_LINE_CHECK_OVERSTRING) {
                if (i != (mBD_BODY_LINE_NUM - 1) && ((str != str_p && str[-1] == CHAR_NEW_LINE) ||
                                                     width + mFont_GetCodeWidthW(*str, TRUE) > mBD_MAX_WIDTH)) {
                    (*end_x) = (x + 1.0f) - 160.0f;
                    (*end_y) = -(*y + 16.0f) + 120.0f;
                } else {
                    (*end_x) = (x + (f32)width + 1.0f) - 160.0f;
                    (*end_y) = -(*y) + 120.0f;
                }

                if (menu_info->proc_status != mSM_OVL_PROC_PLAY && str[-1] == CHAR_NEW_LINE) {
                    line--;
                }

                if (line != 0) {
                    mFont_SetLineStringsW(game, str_p, line, x, *y, color->r, color->g, color->b, 255, FALSE, TRUE,
                                          1.0f, 1.0f, mFont_MODE_POLY);
                }

                (*y) += (f32)(mBD_BODY_LINE_NUM - i) * 16.0f;
                return;
            }
        } while (line_ret == mBD_LINE_CHECK_OK);

        if (line_ret == mBD_LINE_CHECK_NEWLINE && menu_info->proc_status != mSM_OVL_PROC_PLAY) {
            line--;
        }

        if (line != 0) {
            mFont_SetLineStringsW(game, str_p, line, x, *y, color->r, color->g, color->b, 255, FALSE, TRUE, 1.0f, 1.0f,
                                  mFont_MODE_POLY);
        }

        (*y) += 16.0f;
    }
}

static void mBD_set_writing_header(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info, f32 x, f32 y,
                                   rgba_t* color) {
    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;
    MailW_ct_c* mail_content = &board_ovl->mail.content;
    u8* header_back_start_p = &mail_content->header_back_start;
    int len;

    if (menu_info->proc_status == mSM_OVL_PROC_PLAY) {
        if (menu_info->data0 == mSM_BD_OPEN_WRITE_ISLAND || menu_info->data0 == mSM_BD_OPEN_WRITE_BIRTHDAY) {
            mFont_SetLineStringsW(game, mail_content->text.split.header, board_ovl->lengths[mBD_FIELD_HEADER], x, y,
                                  color->r, color->g, color->b, 255, FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
        } else {
            if (board_ovl->field == mBD_FIELD_HEADER) {
                len = PLAYER_NAME_LEN;
            } else {
                len = board_ovl->header_name_len;
            }

            mFont_SetLineStringsW(game, mail_content->text.split.header, *header_back_start_p, x, y, color->r, color->g,
                                  color->b, 255, FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);

            x += *header_back_start_p * 12.0f;
            mFont_SetLineStrings(game, board_ovl->mail.header.recipient.personalID.player_name, len, x, y, 185, 0, 0,
                                 255, FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);

            if (mail_content->header_back_start < MAIL_HEADER_LEN) {
                x += len * 12.0f;
                mFont_SetLineStringsW(game, &mail_content->text.split.header[mail_content->header_back_start],
                                      board_ovl->lengths[mBD_FIELD_HEADER] - mail_content->header_back_start, x, y,
                                      color->r, color->g, color->b, 255, FALSE, FALSE, 1.0f, 1.0f, mFont_MODE_POLY);
            }
        }
    } else {
        u16 tmp_header[MAIL_HEADER_LEN + PLAYER_NAME_LEN];

        if (menu_info->data0 == mSM_BD_OPEN_WRITE_ISLAND || menu_info->data0 == mSM_BD_OPEN_READ_ISLAND ||
            menu_info->data0 == mSM_BD_OPEN_WRITE_BIRTHDAY) {
            mFont_CopyStringsW(tmp_header, mail_content->text.split.header, board_ovl->lengths[mBD_FIELD_HEADER]);
            len = board_ovl->lengths[mBD_FIELD_HEADER];
        } else if (mail_content->mail_type == mMl_TYPE_SHOP_SALE_LEAFLET ||
                   mail_content->mail_type == mMl_TYPE_BROKER_SALE_LEAFLET ||
                   mail_content->mail_type == mMl_TYPE_OMIKUJI) {
            mFont_CopyStringsW(tmp_header, mail_content->text.split.header, MAIL_HEADER_LEN);
            len = MAIL_HEADER_LEN;
        } else {
            mFont_CopyStringsW(tmp_header, mail_content->text.split.header, mail_content->header_back_start);
            mBD_chrCopyOneByteTwoByte(&tmp_header[mail_content->header_back_start],
                                      board_ovl->mail.header.recipient.personalID.player_name,
                                      board_ovl->header_name_len);

            if (mail_content->header_back_start < MAIL_HEADER_LEN) {
                mFont_CopyStringsW(&tmp_header[board_ovl->header_name_len + mail_content->header_back_start],
                                   &mail_content->text.split.header[mail_content->header_back_start],
                                   board_ovl->lengths[mBD_FIELD_HEADER] - mail_content->header_back_start);
            }

            len = board_ovl->header_name_len + board_ovl->lengths[mBD_FIELD_HEADER];
        }

        mFont_SetLineStringsW(game, tmp_header, len, x, y, color->r, color->g, color->b, 255, FALSE, FALSE, 1.0f, 1.0f,
                              mFont_MODE_POLY);
    }
}

static void mBD_set_character(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info, f32 x, f32 y) {
    static rgba_t bday_color = { 90, 90, 110, 255 };
    rgba_t* color;
    f32 b_x;
    f32 b_y;
    f32 end_x;
    f32 end_y;

    if (menu_info->data0 == mSM_BD_OPEN_WRITE_BIRTHDAY) {
        color = &bday_color;
    } else {
        color = &letter_color[submenu->overlay->board_ovl->mail.content.paper_type];
    }

    b_x = x + 64.0f;
    b_y = -y + 36.0f;
    mBD_set_writing_header(submenu, game, menu_info, b_x, b_y, color);

    b_y += 28.0f;
    end_x = b_x - 160.0f;
    end_y = -b_y + 120.0f;
    mBD_set_writing_body(submenu, menu_info, game, b_x, &b_y, &end_x, &end_y, color);
    b_y += 12.0f;
    mBD_set_writing_footer(submenu, game, b_x, b_y, color);

    if (menu_info->proc_status == mSM_OVL_PROC_PLAY && submenu->overlay->editor_ovl != NULL) {
        mBD_set_cursol(submenu, game, x, y);
        (*submenu->overlay->editor_ovl->end_code_draw)(submenu, game, end_x, end_y);
    }
}

static void mBD_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    GRAPH* graph = game->graph;
    f32 x = menu_info->position[0];
    f32 y = menu_info->position[1];

    if (menu_info->data0 == mSM_BD_OPEN_WRITE_BIRTHDAY) {
        mBD_set_frame_dl_Bday_mes(graph, menu_info, x, y, submenu->overlay->board_ovl);
        (*submenu->overlay->set_char_matrix_proc)(graph);
        mBD_set_character(submenu, game, menu_info, x, y);
    } else {
        mBD_set_frame_dl(graph, menu_info, x, y, submenu->overlay->board_ovl);

        if (menu_info->data0 == mSM_BD_OPEN_READ || menu_info->data0 == mSM_BD_OPEN_READ_ISLAND ||
            submenu->overlay->board_ovl->first == FALSE) {
            (*submenu->overlay->set_char_matrix_proc)(graph);
            mBD_set_character(submenu, game, menu_info, x, y);
        }
    }
}

static void mBD_board_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_BOARD];

    (*menu_info->pre_draw_func)(submenu, game);
    mBD_set_dl(submenu, game, menu_info);
}

extern void mBD_board_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* control = &submenu->overlay->menu_control;

    control->menu_move_func = &mBD_board_ovl_move;
    control->menu_draw_func = &mBD_board_ovl_draw;
}

static void mBD_board_ovl_init(Submenu* submenu) {
    static u8 header_str[3] = { 0x0A, 0xC3, 0x1C }; /* san e */
    static u8 footer_str[2] = { 0x60, 0x7C };       /* yori */
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_BOARD];
    mBD_Ovl_c* board_ovl = submenu->overlay->board_ovl;

    submenu->overlay->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->move_drt = mSM_MOVE_IN_TOP;

    board_ovl->field = mBD_FIELD_BODY;
    board_ovl->center_line = 2;
    board_ovl->header_pos = mBD_HEADER_POS_PRE_NAME;
    board_ovl->dst_p = (Mail_c*)menu_info->data2;

    if (menu_info->data0 == mSM_BD_OPEN_WRITE) {
        Mail_hs_c* mail_header = &Common_Get(now_private)->saved_mail_header;
        board_ovl->first = TRUE;
        menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
        mSM_open_submenu_new2(submenu, mSM_OVL_ADDRESS, 0, 0, board_ovl->mail.content.text.split.body, mBD_MAX_WIDTH);
        mMlW_init_mail(&board_ovl->mail, &Common_Get(now_private)->player_ID);
        board_ovl->mail.content.paper_type =
            (Common_Get(now_private)->inventory.pockets[menu_info->data1] - ITM_PAPER_START) % PAPER_UNIQUE_NUM;

        if (mail_header->header_back_start == -1) {
            int name_len = mMl_strlen(Common_Get(now_private)->player_ID.player_name, PLAYER_NAME_LEN, CHAR_SPACE);

            mBD_chrCopyOneByteTwoByte(board_ovl->mail.content.text.split.header, header_str, sizeof(header_str));
            mBD_chrCopyOneByteTwoByte(board_ovl->mail.content.text.split.footer,
                                      Common_Get(now_private)->player_ID.player_name, name_len);
            mBD_chrCopyOneByteTwoByte(board_ovl->mail.content.text.split.footer + name_len, footer_str,
                                      sizeof(footer_str));
            board_ovl->mail.content.header_back_start = 0;
        } else {
            mFont_CopyStringsW(board_ovl->mail.content.text.split.header, mail_header->header, MAIL_HEADER_LEN);
            mFont_CopyStringsW(board_ovl->mail.content.text.split.footer, mail_header->footer, MAIL_FOOTER_LEN);
            board_ovl->mail.content.header_back_start = mail_header->header_back_start;
        }
    } else {
        mMl_conv_MlP2MlW((Mail_c*)menu_info->data2, &board_ovl->mail);

        if (menu_info->data0 == mSM_BD_OPEN_READ || menu_info->data0 == mSM_BD_OPEN_READ_ISLAND) {
            menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
        } else {
            menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
            mSM_open_submenu_new2(submenu, mSM_OVL_ADDRESS, 1, 0, board_ovl->mail.content.text.split.body,
                                  mBD_MAX_WIDTH);
        }

        board_ovl->first = FALSE;
        board_ovl->header_name_len =
            mMl_strlen(board_ovl->mail.header.recipient.personalID.player_name, PLAYER_NAME_LEN, CHAR_SPACE);
    }

    board_ovl->lengths[mBD_FIELD_HEADER] =
        mMlW_strlen(board_ovl->mail.content.text.split.header, MAIL_HEADER_LEN, CHAR_SPACE);
    board_ovl->lengths[mBD_FIELD_FOOTER] =
        mMlW_strlen(board_ovl->mail.content.text.split.footer, MAIL_FOOTER_LEN, CHAR_SPACE);
    board_ovl->lengths[mBD_FIELD_BODY] =
        mMlW_strlen(board_ovl->mail.content.text.split.body, MAIL_BODY_LEN, CHAR_SPACE);

    if (board_ovl->mail.content.header_back_start > MAIL_HEADER_LEN) {
        board_ovl->mail.content.header_back_start = MAIL_HEADER_LEN;
    }

    if (board_ovl->mail.content.header_back_start > board_ovl->lengths[mBD_FIELD_HEADER]) {
        board_ovl->lengths[mBD_FIELD_HEADER] = board_ovl->mail.content.header_back_start;
    }

    board_ovl->ofs_x = 0.0f;
    board_ovl->ofs_y = 76.0f;

    if (board_ovl->lengths[mBD_FIELD_FOOTER] != 0) {
        int i;
        int len;
        u16* tmp_footer_p;
        u16 tmp_footer[MAIL_FOOTER_LEN];

        /* Cut out any left padding spaces */
        tmp_footer_p = tmp_footer;
        mFont_CopyStringsW(tmp_footer_p, board_ovl->mail.content.text.split.footer, MAIL_FOOTER_LEN);
        len = board_ovl->lengths[mBD_FIELD_FOOTER];
        for (i = 0; len > 0; i++, len--, tmp_footer_p++) {
            if (*tmp_footer_p != CHAR_SPACE) {
                break;
            }
        }

        mMlW_clear_buf(board_ovl->mail.content.text.split.footer, MAIL_FOOTER_LEN, CHAR_SPACE);
        mFont_CopyStringsW(board_ovl->mail.content.text.split.footer, tmp_footer_p,
                           board_ovl->lengths[mBD_FIELD_FOOTER] - i);
    }
}

extern void mBD_board_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    if (overlay->board_ovl == NULL) {
        mem_clear((u8*)&board_ovl_data, sizeof(board_ovl_data), 0);
        overlay->board_ovl = &board_ovl_data;
    }

    mBD_board_ovl_init(submenu);
    mBD_board_ovl_set_proc(submenu);
}

extern void mBD_board_ovl_destruct(Submenu* submenu) {
    submenu->overlay->board_ovl = NULL;
}
