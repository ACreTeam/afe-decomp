#include "ac_monument.h"

#include "libforest/osreport.h"
#include "m_field_info.h"
#include "m_kankyo.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_time.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include <dolphin/os.h>

enum {
    aMNM_DRAW_TYPE_WITH_ANIME,
    aMNM_DRAW_TYPE_ONLY_MODEL,

    aMNM_DRAW_TYPE_NUM
};

enum {
    aMNM_DRAW_WITH_ANIME_CLOCK,
    aMNM_DRAW_WITH_ANIME_WINDMILL,
    aMNM_DRAW_WITH_ANIME_FLOWERCLOCK,
    aMNM_DRAW_WITH_ANIME_WINDPOWER,

    aMNM_DRAW_WITH_ANIME_NUM
};

enum {
    aMNM_DRAW_ONLY_MODEL_GASLIGHT,
    aMNM_DRAW_ONLY_MODEL_HELIPORT,
    aMNM_DRAW_ONLY_MODEL_DOKAN,
    aMNM_DRAW_ONLY_MODEL_STONEHENGE,
    aMNM_DRAW_ONLY_MODEL_BIGEGG,
    aMNM_DRAW_ONLY_MODEL_FOOTPOINT,
    aMNM_DRAW_ONLY_MODEL_NAZKA,
    aMNM_DRAW_ONLY_MODEL_BIGMUSH,
    aMNM_DRAW_ONLY_MODEL_SIGN,
    aMNM_DRAW_ONLY_MODEL_WELL,
    aMNM_DRAW_ONLY_MODEL_FOUNTAIN,

    aMNM_DRAW_ONLY_MODEL_NUM
};

enum {
    aMNM_BG_TYPE_NONE,
    aMNM_BG_TYPE_CLOCK,
    aMNM_BG_TYPE_SIGN,
    aMNM_BG_TYPE_WINDMILL,
    aMNM_BG_TYPE_WINDPOWER,
    aMNM_BG_TYPE_DOKAN,
    aMNM_BG_TYPE_FLOWERCLOCK,
    aMNM_BG_TYPE_FOUNTAIN,
    aMNM_BG_TYPE_BIGEGG,
    aMNM_BG_TYPE_WELL,
    aMNM_BG_TYPE_SONEHENGE,
    aMNM_BG_TYPE_BIGMUSH,

    aMNM_BG_TYPE_NUM
};

// clang-format off
static int aMNM_draw_type_table[] = {
    aMNM_DRAW_TYPE_WITH_ANIME,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_WITH_ANIME,
    aMNM_DRAW_TYPE_WITH_ANIME,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_WITH_ANIME,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_ONLY_MODEL,
    aMNM_DRAW_TYPE_ONLY_MODEL,

};
// clang-format on

static u8 aMNM_clock_shadow_vtx_fix_flg_table[4] = {
    TRUE,
    FALSE,
    FALSE,
    TRUE,
};

extern Vtx obj_mnm_clock_shadow_v[];
extern Gfx obj_mnm_clock_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_clock_shadow_data = {
    ARRAY_COUNT(aMNM_clock_shadow_vtx_fix_flg_table),
    aMNM_clock_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_clock_shadow_v,
    obj_mnm_clock_shadowT_model,
};

static u8 aMNM_gaslight_shadow_vtx_fix_flg_table[4] = {
    TRUE,
    FALSE,
    FALSE,
    TRUE,
};

extern Vtx obj_mnm_gaslight_shadow_v[];
extern Gfx obj_mnm_gaslight_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_gaslight_shadow_data = {
    ARRAY_COUNT(aMNM_gaslight_shadow_vtx_fix_flg_table),
    aMNM_gaslight_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_gaslight_shadow_v,
    obj_mnm_gaslight_shadowT_model,
};

static u8 aMNM_windmill_shadow_vtx_fix_flg_table[10] = {
    TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE, TRUE, TRUE,
};

extern Vtx obj_mnm_windmill_shadow_v[];
extern Gfx obj_mnm_windmill_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_windmill_shadow_data = {
    ARRAY_COUNT(aMNM_windmill_shadow_vtx_fix_flg_table),
    aMNM_windmill_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_windmill_shadow_v,
    obj_mnm_windmill_shadowT_model,
};

static u8 aMNM_windpower_shadow_vtx_fix_flg_table[4] = {
    TRUE,
    TRUE,
    FALSE,
    FALSE,
};

