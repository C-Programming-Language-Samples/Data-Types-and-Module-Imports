//----------------------------------------------------------------------
// 26_sketch.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "sketch.h"

//----------------------------------------------------------------------

// Read all of in into a new string.
static char *readAll(FILE *in) {
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
    return text;
}

//----------------------------------------------------------------------

// Main function: Accept integers k and d as command-line arguments.
// Read text from standard input and print its Sketch.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <k> <d> < text\n", argv[0]);
        return 1;
    }
    const int k = atoi(argv[1]);
    const int d = atoi(argv[2]);
    if (k <= 0 || d <= 0) {
        fprintf(stderr, "k and d must be positive\n");
        return 1;
    }

    char *text = readAll(stdin);
    Sketch *sketch = sketchNew(text, k, d);
    sketchPrint(sketch, stdout);
    printf("\n");

    sketchFree(sketch);
    free(text);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 26_sketch 26_sketch.c sketch.c ../25_vector/vector.c -I../25_vector -lm
// cat genome20.txt
// ATAGATGCATAGCGCATAGC
// ./26_sketch 2 16 < genome20.txt
// [0, 0, 0, 0.620173672946042, 0.124034734589208, 0, 0.372104203767625, 0, 0, 0, 0.124034734589208, 0, 0.496138938356834, 0.372104203767625, 0.248069469178417, 0]
