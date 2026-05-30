#include "ac_reset_chair.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "ac_resetcenter_indoor.h"

static void Reset_Chair_Actor_ct(ACTOR* actorx, GAME* game);
static void Reset_Chair_Actor_dt(ACTOR* actorx, GAME* game);
static void Reset_Chair_Actor_move(ACTOR* actorx, GAME* game);
static void Reset_Chair_Actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Reset_Chair_Profile = {
    mAc_PROFILE_RESET_CHAIR,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(RESET_CHAIR_ACTOR),
    Reset_Chair_Actor_ct,
    Reset_Chair_Actor_dt,
    Reset_Chair_Actor_move,
    Reset_Chair_Actor_draw,
    NULL,
};

static void Reset_Chair_Actor_ct(ACTOR* actorx, GAME* game) {
    RESET_CHAIR_ACTOR* actor = (RESET_CHAIR_ACTOR*)actorx;

    actor->reset_mode_E = aRI_get_reset_mode_E();
    switch (actor->reset_mode_E) {
        case 11:
        case 14:
            actor->ofs_z = -130.0f;
            break;
        default:
            actor->ofs_z = 0.0f;
            break;
    }

    actorx->world.position.z = actorx->home.position.z + actor->ofs_z;
    actor->act_idx = 0;
    actor->next_act_idx = 0;
}

static void Reset_Chair_Actor_dt(ACTOR* actorx, GAME* game) {
    // nothing
}

extern Gfx obj_item_movechair_model[];

static void Reset_Chair_Actor_draw(ACTOR* actorx, GAME* game) {
    Matrix_translate(actorx->world.position.x, actorx->world.position.y, actorx->world.position.z, MTX_LOAD);
    Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    aRI_set_resetcenter_prim_color(game);
    gSPDisplayList(NEXT_POLY_OPA_DISP, obj_item_movechair_model);

    CLOSE_DISP(game->graph);
}

static void aRC_wait(RESET_CHAIR_ACTOR* actor, GAME* game) {
    // nothing
}

static void aRC_sailing(RESET_CHAIR_ACTOR* actor, GAME* game) {
    switch(actor->sailing_state) {
        case 0:
            actor->ofs_z = 0.0f;
            actor->sailing_state++;
            break;
        case 1:
            if (actor->ofs_z <= -130.0f) {
                actor->sailing_state++;
            } else {
                actor->ofs_z -= 2.0f;
            }
            break;
        default:
            actor->next_act_idx = 2;
            return;
    }

    actor->actor_class.world.position.z = actor->actor_class.home.position.z + actor->ofs_z;
}

static void aRC_hide(RESET_CHAIR_ACTOR* actor, GAME* game) {
    // nothing
}

static void aRC_return(RESET_CHAIR_ACTOR* actor, GAME* game) {
    switch(actor->sailing_state) {
        case 0:
            actor->ofs_z = -130.0f;
            actor->sailing_state++;
            break;
        case 1:
            if (actor->ofs_z >= 0.0f) {
                actor->sailing_state++;
                actor->ofs_z = 0.0f;
            } else {
                actor->ofs_z += 2.0f;
            }
            break;
        default:
            actor->next_act_idx = 0;
            return;
    }

    actor->actor_class.world.position.z = actor->actor_class.home.position.z + actor->ofs_z;
}

typedef void (*aRC_ACT_PROC)(RESET_CHAIR_ACTOR* actor, GAME* game);

static void Reset_Chair_Actor_move(ACTOR* actorx, GAME* game) {
    static aRC_ACT_PROC move_proc[] = {
        aRC_wait,
        aRC_sailing,
        aRC_hide,
        aRC_return,
    };

    RESET_CHAIR_ACTOR* actor = (RESET_CHAIR_ACTOR*)actorx;

    if (actor->next_act_idx != actor->act_idx) {
        actor->act_idx = actor->next_act_idx;
        actor->sailing_state = 0;
        actor->timer = 0;
    }

    (*move_proc[actor->act_idx])(actor, game);
}
