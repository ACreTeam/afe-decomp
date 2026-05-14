#include "ac_ins_kani.h"

#include "m_field_info.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "ac_set_ovl_insect.h"

enum {
    aIKN_ACT_AVOID,
    aIKN_ACT_LET_ESCAPE,
    aIKN_ACT_HIDE_KANI,
    aIKN_ACT_WAIT,
    aIKN_ACT_MOVE,
    aIKN_ACT_DUG,
    aIKN_ACT_APPEAR_KANI,
    aIKN_ACT_APPEAR_FROM_SHELL,
    aIKN_ACT_INTO_SHELL,
    aIKN_ACT_CAMOUFLAGE,
    aIKN_ACT_TURN,
    aIKN_ACT_DUG_WATER,
    aIKN_ACT_DIVE,
    aIKN_ACT_DROWN,
    aIKN_ACT_ESCAPE_CONT,
    aIKN_ACT_HIDE_YASI,
    aIKN_ACT_FALL_YASI,
    aIKN_ACT_BOUND_YASI,
    aIKN_ACT_STRUGGLE_YASI,
    aIKN_ACT_ROLL_YASI,

    aIKN_ACT_NUM
};

static void aIKN_actor_move(ACTOR* actorx, GAME* game);
static void aIKN_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game);

extern void aIKN_actor_init(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int ux, uz;
    int action;
    
    switch (insect->type) {
        case aINS_INSECT_TYPE_CRAB:
            insect->item = ITM_INSECT44;
            break;
        case aINS_INSECT_TYPE_HERMIT_CRAB:
            insect->item = ITM_INSECT46;
            break;
        case aINS_INSECT_TYPE_COCONUT_CRAB:
            insect->item = ITM_INSECT47;
            break;
    }

    insect->tools_actor.actor_class.mv_proc = aIKN_actor_move;

    if (insect->tools_actor.actor_class.actor_specific == 0) {
        switch (insect->type) {
            case aINS_INSECT_TYPE_CRAB:
                action = aIKN_ACT_HIDE_KANI;
                break;
            case aINS_INSECT_TYPE_HERMIT_CRAB:
                action = aIKN_ACT_CAMOUFLAGE;
                break;
            case aINS_INSECT_TYPE_COCONUT_CRAB:
                actorx->world.position.y = 5.0f + mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, -60.0f);
                actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(47.8125f); //0x2200;
                actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(180.0f);
                actorx->world.angle.x = DEG2SHORT_ANGLE2(47.8125f); //0x2200;
                mFI_Wpos2UtNum(&insect->s32_work1, &insect->s32_work2, actorx->world.position);
                actorx->shape_info.draw_shadow = FALSE;
                action = aIKN_ACT_HIDE_YASI;
                break;
        }

        xyz_t_move(&actorx->home.position, &actorx->world.position);
        mFI_BkNum2WposXZ(&insect->f32_work2, &insect->f32_work3, actorx->block_x, actorx->block_z);
        insect->f32_work2 += mFI_BK_WORLDSIZE_HALF_X_F;
        insect->f32_work3 += mFI_BK_WORLDSIZE_HALF_Z_F;
    } else {
        actorx->drawn = TRUE;
        action = aIKN_ACT_LET_ESCAPE;
    }

    aIKN_setupAction(insect, action, game);
}

static int aIKN_chase_angleY(aINS_INSECT_ACTOR* insect, s16 targetY, s16 step) {
    int ret = chase_angle(&insect->tools_actor.actor_class.shape_info.rotation.y, targetY, step);
    
    if (insect->type == aINS_INSECT_TYPE_COCONUT_CRAB) {
        insect->tools_actor.actor_class.world.angle.y = insect->tools_actor.actor_class.shape_info.rotation.y;
    }

    return ret;
}

static void aIKN_set_mud_effect(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;
    int count = 3 + RANDOM_F(3);

    eEC_CLIP->effect_make_proc(eEC_EFFECT_DIG_MUD, actorx->world.position, 2, actorx->shape_info.rotation.y, game, RSV_NO, 0, 0x4000 | count);
}

static void aIKN_set_water_effect(ACTOR* actorx, GAME* game) {
    xyz_t pos = actorx->world.position;

    pos.y = mCoBG_GetWaterHeight_File(pos, __FILE__, 329);
    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_MIZU, pos, 1, actorx->world.angle.y, game, EMPTY_NO, 4, 0);
    sAdo_OngenTrgStart(0x438, &actorx->world.position);
}

