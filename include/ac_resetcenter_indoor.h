#ifndef AC_RESETCENTER_INDOOR_H
#define AC_RESETCENTER_INDOOR_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aRI_LIGHT_JOINT_NUM 16

typedef struct resetcenter_indoor_actor_s RESETCENTER_INDOOR_ACTOR;

typedef struct {
    int pointlight_idx;
    xyz_t pos;
    s16 angle;
    s16 counter;
    f32 _14;
    f32 rnd;
} aRI_tv_c;

typedef struct {
    f32 target;
    f32 alpha_percent;
} aRI_door_c;

typedef struct {
    u8 state;
    u8 light_color;
    f32 prim_r;
    f32 prim_g;
    f32 prim_b;
    int pointlight_idx;
    int _14;
    cKF_SkeletonInfo_R_c kf;
    s_xyz work[aRI_LIGHT_JOINT_NUM+1];
    s_xyz morph[aRI_LIGHT_JOINT_NUM+1];
    Mtx mtx[2][aRI_LIGHT_JOINT_NUM];
    s16 counter;
} aRI_light_c;

struct resetcenter_indoor_actor_s {
    ACTOR actor_class;
    aRI_tv_c tv;
    aRI_door_c door;
    aRI_light_c light;
    // s16 _AF0;
    u8 nodraw_cmo_boots; // don't draw Resetti's boots
    u8 nodraw_cmb_boots; // don't draw Don's boots
    u8 _AF4[0xAF8-0xAF4];
};

extern int aRI_request_appear_door(void);
extern int aRI_request_disappear_door(void);
extern f32 aRI_get_door_alpha_percent(void);
extern int aRI_request_light_on(void);
extern int aRI_request_light_off(void);
extern void aRI_set_resetcenter_prim_color(GAME* game);
extern int aRI_delete_boots_of_Reset(void);
extern int mRI_delete_boots_of_Racket(void);
extern int aRI_get_reset_mode(void);
extern int aRI_get_reset_mode_E(void);
extern void aRI_next_mode(void);

extern ACTOR_PROFILE Resetcenter_Indoor_Profile;

#ifdef __cplusplus
}
#endif

#endif /* AC_RESETCENTER_INDOOR_H */
