//----------------------------------------------------------------------
// 17_spiral.c
//----------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "turtle.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//----------------------------------------------------------------------

// Main function: Accept integer n (number of sides), integer wraps and
// float decay as command-line arguments. Draw a spiral with those
// characteristics and save it to spiral.svg.
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <wraps> <decay>\n", argv[0]);
        return 1;
    }
    const int n = atoi(argv[1]);
    const int wraps = atoi(argv[2]);
    const double decay = atof(argv[3]);
    if (n <= 0 || decay <= 0.0) {
        fprintf(stderr, "n and decay must be positive\n");
        return 1;
    }

    Draw *d = drawOpen("spiral.svg", 512, 512);
    if (d == NULL) {
        fprintf(stderr, "Could not create spiral.svg\n");
        return 1;
    }
    drawSetPenRadius(d, 0.0);
    drawClear(d, COLOR_LIGHT_GRAY);

    const double angle = 360.0 / n;
    double step = sin(M_PI / n);
    Turtle turtle = turtleNew(d, 0.5, 0.0, angle / 2.0);
    for (int i = 0; i < wraps * n; i++) {
        step /= decay;
        turtleGoForward(&turtle, step);
        turtleTurnLeft(&turtle, angle);
    }

    drawClose(d);
    printf("Saved spiral.svg\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 17_spiral 17_spiral.c ../15_turtle/turtle.c ../lib/draw.c -I../15_turtle -I../lib -lm
// ./17_spiral 1440 10 1.00004
// Saved spiral.svg
// open spiral.svg

// ./17_spiral 3 1 1.0
// ./17_spiral 3 10 1.2
// ./17_spiral 1440 10 1.0004
