#include "MSL_C/w_math.h"

extern double sqrt(double x) {
    return __ieee754_sqrt(x);
}