static int aIKN_chk_player_scoop(ACTOR* actorx) {
    xyz_t pos;
    int ret = FALSE;

    if (mPlib_Check_DigScoop(&pos) == TRUE) {
        float dx = pos.x - actorx->world.position.x;
        float dz = pos.z - actorx->world.position.z;

        if (SQ(dx) + SQ(dz) < SQ(60.0f)) {
            ret = TRUE;
        }
    }

    return ret;
}

static s16 aIKN_chk_shape_angle(s16 angle) {
    s16 ret;

    if ((u16)angle > (u16)DEG2SHORT_ANGLE2(270.0f)) {
        angle += (u16)DEG2SHORT_ANGLE2(-180.0f);
    } else if ((u16)angle < (u16)DEG2SHORT_ANGLE2(90.0f)) {
        angle += (u16)DEG2SHORT_ANGLE2(180.0f);
    }

    if ((u16)angle >= (u16)DEG2SHORT_ANGLE2(180.0f)) {
        angle -= DEG2SHORT_ANGLE2(90.0f);
    } else {
        angle += DEG2SHORT_ANGLE2(90.0f);
    }

    return angle;
}

static int aIKN_set_angle(ACTOR* actorx, s16 angle) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int ret = FALSE;

    if (insect->f32_work1 <= 0.0f) {
        switch (insect->type) {
            case aINS_INSECT_TYPE_CRAB:
                insect->tools_actor.actor_class.world.angle.y = angle;
                insect->s32_work0 = aIKN_chk_shape_angle(angle);
                break;
            case aINS_INSECT_TYPE_HERMIT_CRAB:
                insect->tools_actor.actor_class.world.angle.y = angle;
                insect->s32_work0 = angle;
                break;
            case aINS_INSECT_TYPE_COCONUT_CRAB:
                insect->s32_work0 = angle;
                break;
        }

        insect->f32_work1 = 6.0f + RANDOM_F(12.0f);
        ret = TRUE;
    }

    return ret;
}

static void aIKN_set_avoid_player_angl(ACTOR* actorx, GAME* game, int avoid) {
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (playerx != NULL) {
        f32 dx = actorx->world.position.x - playerx->world.position.x;
        f32 dz = actorx->world.position.z - playerx->world.position.z;
        s16 angl = atans_table(dz, dx);
        s16 avoid_angl;

        if (avoid) {
            angl += RANDOM_CENTER(DEG2SHORT_ANGLE2(120.0f));
            avoid_angl = angl - actorx->world.angle.y;

            if (ABS(avoid_angl) > DEG2SHORT_ANGLE2(30.0f)) {
                if (avoid_angl > 0) {
                    angl = actorx->world.angle.y + DEG2SHORT_ANGLE2(30.0f);
                } else {
                    angl = actorx->world.angle.y - DEG2SHORT_ANGLE2(30.0f);
                }
            }
        }

        aIKN_set_angle(actorx, angl);
    }
}

