//----------------------------------------------------------------------
// 16_koch.c
//----------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "turtle.h"

//----------------------------------------------------------------------

// Draw a Koch curve of order n with the given step size, using turtle.
static void koch(const int n, const double stepSize, Turtle *turtle) {
    if (n == 0) {
        turtleGoForward(turtle, stepSize);
        return;
    }
    koch(n - 1, stepSize, turtle);
    turtleTurnLeft(turtle, 60.0);
    koch(n - 1, stepSize, turtle);
    turtleTurnLeft(turtle, -120.0);
    koch(n - 1, stepSize, turtle);
    turtleTurnLeft(turtle, 60.0);
    koch(n - 1, stepSize, turtle);
}

//----------------------------------------------------------------------

// Main function: Accept integer n as a command-line argument. Draw a
// Koch curve of order n and save it to koch.svg.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    const int n = atoi(argv[1]);
    if (n < 0) {
        fprintf(stderr, "n must not be negative\n");
        return 1;
    }

    Draw *d = drawOpen("koch.svg", 512, 256);
    if (d == NULL) {
        fprintf(stderr, "Could not create koch.svg\n");
        return 1;
    }
    drawSetYscale(d, -0.1, 0.4);
    drawSetPenRadius(d, 0.0);
    drawClear(d, COLOR_LIGHT_GRAY);

    const double stepSize = 1.0 / pow(3.0, n);
    Turtle turtle = turtleNew(d, 0.0, 0.0, 0.0);
    koch(n, stepSize, &turtle);

    drawClose(d);
    printf("Saved koch.svg\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 16_koch 16_koch.c ../15_turtle/turtle.c ../lib/draw.c -I../15_turtle -I../lib -lm
// ./16_koch 4
// Saved koch.svg
// open koch.svg

// ./16_koch 0
// ./16_koch 1
// ./16_koch 2
// ./16_koch 3
