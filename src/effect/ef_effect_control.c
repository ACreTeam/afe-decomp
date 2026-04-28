#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_player_lib.h"
#include "m_debug.h"

static eEC_PROFILE_c* profile_tbl[eEC_EFFECT_NUM] = {
    &iam_ef_shock, // eEC_EFFECT_SHOCK
    &iam_ef_dust, // eEC_EFFECT_DUST
    &iam_ef_muka, // eEC_EFFECT_MUKA
    &iam_ef_warau, // eEC_EFFECT_WARAU
    &iam_ef_ha, // eEC_EFFECT_HA
    &iam_ef_sibuki, // eEC_EFFECT_SIBUKI
    &iam_ef_gimonhu, // eEC_EFFECT_GIMONHU
    &iam_ef_kantanhu, // eEC_EFFECT_KANTANHU
    &iam_ef_ase, // eEC_EFFECT_ASE
    &iam_ef_ase_ch, // eEC_EFFECT_ASE_CH
    &iam_ef_kangaeru, // eEC_EFFECT_KANGAERU
    &iam_ef_otikomi, // eEC_EFFECT_OTIKOMI
    &iam_ef_buruburu, // eEC_EFFECT_BURUBURU
    &iam_ef_siawase_hikari, // eEC_EFFECT_SIAWASE_HIKARI
    &iam_ef_siawase_hana, // eEC_EFFECT_SIAWASE_HANA
    &iam_ef_siawase_hana_ch, // eEC_EFFECT_SIAWASE_HANA_CH
    &iam_ef_takurami, // eEC_EFFECT_TAKURAMI
    &iam_ef_takurami_kira, // eEC_EFFECT_TAKURAMI_KIRA
    &iam_ef_kaze, // eEC_EFFECT_KAZE
    &iam_ef_kaze_happa, // eEC_EFFECT_KAZE_HAPPA
    &iam_ef_lovelove, // eEC_EFFECT_LOVELOVE
    &iam_ef_lovelove_heart, // eEC_EFFECT_LOVELOVE_HEART
    &iam_ef_pun, // eEC_EFFECT_PUN
    &iam_ef_pun_yuge, // eEC_EFFECT_PUN_YUGE
    &iam_ef_pun_sekimen, // eEC_EFFECT_PUN_SEKIMEN
    &iam_ef_naku, // eEC_EFFECT_NAKU
    &iam_ef_namida, // eEC_EFFECT_NAMIDA
    &iam_ef_hirameki_den, // eEC_EFFECT_HIRAMEKI_DEN
    &iam_ef_hirameki_hikari, // eEC_EFFECT_HIRAMEKI_HIKARI
    &iam_ef_situren, // eEC_EFFECT_SITUREN
    &iam_ef_ase2, // eEC_EFFECT_ASE2
    &iam_ef_dash_asimoto, // eEC_EFFECT_DASH_ASIMOTO
    &iam_ef_konpu, // eEC_EFFECT_KONPU
    &iam_ef_lovelove2, // eEC_EFFECT_LOVELOVE2
    &iam_ef_kpun, // eEC_EFFECT_KPUN
    &iam_ef_kisha_kemuri, // eEC_EFFECT_KISHA_KEMURI
    &iam_ef_neboke, // eEC_EFFECT_NEBOKE
    &iam_ef_neboke_awa, // eEC_EFFECT_NEBOKE_AWA
    &iam_ef_hanabi_yanagi, // eEC_EFFECT_HANABI_YANAGI
    &iam_ef_hanabi_botan1, // eEC_EFFECT_HANABI_BOTAN1
    &iam_ef_hanabi_botan2, // eEC_EFFECT_HANABI_BOTAN2
    &iam_ef_hanabi_hoshi, // eEC_EFFECT_HANABI_HOSHI
    &iam_ef_hanabi_set, // eEC_EFFECT_HANABI_SET
    &iam_ef_hanabi_switch, // eEC_EFFECT_HANABI_SWITCH
    &iam_ef_footprint, // eEC_EFFECT_FOOTPRINT
    &iam_ef_turn_footprint, // eEC_EFFECT_TURN_FOOTPRINT
    &iam_ef_bubu, // eEC_EFFECT_BUBU
    &iam_ef_turn_asimoto, // eEC_EFFECT_TURN_ASIMOTO
    &iam_ef_string, // eEC_EFFECT_STRING
    &iam_ef_yukihane, // eEC_EFFECT_YUKIHANE
    &iam_ef_anahikari, // eEC_EFFECT_ANAHIKARI
    &iam_ef_bush_happa, // eEC_EFFECT_BUSH_HAPPA
    &iam_ef_bush_yuki, // eEC_EFFECT_BUSH_YUKI
    &iam_ef_tumble, // eEC_EFFECT_TUMBLE
    &iam_ef_tumble_bodyprint, // eEC_EFFECT_TUMBLE_BODYPRINT
    &iam_ef_slip, // eEC_EFFECT_SLIP
    &iam_ef_tumble_dust, // eEC_EFFECT_TUMBLE_DUST
    &iam_ef_swing_net, // eEC_EFFECT_SWING_NET
    &iam_ef_ami_mizu, // eEC_EFFECT_AMI_MIZU
    &iam_ef_mizutama, // eEC_EFFECT_MIZUTAMA
    &iam_ef_yukidama, // eEC_EFFECT_YUKIDAMA
    &iam_ef_kikuzu, // eEC_EFFECT_KIKUZU
    &iam_ef_swing_axe, // eEC_EFFECT_SWING_AXE
    &iam_ef_steam, // eEC_EFFECT_STEAM
    &iam_ef_night15_moon, // eEC_EFFECT_NIGHT15_MOON
    &iam_ef_night13_moon, // eEC_EFFECT_NIGHT13_MOON
    &iam_ef_neboke_akubi, // eEC_EFFECT_NEBOKE_AKUBI
    &iam_ef_slip_footprint, // eEC_EFFECT_SLIP_FOOTPRINT
    &iam_ef_walk_asimoto, // eEC_EFFECT_WALK_ASIMOTO
    &iam_ef_turi_hamon, // eEC_EFFECT_TURI_HAMON
    &iam_ef_turi_mizu, // eEC_EFFECT_TURI_MIZU
    &iam_ef_turi_hane0, // eEC_EFFECT_TURI_HANE0
    &iam_ef_turi_hane1, // eEC_EFFECT_TURI_HANE1
    &iam_ef_turi_suiteki, // eEC_EFFECT_TURI_SUITEKI
    &iam_ef_ongen, // eEC_EFFECT_ONGEN
    &iam_ef_impact_star, // eEC_EFFECT_IMPACT_STAR
    &iam_ef_sandsplash, // eEC_EFFECT_SANDSPLASH
    &iam_ef_young_tree, // eEC_EFFECT_YOUNG_TREE
    &iam_ef_swing_rod, // eEC_EFFECT_SWING_ROD
    &iam_ef_doyon, // eEC_EFFECT_DOYON
    &iam_ef_kagu_happa, // eEC_EFFECT_KAGU_HAPPA
    &iam_ef_hanabi_dummy, // eEC_EFFECT_HANABI_DUMMY
    &iam_ef_dig_hole, // eEC_EFFECT_DIG_HOLE
    &iam_ef_dig_scoop, // eEC_EFFECT_DIG_SCOOP
    &iam_ef_dig_mud, // eEC_EFFECT_DIG_MUD
    &iam_ef_kigae, // eEC_EFFECT_KIGAE
    &iam_ef_kigae_light, // eEC_EFFECT_KIGAE_LIGHT
    &iam_ef_tape, // eEC_EFFECT_TAPE
    &iam_ef_clacker, // eEC_EFFECT_CLACKER
    &iam_ef_kamifubuki, // eEC_EFFECT_KAMIFUBUKI
    &iam_ef_car_blight, // eEC_EFFECT_CAR_BLIGHT
    &iam_ef_tamaire, // eEC_EFFECT_TAMAIRE
    &iam_ef_car_light, // eEC_EFFECT_CAR_LIGHT
    &iam_ef_reset_hole, // eEC_EFFECT_RESET_HOLE
    &iam_ef_goki, // eEC_EFFECT_GOKI
    &iam_ef_hanabira, // eEC_EFFECT_HANABIRA
    &iam_ef_wait_asimoto, // eEC_EFFECT_WAIT_ASIMOTO
    &iam_ef_otosiana, // eEC_EFFECT_OTOSIANA
    &iam_ef_ikigire, // eEC_EFFECT_IKIGIRE
    &iam_ef_yukidaruma, // eEC_EFFECT_YUKIDARUMA
    &iam_ef_kyousou_onpu, // eEC_EFFECT_KYOUSOU_ONPU
    &iam_ef_douzou_light, // eEC_EFFECT_DOUZOU_LIGHT
    &iam_ef_halloween_smoke, // eEC_EFFECT_HALLOWEEN_SMOKE
    &iam_ef_halloween, // eEC_EFFECT_HALLOWEEN
    &iam_ef_motiyuge, // eEC_EFFECT_MOTIYUGE
    &iam_ef_taberu, // eEC_EFFECT_TABERU
    &iam_ef_kasamizu, // eEC_EFFECT_KASAMIZU
    &iam_ef_kasamizutama, // eEC_EFFECT_KASAMIZUTAMA
    &iam_ef_hanatiri, // eEC_EFFECT_HANATIRI
    &iam_ef_uranai, // eEC_EFFECT_URANAI
    &iam_ef_suisou_awa, // eEC_EFFECT_SUISOU_AWA
    &iam_ef_break_axe, // eEC_EFFECT_BREAK_AXE
    &iam_ef_yajirushi, // eEC_EFFECT_YAJIRUSHI
    &iam_ef_soba_yuge, // eEC_EFFECT_SOBA_YUGE
    &iam_ef_furo_yuge, // eEC_EFFECT_FURO_YUGE
    &iam_ef_shooting, // eEC_EFFECT_SHOOTING
    &iam_ef_shooting_set, // eEC_EFFECT_SHOOTING_SET
    &iam_ef_shooting_kira, // eEC_EFFECT_SHOOTING_KIRA
    &iam_ef_coin, // eEC_EFFECT_COIN
    &iam_ef_tent_lamp, // eEC_EFFECT_TENT_LAMP
    &iam_ef_flash, // eEC_EFFECT_FLASH
    &iam_ef_flashC, // eEC_EFFECT_FLASHC
    &iam_ef_killer, // eEC_EFFECT_KILLER
    &iam_ef_make_hem, // eEC_EFFECT_MAKE_HEM
    &iam_ef_make_hem_kira, // eEC_EFFECT_MAKE_HEM_KIRA
    &iam_ef_make_hem_light, // eEC_EFFECT_MAKE_HEM_LIGHT
    &iam_ef_nomi, // eEC_EFFECT_NOMI
    &iam_ef_resetbreak, // eEC_EFFECT_RESETBREAK
    &iam_ef_resetbreak_parts, // eEC_EFFECT_RESETBREAK_PARTS
    &iam_ef_resetbreak_dust, // eEC_EFFECT_RESETBREAK_DUST
    &iam_ef_resetbreak_piece, // eEC_EFFECT_RESETBREAK_PIECE
    &iam_ef_presentopen, // eEC_EFFECT_PRESENTOPEN
    &iam_ef_presentopen_parts, // eEC_EFFECT_PRESENTOPEN_PARTS
};

