//----------------------------------------------------------------------
// 22_stockaccount.c
//----------------------------------------------------------------------

#include <stdio.h>
#include "stockaccount.h"

//----------------------------------------------------------------------

// Main function: Accept the name of an account file as a command-line
// argument. Read the account and print a report.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <accountFile>\n", argv[0]);
        return 1;
    }
    StockAccount *acct = stockAccountNew(argv[1]);
    if (acct == NULL) {
        fprintf(stderr, "Could not read account file %s\n", argv[1]);
        return 1;
    }
    stockAccountWriteReport(acct);
    stockAccountFree(acct);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 22_stockaccount 22_stockaccount.c stockaccount.c ../10_stockquote/stockquote.c -I../10_stockquote
// cat turing.txt
// Turing, Alan
// 10.24
// 4
// 100 ADBE
//  25 GOOG
//  97 IBM
// 250 MSFT
// ./22_stockaccount turing.txt
// Turing, Alan
//  100  ADBE     92.17     9217.00
//   25  GOOG    750.26    18756.50
//   97   IBM    138.46    13430.62
//  250  MSFT     53.93    13482.50
//                 Cash:      10.24
//                Total:   54896.86
