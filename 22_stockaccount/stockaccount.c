//----------------------------------------------------------------------
// stockaccount.c
//----------------------------------------------------------------------

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "stockaccount.h"
#include "stockquote.h"

#define MAX_NAME 128   // longest customer name
#define MAX_SYMBOL 16  // longest stock symbol

typedef struct {
    int shares;               // share count
    char symbol[MAX_SYMBOL];  // stock symbol
} Position;

struct StockAccount {
    char name[MAX_NAME];  // customer name
    double cash;          // cash balance
    int stockCount;       // number of stocks
    Position *positions;  // the stocks held
};

//----------------------------------------------------------------------

StockAccount *stockAccountNew(const char *filename) {
    FILE *in = fopen(filename, "r");
    if (in == NULL) return NULL;

    StockAccount *acct = malloc(sizeof(StockAccount));
    acct->positions = NULL;

    bool ok = fgets(acct->name, sizeof acct->name, in) != NULL;
    if (ok) {
        acct->name[strcspn(acct->name, "\r\n")] = '\0';
        ok = fscanf(in, "%lf %d", &acct->cash, &acct->stockCount) == 2
          && acct->stockCount >= 0;
    }
    if (ok) {
        acct->positions = malloc(acct->stockCount * sizeof(Position));
        for (int i = 0; ok && i < acct->stockCount; i++) {
            ok = fscanf(in, "%d %15s", &acct->positions[i].shares,
                        acct->positions[i].symbol) == 2;
        }
    }
    fclose(in);

    if (!ok) {
        stockAccountFree(acct);
        return NULL;
    }
    return acct;
}

void stockAccountFree(StockAccount *acct) {
    if (acct == NULL) return;
    free(acct->positions);
    free(acct);
}

double stockAccountValueOf(const StockAccount *acct) {
    double total = acct->cash;
    for (int i = 0; i < acct->stockCount; i++) {
        const double price = stockquotePriceOf(acct->positions[i].symbol);
        const int amount = acct->positions[i].shares;
        total += amount * price;
    }
    return total;
}

void stockAccountWrite(const StockAccount *acct, FILE *out) {
    fprintf(out, "%s\n", acct->name);
    fprintf(out, "%.15g\n", acct->cash);
    fprintf(out, "%d\n", acct->stockCount);
    for (int i = 0; i < acct->stockCount; i++) {
        fprintf(out, "%3d %s\n", acct->positions[i].shares, acct->positions[i].symbol);
    }
}

void stockAccountWriteReport(const StockAccount *acct) {
    printf("%s\n", acct->name);
    double total = acct->cash;
    for (int i = 0; i < acct->stockCount; i++) {
        const int amount = acct->positions[i].shares;
        const char *symbol = acct->positions[i].symbol;
        const double price = stockquotePriceOf(symbol);
        total += amount * price;
        printf("%4d  %4s ", amount, symbol);
        printf("  %7.2f   %9.2f\n", price, amount * price);
    }
    printf("%21s %10.2f\n", "Cash:", acct->cash);
    printf("%21s %10.2f\n", "Total:", total);
}
