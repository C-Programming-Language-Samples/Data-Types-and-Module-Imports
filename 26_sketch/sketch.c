//----------------------------------------------------------------------
// sketch.c
//----------------------------------------------------------------------

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "sketch.h"
#include "vector.h"

struct Sketch {
    Vector *profile;  // unit vector
};

//----------------------------------------------------------------------

// Return a hash code for the k characters starting at s.
static unsigned int hash(const char *s, const int k) {
    unsigned int h = 0;
    for (int i = 0; i < k; i++) {
        h = 31 * h + (unsigned char)s[i];
    }
    return h;
}

//----------------------------------------------------------------------

Sketch *sketchNew(const char *text, const int k, const int d) {
    assert(k > 0 && d > 0);
    double *freq = calloc(d, sizeof(double));
    const size_t length = strlen(text);
    for (size_t i = 0; i + k <= length; i++) {
        freq[hash(text + i, k) % d] += 1.0;
    }
    Vector *vector = vectorNew(freq, d);
    free(freq);

    Sketch *s = malloc(sizeof(Sketch));
    s->profile = vectorDirection(vector);
    vectorFree(vector);
    return s;
}

void sketchFree(Sketch *s) {
    if (s == NULL) return;
    vectorFree(s->profile);
    free(s);
}

double sketchSimilarTo(const Sketch *a, const Sketch *b) {
    return vectorDot(a->profile, b->profile);
}

void sketchPrint(const Sketch *s, FILE *out) {
    vectorPrint(s->profile, out);
}