static u8 eEC_effect_feature[eEC_EFFECT_NUM] = {
    FALSE, // eEC_EFFECT_SHOCK
    FALSE, // eEC_EFFECT_DUST
    FALSE, // eEC_EFFECT_MUKA
    TRUE, // eEC_EFFECT_WARAU
    FALSE, // eEC_EFFECT_HA
    FALSE, // eEC_EFFECT_SIBUKI
    FALSE, // eEC_EFFECT_GIMONHU
    FALSE, // eEC_EFFECT_KANTANHU
    TRUE, // eEC_EFFECT_ASE
    FALSE, // eEC_EFFECT_ASE_CH
    TRUE, // eEC_EFFECT_KANGAERU
    TRUE, // eEC_EFFECT_OTIKOMI
    TRUE, // eEC_EFFECT_BURUBURU
    TRUE, // eEC_EFFECT_SIAWASE_HIKARI
    TRUE, // eEC_EFFECT_SIAWASE_HANA
    FALSE, // eEC_EFFECT_SIAWASE_HANA_CH
    TRUE, // eEC_EFFECT_TAKURAMI
    FALSE, // eEC_EFFECT_TAKURAMI_KIRA
    TRUE, // eEC_EFFECT_KAZE
    TRUE, // eEC_EFFECT_KAZE_HAPPA
    FALSE, // eEC_EFFECT_LOVELOVE
    FALSE, // eEC_EFFECT_LOVELOVE_HEART
    TRUE, // eEC_EFFECT_PUN
    FALSE, // eEC_EFFECT_PUN_YUGE
    FALSE, // eEC_EFFECT_PUN_SEKIMEN
    TRUE, // eEC_EFFECT_NAKU
    FALSE, // eEC_EFFECT_NAMIDA
    FALSE, // eEC_EFFECT_HIRAMEKI_DEN
    FALSE, // eEC_EFFECT_HIRAMEKI_HIKARI
    FALSE, // eEC_EFFECT_SITUREN
    TRUE, // eEC_EFFECT_ASE2
    FALSE, // eEC_EFFECT_DASH_ASIMOTO
    FALSE, // eEC_EFFECT_KONPU
    FALSE, // eEC_EFFECT_LOVELOVE2
    FALSE, // eEC_EFFECT_KPUN
    FALSE, // eEC_EFFECT_KISHA_KEMURI
    TRUE, // eEC_EFFECT_NEBOKE
    FALSE, // eEC_EFFECT_NEBOKE_AWA
    FALSE, // eEC_EFFECT_HANABI_YANAGI
    FALSE, // eEC_EFFECT_HANABI_BOTAN1
    FALSE, // eEC_EFFECT_HANABI_BOTAN2
    FALSE, // eEC_EFFECT_HANABI_HOSHI
    FALSE, // eEC_EFFECT_HANABI_SET
    TRUE, // eEC_EFFECT_HANABI_SWITCH
    FALSE, // eEC_EFFECT_FOOTPRINT
    FALSE, // eEC_EFFECT_TURN_FOOTPRINT
    TRUE, // eEC_EFFECT_BUBU
    FALSE, // eEC_EFFECT_TURN_ASIMOTO
    FALSE, // eEC_EFFECT_STRING
    FALSE, // eEC_EFFECT_YUKIHANE
    FALSE, // eEC_EFFECT_ANAHIKARI
    FALSE, // eEC_EFFECT_BUSH_HAPPA
    FALSE, // eEC_EFFECT_BUSH_YUKI
    FALSE, // eEC_EFFECT_TUMBLE
    FALSE, // eEC_EFFECT_TUMBLE_BODYPRINT
    FALSE, // eEC_EFFECT_SLIP
    FALSE, // eEC_EFFECT_TUMBLE_DUST
    FALSE, // eEC_EFFECT_SWING_NET
    FALSE, // eEC_EFFECT_AMI_MIZU
    FALSE, // eEC_EFFECT_MIZUTAMA
    FALSE, // eEC_EFFECT_YUKIDAMA
    FALSE, // eEC_EFFECT_KIKUZU
    FALSE, // eEC_EFFECT_SWING_AXE
    FALSE, // eEC_EFFECT_STEAM
    TRUE, // eEC_EFFECT_NIGHT15_MOON
    TRUE, // eEC_EFFECT_NIGHT13_MOON
    FALSE, // eEC_EFFECT_NEBOKE_AKUBI
    FALSE, // eEC_EFFECT_SLIP_FOOTPRINT
    FALSE, // eEC_EFFECT_WALK_ASIMOTO
    FALSE, // eEC_EFFECT_TURI_HAMON
    FALSE, // eEC_EFFECT_TURI_MIZU
    FALSE, // eEC_EFFECT_TURI_HANE0
    FALSE, // eEC_EFFECT_TURI_HANE1
    FALSE, // eEC_EFFECT_TURI_SUITEKI
    FALSE, // eEC_EFFECT_ONGEN
    FALSE, // eEC_EFFECT_IMPACT_STAR
    FALSE, // eEC_EFFECT_SANDSPLASH
    FALSE, // eEC_EFFECT_YOUNG_TREE
    FALSE, // eEC_EFFECT_SWING_ROD
    FALSE, // eEC_EFFECT_DOYON
    FALSE, // eEC_EFFECT_KAGU_HAPPA
    FALSE, // eEC_EFFECT_HANABI_DUMMY
    FALSE, // eEC_EFFECT_DIG_HOLE
    FALSE, // eEC_EFFECT_DIG_SCOOP
    FALSE, // eEC_EFFECT_DIG_MUD
    FALSE, // eEC_EFFECT_KIGAE
    FALSE, // eEC_EFFECT_KIGAE_LIGHT
    FALSE, // eEC_EFFECT_TAPE
    FALSE, // eEC_EFFECT_CLACKER
    FALSE, // eEC_EFFECT_KAMIFUBUKI
    FALSE, // eEC_EFFECT_CAR_BLIGHT
    FALSE, // eEC_EFFECT_TAMAIRE
    FALSE, // eEC_EFFECT_CAR_LIGHT
    FALSE, // eEC_EFFECT_RESET_HOLE
    FALSE, // eEC_EFFECT_GOKI
    FALSE, // eEC_EFFECT_HANABIRA
    FALSE, // eEC_EFFECT_WAIT_ASIMOTO
    FALSE, // eEC_EFFECT_OTOSIANA
    FALSE, // eEC_EFFECT_IKIGIRE
    FALSE, // eEC_EFFECT_YUKIDARUMA
    FALSE, // eEC_EFFECT_KYOUSOU_ONPU
    FALSE, // eEC_EFFECT_DOUZOU_LIGHT
    FALSE, // eEC_EFFECT_HALLOWEEN_SMOKE
    FALSE, // eEC_EFFECT_HALLOWEEN
    FALSE, // eEC_EFFECT_MOTIYUGE
    TRUE, // eEC_EFFECT_TABERU
    FALSE, // eEC_EFFECT_KASAMIZU
    FALSE, // eEC_EFFECT_KASAMIZUTAMA
    FALSE, // eEC_EFFECT_HANATIRI
    TRUE, // eEC_EFFECT_URANAI
    FALSE, // eEC_EFFECT_SUISOU_AWA
    FALSE, // eEC_EFFECT_BREAK_AXE
    FALSE, // eEC_EFFECT_YAJIRUSHI
    FALSE, // eEC_EFFECT_SOBA_YUGE
    FALSE, // eEC_EFFECT_FURO_YUGE
    FALSE, // eEC_EFFECT_SHOOTING
    TRUE, // eEC_EFFECT_SHOOTING_SET
    FALSE, // eEC_EFFECT_SHOOTING_KIRA
    FALSE, // eEC_EFFECT_COIN
    TRUE, // eEC_EFFECT_TENT_LAMP
    FALSE, // eEC_EFFECT_FLASH
    TRUE, // eEC_EFFECT_FLASHC
    TRUE, // eEC_EFFECT_KILLER
    TRUE, // eEC_EFFECT_MAKE_HEM
    FALSE, // eEC_EFFECT_MAKE_HEM_KIRA
    TRUE, // eEC_EFFECT_MAKE_HEM_LIGHT
    FALSE, // eEC_EFFECT_NOMI
    FALSE, // eEC_EFFECT_RESETBREAK
    FALSE, // eEC_EFFECT_RESETBREAK_PARTS
    FALSE, // eEC_EFFECT_RESETBREAK_DUST
    FALSE, // eEC_EFFECT_RESETBREAK_PIECE
    TRUE, // eEC_EFFECT_PRESENTOPEN
    FALSE, // eEC_EFFECT_PRESENTOPEN_PARTS
};

