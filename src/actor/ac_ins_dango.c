#include "ac_ins_dango.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "ac_set_ovl_insect.h"

enum {
    aIDG_ACTION_AVOID,
    aIDG_ACTION_LET_ESCAPE,
    aIDG_ACTION_STOP,
    aIDG_ACTION_HIDE,
    aIDG_ACTION_APPEAR,
    aIDG_ACTION_DIVE,
    aIDG_ACTION_DROWN,
    aIDG_ACTION_RETIRE,
    aIDG_ACTION_TURN_BODY,
    aIDG_ACTION_CARRY_BALL,
    aIDG_ACTION_TURN_BODY_SEARCH,
    aIDG_ACTION_SEARCH_BALL,
    aIDG_ACTION_LOSE_HEART,
    aIDG_ACTION_WALK,
    aIDG_ACTION_FLY_AWAY,
    aIDG_ACTION_FLY_AWAY_LET_ESCAPE,

    aIDG_ACTION_NUM
};

static ClObjPipeData_c aIDG_CoInfoData = {
    // clang-format off
    // collision data
    {
        ClObj_FLAG_COLLIDE_PLAYER | ClObj_FLAG_COLLIDE_GROUP_2 | ClObj_FLAG_COLLIDE_GROUP_3 | ClObj_FLAG_CHECK, // 0b00111001
        ClObj_FLAG2_IS_GROUP_3, // 0b00100000
        ClObj_TYPE_PIPE,
    },
    { ClObj_FLAG_CHECK },
    { 4, 10, 0, { 0, 0, 0 } },
    // clang-format on
};

static StatusData_c aIDG_StatusData = { 0, 4, 10, 0, 50 };

static void aIDG_actor_move(ACTOR*, GAME*);
static void aIDG_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

extern void aIDG_actor_init(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    int bx, bz;
    int action;
    ACTOR* parent;
    s16 angle;
    ClObjPipe_c* col_pipe;

    if (insect->tools_actor.actor_class.actor_specific == 0) {
        mFI_BkNum2WposXZ(&insect->f32_work2, &insect->f32_work3, insect->tools_actor.actor_class.block_x,
                         insect->tools_actor.actor_class.block_z);
        insect->f32_work2 += 320.0f;
        insect->f32_work3 += 320.0f;
        mFI_Wpos2UtNum(&bx, &bz, insect->tools_actor.actor_class.world.position);
        insect->ut_x = bx;
        insect->ut_z = bz;

        switch (insect->type) {
            case aINS_INSECT_TYPE_DUNG_BEETLE:
                parent = actor->parent_actor;
                if (parent == NULL) {
                    action = aIDG_ACTION_FLY_AWAY_LET_ESCAPE;
                } else {
                    xyz_t_move(&actor->world.position, &parent->world.position);
                    angle = RANDOM_F(DEG2SHORT_ANGLE2(201.24755859375f));
                    actor->world.position.x += 23.0f * sin_s(angle);
                    actor->world.position.z += 23.0f * cos_s(angle);
                    xyz_t_move(&actor->home.position, &parent->world.position);
                    col_pipe = &insect->col_pipe;
                    ClObjPipe_ct(game, col_pipe);
                    ClObjPipe_set5(game, col_pipe, actor, &aIDG_CoInfoData);
                    CollisionCheck_Status_set3(&actor->status_data, &aIDG_StatusData);
                    actor->shape_info.rotation.x = DEG2SHORT_ANGLE2(45.0f);
                    insect->s32_work1 = DEG2SHORT_ANGLE2(180.0f);
                    action = aIDG_ACTION_CARRY_BALL;
                }
                break;
            default:
                action = aIDG_ACTION_HIDE;
                break;
        }
    } else {
        switch (insect->type) {
            case aINS_INSECT_TYPE_DUNG_BEETLE:
                action = aIDG_ACTION_FLY_AWAY_LET_ESCAPE;
                break;
            default:
                action = aIDG_ACTION_LET_ESCAPE;
                break;
        }
        insect->tools_actor.actor_class.drawn = TRUE;
    }
    insect->insect_flags.unique_wall_check = FALSE;
    insect->bg_range = 2.0f;

    switch (insect->type) {
        case aINS_INSECT_TYPE_SPIDER:
            break;
        case aINS_INSECT_TYPE_PILL_BUG:
            insect->item = ITM_INSECT36;
            break;
        case aINS_INSECT_TYPE_ANT:
            insect->item = ITM_INSECT38;
            break;
        case aINS_INSECT_TYPE_DUNG_BEETLE:
            insect->item = ITM_INSECT41;
            break;
    }
    insect->tools_actor.actor_class.mv_proc = aIDG_actor_move;
    aIDG_setupAction(insect, action, game);
}