extern Vtx obj_mnm_windpower_shadow_v[];
extern Gfx obj_mnm_windpower_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_windpower_shadow_data = {
    ARRAY_COUNT(aMNM_windpower_shadow_vtx_fix_flg_table),
    aMNM_windpower_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_windpower_shadow_v,
    obj_mnm_windpower_shadowT_model,
};

static u8 aMNM_dokan_shadow_vtx_fix_flg_table[35] = {
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
    FALSE, TRUE,  TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE,
    FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE, TRUE,  FALSE, FALSE,
};

extern Vtx obj_mnm_dokan_shadow_v[];
extern Gfx obj_mnm_dokan_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_dokan_shadow_data = {
    ARRAY_COUNT(aMNM_dokan_shadow_vtx_fix_flg_table),
    aMNM_dokan_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_dokan_shadow_v,
    obj_mnm_dokan_shadowT_model,
};

static u8 aMNM_stonehenge_shadow_vtx_fix_flg_table[70] = {
    TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE, TRUE,  TRUE,  TRUE,  FALSE, FALSE, TRUE,
    FALSE, TRUE,  TRUE,  FALSE, TRUE,  TRUE,  TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE,
    TRUE,  TRUE,  TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE, TRUE,  TRUE,  TRUE,  FALSE,
    FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE, TRUE,  TRUE,  TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,
    TRUE,  FALSE, TRUE,  TRUE,  TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE,  FALSE, TRUE,  TRUE,
};

extern Vtx obj_mnm_stonehenge_shadow_v[];
extern Gfx obj_mnm_stonehenge_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_stonehenge_shadow_data = {
    ARRAY_COUNT(aMNM_stonehenge_shadow_vtx_fix_flg_table),
    aMNM_stonehenge_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_stonehenge_shadow_v,
    obj_mnm_stonehenge_shadowT_model,
};

static u8 aMNM_bigegg_shadow_vtx_fix_flg_table[26] = {
    TRUE, FALSE, FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE, FALSE, TRUE,  FALSE, TRUE,  FALSE,
    TRUE, TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE, TRUE,  FALSE, TRUE,  FALSE, TRUE,
};

extern Vtx obj_mnm_bigegg_shadow_v[];
extern Gfx obj_mnm_bigegg_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_bigegg_shadow_data = {
    ARRAY_COUNT(aMNM_bigegg_shadow_vtx_fix_flg_table),
    aMNM_bigegg_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_bigegg_shadow_v,
    obj_mnm_bigegg_shadowT_model,
};

static u8 aMNM_bigmush_shadow_vtx_fix_flg_table[10] = {
    TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE, TRUE, TRUE,
};

extern Vtx obj_mnm_bigmush_shadow_v[];
extern Gfx obj_mnm_bigmush_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_bigmush_shadow_data = {
    ARRAY_COUNT(aMNM_bigmush_shadow_vtx_fix_flg_table),
    aMNM_bigmush_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_bigmush_shadow_v,
    obj_mnm_bigmush_shadowT_model,
};

static u8 aMNM_sign_shadow_vtx_fix_flg_table[10] = {
    TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE, TRUE, TRUE,
};

extern Vtx obj_mnm_sign_shadow_v[];
extern Gfx obj_mnm_sign_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_sign_shadow_data = {
    ARRAY_COUNT(aMNM_sign_shadow_vtx_fix_flg_table),
    aMNM_sign_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_sign_shadow_v,
    obj_mnm_sign_shadowT_model,
};

static u8 aMNM_flowerclock_shadow_vtx_fix_flg_table[26] = {
    TRUE, FALSE, FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE, FALSE, TRUE,  FALSE, TRUE,  FALSE,
    TRUE, TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE, TRUE,  FALSE, TRUE,  FALSE, TRUE,
};

extern Vtx obj_mnm_flowerclock_shadow_v[];
extern Gfx obj_mnm_flowerclock_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_flowerclock_shadow_data = {
    ARRAY_COUNT(aMNM_flowerclock_shadow_vtx_fix_flg_table),
    aMNM_flowerclock_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_flowerclock_shadow_v,
    obj_mnm_flowerclock_shadowT_model,
};

static u8 aMNM_well_shadow_vtx_fix_flg_table[26] = {
    TRUE, FALSE, FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE, FALSE, TRUE,  FALSE, TRUE,  FALSE,
    TRUE, TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE, TRUE,  FALSE, TRUE,  FALSE, TRUE,
};

extern Vtx obj_mnm_well_shadow_v[];
extern Gfx obj_mnm_well_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_well_shadow_data = {
    ARRAY_COUNT(aMNM_well_shadow_vtx_fix_flg_table),
    aMNM_well_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_well_shadow_v,
    obj_mnm_well_shadowT_model,
};

