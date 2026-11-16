//----------------------------------------------------------------------
// 09_cat.c
//----------------------------------------------------------------------

#include <stdio.h>

//----------------------------------------------------------------------

// Main function: Copy the files named by all command-line arguments
// except the last to the file named by the last argument.
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <in1> [<in2> ...] <out>\n", argv[0]);
        return 1;
    }
    const char *outFilename = argv[argc - 1];
    FILE *out = fopen(outFilename, "wb");
    if (out == NULL) {
        fprintf(stderr, "Could not create %s\n", outFilename);
        return 1;
    }

    char buffer[4096];
    for (int i = 1; i < argc - 1; i++) {
        FILE *in = fopen(argv[i], "rb");
        if (in == NULL) {
            fprintf(stderr, "Could not open %s\n", argv[i]);
            fclose(out);
            return 1;
        }
        size_t n;
        while ((n = fread(buffer, 1, sizeof buffer, in)) > 0) {
            fwrite(buffer, 1, n, out);
        }
        fclose(in);
    }

    fclose(out);
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 09_cat 09_cat.c
// cat in1.txt
// This is
// cat in2.txt
// a tiny
// test.
// ./09_cat in1.txt in2.txt out.txt
// cat out.txt
// This is
// a tiny
// test.
