//----------------------------------------------------------------------
// 13_stopwatch.c
//----------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "stopwatch.h"

//----------------------------------------------------------------------

// Main function: Accept integer n as a command-line argument. Compute
// the sum of the squares of the integers from 1 to n with pow(i, 2) and
// with i * i. Print the ratio of the sums and the ratio of the times.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    const int n = atoi(argv[1]);

    double total1 = 0.0;
    const Stopwatch watch1 = stopwatchNew();
    for (int i = 1; i <= n; i++) {
        total1 += pow(i, 2.0);
    }
    const double time1 = stopwatchElapsedTime(watch1);

    double total2 = 0.0;
    const Stopwatch watch2 = stopwatchNew();
    for (int i = 1; i <= n; i++) {
        total2 += (double)i * i;
    }
    const double time2 = stopwatchElapsedTime(watch2);

    printf("%.15g\n", total1 / total2);
    printf("%.15g\n", time1 / time2);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 13_stopwatch 13_stopwatch.c stopwatch.c -lm
// ./13_stopwatch 100000000
// 1
// 2.47937085864163
