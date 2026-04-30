#include "m_npc_schedule.h"

#include "m_common_data.h"

// #define mNPS_TIME_2_SEC(hour, min, sec) ((hour) * 3600 + (min) * 60 + (sec))
// #define mNPS_MAKE_SCHEDULE_TABLE(sched_data) { ARRAY_SIZE(sched_data, mNPS_schedule_data_c), sched_data }

// static mNPS_schedule_data_c girl_schedule_dt[] = {
//     // clang-format off
//     { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(5, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(6, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(12, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(13, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(18, 30, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(21, 0, 0) },
//     { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(24, 0, 0) },
//     // clang-format on
// };

// static mNPS_schedule_data_table_c girl_schedule = mNPS_MAKE_SCHEDULE_TABLE(girl_schedule_dt);

// static mNPS_schedule_data_c ko_girl_schedule_dt[] = {
//     // clang-format off
//     { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(7, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(8, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(13, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(14, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(22, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(23, 30, 0) },
//     { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(24, 0, 0) },
//     // clang-format on
// };

// static mNPS_schedule_data_table_c ko_girl_schedule = mNPS_MAKE_SCHEDULE_TABLE(ko_girl_schedule_dt);

// static mNPS_schedule_data_c boy_schedule_dt[] = {
//     // clang-format off
//     { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(8, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(9, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(12, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(14, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(19, 30, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(22, 0, 0) },
//     { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(24, 0, 0) },
//     // clang-format on
// };

// static mNPS_schedule_data_table_c boy_schedule = mNPS_MAKE_SCHEDULE_TABLE(boy_schedule_dt);

// static mNPS_schedule_data_c sport_man_schedule_dt[] = {
//     // clang-format off
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(1, 0, 0) },
//     { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(5, 30, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(6, 30, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(12, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(12, 30, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(23, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(24, 0, 0) },
//     // clang-format on
// };

// static mNPS_schedule_data_table_c sport_man_schedule = mNPS_MAKE_SCHEDULE_TABLE(sport_man_schedule_dt);

// static mNPS_schedule_data_c grim_man_schedule_dt[] = {
//     // clang-format off
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(4, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(5, 0, 0) },
//     { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(10, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(11, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(15, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(16, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(22, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(23, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(24, 0, 0) },
//     // clang-format on
// };

// static mNPS_schedule_data_table_c grim_man_schedule = mNPS_MAKE_SCHEDULE_TABLE(grim_man_schedule_dt);

// static mNPS_schedule_data_c naniwa_lady_schedule_dt[] = {
//     // clang-format off
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(1, 30, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(2, 30, 0) },
//     { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(9, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(10, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(13, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(14, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(21, 0, 0) },
//     { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(22, 0, 0) },
//     { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(24, 0, 0) },
//     // clang-format on
// };

// static mNPS_schedule_data_table_c naniwa_lady_schedule = mNPS_MAKE_SCHEDULE_TABLE(naniwa_lady_schedule_dt);

// mNPS_schedule_data_table_c* mNPS_schedule[mNpc_LOOKS_NUM] = {
//     // clang-format off
//     &girl_schedule,
//     &ko_girl_schedule,
//     &boy_schedule,
//     &sport_man_schedule,
//     &grim_man_schedule,
//     &naniwa_lady_schedule,
//     // clang-format on
// };

// TODO: make enum for the walk types

