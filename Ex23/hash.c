#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

/**
 * Function to process a single file and add occurrences to the hash table.
 * @param table - Pointer to the hash table.
 * @param filename - Name of the file to be processed.
 */
void process_file(HashTable *table, const char *filename) {
    FILE *file;
    int number;

    /* Open the file for reading */
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    /* Read numbers from the file and add occurrences to the hash table */
    while (fscanf(file, "%d", &number) != EOF) {
        if (number >= 0 && number <= 28) {
            add_occurrence(table, number, filename);
        } else {
            fprintf(stderr, "Number %d in file %s is out of range [0, 28]\n", number, filename);
        }
    }

    /* Close the file */
    fclose(file);
}

/**
 * Main function to process files and display occurrences.
 * @param argc - Number of command line arguments.
 * @param argv - Array of command line arguments.
 * @return Exit status.
 */
int main(int argc, char *argv[]) {
    int i;
    HashTable *table;

    /* Check for proper usage */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Create the hash table */
    table = create_table();

    /* Process each file provided as an argument */
    for (i = 1; i < argc; i++) {
        process_file(table, argv[i]);
    }

    /* Print the occurrences of each number */
    print_occurrences(table);

    /* Free the allocated memory for the hash table */
    free_table(table);

    return EXIT_SUCCESS;
}
