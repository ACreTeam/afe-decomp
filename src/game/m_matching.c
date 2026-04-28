#include "m_matching.h"
#include "m_npc.h"

typedef struct character_point_match_s {
    u8 char0;
    u8 char1;
    u8 point;
} mMG_character_point_match;

static mMG_character_point_match mMG_chara_combi_point_table[36] = {
    {mMG_CHARACTER_NORMAL, mMG_CHARACTER_NORMAL, 0x28},
    {mMG_CHARACTER_NORMAL, mMG_CHARACTER_PEPPY, 0x08},
    {mMG_CHARACTER_NORMAL, mMG_CHARACTER_SNOOTY, 0x60},
    {mMG_CHARACTER_NORMAL, mMG_CHARACTER_LAZY, 0x08},
    {mMG_CHARACTER_NORMAL, mMG_CHARACTER_JOCK, 0x28},
    {mMG_CHARACTER_NORMAL, mMG_CHARACTER_CRANKY, 0x60},
    {mMG_CHARACTER_PEPPY, mMG_CHARACTER_NORMAL, 0x08},
    {mMG_CHARACTER_PEPPY, mMG_CHARACTER_PEPPY, 0x60},
    {mMG_CHARACTER_PEPPY, mMG_CHARACTER_SNOOTY, 0x28},
    {mMG_CHARACTER_PEPPY, mMG_CHARACTER_LAZY, 0x28},
    {mMG_CHARACTER_PEPPY, mMG_CHARACTER_JOCK, 0x60},
    {mMG_CHARACTER_PEPPY, mMG_CHARACTER_CRANKY, 0x08},
    {mMG_CHARACTER_SNOOTY, mMG_CHARACTER_NORMAL, 0x60},
    {mMG_CHARACTER_SNOOTY, mMG_CHARACTER_PEPPY, 0x28},
    {mMG_CHARACTER_SNOOTY, mMG_CHARACTER_SNOOTY, 0x08},
    {mMG_CHARACTER_SNOOTY, mMG_CHARACTER_LAZY, 0x60},
    {mMG_CHARACTER_SNOOTY, mMG_CHARACTER_JOCK, 0x08},
    {mMG_CHARACTER_SNOOTY, mMG_CHARACTER_CRANKY, 0x28},
    {mMG_CHARACTER_LAZY, mMG_CHARACTER_NORMAL, 0x08},
    {mMG_CHARACTER_LAZY, mMG_CHARACTER_PEPPY, 0x28},
    {mMG_CHARACTER_LAZY, mMG_CHARACTER_SNOOTY, 0x60},
    {mMG_CHARACTER_LAZY, mMG_CHARACTER_LAZY, 0x28},
    {mMG_CHARACTER_LAZY, mMG_CHARACTER_JOCK, 0x60},
    {mMG_CHARACTER_LAZY, mMG_CHARACTER_CRANKY, 0x08},
    {mMG_CHARACTER_JOCK, mMG_CHARACTER_NORMAL, 0x28},
    {mMG_CHARACTER_JOCK, mMG_CHARACTER_PEPPY, 0x60},
    {mMG_CHARACTER_JOCK, mMG_CHARACTER_SNOOTY, 0x08},
    {mMG_CHARACTER_JOCK, mMG_CHARACTER_LAZY, 0x60},
    {mMG_CHARACTER_JOCK, mMG_CHARACTER_JOCK, 0x08},
    {mMG_CHARACTER_JOCK, mMG_CHARACTER_CRANKY, 0x28},
    {mMG_CHARACTER_CRANKY, mMG_CHARACTER_NORMAL, 0x60},
    {mMG_CHARACTER_CRANKY, mMG_CHARACTER_PEPPY, 0x08},
    {mMG_CHARACTER_CRANKY, mMG_CHARACTER_SNOOTY, 0x28},
    {mMG_CHARACTER_CRANKY, mMG_CHARACTER_LAZY, 0x08},
    {mMG_CHARACTER_CRANKY, mMG_CHARACTER_JOCK, 0x28},
    {mMG_CHARACTER_CRANKY, mMG_CHARACTER_CRANKY, 0x60},
};

static int mMG_get_character_point(u8 char0, u8 char1) {
    int i;

    for (i = 0; i < ARRAY_COUNT(mMG_chara_combi_point_table); i++) {
        if (mMG_chara_combi_point_table[i].char0 == char0 && mMG_chara_combi_point_table[i].char1 == char1) {
            return mMG_chara_combi_point_table[i].point;
        }
    }

    return 0;
}

