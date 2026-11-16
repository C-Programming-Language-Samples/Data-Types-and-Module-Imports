//----------------------------------------------------------------------
// histogram.c
//----------------------------------------------------------------------

#include <assert.h>
#include <stdlib.h>
#include "histogram.h"

struct Histogram {
    int n;            // number of possible values
    int *freqCounts;  // freqCounts[i] = number of occurrences of i
};

//----------------------------------------------------------------------

Histogram *histogramNew(const int n) {
    assert(n > 0);
    Histogram *h = malloc(sizeof(Histogram));
    h->n = n;
    h->freqCounts = calloc(n, sizeof(int));
    return h;
}

void histogramFree(Histogram *h) {
    if (h == NULL) return;
    free(h->freqCounts);
    free(h);
}

void histogramAddDataPoint(Histogram *h, const int i) {
    assert(i >= 0 && i < h->n);
    h->freqCounts[i]++;
}

void histogramDraw(const Histogram *h, Draw *d) {
    int max = 1;
    for (int i = 0; i < h->n; i++) {
        if (h->freqCounts[i] > max) max = h->freqCounts[i];
    }
    drawSetYscale(d, 0, max);
    drawSetXscale(d, -1, h->n);
    for (int i = 0; i < h->n; i++) {
        drawFilledRectangle(d, i - 0.25, 0.0, 0.5, h->freqCounts[i]);
    }
}