static u8 aMNM_fountain_shadow_vtx_fix_flg_table[26] = {
    TRUE, FALSE, FALSE, TRUE,  FALSE, TRUE,  FALSE, TRUE, FALSE, TRUE,  FALSE, TRUE,  FALSE,
    TRUE, TRUE,  FALSE, FALSE, TRUE,  FALSE, TRUE,  TRUE, TRUE,  FALSE, TRUE,  FALSE, TRUE,
};

extern Vtx obj_mnm_fountain_shadow_v[];
extern Gfx obj_mnm_fountain_shadowT_model[];

static bIT_ShadowData_c aMNM_obj_mnm_fountain_shadow_data = {
    ARRAY_COUNT(aMNM_fountain_shadow_vtx_fix_flg_table),
    aMNM_fountain_shadow_vtx_fix_flg_table,
    60.0f,
    obj_mnm_fountain_shadow_v,
    obj_mnm_fountain_shadowT_model,
};

static bIT_ShadowData_c* aMNM_shadow_data_table[] = {
    &aMNM_obj_mnm_clock_shadow_data,
    &aMNM_obj_mnm_gaslight_shadow_data,
    &aMNM_obj_mnm_windmill_shadow_data,
    &aMNM_obj_mnm_flowerclock_shadow_data,
    NULL,
    &aMNM_obj_mnm_windpower_shadow_data,
    &aMNM_obj_mnm_dokan_shadow_data,
    &aMNM_obj_mnm_stonehenge_shadow_data,
    &aMNM_obj_mnm_bigegg_shadow_data,
    NULL,
    NULL,
    &aMNM_obj_mnm_bigmush_shadow_data,
    &aMNM_obj_mnm_sign_shadow_data,
    &aMNM_obj_mnm_well_shadow_data,
    &aMNM_obj_mnm_fountain_shadow_data,
};

static void aMNM_actor_ct(ACTOR* actorx, GAME* game);
static void aMNM_actor_dt(ACTOR* actorx, GAME* game);
static void aMNM_actor_move(ACTOR* actorx, GAME* game);
static void aMNM_actor_draw_with_anime(ACTOR* actorx, GAME* game);
static void aMNM_actor_draw_only_model(ACTOR* actorx, GAME* game);
static void aMNM_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Monument_Profile = {
    mAc_PROFILE_MONUMENT,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NONE,
    MONUMENT_PARK_CLOCK,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MONUMENT_ACTOR),
    &aMNM_actor_ct,
    &aMNM_actor_dt,
    &aMNM_actor_init,
    &aMNM_actor_draw_with_anime,
    NULL,
};
// clang-format on

static void aMNM_draw_init_with_anime(MONUMENT_ACTOR* actor);
static void aMNM_draw_init_only_model(MONUMENT_ACTOR* actor);
static void aMNM_set_bgOffset(MONUMENT_ACTOR* actor);

