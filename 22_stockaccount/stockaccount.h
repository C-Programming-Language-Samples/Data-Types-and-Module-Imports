//----------------------------------------------------------------------
// stockaccount.h
//----------------------------------------------------------------------

#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H

#include <stdio.h>

// A customer's account: a name, a cash balance and shares of stocks.
typedef struct StockAccount StockAccount;

// Return a new StockAccount read from a file, or NULL on failure.
StockAccount *stockAccountNew(const char *filename);

// Free the memory used by acct.
void stockAccountFree(StockAccount *acct);

// Return the total value of acct in dollars.
double stockAccountValueOf(const StockAccount *acct);

// Write acct to out, in the same format it was read in.
void stockAccountWrite(const StockAccount *acct, FILE *out);

// Print a report of the stocks in acct and their values.
void stockAccountWriteReport(const StockAccount *acct);

#endif
