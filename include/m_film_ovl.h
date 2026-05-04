#ifndef M_FILM_OVL_H
#define M_FILM_OVL_H

#include "types.h"
#include "m_submenu.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct film_ovl_s mFM_Ovl_c;

// TODO: finish

static void mFL_film_ovl_construct(Submenu* submenu);
static void mFL_film_ovl_destruct(Submenu* submenu);
static void mFL_film_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif
#endif // M_FILM_OVL_H
