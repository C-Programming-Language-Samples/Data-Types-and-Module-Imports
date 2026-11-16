//----------------------------------------------------------------------
// 19_drunks.c
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

// Main function: Accept integer turtleCount, integer stepCount and float
// stepSize as command-line arguments. Have turtleCount turtles take
// stepCount random steps of size stepSize, and save their paths to
// drunks.svg.
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <turtleCount> <stepCount> <stepSize>\n", argv[0]);
        return 1;
    }
    const int turtleCount = atoi(argv[1]);
    const int stepCount = atoi(argv[2]);
    const double stepSize = atof(argv[3]);
    if (turtleCount <= 0) {
        fprintf(stderr, "turtleCount must be positive\n");
        return 1;
    }
    srand(time(NULL));

    Draw *d = drawOpen("drunks.svg", 512, 512);
    if (d == NULL) {
        fprintf(stderr, "Could not create drunks.svg\n");
        return 1;
    }
    drawSetPenRadius(d, 0.0);
    drawClear(d, COLOR_LIGHT_GRAY);

    Turtle *turtles = malloc(turtleCount * sizeof(Turtle));
    for (int i = 0; i < turtleCount; i++) {
        const double x = uniform(0.0, 1.0);
        const double y = uniform(0.0, 1.0);
        turtles[i] = turtleNew(d, x, y, 0.0);
    }
    for (int j = 0; j < stepCount; j++) {
        for (int i = 0; i < turtleCount; i++) {
            turtleTurnLeft(&turtles[i], uniform(0.0, 360.0));
            turtleGoForward(&turtles[i], stepSize);
        }
    }

    free(turtles);
    drawClose(d);
    printf("Saved drunks.svg\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 19_drunks 19_drunks.c ../15_turtle/turtle.c ../lib/draw.c -I../15_turtle -I../lib -lm
// ./19_drunks 20 500 .005
// Saved drunks.svg
// open drunks.svg

// ./19_drunks 20 1000 .005
// ./19_drunks 20 5000 .005
