//----------------------------------------------------------------------
// stopwatch.h
//----------------------------------------------------------------------

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <time.h>

// A stopwatch that measures processor time.
typedef struct {
    clock_t start;  // processor time at creation
} Stopwatch;

// Return a new Stopwatch, already running.
Stopwatch stopwatchNew(void);

// Return the time in seconds since watch was created.
double stopwatchElapsedTime(Stopwatch watch);

#endif
