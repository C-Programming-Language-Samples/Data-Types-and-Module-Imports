//----------------------------------------------------------------------
// luminance.c
//----------------------------------------------------------------------

#include <math.h>
#include "luminance.h"

//----------------------------------------------------------------------

double luminance(const Color c) {
    return (0.299 * c.r) + (0.587 * c.g) + (0.114 * c.b);
}

Color luminanceToGray(const Color c) {
    const int y = (int)round(luminance(c));
    return (Color){y, y, y};
}

bool luminanceAreCompatible(const Color c1, const Color c2) {
    return fabs(luminance(c1) - luminance(c2)) >= 128.0;
}
