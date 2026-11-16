//----------------------------------------------------------------------
// 14_histogram.c
//----------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "draw.h"
#include "histogram.h"

//----------------------------------------------------------------------

// Return true with probability p.
static bool bernoulli(const double p) {
    return rand() / (RAND_MAX + 1.0) < p;
}

// Return the number of heads in n flips of a coin that comes up heads
// with probability p.
static int binomial(const int n, const double p) {
    int heads = 0;
    for (int i = 0; i < n; i++) {
        if (bernoulli(p)) heads++;
    }
    return heads;
}

//----------------------------------------------------------------------

// Main function: Accept integer n, float p and integer trialCount as
// command-line arguments. Perform trialCount experiments, each counting
// the heads in n flips of a coin with heads probability p, and save a
// histogram of the results to histogram.svg.
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <p> <trialCount>\n", argv[0]);
        return 1;
    }
    const int n = atoi(argv[1]);
    const double p = atof(argv[2]);
    const int trialCount = atoi(argv[3]);
    if (n < 0) {
        fprintf(stderr, "n must not be negative\n");
        return 1;
    }
    srand(time(NULL));

    Histogram *histogram = histogramNew(n + 1);
    for (int trial = 0; trial < trialCount; trial++) {
        histogramAddDataPoint(histogram, binomial(n, p));
    }

    Draw *d = drawOpen("histogram.svg", 500, 200);
    if (d == NULL) {
        fprintf(stderr, "Could not create histogram.svg\n");
        histogramFree(histogram);
        return 1;
    }
    drawClear(d, COLOR_LIGHT_GRAY);
    histogramDraw(histogram, d);
    drawClose(d);
    histogramFree(histogram);
    printf("Saved histogram.svg\n");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 14_histogram 14_histogram.c histogram.c ../lib/draw.c -I../lib
// ./14_histogram 50 .5 1000000
// Saved histogram.svg
// open histogram.svg
