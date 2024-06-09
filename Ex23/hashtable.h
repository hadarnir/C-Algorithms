#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure to represent an occurrence of a number in a file */
typedef struct Occurrence {
    char *filename;        /* Name of the file */
    int count;             /* Count of occurrences in the file */
    struct Occurrence *next; /* Pointer to the next occurrence */
} Occurrence;

/* Structure to represent a node in the hash table */
typedef struct {
    Occurrence *occurrences; /* Linked list of occurrences */
} HashNode;

/* Structure to represent the hash table */
typedef struct {
    HashNode buckets[29]; /* Fixed-size array for numbers 0-28 */
} HashTable;

/* Function prototypes */
/**
 * Create a new hash table.
 * @return Pointer to the newly created hash table.
 */
HashTable *create_table();

/**
 * Add an occurrence to the hash table.
 * @param table - Pointer to the hash table.
 * @param key - The number to add an occurrence for.
 * @param filename - Name of the file where the occurrence was found.
 */
void add_occurrence(HashTable *table, int key, const char *filename);

/**
 * Print occurrences from the hash table.
 * @param table - Pointer to the hash table.
 */
void print_occurrences(HashTable *table);

/**
 * Free the memory allocated for the hash table.
 * @param table - Pointer to the hash table to be freed.
 */
void free_table(HashTable *table);

#endif /* HASHTABLE_H */
