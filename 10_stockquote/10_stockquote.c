//----------------------------------------------------------------------
// 10_stockquote.c
//----------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include "stockquote.h"

//----------------------------------------------------------------------

// Main function: Accept a stock symbol as a command-line argument.
// Print the price of the stock.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <stockSymbol>\n", argv[0]);
        return 1;
    }
    const double price = stockquotePriceOf(argv[1]);
    if (isnan(price)) {
        fprintf(stderr, "No quote found for %s\n", argv[1]);
        return 1;
    }
    printf("%.2f\n", price);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 10_stockquote 10_stockquote.c stockquote.c
// ./10_stockquote goog
// 750.26
// ./10_stockquote adbe
// 92.17
