//----------------------------------------------------------------------
// 18_drunk.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "draw.h"
#include "turtle.h"

//----------------------------------------------------------------------

// Return a random float in [a, b).
static double uniform(const double a, const double b) {
    return a + (b - a) * (rand() / (RAND_MAX + 1.0));
}

//----------------------------------------------------------------------

// Main function: Accept integer stepCount and float stepSize as
// command-line arguments. Have a turtle take stepCount random steps of
// size stepSize, and save its path to drunk.svg.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <stepCount> <stepSize>\n", argv[0]);
        return 1;
    }
    const int stepCount = atoi(argv[1]);
    const double stepSize = atof(argv[2]);
    srand(time(NULL));

    Draw *d = drawOpen("drunk.svg", 512, 512);
    if (d == NULL) {
        fprintf(stderr, "Could not create drunk.svg\n");
        return 1;
    }
    drawSetPenRadius(d, 0.0);
    drawClear(d, COLOR_LIGHT_GRAY);

    Turtle turtle = turtleNew(d, 0.5, 0.5, 0.0);
    for (int i = 0; i < stepCount; i++) {
        turtleTurnLeft(&turtle, uniform(0.0, 360.0));
        turtleGoForward(&turtle, stepSize);
    }

    drawClose(d);
    printf("Saved drunk.svg\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 18_drunk 18_drunk.c ../15_turtle/turtle.c ../lib/draw.c -I../15_turtle -I../lib -lm
// ./18_drunk 10000 .01
// Saved drunk.svg
// open drunk.svg
