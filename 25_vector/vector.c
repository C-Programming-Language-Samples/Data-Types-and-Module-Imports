//----------------------------------------------------------------------
// vector.c
//----------------------------------------------------------------------

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

struct Vector {
    int n;           // dimension
    double *coords;  // Cartesian coordinates
};

//----------------------------------------------------------------------

// Return a new Vector of dimension n with coordinates not yet set.
static Vector *allocate(const int n) {
    assert(n >= 0);
    Vector *v = malloc(sizeof(Vector));
    v->n = n;
    v->coords = malloc(n * sizeof(double));
    return v;
}

//----------------------------------------------------------------------

Vector *vectorNew(const double *a, const int n) {
    Vector *v = allocate(n);
    if (n > 0) memcpy(v->coords, a, n * sizeof(double));
    return v;
}

void vectorFree(Vector *v) {
    if (v == NULL) return;
    free(v->coords);
    free(v);
}

double vectorGet(const Vector *v, const int i) {
    assert(i >= 0 && i < v->n);
    return v->coords[i];
}

int vectorDimension(const Vector *v) {
    return v->n;
}

Vector *vectorPlus(const Vector *a, const Vector *b) {
    assert(a->n == b->n);
    Vector *result = allocate(a->n);
    for (int i = 0; i < a->n; i++) {
        result->coords[i] = a->coords[i] + b->coords[i];
    }
    return result;
}

Vector *vectorMinus(const Vector *a, const Vector *b) {
    assert(a->n == b->n);
    Vector *result = allocate(a->n);
    for (int i = 0; i < a->n; i++) {
        result->coords[i] = a->coords[i] - b->coords[i];
    }
    return result;
}

Vector *vectorScale(const Vector *v, const double alpha) {
    Vector *result = allocate(v->n);
    for (int i = 0; i < v->n; i++) {
        result->coords[i] = alpha * v->coords[i];
    }
    return result;
}

double vectorDot(const Vector *a, const Vector *b) {
    assert(a->n == b->n);
    double sum = 0.0;
    for (int i = 0; i < a->n; i++) {
        sum += a->coords[i] * b->coords[i];
    }
    return sum;
}

double vectorAbs(const Vector *v) {
    return sqrt(vectorDot(v, v));
}

Vector *vectorDirection(const Vector *v) {
    return vectorScale(v, 1.0 / vectorAbs(v));
}

void vectorPrint(const Vector *v, FILE *out) {
    fputc('[', out);
    for (int i = 0; i < v->n; i++) {
        if (i > 0) fputs(", ", out);
        fprintf(out, "%.15g", v->coords[i]);
    }
    fputc(']', out);
}
