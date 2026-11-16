//----------------------------------------------------------------------
// 03_alberssquares.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "draw.h"

//----------------------------------------------------------------------

// Main function: Accept integers r1, g1, b1, r2, g2 and b2 as
// command-line arguments. Draw Albers squares using colors (r1, g1, b1)
// and (r2, g2, b2), and save them to alberssquares.svg.
int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Usage: %s <r1> <g1> <b1> <r2> <g2> <b2>\n", argv[0]);
        return 1;
    }
    const Color c1 = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3])};
    const Color c2 = {atoi(argv[4]), atoi(argv[5]), atoi(argv[6])};

    Draw *d = drawOpen("alberssquares.svg", 512, 256);
    if (d == NULL) {
        fprintf(stderr, "Could not create alberssquares.svg\n");
        return 1;
    }
    drawSetYscale(d, 0.25, 0.75);

    drawSetPenColor(d, c1);
    drawFilledSquare(d, 0.25, 0.5, 0.2);
    drawSetPenColor(d, c2);
    drawFilledSquare(d, 0.25, 0.5, 0.1);

    drawSetPenColor(d, c2);
    drawFilledSquare(d, 0.75, 0.5, 0.2);
    drawSetPenColor(d, c1);
    drawFilledSquare(d, 0.75, 0.5, 0.1);

    drawClose(d);
    printf("Saved alberssquares.svg\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 03_alberssquares 03_alberssquares.c ../lib/draw.c -I../lib
// ./03_alberssquares 9 90 166 100 100 100
// Saved alberssquares.svg
// open alberssquares.svg

// ./03_alberssquares 0 174 239 147 149 252
