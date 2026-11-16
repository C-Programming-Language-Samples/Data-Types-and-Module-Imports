//----------------------------------------------------------------------
// 01_potentialgene.c
//----------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//----------------------------------------------------------------------

// Return true if the 3 bases starting at codon are a stop codon
// (TAA, TAG or TGA).
static bool isStopCodon(const char *codon) {
    return strncmp(codon, "TAA", 3) == 0
        || strncmp(codon, "TAG", 3) == 0
        || strncmp(codon, "TGA", 3) == 0;
}

// Return true if dna is a potential gene: its length is a multiple of
// 3, it starts with the start codon (ATG), it ends with a stop codon,
// and it has no intervening stop codons.
static bool isPotentialGene(const char *dna) {
    const size_t n = strlen(dna);

    // number of bases is a multiple of 3
    if (n % 3 != 0) return false;

    // starts with start codon
    if (strncmp(dna, "ATG", 3) != 0) return false;

    // no intervening stop codons
    for (size_t i = 0; i + 3 < n; i += 3) {
        if (isStopCodon(dna + i)) return false;
    }

    // ends with a stop codon
    return isStopCodon(dna + n - 3);
}

//----------------------------------------------------------------------

// Main function: Accept a DNA sequence as a command-line argument.
// Print True if it is a potential gene, and False otherwise.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <dna>\n", argv[0]);
        return 1;
    }
    printf("%s\n", isPotentialGene(argv[1]) ? "True" : "False");
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o 01_potentialgene 01_potentialgene.c
// ./01_potentialgene ATGCGCCTGCGTCTGTACTAG
// True
// ./01_potentialgene ATGCGCTGCGTCTGTACTAG
// False
