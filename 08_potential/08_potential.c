//----------------------------------------------------------------------
// 08_potential.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "charge.h"
#include "color.h"
#include "picture.h"

#define MAX_GRAY_SCALE 255
#define SIZE 512  // width and height of the image

//----------------------------------------------------------------------

// Main function: Read charged particles from standard input (their
// number, then x, y and charge for each). Color each pixel of an image
// with a gray value proportional to the total potential at that point,
// and save the image to potential.ppm.
int main(void) {
    // Read charges from standard input into an array.
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Expected the number of charges on standard input\n");
        return 1;
    }
    Charge *charges = malloc(n * sizeof(Charge));
    for (int i = 0; i < n; i++) {
        double x0, y0, q0;
        if (scanf("%lf %lf %lf", &x0, &y0, &q0) != 3) {
            fprintf(stderr, "Expected x, y and q for charge %d\n", i);
            free(charges);
            return 1;
        }
        charges[i] = chargeNew(x0, y0, q0);
    }

    // Create a Picture depicting potential values.
    Picture *pic = pictureNew(SIZE, SIZE);
    for (int col = 0; col < SIZE; col++) {
        for (int row = 0; row < SIZE; row++) {
            const double x = (double)col / SIZE;
            const double y = (double)row / SIZE;
            double v = 0.0;
            for (int i = 0; i < n; i++) {
                v += chargePotentialAt(charges[i], x, y);
            }
            v = (MAX_GRAY_SCALE / 2.0) + (v / 2.0e10);
            int gray;
            if (v > MAX_GRAY_SCALE) gray = MAX_GRAY_SCALE;
            else if (v > 0)         gray = (int)v;
            else                    gray = 0;
            pictureSet(pic, col, SIZE - 1 - row, (Color){gray, gray, gray});
        }
    }

    const bool saved = pictureSave(pic, "potential.ppm");
    pictureFree(pic);
    free(charges);
    if (!saved) {
        fprintf(stderr, "Could not save potential.ppm\n");
        return 1;
    }
    printf("Saved potential.ppm\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 08_potential 08_potential.c ../12_charge/charge.c ../lib/picture.c -I../12_charge -I../lib -lm
// ./08_potential < charges.txt
// Saved potential.ppm
// open potential.ppm
