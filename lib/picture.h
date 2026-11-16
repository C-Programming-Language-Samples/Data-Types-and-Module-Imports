//----------------------------------------------------------------------
// picture.h
//----------------------------------------------------------------------

#ifndef PICTURE_H
#define PICTURE_H

#include <stdbool.h>
#include "color.h"

// A width-by-height grid of pixels, read from and saved to PPM (P6)
// image files. Pixel (0, 0) is the upper-left corner.
typedef struct Picture Picture;

// Return a new width-by-height Picture with all pixels black.
Picture *pictureNew(int width, int height);

// Return a new Picture read from a PPM file, or NULL on failure.
Picture *pictureRead(const char *filename);

// Free the memory used by pic.
void pictureFree(Picture *pic);

// Return the width / height of pic in pixels.
int pictureWidth(const Picture *pic);
int pictureHeight(const Picture *pic);

// Return the color of pixel (col, row).
Color pictureGet(const Picture *pic, int col, int row);

// Set the color of pixel (col, row) to c.
void pictureSet(Picture *pic, int col, int row, Color c);

// Save pic to a PPM file. Return true on success.
bool pictureSave(const Picture *pic, const char *filename);

#endif