static int aIKN_chk_patience(aINS_INSECT_ACTOR* insect, GAME* game) {
    static u32 chk_flg[] = { mCoBG_HIT_WALL_LEFT, mCoBG_HIT_WALL_RIGHT, mCoBG_HIT_WALL_BACK };
    static s16 add_angl[] = { DEG2SHORT_ANGLE2(90.0f), DEG2SHORT_ANGLE2(-90.0f), DEG2SHORT_ANGLE2(180.0f) };
    ACTOR* actorx = (ACTOR*)insect;
    int ret = FALSE;
    int action;
    int i;
    u32 hit_wall;

    if (aIKN_chk_player_scoop(actorx) == TRUE) {
        insect->patience = 100.0f;
    }

    if (insect->patience > 70.0f) {
        switch (insect->type) {
            case aINS_INSECT_TYPE_CRAB:
                if (insect->action == aIKN_ACT_HIDE_KANI) {
                    action = aIKN_ACT_APPEAR_KANI;
                } else {
                    action = aIKN_ACT_AVOID;
                }
                break;
            case aINS_INSECT_TYPE_HERMIT_CRAB:
            case aINS_INSECT_TYPE_COCONUT_CRAB:
                if (insect->s32_work2 == 1) {
                    hit_wall = actorx->bg_collision_check.result.hit_wall;

                    for (i = 0; i < ARRAY_COUNT(chk_flg); i++) {
                        if ((hit_wall & chk_flg[i]) == 0) {
                            break;
                        }
                    }

                    if (i < ARRAY_COUNT(chk_flg)) {
                        insect->f32_work1 = 0.0f;
                        // @BUG - devs added to the angle by [-0.5, 0.5) instead of multiplying (center)
#ifndef BUGFIXES
                        aIKN_set_angle(actorx, actorx->shape_info.rotation.y + add_angl[i] + (int)((fqrand() - 0.5f) + (DEG2SHORT_ANGLE2(45.0f))));
#else
                        aIKN_set_angle(actorx, actorx->shape_info.rotation.y + add_angl[i] + RANDOM_CENTER(DEG2SHORT_ANGLE2(45.0f)));
#endif
                        action = aIKN_ACT_APPEAR_FROM_SHELL;
                    }
                } else {
                    aIKN_set_avoid_player_angl(actorx, game, DEG2SHORT_ANGLE2(0.0f));
                    action = aIKN_ACT_APPEAR_FROM_SHELL;
                }
                break;
        }

        // @BUG - action is never set in the case where hermit/coconut crabs are not blocked?
        aIKN_setupAction(insect, action, game);
        ret = TRUE;
    }

    return ret;
}

static void aIKN_anime_proc(aINS_INSECT_ACTOR* insect) {
    switch (insect->type) {
        case aINS_INSECT_TYPE_CRAB:
        case aINS_INSECT_TYPE_COCONUT_CRAB:
            insect->_1E0 += 0.25f;
            break;
        case aINS_INSECT_TYPE_HERMIT_CRAB:
            if ((int)insect->_1E0 == 0) {
                insect->_1E0 += 0.125f;
            } else {
                insect->_1E0 += 0.175f;
            }
            break;
    }

    if (insect->_1E0 >= 2.0f) {
        insect->_1E0 -= 2.0f;
    }
}

static int aIKN_calc_alpha(aINS_INSECT_ACTOR* insect) {
    int alpha = insect->alpha0;
    int ret = FALSE;

    if (insect->insect_flags.ignore_escape_pending == 0) {
        switch (insect->action) {
            case aIKN_ACT_DUG:
                alpha -= 11;
                if (alpha <= 0) {
                    alpha = 0;
                    ret = TRUE;
                }
                break;
            case aIKN_ACT_APPEAR_KANI:
                alpha += 11;
                if (alpha >= 255) {
                    alpha = 255;
                    ret = TRUE;
                }
                break;
        }

        insect->alpha0 = alpha;
    }

    insect->bg_height = (1.0f - alpha / 255.0f) * 10.0f;
    return ret;
}

static int aIKN_calc_direction_angl(ACTOR* actorx) {
    int ret = FALSE;

    if ((actorx->bg_collision_check.result.hit_wall & mCoBG_HIT_WALL_FRONT) != 0 || actorx->bg_collision_check.result.unk_flag4) {
        xyz_t_move(&actorx->world.position, &actorx->last_world_position);
        ret = aIKN_set_angle(actorx, actorx->shape_info.rotation.y + DEG2SHORT_ANGLE2(180.0f) + RANDOM_CENTER(DEG2SHORT_ANGLE2(67.5f)));
    }

    return ret;
}

static int aIKN_chk_dug_attr(ACTOR* actorx) {
    int ret = FALSE;

    switch (mCoBG_Wpos2BgAttribute_Original(actorx->world.position)) {
        case mCoBG_ATTRIBUTE_GRASS0:
        case mCoBG_ATTRIBUTE_GRASS1:
        case mCoBG_ATTRIBUTE_GRASS2:
        case mCoBG_ATTRIBUTE_GRASS3:
        case mCoBG_ATTRIBUTE_SOIL0:
        case mCoBG_ATTRIBUTE_SOIL1:
        case mCoBG_ATTRIBUTE_SOIL2:
        case mCoBG_ATTRIBUTE_SAND:
        case mCoBG_ATTRIBUTE_25:
        case mCoBG_ATTRIBUTE_26:
        case mCoBG_ATTRIBUTE_36:
        case mCoBG_ATTRIBUTE_37:
        case mCoBG_ATTRIBUTE_38:
            ret = TRUE;
            break;
    }

    return ret;
}

