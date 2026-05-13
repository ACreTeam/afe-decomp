#ifndef CMATH_GCN_H
#define CMATH_GCN_H

#include "MSL_C/w_math.h"
// #include "MSL_C/MSL_Common/float.h"

#define HALF_PI    1.5707964f

#ifdef __cplusplus
namespace std {
#endif

    float sqrtf(float);
    float sinf(float);

    inline float sinf(float x) {
        return (float)sin((double)x);
    }

#if __MWERKS__ > 0x2301 && VERSION == VER_GAEJ01_01
    inline float sqrtf(float x)
    {
        static const double _half = .5f;
        static const double _three = 3.0f;
        if (x > 0.0f)
        {
            double xd = (double)x;
            double guess = __frsqrte(xd);                          // returns an approximation to
            guess = _half * guess * (_three - guess * guess * xd); // now have 12 sig bits
            guess = _half * guess * (_three - guess * guess * xd); // now have 24 sig bits
            guess = _half * guess * (_three - guess * guess * xd); // now have 32 sig bits
            return (float)(xd * guess);
        }
        else if (x < 0.0)
        {
            return NAN;
        }
        else if (isnan(x))
        {
            return NAN;
        }
        else
        {
            return x;
        }
    }
    #else

    inline float sqrtf(float x) {
        static const double _half = .5;
        static const double _three = 3.0;
        volatile float y;

        if (x > 0.0f) {
            double guess = __frsqrte((double)x);                  // returns an approximation to
            guess = _half * guess * (_three - guess * guess * x); // now have 12 sig bits
            guess = _half * guess * (_three - guess * guess * x); // now have 24 sig bits
            guess = _half * guess * (_three - guess * guess * x); // now have 32 sig bits
            y = (float)(x * guess);
            return y;
        }

        return x;
    }
#endif

#ifdef __cplusplus
}
#endif

// TODO: this should be obtained from the other math header
// inline float sqrtf(float x) {
//     static const double _half = .5;
//     static const double _three = 3.0;
//     volatile float y;

//     if (x > 0.0f) {
//         double guess = __frsqrte((double)x);                  // returns an approximation to
//         guess = _half * guess * (_three - guess * guess * x); // now have 12 sig bits
//         guess = _half * guess * (_three - guess * guess * x); // now have 24 sig bits
//         guess = _half * guess * (_three - guess * guess * x); // now have 32 sig bits
//         y = (float)(x * guess);
//         return y;
//     }

//     return x;
// }

#endif
