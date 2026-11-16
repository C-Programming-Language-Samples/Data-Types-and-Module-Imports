//----------------------------------------------------------------------
// histogram.h
//----------------------------------------------------------------------

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "draw.h"

// Frequency counts of the values 0 to n-1, drawn as a bar chart.
typedef struct Histogram Histogram;

// Return a new Histogram for the values 0 to n-1.
Histogram *histogramNew(int n);

// Free the memory used by h.
void histogramFree(Histogram *h);

// Add one occurrence of the value i to h.
void histogramAddDataPoint(Histogram *h, int i);

// Draw h as a bar chart on d.
void histogramDraw(const Histogram *h, Draw *d);

#endif
