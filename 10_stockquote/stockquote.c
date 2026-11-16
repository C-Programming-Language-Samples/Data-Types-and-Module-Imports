//----------------------------------------------------------------------
// stockquote.c
//----------------------------------------------------------------------

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stockquote.h"

#ifndef QUOTES_DIR
#define QUOTES_DIR "../10_stockquote/quotes"
#endif

//----------------------------------------------------------------------

// Return the HTML of the quote page for symbol as a new string, or
// NULL if there is no such page.
static char *readHTML(const char *symbol) {
    // Quote pages are named by the upper-case symbol, e.g. GOOG.html
    char upper[32];
    size_t i = 0;
    for (; symbol[i] != '\0' && i < sizeof upper - 1; i++) {
        upper[i] = (char)toupper((unsigned char)symbol[i]);
    }
    upper[i] = '\0';

    char filename[256];
    snprintf(filename, sizeof filename, "%s/%s.html", QUOTES_DIR, upper);
    FILE *in = fopen(filename, "rb");
    if (in == NULL) return NULL;

    // Read the whole file, doubling the buffer when it fills up
    size_t capacity = 4096;
    size_t length = 0;
    char *html = malloc(capacity);
    size_t n;
    while ((n = fread(html + length, 1, capacity - length - 1, in)) > 0) {
        length += n;
        if (length == capacity - 1) {
            capacity *= 2;
            html = realloc(html, capacity);
        }
    }
    html[length] = '\0';
    fclose(in);
    return html;
}

//----------------------------------------------------------------------

double stockquotePriceOf(const char *symbol) {
    char *html = readHTML(symbol);
    if (html == NULL) return NAN;

    // The price is between the '>' after "yfs_l84" and the next "</span>"
    double price = NAN;
    const char *trade = strstr(html, "yfs_l84");
    const char *beg = (trade != NULL) ? strchr(trade, '>') : NULL;
    const char *end = (beg != NULL) ? strstr(beg, "</span>") : NULL;
    if (end != NULL) {
        // Copy the price, dropping commas
        char digits[64];
        size_t n = 0;
        for (const char *p = beg + 1; p < end && n < sizeof digits - 1; p++) {
            if (*p != ',') digits[n++] = *p;
        }
        digits[n] = '\0';

        char *rest;
        price = strtod(digits, &rest);
        if (rest == digits) price = NAN;
    }
    free(html);
    return price;
}
