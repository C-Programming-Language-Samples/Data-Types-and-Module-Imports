//----------------------------------------------------------------------
// 25_vector.c
//----------------------------------------------------------------------

#include <stdio.h>
#include "vector.h"

//----------------------------------------------------------------------

// Print label, then v, then a newline.
static void printVector(const char *label, const Vector *v) {
    printf("%s", label);
    vectorPrint(v, stdout);
    printf("\n");
}

//----------------------------------------------------------------------

// Main function: Create and use some Vectors.
int main(void) {
    const double xCoords[] = {1.0, 2.0, 3.0, 4.0};
    const double yCoords[] = {5.0, 2.0, 4.0, 1.0};
    Vector *x = vectorNew(xCoords, 4);
    Vector *y = vectorNew(yCoords, 4);

    printVector("x        = ", x);
    printVector("y        = ", y);

    Vector *sum = vectorPlus(x, y);
    printVector("x + y    = ", sum);
    vectorFree(sum);

    Vector *scaled = vectorScale(x, 10.0);
    printVector("10x      = ", scaled);
    vectorFree(scaled);

    printf("|x|      = %.15g\n", vectorAbs(x));
    printf("<x, y>   = %.15g\n", vectorDot(x, y));

    Vector *difference = vectorMinus(x, y);
    printf("|x - y|  = %.15g\n", vectorAbs(difference));
    vectorFree(difference);

    vectorFree(x);
    vectorFree(y);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 25_vector 25_vector.c vector.c -lm
// ./25_vector
// x        = [1, 2, 3, 4]
// y        = [5, 2, 4, 1]
// x + y    = [6, 4, 7, 5]
// 10x      = [10, 20, 30, 40]
// |x|      = 5.47722557505166
// <x, y>   = 25
// |x - y|  = 5.09901951359278
