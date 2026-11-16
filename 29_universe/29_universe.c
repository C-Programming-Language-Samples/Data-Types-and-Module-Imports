//----------------------------------------------------------------------
// 29_universe.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "universe.h"

//----------------------------------------------------------------------

// Main function: Accept a file name, a float dt and an integer steps as
// command-line arguments. Simulate the universe in the file for steps
// time steps of dt seconds, and save the paths of the bodies to
// universe.svg.
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <universeFile> <dt> <steps>\n", argv[0]);
        return 1;
    }
    const double dt = atof(argv[2]);
    const int steps = atoi(argv[3]);

    Universe *universe = universeNew(argv[1]);
    if (universe == NULL) {
        fprintf(stderr, "Could not read universe file %s\n", argv[1]);
        return 1;
    }
    Draw *d = drawOpen("universe.svg", 512, 512);
    if (d == NULL) {
        fprintf(stderr, "Could not create universe.svg\n");
        universeFree(universe);
        return 1;
    }
    drawClear(d, COLOR_BLACK);
    drawSetPenColor(d, COLOR_WHITE);

    for (int t = 0; t < steps; t++) {
        universeIncreaseTime(universe, dt);
        universeDraw(universe, d);
    }

    drawClose(d);
    universeFree(universe);
    printf("Saved universe.svg\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 29_universe 29_universe.c universe.c ../28_body/body.c ../25_vector/vector.c ../lib/draw.c -I../28_body -I../25_vector -I../lib -lm
// ./29_universe 3body.txt 20000 1000
// Saved universe.svg
// open universe.svg

// ./29_universe 2body.txt 20000 1500
// ./29_universe 4body.txt 20000 1000
// ./29_universe 2bodytiny.txt 20000 1500
