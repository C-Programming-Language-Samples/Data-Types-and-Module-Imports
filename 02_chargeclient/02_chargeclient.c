//----------------------------------------------------------------------
// 02_chargeclient.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "charge.h"

//----------------------------------------------------------------------

// Main function: Accept floats x and y as command-line arguments.
// Create two Charges and print the potential at (x, y) due to them.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <x> <y>\n", argv[0]);
        return 1;
    }
    const double x = atof(argv[1]);
    const double y = atof(argv[2]);

    const Charge c1 = chargeNew(0.51, 0.63, 21.3);
    const Charge c2 = chargeNew(0.13, 0.94, 81.9);
    const double v1 = chargePotentialAt(c1, x, y);
    const double v2 = chargePotentialAt(c2, x, y);

    char s1[64], s2[64];
    printf("potential at (%.2f, %.2f) due to\n", x, y);
    printf("  %s and\n", chargeToString(c1, s1, sizeof s1));
    printf("  %s\n", chargeToString(c2, s2, sizeof s2));
    printf("is %.2e\n", v1 + v2);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 02_chargeclient 02_chargeclient.c ../12_charge/charge.c -I../12_charge -lm
// ./02_chargeclient .2 .5
// potential at (0.20, 0.50) due to
//   21.3 at (0.51, 0.63) and
//   81.9 at (0.13, 0.94)
// is 2.22e+12

// ./02_chargeclient .51 .94
// potential at (0.51, 0.94) due to
//   21.3 at (0.51, 0.63) and
//   81.9 at (0.13, 0.94)
// is 2.56e+12