static void aMNM_actor_ct(ACTOR* actorx, GAME* game) {
    static int draw_idx_table[aMNM_TYPE_NUM] = {
        // clang-format off
        aMNM_DRAW_WITH_ANIME_CLOCK,
        aMNM_DRAW_ONLY_MODEL_GASLIGHT,
        aMNM_DRAW_WITH_ANIME_WINDMILL,
        aMNM_DRAW_WITH_ANIME_FLOWERCLOCK,
        aMNM_DRAW_ONLY_MODEL_HELIPORT,
        aMNM_DRAW_WITH_ANIME_WINDPOWER,
        aMNM_DRAW_ONLY_MODEL_DOKAN,
        aMNM_DRAW_ONLY_MODEL_STONEHENGE,
        aMNM_DRAW_ONLY_MODEL_BIGEGG,
        aMNM_DRAW_ONLY_MODEL_FOOTPOINT,
        aMNM_DRAW_ONLY_MODEL_NAZKA,
        aMNM_DRAW_ONLY_MODEL_BIGMUSH,
        aMNM_DRAW_ONLY_MODEL_SIGN,
        aMNM_DRAW_ONLY_MODEL_WELL,
        aMNM_DRAW_ONLY_MODEL_FOUNTAIN,
        // clang-format on
    };

    MONUMENT_ACTOR* actor = (MONUMENT_ACTOR*)actorx;
    int monument_idx = actorx->npc_id - MONUMENT_PARK_CLOCK;

    actor->structure_class.action = monument_idx;
    actor->structure_class.structure_type = aSTR_TYPE_MONUMENT_PARK_CLOCK + monument_idx;
    actor->structure_class.arg0 = draw_idx_table[monument_idx];
    actor->structure_class.season = Common_Get(time.season);

    switch (aMNM_draw_type_table[monument_idx]) {
        case aMNM_DRAW_TYPE_WITH_ANIME:
            aMNM_draw_init_with_anime(actor);
            break;
        case aMNM_DRAW_TYPE_ONLY_MODEL:
            aMNM_draw_init_only_model(actor);
            break;
    }

    switch (monument_idx) {
        case aMNM_TYPE_HELIPORT:
            if ((Common_Get(heli_se_flags) & 1) == 0 && RANDOM(64) == 0 &&
                (Common_Get(weather) >= mEnv_WEATHER_SAKURA || Common_Get(weather) < mEnv_WEATHER_RAIN) &&
                Common_Get(time).now_sec >= mTM_TIME2SEC(9, 0, 0) && Common_Get(time).now_sec < mTM_TIME2SEC(16, 0, 0) &&
                !mEv_check_run_calendar_event()) {
                xyz_t pos;

                xyz_t_move(&pos, &actorx->world.position);
                pos.x += mFI_UT_WORLDSIZE_HALF_X_F;
                pos.z += mFI_UT_WORLDSIZE_HALF_Z_F;
                // @BUG - in e+ they check if BOTH x and z are different. This would cause problems if
                // there are multiple heliports on the same X or Z unit.
                if (Common_Get(heli_se_pos).x != pos.x && Common_Get(heli_se_pos).z != pos.z) {
                    Common_Set(heli_se_pos, pos);
                    Common_Get(heli_se_flags) |= 1;
                }
            }
            break;
    }

    aMNM_set_bgOffset(actor);
}

