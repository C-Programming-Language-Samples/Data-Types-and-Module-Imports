//----------------------------------------------------------------------
// stopwatch.c
//----------------------------------------------------------------------

#include "stopwatch.h"

//----------------------------------------------------------------------

Stopwatch stopwatchNew(void) {
    return (Stopwatch){clock()};
}

double stopwatchElapsedTime(const Stopwatch watch) {
    return (double)(clock() - watch.start) / CLOCKS_PER_SEC;
}
