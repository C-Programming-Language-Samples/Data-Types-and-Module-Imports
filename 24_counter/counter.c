//----------------------------------------------------------------------
// counter.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counter.h"

struct Counter {
    char *name;    // counter name
    int maxCount;  // maximum value
    int count;     // value
};

//----------------------------------------------------------------------

Counter *counterNew(const char *id, const int maxCount) {
    Counter *c = malloc(sizeof(Counter));
    c->name = malloc(strlen(id) + 1);
    strcpy(c->name, id);
    c->maxCount = maxCount;
    c->count = 0;
    return c;
}

void counterFree(Counter *c) {
    if (c == NULL) return;
    free(c->name);
    free(c);
}

void counterIncrement(Counter *c) {
    if (c->count < c->maxCount) c->count++;
}

int counterValue(const Counter *c) {
    return c->count;
}

char *counterToString(const Counter *c, char *buf, const size_t size) {
    snprintf(buf, size, "%s: %d", c->name, c->count);
    return buf;
}

int counterCompare(const Counter *a, const Counter *b) {
    return (a->count > b->count) - (a->count < b->count);
}
