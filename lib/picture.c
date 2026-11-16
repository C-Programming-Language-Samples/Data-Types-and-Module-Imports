//----------------------------------------------------------------------
// picture.c
//----------------------------------------------------------------------

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "picture.h"

struct Picture {
    int width;
    int height;
    unsigned char *rgb;  // 3 bytes per pixel, row by row from the top
};

//----------------------------------------------------------------------

// Return a pointer to the 3 bytes of pixel (col, row).
static unsigned char *pixel(const Picture *pic, const int col, const int row) {
    assert(col >= 0 && col < pic->width);
    assert(row >= 0 && row < pic->height);
    return pic->rgb + 3 * ((size_t)row * pic->width + col);
}

// Read the next number of a PPM header, skipping whitespace and
// comments. Return true on success.
static bool readHeaderInt(FILE *in, int *value) {
    int c = fgetc(in);
    while (isspace(c) || c == '#') {
        if (c == '#') {
            while (c != '\n' && c != EOF) c = fgetc(in);
        }
        c = fgetc(in);
    }
    if (c == EOF) return false;
    ungetc(c, in);
    return fscanf(in, "%d", value) == 1;
}

//----------------------------------------------------------------------

Picture *pictureNew(const int width, const int height) {
    assert(width > 0 && height > 0);
    Picture *pic = malloc(sizeof(Picture));
    pic->width = width;
    pic->height = height;
    pic->rgb = calloc((size_t)width * height * 3, 1);
    return pic;
}

Picture *pictureRead(const char *filename) {
    FILE *in = fopen(filename, "rb");
    if (in == NULL) return NULL;

    // Header: "P6", width, height, maximum value 255, one whitespace
    int width, height, maxValue;
    const bool ok = fgetc(in) == 'P' && fgetc(in) == '6'
                 && readHeaderInt(in, &width)
                 && readHeaderInt(in, &height)
                 && readHeaderInt(in, &maxValue)
                 && width > 0 && height > 0 && maxValue == 255
                 && isspace(fgetc(in));

    Picture *pic = NULL;
    if (ok) {
        pic = pictureNew(width, height);
        const size_t n = (size_t)width * height * 3;
        if (fread(pic->rgb, 1, n, in) != n) {
            pictureFree(pic);
            pic = NULL;
        }
    }
    fclose(in);
    return pic;
}

void pictureFree(Picture *pic) {
    if (pic == NULL) return;
    free(pic->rgb);
    free(pic);
}

int pictureWidth(const Picture *pic) {
    return pic->width;
}

int pictureHeight(const Picture *pic) {
    return pic->height;
}

Color pictureGet(const Picture *pic, const int col, const int row) {
    const unsigned char *p = pixel(pic, col, row);
    return (Color){p[0], p[1], p[2]};
}

void pictureSet(Picture *pic, const int col, const int row, const Color c) {
    assert(c.r >= 0 && c.r <= 255);
    assert(c.g >= 0 && c.g <= 255);
    assert(c.b >= 0 && c.b <= 255);
    unsigned char *p = pixel(pic, col, row);
    p[0] = (unsigned char)c.r;
    p[1] = (unsigned char)c.g;
    p[2] = (unsigned char)c.b;
}

bool pictureSave(const Picture *pic, const char *filename) {
    FILE *out = fopen(filename, "wb");
    if (out == NULL) return false;
    fprintf(out, "P6\n%d %d\n255\n", pic->width, pic->height);
    const size_t n = (size_t)pic->width * pic->height * 3;
    const bool written = fwrite(pic->rgb, 1, n, out) == n;
    const bool closed = fclose(out) == 0;
    return written && closed;
}
