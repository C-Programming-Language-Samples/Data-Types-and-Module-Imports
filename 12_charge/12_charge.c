//----------------------------------------------------------------------
// 12_charge.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "charge.h"

//----------------------------------------------------------------------

// Main function: Accept floats x and y as command-line arguments.
// Create a Charge and print it and its potential at (x, y).
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <x> <y>\n", argv[0]);
        return 1;
    }
    const double x = atof(argv[1]);
    const double y = atof(argv[2]);

    const Charge c = chargeNew(0.51, 0.63, 21.3);
    char buf[64];
    printf("%s\n", chargeToString(c, buf, sizeof buf));
    printf("%.15g\n", chargePotentialAt(c, x, y));
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 12_charge 12_charge.c charge.c -lm
// ./12_charge .5 .5
// 21.3 at (0.51, 0.63)
// 1468638248194.16
