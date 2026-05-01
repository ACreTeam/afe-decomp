#ifndef AC_FURNITURE_H
#define AC_FURNITURE_H

#include "types.h"
#include "m_collision_bg.h"
#include "c_keyframe.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct furniture_actor_s FTR_ACTOR;

#define aFTR_KEEP_ITEM_COUNT (mCoBG_LAYER_NUM - 1)
#define aFTR_CHECK_INTERACTION(inter, type) (((inter) >> (type)) & 1)

#define aFTR_EDGE_COL_NUM 4

enum {
    aFTR_STATE_STOP,
    aFTR_STATE_WAIT_PUSH,
    aFTR_STATE_WAIT_PUSH2,
    aFTR_STATE_WAIT_PUSH3,
    aFTR_STATE_PUSH,
    aFTR_STATE_WAIT_PULL,
    aFTR_STATE_WAIT_PULL2,
    aFTR_STATE_PULL,
    aFTR_STATE_WAIT_LROTATE,
    aFTR_STATE_LROTATE,
    aFTR_STATE_WAIT_RROTATE,
    aFTR_STATE_RROTATE,
    aFTR_STATE_BIRTH_WAIT,
    aFTR_STATE_BIRTH,
    aFTR_STATE_BYE,
    aFTR_STATE_DEATH,

    aFTR_STATE_NUM
};

enum {
    aFTR_CTR_TYPE_GAME,
    aFTR_CTR_TYPE_GAME_PLAY,

    aFTR_CTR_TYPE_NUM
};

enum {
    aFTR_HNW_STATE_WAIT_TURN_ON,
    aFTR_HNW_STATE_TURN_ON,
    aFTR_HNW_STATE_ON,
    aFTR_HNW_STATE_OFF,

    aFTR_HNW_STATE_NUM
};

enum {
    aFTR_SHAPE_TYPEB_90,  /* 2x1 (facing up)*/
    aFTR_SHAPE_TYPEB_180, /* 2x1 [- *] */
    aFTR_SHAPE_TYPEB_270, /* 2x1 (facing down) */
    aFTR_SHAPE_TYPEB_0,   /* 2x1 [* -] */
    aFTR_SHAPE_TYPEA,     /* 1x1 */
    aFTR_SHAPE_TYPEC,     /* 2x2 */

    aFTR_SHAPE_TYPE_NUM
};

enum {
    aFTR_INTERACTION_NONE = 0,
    aFTR_INTERACTION_STORAGE_DRAWERS = 1,  // dressers
    aFTR_INTERACTION_STORAGE_WARDROBE = 2, // double doors
    aFTR_INTERACTION_STORAGE_CLOSET = 4,   // single door
    aFTR_INTERACTION_MUSIC_DISK = 8,
    aFTR_INTERACTION_NO_COLLISION = 0x10,
    aFTR_INTERACTION_HANIWA = 0x20,
    aFTR_INTERACTION_FISH = 0x40,
    aFTR_INTERACTION_INSECT = 0x80,
    aFTR_INTERACTION_MANNEKIN = 0x100,
    aFTR_INTERACTION_UMBRELLA = 0x200,
    aFTR_INTERACTION_FOSSIL = 0x400,
    aFTR_INTERACTION_FAMICOM = 0x800,
    aFTR_INTERACTION_START_DISABLED = 0x1000, // mainly used for TVs to be off when placed
    // there may be more types, but I didn't see any
    aFTR_INTERACTION_FAMICOM_ITEM = 0x2000,
    aFTR_INTERACTION_RADIO_AEROBICS = 0x4000,
    aFTR_INTERACTION_TOGGLE = 0x8000,
};

enum {
    aFTR_INTERACTION_TYPE_DRAWERS,
    aFTR_INTERACTION_TYPE_WARDROBE,
    aFTR_INTERACTION_TYPE_CLOSET,
    aFTR_INTERACTION_TYPE_MUSIC_DISK,
    aFTR_INTERACTION_TYPE_NO_COLLISION,
    aFTR_INTERACTION_TYPE_HANIWA,
    aFTR_INTERACTION_TYPE_FISH,
    aFTR_INTERACTION_TYPE_INSECT,
    aFTR_INTERACTION_TYPE_MANNEKIN,
    aFTR_INTERACTION_TYPE_UMBRELLA,
    aFTR_INTERACTION_TYPE_FOSSIL,
    aFTR_INTERACTION_TYPE_FAMICOM,
    aFTR_INTERACTION_TYPE_START_DISABLED,
    aFTR_INTERACTION_TYPE_FAMICOM_ITEM,
    aFTR_INTERACTION_TYPE_RADIO_AEROBICS,
    aFTR_INTERACTION_TYPE_TOGGLE,

