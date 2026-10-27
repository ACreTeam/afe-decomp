/* @(#)w_pow.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * wrapper pow(x,y) return x**y
 */

#include "MSL_C/MSL_Common_Embedded/Math/fdlibm.h"

#ifdef __STDC__
double pow(double x, double y) /* wrapper pow */
#else
double pow(x, y) /* wrapper pow */
double x, y;
#endif
{
    return __ieee754_pow(x, y);
}
