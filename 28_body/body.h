//----------------------------------------------------------------------
// body.h
//----------------------------------------------------------------------

#ifndef BODY_H
#define BODY_H

#include "draw.h"
#include "vector.h"

// A body in space with a position, a velocity and a mass.
typedef struct Body Body;

// Return a new Body with position r, velocity v and the given mass.
// The Body takes ownership of r and v.
Body *bodyNew(Vector *r, Vector *v, double mass);

// Free the memory used by b, including its position and velocity.
void bodyFree(Body *b);

// Move b by applying force f for dt seconds.
void bodyMove(Body *b, const Vector *f, double dt);

// Return the gravitational force on b from other.
Vector *bodyForceFrom(const Body *b, const Body *other);

// Draw b as a dot on d.
void bodyDraw(const Body *b, Draw *d);

#endif
