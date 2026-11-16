//----------------------------------------------------------------------
// turtle.h
//----------------------------------------------------------------------

#ifndef TURTLE_H
#define TURTLE_H

#include "draw.h"

// A turtle that draws a line on a Draw canvas as it moves.
typedef struct {
    double x;      // x-coordinate
    double y;      // y-coordinate
    double angle;  // heading, in degrees counterclockwise from the x-axis
    Draw *draw;    // the canvas the turtle draws on
} Turtle;

// Return a new Turtle at (x, y) facing angle degrees, drawing on d.
Turtle turtleNew(Draw *d, double x, double y, double angle);

// Rotate t counterclockwise by delta degrees.
void turtleTurnLeft(Turtle *t, double delta);

// Move t forward by step, drawing a line.
void turtleGoForward(Turtle *t, double step);

#endif
