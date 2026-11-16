//----------------------------------------------------------------------
// 04_luminance.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "luminance.h"

//----------------------------------------------------------------------

// Main function: Accept six RGB values defining two colors as
// command-line arguments. Print True if the colors are compatible, and
// False otherwise.
int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Usage: %s <r1> <g1> <b1> <r2> <g2> <b2>\n", argv[0]);
        return 1;
    }
    const Color c1 = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3])};
    const Color c2 = {atoi(argv[4]), atoi(argv[5]), atoi(argv[6])};
    printf("%s\n", luminanceAreCompatible(c1, c2) ? "True" : "False");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 04_luminance 04_luminance.c luminance.c -I../lib -lm
// ./04_luminance 232 232 232 0 0 0
// True
// ./04_luminance 9 90 166 232 232 232
// True
// ./04_luminance 9 90 166 0 0 0
// False