static int aIKN_chk_active_range(ACTOR* actorx) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int ux;
    int uz;
    int ret = FALSE;

    mFI_Wpos2UtNum_inBlock(&ux, &uz, actorx->world.position);
    if ((ux < 2 || ux >= 14) || (uz < 2 || uz >= 14)) {
        xyz_t_move(&actorx->world.position, &actorx->last_world_position);
        ret = aIKN_set_angle(actorx, atans_table(insect->f32_work3 - actorx->world.position.z, insect->f32_work2 - actorx->world.position.x));
    }

    return ret;
}

static int aIKN_chk_cut_tree(aINS_INSECT_ACTOR* insect) {
    int ret = FALSE;
    mActor_name_t* fg_p = mFI_GetUnitFG(insect->tools_actor.actor_class.home.position);

    if (fg_p == NULL || IS_ITEM_TREE_STUMP(*fg_p) == TRUE) {
        ret = TRUE;
    }

    return ret;
}

static int aIKN_chk_shake_tree(aINS_INSECT_ACTOR* insect) {
    int ret = FALSE;

    if (aINS_CLIP->pl_action == aINS_PL_ACT_SHAKE_TREE && aINS_CLIP->pl_action_ut_x == insect->s32_work1 && aINS_CLIP->pl_action_ut_z == insect->s32_work2) {
        ret = TRUE;
    }

    return ret;
}

static void aIKN_set_yasi_start_pos(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (playerx != NULL) {
        float x;
        float z;

        if (playerx->world.position.x < actorx->home.position.x) {
            x = actorx->home.position.x + 30.0f;
            z = actorx->home.position.z + -18.0f;
        } else {
            x = actorx->home.position.x - 30.0f;
            z = actorx->home.position.z + -25.0f;
        }

        actorx->world.position.x = x;
        actorx->world.position.y = 5.0f + mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, -60.0f);
        actorx->world.position.z = z;
    }
}

static void aIKN_avoid(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    int flag = FALSE;
    int action = -1;

    aIKN_anime_proc(insect);
    sAdo_OngenPos((u32)insect, NA_ONGEN_POS_SE_63, &insect->tools_actor.actor_class.world.position); // TODO: 0x60 is last ongen entry in AC

    if (actorx->bg_collision_check.result.jump_flag) {
        action = aIKN_ACT_DIVE;
    } else {
        insect->f32_work1 -= 1.0f;
        if (insect->action == aIKN_ACT_AVOID) {
            flag = aIKN_calc_direction_angl(actorx);
            if (flag == FALSE) {
                aIKN_chk_active_range(actorx);
            }
        } else {
            aIKN_calc_direction_angl(actorx);
        }

        aIKN_chase_angleY(insect, insect->s32_work0, 0x200);
        if (insect->patience < 10.0f) {
            if (insect->action == aIKN_ACT_AVOID) {
                switch (insect->type) {
                    case aINS_INSECT_TYPE_CRAB:
                    case aINS_INSECT_TYPE_COCONUT_CRAB:
                        action = aIKN_ACT_WAIT;
                        break;
                    case aINS_INSECT_TYPE_HERMIT_CRAB:
                        action = aIKN_ACT_INTO_SHELL;
                        break;
                }
            } else if (aIKN_chk_dug_attr(actorx) == TRUE) {
                action = aIKN_ACT_DUG;
            }
        } else {
            if (insect->type == aINS_INSECT_TYPE_HERMIT_CRAB && flag == TRUE && insect->action == aIKN_ACT_AVOID) {
                insect->s32_work2 = 1;
                action = aIKN_ACT_INTO_SHELL;
            }
        }

        if (actorx->world.position.y <= 3.0f) {
            action = aIKN_ACT_DUG_WATER;
        }
    }

    if (action != -1) {
        aIKN_setupAction(insect, action, game);
    } else {
        aIKN_set_avoid_player_angl(actorx, game, TRUE);
    }
}

static void aIKN_hide_kani(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIKN_chk_patience(insect, game);
}