static void aMNM_actor_dt(ACTOR* actorx, GAME* game) {
    MONUMENT_ACTOR* actor = (MONUMENT_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    switch (aMNM_draw_type_table[actor->structure_class.action]) {
        case aMNM_DRAW_TYPE_WITH_ANIME:
            cKF_SkeletonInfo_R_dt(&actor->structure_class.keyframe);
            break;
    }

    if (actor->structure_class.light_list != NULL) {
        Global_light_list_delete(&play->global_light, actor->structure_class.light_list);
    }
}

static void aMNM_set_bgOffset(MONUMENT_ACTOR* actor) {
    static int bg_type[aMNM_TYPE_NUM] = {
        // clang-format off
        aMNM_BG_TYPE_CLOCK,
        aMNM_BG_TYPE_CLOCK,
        aMNM_BG_TYPE_WINDMILL,
        aMNM_BG_TYPE_FLOWERCLOCK,
        aMNM_BG_TYPE_NONE,
        aMNM_BG_TYPE_WINDPOWER,
        aMNM_BG_TYPE_DOKAN,
        aMNM_BG_TYPE_SONEHENGE,
        aMNM_BG_TYPE_BIGEGG,
        aMNM_BG_TYPE_NONE,
        aMNM_BG_TYPE_NONE,
        aMNM_BG_TYPE_BIGMUSH,
        aMNM_BG_TYPE_SIGN,
        aMNM_BG_TYPE_WELL,
        aMNM_BG_TYPE_FOUNTAIN,
        // clang-format on
    };

    static mCoBG_OffsetTable_c clock_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    };

    static mCoBG_OffsetTable_c sign_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    };

    static mCoBG_OffsetTable_c windmill_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    };

    static mCoBG_OffsetTable_c windpower_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    };

    static mCoBG_OffsetTable_c dokan_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x00, 0x06, 0x06, 0x06, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x06, 0x06, 0x00, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x00, 0x06, 0x06, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x06, 0x06, 0x00, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x00, 0x06, 0x06, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x06, 0x00, 0x06, 0x01 },
    };

    static mCoBG_OffsetTable_c flowerclock_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x03, 0x00, 0x03, 0x03, 0x03, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x04, 0x03, 0x04, 0x04, 0x03, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x03, 0x03, 0x03, 0x03, 0x00, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x04, 0x03, 0x03, 0x04, 0x04, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x05, 0x04, 0x04, 0x04, 0x04, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x04, 0x04, 0x04, 0x03, 0x03, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x03, 0x03, 0x00, 0x03, 0x03, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x04, 0x04, 0x03, 0x03, 0x04, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x03, 0x03, 0x03, 0x00, 0x03, 0x01 },
    };

    static mCoBG_OffsetTable_c fountain_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x02, 0x01, 0x02, 0x02, 0x01, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x02, 0x01, 0x01, 0x02, 0x02, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x02, 0x02, 0x01, 0x01, 0x02, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01 },
    };

    static mCoBG_OffsetTable_c bigegg_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x00, 0x06, 0x06, 0x06, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x07, 0x06, 0x08, 0x08, 0x06, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x06, 0x06, 0x00, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x08, 0x07, 0x07, 0x08, 0x08, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x08, 0x08, 0x08, 0x07, 0x07, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x00, 0x06, 0x06, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x07, 0x08, 0x06, 0x06, 0x08, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x06, 0x00, 0x06, 0x01 },
    };

    static mCoBG_OffsetTable_c well_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x04, 0x03, 0x04, 0x05, 0x04, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x04, 0x04, 0x05, 0x04, 0x03, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x04, 0x04, 0x03, 0x04, 0x05, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x04, 0x05, 0x04, 0x03, 0x04, 0x00 },
    };

    static mCoBG_OffsetTable_c stonehenge_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x07, 0x00, 0x07, 0x07, 0x07, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x08, 0x07, 0x07, 0x07, 0x07, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x06, 0x06, 0x00, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x07, 0x07, 0x06, 0x07, 0x07, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x07, 0x07, 0x07, 0x06, 0x06, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x00, 0x06, 0x06, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x07, 0x07, 0x06, 0x06, 0x07, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x06, 0x06, 0x06, 0x00, 0x06, 0x01 },
    };

    static mCoBG_OffsetTable_c bigmush_table[9] = {
        { mCoBG_ATTRIBUTE_NONE, 0x09, 0x00, 0x09, 0x09, 0x09, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x0A, 0x09, 0x0A, 0x0A, 0x09, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x09, 0x09, 0x09, 0x09, 0x00, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x0A, 0x09, 0x09, 0x0A, 0x0A, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x0A, 0x0A, 0x0A, 0x09, 0x09, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x09, 0x09, 0x00, 0x09, 0x09, 0x01 },
        { mCoBG_ATTRIBUTE_NONE, 0x0A, 0x0A, 0x09, 0x09, 0x0A, 0x00 },
        { mCoBG_ATTRIBUTE_NONE, 0x09, 0x09, 0x09, 0x00, 0x09, 0x01 },
    };

    static mCoBG_OffsetTable_c* height_table[] = {
        // clang-format off
        NULL,
        clock_table,
        sign_table,
        windmill_table,
        windpower_table,
        dokan_table,
        flowerclock_table,
        fountain_table,
        bigegg_table,
        well_table,
        stonehenge_table,
        bigmush_table,
        // clang-format on
    };

    static f32 addX[] = { -mFI_UT_WORLDSIZE_X_F, 0.0f, mFI_UT_WORLDSIZE_X_F };
    static f32 addZ[] = { -mFI_UT_WORLDSIZE_Z_F, 0.0f, mFI_UT_WORLDSIZE_Z_F };
    mCoBG_OffsetTable_c* tbl_p = height_table[bg_type[actor->structure_class.action]];
    xyz_t pos;
    int i;

    if (tbl_p != NULL) {
        for (i = 0; i < 3; i++) {
            pos.z = actor->structure_class.actor_class.home.position.z + addZ[i];

            pos.x = actor->structure_class.actor_class.home.position.x + addX[0];
            mCoBG_SetPluss5PointOffset_file(pos, *tbl_p, __FILE__, 844);
            tbl_p++;

            pos.x = actor->structure_class.actor_class.home.position.x + addX[1];
            mCoBG_SetPluss5PointOffset_file(pos, *tbl_p, __FILE__, 848);
            tbl_p++;

            pos.x = actor->structure_class.actor_class.home.position.x + addX[2];
            mCoBG_SetPluss5PointOffset_file(pos, *tbl_p, __FILE__, 852);
            tbl_p++;
        }
    }
}

static void aMNM_setup_light(MONUMENT_ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int now_sec = Common_Get(time.now_sec);

    if (now_sec > mTM_TIME2SEC(19, 0, 0) || now_sec < mTM_TIME2SEC(5, 0, 0)) {
        Light_point_ct(
            // clang-format off
            &actor->structure_class.point_light,
            actor->structure_class.actor_class.world.position.x,
            actor->structure_class.actor_class.world.position.y + mFI_UNIT_BASE_SIZE_F,
            actor->structure_class.actor_class.world.position.z,
            255, 200, 0,
            80
            // clang-format on
        );

        if (actor->structure_class.light_list == NULL) {
            actor->structure_class.light_list =
                Global_light_list_new(game, &play->global_light, &actor->structure_class.point_light);
        }
    } else {
        if (actor->structure_class.light_list != NULL) {
            Global_light_list_delete(&play->global_light, actor->structure_class.light_list);
            actor->structure_class.light_list = NULL;
        }
    }
}