static void eEC_actor_ct(ACTOR* actorx, GAME* game);
static void eEC_actor_dt(ACTOR* actorx, GAME* game);
static void eEC_actor_move(ACTOR* actorx, GAME* game);
static void eEC_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Effect_Control_Profile = {
    mAc_PROFILE_EFFECT_CONTROL,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EFFECT_CONTROL_ACTOR),
    &eEC_actor_ct,
    &eEC_actor_dt,
    &eEC_actor_move,
    &eEC_actor_draw,
    NULL,
};

static eEC_work_c eEC_ctrl_work;

#include "../src/effect/ef_effect_lib.c"

static void eEC_Name2EffectMake(int effect_id, xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0,
                                s16 arg1) {
    if (effect_id >= 0 && effect_id < eEC_EFFECT_NUM) {
        if (eEC_effect_feature[effect_id] == FALSE) {
            profile_tbl[effect_id]->init_proc(pos, prio, angle, game, item_name, arg0, arg1);
        } else if (eEC_effect_feature[effect_id] == TRUE) {
            int i;
            u8* active_flags = eEC_ctrl_work.effect_active_flags;
            eEC_Effect_c* effect = eEC_ctrl_work.effects;

            /* Check if any of the spawned effects are an exact match to this one */
            for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; active_flags++, effect++, i++) {
                if (*active_flags && effect->name == effect_id && effect->item_name == item_name) {
                    return;
                }
            }

            /* No exact matches, so create effect */
            profile_tbl[effect_id]->init_proc(pos, prio, angle, game, item_name, arg0, arg1);
        }
    }
}

