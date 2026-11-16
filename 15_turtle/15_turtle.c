//----------------------------------------------------------------------
// 15_turtle.c
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

// Main function: Accept integer n as a command-line argument. Draw a
// regular polygon with n sides and save it to turtle.svg.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    const int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }

    Draw *d = drawOpen("turtle.svg", 512, 512);
    if (d == NULL) {
        fprintf(stderr, "Could not create turtle.svg\n");
        return 1;
    }
    drawClear(d, COLOR_LIGHT_GRAY);

    Turtle turtle = turtleNew(d, 0.5, 0.0, 180.0 / n);
    const double stepSize = sin(M_PI / n);
    for (int i = 0; i < n; i++) {
        turtleGoForward(&turtle, stepSize);
        turtleTurnLeft(&turtle, 360.0 / n);
    }

    drawClose(d);
    printf("Saved turtle.svg\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 15_turtle 15_turtle.c turtle.c ../lib/draw.c -I../lib -lm
// ./15_turtle 3
// Saved turtle.svg
// open turtle.svg

// ./15_turtle 7
// ./15_turtle 30
