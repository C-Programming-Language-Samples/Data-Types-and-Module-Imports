//----------------------------------------------------------------------
// draw.c
//----------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

#define DEFAULT_SIZE 512.0  // pen sizes are relative to a 512-pixel canvas

struct Draw {
    FILE *out;          // the SVG file
    int width;          // canvas width in pixels
    int height;         // canvas height in pixels
    double xmin, xmax;  // x-scale
    double ymin, ymax;  // y-scale
    Color penColor;
    double penRadius;
    bool styleOpen;     // is a <g> element with the pen style open?
};

//----------------------------------------------------------------------

// Convert x / y coordinates to SVG pixels (y grows downward in SVG).
static double toPixelX(const Draw *d, const double x) {
    return d->width * (x - d->xmin) / (d->xmax - d->xmin);
}

static double toPixelY(const Draw *d, const double y) {
    return d->height * (d->ymax - y) / (d->ymax - d->ymin);
}

// Convert a width / height to pixels.
static double toPixelWidth(const Draw *d, const double w) {
    return d->width * w / (d->xmax - d->xmin);
}

static double toPixelHeight(const Draw *d, const double h) {
    return d->height * h / (d->ymax - d->ymin);
}

// Open a <g> group with the current pen color and width.
static void beginStyle(Draw *d) {
    if (d->styleOpen) return;
    const Color c = d->penColor;
    double width = d->penRadius * DEFAULT_SIZE;
    if (width < 1.0) width = 1.0;
    fprintf(d->out, "<g stroke=\"#%02x%02x%02x\" fill=\"#%02x%02x%02x\" stroke-width=\"%.2f\">\n",
            c.r, c.g, c.b, c.r, c.g, c.b, width);
    d->styleOpen = true;
}

// Close the current <g> group, if any.
static void endStyle(Draw *d) {
    if (!d->styleOpen) return;
    fputs("</g>\n", d->out);
    d->styleOpen = false;
}

//----------------------------------------------------------------------

Draw *drawOpen(const char *filename, const int width, const int height) {
    assert(width > 0 && height > 0);
    FILE *out = fopen(filename, "w");
    if (out == NULL) return NULL;

    Draw *d = malloc(sizeof(Draw));
    *d = (Draw){
        .out = out, .width = width, .height = height,
        .xmin = 0.0, .xmax = 1.0, .ymin = 0.0, .ymax = 1.0,
        .penColor = COLOR_BLACK, .penRadius = 0.002, .styleOpen = false
    };
    fprintf(out, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%d\" height=\"%d\" "
                 "viewBox=\"0 0 %d %d\" stroke-linecap=\"round\">\n",
            width, height, width, height);
    drawClear(d, COLOR_WHITE);
    return d;
}

bool drawClose(Draw *d) {
    endStyle(d);
    fputs("</svg>\n", d->out);
    const bool written = !ferror(d->out);
    const bool closed = fclose(d->out) == 0;
    free(d);
    return written && closed;
}

void drawSetXscale(Draw *d, const double min, const double max) {
    assert(min < max);
    d->xmin = min;
    d->xmax = max;
}

void drawSetYscale(Draw *d, const double min, const double max) {
    assert(min < max);
    d->ymin = min;
    d->ymax = max;
}

void drawSetPenColor(Draw *d, const Color c) {
    assert(c.r >= 0 && c.r <= 255);
    assert(c.g >= 0 && c.g <= 255);
    assert(c.b >= 0 && c.b <= 255);
    if (c.r == d->penColor.r && c.g == d->penColor.g && c.b == d->penColor.b) return;
    endStyle(d);
    d->penColor = c;
}

void drawSetPenRadius(Draw *d, const double radius) {
    assert(radius >= 0.0);
    if (radius == d->penRadius) return;
    endStyle(d);
    d->penRadius = radius;
}

void drawClear(Draw *d, const Color c) {
    endStyle(d);
    fprintf(d->out, "<rect width=\"100%%\" height=\"100%%\" fill=\"#%02x%02x%02x\"/>\n",
            c.r, c.g, c.b);
}

void drawLine(Draw *d, const double x0, const double y0, const double x1, const double y1) {
    beginStyle(d);
    fprintf(d->out, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\"/>\n",
            toPixelX(d, x0), toPixelY(d, y0), toPixelX(d, x1), toPixelY(d, y1));
}

void drawPoint(Draw *d, const double x, const double y) {
    beginStyle(d);
    double r = d->penRadius * DEFAULT_SIZE / 2.0;
    if (r < 0.5) r = 0.5;
    fprintf(d->out, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" stroke=\"none\"/>\n",
            toPixelX(d, x), toPixelY(d, y), r);
}

void drawFilledSquare(Draw *d, const double x, const double y, const double r) {
    drawFilledRectangle(d, x - r, y - r, 2.0 * r, 2.0 * r);
}

void drawFilledRectangle(Draw *d, const double x, const double y, const double w, const double h) {
    beginStyle(d);
    fprintf(d->out, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke=\"none\"/>\n",
            toPixelX(d, x), toPixelY(d, y + h), toPixelWidth(d, w), toPixelHeight(d, h));
}