    aFTR_INTERACTION_NUM,
};

#define aFTR_IS_STORAGE(profile)                                                            \
    (aFTR_CHECK_INTERACTION((profile)->interaction_type, aFTR_INTERACTION_TYPE_DRAWERS) ||  \
     aFTR_CHECK_INTERACTION((profile)->interaction_type, aFTR_INTERACTION_TYPE_WARDROBE) || \
     aFTR_CHECK_INTERACTION((profile)->interaction_type, aFTR_INTERACTION_TYPE_CLOSET) ||   \
     aFTR_CHECK_INTERACTION((profile)->interaction_type, aFTR_INTERACTION_TYPE_MUSIC_DISK))
enum {
    aFTR_CONTACT_ACTION_NONE = 0,
    aFTR_CONTACT_ACTION_CHAIR_UNIDIRECTIONAL = 1,   // only can sit from the front
    aFTR_CONTACT_ACTION_CHAIR_MULTIDIRECTIONAL = 2, // can sit from any direction
    aFTR_CONTACT_ACTION_CHAIR_SOFA = 4,             // cam sit anywhere from the front
    aFTR_CONTACT_ACTION_BED_SINGLE = 8,             // single bed (can't roll)
    aFTR_CONTACT_ACTION_BED_DOUBLE = 0x10,          // double bed (can roll)

    aFTR_CONTACT_ACTION_NUM
};

enum {
    aFTR_CONTACT_ACTION_TYPE_CHAIR1,
    aFTR_CONTACT_ACTION_TYPE_CHAIR4,
    aFTR_CONTACT_ACTION_TYPE_SOFA,
    aFTR_CONTACT_ACTION_TYPE_BED_SINGLE,
    aFTR_CONTACT_ACTION_TYPE_BED_DOUBLE,

    aFTR_CONTACT_ACTION_TYPE_NUM
};

#define aFTR_CHK_CONTACT_ACTION(cnt, action) (((cnt) >> (aFTR_CONTACT_ACTION_TYPE_##action)) & 1)
#define aFTR_CHK_CHAIR(cnt) \
    (aFTR_CHK_CONTACT_ACTION(cnt, CHAIR1) || aFTR_CHK_CONTACT_ACTION(cnt, CHAIR4) || aFTR_CHK_CONTACT_ACTION(cnt, SOFA))
#define aFTR_CHK_BED(cnt) (aFTR_CHK_CONTACT_ACTION(cnt, BED_SINGLE) || aFTR_CHK_CONTACT_ACTION(cnt, BED_DOUBLE))

enum {
    aFTR_SET_TYPE_NORMAL,     /* Can't be placed on top and is not a table (layer0) */
    aFTR_SET_TYPE_SURFACE,    /* Is a surface (layer0) */
    aFTR_SET_TYPE_ON_SURFACE, /* Can be placed on a surface (layer0/layer1) */

    aFTR_SET_TYPE_NUM
};

enum {
    aFTR_KANKYO_MAP_NONE,
    aFTR_KANKYO_MAP_OPA,
    aFTR_KANKYO_MAP_XLU,

    aFTR_KANKYO_MAP_NUM
};

#define aFTR_CAN_PLAY_SE(ftr_actor)                                                \
    (ftr_actor->state != aFTR_STATE_BIRTH && ftr_actor->state != aFTR_STATE_BYE && \
     ftr_actor->state != aFTR_STATE_DEATH && ftr_actor->state != aFTR_STATE_BIRTH_WAIT)

typedef void (*aFTR_FTR_CT_PROC)(FTR_ACTOR*, u8*);
typedef void (*aFTR_FTR_MOVE_PROC)(FTR_ACTOR*, ACTOR*, GAME*, u8*);
typedef void (*aFTR_FTR_DRAW_PROC)(FTR_ACTOR*, ACTOR*, GAME*, u8*);
typedef void (*aFTR_FTR_DT_PROC)(FTR_ACTOR*, u8*);
typedef void (*aFTR_FTR_DMA_PROC)(mActor_name_t, u8*);

typedef struct ftr_vtbl_s {
    aFTR_FTR_CT_PROC ct_proc;
    aFTR_FTR_MOVE_PROC move_proc;
    aFTR_FTR_DRAW_PROC draw_proc;
    aFTR_FTR_DT_PROC dt_proc;
    aFTR_FTR_DMA_PROC dma_proc;
} aFTR_vtable_c;

typedef struct ftr_rig_s {
    cKF_Skeleton_R_c* skeleton;
    cKF_Animation_R_c* animation;
    f32 speed;
} aFTR_rig_c;