static int aIDG_check_strike_stone(aINS_INSECT_ACTOR* insect) {
    int ret;
    int bx, bz;

    ret = FALSE;
    if ((aINS_CLIP->pl_action == aINS_PL_ACT_REFLECT_AXE) || (aINS_CLIP->pl_action == aINS_PL_ACT_REFLECT_SCOOP)) {
        mFI_Wpos2UtNum(&bx, &bz, insect->tools_actor.actor_class.world.position);
        if ((aINS_CLIP->pl_action_ut_x == bx) && (aINS_CLIP->pl_action_ut_z == bz)) {
            ret = TRUE;
        }
    }
    return ret;
}

static int aIDG_check_ball(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;

    ret = FALSE;

    xDiff = Common_Get(ball_pos).x - insect->tools_actor.actor_class.world.position.x;
    zDiff = Common_Get(ball_pos).z - insect->tools_actor.actor_class.world.position.z;

    if ((SQ(xDiff) + SQ(zDiff)) < SQ(60.0f)) {
        ret = TRUE;
    }

    return ret;
}

static int aIDG_check_player_net(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;
    xyz_t pos;

    ret = FALSE;
    if (mPlib_Check_StopNet(&pos) == TRUE) {
        xDiff = pos.x - insect->tools_actor.actor_class.world.position.x;
        zDiff = pos.z - insect->tools_actor.actor_class.world.position.z;

        if ((SQ(xDiff) + SQ(zDiff)) < SQ(70.0f)) {
            ret = TRUE;
        }
    }

    return ret;
}

static int aIDG_check_player_scoop(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;
    xyz_t pos;

    ret = FALSE;
    if (mPlib_Check_DigScoop(&pos) == TRUE) {
        xDiff = pos.x - insect->tools_actor.actor_class.world.position.x;
        zDiff = pos.z - insect->tools_actor.actor_class.world.position.z;

        if ((SQ(xDiff) + SQ(zDiff)) < SQ(70.0f)) {
            ret = TRUE;
        }
    }

    return ret;
}

static int aIDG_check_player_axe(aINS_INSECT_ACTOR* insect) {
    f32 xDiff;
    f32 zDiff;
    int ret;
    xyz_t pos;

    ret = FALSE;
    if (mPlib_Check_HitAxe(&pos) == TRUE) {
        xDiff = pos.x - insect->tools_actor.actor_class.world.position.x;
        zDiff = pos.z - insect->tools_actor.actor_class.world.position.z;

        if ((SQ(xDiff) + SQ(zDiff)) < SQ(70.0f)) {
            ret = TRUE;
        }
    }

    return ret;
}

static int aIDG_check_patience(aINS_INSECT_ACTOR* insect) {
    int ret;

    ret = FALSE;
    if ((insect->ut_x == -1) && (insect->ut_z == -1)) {
        if (aIDG_check_ball(insect) == TRUE) {
            insect->patience = 100.0f;
        } else if (aIDG_check_player_net(insect) == TRUE) {
            insect->patience = 100.0f;
        } else if (aIDG_check_player_scoop(insect) == TRUE) {
            insect->patience = 100.0f;
        } else if (aIDG_check_player_axe(insect) == TRUE) {
            insect->patience = 100.0f;
        }
        if (insect->patience > 90.0f) {
            ret = TRUE;
        }
    }
    return ret;
}