static void aMNM_actor_init(ACTOR* actorx, GAME* game) {
    MONUMENT_ACTOR* actor = (MONUMENT_ACTOR*)actorx;
    mActor_name_t item = actorx->npc_id - MONUMENT_PARK_CLOCK + DUMMY_MONUMENT_PARK_CLOCK;

    mFI_SetFG_common(item, actor->structure_class.actor_class.home.position, FALSE);
    actorx->mv_proc = aMNM_actor_move;
}

static void aMNM_actor_move(ACTOR* actorx, GAME* game) {
    MONUMENT_ACTOR* actor = (MONUMENT_ACTOR*)actorx;
    s16 angle;
    f32 wind_power;
    f32 speed;

    switch (actor->structure_class.action) {
        case aMNM_TYPE_WINDMILL:
            wind_power = mEnv_GetWindPowerF();
            if (wind_power < 0.5f) {
                speed = (wind_power / 0.5f) * 0.5f;
            } else {
                speed = (1.0f + 3.0f * ((wind_power - 0.5f) / 0.5f)) * 0.5f;
            }

            actor->structure_class.keyframe.frame_control.speed = speed;
            cKF_SkeletonInfo_R_play(&actor->structure_class.keyframe);
            sAdo_FuushaOngenPos((u32)actorx, &actorx->world.position, speed);
            break;
        case aMNM_TYPE_WINDPOWER:
            angle = mEnv_GetWindAngleS();
            angle -= DEG2SHORT_ANGLE2(135.0f);
            wind_power = mEnv_GetWindPowerF();
            wind_power *= cos_s(angle);
            if (wind_power < 0.5f) {
                speed = (wind_power / 0.5f) * 0.5f;
            } else {
                speed = (1.0f + 3.0f * ((wind_power - 0.5f) / 0.5f)) * 0.5f;
            }

            actor->structure_class.keyframe.frame_control.speed = speed;
            cKF_SkeletonInfo_R_play(&actor->structure_class.keyframe);
            break;
        case aMNM_TYPE_GASLIGHT:
            aMNM_setup_light(actor, game);
            break;
        case aMNM_TYPE_FOUNTAIN:
            sAdo_OngenPos((u32)actorx, 0x65, &actorx->world.position);
            break;
    }
}

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_mnm_clock;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_mnm_windmill;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_mnm_flowerclock;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_mnm_windpower;

extern cKF_Skeleton_R_c cKF_bs_r_obj_w_mnm_clock;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_mnm_windmill;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_mnm_flowerclock;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_mnm_windpower;

extern cKF_Animation_R_c cKF_ba_r_obj_s_mnm_clock;
extern cKF_Animation_R_c cKF_ba_r_obj_s_mnm_windmill;
extern cKF_Animation_R_c cKF_ba_r_obj_s_mnm_flowerclock;
extern cKF_Animation_R_c cKF_ba_r_obj_s_mnm_windpower;

extern cKF_Animation_R_c cKF_ba_r_obj_w_mnm_clock;
extern cKF_Animation_R_c cKF_ba_r_obj_w_mnm_windmill;
extern cKF_Animation_R_c cKF_ba_r_obj_w_mnm_flowerclock;
extern cKF_Animation_R_c cKF_ba_r_obj_w_mnm_windpower;