static void aIKN_wait(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (insect->type == aINS_INSECT_TYPE_CRAB) {
        insect->s32_work3 += 0x200;
        insect->tools_actor.actor_class.shape_info.rotation.x = DEG2SHORT_ANGLE2(-8.4375f) * ABS(sin_s(insect->s32_work3));
    }

    if (!aIKN_chk_patience(insect, game)) {
        insect->timer--;
        if (insect->timer < 0) {
            int action = aIKN_ACT_MOVE;

            if (insect->type == aINS_INSECT_TYPE_CRAB && aIKN_chk_dug_attr(actorx) == TRUE && RANDOM_F(1.0f) < 0.2f) {
                action = aIKN_ACT_DUG;
            }

            aIKN_setupAction(insect, action, game);
        }
    }
}

static void aIKN_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIKN_anime_proc(insect);
    sAdo_OngenPos((u32)insect, NA_ONGEN_POS_SE_63, &actorx->world.position);

    if ((actorx->bg_collision_check.result.jump_flag) != 0) {
        aIKN_setupAction(insect, aIKN_ACT_DIVE, game);
    } else {
        if (aIKN_calc_direction_angl(actorx) == FALSE) {
            aIKN_chk_active_range(actorx);
        }

        aIKN_chase_angleY(insect, insect->s32_work0, 0x80);
        if (aIKN_chk_patience(insect, game) == FALSE) {
            insect->timer--;

            if (insect->timer < 0) {
                aIKN_setupAction(insect, aIKN_ACT_WAIT, game);
            }
        }
    }
}

static void aIKN_dug(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    s16 target;
    s16 step;
    s16* angl_p;

    aIKN_anime_proc(insect);
    switch (insect->type) {
        case aINS_INSECT_TYPE_CRAB:
            angl_p = &actorx->shape_info.rotation.z;
            // @BUG!! missing target set
            // target = 0x1800;
            step = 0x400;
            break;
        case aINS_INSECT_TYPE_HERMIT_CRAB:
            angl_p = &actorx->shape_info.rotation.x;
            target = 0x1800;
            step = 0x400;
            break;
        case aINS_INSECT_TYPE_COCONUT_CRAB:
            angl_p = &actorx->shape_info.rotation.z;
            target = 0x7000;
            step = 0x300;
            break;
    }

    if (chase_angle(angl_p, target, step) == TRUE && insect->action == aIKN_ACT_DUG_WATER) {
        aIKN_set_water_effect(actorx, game);
        insect->insect_flags.destruct = TRUE;
    } else if (insect->action != aIKN_ACT_DUG_WATER) {
        insect->f32_work1 -= 1.0f;
        if (insect->f32_work1 <= 0.0f) {
            aIKN_set_mud_effect(insect, game);
            insect->f32_work1 = 6.0f;
        }

        if (aIKN_calc_alpha(insect) == TRUE) {
            aIKN_setupAction(insect, aIKN_ACT_HIDE_KANI, game);
        }
    }
}

static void aIKN_appear_kani(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIKN_anime_proc(insect);
    chase_angle(&actorx->shape_info.rotation.z, DEG2SHORT_ANGLE2(0.0f), 0x300);
    if (aIKN_calc_alpha(insect) == TRUE) {
        aIKN_setupAction(insect, aIKN_ACT_AVOID, game);
    }
}

static void aIKN_appear_from_shell(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIKN_anime_proc(insect);
    sAdo_OngenPos((u32)insect, NA_ONGEN_POS_SE_63, &actorx->world.position);
    insect->continue_timer += 15;
    if (insect->continue_timer > 100) {
        int action = aIKN_ACT_AVOID;

        insect->continue_timer = 100;
        if (insect->s32_work2 == 1) {
            action = aIKN_ACT_TURN;
        }

        aIKN_setupAction(insect, action, game);
    }
}

static void aIKN_into_shell(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIKN_anime_proc(insect);
    sAdo_OngenPos((u32)insect, NA_ONGEN_POS_SE_63, &actorx->world.position);
    insect->continue_timer -= 15;
    if (insect->continue_timer < 0) {
        insect->continue_timer = 0;
        aIKN_setupAction(insect, aIKN_ACT_CAMOUFLAGE, game);
    }
}

static void aIKN_turn(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIKN_anime_proc(insect);
    sAdo_OngenPos((u32)insect, NA_ONGEN_POS_SE_63, &actorx->world.position);
    
    if (aIKN_chase_angleY(insect, insect->s32_work0, 0x200) == TRUE) {
        insect->s32_work2 = DEG2SHORT_ANGLE2(0.0f);
        aIKN_setupAction(insect, aIKN_ACT_AVOID, game);
    }
}