static int aIDG_chk_active_range(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 z, x;
    int ret;

    ret = TRUE;
    x = insect->f32_work2 - actorx->world.position.x;
    z = insect->f32_work3 - actorx->world.position.z;
    if ((SQ(x) + SQ(z)) >= SQ(400.0f)) {
        ret = FALSE;
    }
    return ret;
}

static int aIDG_chk_water_attr(aINS_INSECT_ACTOR* insect, GAME* game) {
    int ret = FALSE;

    if (insect->tools_actor.actor_class.bg_collision_check.result.on_ground) {
        xyz_t pos = insect->tools_actor.actor_class.world.position;
        f32 speed = insect->bg_range + insect->tools_actor.actor_class.speed;
        s16 yAngle = insect->tools_actor.actor_class.world.angle.y;

        pos.x += speed * sin_s(yAngle);
        pos.z += speed * cos_s(yAngle);

        if (mCoBG_CheckWaterAttribute(mCoBG_Wpos2BgAttribute_Original(pos))) {
            aIDG_setupAction(insect, aIDG_ACTION_DIVE, game);
            ret = TRUE;
        }
    }

    return ret;
}

static void aIDG_calc_direction_angl(aINS_INSECT_ACTOR* insect) {
    if (insect->tools_actor.actor_class.bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) {
        int wallCount = insect->tools_actor.actor_class.bg_collision_check.result.hit_wall_count & 7;
        if (wallCount != 0) {
            int i;

            for (i = 0; i < wallCount; i++) {
                mCoBG_WallInfo_c* info = &insect->tools_actor.actor_class.bg_collision_check.wall_info[i];
                if (info->type == 0) {
                    insect->tools_actor.actor_class.world.angle.y =
                        insect->tools_actor.actor_class.bg_collision_check.wall_info[i].angleY + 0x4000;
                    break;
                }
            }
        }
    }
    chase_angle(&insect->tools_actor.actor_class.shape_info.rotation.y, insect->tools_actor.actor_class.world.angle.y,
                0x800);
}

static void aIDG_set_chase_ball_angle(aINS_INSECT_ACTOR* insect) {
    ACTOR* actorx = (ACTOR*)insect;
    s16 angle = search_position_angleY(&actorx->world.position, &actorx->parent_actor->world.position);

    actorx->world.angle.y = angle;
    chase_angle(&actorx->shape_info.rotation.y, angle + insect->s32_work1, 0x800);
}

static int aIDG_fun_check_chase_condition(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* parent = insect->tools_actor.actor_class.parent_actor;
    ACTOR* actorx = (ACTOR*)insect;
    int ret = FALSE;

    if (Common_Get(ball_type) & 0x10) {
        // ball is destroyed
        actorx->parent_actor = NULL;
    } else {
        f32 ball_dist = search_position_distanceXZ(&actorx->world.position, &parent->world.position);

        if (ball_dist > 60.0f) {
            // ball is too far away
            actorx->parent_actor = NULL;
            aIDG_setupAction(insect, aIDG_ACTION_LOSE_HEART, game);
        } else if (insect->action == aIDG_ACTION_CARRY_BALL && ball_dist > 25.0f) {
            aIDG_setupAction(insect, aIDG_ACTION_TURN_BODY_SEARCH, game);
        } else if (!aIDG_chk_water_attr(insect, game)) {
            if (!aIDG_chk_active_range(actorx)) {
                aIDG_setupAction(insect, aIDG_ACTION_LOSE_HEART, game);
            } else {
                ret = TRUE;
            }
        }
    }

    return ret;
}

static void aIDG_fun_set_collision(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    CollisionCheck_Uty_ActorWorldPosSetPipeC((ACTOR*)insect, &insect->col_pipe);
    CollisionCheck_setOC(game, &play->collision_check, &insect->col_pipe.collision_obj);
}

