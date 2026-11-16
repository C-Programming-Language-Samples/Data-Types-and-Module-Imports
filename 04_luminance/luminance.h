//----------------------------------------------------------------------
// luminance.h
//----------------------------------------------------------------------

#ifndef LUMINANCE_H
#define LUMINANCE_H

#include <stdbool.h>
#include "color.h"

// Return the luminance of c.
double luminance(Color c);

// Return the gray color with the same luminance as c.
Color luminanceToGray(Color c);

// Return true if c1 and c2 are compatible (their luminances differ by
// at least 128), and false otherwise.
bool luminanceAreCompatible(Color c1, Color c2);

#endif