static void aMNM_draw_init_with_anime(MONUMENT_ACTOR* actor) {
    static cKF_Skeleton_R_c* model_table[] = {
        // clang-format off
        &cKF_bs_r_obj_s_mnm_clock,
        &cKF_bs_r_obj_s_mnm_windmill,
        &cKF_bs_r_obj_s_mnm_flowerclock,
        &cKF_bs_r_obj_s_mnm_windpower,
        // clang-format on
    };

    static cKF_Skeleton_R_c* model_winter_table[] = {
        // clang-format off
        &cKF_bs_r_obj_w_mnm_clock,
        &cKF_bs_r_obj_w_mnm_windmill,
        &cKF_bs_r_obj_w_mnm_flowerclock,
        &cKF_bs_r_obj_w_mnm_windpower,
        // clang-format on
    };

    static cKF_Animation_R_c* anime_table[] = {
        // clang-format off
        &cKF_ba_r_obj_s_mnm_clock,
        &cKF_ba_r_obj_s_mnm_windmill,
        &cKF_ba_r_obj_s_mnm_flowerclock,
        &cKF_ba_r_obj_s_mnm_windpower,
        // clang-format on
    };

    static cKF_Animation_R_c* anime_winter_table[] = {
        // clang-format off
        &cKF_ba_r_obj_w_mnm_clock,
        &cKF_ba_r_obj_w_mnm_windmill,
        &cKF_ba_r_obj_w_mnm_flowerclock,
        &cKF_ba_r_obj_w_mnm_windpower,
        // clang-format on
    };

    int draw_idx = actor->structure_class.arg0;
    u32 season = actor->structure_class.season;
    cKF_Skeleton_R_c* skel;
    cKF_Animation_R_c* anime;

    if (season == mTM_SEASON_WINTER) {
        skel = model_winter_table[draw_idx];
        anime = anime_winter_table[draw_idx];
    } else {
        skel = model_table[draw_idx];
        anime = anime_table[draw_idx];
    }

    cKF_SkeletonInfo_R_ct(&actor->structure_class.keyframe, skel, NULL, actor->structure_class.work_area,
                          actor->structure_class.morph_area);
    cKF_SkeletonInfo_R_init(&actor->structure_class.keyframe, actor->structure_class.keyframe.skeleton, anime, 1.0f,
                            -1.0f, 1.0f, 0.5f, 0.0f, cKF_FRAMECONTROL_REPEAT, NULL);
    cKF_SkeletonInfo_R_play(&actor->structure_class.keyframe);
}

static void aMNM_draw_init_only_model(MONUMENT_ACTOR* actor) {
    actor->structure_class.actor_class.dw_proc = aMNM_actor_draw_only_model;
}

static int aMNM_actor_draw_before_clock(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                        u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    switch (joint_idx) {
        case 2:
            Matrix_RotateZ(-Common_Get(time.rad_min), MTX_MULT);
            break;
        case 4:
            Matrix_RotateZ(-Common_Get(time.rad_hour), MTX_MULT);
            break;
    }

    return TRUE;
}

static int aMNM_actor_draw_before_windmill(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                           u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    switch (joint_idx) {
        case 1:
            Matrix_RotateY(mEnv_GetWindAngleS() + DEG2SHORT_ANGLE2(180.0f), MTX_MULT);
            break;
    }

    return TRUE;
}

static int aMNM_actor_draw_before_flowerclock(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                        u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    switch (joint_idx) {
        case 2:
            Matrix_RotateX(Common_Get(time.rad_min), MTX_MULT);
            break;
        case 4:
            Matrix_RotateX(Common_Get(time.rad_hour), MTX_MULT);
            break;
    }

    return TRUE;
}

static void aMNM_actor_draw_with_anime(ACTOR* actorx, GAME* game) {
    static cKF_draw_callback draw_before[] = {
        // clang-format off
        aMNM_actor_draw_before_clock,
        aMNM_actor_draw_before_windmill,
        aMNM_actor_draw_before_flowerclock,
        NULL,
        // clang-format on
    };

    static cKF_draw_callback draw_after[] = {
        // clang-format off
        NULL,
        NULL,
        NULL,
        NULL,
        // clang-format on
    };

    MONUMENT_ACTOR* actor = (MONUMENT_ACTOR*)actorx;
    GRAPH* graph = game->graph;
    cKF_SkeletonInfo_R_c* keyframe = &actor->structure_class.keyframe;
    Mtx* mtx = GRAPH_ALLOC_TYPE(graph, Mtx, keyframe->skeleton->num_shown_joints);
    int draw_idx;

    if (mtx != NULL) {
        draw_idx = actor->structure_class.arg0;

        _texture_z_light_fog_prim_npc(graph);
        cKF_Si3_draw_R_SV(game, keyframe, mtx, draw_before[draw_idx], draw_after[draw_idx], actorx);
    }

    if (aMNM_shadow_data_table[actor->structure_class.action] != NULL) {
        CLIP(bg_item_clip)->draw_shadow_proc(game, aMNM_shadow_data_table[actor->structure_class.action], 0);
    }
}

// year round
extern Gfx obj_mnm_heliport_model[];
extern Gfx obj_mnm_footpointT_model[];
extern Gfx obj_mnm_nazkaT_model[];

// spring, summer, fall
extern Gfx obj_s_mnm_gaslight_model[];
extern Gfx obj_s_mnm_dokan_model[];
extern Gfx obj_s_mnm_stonehenge_model[];
extern Gfx obj_s_mnm_bigegg_model[];
extern Gfx obj_s_mnm_bigmush_model[];
extern Gfx obj_s_mnm_sign_model[];
extern Gfx obj_s_mnm_well_model[];
extern Gfx obj_s_mnm_fountain_model[];

