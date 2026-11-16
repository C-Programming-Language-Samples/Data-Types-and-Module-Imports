//----------------------------------------------------------------------
// draw.h
//----------------------------------------------------------------------

#ifndef DRAW_H
#define DRAW_H

#include <stdbool.h>
#include "color.h"

// A drawing canvas that is saved as an SVG file. The default scale is
// the unit square, with (0, 0) in the lower-left corner.
typedef struct Draw Draw;

// Return a new width-by-height canvas with a white background, written
// to the SVG file filename, or NULL if the file cannot be created.
Draw *drawOpen(const char *filename, int width, int height);

// Finish the SVG file and free d. Return true on success.
bool drawClose(Draw *d);

// Set the range of x / y coordinates shown on the canvas.
void drawSetXscale(Draw *d, double min, double max);
void drawSetYscale(Draw *d, double min, double max);

// Set the pen color (default black).
void drawSetPenColor(Draw *d, Color c);

// Set the pen radius as a fraction of a 512-pixel canvas (default 0.002).
void drawSetPenRadius(Draw *d, double radius);

// Paint the whole canvas with color c.
void drawClear(Draw *d, Color c);

// Draw a line from (x0, y0) to (x1, y1).
void drawLine(Draw *d, double x0, double y0, double x1, double y1);

// Draw a dot at (x, y).
void drawPoint(Draw *d, double x, double y);

// Draw a filled square centered at (x, y) with half-side length r.
void drawFilledSquare(Draw *d, double x, double y, double r);

// Draw a filled w-by-h rectangle with lower-left corner (x, y).
void drawFilledRectangle(Draw *d, double x, double y, double w, double h);

#endif