static void aIKN_dive(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    f32 water_y = mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 1182);
    int attr_ok = FALSE;
    int action = -1;

    switch (mCoBG_Wpos2BgAttribute_Original(actorx->world.position)) {
        case mCoBG_ATTRIBUTE_SAND:
        case mCoBG_ATTRIBUTE_25:
        case mCoBG_ATTRIBUTE_26:
        case mCoBG_ATTRIBUTE_36:
        case mCoBG_ATTRIBUTE_37:
        case mCoBG_ATTRIBUTE_38:
            attr_ok = TRUE;
            break;
    }

    if (!attr_ok && actorx->world.position.y <= water_y) {
        action = aIKN_ACT_DROWN;
    } else if (actorx->bg_collision_check.result.on_ground) {
        if (insect->insect_flags.ignore_escape_pending == 1) {
            action = aIKN_ACT_ESCAPE_CONT;
        } else {
            action = aIKN_ACT_AVOID;
        }
    }

    if (action != -1) {
        aIKN_setupAction(insect, action, game);
    }
}

static void aIKN_hide_yasi(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (aIKN_chk_cut_tree(insect) == TRUE) {
        aIKN_setupAction(insect, aIKN_ACT_FALL_YASI, game);
    } else if (aIKN_chk_shake_tree(insect) == TRUE) {
        aIKN_setupAction(insect, aIKN_ACT_FALL_YASI, game);
    }
}

static void aIKN_fall_yasi(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (actorx->bg_collision_check.result.on_ground) {
        aIKN_setupAction(insect, aIKN_ACT_BOUND_YASI, game);
    }
}

static void aIKN_bound_yasi(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    if (actorx->bg_collision_check.result.on_ground) {
        aIKN_setupAction(insect, aIKN_ACT_STRUGGLE_YASI, game);
    }
}

static void aIKN_struggle_yasi(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    insect->timer--;
    if (insect->timer <= 120) {
        aIKN_anime_proc(insect);
        sAdo_OngenPos((u32)actorx, NA_ONGEN_POS_SE_15, &actorx->world.position);
        if (insect->timer <= 0) {
            aIKN_setupAction(insect, aIKN_ACT_ROLL_YASI, game);
        }
    }
}

static void aIKN_roll_yasi(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;

    aIKN_anime_proc(insect);
    
    if (chase_angle2(&actorx->shape_info.rotation.x, DEG2SHORT_ANGLE2(0.0f), 0x800) == TRUE) {
        insect->patience = 100.0f;
        aIKN_setupAction(insect, aIKN_ACT_AVOID, game);
    } else {
        insect->bg_height = -10.0f * sin_s((actorx->shape_info.rotation.x >> 1) & 0x7FFF);
    }
}

static void aIKN_avoid_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    switch (insect->type) {
        case aINS_INSECT_TYPE_CRAB:
            insect->target_speed = 1.5f;
            insect->speed_step = 0.15f;
            break;
        case aINS_INSECT_TYPE_HERMIT_CRAB:
            insect->target_speed = 0.7f;
            insect->speed_step = 0.2f;
            break;
        case aINS_INSECT_TYPE_COCONUT_CRAB:
            insect->target_speed = 0.75f;
            insect->speed_step = 0.15f;
            break;
    }

    insect->insect_flags.catch_disabled = FALSE;
}

static void aIKN_let_escape_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;
    
    insect->life_time = 0;
    insect->alpha_time = 80;
    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    actorx->gravity = 2.0f;
    actorx->max_velocity_y = -12.0f;
    aIKN_set_avoid_player_angl(actorx, game, FALSE);
    actorx->shape_info.rotation.x = 0;
    actorx->shape_info.rotation.y = insect->s32_work0;
    actorx->shape_info.rotation.z = 0;
    
    switch (insect->type) {
        case aINS_INSECT_TYPE_CRAB:
            insect->target_speed = 1.5f;
            insect->speed_step = 0.15f;
            break;
        case aINS_INSECT_TYPE_HERMIT_CRAB:
            insect->target_speed = 0.7f;
            insect->speed_step = 0.2f;
            insect->continue_timer = 100;
            break;
        case aINS_INSECT_TYPE_COCONUT_CRAB:
            insect->target_speed = 0.75f;
            insect->speed_step = 0.15f;
            break;
    }

    insect->patience = 25.0f;
    insect->insect_flags.catch_disabled = TRUE;
    insect->insect_flags.ignore_escape_pending = TRUE;
}

