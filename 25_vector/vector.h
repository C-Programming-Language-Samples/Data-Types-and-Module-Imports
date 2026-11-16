//----------------------------------------------------------------------
// vector.h
//----------------------------------------------------------------------

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>

// An immutable spatial vector with n coordinates. Operations return a
// new Vector, which the caller frees with vectorFree().
typedef struct Vector Vector;

// Return a new Vector with a copy of the n coordinates in array a.
Vector *vectorNew(const double *a, int n);

// Free the memory used by v.
void vectorFree(Vector *v);

// Return the ith coordinate of v.
double vectorGet(const Vector *v, int i);

// Return the dimension of v.
int vectorDimension(const Vector *v);

// Return a + b / a - b.
Vector *vectorPlus(const Vector *a, const Vector *b);
Vector *vectorMinus(const Vector *a, const Vector *b);

// Return alpha * v.
Vector *vectorScale(const Vector *v, double alpha);

// Return the dot product of a and b.
double vectorDot(const Vector *a, const Vector *b);

// Return the magnitude of v.
double vectorAbs(const Vector *v);

// Return the unit vector in the direction of v.
Vector *vectorDirection(const Vector *v);

// Write v to out, such as [1, 2, 3, 4].
void vectorPrint(const Vector *v, FILE *out);

#endif
