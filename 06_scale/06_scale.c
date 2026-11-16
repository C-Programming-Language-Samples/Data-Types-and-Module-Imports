//----------------------------------------------------------------------
// 06_scale.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "picture.h"

//----------------------------------------------------------------------

// Main function: Accept the name of a PPM image file and integers w and
// h as command-line arguments. Scale the image to width w and height h,
// and save it to scale.ppm.
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <image.ppm> <w> <h>\n", argv[0]);
        return 1;
    }
    const int w = atoi(argv[2]);
    const int h = atoi(argv[3]);
    if (w <= 0 || h <= 0) {
        fprintf(stderr, "Width and height must be positive\n");
        return 1;
    }
    Picture *source = pictureRead(argv[1]);
    if (source == NULL) {
        fprintf(stderr, "Could not read PPM image %s\n", argv[1]);
        return 1;
    }
    Picture *target = pictureNew(w, h);

    for (int tCol = 0; tCol < w; tCol++) {
        for (int tRow = 0; tRow < h; tRow++) {
            const int sCol = tCol * pictureWidth(source) / w;
            const int sRow = tRow * pictureHeight(source) / h;
            pictureSet(target, tCol, tRow, pictureGet(source, sCol, sRow));
        }
    }

    const bool saved = pictureSave(target, "scale.ppm");
    pictureFree(source);
    pictureFree(target);
    if (!saved) {
        fprintf(stderr, "Could not save scale.ppm\n");
        return 1;
    }
    printf("Saved scale.ppm\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 06_scale 06_scale.c ../lib/picture.c -I../lib
// ./06_scale ../05_grayscale/mandrill.ppm 800 800
// Saved scale.ppm
// open scale.ppm

// ./06_scale ../05_grayscale/mandrill.ppm 600 300
// ./06_scale ../05_grayscale/mandrill.ppm 200 400
// ./06_scale ../05_grayscale/darwin.ppm 200 200