static void aIKN_hide_kani_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;
    
    insect->bg_type = aINS_BG_CHECK_TYPE_NONE;
    insect->alpha0 = 0;
    actorx->speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    actorx->position_speed.y = 0.0f;
    actorx->gravity = 0.0f;
    actorx->max_velocity_y = 0.0f;
    actorx->shape_info.rotation.x = 0;
    actorx->drawn = FALSE;
    actorx->shape_info.draw_shadow = FALSE;
    insect->insect_flags.catch_disabled = TRUE;
}

static void aIKN_wait_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    actorx->speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->s32_work3 = 0;
    insect->timer = 240.0f + RANDOM_F(60.0f);
}

static void aIKN_move_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;
    s16 angle;

    insect->target_speed = 1.5f;
    insect->speed_step = 0.15f;

    if (RANDOM_F(1.0f) < 0.3f) {
        angle = actorx->world.angle.y + DEG2SHORT_ANGLE2(180.0f) + (int)(RANDOM_CENTER_F(2.0f) * DEG2SHORT_ANGLE2(30.0f));
    } else {
        angle = actorx->world.angle.y + (int)(RANDOM_CENTER_F(2.0f) * DEG2SHORT_ANGLE2(30.0f));
    }

    aIKN_set_angle(actorx, angle);
    insect->timer = 120.0f + RANDOM_F(120.0f);
}

static void aIKN_dug_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    actorx->shape_info.rotation.x = 0;
    actorx->speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->f32_work1 = 1.0f;
    insect->insect_flags.catch_disabled = TRUE;
    sAdo_OngenTrgStart(0x477, &actorx->world.position);
    actorx->shape_info.draw_shadow = FALSE;
}

static void aIKN_appear_kani_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    actorx->gravity = 2.0f;
    actorx->max_velocity_y = -12.0f;
    aIKN_set_avoid_player_angl(actorx, game, FALSE);
    actorx->shape_info.rotation.x = 0;
    actorx->shape_info.rotation.y = insect->s32_work0;

    if ((u16)actorx->world.angle.y < (u16)DEG2SHORT_ANGLE2(180.0f)) {
        actorx->shape_info.rotation.z = DEG2SHORT_ANGLE2(-33.75f);
    } else {
        actorx->shape_info.rotation.z = DEG2SHORT_ANGLE2(33.75f);
    }

    actorx->shape_info.draw_shadow = TRUE;
    actorx->drawn = TRUE;
    aIKN_set_mud_effect(insect, game);
}

static void aIKN_appear_from_shell_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    insect->continue_timer = 0;
}

static void aIKN_into_shell_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    actorx->speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->continue_timer = 100;
}

static void aIKN_camouflage_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    actorx->gravity = 2.0f;
    actorx->max_velocity_y = -12.0f;
    actorx->speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    insect->_1E0 = 2.0f;
    actorx->shape_info.draw_shadow = FALSE;
}

static void aIKN_drown_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    aIKN_set_water_effect(actorx, game);
    insect->insect_flags.catch_disabled = TRUE;
    insect->insect_flags.destruct = TRUE;
    actorx->shape_info.draw_shadow = FALSE;
}

static void aIKN_escape_cont_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    aIKN_set_avoid_player_angl(actorx, game, FALSE);

    actorx->shape_info.rotation.x = 0;
    actorx->shape_info.rotation.y = insect->s32_work0;
    actorx->shape_info.rotation.z = 0;

    switch (insect->type) {
        case aINS_INSECT_TYPE_CRAB:
            insect->target_speed = 1.5f;
            insect->speed_step = 0.15f;
            break;
        case aINS_INSECT_TYPE_HERMIT_CRAB:
            insect->target_speed = 0.7f;
            insect->speed_step = 0.2f;
            insect->continue_timer = 100;
            break;
        case aINS_INSECT_TYPE_COCONUT_CRAB:
            insect->target_speed = 0.75f;
            insect->speed_step = 0.15f;
            break;
    }
}

static void aIKN_hide_yasi_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    actorx->speed = 0.0f;
    insect->target_speed = 0.0f;
    insect->speed_step = 0.0f;
    actorx->world.position.y = actorx->home.position.y;
    insect->_1E0 = 1.0f;
    actorx->drawn = FALSE;
    insect->insect_flags.catch_disabled = TRUE;
}

