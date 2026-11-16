//----------------------------------------------------------------------
// charge.c
//----------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include "charge.h"

#define COULOMB 8.99e09  // Coulomb's constant

//----------------------------------------------------------------------

Charge chargeNew(const double x0, const double y0, const double q0) {
    return (Charge){x0, y0, q0};
}

double chargePotentialAt(const Charge c, const double x, const double y) {
    const double dx = x - c.rx;
    const double dy = y - c.ry;
    const double r = sqrt(dx * dx + dy * dy);
    if (r == 0.0) {  // avoid division by 0
        return c.q >= 0.0 ? INFINITY : -INFINITY;
    }
    return COULOMB * c.q / r;
}

char *chargeToString(const Charge c, char *buf, const size_t size) {
    snprintf(buf, size, "%.15g at (%.15g, %.15g)", c.q, c.rx, c.ry);
    return buf;
}
