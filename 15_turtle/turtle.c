//----------------------------------------------------------------------
// turtle.c
//----------------------------------------------------------------------

#include <math.h>
#include "turtle.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//----------------------------------------------------------------------

// Convert degrees to radians.
static double radians(const double degrees) {
    return degrees * M_PI / 180.0;
}

//----------------------------------------------------------------------

Turtle turtleNew(Draw *d, const double x, const double y, const double angle) {
    return (Turtle){x, y, angle, d};
}

void turtleTurnLeft(Turtle *t, const double delta) {
    t->angle += delta;
}

void turtleGoForward(Turtle *t, const double step) {
    const double oldx = t->x;
    const double oldy = t->y;
    t->x += step * cos(radians(t->angle));
    t->y += step * sin(radians(t->angle));
    drawLine(t->draw, oldx, oldy, t->x, t->y);
}
