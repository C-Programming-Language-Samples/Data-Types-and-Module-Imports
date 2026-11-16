//----------------------------------------------------------------------
// 11_split.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIM ','
#define MAX_LINE 1024

//----------------------------------------------------------------------

// Main function: Accept string fileName and integer fieldCount as
// command-line arguments. Split the file fileName.csv by field into
// fieldCount files named fileName0.txt, fileName1.txt, and so on.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <fileName> <fieldCount>\n", argv[0]);
        return 1;
    }
    const char *fileName = argv[1];
    const int fieldCount = atoi(argv[2]);
    if (fieldCount <= 0) {
        fprintf(stderr, "fieldCount must be positive\n");
        return 1;
    }

    // Create the input stream.
    char name[256];
    snprintf(name, sizeof name, "%s.csv", fileName);
    FILE *in = fopen(name, "r");
    if (in == NULL) {
        fprintf(stderr, "Could not open %s\n", name);
        return 1;
    }

    // Create the output streams.
    FILE **outStreams = malloc(fieldCount * sizeof(FILE *));
    for (int i = 0; i < fieldCount; i++) {
        snprintf(name, sizeof name, "%s%d.txt", fileName, i);
        outStreams[i] = fopen(name, "w");
        if (outStreams[i] == NULL) {
            fprintf(stderr, "Could not create %s\n", name);
            for (int j = 0; j < i; j++) fclose(outStreams[j]);
            free(outStreams);
            fclose(in);
            return 1;
        }
    }

    // Read lines from the input stream and write each field to its
    // output stream.
    char line[MAX_LINE];
    while (fgets(line, sizeof line, in) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        const char *field = line;
        for (int i = 0; i < fieldCount && field != NULL; i++) {
            const char *delim = strchr(field, DELIM);
            const int length = (delim != NULL) ? (int)(delim - field) : (int)strlen(field);
            fprintf(outStreams[i], "%.*s\n", length, field);
            field = (delim != NULL) ? delim + 1 : NULL;
        }
    }

    for (int i = 0; i < fieldCount; i++) fclose(outStreams[i]);
    free(outStreams);
    fclose(in);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 11_split 11_split.c
// head -4 djia.csv
// Date,Open,High,Low,Close,Volume,Adj. Close*
// 17-Mar-06,11294.94,11294.94,11253.23,11279.65,2549619968,11279.65
// 16-Mar-06,11210.97,11324.80,11176.07,11253.24,2292179968,11253.24
// 15-Mar-06,11149.76,11258.28,11097.23,11209.77,2292999936,11209.77
// ./11_split djia 3
// head -4 djia0.txt
// Date
// 17-Mar-06
// 16-Mar-06
// 15-Mar-06
// head -4 djia1.txt
// Open
// 11294.94
// 11210.97
// 11149.76
// head -4 djia2.txt
// High
// 11294.94
// 11324.80
// 11258.28