// winter
extern Gfx obj_w_mnm_gaslight_model[];
extern Gfx obj_w_mnm_dokan_model[];
extern Gfx obj_w_mnm_stonehenge_model[];
extern Gfx obj_w_mnm_bigegg_model[];
extern Gfx obj_w_mnm_bigmush_model[];
extern Gfx obj_w_mnm_sign_model[];
extern Gfx obj_w_mnm_well_model[];
extern Gfx obj_w_mnm_fountain_model[];

extern EVW_ANIME_DATA obj_s_mnm_fountain_evw_anime[];
extern EVW_ANIME_DATA obj_w_mnm_fountain_evw_anime[];

static void aMNM_actor_draw_only_model(ACTOR* actorx, GAME* game) {
    static Gfx* display_list[] = {
        obj_s_mnm_gaslight_model,
        obj_mnm_heliport_model,
        obj_s_mnm_dokan_model,
        obj_s_mnm_stonehenge_model,
        obj_s_mnm_bigegg_model,
        obj_mnm_footpointT_model,
        obj_mnm_nazkaT_model,
        obj_s_mnm_bigmush_model,
        obj_s_mnm_sign_model,
        obj_s_mnm_well_model,
        obj_s_mnm_fountain_model,
    };
    
    static Gfx* display_list_winter[] = {
        obj_w_mnm_gaslight_model,
        obj_mnm_heliport_model,
        obj_w_mnm_dokan_model,
        obj_w_mnm_stonehenge_model,
        obj_w_mnm_bigegg_model,
        obj_mnm_footpointT_model,
        obj_mnm_nazkaT_model,
        obj_w_mnm_bigmush_model,
        obj_w_mnm_sign_model,
        obj_w_mnm_well_model,
        obj_w_mnm_fountain_model,
    };
    
    static EVW_ANIME_DATA* fountain_evw_anime[] = {
        obj_s_mnm_fountain_evw_anime,
        obj_w_mnm_fountain_evw_anime,
    };

    MONUMENT_ACTOR* actor = (MONUMENT_ACTOR*)actorx;
    GRAPH* graph = game->graph;
    GAME_PLAY* play = (GAME_PLAY*)game;
    Mtx* mtx = _Matrix_to_Mtx_new(graph);
    Gfx* gfx;
    LightsN* lights_n;
    xyz_t light_pos;

    if (mtx != NULL) {
        u32 season = actor->structure_class.season;
        int draw_idx = actor->structure_class.arg0;
        if (season == mTM_SEASON_WINTER) {
            gfx = display_list_winter[draw_idx];
        } else {
            gfx = display_list[draw_idx];
        }

        switch (actor->structure_class.action) {
            case aMNM_TYPE_GASLIGHT:
                light_pos = actor->structure_class.actor_class.world.position;
                light_pos.y += 1000.0f;
                lights_n = Global_light_read(&play->global_light, graph);
                LightsN_list_check(lights_n, play->global_light.list, &light_pos);
                LightsN_disp(lights_n, graph);
                break;
            
            case aMNM_TYPE_FOUNTAIN:
                Evw_Anime_Set(play, fountain_evw_anime[actor->structure_class.season == mTM_SEASON_WINTER]);
                break;
        }

        _texture_z_light_fog_prim_npc(graph);

        OPEN_DISP(graph);
        switch (actor->structure_class.action) {
            case aMNM_TYPE_HELIPORT:
            case aMNM_TYPE_FOOTPOINT:
            case aMNM_TYPE_NAZKA:
                gSPMatrix(NEXT_BG_OPA_DISP, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(NEXT_BG_OPA_DISP, gfx);
                break;
            case aMNM_TYPE_SIGN:
            case aMNM_TYPE_WELL:
                gSPSegment(NEXT_POLY_OPA_DISP, ANIME_2_TXT_SEG, g_fdinfo->field_palette.grass_pal);
                gSPMatrix(NEXT_POLY_OPA_DISP, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(NEXT_POLY_OPA_DISP, gfx);
                break;
            default:
                gSPMatrix(NEXT_POLY_OPA_DISP, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(NEXT_POLY_OPA_DISP, gfx);
                break;
        }

        CLOSE_DISP(graph);
    }

    if (aMNM_shadow_data_table[actor->structure_class.action] != NULL) {
        CLIP(bg_item_clip)->draw_shadow_proc(game, aMNM_shadow_data_table[actor->structure_class.action], bIT_SHADOW_TYPE_HARD);
    }
}