static int mMG_get_constellation_point(u8 constellation0, u8 constellation1) {
    static const u8 star_match_table[4][4] = {
        {0x80, 0x30, 0x30, 0x00},
        {0x30, 0x80, 0x00, 0x30},
        {0x30, 0x00, 0x80, 0x30},
        {0x00, 0x30, 0x30, 0x80},
    };

    return star_match_table[constellation0 & 3][constellation1 & 3];
}

typedef struct tribe_point_match_s {
    u8 tribe0;
    u8 tribe1;
} mMG_tribe_point_match;

static int mMG_get_tribe_point(u8 tribe0, u8 tribe1) {
    static mMG_tribe_point_match good_combi_table[7] = {
        {mMG_TRIBE_DOG, mMG_TRIBE_WOLF},
        {mMG_TRIBE_BULL, mMG_TRIBE_COW},
        {mMG_TRIBE_KANGAROO, mMG_TRIBE_KOALA},
        {mMG_TRIBE_BEAR, mMG_TRIBE_CUB},
        {mMG_TRIBE_SQUIRREL, mMG_TRIBE_MOUSE},
        {mMG_TRIBE_GOAT, mMG_TRIBE_SHEEP},
        {mMG_TRIBE_TIGER, mMG_TRIBE_CAT},
    };
    
    static mMG_tribe_point_match bad_combi_table[3] = {
        {mMG_TRIBE_DOG, mMG_TRIBE_GORILLA},
        {mMG_TRIBE_WOLF, mMG_TRIBE_SHEEP},
        {mMG_TRIBE_CAT, mMG_TRIBE_MOUSE},
    };

    mMG_tribe_point_match* combi_p;
    int i;

    if (tribe0 == tribe1) {
        return 64; // neutral (same tribe)
    }

    combi_p = good_combi_table;
    for (i = 0; i < ARRAY_COUNT(good_combi_table); i++) {
        if ((combi_p->tribe0 == tribe0 && combi_p->tribe1 == tribe1) ||
            (combi_p->tribe0 == tribe1 && combi_p->tribe1 == tribe0)) {
            return 128; // good combination
        }

        combi_p++;
    }

    combi_p = bad_combi_table;
    for (i = 0; i < ARRAY_COUNT(bad_combi_table); i++) {
        if ((combi_p->tribe0 == tribe0 && combi_p->tribe1 == tribe1) ||
            (combi_p->tribe0 == tribe1 && combi_p->tribe1 == tribe0)) {
            return 0; // bad combination
        }

        combi_p++;
    }

    return 32; // neutral (different tribe)
}

static int mMG_get_intelligence_point(u8 intelligence0, u8 intelligence1) {
    return ~((u8)intelligence0 ^ (u8)intelligence1) & 0x7F;
}

static int mMG_get_popular_point(u8 popular0, u8 popular1) {
    return (u8)ABS((u8)popular0 - (u8)popular1);
}

static int mMG_check_param_error(u8 character, u8 constellation, u8 tribe) {
    if (character >= 20) {
        return FALSE;
    }

    if (constellation >= 12) {
        return FALSE;
    }

    if (tribe >= 64) {
        return FALSE;
    }

    return TRUE;
}

static int mMG_param_matching_point(
    u8 popular0, u8 intelligence0, u8 character0, u8 constellation0, u8 tribe0,
    u8 popular1, u8 intelligence1, u8 character1, u8 constellation1, u8 tribe1
) {
    if (mMG_check_param_error(character0, constellation0, tribe0) && mMG_check_param_error(character1, constellation1, tribe1)) {
        int char_point = mMG_get_character_point(character0, character1);
        int constellation_point = mMG_get_constellation_point(constellation0, constellation1);
        int tribe_point = mMG_get_tribe_point(tribe0, tribe1);
        int intelligence_point = mMG_get_intelligence_point(intelligence0, intelligence1);
        int popular_point = mMG_get_popular_point(popular0, popular1);
        int point = char_point + constellation_point + tribe_point + intelligence_point;
        
        if (point < 200) {
            return ABS(point - popular_point);
        }

        return point;
    }

    return 0;
}

extern int mMG_paramC_matching_point(u8* params0, u8* params1) {
    return mMG_param_matching_point(params0[3], params0[4], params0[1], params0[2], params0[0],
        params1[3], params1[4], params1[1], params1[2], params1[0]);
}