// New data
#define mNPS_TIME_2_SEC(hour, min, sec) ((hour) * 3600 + (min) * 60 + (sec))
#define mNPS_MAKE_SCHEDULE_TABLE(sched_data) { ARRAY_SIZE(sched_data, mNPS_schedule_data_c), sched_data }
#define mNPS_SCHED_DT(type, end_hour, end_min, walk_type) \
    { mNPS_SCHED_##type, mNPS_TIME_2_SEC(end_hour, end_min, 0), walk_type }

static mNPS_schedule_data_c futsu_girl_schedule_dt[9] = {
    // clang-format off
    mNPS_SCHED_DT(FIELD, 0, 30, 1),
    mNPS_SCHED_DT(IN_HOUSE, 1, 0, 0),
    mNPS_SCHED_DT(SLEEP, 5, 0, 0),
    mNPS_SCHED_DT(IN_HOUSE, 5, 30, 0),
    mNPS_SCHED_DT(FIELD, 12, 30, 2),
    mNPS_SCHED_DT(IN_HOUSE, 13, 0, 0),
    mNPS_SCHED_DT(FIELD, 19, 30, 3),
    mNPS_SCHED_DT(IN_HOUSE, 20, 30, 0),
    mNPS_SCHED_DT(FIELD, 24, 0, 1),
    // clang-format on
};

static mNPS_schedule_data_table_c futsu_girl_schedule = mNPS_MAKE_SCHEDULE_TABLE(futsu_girl_schedule_dt);

static mNPS_schedule_data_c genki_girl_schedule_dt[9] = {
    // clang-format off
    mNPS_SCHED_DT(FIELD, 2, 0, 3),
    mNPS_SCHED_DT(IN_HOUSE, 2, 30, 0),
    mNPS_SCHED_DT(SLEEP, 7, 0, 0),
    mNPS_SCHED_DT(IN_HOUSE, 7, 30, 0),
    mNPS_SCHED_DT(FIELD, 13, 0, 3),
    mNPS_SCHED_DT(IN_HOUSE, 13, 30, 0),
    mNPS_SCHED_DT(FIELD, 20, 30, 3),
    mNPS_SCHED_DT(IN_HOUSE, 21, 30, 0),
    mNPS_SCHED_DT(FIELD, 24, 0, 3),
    // clang-format on
};

static mNPS_schedule_data_table_c genki_girl_schedule = mNPS_MAKE_SCHEDULE_TABLE(genki_girl_schedule_dt);

static mNPS_schedule_data_c bonyari_boy_schedule_dt[9] = {
    // clang-format off
    mNPS_SCHED_DT(FIELD, 1, 0, 2),
    mNPS_SCHED_DT(IN_HOUSE, 1, 30, 0),
    mNPS_SCHED_DT(SLEEP, 8, 0, 0),
    mNPS_SCHED_DT(IN_HOUSE, 8, 30, 0),
    mNPS_SCHED_DT(FIELD, 12, 0, 4),
    mNPS_SCHED_DT(IN_HOUSE, 12, 30, 0),
    mNPS_SCHED_DT(FIELD, 16, 30, 3),
    mNPS_SCHED_DT(IN_HOUSE, 17, 30, 0),
    mNPS_SCHED_DT(FIELD, 24, 0, 2),
    // clang-format on
};

static mNPS_schedule_data_table_c bonyari_boy_schedule = mNPS_MAKE_SCHEDULE_TABLE(bonyari_boy_schedule_dt);

static mNPS_schedule_data_c hakihaki_boy_schedule_dt[9] = {
    // clang-format off
    mNPS_SCHED_DT(FIELD, 1, 30, 5),
    mNPS_SCHED_DT(IN_HOUSE, 2, 0, 0),
    mNPS_SCHED_DT(SLEEP, 6, 30, 0),
    mNPS_SCHED_DT(IN_HOUSE, 7, 0, 0),
    mNPS_SCHED_DT(FIELD, 13, 30, 6),
    mNPS_SCHED_DT(IN_HOUSE, 14, 0, 0),
    mNPS_SCHED_DT(FIELD, 17, 30, 7),
    mNPS_SCHED_DT(IN_HOUSE, 18, 30, 0),
    mNPS_SCHED_DT(FIELD, 24, 0, 5),
    // clang-format on
};

static mNPS_schedule_data_table_c hakihaki_boy_schedule = mNPS_MAKE_SCHEDULE_TABLE(hakihaki_boy_schedule_dt);

static mNPS_schedule_data_c kowai_boy_schedule_dt[9] = {
    // clang-format off
    mNPS_SCHED_DT(FIELD, 4, 0, 8),
    mNPS_SCHED_DT(IN_HOUSE, 4, 30, 0),
    mNPS_SCHED_DT(SLEEP, 10, 0, 0),
    mNPS_SCHED_DT(IN_HOUSE, 10, 30, 0),
    mNPS_SCHED_DT(FIELD, 14, 30, 8),
    mNPS_SCHED_DT(IN_HOUSE, 15, 0, 0),
    mNPS_SCHED_DT(FIELD, 18, 30, 8),
    mNPS_SCHED_DT(IN_HOUSE, 19, 30, 0),
    mNPS_SCHED_DT(FIELD, 24, 0, 8),
    // clang-format on
};

static mNPS_schedule_data_table_c kowai_boy_schedule = mNPS_MAKE_SCHEDULE_TABLE(kowai_boy_schedule_dt);

static mNPS_schedule_data_c takabi_girl_schedule_dt[9] = {
    // clang-format off
    mNPS_SCHED_DT(FIELD, 3, 0, 9),
    mNPS_SCHED_DT(IN_HOUSE, 3, 30, 0),
    mNPS_SCHED_DT(SLEEP, 9, 0, 0),
    mNPS_SCHED_DT(IN_HOUSE, 9, 30, 0),
    mNPS_SCHED_DT(FIELD, 14, 0, 1),
    mNPS_SCHED_DT(IN_HOUSE, 14, 30, 0),
    mNPS_SCHED_DT(FIELD, 21, 30, 7),
    mNPS_SCHED_DT(IN_HOUSE, 22, 30, 0),
    mNPS_SCHED_DT(FIELD, 24, 0, 9),
    // clang-format on
};

static mNPS_schedule_data_table_c takabi_girl_schedule = mNPS_MAKE_SCHEDULE_TABLE(takabi_girl_schedule_dt);

mNPS_schedule_data_table_c* mNPS_schedule[mNpc_LOOKS_NUM] = {
    &futsu_girl_schedule, // mNpc_LOOKS_GIRL
    &genki_girl_schedule, // mNpc_LOOKS_KO_GIRL
    &bonyari_boy_schedule, // mNpc_LOOKS_BOY
    &hakihaki_boy_schedule, // mNpc_LOOKS_SPORT_MAN
    &kowai_boy_schedule, // mNpc_LOOKS_GRIM_MAN
    &takabi_girl_schedule, // mNpc_LOOKS_NANIWA_LADY
};

static void mNPS_set_sick_schedule(mNPS_schedule_c* schedule) {
    Animal_c* animal;
    int i;
    
    if (schedule->current_type == mNPS_SCHED_FIELD) {
        schedule->current_type = mNPS_SCHED_IN_HOUSE;
    }

    animal = Save_Get(animals);
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (&animal->id == schedule->id) {
            animal->is_home = TRUE;
            break;
        }
        animal++;
    }
}

