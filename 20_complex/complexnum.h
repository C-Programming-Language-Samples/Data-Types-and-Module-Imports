//----------------------------------------------------------------------
// complexnum.h
//----------------------------------------------------------------------

#ifndef COMPLEXNUM_H
#define COMPLEXNUM_H

#include <stdbool.h>
#include <stddef.h>

// A complex number re + im i.
typedef struct {
    double re;  // real part
    double im;  // imaginary part
} Complex;

// Return the complex number re + im i.
Complex complexNew(double re, double im);

// Return the real / imaginary part of z.
double complexRe(Complex z);
double complexIm(Complex z);

// Return the complex conjugate of z.
Complex complexConjugate(Complex z);

// Return a + b.
Complex complexAdd(Complex a, Complex b);

// Return a * b.
Complex complexMul(Complex a, Complex b);

// Return true if a and b are equal.
bool complexEquals(Complex a, Complex b);

// Return the absolute value of z.
double complexAbs(Complex z);

// Write a string representation of z into buf and return buf.
char *complexToString(Complex z, char *buf, size_t size);

#endif
