//----------------------------------------------------------------------
// 28_body.c
//----------------------------------------------------------------------

#include <stdio.h>
#include "body.h"
#include "vector.h"

//----------------------------------------------------------------------

// Main function: Print the gravitational force on the Earth from the Sun.
int main(void) {
    const double sunR[] = {0.0, 0.0};
    const double sunV[] = {0.0, 0.0};
    const double earthR[] = {1.496e11, 0.0};
    const double earthV[] = {0.0, 2.98e4};
    Body *sun = bodyNew(vectorNew(sunR, 2), vectorNew(sunV, 2), 1.989e30);
    Body *earth = bodyNew(vectorNew(earthR, 2), vectorNew(earthV, 2), 5.972e24);

    Vector *f = bodyForceFrom(earth, sun);
    printf("force on the Earth from the Sun = ");
    vectorPrint(f, stdout);
    printf("\n");
    printf("magnitude = %.3e newtons\n", vectorAbs(f));

    vectorFree(f);
    bodyFree(sun);
    bodyFree(earth);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 28_body 28_body.c body.c ../25_vector/vector.c ../lib/draw.c -I../25_vector -I../lib -lm
// ./28_body
// force on the Earth from the Sun = [-3.54011384905202e+22, 0]
// magnitude = 3.540e+22 newtons
