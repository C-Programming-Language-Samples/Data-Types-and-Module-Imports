//----------------------------------------------------------------------
// universe.h
//----------------------------------------------------------------------

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "draw.h"

// A collection of bodies that attract each other by gravity.
typedef struct Universe Universe;

// Return a new Universe read from a file, or NULL on failure.
Universe *universeNew(const char *filename);

// Free the memory used by u, including its bodies.
void universeFree(Universe *u);

// Simulate the passing of dt seconds in u.
void universeIncreaseTime(Universe *u, double dt);

// Draw the bodies of u on d.
void universeDraw(const Universe *u, Draw *d);

#endif
