//----------------------------------------------------------------------
// counter.h
//----------------------------------------------------------------------

#ifndef COUNTER_H
#define COUNTER_H

#include <stddef.h>

// A named counter that counts from 0 up to a maximum value.
typedef struct Counter Counter;

// Return a new Counter with the given name and maximum value.
Counter *counterNew(const char *id, int maxCount);

// Free the memory used by c.
void counterFree(Counter *c);

// Add 1 to c, unless it is at its maximum.
void counterIncrement(Counter *c);

// Return the value of c.
int counterValue(const Counter *c);

// Write a string representation of c into buf and return buf.
char *counterToString(const Counter *c, char *buf, size_t size);

// Return a negative number, zero or a positive number as the value of a
// is less than, equal to or greater than the value of b.
int counterCompare(const Counter *a, const Counter *b);

#endif
