#include "ac_t_hatParty3.h"
#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTHP3_actor_ct(ACTOR* actor, GAME*);
static void aTHP3_actor_move(ACTOR* actor, GAME*);
static void aTHP3_actor_draw(ACTOR* actor, GAME*);
static void aTHP3_setupAction(ACTOR*, int);

ACTOR_PROFILE T_HatParty3_Profile = {
    mAc_PROFILE_T_HAT_PARTY3,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(TOOL_HAT_PARTY3_ACTOR),
    &aTHP3_actor_ct,
    NONE_ACTOR_PROC,
    &aTHP3_actor_move,
    &aTHP3_actor_draw,
    NULL,
};

extern Gfx hat_party3_body_model[];

static void aTHP3_actor_ct(ACTOR* actor, GAME* game) {
    aTHP3_setupAction(actor, aTOL_ACTION_S_TAKEOUT);
}

static void aTHP3_destruct(ACTOR* actor) {
    Actor_delete(actor);
}

static void aTHP3_setupAction(ACTOR* actor, int action) {
    TOOL_HAT_PARTY3_ACTOR* hat = (TOOL_HAT_PARTY3_ACTOR*)actor;
    static HATPARY3_PROC process[] = {
        (HATPARY3_PROC)none_proc1, (HATPARY3_PROC)none_proc1,
        (HATPARY3_PROC)none_proc1, aTHP3_destruct,
        (HATPARY3_PROC)none_proc1, NULL,
    };

    hat->act_proc = process[action];
    hat->action = action;
    hat->tools_class.work0 = action;
}

static void aTHP3_actor_move(ACTOR* actor, GAME* game) {
    TOOL_HAT_PARTY3_ACTOR* hat = (TOOL_HAT_PARTY3_ACTOR*)actor;

    if (hat->tools_class.work0 != hat->action) {
        aTHP3_setupAction(actor, hat->tools_class.work0);
    }

    hat->act_proc(actor);
}

static void aTHP3_actor_draw(ACTOR* actor, GAME* game) {
    TOOL_HAT_PARTY3_ACTOR* hat = (TOOL_HAT_PARTY3_ACTOR*)actor;

    if (hat->tools_class.init_matrix == 1) {
        GRAPH* graph = game->graph;

        Matrix_put(&hat->tools_class.matrix_work);
        Matrix_Position_Zero(&hat->tools_class.actor_class.world.position);

        hat->tools_class.init_matrix = 0;

        _texture_z_light_fog_prim_npc(graph);

        OPEN_POLY_OPA_DISP(graph);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, hat_party3_body_model);
        CLOSE_POLY_OPA_DISP(graph);
    }
}