static void eEC_Name2EffectKill(int effect_id, u16 item_name) {
    int i;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    eEC_Effect_c* effect = eEC_ctrl_work.effects;

    for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; i++, active_flags++, effect++) {
        if (*active_flags && effect->name == effect_id && effect->item_name == item_name && effect->prog_idx != -1) {
            if (profile_tbl[effect_id]->n_frames == eEC_IMMEDIATE_DEATH) {
                *active_flags = 0;

                if (profile_tbl[effect_id]->child_effect_id != eEC_NO_CHILD_ID) {
                    eEC_Name2EffectKill(profile_tbl[effect_id]->child_effect_id, item_name);
                }
            } else if (profile_tbl[effect_id]->n_frames != eEC_IGNORE_DEATH) {
                effect->timer = profile_tbl[effect_id]->n_frames;
                effect->state = eEC_STATE_FINISHED;

                if (profile_tbl[effect_id]->child_effect_id != eEC_NO_CHILD_ID) {
                    eEC_Name2EffectKill(profile_tbl[effect_id]->child_effect_id, item_name);
                }
            }
        }
    }
}

static void eEC_Name2EffectKillAll(u16 item_name) {
    int i;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    eEC_Effect_c* effect = eEC_ctrl_work.effects;

    for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; i++, active_flags++, effect++) {
        if (*active_flags && effect->item_name == item_name && effect->prog_idx != -1) {
            if (profile_tbl[effect->name]->n_frames == eEC_IMMEDIATE_DEATH) {
                *active_flags = FALSE;
            } else if (eEC_ctrl_work.program_info[effect->prog_idx].end_frame != eEC_IGNORE_DEATH) {
                effect->timer = eEC_ctrl_work.program_info[effect->prog_idx].end_frame;
                effect->state = eEC_STATE_FINISHED;
            }
        }
    }
}

