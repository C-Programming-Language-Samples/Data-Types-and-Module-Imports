//----------------------------------------------------------------------
// 21_mandelbrot.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "complexnum.h"
#include "picture.h"

#define MAX 255  // maximum number of iterations

//----------------------------------------------------------------------

// Return the number of iterations of the Mandelbrot sequence starting at
// z0 for which its magnitude stays at most 2, up to limit.
static int mandel(const Complex z0, const int limit) {
    Complex z = z0;
    for (int t = 0; t < limit; t++) {
        if (complexAbs(z) > 2.0) return t;
        z = complexAdd(complexMul(z, z), z0);
    }
    return limit;
}

//----------------------------------------------------------------------

// Main function: Accept integer n and floats xc, yc and size as
// command-line arguments. Sample the Mandelbrot set on an n-by-n grid
// in the square of the given size centered at (xc, yc), and save the
// image to mandelbrot.ppm.
int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <n> <xc> <yc> <size>\n", argv[0]);
        return 1;
    }
    const int n = atoi(argv[1]);
    const double xc = atof(argv[2]);
    const double yc = atof(argv[3]);
    const double size = atof(argv[4]);
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }

    Picture *pic = pictureNew(n, n);
    for (int col = 0; col < n; col++) {
        for (int row = 0; row < n; row++) {
            const double x0 = xc - size / 2 + size * col / n;
            const double y0 = yc - size / 2 + size * row / n;
            const Complex z0 = complexNew(x0, y0);
            const int gray = MAX - mandel(z0, MAX);
            pictureSet(pic, col, n - 1 - row, (Color){gray, gray, gray});
        }
    }

    const bool saved = pictureSave(pic, "mandelbrot.ppm");
    pictureFree(pic);
    if (!saved) {
        fprintf(stderr, "Could not save mandelbrot.ppm\n");
        return 1;
    }
    printf("Saved mandelbrot.ppm\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 21_mandelbrot 21_mandelbrot.c ../20_complex/complexnum.c ../lib/picture.c -I../20_complex -I../lib -lm
// ./21_mandelbrot 512 -.5 0 2
// Saved mandelbrot.ppm
// open mandelbrot.ppm

// ./21_mandelbrot 512 .1015 -.633 .01

// Compile with the polar Complex from 23_complexpolar instead:
// gcc -o 21_mandelbrot 21_mandelbrot.c ../23_complexpolar/complexnum.c ../lib/picture.c -I../23_complexpolar -I../lib -lm
