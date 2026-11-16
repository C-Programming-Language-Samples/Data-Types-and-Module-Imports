//----------------------------------------------------------------------
// 20_complex.c
//----------------------------------------------------------------------

#include <stdio.h>
#include "complexnum.h"

//----------------------------------------------------------------------

// Main function: Compute z = z * z + z0 twice, starting at z0 = 1 + i,
// and print the result normally and with full precision.
int main(void) {
    const Complex z0 = complexNew(1.0, 1.0);
    Complex z = z0;
    z = complexAdd(complexMul(z, z), z0);
    z = complexAdd(complexMul(z, z), z0);

    char buf[64];
    printf("%s\n", complexToString(z, buf, sizeof buf));
    printf("%.17g + %.17gi\n", complexRe(z), complexIm(z));
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 20_complex 20_complex.c complexnum.c -lm
// ./20_complex
// -7 + 7i
// -7 + 7i
