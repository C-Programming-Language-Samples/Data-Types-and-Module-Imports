//----------------------------------------------------------------------
// 05_grayscale.c
//----------------------------------------------------------------------

#include <stdio.h>
#include "luminance.h"
#include "picture.h"

//----------------------------------------------------------------------

// Main function: Accept the name of a PPM image file as a command-line
// argument. Convert the image to grayscale and save it to grayscale.ppm.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image.ppm>\n", argv[0]);
        return 1;
    }
    Picture *pic = pictureRead(argv[1]);
    if (pic == NULL) {
        fprintf(stderr, "Could not read PPM image %s\n", argv[1]);
        return 1;
    }

    for (int col = 0; col < pictureWidth(pic); col++) {
        for (int row = 0; row < pictureHeight(pic); row++) {
            const Color pixel = pictureGet(pic, col, row);
            const Color gray = luminanceToGray(pixel);
            pictureSet(pic, col, row, gray);
        }
    }

    const bool saved = pictureSave(pic, "grayscale.ppm");
    pictureFree(pic);
    if (!saved) {
        fprintf(stderr, "Could not save grayscale.ppm\n");
        return 1;
    }
    printf("Saved grayscale.ppm\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 05_grayscale 05_grayscale.c ../04_luminance/luminance.c ../lib/picture.c -I../04_luminance -I../lib -lm
// ./05_grayscale mandrill.ppm
// Saved grayscale.ppm
// open grayscale.ppm

// ./05_grayscale darwin.ppm
