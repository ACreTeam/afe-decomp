#include "ac_t_hatChristmas1.h"
#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTHC1_actor_ct(ACTOR* actor, GAME*);
static void aTHC1_actor_move(ACTOR* actor, GAME*);
static void aTHC1_actor_draw(ACTOR* actor, GAME*);
static void aTHC1_setupAction(ACTOR*, int);

ACTOR_PROFILE T_HatChristmas1_Profile = {
    mAc_PROFILE_T_HAT_CHRISTMAS1,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(TOOL_HAT_CHRISTMAS1_ACTOR),
    &aTHC1_actor_ct,
    NONE_ACTOR_PROC,
    &aTHC1_actor_move,
    &aTHC1_actor_draw,
    NULL,
};

extern Gfx hat_christmas1_body_model[];

static void aTHC1_actor_ct(ACTOR* actor, GAME* game) {
    aTHC1_setupAction(actor, aTOL_ACTION_S_TAKEOUT);
}

static void aTHC1_destruct(ACTOR* actor) {
    Actor_delete(actor);
}

static void aTHC1_setupAction(ACTOR* actor, int action) {
    TOOL_HAT_CHRISTMAS1_ACTOR* hat = (TOOL_HAT_CHRISTMAS1_ACTOR*)actor;
    static HATCHRISTMAS1_PROC process[] = {
        (HATCHRISTMAS1_PROC)none_proc1, (HATCHRISTMAS1_PROC)none_proc1,
        (HATCHRISTMAS1_PROC)none_proc1, aTHC1_destruct,
        (HATCHRISTMAS1_PROC)none_proc1, NULL,
    };

    hat->act_proc = process[action];
    hat->action = action;
    hat->tools_class.work0 = action;
}

static void aTHC1_actor_move(ACTOR* actor, GAME* game) {
    TOOL_HAT_CHRISTMAS1_ACTOR* hat = (TOOL_HAT_CHRISTMAS1_ACTOR*)actor;

    if (hat->tools_class.work0 != hat->action) {
        aTHC1_setupAction(actor, hat->tools_class.work0);
    }

    hat->act_proc(actor);
}

static void aTHC1_actor_draw(ACTOR* actor, GAME* game) {
    TOOL_HAT_CHRISTMAS1_ACTOR* hat = (TOOL_HAT_CHRISTMAS1_ACTOR*)actor;

    if (hat->tools_class.init_matrix == 1) {
        GRAPH* graph = game->graph;

        Matrix_put(&hat->tools_class.matrix_work);
        Matrix_Position_Zero(&hat->tools_class.actor_class.world.position);

        hat->tools_class.init_matrix = 0;

        _texture_z_light_fog_prim_npc(graph);

        OPEN_POLY_OPA_DISP(graph);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, hat_christmas1_body_model);
        CLOSE_POLY_OPA_DISP(graph);
    }
}
