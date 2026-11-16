//----------------------------------------------------------------------
// complexnum.c
//----------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include "complexnum.h"

//----------------------------------------------------------------------

Complex complexNew(const double re, const double im) {
    return (Complex){re, im};
}

double complexRe(const Complex z) {
    return z.re;
}

double complexIm(const Complex z) {
    return z.im;
}

Complex complexConjugate(const Complex z) {
    return complexNew(z.re, -z.im);
}

Complex complexAdd(const Complex a, const Complex b) {
    const double re = a.re + b.re;
    const double im = a.im + b.im;
    return complexNew(re, im);
}

Complex complexMul(const Complex a, const Complex b) {
    const double re = a.re * b.re - a.im * b.im;
    const double im = a.re * b.im + a.im * b.re;
    return complexNew(re, im);
}

bool complexEquals(const Complex a, const Complex b) {
    return a.re == b.re && a.im == b.im;
}

double complexAbs(const Complex z) {
    return sqrt(z.re * z.re + z.im * z.im);
}

char *complexToString(const Complex z, char *buf, const size_t size) {
    snprintf(buf, size, "%.15g + %.15gi", z.re, z.im);
    return buf;
}
