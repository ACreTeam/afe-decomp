#include "ac_t_hatHarvest2.h"
#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTHH2_actor_ct(ACTOR* actor, GAME*);
static void aTHH2_actor_move(ACTOR* actor, GAME*);
static void aTHH2_actor_draw(ACTOR* actor, GAME*);
static void aTHH2_setupAction(ACTOR*, int);

ACTOR_PROFILE T_HatHarvest2_Profile = {
    mAc_PROFILE_T_HAT_HARVEST2,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(TOOL_HAT_HARVEST2_ACTOR),
    &aTHH2_actor_ct,
    NONE_ACTOR_PROC,
    &aTHH2_actor_move,
    &aTHH2_actor_draw,
    NULL,
};

extern Gfx hat_harvest2_body_model[];

static void aTHH2_actor_ct(ACTOR* actor, GAME* game) {
    aTHH2_setupAction(actor, aTOL_ACTION_S_TAKEOUT);
}

static void aTHH2_destruct(ACTOR* actor) {
    Actor_delete(actor);
}

static void aTHH2_setupAction(ACTOR* actor, int action) {
    TOOL_HAT_HARVEST2_ACTOR* hat = (TOOL_HAT_HARVEST2_ACTOR*)actor;
    static HATHARVEST2_PROC process[] = {
        (HATHARVEST2_PROC)none_proc1, (HATHARVEST2_PROC)none_proc1,
        (HATHARVEST2_PROC)none_proc1, aTHH2_destruct,
        (HATHARVEST2_PROC)none_proc1, NULL,
    };

    hat->act_proc = process[action];
    hat->action = action;
    hat->tools_class.work0 = action;
}

static void aTHH2_actor_move(ACTOR* actor, GAME* game) {
    TOOL_HAT_HARVEST2_ACTOR* hat = (TOOL_HAT_HARVEST2_ACTOR*)actor;

    if (hat->tools_class.work0 != hat->action) {
        aTHH2_setupAction(actor, hat->tools_class.work0);
    }

    hat->act_proc(actor);
}

static void aTHH2_actor_draw(ACTOR* actor, GAME* game) {
    TOOL_HAT_HARVEST2_ACTOR* hat = (TOOL_HAT_HARVEST2_ACTOR*)actor;

    if (hat->tools_class.init_matrix == 1) {
        GRAPH* graph = game->graph;

        Matrix_put(&hat->tools_class.matrix_work);
        Matrix_Position_Zero(&hat->tools_class.actor_class.world.position);

        hat->tools_class.init_matrix = 0;

        _texture_z_light_fog_prim_npc(graph);

        OPEN_POLY_OPA_DISP(graph);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, hat_harvest2_body_model);
        CLOSE_POLY_OPA_DISP(graph);
    }
}