static void aIDG_fun_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.25f;
    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static void aIDG_fun_fly_anime_proc(aINS_INSECT_ACTOR* insect) {
    insect->_1E0 += 0.5f;
    if (insect->_1E0 >= 3.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static void aIDG_avoid(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    int bx, bz;
    if (aIDG_chk_water_attr(insect, game) == FALSE) {
        if (aIDG_chk_active_range(actor) == FALSE) {
            aIDG_setupAction(insect, aIDG_ACTION_RETIRE, game);
        } else {
            aIDG_calc_direction_angl(insect);
            if (insect->bg_type == aINS_BG_CHECK_TYPE_NO_UNIT_COLUMN_NO_ATTR) {
                mFI_Wpos2UtNum(&bx, &bz, insect->tools_actor.actor_class.world.position);
                if ((insect->ut_x != bx) || ((s16)insect->ut_z != bz)) {
                    insect->ut_x = -1;
                    insect->ut_z = -1;
                    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
                }
            } else if (aIDG_check_patience(insect) == TRUE) {
                aIDG_setupAction(insect, aIDG_ACTION_STOP, game);
            }
        }
    }
}

static void aIDG_let_escape(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    if (aIDG_chk_water_attr(insect, game) == FALSE) {
        aIDG_calc_direction_angl(insect);
    }
}

static void aIDG_stop(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    if ((aIDG_chk_water_attr(insect, game) == FALSE) && (insect->patience < 50.0f)) {
        aIDG_setupAction(insect, aIDG_ACTION_AVOID, game);
    }
}

static void aIDG_hide(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*) game;
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;

    if (aIDG_check_strike_stone(insect) == TRUE) {
        aIDG_setupAction(insect, aIDG_ACTION_APPEAR, &play->game);
    }
}

static void aIDG_appear(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    if (insect->tools_actor.actor_class.bg_collision_check.result.on_ground) {
        aIDG_setupAction(insect, aIDG_ACTION_STOP, game);
    }
}

static void aIDG_dive(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*) game;
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    
    if (actor->world.position.y <=
        mCoBG_GetWaterHeight_File(actor->world.position, "ac_ins_dango.c", 876)) {
        aIDG_setupAction(insect, aIDG_ACTION_DROWN, &play->game);
    }
}

static void aIDG_turn_body(ACTOR* actorx, GAME* game) {
    static s16 anglX_table[] = { 0x2000, 0x0000 };
    static int anglY_table[] = { 0x8000, 0x0000 };
    static int anglY_add[] = { 0x1000, -0x1000 };

    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int idx = 0;
    int doneX;
    int doneY;

    if (insect->action != aIDG_ACTION_TURN_BODY) {
        idx = 1;
    }
    
    doneX = chase_angle(&actorx->shape_info.rotation.x, anglX_table[idx], 0x800);
    insect->s32_work1 += anglY_add[idx];
    if ((anglY_table[idx] - insect->s32_work1) * anglY_add[idx] < 0) {
        insect->s32_work1 = anglY_table[idx];
        doneY = TRUE;
    } else {
        doneY = FALSE;
    }
    
    if (doneX == TRUE && doneY == TRUE) {
        aIDG_setupAction(insect, insect->action + 1, game);
    }
}

static void aIDG_carry_ball(ACTOR* actorx, GAME* game) {
    aIDG_fun_anime_proc((aINS_INSECT_ACTOR*)actorx);
    if (aIDG_fun_check_chase_condition((aINS_INSECT_ACTOR*)actorx, game) == TRUE) {
        aIDG_set_chase_ball_angle((aINS_INSECT_ACTOR*)actorx);
        aIDG_fun_set_collision((aINS_INSECT_ACTOR*)actorx, game);
    }
}

static void aIDG_search_ball(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIDG_fun_anime_proc(insect);
    if (aIDG_fun_check_chase_condition(insect, game) == TRUE) {
        aIDG_set_chase_ball_angle(insect);
        
        if (ClObj_DID_COLLIDE(insect->col_pipe.collision_obj) && insect->col_pipe.collision_obj.collided_actor == actorx->parent_actor) {
            aIDG_setupAction(insect, aIDG_ACTION_TURN_BODY, game);
        }

        aIDG_fun_set_collision(insect, game);
    }
}

