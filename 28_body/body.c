//----------------------------------------------------------------------
// body.c
//----------------------------------------------------------------------

#include <stdlib.h>
#include "body.h"

#define G 6.67e-11  // gravitational constant

struct Body {
    Vector *r;    // position
    Vector *v;    // velocity
    double mass;  // mass
};

//----------------------------------------------------------------------

Body *bodyNew(Vector *r, Vector *v, const double mass) {
    Body *b = malloc(sizeof(Body));
    b->r = r;
    b->v = v;
    b->mass = mass;
    return b;
}

void bodyFree(Body *b) {
    if (b == NULL) return;
    vectorFree(b->r);
    vectorFree(b->v);
    free(b);
}

void bodyMove(Body *b, const Vector *f, const double dt) {
    // a = f / mass, v = v + a dt, r = r + v dt
    Vector *a = vectorScale(f, 1.0 / b->mass);
    Vector *dv = vectorScale(a, dt);
    Vector *v = vectorPlus(b->v, dv);
    Vector *dr = vectorScale(v, dt);
    Vector *r = vectorPlus(b->r, dr);

    vectorFree(a);
    vectorFree(dv);
    vectorFree(dr);
    vectorFree(b->v);
    vectorFree(b->r);
    b->v = v;
    b->r = r;
}

Vector *bodyForceFrom(const Body *b, const Body *other) {
    Vector *delta = vectorMinus(other->r, b->r);
    const double dist = vectorAbs(delta);
    const double magnitude = (G * b->mass * other->mass) / (dist * dist);
    Vector *direction = vectorDirection(delta);
    Vector *force = vectorScale(direction, magnitude);
    vectorFree(delta);
    vectorFree(direction);
    return force;
}

void bodyDraw(const Body *b, Draw *d) {
    drawSetPenRadius(d, 0.0125);
    drawPoint(d, vectorGet(b->r, 0), vectorGet(b->r, 1));
}