extern mNPS_schedule_c* mNPS_get_schedule_area(AnmPersonalID_c* anm_id) {
    mNPS_schedule_c* schedule = Common_Get(npc_schedule);
    int i;

    if ((mEv_CheckFirstJob() == TRUE || mEv_check_status(mEv_EVENT_HALLOWEEN, mEv_STATUS_ACTIVE)) == TRUE) {
        for (i = 0; i < SCHEDULE_NUM; i++) {
            if (schedule->id == anm_id) {
                return schedule;
            }

            schedule++;
        }
    } else {
        int sick_animal_idx = mNpc_GetSickAnimalIdx();
        Animal_c* sick_animal;

        if (sick_animal_idx != -1) {
            sick_animal = Save_Get(animals) + sick_animal_idx;
        } else {
            sick_animal = NULL;
        }

        for (i = 0; i < SCHEDULE_NUM; i++) {
            if (schedule->id == anm_id) {
                if (sick_animal != NULL && &sick_animal->id == anm_id) {
                    mNPS_set_sick_schedule(schedule);
                }
                
                return schedule;
            }

            schedule++;
        }
    }

    return NULL;
}

static void mNPS_set_schedule_area(AnmPersonalID_c* anm_id) {
    mNPS_schedule_c* schedule = mNPS_get_schedule_area(NULL); /* try to get an unused schedule */

    if (schedule != NULL) {
        schedule->id = anm_id;
        schedule->data_table = mNPS_schedule[anm_id->looks];
        schedule->forced_timer = 0;
    }
}