static void eEC_InitEffectControlWork(void) {
    eEL_InitUnchar(eEC_ctrl_work.effect_active_flags, eEC_EFFECT_ACTIVE_MAX, 0);
    eEC_ctrl_work.active_effect_num = 0;
}

static eEC_Effect_c* eEC_MakeEffect(s16 effect_id, xyz_t pos, xyz_t* ofs, GAME* game, void* ct_arg, u16 item_name,
                                    int prio, s16 arg0, s16 arg1);

static void eEC_EffectLib2Clip(ACTOR* actorx) {
    EFFECT_CONTROL_ACTOR* effect_ctrl = (EFFECT_CONTROL_ACTOR*)actorx;

    effect_ctrl->clip.effect_make_proc = &eEC_Name2EffectMake;
    effect_ctrl->clip.effect_kill_proc = &eEC_Name2EffectKill;
    effect_ctrl->clip.effect_kill_all_proc = &eEC_Name2EffectKillAll;
    effect_ctrl->clip.vector_rotate_y_proc = &eEL_VectorRoteteY;
    effect_ctrl->clip.random_first_speed_proc = &eEL_RandomFirstSpeed;
    effect_ctrl->clip.set_continious_env_proc = &eEL_SetContiniousEnv;
    effect_ctrl->clip.calc_adjust_proc = &eEL_CalcAdjust;
    effect_ctrl->clip.auto_matrix_xlu_proc = &eEL_AutoMatrixXlu;
    effect_ctrl->clip.auto_matrix_xlu_offset_proc = &eEL_AutoMatrixXlu_Offset;
    effect_ctrl->clip._20 = NULL;
    effect_ctrl->clip._24 = NULL;
    effect_ctrl->clip.make_effect_proc = &eEC_MakeEffect;
    effect_ctrl->clip.morph_combine_proc = &eEC_MorphCombine;
    effect_ctrl->clip.regist_effect_light = &eEL_RegistEffectLight;
    effect_ctrl->clip.decide_light_power_proc = &eEL_DecideLightPower;
    effect_ctrl->clip.check_lookat_block_proc = &mEL_CheckLookAtBlock;
    effect_ctrl->clip.effect_light_status = &eEL_EffectLightStatus;
    effect_ctrl->clip.special_block_center_pos_proc = &eEL_SpecialBlockCenterPos;

    eEC_CLIP = &effect_ctrl->clip;
}

