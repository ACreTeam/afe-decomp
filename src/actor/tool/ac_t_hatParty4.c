#include "ac_t_hatParty4.h"
#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTHP4_actor_ct(ACTOR* actor, GAME*);
static void aTHP4_actor_move(ACTOR* actor, GAME*);
static void aTHP4_actor_draw(ACTOR* actor, GAME*);
static void aTHP4_setupAction(ACTOR*, int);

ACTOR_PROFILE T_HatParty4_Profile = {
    mAc_PROFILE_T_HAT_PARTY4,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(TOOL_HAT_PARTY4_ACTOR),
    &aTHP4_actor_ct,
    NONE_ACTOR_PROC,
    &aTHP4_actor_move,
    &aTHP4_actor_draw,
    NULL,
};

extern Gfx hat_party4_body_model[];

static void aTHP4_actor_ct(ACTOR* actor, GAME* game) {
    aTHP4_setupAction(actor, aTOL_ACTION_S_TAKEOUT);
}

static void aTHP4_destruct(ACTOR* actor) {
    Actor_delete(actor);
}

static void aTHP4_setupAction(ACTOR* actor, int action) {
    TOOL_HAT_PARTY4_ACTOR* hat = (TOOL_HAT_PARTY4_ACTOR*)actor;
    static HATPARY4_PROC process[] = {
        (HATPARY4_PROC)none_proc1, (HATPARY4_PROC)none_proc1,
        (HATPARY4_PROC)none_proc1, aTHP4_destruct,
        (HATPARY4_PROC)none_proc1, NULL,
    };

    hat->act_proc = process[action];
    hat->action = action;
    hat->tools_class.work0 = action;
}

static void aTHP4_actor_move(ACTOR* actor, GAME* game) {
    TOOL_HAT_PARTY4_ACTOR* hat = (TOOL_HAT_PARTY4_ACTOR*)actor;

    if (hat->tools_class.work0 != hat->action) {
        aTHP4_setupAction(actor, hat->tools_class.work0);
    }

    hat->act_proc(actor);
}

static void aTHP4_actor_draw(ACTOR* actor, GAME* game) {
    TOOL_HAT_PARTY4_ACTOR* hat = (TOOL_HAT_PARTY4_ACTOR*)actor;

    if (hat->tools_class.init_matrix == 1) {
        GRAPH* graph = game->graph;

        Matrix_put(&hat->tools_class.matrix_work);
        Matrix_Position_Zero(&hat->tools_class.actor_class.world.position);

        hat->tools_class.init_matrix = 0;

        _texture_z_light_fog_prim_npc(graph);

        OPEN_POLY_OPA_DISP(graph);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, hat_party4_body_model);
        CLOSE_POLY_OPA_DISP(graph);
    }
}
