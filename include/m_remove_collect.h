#ifndef M_REMOVE_COLLECT_H
#define M_REMOVE_COLLECT_H

#include "types.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

// @TODO: we could definitely use a struct for the DnM+ private data
extern void mRC_remove_collect_data_P_to_PP(Private_c* pp_priv, u8* p_priv);

#ifdef __cplusplus
}
#endif
#endif // M_REMOVE_COLLECT_H
