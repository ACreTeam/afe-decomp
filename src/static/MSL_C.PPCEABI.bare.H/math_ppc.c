#undef __USE_INLINE
#define __USE_INLINE 1
#undef __INLINE
#define __INLINE __declspec(weak)

// Redefine the __INLINE macro to be weak so the functions are emitted here
// but can still be inlined in other TUs.
#include "MSL_C/MSL_Common/float.h"
