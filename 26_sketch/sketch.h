//----------------------------------------------------------------------
// sketch.h
//----------------------------------------------------------------------

#ifndef SKETCH_H
#define SKETCH_H

#include <stdio.h>

// A profile of a text: a unit vector of dimension d whose element i
// counts the k-grams of the text that hash to i.
typedef struct Sketch Sketch;

// Return a new Sketch of text, using k-grams and dimension d.
Sketch *sketchNew(const char *text, int k, int d);

// Free the memory used by s.
void sketchFree(Sketch *s);

// Return the similarity of a and b, from 0 (dissimilar) to 1 (similar).
double sketchSimilarTo(const Sketch *a, const Sketch *b);

// Write s to out.
void sketchPrint(const Sketch *s, FILE *out);

#endif