static void eEC_MakeEffectLight(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    Light_diffuse_ct(&eEC_ctrl_work.light_info, 0, 127, 0, 0, 0, 0);
    eEC_ctrl_work.light_list = Global_light_list_new(game, &play->global_light, &eEC_ctrl_work.light_info);
}

static void eEC_DeleteEffectLight(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    Global_light_list_delete(&play->global_light, eEC_ctrl_work.light_list);
}

int eMH_special_point_light_num = 0;

static void eEC_actor_ct(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    eEC_EffectLib2Clip(actorx);
    eEC_InitEffectControlWork();
    eEC_MakeEffectLight(game);
    eEL_InitEffectLight();

    switch (Save_Get(scene_no)) {
        case SCENE_TENT:
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TENT_LAMP, actorx->world.position, 3, 0, game, RSV_NO, 0, 0);
            break;
    }

    eMH_special_point_light_num = -1;
}

static void eEC_actor_dt(ACTOR* actorx, GAME* game) {
    eEC_CLIP = NULL;
    eEC_DeleteEffectLight(game);
}

static void eEC_actor_draw(ACTOR* actorx, GAME* game) {
    int i;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    eEC_Effect_c* effect = eEC_ctrl_work.effects;

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; i++, active_flags++, effect++) {
        if (*active_flags) {
            profile_tbl[effect->name]->draw_proc(effect, game);
        }
    }
}