extern void mNPS_set_island_schedule_area(AnmPersonalID_c* anm_id) {
    if (Common_Get(npc_schedule[ANIMAL_NUM_MAX]).id != NULL) {
        return;
    }

    Common_Set(npc_schedule[ANIMAL_NUM_MAX].id, anm_id);
    Common_Set(npc_schedule[ANIMAL_NUM_MAX].data_table, mNPS_schedule[anm_id->looks]);
    Common_Set(npc_schedule[ANIMAL_NUM_MAX].forced_timer, 0);
}

extern void mNPS_reset_schedule_area(AnmPersonalID_c* anm_id) {
    mNPS_schedule_c* schedule = mNPS_get_schedule_area(anm_id);

    if (schedule != NULL) {
        schedule->id = NULL;
    }
}

static void mNPS_schedule_manager_sub(mNPS_schedule_c* schedule) {
    int now_sec = Common_Get(time.now_sec);
    int count = schedule->data_table->count;
    mNPS_schedule_data_c* schedule_entry = schedule->data_table->sched_data;

    /* Locate our current scehdule entry */
    for (; count != 0; count--) {
        if (schedule_entry->end_time > now_sec) {
            break;
        }

        schedule_entry++;
    }

    schedule->saved_type = schedule_entry->type;
    if (schedule->forced_timer > 0) {
        schedule->current_type = schedule->forced_type;
        schedule->forced_timer--;
    } else {
        schedule->current_type = schedule->saved_type;
    }
}

static void mNPS_schedule_manager_sub0() {
    mNPS_schedule_c* schedule = Common_Get(npc_schedule);
    int i;

    /* Set all town animals to go outside in their home block */
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (schedule->id != NULL) {
            schedule->current_type = mNPS_SCHED_FIELD;
        }

        schedule++;
    }
}

static void mNPS_schedule_manager_sub1() {
    mNPS_schedule_c* schedule = Common_Get(npc_schedule);
    int sick_animal_idx = mNpc_GetSickAnimalIdx();
    Animal_c* sick_animal;
    int i;

    if (sick_animal_idx != -1) {
        sick_animal = Save_Get(animals) + sick_animal_idx;
    } else {
        sick_animal = NULL;
    }

    /* Set all town animals to go about their intended schedule */
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (schedule->id != NULL) {
            mNPS_schedule_manager_sub(schedule);

            if (sick_animal != NULL && schedule->id == &sick_animal->id) {
                mNPS_set_sick_schedule(schedule);
            }
        }

        schedule++;
    }
}

static void mNPS_island_schedule_manager() {
    mNPS_schedule_c* schedule = Common_GetPointer(npc_schedule[ANIMAL_NUM_MAX]);

    if (schedule->id != NULL) {
        switch (mISL_GetNpcDayType(&Common_Get(cur_island_house_p)->island)) {
            case mISL_NPC_DAY_TYPE_NORMAL:
                mNPS_schedule_manager_sub(schedule);
                break;
            default:
                schedule->current_type = mNPS_SCHED_FIELD;
                break;
        }
    }
}

extern void mNPS_schedule_manager() {
    int force_outside = FALSE;

    if (mEv_CheckFirstJob() == TRUE || mEv_check_status(mEv_EVENT_HALLOWEEN, mEv_STATUS_ACTIVE)) {
        force_outside = TRUE;
    }

    if (force_outside == TRUE) {
        mNPS_schedule_manager_sub0();
    } else {
        mNPS_schedule_manager_sub1();
    }

    mNPS_island_schedule_manager();
}

extern void mNPS_set_all_schedule_area() {
    Animal_c* animal = Save_Get(animals);
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            mNPS_set_schedule_area(&animal->id);
        }

        animal++;
    }

    mNPS_schedule_manager();
}
