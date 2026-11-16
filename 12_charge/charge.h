//----------------------------------------------------------------------
// charge.h
//----------------------------------------------------------------------

#ifndef CHARGE_H
#define CHARGE_H

#include <stddef.h>

// A charged particle with charge q at the point (rx, ry).
typedef struct {
    double rx;  // x-coordinate
    double ry;  // y-coordinate
    double q;   // charge
} Charge;

// Return a new Charge at (x0, y0) with charge q0.
Charge chargeNew(double x0, double y0, double q0);

// Return the potential of c at the point (x, y).
double chargePotentialAt(Charge c, double x, double y);

// Write a string representation of c into buf and return buf.
char *chargeToString(Charge c, char *buf, size_t size);

#endif