static int eEC_DistDeath(eEC_Effect_c* effect, GAME* game, s16 prog_idx) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int res = FALSE; // in range

    if (prog_idx != -1) {
        f32 max_dist = profile_tbl[effect->name]->max_dist;

        if (max_dist != eEC_IGNORE_DEATH_DIST) {
            PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

            if (ABS(player->actor_class.world.position.x - effect->position.x) > max_dist ||
                ABS(player->actor_class.world.position.z - effect->position.z) > max_dist ||
                ABS(player->actor_class.world.position.y - effect->position.y) > max_dist) {
                res = TRUE; // out of range
            }
        }
    }

    return res;
}

static void eEC_AllEffectMove(GAME* game) {
    int i;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    eEC_Effect_c* effect = eEC_ctrl_work.effects;

    for (i = 0; i < eEC_EFFECT_ACTIVE_MAX; i++, active_flags++, effect++) {
        if (*active_flags) {
            s16 prog_idx = effect->prog_idx;

            profile_tbl[effect->name]->move_proc(effect, game);
            effect->timer--;

            if (effect->timer <= 0 || eEC_DistDeath(effect, game, prog_idx) == TRUE) {
                *active_flags = 0;
                effect->timer = 0;
                effect->_0A = 0;
            }
        }
    }
}

