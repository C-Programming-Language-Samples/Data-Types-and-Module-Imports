//----------------------------------------------------------------------
// complexnum.c
//----------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include "complexnum.h"

//----------------------------------------------------------------------

Complex complexNew(const double re, const double im) {
    return (Complex){sqrt(re * re + im * im), atan2(im, re)};
}

double complexRe(const Complex z) {
    return z.r * cos(z.theta);
}

double complexIm(const Complex z) {
    return z.r * sin(z.theta);
}

Complex complexConjugate(const Complex z) {
    return complexNew(complexRe(z), -complexIm(z));
}

Complex complexAdd(const Complex a, const Complex b) {
    const double re = complexRe(a) + complexRe(b);
    const double im = complexIm(a) + complexIm(b);
    return complexNew(re, im);
}

// Multiply the magnitudes and add the angles.
Complex complexMul(const Complex a, const Complex b) {
    return (Complex){a.r * b.r, a.theta + b.theta};
}

bool complexEquals(const Complex a, const Complex b) {
    return a.r == b.r && a.theta == b.theta;
}

double complexAbs(const Complex z) {
    return z.r;
}

char *complexToString(const Complex z, char *buf, const size_t size) {
    snprintf(buf, size, "%.15g + %.15gi", complexRe(z), complexIm(z));
    return buf;
}
