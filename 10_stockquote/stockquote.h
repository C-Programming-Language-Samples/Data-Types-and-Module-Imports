//----------------------------------------------------------------------
// stockquote.h
//----------------------------------------------------------------------

#ifndef STOCKQUOTE_H
#define STOCKQUOTE_H

// Return the price of the stock with the given symbol, read from its
// quote page in ../10_stockquote/quotes, or NAN if there is none.
double stockquotePriceOf(const char *symbol);

#endif
