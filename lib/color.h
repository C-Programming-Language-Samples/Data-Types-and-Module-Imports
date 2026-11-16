//----------------------------------------------------------------------
// color.h
//----------------------------------------------------------------------

#ifndef COLOR_H
#define COLOR_H

// A color with red, green and blue components from 0 to 255.
typedef struct {
    int r;  // red
    int g;  // green
    int b;  // blue
} Color;

#define COLOR_BLACK      ((Color){0, 0, 0})
#define COLOR_WHITE      ((Color){255, 255, 255})
#define COLOR_LIGHT_GRAY ((Color){192, 192, 192})

#endif