static void eEC_actor_move(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

    eEL_CalcEffectLight_Set(game);
    eEC_AllEffectMove(game);
    actorx->world.position = player->actor_class.world.position;
}

static int eEC_GetEffectBuff(int prio) {
    int now_idx = eEC_ctrl_work.active_effect_num;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    int i;

    for (i = now_idx; i < eEC_EFFECT_ACTIVE_MAX; i++) {
        if (active_flags[i] == 0) {
            return i;
        }
    }

    for (i = 0; i < now_idx - 1; i++) {
        if (active_flags[i] == 0) {
            return i;
        }
    }

    for (i = now_idx; i < eEC_EFFECT_ACTIVE_MAX; i++) {
        if (active_flags[i] < prio) {
            return i;
        }
    }

    for (i = 0; i < now_idx - 1; i++) {
        if (active_flags[i] != 2) {
            return i;
        }
    }

    return -1;
}

static void eEC_SetFirstOffset(eEC_Effect_c* effect, xyz_t* ofs) {
    static xyz_t default_offset = { 0.0f, 0.0f, 0.0f };

    effect->offset = default_offset;
    if (ofs != NULL) {
        effect->offset = *ofs;
    }
}

static eEC_Effect_c* eEC_MakeEffect(s16 effect_id, xyz_t pos, xyz_t* ofs, GAME* game, void* ct_arg, u16 item_name,
                                    int prio, s16 arg0, s16 arg1) {
    static xyz_t defaultX = { 0.0f, 0.0f, 0.0f };
    static xyz_t scale_default = { 0.01f, 0.01f, 0.01f };
    int* active_effect_num = &eEC_ctrl_work.active_effect_num;
    eEC_Effect_c* effect = NULL;
    eEC_Effect_c* effects = eEC_ctrl_work.effects;
    u8* active_flags = eEC_ctrl_work.effect_active_flags;
    int use_idx;

    use_idx = eEC_GetEffectBuff(prio);
    if (use_idx != -1) {
        active_flags[use_idx] = prio;
        effects[use_idx].name = effect_id;
        effects[use_idx].position = pos;
        effects[use_idx].item_name = item_name;
        effects[use_idx].prio = prio;
        effects[use_idx].state = eEC_STATE_NORMAL;
        eEC_SetFirstOffset(&effects[use_idx], ofs);
        effects[use_idx].timer = 10;
        effects[use_idx].velocity = defaultX;
        effects[use_idx].acceleration = defaultX;
        effects[use_idx].scale = scale_default;
        effects[use_idx].arg0 = arg0;
        effects[use_idx].arg1 = arg1;

        profile_tbl[effect_id]->ct_proc(&effects[use_idx], game, ct_arg);
        *active_effect_num = use_idx + 1;
        effect = &effects[use_idx];
    }

    return effect;
}