static void aIDG_lose_heart(ACTOR* actorx, GAME* game) {
    static s16 angle_table[] = { 0x300, -0x300 };
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (chase_angle(&actorx->shape_info.rotation.x, DEG2SHORT_ANGLE2(0.0f), 0x100) == TRUE) {
        if (insect->s32_work2 == 0) {
            if (chase_angle(&actorx->shape_info.rotation.y, actorx->world.angle.y + angle_table[insect->s32_work3 & 1], 0x80) == TRUE) {
                if (insect->s32_work3 == 0) {
                    insect->s32_work2 = (10.0f + RANDOM_F(10.0f)) * 2.0f;
                    insect->s32_work3 = 3 + RANDOM(2);
                } else {
                    insect->s32_work3--;
                }
            }
        } else {
            insect->s32_work2--;
        }
    }

    insect->s32_work0--;
    if (insect->s32_work0 < 0) {
        aIDG_setupAction(insect, aIDG_ACTION_WALK, game);
    }
}

static void aIDG_walk(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIDG_fun_anime_proc(insect);
    if (aIDG_chk_water_attr(insect, game) == FALSE) {
        aIDG_calc_direction_angl(insect);
        insect->s32_work0--;
        if (insect->s32_work0 <= 0) {
            aIDG_setupAction(insect, aIDG_ACTION_FLY_AWAY, game);
        }
    }
}

static void aIDG_fly_away(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 gravity;

    aIDG_fun_fly_anime_proc(insect);
    gravity = actorx->gravity;
    gravity *= 1.1f;
    if (gravity > 12.0f) {
        gravity = 12.0f;
    }

    actorx->gravity = gravity;
    sAdo_OngenPos((u32)insect, NA_ONGEN_POS_SE_25, &actorx->world.position);
}

static void aIDG_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;
    s16 angle;

    insect->tools_actor.actor_class.speed = 1.5f;
    insect->target_speed = 1.5f;
    insect->speed_step = 0.3f;
    insect->_1E0 = 1.0f;

    player = get_player_actor_withoutCheck(play);
    if (player != NULL) {
        angle = player->actor_class.shape_info.rotation.y + (s16)(21845.0f * (fqrand() - 0.5f));
        insect->tools_actor.actor_class.world.angle.y = angle;
        insect->tools_actor.actor_class.shape_info.rotation.y = angle;
    }
}

static void aIDG_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    insect->tools_actor.actor_class.gravity = 2.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    aIDG_avoid_init(insect, game);
    insect->insect_flags.catch_disabled = TRUE;
    insect->insect_flags.ignore_escape_pending = TRUE;
}

static void aIDG_stop_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->target_speed = 0.0f;
    insect->speed_step = 0.05f;
    insect->_1E0 = 0.0f;
}

static void aIDG_hide_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->bg_type = aINS_BG_CHECK_TYPE_NO_UNIT_COLUMN_NO_ATTR;
    insect->tools_actor.actor_class.gravity = 2.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    insect->tools_actor.actor_class.drawn = FALSE;
}

static void aIDG_appear_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    aIDG_avoid_init(insect, game);
    insect->tools_actor.actor_class.drawn = TRUE;
    insect->_1E0 = 0.0f;
    insect->tools_actor.actor_class.position_speed.y = 12.0f;
}

static void aIDG_dive_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 1.5f;
    insect->speed_step = 0.3f;
    insect->target_speed = 1.5f;
    insect->tools_actor.actor_class.position_speed.y = 8.0f;
    insect->_1E0 = 0.0f;
    insect->insect_flags.catch_disabled = TRUE;
}

