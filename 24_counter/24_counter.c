//----------------------------------------------------------------------
// 24_counter.c
//----------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "counter.h"

//----------------------------------------------------------------------

// Return true with probability p.
static bool bernoulli(const double p) {
    return rand() / (RAND_MAX + 1.0) < p;
}

//----------------------------------------------------------------------

// Main function: Accept integer n and float p as command-line
// arguments. Flip a coin with heads probability p n times, and print
// the number of heads and tails.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <n> <p>\n", argv[0]);
        return 1;
    }
    const int n = atoi(argv[1]);
    const double p = atof(argv[2]);
    srand(time(NULL));

    Counter *heads = counterNew("Heads", n);
    Counter *tails = counterNew("Tails", n);
    for (int i = 0; i < n; i++) {
        if (bernoulli(p)) counterIncrement(heads);
        else              counterIncrement(tails);
    }

    char buf[64];
    printf("%s\n", counterToString(heads, buf, sizeof buf));
    printf("%s\n", counterToString(tails, buf, sizeof buf));

    counterFree(heads);
    counterFree(tails);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 24_counter 24_counter.c counter.c
// ./24_counter 1000 .5
// Heads: 506
// Tails: 494

// ./24_counter 1000 .3
// Heads: 307
// Tails: 693