static void aIKN_fall_yasi_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    aIKN_set_yasi_start_pos(insect, game);
    actorx->gravity = 2.0f;
    actorx->max_velocity_y = -12.0f;
    insect->move_proc = aINS_CLIP->position_move_proc;
    actorx->drawn = TRUE;
    insect->_1E0 = 0.0f;
    insect->bg_height = -10.0f;
    insect->bg_type = aINS_BG_CHECK_TYPE_REG_NO_ATTR;
    actorx->shape_info.rotation.x = DEG2SHORT_ANGLE2(180.0f);
    actorx->shape_info.rotation.y = 0;
    actorx->shape_info.rotation.z = 0;
    actorx->shape_info.draw_shadow = TRUE;
    insect->insect_flags.catch_disabled = FALSE;
    sAdo_OngenTrgStart(0x478, &actorx->world.position);
}

static void aIKN_bound_yasi_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    actorx->position_speed.y = 6.0f;
    actorx->gravity = 2.0f;
    sAdo_OngenTrgStart(0x419, &actorx->world.position);
}

static void aIKN_struggle_yasi_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    insect->timer = 180;
}

static void aIKN_roll_yasi_init(aINS_INSECT_ACTOR* insect, GAME* game) {
    ACTOR* actorx = (ACTOR*)insect;

    sAdo_OngenTrgStart(0x479, &actorx->world.position);
}

typedef void (*aIKN_INIT_PROC)(aINS_INSECT_ACTOR* insect, GAME* game);

static void aIKN_setupAction(aINS_INSECT_ACTOR* insect, int action, GAME* game) {
    static aIKN_INIT_PROC init_proc[] = {
        // clang-format off
        aIKN_avoid_init,
        aIKN_let_escape_init,
        aIKN_hide_kani_init,
        aIKN_wait_init,
        aIKN_move_init,
        aIKN_dug_init,
        aIKN_appear_kani_init,
        aIKN_appear_from_shell_init,
        aIKN_into_shell_init,
        aIKN_camouflage_init,
        (aIKN_INIT_PROC)none_proc1,
        aIKN_dug_init,
        (aIKN_INIT_PROC)none_proc1,
        aIKN_drown_init,
        aIKN_escape_cont_init,
        aIKN_hide_yasi_init,
        aIKN_fall_yasi_init,
        aIKN_bound_yasi_init,
        aIKN_struggle_yasi_init,
        aIKN_roll_yasi_init,
        // clang-format on
    };

    static aINS_ACTION_PROC act_proc[] = {
        // clang-format off
        aIKN_avoid,
        aIKN_avoid,
        aIKN_hide_kani,
        aIKN_wait,
        aIKN_move,
        aIKN_dug,
        aIKN_appear_kani,
        aIKN_appear_from_shell,
        aIKN_into_shell,
        aIKN_hide_kani,
        aIKN_turn,
        aIKN_dug,
        aIKN_dive,
        (aINS_ACTION_PROC)none_proc1,
        aIKN_avoid,
        aIKN_hide_yasi,
        aIKN_fall_yasi,
        aIKN_bound_yasi,
        aIKN_struggle_yasi,
        aIKN_roll_yasi,
        // clang-format on
    };

    insect->action = action;
    insect->action_proc = act_proc[action];
    (*init_proc[action])(insect, game);
}

static void aIKN_actor_move(ACTOR* actorx, GAME* game) {
    aINS_INSECT_ACTOR* insect = (aINS_INSECT_ACTOR*)actorx;
    u32 label = mPlib_Get_item_net_catch_label();

    if (label == (u32)insect) {
        insect->alpha0 = 255;
        actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(180.0f);
        aIKN_setupAction(insect, aIKN_ACT_LET_ESCAPE, game);
    } else {
        switch (insect->action) {
            case aIKN_ACT_WAIT:
            case aIKN_ACT_HIDE_YASI:
            case aIKN_ACT_FALL_YASI:
            case aIKN_ACT_BOUND_YASI:
            case aIKN_ACT_STRUGGLE_YASI:
            case aIKN_ACT_ROLL_YASI:
                break;
            default:
                chase_angle(&actorx->shape_info.rotation.x, DEG2SHORT_ANGLE2(0.0f), 0x100);
                break;
        }

        (*insect->action_proc)(actorx, game);
    }
}