typedef struct ftr_tex_animation_s {
    u8** animation;
    int animation_count;
} aFTR_tex_anim_c;

typedef struct ftr_profile_s {
    Gfx* opaque0;
    Gfx* opaque1;
    Gfx* translucent0;
    Gfx* translucent1;
    u8* texture;
    u16* palette;
    aFTR_rig_c* rig;
    aFTR_tex_anim_c* tex_anim;
    f32 height;
    f32 scale;
    u8 shape;              /* aFTR_SHAPE_TYPE* */
    u8 move_bg_type;       /* mCoBG_FTR_TYPE* */
    u8 check_rotation;     /* when non-zero extra checks are performed for items in the way during rotation? */
    u8 kankyo_map;         /* lighting map */
    u8 contact_action;     /* action on contact */
    u16 interaction_type;  /* action when interacting */
    aFTR_vtable_c* vtable; /* unique furniture functions */
} aFTR_PROFILE;

typedef struct furniture_collision_s {
    f32 start[2];           /* starting xz pos */
    f32 end[2];             /* ending xz pos */
    f32 normal[2];          /* xz normal */
    f32 height;             /* collision y */
    f32 edge_contact_ratio; /* percentage of the xz collision in contact with edge to count as collision */
} aFTR_collision_c;

/* sizeof(FTR_ACTOR) == 0x868 */
struct furniture_actor_s {
    /* 0x000 */ u16 name;
    /* 0x002 */ s16 ctr_type; // 0 = GAME's frame counter, 1 = GAME_PLAY's frame counter
    /* 0x004 */ s16 _04;
    /* 0x008 */ int id;
    /* 0x00C */ xyz_t position;
    /* 0x018 */ xyz_t last_position;
    /* 0x024 */ xyz_t target_position;
    /* 0x030 */ int target_direction; /* direction to target position */
    /* 0x034 */ f32 player_distance;  /* distance to the player */
    /* 0x038 */ f32 angle_y;          /* current Y angle */
    /* 0x03C */ f32 angle_y_target;   /* goal Y angle */
    /* 0x040 */ s16 state;
    /* 0x042 */ u8 shape_type;          /* current size & shape (rotation) */
    /* 0x043 */ u8 original_shape_type; /* original size & shape (rotation) */
    /* 0x044 */ xyz_t base_position;
    /* 0x050 */ aFTR_collision_c edge_collision[aFTR_EDGE_COL_NUM]; /* collision for each edge */
    /* 0x0D0 */ s16 collision_direction;
    /* 0x0D4 */ int move_bg_idx;
    /* 0x0D8 */ mCoBG_bg_regist_c bg_register;
    /* 0x100 */ mCoBG_bg_contact_c bg_contact;
    /* 0x128 */ s16 s_angle_y; /* current Y angle but 'binangle' format */
    /* 0x12C */ f32 collision_scale;
    /* 0x130 */ u8 switch_bit;          /* furniture on/off state */
    /* 0x131 */ u8 switch_changed_flag; /* signal that the on/off state is toggled */
    /* 0x132 */ s8 haniwa_step;
    /* 0x134 */ s16 haniwa_state;
    /* 0x138 */ cKF_SkeletonInfo_R_c keyframe; /* for actor animations */
    /* 0x1A8 */ s_xyz joint[9];
    /* 0x1DE */ s_xyz morph[9];
    /* 0x218 */ Mtx skeleton_mtx[2][12];
    /* 0x818 */ cKF_TextureAnimation_c tex_animation; /* used for texture animations like TVs */
    /* 0x81C */ xyz_t scale;
    /* 0x828 */ f32 birth_scale_modifier; /* modifies scale for "birth" animation */
    /* 0x82C */ s16 birth_anim_counter;
    /* 0x82E */ s16 birth_anim_step;
    /* 0x830 */ s16 rotation_delay_timer;
    /* 0x832 */ s16 dynamic_work_s[5]; /* reserved for any use by each unique furniture actor */
    /* 0x83C */ f32 dynamic_work_f[4]; /* reserved for any use by each unique furniture actor */
    /* 0x84C */ s16 layer;             /* layer the furniture actor resides on */
    /* 0x84E */ s16 _84E;
    /* 0x850 */ s16 demo_status; /* set when a music player is interacted with */
    /* 0x852 */ s16 dust_timer;
    /* 0x854 */ mActor_name_t items[aFTR_KEEP_ITEM_COUNT]; /* used for holding items (music players & wardrobes)  */
    /* 0x85C */ int _85C;
    /* 0x860 */ u16* pal_p; /* used for furniture actors with dynamic palettes such as the structure model items */
    /* 0x864 */ int _864;
};

#ifdef __cplusplus
}
#endif

#endif