static void aIDG_drown_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    xyz_t pos = insect->tools_actor.actor_class.world.position;
    f32 height = mCoBG_GetWaterHeight_File(pos, "ac_ins_dango.c", 1241);

    pos.y = height;

    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_MIZU, pos, 1, insect->tools_actor.actor_class.world.angle.y, game, 0, 4, 0);
    sAdo_OngenTrgStart(0x438, &insect->tools_actor.actor_class.world.position);

    insect->insect_flags.catch_disabled = TRUE;
    insect->insect_flags.destruct = TRUE;
    insect->tools_actor.actor_class.shape_info.draw_shadow = FALSE;
}

static void aIDG_retire_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->life_time = 0;
    insect->alpha_time = 0x50;
    insect->tools_actor.actor_class.shape_info.rotation.x = 0;
    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    insect->insect_flags.catch_disabled = TRUE;
    insect->insect_flags.ignore_escape_pending = TRUE;
}

static void aIDG_turn_body_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->target_speed = 0.0f;
    insect->_1E0 = 0.0f;
}

static void aIDG_carry_ball_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    insect->tools_actor.actor_class.gravity = 2.0f;
    insect->tools_actor.actor_class.max_velocity_y = -20.0f;
    insect->speed_step = 0.1f;
    insect->target_speed = 1.0f;
}

static void aIDG_lose_heart_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->tools_actor.actor_class.speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->target_speed = 0.0f;
    insect->s32_work0 = 120;
    insect->_1E0 = 0.0f;
    insect->tools_actor.actor_class.world.angle.y = insect->tools_actor.actor_class.shape_info.rotation.y;
}

static void aIDG_walk_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->speed_step = 0.1f;
    insect->target_speed = 1.0f;
    insect->s32_work0 = 300;
    insect->tools_actor.actor_class.world.angle.y = insect->tools_actor.actor_class.shape_info.rotation.y;
}

static void aIDG_fly_away_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->tools_actor.actor_class.gravity = 0.06f;
    insect->tools_actor.actor_class.max_velocity_y = 12.0f;
    insect->tools_actor.actor_class.speed = 4.0f;
    aIDG_retire_init(insect, game);
}

typedef void (*aIBT_INIT_PROC)(aINS_INSECT_ACTOR*, GAME*);

static void aIDG_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIBT_INIT_PROC init_proc[] = {
        // clang-format off
        aIDG_avoid_init,
        aIDG_let_escape_init,
        aIDG_stop_init,
        aIDG_hide_init,
        aIDG_appear_init,
        aIDG_dive_init,
        aIDG_drown_init,
        aIDG_retire_init,
        aIDG_turn_body_init,
        aIDG_carry_ball_init,
        aIDG_turn_body_init,
        aIDG_carry_ball_init,
        aIDG_lose_heart_init,
        aIDG_walk_init,
        aIDG_fly_away_init,
        aIDG_fly_away_init,
        // clang-format on
    };

    static aINS_ACTION_PROC act_proc[] = {
        // clang-format off
        aIDG_avoid,
        aIDG_let_escape,
        aIDG_stop,
        aIDG_hide,
        aIDG_appear,
        aIDG_dive,
        (aINS_ACTION_PROC)none_proc1,
        aIDG_let_escape,
        aIDG_turn_body,
        aIDG_carry_ball,
        aIDG_turn_body,
        aIDG_search_ball,
        aIDG_lose_heart,
        aIDG_walk,
        aIDG_fly_away,
        aIDG_fly_away,
        // clang-format on
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}


static void aIDG_actor_move(ACTOR* actor, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
 
    u32 label = mPlib_Get_item_net_catch_label();

    if (label == (u32)actor) {
        int action;

        switch (insect->type) {
            case aINS_INSECT_TYPE_DUNG_BEETLE:
                action = aIDG_ACTION_FLY_AWAY_LET_ESCAPE;
                break;
            default:
                action = aIDG_ACTION_LET_ESCAPE;
                break;
        }

        insect->alpha0 = 255;
        aIDG_setupAction(insect, action, game);
    } else {
        insect->action_proc(actor,game);
    }
}
