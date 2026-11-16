//----------------------------------------------------------------------
// 27_comparedocuments.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sketch.h"

#define MAX_FILENAME 256

//----------------------------------------------------------------------

// Return the contents of a file as a new string, or NULL on failure.
static char *readFile(const char *filename) {
    FILE *in = fopen(filename, "rb");
    if (in == NULL) return NULL;
    size_t capacity = 4096;
    size_t length = 0;
    char *text = malloc(capacity);
    size_t n;
    while ((n = fread(text + length, 1, capacity - length - 1, in)) > 0) {
        length += n;
        if (length == capacity - 1) {
            capacity *= 2;
            text = realloc(text, capacity);
        }
    }
    text[length] = '\0';
    fclose(in);
    return text;
}

// Return the part of path after its last '/'.
static const char *baseName(const char *path) {
    const char *slash = strrchr(path, '/');
    return (slash != NULL) ? slash + 1 : path;
}

//----------------------------------------------------------------------

// Main function: Accept integers k and d as command-line arguments.
// Read a list of file names from standard input, and print a table of
// the similarity of every pair of files.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <k> <d> < documents.txt\n", argv[0]);
        return 1;
    }
    const int k = atoi(argv[1]);
    const int d = atoi(argv[2]);
    if (k <= 0 || d <= 0) {
        fprintf(stderr, "k and d must be positive\n");
        return 1;
    }

    // Read the file names.
    int count = 0;
    int capacity = 8;
    char **filenames = malloc(capacity * sizeof(char *));
    char name[MAX_FILENAME];
    while (scanf("%255s", name) == 1) {
        if (count == capacity) {
            capacity *= 2;
            filenames = realloc(filenames, capacity * sizeof(char *));
        }
        filenames[count] = malloc(strlen(name) + 1);
        strcpy(filenames[count], name);
        count++;
    }

    // Build one Sketch per file.
    Sketch **sketches = malloc(count * sizeof(Sketch *));
    int built = 0;
    for (; built < count; built++) {
        char *text = readFile(filenames[built]);
        if (text == NULL) {
            fprintf(stderr, "Could not read %s\n", filenames[built]);
            break;
        }
        sketches[built] = sketchNew(text, k, d);
        free(text);
    }

    // Print the table.
    if (built == count) {
        printf("    ");
        for (int i = 0; i < count; i++) {
            printf("%8.4s", baseName(filenames[i]));
        }
        printf("\n");
        for (int i = 0; i < count; i++) {
            printf("%.4s", baseName(filenames[i]));
            for (int j = 0; j < count; j++) {
                printf("%8.2f", sketchSimilarTo(sketches[i], sketches[j]));
            }
            printf("\n");
        }
    }

    for (int i = 0; i < built; i++) sketchFree(sketches[i]);
    for (int i = 0; i < count; i++) free(filenames[i]);
    free(sketches);
    free(filenames);
    return (built == count) ? 0 : 1;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 27_comparedocuments 27_comparedocuments.c ../26_sketch/sketch.c ../25_vector/vector.c -I../26_sketch -I../25_vector -lm
// cat documents.txt
// constitution.txt
// tomsawyer.txt
// huckfinn.txt
// prejudice.txt
// ../25_vector/vector.c
// ../11_split/djia.csv
// amazon.html
// actg.txt
// ./27_comparedocuments 5 10000 < documents.txt
//         cons    toms    huck    prej    vect    djia    amaz    actg
// cons    1.00    0.66    0.60    0.64    0.06    0.18    0.21    0.11
// toms    0.66    1.00    0.93    0.88    0.05    0.24    0.18    0.14
// huck    0.60    0.93    1.00    0.82    0.04    0.23    0.16    0.12
// prej    0.64    0.88    0.82    1.00    0.05    0.25    0.19    0.15
// vect    0.06    0.05    0.04    0.05    1.00    0.03    0.07    0.02
// djia    0.18    0.24    0.23    0.25    0.03    1.00    0.16    0.11
// amaz    0.21    0.18    0.16    0.19    0.07    0.16    1.00    0.07
// actg    0.11    0.14    0.12    0.15    0.02    0.11    0.07    1.00
