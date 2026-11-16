//----------------------------------------------------------------------
// 07_fade.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "picture.h"

//----------------------------------------------------------------------

// Return a color that blends c1 and c2, using alpha as the blending
// factor (0 gives c1, 1 gives c2).
static Color blend(const Color c1, const Color c2, const double alpha) {
    const double r = (1 - alpha) * c1.r + alpha * c2.r;
    const double g = (1 - alpha) * c1.g + alpha * c2.g;
    const double b = (1 - alpha) * c1.b + alpha * c2.b;
    return (Color){(int)r, (int)g, (int)b};
}

//----------------------------------------------------------------------

// Main function: Accept the names of two PPM image files of the same
// size and an integer n as command-line arguments. Fade from the first
// image to the second in n steps, and save the n + 1 frames to
// fade0.ppm, fade1.ppm, ..., fade<n>.ppm.
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <source.ppm> <target.ppm> <n>\n", argv[0]);
        return 1;
    }
    const int n = atoi(argv[3]);
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }
    Picture *source = pictureRead(argv[1]);
    Picture *target = pictureRead(argv[2]);
    if (source == NULL || target == NULL) {
        fprintf(stderr, "Could not read PPM image %s\n", source == NULL ? argv[1] : argv[2]);
        pictureFree(source);
        pictureFree(target);
        return 1;
    }
    const int width = pictureWidth(source);
    const int height = pictureHeight(source);
    if (pictureWidth(target) != width || pictureHeight(target) != height) {
        fprintf(stderr, "The two images must be the same size\n");
        pictureFree(source);
        pictureFree(target);
        return 1;
    }

    Picture *pic = pictureNew(width, height);
    for (int t = 0; t <= n; t++) {
        const double alpha = (double)t / n;
        for (int col = 0; col < width; col++) {
            for (int row = 0; row < height; row++) {
                const Color c0 = pictureGet(source, col, row);
                const Color cn = pictureGet(target, col, row);
                pictureSet(pic, col, row, blend(c0, cn, alpha));
            }
        }
        char filename[32];
        snprintf(filename, sizeof filename, "fade%d.ppm", t);
        if (!pictureSave(pic, filename)) {
            fprintf(stderr, "Could not save %s\n", filename);
            break;
        }
    }
    printf("Saved fade0.ppm ... fade%d.ppm\n", n);

    pictureFree(source);
    pictureFree(target);
    pictureFree(pic);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 07_fade 07_fade.c ../lib/picture.c -I../lib
// ./07_fade ../05_grayscale/mandrill.ppm ../05_grayscale/darwin.ppm 7
// Saved fade0.ppm ... fade7.ppm
// open fade*.ppm
